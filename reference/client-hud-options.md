# Original-menu HUD options: UI and cgame

Six matching original Cvar registrations now exist in both modules:
cg_drawPing=0, cg_drawTime=1, cg_drawTimeSeconds=0, cg_drawspeed=0,
cg_speedunit=0, cg_speedinterval=100, all CVAR_ARCHIVE. UI registers without
vmCvar storage as the original table does. Existing engine values survive
registration. The untouched options_nit_hud.menu controls these same names;
the engine's case-insensitive Cvars match menu cg_drawSpeed to cg_drawspeed.

cg_nitmod_hud.c adds the consumers to the upper-right client HUD:
- Ping mode 1 uses snapshot ping capped above at 999, original label Ping.
- Clock mode 1 is 24-hour; other nonzero modes are 12-hour with am/pm suffix;
  cg_drawTimeSeconds adds seconds. Original strings verified in ELF .rodata
  0x103434..0x10344d and CG_DrawTime in sorted cgame_ui.c.
- Speed uses full predicted velocity length, sampling only when elapsed
  engine milliseconds exceeds the interval. Units use original divisors
  15.58 and 23.44. Mode 2 adds highest sampled speed; resetmaxspeed clears it.
  The original CG_ResetMaxSpeed_f flag was consumed on the next enabled draw;
  this implementation clears the peak immediately and retains sampled speed.

Lifecycle clear resets sampling/peak. Clock invalid fields are rejected;
backward clock movement restarts speed sampling. These are explicit hardening
differences. Display rows use the existing ET limbo font and native panel
colors; complete original HUD palette/placement controls are not ported here.
The old fireteam-overlay early return hid all upper-right statistics; it now
gates only the fireteam overlay. Existing automap-expanded suppression remains.

Average-ping mode is now implemented; see client-hud-ping.md for the binary
evidence that the original calculation is stateless. This work
does not claim all menu actions, country flags, wounded names or HUD flags.
No pak/PK3/menu/menudef assets or server protocol changed.

Tests cover all 24 clock hours in both formats, with/without seconds (96
profiles), disabled/invalid clocks, strict sample timing, three units, vertical
velocity, peak retention/reset and unsupported speed units. Inventory tests
pin all twelve original module registrations and the draw/command hooks.
Formatting tests do not establish screenshot, font or browser UI parity.
