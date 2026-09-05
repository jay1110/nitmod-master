# Limbo weapon-stat request protocol

Original CG_LimboPanel_RequestWeaponStats sends `ws <stat>` after
BG_WeapStatForWeapon and suppresses sentinel 26. The original aWeapID table
is ELF VA 0x1004a0, 52 pairs (416 bytes), in the hash-pinned cgame reference
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

The request previously sent ET indices, which include WS_SMOKE at 15.
It now uses the original table for Nitmod and the unchanged BG mapping for
ET. Examples: satchel detonator 15, rifle grenade 16, landmine 17,
MG42 18, Garand 19, K43 20, tripmine 23. Smoke bomb has no original row;
satchel itself is explicitly unmapped. No request is sent for these.

The private weapon rows 47/48/50/51 are retained as reference mapping,
but their typed inventory remains unimplemented; this does not unlock them.
The helper does not replace server/native BG statistics enums or arrays.

CheckLimboWeaponStatProtocol checks every representable wire weapon under
both protocols plus invalid input. Actual browser/server transcript parity
remains outstanding. No pak files are modified.
