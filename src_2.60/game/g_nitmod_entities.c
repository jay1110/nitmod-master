#include "g_local.h"
#include "nitmod_support_time.h"
#include "g_nitmod_entities.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_entity_array.h"

/* Engine owns the entities. Registration order matches the original list;
 * a reused entity slot must be removed before it acquires a new owner. */
static nitmodEntityArray_t satchels;
static nitmodEntityArray_t landmines;
static nitmodEntityArray_t airstrikes;
static nitmodEntityArray_t mg42s;

static void G_NITMOD_ArtilleryHintThink( gentity_t *hint ) {
	int i;

	if( hint->count ) {
		G_FreeEntity( hint );
		return;
	}
	for( i = 0; i < level.num_entities; ++i ) {
		gentity_t *shell = &g_entities[i];
		if( shell->inuse && shell->s.eType == ET_MISSILE && shell->s.weapon == WP_ARTY &&
			shell->parent == hint->parent && shell->s.pos.trTime == hint->s.pos.trTime ) {
			hint->nextthink = NITMOD_SupportSignedTime((uint32_t)level.time + UINT32_C(1000));
			return;
		}
	}
	/* Preserve the original one-second terminal state before unlink/free so
	 * every snapshot observes a clean end to the marker's lifetime. */
	hint->count = 1;
	hint->nextthink = NITMOD_SupportSignedTime((uint32_t)level.time + UINT32_C(1000));
}

void G_NITMOD_SpawnArtilleryHint( gentity_t *shell ) {
	gentity_t *hint;

	if( !shell || !shell->parent ||
		G_NITMOD_LegacyCvarInteger( "g_artilleryHints", 1 ) != 1 ) {
		return;
	}
	hint = G_Spawn();
	hint->classname = "arty_hint";
	hint->s.eType = ET_LANDMINESPOT_HINT; /* original Nitmod wire type 58 */
	hint->s.teamNum = shell->parent->client ?
		shell->parent->client->sess.sessionTeam : shell->s.teamNum;
	hint->s.pos.trType = TR_STATIONARY;
	hint->s.pos.trTime = shell->s.pos.trTime;
	VectorCopy( shell->s.pos.trBase, hint->s.pos.trBase );
	VectorCopy( shell->s.pos.trBase, hint->r.currentOrigin );
	hint->parent = shell->parent;
	hint->r.ownerNum = shell->parent->s.number;
	hint->s.clientNum = shell->parent->s.number;
	hint->clipmask = MASK_MISSILESHOT;
	hint->r.svFlags = SVF_BROADCAST;
	hint->think = G_NITMOD_ArtilleryHintThink;
	hint->nextthink = NITMOD_SupportSignedTime((uint32_t)level.time + UINT32_C(1));
	trap_LinkEntity( hint );
}

int G_NITMOD_ExplodeSatchels( gentity_t *owner, nitmodEntityRelease_t explode ) {
	struct {
		gentity_t *entity;
		int generation;
	} pending[NITMOD_ENTITY_ARRAY_CAPACITY];
	int count, index, member;
	int exploded = 0;
	if( !owner || !explode ) {
		return 0;
	}
	count = satchels.count;
	for( index = 0; index < count; index++ ) {
		pending[index].entity = satchels.entities[index];
		pending[index].generation = satchels.entities[index]->spawnCount;
	}
	for( index = 0; index < count; index++ ) {
		gentity_t *entity = pending[index].entity;
		float dx, dy, dz, distanceSquared;
		/* A previous blast can free, transfer or replace another candidate. */
		if( !entity->inuse || entity->spawnCount != pending[index].generation ||
			entity->parent != owner || entity->s.eType != ET_MISSILE ||
			entity->methodOfDeath != MOD_SATCHEL ) {
			continue;
		}
		for( member = 0; member < satchels.count; member++ ) {
			if( satchels.entities[member] == entity ) break;
		}
		if( member == satchels.count ) continue;
		dx = entity->r.currentOrigin[0] - owner->r.currentOrigin[0];
		dy = entity->r.currentOrigin[1] - owner->r.currentOrigin[1];
		dz = entity->r.currentOrigin[2] - owner->r.currentOrigin[2];
		distanceSquared = dx * dx + dy * dy + dz * dz;
		/* Inclusive reference range; the positive comparison also rejects NaN. */
		if( distanceSquared <= 2000.0f * 2000.0f ) {
			explode( entity );
			exploded++;
		}
	}
	return exploded;
}

static void G_NITMOD_FadeOwned( nitmodEntityArray_t *list, gentity_t *owner,
	nitmodEntityRelease_t release, qboolean requireInuse ) {
	int index;
	if( !owner || !release ) {
		return;
	}
	/* Reverse traversal preserves every match when removal compacts the list. */
	for( index = list->count - 1; index >= 0; index-- ) {
		gentity_t *entity = list->entities[index];
		if( entity->parent != owner || ( requireInuse && !entity->inuse ) ) {
			continue;
		}
		entity->parent = NULL;
		entity->r.ownerNum = ENTITYNUM_NONE;
		NITMOD_RemoveEntityFromArray( list, entity );
		release( entity );
	}
}

void G_NITMOD_FadeLandmines( gentity_t *owner, nitmodEntityRelease_t release ) {
	G_NITMOD_FadeOwned( &landmines, owner, release, qtrue );
}

void G_NITMOD_FadeSatchels( gentity_t *owner, nitmodEntityRelease_t release ) {
	G_NITMOD_FadeOwned( &satchels, owner, release, qfalse );
}

void G_NITMOD_FadeAirstrikes( gentity_t *owner, nitmodEntityRelease_t release ) {
	G_NITMOD_FadeOwned( &airstrikes, owner, release, qtrue );
}

void G_NITMOD_ResetEntityLists( void ) {
	NITMOD_InitEntityArray( &mg42s );
	NITMOD_InitEntityArray( &satchels );
	NITMOD_InitEntityArray( &landmines );
	NITMOD_InitEntityArray( &airstrikes );
}

void G_NITMOD_RegisterMG42( gentity_t *entity ) {
	nitmodEntityArrayResult_t result = NITMOD_AddEntityToArray( &mg42s, entity );
	if( result == NITMOD_ENTITY_ARRAY_FULL ) G_Error( "Entity Array Overflow" );
	else if( result == NITMOD_ENTITY_ARRAY_INVALID ) G_Error( "Invalid MG42 entity array" );
}

void G_NITMOD_UnregisterMG42( gentity_t *entity ) {
	if( NITMOD_RemoveEntityFromArray( &mg42s, entity ) == NITMOD_ENTITY_ARRAY_INVALID )
		G_Error( "Invalid MG42 entity array" );
}

gentity_t *G_NITMOD_MG42At( int index ) {
	return index >= 0 && index < mg42s.count ? mg42s.entities[index] : NULL;
}

void G_NITMOD_RegisterLandmine( gentity_t *entity ) {
	nitmodEntityArrayResult_t result;
	if( !entity ) {
		G_Error( "NULL landmine entity" );
		return;
	}
	result = NITMOD_AddEntityToArray( &landmines, entity );
	if( result == NITMOD_ENTITY_ARRAY_FULL ) {
		G_Error( "Entity Array Overflow" );
	} else if( result == NITMOD_ENTITY_ARRAY_INVALID ) {
		G_Error( "Invalid landmine entity array" );
	}
}

void G_NITMOD_UnregisterLandmine( gentity_t *entity ) {
	if( NITMOD_RemoveEntityFromArray( &landmines, entity ) == NITMOD_ENTITY_ARRAY_INVALID ) {
		G_Error( "Invalid landmine entity array" );
	}
}

gentity_t *G_NITMOD_LandmineAt( int index ) {
	return index >= 0 && index < landmines.count ? landmines.entities[index] : NULL;
}

int G_NITMOD_CountTeamLandmines( int team, int maximum ) {
	int index;
	int count = 0;
	for( index = 0; index < landmines.count; index++ ) {
		const gentity_t *entity = landmines.entities[index];
		/* team + 4 is unarmed. Read live state across arming/team changes. */
		if( entity->s.teamNum % 4 == team && entity->s.teamNum < 4 ) {
			count++;
		}
	}
	return count > maximum ? maximum : count;
}

void G_NITMOD_RegisterSatchel( gentity_t *entity ) {
	nitmodEntityArrayResult_t result;
	if( !entity ) {
		G_Error( "NULL satchel entity" );
		return;
	}
	result = NITMOD_AddEntityToArray( &satchels, entity );
	if( result == NITMOD_ENTITY_ARRAY_FULL ) {
		G_Error( "Entity Array Overflow" );
	} else if( result == NITMOD_ENTITY_ARRAY_INVALID ) {
		G_Error( "Invalid satchel entity array" );
	}
}

void G_NITMOD_UnregisterSatchel( gentity_t *entity ) {
	/* Unconditional removal also covers entities already changed to events. */
	if( NITMOD_RemoveEntityFromArray( &satchels, entity ) == NITMOD_ENTITY_ARRAY_INVALID ) {
		G_Error( "Invalid satchel entity array" );
	}
}

/* Original airstrike list contains both thrown markers and scheduled bombs.
 * Register/free bookkeeping prevents a reused entity slot retaining ownership. */
void G_NITMOD_RegisterAirstrike( gentity_t *entity ) {
    nitmodEntityArrayResult_t result;
    if( !entity ) { G_Error( "NULL airstrike entity" ); return; }
    result = NITMOD_AddEntityToArray( &airstrikes, entity );
    if( result == NITMOD_ENTITY_ARRAY_FULL ) G_Error( "Entity Array Overflow" );
    else if( result == NITMOD_ENTITY_ARRAY_INVALID ) G_Error( "Invalid airstrike entity array" );
}

void G_NITMOD_UnregisterAirstrike( gentity_t *entity ) {
    if( NITMOD_RemoveEntityFromArray( &airstrikes, entity ) == NITMOD_ENTITY_ARRAY_INVALID ) {
        G_Error( "Invalid airstrike entity array" );
    }
}

gentity_t *G_NITMOD_FindSatchel( const gentity_t *owner ) {
	int index;
	for( index = 0; index < satchels.count; index++ ) {
		gentity_t *entity = satchels.entities[index];
		if( entity->parent == owner ) {
			return entity;
		}
	}
	return NULL;
}
