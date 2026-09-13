#include "g_local.h"
#include "g_nitmod_mdx.h"
#include "g_nitmod_hitboxdebug.h"
#include "g_nitmod_legacy_cvars.h"

/* Original G_AntilagSafe / G_ReAdjustSingleClientPosition 0x451b0. */
static qboolean G_NITMOD_AntilagSafe(gentity_t *ent) {
 if(!ent || !ent->inuse || !ent->r.linked || !ent->client ||
  (ent->client->sess.sessionTeam!=TEAM_AXIS && ent->client->sess.sessionTeam!=TEAM_ALLIES) ||
  (ent->client->ps.pm_flags&PMF_LIMBO)) return qfalse;
 if(ent->client->backupMarker.time==level.time && ent->client->ps.pm_type==PM_DEAD)
  return G_NITMOD_LegacyCvarInteger("g_realHead",0)!=0;
 return ent->health>0 && ent->client->ps.pm_type==PM_NORMAL &&
  !(ent->client->ps.eFlags&EF_MOUNTEDTANK);
}

void G_StoreClientPosition( gentity_t* ent ) {
	int	top;

	if(!G_NITMOD_AntilagSafe(ent)) return;

	ent->client->topMarker++;
	if( ent->client->topMarker >= MAX_CLIENT_MARKERS ) {
		ent->client->topMarker = 0;
	}

	top = ent->client->topMarker;

	VectorCopy( ent->r.mins, ent->client->clientMarkers[top].mins );
	VectorCopy( ent->r.maxs, ent->client->clientMarkers[top].maxs );
	VectorCopy( ent->s.pos.trBase, ent->client->clientMarkers[top].origin );
	ent->client->clientMarkers[top].time = level.time;
	G_NITMOD_MDXStoreMarker(ent,top);
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

	G_NITMOD_MDXRewind(ent,i==ent->client->topMarker?j:i,j,time);
	trap_LinkEntity( ent );
}

static void G_ReAdjustSingleClientPosition( gentity_t* ent ) {
	if(!G_NITMOD_AntilagSafe(ent)) {
		return;
	}

	// restore from backup
	if( ent->client->backupMarker.time == level.time ) {
		VectorCopy( ent->client->backupMarker.origin, ent->r.currentOrigin );
		VectorCopy( ent->client->backupMarker.mins, ent->r.mins );
		VectorCopy( ent->client->backupMarker.maxs, ent->r.maxs );
		ent->client->backupMarker.time = 0;
		G_NITMOD_MDXRestore(ent);

		trap_LinkEntity( ent );
	}
}

void G_AdjustClientPositions( gentity_t* ent, int time, qboolean forward ) {
	int	i;
	gentity_t	*list;

	for( i = 0; i < level.numConnectedClients; i++, list++ ) {
		list = g_entities + level.sortedClients[i];
		if(list != ent && G_NITMOD_AntilagSafe(list)) {
			if( forward ) {
				G_AdjustSingleClientPosition( list, time );
			} else {
				G_ReAdjustSingleClientPosition( list );
			}
		}
	}
}

void G_ResetMarkers( gentity_t* ent ) {
	int i;

	/* Original G_ResetMarkers 0x45740 initializes all 17 times to zero. */
	ent->client->topMarker = MAX_CLIENT_MARKERS - 1;
	for( i = MAX_CLIENT_MARKERS - 1; i >= 0; i-- ) {
		VectorCopy( ent->r.mins, ent->client->clientMarkers[i].mins );
		VectorCopy( ent->r.maxs, ent->client->clientMarkers[i].maxs );
		VectorCopy( ent->r.currentOrigin, ent->client->clientMarkers[i].origin );
		ent->client->clientMarkers[i].time = 0;
		G_NITMOD_MDXInitializeMarker(ent,i);
	}
	G_NITMOD_MDXFinishMarkerReset(ent);
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
			(list->client->sess.sessionTeam != TEAM_SPECTATOR) &&
 			(list != ent) &&
 			list->r.linked &&
			!(list->client->ps.pm_flags & PMF_LIMBO) &&
			(list->client->ps.pm_type == PM_NORMAL || list->client->ps.pm_type == PM_DEAD)
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
			if (g_antilag.integer & 2) G_NITMOD_DrawAttachedHitboxes(list);
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

/* Original DetectHitZone: recover the temporary part before detachment. */
static void G_NITMOD_HistoricalRegion(gentity_t *attacker,trace_t *result,
 const vec3_t start,const vec3_t end) {
 gentity_t *part=&g_entities[result->entityNum];
 int targetNum=G_SwitchBodyPartEntity(part),region=HR_BODY;
 gentity_t *target=&g_entities[targetNum];
 trace_t detail;
 G_NITMOD_MDXEndDamage();
 attacker->nitmodLastTraceRegion=-1;
 if(!target->client) return;
 if(part->s.eType==ET_TEMPHEAD) region=HR_HEAD;
 else if(part->s.eType==ET_TEMPLEGS) region=HR_LEGS;
 else {
  trap_Trace(&detail,start,NULL,NULL,end,targetNum,MASK_SHOT);
  part=&g_entities[detail.entityNum];
  if(part->parent==target) {
   if(part->s.eType==ET_TEMPHEAD) region=HR_HEAD;
   else if(part->s.eType==ET_TEMPLEGS) region=HR_LEGS;
  }
 }
 attacker->nitmodLastTraceRegion=region;
 G_NITMOD_MDXBeginDamage(attacker,target,region);
}

// Run a trace with players in historical positions.
void G_HistoricalTrace( gentity_t* ent, trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask, qboolean recordRegion ) {
	int res, i;
	vec3_t dir;

	/* Original G_HistoricalTrace resets the region and ignores corpses. */
	ent->nitmodLastTraceRegion = -1;
	G_NITMOD_MDXEndDamage();
	for(i = 0; i < BODY_QUEUE_SIZE; ++i)
		if(level.bodyQue[i]) G_TempTraceIgnoreEntity(level.bodyQue[i]);

	if( !(g_antilag.integer & 1) || !ent->client ) {
		G_AttachBodyParts( ent );

		trap_Trace( results, start, mins, maxs, end, passEntityNum, contentmask );

		if(recordRegion) G_NITMOD_HistoricalRegion(ent,results,start,end);
		res = G_SwitchBodyPartEntity( &g_entities[ results->entityNum ] );
		POSITION_READJUST

		G_DettachBodyParts();
		G_ResetTempTraceIgnoreEnts();
		return;
	}

	G_AdjustClientPositions( ent, ent->client->pers.cmd.serverTime, qtrue );

	G_AttachBodyParts( ent ) ;

	trap_Trace( results, start, mins, maxs, end, passEntityNum, contentmask );

	if(recordRegion) G_NITMOD_HistoricalRegion(ent,results,start,end);
	res = G_SwitchBodyPartEntity( &g_entities[ results->entityNum ] );
	POSITION_READJUST

	G_DettachBodyParts();
	G_ResetTempTraceIgnoreEnts();

	G_AdjustClientPositions( ent, 0, qfalse );
}

void G_HistoricalTraceBegin( gentity_t *ent ) {
	if(!g_antilag.integer || !ent || !ent->client) return;
	G_AdjustClientPositions( ent, ent->client->pers.cmd.serverTime, qtrue );
}

void G_HistoricalTraceEnd( gentity_t *ent ) {
	G_AdjustClientPositions( ent, 0, qfalse );
}

//bani - Run a trace without fixups (historical fixups will be done externally)
void G_Trace( gentity_t* ent, trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask, qboolean recordRegion ) {
	int res;
	vec3_t dir;

	G_AttachBodyParts( ent );

	trap_Trace( results, start, mins, maxs, end, passEntityNum, contentmask );

	if(recordRegion) G_NITMOD_HistoricalRegion(ent,results,start,end);
	res = G_SwitchBodyPartEntity( &g_entities[ results->entityNum ] );
	POSITION_READJUST

	G_DettachBodyParts();
}
