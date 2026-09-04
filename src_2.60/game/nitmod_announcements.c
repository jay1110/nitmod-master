#include <limits.h>
#include "nitmod_announcements.h"
#include "nitmod_protocol.h"

int NITMOD_AnnouncementCount( int type, int detail ) {
	if( detail < 0 ) {
		return -1;
	}
	switch( type ) {
	case 1: /* G_UpdateKillingSpree: kills / 5 - 1, through 30. */
		return detail < 6 ? ( detail + 1 ) * 5 : -1;
	case 2: /* Same function: negative streaks -10, -20, -30. */
		return detail < 3 ? ( detail + 1 ) * 10 : -1;
	case 3: /* Original MKName has five entries; return the tier, not kills. */
		return detail < 5 ? detail + 1 : -1;
	case 4: /* ReviveEntity sends the actual count at each fifth revive. */
		return detail >= 5 && detail % 5 == 0 ? detail : -1;
	case 5: /* ReviveEntity sends count - 2 for counts 2 through 5. */
		return detail < 4 ? detail + 2 : -1;
	default:
		return -1;
	}
}

int NITMOD_ParseAnnouncementInteger( const char *text, int *value ) {
	return NITMOD_ParseProtocolInteger( text, value );
}
