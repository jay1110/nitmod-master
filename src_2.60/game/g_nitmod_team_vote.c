#include "g_local.h"

/* Nitmod separates in-place team operations from their restart wrappers.
 * Request-side permission-6 overrides are deliberately denied until the
 * original permission system exists; console invocations still bypass the
 * cvar. Neither a request nor its rejection may shuffle/reset players. */
static int TeamVote(gentity_t *ent, char *arg, qboolean referee,
    int allowed, void (*execute)(void)) {
    if(!arg) {
        execute();
        return G_OK;
    }
    if(trap_Argc() > 2) {
        G_refPrintf(ent, "Usage: ^3%s %s^7\n", referee ? "\\ref" : "\\callvote", arg);
        return G_INVALID;
    }
    if(ent && !allowed) {
        G_refPrintf(ent, "Sorry, [lof]^3%s^7 [lon]voting has been disabled", arg);
        return G_INVALID;
    }
    return G_OK;
}

int G_NITMOD_ShuffleVote(gentity_t *ent, unsigned int index, char *arg,
    char *arg2, qboolean referee) {
    (void)index; (void)arg2;
    return TeamVote(ent, arg, referee, vote_allow_shuffleteams.integer, Svcmd_ShuffleTeams_f);
}
int G_NITMOD_ShuffleNoRestartVote(gentity_t *ent, unsigned int index, char *arg,
    char *arg2, qboolean referee) {
    (void)index; (void)arg2;
    return TeamVote(ent, arg, referee, vote_allow_shuffleteams_norestart.integer, G_shuffleTeams);
}
int G_NITMOD_SwapVote(gentity_t *ent, unsigned int index, char *arg,
    char *arg2, qboolean referee) {
    (void)index; (void)arg2;
    return TeamVote(ent, arg, referee, vote_allow_swapteams.integer, G_swapTeams);
}
int G_NITMOD_SwapRestartVote(gentity_t *ent, unsigned int index, char *arg,
    char *arg2, qboolean referee) {
    (void)index; (void)arg2;
    return TeamVote(ent, arg, referee, vote_allow_swapteamsrestart.integer, Svcmd_SwapTeams_f);
}
