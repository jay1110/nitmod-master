/* Emscripten-only smoke test, not an ET engine or gameplay fixture. */
#include "../src_2.60/game/q_shared.h"
#include "../src_2.60/game/g_public.h"
#include "../src_2.60/cgame/cg_public.h"
#include "../src_2.60/ui/ui_public.h"
#include <dlfcn.h>

#include <stdint.h>
#include "../src_2.60/game/nitmod_syscall_abi.h"
typedef intptr_t (*syscall_t)(intptr_t *);
typedef void (*entry_t)(syscall_t);
/* Match ET:Legacy VM_EntryPoint_t, including qagame: 13 wasm32 slots. */
typedef int (*gameMain_t)(int, int, int, int, int, int, int, int, int, int, int, int, int);
typedef int (*clientMain_t)(int, int, int, int, int, int, int, int, int, int, int, int, int);

static int expectedArgvCommand, expectedArgvSize, argvCalls;
static const char *argvResponse;

static int slotCount;
static intptr_t CheckSlots(intptr_t *args) {
    int i;
    for(i = 0; i < slotCount; ++i) if(args[i] != i - 1) exit(2);
    return -123;
}

static int CheckArrayPacking(void) {
    nitmod_syscall_t nitmodSyscall = CheckSlots;
    int value = -1;
    slotCount = 1;
    if(NITMOD_SYSCALL(value++) != -123 || value != 0) return 1;
    slotCount = 4;
    if(NITMOD_SYSCALL(-1, 0, 1, 2) != -123) return 1;
    slotCount = 16;
    return NITMOD_SYSCALL(-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14) != -123;
}

/* A narrow engine double: validate the array command/int/pointer/int tuple and
 * write into module-owned memory. No other syscall is accepted. */
static intptr_t ArgvSyscall(intptr_t *args) {
    int command = (int)args[0];
    int index, size;
    char *buffer;
    if(command != expectedArgvCommand || argvCalls != 0) {
        fprintf(stderr, "Unexpected or repeated argv syscall: %d\n", command);
        exit(2);
    }
    index = (int)args[1];
    buffer = (char *)args[2];
    size = (int)args[3];
    if(index != 0 || !buffer || size != expectedArgvSize ||
       strlen(argvResponse) + 1 > (size_t)size) {
        fprintf(stderr, "Invalid argv tuple: index=%d size=%d\n", index, size);
        exit(2);
    }
    ++argvCalls;
    memcpy(buffer, argvResponse, strlen(argvResponse) + 1);
    return 0;
}

static void BeginArgvProbe(entry_t entry, int command, int size, const char *response) {
    expectedArgvCommand = command;
    expectedArgvSize = size;
    argvResponse = response;
    argvCalls = 0;
    entry(ArgvSyscall);
}

static intptr_t RejectSyscall(intptr_t *args) {
    fprintf(stderr, "Unexpected syscall in pre-init probe: %d\n", (int)args[0]);
    exit(2);
    return 0;
}

static int botCvarUpdates;
static int injectMemoryDump, memoryDumpStep;
static intptr_t TraceBotFrame(intptr_t *args) {
    if(args[0] == G_CVAR_UPDATE && botCvarUpdates < 7 && args[1]) {
        /* Baseline leaves cvars untouched; the opt-in probe updates memorydump. */
        ++botCvarUpdates;
        if(injectMemoryDump && botCvarUpdates == 7) {
            vmCvar_t *cvar = (vmCvar_t *)args[1];
            cvar->integer = 1;
            cvar->value = 1.0f;
            memcpy(cvar->string, "1", 2);
        }
        return 0;
    }
    if(injectMemoryDump && botCvarUpdates == 7 &&
       (args[0] == BOTLIB_LIBVAR_SET || args[0] == G_CVAR_SET) && args[1] && args[2] &&
       !strcmp((const char *)args[1], "memorydump")) {
        if(memoryDumpStep == 0 && args[0] == BOTLIB_LIBVAR_SET &&
           !strcmp((const char *)args[2], "1")) {
            memoryDumpStep = 1;
            return 0;
        }
        if(memoryDumpStep == 1 && args[0] == G_CVAR_SET &&
           !strcmp((const char *)args[2], "0")) {
            memoryDumpStep = 2;
            return 0;
        }
    }
    if(args[0] == BOTLIB_START_FRAME && botCvarUpdates == 7 && args[1] == 0) {
        if(injectMemoryDump && memoryDumpStep != 2) exit(2);
        if(injectMemoryDump) puts("Cvar writeback consumed: memorydump=1 causes Botlib set(1), then engine reset(0)");
        printf("Observed bot limitation: seven G_CVAR_UPDATE calls then BOTLIB_START_FRAME (%d), time bits=0\n", (int)args[0]);
        /* Stop this isolated process at the unsupported boundary. */
        exit(0);
    }
    fprintf(stderr, "Unexpected bot probe syscall: %d after %d updates\n", (int)args[0], botCvarUpdates);
    exit(2);
    return 0;
}

static int ProbeBotFrame(const char *path) {
    void *handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    entry_t entry;
    gameMain_t call;
    if(!handle) return 1;
    entry = (entry_t)dlsym(handle, "dllEntry");
    call = (gameMain_t)dlsym(handle, "vmMain");
    if(!entry || !call) return 1;
    entry(TraceBotFrame);
    call(BOTAI_START_FRAME, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    fprintf(stderr, "Expected bot syscall was not observed\n");
    return 1;
}

static int CheckClient(clientMain_t call, int command, int expected) {
    int actual = call(command, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(actual != expected) {
        fprintf(stderr, "command %d: expected %d, got %d\n", command, expected, actual);
        return 1;
    }
    return 0;
}

/* Local Legacy header audit pins CG_CONSOLE_COMPLETE_ARGUMENT to 1338.
 * It is deliberately NOT added to the ET 2.60 production export enum. */
static intptr_t TraceUnsupportedExtension(intptr_t *args) {
    if(args[0] == CG_ERROR && args[1] &&
       !strcmp((const char *)args[1], "vmMain: unknown command 1338")) {
        puts("Observed expected cgame CG_ERROR for unsupported extension 1338");
        exit(0);
    }
    fprintf(stderr, "Unexpected extension-probe callback: %d\n", (int)args[0]);
    exit(2);
    return 0;
}

static int ProbeUnsupportedExtension(const char *path) {
    void *handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    entry_t entry;
    clientMain_t call;
    if(!handle) return 1;
    entry = (entry_t)dlsym(handle, "dllEntry");
    call = (clientMain_t)dlsym(handle, "vmMain");
    if(!entry || !call) return 1;
    entry(TraceUnsupportedExtension);
    call(1338, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    fputs("Expected extension error was not observed\n", stderr);
    return 1;
}

int main(int argc, char **argv) {
    void *handles[3];
    int i, opened = 0, failed = 0;
    if(CheckArrayPacking()) return 2;
    if(argc == 3 && !strcmp(argv[1], "--cvar-probe")) {
        injectMemoryDump = 1;
        return ProbeBotFrame(argv[2]);
    }
    if(argc == 3 && !strcmp(argv[1], "--botlib-probe")) return ProbeBotFrame(argv[2]);
    if(argc == 3 && !strcmp(argv[1], "--extension-probe")) return ProbeUnsupportedExtension(argv[2]);
    if(argc < 2 || argc > 4) return 1;
    for(i = 1; i < argc; ++i) {
        void *handle = dlopen(argv[i], RTLD_NOW | RTLD_LOCAL);
        void *mainAddress;
        entry_t entry;
        const char *name = strrchr(argv[i], '/');
        name = name ? name + 1 : argv[i];
        if(!handle) { fprintf(stderr, "dlopen: %s\n", dlerror()); failed = 1; break; }
        handles[opened++] = handle;
        entry = (entry_t)dlsym(handle, "dllEntry");
        mainAddress = dlsym(handle, "vmMain");
        if(!entry || !mainAddress) { failed = 1; break; }
        {
            int (*abi)(void) = (int (*)(void))dlsym(handle, "vmWasmAbi1");
            if(!abi || abi() != 1) { failed = 1; break; }
        }
        entry(RejectSyscall);
        if(!strcmp(name, "qagame.mp.wasm32.so")) {
            gameMain_t call = (gameMain_t)mainAddress;
            failed = call(GAME_MESSAGERECEIVED, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) != -1;
            failed |= call(-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) != -1;
            BeginArgvProbe(entry, G_ARGV, MAX_TOKEN_CHARS, "__nitmod_smoke_unknown__");
            failed |= call(GAME_CONSOLE_COMMAND, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) != qfalse;
            failed |= argvCalls != 1;
            entry(RejectSyscall);
        } else if(!strcmp(name, "cgame.mp.wasm32.so")) {
            clientMain_t call = (clientMain_t)mainAddress;
            failed = CheckClient(call, CG_MESSAGERECEIVED, -1);
            failed |= CheckClient(call, CG_WANTSBINDKEYS, 0);
        } else if(!strcmp(name, "ui.mp.wasm32.so")) {
            clientMain_t call = (clientMain_t)mainAddress;
            failed = CheckClient(call, UI_GETAPIVERSION, UI_API_VERSION);
            failed |= CheckClient(call, UI_HASUNIQUECDKEY, qtrue);
            failed |= CheckClient(call, UI_WANTSBINDKEYS, qfalse);
            BeginArgvProbe(entry, UI_ARGV, MAX_STRING_CHARS, "ui_cdkey");
            failed |= CheckClient(call, UI_CONSOLE_COMMAND, qtrue);
            failed |= argvCalls != 1;
            entry(RejectSyscall);
        } else { failed = 1; }
        if(failed) { fprintf(stderr, "entrypoint probe failed: %s\n", name); break; }
        printf("entrypoint probes passed: %s\n", name);
    }
    while(opened) if(dlclose(handles[--opened])) failed = 1;
    return failed;
}
