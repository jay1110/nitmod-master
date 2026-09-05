# System-settings batch

The 21-value systemCvarsGet/Reset/Apply staging pipeline is consolidated
in ui_nitmod_settings.c and dispatched through the real menu-script path.
This replaces the duplicated UI main blocks, not 63 previously absent features.
Graphics, sound, network and mouse fields retain their names and formatting;
gamma/sensitivity remain float, texture mode remains a string, others retain
integer truncation. Apply retains the existing zero-rate fallback 5000/30/1.
No video/sound restart is issued implicitly and no configuration files change.

All values are read and checked before any writes. Nonfinite/out-of-range
numeric input rejects the batch without clearing staged values. Reset only
clears ui_ staging cvars, not engine settings. Successful apply copies all
21 fields and then clears all 21 staging fields. These are deliberate safety
improvements around the existing menu contract, not certified binary parity.

The actual UI_RunMenuScript fixture checks all read/write names, order and
values for get/apply/reset, zero-rate fallback and rejection at every numeric
field: 126 profiles. No unexpected syscall is accepted. Original menu files
and pak remain untouched; browser settings behavior is still unverified.
