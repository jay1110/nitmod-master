#ifndef G_NITMOD_WAR_H
#define G_NITMOD_WAR_H
struct gentity_s;
/* Per-spawn, server-only state. The caller owns lifecycle and configuration.
 * No gameplay hook is enabled until full war-mode restrictions are ported. */
typedef struct {
    int stripped;
} nitmodWarState_t;
void G_NITMOD_ResetWarState( nitmodWarState_t *state );
int G_NITMOD_ApplyWarEntry( struct gentity_s *entity, nitmodWarState_t *state,
    int warMode, int isDemoClient );
#endif
