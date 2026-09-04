# Client particle option batch

Register cg_smokeparticles, cg_trailparticles and cg_impactparticles in cgame
with typed vmCvar_t handles, and in UI without handles. All three original
defaults are 1 with CVAR_ARCHIVE. Original menus can now control these paths
without editing any asset. A zero value disables creation; every nonzero
value enables it, including negative values as in the original.

Original ELF32 entrypoints and recovered guards:

| Function | Address | Option |
| --- | --- | --- |
| CG_ParticleBubble | 0x8c540 | trailparticles |
| CG_ParticleSmoke | 0x8c5d0 | smokeparticles |
| CG_ParticleImpactSmokePuffExtended | 0x8d610 | smokeparticles |
| CG_ParticleImpactSmokePuff | 0x8d7e0 | smokeparticles |
| CG_ParticleSparks | 0x8e850 | impactparticles |
| CG_ParticleDust | 0x8eaa0 | smokeparticles |
| CG_RocketTrail | 0xbfb50 | trailparticles |
| CG_GrenadeTrail | 0xc02d0 | trailparticles |

Reference: sorted cgame_particles.c and cgame_client.c. Entry guards precede
allocation, random generation and entity access. Dust's disabled branch also
preserves its direction argument; enabled native dust negates it. Rocket and
grenade guards leave trailTime untouched, matching the recovered entry gate.
The native simple smoke-puff wrapper inherits the guard through Extended.

This batch restores option dispatch, not the entire original particle
implementation. Enabled rendering retains typed ET 2.60 behavior. Additional
original impact-material branches and explosion-trail helpers remain to port.
Smoke grenade visibility, flame rendering, blood, weather, ordinary explosions,
audio and server state are not globally disabled by these changes. Existing
particles finish naturally when a creation option is switched off.

Tests: the full cgame fixture exercises 384 combinations (four values for each
of three Cvars, six particle entrypoints), checking real free/active particle
lists and disabled dust argument preservation. A disabled rocket test verifies
the return precedes entity access and engine callbacks. Enabled rocket/grenade
visual fidelity and browser rendering remain unverified. Inventory tests pin
the six registrations against the original cgame/UI defaults and flags.

Native Debug build and 88/88 CTest tests passed. No pak/PK3/menu/original binary
was modified. WASM artifact/load validation is recorded separately from actual
browser gameplay parity.
