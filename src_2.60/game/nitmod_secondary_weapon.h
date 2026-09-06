#ifndef NITMOD_SECONDARY_WEAPON_H
#define NITMOD_SECONDARY_WEAPON_H

/* Original cg_uinfo bit 6 -> client +0xb0c; affects fallback only. */
#define NITMOD_CGF_NO_AUTO_SECONDARY 64u
static weapon_t NITMOD_DefaultSecondaryWeapon(int team, int playerClass,
    unsigned int lightRewards, unsigned int heavyRewards, unsigned int clientFlags) {
    if(!(clientFlags & NITMOD_CGF_NO_AUTO_SECONDARY)) {
        if(playerClass == PC_SOLDIER && (heavyRewards & 16u))
            return team == TEAM_ALLIES ? WP_THOMPSON : WP_MP40;
        if(lightRewards & 16u) {
            if(playerClass == PC_COVERTOPS)
                return team == TEAM_ALLIES ? WP_AKIMBO_SILENCEDCOLT : WP_AKIMBO_SILENCEDLUGER;
            return team == TEAM_ALLIES ? WP_AKIMBO_COLT : WP_AKIMBO_LUGER;
        }
    }
    return team == TEAM_ALLIES ? WP_COLT : WP_LUGER;
}

/* Original G_CorrectSecondaryWeapon: these arguments are numeric levels,
 * unlike the subsequent G_AddClassWeapons fallback reward-mask tests.
 * Include bg_public.h first. No engine imports or wire-number assumptions. */
static weapon_t NITMOD_CorrectSecondaryWeapon(weapon_t requested, int team,
    int lightLevel, int heavyLevel, int playerClass, int dualSMG,
    unsigned int medicOptions) {
    switch(requested) {
    default: return WP_NONE;
    case WP_LUGER: case WP_COLT: case WP_SILENCER: case WP_SILENCED_COLT:
        break;
    case WP_MP40: case WP_THOMPSON:
        if(heavyLevel > 3 && playerClass == PC_SOLDIER && !dualSMG)
            return team == TEAM_ALLIES ? WP_THOMPSON : WP_MP40;
        if(lightLevel > 3)
            return team == TEAM_ALLIES ? WP_AKIMBO_COLT : WP_AKIMBO_LUGER;
        break;
    case WP_AKIMBO_COLT: case WP_AKIMBO_LUGER:
        if(lightLevel > 3 && (playerClass != PC_MEDIC || !(medicOptions & 2u)))
            return team == TEAM_ALLIES ? WP_AKIMBO_COLT : WP_AKIMBO_LUGER;
        break;
    case WP_AKIMBO_SILENCEDCOLT: case WP_AKIMBO_SILENCEDLUGER:
        if(lightLevel > 3) {
            if(playerClass == PC_COVERTOPS)
                return team == TEAM_ALLIES ? WP_AKIMBO_SILENCEDCOLT : WP_AKIMBO_SILENCEDLUGER;
            return team == TEAM_ALLIES ? WP_AKIMBO_COLT : WP_AKIMBO_LUGER;
        }
        break;
    }
    return team == TEAM_ALLIES ? WP_COLT : WP_LUGER;
}
#endif
