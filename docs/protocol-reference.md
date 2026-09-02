# Recovered Nitmod protocol reference

This document records wire layouts recovered from the supplied
`qagame.mp.i386.so` and `cgame.mp.i386.so`.  It is a reconstruction aid, not a
claim that the current source has full gameplay parity.

## Capability exchange

The reconstructed transport starts with `nitcap <version> <bitmask>` and the
server replies with `nitcaps <version> <accepted-bitmask>`.  Nitmod-only
commands are sent only after that exchange, so stock clients do not receive an
unknown command.

## `scs`: simple configuration

The command has exactly eleven decimal fields, in this order:

1. `g_doubleJump`
2. `g_missileCams`
3. `g_war`
4. `g_noReload`
5. `g_filtercams`
6. `g_spectatorNames`
7. `g_misc`
8. `n_proneDelay`
9. `n_dynamiteTimer`
10. `n_crouchStandDelay`
11. `n_standCrouchDelay`

## `#`: game state

The command has twenty fields.  The first fourteen are decimal integers,
field 15 is a fixed three-decimal float, and the remaining five are decimal
integers:

1. `team_panzerRestriction`
2. `team_maxPanzers`
3. `team_maxMG42s`
4. `team_maxFlamers`
5. `team_maxMortars`
6. `team_maxriflegrenades`
7. `g_adrenaline`
8. `jp_keepAwards`
9. `team_maxSoldiers`
10. `team_maxMedics`
11. `team_maxEngineers`
12. `team_maxFieldops`
13. `team_maxCovertops`
14. `g_weapons`
15. `g_DJHeight`
16. `g_TDMOptions`
17. `g_DMOptions`
18. `g_gravity`
19. current map-count
20. `g_resetXPMapCount`

The original binary exposes `g_DJHeight` with a nearby `1.4` string.  Defaults
for the remaining Nitmod-specific fields are not inferred from unrelated
binary string adjacency; they must be recovered with the original cvar table
or runtime transcripts before gameplay ownership is introduced.

## `ob`: objective event

`ob <type> <detail> <objective> <actor> <means-of-death>` uses the OID record at
extended configstring index `609 + objective`; the client displays its `n`
field. The final field is a `MOD_*` value (or zero when no weapon applies),
not a team number. Recovered event pairs are `0,0` (dynamite planted), `0,1` (defused),
`4,2` (constructed), `4,3` (destroyed), `4,4` (damaged), and types `9`/`10`
for Axis/Allies checkpoint captures.

## Validation

The reconstructed cgame accepts a custom command only after `nitcaps`
negotiates its corresponding feature bit. Every implemented fixed-layout
command checks its exact argument count before changing client state. This is
a deliberate compatibility and robustness boundary; it does not alter the
wire layout recovered from the original module.

## `mes`: map-end statistics

`mes <bodyshots> <headshots> <kills> <deaths> <revives>` is sent once per
human client as the match exits.  The 2.60 base supplies headshots (summed
weapon counters), kills, deaths, and syringe revives. Its dedicated Nitmod
bodyshot counter has not yet been recovered, so the current port transmits
zero for that field rather than claiming a derived value is identical.
