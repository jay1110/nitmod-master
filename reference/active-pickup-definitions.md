# Pickup definitions and localhost limbo quotas

## Gameplay integration

`G_CanPickupWeapon` now connects the existing recovered pickup policy to parsed
weapon class masks. The earlier restriction/war/knife/pick-any precheck remains
first. Only a successfully parsed definition activates the class-mask path;
unavailable configuration or missing/unsupported definitions retain the existing
ET fallback. Restrictions can deny before any file is opened.

The map-owned cache in `g_nitmod_weapon_definition.c` stores both successful and
failed lookups by native weapon identity. Base/scoped/alternate weapons remain
distinct even when they share a filename. `G_InitGame` resets the cache, including
on restart, allowing changed files to be retried. Files are read from `weapons/`
through the engine filesystem; there are no writes to pak or PK3 assets.

The common-block parser reads the already recovered ammo/recoil/options grammar
so those recognized fields do not invalidate a class-mask lookup. Only `classes`
is applied by this integration. Shared ammo, recoil and prediction state are
not modified. Unknown common attributes still cause a safe fallback: this is
not a claim that the entire original weapon-definition grammar is supported.
Original custom-directory selection and in-map definition reload are not
implemented by this cache.

Evidence remains the existing original `G_CanPickupWeapon` class-mask-first
policy, documented in weapon-restrictions.md and tested in the pickup fixtures.
Runtime integration now covers all five classes with a parsed mask, no inventory
mutation, and denial by a heavy-weapon limit despite that mask. Loader tests
cover cache hits, distinct alternate identities, failed-load caching, preserved
outputs, invalid identities and retry after reset.

## Client integration

`NITMOD_WeaponQuotaDisabled` now applies validated `#` settings to reconstructed
Nitmod localhost games as well as original Nitmod servers. Original wire-ID
translation remains separate and unchanged. Limbo quota tests exercise all six
tracked weapon identities, caps -2 through 3 and counts 0 through 2 under both
layouts (216 combinations). The existing class, selection and STEN tests remain.

This batch changes qagame and cgame's limbo UI, not the separate ui module.
It does not expose extra localhost class loadouts whose server grant behavior
is not implemented. No new protocol message, cosmetic cvar-only feature or
placeholder weapon simulation is introduced.

Native builds and all 97 tests pass. Emscripten build/load checks are distinct
from live browser item-pickup and menu verification, which remains outstanding.
