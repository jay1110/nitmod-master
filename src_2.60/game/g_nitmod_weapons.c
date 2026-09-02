#include "g_local.h"
#include "g_nitmod_weapons.h"

void G_NITMOD_RemoveWeapons( gclient_t *client ) {
    /* Original item identities, NOT original numeric weapon IDs.
     * Poison syringe/bomb/mine and engineer bomb have no native equivalent.
     * Knife, satchel detonator and internal dummy/effect weapons survive. */
    static const weapon_t removed[] = {
        WP_PANZERFAUST, WP_FLAMETHROWER, WP_MOBILE_MG42, WP_MOBILE_MG42_SET,
        WP_MORTAR, WP_MORTAR_SET, WP_FG42, WP_FG42SCOPE, WP_K43, WP_GARAND,
        WP_K43_SCOPE, WP_GARAND_SCOPE, WP_STEN, WP_MP40, WP_THOMPSON,
        WP_KAR98, WP_GPG40, WP_CARBINE, WP_M7, WP_COLT, WP_SILENCED_COLT,
        WP_AKIMBO_COLT, WP_AKIMBO_SILENCEDCOLT, WP_LUGER, WP_SILENCER,
        WP_AKIMBO_LUGER, WP_AKIMBO_SILENCEDLUGER, WP_GRENADE_PINEAPPLE,
        WP_GRENADE_LAUNCHER, WP_BINOCULARS, WP_PLIERS, WP_DYNAMITE,
        WP_LANDMINE, WP_MEDIC_ADRENALINE, WP_MEDIC_SYRINGE, WP_MEDKIT,
        WP_AMMO, WP_ARTY, WP_SMOKE_MARKER, WP_SMOKE_BOMB, WP_SATCHEL,
        WP_TRIPMINE
    };
    unsigned int words[sizeof(client->ps.weapons) / sizeof(client->ps.weapons[0])];
    unsigned int i;
    if( !client ) return;
    /* Unsigned representation avoids signed left-shift UB for bit 31. */
    memcpy(words, client->ps.weapons, sizeof(words));
    for( i = 0; i < sizeof(removed) / sizeof(removed[0]); i++ ) {
        words[removed[i] / 32] &= ~(1u << (removed[i] % 32));
    }
    memcpy(client->ps.weapons, words, sizeof(words));
}
