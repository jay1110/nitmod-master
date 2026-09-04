# Original cursor hint protocol and rendering

Evidence: `cgame/sorted/cgame_ui.c`, `CG_DrawCursorhint`, switch around
line 16433, and `cgame_client.c`, shader registrations around line 14573.
The split functions do not include exact entry addresses. These references
provide both wire-number dispatch and asset-path evidence.

Original hint IDs diverge from ET 2.60 after health (13). The port normalizes
the original server's playerState hints once at snapshot ingestion, together
with weapon fields; local trace hints already use typed native IDs.

Important mappings: 14 knife, 15 ladder, 16 button, 17 water, 18 weapon,
19 ammo, 20 powerup, 21 inventory, 29 build, 30 disarm, 31 revive,
32 dynamite, 33 constructible, 34 uniform, 35 landmine, 36 tank,
37 satchel charge, 38 friendly-player symbol. Original hidden values
25/26/28 become HINT_FORCENONE, not zero: zero would accidentally enable
the native fallback trace. Unknown IDs retain the original usable fallback.

For wire 18/19 only, serverCursorHintVal is a wire weapon number and is
translated alongside the other snapshot weapon fields. Unsupported weapons
remain unsupported (WP_NONE); they are not aliased to unrelated weapons.

The original renderer now uses the centered HUD anchor, fade, size/alpha
pulse modes, appropriate selected weapon icon and width, ammo overlay, and
plain blue progress bar for non-pickup hints. Pickup values never become
progress bars. The original health/knife/ammo asset paths are registered for
original protocol only; native ET retains its paths and renderer. No pak or
menu edits, qagame wire changes, or reference binary edits are involved.

The cgame fixture covers 975 combinations (65 IDs, five modes, three values)
through snapshot normalization and rendering, plus invalid values, expiry,
and exact widescreen pickup geometry. A weapon-31 example proves that the
wire value becomes native WP_FG42 rather than indexing native weapon 31.
The fixture uses synthetic shader handles; real asset appearance and actual
dedicated-server interaction remain unverified.
