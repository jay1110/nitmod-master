#include <string.h>
#include "nitmod_entity_array.h"

void NITMOD_InitEntityArray( nitmodEntityArray_t *array ) {
	if( array ) {
		array->count = 0;
	}
}

static int NITMOD_ValidEntityArray( const nitmodEntityArray_t *array ) {
	return array && array->count >= 0 && array->count <= NITMOD_ENTITY_ARRAY_CAPACITY;
}

nitmodEntityArrayResult_t NITMOD_AddEntityToArray( nitmodEntityArray_t *array, struct gentity_s *entity ) {
	int index;
	if( !NITMOD_ValidEntityArray( array ) ) {
		return NITMOD_ENTITY_ARRAY_INVALID;
	}
	if( array->count == NITMOD_ENTITY_ARRAY_CAPACITY ) {
		return NITMOD_ENTITY_ARRAY_FULL;
	}
	for( index = 0; index < array->count; index++ ) {
		if( array->entities[index] == entity ) {
			return NITMOD_ENTITY_ARRAY_UNCHANGED;
		}
	}
	array->entities[array->count++] = entity;
	return NITMOD_ENTITY_ARRAY_CHANGED;
}

nitmodEntityArrayResult_t NITMOD_RemoveEntityFromArray( nitmodEntityArray_t *array, struct gentity_s *entity ) {
	int index;
	if( !NITMOD_ValidEntityArray( array ) ) {
		return NITMOD_ENTITY_ARRAY_INVALID;
	}
	for( index = 0; index < array->count; index++ ) {
		if( array->entities[index] == entity ) {
			if( index + 1 < array->count ) {
				memmove( &array->entities[index], &array->entities[index + 1],
					(array->count - index - 1) * sizeof(array->entities[0]) );
			}
			array->count--;
			return NITMOD_ENTITY_ARRAY_CHANGED;
		}
	}
	return NITMOD_ENTITY_ARRAY_UNCHANGED;
}
