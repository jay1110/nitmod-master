#include "g_nitmod_lua.h"
#include "g_local.h"
#include "nitmod_support_time.h"
#include "g_nitmod_db_lifecycle.h"
#include "g_nitmod_server_cvars.h"
#include "g_nitmod_nxac.h"
#include "g_nitmod_nxac_transfer.h"
#include "g_nitmod_mdx.h"
static void ClientSpawnContext(gentity_t *ent,qboolean revived,qboolean teamChange,qboolean restoreHealth);
#include "g_nitmod_etbot_lifecycle.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_restrictions.h"
#include "g_nitmod_integrity.h"
#include "g_nitmod_abilities.h"
#include "nitmod_powerup_ids.h"
#include "nitmod_protocol.h"
#include "nitmod_secondary_weapon.h"
#include "nitmod_class_primaries.h"
#include <limits.h>

void NITMOD_SetSpawnProtection(gclient_t *client, qboolean revived) {
	unsigned int duration;
	if(!client || client->sess.sessionTeam == TEAM_SPECTATOR) return;
	/* Original ClientSpawn uses 32-bit IMUL/ADD, including timer wrap. */
	duration = revived ? (g_fastres.integer == 1 ? 1000u : 3000u)
		: (unsigned int)g_spawnInvul.integer * 1000u;
	client->ps.powerups[PW_INVULNERABLE] = (int)((unsigned int)level.time + duration);
}
#include "g_nitmod_teamcount.h"
#include "nitmod_air.h"
#include "g_nitmod_config.h"
#include "nitmod_weapon_reload.h"
#include "../../pak/ui/menudef.h"

// g_client.c -- client functions that don't happen every frame

// Ridah, new bounding box
//static vec3_t	playerMins = {-15, -15, -24};
//static vec3_t	playerMaxs = {15, 15, 32};
vec3_t	playerMins = {-18, -18, -24};
vec3_t	playerMaxs = {18, 18, 48};
// done.

/*QUAKED info_player_deathmatch (1 0 1) (-18 -18 -24) (18 18 48)
potential spawning position for deathmatch games.
Targets will be fired when someone spawns in on them.
"nobots" will prevent bots from using this spot.
"nohumans" will prevent non-bots from using this spot.
If the start position is targeting an entity, the players camera will start out facing that ent (like an info_notnull)
*/
void SP_info_player_deathmatch( gentity_t *ent ) {
	vec3_t	dir;

	ent->enemy = G_PickTarget( ent->target );
	if(ent->enemy)
	{
		VectorSubtract( ent->enemy->s.origin, ent->s.origin, dir );
		vectoangles( dir, ent->s.angles );
	}

}

//----(SA) added
/*QUAKED info_player_checkpoint (1 0 0) (-16 -16 -24) (16 16 32) a b c d
these are start points /after/ the level start
the letter (a b c d) designates the checkpoint that needs to be complete in order to use this start position
*/
void SP_info_player_checkpoint(gentity_t *ent) {
	ent->classname = "info_player_checkpoint";
	SP_info_player_deathmatch( ent );
}

//----(SA) end


/*QUAKED info_player_start (1 0 0) (-18 -18 -24) (18 18 48)
equivelant to info_player_deathmatch
*/
void SP_info_player_start(gentity_t *ent) {
	ent->classname = "info_player_deathmatch";
	SP_info_player_deathmatch( ent );
}

/*QUAKED info_player_intermission (1 0 1) (-16 -16 -24) (16 16 32) AXIS ALLIED
The intermission will be viewed from this point.  Target an info_notnull for the view direction.
*/
void SP_info_player_intermission( gentity_t *ent ) {

}

extern void BotSpeedBonus(int clientNum);


/*
=======================================================================

  SelectSpawnPoint

=======================================================================
*/

/*
================
SpotWouldTelefrag

================
*/
static gentity_t *nitmodSpawnEntities[MAX_GENTITIES];
static int nitmodSpawnCount;
gentity_t *G_NITMOD_NextSpawnEntity(int *cursor, int hash) {
 while(*cursor < nitmodSpawnCount) {
  gentity_t *ent=nitmodSpawnEntities[(*cursor)++];
  if(ent->nitmodClassnameHash==hash) return ent;
 }
 return NULL;
}
void G_NITMOD_ResetSpawnEntities(void) { nitmodSpawnCount = 0; }
static qboolean IsSpawnHash(int h) {
 return h==0x3eee0 || h==0x3b699 || h==0x3ec15 || h==0x49240 || h==0x527df || h==0x42729 || h==0x37c98;
}
void G_NITMOD_RegisterSpawnEntity(gentity_t *ent) {
 int i; if(!IsSpawnHash(ent->nitmodClassnameHash)) return;
 for(i=0;i<nitmodSpawnCount;i++) if(nitmodSpawnEntities[i]==ent) return;
 if(nitmodSpawnCount==MAX_GENTITIES) { G_Error("Spawn entity array full"); return; }
 nitmodSpawnEntities[nitmodSpawnCount++]=ent;
}
void G_NITMOD_UnregisterSpawnEntity(gentity_t *ent) {
 int i; if(!IsSpawnHash(ent->nitmodClassnameHash)) return;
 for(i=0;i<nitmodSpawnCount;i++) if(nitmodSpawnEntities[i]==ent) {
  memmove(&nitmodSpawnEntities[i],&nitmodSpawnEntities[i+1],(nitmodSpawnCount-i-1)*sizeof(nitmodSpawnEntities[0]));
  --nitmodSpawnCount;return;
 }
}

qboolean SpotWouldTelefrag( gentity_t *spot ) {
	int			i, num;
	int			touch[MAX_GENTITIES];
	gentity_t	*hit;
	vec3_t		mins, maxs;

	VectorAdd( spot->r.currentOrigin, playerMins, mins );
	VectorAdd( spot->r.currentOrigin, playerMaxs, maxs );
	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	for (i=0 ; i<num ; i++) {
		hit = &g_entities[touch[i]];
		if ( hit->client && hit->client->ps.stats[STAT_HEALTH] > 0 ) {
			return qtrue;
		}

	}

	return qfalse;
}

/*
================
SelectNearestDeathmatchSpawnPoint

Find the spot that we DON'T want to use
================
*/
#define	MAX_SPAWN_POINTS	128
gentity_t *SelectNearestDeathmatchSpawnPoint( vec3_t from ) {
	gentity_t	*spot;
 int spawnIndex;
	vec3_t		delta;
	float		dist, nearestDist;
	gentity_t	*nearestSpot;

	nearestDist = 999999;
	nearestSpot = NULL;
	spot = NULL;

	for(spawnIndex=0;spawnIndex<nitmodSpawnCount;spawnIndex++) {
  spot=nitmodSpawnEntities[spawnIndex];
  if(spot->nitmodClassnameHash!=0x49240) continue;

		VectorSubtract( spot->r.currentOrigin, from, delta );
		dist = VectorLength( delta );
		if ( dist < nearestDist ) {
			nearestDist = dist;
			nearestSpot = spot;
		}
	}

	return nearestSpot;
}


/*
================
SelectRandomDeathmatchSpawnPoint

go to a random point that doesn't telefrag
================
*/
#define	MAX_SPAWN_POINTS	128
gentity_t *SelectRandomDeathmatchSpawnPoint( void ) {
	gentity_t	*spot;
 int spawnIndex;
	int			count;
	int			selection;
	gentity_t	*spots[MAX_GENTITIES];

	count = 0;
	spot = NULL;

	for(spawnIndex=0;spawnIndex<nitmodSpawnCount;spawnIndex++) {
  spot=nitmodSpawnEntities[spawnIndex];
  if(spot->nitmodClassnameHash!=0x49240) continue;
		if ( SpotWouldTelefrag( spot ) ) {
			continue;
		}
		spots[ count ] = spot;
		count++;
	}

	if ( !count ) {	// no spots that won't telefrag
		for(spawnIndex=0;spawnIndex<nitmodSpawnCount;spawnIndex++)
   if(nitmodSpawnEntities[spawnIndex]->nitmodClassnameHash==0x49240) return nitmodSpawnEntities[spawnIndex];
  return NULL;
	}

	selection = rand() % count;
	return spots[ selection ];
}


/*
===========
SelectSpawnPoint

Chooses a player start, deathmatch start, etc
============
*/
gentity_t *SelectSpawnPoint ( vec3_t avoidPoint, vec3_t origin, vec3_t angles ) {
	gentity_t	*spot;
	gentity_t	*nearestSpot;

	nearestSpot = SelectNearestDeathmatchSpawnPoint( avoidPoint );

	spot = SelectRandomDeathmatchSpawnPoint ( );
	if ( spot == nearestSpot ) {
		// roll again if it would be real close to point of death
		spot = SelectRandomDeathmatchSpawnPoint ( );
		if ( spot == nearestSpot ) { 
			// last try
			spot = SelectRandomDeathmatchSpawnPoint ( );
		}		
	}

	// find a single player start spot
	if (!spot) {
		G_Error( "Couldn't find a spawn point" );
	}

	VectorCopy (spot->r.currentOrigin, origin);
	origin[2] += 9;
	VectorCopy (spot->s.angles, angles);

	return spot;
}

/*
===========
SelectInitialSpawnPoint

Try to find a spawn point marked 'initial', otherwise
use normal spawn selection.
============
*/
/*gentity_t *SelectInitialSpawnPoint( vec3_t origin, vec3_t angles ) {
	gentity_t	*spot;

	spot = NULL;
	while ((spot = G_Find (spot, FOFS(classname), "info_player_deathmatch")) != NULL) {
		if ( spot->spawnflags & 1 ) {
			break;
		}
	}

	if ( !spot || SpotWouldTelefrag( spot ) ) {
		return SelectSpawnPoint( vec3_origin, origin, angles );
	}

	VectorCopy (spot->r.currentOrigin, origin);
	origin[2] += 9;
	VectorCopy (spot->s.angles, angles);

	return spot;
}*/

/*
===========
SelectSpectatorSpawnPoint

============
*/
gentity_t *SelectSpectatorSpawnPoint( vec3_t origin, vec3_t angles ) {
	FindIntermissionPoint();

	VectorCopy( level.intermission_origin, origin );
	VectorCopy( level.intermission_angle, angles );

	return NULL;
}

/*
=======================================================================

BODYQUE

=======================================================================
*/

/*
===============
InitBodyQue
===============
*/
void InitBodyQue (void) {
	int		i;
	gentity_t	*ent;

	level.bodyQueIndex = 0;
	for (i=0; i<BODY_QUEUE_SIZE ; i++) {
		ent = G_Spawn();
		ent->classname = "bodyque";
		ent->neverFree = qtrue;
		level.bodyQue[i] = ent;
	}
}

/*
=============
BodyUnlink
  
Called by BodySink
=============
*/
void BodyUnlink( gentity_t *ent ) {
	/* Original BodyUnlink 0x47690: invalidate the client's corpse cache
	 * before hiding this reusable body entity. */
	gentity_t *event = G_NITMOD_TempEventOriginal(ent->r.currentOrigin, 94);
	event->s.otherEntityNum = ent->s.number;
	event->r.svFlags = SVF_BROADCAST;
	trap_UnlinkEntity( ent );
	ent->physicsObject = qfalse;
}
                
/*
=============
BodySink

After sitting around for five seconds, fall into the ground and dissapear 
=============
*/ 
void BodySink2( gentity_t *ent ) {
	ent->physicsObject = qfalse;
    /* Original BodySink2 0x4910e: sink for exactly 1800 ms. */
    ent->nextthink = NITMOD_SupportSignedTime((uint32_t)level.time + UINT32_C(1800));
    ent->think = BodyUnlink;
    ent->s.pos.trType = TR_LINEAR;
    ent->s.pos.trTime = level.time;
    VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
	VectorSet( ent->s.pos.trDelta, 0, 0, -8 );
}

/*
=============
BodySink

After sitting around for five seconds, fall into the ground and dissapear
=============
*/
void BodySink( gentity_t *ent ) {
	if( ent->activator ) {
		// see if parent is still disguised
		if( ent->activator->client->ps.powerups[PW_OPS_DISGUISED] ) {
			ent->nextthink = level.time + 100;
			return;
		} else {
			ent->activator = NULL;
		}
	}

	BodySink2( ent );
}


/*
=============
CopyToBodyQue

A player is respawning, so make an entity that looks
just like the existing corpse to leave behind.
=============
*/
void CopyToBodyQue( gentity_t *ent ) {
	gentity_t		*body;
	int			contents, i;

	trap_UnlinkEntity (ent);

	// if client is in a nodrop area, don't leave the body
  	contents = trap_PointContents( ent->client->ps.origin, -1 );
	if ( contents & CONTENTS_NODROP ) {
		return;
	}

	// grab a body que and cycle to the next one
	body = level.bodyQue[ level.bodyQueIndex ];
	level.bodyQueIndex = (level.bodyQueIndex + 1) % BODY_QUEUE_SIZE;

	// Gordon: um, what on earth was this here for?
//	trap_UnlinkEntity (body);

	body->s = ent->s;
	G_NITMOD_MDXCopy(body, ent);
	body->s.eFlags = EF_DEAD;		// clear EF_TALK, etc

	if( ent->client->ps.eFlags & EF_HEADSHOT ) {
		body->s.eFlags |= EF_HEADSHOT;			// make sure the dead body draws no head (if killed that way)
	}

	body->s.eType = ET_CORPSE;
	body->classname = "corpse";
	body->s.powerups = 0;	// clear powerups
	body->s.loopSound = 0;	// clear lava burning
	body->s.number = body - g_entities;
	body->timestamp = level.time;
	body->nitmodItemSlide = qfalse;
	body->nitmodItemAlign = qfalse;
	body->physicsObject = qtrue;
	body->physicsBounce = 0;		// don't bounce
	if ( body->s.groundEntityNum == ENTITYNUM_NONE ) {
		body->s.pos.trType = TR_GRAVITY;
		body->s.pos.trTime = level.time;
		VectorCopy( ent->client->ps.velocity, body->s.pos.trDelta );
	} else {
		body->s.pos.trType = TR_STATIONARY;
	}
	body->s.event = 0;

	// DHM - Clear out event system
	for( i=0; i<MAX_EVENTS; i++ )
		body->s.events[i] = 0;
	body->s.eventSequence = 0;

	/* Original CopyToBodyQue preserves the selected death animation and
	 * its absolute end time, so late snapshots resume the correct frame. */
	body->s.torsoAnim = body->s.legsAnim = ent->client->legsDeathAnim;
	body->s.effect1Time = ent->client->nitmodDeathAnimEndTime;
	if(body->s.onFireEnd > level.time)
		body->s.onFireEnd = (int)((unsigned int)body->s.effect1Time + 1500u);

	body->r.svFlags = ent->r.svFlags & ~SVF_BOT;
	VectorCopy (ent->r.mins, body->r.mins);
	VectorCopy (ent->r.maxs, body->r.maxs);
	VectorCopy (ent->r.absmin, body->r.absmin);
	VectorCopy (ent->r.absmax, body->r.absmax);
	
	// ydnar: bodies have lower bounding box
	body->r.maxs[ 2 ] = 0;

	body->clipmask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP;
	// DHM - Nerve :: allow bullets to pass through bbox
	// Gordon: need something to allow the hint for covert ops
	body->r.contents = CONTENTS_CORPSE;
	body->r.ownerNum = ent->r.ownerNum;

	BODY_TEAM(body) =		ent->client->sess.sessionTeam;
	BODY_CLASS(body) =		ent->client->sess.playerType;
	BODY_CHARACTER(body) =	ent->client->pers.characterIndex;
	BODY_VALUE(body) =		0;

	body->s.time2 &= NITMOD_ES_GLOW;

	body->activator = NULL;

	/* Original CopyToBodyQue 0x49461, independent of team/game type. */
	body->nextthink = level.time + 20000;

	body->think = BodySink;

	body->die = body_die;

	// don't take more damage if already gibbed
	/* Original CopyToBodyQue 0x49491 retains damage at the boundary. */
	if ( ent->health < GIB_HEALTH ) {
		body->takedamage = qfalse;
	} else {
		body->takedamage = qtrue;
	}


	VectorCopy ( body->s.pos.trBase, body->r.currentOrigin );
	G_NITMOD_MDXUpdate(body);
	trap_LinkEntity (body);
}

//======================================================================


/*
==================
SetClientViewAngle

==================
*/
void SetClientViewAngle( gentity_t *ent, vec3_t angle ) {
	int			i;

	// set the delta angle
	for (i=0 ; i<3 ; i++) {
		int		cmdAngle;

		cmdAngle = ANGLE2SHORT(angle[i]);
		ent->client->ps.delta_angles[i] = cmdAngle - ent->client->pers.cmd.angles[i];
	}
	VectorCopy( angle, ent->s.angles );
	VectorCopy (ent->s.angles, ent->client->ps.viewangles);
}

void SetClientViewAnglePitch( gentity_t *ent, vec_t angle ) {
	int	cmdAngle;

	cmdAngle = ANGLE2SHORT(angle);
	ent->client->ps.delta_angles[PITCH] = cmdAngle - ent->client->pers.cmd.angles[PITCH];

	ent->s.angles[ PITCH ] = 0;
	VectorCopy( ent->s.angles, ent->client->ps.viewangles);
}

/* JPW NERVE
================
limbo
================
*/
void limbo( gentity_t *ent, qboolean makeCorpse ) 
{
	int i,contents;
	//int startclient = ent->client->sess.spectatorClient;
	int startclient = ent->client->ps.clientNum;

	if (!(ent->client->ps.pm_flags & PMF_LIMBO)) {

		if( ent->client->ps.persistant[PERS_RESPAWNS_LEFT] == 0 ) {
			if( g_maxlivesRespawnPenalty.integer ) {
				ent->client->ps.persistant[PERS_RESPAWNS_PENALTY] = g_maxlivesRespawnPenalty.integer;
			} else {
				ent->client->ps.persistant[PERS_RESPAWNS_PENALTY] = -1;
			}
		}

		// DHM - Nerve :: First save off persistant info we'll need for respawn
		for( i = 0; i < MAX_PERSISTANT; i++) {
			ent->client->saved_persistant[i] = ent->client->ps.persistant[i];
		}

		ent->client->ps.pm_flags |= PMF_LIMBO;
		ent->client->ps.pm_flags |= PMF_FOLLOW;

		
		if( makeCorpse ) {
			NITMOD_DropLimboPacks(ent);
			CopyToBodyQue (ent); // make a nice looking corpse
		} else {
			trap_UnlinkEntity (ent);
		}

		// DHM - Nerve :: reset these values
		ent->client->ps.viewlocked = 0;
		ent->client->ps.viewlocked_entNum = 0;

		ent->r.maxs[2] = 0;
		ent->r.currentOrigin[2] += 8;
		contents = trap_PointContents( ent->r.currentOrigin, -1 ); // drop stuff
		ent->s.weapon = ent->client->limboDropWeapon; // stored in player_die()
		if ( makeCorpse && !( contents & CONTENTS_NODROP ) ) {
			TossClientItems( ent );
		}

		ent->client->sess.spectatorClient = startclient;
		Cmd_FollowCycle_f(ent,1); // get fresh spectatorClient

		if (ent->client->sess.spectatorClient == startclient) {
			// No one to follow, so just stay put
			ent->client->sess.spectatorState = SPECTATOR_FREE;
		}
		else
			ent->client->sess.spectatorState = SPECTATOR_FOLLOW;

//		ClientUserinfoChanged( ent->client - level.clients );		// NERVE - SMF - don't do this
		if (ent->client->sess.sessionTeam == TEAM_AXIS) {
			ent->client->deployQueueNumber = level.redNumWaiting;
			level.redNumWaiting++;
		}
		else if (ent->client->sess.sessionTeam == TEAM_ALLIES) {
			ent->client->deployQueueNumber = level.blueNumWaiting;
			level.blueNumWaiting++;
		}

		for(i=0; i<level.numConnectedClients; i++) {
			gclient_t *cl = &level.clients[level.sortedClients[i]];
			if(((cl->ps.pm_flags & PMF_LIMBO) ||
			  (cl->sess.sessionTeam == TEAM_SPECTATOR && cl->sess.spectatorState == SPECTATOR_FOLLOW)) &&
			  cl->sess.spectatorClient == ent - g_entities) {//ent->s.number ) {
				Cmd_FollowCycle_f( &g_entities[level.sortedClients[i]], 1 );
			}
		}
	}
}

/* JPW NERVE
================
reinforce 
================
// -- called when time expires for a team deployment cycle and there is at least one guy ready to go
*/
void reinforce(gentity_t *ent) {
	int p;
	gclient_t *rclient;

	/* Original reinforce 0x4e2a0: only limbo gates deployment; bot userinfo
	 * and multiview must not bypass or alter the reinforcement path. */
	if (!(ent->client->ps.pm_flags & PMF_LIMBO)) {
		G_Printf("player already deployed, skipping\n");
		return;
	}

	// DHM - Nerve :: restore persistant data now that we're out of Limbo
	rclient = ent->client;
	for (p=0; p<MAX_PERSISTANT; p++)
		rclient->ps.persistant[p] = rclient->saved_persistant[p];
	// dhm

	respawn(ent);
}
// jpw


/*
================
respawn
================
*/
void respawn( gentity_t *ent ) {

#ifdef SAVEGAME_SUPPORT
	if( g_gametype.integer == GT_SINGLE_PLAYER ) {
		if (g_reloading.integer || saveGamePending) {
			return;
		}
	}
#endif // SAVEGAME_SUPPORT

	ent->client->ps.pm_flags &= ~PMF_LIMBO; // JPW NERVE turns off limbo

	// DHM - Nerve :: Decrease the number of respawns left
	if( g_gametype.integer != GT_WOLF_LMS ) {
		if( ent->client->ps.persistant[PERS_RESPAWNS_LEFT] > 0 && g_gamestate.integer == GS_PLAYING ) {
			if( g_maxlives.integer > 0 ) {
				ent->client->ps.persistant[PERS_RESPAWNS_LEFT]--;
			} else {
				if( g_alliedmaxlives.integer > 0 && ent->client->sess.sessionTeam == TEAM_ALLIES ) {
					ent->client->ps.persistant[PERS_RESPAWNS_LEFT]--;
				}
				if( g_axismaxlives.integer > 0 && ent->client->sess.sessionTeam == TEAM_AXIS ) {
					ent->client->ps.persistant[PERS_RESPAWNS_LEFT]--;
				}
			}
		}
	}

	G_DPrintf( "Respawning %s, %i lives left\n", ent->client->pers.netname, ent->client->ps.persistant[PERS_RESPAWNS_LEFT]);

	ClientSpawn(ent, qfalse);

	// DHM - Nerve :: Add back if we decide to have a spawn effect
	// add a teleportation effect
	//tent = G_TempEntity( ent->client->ps.origin, EV_PLAYER_TELEPORT_IN );
	//tent->s.clientNum = ent->s.clientNum;
}

// NERVE - SMF - merge from team arena
/*
================
TeamCount

Returns number of players on a team
================
*/
team_t TeamCount(int ignoreClientNum, int team)
{
	int i, ref, count = 0;

	for(i=0; i<level.numConnectedClients; i++) {
		if((ref = level.sortedClients[i]) == ignoreClientNum) continue;
		if(level.clients[ref].sess.sessionTeam == team) count++;
	}

	return(count);
}
// -NERVE - SMF

/*
================
PickTeam

================
*/
team_t PickTeam(int ignoreClientNum)
{
	int counts[TEAM_NUM_TEAMS] = { 0, 0, 0 };

	counts[TEAM_ALLIES] = TeamCount(ignoreClientNum, TEAM_ALLIES);
	counts[TEAM_AXIS] = TeamCount(ignoreClientNum, TEAM_AXIS);

	if(counts[TEAM_ALLIES] > counts[TEAM_AXIS]) return(TEAM_AXIS);
	if(counts[TEAM_AXIS] > counts[TEAM_ALLIES]) return(TEAM_ALLIES);

	// equal team count, so join the team with the lowest score
	return(((level.teamScores[TEAM_ALLIES] > level.teamScores[TEAM_AXIS]) ? TEAM_AXIS : TEAM_ALLIES));
}

/*
===========
AddExtraSpawnAmmo
===========
*/
static void AddExtraSpawnAmmo( gclient_t *client, weapon_t weaponNum)
{
	/* Original AddExtraSpawnAmmo: war modes 1..4 suppress reward ammo. */
	if ((unsigned int)G_NITMOD_ConfiguredWarMode() - 1u < 4u) return;
	switch( weaponNum ) {
		//case WP_KNIFE:
		case WP_LUGER:
		case WP_COLT:
		case WP_STEN:
		case WP_SILENCER:
		case WP_CARBINE:
		case WP_KAR98:
		case WP_SILENCED_COLT:
			if( (client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] & 2u) )
				client->ps.ammo[BG_FindAmmoForWeapon(weaponNum)] += GetAmmoTableData(weaponNum)->maxclip;
			break;
		case WP_MP40:
		case WP_THOMPSON:
			if( ((client->sess.nitmodSkillMasks[SK_FIRST_AID] & 2u) && client->sess.playerType == PC_MEDIC) || (client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] & 2u) ) {
				client->ps.ammo[BG_FindAmmoForWeapon(weaponNum)] += GetAmmoTableData(weaponNum)->maxclip;
			}
			break;
		case WP_M7:
		case WP_GPG40:
			if( (client->sess.nitmodSkillMasks[SK_EXPLOSIVES_AND_CONSTRUCTION] & 2u) )
				client->ps.ammo[BG_FindAmmoForWeapon(weaponNum)] += 4;
			break;
		case WP_GRENADE_PINEAPPLE:
		case WP_GRENADE_LAUNCHER:
			if( client->sess.playerType == PC_ENGINEER ) {
				if( (client->sess.nitmodSkillMasks[SK_EXPLOSIVES_AND_CONSTRUCTION] & 2u) ) {
					client->ps.ammoclip[BG_FindAmmoForWeapon(weaponNum)] += 4;
				}
			}
			if( client->sess.playerType == PC_MEDIC ) {
				if( (client->sess.nitmodSkillMasks[SK_FIRST_AID] & 2u) ) {
					client->ps.ammoclip[BG_FindAmmoForWeapon(weaponNum)] += 1;
				}
			}
			break;
		/*case WP_MOBILE_MG42:
		case WP_PANZERFAUST:
		case WP_FLAMETHROWER:
			if( client->sess.skill[SK_HEAVY_WEAPONS] >= 1 )
				client->ps.ammo[BG_FindAmmoForWeapon(weaponNum)] += GetAmmoTableData(weaponNum)->maxclip;
			break;
		case WP_MORTAR:
		case WP_MORTAR_SET:
			if( client->sess.skill[SK_HEAVY_WEAPONS] >= 1 )
				client->ps.ammo[BG_FindAmmoForWeapon(weaponNum)] += 2;
			break;*/
		case WP_MEDIC_SYRINGE:
		case WP_MEDIC_ADRENALINE:
			if( (client->sess.nitmodSkillMasks[SK_FIRST_AID] & 4u) )
 				client->ps.ammoclip[BG_FindAmmoForWeapon(weaponNum)] += 2;
			break;
		case WP_GARAND:
		case WP_K43:
		case WP_FG42:
			if( (client->sess.nitmodSkillMasks[SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS] & 2u) || (client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] & 2u) )
				client->ps.ammo[BG_FindAmmoForWeapon(weaponNum)] += GetAmmoTableData(weaponNum)->maxclip;
			break;
		case WP_GARAND_SCOPE:
		case WP_K43_SCOPE:
		case WP_FG42SCOPE:
			if( (client->sess.nitmodSkillMasks[SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS] & 2u) || (client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] & 2u) )
				client->ps.ammo[BG_FindAmmoForWeapon(weaponNum)] += GetAmmoTableData(weaponNum)->maxclip;
			break;
		default:
			break;
	}
}

qboolean AddWeaponToPlayer( gclient_t *client, weapon_t weapon, int ammo, int ammoclip, qboolean setcurrent ) {
	COM_BitSet( client->ps.weapons, weapon );
	client->ps.ammoclip[BG_FindClipForWeapon(weapon)] = ammoclip;
	client->ps.ammo[BG_FindAmmoForWeapon(weapon)] = ammo;
	if( setcurrent )
		client->ps.weapon = weapon;

	// skill handling
	AddExtraSpawnAmmo( client, weapon );
	Bot_Event_AddWeapon(client->ps.clientNum, Bot_WeaponGameToBot(weapon));

	return qtrue;
}

/* Preserve the already selected primary: original grants secondary before
 * primary, whereas the ET 2.60 adapter grants them in the opposite order. */
static qboolean G_NITMOD_GrantSelectedSecondary(gclient_t *client, int dualSMG,
    unsigned int medicOptions) {
    weapon_t weapon = NITMOD_CorrectSecondaryWeapon(client->sess.playerWeapon2,
        client->sess.sessionTeam, client->sess.skill[SK_LIGHT_WEAPONS],
        client->sess.skill[SK_HEAVY_WEAPONS], client->sess.playerType,
        dualSMG, medicOptions);
    const ammotable_t *table;
    int alternate;
    if(weapon == WP_NONE)
        weapon = NITMOD_DefaultSecondaryWeapon(client->sess.sessionTeam,
            client->sess.playerType, client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS],
            client->sess.nitmodSkillMasks[SK_HEAVY_WEAPONS], client->pers.clientFlags);
    table = GetAmmoTableData(weapon);
    if(BG_IsAkimboWeapon(weapon))
        client->ps.ammoclip[BG_FindClipForWeapon(BG_AkimboSidearm(weapon))] = table->defaultStartingClip;
    /* If the corrected secondary is already the primary, its later original
     * primary grant wins. Do not overwrite that class-specific ammo here. */
    if(weapon != client->ps.weapon)
        AddWeaponToPlayer(client, weapon, table->defaultStartingAmmo, table->defaultStartingClip, qfalse);
    alternate = client->sess.playerType == PC_COVERTOPS ? weapAlts[weapon] : WP_NONE;
    if(alternate != WP_NONE) {
        table = GetAmmoTableData(alternate);
        AddWeaponToPlayer(client, alternate, table->defaultStartingAmmo, table->defaultStartingClip, qfalse);
    }
    return qtrue;
}

void BotSetPOW(int entityNum, qboolean isPOW);

static int G_NITMOD_ClassChargeTime(const gclient_t *client) {
	int team;

	if(!client || client->sess.sessionTeam < TEAM_AXIS ||
		client->sess.sessionTeam > TEAM_ALLIES) return 0;
	team = client->sess.sessionTeam - TEAM_AXIS;
	switch(client->sess.playerType) {
	case PC_MEDIC: return level.medicChargeTime[team];
	case PC_ENGINEER: return level.engineerChargeTime[team];
	case PC_FIELDOPS: return level.lieutenantChargeTime[team];
	case PC_COVERTOPS: return level.covertopsChargeTime[team];
	case PC_SOLDIER:
	default: return level.soldierChargeTime[team];
	}
}

static void G_NITMOD_ApplySlashKillCharge(gclient_t *client) {
	int options;

	if(!client || !client->nitmodSlashKillPending) return;
	options = G_NITMOD_LegacyCvarInteger("g_slashKill", 0);
	if(options & 1) {
		/* Original x87 truncates only after subtraction, including odd times. */
		client->ps.classWeaponTime = (int)((double)level.time - (double)G_NITMOD_ClassChargeTime(client) * 0.5);
	} else if(options & 2) {
		client->ps.classWeaponTime = level.time;
	} else if(options & 4) {
		client->ps.classWeaponTime = client->nitmodSlashKillChargeTime +
			(level.time - client->nitmodSlashKillDeathTime);
	}
	client->nitmodSlashKillPending = qfalse;
}

/* Original SetWolfSpawnWeapons branch at qagame 0x0005c5c7.  The recovered
 * binary uses the old wire weapon numbers here; keep those out of the live
 * code and express the loadout with the typed ET weapon enum instead. */
static qboolean G_NITMOD_GrantWarLoadout(gclient_t *client) {
	const unsigned int options =
		(unsigned int)G_NITMOD_LegacyCvarInteger("n_sniperWarOptions", 7);
	const int warMode = G_NITMOD_ConfiguredWarMode();
	weapon_t rifle;
	weapon_t scopedRifle;

	if(!client || warMode < 1 || warMode > 4) return qfalse;

	/* The knife was installed by the common prefix.  Mode 4 intentionally
	 * adds nothing else. */
	if(warMode == 4) return qtrue;

	/* Original modes 1 and 3 also carry the otherwise surprising empty K43
	 * scope slot. Preserve it by typed identity; it shares ammunition with
	 * the base K43 and therefore must precede the real mode loadout. */
	if(warMode == 1 || warMode == 3)
		AddWeaponToPlayer(client, WP_K43_SCOPE, 0, 0, qfalse);

	if(warMode == 1) {
		AddWeaponToPlayer(client, WP_PANZERFAUST, 1, 0, qtrue);
		return qtrue;
	}

	if(warMode == 3) {
		weapon_t rifleGrenade;

		if(client->sess.sessionTeam == TEAM_AXIS) {
			rifle = WP_KAR98;
			rifleGrenade = WP_GPG40;
		} else {
			rifle = WP_CARBINE;
			rifleGrenade = WP_M7;
		}
		AddWeaponToPlayer(client, rifle, 500, 10, qtrue);
		AddWeaponToPlayer(client, rifleGrenade, 500,
			GetAmmoTableData(rifleGrenade)->defaultStartingClip, qfalse);
		client->sess.rifleGrenadeStatus = 1;
		return qtrue;
	}

	if(options & 1u) {
		AddWeaponToPlayer(client, WP_BINOCULARS, 1, 0, qfalse);
		client->ps.stats[STAT_KEYS] |= (1 << INV_BINOCS);
	}

	/* Bit 4 grants the Axis scoped rifle independently of team.  This looks
	 * unusual, but is an explicit operation in the original before its
	 * team-specific rifle pair is installed. */
	if(options & 4u)
		AddWeaponToPlayer(client, WP_K43_SCOPE, 0, 0, qfalse);

	if(client->sess.sessionTeam == TEAM_AXIS) {
		rifle = WP_K43;
		scopedRifle = WP_K43_SCOPE;
	} else {
		rifle = WP_GARAND;
		scopedRifle = WP_GARAND_SCOPE;
	}

	/* Nitmod deliberately gives effectively unlimited war-mode reserve ammo,
	 * rather than applying the ordinary class/skill spawn-ammo calculation. */
	AddWeaponToPlayer(client, rifle, 500, 10, qtrue);
	AddWeaponToPlayer(client, scopedRifle, 500, 10, qfalse);
	return qtrue;
}

/*
===========
SetWolfSpawnWeapons
===========
*/
/* Original nitmod_AddNewWeapon (0x10d4f0): separate DM/ordinary masks,
 * configured starting ammunition, and no current-weapon change. */
static qboolean G_NITMOD_AddSpecialClassTool(gclient_t *client, weapon_t weapon) {
	unsigned int normalBit, dmBit, options;
	const ammotable_t *ammo;
	switch(weapon) {
	case WP_TRIPMINE: normalBit = 0x8000u; dmBit = 0x800u; break;
	case WP_POISON_MINE: normalBit = 0x4000u; dmBit = 0x200u; break;
	case WP_POISON_BOMB: normalBit = 0x2000u; dmBit = 0x400u; break;
	default: return qfalse;
	}
	options = g_gametype.integer == GT_WOLF_DM ?
		(unsigned int)g_DMOptions.integer :
		(unsigned int)G_NITMOD_ConfiguredWeaponFlags();
	if(!(options & (g_gametype.integer == GT_WOLF_DM ? dmBit : normalBit))) return qfalse;
	ammo = GetAmmoTableData(weapon);
	return AddWeaponToPlayer(client, weapon, ammo->defaultStartingAmmo,
		ammo->defaultStartingClip, qfalse);
}

/* Original G_AddClassSpecificTools.part.3 0x47db0 and wrapper0x49f60.
 * Class stealing needs this tool-only grant: no health, primary ammunition,
 * charge timestamp or respawn-latch reset. Existing spawn primitives retain
 * custom starting ammo, reward bonuses and bot notifications. */
void G_NITMOD_AddClassSpecificTools(gclient_t *client) {
	int pc, war;
	unsigned int dmOptions, skills;
	qboolean deathmatch, binoculars;
	if(!client || client->sess.sessionTeam < TEAM_AXIS || client->sess.sessionTeam > TEAM_ALLIES) return;
	war = G_NITMOD_ConfiguredWarMode();
	if((unsigned int)war - 1u < 4u) return;
	pc = client->sess.playerType;
	deathmatch = g_gametype.integer == GT_WOLF_DM;
	dmOptions = (unsigned int)g_DMOptions.integer;
	skills = client->sess.nitmodSkillMasks[SK_EXPLOSIVES_AND_CONSTRUCTION];
	binoculars = (client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] & 2u) != 0;
	G_NITMOD_GrantAdrenalineSpawn(client, G_NITMOD_FirstAidUnlocks(client),
		(unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenClasses", 2),
		(unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenaline", 0),
		war, GetAmmoTableData(WP_MEDIC_ADRENALINE));
#define CLASS_TOOL(w) AddWeaponToPlayer(client, (w), GetAmmoTableData(w)->defaultStartingAmmo, GetAmmoTableData(w)->defaultStartingClip, qfalse)
	switch(pc) {
	case PC_ENGINEER:
		if(!deathmatch) AddWeaponToPlayer(client, WP_DYNAMITE, 0, 1, qfalse);
		if(!deathmatch || (dmOptions & 0xb00u)) AddWeaponToPlayer(client, WP_PLIERS, 0, 1, qfalse);
		if(!deathmatch || (dmOptions & 0x100u)) CLASS_TOOL(WP_LANDMINE);
		if((skills & 32u) && (G_NITMOD_ConfiguredWeaponFlags() & 4) &&
		   (!deathmatch || (dmOptions & 0x2000u))) CLASS_TOOL(WP_BOMB);
		G_NITMOD_AddSpecialClassTool(client, WP_TRIPMINE);
		G_NITMOD_AddSpecialClassTool(client, WP_POISON_MINE);
		break;
	case PC_MEDIC:
		if(!deathmatch) { CLASS_TOOL(WP_MEDIC_SYRINGE); CLASS_TOOL(WP_MEDKIT); }
		break;
	case PC_FIELDOPS:
		if(!(G_NITMOD_LegacyCvarInteger("g_fieldOps", 0) & 1) ||
		   (client->sess.nitmodSkillMasks[SK_SIGNALS] & 2u)) binoculars = qtrue;
		if(!deathmatch) {
			AddWeaponToPlayer(client, WP_AMMO, 0, 1, qfalse);
			CLASS_TOOL(WP_SMOKE_MARKER);
		}
		break;
	case PC_COVERTOPS:
		if(!deathmatch) CLASS_TOOL(WP_SMOKE_BOMB);
		G_NITMOD_AddSpecialClassTool(client, WP_POISON_BOMB);
		if(!deathmatch || (dmOptions & 0x1000u)) {
			qboolean planted = G_FindSatchel(&g_entities[client->ps.clientNum]) != NULL;
			AddWeaponToPlayer(client, WP_SATCHEL, 0, planted ? 0 : 1, qfalse);
			AddWeaponToPlayer(client, WP_SATCHEL_DET, 0, planted ? 1 : 0, qfalse);
		}
		binoculars = qtrue;
		break;
	default: break;
	}
	if(binoculars) {
		AddWeaponToPlayer(client, WP_BINOCULARS, 1, 0, qfalse);
		client->ps.stats[STAT_KEYS] |= 1 << INV_BINOCS;
	}
	if(!deathmatch && (skills & 16u) &&
	   (pc == PC_ENGINEER || (G_NITMOD_LegacyCvarInteger("g_skills", 0) & 1)))
		client->ps.powerups[NITMOD_PW_FLAK] = INT_MAX;
	if(g_poison.integer && (client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] & 16u))
		CLASS_TOOL(WP_POISON_SYRINGE);
#undef CLASS_TOOL
}

void SetWolfSpawnWeapons( gclient_t *client )
{
	int		pc = client->sess.playerType;
	weapon_t primaryWeapon = client->sess.playerWeapon;
	unsigned int medicOptions = 0;
	/* Original G_AddClassSpecificTools: DM gates apply to class tools only. */
	const qboolean deathmatch = g_gametype.integer == GT_WOLF_DM;
	const unsigned int dmOptions = (unsigned int)g_DMOptions.integer;
	qboolean	isBot = (g_entities[client->ps.clientNum].r.svFlags & SVF_BOT) ? qtrue : qfalse;
	qboolean	isPOW = (g_entities[client->ps.clientNum].r.svFlags & SVF_POW) ? qtrue : qfalse;

	client->sess.rifleGrenadeStatus = 0;

	if ( client->sess.sessionTeam == TEAM_SPECTATOR )
		return;
	Bot_Event_ResetWeapons(client->ps.clientNum);
	if(pc == PC_MEDIC) G_NITMOD_ReadMedicOptions(&medicOptions);

	// Reset special weapon time
	client->ps.classWeaponTime = -999999;
	G_NITMOD_ApplySlashKillCharge(client);

	// Communicate it to cgame
	client->ps.stats[STAT_PLAYER_CLASS] = pc;

	// Abuse teamNum to store player class as well (can't see stats for all clients in cgame)
	client->ps.teamNum = pc;

	// JPW NERVE -- zero out all ammo counts
	memset(client->ps.ammo, 0, MAX_WEAPONS * sizeof(int));

	// All players start with a knife (not OR-ing so that it clears previous weapons)
	client->ps.weapons[0] = 0;
	client->ps.weapons[1] = 0;

	// Gordon: set up pow status
	if( isBot ) {
		if( isPOW ) {
			BotSetPOW( client->ps.clientNum, qtrue );
			return;
		} else {
			BotSetPOW( client->ps.clientNum, qfalse );
		}
	}

	/* Original SetWolfSpawnWeapons: Light Weapons reward bit32 selects
	 * the configured starting clip; otherwise exactly one knife. */
	AddWeaponToPlayer( client, WP_KNIFE, 0,
		(client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] & 32u) ?
		GetAmmoTableData(WP_KNIFE)->defaultStartingClip : 1, qtrue );

	client->ps.weaponstate = WEAPON_READY;

	/* War modes replace the normal class loadout in the original game. */
	if(G_NITMOD_GrantWarLoadout(client)) return;

	/* Original validates the class/team list before the silent restriction
	 * check. The fallback is granted without rechecking or changing latches. */
	if(g_knifeonly.integer != 1 &&
		(!NITMOD_ClassHasPrimary(client->sess.sessionTeam, pc, primaryWeapon) ||
		 G_IsWeaponDisabled(&g_entities[client->ps.clientNum], primaryWeapon)))
		primaryWeapon = NITMOD_ClassPrimaryAt(client->sess.sessionTeam, pc, 0);

	// Engineer gets dynamite
	if ( pc == PC_ENGINEER ) {
		if (!deathmatch)
			AddWeaponToPlayer( client, WP_DYNAMITE, 0, 1, qfalse );
		if (!deathmatch || (dmOptions & 0xb00u))
			AddWeaponToPlayer( client, WP_PLIERS, 0, 1, qfalse );

		if( g_knifeonly.integer != 1 ) {
			if( client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] & 2u ) {
				if( AddWeaponToPlayer( client, WP_BINOCULARS, 1, 0, qfalse ) ) {
					client->ps.stats[STAT_KEYS] |= ( 1 << INV_BINOCS );
				}
			}

			if (client->sess.sessionTeam == TEAM_AXIS) {
				switch( primaryWeapon ) {
				case WP_KAR98:
					if( AddWeaponToPlayer( client, WP_KAR98, GetAmmoTableData(WP_KAR98)->defaultStartingAmmo, GetAmmoTableData(WP_KAR98)->defaultStartingClip, qtrue ) ) {
						if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_GPG40)) {
							client->sess.rifleGrenadeStatus = AddWeaponToPlayer( client, WP_GPG40, GetAmmoTableData(WP_GPG40)->defaultStartingAmmo, GetAmmoTableData(WP_GPG40)->defaultStartingClip, qfalse ) ? 1 : 0;
						}
					}
					break;
				default:
					AddWeaponToPlayer( client, primaryWeapon, GetAmmoTableData(primaryWeapon)->defaultStartingAmmo, GetAmmoTableData(primaryWeapon)->defaultStartingClip, qtrue );
					break;
				}
				if (!deathmatch || (dmOptions & 0x100u))
					AddWeaponToPlayer( client, WP_LANDMINE, GetAmmoTableData(WP_LANDMINE)->defaultStartingAmmo, GetAmmoTableData(WP_LANDMINE)->defaultStartingClip, qfalse );
				AddWeaponToPlayer( client, WP_GRENADE_LAUNCHER, 0, 4, qfalse );

			} else {
				switch( primaryWeapon ) {
				case WP_CARBINE:
					if( AddWeaponToPlayer( client, WP_CARBINE, GetAmmoTableData(WP_CARBINE)->defaultStartingAmmo, GetAmmoTableData(WP_CARBINE)->defaultStartingClip, qtrue ) ) {
						if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_M7)) {
							client->sess.rifleGrenadeStatus = AddWeaponToPlayer( client, WP_M7, GetAmmoTableData(WP_M7)->defaultStartingAmmo, GetAmmoTableData(WP_M7)->defaultStartingClip, qfalse ) ? 1 : 0;
						}
					}
					break;
				default:
					AddWeaponToPlayer( client, primaryWeapon, GetAmmoTableData(primaryWeapon)->defaultStartingAmmo, GetAmmoTableData(primaryWeapon)->defaultStartingClip, qtrue );
					break;
				}
				if (!deathmatch || (dmOptions & 0x100u))
					AddWeaponToPlayer( client, WP_LANDMINE, GetAmmoTableData(WP_LANDMINE)->defaultStartingAmmo, GetAmmoTableData(WP_LANDMINE)->defaultStartingClip, qfalse );
				AddWeaponToPlayer( client, WP_GRENADE_PINEAPPLE, 0, 4, qfalse );
			}
		}
	}

	if ( g_knifeonly.integer != 1 ) {
		// Field ops gets binoculars, ammo pack, artillery, and a grenade
		if ( pc == PC_FIELDOPS ) {
			unsigned int fieldOpsOptions =
				(unsigned int)G_NITMOD_LegacyCvarInteger("g_fieldOps", 0);
			qboolean grantBinoculars = qtrue;

			if (!deathmatch)
				AddWeaponToPlayer( client, WP_AMMO, 0, 1, qfalse );

			/* Original bit 1 removes the unconditional loadout grant.  Either
			 * Battle Sense or Signals' first unlock restores it. */
			if( fieldOpsOptions & 1u ) {
				grantBinoculars =
					(client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] & 2u) ||
					(client->sess.nitmodSkillMasks[SK_SIGNALS] & 2u);
			}

			if( grantBinoculars &&
				AddWeaponToPlayer( client, WP_BINOCULARS, 1, 0, qfalse ) ) {
				client->ps.stats[STAT_KEYS] |= ( 1 << INV_BINOCS );
			}

			if (!deathmatch)
				AddWeaponToPlayer( client, WP_SMOKE_MARKER, GetAmmoTableData(WP_SMOKE_MARKER)->defaultStartingAmmo, GetAmmoTableData(WP_SMOKE_MARKER)->defaultStartingClip, qfalse );

			if( client->sess.sessionTeam == TEAM_AXIS ) {
				AddWeaponToPlayer( client, primaryWeapon,  GetAmmoTableData(primaryWeapon)->defaultStartingAmmo, GetAmmoTableData(primaryWeapon)->defaultStartingClip, qtrue );
				AddWeaponToPlayer( client, WP_GRENADE_LAUNCHER,  0, 1, qfalse );
			} else {
				AddWeaponToPlayer( client, primaryWeapon, GetAmmoTableData(primaryWeapon)->defaultStartingAmmo, GetAmmoTableData(primaryWeapon)->defaultStartingClip, qtrue );
				AddWeaponToPlayer( client, WP_GRENADE_PINEAPPLE, 0, 1, qfalse );
			}
		} else if( pc == PC_MEDIC ) {
			if( client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] & 2u ) {
				if( AddWeaponToPlayer( client, WP_BINOCULARS, 1, 0, qfalse ) ) {
					client->ps.stats[STAT_KEYS] |= ( 1 << INV_BINOCS );
				}
			}

			if (!deathmatch)
				AddWeaponToPlayer( client, WP_MEDIC_SYRINGE, GetAmmoTableData(WP_MEDIC_SYRINGE)->defaultStartingAmmo, GetAmmoTableData(WP_MEDIC_SYRINGE)->defaultStartingClip, qfalse );
			if (!deathmatch)
				AddWeaponToPlayer( client, WP_MEDKIT, GetAmmoTableData(WP_MEDKIT)->defaultStartingAmmo, GetAmmoTableData(WP_MEDKIT)->defaultStartingClip, qfalse );

			if (client->sess.sessionTeam == TEAM_AXIS) {
				if(!(medicOptions & 4u))
					AddWeaponToPlayer( client, primaryWeapon, 0, GetAmmoTableData(primaryWeapon)->defaultStartingClip, qtrue );
				AddWeaponToPlayer( client, WP_GRENADE_LAUNCHER, 0, 1, qfalse );
			} else {
				if(!(medicOptions & 4u))
					AddWeaponToPlayer( client, primaryWeapon, 0, GetAmmoTableData(primaryWeapon)->defaultStartingClip, qtrue );
				AddWeaponToPlayer( client, WP_GRENADE_PINEAPPLE, 0, 1, qfalse );
			}
		} else if ( pc == PC_SOLDIER ) {
			if( client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] & 2u ) {
				if( AddWeaponToPlayer( client, WP_BINOCULARS, 1, 0, qfalse ) ) {
					client->ps.stats[STAT_KEYS] |= ( 1 << INV_BINOCS );
				}
			}

			switch( client->sess.sessionTeam ) {
				case TEAM_AXIS:
					switch( primaryWeapon ) {
					default:
					case WP_MP40:
						AddWeaponToPlayer( client, WP_MP40, GetAmmoTableData(WP_MP40)->defaultStartingAmmo, GetAmmoTableData(WP_MP40)->defaultStartingClip, qtrue );
						break;
					case WP_PANZERFAUST:
						AddWeaponToPlayer( client, WP_PANZERFAUST, GetAmmoTableData(WP_PANZERFAUST)->defaultStartingAmmo, GetAmmoTableData(WP_PANZERFAUST)->defaultStartingClip, qtrue );
						break;
					case WP_FLAMETHROWER:
						AddWeaponToPlayer( client, WP_FLAMETHROWER, GetAmmoTableData(WP_FLAMETHROWER)->defaultStartingAmmo, GetAmmoTableData(WP_FLAMETHROWER)->defaultStartingClip, qtrue );
						break;
					case WP_MOBILE_MG42:
						if( AddWeaponToPlayer( client, WP_MOBILE_MG42, GetAmmoTableData(WP_MOBILE_MG42)->defaultStartingAmmo, GetAmmoTableData(WP_MOBILE_MG42)->defaultStartingClip, qtrue ) ) {
							if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_MOBILE_MG42_SET))
								AddWeaponToPlayer( client, WP_MOBILE_MG42_SET, GetAmmoTableData(WP_MOBILE_MG42_SET)->defaultStartingAmmo, GetAmmoTableData(WP_MOBILE_MG42_SET)->defaultStartingClip, qfalse );
						}
						break;
					case WP_MORTAR:
						if( AddWeaponToPlayer( client, WP_MORTAR, GetAmmoTableData(WP_MORTAR)->defaultStartingAmmo, GetAmmoTableData(WP_MORTAR)->defaultStartingClip, qtrue ) ) {
							if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_MORTAR_SET))
								AddWeaponToPlayer( client, WP_MORTAR_SET, GetAmmoTableData(WP_MORTAR_SET)->defaultStartingAmmo, GetAmmoTableData(WP_MORTAR_SET)->defaultStartingClip, qfalse );
						}
						break;
					}
					break;
				case TEAM_ALLIES:
					switch( primaryWeapon ) {
					default:
					case WP_THOMPSON:
						AddWeaponToPlayer( client, WP_THOMPSON, GetAmmoTableData(WP_THOMPSON)->defaultStartingAmmo, GetAmmoTableData(WP_THOMPSON)->defaultStartingClip, qtrue );
						break;
					case WP_PANZERFAUST:
						AddWeaponToPlayer( client, WP_PANZERFAUST, GetAmmoTableData(WP_PANZERFAUST)->defaultStartingAmmo, GetAmmoTableData(WP_PANZERFAUST)->defaultStartingClip, qtrue );
						break;
					case WP_FLAMETHROWER:
						AddWeaponToPlayer( client, WP_FLAMETHROWER, GetAmmoTableData(WP_FLAMETHROWER)->defaultStartingAmmo, GetAmmoTableData(WP_FLAMETHROWER)->defaultStartingClip, qtrue );
						break;
					case WP_MOBILE_MG42:
						if( AddWeaponToPlayer( client, WP_MOBILE_MG42, GetAmmoTableData(WP_MOBILE_MG42)->defaultStartingAmmo, GetAmmoTableData(WP_MOBILE_MG42)->defaultStartingClip, qtrue ) ) {
							if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_MOBILE_MG42_SET))
								AddWeaponToPlayer( client, WP_MOBILE_MG42_SET, GetAmmoTableData(WP_MOBILE_MG42_SET)->defaultStartingAmmo, GetAmmoTableData(WP_MOBILE_MG42_SET)->defaultStartingClip, qfalse );
						}
						break;
					case WP_MORTAR:
						if( AddWeaponToPlayer( client, WP_MORTAR, GetAmmoTableData(WP_MORTAR)->defaultStartingAmmo, GetAmmoTableData(WP_MORTAR)->defaultStartingClip, qtrue ) ) {
							if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_MORTAR_SET))
								AddWeaponToPlayer( client, WP_MORTAR_SET, GetAmmoTableData(WP_MORTAR_SET)->defaultStartingAmmo, GetAmmoTableData(WP_MORTAR_SET)->defaultStartingClip, qfalse );
						}
						break;
					}
					break;
				default:
					break;
			}
		} else if( pc == PC_COVERTOPS ) {
			switch( primaryWeapon ) {
			case WP_K43:
			case WP_GARAND:
				if( client->sess.sessionTeam == TEAM_AXIS ) {
					if( AddWeaponToPlayer( client, WP_K43, GetAmmoTableData(WP_K43)->defaultStartingAmmo, GetAmmoTableData(WP_K43)->defaultStartingClip, qtrue ) ) {
						if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_K43_SCOPE))
							AddWeaponToPlayer( client, WP_K43_SCOPE, GetAmmoTableData(WP_K43_SCOPE)->defaultStartingAmmo, GetAmmoTableData(WP_K43_SCOPE)->defaultStartingClip, qfalse );
					}
					break;
				} else {
					if( AddWeaponToPlayer( client, WP_GARAND, GetAmmoTableData(WP_GARAND)->defaultStartingAmmo, GetAmmoTableData(WP_GARAND)->defaultStartingClip, qtrue ) ) {
						if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_GARAND_SCOPE))
							AddWeaponToPlayer( client, WP_GARAND_SCOPE, GetAmmoTableData(WP_GARAND_SCOPE)->defaultStartingAmmo, GetAmmoTableData(WP_GARAND_SCOPE)->defaultStartingClip, qfalse );
					}
					break;
				}
			case WP_FG42:
				if( AddWeaponToPlayer( client, WP_FG42, GetAmmoTableData(WP_FG42)->defaultStartingAmmo, GetAmmoTableData(WP_FG42)->defaultStartingClip, qtrue ) ) {
					if(!G_IsWeaponDisabled(&g_entities[client->ps.clientNum], WP_FG42SCOPE))
						AddWeaponToPlayer( client, WP_FG42SCOPE, GetAmmoTableData(WP_FG42SCOPE)->defaultStartingAmmo, GetAmmoTableData(WP_FG42SCOPE)->defaultStartingClip, qfalse );
				}
				break;
			default:
				AddWeaponToPlayer( client, WP_STEN, GetAmmoTableData(WP_STEN)->defaultStartingAmmo, GetAmmoTableData(WP_STEN)->defaultStartingClip, qtrue );
				break;
			}

			if( AddWeaponToPlayer( client, WP_BINOCULARS, 1, 0, qfalse ) ) {
				client->ps.stats[STAT_KEYS] |= ( 1 << INV_BINOCS );
			}

			if (!deathmatch)
				AddWeaponToPlayer( client, WP_SMOKE_BOMB, GetAmmoTableData(WP_SMOKE_BOMB)->defaultStartingAmmo,  GetAmmoTableData(WP_SMOKE_BOMB)->defaultStartingClip, qfalse );

			/* Original 0x47eca/0x486c0: check availability before looking
			 * up the owner's existing charge (call at 0x47eeb). */
			if (!deathmatch || (dmOptions & 0x1000u)) {
				qboolean planted = G_FindSatchel( &g_entities[client->ps.clientNum] ) != NULL;
				AddWeaponToPlayer( client, WP_SATCHEL, 0, planted ? 0 : 1, qfalse );
				AddWeaponToPlayer( client, WP_SATCHEL_DET, 0, planted ? 1 : 0, qfalse );
			}
		}

		G_NITMOD_GrantSelectedSecondary(client, g_dualSMG.integer, medicOptions);
		if( pc == PC_SOLDIER ) {
			if( client->sess.sessionTeam == TEAM_AXIS ) {
				AddWeaponToPlayer( client, WP_GRENADE_LAUNCHER,  0, 4, qfalse );
			} else {
				AddWeaponToPlayer( client, WP_GRENADE_PINEAPPLE, 0, 4, qfalse );
			}
		}
		if( pc == PC_COVERTOPS ) {
			if( client->sess.sessionTeam == TEAM_AXIS ) {
				AddWeaponToPlayer( client, WP_GRENADE_LAUNCHER,  0, 2, qfalse );
			} else {
				AddWeaponToPlayer( client, WP_GRENADE_PINEAPPLE, 0, 2, qfalse );
			}
		}
	} else {
		// Knifeonly block
		if( pc == PC_MEDIC ) {
			AddWeaponToPlayer( client, WP_MEDIC_SYRINGE, 0, 20, qfalse );
			if( client->sess.skill[SK_FIRST_AID] >= 4 )
				AddWeaponToPlayer( client, WP_MEDIC_ADRENALINE, 0, 10, qfalse );

		}
		// End Knifeonly stuff -- Ensure that medics get their basic stuff
	}
	/* Original G_AddClassWeapons: opposite SMG for an SMG primary,
	 * otherwise the team's SMG. Covert ops are explicitly excluded. */
	if(pc == PC_MEDIC && (medicOptions & 4u) && g_knifeonly.integer != 1) {
		weapon_t pistol = client->sess.sessionTeam == TEAM_AXIS ? WP_LUGER : WP_COLT;
		weapon_t akimbo = client->sess.sessionTeam == TEAM_AXIS ? WP_AKIMBO_LUGER : WP_AKIMBO_COLT;
		client->ps.weapon = COM_BitCheck(client->ps.weapons, akimbo) ? akimbo : pistol;
	}
	if(g_dualSMG.integer && g_knifeonly.integer != 1 && pc != PC_COVERTOPS &&
		(unsigned int)G_NITMOD_ConfiguredWarMode() - 1u >= 4u) {
		weapon_t primary = primaryWeapon;
		weapon_t extra = primary == WP_MP40 ? WP_THOMPSON :
			primary == WP_THOMPSON ? WP_MP40 :
			client->sess.sessionTeam == TEAM_AXIS ? WP_MP40 : WP_THOMPSON;
		AddWeaponToPlayer(client, extra,
			pc == PC_MEDIC ? 0 : GetAmmoTableData(extra)->defaultStartingAmmo,
			GetAmmoTableData(extra)->defaultStartingClip, qfalse);
	}
	if(g_knifeonly.integer != 1) {
		/* Original client+0x158 is the flak powerup, not binocular ammo.
		 * g_skills bit 1 shares Engineering reward16 across classes. */
		if(!deathmatch && (client->sess.nitmodSkillMasks[SK_EXPLOSIVES_AND_CONSTRUCTION] & 16u) &&
			(pc == PC_ENGINEER || (G_NITMOD_LegacyCvarInteger("g_skills", 0) & 1)))
			client->ps.powerups[NITMOD_PW_FLAK] = INT_MAX;
		/* Class callers of original G_AddClassSpecificTools.part.3.
		 * War modes have already returned before ordinary class grants. */
		if(pc == PC_ENGINEER) {
			/* Original class-tool branch: Engineering bit32, g_weapons bit4;
			 * Deathmatch additionally requires g_DMOptions bit0x2000. */
			if((client->sess.nitmodSkillMasks[SK_EXPLOSIVES_AND_CONSTRUCTION] & 32u) &&
				(G_NITMOD_ConfiguredWeaponFlags() & 4) &&
				(!deathmatch || (dmOptions & 0x2000u))) {
				const ammotable_t *bombAmmo = GetAmmoTableData(WP_BOMB);
				AddWeaponToPlayer(client, WP_BOMB, bombAmmo->defaultStartingAmmo,
					bombAmmo->defaultStartingClip, qfalse);
			}
			G_NITMOD_AddSpecialClassTool(client, WP_TRIPMINE);
			G_NITMOD_AddSpecialClassTool(client, WP_POISON_MINE);
		} else if(pc == PC_COVERTOPS) {
			G_NITMOD_AddSpecialClassTool(client, WP_POISON_BOMB);
		}
		G_NITMOD_GrantAdrenalineSpawn(client, G_NITMOD_FirstAidUnlocks(client),
			(unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenClasses", 2),
			(unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenaline", 0),
			G_NITMOD_ConfiguredWarMode(), GetAmmoTableData(WP_MEDIC_ADRENALINE));
		/* Original G_AddClassSpecificTools.part.3 (0x4802d) checks Light
		 * Weapons reward bit 16 for wire weapon 47. Use the typed
		 * weapon row so custom weapon definitions keep their ammo contract. */
		if(g_poison.integer && (client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] & 16u)) {
			const ammotable_t *poisonAmmo = GetAmmoTableData(WP_POISON_SYRINGE);
			AddWeaponToPlayer(client, WP_POISON_SYRINGE,
				poisonAmmo->defaultStartingAmmo,
				poisonAmmo->defaultStartingClip, qfalse);
		}
	}
}

int G_CountTeamMedics( team_t team, qboolean alivecheck ) {
	int numMedics = 0;
	int i, j;

	/* Original 0x4a08c/0x4a09a: share the sorted non-spectator prefix
	 * for both team-health bonuses and living-medic/LMS checks. */
	for( i = 0; i < level.numNonSpectatorClients; i++ ) {
		j = level.sortedClients[i];

		if( level.clients[j].sess.sessionTeam != team ) {
			continue;
		}

		if( level.clients[j].sess.playerType != PC_MEDIC ) {
			continue;
		}

		if( alivecheck ) {
			if( g_entities[j].health <= 0 ) {
				continue;
			}

			if( level.clients[j].ps.pm_type == PM_DEAD || level.clients[j].ps.pm_flags & PMF_LIMBO ) {
				continue;
			}
		}

		numMedics++;
	}

	return numMedics;
}

//
// AddMedicTeamBonus
//
int G_NITMOD_ClassMaxHealth(int playerClass) {
	char text[MAX_CVAR_VALUE_STRING], *cursor, *token;
	int i, value;
	if(playerClass < PC_SOLDIER || playerClass > PC_COVERTOPS) return 0;
	Q_strncpyz(text, n_classesMaxHP.string, sizeof(text));
	cursor = text;
	/* Original nitrox_ParseMaxHP 0x10f550 uses strtok(" "), not the
	 * command parser: tabs/newlines, quotes and comments are not separators. */
	for(i = 0; i <= playerClass; ++i) {
		while(*cursor == ' ') ++cursor;
		if(!*cursor) return 0;
		token = cursor;
		while(*cursor && *cursor != ' ') ++cursor;
		if(*cursor) *cursor++ = 0;
		if(i == playerClass) {
			value = NITMOD_ParseOriginalDecimal32(token);
			return value > 0 ? value : 0;
		}
	}
	return 0;
}

void G_NITMOD_SetHealthLimits(gclient_t *client, int numMedics, int war, int gametype, int override) {
	int maximum;
	if(!client || numMedics < 0 || numMedics > MAX_CLIENTS || override < 0) return;
	/* Original AddMedicTeamBonus: either special mode suppresses team and
	 * battle-sense bonuses. The medic overhealth exception requires BOTH. */
	maximum = 100;
	if(!war && gametype != 8) {
		maximum += numMedics >= 3 ? 25 : numMedics * 10;
		if(client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] & 8u) maximum += 15;
	}
	if(override > 0) maximum = override;
	client->pers.maxHealth = client->ps.stats[STAT_MAX_HEALTH] = maximum;
	client->ps.stats[STAT_NITMOD_MAX_HEALTH] =
		client->sess.playerType == PC_MEDIC && !override && !(war && gametype == 8) ?
		(int)(maximum * 1.12) : maximum;
}

int G_NITMOD_SpawnHealth(const gclient_t *client, int war, int gametype, int override) {
	if(!client) return 0;
	return client->ps.stats[STAT_MAX_HEALTH] -
		(!war && gametype != 8 && !override && (client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] & 8u) ? 15 : 0);
}

static void ApplySpawnHealth(gentity_t *ent, qboolean restoreHealth, int war, int gametype, int override) {
	if (restoreHealth) ent->health = G_NITMOD_SpawnHealth(ent->client, war, gametype, override);
	ent->client->ps.stats[STAT_HEALTH] = ent->health;
}

void AddMedicTeamBonus( gclient_t *client ) {
	if(!client) return;
	G_NITMOD_SetHealthLimits(client, G_CountTeamMedics(client->sess.sessionTeam, qfalse),
		G_NITMOD_ConfiguredWarMode(), g_gametype.integer, G_NITMOD_ClassMaxHealth(client->sess.playerType));
}

/*
===========
ClientCheckName
============
*/
void ClientCleanName( const char *in, char *out, int outSize )
{
	int		len, colorlessLen;
	char	ch;
	char	*p;
	int		spaces;

	//save room for trailing null byte
	outSize--;

	len = 0;
	colorlessLen = 0;
	p = out;
	*p = 0;
	spaces = 0;

	while( 1 ) {
		ch = *in++;
		if( !ch ) {
			break;
		}

		// don't allow leading spaces
		if( !*p && ch == ' ' ) {
			continue;
		}

		// check colors
		if( ch == Q_COLOR_ESCAPE ) {
			// solo trailing carat is not a color prefix
			if( !*in ) {
				break;
			}

			// don't allow black in a name, period
/*			if( ColorIndex(*in) == 0 ) {
				in++;
				continue;
			}
*/
			// make sure room in dest for both chars
			if( len > outSize - 2 ) {
				break;
			}

			*out++ = ch;
			*out++ = *in++;
			len += 2;
			continue;
		}

		// don't allow too many consecutive spaces
		if( ch == ' ' ) {
			spaces++;
			if( spaces > 3 ) {
				continue;
			}
		}
		else {
			spaces = 0;
		}

		if( len > outSize - 1 ) {
			break;
		}

		*out++ = ch;
		colorlessLen++;
		len++;
	}
	*out = 0;

	// don't allow empty names
	if( *p == 0 || colorlessLen == 0 ) {
		Q_strncpyz( p, "UnnamedPlayer", outSize );
	}
}

/* Nitmod counts only visible, non-space characters for n_minNameLength.
 * A colour escape consumes both bytes and does not contribute to the count. */
static int G_NITMOD_VisibleNameLength( const char *name )
{
	int length = 0;

	while( name && *name ) {
		if( *name == Q_COLOR_ESCAPE ) {
			if( !name[1] ) break;
			name += 2;
			continue;
		}
		if( *name != ' ' ) {
			length++;
		}
		name++;
	}

	return length;
}

void G_StartPlayerAppropriateSound(gentity_t *ent, char *soundType) {
}

/*
===========
ClientUserInfoChanged

Called from ClientConnect when the player first connects and
directly by the server system when the player updates a userinfo variable.

The game can override any of the settings and call trap_SetUserinfo
if desired.
============
*/
#include "g_nitmod_accounts.h"
/* Keep the server's userinfo and published player name in sync after a hit.
 * Original ClientConnect/ClientUserinfoChanged normalize before matching. */
static qboolean G_NITMOD_CensorUserinfoName(int clientNum, char *userinfo) {
	char name[MAX_INFO_STRING];
	Q_strncpyz(name, Info_ValueForKey(userinfo, "name"), sizeof(name));
	if(!G_NITMOD_CensorText("g_censorNames", name, sizeof(name))) return qfalse;
	G_LogPrintf("[NAME CENSOR] Client %i Censored Name: \"%s\"\n",
		clientNum, Info_ValueForKey(userinfo, "name"));
	Info_SetValueForKey(userinfo, "name", name);
	trap_SetUserinfo(clientNum, userinfo);
	return qtrue;
}

void ClientUserinfoChanged( int clientNum ) {
	gentity_t *ent;
	char	*s;
	char	oldname[MAX_STRING_CHARS];
	char	userinfo[MAX_INFO_STRING];
	gclient_t	*client;
	int		i;
	char	skillStr[16] = "";
	char	medalStr[16] = "";
	char	xpStr[128] = "";
	int		characterIndex;
	int databaseMuted;


	ent = g_entities + clientNum;
	client = ent->client;

	client->pers.nitmodDemoClient=G_NITMOD_IsDemoClient(clientNum,
        trap_Cvar_VariableIntegerValue("sv_demoState"),trap_Cvar_VariableIntegerValue("sv_demoClients"));
	client->ps.clientNum = clientNum;

	client->medals = 0;
	for( i = 0; i < SK_NUM_SKILLS; i++ ) {
		client->medals += client->sess.medals[ i ];
	}

	trap_GetUserinfo( clientNum, userinfo, sizeof( userinfo ) );

	// check for malformed or illegal info strings
	if ( !Info_Validate(userinfo) ) {
		Q_strncpyz( userinfo, "\\name\\badinfo", sizeof(userinfo) );
	}

#ifndef DEBUG_STATS
	if( g_developer.integer || *g_log.string || g_dedicated.integer ) 
#endif
	{
		G_Printf("Userinfo: %s\n", userinfo);
	}

	// check for local client
	s = Info_ValueForKey( userinfo, "ip" );
	G_NITMOD_CacheClientAddress( ent, s );
	if ( s && !strcmp( s, "localhost" ) ) {
		client->pers.localClient = qtrue;
		level.fLocalHost = qtrue;
		client->sess.referee = RL_REFEREE;
	}

	// OSP - extra client info settings
	//		 FIXME: move other userinfo flag settings in here
	if(ent->r.svFlags & SVF_BOT) {
		client->pers.autoActivate = PICKUP_TOUCH;
		client->pers.bAutoReloadAux = qtrue;
		client->pers.bAltReloadAux = qfalse;
		client->pmext.bAutoReload = qtrue;
		client->pers.predictItemPickup = qfalse;
	} else {
		s = Info_ValueForKey(userinfo, "cg_uinfo");
		sscanf(s, "%i %i %i",
								&client->pers.clientFlags,
								&client->pers.clientTimeNudge,
								&client->pers.clientMaxPackets);

		client->pers.autoActivate = (client->pers.clientFlags & CGF_AUTOACTIVATE) ? PICKUP_TOUCH : PICKUP_ACTIVATE;
		client->pers.predictItemPickup = ((client->pers.clientFlags & CGF_PREDICTITEMS) != 0);
		client->pers.bAltReloadAux =
			(client->pers.clientFlags & NITMOD_CGF_ALT_RELOAD) != 0;

		if(client->pers.clientFlags & CGF_AUTORELOAD) {
			client->pers.bAutoReloadAux = qtrue;
			client->pmext.bAutoReload = qtrue;
		} else {
			client->pers.bAutoReloadAux = qfalse;
			client->pmext.bAutoReload = qfalse;
		}
	}

	// set name
	Q_strncpyz( oldname, client->pers.netname, sizeof( oldname ) );
	if(!(ent->r.svFlags & SVF_BOT) && !client->pers.nitmodDemoClient &&
		G_NITMOD_CensorUserinfoName(clientNum, userinfo) &&
		(G_NITMOD_LegacyCvarInteger("g_censorPenalty", 1) & 2)) {
		G_LogPrintf("[DROPCLIENT] Client %d Name censor (%s)\n",
			clientNum, Info_ValueForKey(userinfo, "name"));
		trap_DropClient(clientNum, "Name censor. Please change your name.", 0);
		return;
	}
	s = Info_ValueForKey(userinfo, "name");
	ClientCleanName(s, client->pers.netname, sizeof(client->pers.netname));

	if ( client->pers.connected == CON_CONNECTED ) {
		if ( strcmp( oldname, client->pers.netname ) ) {
			trap_SendServerCommand( -1, va("print \"[lof]%s" S_COLOR_WHITE " [lon]renamed to[lof] %s\n\"", oldname, 
				client->pers.netname) );
		}
	}

	if(!G_NITMOD_AccountUserinfo(clientNum,userinfo)) return;
	G_NITMOD_GlobalStatsRequest(clientNum,Info_ValueForKey(userinfo,"n_guid"));
	databaseMuted=G_NITMOD_AccountMuted(clientNum);
	for( i = 0; i < SK_NUM_SKILLS; i++ ) {
		Q_strcat( skillStr, sizeof(skillStr), va("%i",client->sess.skill[i]) );
		Q_strcat( medalStr, sizeof(medalStr), va("%i",client->sess.medals[i]) );
		Q_strcat( xpStr, sizeof(xpStr), va("%s%u", i ? " " : "",
			client->sess.nitmodSkillMasks[i]) );
		// FIXME: Gordon: wont this break if medals > 9 arnout? JK: Medal count is tied to skill count :() Gordon: er, it's based on >> skill per map, so for a huuuuuuge campaign it could break...
	}

	client->ps.stats[STAT_MAX_HEALTH] = client->pers.maxHealth;

	// check for custom character
	s = Info_ValueForKey( userinfo, "ch" );
	if( *s ) {
		characterIndex = atoi(s);
	} else {
		characterIndex = -1;
	}

	// To communicate it to cgame
	client->ps.stats[ STAT_PLAYER_CLASS ] = client->sess.playerType;
	// Gordon: Not needed any more as it's in clientinfo?

	// send over a subset of the userinfo keys so other clients can
	// print scoreboards, display models, and play custom sounds
	if ( ent->r.svFlags & SVF_BOT ) {
		// n: netname
		// t: sessionTeam
		// c1: color
		// hc: maxHealth
		// skill: skill
		// c: playerType (class?)
		// r: rank
		// f: fireteam
		// bot: botSlotNumber
		// nwp: noWeapon
		// m: medals
		// ch: character

		s = va( "n\\%s\\t\\%i\\skill\\%s\\c\\%i\\r\\%i\\m\\%s\\s\\%s%s\\dn\\%s\\dr\\%i\\w\\%i\\lw\\%i\\sw\\%i\\mu\\%i",
			client->pers.netname,
			client->sess.sessionTeam, 
			Info_ValueForKey( userinfo, "skill" ), 
			client->sess.playerType,
			client->sess.rank,
			medalStr,
            skillStr,
			characterIndex >= 0 ? va( "\\ch\\%i", characterIndex ) : "",
			client->disguiseNetname,
			client->disguiseRank,
			client->sess.playerWeapon,
			client->sess.latchPlayerWeapon,
			client->sess.latchPlayerWeapon2,
			(client->sess.muted || databaseMuted) ? 1 : 0
		);
	} else {
		s = va( "n\\%s\\t\\%i\\c\\%i\\r\\%i\\m\\%s\\s\\%s\\dn\\%s\\dr\\%i\\w\\%i\\lw\\%i\\sw\\%i\\mu\\%i\\ref\\%i",
			client->pers.netname, 
			client->sess.sessionTeam, 
			client->sess.playerType, 
			client->sess.rank, 
			medalStr,
			skillStr,
			client->disguiseNetname,
			client->disguiseRank,
			client->sess.playerWeapon,
			client->sess.latchPlayerWeapon,
			client->sess.latchPlayerWeapon2,
			(client->sess.muted || databaseMuted) ? 1 : 0,
			client->sess.referee
		);
	}

	trap_GetConfigstring( CS_PLAYERS + clientNum, oldname, sizeof( oldname ) );

	/* Optional original equipment field; stock clients ignore unknown keys. */
	if(g_gametype.integer==8 && (g_DMOptions.integer&8) &&
		client->sess.sessionTeam==TEAM_SPECTATOR) client->sess.shoutcaster=1;
	s = va( "%s\\rn\\%i\\lc\\%i\\xp\\%s\\sc\\%i\\u\\%i", s, client->sess.rifleGrenadeStatus,
		client->sess.latchPlayerType, xpStr, client->sess.shoutcaster, client->sess.uci );

	trap_SetConfigstring( CS_PLAYERS + clientNum, s );

	if( !Q_stricmp( oldname, s ) ) {
		return;
	}

	G_LogPrintf( "ClientUserinfoChanged: %i %s\n", clientNum, s );
	G_NITMOD_LuaClientEvent("et_ClientUserinfoChanged",clientNum);
	G_DPrintf( "ClientUserinfoChanged: %i :: %s\n", clientNum, s );
}


/*
===========
ClientConnect

Called when a player begins connecting to the server.
Called again for every map change or tournement restart.

The session information will be valid after exit.

Return NULL if the client should be allowed, otherwise return
a string with the reason for denial.

Otherwise, the client will be sent the current gamestate
and will eventually get to ClientBegin.

firstTime will be qtrue the very first time a client connects
to the server machine, but qfalse on map changes and tournement
restarts.
============
*/
char *ClientConnect( int clientNum, qboolean firstTime, qboolean isBot ) {
	char		*value;
	gclient_t	*client;
	char		userinfo[MAX_INFO_STRING];
	const char	*rawName;
	gentity_t	*ent;
	int		minimumNameLength;
	qboolean demoClient;
#ifdef USEXPSTORAGE
	ipXPStorage_t* xpBackup;
	int			i;
#endif // USEXPSTORAGE

	ent = &g_entities[ clientNum ];
	G_NITMOD_CvarScanResetClient(clientNum);
	G_NITMOD_NxACResetClient(clientNum);
	G_NITMOD_NxACTransferResetClient(clientNum);
	G_NITMOD_MDXReset(&g_entities[clientNum]);
	G_NITMOD_ResetClient(clientNum);

	trap_GetUserinfo( clientNum, userinfo, sizeof( userinfo ) );

	/* Original ClientConnect exempts server-demo slots from name admission. */
	demoClient = G_NITMOD_IsDemoClient(clientNum,
		trap_Cvar_VariableIntegerValue("sv_demoState"),
		trap_Cvar_VariableIntegerValue("sv_demoClients"));
	if(!isBot && !demoClient && G_NITMOD_CensorUserinfoName(clientNum, userinfo) &&
		(G_NITMOD_LegacyCvarInteger("g_censorPenalty", 1) & 2)) {
		G_LogPrintf("[DROPCLIENT] Client %d Name censor (%s)\n",
			clientNum, Info_ValueForKey(userinfo, "name"));
		return "Name censor. Please change your name.";
	}

	/* Original ClientConnect counts the received name before ClientCleanName. */
	minimumNameLength = G_NITMOD_LegacyCvarInteger("n_minNameLength", 0);
	if( !isBot && !demoClient && minimumNameLength > 0 ) {
		rawName = Info_ValueForKey(userinfo, "name");
		if( G_NITMOD_VisibleNameLength(rawName) < minimumNameLength ) {
			G_LogPrintf("[DROPCLIENT] Client %d Name too short (%s)\n",
				clientNum, rawName);
			return va("Your name is too short, it must contain at least %d visible characters.\n",
				minimumNameLength);
		}
	}

	// IP filtering
	{ const char *ban=G_NITMOD_DatabaseBanReason(userinfo); if(ban) return (char *)ban; }
	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=500
	// recommanding PB based IP / GUID banning, the builtin system is pretty limited
	// check to see if they are on the banned IP list
	value = Info_ValueForKey (userinfo, "ip");
	if ( G_FilterIPBanPacket( value ) ) {
		return "You are banned from this server.";
	}

	// Xian - check for max lives enforcement ban
	if( g_gametype.integer != GT_WOLF_LMS ) {
		if( g_enforcemaxlives.integer && (g_maxlives.integer > 0 || g_axismaxlives.integer > 0 || g_alliedmaxlives.integer > 0) ) {
			if( trap_Cvar_VariableIntegerValue( "sv_punkbuster" ) ) {
				value = Info_ValueForKey ( userinfo, "cl_guid" );
				if ( G_FilterMaxLivesPacket ( value ) ) {
					return "Max Lives Enforcement Temp Ban. You will be able to reconnect when the next round starts. This ban is enforced to ensure you don't reconnect to get additional lives.";
				}
			} else {
				value = Info_ValueForKey ( userinfo, "ip" );	// this isn't really needed, oh well.
				if ( G_FilterMaxLivesIPPacket ( value ) ) {
					return "Max Lives Enforcement Temp Ban. You will be able to reconnect when the next round starts. This ban is enforced to ensure you don't reconnect to get additional lives.";
				}
			}
		}
	}
	// End Xian
	
	// we don't check password for bots and local client
	// NOTE: local client <-> "ip" "localhost"
	//   this means this client is not running in our current process
	if ( !isBot && !( ent->r.svFlags & SVF_BOT ) && (strcmp(Info_ValueForKey ( userinfo, "ip" ), "localhost") != 0)) {
		// check for a password
		value = Info_ValueForKey (userinfo, "password");
		if ( g_password.string[0] && Q_stricmp( g_password.string, "none" ) && strcmp( g_password.string, value) != 0) {
			if( !sv_privatepassword.string[ 0 ] || strcmp( sv_privatepassword.string, value ) ) {
				return "Invalid password";
			}
		}
	}

	{
		const char *denial = G_NITMOD_CheckConnection(clientNum, userinfo, isBot);
		if (denial) return (char *)denial;
	}

	// Gordon: porting q3f flag bug fix
	//			If a player reconnects quickly after a disconnect, the client disconnect may never be called, thus flag can get lost in the ether
	if( ent->inuse ) {
		G_LogPrintf( "Forcing disconnect on active client: %i\n", ent-g_entities );
		// so lets just fix up anything that should happen on a disconnect
		ClientDisconnect( ent-g_entities );
	}

	// they can connect
	G_NITMOD_AccountReset(clientNum);
	ent->client = level.clients + clientNum;
	client = ent->client;



	memset( client, 0, sizeof(*client) );
    client->pers.nitmodDemoClient=G_NITMOD_IsDemoClient(clientNum,
        trap_Cvar_VariableIntegerValue("sv_demoState"),trap_Cvar_VariableIntegerValue("sv_demoClients"));
	client->pers.nitmodLastAmmoClient = -1;
	client->pers.nitmodLastKillerClient = -1;
	client->pers.nitmodLastHealthClient = -1;
	client->pers.nitmodLastKilledClient = -1;
	client->pers.nitmodLastReviverClient = -1;

	client->pers.connected = CON_CONNECTING;
	client->pers.connectTime = level.time;			// DHM - Nerve

	if( firstTime )
		client->pers.initialSpawn = qtrue;				// DHM - Nerve

	// read or initialize the session data
	if( firstTime ) {
		G_InitSessionData( client, userinfo );
		client->pers.enterTime = level.time;
		client->ps.persistant[PERS_SCORE] = 0;
	} else {
		G_ReadSessionData( client );
	}
	client->sess.uci=G_NITMOD_GeoIPCountry(Info_ValueForKey(userinfo,"ip"),isBot);

#ifdef USEXPSTORAGE
	value = Info_ValueForKey (userinfo, "ip");
	if( NITMOD_DBUserCount()<0 && (xpBackup = G_FindXPBackup( value )) ) {
		for( i = 0; i < SK_NUM_SKILLS; i++ ) {
			client->sess.skillpoints[ i ] = xpBackup->skills[ i ];
		}
		G_CalcRank( client );
	}
#endif // USEXPSTORAGE

	if( g_gametype.integer == GT_WOLF_CAMPAIGN ) {
		if( g_campaigns[level.currentCampaign].current == 0 || level.newCampaign ) {
			client->pers.enterTime = level.time;
		}
	} else {
		client->pers.enterTime = level.time;
	}

	if( isBot ) {
		// Set up the name for the bot client before initing the bot
		value = Info_ValueForKey ( userinfo, "scriptName" );
		if (value && value[0]) {
			Q_strncpyz( client->pers.botScriptName, value, sizeof( client->pers.botScriptName ) );
			ent->scriptName = client->pers.botScriptName;
		}
		ent->aiName = ent->scriptName;
		ent->s.number = clientNum;

		ent->r.svFlags |= SVF_BOT;
		ent->inuse = qtrue;
		/* Original exposes bot flags before Lua and ignores its denial for bots. */
		(void)G_NITMOD_LuaConnect(clientNum,firstTime,isBot);
		// if this bot is reconnecting, and they aren't supposed to respawn, then dont let it in
		if (!firstTime) {
			value = Info_ValueForKey (userinfo, "respawn");
			if (value && value[0] && (!Q_stricmp(value, "NO") || !Q_stricmp(value, "DISCONNECT"))) {
				return "BotConnectFailed (no respawn)";
			}
		}

		/* External Omni-bot clients are driven through ETInterface.  Feeding
		 * them into ET 2.60's legacy botlib starts the removed AAS syscall
		 * range (304+) on ET:Legacy and crashes the WASM server. */
		if (!G_NITMOD_LegacyCvarInteger("omnibot_enable", 0) &&
			!G_BotConnect( clientNum, !firstTime )) {
			return "BotConnectfailed";
		}
	}
	else if( g_gametype.integer == GT_COOP || g_gametype.integer == GT_SINGLE_PLAYER ) {
		// RF, in single player, enforce team = ALLIES
		// Arnout: disabled this for savegames as the double ClientBegin it causes wipes out all loaded data
		if( saveGamePending != 2 )
			client->sess.sessionTeam = TEAM_ALLIES;
			client->sess.spectatorState = SPECTATOR_NOT;
			client->sess.spectatorClient = 0;
	} else if( firstTime ) {
		// force into spectator
		client->sess.sessionTeam = TEAM_SPECTATOR;
		client->sess.spectatorState = SPECTATOR_FREE;
		client->sess.spectatorClient = 0;

		// unlink the entity - just in case they were already connected
		trap_UnlinkEntity( ent );
	}

	// get and distribute relevent paramters
	if(!isBot) {
		char *denial=G_NITMOD_LuaConnect(clientNum,firstTime,isBot);
		if(denial && !(ent->r.svFlags & SVF_BOT))
			return va("You are excluded from this server. %s\n",denial);
	}
	G_LogPrintf( "ClientConnect: %i\n", clientNum );
	G_UpdateCharacter( client );
	ClientUserinfoChanged( clientNum );

	if (g_gametype.integer == GT_SINGLE_PLAYER) {

		if (!isBot) {
			ent->scriptName = "player";

// START	Mad Doctor I changes, 8/14/2002
			// We must store this here, so that BotFindEntityForName can find the
			// player.
			ent->aiName = "player";
// END		Mad Doctor I changes, 8/12/2002

			G_Script_ScriptParse( ent );
			G_Script_ScriptEvent( ent, "spawn", "" );
		}

	}


	// don't do the "xxx connected" messages if they were caried over from previous level
	//		TAT 12/10/2002 - Don't display connected messages in single player
	if ( firstTime && !G_IsSinglePlayerGame())
	{
		trap_SendServerCommand( -1, va("cpm \"%s" S_COLOR_WHITE " connected\n\"", client->pers.netname) );
	}

	// count current clients and rank for scoreboard
	CalculateRanks();
	G_NITMOD_RefreshTeamPopulation();
	Bot_Event_ClientConnected(clientNum, isBot);

	return NULL;
}

//
// Scaling for late-joiners of maxlives based on current game time
//
int G_ComputeMaxLives(gclient_t *cl, int maxRespawns)
{
	float scaled, duration;
	int val;

	// rain - #102 - don't scale of the timelimit is 0
	if (g_timelimit.value == 0.0) {
		return maxRespawns - 1;
	}

	/* Original 0x4d1dc -> 0x4d270 disables the limit after map time
	 * expires; overtime must not become a zero-life late join. */
	duration = g_timelimit.value * 60000.0f;
	if((float)(level.time - level.startTime) >= duration) return -1;
	scaled = (float)(maxRespawns - 1) *
		(1.0f - (float)(level.time - level.startTime) / duration);
	val = (int)scaled;
	val += ((scaled - (float)val) < 0.5f) ? 0 : 1;
	return(val);
}

/*
===========
ClientBegin

called when a client has finished connecting, and is ready
to be placed into the level.  This will happen every level load,
and on transition between teams, but doesn't happen on respawns
============
*/
void ClientBegin( int clientNum )
{
	gentity_t	*ent;
	gclient_t	*client;
	qboolean restoreHealth,notifyLuaBegin,isBot;
	int			flags;
	int			spawn_count, lives_left;		// DHM - Nerve

	ent = g_entities + clientNum;
	isBot = (ent->r.svFlags & SVF_BOT) != 0;
	G_NITMOD_MDXReset(ent);
	restoreHealth = ent->health <= 0 || G_NITMOD_LegacyCvarInteger("g_teamChangeKills", 1);

	client = level.clients + clientNum;
    notifyLuaBegin=client->pers.connected==CON_CONNECTING && !(ent->r.svFlags&SVF_BOT) && !client->pers.nitmodDemoClient;
	G_NITMOD_ResetGameplayClient( clientNum );

	if ( ent->r.linked ) {
		trap_UnlinkEntity( ent );
	}

	G_InitGentity( ent );
	ent->touch = 0;
	ent->pain = 0;
	ent->client = client;

	if(notifyLuaBegin) G_NITMOD_SendForcedCvars(clientNum);
	client->pers.connected = CON_CONNECTED;
	client->pers.teamState.state = TEAM_BEGIN;

	// save eflags around this, because changing teams will
	// cause this to happen with a valid entity, and we
	// want to make sure the teleport bit is set right
	// so the viewpoint doesn't interpolate through the
	// world to the new position
	// DHM - Nerve :: Also save PERS_SPAWN_COUNT, so that CG_Respawn happens
	spawn_count = client->ps.persistant[PERS_SPAWN_COUNT];
	//bani - proper fix for #328
	if( client->ps.persistant[PERS_RESPAWNS_LEFT] > 0 ) {
		lives_left = client->ps.persistant[PERS_RESPAWNS_LEFT] - 1;
	} else {
		lives_left = client->ps.persistant[PERS_RESPAWNS_LEFT];
	}
	flags = client->ps.eFlags;
	memset( &client->ps, 0, sizeof( client->ps ) );
    memset(client->nitmodLuaUnusedPowerups,0,sizeof(client->nitmodLuaUnusedPowerups));
    memset(client->nitmodLuaPersistant,0,sizeof(client->nitmodLuaPersistant));
    client->nitmodLuaPersistant[3]=client->sess.kills;
    client->nitmodLuaPersistant[5]=client->sess.nitmodHeadHits;
    client->nitmodLuaPersistant[6]=client->sess.nitmodBodyHits;
    client->ps.persistant[PERS_KILLED]=client->sess.deaths;

	client->ps.eFlags = flags;
	client->ps.persistant[PERS_SPAWN_COUNT] = spawn_count;
	client->ps.persistant[PERS_RESPAWNS_LEFT] = lives_left;
	

	client->pers.nitmodLastKillerClient = -1;
	client->pers.nitmodRevengeTarget = -1;
	client->pers.nitmodLastKilledClient = -1;

	client->pers.complaintClient = -1;
	client->pers.complaintEndTime = -1;

	/* Original ClientBegin 0x4e6dd resets push permission from SVF_BOT. */
	client->sess.botPush = isBot;

	// locate ent at a spawn point
	ClientSpawnContext( ent, qfalse, qtrue, restoreHealth );

	// Xian -- Changed below for team independant maxlives
	if( g_gametype.integer != GT_WOLF_LMS ) {
		if( ( client->sess.sessionTeam == TEAM_AXIS || client->sess.sessionTeam == TEAM_ALLIES ) ) {
		
			if( !client->maxlivescalced ) {
				if(g_maxlives.integer > 0) {
					client->ps.persistant[PERS_RESPAWNS_LEFT] = G_ComputeMaxLives(client, g_maxlives.integer);
				} else {
					client->ps.persistant[PERS_RESPAWNS_LEFT] = -1;
				}

				if( g_axismaxlives.integer > 0 || g_alliedmaxlives.integer > 0 ) {
					if(client->sess.sessionTeam == TEAM_AXIS) {
						client->ps.persistant[PERS_RESPAWNS_LEFT] = G_ComputeMaxLives(client, g_axismaxlives.integer);	
					} else if(client->sess.sessionTeam == TEAM_ALLIES) {
						client->ps.persistant[PERS_RESPAWNS_LEFT] = G_ComputeMaxLives(client, g_alliedmaxlives.integer);
					} else {
						client->ps.persistant[PERS_RESPAWNS_LEFT] = -1;
					}
 				}

				client->maxlivescalced = qtrue;
			} else {
				if( g_axismaxlives.integer > 0 || g_alliedmaxlives.integer > 0 ) {
					if( client->sess.sessionTeam == TEAM_AXIS ) {
						if( client->ps.persistant[ PERS_RESPAWNS_LEFT ] > g_axismaxlives.integer ) {
							client->ps.persistant[ PERS_RESPAWNS_LEFT ] = g_axismaxlives.integer;
						}
					} else if( client->sess.sessionTeam == TEAM_ALLIES ) {
						if( client->ps.persistant[ PERS_RESPAWNS_LEFT ] > g_alliedmaxlives.integer ) {
							client->ps.persistant[ PERS_RESPAWNS_LEFT ] = g_alliedmaxlives.integer;
						}
					}
 				}
			}
		}
	}	


	// DHM - Nerve :: Start players in limbo mode if they change teams during the match
	if(restoreHealth && client->sess.sessionTeam != TEAM_SPECTATOR && (level.time - level.startTime > FRAMETIME * GAME_INIT_FRAMES) ) {
/*	  if( (client->sess.sessionTeam != TEAM_SPECTATOR && (level.time - client->pers.connectTime) > 60000) ||
		( g_gamestate.integer == GS_PLAYING && ( client->sess.sessionTeam == TEAM_AXIS || client->sess.sessionTeam == TEAM_ALLIES ) && 
		 g_gametype.integer == GT_WOLF_LMS && ( level.numTeamClients[0] > 0 || level.numTeamClients[1] > 0 ) ) ) {*/
		ent->health = 0;
		ent->r.contents = CONTENTS_CORPSE;

		client->ps.pm_type = PM_DEAD;
		client->ps.stats[STAT_HEALTH] = 0;

		if( g_gametype.integer != GT_WOLF_LMS ) {
			if( g_maxlives.integer > 0 ) {
				client->ps.persistant[PERS_RESPAWNS_LEFT]++;
			}
		}

		limbo(ent, qfalse);
	}

	if(client->sess.sessionTeam != TEAM_SPECTATOR) {
		trap_SendServerCommand( -1, va("print \"[lof]%s" S_COLOR_WHITE " [lon]entered the game\n\"", client->pers.netname) );
	}

	G_LogPrintf( "ClientBegin: %i\n", clientNum );
	G_NITMOD_AccountBegin(clientNum);
	if(notifyLuaBegin) G_NITMOD_CvarScanStart(clientNum);
	if(notifyLuaBegin) G_NITMOD_LuaClientEvent("et_ClientBegin",clientNum);

	// Xian - Check for maxlives enforcement
	if( g_gametype.integer != GT_WOLF_LMS ) {
		if ( g_enforcemaxlives.integer == 1 && (g_maxlives.integer > 0 || g_axismaxlives.integer > 0 || g_alliedmaxlives.integer > 0)) {
			char *value;
			char userinfo[MAX_INFO_STRING];
			trap_GetUserinfo( clientNum, userinfo, sizeof( userinfo ) );
			value = Info_ValueForKey ( userinfo, "cl_guid" );
			G_LogPrintf( "EnforceMaxLives-GUID: %s\n", value );
			AddMaxLivesGUID( value );

			value = Info_ValueForKey (userinfo, "ip");
			G_LogPrintf( "EnforceMaxLives-IP: %s\n", value );
			AddMaxLivesBan( value );
		}
	}
	// End Xian

	// count current clients and rank for scoreboard
	CalculateRanks();
	G_NITMOD_RefreshTeamPopulation();

	// No surface determined yet.
	ent->surfaceFlags = 0;

	// OSP
	G_smvUpdateClientCSList(ent);
	// OSP
}

gentity_t *SelectSpawnPointFromList( char *list, vec3_t spawn_origin, vec3_t spawn_angles )
{
	char *pStr, *token;
	gentity_t	*spawnPoint=NULL, *trav;
	#define	MAX_SPAWNPOINTFROMLIST_POINTS	16
	int	valid[MAX_SPAWNPOINTFROMLIST_POINTS];
	int numValid;

	memset( valid, 0, sizeof(valid) );
	numValid = 0;

	pStr = list;
	while(numValid < MAX_SPAWNPOINTFROMLIST_POINTS && (token = COM_Parse( &pStr )) != NULL && token[0]) {
		trav = g_entities + level.maxclients;
		while((trav = G_FindByTargetname(trav, token)) != NULL) {
			if (!spawnPoint) spawnPoint = trav;
			if (!SpotWouldTelefrag( trav )) {
				valid[numValid++] = trav->s.number;
				if (numValid >= MAX_SPAWNPOINTFROMLIST_POINTS) {
					break;
				}
			}
		}
	}

	if (numValid)
	{
		spawnPoint = &g_entities[valid[rand()%numValid]];

		// Set the origin of where the bot will spawn
		VectorCopy (spawnPoint->r.currentOrigin, spawn_origin);
		spawn_origin[2] += 9;

		// Set the angle we'll spawn in to
		VectorCopy (spawnPoint->s.angles, spawn_angles);
	}

	return spawnPoint;
}


// TAT 1/14/2003 - init the bot's movement autonomy pos to it's current position
void BotInitMovementAutonomyPos(gentity_t *bot);

#if 0 // rain - not used
static char *G_CheckVersion( gentity_t *ent )
{
	// Prevent nasty version mismatches (or people sticking in Q3Aimbot cgames)

	char userinfo[MAX_INFO_STRING];
	char *s;

	trap_GetUserinfo( ent->s.number, userinfo, sizeof( userinfo ) );
	s = Info_ValueForKey( userinfo, "cg_etVersion" );
	if( !s || strcmp( s, GAME_VERSION_DATED ) )
		return( s );
	return( NULL );
}
#endif

/*
===========
ClientSpawn

Called every time a client is placed fresh in the world:
after the first ClientBegin, and after each respawn
Initializes all non-persistant parts of playerState
============
*/
void ClientSpawn(gentity_t *ent,qboolean revived) { ClientSpawnContext(ent,revived,qfalse,qtrue); }
static void ClientSpawnContext( gentity_t *ent, qboolean revived, qboolean teamChange, qboolean restoreHealth )
{
	int			index;
	vec3_t		spawn_origin, spawn_angles;
	gclient_t	*client;
	int			i;
	clientPersistant_t	saved;
	clientSession_t		savedSess;
	int			persistant[MAX_PERSISTANT];
	int nitmodPersistant[16];
	gentity_t	*spawnPoint;
	int			flags;
	int			savedPing;
	int			savedTeam;
	int			savedSlotNumber;
	qboolean savedSlashKillPending;
	int savedSlashKillChargeTime, savedSlashKillDeathTime;
	int savedSwitchTeamTime;
	index = ent - g_entities;
	client = ent->client;

	G_UpdateSpawnCounts();

	client->pers.lastSpawnTime = level.time;
	client->pers.lastBattleSenseBonusTime = level.timeCurrent;
	client->pers.lastHQMineReportTime = level.timeCurrent;

/*#ifndef _DEBUG
	if( !client->sess.versionOK ) {
		char *clientMismatchedVersion = G_CheckVersion( ent );	// returns NULL if version is identical

		if( clientMismatchedVersion ) {
			trap_DropClient( ent - g_entities, va( "Client/Server game mismatch: '%s/%s'", clientMismatchedVersion, GAME_VERSION_DATED ) );
		} else {
			client->sess.versionOK = qtrue;
		}
	}
#endif*/

	// find a spawn point
	// do it before setting health back up, so farthest
	// ranging doesn't count this client
	if( revived ) {
		spawnPoint = ent;
		VectorCopy( ent->r.currentOrigin, spawn_origin );
		spawn_origin[2] += 9;	// spawns seem to be sunk into ground?
		VectorCopy( ent->s.angles, spawn_angles );
	} else {
		// Arnout: let's just be sure it does the right thing at all times. (well maybe not the right thing, but at least not the bad thing!)
		//if( client->sess.sessionTeam == TEAM_SPECTATOR || client->sess.sessionTeam == TEAM_FREE ) {
		if( client->sess.sessionTeam != TEAM_AXIS && client->sess.sessionTeam != TEAM_ALLIES ) {
			spawnPoint = SelectSpectatorSpawnPoint( spawn_origin, spawn_angles );
		} else {
			// RF, if we have requested a specific spawn point, use it (fixme: what if this will place us inside another character?)
/*			spawnPoint = NULL;
			trap_GetUserinfo( ent->s.number, userinfo, sizeof(userinfo) );
			if( (str = Info_ValueForKey( userinfo, "spawnPoint" )) != NULL && str[0] ) {
				spawnPoint = SelectSpawnPointFromList( str, spawn_origin, spawn_angles );
				if (!spawnPoint) {
					G_Printf( "WARNING: unable to find spawn point \"%s\" for bot \"%s\"\n", str, ent->aiName );
				}
			}
			//
			if( !spawnPoint ) {*/
				spawnPoint = SelectCTFSpawnPoint( client->sess.sessionTeam, client->pers.teamState.state, spawn_origin, spawn_angles, client->sess.spawnObjectiveIndex, teamChange );
                if(!spawnPoint && g_gametype.integer==8 && !teamChange) return;
//			}
		}
	}

	client->pers.teamState.state = TEAM_ACTIVE;

	// toggle the teleport bit so the client knows to not lerp
	flags = ent->client->ps.eFlags & EF_TELEPORT_BIT;
	flags ^= EF_TELEPORT_BIT;
	flags |= (client->ps.eFlags & EF_VOTED);
	// clear everything but the persistant data

	ent->s.eFlags &= ~EF_MOUNTEDTANK;

	/* Original slash-kill latch is persistent; sidecar fields must survive
	 * this spawn reset until SetWolfSpawnWeapons consumes them. */
	/* Original client+0x974 lies inside the preserved persistent block. */
	savedSwitchTeamTime = client->switchTeamTime;
	savedSlashKillPending = client->nitmodSlashKillPending;
	savedSlashKillChargeTime = client->nitmodSlashKillChargeTime;
	savedSlashKillDeathTime = client->nitmodSlashKillDeathTime;
	saved			= client->pers;
	savedSess		= client->sess;
	savedPing		= client->ps.ping;
	savedTeam		= client->ps.teamNum;
	// START	xkan, 8/27/2002
	savedSlotNumber	= client->botSlotNumber;
	// END		xkan, 8/27/2002

	for( i = 0 ; i < MAX_PERSISTANT ; i++ ) {
		persistant[i] = client->ps.persistant[i];
		nitmodPersistant[i] = client->nitmodLuaPersistant[i];
	}

	{
		qboolean set = client->maxlivescalced;

		memset( client, 0, sizeof(*client) );

		client->maxlivescalced = set;
	}

	client->switchTeamTime = savedSwitchTeamTime;
	client->nitmodSlashKillPending = savedSlashKillPending;
	client->nitmodSlashKillChargeTime = savedSlashKillChargeTime;
	client->nitmodSlashKillDeathTime = savedSlashKillDeathTime;
	client->pers			= saved;
	client->sess			= savedSess;
	client->ps.ping			= savedPing;
	client->ps.teamNum		= savedTeam;
	// START	xkan, 8/27/2002
	client->botSlotNumber	= savedSlotNumber;
	// END		xkan, 8/27/2002

	for( i = 0 ; i < MAX_PERSISTANT ; i++ ) {
		client->ps.persistant[i] = persistant[i];
		client->nitmodLuaPersistant[i] = nitmodPersistant[i];
	}

	// increment the spawncount so the client will detect the respawn
	client->ps.persistant[PERS_SPAWN_COUNT]++;
	if( revived ) {
		client->ps.persistant[PERS_REVIVE_COUNT]++;
	}
	client->ps.persistant[PERS_TEAM] = client->sess.sessionTeam;
	client->ps.persistant[PERS_HWEAPON_USE] = 0;

	/* Original ClientSpawn uses the same Battle Sense reward as resurfacing. */
	client->airOutTime = NITMOD_AirDeadline( level.time,
		client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] );

	// clear entity values
	client->ps.stats[STAT_MAX_HEALTH] = client->pers.maxHealth;
	client->ps.eFlags = flags;
	// MrE: use capsules for AI and player
	//client->ps.eFlags |= EF_CAPSULE;

	ent->s.groundEntityNum = ENTITYNUM_NONE;
	ent->client = &level.clients[index];
	ent->takedamage = qtrue;
	ent->inuse = qtrue;
	if( ent->r.svFlags & SVF_BOT )
		ent->classname = "bot";
	else
		ent->classname = "player";
	ent->r.contents = CONTENTS_BODY;

	ent->clipmask = MASK_PLAYERSOLID;

	// DHM - Nerve :: Init to -1 on first spawn;
	if ( !revived )
		ent->props_frame_state = -1;

	ent->die = player_die;
	ent->waterlevel = 0;
	ent->watertype = 0;
	ent->flags = 0;
	
	VectorCopy( playerMins, ent->r.mins );
	VectorCopy( playerMaxs, ent->r.maxs );

	// Ridah, setup the bounding boxes and viewheights for prediction
	VectorCopy( ent->r.mins, client->ps.mins );
	VectorCopy( ent->r.maxs, client->ps.maxs );
	
	client->ps.crouchViewHeight = CROUCH_VIEWHEIGHT;
	client->ps.standViewHeight = DEFAULT_VIEWHEIGHT;
	client->ps.deadViewHeight = DEAD_VIEWHEIGHT;
	
	client->ps.crouchMaxZ = client->ps.maxs[2] - (client->ps.standViewHeight - client->ps.crouchViewHeight);

	client->ps.runSpeedScale = 0.8;
	client->ps.sprintSpeedScale = 1.1;
	client->ps.crouchSpeedScale = 0.25;
	client->ps.weaponstate = WEAPON_READY;

	// Rafael
	client->pmext.sprintTime = SPRINTTIME;
	client->ps.sprintExertTime = 0;

	client->ps.friction = 1.0;
	// done.

	// TTimo
	// retrieve from the persistant storage (we use this in pmoveExt_t beause we need it in bg_*)
	client->pmext.bAutoReload = client->pers.bAutoReloadAux;
	// done

	client->ps.clientNum = index;

	trap_GetUsercmd( client - level.clients, &ent->client->pers.cmd );	// NERVE - SMF - moved this up here

	// DHM - Nerve :: Add appropriate weapons
	if ( !revived ) {
		qboolean update = qfalse;
		int selected = NITMOD_SelectAvailableClass(ent, client->sess.latchPlayerType);
		if(selected < 0) {
			SetTeam(ent, "spectator", qtrue, -1, -1, qfalse);
			return;
		}
		if(selected != client->sess.latchPlayerType) update = qtrue;
		client->sess.latchPlayerType = selected;

		if( client->sess.playerType != client->sess.latchPlayerType )
			update = qtrue;

		//if ( update || client->sess.playerWeapon != client->sess.latchPlayerWeapon) {
		//	G_ExplodeMines(ent);
		//}

		client->sess.playerType = client->sess.latchPlayerType;

		if( G_IsWeaponDisabled( ent, client->sess.latchPlayerWeapon ) ) {
			bg_playerclass_t* classInfo = BG_PlayerClassForPlayerState( &ent->client->ps );
			client->sess.latchPlayerWeapon = classInfo->classWeapons[0];
			update = qtrue;
		}

		if( client->sess.playerWeapon != client->sess.latchPlayerWeapon ) {
			client->sess.playerWeapon = client->sess.latchPlayerWeapon;
			update = qtrue;
		}

		if( G_IsWeaponDisabled( ent, client->sess.playerWeapon ) ) {
			bg_playerclass_t* classInfo = BG_PlayerClassForPlayerState( &ent->client->ps );
			client->sess.playerWeapon = classInfo->classWeapons[0];
			update = qtrue;
		}

		client->sess.playerWeapon2 = client->sess.latchPlayerWeapon2;

		if( update ) {
			ClientUserinfoChanged( index );
		}
	}

	NITMOD_SetSpawnProtection(client, revived);

	G_UpdateCharacter( client );

	SetWolfSpawnWeapons( client ); 
	/* Publish the status after weapon assignment, including failed/no grant. */
	ClientUserinfoChanged( index );
	
	// START	Mad Doctor I changes, 8/17/2002

	// JPW NERVE -- increases stats[STAT_MAX_HEALTH] based on # of medics in game
	AddMedicTeamBonus( client );

	// END		Mad Doctor I changes, 8/17/2002

	if( !revived ) {
		client->pers.cmd.weapon = ent->client->ps.weapon;
	}
// dhm - end

	// JPW NERVE ***NOTE*** the following line is order-dependent and must *FOLLOW* SetWolfSpawnWeapons() in multiplayer
	// AddMedicTeamBonus() now adds medic team bonus and stores in ps.stats[STAT_MAX_HEALTH].

	ApplySpawnHealth(ent, restoreHealth, G_NITMOD_ConfiguredWarMode(),
		g_gametype.integer, G_NITMOD_ClassMaxHealth(client->sess.playerType));

	G_SetOrigin( ent, spawn_origin );
	VectorCopy( spawn_origin, client->ps.origin );

	// the respawned flag will be cleared after the attack and jump keys come up
	client->ps.pm_flags |= PMF_RESPAWNED;

	if( !revived ) {
		SetClientViewAngle( ent, spawn_angles );
	} else {
		//bani - #245 - we try to orient them in the freelook direction when revived
		vec3_t	newangle;

		newangle[YAW] = SHORT2ANGLE( ent->client->pers.cmd.angles[YAW] + ent->client->ps.delta_angles[YAW] );
		newangle[PITCH] = 0;
		newangle[ROLL] = 0;

		SetClientViewAngle( ent, newangle );
	}

	if( ent->r.svFlags & SVF_BOT ) {
		// xkan, 10/11/2002 - the ideal view angle is defaulted to 0,0,0, but the 
		// spawn_angles is the desired angle for the bots to face.
		BotSetIdealViewAngles( index, spawn_angles );

		// TAT 1/14/2003 - now that we have our position in the world, init our autonomy positions
		BotInitMovementAutonomyPos(ent);
	}

	if( ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		//G_KillBox( ent );
		trap_LinkEntity (ent);
	}

	client->respawnTime = level.timeCurrent;
	client->inactivityTime = (int)((unsigned int)level.time + (unsigned int)g_inactivity.integer * 1000u);
	client->latched_buttons = 0;
	client->latched_wbuttons = 0;	//----(SA)	added

	// xkan, 1/13/2003 - reset death time
	client->deathTime = 0;

	if ( level.intermissiontime ) {
		MoveClientToIntermission( ent );
	} else {
		// fire the targets of the spawn point
		if ( !revived )
			G_UseTargets( spawnPoint, ent );
	}

	// run a client frame to drop exactly to the floor,
	// initialize animations and other things
	G_NITMOD_LuaSpawn((int)(ent-g_entities),revived,teamChange,restoreHealth);
	client->ps.commandTime = level.time - 100;
	ent->client->pers.cmd.serverTime = level.time;
	ClientThink( ent-g_entities );

	// positively link the client, even if the command times are weird
	if ( ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );
		VectorCopy( ent->client->ps.origin, ent->r.currentOrigin );
		trap_LinkEntity( ent );
	}

	// run the presend to set anything else
	ClientEndFrame( ent );

	// set idle animation on weapon
	ent->client->ps.weapAnim = ( ( ent->client->ps.weapAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | PM_IdleAnimForWeapon( ent->client->ps.weapon );

	// clear entity state values
	BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );

	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=569
	G_ResetMarkers( ent );

	// Set up bot speed bonusses
	BotSpeedBonus( ent->s.number );

	// RF, start the scripting system
	if (!revived && client->sess.sessionTeam != TEAM_SPECTATOR) {
		Bot_ScriptInitBot( ent->s.number );
		//
		if (spawnPoint && spawnPoint->targetname) {
			Bot_ScriptEvent( ent->s.number, "spawn", spawnPoint->targetname );
		} else {
			Bot_ScriptEvent( ent->s.number, "spawn", "" );
		}
		// RF, call entity scripting event
		G_Script_ScriptEvent( ent, "playerstart", "" );
	} else if( revived && ent->r.svFlags & SVF_BOT) {
		Bot_ScriptEvent( ent->s.number, "revived", "" );
	}



}


/*
===========
ClientDisconnect

Called when a player drops from the server.
Will not be called between levels.

This should NOT be called directly by any game logic,
call trap_DropClient(), which will call this and do
server system housekeeping.
============
*/
void ClientDisconnect( int clientNum ) {
	gentity_t	*ent;
	gentity_t	*flag=NULL;
	gitem_t		*item=NULL;
	vec3_t		launchvel;
	int			i;

	G_NITMOD_CvarScanResetClient(clientNum);
	G_NITMOD_NxACResetClient(clientNum);
	G_NITMOD_NxACTransferResetClient(clientNum);
	G_NITMOD_MDXReset(&g_entities[clientNum]);
	G_NITMOD_LuaClientEvent("et_ClientDisconnect",clientNum);
	G_NITMOD_GlobalStatsUpload(clientNum);
	G_NITMOD_GlobalStatsReset(clientNum);
	Bot_Event_ClientDisConnected(clientNum);
	if(!G_NITMOD_DatabaseIsShuttingDown()) G_NITMOD_AccountSaveXP(clientNum);
	G_NITMOD_AccountReset(clientNum);
	G_NITMOD_ResetClient( clientNum );
	ent = g_entities + clientNum;
	if ( !ent->client ) {
		return;
	}

#ifdef USEXPSTORAGE
	if(NITMOD_DBUserCount()<0) G_AddXPBackup( ent );
#endif // USEXPSTORAGE

	G_RemoveClientFromFireteams( clientNum, qtrue, qfalse );
	G_RemoveFromAllIgnoreLists( clientNum );
	G_LeaveTank( ent, qfalse, qfalse );

	// stop any following clients
	for ( i = 0 ; i < level.numConnectedClients ; i++ ) {
		flag = g_entities + level.sortedClients[i];
		if ( flag->client->sess.sessionTeam == TEAM_SPECTATOR
			&& flag->client->sess.spectatorState == SPECTATOR_FOLLOW
			&& flag->client->sess.spectatorClient == clientNum ) {
			StopFollowing( flag );
		}
		if ( flag->client->ps.pm_flags & PMF_LIMBO
			&& flag->client->sess.spectatorClient == clientNum ) {
			Cmd_FollowCycle_f( flag, 1 );
		}
	}

	// NERVE - SMF - remove complaint client
	for ( i = 0 ; i < level.numConnectedClients ; i++ ) {
		if ( flag->client->pers.complaintEndTime > level.time && flag->client->pers.complaintClient == clientNum ) {
			flag->client->pers.complaintClient = -1;
			flag->client->pers.complaintEndTime = -1;

			CPx( level.sortedClients[i], "complaint -2" );
			break;
		}
	}

	if( g_landminetimeout.integer ) {
		G_ExplodeMines(ent);
	}
	if(G_NITMOD_LegacyCvarInteger("n_tripmineTimeout", 1)) {
		G_NITMOD_RemoveTripmines(ent);
	}
	G_FadeItems(ent, MOD_SATCHEL);
	G_NITMOD_FadeDisconnectProjectiles(ent, G_NITMOD_LegacyCvarInteger("g_missileCams", 0));

	// remove ourself from teamlists
	{
		mapEntityData_t	*mEnt;
		mapEntityData_Team_t *teamList;

		for( i = 0; i < 2; i++ ) {
			teamList = &mapEntityData[i];

			if((mEnt = G_FindMapEntityData(&mapEntityData[0], ent-g_entities)) != NULL) {
				G_FreeMapEntityData( teamList, mEnt );
			}

			mEnt = G_FindMapEntityDataSingleClient( teamList, NULL, ent->s.number, -1 );
			
			while( mEnt ) {
				mapEntityData_t	*mEntFree = mEnt;

				mEnt = G_FindMapEntityDataSingleClient( teamList, mEnt, ent->s.number, -1 );

				G_FreeMapEntityData( teamList, mEntFree );
			}
		}
	}

	// send effect if they were completely connected
	if ( ent->client->pers.connected == CON_CONNECTED 
		&& ent->client->sess.sessionTeam != TEAM_SPECTATOR
		&& !(ent->client->ps.pm_flags & PMF_LIMBO) ) {

		// They don't get to take powerups with them!
		// Especially important for stuff like CTF flags
		TossClientItems( ent );

		// New code for tossing flags
			if (ent->client->ps.powerups[PW_REDFLAG]) {
				item = BG_FindItem("Red Flag");
				if (!item)
					item = BG_FindItem("Objective");

				ent->client->ps.powerups[PW_REDFLAG] = 0;
			}
			if (ent->client->ps.powerups[PW_BLUEFLAG]) {
				item = BG_FindItem("Blue Flag");
				if (!item)
					item = BG_FindItem("Objective");

				ent->client->ps.powerups[PW_BLUEFLAG] = 0;
			}

			if( item ) {
				// OSP - fix for suicide drop exploit through walls/gates
				launchvel[0] = 0;//crandom()*20;
				launchvel[1] = 0;//crandom()*20;
				launchvel[2] = 0;//10+random()*10;

				flag = LaunchItem(item,ent->r.currentOrigin,launchvel,ent-g_entities);
				flag->s.modelindex2 = ent->s.otherEntityNum2;// JPW NERVE FIXME set player->otherentitynum2 with old modelindex2 from flag and restore here
				flag->message = ent->message;	// DHM - Nerve :: also restore item name
				// Clear out player's temp copies
				ent->s.otherEntityNum2 = 0;
				ent->message = NULL;
			}

		// OSP - Log stats too
		G_LogPrintf("WeaponStats: %s\n", G_createStats(ent));
	}

	G_LogPrintf( "ClientDisconnect: %i\n", clientNum );

	trap_UnlinkEntity (ent);
	ent->s.modelindex = 0;
	ent->inuse = qfalse;
	ent->classname = "disconnected";
	ent->client->pers.connected = CON_DISCONNECTED;
	ent->client->ps.persistant[PERS_TEAM] = TEAM_FREE;
	i = ent->client->sess.sessionTeam;
	ent->client->sess.sessionTeam = TEAM_FREE;
	ent->active = 0;

	trap_SetConfigstring( CS_PLAYERS + clientNum, "");


	CalculateRanks();
	G_NITMOD_RefreshTeamPopulation();

	if ((ent->r.svFlags & SVF_BOT) &&
		!G_NITMOD_LegacyCvarInteger("omnibot_enable", 0)) {
		BotAIShutdownClient( clientNum );
	}

	// OSP
	G_verifyMatchState(i);
	G_smvAllRemoveSingleClient(ent - g_entities);
	// OSP
}

// In just the GAME DLL, we want to store the groundtrace surface stuff,
// so we don't have to keep tracing.
void ClientStoreSurfaceFlags
( 
	int clientNum, 
	int surfaceFlags
)
{
	// Store the surface flags
	g_entities[clientNum].surfaceFlags = surfaceFlags;

}
