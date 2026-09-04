# HUD palette connection

Original CG HUD color setup in sorted cgame_ui.c (ending at LAB_00096919)
parses three RGB components and assigns cg_HUDAlpha.value to both background
and border alpha. The fourth component in original menu presets is ignored.
Original table defaults are .16 .2 .17, .5  .5 .5, and 0.8; all three are
registered with CVAR_ARCHIVE in cgame and ui, preserving existing values.

The controls now affect the ping/clock/speed panels, existing FPS/round-timer
panels and the fireteam window background/border (not its header/row colors).
Other HUD consumers remain unported. No menu, menudef or pak files are changed. Defaults for
invalid RGB inputs are the original background/border colors; malformed input
does not partially update a color. Nonfinite inputs are rejected and finite
channels/alpha clamp to [0,1], intentional hardening beyond original strtod.
The shared alpha also makes the default timer border .8 instead of stock .5.

Tests cover whitespace/comma numeric triples, ignored preset alpha, negative
and excessive channels, shared alpha, incomplete/malformed/nonfinite RGB and
atomic output preservation. Inventory assertions pin both modules' defaults
and flags. Browser/menu screenshot comparison remains pending.

## Named presets and fireteam integration

Original ELF32 jP_SetHUDColors at VA 0x86770 (1481 bytes; SHA-256
c8f52d590c80ef1798eaae206ec9fe81eb29e172b37f8344d0170a230dba8ca8)
uses case-sensitive comparisons. Its palette strings at 0x108bd5..0x108c67
establish these presets: default/def/grey/gray = (.5,.5,.5), red = (.75,0,0),
green = (0,.75,0), blue = (0,0,.75), black = (0,0,0), white = (1,1,1),
dkgrey/darkgrey/dkgray/darkgray = (.25,.25,.25), and cthulhu/cthulhu_green =
(0,.25,.25). In particular, `default` is gray even for the background; this
is different from the registration default (.16,.2,.17).

The port resolves aliases immediately without rewriting archived Cvars.
Intentional deviations: the original rewrites Cvars but then parses the stale
copied text, and its background cthulhu branch checks the border buffer and
writes the border Cvar. Neither unsafe/stale parsing nor cross-color mutation
is reproduced. Both inputs remain independent and use the shared alpha.

Original CG_DrawFireTeamOverlay in sorted/cgame_ui.c uses HUD_Border and
HUD_Background for the outer rectangle/fill; the typed native overlay now
uses the same shared palette accessor. Header/selection colors stay unchanged.

The full cgame fixture adds 60 preset/alpha combinations plus independent
background/border, no-Cvar-mutation and invalid-background fallback checks.

Validation: native Debug build succeeded; CTest 88/88 passed. Emscripten
side-module build and fresh Node dlopen/dlsym/entrypoint probes passed for
all three modules. Pak read-only guard and diff whitespace checks passed.
This does not establish browser rendering or dedicated-server parity.
