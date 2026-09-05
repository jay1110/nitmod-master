# Limbo population counters

Original reference: `cgame_ui.c`, function
`CG_LimboPanel_RenderCounter_ValueForButton`, cases 0 and 1.
Both original loops end at `cgs + maxclients * 0x1a4 + 0x940c`
(maxclients is the field at offset 27400). They filter invalid client
records and team; class counters additionally filter class.

The productive implementation now uses server maxclients for both Nitmod
counters. ET 2.60 retains its 64-slot scan. The existing spectator helper
already allows inspecting either combat team; no change was needed there.
The limit is clamped to 0..MAX_CLIENTS and invalid team-button indices
return zero instead of reading outside teamOrder. Null buttons return zero.
These bounds are deliberate safety additions, not original behavior claims.

CheckLimboPopulationCounters tests both protocols, six server limits,
three teams, both counter types, invalid records, mixed classes and stale
records beyond the server limit. Browser presentation remains unverified.
