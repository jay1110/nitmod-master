# Modern magazine display (HUDFlags bit 16)

The original menu already sets bit 16; no asset change is needed. The typed
status HUD now draws magazine segments instead of the numeric clip/reserve
string when that bit is enabled and a clip plus reserve count is available.
Single-count tools, mounted weapons and disabled-bit displays retain their
existing numeric/hidden paths.

Evidence: sorted cgame_ui.c, LAB_00052430 (akimbo) and the single-magazine
branch at lines 6243 onward. These are Ghidra source labels, not addresses
in the separately supplied ELF. Original behavior reproduced:

- Capacity comes from the typed weapon's ammo table, never a wire ID.
- Segments start at (590,458), size 1x4, adjusted for resolution before a
  three-physical-pixel step to the left.
- All segments turn red at or below capacity/4; empty segments have .35 alpha.
- Single magazines wrap at segments 50 and 100 with five scaled pixels of
  vertical spacing. Akimbo uses the secondary clip first and primary at y464.
- Later rows retain the original doubled screen-X-bias expression.
- Reserve count is centered at x606, y463 plus 2.5 per wrap, or y466 for akimbo,
  scale .2, style 3. Existing limboFont1 is used; font/centering equivalence
  still requires a visual comparison with the original client.

Defensive differences: invalid weapon IDs, negative visible counts and
capacities outside 1..150 fall back to the numeric HUD. The display weapon
selected by CG_PlayerAmmoValue supplies the capacity, avoiding a mismatched
predicted weapon when viewing another player's ammo. No ammo or weapon state
is changed, and no new weapon is granted or implemented by this renderer.

The full-cgame fixture tests all 32 flag combinations, capacities 1/8/30/50/
51/100/101/150, every fill level through capacity+1, single/dual clips, scaled
rectangle geometry, row ordering, warning colors, alpha and invalid inputs.
The renderer callbacks are tested; this is not browser screenshot parity.

Native build: 90/90 tests pass. WASM build and Node entrypoint probes pass.
No pak assets or engine/protocol contracts are modified. Browser/dedicated
gameplay, full scoreboard parity, spree placement and missing weapon behavior
remain separate unfinished work.
