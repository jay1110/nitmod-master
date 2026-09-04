# Original crosshair target presentation

Behavior references: sorted/cgame_ui.c CG_DrawCrosshairNames and
sorted/cgame_client.c CG_LoadRankIcons. Original cgame SHA-256:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

## Implemented

- Player labels use limboFont2, scale .2, baseline 182, style 7. Their text
  is centered at virtual X=336; the class icon at X=320-width/2 uses 14x14.
  With cg_drawCrosshairNames bit 2 and valid positive rank, the class icon
  shifts left 16 pixels and the HUD rank icon occupies its previous position.
- Names, class and rank come from clientInfo; disguised targets use the
  disguise name/rank and the original three class bits at powerups bits 8..10.
  Invalid client/class/rank values never index arrays. Invalid rank falls back
  to the class-only presentation.
- Health bars use the original rectangle (270,190,100,10), clamped fraction,
  red-to-white foreground and quarter-alpha background. This replaces the
  native 110-pixel width only for original-protocol rendering.
- Movers and construction labels use scale .2 at (320,182). Original name
  configstrings are 26 and 27, NOT native 28 and 29. The engine gamestate is
  not rewritten; only the consumer selects the appropriate indices.
- Construction-marker recognition uses original entity type 33. Original
  disguise/no-shoot detection uses bit 7 instead of native PW_OPS_DISGUISED.
- DM mode 8 suppresses original target labels. Native rendering is retained.
  HUD anchor selection is scoped and restored. Trace/entity/tag-parent bounds
  prevent invalid array access; index 64 is not a client.

## Rank table evidence

The original table begins at ELF VA 0x1394e0 (Ghidra 0x1494e0), with four
16-byte records per rank: HUD and model records for each team. The HUD paths
are gfx/hud/ranks/rankN in both team banks; model paths are shaderfix/rankN.
The typed native table's second slot is model media, not the second team.
The new renderer therefore selects rankicons[rank][0].shader, never the helmet
shader. No asset names or packages were changed.

## Remaining behavior gaps

This ports presentation and the explicit wire identifiers, not every original
visibility/health rule. Existing ET260 field-ops disguise recognition and
maximum-health calculation are retained. Original class-specific maximum
health settings and private skill masks must still be reconstructed before
claiming full health/skill parity. The original name format appends ^7; the
typed renderer resets render color explicitly instead of storing that suffix.
Missing/invalid icon handles are skipped rather than sent to the engine.

## Verification

CheckCrosshairPresentation executes actual drawing code through mocked traps:
1040 combinations of protocol, option flags, class, rank and disguise mode;
font/glyph choice, icon selection, text and half-health geometry, invalid
indices/classes, health clamps and zero denominator. Separate gamestate strings
verify both original/native name banks, entity 64, missing entries and bounds.
The full native suite and WASM build/load tests are also required. These tests
do not replace browser screenshots or dedicated-server gameplay validation.
