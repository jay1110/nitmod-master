#include "g_local.h"
#include "g_nitmod_legacy_cvars.h"

void G_StoreClientPosition( gentity_t* ent ) {
	int	top;

	if(!( ent->inuse && 
 		(ent->client->sess.sessionTeam == TEAM_AXIS || ent->client->sess.sessionTeam == TEAM_ALLIES) && 
 		ent->r.linked &&
 		(ent->health > 0) &&
 		!(ent->client->ps.pm_flags & PMF_LIMBO) &&
		(ent->client->ps.pm_type == PM_NORMAL)
 	)) {
		return;
	}

	ent->client->topMarker++;
	if( ent->client->topMarker >= MAX_CLIENT_MARKERS ) {
		ent->client->topMarker = 0;
	}

	top = ent->client->topMarker;

	VectorCopy( ent->r.mins, ent->client->clientMarkers[top].mins );
	VectorCopy( ent->r.maxs, ent->client->clientMarkers[top].maxs );
	VectorCopy( ent->s.pos.trBase, ent->client->clientMarkers[top].origin );
	ent->client->clientMarkers[top].time = level.time;
}

static void G_AdjustSingleClientPosition( gentity_t* ent, int time ) {
	int	i, j;

	if( time > level.time ) {
		time = level.time;
	} // no lerping forward....

	// find a pair of markers which bound the requested time
	i = j = ent->client->topMarker;
	do {
		if( ent->client->clientMarkers[i].time <= time ) {
			break;
		}

		j = i;
		i--;
		if( i < 0 ) {
			i = MAX_CLIENT_MARKERS - 1;
		}
	} while( i != ent->client->topMarker );

	if( i == j ) { // oops, no valid stored markers
		return;
	}

	// save current position to backup
	if( ent->client->backupMarker.time != level.time ) {
		VectorCopy( ent->r.currentOrigin, ent->client->backupMarker.origin );
		VectorCopy( ent->r.mins, ent->client->backupMarker.mins );
		VectorCopy( ent->r.maxs, ent->client->backupMarker.maxs );
		ent->client->backupMarker.time = level.time;
	}

	if( i != ent->client->topMarker ) {
		float frac = (float)(time - ent->client->clientMarkers[i].time) /
			(float)(ent->client->clientMarkers[j].time - ent->client->clientMarkers[i].time);

		LerpPosition( ent->client->clientMarkers[i].origin, ent->client->clientMarkers[j].origin, frac,	ent->r.currentOrigin );
		LerpPosition( ent->client->clientMarkers[i].mins, ent->client->clientMarkers[j].mins, frac, ent->r.mins );
		LerpPosition( ent->client->clientMarkers[i].maxs, ent->client->clientMarkers[j].maxs, frac, ent->r.maxs );
	} else {
		VectorCopy( ent->client->clientMarkers[j].origin, ent->r.currentOrigin );
		VectorCopy( ent->client->clientMarkers[j].mins,	ent->r.mins );
		VectorCopy( ent->client->clientMarkers[j].maxs,	ent->r.maxs );
	}

	trap_LinkEntity( ent );
}

static void G_ReAdjustSingleClientPosition( gentity_t* ent ) {
	if( !ent || !ent->client ) {
		return;
	}

	// restore from backup
	if( ent->client->backupMarker.time == level.time ) {
		VectorCopy( ent->client->backupMarker.origin, ent->r.currentOrigin );
		VectorCopy( ent->client->backupMarker.mins, ent->r.mins );
		VectorCopy( ent->client->backupMarker.maxs, ent->r.maxs );
		ent->client->backupMarker.time = 0;

		trap_LinkEntity( ent );
	}
}

void G_AdjustClientPositions( gentity_t* ent, int time, qboolean forward ) {
	int	i;
	gentity_t	*list;

	for( i = 0; i < level.numConnectedClients; i++, list++ ) {
		list = g_entities + level.sortedClients[i];
		// Gordon: ok lets test everything under the sun
 		if( list->client && 
 			list->inuse && 
 			(list->client->sess.sessionTeam == TEAM_AXIS || list->client->sess.sessionTeam == TEAM_ALLIES) && 
 			(list != ent) &&
 			list->r.linked &&
 			(list->health > 0) &&
 			!(list->client->ps.pm_flags & PMF_LIMBO) &&
			(list->client->ps.pm_type == PM_NORMAL)
 		) {
			if( forward ) {
				G_AdjustSingleClientPosition( list, time );
			} else {
				G_ReAdjustSingleClientPosition( list );
			}
		}
	}
}

void G_ResetMarkers( gentity_t* ent ) {
	int	i, time;
	char	buffer[ MAX_CVAR_VALUE_STRING ];
	float	period;

	trap_Cvar_VariableStringBuffer( "sv_fps", buffer, sizeof( buffer ) - 1 );

	period = atoi( buffer );
	if( !period ) {
		period = 50;
	} else {
		period = 1000.f / period;
	}

	ent->client->topMarker = MAX_CLIENT_MARKERS - 1;
	for( i = MAX_CLIENT_MARKERS - 1, time = level.time; i >= 0; i--, time -= period ) {
		VectorCopy( ent->r.mins, ent->client->clientMarkers[i].mins );
		VectorCopy( ent->r.maxs, ent->client->clientMarkers[i].maxs );
		VectorCopy( ent->r.currentOrigin, ent->client->clientMarkers[i].origin );
		ent->client->clientMarkers[i].time = time;
	}
}

/* Recovered nitrox_HitboxHeight (qagame 0x0010f460). */
float G_NITMOD_HitboxHeight( const gentity_t *target, const gentity_t *attacker ) {
	int realBody;
	int flags;

	if ( !target ) return 0.0f;
	if ( !target->client ) return target->r.maxs[2];

	realBody = G_NITMOD_LegacyCvarInteger( "g_realBody", 0 );
	flags = target->client->ps.eFlags;
	if ( !( flags & ( EF_DEAD | EF_PRONE | EF_SPARE0 ) ) ) {
		if ( !( flags & EF_CROUCHING ) )
			return ( realBody & 2 ) ? 36.0f : 48.0f;
		if ( realBody & 8 ) return 18.0f;
	} else {
		if ( attacker && attacker->client &&
			( attacker->s.weapon == WP_POISON_SYRINGE ||
			  attacker->s.weapon == WP_MEDIC_SYRINGE ||
			  attacker->s.weapon == WP_KNIFE ) )
			return 32.0f;
		if ( ( realBody & 4 ) ||
			G_NITMOD_LegacyCvarInteger( "g_hitboxes", 0 ) )
			return 4.0f;
	}
	return 24.0f;
}

void G_AttachBodyParts(gentity_t* ent) {
	int	i;
	gentity_t	*list;

	for( i = 0; i < level.numConnectedClients; i++, list++ ) {
		list = g_entities + level.sortedClients[i];
		// Gordon: ok lets test everything under the sun
	 	if( list->inuse && 
 			(list->client->sess.sessionTeam == TEAM_AXIS || list->client->sess.sessionTeam == TEAM_ALLIES) && 
 			(list != ent) &&
 			list->r.linked &&
 			(list->health > 0) &&
 			!(list->client->ps.pm_flags & PMF_LIMBO) &&
			(list->client->ps.pm_type == PM_NORMAL)
		) {
			list->client->tempHead = G_BuildHead( list );
			list->client->tempLeg = G_BuildLeg( list );
			VectorCopy( list->r.mins, list->client->nitmodSavedBodyMins );
			VectorCopy( list->r.maxs, list->client->nitmodSavedBodyMaxs );
			list->client->nitmodBodyBoundsAdjusted = qtrue;
			if ( G_NITMOD_LegacyCvarInteger( "g_realBody", 0 ) & 1 ) {
				list->r.mins[0] += 3.0f;
				list->r.mins[1] += 3.0f;
				list->r.maxs[0] -= 3.0f;
				list->r.maxs[1] -= 3.0f;
			}
			list->r.maxs[2] = G_NITMOD_HitboxHeight( list, ent );
		} else {
			list->client->tempHead = NULL;
			list->client->tempLeg = NULL;
			list->client->nitmodBodyBoundsAdjusted = qfalse;
		}
	}
}

void G_DettachBodyParts() {
	int			i;
	gentity_t	*list;

	for( i = 0; i < level.numConnectedClients; i++, list++ ) {
		list = g_entities + level.sortedClients[i];
		if( list->client->tempHead ) {
			G_FreeEntity( list->client->tempHead );
		}
		if( list->client->tempLeg ) {
			G_FreeEntity( list->client->tempLeg );
		}
		if ( list->client->nitmodBodyBoundsAdjusted ) {
			VectorCopy( list->client->nitmodSavedBodyMins, list->r.mins );
			VectorCopy( list->client->nitmodSavedBodyMaxs, list->r.maxs );
			list->client->nitmodBodyBoundsAdjusted = qfalse;
		}
	}
}

int G_SwitchBodyPartEntity(gentity_t* ent) {
	if( ent->s.eType == ET_TEMPHEAD ) {
		return ent->parent-g_entities;
	}
	if( ent->s.eType == ET_TEMPLEGS ) {
		return ent->parent-g_entities;
	}
	return ent-g_entities;
}

#define POSITION_READJUST						\
	if( res != results->entityNum ) {				\
		VectorSubtract( end, start, dir );			\
		VectorNormalizeFast( dir );				\
									\
		VectorMA( results->endpos, -1, dir, results->endpos );	\
		results->entityNum = res;				\
	}

// Run a trace with players in historical positions.
void G_HistoricalTrace( gentity_t* ent, trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask ) {
	int res;
	vec3_t dir;

	if( !g_antilag.integer || !ent->client ) {
		G_AttachBodyParts( ent );

		trap_Trace( results, start, mins, maxs, end, passEntityNum, contentmask );

		res = G_SwitchBodyPartEntity( &g_entities[ results->entityNum ] );
		POSITION_READJUST

		G_DettachBodyParts();
		return;
	}

	G_AdjustClientPositions( ent, ent->client->pers.cmd.serverTime, qtrue );

	G_AttachBodyParts( ent ) ;

	trap_Trace( results, start, mins, maxs, end, passEntityNum, contentmask );

	res = G_SwitchBodyPartEntity( &g_entities[ results->entityNum ] );
	POSITION_READJUST

	G_DettachBodyParts();

	G_AdjustClientPositions( ent, 0, qfalse );
}

void G_HistoricalTraceBegin( gentity_t *ent ) {
	G_AdjustClientPositions( ent, ent->client->pers.cmd.serverTime, qtrue );
}

void G_HistoricalTraceEnd( gentity_t *ent ) {
	G_AdjustClientPositions( ent, 0, qfalse );
}

//bani - Run a trace without fixups (historical fixups will be done externally)
void G_Trace( gentity_t* ent, trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask ) {
	int res;
	vec3_t dir;

	G_AttachBodyParts( ent );

	trap_Trace( results, start, mins, maxs, end, passEntityNum, contentmask );

	res = G_SwitchBodyPartEntity( &g_entities[ results->entityNum ] );
	POSITION_READJUST

	G_DettachBodyParts();
}
