# Team-operation menu/vote adapters

Three missing original server commands are active: shuffleteams,
shuffleteams_norestart, swapteamsrestart. Existing swapteams now dispatches
the original no-restart operation instead of the ET restart wrapper.
Their original menu commands require no pak changes. Legacy shuffleteamsxp
and its old enable cvar remain available independently.

Evidence: sorted nitmod_game.c G_ShuffleTeams_v,
G_ShuffleTeams_NoRestart_v, G_SwapTeams_v and G_SwapTeamsRestart_v;
sorted nitmod_cmds.c Svcmd_ShuffleTeams_f explicitly calls only G_shuffleTeams
when its restart argument is zero. Original aVoteInfo at ELF 0x29e8e0 supplies
all four command spellings, labels and help strings. Original cvar records
0x2a8ab4/0x2a8ad0/0x2a8b08 establish the three new defaults (1, flags 0).

g_nitmod_team_vote.c supplies typed vote callbacks. Requests reject extra
arguments and disabled cvars; accepted callbacks invoke exactly one existing
typed operation: Svcmd_ShuffleTeams_f, G_shuffleTeams, G_swapTeams or
Svcmd_SwapTeams_f. Original permission-6 player overrides remain denied until
their owner is reconstructed. Console requests bypass the enable cvar.
An already accepted vote executes even if the cvar subsequently changes,
matching the original acceptance branch.

The shared UI mask uses original bits 0x200, 0x400000, 0x400, 0x800000.
New cvar modifications trigger existing voteFlags publication and existing
cgame-to-UI propagation. No additional cgame/UI renderer is introduced.
The native shuffleteamsxp cvar no longer incorrectly owns the original
shuffleteams menu bit.

Important remaining differences: original G_shuffleTeams (ELF 0xdd010)
uses nitrox_SortByKDRatio, including private accumulated statistics not yet
mapped to owned ET state. The reused ET implementation still sorts by XP.
Original drop-item, tripmine cleanup and announcement details also are not
fully reconstructed by these adapters. Original help labels say 'randomly'
but that is not evidence of a random selection algorithm. No whole-team
operation parity claim follows from these command wrappers.

Tests: 768 request/acceptance combinations exercise independent cvar bits,
caller/referee presence, excess arguments, no request-side mutation and exact
accepted-operation dispatch. Engine-linked tests verify all four actual vote
table bindings; existing mask tests cover every enabled option. These tests
do not replace live multi-player shuffle/reset/rejoin scenarios. CMake/SCons
include the new production unit; native and WASM verification are separate
from original gameplay parity. Pak and reference artifacts stay unchanged.
