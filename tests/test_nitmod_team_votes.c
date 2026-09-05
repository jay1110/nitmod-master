#include "g_local.h"
#include <stdio.h>
#include <string.h>

vmCvar_t vote_allow_shuffleteams, vote_allow_shuffleteams_norestart;
vmCvar_t vote_allow_swapteams, vote_allow_swapteamsrestart;
static int argcValue, reads, notices, calls[4];
int trap_Argc(void) { ++reads; return argcValue; }
void G_refPrintf(gentity_t *ent, const char *fmt, ...) { (void)ent; (void)fmt; ++notices; }
void Svcmd_ShuffleTeams_f(void) { ++calls[0]; }
void G_shuffleTeams(void) { ++calls[1]; }
void G_swapTeams(void) { ++calls[2]; }
void Svcmd_SwapTeams_f(void) { ++calls[3]; }

int main(void) {
    typedef int (*voteFn)(gentity_t *, unsigned int, char *, char *, qboolean);
    voteFn functions[] = {G_NITMOD_ShuffleVote, G_NITMOD_ShuffleNoRestartVote,
        G_NITMOD_SwapVote, G_NITMOD_SwapRestartVote};
    vmCvar_t *options[] = {&vote_allow_shuffleteams, &vote_allow_shuffleteams_norestart,
        &vote_allow_swapteams, &vote_allow_swapteamsrestart};
    static gentity_t ent, before;
    int kind, mask, caller, referee, count, i, errors = 0, profiles = 0;
    char arg[] = "teamvote", value[] = "unchanged";
    memset(&ent, 0x5a, sizeof(ent)); before = ent;
    for(kind = 0; kind < 4; ++kind) for(mask = 0; mask < 16; ++mask)
    for(caller = 0; caller < 2; ++caller) for(referee = 0; referee < 2; ++referee)
    for(count = 2; count < 5; ++count) {
        int valid = count == 2 && (!caller || (mask & (1 << kind)));
        for(i = 0; i < 4; ++i) options[i]->integer = !!(mask & (1 << i));
        reads = notices = 0; memset(calls, 0, sizeof(calls)); argcValue = count;
        if(functions[kind](caller ? &ent : NULL, 99, arg, value, referee) != (valid ? G_OK : G_INVALID) ||
           reads != 1 || notices != !valid || memcmp(&ent, &before, sizeof(ent)) ||
           strcmp(value, "unchanged")) ++errors;
        for(i = 0; i < 4; ++i) if(calls[i]) ++errors;
        reads = notices = 0;
        if(functions[kind](NULL, 0, NULL, NULL, qfalse) != G_OK || reads || notices) ++errors;
        for(i = 0; i < 4; ++i) if(calls[i] != (i == kind)) ++errors;
        ++profiles;
    }
    printf("Team votes: %d request/acceptance profiles, %d errors\n", profiles, errors);
    return errors != 0;
}
