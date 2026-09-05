# Setup cancellation, shared weapon blocks and binding rendering

## qagame

Cmd_ResetSetup_f is grouped with Cmd_SetClass_f in
game/g_nitmod_class_command.c. Original sorted nitmod_cmds.c shows three
latch comparisons, with publication at ELF 0x66383 if any changed. The ET
implementation silently reset a class-only change without publishing it.
The port now restores class, primary and secondary before one userinfo update.
Entity/client ownership validation is deliberate hardening; the command wire
format and ClientCommand dispatch remain unchanged. The common prototype is
required for matching WASM call signatures after the source-file move.

Tests cover all eight changed-field combinations, publication after mutation,
idempotence, unrelated client-state preservation and invalid entities.

## cgame

Original cgame skips shared both/both_altweap metadata instead of putting it
into media fields. The skip now distinguishes TT_STRING data from braces,
including quoted braces in nested shared blocks. Quoted opening delimiters
and unterminated blocks fail through the existing source-release path.
Forced reload failures retain the previous media record. Synthetic lexer
tests complement read-only parsing of the shipped weapon assets.

## UI

Original Item_Bind_Paint has a literal FIXME fallback for controls without
a label (ui_ui_item.c, path before label joined_r0x00047e6d). This is an
intentional improvement, not a claim of original behavior: label-free controls
now render engine-owned bindings like labelled controls. A missing command
shows the existing unbound marker; null items and parentless focus painting
are guarded. Tests exercise two bindings, unbound/null input and parentless
focus flags without reading command names as cvars.

WASM builds and Node loading/ABI probes pass for all three modules. These
changes do not establish browser visual parity or complete weapon/gameplay
reconstruction. No pak or original reference artifacts are changed.
