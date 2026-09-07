#include "g_local.h"
#include <assert.h>
gentity_t g_entities[MAX_GENTITIES]; level_locals_t level;
static gclient_t clients[MAX_CLIENTS];
static const char *password="secret",*argument="secret";
static int argcValue=2,updates,moves;
void G_smvRemoveInvalidClients(gentity_t *ent,int team) { abort(); }
void StopFollowing(gentity_t *ent) { abort(); }
void Com_Error(int code,const char *fmt,...) { abort(); }
void Com_Printf(const char *fmt,...) {}
void G_Printf(const char *fmt,...) {}
void trap_SendServerCommand(int client,const char *text) {}
void ClientUserinfoChanged(int n) { ++updates; }
int trap_Argc(void) { return argcValue; }
void trap_Argv(int n,char *out,int size) { assert(n==1); Q_strncpyz(out,argument,size); }
void trap_Cvar_VariableStringBuffer(const char *name,char *out,int size) {
    assert(!strcmp(name,"shoutcastPassword")); Q_strncpyz(out,password,size);
}
qboolean SetTeam(gentity_t *ent,char *name,qboolean force,weapon_t a,weapon_t b,qboolean weapons) {
    assert(!strcmp(name,"spectator") && force && a==-1 && b==-1 && !weapons);
    ent->client->sess.sessionTeam=TEAM_SPECTATOR; ++moves; return qtrue;
}
int main(void) {
    int i;
    level.clients=clients;level.maxclients=3;
    for(i=0;i<3;++i) { g_entities[i].client=&clients[i];clients[i].pers.connected=CON_CONNECTED; }
    strcpy(clients[0].pers.netname,"Alice"); strcpy(clients[1].pers.netname,"Bob");strcpy(clients[2].pers.netname,"Bobby");
    clients[0].sess.sessionTeam=TEAM_AXIS;
    password="none"; assert(G_NITMOD_ShoutcasterCommand(0,"sclogin") && !updates);
    password=""; G_NITMOD_ShoutcasterCommand(0,"sclogin"); assert(!updates);
    password="secret"; argument="wrong"; G_NITMOD_ShoutcasterCommand(0,"sclogin"); assert(!updates);
    argument="secret"; argcValue=1; G_NITMOD_ShoutcasterCommand(0,"sclogin"); assert(!updates);
    argcValue=2; G_NITMOD_ShoutcasterCommand(0,"sclogin");
    assert(updates==1 && moves==1 && clients[0].sess.shoutcaster && clients[0].sess.spec_invite==3);
    G_NITMOD_ShoutcasterCommand(0,"sclogin"); assert(updates==1);
    password=""; G_NITMOD_ShoutcasterCommand(0,"sclogout");
    assert(updates==2 && !clients[0].sess.shoutcaster && !clients[0].sess.spec_invite);
    password="secret"; argument="1";
    assert(!G_NITMOD_ShoutcasterCommand(0,"makeshoutcaster"));
    G_NITMOD_ShoutcasterCommand(-1,"makeshoutcaster"); assert(clients[1].sess.shoutcaster);
    clients[1].sess.referee=1;
    G_NITMOD_ShoutcasterCommand(-1,"removeshoutcaster"); assert(!clients[1].sess.shoutcaster && clients[1].sess.spec_invite==3);
    argument="Bob"; G_NITMOD_ShoutcasterCommand(-1,"makeshoutcaster"); assert(!clients[1].sess.shoutcaster && !clients[2].sess.shoutcaster);
    argument="^1alice"; G_NITMOD_ShoutcasterCommand(-1,"makeshoutcaster"); assert(clients[0].sess.shoutcaster);
    argument="9999999999999999"; G_NITMOD_ShoutcasterCommand(-1,"makeshoutcaster");
    level.numConnectedClients=3;
    for(i=0;i<3;++i) { level.sortedClients[i]=i; g_entities[i].inuse=qtrue; clients[i].sess.spec_invite=3; }
    clients[2].sess.sessionTeam=TEAM_AXIS;
    G_updateSpecLock(TEAM_AXIS,qtrue);
    assert(clients[0].sess.spec_invite==3 && clients[1].sess.spec_invite==3 && clients[2].sess.spec_invite==2);
    G_removeSpecInvite(TEAM_ALLIES);
    assert(clients[0].sess.spec_invite==3 && clients[1].sess.spec_invite==3 && clients[2].sess.spec_invite==0);
    assert(!G_NITMOD_ShoutcasterCommand(-1,"unknown"));
    puts("Shoutcaster authentication, console grants, ambiguity, logout and referee invitations: PASS"); return 0;
}
