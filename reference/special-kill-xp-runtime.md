# Active special-kill XP awards

The original `G_AddKillSkillPoints` in
`src_nitmod_decompiled/qagame/sorted/nitmod_game.c` has explicit cases
0x3a (Goomba: skill 0, float bits 0x40a00000 = 5) and 0x42
(Tripmine: skill 1, float bits 0x40800000 = 4). The original death-cause
table independently identifies those wire values as Goomba and Tripmine.

The reconstructed `game/g_stats.c` dispatch now awards five Battle Sense
XP and four Engineering XP respectively, using the native named MODs.
Both call the existing `G_AddSkillPoints`, so player XP, player score,
team XP, team score and ordinary skill-threshold processing share the
same path as existing weapon kills. No new wire message is introduced.

`tests/check_special_kill_xp.h` exercises the real dispatcher and award
function for both causes plus knife as a regression control, across all
teams, warmup/playing, LMS/non-LMS, splash settings and hit regions. It
checks player XP, both teams' XP, team scores and stat-report count.
These low-XP cases do not test crossing an upgrade threshold. The prior
Goomba damage fixture also reaches the new award path on lethal hits.

The original global-award calls and Goomba counter increment remain
unported here; this is XP integration, not complete statistics parity.
UI/cgame source and original assets are unchanged by this increment.
Browser end-to-end verification remains outstanding.
