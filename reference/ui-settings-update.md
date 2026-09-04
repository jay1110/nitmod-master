# UI settings update adapter

Reference: original ui.mp.i386.so UI_Update, ELF 0x20cf0 (992 bytes),
src_nitmod_decompiled/ui/sorted/ui_ui_misc.c, UI_Update.

The existing seven update actions are consolidated in ui_nitmod_settings.c:
name get/set, network rate, color/depth precision, subdivision selection,
four graphics preset configurations, and mouse inversion. This is not seven
newly implemented features. The corrected original-specific behavior is the
network preset: ui_rate >=5000 sets ui_cl_maxpackets=100, not ET's 30.
The other intervals remain >=4000: 15/2 and below4000: 15/1 (packets/dup).

Colorbits 0/16 also clear stencil bits; 32 sets depthbits=24 without changing
stencil bits. LOD bias 0/1/2 selects subdivisions 4/12/20. Presets queue the
original high/normal/fast/fastest ui cfg filenames via EXEC_APPEND; no cfg is
created or edited. Name transfers retain the 1024-byte read boundary and colors.
These are menu updates, not automatic application of all staged engine cvars.

Safety differences: null/empty/unknown actions do not read arbitrary cvars;
nonfinite rate values and numeric selectors outside signed-int range do not
produce updates. Valid numeric selectors retain truncation toward zero.
Integer conversion no longer occurs before unrelated string actions. Fixed
preset filenames and direct cvar APIs avoid interpolating input into commands.

CheckSettings invokes the actual update menu dispatch for 292 numeric selector
profiles and directly checks 1005 rate values around both thresholds, both name
transfers, out-of-range and unknown inputs. The engine mock checks the emitted
cvar names, values and preset command strings. Native and WASM builds include
the new module through CMake and historical UI SCons source lists.

Original menu assets and pak remain unchanged. This does not establish visual
parity or fix every remaining UI feature; live browser verification is pending.
