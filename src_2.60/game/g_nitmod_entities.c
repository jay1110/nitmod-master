#include "g_local.h"
#include "g_nitmod_entities.h"
#include "nitmod_entity_array.h"

/* Engine owns the entities. Registration order matches the original list;
 * a reused entity slot must be removed before it acquires a new owner. */
static nitmodEntityArray_t satchels;
static nitmodEntityArray_t landmines;

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

void G_NITMOD_ResetEntityLists( void ) {
	NITMOD_InitEntityArray( &satchels );
	NITMOD_InitEntityArray( &landmines );
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
