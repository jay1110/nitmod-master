#include "g_local.h"
#include "g_nitmod_abilities.h"
#include "g_nitmod_weapons.h"
#include "g_nitmod_war.h"

void G_NITMOD_ResetWarState( nitmodWarState_t *state ) {
    if( state ) state->stripped = 0;
}

int G_NITMOD_ApplyWarEntry( gentity_t *entity, nitmodWarState_t *state,
    int warMode, int isDemoClient ) {
    if( !state || !G_NITMOD_CanCheckWeapons(entity, isDemoClient) ||
        warMode != 4 || state->stripped ) return 0;
    G_NITMOD_RemoveWeapons(entity->client);
    entity->client->ps.weapon = WP_KNIFE;
    /* Original event 0x19 maps to native EV_NOAMMO, not raw ID 25.
     * Preserve the original ordering: mark completion after the event. */
    G_AddEvent(entity, EV_NOAMMO, 0);
    state->stripped = 1;
    return 1;
}
