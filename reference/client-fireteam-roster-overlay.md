# Fireteam roster and original overlay batch

Reference routines: CG_ParseFireteams in sorted/cgame_servercmds.c,
CG_SortFireTeam, CG_IsOnFireteam, CG_IsOnSameFireteam in
sorted/cgame_client.c, CG_DrawFireTeamOverlay in sorted/cgame_ui.c.

## Reception and ownership

Original `n`, native `id`, leader `l`, and the sixteen hex digits in `c`
are decoded into a temporary typed fireteamData_t. The leftmost digit
contains clients 60..63; the rightmost contains clients 0..3. Only a valid
record is published. Parsing a new set first clears records and member
pointers, so disabled/deleted records cannot retain stale join bits.
Overlapping masks retain the previous parser's last-record-wins pointers.

Hardening differences: IDs outside the six-name table, leaders outside
0..63 or absent from the mask, incomplete/nonhex masks, and malformed
integers are rejected. Disabled `-1` records remain inactive. This does
not introduce a new wire format or require server capability negotiation.

CG_IsOnFireteam is now a bounded function, replacing the unchecked macro.
Original deathmatch (8) and spectator exclusions match the reference.
Native valid membership behavior is retained. Sorting keeps the observed
member/leader/descending-rank order but fixes the comparator's contradictory
results for two nonmembers and for self-comparison. Nonmember ties use
client index. Position lookups and invitation/application/proposition
display reject invalid player indices, including the second proposer ID.

## Original overlay

Six rows maximum, class skill icon (10x10), name limit 14, compact health,
alternating wounded marker, and location text. Width is measured using the
existing location formatter and cg_locationMaxChars instead of the fixed
204-unit ET table. Locations are copied per row, not stored as transient
va pointers. Header uses ariblk/27 and rows courbd/30 at original scales.
The left aspect anchor is restored after drawing. Original spectator and
deathmatch clients see no fireteam overlay. Native layout is unchanged.

Known presentation differences: existing location formatter and white HUD
text are used; exact original location color prefixes/private HUD_Text
palette have not been established here. Invalid classes skip their icon.
The original death marker is represented by zero and wounded asterisk.
No full screenshot parity is claimed.

## Verification

Full cgame fixture tests all 64 membership bits in both protocols, mixed-case
hex, atomic malformed-record rejection, all 4096 comparator pairs, leader
ordering, out-of-range lookups, spectator/deathmatch gates, actual overlay
icon geometry, and invalid overlay identifiers. Existing auto-selection
tests exercise the same sorted roster. Native build/CTest and WASM build
and Node load/entrypoint probes are run; no live browser/server test.

No pak, menu, PK3, original binary, or qagame message producer is modified.
