# Static map corona lifecycle

Original cgame ELF: SP_corona 0xb2d10, CG_Coronas 0x4a370 and its render
body 0x3e5c0. Sorted cgame_spawn.c and cgame_client.c preserve the branches.
The seven-float records hold scale, origin and RGB; capacity is 1024.

The new cg_nitmod_coronas.c module implements the missing client-side map
entity path, separate from existing network ET_CORONA rendering:

- Register `corona` in the client spawn dispatch; reset storage on map parse.
- Reject entities having targetname, scriptname or spawnflags keys, even
  empty/zero-valued ones. Those entities belong to the server-controlled path.
- Read origin (default 0 0 0), scale (default 1), _color before color.
  The original default at ELF 0x10e953 is `0 0 0`: the apparent fallback
  white writes are overwritten by the parsed zero vector. Preserve that
  observed result rather than silently changing maps without a color key.
- On each normal scene build, require original protocol, enabled cg_coronas
  and engine PVS membership. Mode 2 bypasses distance/direction culling,
  but never PVS. Other enabled values require distance <= cg_coronafardist
  and view-direction dot < -0.6.
- Trace using MASK_SOLID | CONTENTS_BODY and submit the stable list index,
  original float colors and scale, and visibility = (fraction == 1).
  Occluded entries still submit a false visibility flag for engine fading.

Explicit hardening: malformed/nonfinite fields are rejected transactionally;
excess records warn and are ignored rather than crashing the client; invalid
distance calculations never reach tracing. Source vector parsing is stricter
than original sscanf, and malformed maps are not claimed behavior-identical.
No engine ABI or server messages added. Native ET path stays disabled.

Full-cgame tests exercise actual spawn dispatch, absent defaults, all three
server-owned key exclusions, five malformed origins, color-key priority,
96 renderer/PVS/distance/direction/occlusion combinations with real syscall
arguments, the 1024-record boundary, reset, and native-protocol suppression.
CMake and SCons include the module. Live browser visual comparison and
original-server session tests remain outstanding. pak and original binaries
are untouched.
