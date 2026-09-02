#include "nitmod_weapon_clip.h"
#include "nitmod_weapon_consumption.h"

int NITMOD_SelectWeaponClip( const playerState_t *state, int weapon, int *clip ) {
    int selected, sidearm, sideClip;
    if( !state || !clip || weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ) return 0;
    selected = BG_FindClipForWeapon((weapon_t)weapon);
    if( selected <= WP_NONE || selected >= WP_NUM_WEAPONS || state->ammoclip[selected] < 0 ) return 0;
    if( BG_IsAkimboWeapon(weapon) ) {
        sidearm = BG_AkimboSidearm(weapon);
        if( sidearm <= WP_NONE || sidearm >= WP_NUM_WEAPONS ) return 0;
        sideClip = BG_FindClipForWeapon((weapon_t)sidearm);
        if( sideClip <= WP_NONE || sideClip >= WP_NUM_WEAPONS || state->ammoclip[sideClip] < 0 ) return 0;
        if( !BG_AkimboFireSequence(weapon, state->ammoclip[selected], state->ammoclip[sideClip]) )
            selected = sidearm; /* Original uses sidearm ID here, not sideClip. */
    }
    if( state->ammoclip[selected] < 0 ) return 0;
    *clip = selected;
    return 1;
}

int NITMOD_ConsumeSelectedWeaponClip( playerState_t *state, int weapon,
    int amount, int warMode, unsigned int noReload,
    const ammotable_t *ammoTable, int ammoSlots ) {
    int clip;
    if( !ammoTable || !NITMOD_SelectWeaponClip(state, weapon, &clip) || clip >= ammoSlots ) return 0;
    return NITMOD_ConsumeWeaponClip(state, weapon, clip, amount, warMode, noReload, &ammoTable[clip]);
}
