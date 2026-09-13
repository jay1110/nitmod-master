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
	for( length = 0; length < NITMOD_CONFIGSTRING_CHARS - 1; length++ ) {
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
	if( !strcmp( store->values[index], value ) ) {
		return NITMOD_CONFIG_UNCHANGED;
	}
	/* memmove also permits a caller to pass a substring of the same slot. */
	/* Original nitrox_SetConfigstring compares before Q_strncpyz(size 0x3fa).
	 * Repeating an overlong input must therefore still mark the slot dirty. */
	memmove( store->values[index], value, length );
	store->values[index][length] = '\0';
	store->dirty[index] = 1;
	store->hasDirty = 1;
	return NITMOD_CONFIG_UPDATED;
}
