# Rifle-grenade switch policy and remembered mode

The reviewed original pairs are IDs 22/36 (KAR98/GPG40) and 23/37
(CARBINE/M7). Existing alternate and inventory-alias tests compare these
typed identities against both hash-pinned original modules.

| Phase | Condition | Duration | Additional effect |
| --- | --- | --- | --- |
| Drop, attaching | target magazine == 0 and target reserve != 0 | 0 ms | request existing native PM_ReloadClip(target) |
| Drop, all other paired cases | any | 0 ms | no transfer request |
| Raise, attaching | any | 2350 ms | alternate-mode animation |
| Raise, returning to rifle | old launcher ammo-alias magazine != 0 | 1347 ms | alternate-mode animation |
| Raise, returning to rifle | old launcher ammo-alias magazine == 0 | 0 ms | no body or first-person switch animation |

Drop evidence: qagame 0x2a61c..0x2a661 / cgame 0x19afc..0x19b41.
The original directly indexes target magazine and reserve, requires a zero
magazine and a nonzero reserve, and calls PM_ReloadClip. Return-to-rifle
drop has no such transfer, only zero duration.

Raise attachment loads 0x92e at qagame 0x2c959 / cgame 0x1be19.
Raise return calls BG_FindAmmoForWeapon(oldweapon) but reads that index in
ammoclip, NOT ammo: qagame 0x2c87d..0x2c89a / cgame
0x1bd3d..0x1bd5a. A nonzero result selects 0x543. The zero branch updates
the weapon animation condition and returns without animations (qagame
0x2c8f9..0x2c923 / cgame 0x1bdb9..0x1bde3).

Remembered grenade mode is bit 1 in native pmoveExt.silencedSideArm. Rifle
targets clear it before same-weapon return: qagame 0x2be1f..0x2be28 /
cgame 0x1b2ff..0x1b308. Launcher targets set it at qagame
0x2c486..0x2c48f / cgame 0x1b946..0x1b94f. Bit 0 (silencer) and all
other bits are preserved; no syringe/adrenaline mode is inferred.

## Typed integration

NITMOD_RifleGrenadeDrop returns only the native transfer request; the live
shared begin function still invokes PM_ReloadClip and retains its timing,
event and body-animation order. It does NOT activate the separate recovered
reload implementation. NITMOD_RifleGrenadeRaise uses the reviewed inventory
ammo alias of the explicit old weapon, since playerState.weapon has already
been committed to the new weapon. It never modifies inventory. The finish
caller retains existing condition updates, animation gating and time addition.
The remembered-mode helper runs before the same-weapon early return.

This replaces duplicate cases with tested ET-equivalent behavior. Negative
clip/reserve values preserve the original exact-zero/nonzero predicates;
this policy layer neither legitimizes invalid inventory nor adds validation
that would silently change the branch semantics. Null/unsupported requests
leave outputs unchanged. Numeric original weapon IDs never index native data.

## Tests and remaining work

45000 combinations cover all 2500 native pairs, six magazine values including
integer extremes, and three reserve values; each exercises drop and raise.
Whole-state comparisons ensure read-only behavior. The return oracle uses
the actual native BG_FindAmmoForWeapon rather than the recovered alias helper.
468 mode cases cover bit preservation, idempotence and composition with the
pistol helper. Null/invalid inputs and actual caller ordering are also checked.

The host build and all 65 tests pass. These are policy and source-contract
tests, not execution of the original modules. Native PM_ReloadClip remains a
separate boundary; engine event/animation replay, complete switch parity and
Linux-i386/WASM release validation remain pending.
