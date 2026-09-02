# Original ammo/timing defaults

Original qagame symbol ammoTableMP is at ELF 0x2a69a0, size 0xea0:
52 records of 72 bytes. This is not the native ET ammotable_t stride.
tools/extract_weapon_ammo.py verifies the original SHA-256 before reading
the first ten integer slots. The nine editable destinations were previously
mapped against BG_RW_ParseDefinition; uses is now also mapped through the
PM_Weapon consumer (see below). Later original fields, including
any numeric means-of-death values, are deliberately not decoded or copied.

nitmod_weapon_defaults.c translates 44 original weapon identities to named
native enums, reusing the identity correspondence established for filenames.
NITMOD_WeaponAmmoDefaults copies maxammo, maxclip, defaultStartingAmmo,
defaultStartingClip, reloadTime, fireDelayTime, nextShotTime, maxHeat and
coolRate and uses into a caller-supplied native ammo record. Native mod is preserved;
unsupported identities and null output fail without writes. The helper is
built for both cgame and qagame, with no global table mutation.

Examples of real differences from the native ET table: original knife has
maxammo/maxclip 8 and starting clip 4 (native 999/999/0); original hand-grenade
maxclip is 9 (native 15). These are on-disk baseline values before .weap
overrides, not necessarily final live-server settings. They remain inactive
until the complete weapon loading/prediction path can use them consistently.

Verification: all 440 copied values are compared with hash-pinned original
bytes by test_weapon_ammo_reference.py. Executable tests cover every native
weapon identity against the supported path set, invalid identities/null output,
all 44 consumption values, mod preservation, concrete knife/grenade differences and composition
with the actual registry/source/parser. An empty definition retains the
provided reconstructed defaults without inventing class/recoil overrides.

Remaining work: independently map original means-of-death identifiers,
complete other weapon attributes, decide authoritative initial/reload defaults
across both modules, then connect registry lifecycle to engine initialization.
This does not claim original-engine runtime, i386 ABI or WASM parity.

## Consumption field evidence

Original PM_Weapon reads ammoTableMP[weapon].uses at ELF 0x2cc30, using the
72-byte stride calculated at 0x2cc2b and offset +4. The result in EDI is
compared with PM_WeaponAmmoAvailable's output at 0x2cdf2 and with reserve
ammo at 0x2ce1a. The same amount is passed as argument two to
PM_WeaponUseAmmo at 0x2cced..0x2ccfa, whose subtraction occurs at 0x2aabd.
Native bg_pmove.c uses ammotable_t.uses for ammoNeeded in the same role.
This establishes the field by use, not merely by table position.

Among the 44 mapped identities, 12 have baseline uses=0 and 32 have uses=1.
The executable test checks every identity against those groups, preserves
mod sentinels, and follows reconstructed uses through an empty definition
and the actual registry. The parser still has no editable 'uses' attribute;
it preserves whatever verified default the caller supplies.

The original has a separate knife/weaponstate==6 override at
0x2cde3..0x2cdef, changing the needed amount to one. This is not activated
or represented as a permanent knife-table value. Infinite-ammo refill,
knife alternate attack and other state-specific consumption rules remain
separate reconstruction work. Numeric mod values still require semantic
translation before any copying into native ammotable_t.mod.
