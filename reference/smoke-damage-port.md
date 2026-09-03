# Smoke-bomb damage option

Original qagame Nit_WeapDie at ELF 0x89390 was rechecked with objdump.
It clears free, assigns CONTENTS_CORPSE, schedules G_ExplodeMissile at time+1
and returns. It has neither a missile-type guard nor owner inventory/event
logic. The typed G_NITMOD_WeaponDie preserves these distinctions and uses
explicit signed wrap at INT_MAX; null rejection is a defensive difference.

The sorted spawn branch for smoke_bomb (original weapon 0x1c) enables damage
only under g_damageweapons & 8. Reconstructed typed fields are health=40,
takedamage=true, CONTENTS_CORPSE, mins=(-4,-4,0), maxs=(4,4,6), and matching
initial absmin/absmax. The latter follow the original pre-link initialization;
engine linking still owns calculation of world-space bounds.

The actual WP_SMOKE_BOMB spawn branch now invokes this configuration helper.
The default Cvar remains 0; unrelated flags alone leave the native baseline
unchanged. This is not the smoke-marker/airstrike canister branch. Only masks
0x2 (satchel) and 0x8 (smoke bomb) are currently integrated. No new network
command or client-side capability advertisement is introduced.

256 mask cases compare every entity byte against expected configuration;
eight callback cases check full entity state across two entity types and four
timestamps, including INT_MAX. Tests invoke the callback assigned by the helper
and fail if explosion happens synchronously. The source contract checks the
actual spawn hook. Native and WASM builds and 79/79 host tests pass.
The original artifact is unchanged and hash checks remain in the suite.

Actual projectile damage/collision/rendering in an engine and original gameplay
replay are still pending. Other Nit_WeapDie consumers remain unported; this is
not complete g_damageweapons coverage.
