#include "g_local.h"
#include "g_nitmod_global_stats.h"
#include "g_nitmod_lua.h"
#include "nitmod_stats_transport.h"
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include "nitmod_global_awards.h"
static struct { char guid[33]; int pending,ready,awards,uploaded; long long retryAfter; int values[15],local[16]; } stats[MAX_CLIENTS];
static char endpoint[MAX_CVAR_VALUE_STRING];
/* Preserve the original signed 32-bit wire arithmetic without C overflow UB. */
static int Total(int n,int index) {
    unsigned int value=(unsigned int)stats[n].local[index];
    if(stats[n].ready && index<15) value+=(unsigned int)stats[n].values[index];
    return value<=INT_MAX ? (int)value : -1-(int)(UINT_MAX-value);
}
void G_NITMOD_GlobalStatsEvent(int n,int statistic) {
    int i,total;
    if(!*endpoint || n<0 || n>=level.maxclients || n>=MAX_CLIENTS ||
       !g_entities[n].client || (g_entities[n].r.svFlags&SVF_BOT) || statistic<0 || statistic>=16) return;
    if(g_gamestate.integer==GS_PLAYING) {
        int value=stats[n].local[statistic];
        stats[n].local[statistic]=value==INT_MAX ? INT_MIN : value+1;
    }
    stats[n].awards=0;
    for(i=0;i<(int)(sizeof(globalAwards)/sizeof(globalAwards[0]));++i)
        if(Total(n,globalAwards[i].stat)>=globalAwards[i].threshold)
            stats[n].awards|=globalAwards[i].mask;
    total=Total(n,statistic);
    if(stats[n].ready && total>0)
        for(i=0;i<(int)(sizeof(globalAwards)/sizeof(globalAwards[0]));++i)
            if(globalAwards[i].stat==statistic && globalAwards[i].threshold==total) {
                trap_SendServerCommand(-1,va("popaw %i %i",n,i));return;
            }
}
void G_NITMOD_GlobalStatsReset(int n) {
    if(n<0 || n>=MAX_CLIENTS) return;
    NITMOD_StatsCancel(n);memset(&stats[n],0,sizeof(stats[n]));
}
void G_NITMOD_GlobalStatsDeath(int victim,int attacker,int mod) {
    int special=-1;
    if(victim<0 || victim>=level.maxclients || victim>=MAX_CLIENTS ||
       attacker<0 || attacker>=level.maxclients || attacker>=MAX_CLIENTS ||
       !g_entities[victim].client || !g_entities[attacker].client) return;
    if(victim==attacker) { G_NITMOD_GlobalStatsEvent(victim,1);return; }
    if(g_entities[victim].client->sess.sessionTeam==g_entities[attacker].client->sess.sessionTeam) {
        if(!(g_entities[victim].r.svFlags&SVF_BOT)) G_NITMOD_GlobalStatsEvent(attacker,2);
        return;
    }
    if(!(g_entities[attacker].r.svFlags&SVF_BOT)) G_NITMOD_GlobalStatsEvent(victim,1);
    if(g_entities[victim].r.svFlags&SVF_BOT) return;
    G_NITMOD_GlobalStatsEvent(attacker,0);
    switch(mod) {
    case MOD_TRIPMINE: special=5;break;
    case MOD_GOOMBA: special=6;break;
    case MOD_FLAMETHROWER: special=8;break;
    case MOD_SATCHEL: special=12;break;
    default: break;
    }
    if(special>=0) G_NITMOD_GlobalStatsEvent(attacker,special);
}
void G_NITMOD_GlobalStatsUpload(int n) {
    char packet[512];int i,changed=0;
    if(!*endpoint || n<0 || n>=level.maxclients || n>=MAX_CLIENTS || !g_entities[n].client ||
       (g_entities[n].r.svFlags&SVF_BOT) || stats[n].uploaded || strlen(stats[n].guid)!=32 ||
       g_gamestate.integer==GS_WARMUP || g_gamestate.integer==GS_WARMUP_COUNTDOWN) return;
    stats[n].local[3]=(int)(((long long)level.time-g_entities[n].client->pers.connectTime)/60000);
    /* Time and rounds alone do not trigger an original upload. */
    for(i=0;i<16;++i) if(i!=3 && i!=11 && stats[n].local[i]>0) changed=1;
    if(!changed) return;
    Com_sprintf(packet,sizeof(packet),"ps %s",stats[n].guid);
    for(i=0;i<16;++i) Q_strcat(packet,sizeof(packet),va(" %i",stats[n].local[i]));
    Q_strcat(packet,sizeof(packet)," ");
    Q_strcat(packet,sizeof(packet),g_entities[n].client->pers.netname);
    if(NITMOD_StatsUpload(endpoint,packet)) {
        memset(stats[n].local,0,sizeof(stats[n].local));stats[n].uploaded=1;
    }
}
void G_NITMOD_GlobalStatsShutdown(void) { int i;for(i=0;i<MAX_CLIENTS;++i) { G_NITMOD_GlobalStatsUpload(i);G_NITMOD_GlobalStatsReset(i); } *endpoint=0; }
void G_NITMOD_GlobalStatsInit(void) {
    G_NITMOD_GlobalStatsShutdown();
    trap_Cvar_VariableStringBuffer("n_globalStatsBridge",endpoint,sizeof(endpoint));
}
void G_NITMOD_GlobalStatsRequest(int n,const char *guid) {
    int i;
    if(n<0 || n>=level.maxclients || n>=MAX_CLIENTS || !guid || strlen(guid)!=32 ||
       !g_entities[n].client || (g_entities[n].r.svFlags&SVF_BOT)) return;
    for(i=0;i<32;++i) if(!((guid[i]>='0' && guid[i]<='9') || (guid[i]>='a' && guid[i]<='z') || (guid[i]>='A' && guid[i]<='Z'))) return;
    if(!Q_stricmp(stats[n].guid,guid)) {
        if(stats[n].pending || stats[n].ready || stats[n].retryAfter>=level.time) return;
    } else {
        G_NITMOD_GlobalStatsReset(n);Q_strncpyz(stats[n].guid,guid,sizeof(stats[n].guid));
    }
    if(*endpoint) {
        stats[n].retryAfter=(long long)level.time+3000;
        stats[n].pending=NITMOD_StatsStart(n,endpoint,guid);
    }
}
static int Parse(int n,char *packet,int *values,const char **raw) {
    char *p=packet,*end;int i;
    if(strlen(packet)<34 || !isspace((unsigned char)packet[32])) return 0;
    packet[32]=0;
    if(Q_stricmp(packet,stats[n].guid)) return 0;
    p=packet+33;*raw=p;
    for(i=0;i<15;++i) {
        long value;
        while(isspace((unsigned char)*p)) ++p;
        if(!*p) return 0;
        errno=0;value=strtol(p,&end,10);
        if(end==p || errno==ERANGE || value<INT_MIN || value>INT_MAX || (*end && !isspace((unsigned char)*end))) return 0;
        values[i]=(int)value;p=end;
    }
    while(isspace((unsigned char)*p)) ++p;
    return !*p;
}
void G_NITMOD_GlobalStatsFrame(void) {
    int n;
    for(n=0;n<MAX_CLIENTS;++n) if(stats[n].pending) {
        char packet[1024];int values[15],result=NITMOD_StatsRead(n,packet,sizeof(packet));const char *raw;
        if(!result) continue;
        stats[n].pending=0;
        if(result<0 || !g_entities[n].client || !Parse(n,packet,values,&raw)) continue;
        memcpy(stats[n].values,values,sizeof(values));stats[n].ready=1;
        G_NITMOD_LuaReceivedGlobalStats(n,raw);
    }
}
int G_NITMOD_GlobalStatsCommand(int client,const char *command) {
    char arg[32],message[256];int target=0,i;
    if(Q_stricmp(command,"ggs")) return 0;
    if(client<0 || client>=level.maxclients || trap_Argc()!=2) return 1;
    trap_Argv(1,arg,sizeof(arg));if(!*arg) return 1;
    for(i=0;arg[i];++i) { if(arg[i]<'0' || arg[i]>'9') return 1; target=target*10+arg[i]-'0';if(target>=MAX_CLIENTS) return 1; }
    if(target>=level.maxclients || !g_entities[target].client || (g_entities[target].r.svFlags&SVF_BOT)) {
        trap_SendServerCommand(client,"glstats 0 NR\n");return 1;
    }
    Com_sprintf(message,sizeof(message),"glstats %i",stats[target].awards);
    for(i=0;i<15;++i) Q_strcat(message,sizeof(message),va(" %i",Total(target,i)));
    Q_strcat(message,sizeof(message),"\n");trap_SendServerCommand(client,message);return 1;
}
