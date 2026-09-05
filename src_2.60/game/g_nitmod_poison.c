#include "g_local.h"
#include "g_nitmod_config.h"
#include "g_nitmod_weapon_definition.h"
#include <limits.h>

void G_NITMOD_ClearPoison(gentity_t *victim) {
	if(!victim || !victim->client) return;
	victim->client->ps.eFlags &= ~NITMOD_EF_POISONED;
	victim->client->nitmodPoisonAttacker = -1;
	victim->client->nitmodPoisonStacks = 0;
	victim->client->nitmodPoisonNextTick = 0;
}

void G_NITMOD_CurePoisonFromHealth(gentity_t *victim, gentity_t *provider,
	qboolean cabinet) {
	int poisonOptions;

	if(!victim || !victim->client || !(victim->client->ps.eFlags & NITMOD_EF_POISONED)) return;
	poisonOptions = g_poison.integer;
	if(!(poisonOptions & 2)) return;

	/* Original Pickup_Health: with bit 8 the poisoner cannot cure their own
	 * victim using a health pack. A cabinet has no provider and always cures. */
	if(!cabinet && (poisonOptions & 8) && provider && provider->client &&
		victim->client->nitmodPoisonAttacker == provider->s.number) return;
	G_NITMOD_ClearPoison(victim);
}

qboolean G_NITMOD_PoisonAttack(gentity_t *attacker) {
	trace_t trace;
	vec3_t start, end, direction, localRight, localUp;
	gentity_t *victim;
	if(!attacker || !attacker->client || !g_poison.integer) return qfalse;
	AngleVectors(attacker->client->ps.viewangles, direction, localRight, localUp);
	CalcMuzzlePointForActivate(attacker, direction, localRight, localUp, start);
	VectorMA(start, 64, direction, end);
	G_HistoricalTrace(attacker, &trace, start, NULL, NULL, end,
		attacker->s.number, MASK_SHOT);
	if(trace.fraction == 1 || trace.entityNum < 0 || trace.entityNum >= level.maxclients) return qfalse;
	victim = &g_entities[trace.entityNum];
	if(!victim->client || victim->health <= 0 || victim->client->invulnerabilityTime >= level.time) return qfalse;
	if(!g_friendlyFire.integer && g_gametype.integer != GT_WOLF_LMS && OnSameTeam(attacker, victim)) return qfalse;
	/* Original Weapon_Poison emits private event 100 with NCS sound slot 8
	 * before latching poison. The typed adapter uses ET's equivalent bounded
	 * general-sound event; original clients already resolve the same slot. */
	NITMOD_PlaySoundEvent(victim, 8);
	if(!(victim->client->ps.eFlags & NITMOD_EF_POISONED))
		victim->client->nitmodPoisonStacks = 0;
	victim->client->ps.eFlags |= NITMOD_EF_POISONED;
	victim->client->nitmodPoisonAttacker = attacker->s.number;
	if(victim->client->nitmodPoisonStacks < INT_MAX) ++victim->client->nitmodPoisonStacks;
	victim->client->nitmodPoisonNextTick = level.time;
	return qtrue;
}

void G_NITMOD_RunPoison(gentity_t *victim) {
	gclient_t *client;
	gentity_t *attacker = NULL;
	int damage, interval;
	if(!victim || !(client = victim->client) || !(client->ps.eFlags & NITMOD_EF_POISONED)) return;
	if(victim->health <= 0 || client->sess.sessionTeam == TEAM_SPECTATOR || !client->nitmodPoisonStacks) {
		G_NITMOD_ClearPoison(victim);
		return;
	}
	if(client->nitmodPoisonNextTick >= level.time) return;
	if(client->nitmodPoisonAttacker >= 0 && client->nitmodPoisonAttacker < level.maxclients)
		attacker = &g_entities[client->nitmodPoisonAttacker];
	damage = (g_poison.integer & 4) ? 10 : 1;
	interval = (g_poison.integer & 4) ? 1500 : 50;
	G_NITMOD_WeaponDamageOverrides(WP_POISON_SYRINGE, &damage, NULL, NULL);
	G_Damage(victim, attacker, attacker, NULL, NULL,
		damage * client->nitmodPoisonStacks, 0, MOD_POISON);
	client->nitmodPoisonNextTick = level.time + interval;
}
