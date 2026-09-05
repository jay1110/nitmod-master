# Class health overrides: runtime integration

Original nitrox_ParseMaxHP (sorted nitmod_core.c) clears five class entries,
then reads positive integers from n_classesMaxHP in Soldier, Medic, Engineer,
Field Ops, Covert Ops order. The hash-derived cvar inventory gives default
"0 0 0 0 0" and archive flag 1. AddMedicTeamBonus in nitmod_unknown.c applies
a positive class override after the ordinary team/skill calculation, using
it for both base and effective healing maxima. The original spawn path also
skips the usual 15-point skill subtraction when a class override is present.

The reconstructed server now registers this cvar and reads its five values
when calculating spawn health. Missing, nonpositive or malformed entries use
the existing baseline. Values above 32767 are rejected rather than wrapping
the engine's signed 16-bit stat transport. Quoted/numeric parsing is stricter
than the original strtok/strtol prefix acceptance; extra entries are ignored.

STAT_NITMOD_MAX_HEALTH explicitly names stat slot 9, already used as the
original Nitmod healing maximum by the client HUD. It adds no playerState
fields and does not move existing stat indices. The server publishes the cap;
shared BG_EffectiveMaxHealth supplies it to item-eligibility prediction,
server health pickups and regeneration, and the reconstructed HUD adapter.
A zero cap retains legacy ET class-based calculation. Negotiated clients also
receive the five-value `nch` snapshot on handshake and whenever
`n_classesMaxHP` changes, so crosshair health bars use the same limits as the
server. This replaces original Nitmod's private configstring 39 transport:
native ET 2.60 owns slot 39 as `CS_FILTERCAMS`, so reusing it would corrupt
engine state. No PK3 or UI menu asset is required. Stock ET clients do not
receive the extension; mixed-client prediction parity is not claimed.

Configuration takes effect when health is recalculated at spawn, not as an
immediate rewrite of every living player's health. Example:

    set n_classesMaxHP "150 120 130 110 100"

Tests exercise all classes with and without native Battle Sense level 3,
defaults, overrides, malformed/overflow entries and missing trailing values;
they invoke actual AddMedicTeamBonus, BG_CanItemBeGrabbed, Pickup_Health and
ClientTimerActions around each healing boundary. Full spawn execution and
live browser visual parity are not established by these tests.

War/deathmatch continuation: G_NITMOD_SetHealthLimits now applies the original
AddMedicTeamBonus branches (sorted nitmod_unknown.c, labels 0x5a20d..0x5a275).
Any nonzero war setting OR gametype 8 suppresses the team-medic and Battle
Sense maximum-health bonuses. Medic overhealth remains unless BOTH conditions
hold. Positive class overrides take precedence in all modes.
G_NITMOD_SpawnHealth also implements the corresponding ClientSpawn branch
(sorted nitmod_client.c, joined_r0x0005df0c): the 15-point skill subtraction
only applies without war, outside gametype 8 and without a class override.
Both helpers are called by the active spawn path, not isolated preparations.

The matrix tests cover 5 classes, 5 native skill levels, 65 team-medic counts,
7 war values, 2 gametype variants and 2 override states (45500 combinations),
including independence of current health and residual regeneration time.
The native skill threshold/unlock representation is still not the complete
original six-level system. Full respawn/revive and browser replays remain open.
