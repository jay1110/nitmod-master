#include "g_local.h"
#include "g_nitmod_abilities.h"
#include <limits.h>

int G_NITMOD_GrantAdrenalineUpgrade( gclient_t *client,
    unsigned int firstAidUnlocks, unsigned int allowedClasses,
    unsigned int adrenalineOptions, int warMode ) {
    typedef char adrenalineBitCheck[(WP_MEDIC_ADRENALINE % 32 < 31) ? 1 : -1];
    int clip;
    if( !G_NITMOD_ClientHasAdrenaline(client, firstAidUnlocks, allowedClasses) ) return 0;
    clip = G_NITMOD_AdrenalineClip(adrenalineOptions);
    /* AddWeaponToPlayer's first-aid ammo bonus is skipped in war modes 1..4.
     * Adrenaline maps to its own original ammo/clip slots; native aliases
     * would overwrite syringe stock, so this isolated operation is explicit. */
    if( !(warMode >= 1 && warMode <= 4) && (firstAidUnlocks & 4u) ) clip += 2;
    client->ps.weapons[WP_MEDIC_ADRENALINE / 32] |= 1 << (WP_MEDIC_ADRENALINE % 32);
    client->ps.ammo[WP_MEDIC_ADRENALINE] = 0;
    client->ps.ammoclip[WP_MEDIC_ADRENALINE] = clip;
    return 1;
}

int G_NITMOD_GrantAdrenalineSpawn( gclient_t *client,
    unsigned int firstAidUnlocks, unsigned int allowedClasses,
    unsigned int adrenalineOptions, int warMode, const ammotable_t *defaults ) {
    typedef char adrenalineBitCheck[(WP_MEDIC_ADRENALINE % 32 < 31) ? 1 : -1];
    int clip, bonus;
    if( warMode >= 1 && warMode <= 4 ) return 0;
    if( !G_NITMOD_ClientHasAdrenaline(client, firstAidUnlocks, allowedClasses) ) return 0;
    if( !defaults || defaults->defaultStartingAmmo < 0 ) return -1;
    clip = adrenalineOptions & 4u ? 1 :
        (adrenalineOptions & 1u ? 0 : defaults->defaultStartingClip);
    bonus = firstAidUnlocks & 4u ? 2 : 0;
    if( clip < 0 || clip > INT_MAX - bonus ) return -1;
    client->ps.weapons[WP_MEDIC_ADRENALINE / 32] |= 1 << (WP_MEDIC_ADRENALINE % 32);
    client->ps.ammo[WP_MEDIC_ADRENALINE] = defaults->defaultStartingAmmo;
    client->ps.ammoclip[WP_MEDIC_ADRENALINE] = clip + bonus;
    return 1;
}
