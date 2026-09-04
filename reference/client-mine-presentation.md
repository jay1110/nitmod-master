# Landmine presentation and owner hints

References: sorted `cgame_effects.c`, `CG_Missile` around labels 0x66240–0x66442;
`cgame_nitrox.c`, `Nit_SpecMines`; `cgame_client.c`,
`CG_ScanForCrosshairMine` (call-site return 0x56352); and
`cgame_ui.c`, `CG_DrawCrosshairNames` (0x56a79 return site).
These are Ghidra addresses/labels, not all function entrypoints.

The original-protocol landmine path now has typed visibility/render decisions:

- Normal local spectators remain excluded, even while following a player.
- Server-marked shoutcasters can see armed mines using `nitmod/SpecMines`.
  The source's sine pulse, teamNum modulo-four red/blue tint, alpha 255,
  lighting origin, eight-unit burial and additional two-unit shader offset
  are retained. No client cvar grants this role.
- Friendly mines and discovered enemy mines use the existing animated marker
  renderer. The spotting-client density exception keeps the construction shader.
- Unarmed and triggered states preserve their source height offsets.
- Friendly armed mines use a 512-unit solid trace with a strict 16-unit
  per-axis endpoint test. `otherEntityNum` supplies the owner (not clientNum
  or density). Invalid/world owners clear the candidate.
- The original one-frame owner label precedes ordinary crosshair scanning,
  uses limboFont2 at .18, baseline 182, centered at 320, style 7, and the text
  `<name>^7's landmine`. It is consumed once and cleared at frame reset.

Boundaries: the original private mine-visibility skill bit and colored-mine
setting remain unmapped. That branch deliberately retains ET's battle-sense
level >= 4, inclusive 256-unit radius and construction shader. Gift/poison
mines (original weapon 51) still lack their own typed weapon implementation;
this patch does not alias them to landmines or claim their support. Third-person,
DM, stale/missing owner and invalid-client hints are suppressed safely.
No changes to pak, assets, qagame, UI, protocol numbers or reference binaries.

`CheckMineDisplay` tests 576 combinations of protocol, local team, caster role,
mine state, spotted status and skill level, plus shader/tint/height assertions,
radius boundaries, spotting precedence, trace-box edges, one-shot label
consumption, stale/reset cases and invalid owners/clients. These are typed
helper and syscall-fixture tests, not a real dedicated-server/render replay.
