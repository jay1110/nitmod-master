/* Recovered Nitmod client-side helpers; see cg_nitmod.h. */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "cg_local.h"
#include "cg_nitmod.h"
#include "../game/nitmod_snapshots.h"

qboolean Nit_RemoveWordInString( char *text, const char *word ) {
	char *match;
	size_t wordLength;

	if ( !text || !word ) {
		return qfalse;
	}

	wordLength = strlen( word );
	if ( !wordLength ) {
		return qtrue;
	}

	while ( ( match = strstr( text, word ) ) != NULL ) {
		memmove( match, match + wordLength, strlen( match + wordLength ) + 1 );
	}

	return qtrue;
}

void nitrox_ClampFloat( float *value, float minimum, float maximum ) {
	if ( !value ) {
		return;
	}

	if ( *value < minimum ) {
		*value = minimum;
	} else if ( *value > maximum ) {
		*value = maximum;
	}
}

void nitrox_ClampInt( int *value, float minimum, float maximum ) {
	if ( !value ) {
		return;
	}

	if ( *value < minimum ) {
		*value = minimum >= 0.0f ? (int)( minimum + 0.5f ) : (int)( minimum - 0.5f );
	} else if ( *value > maximum ) {
		*value = maximum >= 0.0f ? (int)( maximum + 0.5f ) : (int)( maximum - 0.5f );
	}
}

void nitrox_StripLeadingSpaces( char *text ) {
	char *first;

	if ( !text ) {
		return;
	}

	first = text;
	while ( *first == ' ' ) {
		first++;
	}
	if ( first != text ) {
		memmove( text, first, strlen( first ) + 1 );
	}
}

void nitrox_stripLeadingSpaces( char *text ) {
	nitrox_StripLeadingSpaces( text );
}

int nitrox_ClassNumForLetter( const char *letter ) {
	if ( !letter || !letter[0] ) {
		return PC_SOLDIER;
	}

	switch ( tolower( (unsigned char)letter[0] ) ) {
	case 'm': return PC_MEDIC;
	case 'e': return PC_ENGINEER;
	case 'f': return PC_FIELDOPS;
	case 'c': return PC_COVERTOPS;
	case 's':
	default:  return PC_SOLDIER;
	}
}

qboolean nitrox_NextConfigKey( const char **cursor, char *key, size_t keySize ) {
	const char *start;
	const char *end;
	size_t length;

	if ( !cursor || !*cursor || !key || keySize < 2 ) {
		return qfalse;
	}

	start = *cursor;
	if ( *start == '\\' ) {
		start++;
	}
	if ( !*start ) {
		key[0] = '\0';
		*cursor = start;
		return qfalse;
	}

	end = start;
	while ( *end && *end != '\\' ) {
		end++;
	}
	length = end - start;
	if ( length >= keySize ) {
		length = keySize - 1;
	}
	memcpy( key, start, length );
	key[length] = '\0';

	*cursor = *end == '\\' ? end + 1 : end;
	return qtrue;
}

void nitmod_PrintConfigStringStats( void ) {
	int index;
	int characters;
	const char *configString;

	characters = 0;
	for ( index = 0; index < MAX_CONFIGSTRINGS; index++ ) {
		configString = CG_ConfigString( index );
		if ( configString[0] ) {
			CG_Printf( "%4i: %s\n", index, configString );
			characters += strlen( configString );
		}
	}
	CG_Printf( "^9|------------------------------\n^2%i ^7chars in Gamestate\n^9|------------------------------\n", characters );
}

void nitrox_MinimizeET_f( void ) {
	CG_Printf( "Sorry, minimize command is not yet supported by your OS.\n" );
}

void nitrox_MD5ToString( const byte digest[16], char output[33] ) {
	static const char hexadecimal[] = "0123456789abcdef";
	int index;

	if ( !digest || !output ) {
		return;
	}

	for ( index = 0; index < 16; index++ ) {
		output[index * 2] = hexadecimal[digest[index] >> 4];
		output[index * 2 + 1] = hexadecimal[digest[index] & 15];
	}
	output[32] = '\0';
}

void MD5toStr( const byte digest[16], char output[33] ) {
	nitrox_MD5ToString( digest, output );
}

void nitmod_PrintCGS( void ) {
	nitmod_PrintConfigStringStats();
}

qboolean checkGuid( const char *guid ) {
	int index;
	unsigned int checksum;

	if ( !guid || strlen( guid ) != 32 ) {
		return qfalse;
	}

	checksum = 0;
	for ( index = 0; index < 32; index++ ) {
		checksum += (unsigned char)guid[index];
	}
	return checksum % 100 == 0 ? qtrue : qfalse;
}

void nitrox_ParseChargeTimes( void ) {
	nitmodChargeTimes_t next;
	if( trap_Argc() != 11 ) {
		CG_Printf( "Nitmod: ignoring malformed ct command\n" );
		return;
	}
	if( !NITMOD_ParseChargeSnapshot( trap_Argc(), CG_Argv, &next ) ) {
		return;
	}
	memcpy( cg.soldierChargeTime, next.soldier, sizeof(next.soldier) );
	memcpy( cg.medicChargeTime, next.medic, sizeof(next.medic) );
	memcpy( cg.engineerChargeTime, next.engineer, sizeof(next.engineer) );
	memcpy( cg.ltChargeTime, next.fieldops, sizeof(next.fieldops) );
	memcpy( cg.covertopsChargeTime, next.covertops, sizeof(next.covertops) );
}
