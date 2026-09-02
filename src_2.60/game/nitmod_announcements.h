/* Shared, engine-independent semantics of the recovered announcement tuple. */
#ifndef NITMOD_ANNOUNCEMENTS_H
#define NITMOD_ANNOUNCEMENTS_H

/* Returns the displayed count, or -1 for an invalid payload. For type 3
 * only the tier is known: the original multi-kill lookup table is absent. */
int NITMOD_AnnouncementCount( int type, int detail );
/* Decimal protocol fields must contain digits only and fit in a signed int.
 * On failure the caller's output remains unchanged. */
int NITMOD_ParseAnnouncementInteger( const char *text, int *value );

#endif
