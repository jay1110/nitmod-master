# Shared UI slider pipeline

Reference: src_nitmod_decompiled/ui/sorted/ui_ui_item.c,
Item_Slider_HandleKey, Item_Slider_ThumbPosition, Item_Slider_OverSlider,
Item_Slider_Paint; typed baseline in src_2.60/ui/ui_shared.c.

The original 96-unit track, 12-unit thumb, label offset (textRect.x +
textRect.w + 8), strict hit rectangle and accepted mouse/Enter keys are
retained. These operations already existed in ET260; this batch closes
functional/safety gaps in their shared port, not a new Nitmod-only feature.

Paint, hit testing, clicking and dragging now share validated geometry/ranges.
Missing type data/Cvar and nonfinite, equal or reversed bounds cause no write
or slider rendering. The thumb position has a finite fallback. NaN Cvar values
display at minimum, infinite values clamp to an endpoint. Double intermediate
arithmetic supports finite float endpoints whose subtraction would overflow
float. A missing parent cannot be dereferenced for focus-pulse color.

Click and drag both clamp their fraction to [0,1]. This intentionally differs
from the original click routine, which can write below the minimum in the
left half-thumb hit margin. Key releases are rejected. The original unused
extra Cvar read during painting is removed. Data invalidated during capture
is rechecked before every write. No assets or menu definitions changed.

CheckSliders in test_nitmod_ui_bitflag.c checks 200 click combinations (label
offset, edge positions, five keys and press/release), thumb/render geometry,
real Item_StartCapture -> Menu_PaintAll drag updates and Item_HandleKey release,
capture data loss, invalid/huge ranges and nonfinite Cvars. Shared code is built
in both cgame and UI. This is not an original-browser screenshot comparison;
full menu and gameplay parity remain separate work.
