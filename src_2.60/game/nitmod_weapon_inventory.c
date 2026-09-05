#include "nitmod_weapon_inventory.h"
/* First matching weapon item in BOTH original modules; see
 * reference/weapon-item-aliases.md. Never index native arrays by original IDs. */
static const struct {
    int weapon, ammo, clip;
} inventory[] = {
    { WP_KNIFE, WP_KNIFE, WP_KNIFE },
    { WP_LUGER, WP_LUGER, WP_LUGER },
    { WP_MP40, WP_MP40, WP_MP40 },
    { WP_GRENADE_LAUNCHER, WP_GRENADE_LAUNCHER, WP_GRENADE_LAUNCHER },
    { WP_PANZERFAUST, WP_PANZERFAUST, WP_PANZERFAUST },
    { WP_FLAMETHROWER, WP_FLAMETHROWER, WP_FLAMETHROWER },
    { WP_COLT, WP_COLT, WP_COLT },
    { WP_THOMPSON, WP_THOMPSON, WP_THOMPSON },
    { WP_GRENADE_PINEAPPLE, WP_GRENADE_PINEAPPLE, WP_GRENADE_PINEAPPLE },
    { WP_STEN, WP_STEN, WP_STEN },
    { WP_MEDIC_SYRINGE, WP_MEDIC_SYRINGE, WP_MEDIC_SYRINGE },
    { WP_AMMO, WP_AMMO, WP_AMMO },
    { WP_SILENCER, WP_LUGER, WP_LUGER },
    { WP_DYNAMITE, WP_DYNAMITE, WP_DYNAMITE },
    { WP_SMOKETRAIL, WP_SMOKETRAIL, WP_SMOKETRAIL },
    { WP_MEDKIT, WP_MEDKIT, WP_MEDKIT },
    { WP_BINOCULARS, WP_BINOCULARS, WP_BINOCULARS },
    { WP_PLIERS, WP_PLIERS, WP_PLIERS },
    { WP_SMOKE_MARKER, WP_SMOKE_MARKER, WP_SMOKE_MARKER },
    { WP_KAR98, WP_KAR98, WP_KAR98 },
    { WP_CARBINE, WP_CARBINE, WP_CARBINE },
    { WP_GARAND, WP_GARAND, WP_GARAND },
    { WP_LANDMINE, WP_LANDMINE, WP_LANDMINE },
    { WP_SATCHEL, WP_SATCHEL, WP_SATCHEL },
    { WP_SATCHEL_DET, WP_SATCHEL_DET, WP_SATCHEL_DET },
    { WP_SMOKE_BOMB, WP_SMOKE_BOMB, WP_SMOKE_BOMB },
    { WP_MOBILE_MG42, WP_MOBILE_MG42, WP_MOBILE_MG42 },
    { WP_K43, WP_K43, WP_K43 },
    { WP_FG42, WP_FG42, WP_FG42 },
    { WP_MORTAR, WP_MORTAR, WP_MORTAR },
    { WP_AKIMBO_COLT, WP_COLT, WP_AKIMBO_COLT },
    { WP_AKIMBO_LUGER, WP_LUGER, WP_AKIMBO_LUGER },
    { WP_GPG40, WP_GPG40, WP_GPG40 },
    { WP_M7, WP_M7, WP_M7 },
    { WP_SILENCED_COLT, WP_COLT, WP_COLT },
    { WP_GARAND_SCOPE, WP_GARAND, WP_GARAND },
    { WP_K43_SCOPE, WP_K43, WP_K43 },
    { WP_FG42SCOPE, WP_FG42, WP_FG42 },
    { WP_MORTAR_SET, WP_MORTAR, WP_MORTAR },
    { WP_MEDIC_ADRENALINE, WP_MEDIC_ADRENALINE, WP_MEDIC_ADRENALINE },
    { WP_AKIMBO_SILENCEDCOLT, WP_COLT, WP_AKIMBO_COLT },
    { WP_AKIMBO_SILENCEDLUGER, WP_LUGER, WP_AKIMBO_LUGER },
    { WP_MOBILE_MG42_SET, WP_MOBILE_MG42, WP_MOBILE_MG42 },
    { WP_TRIPMINE, WP_TRIPMINE, WP_TRIPMINE },
    { WP_BOMB, WP_BOMB, WP_BOMB },
    { WP_POISON_SYRINGE, WP_POISON_SYRINGE, WP_POISON_SYRINGE },
    { WP_POISON_BOMB, WP_POISON_BOMB, WP_POISON_BOMB },
    { WP_POISON_MINE, WP_POISON_MINE, WP_POISON_MINE },
};

int NITMOD_WeaponInventorySlots( int weapon, nitmodWeaponInventorySlots_t *slots ) {
    unsigned int i;
    if( !slots ) return 0;
    for( i = 0; i < sizeof(inventory) / sizeof(inventory[0]); ++i ) {
        if( inventory[i].weapon == weapon ) {
            slots->ammo = inventory[i].ammo;
            slots->clip = inventory[i].clip;
            return 1;
        }
    }
    return 0;
}

int NITMOD_SelectRecoveredWeaponClip( const playerState_t *state, int weapon, int *clip ) {
    nitmodWeaponInventorySlots_t slots, sideSlots;
    int selected, sidearm;
    if( !state || !clip || !NITMOD_WeaponInventorySlots(weapon, &slots) ) return 0;
    selected = slots.clip;
    if( state->ammoclip[selected] < 0 ) return 0;
    if( BG_IsAkimboWeapon(weapon) ) {
        sidearm = BG_AkimboSidearm(weapon);
        if( !NITMOD_WeaponInventorySlots(sidearm, &sideSlots) ||
            state->ammoclip[sideSlots.clip] < 0 ) return 0;
        if( !BG_AkimboFireSequence(weapon, state->ammoclip[selected], state->ammoclip[sideSlots.clip]) )
            selected = sidearm;
    }
    if( state->ammoclip[selected] < 0 ) return 0;
    *clip = selected;
    return 1;
}
