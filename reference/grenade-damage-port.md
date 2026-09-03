# Hand-grenade damage option

The original spawn cases 4 and 9 (grenade) share the g_damageweapons & 1
branch in sorted nitmod_unknown.c. Both configure health 40, takedamage,
CONTENTS_CORPSE, mins/initial absmin (-4,-4,0), maxs/initial absmax (4,4,6),
and Nit_WeapDie. This matches the separately recovered smoke-bomb setup
except for its enabling mask (8).

The two native hand-grenade branches WP_GRENADE_LAUNCHER and
WP_GRENADE_PINEAPPLE now call the typed configuration helper. Shared private
setup avoids duplicating the verified field assignments. The rifle-grenade
branches WP_GPG40/WP_M7, smoke marker and other weapons are unchanged.
Native default damage/radius/MOD settings are retained; this is not a port
of the original private weapon damage tables. Default g_damageweapons=0 is
unchanged. The separate g_canisterKick behavior remains unported.

Tests now cover 512 combinations across smoke/grenade helpers, ensuring the
two masks remain independent and unrelated bits preserve the entire baseline
entity. Eight existing death-callback cases continue to pass. Source tests
check both actual hand-grenade spawn hooks. Native/WASM builds and 79/79 host
tests pass; original engine collision/damage-chain replay remains pending.

The original additional case 0x30 named bomb was inspected but not mapped to
WP_SMOKE_MARKER without further weapon-identity evidence. No speculative
activation of mask 0x10 was made.
