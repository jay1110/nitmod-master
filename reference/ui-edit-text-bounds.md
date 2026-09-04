# Shared UI edit-field rendering bounds

Corrected three pointer-versus-character comparisons in ui_shared.c:
the Cvar and local-string paths of BG_PanelButton_RenderEdit, and
Item_TextField_Paint. Each clipping loop now stops at the actual terminating
character. Previously a narrow/negative available width could keep the loop
running past the string end. Normal suffix clipping and cursor formatting are
preserved; this is safety work, not a new original Nitmod UI feature.

Item_TextField_Paint also resets paintOffset to zero if it is negative or
beyond the current Cvar text length, and resets the measured width to zero
when clipping reaches the terminator. This handles a Cvar becoming shorter
between editing and rendering. An offset exactly at the end remains valid.

Full-UI tests use a deterministic byte-width callback (not a font renderer):

- 768 panel cases: local/Cvar text, focus on/off, blink on/off, insert/overwrite,
  sixteen widths including negative/zero, three inputs including empty and
  color-coded text. Assert one draw, expected suffix and bounded width calls.
- 96 edit-field cases: six scroll offsets including negative/past-end values
  and sixteen widths. Assert offset normalization, suffix and bounded work.

Native build and all 90 CTest tests pass. WASM cgame/ui builds and Node
module/entrypoint checks are run. No original assets or protocol fields changed.
Actual font appearance, color-code-aware clipping and browser/server visual
parity are not established by these synthetic rendering tests.
