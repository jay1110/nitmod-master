# Deathmatch scoreboard presentation

Reference: sorted/cgame_ui.c WM_DrawClientScoreDM (line 30809), and
sorted/cgame_nitrox.c nitmod_DMTeamScoreboard. This replaces the provisional
DM row rendering; it does not replace the already ported team rows.

The same private presentation records now support original DM rows:
7x14 shadowed text, bounded 18-character names reduced for country/friend/
ready icons, a 14-pixel name inset for active players, and a 610x15 own-row
highlight with fade*0.3 alpha. K/D, XP and ping start at x+196, x+310 and
x+572 independent of those icons. DM has no team class, objective, disguise,
health or lives icons. Ready uses status bit 1 outside GS_PLAYING, not the
team renderer's low-two-bit rule. BOT uses status bit 2, not ping 999.
Country flags are suppressed for -1/999 ping. Spectator labels reuse the
existing connecting/TV/shoutcaster formatter and the original DM placement,
including its different right edge with/without a country flag.

The active DM board now draws all requested alternating background bands and
their bottom rules, uses the original hostname/header placement, and iterates
scores in server order until the y=453 row boundary. The background row count
does not truncate the score list. Invalid clients are skipped and array/count
bounds are enforced; these are deliberate defenses absent from the original.
The existing validated intermission-winner display remains unchanged.

The team and DM renderers share actual glyph/icon submission, retaining
separate layout builders. Cgame-only implementation: no new network messages,
qagame/UI ABI changes, pak changes or original-module modifications.

Verification: the full cgame fixture adds DM checks to 6,912 existing status/
team/powerup/health/ping/phase/size cases, covering column invariance, distinct
ready/BOT semantics, name budget, spectators and invalid inputs. Renderer
tests inspect submitted country/status/highlight rectangles and glyph output.
Full-board tests cover background counts 0..3 without truncating two valid
scores around an invalid entry, plus INT_MAX counts clipped to real array and
screen bounds. All 97 native CTest tests passed. Browser screenshot parity,
Linux-i386 execution and complete Nitmod reconstruction remain unverified.
