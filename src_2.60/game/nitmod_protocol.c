#include <limits.h>
#include <float.h>
#include <errno.h>
#include <stdlib.h>
#include "nitmod_protocol.h"

const char *NITMOD_ServerMessageText( int reason ) {
    static const char *messages[] = {
#include "nitmod_server_messages.inc"
    };
    if(reason < 0 || reason >= sizeof(messages)/sizeof(messages[0])) return 0;
    return messages[reason];
}

const char *NITMOD_WeaponLimitText( int reason ) {
    if( reason < 19 || reason > 25 ) return 0;
    return NITMOD_ServerMessageText(reason);
}

int NITMOD_ParseProtocolFloat( const char *text, float *value ) {
	const char *cursor;
	char *end;
	int digits = 0;
	double parsed;
	float result;
	if( !text || !value ) {
		return 0;
	}
	cursor = text;
	if( *cursor == '-' ) {
		cursor++;
	}
	while( *cursor >= '0' && *cursor <= '9' ) {
		digits = 1;
		cursor++;
	}
	if( *cursor == '.' ) {
		cursor++;
		while( *cursor >= '0' && *cursor <= '9' ) {
			digits = 1;
			cursor++;
		}
	}
	if( !digits ) {
		return 0;
	}
	if( *cursor == 'e' || *cursor == 'E' ) {
		cursor++;
		if( *cursor == '+' || *cursor == '-' ) {
			cursor++;
		}
		if( *cursor < '0' || *cursor > '9' ) {
			return 0;
		}
		while( *cursor >= '0' && *cursor <= '9' ) {
			cursor++;
		}
	}
	if( *cursor ) {
		return 0;
	}
	/* Like the engine's %f serializer, strtod uses the C numeric locale. */
	errno = 0;
	parsed = strtod( text, &end );
	if( *end || errno == ERANGE || parsed > FLT_MAX || parsed < -FLT_MAX ) {
		return 0;
	}
	result = (float)parsed;
	if( parsed != 0.0 && result == 0.0f ) {
		return 0;
	}
	*value = result;
	return 1;
}

int NITMOD_ParseProtocolUnsigned( const char *text, unsigned int *value ) {
	unsigned int parsed = 0;
	unsigned int digit;
	if( !text || !*text || !value ) {
		return 0;
	}
	while( *text ) {
		if( *text < '0' || *text > '9' ) {
			return 0;
		}
		digit = (unsigned int)( *text++ - '0' );
		if( parsed > ( UINT_MAX - digit ) / 10 ) {
			return 0;
		}
		parsed = parsed * 10 + digit;
	}
	*value = parsed;
	return 1;
}

int NITMOD_ParseProtocolInteger( const char *text, int *value ) {
	unsigned int parsed;
	if( !value || !NITMOD_ParseProtocolUnsigned( text, &parsed ) || parsed > INT_MAX ) {
		return 0;
	}
	*value = (int)parsed;
	return 1;
}

int NITMOD_ParseProtocolSigned( const char *text, int *value ) {
	unsigned int magnitude;
	unsigned int minimumMagnitude = (unsigned int)( -( INT_MIN + 1 ) ) + 1u;
	if( !text || !value ) {
		return 0;
	}
	if( *text != '-' ) {
		return NITMOD_ParseProtocolInteger( text, value );
	}
	if( !NITMOD_ParseProtocolUnsigned( text + 1, &magnitude ) || magnitude > minimumMagnitude ) {
		return 0;
	}
	*value = magnitude == minimumMagnitude ? INT_MIN : -(int)magnitude;
	return 1;
}
