from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def test_runtime_values_are_checked_as_their_real_types():
    ents = (ROOT / "src_2.60/cgame/cg_ents.c").read_text(encoding="utf-8")
    predict = (ROOT / "src_2.60/cgame/cg_predict.c").read_text(encoding="utf-8")
    commands = (ROOT / "src_2.60/cgame/cg_servercmds.c").read_text(encoding="utf-8")
    ui = (ROOT / "src_2.60/ui/ui_main.c").read_text(encoding="utf-8")
    assert "!cent->dl_stylestring[0]" in ents
    assert "fabsf(AngleDelta(ps2->viewangles[i], ps1->viewangles[i]))" in predict
    assert commands.count("if(text[0])") >= 3
    assert 'Com_Printf( "%s", trap_TranslateString( "Favorite already in list' in ui

if __name__ == "__main__":
    test_runtime_values_are_checked_as_their_real_types()
