# Server skill threshold runtime

The reconstructed qagame now evaluates all seven skills against their own
five configured `skill_*` thresholds and their matching `g_maxLevel*` cap.
This replaces ET's fixed five-level `skillLevels` loop and permits Nitmod's
level five. Invalid threshold text falls back transactionally to the original
`20 50 90 140 200` row. `n_noSkillUpgrades` clears both the displayed level
and independent unlock mask.

The independent masks are preserved in typed session state and published in
the original `xp` player-info field. On capability negotiation qagame also
sends the seven threshold rows through the original `sl` command (`B`, `E`,
`M`, `F`, `L`, `S`, `C`). The existing cgame parser therefore uses the same
thresholds for HUD and next-level presentation without changing PK3 files.
