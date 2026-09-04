# Nitmod loading-screen reconstruction

The code-only loading-screen port uses the existing assets delivered by the
original Nitmod PK3. No file below `pak/` is generated or modified.

## cgame

`CG_DrawConnectScreen` is mapped to the original cgame function at `0x7bc00`.
It renders the map description, map/campaign identity, server MOTD, server-rule
icons, hunk progress and all original Nitmod gametype labels (map voting, team
deathmatch and deathmatch).

## ui

The UI connection path is mapped to the original functions around `0x21f90`
through `0x233b9`. It now clears the complete physical viewport, preserves the
4:3 panel on widescreen displays, positions connection text in the extended
virtual space and renders bounded download progress plus transfer/ETA text.

All byte counts are read from the engine-owned `cl_downloadSize`,
`cl_downloadCount` and `cl_downloadTime` cvars. The progress fraction is clamped
to `[0, 1]`; no decompiler offsets or raw global-memory accesses are retained.
