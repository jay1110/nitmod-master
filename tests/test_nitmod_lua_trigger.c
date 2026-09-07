#include "g_local.h"
#include <assert.h>

gentity_t g_entities[MAX_GENTITIES];
level_locals_t level;
static gclient_t clients[MAX_CLIENTS];
static int boxCount, boxCalls, scripts, targets;
static int boxEntities[MAX_GENTITIES];
void Com_Error(int code, const char *fmt, ...) { abort(); }
void Com_Printf(const char *fmt, ...) {}
void trap_Cvar_Set(const char *name, const char *value) {}
int trap_EntitiesInBox(const vec3_t mins, const vec3_t maxs, int *list, int max) {
    ++boxCalls; assert(max == MAX_GENTITIES);
    memcpy(list, boxEntities, boxCount * sizeof(int)); return boxCount;
}
void G_Script_ScriptEvent(gentity_t *ent, char *event, char *params) {
    assert(!strcmp(event,"activate") && !params); ++scripts;
}
void G_UseTargets(gentity_t *ent, gentity_t *activator) { ++targets; }
void G_FreeEntity(gentity_t *ent) {}
extern void multi_trigger(gentity_t *, gentity_t *);
extern void multi_wait(gentity_t *);

int main(void) {
    gentity_t *trigger = &g_entities[100], *activator = &g_entities[0];
    int required, present;
    level.clients=clients; level.time=1000;
    g_entities[0].client=&clients[0]; g_entities[1].client=&clients[1];
    g_entities[2].client=&clients[2];
    /* World entity in the same box must not count as a player. */
    boxEntities[0]=101; boxEntities[1]=0; boxEntities[2]=1; boxEntities[3]=2;
    for(required=0; required<=4; ++required) for(present=0; present<=3; ++present) {
        int expected=required<=1 || present>=required;
        trigger->numPlayers=required; trigger->wait=0.5f; trigger->nextthink=0;
        scripts=targets=boxCalls=0; boxCount=present+1;
        multi_trigger(trigger,activator);
        assert(scripts==expected && targets==expected);
        assert(boxCalls==(required>1));
        if(expected) { assert(trigger->nextthink==1500); multi_wait(trigger); assert(!trigger->nextthink); }
    }
    trigger->numPlayers=2; boxCount=3; scripts=targets=0;
    trigger->nextthink=1500; multi_trigger(trigger,activator);
    assert(scripts==1 && targets==0); /* Original script fires even during cooldown. */
    trigger->nextthink=0; activator->client->ps.eFlags=EF_SPARE0;
    scripts=targets=boxCalls=0; multi_trigger(trigger,activator);
    assert(!scripts && !targets && !boxCalls);
    activator->client->ps.eFlags=0; trigger->wait=-1;
    multi_trigger(trigger,activator);
    assert(targets==1 && trigger->nextthink==1100 && trigger->think==G_FreeEntity && !trigger->touch);
    clients[0].sess.nitmodNewton=7; clients[1].sess.nitmodNewton=8;
    G_deleteStats(0);
    assert(!clients[0].sess.nitmodNewton && clients[1].sess.nitmodNewton==8);
    puts("Lua dependencies: original trigger population/cooldown/playdead and per-client Newton reset: PASS");
    return 0;
}
