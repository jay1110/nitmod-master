#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_hints.h"
#include <assert.h>
#include <stdio.h>

cg_t cg;
cgs_t cgs;
static int original, capable, configured, reads, unlocked;
qboolean NITMOD_UsesOriginalProtocol(void) { return original; }
qboolean NITMOD_ServerSupports(unsigned int feature) { return capable; }
int NITMOD_ClassMaxHealth(int cls) { return configured; }
qboolean NITMOD_ClientSkillUnlocked(int client, int skill, int level) { return unlocked; }
const char *CG_ConfigString(int index) { assert(original && index == 39); ++reads; return ""; }
char *Info_ValueForKey(const char *s, const char *key) { return ""; }
int NITMOD_ParseProtocolInteger(const char *text, int *value) { return 0; }

int main(void) {
    static snapshot_t snapshot;
    int cls;
    cg.snap = &snapshot;
    cgs.maxclients = 2;
    cgs.clientinfo[0].team = TEAM_AXIS;
    cgs.clientinfo[1].team = TEAM_AXIS;
    cgs.clientinfo[1].infoValid = qtrue;
    for(original = 0; original <= 1; ++original) {
        for(capable = 0; capable <= 1; ++capable) {
            for(cls = 0; cls < NUM_PLAYER_CLASSES; ++cls) {
                int enabled = original || capable;
                cgs.clientinfo[1].cls = cls;
                configured = 250 + cls;
                reads = 0;
                assert(CG_NitmodCrosshairMaxHealth(1) == (enabled ? configured : 0));
                assert(reads == 0);
                configured = 0;
                unlocked = 0;
                assert(CG_NitmodCrosshairMaxHealth(1) == (enabled ? (cls == PC_MEDIC ? 123 : 100) : 0));
                assert(reads == (original ? 1 : 0));
                unlocked = 1;
                assert(CG_NitmodCrosshairMaxHealth(1) == (enabled ? (cls == PC_MEDIC ? 140 : 115) : 0));
                unlocked = 0;
            }
        }
    }
    /* Original CG_CrosshairClientMaxHealth counts viewer-team medics,
     * not target-team medics, and caps their contribution at 25. */
    original = 1;
    capable = 0;
    configured = 0;
    cgs.maxclients = MAX_CLIENTS;
    snapshot.ps.clientNum = 0;
    {
        int medics, valid, targetTeam, cases = 0;
        for(medics = 0; medics <= 5; ++medics)
        for(valid = 0; valid <= 1; ++valid)
        for(targetTeam = TEAM_AXIS; targetTeam <= TEAM_ALLIES; ++targetTeam)
        for(unlocked = 0; unlocked <= 1; ++unlocked) {
            int i, expected = 100 + (valid ? (medics >= 3 ? 25 : medics * 10) : 0) + (unlocked ? 15 : 0);
            memset(cgs.clientinfo, 0, sizeof(cgs.clientinfo));
            cgs.clientinfo[0].team = TEAM_AXIS;
            cgs.clientinfo[1].team = targetTeam;
            cgs.clientinfo[1].infoValid = qtrue;
            cgs.clientinfo[1].cls = PC_SOLDIER;
            for(i = 2; i < 2 + medics; ++i) {
                cgs.clientinfo[i].team = TEAM_AXIS;
                cgs.clientinfo[i].cls = PC_MEDIC;
                cgs.clientinfo[i].infoValid = valid;
            }
            /* Opponent medics do not affect the viewer's team bonus. */
            cgs.clientinfo[10].infoValid = qtrue;
            cgs.clientinfo[10].team = TEAM_ALLIES;
            cgs.clientinfo[10].cls = PC_MEDIC;
            assert(CG_NitmodCrosshairMaxHealth(1) == expected);
            ++cases;
        }
        printf("Crosshair viewer-team/medic/reward cases: %d passed\n", cases);
    }
    assert(!CG_NitmodCrosshairMaxHealth(-1));
    assert(!CG_NitmodCrosshairMaxHealth(MAX_CLIENTS));
    cg.snap = NULL;
    assert(!CG_NitmodCrosshairMaxHealth(1));
    puts("WASM crosshair class health: overrides, capability, protocol isolation and bonuses passed");
    return 0;
}
