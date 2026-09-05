from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PROTOCOL = (ROOT / "src_2.60/game/nitmod_protocol.h").read_text(encoding="utf-8")
SERVER = (ROOT / "src_2.60/game/g_nitmod_config.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
CLIENT = (ROOT / "src_2.60/cgame/cg_nitmod_config.c").read_text(encoding="utf-8")
COMMANDS = (ROOT / "src_2.60/cgame/cg_servercmds.c").read_text(encoding="utf-8")
HINTS = (ROOT / "src_2.60/cgame/cg_nitmod_hints.c").read_text(encoding="utf-8")


def run_checks() -> None:
    assert "NITMOD_FEATURE_CLASS_HEALTH" in PROTOCOL
    assert 'va( "nch %i %i %i %i %i"' in SERVER
    for player_class in ("PC_SOLDIER", "PC_MEDIC", "PC_ENGINEER", "PC_FIELDOPS", "PC_COVERTOPS"):
        assert f"G_NITMOD_ClassMaxHealth( {player_class} )" in SERVER
    assert "nitmod_SendClassHealth( clientNum );" in SERVER
    assert "cv->vmCvar == &n_classesMaxHP" in MAIN
    assert "nitmod_SendClassHealth( -1 );" in MAIN
    assert 'NITMOD_HasArgumentCount( "nch", NUM_PLAYER_CLASSES + 1 )' in CLIENT
    assert "values[playerClass] < 0 || values[playerClass] > 32767" in CLIENT
    assert "memcpy( nitmodClassMaxHealth, values" in CLIENT
    assert 'Q_stricmp( cmd, "nch" )' in COMMANDS
    assert "NITMOD_ServerSupports( NITMOD_FEATURE_CLASS_HEALTH )" in COMMANDS
    assert "health = NITMOD_ClassMaxHealth(ci->cls);" in HINTS


if __name__ == "__main__":
    run_checks()
    print("Nitmod class-health protocol checks passed")
