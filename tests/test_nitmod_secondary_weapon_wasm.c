#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_secondary_weapon.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
    int team, level, cls, dual, opts, count = 0;
    for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
    for(level = 0; level <= 5; ++level)
    for(cls = 0; cls < 5; ++cls)
    for(dual = 0; dual < 2; ++dual)
    for(opts = 0; opts < 4; ++opts) {
        weapon_t pistol = team == TEAM_ALLIES ? WP_COLT : WP_LUGER;
        weapon_t akimbo = team == TEAM_ALLIES ? WP_AKIMBO_COLT : WP_AKIMBO_LUGER;
        weapon_t smg = team == TEAM_ALLIES ? WP_THOMPSON : WP_MP40;
        weapon_t quiet = team == TEAM_ALLIES ? WP_AKIMBO_SILENCEDCOLT : WP_AKIMBO_SILENCEDLUGER;
        assert(NITMOD_CorrectSecondaryWeapon(WP_KNIFE,team,level,level,cls,dual,opts) == WP_NONE);
        assert(NITMOD_CorrectSecondaryWeapon(WP_SILENCER,team,level,level,cls,dual,opts) == pistol);
        assert(NITMOD_CorrectSecondaryWeapon(WP_AKIMBO_LUGER,team,level,0,cls,dual,opts) ==
            (level >= 4 && !(cls == PC_MEDIC && (opts & 2)) ? akimbo : pistol));
        assert(NITMOD_CorrectSecondaryWeapon(WP_MP40,team,0,level,cls,dual,opts) ==
            (level >= 4 && cls == PC_SOLDIER && !dual ? smg : pistol));
        assert(NITMOD_CorrectSecondaryWeapon(WP_THOMPSON,team,level,0,cls,dual,opts) ==
            (level >= 4 ? akimbo : pistol));
        assert(NITMOD_CorrectSecondaryWeapon(WP_AKIMBO_SILENCEDCOLT,team,level,0,cls,dual,opts) ==
            (level >= 4 ? (cls == PC_COVERTOPS ? quiet : akimbo) : pistol));
        ++count;
    }
    for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
    for(cls = 0; cls < 5; ++cls)
    for(level = 0; level < 64; ++level)
    for(dual = 0; dual < 64; ++dual)
    for(opts = 0; opts < 2; ++opts) {
        weapon_t expected = team == TEAM_ALLIES ? WP_COLT : WP_LUGER;
        if(!opts && (level & 16)) expected = cls == PC_COVERTOPS ?
            (team == TEAM_ALLIES ? WP_AKIMBO_SILENCEDCOLT : WP_AKIMBO_SILENCEDLUGER) :
            (team == TEAM_ALLIES ? WP_AKIMBO_COLT : WP_AKIMBO_LUGER);
        if(!opts && cls == PC_SOLDIER && (dual & 16))
            expected = team == TEAM_ALLIES ? WP_THOMPSON : WP_MP40;
        assert(NITMOD_DefaultSecondaryWeapon(team,cls,level,dual,opts ? 64u : 0u) == expected);
    }
    printf("Secondary selection: %d combinations plus 81920 fallback cases passed\n", count);
    return 0;
}
