#include "g_local.h"
#include "g_nitmod_rifle.h"

int G_NITMOD_RevokeRifleGrenade( gentity_t *entity, int nativeWeapon ) {
    unsigned int words[sizeof(((playerState_t *)0)->weapons) / sizeof(unsigned int)];
    unsigned int mask;
    int slot;
    gclient_t *client;
    if( !entity || !entity->client ||
        (nativeWeapon != WP_GPG40 && nativeWeapon != WP_M7) ) return -1;
    client = entity->client;
    /* Slot identity comes from the owned playerstate rather than subtracting
     * potentially unrelated pointers. Native callers keep these consistent. */
    slot = client->ps.clientNum;
    if( slot < 0 || slot >= MAX_CLIENTS ) return -1;
    mask = 1u << (nativeWeapon % 32);
    memcpy(words, client->ps.weapons, sizeof(words));
    if( !(words[nativeWeapon / 32] & mask) ) return 0;
    words[nativeWeapon / 32] &= ~mask;
    memcpy(client->ps.weapons, words, sizeof(words));
    if( client->sess.rifleGrenadeStatus ) {
        client->sess.rifleGrenadeStatus = 0;
        ClientUserinfoChanged(slot);
    }
    return 1;
}
