# Original snapshot persistant adapter

Original Nitmod does not use ET 2.60's persistant enum. The receiver now
normalizes the array immediately after a successful CG_GETSNAPSHOT, before
initialization, interpolation, prediction or player-state transitions.
Native/reconstructed servers (et260 protocol selection) are byte-unchanged.
No engine ABI structs or native enums are resized or renumbered.

| Original slot | Meaning | Native consumer |
|---|---|---|
| 0 | score | PERS_SCORE |
| 1 | head-hit sound counter | PERS_HITS, wire copy |
| 2 | body-hit sound counter | wire copy only |
| 3 | kills | wire copy only |
| 4 | deaths | PERS_KILLED, wire copy |
| 5 / 6 | headshots / bodyshots | wire copy only |
| 7 | team | PERS_TEAM |
| 8 | spawn count | PERS_SPAWN_COUNT |
| 9 / 10 | remaining respawns / penalty | PERS_RESPAWNS_LEFT / PENALTY |
| 11 | revive count | PERS_REVIVE_COUNT |
| 12 | mounted weapon use | PERS_HWEAPON_USE |
| 13 / 14 / 15 | goombas / best spree / current spree | wire copy only |

Native-only rank, spare and wolfkick slots are zeroed; attacker is -1
(unavailable), not a headshot count masquerading as a client index. No
attacker identity is fabricated. Native prediction thus receives team and
mounted state in the slots its shared movement/character code expects.
Spawn and revive comparisons no longer inspect death/bodyshot counters;
reinforcement UI no longer treats team number as lives remaining.

Two bounded sidecars preserve all 16 original counters for the two existing
cg.activeSnapshots buffers. Each carries serverTime and validity. This
ownership matters: reading nextSnap must not change current HUD statistics.
Native reuse invalidates a sidecar, and config/HUD reset clears both.
The live-stat text and counter-change paths read the matching wire copy.
Translation is a once-per-successful-engine-read boundary operation, not
an idempotent transform to apply repeatedly to a normalized playerState.
Wire lookup for non-owned player states accepts an unconverted state; do
not pass a copied normalized predictedPlayerState for private statistics.

## Evidence

Reference cgame SHA-256:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.
playerState.persistant starts at 0x110; snapshot.ps at 0x2c.
CG_TransitionPlayerState ELF 0x98ea0 compares 0x130 (spawn) at 0x98f6b,
0x13c (revive) at 0x98f81, and team at 0x12c at 0x98fb6.
CG_DrawLivesLeft ELF 0x45e90 reads snapshot+0x160 (slot 9).
The reinforcement branch in sorted/cgame_ui.c:9510–9511 reads snapshot
0x160/0x164 (respawns/penalty), matching native CG_DrawFollow semantics.
Original CG_CalcFov reads snapshot+0x16c (slot 12 mounted use).
CG_CheckLocalSounds reads ps+0x118/0x114 (body/head sound counters).
BG_GetStatGoombas 0x23990, BG_GetStatBestSpree 0x239d0 and BG_GetKillSpree
0x23a10 read ps+0x144/0x148/0x14c. Live-stat offsets are recorded in
client-live-hud-stats.md. G_SetPlayerScore writes ps+0x110, as documented
in skill-score-disassembly.md.

## Verification and limits

Tests cover all 16 independent input slots, both buffers and both protocols
(64 cases), checking the entire snapshot for unintended changes. Additional
checks retain current/future HUD values independently, exercise highlighted
counter transitions after normalization and invalidate cache on native reuse.
Existing native gameplay and WASM build/load checks are also run.
This is not a live dedicated-server or browser parity claim. No qagame
wire emission, pak, PK3, menu or original binary changes are made.
