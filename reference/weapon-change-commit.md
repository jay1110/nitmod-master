# Weapon-change target and raising-state commit

The inlined PM_FinishWeaponChange in PM_Weapon reads nextWeapon, clamps
out-of-range targets to NONE, checks inventory ownership, writes weapon,
then translates dropping-to-reload to raising-to-reload (all other incoming
states select ordinary raising). This selection is already equivalent in
stock ET 2.60; this change extracts and tests it, not a new gameplay rule.

Evidence in the retained original modules:

| Effect | qagame | cgame |
| --- | --- | --- |
| Read target, unsigned range check against 52, ownership call | 0x2bd93..0x2bdb0 | 0x1b275..0x1b292 |
| Missing weapon becomes NONE; ordinary raising = 1 | 0x2bdcb..0x2bdee | 0x1b2ad..0x1b2d0 |
| Owned target; original dropping-to-reload = 4 becomes raising-to-reload = 2 | 0x2c245..0x2c25f | 0x1b725..0x1b73f |
| Missing target still preserves reload intent | 0x2c82d..0x2c839 | 0x1bced..0x1bcf9 |

NITMOD_CommitWeaponChange uses native WP_NUM_WEAPONS and named state enums,
never original offsets or numeric weapon IDs. The native caller preserves
oldweapon before this call; nextWeapon, timers, inventory, animations and
all other state remain unchanged. Subsequent native finish effects remain
in PM_FinishWeaponChange. A null pointer returns -1 without dereferencing.
Unsigned bit testing avoids signed shift overflow at inventory bit 31.

Tests cover every native target plus INT_MIN, -1, WP_NUM_WEAPONS and INT_MAX;
every native state and adjacent invalid states; empty, single-bit, full and
all-except-target ownership. Whole-state comparison enforces the two-field
mutation contract. A source check pins the call and preservation of oldweapon
in the actual shared cgame/qagame function. These are host unit/source tests,
not an original-module execution harness. Full timing/animation parity,
engine replay and Linux-i386/WASM validation remain outstanding.
