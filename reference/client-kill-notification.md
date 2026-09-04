# HUDFlags kill notification

The original options_nit_hud.menu already toggles cg_HUDFlags bit 4 for the
Nitmod-style kill notification. The typed cgame previously registered the
cvar but did not consume that bit. No menu/PK3 modification is needed.

CG_Obituary now routes non-team local kill notices through CG_NitmodKillPrint
when bit 4 is set. Otherwise the existing priority centerprint remains, as
it does for teammate/swap messages. The ordinary obituary feed is unaffected.
The existing team classification is retained; original Deathmatch teamkill
exceptions and complete obituary semantics remain separate work.

The typed HUD stores one bounded 64-byte message, replacing it on a new kill.
Lifetime is 1850 ms, alpha decreases from 1 to 0, and text scale is
(sin(alpha * 1.1) + 0.7) * 0.2. Drawing is centered at virtual (320, 120),
white, style 3, using the existing limboFont1. Font/layout fidelity still
needs an original-client screenshot comparison. Lifecycle reset clears it.
Changing the flag does not cancel a notice already started, matching the
original start-time gate. Arithmetic uses a double end time to avoid signed
addition overflow and clamps rollback-time alpha to one (defensive deviation).

Evidence: cgame_events.c original kill-notice branch and cgame_nitrox.c
nitmod_AddKillPrint/nitmod_DrawKillPrint. Local ELF symbols are 0xf68f0 and
0xf6930; llvm-objdump confirms duration 0x73a, sin call and centered-text call.

The full-cgame fixture tests all 32 HUD flag combinations with team/non-team
classification, alpha at start/midpoint/end, text truncation, replacement,
team-message non-interference, reset, and drawing before/after expiry. These
are handler/renderer tests, not a real-server obituary replay.

Native build and all 90 tests pass; WASM build and Node load/entrypoint probes
are run. Pak files and protocol IDs remain unchanged. Modern ammo-bar bit 16
is now covered in client-modern-ammo.md; partial spree-placement bit 8 is
covered in client-spree-display.md. Full Browser/Dedicated parity remains open.
