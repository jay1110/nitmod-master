#ifndef G_NITMOD_ENTITIES_H
#define G_NITMOD_ENTITIES_H

struct gentity_s;
void G_NITMOD_ResetEntityLists( void );
void G_NITMOD_RegisterSatchel( struct gentity_s *entity );
void G_NITMOD_UnregisterSatchel( struct gentity_s *entity );
void G_NITMOD_RegisterLandmine( struct gentity_s *entity );
void G_NITMOD_UnregisterLandmine( struct gentity_s *entity );
int G_NITMOD_CountTeamLandmines( int team, int maximum );
/* Release callback handles engine/map bookkeeping after ownership is cleared.
 * It must release only the supplied entity, not reset/repopulate the lists. */
typedef void (*nitmodEntityRelease_t)( struct gentity_s *entity );
/* Stable registration-order snapshot; ignores entities replaced or removed
 * during earlier callbacks. Returns the number of explosion callbacks. */
int G_NITMOD_ExplodeSatchels( struct gentity_s *owner, nitmodEntityRelease_t explode );
void G_NITMOD_FadeLandmines( struct gentity_s *owner, nitmodEntityRelease_t release );
/* Engine release adapter; mine must be NULL or a slot in g_entities. */
void NITMOD_FreeFadedLandmine( struct gentity_s *mine );
void G_NITMOD_FadeSatchels( struct gentity_s *owner, nitmodEntityRelease_t release );
struct gentity_s *G_NITMOD_FindSatchel( const struct gentity_s *owner );
/* Team-only proximity marker that follows one artillery salvo. */
void G_NITMOD_SpawnArtilleryHint( struct gentity_s *shell );

#endif
