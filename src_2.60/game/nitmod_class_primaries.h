#ifndef NITMOD_CLASS_PRIMARIES_H
#define NITMOD_CLASS_PRIMARIES_H
#include "bg_public.h"

static inline weapon_t NITMOD_ClassPrimaryAt(int team, int cls, int slot) {
    /* Original ELF class records: axis 0x2a79c0, allies 0x2a7ac0,
     * 48 bytes each; six primary slots at +16. Map IDs by item identity. */
    static const int primaries[2][5][6] = {
        {
            { WP_MP40, WP_MOBILE_MG42, WP_FLAMETHROWER, WP_PANZERFAUST, WP_MORTAR, WP_NONE },
            { WP_MP40, WP_THOMPSON, WP_STEN, WP_NONE, WP_NONE, WP_NONE },
            { WP_MP40, WP_THOMPSON, WP_KAR98, WP_NONE, WP_NONE, WP_NONE },
            { WP_MP40, WP_THOMPSON, WP_STEN, WP_NONE, WP_NONE, WP_NONE },
            { WP_STEN, WP_FG42, WP_K43, WP_NONE, WP_NONE, WP_NONE }
        }, {
            { WP_THOMPSON, WP_MOBILE_MG42, WP_FLAMETHROWER, WP_PANZERFAUST, WP_MORTAR, WP_NONE },
            { WP_THOMPSON, WP_MP40, WP_STEN, WP_NONE, WP_NONE, WP_NONE },
            { WP_THOMPSON, WP_MP40, WP_CARBINE, WP_NONE, WP_NONE, WP_NONE },
            { WP_THOMPSON, WP_MP40, WP_STEN, WP_NONE, WP_NONE, WP_NONE },
            { WP_STEN, WP_FG42, WP_GARAND, WP_NONE, WP_NONE, WP_NONE }
        }
    };
    if((team != TEAM_AXIS && team != TEAM_ALLIES) || cls < PC_SOLDIER ||
       cls > PC_COVERTOPS || slot < 0 || slot >= 6) return WP_NONE;
    return primaries[team == TEAM_ALLIES][cls][slot];
}

static inline int NITMOD_ClassHasPrimary(int team, int cls, int weapon) {
    int i;
    if(weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS) return 0;
    for(i=0;i<6;++i) if(NITMOD_ClassPrimaryAt(team,cls,i)==weapon) return 1;
    return 0;
}
#endif
