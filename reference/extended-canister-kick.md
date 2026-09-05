# Bomb and poison-bomb kick integration

Original G_CanisterKick (ELF 0xfd070, sorted nitmod_admin.c) admits original
weapon IDs 4, 9, 21, 28, 48 and 50. The last two now map explicitly to native
WP_BOMB and WP_POISON_BOMB. WP_POISON_MINE and WP_TRIPMINE remain excluded.

The recovered fire_grenade cases 0x30/0x32 in sorted nitmod_unknown.c establish
kick collision sizes independently of damageability: bomb mins (-11,-11,0),
maxs (11,11,10); poison bomb mins (-4,-4,0), maxs (4,4,6). Both use corpse
contents. G_NITMOD_ConfigureCanisterKick applies these sizes and preserves
all unrelated projectile state.

G_CanisterKick uses the existing original trajectory, pitch cap, truncation,
first-missile selection and optional ownership-transfer behavior. Activated
airstrike markers retain ownership; bomb and poison-bomb ownership can transfer.
The fuse and think callback do not change. Existing client missile rendering
consumes ordinary entity trajectory/owner/team state; no new wire command or
UI menu/asset is introduced.

The linked qagame tests cover every native weapon identity with both owner
settings, five actor/Cvar gates and both activation states, plus collision
setup for every identity with kick enabled/disabled. The existing actual
Cmd_Activate2_f ordering and ordinary grenade-spawn tests remain enabled.

Scope: kick interaction and collision configuration only. This does not add
the missing server poison damage/think system or claim a complete additional
weapon spawn/fire path. Browser gameplay parity remains unverified.
