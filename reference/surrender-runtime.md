# Team surrender: active vote lifecycle

Original qagame G_Surrender_v is at ELF 0xe9380 (247 bytes). Its sorted
nitmod_game.c request/acceptance branches and G_Surrender_v_part_2 establish
the playing-state gate, [AXIS]/[ALLIES] argument, opponent victory, LogExit
and the broadcast surrender chat. Original Cmd_Vote_f rejects opposing-team
votes; CheckVote uses a team electorate for surrender. The caller's team is
captured in original Cmd_CallVote_f (sorted nitmod_cmds.c near line 858).

The reconstructed server registers vote_allow_surrender (default 1, flags 0)
and its original 0x20000 menu bit. The actual vote dispatcher now owns a
typed callback in g_nitmod_surrender.c. A private voteInfo.surrenderTeam field
captures the admitted team. Only playing Axis/Allies clients are admitted;
disabled requests, spectators, missing clients and context-free console
requests are rejected without modifying the pending team. The original
permission-6 override remains unavailable; a player referee cannot bypass a
disabled cvar. This is an explicit incomplete admin-compatibility point.

Cmd_Vote_f gates the electorate before setting EF_VOTED or changing counts.
CheckVote uses numVotingTeamClients for the captured team, rather than the
server-wide total. Counts are clamped to 0..MAX_CLIENTS. Captured ownership
deliberately avoids the original denominator's dependency on the caller's
current slot/team after a disconnect or team switch.

On acceptance while still playing, the callback updates native
CS_MULTI_MAPWINNER's 'winner' key (1 for an Axis surrender, 0 for Allies),
preserving unrelated keys, then calls LogExit and emits the original chat
announcement. The original private key 'w' is not copied into the ET layout.
Existing cgame debriefing reads the native 'winner' key, and existing LogExit
owns intermission queuing and end-of-map statistics. A vote accepted after
the playing phase performs no duplicate round-ending action. No new cgame
renderer or UI asset is needed for this connection.

Tests cover admission across states/teams/cvar/referee combinations, invalid
callers, voter teams, electorate bounds and exact winner/log/chat ordering.
Engine-linked tests exercise G_voteCmdCheck and Cmd_Vote_f for both teams and
spectators. Real CheckVote is tested for waiting, passing and failing with a
two-person own team and 62 opponents, so global-count regressions are visible.
The end-action unit substitutes engine/log callbacks: actual browser
intermission and multi-client network replay remain unverified.

Only private server state changes size; playerState/entityState/engine ABI
layouts are unchanged. Pak and original reference modules are untouched.
