#ifndef NITMOD_CONFIG_STORE_H
#define NITMOD_CONFIG_STORE_H

#include "nitmod_protocol.h"

typedef struct {
	char values[NITMOD_MAX_CONFIGSTRINGS][NITMOD_CONFIGSTRING_CHARS];
	unsigned char dirty[NITMOD_MAX_CONFIGSTRINGS];
	int hasDirty;
} nitmodConfigStore_t;

typedef enum {
	NITMOD_CONFIG_TOO_LONG = -3,
	NITMOD_CONFIG_UNSAFE = -2,
	NITMOD_CONFIG_BAD_INDEX = -1,
	NITMOD_CONFIG_UNCHANGED = 0,
	NITMOD_CONFIG_UPDATED = 1
} nitmodConfigResult_t;

void NITMOD_ClearConfigStore( nitmodConfigStore_t *store );
void NITMOD_ClearConfigDirty( nitmodConfigStore_t *store );
/* Failed or identical writes leave both the value and dirty state intact.
 * NULL value means empty. Command delimiters are rejected by the port's
 * existing quoted NCS transport policy; the original did not validate them. */
nitmodConfigResult_t NITMOD_StoreConfig( nitmodConfigStore_t *store, int index, const char *value );

#endif
