#include "../src_2.60/cgame/cg_nitmod_names.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
cg_t cg;
cgs_t cgs;
vmCvar_t cg_draw2D;
static snapshot_t snapshot;
static int mod;
qboolean NITMOD_UsesNitmodHud(void) { return mod != 0; }
int CG_Text_Width_Ext(const char *text, float scale, int limit, fontInfo_t *font) { return 10; }
int CG_Text_Height_Ext(const char *text, float scale, int limit, fontInfo_t *font) { return 10; }
void QDECL Com_Error(int level, const char *format, ...) { abort(); }
int main(void) {
    centity_t target;
    int alive, cls, team, dead, range, count = 0;
    static const int distances[] = {63, 64, 100, 1600, 1601};
    memset(&target, 0, sizeof(target));
    cg.snap = &snapshot; cg.refdef_current = &cg.refdef;
    cg.refdef.fov_x = 96; cg.refdef.fov_y = 102;
    cg_draw2D.integer = cg_woundedNames.integer = 1;
    snapshot.ps.clientNum = 1; snapshot.ps.persistant[PERS_TEAM] = TEAM_AXIS;
    target.currentState.number = target.currentState.clientNum = 2;
    strcpy(cgs.clientinfo[2].name, "Medic");
    cgs.clientinfo[2].health = 100;
    /* Same typed data for original and reconstructed Nitmod; etmain excluded. */
    for(mod = 0; mod < 3; ++mod)
    for(alive = 0; alive < 2; ++alive)
    for(cls = 0; cls < 5; ++cls)
    for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
    for(dead = 0; dead < 2; ++dead)
    for(range = 0; range < 5; ++range) {
        int expected = mod != 0 && team == TEAM_AXIS && cls == PC_MEDIC &&
            (!alive || (dead && distances[range] >= 64 && distances[range] <= 1600));
        target.lerpOrigin[0] = distances[range]; target.currentState.eFlags = dead ? EF_DEAD : 0;
        cgs.clientinfo[2].cls = cls; cgs.clientinfo[2].team = team;
        snapshot.ps.stats[STAT_HEALTH] = alive * 100;
        snapshot.ps.stats[STAT_PLAYER_CLASS] = cls;
        CG_NitmodNamesBeginFrame();
        assert(CG_NitmodQueueWoundedName(&target) == expected);
        assert(nameCount == expected); ++count;
    }
    assert(!CG_NitmodQueueWoundedName(NULL));
    printf("WASM wounded names: %d typed eligibility cases passed\n", count);
    return 0;
}
