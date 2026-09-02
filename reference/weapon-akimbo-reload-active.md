# Active akimbo reload request correction

## Evidence and reproduced defect

Original manual reload accepts either underfilled hand. The sidearm branch
at qagame `0x2a9e8..0x2aa38` resolves the sidearm clip and compares its
capacity, then falls back to the main-hand comparison at `0x2a954`.
Cgame has the equivalent branch at `0x19ec8..0x19f18`, falling back to
`0x19e3c`. Automatic reload requires both clips empty and reserve present.
The complete original begin bodies (`0x28730..0x28a4f` and
`0x17c40..0x17f5f`) have no additional full-magazine veto.

Native outer request handling already checked both hands correctly. Its
inner begin function then compared `ammoclip[item->giAmmoIndex]` to the
target capacity. For the four akimbo identities this indexes the sidearm
clip, incorrectly rejecting an underfilled main hand when the sidearm is
full. The new integration test failed at the expected RELOADING state
assertion before the product change and passed afterward.

## Product scope

The shared `PM_BeginWeaponReload` bypasses this legacy full-magazine check
only for `BG_IsAkimboWeapon` identities accepted by the reviewed
`NITMOD_ReloadWeaponEligible` map: akimbo Luger, Colt and their two silenced
variants. Other weapons retain their current full-magazine guard.
Normal outer requests with both hands full still do not reload. Direct
begin calls for mapped akimbo now follow the original absence of this
guard; this must not be confused with outer request eligibility.

No reserve alias, capacity, timing, transfer order or protocol field changes.
Server movement and client prediction use the same edited source.

## Verification

`TestAkimboReloadRequests` executes real outer check, begin and completion
bodies across 1296 scenarios: four identities, three clip levels for each
hand (empty/one/full), reserve 0/1/30, manual/automatic requests,
READY/FIRING/FIRINGALT and neutral/left lean.

Rejected requests preserve the complete player state and emit no events.
Accepted requests check reload timing, a single predictable fill event,
one body event and unchanged inventory before completion. Completion is
compared bytewise with an independent main-first shared-reserve transfer
oracle, including idle animation and absence of extra events.

Host Debug build and 66/66 CTests pass. These are source integration tests
and original disassembly evidence, not execution of the original ELF,
model playback, full movement replay or Linux-i386/WASM release proof.
