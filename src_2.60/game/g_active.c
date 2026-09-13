#include "nitmod_xp_snapshot.h"

#include "g_local.h"
#include "g_nitmod_nxac.h"
extern qboolean Bot_Util_AllowPush(int weaponId);
#include "g_nitmod_admin.h"
#include "g_nitmod_mdx.h"
#include "nitmod_lua_events.h"
#include "nitmod_weapon_recoil.h"
#include "g_nitmod_weapon_definition.h"
#include "g_nitmod_air.h"
#include "g_nitmod_restrictions.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_integrity.h"
#include "g_nitmod_config.h"
#include "g_nitmod_antiwarp.h"
#include "g_nitmod_hitboxdebug.h"
#include "g_nitmod_abilities.h"
#include "g_nitmod_charge.h"
#include "nitmod_air.h"
#include "nitmod_weapon_reload.h"
#include "nitmod_regeneration.h"
#include "nitmod_support_time.h"
#include <limits.h>

/* Original G_SendVoiceChat 0x59210: Pmove alternate tool action uses the
 * ordinary team voice path, including its squelch and recipient filters. */
void G_SendVoiceChat(int clientNum, const char *id) {
 if(clientNum<0 || clientNum>=level.maxclients || !g_entities[clientNum].client || !id) return;
 G_Voice(&g_entities[clientNum],NULL,SAY_TEAM,id,qfalse);
}

/*
===============
G_DamageFeedback

Called just before a snapshot is sent to the given player.
Totals up all damage and generates both the player_state_t
damage values to that client for pain blends and kicks, and
global pain sound events for all clients.
===============
*/
void P_DamageFeedback( gentity_t *player ) {
	gclient_t	*client;
	float	count;
	vec3_t	angles;

	client = player->client;
	if ( client->ps.pm_type == PM_DEAD ) {
		return;
	}

	// total points of damage shot at the player this frame
	count = client->damage_blood;
	if ( count == 0 ) {
		return;		// didn't take any damage
	}

	if ( count > 127 ) {
		count = 127;
	}

	// send the information to the client

	// world damage (falling, slime, etc) uses a special code
	// to make the blend blob centered instead of positional
	if ( client->damage_fromWorld ) {
		client->ps.damagePitch = 255;
		client->ps.damageYaw = 255;

		client->damage_fromWorld = qfalse;
	} else {
		vectoangles( client->damage_from, angles );
		client->ps.damagePitch = angles[PITCH]/360.0 * 256;
		client->ps.damageYaw = angles[YAW]/360.0 * 256;
	}

	// play an apropriate pain sound
	if ( (level.time > player->pain_debounce_time) && !(player->flags & FL_GODMODE) && !(player->s.powerups & PW_INVULNERABLE) ) {	//----(SA)	
		player->pain_debounce_time = level.time + 700;
		G_AddEvent( player, EV_PAIN, player->health );
	}

	client->ps.damageEvent++;	// Ridah, always increment this since we do multiple view damage anims

	client->ps.damageCount = count;

	//
	// clear totals
	//
	client->damage_blood = 0;
	client->damage_knockback = 0;
}


#define MIN_BURN_INTERVAL 399 // JPW NERVE set burn timeinterval so we can do more precise damage (was 199 old model)

/*
=============
P_WorldEffects

Check for lava / slime contents and drowning
=============
*/
void P_WorldEffects( gentity_t *ent ) {
	int waterlevel;
	int drowningDamage;

	/* Original P_WorldEffects tests Battle Sense reward bit 0x20. */
	drowningDamage = G_NITMOD_UpdateClientAir( ent, level.time,
		ent->client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] );
	if( ent->client->noclip ) {
		return;
	}
	waterlevel = ent->waterlevel;
	if( drowningDamage ) {
		/* Original P_WorldEffects 0x3cdb9/0x3ce88: only surviving
		 * drowning ticks emit a fixed-bank Nitmod sound (9 or 10). */
		if( ent->health > drowningDamage ) {
			NITMOD_PlaySoundEvent(ent, (rand() & 1) ? 9 : 10);
		}
		ent->pain_debounce_time = level.time + 200;
		G_Damage(ent, NULL, NULL, NULL, NULL, drowningDamage, 0, MOD_WATER);
	}

	//
	// check for sizzle damage (move to pmove?)
	//
	if (waterlevel && (ent->watertype&CONTENTS_LAVA) ) {
		if (ent->health > 0	&& ent->pain_debounce_time <= level.time ) {

				if (ent->watertype & CONTENTS_LAVA) {
					G_Damage (ent, NULL, NULL, NULL, NULL, 
						30*waterlevel, 0, MOD_LAVA);
				}

		}
	}

	//
	// check for burning from flamethrower
	//
	// JPW NERVE MP way
	if (ent->s.onFireEnd && ent->client) {
		if (level.time - ent->client->lastBurnTime >= MIN_BURN_INTERVAL) { 

			// JPW NERVE server-side incremental damage routine / player damage/health is int (not float)
			// so I can't allocate 1.5 points per server tick, and 1 is too weak and 2 is too strong.  
			// solution: allocate damage far less often (MIN_BURN_INTERVAL often) and do more damage.
			// That way minimum resolution (1 point) damage changes become less critical.

			ent->client->lastBurnTime = level.time;
			if ((ent->s.onFireEnd > level.time) && (ent->health > 0)) {
				gentity_t *attacker;
   				attacker = g_entities + ent->flameBurnEnt;
				/* Original P_WorldEffects resolves flame damage for every burn tick. */
				G_Damage (ent, attacker, attacker, NULL, NULL,
					G_GetWeaponDamage(WP_FLAMETHROWER), DAMAGE_NO_KNOCKBACK, MOD_FLAMETHROWER);
			}
		}
	}
	// jpw
}



/*
===============
G_SetClientSound
===============
*/
void G_SetClientSound( gentity_t *ent ) {
/*	if (ent->waterlevel && (ent->watertype & CONTENTS_LAVA) )	//----(SA)	modified since slime is no longer deadly
		ent->s.loopSound = level.snd_fry;
	else*/ // Gordon: doesnt exist
		ent->s.loopSound = 0;
}

/*
==============
PushBot
==============
*/
void BotVoiceChatAfterIdleTime( int client, const char *id, int mode, int delay, qboolean voiceonly, int idleTime, qboolean forceIfDead );

void PushBot( gentity_t *ent, gentity_t *other ) {
	vec3_t dir, ang, f, r;
	float oldspeed;
	/* Original PushBot 0x3cf08..0x3cf46. */
	if (!other->client || !Bot_Util_AllowPush(other->client->ps.weapon) ||
		!other->client->sess.botPush) return;
	//
	oldspeed = VectorLength( other->client->ps.velocity );
	if (oldspeed < 200)
		oldspeed = 200;
	//
	VectorSubtract( other->r.currentOrigin, ent->r.currentOrigin, dir );
	VectorNormalize( dir );
	vectoangles( dir, ang );
	AngleVectors( ang, f, r, NULL );
	f[2] = 0;
	r[2] = 0;
	//
	VectorMA( other->client->ps.velocity, 200, f, other->client->ps.velocity );
	VectorMA( other->client->ps.velocity, 100 * ((level.time+(ent->s.number*1000))%4000 < 2000 ? 1.0 : -1.0), r, other->client->ps.velocity );
	//
	if (VectorLengthSquared( other->client->ps.velocity ) > SQR(oldspeed)) {
		VectorNormalize( other->client->ps.velocity );
		VectorScale( other->client->ps.velocity, oldspeed, other->client->ps.velocity );
	}

}

/*
==============
ClientNeedsAmmo
==============
*/
qboolean ClientNeedsAmmo( int client ) {
	return AddMagicAmmo( &g_entities[client], 0 ) ? qtrue : qfalse;
}

// Does ent have enough "energy" to call artillery?
qboolean ReadyToCallArtillery(gentity_t *ent) {
 return G_NITMOD_ChargeAction(ent,NITMOD_TABLE_ARTILLERY,SK_SIGNALS,qfalse);
}

/* Original ReadyToConstruct 0x3d1b0 has a distinct noCharge contract:
 * affordability is checked first; only a successful updating call refills. */
qboolean ReadyToConstruct(gentity_t *ent, gentity_t *constructible, qboolean updateState) {
 int team,duration,weaponTime;
 float fraction;
 double candidate;
 if(!ent || !ent->client || !constructible) return qfalse;
 team=ent->client->sess.sessionTeam-TEAM_AXIS;
 if(team<0 || team>1 || constructible->constructibleStats.duration<=0) return qfalse;
 duration=level.engineerChargeTime[team];
 if(duration<0) return qfalse;
 candidate=ent->client->ps.classWeaponTime;
 if(candidate+duration<level.time) candidate=(double)level.time-duration;
 if(g_debugConstruct.integer) {
  candidate+=((double)duration/((double)constructible->constructibleStats.duration/FRAMETIME))*0.5;
 } else {
  NITMOD_GameplayTableValue(NITMOD_TABLE_CONSTRUCT,
   ent->client->sess.nitmodSkillMasks[SK_EXPLOSIVES_AND_CONSTRUCTION],&fraction);
  candidate+=((double)duration/((double)constructible->constructibleStats.duration/FRAMETIME))*fraction*constructible->constructibleStats.chargebarreq;
 }
 if(!(candidate>=INT_MIN && candidate<(double)INT_MAX+1.0)) return qfalse;
 weaponTime=(int)candidate;
 if(weaponTime>level.time) return qfalse;
 if(updateState) {
  if(G_NITMOD_LegacyCvarInteger("g_noCharge",0)) {
   candidate=(double)level.time-duration;
   if(candidate<INT_MIN) return qfalse;
   weaponTime=(int)candidate;
  }
  ent->client->ps.classWeaponTime=weaponTime;
 }
 return qtrue;
}

void BotSetBlockEnt( int client, int blocker );
/*
==============
CheckBotImpacts
==============
*/
void CheckBotImpacts( gentity_t *ent, gentity_t *other ) {
	char *blockEnts[] = {"func_explosive", NULL};
	int j;

	for (j=0; blockEnts[j]; j++) {
		if (other->classname && !Q_stricmp( other->classname, blockEnts[j] )) {
			BotSetBlockEnt( ent->s.number, other->s.number );
		}
	}
}

//==============================================================

/*
==============
ClientImpacts
==============
*/
void ClientImpacts( gentity_t *ent, pmove_t *pm ) {
	int		i, j;
	gentity_t	*other;
	trace_t	trace;

	memset( &trace, 0, sizeof(trace) );
	for (i=0 ; i<pm->numtouch ; i++) {
		for (j=0 ; j<i ; j++) {
			if (pm->touchents[j] == pm->touchents[i] ) {
				break;
			}
		}
		if (j != i) {
			continue;	// duplicated
		}
		other = &g_entities[ pm->touchents[i] ];

		/* Original ClientImpacts suppresses both pushes while the contacted
		 * client has invulnerability, and dispatches only the other touch. */
		if ( ent->client && (other->r.svFlags & SVF_BOT) &&
			other->client && !other->client->ps.powerups[PW_INVULNERABLE] ) {
			PushBot( ent, other );
		}

		if ( (ent->r.svFlags & SVF_BOT) &&
			ent->s.groundEntityNum == other->s.number && other->client &&
			!other->client->ps.powerups[PW_INVULNERABLE] ) {
			PushBot( other, ent );
		}

		if ( !other->touch ) {
			continue;
		}

		other->touch( other, ent, &trace );
	}

}

/*
============
G_TouchTriggers

Find all trigger entities that ent's current position touches.
Spectators will only interact with teleporters.
============
*/
void	G_TouchTriggers( gentity_t *ent ) {
	int			i, num;
	int			touch[MAX_GENTITIES];
	gentity_t	*hit;
	trace_t		trace;
	vec3_t		mins, maxs;
	static vec3_t	range = { 40, 40, 52 };

	if ( !ent->client ) {
		return;
	}

	// Arnout: reset the pointer that keeps track of trigger_objective_info tracking
	ent->client->touchingTOI = NULL;

	// dead clients don't activate triggers!
	/* Original G_TouchTriggers 0x3d525 also rejects flag 0x00800000. */
	if ( ent->client->ps.stats[STAT_HEALTH] <= 0 ||
		(ent->client->ps.eFlags & EF_SPARE0) ) {
		return;
	}

	VectorSubtract( ent->client->ps.origin, range, mins );
	VectorAdd( ent->client->ps.origin, range, maxs );

	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	// can't use ent->absmin, because that has a one unit pad
	VectorAdd( ent->client->ps.origin, ent->r.mins, mins );
	VectorAdd( ent->client->ps.origin, ent->r.maxs, maxs );

	for ( i=0 ; i<num ; i++ ) {
		hit = &g_entities[touch[i]];

		if ( !hit->touch && !ent->touch ) {
			continue;
		}
		if ( !( hit->r.contents & CONTENTS_TRIGGER ) ) {
			continue;
		}

		// Arnout: invisible entities can't be touched
		// Gordon: radiant tabs arnout! ;)
		if( hit->entstate == STATE_INVISIBLE ||
			hit->entstate == STATE_UNDERCONSTRUCTION ) {
			continue;
		}

		// ignore most entities if a spectator
		if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
			if ( hit->s.eType != ET_TELEPORT_TRIGGER ) {
				continue;
			}
		}

		// use seperate code for determining if an item is picked up
		// so you don't have to actually contact its bounding box
		if ( hit->s.eType == ET_ITEM ) {
			if ( !BG_PlayerTouchesItem( &ent->client->ps, &hit->s, level.time ) ) {
				continue;
			}
		} else {
			// MrE: always use capsule for player
			if ( !trap_EntityContactCapsule( mins, maxs, hit ) ) {
			//if ( !trap_EntityContact( mins, maxs, hit ) ) {
				continue;
			}
		}

		memset( &trace, 0, sizeof(trace) );

		if ( hit->touch ) {
			hit->touch (hit, ent, &trace);
		}

	}
}

/*
=================
SpectatorThink
=================
*/
/* Original G_SetIdentifyClient (qagame ELF 0x3d8d0), shared by both
 * spectator and active think paths. Preserve disguised/followed identities. */
static void G_SetIdentifyClient( gentity_t *ent ) {
	gclient_t *client = ent->client;
	int number = client->ps.identifyClient;
	gentity_t *target;

	if( number >= 0 && number < MAX_GENTITIES ) {
		target = &g_entities[number];
		if( target->inuse && target->client &&
			(target->team == ent->team || target->client->ps.powerups[PW_OPS_DISGUISED] ||
			(client->ps.pm_flags & PMF_FOLLOW)) ) {
			client->ps.identifyClientHealth = target->health;
			return;
		}
	}
	client->ps.identifyClient = -1;
	client->ps.identifyClientHealth = 0;
}

void SpectatorThink( gentity_t *ent, usercmd_t *ucmd ) {
	pmove_t	pm;
	gclient_t	*client;

	client = ent->client;

	G_SetIdentifyClient(ent);

	if ( client->sess.spectatorState != SPECTATOR_FOLLOW ) {
		client->ps.pm_type = PM_SPECTATOR;
		client->ps.speed = 800;	// was: 400 // faster than normal
		if (client->ps.sprintExertTime)
			client->ps.speed *= 3;	// (SA) allow sprint in free-cam mode


		// OSP - dead players are frozen too, in a timeout
		if((client->ps.pm_flags & PMF_LIMBO) && level.match_pause != PAUSE_NONE) {
			client->ps.pm_type = PM_FREEZE;
		} else if( client->noclip ) {
			client->ps.pm_type = PM_NOCLIP;
		}

		// set up for pmove
		memset (&pm, 0, sizeof(pm));
		pm.ps = &client->ps;
		pm.pmext = &client->pmext;
		pm.nitmodDoubleJump = g_doubleJump.integer;
		pm.nitmodLeanEnabled = qtrue;
		pm.nitmodReloadEnabled = qtrue;
		pm.nitmodAuthoritativeWeapons = qtrue;
	pm.nitmodVoiceChat = G_SendVoiceChat;
		pm.nitmodWarMode = G_NITMOD_ConfiguredWarMode();
		pm.nitmodProneDelay = G_NITMOD_LegacyCvarInteger("n_proneDelay", 0);
		pm.nitmodCrouchStandDelay = G_NITMOD_LegacyCvarInteger("n_crouchStandDelay", 0);
		pm.nitmodStandCrouchDelay = G_NITMOD_LegacyCvarInteger("n_standCrouchDelay", 0);
		pm.nitmodNoReload = (unsigned int)G_NITMOD_ConfiguredNoReload();
		pm.nitmodWeaponFlags = G_NITMOD_ConfiguredWeaponFlags();
		pm.nitmodRefreshWeaponOptions = qtrue;
		pm.nitmodFixedPhysics = G_NITMOD_LegacyCvarInteger("g_fixedphysics", 0) != 0;
		pm.nitmodFixedPhysicsFps = G_NITMOD_LegacyCvarInteger("g_fixedphysicsfps", 125);

		pm.nitmodDoubleJumpHeight = g_DJHeight.value;
		pm.nitmodReloadPreferenceFlags = NITMOD_EncodeReloadPreferences(0,
			client->pers.bAutoReloadAux, client->pers.bAltReloadAux);
		pm.character = client->pers.character;
		pm.cmd = *ucmd;
		pm.skill = client->sess.skill;
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;	// spectators can fly through bodies
		pm.trace = trap_TraceCapsuleNoEnts;
		pm.pointcontents = trap_PointContents;

#ifdef SAVEGAME_SUPPORT
		if( g_gametype.integer == GT_SINGLE_PLAYER && g_reloading.integer )
			pm.reloading = qtrue;
#endif // SAVEGAME_SUPPORT

		Pmove( &pm ); // JPW NERVE

		// Rafael - Activate
		// Ridah, made it a latched event (occurs on keydown only)
		if (client->latched_buttons & BUTTON_ACTIVATE)
		{
			Cmd_Activate_f (ent);
		}

		// save results of pmove
		VectorCopy( client->ps.origin, ent->s.origin );

		G_TouchTriggers( ent );
		trap_UnlinkEntity( ent );
	}

	if (ent->flags & FL_NOFATIGUE)
		ent->client->pmext.sprintTime = SPRINTTIME;


	client->oldbuttons = client->buttons;
	client->buttons = ucmd->buttons;

//----(SA)	added
	client->oldwbuttons = client->wbuttons;
	client->wbuttons = ucmd->wbuttons;

	// MV clients use these buttons locally for other things
	if(client->pers.mvCount < 1) {
		// attack button cycles through spectators
		if ( ( client->buttons & BUTTON_ATTACK ) && ! ( client->oldbuttons & BUTTON_ATTACK ) ) {
			Cmd_FollowCycle_f( ent, 1 );
		}
		// activate button swaps places with bot
		else if( client->sess.sessionTeam != TEAM_SPECTATOR &&
				( ( client->buttons & BUTTON_ACTIVATE ) && ! ( client->oldbuttons & BUTTON_ACTIVATE ) ) &&
				( g_entities[ent->client->sess.spectatorClient].client ) &&
				( g_entities[ent->client->sess.spectatorClient].r.svFlags & SVF_BOT ) )
		{
			Cmd_SwapPlacesWithBot_f( ent, ent->client->sess.spectatorClient );
		} else if ( 
			( client->sess.sessionTeam == TEAM_SPECTATOR ) && // don't let dead team players do free fly
			( client->sess.spectatorState == SPECTATOR_FOLLOW ) && 
			( ( ( client->buttons & BUTTON_ACTIVATE ) && 
			! ( client->oldbuttons & BUTTON_ACTIVATE )) || ucmd->upmove > 0 ) &&
			G_allowFollow(ent, TEAM_AXIS) && G_allowFollow(ent, TEAM_ALLIES) )
		{
			// code moved to StopFollowing
			StopFollowing(ent);
		}
	}
}


/*
=================
ClientInactivityTimer

Returns qfalse if the client is dropped
=================
*/
qboolean ClientInactivityTimer( gclient_t *client ) {
	int duration = client->sess.sessionTeam == TEAM_SPECTATOR ? g_spectatorInactivity.integer : g_inactivity.integer;
	int clientNum = (int)(client - level.clients);
	qboolean spectatorExempt = qfalse;
	/* Original ClientInactivityTimer 0x3dd30: disabled timers have a fixed
	 * one-minute grace period, including after a live Cvar change. */
	if((client->sess.sessionTeam == TEAM_SPECTATOR && duration <= 0) ||
	   ((client->sess.sessionTeam == TEAM_AXIS || client->sess.sessionTeam == TEAM_ALLIES) && duration <= 0)) {
		client->inactivityTime = (int)((unsigned int)level.time + 60000u);
		client->inactivityWarning = qfalse;
		return qtrue;
	}
	if(client->sess.sessionTeam == TEAM_SPECTATOR) {
		int i, occupiedPrivate = 0;
		int privateSlots = trap_Cvar_VariableIntegerValue("sv_privateClients");
		/* Preserve the private-slot rule while bounding its original array scan. */
		if(privateSlots < 0) privateSlots = 0;
		if(privateSlots > level.maxclients) privateSlots = level.maxclients;
		if(privateSlots > MAX_CLIENTS) privateSlots = MAX_CLIENTS;
		for(i = 0; i < privateSlots; ++i)
			if(level.clients[i].pers.connected != CON_DISCONNECTED) ++occupiedPrivate;
		spectatorExempt = ((g_inactivityOptions.integer & 1) && client->sess.spectatorState == SPECTATOR_FOLLOW) ||
			(!(g_inactivityOptions.integer & 2) &&
			 ((clientNum < privateSlots && occupiedPrivate < privateSlots) ||
			  level.numConnectedClients < level.maxclients + occupiedPrivate - privateSlots));
	}
	if(client->pers.cmd.forwardmove || client->pers.cmd.rightmove || client->pers.cmd.upmove ||
	   (client->pers.cmd.wbuttons & (WBUTTON_ATTACK2 | WBUTTON_LEANLEFT | WBUTTON_LEANRIGHT)) ||
	   (client->pers.cmd.buttons & BUTTON_ATTACK) || client->ps.pm_type == PM_DEAD ||
	   (client->ps.pm_flags & PMF_LIMBO) ||
	   ((client->ps.eFlags & EF_PRONE) && client->ps.weapon == WP_MOBILE_MG42_SET) ||
	   spectatorExempt || client->sess.nitmodEttvSlave ||
	   (G_NITMOD_AdminPrivilege(clientNum,"inactivity") &&
	    (client->sess.sessionTeam == TEAM_SPECTATOR || !(g_inactivityOptions.integer & 4)))) {
		/* Permission9 (inactivity) always protects spectators; option4 only
		 * removes the playing-team exemption. ETTV is independently exempt. */
		client->inactivityWarning = qfalse;
		client->inactivityTime = (int)((unsigned int)level.time + 1000u * (unsigned int)duration);
		return qtrue;
	}
	if(client->pers.localClient) return qtrue;
	if(!client->inactivityWarning) {
		if(level.time <= (int)((unsigned int)client->inactivityTime - (unsigned int)duration * 500u)) return qtrue;
		if(client->sess.sessionTeam == TEAM_SPECTATOR) {
			trap_SendServerCommand(clientNum, va("pop \"^8INACTIVITY WARNING: ^7%i seconds until inactivity drop!\"", duration / 2));
			G_Printf("%is spectator inactivity warning issued to: %s\n", duration / 2, client->pers.netname);
		} else {
			trap_SendServerCommand(clientNum, va("pop \"^8INACTIVITY WARNING: ^7%i seconds until moving to spectators for inactivity!\"", duration / 2));
			G_Printf("%is inactivity warning issued to: %s\n", duration / 2, client->pers.netname);
		}
		client->inactivityWarning = qtrue;
		return qtrue;
	}
	if(level.time <= client->inactivityTime) return qtrue;
	if(client->sess.sessionTeam != TEAM_SPECTATOR) {
		client->inactivityTime = (int)((unsigned int)level.time + (g_spectatorInactivity.integer ? (unsigned int)g_spectatorInactivity.integer * 1000u : 60000u));
		client->inactivityWarning = qfalse;
		SetTeam(&g_entities[clientNum], "spectator", qtrue, 0, 0, qfalse);
		trap_SendServerCommand(-1, va("pop \"^8INACTIVITY: ^7%s^7 moved to spectators\"", client->pers.netname));
		return qtrue;
	}
	/* Original preserves the expired warning/deadline until disconnect. */
	trap_DropClient(clientNum, "Dropped due to inactivity", 0);
	return qfalse;
}


/*
==================
ClientTimerActions

Actions that happen once a second
==================
*/
void G_NITMOD_HealthTimer(gentity_t *ent, int msec, unsigned int medicOptions, int war) {
	gclient_t *client;
	int baseRate, extraRate;
	qboolean regenerate;
	if(!ent || !ent->client) return;

	client = ent->client;
	/* Original ClientTimerActions gates before residual accumulation. */
	if((unsigned int)war - 1u < 4u ||
		(client->sess.playerType == PC_MEDIC && (medicOptions & 32u))) return;
	extraRate = medicOptions & 64u ? 1 : medicOptions & 128u ? 0 : 2;
	baseRate = extraRate + 1;
	/* Original 0x3e2ce..0x3e2d9 stores the wrapping ADD result. */
	client->timeResidual = (int)((unsigned int)client->timeResidual + (unsigned int)msec);

	while( client->timeResidual >= 1000 ) {
		client->timeResidual -= 1000;

		// regenerate
		/* Original ClientTimerActions (ELF 0x3e270): DM option bit 2 admits
		 * every class. Otherwise a living medic regenerates normally, and
		 * g_medics bit 16 admits a client with the sixth First Aid reward. */
		regenerate = NITMOD_RegenerationEligible(g_gametype.integer == GT_WOLF_DM,
			g_DMOptions.integer, medicOptions,
			client->sess.playerType == PC_MEDIC &&
			!(client->ps.eFlags & (EF_DEAD | NITMOD_EF_POISONED)),
			G_NITMOD_FirstAidUnlocks(client));
		if( regenerate ) {
			int maximum = BG_EffectiveMaxHealth(&client->ps);
			if( ent->health < client->ps.stats[STAT_MAX_HEALTH]) {
				int next = (int)((unsigned int)ent->health + (unsigned int)baseRate);
				ent->health = (int)(next > client->ps.stats[STAT_MAX_HEALTH] ?
					client->ps.stats[STAT_MAX_HEALTH] : next);
			} else if( ent->health < maximum) {
				int next = (int)((unsigned int)ent->health + (unsigned int)extraRate);
				ent->health = (int)(next > maximum ? maximum : next);
			}
		} else {
			// count down health when over max
			if ( ent->health > BG_EffectiveMaxHealth(&client->ps) && ent->health > 1 ) {
				ent->health--;
			}
		}
	}
}

void ClientTimerActions(gentity_t *ent, int msec) {
	G_NITMOD_HealthTimer(ent, msec, G_NITMOD_ConfiguredMedicOptions(), G_NITMOD_ConfiguredWarMode());
}

/*
====================
ClientIntermissionThink
====================
*/
void ClientIntermissionThink( gclient_t *client ) {
	client->ps.eFlags &= ~EF_TALK;
	client->ps.eFlags &= ~EF_FIRING;

	// the level will exit when everyone wants to or after timeouts

	// swap and latch button actions
	client->oldbuttons = client->buttons;
	client->buttons = client->pers.cmd.buttons;

//----(SA)	added
	client->oldwbuttons = client->wbuttons;
	client->wbuttons = client->pers.cmd.wbuttons;
}


/*
================
ClientEvents

Events will be passed on to the clients for presentation,
but any server game effects are handled here
================
*/
/* Original ClientEvents: ordinary shots retain the first 500 ms after spawn;
 * mounted MG42 shots revoke protection immediately. Event IDs are native here. */
/* Original x87 FISTP with truncation returns integer-indefinite outside
 * signed32, including NaN. Avoid target-dependent float-to-int casts. */
static int NITMOD_SpeedInteger(double value) {
	if(!(value >= -2147483648.0 && value < 2147483648.0)) return INT_MIN;
	return (int)value;
}

void G_NITMOD_AttackInvulnerability(gentity_t *ent, int event, int now, int enabled) {
	if(!ent || !ent->client || !enabled) return;
	switch(event) {
	case EV_FIRE_WEAPON:
	case EV_FIRE_WEAPONB:
	case EV_FIRE_WEAPON_LASTSHOT:
		/* Original ClientEvents subtracts in signed 32-bit timer space. */
		if((int)((unsigned int)now - (unsigned int)ent->client->pers.lastSpawnTime) <= 500) return;
		break;
	case EV_FIRE_WEAPON_MG42:
	case EV_FIRE_WEAPON_MOUNTEDMG42:
	case EV_NITMOD_THROW_KNIFE: /* Original event 95 cancels immediately. */
		break;
	default:
		return;
	}
	ent->client->ps.powerups[PW_INVULNERABLE] = 0;
}

void G_NITMOD_FallDamage(gentity_t *ent, int event) {
	gentity_t *target = NULL;
	int damage, stun = 0, slot, flags = g_goombaFlags.integer;
	qboolean sameTeam;
	if(!ent || !ent->client || ent->s.eType != ET_PLAYER) return;
	switch(event) {
	case EV_FALL_SHORT: damage = 0; break;
	case EV_FALL_NDIE: damage = 500; break;
	case EV_FALL_DMG_10: damage = 10; stun = 250; break;
	case EV_FALL_DMG_15: damage = 15; stun = 250; break;
	case EV_FALL_DMG_25: damage = 25; stun = 500; break;
	case EV_FALL_DMG_50: damage = 50; stun = 1000; break;
	default: return;
	}
	/* Original resolves the ground client before consulting g_goomba. */
	slot = ent->s.groundEntityNum;
	if(slot >= 0 && slot < MAX_GENTITIES && g_entities[slot].client) target = &g_entities[slot];
	else {
		trace_t trace;
		vec3_t end;
		VectorCopy(ent->r.currentOrigin, end); end[2] -= 4;
		trap_Trace(&trace, ent->r.currentOrigin, NULL, NULL, end, ent->s.number, MASK_SHOT);
		if(trace.entityNum >= 0 && trace.entityNum < MAX_GENTITIES)
			target = &g_entities[trace.entityNum];
	}
	if(!g_goomba.integer || (target && (!target->client || !target->takedamage))) target = NULL;
	sameTeam = target && target->client->sess.sessionTeam == ent->client->sess.sessionTeam;
	if(event == EV_FALL_SHORT && (!target || (flags & 2) || (sameTeam && (flags & 4)))) return;
	if(target) {
		int amount;
		if(g_gametype.integer != 8 && sameTeam && (flags & 1)) return;
		if(!damage) damage = 5;
		if(stun) { target->client->ps.pm_time = stun; target->client->ps.pm_flags |= PMF_TIME_KNOCKBACK; }
		target->pain_debounce_time = (int)((unsigned int)level.time + 200u);
		/* Original IMUL retains the low 32 bits, including negative results. */
		amount = (flags & 16) ? target->health : (int)((unsigned int)damage * (unsigned int)g_goomba.integer);
		if(ent->health > 0)
			G_Damage(target, ent, ent, NULL, NULL, amount,
				(flags & 16) ? DAMAGE_NITMOD_INSTANT_KILL : 0, MOD_GOOMBA);
		/* Original short falls play sound slot 5 at the stomped client after
		 * applying damage. This uses the existing typed general-sound path. */
		if(damage <= 5) {
			NITMOD_PlaySoundEvent(target, 5);
			return;
		}
		if(flags & 8) return;
		damage = (int)(damage * .2f);
	} else {
		if(stun) { ent->client->ps.pm_time = stun; ent->client->ps.pm_flags |= PMF_TIME_KNOCKBACK; }
		ent->pain_debounce_time = (int)((unsigned int)level.time + 200u);
	}
	G_Damage(ent, NULL, NULL, NULL, NULL, damage, 0, MOD_FALLING);
}

void ClientEvents( gentity_t *ent, int oldEventSequence ) {
	int			i;
	int			event;
	gclient_t	*client;

	client = ent->client;

	if ( oldEventSequence < client->ps.eventSequence - MAX_EVENTS ) {
		oldEventSequence = client->ps.eventSequence - MAX_EVENTS;
	}
	for ( i = oldEventSequence ; i < client->ps.eventSequence ; i++ ) {
		event = NITMOD_LuaEventServerDispatch(client->ps.events[ i & (MAX_EVENTS-1) ]);

		switch ( event ) {
		case EV_FALL_NDIE:
		case EV_FALL_SHORT:
		case EV_FALL_DMG_10:
		case EV_FALL_DMG_15:
		case EV_FALL_DMG_25:
		//case EV_FALL_DMG_30:
		case EV_FALL_DMG_50:
		//case EV_FALL_DMG_75:
		
			G_NITMOD_FallDamage(ent, event);
			client->nitmodPushed = qfalse; /* Original clears after the fall damage/death call. */
			break;

		case EV_FIRE_WEAPON_MG42:
			G_NITMOD_AttackInvulnerability(ent, event, level.time, g_noAttackInvul.integer);

			// Gordon: reset player disguise on stealing docs
			ent->client->ps.powerups[PW_OPS_DISGUISED] = 0;

			mg42_fire( ent );

			// Only 1 stats bin for mg42
#ifndef DEBUG_STATS
			if(g_gamestate.integer == GS_PLAYING)
#endif
				ent->client->sess.aWeaponStats[BG_WeapStatForWeapon(WP_MOBILE_MG42)].atts++;

			break;
		case EV_FIRE_WEAPON_MOUNTEDMG42:
			G_NITMOD_AttackInvulnerability(ent, event, level.time, g_noAttackInvul.integer);
			// Gordon: reset player disguise on stealing docs
			ent->client->ps.powerups[PW_OPS_DISGUISED] = 0;

			mountedmg42_fire( ent );
			// Only 1 stats bin for mg42
#ifndef DEBUG_STATS
			if(g_gamestate.integer == GS_PLAYING)
#endif
				ent->client->sess.aWeaponStats[BG_WeapStatForWeapon(WP_MOBILE_MG42)].atts++;

			break;

		case EV_FIRE_WEAPON_AAGUN:

			// Gordon: reset player disguise on stealing docs
			ent->client->ps.powerups[PW_OPS_DISGUISED] = 0;

			aagun_fire( ent );
			break;

		case EV_FIRE_WEAPON:
		case EV_FIRE_WEAPONB:
		case EV_FIRE_WEAPON_LASTSHOT:
			G_NITMOD_AttackInvulnerability(ent, event, level.time, g_noAttackInvul.integer);
			if(ent->client->ps.powerups[PW_OPS_DISGUISED] && !G_NITMOD_CheckDisguise(ent))
				ent->client->ps.powerups[PW_OPS_DISGUISED] = 0;
			FireWeapon( ent );
			break;
		case EV_NITMOD_THROW_KNIFE:
			G_NITMOD_AttackInvulnerability(ent, event, level.time, g_noAttackInvul.integer);
			G_NITMOD_ThrowKnife(ent);
			break;

		default:
			break;
		}
	}

}

/*
==============
SendPendingPredictableEvents
==============
*/
void SendPendingPredictableEvents( playerState_t *ps ) {
	/*
	gentity_t *t;
	int event, seq;
	int extEvent, number;

	// if there are still events pending
	if ( ps->entityEventSequence < ps->eventSequence ) {
		// create a temporary entity for this event which is sent to everyone
		// except the client generated the event
		seq = ps->entityEventSequence & (MAX_EVENTS-1);
		event = ps->events[ seq ] | ( ( ps->entityEventSequence & 3 ) << 8 );
		// set external event to zero before calling BG_PlayerStateToEntityState
		extEvent = ps->externalEvent;
		ps->externalEvent = 0;
		// create temporary entity for event
		t = G_TempEntity( ps->origin, event );
		number = t->s.number;
		BG_PlayerStateToEntityState( ps, &t->s, qtrue );
		t->s.number = number;
		t->s.eType = ET_EVENTS + event;
		t->s.eFlags |= EF_PLAYER_EVENT;
		t->s.otherEntityNum = ps->clientNum;
		// send to everyone except the client who generated the event
		t->r.svFlags |= SVF_NOTSINGLECLIENT;
		t->r.singleClient = ps->clientNum;
		// set back external event
		ps->externalEvent = extEvent;
	}
	*/
}

// DHM - Nerve
void WolfFindMedic( gentity_t *self ) {
	int i, medic=-1;
	gclient_t	*cl;
	vec3_t	start, end;
	trace_t	tr;
	float	bestdist=1024, dist;

	self->client->ps.viewlocked_entNum = 0;
	self->client->ps.viewlocked = 0;
	/* Original leaves the death yaw intact while updating the medic lock. */

	VectorCopy( self->s.pos.trBase, start );
	start[2] += self->client->ps.viewheight;

	for( i = 0; i < level.numConnectedClients; i++ ) {
		cl = &level.clients[ level.sortedClients[i] ];

		if( level.sortedClients[i] == self->client->ps.clientNum ) {
			continue;
		}

		if( cl->sess.sessionTeam != self->client->sess.sessionTeam ) {
			continue;
		}

		if( cl->ps.pm_type == PM_DEAD ) {
			continue;
		}

		// zinx - limbo'd players are not PM_DEAD or STAT_HEALTH <= 0.
		// and we certainly don't want to lock to them
		// fix for bug #345
		if( cl->ps.pm_flags & PMF_LIMBO ) {
			continue;
		}

		if( cl->ps.stats[ STAT_HEALTH ] <= 0 ) {
			continue;
		}

		if( cl->sess.playerType != PC_MEDIC ) {
			continue;
		}

		VectorCopy( g_entities[level.sortedClients[i]].s.pos.trBase, end );
		end[2] += cl->ps.viewheight;

		trap_Trace (&tr, start, NULL, NULL, end, self->s.number, CONTENTS_SOLID);
		if( tr.fraction < 0.95 ) {
			continue;
		}

		VectorSubtract( end, start, end );
		dist = VectorNormalize( end );

		if ( dist < bestdist ) {
			medic = cl->ps.clientNum;
			bestdist = dist;
		}
	}

	if ( medic >= 0 ) {
		self->client->ps.viewlocked_entNum = medic;
		self->client->ps.viewlocked = 7;
	}
}


//void ClientDamage( gentity_t *clent, int entnum, int enemynum, int id );		// NERVE - SMF

/*
==============
ClientThink

This will be called once for each client frame, which will
usually be a couple times for each server frame on fast clients.

If "g_synchronousClients 1" is set, this will be called exactly
once for each server frame, which makes for smooth demo recording.
==============
*/
void ClientThink_real( gentity_t *ent ) {
	int			msec, oldEventSequence, monsterslick = 0;
	pmove_t		pm;
	usercmd_t	*ucmd;
	gclient_t	*client = ent->client;


	// don't think if the client is not yet connected (and thus not yet spawned in)
	if (client->pers.connected != CON_CONNECTED) {
		return;
	}

	/* Original ClientThink_real 0x4025e..0x40285: unavailable support bits
	 * are refreshed before command timing, including non-Field-Ops clients. */
	{
		int team = client->sess.sessionTeam == TEAM_AXIS ? 0 : 1;
		client->ps.ammo[WP_ARTY] =
			(level.nitmodAirstrikeCounter[team] > 0 ? 1 : 0) |
			(level.nitmodArtilleryCounter[team] > 0 ? 2 : 0);
	}

	if( ent->s.eFlags & EF_MOUNTEDTANK ) {
		client->pmext.centerangles[YAW] = ent->tagParent->r.currentAngles[ YAW ];
		client->pmext.centerangles[PITCH] = ent->tagParent->r.currentAngles[ PITCH ];
	}

/*	if (client->cameraPortal) {
		G_SetOrigin( client->cameraPortal, client->ps.origin );
		trap_LinkEntity(client->cameraPortal);
		VectorCopy( client->cameraOrigin, client->cameraPortal->s.origin2);
	}*/

	// mark the time, so the connection sprite can be removed
	ucmd = &ent->client->pers.cmd;

	ent->client->ps.identifyClient = ucmd->identClient;		// NERVE - SMF

	/* Original ClientThink_real 0x402a5: sample each processed command before
	 * antiwarp/time clamping. The ring and reported ping survive respawn. */
	{
		unsigned int index = client->pers.nitmodPingSampleHead & 63u;
		unsigned int sample = (unsigned int)client->nitmodPingFrameOffset +
			(unsigned int)level.previousTime - (unsigned int)ucmd->serverTime;
		client->pers.nitmodPingSamples[index] = (int)sample;
		client->pers.nitmodPingSampleHead = (index + 1u) & 63u;
		if (G_NITMOD_LegacyCvarInteger("g_truePing", 0)) {
			unsigned int total = 0;
			int i;
			for (i = 0; i < 64; ++i)
				total += (unsigned int)client->pers.nitmodPingSamples[i];
			client->pers.nitmodRealPing = (int)total / 64;
		} else {
			client->pers.nitmodRealPing = client->ps.ping;
		}
		if (client->pers.nitmodRealPing < 0)
			client->pers.nitmodRealPing = 0;
	}

	G_NITMOD_PrepareUsercmd(ent);

	// sanity check the command time to prevent speedup cheating
	if ( ucmd->serverTime > level.time + 200 && !G_NITMOD_DoAntiwarp(ent) ) {
		ucmd->serverTime = level.time + 200;
//		G_Printf("serverTime <<<<<\n" );
	}
	if ( ucmd->serverTime < level.time - 1000 && !G_NITMOD_DoAntiwarp(ent) ) {
		ucmd->serverTime = level.time - 1000;
//		G_Printf("serverTime >>>>>\n" );
	} 

	G_NITMOD_UpdateCensorMute(ent);

	msec = ucmd->serverTime - client->ps.commandTime;
	// following others may result in bad times, but we still want
	// to check for follow toggles
	if ( msec < 1 && client->sess.spectatorState != SPECTATOR_FOLLOW ) {
		return;
	}
	if ( msec > 200 ) {
		msec = 200;
	}

	if ( !G_NITMOD_DoAntiwarp(ent) && (pmove_fixed.integer || client->pers.pmoveFixed) ) {
		ucmd->serverTime = ((ucmd->serverTime + pmove_msec.integer-1) / pmove_msec.integer) * pmove_msec.integer;
	}

	if( client->wantsscore ) {
		G_SendScore( ent );
		client->wantsscore = qfalse;
	}

	//
	// check for exiting intermission
	//
	if ( level.intermissiontime ) {
		ClientIntermissionThink( client );
		return;
	}

	G_NITMOD_CvarScanThink(ent - g_entities);

	// check for inactivity timer, but never drop the local client of a non-dedicated server
	// OSP - moved here to allow for spec inactivity checks as well
	if ( !ClientInactivityTimer( client ) ) {
		return;
	}
	
	if( !(ent->r.svFlags & SVF_BOT) && level.time - client->pers.lastCCPulseTime > 2000 ) {
		G_SendMapEntityInfo( ent );
		client->pers.lastCCPulseTime = level.time;
	}

	if( !(ucmd->flags & 0x01) || ucmd->forwardmove || ucmd->rightmove || ucmd->upmove || ucmd->wbuttons || ucmd->doubleTap ) {
		ent->r.svFlags &= ~(SVF_SELF_PORTAL_EXCLUSIVE|SVF_SELF_PORTAL);
	}

	// spectators don't do much
	// DHM - Nerve :: In limbo use SpectatorThink
	if ( client->sess.sessionTeam == TEAM_SPECTATOR || client->ps.pm_flags & PMF_LIMBO ) {
		/*if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD ) {
			return;
		}*/
		SpectatorThink( ent, ucmd );
		return;
	}

	/* Original ClientThink_real 0x4052b: spectators/limbo retain the deadline;
	 * equality is still visible, zero means no flame-owned broadcast expiry. */
	if(client->nitmodFlameBroadcastUntil && client->nitmodFlameBroadcastUntil < level.time) {
		client->nitmodFlameBroadcastUntil = 0;
		ent->r.svFlags &= ~SVF_BROADCAST;
	}

	/* Original G_CheckClientWeapons revokes adrenaline immediately when its
	 * configured class/unlock eligibility changes. It never grants here; the
	 * spawn/skill paths remain responsible for assignment. */
	G_NITMOD_CheckAdrenaline(ent, client->pers.nitmodDemoClient, G_NITMOD_FirstAidUnlocks(client),
		(unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenClasses", 2));

	if(G_NITMOD_IsViewingCamera(client) || level.match_pause != PAUSE_NONE
#ifdef SAVEGAME_SUPPORT
	  || (g_gametype.integer == GT_SINGLE_PLAYER && saveGamePending && g_reloading.integer && (g_reloading.integer != RELOAD_FAILED))) {
#else
		) {
#endif // SAVEGAME_SUPPORT
		ucmd->buttons = 0;
		ucmd->forwardmove = 0;
		ucmd->rightmove = 0;
		ucmd->upmove = 0;
		ucmd->wbuttons = 0;
		ucmd->doubleTap = 0;

		// freeze player (RELOAD_FAILED still allowed to move/look)
		if(level.match_pause != PAUSE_NONE) {
			client->ps.pm_type = PM_FREEZE;
		} else if(G_NITMOD_IsViewingCamera(client)
#ifdef SAVEGAME_SUPPORT
			|| (g_gametype.integer == GT_SINGLE_PLAYER && g_reloading.integer & (RELOAD_NEXTMAP_WAITING|RELOAD_ENDGAME))) {
#else
			) {
#endif // SAVEGAME_SUPPORT
			VectorClear(client->ps.velocity);
			client->ps.pm_type = PM_FREEZE;
		}
	} else if ( client->noclip ) {
		client->ps.pm_type = PM_NOCLIP;
	} else if ( client->ps.stats[STAT_HEALTH] <= 0 ) {
		client->ps.pm_type = PM_DEAD;
	} else {
		client->ps.pm_type = client->nitmodFrozen ? PM_FREEZE : PM_NORMAL;
	}

	client->ps.aiState = AISTATE_COMBAT;
	client->ps.gravity = g_gravity.value;

	// set speed
	client->ps.speed = NITMOD_SpeedInteger(g_speed.value);

	if( client->speedScale )				// Goalitem speed scale
		client->ps.speed = NITMOD_SpeedInteger(client->ps.speed * (client->speedScale * 0.01));

	// set up for pmove
	oldEventSequence = client->ps.eventSequence;

	client->currentAimSpreadScale = (float)client->ps.aimSpreadScale/255.0;

	memset (&pm, 0, sizeof(pm));

	pm.ps = &client->ps;
	pm.pmext = &client->pmext;
	pm.nitmodDoubleJump = g_doubleJump.integer;
	pm.nitmodLeanEnabled = qtrue;
	pm.nitmodReloadEnabled = qtrue;
	pm.nitmodAuthoritativeWeapons = qtrue;
	pm.nitmodVoiceChat = G_SendVoiceChat;
	pm.nitmodWarMode = G_NITMOD_ConfiguredWarMode();
	pm.nitmodProneDelay = G_NITMOD_LegacyCvarInteger("n_proneDelay", 0);
	pm.nitmodCrouchStandDelay = G_NITMOD_LegacyCvarInteger("n_crouchStandDelay", 0);
	pm.nitmodStandCrouchDelay = G_NITMOD_LegacyCvarInteger("n_standCrouchDelay", 0);
	pm.nitmodNoReload = (unsigned int)G_NITMOD_ConfiguredNoReload();
	pm.nitmodWeaponFlags = G_NITMOD_ConfiguredWeaponFlags();
	pm.nitmodRefreshWeaponOptions = qtrue;
	pm.nitmodFixedPhysics = G_NITMOD_LegacyCvarInteger("g_fixedphysics", 0) != 0;
	pm.nitmodFixedPhysicsFps = G_NITMOD_LegacyCvarInteger("g_fixedphysicsfps", 125);

	pm.nitmodDoubleJumpHeight = g_DJHeight.value;
	pm.nitmodReloadPreferenceFlags = NITMOD_EncodeReloadPreferences(0,
		client->pers.bAutoReloadAux, client->pers.bAltReloadAux);
	pm.character = client->pers.character;
	pm.cmd = *ucmd;
	pm.oldcmd = client->pers.oldcmd;
	// MrE: always use capsule for AI and player
	pm.trace = trap_TraceCapsule;
	if ( pm.ps->pm_type == PM_DEAD ) {
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
		// DHM-Nerve added:: EF_DEAD is checked for in Pmove functions, but wasn't being set
		//              until after Pmove
		pm.ps->eFlags |= EF_DEAD;
		// dhm-Nerve end
	} else if( pm.ps->pm_type == PM_SPECTATOR ) {
		pm.trace = trap_TraceCapsuleNoEnts;
	} else {
		pm.tracemask = MASK_PLAYERSOLID;
	}
	/* Original ClientThink_doPmove 0x3fb90..0x3fc80: run poison after
	 * connection/command/intermission/spectator/limbo gates and PM_DEAD
	 * setup. A paused or dead active body still receives due poison ticks. */
	G_NITMOD_RunPoison(ent);

	//DHM - Nerve :: We've gone back to using normal bbox traces
	//pm.trace = trap_Trace;
	pm.pointcontents = trap_PointContents;
	pm.debugLevel = g_debugMove.integer;
	pm.noFootsteps = qfalse;

	pm.pmove_fixed = pmove_fixed.integer | client->pers.pmoveFixed;
	pm.pmove_msec = pmove_msec.integer;

	pm.noWeapClips = qfalse;

	VectorCopy( client->ps.origin, client->oldOrigin );

	// NERVE - SMF
	pm.gametype = g_gametype.integer;
	/* Original ClientThink_doPmove keeps the real charge threshold even with
	 * g_noCharge. That Cvar suppresses payment after an accepted action. */
	pm.ltChargeTime = level.lieutenantChargeTime[client->sess.sessionTeam-1];
	pm.soldierChargeTime = level.soldierChargeTime[client->sess.sessionTeam-1];
	pm.engineerChargeTime = level.engineerChargeTime[client->sess.sessionTeam-1];
	pm.medicChargeTime = level.medicChargeTime[client->sess.sessionTeam-1];
	// -NERVE - SMF

	pm.skill = client->sess.skill;
	pm.nitmodPackChargeEnabled=qtrue; /* Server rules do not depend on client negotiation. */
	pm.nitmodPackChargeBypass=qfalse;
	memcpy(pm.nitmodPackSkillMasks,client->sess.nitmodSkillMasks,sizeof(pm.nitmodPackSkillMasks));

	client->pmext.airleft = NITMOD_AirRemaining( ent->client->airOutTime, level.time );

	pm.covertopsChargeTime = level.covertopsChargeTime[client->sess.sessionTeam-1];

	if( client->ps.pm_type != PM_DEAD && level.timeCurrent - client->pers.lastBattleSenseBonusTime > 45000 ) {
		/*switch( client->combatState )
		{
		case COMBATSTATE_COLD:	G_AddSkillPoints( ent, SK_BATTLE_SENSE, 0.f ); G_DebugAddSkillPoints( ent, SK_BATTLE_SENSE, 0.f, "combatstate cold" ); break;
		case COMBATSTATE_WARM:	G_AddSkillPoints( ent, SK_BATTLE_SENSE, 2.f ); G_DebugAddSkillPoints( ent, SK_BATTLE_SENSE, 2.f, "combatstate warm" ); break;
		case COMBATSTATE_HOT:	G_AddSkillPoints( ent, SK_BATTLE_SENSE, 5.f ); G_DebugAddSkillPoints( ent, SK_BATTLE_SENSE, 5.f, "combatstate hot" ); break;
		case COMBATSTATE_SUPERHOT:	G_AddSkillPoints( ent, SK_BATTLE_SENSE, 8.f ); G_DebugAddSkillPoints( ent, SK_BATTLE_SENSE, 8.f, "combatstate super-hot" ); break;
		}*/

		if( client->combatState != COMBATSTATE_COLD ) {
			if( client->combatState & (1<<COMBATSTATE_KILLEDPLAYER) && client->combatState & (1<<COMBATSTATE_DAMAGERECEIVED) ) {
				G_AddSkillPoints( ent, SK_BATTLE_SENSE, 8.f ); G_DebugAddSkillPoints( ent, SK_BATTLE_SENSE, 8.f, "combatstate super-hot" );
			} else if( client->combatState & (1<<COMBATSTATE_DAMAGEDEALT) && client->combatState & (1<<COMBATSTATE_DAMAGERECEIVED) ) {
				G_AddSkillPoints( ent, SK_BATTLE_SENSE, 5.f ); G_DebugAddSkillPoints( ent, SK_BATTLE_SENSE, 5.f, "combatstate hot" );
			} else {
				G_AddSkillPoints( ent, SK_BATTLE_SENSE, 2.f ); G_DebugAddSkillPoints( ent, SK_BATTLE_SENSE, 2.f, "combatstate warm" );
			}
		}

		client->pers.lastBattleSenseBonusTime = level.timeCurrent;
		client->combatState = COMBATSTATE_COLD;	// cool down again
	}

	pm.leadership = qfalse;
	/*for ( i = 0 ; i < level.numConnectedClients; i++ ) {
		gclient_t *cl = &level.clients[level.sortedClients[i]];
		vec3_t dist;

		if( cl->sess.sessionTeam != client->sess.sessionTeam ) {
			continue;
		}

		if( cl->sess.skill[SK_SIGNALS] < 5 ) {
			continue;
		}

		if( !trap_InPVS( g_entities[level.sortedClients[i]].r.currentOrigin, ent->r.currentOrigin ) ) {
			continue;
		}

		VectorSubtract( g_entities[level.sortedClients[i]].r.currentOrigin, ent->r.currentOrigin, dist );
		if( VectorLengthSquared( dist ) > SQR(512) )
			continue;

		pm.leadership = qtrue;

        break;        
	}*/

#ifdef SAVEGAME_SUPPORT
	if( g_gametype.integer == GT_SINGLE_PLAYER && g_reloading.integer )
		pm.reloading = qtrue;
#endif // SAVEGAME_SUPPORT

	// Gordon: bit hacky, stop the slight lag from client -> server even on locahost, switching back to the weapon you were holding
	//			and then back to what weapon you should have, became VERY noticible for the kar98/carbine + gpg40, esp now i've added the
	//			animation locking
	if( level.time - client->pers.lastSpawnTime < 1000 ) {
		pm.cmd.weapon = client->ps.weapon;
	}

	monsterslick = Pmove( &pm );

	// Gordon: thx to bani for this
	// ikkyo - fix leaning players bug                                       
	VectorCopy( client->ps.velocity, ent->s.pos.trDelta );                  
	SnapVector( ent->s.pos.trDelta );
	// end

	// server cursor hints
	// TAT 1/10/2003 - bots don't need to check for cursor hints
	if ( !(ent->r.svFlags & SVF_BOT) && ent->lastHintCheckTime < level.time )
	{
		G_CheckForCursorHints(ent);

		ent->lastHintCheckTime = level.time + FRAMETIME;
	}

	// DHM - Nerve :: Set animMovetype to 1 if ducking
	if ( ent->client->ps.pm_flags & PMF_DUCKED )
		ent->s.animMovetype = 1;
	else
		ent->s.animMovetype = 0;

	// save results of pmove
	if ( ent->client->ps.eventSequence != oldEventSequence ) {
		ent->eventTime = level.time;
		ent->r.eventTime = level.time;
	}

	// Ridah, fixes jittery zombie movement
	if (g_smoothClients.integer) {
		BG_PlayerStateToEntityStateExtraPolate( &ent->client->ps, &ent->s, level.time, qfalse );
	} else {
		BG_PlayerStateToEntityState( &ent->client->ps, &ent->s, qfalse );
	}
	G_NITMOD_UpdateAdminGlow(ent);
	BG_NITMOD_CopyLeanState(&ent->client->ps, &ent->s);

	if ( !( ent->client->ps.eFlags & EF_FIRING ) ) {
		client->fireHeld = qfalse;		// for grapple
	}

//
//	// use the precise origin for linking
//	VectorCopy( ent->client->ps.origin, ent->r.currentOrigin );
//
//	// use the snapped origin for linking so it matches client predicted versions
	VectorCopy( ent->s.pos.trBase, ent->r.currentOrigin );

	VectorCopy (pm.mins, ent->r.mins);
	VectorCopy (pm.maxs, ent->r.maxs);
	/* Keep live collision bounds consistent with the recovered historical
	 * trace policy. Attacker-specific prone handling is applied by antilag. */
	ent->r.maxs[2] = G_NITMOD_HitboxHeight( ent, NULL );

	ent->waterlevel = pm.waterlevel;
	ent->watertype = pm.watertype;

	// execute client events
	if(level.match_pause == PAUSE_NONE) {
		ClientEvents( ent, oldEventSequence );
		if(client->ps.groundEntityNum != ENTITYNUM_NONE && !(client->ps.pm_flags & PMF_TIME_LAND))
			client->nitmodPushed = qfalse;
	}

	// link entity now, after any personal teleporters have been used
	trap_LinkEntity (ent);
	if ( !ent->client->noclip ) {
		G_TouchTriggers( ent );
	}

	// NOTE: now copy the exact origin over otherwise clients can be snapped into solid
	VectorCopy( ent->client->ps.origin, ent->r.currentOrigin );

	// touch other objects
	ClientImpacts( ent, &pm );

	// save results of triggers and client events
	if (ent->client->ps.eventSequence != oldEventSequence) {
		ent->eventTime = level.time;
	}

	// swap and latch button actions
	client->oldbuttons = client->buttons;
	client->buttons = ucmd->buttons;
	client->latched_buttons = client->buttons & ~client->oldbuttons;
//	client->latched_buttons |= client->buttons & ~client->oldbuttons;	// FIXME:? (SA) MP method (causes problems for us.  activate 'sticks')

	//----(SA)	added
	client->oldwbuttons = client->wbuttons;
	client->wbuttons = ucmd->wbuttons;
	client->latched_wbuttons = client->wbuttons & ~client->oldwbuttons;
//	client->latched_wbuttons |= client->wbuttons & ~client->oldwbuttons;	// FIXME:? (SA) MP method

	// Rafael - Activate
	// Ridah, made it a latched event (occurs on keydown only)
	if( client->latched_buttons & BUTTON_ACTIVATE ) {
		Cmd_Activate_f( ent );
	}

	if (ent->flags & FL_NOFATIGUE)
		ent->client->pmext.sprintTime = SPRINTTIME;

	G_SetIdentifyClient(ent);

	// check for respawning
	if( client->ps.stats[STAT_HEALTH] <= 0 ) {

		// DHM - Nerve
		WolfFindMedic( ent );

		// See if we need to hop to limbo
		if( level.timeCurrent > client->respawnTime && !(ent->client->ps.pm_flags & PMF_LIMBO) ) {
			if( ucmd->upmove > 0 ) {
				if( g_gametype.integer == GT_WOLF_LMS || client->ps.persistant[PERS_RESPAWNS_LEFT] >= 0 ) {
					trap_SendServerCommand( ent-g_entities, "reqforcespawn" );
				} else {
					limbo( ent, ( client->ps.stats[STAT_HEALTH] > GIB_HEALTH ) );
				}
			}

			if((g_forcerespawn.integer > 0 && level.timeCurrent - client->respawnTime > g_forcerespawn.integer * 1000) || client->ps.stats[STAT_HEALTH] <= GIB_HEALTH) {
				limbo(ent, (client->ps.stats[STAT_HEALTH] > GIB_HEALTH));
			}
		}

		return;
	}

	if( level.gameManager && level.timeCurrent - client->pers.lastHQMineReportTime > 20000 ) {	// NOTE: 60 seconds? bit much innit
		if( level.gameManager->s.modelindex && client->sess.sessionTeam == TEAM_AXIS ) {
			if( G_SweepForLandmines( ent->r.currentOrigin, 256.f, TEAM_AXIS ) ) {
				client->pers.lastHQMineReportTime = level.timeCurrent;
				trap_SendServerCommand(ent-g_entities, "cp \"Mines have been reported in this area.\" 1");
			}
		} else if( level.gameManager->s.modelindex2 && client->sess.sessionTeam == TEAM_ALLIES ) {
			if( G_SweepForLandmines( ent->r.currentOrigin, 256.f, TEAM_ALLIES ) ) {
				client->pers.lastHQMineReportTime = level.timeCurrent;
				trap_SendServerCommand(ent-g_entities, "cp \"Mines have been reported in this area.\" 1");
			}
		}
	}

	G_NITMOD_DrawClientThinkHitboxes(ent);

	// perform once-a-second actions
	if(level.match_pause == PAUSE_NONE) {
		ClientTimerActions( ent, msec );
	}
}

/*
==================
ClientThink

A new command has arrived from the client
==================
*/
void ClientThink( int clientNum ) {
	gentity_t *ent = g_entities + clientNum;
	usercmd_t cmd;
	trap_GetUsercmd(clientNum, &cmd);
	G_NITMOD_NxACUsercmd(clientNum, &cmd);
	ent->client->lastCmdTime = level.time;
	if (G_NITMOD_DoAntiwarp(ent)) {
		G_NITMOD_QueueUsercmd(ent, &cmd);
		G_NITMOD_RunUsercmds(ent);
	} else {
		/* Original ClientThink keeps queued commands/debt across an inactive
		 * antiwarp interval; DoClientThinks reconciles them on re-entry. */
		ent->client->pers.oldcmd = ent->client->pers.cmd;
		ent->client->pers.cmd = cmd;
#ifdef ALLOW_GSYNC
		if (!g_synchronousClients.integer)
#endif
			ClientThink_real(ent);
	}

	// if this is the locally playing client, do bot thinks
#ifndef NO_BOT_SUPPORT
	if( bot_enable.integer && !g_dedicated.integer && clientNum == 0 ) {
		BotAIThinkFrame(ent->client->pers.cmd.serverTime);
		level.lastClientBotThink = level.time;
	}
#endif // NO_BOT_SUPPORT
}


void G_RunClient( gentity_t *ent ) {
	// Gordon: special case for uniform grabbing
	if( ent->client->pers.cmd.buttons & BUTTON_ACTIVATE ) {
		Cmd_Activate2_f( ent );
	}

	if( ent->health <= 0 && ent->client->ps.pm_flags & PMF_LIMBO ) {
		if( ent->r.linked ) {
			trap_UnlinkEntity( ent );
		}
	}

	if (G_NITMOD_DoAntiwarp(ent)) {
		G_NITMOD_RunUsercmds(ent);
		return;
	}

#ifdef ALLOW_GSYNC
	if ( !g_synchronousClients.integer )
#endif // ALLOW_GSYNC
	{
		return;
	}

	ent->client->pers.cmd.serverTime = level.time;
	ClientThink_real( ent );
}

/*
==================
SpectatorClientEndFrame

==================
*/
void SpectatorClientEndFrame( gentity_t *ent )
{
	// OSP - specs periodically get score updates for useful demo playback info
	if(/*ent->client->pers.mvCount > 0 &&*/ ent->client->pers.mvScoreUpdate < level.time) {
		ent->client->pers.mvScoreUpdate = level.time + MV_SCOREUPDATE_INTERVAL;
		ent->client->wantsscore = qtrue;
//		G_SendScore(ent);
	}

	// if we are doing a chase cam or a remote view, grab the latest info
	if((ent->client->sess.spectatorState == SPECTATOR_FOLLOW) || (ent->client->ps.pm_flags & PMF_LIMBO)) {
		int clientNum, testtime;
		gclient_t *cl;
		qboolean do_respawn = qfalse; // JPW NERVE

		/* Original Nitmod bypasses the reinforcement wave once the ordinary
		 * respawn delay expires when g_instantSpawn is enabled. */
		if (g_gamestate.integer == GS_PLAYING &&
			G_NITMOD_LegacyCvarInteger("g_instantSpawn", 0) &&
			ent->client->respawnTime <= level.timeCurrent &&
			ent->client->sess.sessionTeam != TEAM_SPECTATOR) {
			do_respawn = qtrue;
		// Players can respawn quickly in warmup
		} else if(g_gamestate.integer != GS_PLAYING && ent->client->respawnTime <= level.timeCurrent &&
		  ent->client->sess.sessionTeam != TEAM_SPECTATOR) {
			do_respawn = qtrue;
		} else if(ent->client->sess.sessionTeam == TEAM_AXIS) {
			testtime = (level.dwRedReinfOffset + level.timeCurrent - level.startTime) % g_redlimbotime.integer;
			do_respawn = (testtime < ent->client->pers.lastReinforceTime);
			ent->client->pers.lastReinforceTime = testtime;
		}
		else if (ent->client->sess.sessionTeam == TEAM_ALLIES) {
			testtime = (level.dwBlueReinfOffset + level.timeCurrent - level.startTime) % g_bluelimbotime.integer;
			do_respawn = (testtime < ent->client->pers.lastReinforceTime);
			ent->client->pers.lastReinforceTime = testtime;
		}

		if( g_gametype.integer != GT_WOLF_LMS ) {
			if ( ( g_maxlives.integer > 0 || g_alliedmaxlives.integer > 0 || g_axismaxlives.integer > 0 )
				&& ent->client->ps.persistant[PERS_RESPAWNS_LEFT] == 0 ) {
				if( do_respawn ) {
					if( g_maxlivesRespawnPenalty.integer ) {
						if( ent->client->ps.persistant[PERS_RESPAWNS_PENALTY] > 0 ) {
							ent->client->ps.persistant[PERS_RESPAWNS_PENALTY]--;
							do_respawn = qfalse;
						}
					} else {
						do_respawn = qfalse;
					}
				}
			}
		}

		if( g_gametype.integer == GT_WOLF_LMS && g_gamestate.integer == GS_PLAYING ) {
			// Force respawn in LMS when nobody is playing and we aren't at the timelimit yet
			if( !level.teamEliminateTime &&
				level.numTeamClients[0] == level.numFinalDead[0] && level.numTeamClients[1] == level.numFinalDead[1] &&
				ent->client->respawnTime <= level.timeCurrent && ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
				do_respawn = qtrue;
			} else {
				do_respawn = qfalse;
			}
		}

		if ( do_respawn ) {
			reinforce(ent);
			return;
		}

		// Limbos aren't following while in MV
		if((ent->client->ps.pm_flags & PMF_LIMBO) && ent->client->pers.mvCount > 0) {
			return;
		}

		clientNum = ent->client->sess.spectatorClient;

		// team follow1 and team follow2 go to whatever clients are playing
		if ( clientNum == -1 ) {
			clientNum = level.follow1;
		} else if ( clientNum == -2 ) {
			clientNum = level.follow2;
		}

		if ( clientNum >= 0 ) {
			cl = &level.clients[ clientNum ];
			if(cl->pers.connected == CON_CONNECTED && cl->sess.sessionTeam != TEAM_SPECTATOR) {
				int flags = (cl->ps.eFlags & ~(EF_VOTED)) | (ent->client->ps.eFlags & (EF_VOTED));
				int ping = ent->client->ps.ping;

				if(ent->client->sess.sessionTeam != TEAM_SPECTATOR && (ent->client->ps.pm_flags & PMF_LIMBO)) {
					int savedScore = ent->client->ps.persistant[PERS_SCORE];
					int savedRespawns = ent->client->ps.persistant[PERS_RESPAWNS_LEFT];
					int savedRespawnPenalty = ent->client->ps.persistant[PERS_RESPAWNS_PENALTY];
					int savedClass = ent->client->ps.stats[STAT_PLAYER_CLASS];
					int savedMVList = ent->client->ps.powerups[PW_MVCLIENTLIST];

					do_respawn = ent->client->ps.pm_time;

					ent->client->ps = cl->ps;
					ent->client->ps.pm_flags |= PMF_FOLLOW;
					ent->client->ps.pm_flags |= PMF_LIMBO;

					ent->client->ps.pm_time = do_respawn;							// put pm_time back
					ent->client->ps.persistant[PERS_RESPAWNS_LEFT] = savedRespawns;
					ent->client->ps.persistant[PERS_RESPAWNS_PENALTY] = savedRespawnPenalty;
					ent->client->ps.persistant[PERS_SCORE] = savedScore;			// put score back
					ent->client->ps.powerups[PW_MVCLIENTLIST] = savedMVList;
					ent->client->ps.stats[STAT_PLAYER_CLASS] = savedClass;			// NERVE - SMF - put player class back
				} else {
					ent->client->ps = cl->ps;
					ent->client->ps.pm_flags |= PMF_FOLLOW;
				}

				// DHM - Nerve :: carry flags over
				ent->client->ps.eFlags = flags;
				ent->client->ps.ping = ping;

				return;
			} else {
				// drop them to free spectators unless they are dedicated camera followers
				if ( ent->client->sess.spectatorClient >= 0 ) {
					ent->client->sess.spectatorState = SPECTATOR_FREE;
					ClientBegin( ent->client - level.clients );
				}
			}
		}
	}

	/*if ( ent->client->sess.spectatorState == SPECTATOR_SCOREBOARD ) {
		ent->client->ps.pm_flags |= PMF_SCOREBOARD;
	} else {
		ent->client->ps.pm_flags &= ~PMF_SCOREBOARD;
	}*/

	// we are at a free-floating spec state for a player,
	// set speclock status, as appropriate
	//	 --> Can we use something besides a powerup slot?
	if(ent->client->pers.mvCount < 1) {
		ent->client->ps.powerups[PW_BLACKOUT] = (G_blockoutTeam(ent, TEAM_AXIS) * TEAM_AXIS) |
												(G_blockoutTeam(ent, TEAM_ALLIES) * TEAM_ALLIES);
	}
}


// DHM - Nerve :: After reviving a player, their contents stay CONTENTS_CORPSE until it is determined
//					to be safe to return them to PLAYERSOLID

qboolean StuckInClient( gentity_t *self ) {
	int i;
	vec3_t	hitmin, hitmax;
	vec3_t	selfmin, selfmax;
	gentity_t *hit;

	for(i=0; i<level.numConnectedClients; i++) {
		hit = g_entities + level.sortedClients[i];

		if(!hit->inuse || hit == self || !hit->client ||
		  !hit->s.solid || hit->health <= 0) {
			continue;
		}

		VectorAdd(hit->r.currentOrigin, hit->r.mins, hitmin);
		VectorAdd(hit->r.currentOrigin, hit->r.maxs, hitmax);
		VectorAdd(self->r.currentOrigin, self->r.mins, selfmin);
		VectorAdd(self->r.currentOrigin, self->r.maxs, selfmax);

		if(hitmin[0] > selfmax[0]) continue;
		if(hitmax[0] < selfmin[0]) continue;
		if(hitmin[1] > selfmax[1]) continue;
		if(hitmax[1] < selfmin[1]) continue;
		if(hitmin[2] > selfmax[2]) continue;
		if(hitmax[2] < selfmin[2]) continue;

		return(qtrue);
	}

	return(qfalse);
}

extern vec3_t	playerMins, playerMaxs;
#define WR_PUSHAMOUNT 25

void WolfRevivePushEnt( gentity_t *self, gentity_t *other ) {
	vec3_t	dir, push;

	VectorSubtract( self->r.currentOrigin, other->r.currentOrigin, dir );
	dir[2] = 0;
	VectorNormalizeFast( dir );

	VectorScale( dir, WR_PUSHAMOUNT, push );

	if ( self->client ) {
		VectorAdd( self->s.pos.trDelta, push, self->s.pos.trDelta );
		VectorAdd( self->client->ps.velocity, push, self->client->ps.velocity );
	}

	VectorScale( dir, -WR_PUSHAMOUNT, push );
	push[2] = WR_PUSHAMOUNT/2;

	VectorAdd( other->s.pos.trDelta, push, other->s.pos.trDelta );
	VectorAdd( other->client->ps.velocity, push, other->client->ps.velocity );
}

// Arnout: completely revived for capsules
void WolfReviveBbox( gentity_t *self ) {
	int			touch[MAX_GENTITIES];
	int			num,i, touchnum=0;
	gentity_t	*hit = NULL; // TTimo: init
	vec3_t		mins, maxs;

	hit = G_TestEntityPosition( self );

	if( hit && ( hit->s.number == ENTITYNUM_WORLD || ( hit->client && (hit->client->ps.persistant[PERS_HWEAPON_USE] || (hit->client->ps.eFlags & EF_MOUNTEDTANK))) ) ) {
		G_DPrintf( "WolfReviveBbox: Player stuck in world or MG42 using player\n" );
		// Move corpse directly to the person who revived them
		if ( self->props_frame_state >= 0 ) {
//			trap_UnlinkEntity( self );
			VectorCopy( g_entities[self->props_frame_state].client->ps.origin, self->client->ps.origin );
			VectorCopy( self->client->ps.origin, self->r.currentOrigin );
			trap_LinkEntity( self );

			// Reset value so we don't continue to warp them
			self->props_frame_state = -1;
		}
		return;
	}

	VectorAdd( self->r.currentOrigin, playerMins, mins );
	VectorAdd( self->r.currentOrigin, playerMaxs, maxs );

	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	for (i=0 ; i<num ; i++) {
		hit = &g_entities[touch[i]];

		// Always use capsule for player
		if ( !trap_EntityContactCapsule( mins, maxs, hit ) ) {
		//if ( !trap_EntityContact( mins, maxs, hit ) ) {
			continue;
		}

		if ( hit->client && hit->health > 0 ) {
			if ( hit->s.number != self->s.number ) {
				WolfRevivePushEnt( hit, self );
				touchnum++;
			}
		} else if ( hit->r.contents & ( CONTENTS_SOLID | CONTENTS_BODY | CONTENTS_PLAYERCLIP ) ) {
			WolfRevivePushEnt( hit, self );
			touchnum++;
		}
	}

	G_DPrintf( "WolfReviveBbox: Touchnum: %d\n", touchnum );

	if ( touchnum == 0 ) {
		G_DPrintf( "WolfReviveBbox:  Player is solid now!\n" );
		self->r.contents = CONTENTS_BODY;
	}
}

/*
==============
ClientEndFrame

Called at the end of each server frame for each connected client
A fast client will have multiple ClientThink for each ClientEndFrame,
while a slow client may have multiple ClientEndFrame between ClientThink.
==============
*/
void ClientEndFrame( gentity_t *ent ) {
	int			i;

	/* Original Nitmod applies the configured rate once per elapsed minute. */
	if((G_NITMOD_LegacyCvarInteger("g_XPDecay", 0) & 1) &&
		level.time % 60000 == 0) {
		G_NITMOD_XPDecay(ent, 60, qfalse);
	}

	/* Original ClientEndFrame drains one pending command per frame after the
	 * last flood wait plus 999 ms; the 30-second window does not clear count. */
	if(NITMOD_SupportSignedTime((uint32_t)ent->client->pers.nitmodFloodNextTime + UINT32_C(999)) < level.time &&
		ent->client->pers.nitmodFloodCount != 0) {
		ent->client->pers.nitmodFloodCount = NITMOD_SupportSignedTime((uint32_t)ent->client->pers.nitmodFloodCount - UINT32_C(1));
		if(!ent->client->pers.nitmodFloodCount)
			ent->client->pers.nitmodFloodWindowTime = 0;
	}

	// used for informing of speclocked teams.
	// Zero out here and set only for certain specs
	ent->client->ps.powerups[PW_BLACKOUT] = ent->client->nitmodBlinded ? NITMOD_BLACKOUT_ADMIN : 0;

	if (( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) || (ent->client->ps.pm_flags & PMF_LIMBO)) { // JPW NERVE
		SpectatorClientEndFrame( ent );
		if(ent->client->nitmodBlinded) ent->client->ps.powerups[PW_BLACKOUT] |= NITMOD_BLACKOUT_ADMIN;
		return;
	}

	/* Original contacts live in persistant[1/2]. Native ET owns those indices,
	 * so use the two spare snapshot slots without changing playerState ABI. */
	ent->client->ps.persistant[PERS_NITMOD_HEAD_HITS] = ent->client->nitmodLuaPersistant[1];
	ent->client->ps.persistant[PERS_NITMOD_BODY_HITS] = ent->client->nitmodLuaPersistant[2];

		// turn off any expired powerups
		// OSP -- range changed for MV
		for ( i = 0 ; i < PW_NUM_POWERUPS ; i++ ) {

			/* Original 0x42673/0x42689 excludes wire slots 4 and 7..10.
			 * BLACKOUT is maintained separately for the native admin adapter. */
			if( i == PW_BLACKOUT || i == PW_NOFATIGUE ||
				ent->client->ps.powerups[i] == 0 ||
				i == PW_OPS_CLASS_1 || i == PW_OPS_CLASS_2 ||
				i == PW_OPS_CLASS_3 || i == PW_OPS_DISGUISED ) {

				continue;
			}
			// OSP -- If we're paused, update powerup timers accordingly.
			// Make sure we dont let stuff like CTF flags expire.
			if(level.match_pause != PAUSE_NONE &&
			  ent->client->ps.powerups[i] != INT_MAX) {
				/* Original ClientEndFrame ADD wraps the timer in 32 bits. */
				ent->client->ps.powerups[i] = (int)((unsigned int)ent->client->ps.powerups[i]
					+ (unsigned int)level.time - (unsigned int)level.previousTime);
			}


			if ( ent->client->ps.powerups[ i ] < level.time ) {
				ent->client->ps.powerups[ i ] = 0;
			}
		}

		{
			int totalXP = NITMOD_TotalSkillXP(ent->client->sess.skillpoints);
			NITMOD_SetSnapshotXP(&ent->client->ps, totalXP);
		}

		/* Original 0x42843..0x428a2 shifts these nine integer clocks only.
		 * SUB/ADD wrap in 32 bits, including the air deadline. */
		if(level.match_pause != PAUSE_NONE) {
			uint32_t time_delta = (uint32_t)level.time - (uint32_t)level.previousTime;
			ent->client->airOutTime = NITMOD_SupportSignedTime((uint32_t)ent->client->airOutTime + time_delta);
			ent->client->inactivityTime = NITMOD_SupportSignedTime((uint32_t)ent->client->inactivityTime + time_delta);
			ent->client->lastBurnTime = NITMOD_SupportSignedTime((uint32_t)ent->client->lastBurnTime + time_delta);
			ent->client->pers.connectTime = NITMOD_SupportSignedTime((uint32_t)ent->client->pers.connectTime + time_delta);
			ent->client->pers.enterTime = NITMOD_SupportSignedTime((uint32_t)ent->client->pers.enterTime + time_delta);
			ent->client->ps.classWeaponTime = NITMOD_SupportSignedTime((uint32_t)ent->client->ps.classWeaponTime + time_delta);
			ent->lastHintCheckTime = NITMOD_SupportSignedTime((uint32_t)ent->lastHintCheckTime + time_delta);
			ent->pain_debounce_time = NITMOD_SupportSignedTime((uint32_t)ent->pain_debounce_time + time_delta);
			ent->s.onFireEnd = NITMOD_SupportSignedTime((uint32_t)ent->s.onFireEnd + time_delta);
		}

	// save network bandwidth
#if 0
	if ( !g_synchronousClients->integer && ent->client->ps.pm_type == PM_NORMAL ) {
		// FIXME: this must change eventually for non-sync demo recording
		VectorClear( ent->client->ps.viewangles );
	}
#endif

	//
	// If the end of unit layout is displayed, don't give
	// the player any normal movement attributes
	//
	if ( level.intermissiontime ) {
		return;
	}

	// burn from lava, etc
	P_WorldEffects (ent);
	/* Original ClientEndFrame: apply the roll offset after world effects. */
	{
	gclient_t *client=ent->client;
	if(client->nitmodDisoriented) {
		if(client->ps.pm_type==PM_DEAD && !(client->ps.eFlags&EF_SPARE0)) return;
		client->ps.delta_angles[ROLL]=32000;
		client->ps.viewangles[ROLL]=0;
		client->nitmodDisorientApplied=qtrue;
	} else if(client->nitmodDisorientApplied) {
		client->ps.delta_angles[ROLL]=0;
		client->nitmodDisorientApplied=qfalse;
	}
	}

	/* Original ClientEndFrame 0x42928..0x42993 goes directly from
	 * disorientation to snapshot state; no legacy P_DamageFeedback pass. */

	// add the EF_CONNECTION flag if we haven't gotten commands recently
	if ( level.time - ent->client->lastCmdTime > 1000 ) {
		ent->s.eFlags |= EF_CONNECTION;
	} else {
		ent->s.eFlags &= ~EF_CONNECTION;
	}

	ent->client->ps.stats[STAT_HEALTH] = ent->health;	// FIXME: get rid of ent->health...
														// Gordon: WHY? other ents use it.

	G_SetClientSound (ent);

	// set the latest infor

	// Ridah, fixes jittery zombie movement
	if (g_smoothClients.integer) {
		BG_PlayerStateToEntityStateExtraPolate( &ent->client->ps, &ent->s, level.time, qfalse );
	} else {
		BG_PlayerStateToEntityState( &ent->client->ps, &ent->s, qfalse );
	}
	G_NITMOD_UpdateAdminGlow(ent);
	BG_NITMOD_CopyLeanState(&ent->client->ps, &ent->s);

	//SendPendingPredictableEvents( &ent->client->ps );

	// DHM - Nerve :: If it's been a couple frames since being revived, and props_frame_state
	//					wasn't reset, go ahead and reset it
	if ( ent->props_frame_state >= 0 && ( (level.time - ent->s.effect3Time) > 100 ) )
		ent->props_frame_state = -1;

	if ( ent->health > 0 && StuckInClient( ent ) ) {
		G_DPrintf( "%s is stuck in a client.\n", ent->client->pers.netname );
		ent->r.contents = CONTENTS_CORPSE;
	}

	if ( ent->health > 0 && ent->r.contents == CONTENTS_CORPSE && !(ent->s.eFlags & (EF_MOUNTEDTANK | EF_SPARE0))) {
		WolfReviveBbox( ent );
	}

	// DHM - Nerve :: Reset 'count2' for flamethrower
	if ( !(ent->client->buttons & BUTTON_ATTACK) )
		ent->count2 = 0;
	// dhm

	// zinx - #280 - run touch functions here too, so movers don't have to wait
	// until the next ClientThink, which will be too late for some map
	// scripts (railgun)
	G_TouchTriggers( ent );

	// run entity scripting
	G_Script_ScriptRun( ent );

	G_NITMOD_SkipCorrection(ent);

	// store the client's current position for antilag traces
	G_NITMOD_MDXUpdate(ent);
	G_NITMOD_DrawClientEndHitboxes(ent);
	G_StoreClientPosition( ent );
}
