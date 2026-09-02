# Adrenaline class-tool spawn grant

G_AddClassSpecificTools (ELF 0x49f60) returns immediately for g_war 1..4.
Otherwise its part.3 implementation checks ClientHasAdren and enters the
adrenaline grant at 0x480b0. This differs from the skill-upgrade grant:
the spawn path reads defaultStartingClip from ammoTableMP +0xc28 and
defaultStartingAmmo from +0xc24 (original weapon 43, stride 72). Options
mask 4 overrides the clip to one; otherwise mask 1 overrides it to zero.
The first-aid mask 4 bonus adds two. The wrapper's war gate means the
spawn operation skips entirely in those modes, rather than merely dropping
the bonus as the separate upgrade operation does.

G_NITMOD_GrantAdrenalineSpawn reconstructs this isolated inventory effect
using explicit caller-supplied loaded ammotable_t defaults. It preserves
independent native adrenaline slots and never resolves the native syringe
alias. Reserve and clip are assigned, the weapon bit is set, and current
weapon/syringe stock/other client state remain unchanged. Invalid selected
defaults and overflow when adding the bonus reject before any mutation.
An invalid unused default clip does not block an explicit 0/1 option override.

286720 spawn combinations supplement the existing 286720 upgrade cases.
Nonstandard defaults 7/9 distinguish the two behaviors. Tests compare the
whole gclient_t and cover repeated calls, overflow, invalid reserve/clip,
war/eligibility early returns and nulls. An integration test starts with
hash-verified original defaults, runs real source/parser/registry loading
with engine-source doubles, and supplies that record to the spawn operation.

There is no active spawn/skill hook. These helpers still omit the original
Bot_WeaponGameToBot/Bot_Event_AddWeapon notifications: the repository's
native 2.60 bot system does not expose that Omni-bot API. The surrounding
class tools, game-mode rules, authoritative configuration and client-side
separate-ammo consumers remain to be reconstructed before activation.
