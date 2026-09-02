#ifndef G_NITMOD_WEAPONS_H
#define G_NITMOD_WEAPONS_H
struct gclient_s;
/* Mapped ET subset of original G_RemoveWeapons. Ownership bits only;
 * does not select/grant knife, clear ammo or implement war-mode lifecycle. */
void G_NITMOD_RemoveWeapons( struct gclient_s *client );
#endif
