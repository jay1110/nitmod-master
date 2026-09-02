# Satchel destruction handler

Update: the satchel-only spawn gate is now active. The prior inactive stage
described below is historical. Hash-pinned extraction of gameCvarTable confirms
g_damageweapons default "0", flags 0, trackChange 0 and reset 0 (record address
2792360, vmCvar address 48487520). Native G_RegisterCvars/G_UpdateCvars now
maintain the typed Cvar through their existing table lifecycle.

After baseline satchel initialization, mask 0x2 sets health=40, takedamage=true
and the typed death callback. All other flags alone leave that baseline
unchanged. This is a spawn-time decision, not a retroactive update of existing
satchels. Only this mask is implemented; the other g_damageweapons behaviors
remain open. Default 0 leaves existing default shootability unchanged.

256 mask cases test selection, and the 32 handler cases now invoke the callback
assigned by the configuration helper for missiles. A hash-pinned Cvar test
checks the original registration and the actual spawn hook/order. This is
server-side entity behavior with existing event IDs; no new client command or
capability advertisement is introduced. Native/WASM builds and 78 tests pass;
live damage-chain and original gameplay comparisons remain pending.

Original Nit_SatchelDie at qagame ELF 0x8a5f0 was inspected with objdump.
For ET_MISSILE it clears the free callback, sets contents to 0x02000000
(CONTENTS_CORPSE), schedules G_ExplodeMissile at current time + 1, restores
the owner's satchel inventory, and emits event 0x19 when the held weapon is
the detonator. Typed ET identities are WP_SATCHEL/DET and EV_NOAMMO.
Unlike G_FreeSatchel, this path does not check connection state or player class.

The implementation is in game/g_nitmod_satchel_die.c with the complete typed
ET die-callback signature. Extra callback parameters are ignored. Null entity,
invalid owner index and absent client are handled defensively; these guards
are not claimed as original behavior. Entity scheduling precedes owner checks.
The original 32-bit increment wraps explicitly at INT_MAX without signed C
overflow. It schedules the explosion; it does not explode synchronously.

The original spawn reference in sorted nitmod_unknown.c assigns this callback
only under g_damageweapons & 2, together with health 40 and takedamage true.
That option is not yet reconstructed in the product. Therefore this handler
is compiled and tested but deliberately NOT assigned to spawned satchels.
No unconditional shootability, new Cvar default or guessed client capability
was introduced. Activation requires the corresponding configuration port.

32 executed cases cover missile/non-missile state, client presence, held
weapon and four timestamps including INT_MAX. The event test checks that
inventory restoration precedes event emission. A synchronous explosion fails
the test. Owner is a disconnected, non-covert zero-initialized client, ensuring
the stricter free-handler gates were not accidentally reused here.
Native/WASM builds and 78/78 host tests pass. No original gameplay replay is
claimed; malformed-owner guards and floating/platform differences remain
outside behavioral equivalence claims.
