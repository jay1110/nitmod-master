#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_hudstats.h"

/* Commands execute before snapshot transition. Cache one immutable copy for
 * each actual snapshot buffer, so future commands cannot alter old counters. */
typedef struct { qboolean valid; int time,target,values[5]; } hudStats_t;
static hudStats_t history[128], snapshots[2];
static unsigned int cursor;
void CG_NitmodResetNativeHudStats(void) {
    memset(history,0,sizeof(history));memset(snapshots,0,sizeof(snapshots));cursor=0;
}
qboolean CG_NitmodNativeHudStatsCommand(const char *command) {
    hudStats_t next;int i;
    if(strcmp(command,"nls")) return qfalse;
    if(NITMOD_UsesOriginalProtocol() || !NITMOD_ServerSupports(NITMOD_FEATURE_HUD_STATS) || trap_Argc()!=8) return qtrue;
    memset(&next,0,sizeof(next));
    if(!NITMOD_ParseProtocolSigned(CG_Argv(1),&next.time) ||
       !NITMOD_ParseProtocolInteger(CG_Argv(2),&next.target) || next.target<0 || next.target>=MAX_CLIENTS) return qtrue;
    for(i=0;i<5;++i) if(!NITMOD_ParseProtocolSigned(CG_Argv(i+3),&next.values[i])) return qtrue;
    next.valid=qtrue;history[cursor++%128]=next;
    return qtrue;
}
void CG_NitmodCaptureNativeHudStats(const snapshot_t *snap) {
    int slot,i;
    hudStats_t *out;
    if(!snap || NITMOD_UsesOriginalProtocol()) return;
    for(slot=0;slot<2;++slot) if(snap==&cg.activeSnapshots[slot]) break;
    if(slot==2) return;
    out=&snapshots[slot];memset(out,0,sizeof(*out));
    if(!NITMOD_ServerSupports(NITMOD_FEATURE_HUD_STATS)) return;
    for(i=0;i<128 && (unsigned int)i<cursor;++i) {
        const hudStats_t *candidate=&history[(cursor-1U-(unsigned int)i)%128];
        if(candidate->valid && candidate->target==snap->ps.clientNum && candidate->time<=snap->serverTime &&
           (!out->valid || candidate->time>out->time)) {
            *out=*candidate;
        }
    }
    if(out->valid) out->time=snap->serverTime;
}
qboolean CG_NitmodNativeHudStat(const playerState_t *state,int row,int *value) {
    int slot;
    if(!state || !value || row<0 || row>=5 || NITMOD_UsesOriginalProtocol()) return qfalse;
    for(slot=0;slot<2;++slot) if(state==&cg.activeSnapshots[slot].ps && snapshots[slot].valid &&
       snapshots[slot].time==cg.activeSnapshots[slot].serverTime && snapshots[slot].target==state->clientNum) {
        *value=snapshots[slot].values[row];return qtrue;
    }
    return qfalse;
}
