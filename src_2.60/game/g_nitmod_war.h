#ifndef G_NITMOD_WAR_H
#define G_NITMOD_WAR_H
struct gentity_s;
/* Per-spawn, server-only state; cleared with gclient_t by ClientSpawn. */
typedef struct {
    int stripped;
} nitmodWarState_t;
void G_NITMOD_ResetWarState( nitmodWarState_t *state );
int G_NITMOD_CheckWarEntry( struct gentity_s *entity, int warMode );
int G_NITMOD_ApplyWarEntry( struct gentity_s *entity, nitmodWarState_t *state,
    int warMode, int isDemoClient );
#endif
