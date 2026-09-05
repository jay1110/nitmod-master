from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
VIEW = (ROOT / "src_2.60/cgame/cg_nitmod_view.c").read_text(encoding="utf-8")
ENTS = (ROOT / "src_2.60/cgame/cg_ents.c").read_text(encoding="utf-8")
FRAME = (ROOT / "src_2.60/cgame/cg_view.c").read_text(encoding="utf-8")


def test_original_weapon_mask_mapping():
    assert "case WP_PANZERFAUST: option = 1" in VIEW
    assert "case WP_MORTAR_SET: option = 2" in VIEW
    assert "case WP_GPG40:" in VIEW and "case WP_M7: option = 4" in VIEW


def test_original_server_compatible_owner_tracking():
    assert "state->clientNum != cg.snap->ps.clientNum" in VIEW
    assert "CG_NitmodMissileCameraTrack(cent);" in ENTS
    assert "modelindex" not in VIEW.split("CG_NitmodMissileCameraTrack", 1)[1].split("CG_NitmodDrawMissileCamera", 1)[0]


def test_frame_lifecycle_and_view_restore():
    assert "CG_NitmodMissileCameraBeginFrame();" in FRAME
    assert "CG_NitmodDrawMissileCamera();" in FRAME
    assert "trap_R_SaveViewParms();" in VIEW
    assert "trap_R_RestoreViewParms();" in VIEW
    assert "cg.refdef_current = mainView;" in VIEW
