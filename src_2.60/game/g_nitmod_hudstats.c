#include "g_local.h"
#include "g_nitmod_config.h"
#include "g_nitmod_hudstats.h"

/* Original sends these five integers in playerState.persistant. Native ET
 * owns those slots; a negotiated reliable snapshot companion preserves the
 * values without changing the engine ABI or truncating them to 16 bits. */
static struct { qboolean valid; int target,values[5]; } lastStats[MAX_CLIENTS];
void G_NITMOD_ResetHudStats(int n) {
    if(n<0) memset(lastStats,0,sizeof(lastStats));
    else if(n<MAX_CLIENTS) memset(&lastStats[n],0,sizeof(lastStats[n]));
}
void G_NITMOD_SendHudStats(void) {
    int n,i,target,values[5];
    for(n=0;n<level.maxclients && n<MAX_CLIENTS;++n) {
        gclient_t *viewer=g_entities[n].client,*subject;
        if(!viewer || viewer->pers.connected!=CON_CONNECTED || (g_entities[n].r.svFlags&SVF_BOT) ||
           !G_NITMOD_ClientSupports(n,NITMOD_FEATURE_HUD_STATS)) {lastStats[n].valid=qfalse;continue;}
        target=viewer->ps.clientNum;
        if(target<0 || target>=MAX_CLIENTS || !(subject=g_entities[target].client)) continue;
        values[0]=subject->nitmodLuaPersistant[15];
        values[1]=subject->nitmodLuaPersistant[6];
        values[2]=subject->nitmodLuaPersistant[5];
        values[3]=subject->nitmodLuaPersistant[3];
        values[4]=subject->ps.persistant[PERS_KILLED];
        if(lastStats[n].valid && lastStats[n].target==target && !memcmp(lastStats[n].values,values,sizeof(values))) continue;
        trap_SendServerCommand(n,va("nls %d %d %d %d %d %d %d",level.time,target,values[0],values[1],values[2],values[3],values[4]));
        lastStats[n].valid=qtrue;lastStats[n].target=target;
        for(i=0;i<5;++i) lastStats[n].values[i]=values[i];
    }
}
