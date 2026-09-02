#include <string.h>
#include "nitmod_config_store.h"

void NITMOD_ClearConfigStore( nitmodConfigStore_t *store ) {
	memset( store, 0, sizeof( *store ) );
}

void NITMOD_ClearConfigDirty( nitmodConfigStore_t *store ) {
	memset( store->dirty, 0, sizeof( store->dirty ) );
	store->hasDirty = 0;
}

nitmodConfigResult_t NITMOD_StoreConfig( nitmodConfigStore_t *store, int index, const char *value ) {
	int length;
	if( index < 0 || index >= NITMOD_MAX_CONFIGSTRINGS ) {
		return NITMOD_CONFIG_BAD_INDEX;
	}
	if( !value ) {
		value = "";
	}
	for( length = 0; length < NITMOD_CONFIGSTRING_CHARS; length++ ) {
		if( !value[length] ) {
			break;
		}
		/* Backslashes delimit ET info strings; quoted engine arguments do not
		 * interpret them as escapes. Quotes and newlines remain forbidden. */
		if( value[length] == '"' ||
			value[length] == '\n' || value[length] == '\r' ) {
			return NITMOD_CONFIG_UNSAFE;
		}
	}
	if( length == NITMOD_CONFIGSTRING_CHARS ) {
		return NITMOD_CONFIG_TOO_LONG;
	}
	if( !strcmp( store->values[index], value ) ) {
		return NITMOD_CONFIG_UNCHANGED;
	}
	/* memmove also permits a caller to pass a substring of the same slot. */
	memmove( store->values[index], value, length + 1 );
	store->dirty[index] = 1;
	store->hasDirty = 1;
	return NITMOD_CONFIG_UPDATED;
}
