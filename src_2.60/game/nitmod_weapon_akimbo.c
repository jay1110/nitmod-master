#include "q_shared.h"
#include "bg_public.h"

/* Native ET helpers, moved from bg_misc.c. Original Nitmod has the same
 * four identities, sidearms and fire-order rule. */
qboolean BG_AkimboFireSequence( int weapon, int akimboClip, int mainClip ) {
	if( !BG_IsAkimboWeapon( weapon ) )
		return qfalse;

	if( !akimboClip )
		return qfalse;

	// no ammo in main weapon, must be akimbo turn
	if( !mainClip )
		return qtrue;

	// at this point, both have ammo

	// now check 'cycle'   // (removed old method 11/5/2001)
	if( ((unsigned int)akimboClip ^ (unsigned int)mainClip) & 1u) { 
		return qfalse;
	}

	return qtrue;
}

qboolean BG_IsAkimboWeapon( int weaponNum ) {
	if( weaponNum == WP_AKIMBO_COLT ||
		weaponNum == WP_AKIMBO_SILENCEDCOLT ||
		weaponNum == WP_AKIMBO_LUGER ||
		weaponNum == WP_AKIMBO_SILENCEDLUGER )
		return qtrue;
	else
		return qfalse;
}

int BG_AkimboSidearm( int weaponNum ) {
	switch( weaponNum )
	{
	case WP_AKIMBO_COLT:			return WP_COLT;				break;
	case WP_AKIMBO_SILENCEDCOLT:	return WP_COLT;	break;
	case WP_AKIMBO_LUGER:			return WP_LUGER;			break;
	case WP_AKIMBO_SILENCEDLUGER:	return WP_LUGER;			break;
	default:						return WP_NONE;				break;
	}
}
