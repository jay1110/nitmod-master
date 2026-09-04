# Client country-flag pipeline

The original cgame keyword table was recovered directly from
`cgame.mp.i386.so`: keyword-table value `0x58`, used by
`CG_NewClientInfo`, resolves to player configstring key `u`. The parsed value
indexes `gfx/flags/world_flags`; values below 255 are drawable and 255 means
unavailable.

The reconstructed client stores this value as `clientInfo_t.countryCode`.
Parsing is strict and accepts only decimal integers 0..254. Missing, negative,
overflowing, suffixed or out-of-range values become 255, preventing invalid
atlas coordinates. A new player record is initialized to 255 before parsing.

The original shader `gfx/flags/world_flags` is registered with the other game
textures. It is treated as a 16 by 16 atlas of 32-pixel cells. UV calculation
is isolated and bounds checked. The flag is drawn only for original Nitmod,
when `cg_countryflags` is enabled and a positive shader handle exists.

Normal, compact, and Deathmatch/FFA scoreboard rows share the same helper and
reserve name-column space only when a flag was actually drawn. No atlas or
PK3 asset was added or changed; the existing server-provided Nitmod asset is
used.

Tests cover every valid index 0..254, both invalid boundaries, null UV
outputs, strict player-field parsing and overflow rejection. Runtime builds
still require a live visual comparison to confirm the original atlas ordering.
