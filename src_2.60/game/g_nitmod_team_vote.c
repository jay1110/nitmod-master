#include "g_local.h"
#include "g_nitmod_admin.h"

/* Original team votes require referee status AND permission 6 for the
 * disabled-vote override; requests must not execute the team operation. */
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
    if(ent && !allowed && !(ent->client && ent->client->sess.referee &&
        G_NITMOD_AdminPrivilege((int)(ent - g_entities), "novotelimit"))) {
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
