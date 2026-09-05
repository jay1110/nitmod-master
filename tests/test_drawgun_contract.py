"""Protect the recovered original Nitmod first-person draw-gun modes."""
from pathlib import Path

root = Path(__file__).resolve().parents[1]
debug = (root / "src_2.60/cgame/cg_nitmod_debug.c").read_text(encoding="utf-8")
weapons = (root / "src_2.60/cgame/cg_weapons.c").read_text(encoding="utf-8")
original_media = (root / "src_nitmod_decompiled/cgame/sorted/cgame_client.c").read_text(encoding="utf-8")
original_draw = (root / "src_nitmod_decompiled/cgame/sorted/cgame_ents.c").read_text(encoding="utf-8")

expected = {
    2: "textures/sfx/transgunWhite",
    3: "textures/sfx/transgunRed",
    4: "textures/sfx/transgunGreen",
    5: "textures/sfx/transgunBlue",
    6: "textures/sfx/construction",
}
for mode, shader in expected.items():
    assert f"case {mode}:" in debug
    assert f'"{shader}"' in debug
    assert f'"{shader}"' in original_media
    if mode == 2:
        assert "1 < (int)GHIDRA_FIELD(cg_drawGun, 12, 4)" in original_draw
    else:
        assert f"GHIDRA_FIELD(cg_drawGun, 12, 4) == {mode}" in original_draw

assert "CG_NitmodViewWeaponShader(cg_drawGun.integer)" in weapons
assert "ps && !cg.renderingThirdPerson" in weapons
assert "gun->customShader = viewShader" in weapons
print("draw-gun contract: ok")
