#include "g_local.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_omnibot.h"
#include "g_nitmod_etbot_lifecycle.h"

#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

typedef int (*nitmodOmniBotExport_t)(void *functions, int size);

typedef struct {
	void *initialize;
	void *update;
	void *shutdown;
	void *consoleCommand;
	void *sendTrigger;
	void *addBlackboardRecord;
	void *sendEvent;
	void *sendGlobalEvent;
	void *addGoal;
	void *deleteGoal;
	void *updateEntity;
} nitmodOmniBotExports_t;

typedef enum {
	NITMOD_OMNIBOT_UNCHECKED,
	NITMOD_OMNIBOT_NOT_FOUND,
	NITMOD_OMNIBOT_NO_EXPORT,
	NITMOD_OMNIBOT_BAD_EXPORTS,
	NITMOD_OMNIBOT_PROBED
} nitmodOmniBotProbe_t;

static nitmodOmniBotProbe_t omniBotProbe;
static char omniBotProbeError[256];

/*
 * The original 2.3.5 qagame loads the base name "omnibot_et" and requests
 * ExportBotFunctionsFromDLL, interface version 17.  Emscripten's dlopen can
 * only see a side module that the browser preloaded under this exact name.
 *
 * The typed ETInterface adapter owns initialization and gameplay callbacks;
 * this helper only exposes the selected module/path for diagnostics.
 */
const char *G_NITMOD_OmniBotModuleName(void) {
#ifdef __EMSCRIPTEN__
	return "omnibot_et.wasm32.so";
#elif defined(_WIN32)
	return "omnibot_et.dll";
#elif defined(__APPLE__)
	return "omnibot_et_mac.so";
#else
	return "omnibot_et.so";
#endif
}

void G_NITMOD_OmniBotExpectedPath(char *buffer, int bufferSize) {
	char directory[MAX_OSPATH];
	int length;

	if (!buffer || bufferSize <= 0) {
		return;
	}
	trap_Cvar_VariableStringBuffer("omnibot_path", directory, sizeof(directory));
	if (!directory[0]) {
		Q_strncpyz(buffer, G_NITMOD_OmniBotModuleName(), bufferSize);
		return;
	}
	length = (int)strlen(directory);
	Com_sprintf(buffer, bufferSize, "%s%s%s", directory,
		(directory[length - 1] == '/' || directory[length - 1] == '\\') ? "" : "/",
		G_NITMOD_OmniBotModuleName());
}

int G_NITMOD_OmniBotProbe(void) {
	char path[MAX_OSPATH];
	nitmodOmniBotExports_t exports;
	nitmodOmniBotExport_t exportFunctions;
	int result;
#if defined(_WIN32)
	HMODULE library;
#else
	void *library;
#endif

	omniBotProbeError[0] = '\0';
	memset(&exports, 0, sizeof(exports));
	G_NITMOD_OmniBotExpectedPath(path, sizeof(path));
#if defined(_WIN32)
	library = LoadLibraryA(path);
#else
	dlerror();
	library = dlopen(path, RTLD_NOW | RTLD_LOCAL);
#endif
	if (!library) {
#if defined(_WIN32)
		Com_sprintf(omniBotProbeError, sizeof(omniBotProbeError), "LoadLibrary error %lu", (unsigned long)GetLastError());
#else
		const char *error = dlerror();
		Q_strncpyz(omniBotProbeError, error ? error : "dlopen failed", sizeof(omniBotProbeError));
#endif
		omniBotProbe = NITMOD_OMNIBOT_NOT_FOUND;
		return 0;
	}

#if defined(_WIN32)
	exportFunctions = (nitmodOmniBotExport_t)GetProcAddress(library, "ExportBotFunctionsFromDLL");
#else
	exportFunctions = (nitmodOmniBotExport_t)dlsym(library, "ExportBotFunctionsFromDLL");
#endif
	if (!exportFunctions) {
		Q_strncpyz(omniBotProbeError, "ExportBotFunctionsFromDLL is missing", sizeof(omniBotProbeError));
		omniBotProbe = NITMOD_OMNIBOT_NO_EXPORT;
	} else {
		result = exportFunctions(&exports, sizeof(exports));
		if (result || !exports.initialize || !exports.update || !exports.shutdown) {
			Com_sprintf(omniBotProbeError, sizeof(omniBotProbeError), "export result=%i, required callbacks incomplete", result);
			omniBotProbe = NITMOD_OMNIBOT_BAD_EXPORTS;
		} else {
			omniBotProbe = NITMOD_OMNIBOT_PROBED;
		}
	}

#if defined(_WIN32)
	FreeLibrary(library);
#else
	dlclose(library);
#endif
	return omniBotProbe == NITMOD_OMNIBOT_PROBED;
}

void G_NITMOD_OmniBotConsoleCommand(void) {
	char action[32];

	trap_Argv(1, action, sizeof(action));
	if (!action[0] || !Q_stricmp(action, "status")) {
		G_NITMOD_OmniBotReportStatus();
		return;
	}
	if (!Q_stricmp(action, "load") || !Q_stricmp(action, "reload")) {
		G_NITMOD_OmniBotProbe();
		G_NITMOD_OmniBotReportStatus();
		return;
	}
	if (!Q_stricmp(action, "unload")) {
		omniBotProbe = NITMOD_OMNIBOT_UNCHECKED;
		omniBotProbeError[0] = '\0';
		trap_Cvar_Set("omnibot_playing", "0");
		G_Printf("Omni-bot probe state cleared\n");
		return;
	}
	G_Printf("usage: omnibot [status|load|reload|unload]\n");
}

void G_NITMOD_OmniBotReportStatus(void) {
	char path[MAX_OSPATH];
	int enabled = G_NITMOD_LegacyCvarInteger("omnibot_enable", 0);
	qboolean loaded = Bot_Interface_IsLoaded();
	const char *loadedPath = Bot_Interface_LibraryPath();

	G_NITMOD_OmniBotExpectedPath(path, sizeof(path));
	G_Printf("Omni-bot status: enabled=%i loaded=%i interface=17 probe=%i\n",
		enabled, loaded, (int)omniBotProbe);
	G_Printf("Omni-bot module: %s\n",
		loadedPath && loadedPath[0] ? loadedPath : path);
	if (omniBotProbeError[0]) {
		G_Printf("Omni-bot probe error: %s\n", omniBotProbeError);
	}
	G_Printf("Omni-bot adapter: typed ETInterface active=%i\n", loaded);
}

void G_NITMOD_OmniBotStartup(void) {
	if (!G_NITMOD_LegacyCvarInteger("omnibot_enable", 0)) {
		trap_Cvar_Set("omnibot_playing", "0");
		return;
	}

	Bot_Interface_InitHandles();
	if (!Bot_Interface_Init()) {
		G_Printf("^1Omni-bot: typed ETInterface initialization failed.\n");
	}
	G_NITMOD_OmniBotReportStatus();
}
