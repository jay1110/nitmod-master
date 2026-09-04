# Active status HUD

Ported the original CG_DrawActivePowerups from cgame_ui.c, with media
paths recovered from cgame_client.c. The display is original-protocol-only,
right anchored, and reads the viewed snapshot, not local predicted state.

Original snapshot offsets map via the 44-byte ps header to typed fields:

| Original offset | Typed original-wire field | Display |
|---|---|---|
| 0x190 / 0x194 | powerups[5] / [6] | Objective (takes precedence over disguise) |
| 0x198 | powerups[7] | Disguise uniform |
| 0x19c / 0x1a0 / 0x1a4 | powerups[8..10] | Disguised class bits |
| 0x158 | persistant[7] | Team, selecting opposite uniform |
| 0x100 bit 64 | stats[1] bit 64 | Binoculars |
| 0x95 bit 16 | eFlags EF_HEADSHOT | Hide helmet |
| 0x180 / 0x184 | powerups[1] / [2] | Shield, then flak fallback |

The native compiler layout was inspected with Clang's wasm32 record-layout
dump (ps powerups=336, persistant=272, eFlags=104). These wire slots must not
be replaced with native ET PW_* names. No player-state data is mutated.
Original icon positions and 15x15 dimensions are retained; malformed class
bits 5..7 omit the label as a defensive difference. Renderer color and
anchor are restored. Tests pin source dispatch and original media paths;
pixel and gameplay parity in-browser remain unverified.
