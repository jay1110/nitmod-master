# Airstrike marker damage mask

Original spawn case 0x15 in sorted nitmod_unknown.c tests g_damageweapons & 4
and subsequently registers the entity in AirstrikeEntities. This, rather than
the distinct case 0x30 named bomb, maps to native WP_SMOKE_MARKER.
The original assigns 40 HP, takedamage, CONTENTS_CORPSE, (-4,-4,0)/(4,4,6)
bounds and Nit_WeapDie. Those assignments share the previously reconstructed
small-canister configuration and delayed-death handler.

The native smoke-marker spawn branch now invokes its own mask-4 helper.
Default flag value 0 leaves the baseline unchanged; other bits alone do not
enable marker damage. Native marker damage/radius/MOD, normal think setup,
airstrike logic and other gameplay settings remain unchanged. The death handler
replaces the entity's think callback with next-tick G_ExplodeMissile, as already
tested for the common handler; no live airstrike interruption test is claimed.

The original AirstrikeEntities registry and separate g_canisterKick option
are not implemented by this change. Landmine arming and damage behavior were
not modified. The additional bomb case 0x30/mask 0x10 is still unassigned.

768 combined smoke/grenade/marker flag cases compare the complete configured
entity, verifying independent masks. The source contract checks the actual
WP_SMOKE_MARKER hook. Native/WASM builds and 79/79 host CTests pass.
Original-engine projectile collision, damage chain and airstrike replay remain
pending; this is not full weapon-policy parity.
