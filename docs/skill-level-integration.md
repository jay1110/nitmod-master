# Six-level skill integration audit

Current status: isolated threshold parsing and progress calculation are tested.
Native CS_PLAYERS skill-digit parsing is now active with exact length/range
checks. Reward and next-threshold lookups have explicit lower/upper bounds.
No sixth level, sl message, custom Cvar or private skill bitfield is activated.

All 35 original Nitmod reward strings are now recovered into a separate,
bounded cgame accessor and compared against the original ELF in an executable
test. See `reference/skill-rewards.md`. This does not implement the abilities;
native promotion popups still use their original four-reward table.

The first level-five ability's numeric behavior is reconstructed separately:
nitmod_air.c selects a 15-second reserve for battle-sense unlock bit 0x20
instead of 12 seconds, with tested refill/drowning transitions. The active
engine adapter now preserves native PW_BREATHER behavior and uses zero
unlock bits until skill-state integration; the 15-second perk remains off.

## Reconstructed numeric contract

qagame `nitmod_game.c` G_SetPlayerSkill (18361 onward) checks Lua first,
selects a per-skill jp_maxLevel* Cvar, then resets both level and unlock bits.
Values above six are capped to six; limits below two grant no upgrades.
For each level 1..5 below the limit, a nonnegative threshold reached by XP
sets that level's bit and makes it the highest achieved level. Disabled or
unmet earlier thresholds do not prevent later levels from unlocking.
`n_noSkillUpgrades` forces both results to zero. Score recomputation follows.

`NITMOD_EvaluateSkill` reconstructs only that numeric middle section.
Tests cover all seven skills, every threshold just below/at the boundary,
limits -1..8, global disable, negative XP, disabled and unordered thresholds,
and invalid API arguments without output mutation. Lua, score side effects,
private client-state offsets and original-binary execution are not covered.

## Required integration work

The adrenaline inventory revocation operation is now recovered and tested:
it clears only ps.weapons ownership when explicit eligibility fails. Ammo,
selected weapon and running powerup remain intact, and eligibility restoration
does not grant a weapon. Original demo-client/FOLLOW/health guards are now
resolved and composed with this operation. Cached demo-state lifecycle,
private war-mode state and generic restrictions still block an active hook.

Adrenaline eligibility and immediate clip selection are now typed and tested
in g_nitmod_abilities.c. Eligibility requires first-aid unlock bit 0x10 and
the appropriate g_adrenClasses bit, independent of numeric skill level.
These helpers are not gameplay-active. See reference/skill-abilities-disassembly.md
for original addresses, option precedence and outstanding inventory paths.

The score side effect is now shared by existing active callers through
G_SetPlayerScore in g_nitmod_score.c. It consumes the actual seven session XP
fields, truncates after each addition and rejects invalid updates atomically.
See reference/skill-score-disassembly.md for tests and precision differences.
It does not itself update skill levels, rank, Lua state or abilities.

`NITMOD_CalculateSkillLoss` now reconstructs the numeric loss transaction:
remaining XP, actual removed XP and recomputed progress. Tests cover all
skill thresholds, disabled levels, limits, negative XP, negative losses and
rounded-away subtraction. The original Nitmod G_LoseSkillPoints does NOT
restore the old level as native ET does. Switching the active routine must
therefore include downgrade/rank/ability handling, not just a new table.
Lua interception can change the result and is not modeled by this pure helper.
Nonfinite or overflowing transactions are rejected without output mutation;
this is deliberate hardening, not original floating-point parity.

| Consumer | Current assumption | Required before activation |
| --- | --- | --- |
| game/bg_public.h and bg_misc.c | five levels, one const threshold vector | introduce shared per-skill state without silently changing unrelated constants |
| game/g_stats.c G_SetPlayerSkill | descending lookup into native vector | integrate numeric result, decide typed storage for separate unlock mask and Lua override |
| game/g_stats.c G_LoseSkillPoints | restores XP using skillLevels[oldskill] | use matching per-skill threshold; handle disabled levels and keep original XP-loss semantics |
| game/g_stats.c and g_session.c ranks | native rank logic active; isolated Nitmod sum-of-levels calculation recovered and exhaustively tested | integrate recovered rank with skill refresh, Lua, userinfo and ability changes; verify persistence |
| cgame/cg_players.c | active native four-reward table; all 35 Nitmod strings recovered separately; indices bounded | port corresponding abilities, then select Nitmod table when level 5 is activated |
| cgame/cg_servercmds.c | bounded next-threshold lookup into single native vector | select correct skill row before six-level activation |
| cgame/cg_draw.c | four progress blocks | verify six-level layout and assets against original |
| game/g_client.c, g_items.c, g_combat.c | many literal level-four ability checks | recover which abilities use numeric level versus individual unlock bits |
| protocol/config/session | sl inactive, native skill persistence | negotiate feature, initialize/reset/resync matrix, migrate state consistently |

UI menu references named skillLevels must be resolved in their own context;
name matching alone does not establish that a menu difficulty list is an XP
threshold consumer. No blanket search-and-replace of level constants is safe.
