# Weapon visual option batch

## Restored dispatch

cg_tracers and cg_muzzleFlash are registered in cgame (typed handles) and UI
(menu Cvars), default 1 with CVAR_ARCHIVE, matching the original tables.
Original menus and pak content remain untouched.

CG_Bullet (original ELF32 0xd26d0; sorted cgame_math.c) distinguishes:

- Non-flesh moving tracers: mode 1 always allows them, mode 2 allows them only
  when sourceEntityNum differs from the viewed snapshot player; other modes
  disable them. Tracer attachment still uses otherEntNum2 when available.
- Flesh tracers: every nonzero mode permits the existing tracerChance test.
  The probability RNG is not consumed when the option rejects this path.

The native CG_Bullet now uses that typed predicate at both emission sites.
Existing muzzle calculation, water handling, chance checks and impact handling
are retained; disabling tracers does not suppress bullet impacts or sounds.

CG_AddPlayerWeapon (original 0xc9ea0; sorted cgame_ents.c, LAB_000db268)
allows the flash model if ps is NULL or cg_muzzleFlash is nonzero. The native
flash submission uses that condition, without disabling flame chunks, barrel
smoke, dynamic lighting or third-person weapons. Mounted-weapon paths elsewhere
are not globally gated. The change is not a global weapon-render early return.

CG_AddBulletParticles (0xce5d0) and CG_AddDirtBulletParticles (0xce650)
have original cg_impactparticles entry guards. Both native generators now
return before allocation and RNG when disabled. Their existing callers inherit
the option, extending the previous sparks-only gate to falling bullet debris
and dirt particles. Enabled ET 2.60 particle parameters are not replaced.

## Verification and limits

Full cgame fixture: particle pool matrix extended from 384 to 512 combinations,
including both actual debris generators. Another 160 tracer predicate cases
cover five modes, flesh/non-flesh, four sources and four viewed players; ten
flash predicate cases cover first-/third-person contexts. Inventory assertions
pin both new options' cgame/UI defaults and flags. Renderer callback/end-to-end
shot scenarios for the new predicates remain unverified; predicate coverage
alone does not establish full visual parity.

Native Debug build, CTest 88/88, Emscripten build, pak read-only and whitespace
checks passed. Original ELF references are unchanged.
