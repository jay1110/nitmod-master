# Debriefing deathmatch ordering

Original `CG_SortPlayersByXP` in `cgame_client.c` selects client offset
0x9584 for gametype 8 and 0x9498 otherwise (client stride 0x1a4).
`CG_Debriefing_ParsePlayerKillsDeaths` in `cgame_ui.c` writes the first
`impkd` value to 0x9584 and the second to 0x9588, identifying the former
as kills. The typed port now sorts original-protocol deathmatch players
by descending kills, retaining descending XP for other modes/native ET.

Equal scores remain equal, with no invented tie-break rule. As a safety
deviation, two invalid entries compare equal rather than both comparing
less than each other; out-of-range IDs never index clientinfo.

Tests cover both protocols, gametypes 0..8, actual qsort ordering, valid
and invalid IDs, self-comparison, antisymmetry, ties and extreme XP.
Original-server browser presentation is not verified by these tests.
