# Client skill unlock masks and extended breath

The original CS_PLAYERS `xp` token (0x70) contains seven signed integers
used as bitmasks, not experience points. CG_NewClientInfo parses them at
local_840; its upgrade branch reads local_8e8[skill + 0x2a] and stores them
at cgs + client*0x1a4 + 0x958c + skill*4. Original qagame's userinfo sender
serializes the seven entries at client+0xed0 into this exact xp field;
weapon/ammo routines also consume this array as ability masks.

The port corrects the earlier XP-vector interpretation: private
nitmodSkillMasks stores the wire values, separate from actual skillpoints
and displayed skill levels. Missing trailing entries are zero. Existing
transactional rejection of malformed/overflowing/overlong vectors remains.
Signed values retain their bit representation, matching the original reads.

Original water-under event 0x14 tests bit 0x20 in the viewed player's first
mask (Battle Sense): it sets 15000 ms breath instead of 12000 ms. This path
is now connected using typed client/snapshot fields. Native event behavior
retains HOLDBREATHTIME. Deadlines saturate at INT_MAX rather than overflow.
The HUD's original 12000 denominator is intentionally unchanged.

Tests cover all 64 six-bit masks and six unlock bits, real water event
dispatch, invalid helper indices, deadline overflow, parser rejection and
separation from real XP. Prediction and server-side abilities remain
separate port work; no blanket
conversion from displayed levels is claimed. Browser parity remains open.
Original modules, pak assets and server messages are unchanged.

## Health and mine visibility consumers

Original CG_CrosshairClientMaxHealth tests bit 8 at the target client's
0x958c before adding 15 health. The typed crosshair calculation now does
the same; positive class-specific CS39 overrides still take precedence.
Tests exercise 64 masks across five classes and five medic counts with
deliberately contradictory displayed levels.

The original CG_Missile mine branch in sorted/cgame_effects.c tests bit
16 of the local client's mask, not the followed player's displayed level.
The typed mine renderer now uses that bit, retaining the inclusive 256-unit
radius and existing spotting/ownership/team/caster checks. Tests cover all
64 masks and a local/followed-client disagreement. The colored-mine option
is covered in client-colored-mines.md; prediction/server abilities remain open.
