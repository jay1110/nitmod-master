#include "g_local.h"
#include "g_nitmod_shoutcaster.h"

static int Enabled(char *password, int size) {
    trap_Cvar_VariableStringBuffer("shoutcastPassword",password,size);
    return *password && strcmp(password,"none");
}
static void Reply(int client,const char *text) {
    if(client<0) G_Printf("%s",text);
    else trap_SendServerCommand(client,va("print \"%s\"",text));
}
static int Target(const char *text) {
    int i,found=-1; char needle[MAX_NETNAME],name[MAX_NETNAME];
    if(*text) {
        const char *p=text; unsigned int n=0;
        while(*p>='0' && *p<='9') { n=n*10+(*p++-'0'); if(n>=MAX_CLIENTS) return -1; }
        if(!*p) return n<(unsigned)level.maxclients && g_entities[n].client &&
            g_entities[n].client->pers.connected==CON_CONNECTED ? (int)n : -1;
    }
    Q_strncpyz(needle,text,sizeof(needle)); Q_CleanStr(needle); Q_strlwr(needle);
    if(!*needle) return -1;
    for(i=0;i<level.maxclients;++i) {
        if(!g_entities[i].client || g_entities[i].client->pers.connected!=CON_CONNECTED) continue;
        Q_strncpyz(name,g_entities[i].client->pers.netname,sizeof(name)); Q_CleanStr(name); Q_strlwr(name);
        if(strstr(name,needle)) { if(found>=0) return -1; found=i; }
    }
    return found;
}
static void SetStatus(int n,int enabled,int announce) {
    gentity_t *ent=&g_entities[n];
    if(enabled) {
        if(ent->client->sess.sessionTeam!=TEAM_SPECTATOR)
            SetTeam(ent,"spectator",qtrue,-1,-1,qfalse);
        ent->client->sess.shoutcaster=1;
        ent->client->sess.spec_invite=TEAM_AXIS|TEAM_ALLIES;
    } else {
        ent->client->sess.shoutcaster=0;
        if(!ent->client->sess.referee) ent->client->sess.spec_invite=0;
    }
    if(announce) trap_SendServerCommand(-1,va("cp \"%s\n^3%s\n\"",ent->client->pers.netname,
        enabled ? "has become a shoutcaster" : "has been stripped of his shoutcaster status"));
    ClientUserinfoChanged(n);
}
int G_NITMOD_ShoutcasterCommand(int client,const char *command) {
    int login=!Q_stricmp(command,"sclogin"),logout=!Q_stricmp(command,"sclogout");
    int make=!Q_stricmp(command,"makeshoutcaster"),remove=!Q_stricmp(command,"removeshoutcaster");
    char password[MAX_CVAR_VALUE_STRING],argument[MAX_TOKEN_CHARS]; int target;
    if(client>=0) {
        if(!login && !logout) return 0; /* Grant/removal commands are server-console only. */
        if(client>=level.maxclients || !g_entities[client].client) return 1;
        if(logout) {
            if(!g_entities[client].client->sess.shoutcaster) Reply(client,"^1You are not a Shoutcaster.\n");
            else SetStatus(client,0,0);
            return 1;
        }
        if(g_entities[client].client->sess.shoutcaster) { Reply(client,"^1You are already shoutcaster.\n"); return 1; }
        if(!Enabled(password,sizeof(password))) { Reply(client,"^1Shoutcaster status is disabled on this server.\n"); return 1; }
        if(trap_Argc()<2) { Reply(client,"^xusage: ^gsclogin [password]\n"); return 1; }
        trap_Argv(1,argument,sizeof(argument));
        if(strcmp(argument,password)) Reply(client,"^1Shoutcaster error: ^9Invalid Password.\n");
        else SetStatus(client,1,1);
        return 1;
    }
    if(!make && !remove) return 0;
    if(!Enabled(password,sizeof(password))) { Reply(-1,"^1Shoutcaster status is disabled on this server.\n"); return 1; }
    if(trap_Argc()<2) { Reply(-1,va("^9usage: ^g%s ^7[name|slot#]^7\n",command)); return 1; }
    trap_Argv(1,argument,sizeof(argument)); target=Target(argument);
    if(target<0) { Reply(-1,"^1No unique connected player matches.\n"); return 1; }
    if(!!g_entities[target].client->sess.shoutcaster==make) {
        Reply(-1,make ? "^1Player is already a shoutcaster.\n" : "^1Player is not a shoutcaster.\n");
    } else SetStatus(target,make,1);
    return 1;
}
