# Client projectile timing and bullet impact distance

## Reconstructed paths

Original reference: `original_nitmod_shared_objects_32bit/cgame.mp.i386.so`,
SHA-256 `45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f`.

- `CG_CalcEntityLerpPositions`, ELF `0x5b0e0`, size 1116;
  projectile branch `0x5b2e0..0x5b537`.
- Original cvar table: `cg_projectileNudge=1`, archive;
  `sv_fps=20`, read-only (64); `cg_markDistance=384`, archive.
- `sorted/cgame_effects.c`, bullet-impact distance gate: scoped weapon IDs
  39..41 bypass distance; other bullet marks/material sounds require distance
  strictly below `cg_markDistance.integer`.

Typed implementation lives in `cg_nitmod_config.c`, integrated at the
noninterpolated trajectory path in `cg_ents.c` and the existing bullet-impact
gate in `cg_weapons.c`. Original-protocol only; native/reconstructed ET260
keeps its prior timing and 384-unit distance. No assets or server messages changed.

With positive nudge, missiles owned by `cg.clientNum` advance one server frame
(`1000 / sv_fps`). Other missiles additionally advance snapshot ping for
mode 1, or the configured millisecond value for modes above 1. Position and
angles use the same shifted time; entity trajectory fields are not mutated.
As in the original projectile branch, mover adjustment is bypassed.

Disassembly `0x5b3a8..0x5b3bc` confirms the original trace start is evaluated
at the SAME shifted time as its end. Preserve the zero-length MASK_SHOT trace
and fraction handling, rather than claiming or inventing a collision sweep.

Portability guards (intentional differences): missing snapshots, nonpositive
server FPS, negative remote ping, and signed timestamp overflow fall back to
the current timestamp. The original division/overflow is not safe for these
inputs. Already-interpolated entities, player extrapolation and early-transition
logic are outside this batch; nonmissile mover behavior remains the ET260 path.

Mark distance gates only the existing bullet mark/material-sound branch:
particles and explosions are not suppressed. All three scoped rifle exceptions
are preserved, including when the configured distance is zero or negative.

## Verification

`CheckProjectileOptions` in `test_original_charge_dispatch.c` exercises 450
protocol/nudge/FPS/ping/ownership combinations, actual trajectory evaluation,
trace endpoints/mask, unchanged entity state, scoped distance exceptions,
strict distance boundary, null state and overflow guards.

Native CTest and WASM build/load smoke results are recorded in the task report.
These are not a live dedicated-server visual comparison or complete movement
parity. Full original prediction, private weapons and projectile rendering
remain separate reconstruction work.
