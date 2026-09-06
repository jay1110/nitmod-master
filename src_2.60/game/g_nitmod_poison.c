#include "g_local.h"
#include "g_nitmod_config.h"
#include "g_nitmod_weapon_definition.h"
#include <limits.h>

qboolean G_NITMOD_IsViewingCamera(const gclient_t *client) {
	/* Poison shares this bit. Only Cmd_StartCamera_f creates a camera portal. */
	return client && client->cameraPortal && (client->ps.eFlags & EF_VIEWING_CAMERA);
}

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
	/* Weapon_Poison keeps fractional coordinates and lowers the leaned
	 * muzzle, unlike the ET activation helper (which also SnapVectors it). */
	VectorCopy(attacker->s.pos.trBase, start);
	/* Original ELF 0xf3590..0xf35c8, 0xf3770 and 0xf3820. */
	if(attacker->health <= 0) start[2] += 25;
	else if(attacker->client->ps.viewangles[PITCH] > 30 &&
		(attacker->client->ps.eFlags & EF_CROUCHING)) start[2] += 30;
	else start[2] += attacker->client->ps.viewheight;
	VectorMA(start, attacker->client->ps.leanf, localRight, start);
	start[2] -= fabs(attacker->client->ps.leanf / 3.5f);
	VectorMA(start, 64, direction, end);
	G_HistoricalTrace(attacker, &trace, start, NULL, NULL, end,
		attacker->s.number, MASK_SHOT);
	if(trace.fraction == 1 || trace.entityNum < 0 || trace.entityNum >= level.maxclients) return qfalse;
	victim = &g_entities[trace.entityNum];
	/* Original client+0x154 is the invulnerability powerup expiry, also
	 * written by the typed NITMOD_SetSpawnProtection path. */
	if(!victim->client || victim->health <= 0 ||
		victim->client->ps.powerups[PW_INVULNERABLE] >= level.time) return qfalse;
	/* Original Weapon_Poison ELF 0xf36b4 / 0xf3736: friendly-fire bit 0,
	 * with the team restriction bypassed only in Deathmatch (8). */
	if(!(g_friendlyFire.integer & 1) && g_gametype.integer != GT_WOLF_DM && OnSameTeam(attacker, victim)) return qfalse;
	/* Original Weapon_Poison emits private event 100 with NCS sound slot 8
	 * before latching poison. The typed adapter uses ET's equivalent bounded
	 * general-sound event; original clients already resolve the same slot. */
	NITMOD_PlaySoundEvent(victim, 8);
	/* Original Weapon_Poison only initializes the timer on first infection;
	 * repeated hits transfer attribution and add a stack without delaying it. */
	if(!(victim->client->ps.eFlags & NITMOD_EF_POISONED)) {
		victim->client->nitmodPoisonStacks = 0;
		victim->client->nitmodPoisonNextTick = level.time;
	}
	victim->client->ps.eFlags |= NITMOD_EF_POISONED;
	victim->client->nitmodPoisonAttacker = attacker->s.number;
	if(victim->client->nitmodPoisonStacks < INT_MAX) ++victim->client->nitmodPoisonStacks;
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
	interval = G_NITMOD_PoisonInterval(interval);
	G_NITMOD_WeaponDamageOverrides(WP_POISON_SYRINGE, &damage, NULL, NULL);
	G_Damage(victim, attacker, attacker, NULL, NULL,
		damage * client->nitmodPoisonStacks, 0, MOD_POISON);
	client->nitmodPoisonNextTick = level.time + interval;
}
