#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_log.h"

static fileHandle_t nitmodClientLog;

void CG_NitmodLogLine(char *out, int size, const qtime_t *now, const char *text) {
    if(!out || size <= 0) return;
    if(!now || !text) {
        out[0] = '\0';
        return;
    }
    Com_sprintf(out, size, "[%02d:%02d:%02d] %s", now->tm_hour, now->tm_min, now->tm_sec, text);
}

void CG_NitmodLogInit(void) {
    CG_NitmodLogShutdown();
    if(!cg_clientLog.integer || !cg_logFile.string[0]) {
        CG_Printf("Not logging client output to disk.\n");
        return;
    }
    trap_FS_FOpenFile(cg_logFile.string, &nitmodClientLog, FS_APPEND);
    if(!nitmodClientLog)
        CG_Printf("^3WARNING: Couldn't open client log: %s\n", cg_logFile.string);
}

void CG_NitmodLogShutdown(void) {
    if(nitmodClientLog) {
        trap_FS_FCloseFile(nitmodClientLog);
        nitmodClientLog = 0;
    }
}

void CG_NitmodLogText(const char *text) {
    char line[1024];
    qtime_t now;
    int length;
    if(!nitmodClientLog || !text || !text[0]) return;
    trap_RealTime(&now);
    CG_NitmodLogLine(line, sizeof(line), &now, text);
    length = strlen(line);
    if(length > 0) trap_FS_Write(line, length, nitmodClientLog);
}
