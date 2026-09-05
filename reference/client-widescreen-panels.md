# Client widescreen text and panels

Scope: cgame presentation only; no protocol, pak, menu or asset changes.
Applies to original Nitmod servers and reconstructed localhost Nitmod via
`NITMOD_UsesNitmodHud()`. The ETmain fallback retains its existing scaling.

## Coordinate domains

The existing HUD transform preserves 640x480 geometry on wide displays using
height-based scale. Centered panels occupy a centered 4:3 canvas; this is not
a redesign that expands scoreboard columns across the full screen.

| Consumer | Anchor |
| --- | --- |
| Warmup/countdown and waiting text | Center |
| Scoreboard, including its intermission variant | Center |
| Debriefing pages, chat and pointer | Center |
| Objective, limbo and spectator messages; fallback centerprint | Center |
| Normal popup list (including kill/death text) | Left |
| Large skill/rank popup | Right |
| Vote and demo recording text | Left |

Wrappers restore the caller's anchor even when content returns early. Existing
Nitmod-specific messages that select their own anchors retain those overrides.
Vertical border thickness now follows the active horizontal scale rather than
the full stretched screen width. Explicit fixed-pixel borders remain fixed.

Debriefing uses logical panel coordinates for its pointer. Its display-context
cursor is synchronized after mouse handling (including drag early returns),
before key handling and before drawing. This avoids stale hit-test coordinates;
it must not use the limbo screen-to-panel inverse conversion a second time.

## Audit boundaries

Nitmod announcements, center/kill prints, graphical obituaries, notifications
and status widgets already have scoped anchors. Disabled `CG_DrawNotify` was
not enabled. Fullscreen effects are not moved into a centered HUD canvas.
This change does not certify all UI assets or every remaining draw path as
original-client-equivalent.

## Verification

- `check_widescreen_text.h`: real warmup glyph draw coordinates at 640x480,
  1280x720, 1920x1080 and 3440x1440 for ETmain, original Nitmod and localhost
  Nitmod; scoreboard early-return anchor restoration; scaled border thickness.
- Existing `CheckHudAnchors`: anchor transforms, render coordinates and limbo
  cursor conversion including narrow and invalid viewport cases.
- Native suite and Emscripten build/load/ABI smoke tests.
- Live browser visual parity, populated scoreboard layouts and interactive
  intermission page transitions still require a gameplay check. Automated
  warmup geometry checks are not a screenshot comparison of those panels.
