# Original Nitmod HUD placement

Ports the original CG_HudPlacement/CG_AdjustFrom640 coordinate contract to
the reconstructed HUD. Evidence: sorted/cgame_ui.c CG_HudPlacement and
CG_FillRect, sorted/cgame_ents.c CG_AdjustFrom640, and cgame_client.c CG_Init
scale initialization (original cgs fields 27364/27368/27372).

On wide displays, both dimensions scale by height/480; the unused horizontal
space is split into two equal margins. Placement 0 adds one margin (center),
1 adds none (left), 2 adds two (right). Narrow/4:3 displays retain width/640
horizontal scaling. This is coordinate parity, not full visual parity.

Connected consumers:

- announcer and special/XP announcements: center;
- kill print: center;
- spree label/player: left or right according to existing HUD flag and
  notification state (original nitrox call sites explicitly select 1/2);
- sliding notification: right;
- alternate ammunition bars/reserve: right;
- ping/clock/speed status fields: right.

Each widget saves/restores placement. Fullscreen effects, existing menus,
native ET servers and unconverted draw paths retain their old transform.
Scale factors are computed once per scope, not per glyph. No engine or PK3
changes are needed. Module HUD reset clears placement state.

Ammo row restarts now reuse their transformed origin: additional rows and
the second akimbo hand cannot fall back to a stretched coordinate. The
original three-physical-pixel bar step is preserved.

Tests exercise all four modes (including unmodified/stretch fallback),
native/original protocols, six display sizes plus missing dimensions, real
CG_DrawPic submission and scope restoration/reset. Existing HUD rendering
tests remain enabled. Native CTest and WASM build/load checks are run.
Browser screenshots and full migration of the remaining HUD/menus are still
outstanding. This does not claim the UI/scoreboard reconstruction is finished.
