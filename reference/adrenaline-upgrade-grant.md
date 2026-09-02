# Adrenaline skill-upgrade inventory effect

G_UpgradeSkill's adrenaline path calls AddWeaponToPlayer(client, original
weapon 43, reserve=0, option-selected clip, setcurrent=false). Its options
are already implemented by G_NITMOD_AdrenalineClip: mask 4 selects one,
otherwise mask 1 selects zero, otherwise twelve. The battle-sense binocular
early return and Lua hook are outside this isolated operation.

Original AddWeaponToPlayer (ELF 0x49d90) sets the weapon bit, assigns clip
through BG_FindClipForWeapon, assigns reserve through BG_FindAmmoForWeapon,
and only changes current weapon when requested. Original adrenaline aliases
both resolve to its own ID 43, unlike native ET's shared syringe alias.
This is mapped to native WP_MEDIC_ADRENALINE storage, not numeric index 43.

The ammo bonus must not be omitted: registration's weapon dispatch table
entry at ELF 0x234c2c is relative 0xffda58bc with PIC base 0x2a4614,
targeting 0x49ed0. That branch tests client+0xed8 mask 4 (first-aid unlocks)
and adds two to the ammo-indexed clip at 0x49ee5. g_war values 1..4 bypass
all these bonuses at 0x49df8..0x49e05. Therefore eligible upgrades can assign
14/2/3 outside those war modes, not only the initial 12/0/1 argument.

G_NITMOD_GrantAdrenalineUpgrade composes the recovered eligibility/class
mask, option selection, war-dependent bonus and the three inventory writes.
It sets the ownership bit, zeroes only the independent adrenaline reserve,
and assigns (not increments) that clip. It does not touch syringe stock,
selected weapon, powerups or other client state. Ineligible/null clients
do not change. The operation is isolated and has no active callers.

286720 rule combinations use real gclient_t with complete state comparisons.
Separate repeat tests ensure no cumulative bonus, option precedence, war
transition, retained syringe stock, invalid classes and null safety.

This is not the complete G_UpgradeSkill or AddWeaponToPlayer port. Original
Bot_Event_AddWeapon notification, authoritative unlock/Cvar storage, upgrade
dispatch ordering, spawn variants and client/prediction alias selection must
be integrated together before activation. Calling the native grant helper
here would overwrite syringe stock, so it is deliberately not used. No native
item alias, playerState ABI, wire contract or active spawn rule is changed.
