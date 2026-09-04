# Original UI widescreen layout and input

Reference: original ui.mp.i386.so symbols and sorted UI source:

- UI_AdjustFrom640: ELF 0x10900; AdjustFrom640: 0x38670.
- Cui_WideRect: 0x2b090, Cui_WideX: 0x2b160, Cui_WideXoffset: 0x2b1a0.
- Menu_UpdatePosition: 0x2ee10; _UI_MouseEvent: 0x27780.
- UI_DrawLoadPanel: 0x12b20 (Ghidra relocation adds 0x10000).

For displays wider than 4:3, original drawing multiplies horizontal scale
by (4/3)/aspect. The virtual canvas width becomes aspect*480. Wider menus
therefore retain 4:3 proportions rather than stretching the 640-wide layout.
Typed helpers derive aspect from positive engine viewport dimensions, leaving
the engine's raw xscale/yscale untouched. Missing dimensions fall back to 640.

Active paths now include UI picture/text scaling, shared model-preview
viewport scaling, fullscreen menu child centering, the (16,*,608,*) panel
centering rule, clouds width expansion, cursor movement across the widened
canvas and centering of the loading panel. Existing hit tests operate in
the same virtual coordinates (the original's equal aspect multiplication
on both sides of Rect_ContainsPoint cancels out).

Full-640x480 item backgrounds retain the original Cui_WideRect special
scaling, including its r_mode=11 exception; this legacy path is distinct
from ordinary item centering. Fullscreen menu background drawing and the
original 635-unit tooltip right limit are not redesigned in this patch.
Do not claim every background asset is visually verified at every resolution.

Corrections relative to original mutable layout: rectangle transformations
use temporary copies, so repeated positioning does not compound background
scaling/cloud width. Item_UpdatePosition uses the same parent layout as
Menu_UpdatePosition, retaining centered placement after script transitions.
Loading-panel coordinates are restored after rendering instead of adding an
offset to static records repeatedly. Cursor arithmetic is widened and clamped
before integer conversion. No protocol or public engine ABI changes.

UIDLL gates shared menu changes; cgame's independent HUD placement and native
shared-menu scale are unchanged. This is not a rewrite of the cgame HUD.

Full UI fixture covers seven viewport profiles (4:3, 5:4, 16:9, ultrawide,
4K and unavailable dimensions), real picture syscall coordinates, centered
hit tests, ten repeated fullscreen and inset-menu updates per profile,
background mode-11 handling, 21 loading-panel renders with restored source
positions/full physical clears, and repeated extreme mouse deltas.

Native build: 97/97 CTest cases pass. WASM build and Node individual/concurrent
loads plus entrypoint probes pass for all three modules. Live browser visual
comparison remains pending. pak assets and original modules are untouched.
