# Fight/prepare announcer

Original-protocol `an 0` and `an -1` now display FIGHT! and PREPARE TO FIGHT!.
They accept the two-argument command or a third unused argument, as distinct
from the signed XP required by special-notification categories. Other protocol
and server commands are unchanged.

The cgame cg_announcer registration (default 1, CVAR_ARCHIVE) is enabled;
the UI already registers the same name/default. Zero suppresses starting
either text or sound, and also hides a currently active display. Re-enabling
within its original lifetime reveals it without replaying sound.

Evidence: sorted cgame_ui.c CG_AddAnnouncer/CG_DrawAnnouncer and the `an`
switch in cgame_servercmds.c. Original ELF symbols are 0x4ebc0 and 0x4b640.
There is one replaceable slot, not a queued list. The two command cases use
animation mode 1, duration 1000, scale factors 1.1/.85, red/yellow RGB,
and zero vertical offset. The typed implementation centers at (320,240),
with scale `(1.1 - remaining/1000) * factor`, using limboFont1/style 3.

Original sound registration in cgame_client.c uses sound/nit/fight.wav and
sound/nit/prepare.wav, compression false. Both are registered during typed
media initialization and played on CHAN_ANNOUNCER (7), once per accepted
start. Failed/nonpositive handles are silent; text still starts. Cached
handles are replaced by subsequent media initialization, not by HUD reset.

Defensive deviations: signed command parsing and argument-count checks,
double time arithmetic, and rollback clamping. Typed rendering submits
explicit alpha 1. Font/color/placement equivalence still needs original-client
screenshots, including the original aspect-aware HUD placement behavior.
The generic original CG_AddAnnouncer mechanism is now implemented as
CG_NitmodAddAnnouncer: a copied 1024-byte text slot, arbitrary positive duration,
RGB color, scale, integer vertical offset and optional sound. Sound-only calls
do not replace the text. Empty text hides the slot. HUD reset clears its state.
Mode 2 uses (1.1 - sin(remaining*pi))*scale; mode 3 uses
(.1 + sin(remaining*pi))*scale. Other mode values use the original linear
fallback. Both existing FIGHT/PREPARE call sites now use this shared mechanism.
No new server command or unverified mode-2/3 caller has been invented.

Defensive limits: RGB must be finite in 0..1, scale finite in (0,100], duration
positive. Invalid text parameters leave the previous slot intact; positive
sound handles still play first as in the original. Frame output pointers are
validated. Tests cover all modes/fallbacks at eight times, expiry, copied-text
ownership/truncation, disabled state, invalid inputs and reset. Existing
FIGHT/PREPARE command and sound tests remain. Mode-2/3 visual behavior is not
yet browser-verified and these modes have no known active original call site.

The automatic FIGHT trigger is now connected in CG_ParseWolfinfo, where
CS_WOLFINFO's gamestate changes from a non-playing state to GS_PLAYING.
Original-protocol servers use the same typed announcer as `an 0`, respecting
cg_announcer. Repeated GS_PLAYING updates do not restart text or sound.
The stock ET protocol retains its existing console/centerprint behavior.
This follows the original cgame_servercmds.c transition branch calling
CG_AddAnnouncer("FIGHT!", ..., 1.1, 1000, 1, 0, 0, 1, 0). Original auto-record
behavior in that branch is a separate feature and is not changed here.

Verification: all 90 native tests pass. Tests exercise both commands,
disabled/nonzero cvar modes, exact sound paths/channel, timing at start,
midpoint and expiry, missing handles, replacing an active message, live
disable/re-enable, and lifecycle reset. Additional native parser tests
cover every nonnegative prior gamestate, repeated playing updates, a following
non-playing update, both protocol modes, and enabled/disabled cg_announcer.
WASM build and Node load/entrypoint probes pass; actual browser/dedicated
gameplay remains unverified. No pak
assets were modified.
