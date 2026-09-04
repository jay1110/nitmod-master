# Popup queue, layout and lifetime batch

Original ELF32: CG_UpdatePMLists 0x996c0 (515 bytes), CG_DrawPMItems 0x99f10
(1611 bytes), sorted cgame_client.c / cgame_ui.c. Typed port continues to use
the existing bounded ET 2.60 popup pools and engine adapters.

Restored cgame archive defaults: cg_numPopups=6, cg_popupFadeTime=6000 and
cg_HUDFlags=4. UI registers the same defaults to support options_nit_hud.menu
before cgame starts. The original UI table did not register these three;
this is an intentional adapter addition preserving existing Cvar values.

Small popup behavior:
- Queue promotion occurs on the next strictly later game timestamp, not after
  the old stock one-second minimum. One entry is promoted per update.
- Hold alpha 1 for 1500 ms, then linearly fade over cg_popupFadeTime.
- Expire after start+1500+fade (strict greater-than comparison); old-list tail
  cleanup uses the same lifetime, avoiding a mismatch with the renderer.
- cg_numPopups<=0 hides the display without disabling queue maintenance.
  Otherwise count includes the current popup and caps at eight.
- HUDFlags bit 2 selects y=70 and five entries, provided count is positive.
  Otherwise bit 1 selects y=310; the default is y=360.
- Small icons are 12 pixels with 14-pixel line spacing, matching original
  popup rendering rather than stock variable icon size/respawn-counter shift.

Safety differences: nonpositive fade duration is treated as no fade after the
hold, alpha clamps to [0,1], and lifetime arithmetic uses double to avoid
signed timestamp addition overflow. No Cvar is rewritten to enforce a bound.
Large rank/skill popup timings remain unchanged. Original multi-part kill
messages, tinted icons, HUDFlags bits 4/8/16 consumers and other HUD stats are
not claimed implemented by this batch.

Full cgame tests use nine real queued messages and the renderer syscall seam:
48 count/layout combinations, icon counts, initial y, bounded alpha, same-time
queue stability, next-frame promotion, old-list expiry, exact expiry boundary
and six alpha cases. Cvar assertions pin defaults. Native Debug build and all
88 tests pass; browser screenshots/dedicated-server visual parity remain open.
No original assets, pak files or original binaries were modified.
