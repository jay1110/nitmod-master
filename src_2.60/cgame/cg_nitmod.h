/*
 * Recovered Nitmod client-side helpers.
 *
 * These functions were ported from the cgame binary into typed ET 2.60 code.
 * Keep game-facing state in the regular cg/cgs structures; this interface is
 * deliberately limited to stateless helpers.
 */

#ifndef CG_NITMOD_H
#define CG_NITMOD_H

#include "../game/q_shared.h"

qboolean Nit_RemoveWordInString( char *text, const char *word );
void nitrox_ClampFloat( float *value, float minimum, float maximum );
void nitrox_ClampInt( int *value, float minimum, float maximum );
void nitrox_StripLeadingSpaces( char *text );
void nitrox_stripLeadingSpaces( char *text );
int nitrox_ClassNumForLetter( const char *letter );
qboolean nitrox_NextConfigKey( const char **cursor, char *key, size_t keySize );
void nitmod_PrintConfigStringStats( void );
void nitrox_MinimizeET_f( void );
void nitrox_MD5ToString( const byte digest[16], char output[33] );
void MD5toStr( const byte digest[16], char output[33] );
void nitmod_PrintCGS( void );
qboolean checkGuid( const char *guid );
void nitrox_ParseChargeTimes( void );

#endif
