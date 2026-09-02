# Weapon definition file selection

Reference: original qagame `BG_RegisterWeapon`, ELF virtual address `0x363c0`
(Ghidra rebased address `0x463c0`). The original artifact is hash-pinned by
`tools/extract_weapon_paths.py`; no original file is modified.

The PIC base is recovered from the thunk return and add at `0x363d8`.
The indexed load at `0x36492` locates the 52-entry relative jump table.
Each supported case assigns EDI (alternate selector) and EBP (filename).
The common loader passes EDI to `BG_RegisterWeaponFromWeaponFile` at
`0x364ea`. The extractor checks the actual instruction operands, rather
than treating the decompiled call with missing arguments as authoritative.

44 identities have named ET 2.60 equivalents in `nitmod_weapon_paths.c`.
The test keeps a separate explicit original-ID-to-native-name translation:
original numeric IDs must not be copied into native weapon arrays.
Original IDs 47 (poison), 48 (bomb), 50 (poison gas), and 51 (gas landmine)
have no selected native representation and are excluded.
Native NONE, ARTY, MAPMORTAR, VERYBIGEXPLOSION, DUMMY_MG42 and LOCKPICK
return no descriptor. Original cases 0, 13, 17 and 32 have no file.

Only original IDs 39, 40, 41 and 46 select `both_altweap`: scoped Garand,
scoped K43, scoped FG42 and deployed MG42. Their files are shared with
the base weapons. Deployed mortar uses `mortar_set.weap` and normal `both`.
The original CARBINE identity uses `m1_garand.weap`; GARAND uses
`m1_garand_s.weap`. Naming alone is not sufficient to infer the mapping.

`G_NITMOD_LoadNativeWeaponClassMask` joins the caller's preferred directory
and verified basename, with `weapons/` as open-failure fallback. It passes
the recovered alternate selector to the existing strict parser. Paths
must fit MAX_QPATH including NUL; an overlong path fails without opening
anything or changing the output mask. Equal preferred/fallback paths are
not opened twice (deliberate error-path simplification). Empty directories
are rejected. A successful open followed by invalid contents does not
trigger fallback, matching the recovered loader control flow.

Evidence: executable lookup/boundary tests, composed mocked engine-source
tests, and hash-pinned extraction comparison for all 44 filenames and
selectors. This is not an original-engine gameplay transcript. The parser
still supports only mask-only selected blocks, not full weapon attributes.
Registration/reset/reload ownership and native pickup activation remain
pending; neither inventory nor client protocol changes in this increment.
