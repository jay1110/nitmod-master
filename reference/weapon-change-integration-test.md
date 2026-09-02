# Executed native weapon-change integration test

The new `nitmod_weapon_change` CTest target compiles the actual product
definitions of PM_BeginWeaponChange, PM_FinishWeaponChange, PM_ReloadClip,
PM_AddEvent, PM_StartWeaponAnim and the four switch-animation selectors.
`tools/extract_weapon_change_test.py` extracts complete definitions verbatim
from bg_pmove.c into the build directory. It ignores braces inside comments
and literals and fails on missing/duplicate definitions. CMake regenerates
the header when either the product source or extractor changes. There is no
hand-maintained copy of these functions and no production compile-time hook.
The host test is available when the Python interpreter is found by CMake.

The executable links actual native item/ammo tables, bit checks, predictable
event ring, vector math and reconstructed switch helpers. BG_AnimScriptEvent
and BG_UpdateConditionValue are boundary doubles which validate arguments and
record event/condition selection. The body-script double returns -1, covering
the missing-script outcome without pretending to run a model animation.

## Scenarios

- 576 combinations: all 18 directed scope, pistol, rifle-grenade and deploy
  pairs, both reload intents, prone/non-prone, empty/nonempty old magazine,
  and normal/dead/animation-timer/command-NONE first-person gates.
- Actual drop state/time and event-ring contents, then simulated expiry of
  drop time and actual finish state/time, condition update and animations.
- Original empty-launcher return suppresses both switch animations; magazine
  attachment uses real native PM_ReloadClip and consumes one reserve round.
- Prone mortar deployment is rejected; mounted direction changes only on
  deployment and remains untouched on every other pair.
- Nine begin guards reject without player-state mutation: respawn, NONE,
  out-of-range target, unowned target, three excluded weapon states, spinup,
  and active grenade timer.
- Two between-phase ownership-loss cases commit NONE while retaining the
  proper raising/reload intent, with no additional predictable event.
- Knife/smoke same-weapon finish exceptions and ordinary Colt same-target
  early return execute the actual finish function, not just its predicate.

576 includes the prone-mortar cases which correctly stop at the begin guard;
not every combination reaches finish. The test checks shared source behavior,
not separate live engine client/server instances. Native effects are exercised
but the scheduler, rendering, model scripts and surrounding PM_Weapon dispatch
are not. It is not an original-i386 replay, whole-Pmove test or Linux/WASM ABI
verification. No gameplay behavior or protocol changed in this increment.

Host build succeeds; all 66 CTests pass including this new executable.

## Ordinary-switch and late-veto coverage

The executable additionally runs 38128 combinations for every native old/new
pair excluding same-weapon and alternate pairs: 2383 pairs times two reload
intents, two prone states and four first-person gates. Native enum identities
outside the recovered 44 are regression coverage only, not new original parity
claims. Prone MORTAR_SET targets stop at the existing late veto; the others
execute both real phases with 250 ms drop/raise. Tests verify:

- No accidental specialized timing, clip transfer or deployment direction
  capture on unrelated transitions; ammo/clip arrays remain byte-for-byte.
- Exact normal-versus-reload event selection for ordinary, rifle, grenade and
  mortar targets, including the last event-ring slot; finish preserves the
  complete event and parameter arrays without adding another event.
- Grenade timer resets only on the four existing target identities; a negative
  incoming timer otherwise survives. Scope spread resets only for scoped
  targets. Remembered mode bits use an independent expected-value calculation.
- Actual first-person drop/raise animation selection and gates, body-event
  selection, state transitions, and preservation of the entire extended
  movement state except the expected remembered-mode bit.

Sixteen mortar cases cover water levels 0 through 3, prone/non-prone and both
reload intents. The blocked cases compare whole player/extended state, with
only nextWeapon expected to change. Original qagame 0x2a2f4 writes nextWeapon
before the prone/water veto at 0x2a30b..0x2a31a; cgame likewise writes at
0x197d4 before 0x197eb..0x197fa. Thus this is intentionally different from the
early guards, which change nothing. Water levels 0..2 without prone permit
deployment, while exactly level 3 rejects. No broader movement permission is
inferred from this isolated function test.

These additions do not alter product code or claim original-machine-code,
full-engine, Linux-i386 or WASM replay coverage.
