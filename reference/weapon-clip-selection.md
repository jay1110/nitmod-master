# Native clip and akimbo selection

Original BG_AkimboFireSequence at ELF 0x21240 recognizes original weapon
IDs 34/35/44/45. Empty akimbo clip selects the sidearm; otherwise empty
sidearm selects akimbo; with both nonempty an even sum selects akimbo.
BG_AkimboSidearm's lookup at ELF 0x22dfa0 maps these IDs to 7/2/7/2,
respectively: native Colt/Luger, including silenced variants. These match
the existing ET helper semantics.

Three native helpers were moved from bg_misc.c to nitmod_weapon_akimbo.c:
BG_IsAkimboWeapon, BG_AkimboSidearm, BG_AkimboFireSequence. They remain active
under their original public names. The parity calculation now uses unsigned
XOR instead of signed addition, preserving parity without signed overflow.
CMake and SCons include this unit for cgame, qagame and ui (whose bg_misc
also uses BG_IsAkimboWeapon). No native sidearm or normal firing rule changes.

NITMOD_SelectWeaponClip uses native BG_FindClipForWeapon/item aliases, then
the native akimbo helpers. Like the original PM_WeaponUseAmmo and
PM_WeaponAmmoAvailable, it resolves sidearm's clip for the sequence decision,
but selects the sidearm weapon ID directly when that hand fires. It does
not silently substitute a different alias for the latter operation.
NITMOD_ConsumeSelectedWeaponClip passes the selected slot and that slot's
ammo record to the already tested exact-zero-refill operation.

New adapters reject invalid IDs, invalid clip aliases and negative clip
counts without changing state/output. Bounds include the supplied ammo-table
length. They handle clip mode only, not noWeapClips/reserve-ammo mode. Native
PM_Weapon call sites still use the pre-existing path; there is no new Cvar,
wire message, registry lookup or unconditional gameplay refill.

Tests exercise 4 * 17 * 17 = 1156 akimbo clip pairs, actual moved helpers,
selection without state mutation, consumption/refill into exactly the chosen
slot, integer parity boundaries and native-type scoped/base alias routing.
Only BG_FindClipForWeapon is replaced by a controlled alias fixture; this is
not a proof that every original private item alias matches native ET. Full
playerState_t comparisons guard unrelated state. Runtime configuration and
original item-table alias parity remain separate integration work.
