# XP map-cycle runtime

The original qagame stores its zero-based map-cycle counter in the world
`session` cvar. `g_resetXPMapCount` is now a typed qagame cvar. Map-vote (and
the corresponding TDM/DM map-vote modes) advance the counter in `ExitLevel`
before session data is written.

At cycle position zero, persisted client XP and weapon statistics are cleared
once during `G_InitWorldSession`. Intermediate maps preserve them. Bit 4 of
`g_XPSave` disables the cyclic reset and transmits a zero reset length to
cgame, matching the recovered `nitmod_SendNCS` control flow.

The authoritative zero-based counter and configured reset length occupy the
last two fields of the original 20-field `#` command. cgame therefore uses the
same state for scoreboard/intermission map-cycle presentation.

The parser accepts both the extended Nitmod world session and the historic
three-field ET 2.60 session so an existing local installation can upgrade.
