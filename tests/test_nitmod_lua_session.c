#include "g_local.h"
#include <assert.h>
extern void G_WriteClientSessionData(gclient_t *client,qboolean restart);
gentity_t g_entities[MAX_GENTITIES];level_locals_t level;g_campaignInfo_t g_campaigns[1];
vmCvar_t g_gametype,g_gamestate,g_currentRound,g_altStopwatchMode,g_swapteams;
static gclient_t clients[2];
static struct { char key[64],value[MAX_STRING_CHARS]; } cvars[32];static int count;
void Com_Error(int code,const char *fmt,...) { abort(); }
void Com_Printf(const char *fmt,...) {}
void trap_Cvar_Set(const char *name,const char *value) {
    int i;for(i=0;i<count;++i) if(!strcmp(cvars[i].key,name)) break;
    assert(i<32);if(i==count) ++count;
    Q_strncpyz(cvars[i].key,name,sizeof(cvars[i].key));Q_strncpyz(cvars[i].value,value,sizeof(cvars[i].value));
}
void trap_Cvar_VariableStringBuffer(const char *name,char *out,int size) {
    int i;*out=0;for(i=0;i<count;++i) if(!strcmp(cvars[i].key,name)) { Q_strncpyz(out,cvars[i].value,size);return; }
}
int trap_Cvar_VariableIntegerValue(const char *name) { char value[64];trap_Cvar_VariableStringBuffer(name,value,sizeof(value));return atoi(value); }
unsigned int G_smvGenerateClientList(gentity_t *ent) { return 0; }
char *G_createStats(gentity_t *ent) { return ""; }
void G_parseStats(char *text) {}
void G_deleteStats(int n) { clients[n].sess.nitmodNewton=0; }
void G_NITMOD_ReadEquipment(gclient_t *client,int n) {}
void G_NITMOD_WriteEquipment(const gclient_t *client,int n) {}
void G_SetPlayerSkill(gclient_t *client,skillType_t skill) {}
int main(void) {
    char oldSession[MAX_STRING_CHARS];
    level.clients=clients;g_gametype.integer=GT_WOLF;
    clients[0].sess.sessionTeam=TEAM_SPECTATOR;clients[0].sess.shoutcaster=1;
    clients[0].sess.spec_invite=3;clients[0].sess.nitmodNewton=7;
    clients[0].sess.nitmodHeadHits=11;clients[0].sess.nitmodBodyHits=22;
    clients[0].sess.nitmodKillingSpree=91;
    G_WriteClientSessionData(&clients[0],qfalse);
    assert(!clients[0].sess.nitmodKillingSpree);
    trap_Cvar_VariableStringBuffer("session0",oldSession,sizeof(oldSession));
    memset(&clients[0],0,sizeof(clients[0]));G_ReadSessionData(&clients[0]);
    assert(clients[0].sess.shoutcaster==1 && clients[0].sess.spec_invite==3 && clients[0].sess.nitmodNewton==7);
    assert(clients[0].sess.nitmodHeadHits==11 && clients[0].sess.nitmodBodyHits==22);
    trap_Cvar_Set("nitmod_killingspree0","17");G_ReadSessionData(&clients[0]);
    assert(clients[0].sess.nitmodKillingSpree==17);
    /* Existing stock session without the new keys is accepted with zero defaults. */
    trap_Cvar_Set("session1",oldSession);clients[1].sess.shoutcaster=99;clients[1].sess.nitmodNewton=99;
    G_ReadSessionData(&clients[1]);assert(!clients[1].sess.shoutcaster && !clients[1].sess.nitmodNewton);
    assert(!clients[1].sess.nitmodKillingSpree && !clients[1].sess.nitmodHeadHits && !clients[1].sess.nitmodBodyHits);
    G_InitSessionData(&clients[0],"");assert(!clients[0].sess.shoutcaster && !clients[0].sess.spec_invite);
    assert(!trap_Cvar_VariableIntegerValue("nitmod_shoutcaster0"));
    assert(!clients[0].sess.nitmodKillingSpree && !clients[0].sess.nitmodHeadHits && !clients[0].sess.nitmodBodyHits);
    puts("Actual session write/read, old-session defaults, new-client privilege reset: PASS");return 0;
}
