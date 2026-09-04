# Mortar bipod media and rendering

Original CG_AddPlayerWeapon, sorted/cgame_ents.c lines around 8850..8986,
selects independent team/generic model and skin handles for parts 3 and 4,
positions them on tag_barrel4/tag_barrel5 and submits each directly to the
renderer. Original weapon-relative records are identified by the accesses
to cg_weapons offsets 257800..257908 (mortar-set identity).

CG_NitmodDrawMortarBipod is now called by the active deployed-mortar special
branch. It copies lighting origin, shadow plane and render flags from the
weapon parent, selects media independently for each leg, positions against
the moving barrel and submits both. Existing first-person/not-raising/part-3
gates remain. Generic first-person part rendering already supplies the
disguise-adjusted team. No gameplay, firing, weapon-ID or network change.

Full-cgame tests inspect real tag and renderer callbacks for six team values
and sixteen independent model/skin override combinations (96 scenarios).
Both entire refEntity outputs are checked, including transformed origins,
axes, lighting and flags. Null arguments produce no callbacks. The original
zero-handle submission behavior is retained, not silently replaced by a
different rendering policy. Each leg starts with a clean typed entity;
decompiler copy loops and writes back into cached skins are not reproduced.

This closes the previously documented bipod media gap, not all mortar
animation or attachment behavior. Actual deployment/raising transitions and
live browser visual parity remain unverified. Original pak assets and
reference binaries remain untouched.
