/* Include production TU to inspect its private per-frame selection without
 * exposing a test-only accessor in the module API. Renderer is not exercised. */
#include "../src_2.60/cgame/cg_nitmod_view.c"
#include <assert.h>
#include <stdio.h>
cg_t cg;
static snapshot_t snapshot;
static nitmodSimpleConfig_t config;
static qboolean isNitmod;
qboolean NITMOD_UsesNitmodHud(void) { return isNitmod; }
const nitmodSimpleConfig_t *NITMOD_SimpleConfig(void) { return &config; }
int main(void) {
    static const int weapons[] = {WP_PANZERFAUST, WP_MORTAR, WP_MORTAR_SET, WP_GPG40, WP_M7, WP_MP40};
    static const int options[] = {1, 2, 2, 4, 4, 0};
    centity_t missile;
    int mod, mask, weapon, owner, cases = 0;
    memset(&missile, 0, sizeof(missile));
    cg.snap = &snapshot; snapshot.ps.clientNum = 5;
    missile.currentState.eType = ET_MISSILE;
    for(mod = 0; mod < 2; ++mod)
    for(mask = 0; mask < 8; ++mask)
    for(weapon = 0; weapon < 6; ++weapon)
    for(owner = 4; owner <= 5; ++owner) {
        isNitmod = mod; config.missileCams = mask;
        missile.currentState.weapon = weapons[weapon];
        missile.currentState.clientNum = owner;
        CG_NitmodMissileCameraBeginFrame();
        CG_NitmodMissileCameraTrack(&missile);
        assert((nitmodMissileCamera == &missile) == (mod && owner == 5 && (mask & options[weapon]) != 0));
        ++cases;
    }
    CG_NitmodMissileCameraBeginFrame();
    CG_NitmodMissileCameraTrack(NULL);
    cg.snap = NULL; CG_NitmodMissileCameraTrack(&missile);
    assert(!nitmodMissileCamera);
    cg.snap = &snapshot; missile.currentState.eType = ET_PLAYER;
    CG_NitmodMissileCameraTrack(&missile); assert(!nitmodMissileCamera);
    printf("WASM missile-camera tracking: %d mask/weapon/owner cases passed\n", cases);
    return 0;
}
