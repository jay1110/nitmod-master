# Intermission readiness, duration and client countdown

Original CheckIntermissionExit in sorted nitmod_unknown.c uses
g_intermissionTime (default 60 seconds) and g_intermissionReadyPercent
(default 100, floating-point value). Both original registrations have flags
zero and track-change/reset false. Fully connected humans count, including
spectators; bots and connecting clients do not. Ready humans are those with
pers.ready set. Percentages use float division, not integer truncation.
Referee all-ready overrides the wait, otherwise readiness or the duration
deadline permits exiting. No humans does not bypass the duration deadline.

The typed predicate now replaces the stock match_readypercent/60-second
decision in CheckIntermissionExit. Existing delayed stats dumping and
ExitLevel remain in place. The engine-shared structs are unchanged.

BeginIntermission publishes a shifted CS_INTERMISSION_START_TIME for positive
durations: now + duration*1000 - 60000. This matches the original and makes
the existing 60-second client countdown show the configured time without
changing cgame or assets. Server expiration still uses the real start time.
Integer overflow in the display timestamp saturates; deadline arithmetic
uses double to avoid signed overflow. Zero/negative duration is not unlimited.

Scope limitation: original g_mapVoteFlags bit 2 can require the voted-human
percentage before allowing *either* readiness or timer exit. The mapvote
workflow/Cvar is not implemented in this tree, so this additional gate is
not claimed here. Full mapvote parity remains open. The original code's
static end-of-match action reset behavior was not changed.

Full-qagame tests cover 36 readiness/percentage/deadline combinations,
spectator inclusion, bot/connecting exclusion, empty server, referee override,
zero duration, display offsets and overflow. They invoke the live-state
predicate, not actual map loading/ExitLevel or browser countdown rendering.
