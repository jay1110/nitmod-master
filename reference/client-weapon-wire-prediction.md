# Weapon wire identities and prediction reconciliation

## Diagnosed mismatches

The original Nitmod weapon enum supplied with the report removes ET's
MAPMORTAR and LOCKPICK slots and relocates TRIPMINE. MP40 remains 3, but
most identities from 17 onward differ. Using raw server inventory bits,
ammo indices and weapon IDs directly as typed ET IDs therefore selects
unrelated weapons or makes legitimate weapons unavailable.

The predictable-event cache held native Pmove event IDs, while server
confirmations retained original Nitmod IDs. Comparing them numerically
replayed equivalent shots as corrections. The starting snapshot ring was
also copied unchanged into native prediction. Finally, CG_FireWeapon
selected last-shot sounds using the raw entity event instead of the
already-translated dispatch event.

## Implemented boundary adapters

- Translate original snapshot player weapon, next weapon, inventory bits,
  ammo, clip and heat indices to typed ET indices once in CG_ReadNextSnapshot.
- Translate weapon-bearing player/corpse/missile/event entities. Do not
  translate the overloaded `weapon` field on explode/rubble effects.
- Convert outgoing usercmd weapon selection back to the original IDs;
  convert engine usercmds to typed IDs before prediction consumes them.
- Translate playerinfo primary/latched/secondary weapons and outgoing
  limbo team/loadout selections consistently.
- Native-layout servers, including reconstructed localhost servers carrying
  `nitmod_csLayout=et260`, keep the existing identities and command ABI.
- Normalize the copied predictable event ring and compare server
  confirmations in the same identity space as cached native prediction.
  External events and snapshot event numbers remain original wire values.
- Pass the dispatch event explicitly to CG_FireWeapon so original last-shot
  events select last-shot sounds without rewriting snapshot event IDs.

## Brass models

Original `CG_RW_ParseClient` accepts `brassModel`; original
`CG_MachineGunEjectBrassNew` uses that weapon-specific handle or a fallback
mask `0x10e0387` covering original IDs 22..46. Those typed media fields and
the first-person selector are now implemented. MP40 defaults to small-gun
brass, not panzerfaust brass. Actual wrong-model playback in the reported
browser session has **not** been reproduced; the new model path and tests
must not be presented as proof of its complete root cause.

## CS_PLAYERS clarification

The supplied original cgame binary **does not** use CS_PLAYERS=64.
CG_RegisterGraphics starts player registration at `0x2b1`, and
CG_ServerCommand subtracts `0x2b1` when invoking CG_NewClientInfo. This is
689, matching the canonical ET tree. Keep raw player records at that index.
The user's value 64 may refer to a different build or constant; no global
remapping to 64 is introduced based on that unverified claim.

## Verification and limits

Full-cgame regression tests cover all 48 representable original identities
(including NONE): snapshot inventory/ammo/clip/heat conversion, engine
usercmd round trips, explicit shifted-ID examples, and preservation of the
rubble gravity field. Native-layout usercmd behavior is tested separately.
Real fire dispatch tests cover original 33/34/35, one predicted shot plus
two server confirmations, sound selection and brass callback counts.
Brass file parsing is tested through actual weapon registration.

Original poison syringe (47), bomb (48), poison bomb (50), and poison mine
(51) still lack typed gameplay implementations. They are not aliased to
unrelated ET weapons. Weapon item-model indices, animation differences,
timings, recoil and other original gameplay semantics still require work.
These changes are not a claim of full weapon parity or a verified live
Dedicated-server/browser join. Original PK3/pak content remains unchanged.
