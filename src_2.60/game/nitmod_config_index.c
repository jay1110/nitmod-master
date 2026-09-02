#include <string.h>
#include "nitmod_config_index.h"

int NITMOD_FindConfigIndex( const char *name, int count, int create,
	nitmodReadConfigIndex_t read, void *context, int *needsWrite ) {
	int index;
	const char *value;
	if( !needsWrite ) {
		return -2;
	}
	*needsWrite = 0;
	if( !name || !name[0] ) {
		return 0;
	}
	if( count < 1 || !read ) {
		return -2;
	}
	for( index = 1; index < count; index++ ) {
		value = read( context, index );
		if( !value ) {
			return -2;
		}
		if( !value[0] ) {
			if( !create ) {
				return 0;
			}
			*needsWrite = 1;
			return index;
		}
		if( !strcmp( value, name ) ) {
			return index;
		}
	}
	return create ? -1 : 0;
}
