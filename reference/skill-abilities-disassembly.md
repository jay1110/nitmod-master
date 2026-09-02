# Skill ability prerequisites

Original qagame SHA-256:
`84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49`.
Addresses are ELF virtual addresses, not Ghidra rebased addresses.

## Adrenaline eligibility

EntHasAdren at 0x814b0 (size 0xb0) loads entity->client at original offset
0x190. ClientHasAdren at 0x81560 (size 0xa0) takes the client directly.
Both test client+0xed8 bit 0x10: the first-aid unlock mask, NOT numeric
skill level. G_SetPlayerSkill establishes the seven masks from 0xed0 in
four-byte steps; first aid is index 2. Both then inspect client+0xbc8,
mapped to sess.playerType, accepting classes 0..4 only.

The allowed-class Cvar is g_adrenClasses at ELF 0x2e3ef80: PIC base
0x2a4614 plus 0x2b9a96c, with integer field +12. Allowed bits are soldier
1, medic 2, engineer 4, field ops 8, covert ops 16. Unknown classes return
false. Native ET's medic/level-four test is not an equivalent replacement.

g_nitmod_abilities.c implements both typed wrappers using explicit caller-
owned unlock and configuration masks; it never reads private offsets.
Null pointers return false as deliberate hardening. These helpers are built
but NOT called by active gameplay yet: private unlock storage, class changes,
inventory reconciliation and corresponding Cvars still need integration.

## Immediate ammunition selection

G_UpgradeSkill at 0xce47b..0xce498 loads g_adrenaline (0x2e48400), not
g_adrenClasses. Bit 4 selects one round and takes priority; otherwise bit 1
selects zero rounds, otherwise twelve. The following AddWeaponToPlayer call
uses zero reserve ammo and does not select the weapon. G_NITMOD_AdrenalineClip
reconstructs only the clip argument, without granting or removing weapons.

The original battle-sense/binocular branch returns before this adrenaline
path, including when AddWeaponToPlayer reports failure. The engineering
branch when adrenaline is unavailable writes INT_MAX at client+0x158;
this destination is not safely mapped and remains unported. No generic
weapon removal is invented for skill downgrades: separate original client
reconciliation paths clear the adrenaline weapon when eligibility is lost.

## Tests and remaining evidence

The inner adrenaline inventory reconciliation from ClientThink_checkWeapons
is now implemented as G_NITMOD_ReconcileAdrenaline. ELF 0x3f740..0x3f788
checks ownership of weapon 0x2b, calls EntHasAdren, and clears that bit at
client+0x3d4 if eligibility fails. A second path at 0x3f813..0x3f88f performs
the same operation after generic disabled-weapon processing. Both map to
the native ps.weapons bit array and WP_MEDIC_ADRENALINE constant.

Only the weapon ownership bit changes: no ammo reset, selected-weapon change,
powerup cancellation or automatic grant when eligibility returns is added.
20480 combinations test five classes, 32 class masks, 64 unlock masks and
ownership present/absent. Full client comparisons check mutation boundaries;
repeated calls and class/unlock-loss transitions are tested separately.

This is NOT the complete ClientThink_checkWeapons port. The outer guards are
now resolved: client+0x54d8 is the server-demo client marker, client+0xd bit
0x10 is pm_flags bit 0x1000 (PMF_FOLLOW), and entity+0x2c8 is health.
ELF 0x3f6ac..0x3f6d4 skips demo clients, following spectators and health <= 0.
It does not directly test PMF_LIMBO. G_NITMOD_CanCheckWeapons expresses these
guards; G_NITMOD_CheckAdrenaline composes them with the recovered revocation.
Null pointers also reject safely as deliberate hardening.

ClientConnect and ClientUserinfoChanged compute the demo marker from engine
Cvars sv_demoState and sv_demoClients: state 1..3 and clientNum < demoClients.
The userinfo store is confirmed at ELF 0x4a89e. The marker is cached, not the
bot flag. G_NITMOD_IsDemoClient reconstructs the classification; negative
client numbers deliberately reject. It makes no engine calls or state writes.
35,912 small-range combinations and integer boundary cases test classification.
524,288 guard/inventory cases cover all 16-bit flags, demo/non-demo and four
health values, checking that rejected clients remain byte-identical.

War mode and private client+0x5394 state, generic weapon restrictions,
loadout fallbacks and notifications remain unresolved. Cached demo-state
lifecycle and explicit skill/configuration ownership are not active yet.
The guarded operation therefore still has no gameplay call site and must not
be treated as a replacement for the entire original weapon check.

122880 combinations cover five native class constants, 64 allowed-class
masks, 64 unlock masks and six independent numeric skill levels. Both
typed wrappers must agree and leave the client byte-identical. Invalid
classes and null pointers reject safely. 512 clip cases cover low option
combinations and the high unsigned bit. Original-module execution, inventory
side effects and replay parity are still pending.
