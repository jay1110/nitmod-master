# Active reload while leaning

## Original evidence

The complete `PM_BeginWeaponReload` bodies in the preserved i386 originals
were inspected: qagame `0x28730..0x28a4f` and cgame
`0x17c40..0x17f5f` (exclusive ends). Neither contains a lean veto.
The flow checks ready/normal-fire/alternate-fire state, current reserve,
MG42/definition-based midclip restrictions and target eligibility before
body-animation dispatch. First-person animation gates do not cancel reload
timing or the predictable fill-clip event. Original hashes remain recorded
in `original_nitmod_i386.sha256` and covered by reference-artifact tests.

## Narrow activation

Shared `src_2.60/game/bg_pmove.c` now retains the native lean veto only when
`NITMOD_ReloadWeaponEligible(weapon)` is false. The 39 reviewed eligible
native identities can therefore reload while leaning whenever the other
existing native gates permit it. This is not a new eligibility gate: an
unmapped identity without lean still follows its existing native path.

State, current-reserve, midclip and full-magazine checks remain in their
existing order. The adrenaline reserve-alias exception remains unchanged.
Firing restrictions while leaning are unrelated and were not modified.
Both qagame movement and cgame prediction compile this shared source;
there are no protocol, userinfo, UI or structure-layout changes.

## Executed coverage

`TestLeaningReload` executes the verbatim product functions and compares
each result to the same input without lean. Its 4212 comparisons cover:

- 39 mapped reload identities;
- READY, FIRING and FIRINGALT;
- available reserve/empty clip, empty reserve, full clip;
- direct begin, manual outer check and automatic outer check;
- standing/prone and left/right lean.

The comparison checks the whole player state (except the deliberately
different lean input), whole pmove extension, body-event arguments and
absence of unexpected condition calls. At least one baseline must start
reload, preventing an all-rejected test from passing vacuously.
Existing 288 state/outer-check and 144 scoped-return tests now expect lean
to permit reload, while retaining full-magazine rejection. The source
contract checks the fallback explicitly.

Host Debug build and all 66 CTests pass. This is original control-flow
evidence plus executed host regression coverage, not an original-ELF
replay, whole-PM_Weapon scheduler test or Linux-i386/WASM release proof.
Original definition/ability integration and remaining inventory-policy
differences are still open.
