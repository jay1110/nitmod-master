# Profile and control-settings batch

profileCvarsGet/Apply/Reset and defaultControls now share the typed settings
adapter rather than four embedded UI main branches. Original reference:
UI_RunMenuScript in sorted/ui_ui_misc.c, around Ghidra 0x36bd0..0x36e97.
The decompiler omits call arguments there; the existing typed menu contract
is retained rather than guessing new argument meanings.

Get stages the integer mouse-pitch selector. Apply reads both selectors,
sets ui_mousePitch/m_pitch, queues default.cfg or default_left.cfg, updates
the binding table and clears both staging fields. Reset only clears staging;
defaultControls only queues the selected defaults and updates bindings.
Fractional selectors retain truncation and any nonzero integer selects the
alternate mode. Nonfinite/out-of-int-range input now causes no partial writes.

100 menu-script profiles verify all action/handedness/pitch combinations,
exact cvar names/values, commands and clearing; a NaN apply case verifies
atomic rejection. Existing full binding lifecycle tests remain in place.
No cfg files are edited. This is coherent integration of existing behavior,
not four new Nitmod features. Browser/profile persistence parity is open.
