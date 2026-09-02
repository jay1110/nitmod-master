#ifndef NITMOD_ENTITY_ARRAY_H
#define NITMOD_ENTITY_ARRAY_H

/* nitrox_*EntityArray, qagame nitmod_core.c:2350-2408.
 * Entries borrow engine-owned entities; this container never frees them.
 * Keeping pointers typed avoids the original i386 address-as-int layout. */
struct gentity_s;
#define NITMOD_ENTITY_ARRAY_CAPACITY 1024

typedef struct {
	int count;
	struct gentity_s *entities[NITMOD_ENTITY_ARRAY_CAPACITY];
} nitmodEntityArray_t;

typedef enum {
	NITMOD_ENTITY_ARRAY_INVALID = -2,
	NITMOD_ENTITY_ARRAY_FULL = -1,
	NITMOD_ENTITY_ARRAY_UNCHANGED = 0,
	NITMOD_ENTITY_ARRAY_CHANGED = 1
} nitmodEntityArrayResult_t;

/* Reset changes count only, as in the reference. Entries >= count are stale
 * and must not be read. Callers must remove entries before freeing entities. */
void NITMOD_InitEntityArray( nitmodEntityArray_t *array );
/* FULL is checked before duplicate lookup, matching the original G_Error
 * branch. The engine adapter must decide how to report the returned error. */
nitmodEntityArrayResult_t NITMOD_AddEntityToArray( nitmodEntityArray_t *array, struct gentity_s *entity );
nitmodEntityArrayResult_t NITMOD_RemoveEntityFromArray( nitmodEntityArray_t *array, struct gentity_s *entity );

#endif
