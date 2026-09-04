#include <limits.h>
#include <float.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "nitmod_protocol.h"

const char *NITMOD_ChatCommand( const char *command ) {
	static const char *names[] = { "say", "say_team", "say_teamnl", "say_buddy", "ma", "m", "pm" };
	int i;
	if (!command) return NULL;
	for (i = 0; i < (int)(sizeof(names) / sizeof(names[0])); ++i) {
		const unsigned char *p = (const unsigned char *)command;
		const char *q = names[i];
		while (*p && *q) {
			int c = *p >= 'A' && *p <= 'Z' ? *p + ('a' - 'A') : *p;
			if (c != *q) break;
			++p; ++q;
		}
		if (!*p && !*q) return names[i];
	}
	return NULL;
}

int NITMOD_TextNeedsEncoding( const char *text ) {
	const unsigned char *p = (const unsigned char *)text;
	if (!p) return 0;
	for (; *p; ++p) if (*p == '%' || *p == '=' || *p >= 127) return 1;
	return 0;
}

int NITMOD_BuildChatCommand( const char *command, const char *text, char *output, int capacity ) {
	const char *name = NITMOD_ChatCommand(command);
	const unsigned char *p;
	int prefix, needed;
	if (!name || !text || !*text || !output || text == output || capacity < 1) return 0;
	prefix = (int)strlen(name) + 2;
	needed = prefix + 3; /* closing quote, newline, NUL */
	if (needed > capacity) return 0;
	for (p = (const unsigned char *)text; *p; ++p) {
		int width;
		if (*p < 32 || *p == '"') return 0;
		width = (*p == '%' || *p == '=' || *p >= 127) ? 3 : 1;
		if (width > capacity - needed) return 0;
		needed += width;
	}
	memcpy(output, name, prefix - 2);
	output[prefix - 2] = ' '; output[prefix - 1] = '"';
	NITMOD_EncodeText(text, output + prefix, capacity - prefix);
	output[needed - 3] = '"'; output[needed - 2] = '\n'; output[needed - 1] = 0;
	return 1;
}

int NITMOD_EncodeText( const char *text, char *output, int capacity ) {
	static const char hex[] = "0123456789ABCDEF";
	const unsigned char *p;
	int needed = 1;
	if (!text || !output || capacity < 1 || text == output) return 0;
	for (p = (const unsigned char *)text; *p; ++p) {
		int width = (*p == '%' || *p == '=' || *p >= 127) ? 3 : 1;
		if (width > capacity - needed) return 0;
		needed += width;
	}
	for (p = (const unsigned char *)text; *p; ++p) {
		if (*p == '%' || *p == '=' || *p >= 127) {
			*output++ = '=';
			*output++ = hex[*p >> 4];
			*output++ = hex[*p & 15];
		} else *output++ = (char)*p;
	}
	*output = 0;
	return 1;
}

static int NITMOD_TextHex( unsigned char c ) {
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return -1;
}

void NITMOD_DecodeText( char *text ) {
	char *out = text;
	if (!text) return;
	while (*text) {
		if (*text == '=' && text[1] && text[2]) {
			int hi = NITMOD_TextHex((unsigned char)text[1]);
			int lo = NITMOD_TextHex((unsigned char)text[2]);
			if (hi >= 2 && lo >= 0) {
				*out++ = (char)((hi << 4) | lo);
				text += 3;
				continue;
			}
		}
		*out++ = *text++;
	}
	*out = 0;
}

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
