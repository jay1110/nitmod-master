# Adrenaline inventory and HUD anchors

Original bg_itemlist item 31 (cgame ELF 0x12ed00 + 31 * 56) has tag 43,
ammo index 43 and clip index 43. Original BG_FindAmmoForWeapon and
BG_FindClipForWeapon read offsets 0x30/0x34. The ET item previously pointed
both indices at the medic revive syringe. Original snapshot decoding already
preserves independent slots, so an engineer with adrenaline but no revive
syringes was incorrectly rejected by CG_WeaponSelectable.

The shared typed item now uses WP_MEDIC_ADRENALINE for both indices.
AddWeaponToPlayer initializes ammo through those accessors; prediction's
PM_WeaponAmmoAvailable/PM_WeaponUseAmmo and selection consume the same slots.
This removes the deliberately retained stock ET sharing difference: rebuilt
Nitmod cgame/qagame/ui must be deployed consistently for reconstructed local
games. Original Nitmod servers already use the independent inventory.

tests/check_adrenaline_inventory.h covers 22 reserve/clip consumption cases,
unchanged revive-syringe inventory, availability with an empty revive syringe,
and rejection when only revive syringes remain. Existing bank-7 cycles and
hash-pinned alias comparisons also run; all 44 representable original alias
pairs now match.

The supplied 2026-09-04-091312 screenshot is the ORIGINAL native client,
not a faulty WASM rendering. The earlier right-anchor interpretation was wrong.
The original cgame_ui.c compass block uses outer rect (46,382,86,86), ring
(50,386,78,78), and CG_DrawAutoMap uses (54,390,70,70). CG_HudPlacement(1)
selects the left anchor. Original CG_Draw2D calls player status without the
ET portrait and draws the compass for spectators too. The compact map stays
visible while the expanded map is open; cg_drawCompass=0 still draws the
expanded map.

These paths now use the original layout for the original Nitmod protocol,
preserving stock ET behavior otherwise. The 1920x1080 anchor regression checks
the ring at (112.5,868.5), size 175.5 square, matching the reference footprint.
This is a transform test, not a browser screenshot comparison. Full UI/HUD
pixel parity remains unverified. Pak content is unchanged.

Bomb and poison weapon media from the previous batch remain separate caches;
their ownership, selection and firing integration is still pending.
