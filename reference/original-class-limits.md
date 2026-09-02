# Five team class limits

Original G_IsClassDisabled in sorted nitmod_game.c counts other clients on
the actor's team when either current playerType or latchPlayerType matches.
It traverses level.sortedClients up to numNonSpectatorClients (the original
field immediately before numPlayingClients and sortedClients), excluding the
actor. A client matching both fields counts once. Spectators and invalid
class IDs are not restricted by the original predicate.

team_maxSoldiers, team_maxMedics, team_maxEngineers, team_maxFieldops and
team_maxCovertops register with default -1, flags zero, track/reset false.
Only -1 means unlimited. Limit 0 disables a class; other signed limits use
the original count >= limit comparison. Existing g_war modes exempt soldier
(1), covertops (2), engineer (3); this does not implement the whole war mode.

Cmd_Team and non-revive ClientSpawn now invoke the recovered selection:
keep an available requested class, otherwise scan soldier through covertops,
otherwise force spectators. The spawn path returns after the spectator
transition to avoid continuing stale spawning work. Spectator requests may
pass the preliminary team command check, as in the original; the spawn check
then runs with the assigned team. Direct Bot team setup and the original
third call site in nitmod_game.c are not reconstructed in this patch.

The five live values populate the existing # game-state fields. Cvar changes
trigger the existing capability-gated snapshot update. cgame already parses
these fields; no protocol field count, playerstate or entity ABI is changed.
The original limbo disabled-class rendering is NOT implemented here: the
current client lacks the audited latched-class clientinfo field/decoder.

G_IsClassDisabled's nonquiet response uses the original message text IDs
14..18 through stock cp, an intentional transport difference for stock-client
compatibility. Production selection uses quiet=true, like the original.
Validation additionally bounds sorted indices and class inputs. No assets
or reference binaries are edited.

Full-qagame tests cover 300 class/limit/war/spectator profiles, current-plus-
latched counting without double counting, actor/opponent exclusion, all-full
and first-available fallback. These are direct predicate/selection tests,
not an end-to-end engine ClientSpawn or spectator-transition replay.
