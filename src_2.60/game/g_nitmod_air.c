#include <limits.h>
#include "g_local.h"
#include "g_nitmod_air.h"
#include "nitmod_air.h"

int G_NITMOD_UpdateClientAir( gentity_t *entity, int now,
	unsigned int battleSenseUnlocked ) {
	nitmodAirState_t air;
	gclient_t *client;
	int damage;
	if( !entity || !entity->client ) return 0;
	client = entity->client;
	/* Original P_WorldEffects 0x3cd78 does not consult PW_BREATHER. */
	air.deadline = client->airOutTime;
	air.drowningDamage = entity->damage;
	damage = NITMOD_UpdateAir( &air, now, entity->waterlevel,
		client->noclip, entity->health, battleSenseUnlocked );
	client->airOutTime = air.deadline;
	entity->damage = air.drowningDamage;
	return damage;
}
