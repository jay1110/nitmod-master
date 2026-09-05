# Runtime class stealing

Original qagame references: `G_ClassSteal` at `0x5b3d0` and
`G_ClassSteal_RemoveTools` at `0x5b250` in the split Ghidra source.

`g_classChange` now has a typed consumer in the normal activate path. Holding
activate on an unused corpse of another class advances the corpse's existing
`BODY_VALUE` progress by `100 / sv_fps` per server frame. At 250 progress the
body is marked consumed, its lifetime is extended to the original 20-second
deadline, and `BODY_CLASS` becomes both the active and latched player class.

The transition removes the exact class-owned weapon set from the original
routine and adds the native tools for engineer, medic, field ops or covert ops.
Primary weapons, ammunition, health, position and skill progress are retained.
Covert silenced-pistol ownership is swapped through typed weapon bits.

The original award/database call following a successful steal is intentionally
not reproduced because its offset-only state has no verified typed mapping.
The package tree and original binaries remain unchanged.
