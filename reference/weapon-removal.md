# Weapon removal and war-mode entry

Update: the war=4 entry branch is now gameplay-active; see
reference/active-war-entry.md. The integration-pending statements below
describe the earlier isolated recovery stage.

Original qagame SHA-256:
`84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49`.
G_RemoveWeapons starts at ELF 0x3f160 and clears 46 explicit ownership bits.
It does not clear all inventory, ammo, binocular key flags or selected weapon.

Original weapon IDs differ from native ET. The bg_itemlist symbol at
0x2a59a0 is 4088 bytes. BG_InitWeaponStrings at 0x1c7c0 confirms 56-byte
records, type at +36, weapon tag at +40 and name pointer at +28.
`tools/extract_weapon_items.py` reads identities from the hash-pinned ELF;
53 weapon item rows include aliases and duplicate classnames. In particular,
weapon_landmine is shared by normal and poison mines: classname alone is
not a unique mapping key.

Examples: original adrenaline 43 maps to ET WP_MEDIC_ADRENALINE (46),
binoculars 19 to WP_BINOCULARS (20), mobile MG42 29 to WP_MOBILE_MG42 (31).
G_NITMOD_RemoveWeapons uses named native constants for 42 mapped entries.
Poison syringe (47), bomb (48), poison bomb (50) and poison landmine (51)
have no native equivalents and are deliberately not assigned arbitrary bits.
Tripmine 49 maps by original item identity to native WP_TRIPMINE.

Native knife, satchel detonator, dummy/effect weapons, lockpick and unused
inventory bits survive. Unsigned bit arithmetic avoids sign-bit shift UB.
Tests exercise every one of the 64 inventory bit positions and idempotence,
checking the whole client: only the listed ownership bits may change.
The original identity extractor has a separate hash-pinned regression test.

At ClientThink_checkWeapons 0x3f896..0x3f8f9, war mode 4 and a zero private
marker at client+0x5394 trigger removal, selected weapon 1 (knife), event
0x19 with parameter zero, then marker=1. This is a one-shot latch, not an
unconditional per-frame removal. The event mapping is now resolved: original
cgame CG_EntityEvent cases 0x19/0x1a share no-ammo sound/auto-switch logic,
passing (event != 0x1a) to CG_OutOfAmmoChange. Native cg_event.c implements
this pair as EV_NOAMMO/EV_WEAPONSWITCHED. Raw event 25 would incorrectly
produce EV_WATER_TOUCH in ET. Nitmod-only weapon switch exceptions remain
outside this mapping; no blanket event-number translation is implied.

Original ClientSpawn clears the full 0x54dc-byte client, saving/restoring
specific pers/session and other fields. The latch at 0x5394 is not among
those preserved fields. The typed state exposes an explicit per-spawn reset;
mode changes alone do not reset it. This is source-based evidence, not replay.

g_nitmod_war.c composes guards, mapped removal, knife selection, native event
and the final latch write. An event spy verifies call order and arguments;
tests cover repeated calls, guards, mode changes, explicit spawn reset and
missing knife ownership. Selecting the knife does not grant its weapon bit.
Native spawn ownership, full mode configuration and weapon restrictions are
still unintegrated: this adapter has no active gameplay call site.

The removal helper is built through CMake/SCons but not gameplay-active.
It neither grants the knife nor implements the complete war mode, and host
tests do not constitute original-module execution or Linux/WASM parity.
