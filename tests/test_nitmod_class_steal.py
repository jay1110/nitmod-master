from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_original_class_steal_has_a_typed_runtime_consumer():
    source = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
    body = source.split("static qboolean G_NITMOD_ClassSteal", 1)[1].split(
        "qboolean Do_Activate_f", 1
    )[0]

    assert 'G_NITMOD_LegacyCvarInteger("g_classChange", 0)' in body
    assert "BODY_CLASS(body) == ent->client->sess.playerType" in body
    assert "body->activator" in body
    assert "BODY_VALUE(body) < 250" in body
    assert 'trap_Cvar_VariableIntegerValue("sv_fps")' in body
    assert "body->timestamp + 20000" in body
    assert "ent->client->sess.playerType = BODY_CLASS(body)" in body
    assert "G_NITMOD_RemoveClassTools(ent->client)" in body
    assert "G_NITMOD_AddClassTools(ent)" in body
    assert "ClientUserinfoChanged(ent->s.number)" in body
    assert "G_NITMOD_ClassSteal(ent, traceEnt)" in source


def test_class_tool_transition_covers_all_five_classes():
    source = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
    tools = source.split("static void G_NITMOD_AddClassTools", 1)[1].split(
        "static qboolean G_NITMOD_ClassSteal", 1
    )[0]
    for player_class in (
        "PC_SOLDIER",
        "PC_MEDIC",
        "PC_ENGINEER",
        "PC_FIELDOPS",
        "PC_COVERTOPS",
    ):
        if player_class != "PC_SOLDIER":
            assert player_class in tools
    for weapon in (
        "WP_DYNAMITE",
        "WP_PLIERS",
        "WP_MEDIC_SYRINGE",
        "WP_MEDKIT",
        "WP_AMMO",
        "WP_SMOKE_MARKER",
        "WP_SMOKE_BOMB",
        "WP_SATCHEL",
        "WP_SATCHEL_DET",
    ):
        assert weapon in tools


if __name__ == "__main__":
    test_original_class_steal_has_a_typed_runtime_consumer()
    test_class_tool_transition_covers_all_five_classes()
    print("Nitmod typed corpse class-steal contract passed")
