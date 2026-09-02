# Begin-reload inventory and weapon eligibility

## Native state gate and isolated state/timer effects

NITMOD_ReloadStateAllowed accepts native WEAPON_READY, WEAPON_FIRING and
WEAPON_FIRINGALT. Original 5/6 mean normal/alternate fire: qagame PM_Weapon
calls PM_AltFire at 0x2cc04, stores 5 on false at 0x2cc19 and 6 on true at
0x2cdbc; cgame equivalents are 0x1c0c4, 0x1c0d9, 0x1c27c. The original
begin-reload gate accepts 0/5/6 at 0x28756..0x28766. Native values 5/6
(READYING/RELAXING) are therefore explicitly rejected, not reused numerically.

NITMOD_PrepareReloadInventory applies this gate before the existing inventory
sequence. Empty reserve resets only native weaponstate to WEAPON_READY;
blocked/invalid/allowed outcomes leave the player state unchanged. This is an
opt-in composed helper, not an active PM_BeginWeaponReload replacement.

NITMOD_ApplyReloadTiming implements the separately observed timer effect:
READY adds the supplied duration to weaponTime (qagame 0x288a0), firing
uses max(existing time, duration) (0x288d0..0x288d5), then sets RELOADING
(original 7 stored at 0x288ac, translated to the native enum). Negative
durations and ready-state overflow reject atomically. Negative existing times
remain supported. Caller must calculate duration and pass all start checks
first. Animation and EV_FILL_CLIP emission are deliberately not performed.

Tests cover 12 native/invalid states across seven timer boundaries and five
durations (420 cases), plus three reserve states for each (36 cases).
Whole-state comparisons verify that only the documented fields change.
No complete mapping of unrelated original weapon states or native gameplay
activation is claimed; fast-reload duration, animations and events remain.

NITMOD_ReloadWeaponEligible translates the original begin-reload range check
to supported native ET identities: original IDs 1..15 or 22..51. qagame
compares at 0x287c0..0x287ce; cgame at 0x17cd0..0x17cde. The 44 reviewed
identities contain 39 passing and five excluded weapons: SMOKETRAIL, MEDKIT,
BINOCULARS, PLIERS, SMOKE_MARKER. Unsupported identities are rejected rather
than interpreting a native numeric ID as an original ID. The reference test
compares all native results against the original ranges through the explicit
reviewed identity map. This is not a claim that every passing weapon can
actually reload in gameplay; outer PM_CheckForReload has further exclusions.

NITMOD_CheckReloadStartInventory composes the known inventory-side sequence:
read reserve for the CURRENT state->weapon, report empty reserve first,
check the requested TARGET weapon's midclip rule, then target eligibility.
Server reads current weapon at 0x28782 and resolves its ammo at 0x2878b;
zero reserve branches at 0x28798 to the zero weaponstate store at 0x287f2.
Client current-weapon read is 0x17c92, reset store 0x17d02. Consequently the
empty-reserve outcome takes precedence even over an ineligible target.

The helper returns an explicit result (invalid, blocked, empty reserve,
inventory allowed) and does NOT reset weaponstate. It must only be used after
the outer weapon-state gate (now provided by NITMOD_PrepareReloadInventory):
original numeric states cannot be copied directly into ET's enum. Timers,
animations, events and reload initiation remain outside the inventory helper.

46464 combinations cover all 44 current/target identities, negative/zero/
positive current reserve, empty/nonempty target clip, both option values and
the MG42 ability bit. Differing current/target reserve slots explicitly test
that the target's reserve does not replace the current weapon's reserve.
All checks compare the entire player state for immutability. Invalid pointers,
unsupported identities and negative clip counts are separately tested.
Unknown identities/null options reject before reserve processing as deliberate
API hardening; valid supported identities preserve empty-reserve precedence.

No active engine hook or network change is introduced. This is host-test and
disassembly evidence for a partial gate, not a full original-engine replay.
