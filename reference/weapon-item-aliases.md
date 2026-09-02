# Original/native ammo and clip alias comparison

## Recovered shared inventory adapter

`nitmod_weapon_inventory.c` now provides an explicit, opt-in lookup of ammo
and clip slots for the 44 reviewed native identities. Both slots are returned
atomically; unknown/private identities and null output reject. No original
numeric weapon IDs enter native arrays. The native item table is unchanged.

The client confirms the same first-match scan: BG_FindClipForWeapon at
0x106e0 uses 56-byte stride, type +0x24, tag +0x28 and clip +0x34;
BG_FindAmmoForWeapon at 0x10730 returns +0x30. Client bg_itemlist is at
0x12ed00, size 4088. Its SHA-256 is pinned independently by the extractor.
The reference test executes the recovered lookup for every native weapon,
checks all 44 supported pairs against BOTH original modules and checks
unsupported IDs leave output unchanged. This establishes alias-data parity,
not gameplay or full item-table parity.

`NITMOD_SelectRecoveredWeaponClip` uses those slots and the reviewed akimbo
helpers. The real-table diagnostic checks 1156 akimbo pairs and 289
adrenaline/syringe pairs, composing adrenaline selection with the isolated
clip consumer and checking full player state. Null/negative/unsupported
selection rejects without changing output or state. This path is compiled
into cgame/qagame but has no active PM_Weapon hook. Reserve-ammo mode,
reload, pickup, complete weapon lifecycle and prediction integration remain
pending; the existing native selector deliberately retains syringe sharing.

Original BG_FindClipForWeapon (ELF 0x211a0) scans 56-byte bg_itemlist records
from item 1 until null classname, matching type==IT_WEAPON at +0x24 and
weapon tag at +0x28, then returns +0x34. BG_FindAmmoForWeapon (0x211f0)
uses the same first-match scan and returns +0x30. The hash-pinned item
extractor now includes these two aliases and each record's address.

The diagnostic executable links the real native bg_itemlist,
BG_FindAmmoForWeapon and BG_FindClipForWeapon from bg_misc.c. Unrelated
engine services are fail-fast stubs; alias lookups do not use them. The
reference test translates original IDs through the reviewed 44-identity map
and compares the actual native executable's result, preserving first-match
semantics even when the original table has duplicate entries.

Result: 43 of 44 mapped weapons have matching ammo AND clip aliases.
The sole identified difference is WP_MEDIC_ADRENALINE. Original ID 43 uses
its own ammo and clip ID 43, while native ET WP_MEDIC_ADRENALINE resolves
both to WP_MEDIC_SYRINGE. The test explicitly pins that difference and fails
on any additional discrepancy or silent change. It is not counted as parity.

Native sharing remains unchanged. Replacing it requires a coherent review
of spawn grants, ammo pickup, syringe/adrenaline inventory and prediction;
the isolated consumer is not permission to change these active systems.
The original numeric ID 43 is not the native adrenaline enum value and must
never be copied directly into native arrays.

The diagnostic also runs all 1156 akimbo clip pairs through the actual
native table, moved native helpers, new selector and new consumer, checking
full player state on each operation. This supplements (not replaces) the
controlled alias fixture used for malformed-alias boundary tests. Thus
standard Colt/Luger sidearm selection, including silenced akimbo variants,
now has both a real-native-data integration check and original alias evidence.
Silenced akimbo weapons also alias their akimbo-hand clip to the corresponding
unsilenced AKIMBO_COLT/AKIMBO_LUGER slot. The real-table fixture initializes
those shared slots, rather than incorrectly assuming one clip per weapon ID.

The snapshot is still host-side evidence, not an original-engine replay.
Private Nitmod-only weapon aliases and the complete active consumption/config
path remain outside this comparison.
