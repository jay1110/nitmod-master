#include "g_local.h"
#include <assert.h>
#include <stdio.h>
gentity_t g_entities[MAX_GENTITIES];
static int pvs, armed, spotted, checks;
qboolean trap_InPVS(const vec3_t a, const vec3_t b) {
    assert(a == g_entities[0].r.currentOrigin && b == g_entities[64].r.currentOrigin);
    ++checks; return pvs;
}
qboolean G_LandmineArmed(gentity_t *ent) { return armed; }
qboolean G_LandmineSpotted(gentity_t *ent) { return spotted; }
team_t G_LandmineTeam(gentity_t *ent) { return TEAM_AXIS; }
int main(void) {
    static gclient_t client;
    int skill, same, reward, cases = 0;
    g_entities[0].client = &client;
    for(pvs = 0; pvs < 2; ++pvs) for(armed = 0; armed < 2; ++armed)
    for(spotted = 0; spotted < 2; ++spotted) for(skill = 0; skill < 2; ++skill)
    for(same = 0; same < 2; ++same) for(reward = 0; reward < 64; ++reward) {
        client.sess.skill[SK_BATTLE_SENSE] = skill ? 4 : 0;
        client.sess.nitmodSkillMasks[SK_BATTLE_SENSE] = reward;
        client.sess.sessionTeam = same ? TEAM_AXIS : TEAM_ALLIES;
        assert(!!G_LandmineSnapshotCallback(64, 0) == !!(pvs && ((reward & 16) || !armed || spotted || same)));
        ++cases;
    }
    assert(checks == cases);
    assert(!G_LandmineSnapshotCallback(-1, 0));
    assert(!G_LandmineSnapshotCallback(MAX_GENTITIES, 0));
    assert(!G_LandmineSnapshotCallback(64, -1));
    assert(!G_LandmineSnapshotCallback(64, MAX_CLIENTS));
    g_entities[0].client = NULL;
    assert(!G_LandmineSnapshotCallback(64, 0) && checks == cases);
    printf("WASM mine snapshots: %d PVS/visibility combinations and invalid inputs passed\n", cases);
    return 0;
}
