# Original administrative blindness receive path

Original G_shrubbot_blind in nitmod_admin.c sets playerState eFlags bit
0x400000 at client offset 0x68, after its administrative permission checks.
Original CG_DrawFlashFade reads that flag at snapshot byte offset 0x96,
then writes ui_blackout=1 after normal speclock synchronization. The literal
is verified in cgame.mp.i386.so at file offset 0x10e9db (`1`); the ordinary
clear value at 0x10e957 is `0`.

NITMOD_EF_BLINDED now names that original-protocol flag. CG_DrawFlashFade
applies it only for NITMOD_UsesOriginalProtocol(), preserving native ET and
the reconstructed et260-layout interpretation. The current draw uses the
already-read int_ui_blackout, so the effect follows the original one-frame
cvar synchronization order. The flag overrides an ordinary clear in the same
frame; removing it permits the normal clear on subsequent frames. No client
command manufactures this flag or bypasses the server's authorization.

The complete cgame fixture covers 96 combinations of original/native/rebuilt
protocol, powerup mask, existing cvar, multiview and blindness. It checks write
count, final cvar value and full-screen render count. The 480 existing overlay
geometry checks remain active. Original-server live replay remains pending.
This ports the client receive/render behavior, not shrubbot administration on
the reconstructed server. No pak asset, original binary or protocol is changed.
