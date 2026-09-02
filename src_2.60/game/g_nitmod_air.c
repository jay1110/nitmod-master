#include <limits.h>
#include "g_local.h"
#include "g_nitmod_air.h"
#include "nitmod_air.h"

static int NITMOD_AirClampInt( double value ) {
	if( value > INT_MAX ) return INT_MAX;
	if( value < INT_MIN ) return INT_MIN;
	return (int)value;
}

int G_NITMOD_UpdateClientAir( gentity_t *entity, int now,
	unsigned int battleSenseUnlocked ) {
	nitmodAirState_t air;
	gclient_t *client;
	int damage;
	if( !entity || !entity->client ) return 0;
	client = entity->client;
	/* Preserve the ET breather branch, including its nonzero (not >0)
	 * condition and deadline calculation. Only integer overflow saturates. */
	if( !client->noclip && entity->waterlevel == 3 && client->airOutTime < now &&
		client->ps.powerups[PW_BREATHER] ) {
		double elapsed = (double)now - client->airOutTime;
		client->ps.powerups[PW_BREATHER] = NITMOD_AirClampInt(
			(double)client->ps.powerups[PW_BREATHER] - elapsed );
		client->airOutTime = NITMOD_AirClampInt((double)now + elapsed);
		return 0;
	}
	air.deadline = client->airOutTime;
	air.drowningDamage = entity->damage;
	damage = NITMOD_UpdateAir( &air, now, entity->waterlevel,
		client->noclip, entity->health, battleSenseUnlocked );
	client->airOutTime = air.deadline;
	entity->damage = air.drowningDamage;
	return damage;
}
