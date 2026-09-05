# Tooltip layout on the widened menu canvas

The shared menu renderer previously clamped tooltips against x=635 twice:
once in local source coordinates, then after parent positioning, mutating
rectClient on every overflow. The existing widened UIDLL canvas made that
fixed final bound incorrect and moving menus could retain stale offsets.

Tooltip_ComputePosition now retains its unclamped source coordinates.
Item_SetScreenCoords clamps only the resolved tooltip rectangle, using the
UIDLL virtual width minus five, or 635 for cgame's unchanged menu canvas.
Both paths also keep the rectangle above y=475 and inside the top/left
five-unit margin. The preferred location, text measurement and size remain
unchanged. Oversized tooltips are pinned to the margin, not scaled or clipped.

This is an intentional layout correction beyond original fixed-635
behavior, not a newly reconstructed menu action. No menu/PK3 changes.
The UI fixture verifies three aspect ratios, four parent positions and ten
repeated position cycles with unchanged source coordinates. Browser visual
validation and oversized-text wrapping are not covered.
