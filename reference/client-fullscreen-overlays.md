# Full-screen overlays and spectator blackout

Original cgame ELF CG_DrawPicFullScreen 0x50270 and CG_FillRectFullScreen
0x50340 scale X by glconfig.vidWidth/640 and Y by screenYScale, independently
of the aspect-corrected HUD anchor. The picture helper flips texture UVs for
negative dimensions; the solid helper retains signed dimensions and restores
the renderer color after drawing.

Typed implementations in cg_drawtools.c now serve weapon-scope and binocular
reticles, flash fade, zoom transition, damage flash and fire flash. Original
protocol bypasses HUD transforms; native and reconstructed et260 layouts
retain CG_AdjustFrom640 behavior. In the default stretched HUD configuration
this often produces the same coordinates as before; the difference matters
when an aspect-corrected HUD transform is active. This is not a new reticle
asset or a claim that all reticle geometry has been reconstructed.

CG_DrawFlashFade (ELF 0x3da00) uses int_ui_blackout even in single-player
mode and does not suppress the powerup-to-ui_blackout synchronization when
multiview is active. Those differences are now original-protocol gated.
The native multiview exceptions remain for native-layout servers. The current
frame still uses the already-read cvar, matching the original one-frame
writeback ordering. The original additional flag-0x400000 forced blackout
branch is now mapped to shrubbot blindness and active only for original
Nitmod servers; see client-admin-blind.md. Fade timing,
fire sound and damage calculations are otherwise unchanged.

Tests: 480 geometry/UV/color/shader cases over five resolutions, four HUD
anchors, dimension signs, picture/solid modes and three protocol layouts;
48 real CG_DrawFlashFade cases over powerup bits, current UI state and
multiview. Renderer calls and UI cvar writes are captured in the full cgame
fixture; unexpected syscalls remain fatal. Full native CTest, WASM build and
Node side-module loader/ABI probes run. Browser screenshots and original
binary replay remain pending. Pak files and original modules are unchanged.
