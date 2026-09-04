#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_autoexec.h"

/* Original ELF oldTeam.12005 / oldCls.12006 both initialize to -1.
 * These track attempted transitions, including absent optional files. */
static int previousTeam = -1, previousClass = -1;

void CG_NitmodResetAutoexec(void) {
    previousTeam = previousClass = -1;
}

static qboolean ExecOptionalConfig(const char *stem) {
    char path[MAX_QPATH], command[MAX_QPATH + 8];
    int handle;
    Com_sprintf(path, sizeof(path), "autoexec_%s.cfg", stem);
    handle = trap_PC_LoadSource(path);
    if(handle <= 0) return qfalse;
    trap_PC_FreeSource(handle);
    Com_sprintf(command, sizeof(command), "exec %s\n", path);
    trap_SendConsoleCommand(command);
    return qtrue;
}

/* Original CG_Init selects the map-specific file OR the default, not both.
 * Unlike respawn configs this also runs when initializing demo playback. */
void CG_NitmodMapAutoexec(void) {
    int i;
    qboolean valid = qtrue;
    if(!NITMOD_UsesOriginalProtocol()) return;
    for(i = 0; i < sizeof(cgs.rawmapname) && cgs.rawmapname[i]; ++i) {
        unsigned char c = cgs.rawmapname[i];
        if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
             (c >= '0' && c <= '9') || c == '_' || c == '-' || c == '.')) valid = qfalse;
    }
    /* Reserve autoexec_ + .cfg + NUL; never execute a truncated filename. */
    if(!i || i > MAX_QPATH - 14) valid = qfalse;
    if(!valid || !ExecOptionalConfig(cgs.rawmapname)) ExecOptionalConfig("default");
}

/* Original CG_Respawn runs class first, then team, only on a real respawn.
 * Fixed stems preserve filename case and never interpolate server text. */
void CG_NitmodRespawnAutoexec(qboolean revived) {
    static const char *classes[NUM_PLAYER_CLASSES] = {
        "Soldier", "Medic", "Engineer", "Fieldops", "Covertops"
    };
    static const char *teams[] = { "free", "axis", "allies", "spectator" };
    const clientInfo_t *client;
    int team, playerClass;
    if(revived || cg.demoPlayback || !cg.snap || !NITMOD_UsesOriginalProtocol() ||
       cg.clientNum < 0 || cg.clientNum >= MAX_CLIENTS) return;
    client = &cgs.clientinfo[cg.clientNum];
    team = client->team; playerClass = client->cls;
    if(team < TEAM_FREE || team > TEAM_SPECTATOR) return;
    if((team == TEAM_AXIS || team == TEAM_ALLIES) &&
       playerClass >= 0 && playerClass < NUM_PLAYER_CLASSES && playerClass != previousClass) {
        ExecOptionalConfig(classes[playerClass]);
        previousClass = playerClass;
    }
    if(team != previousTeam) {
        ExecOptionalConfig(teams[team]);
        previousTeam = team;
    }
}
