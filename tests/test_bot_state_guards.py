from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_bot_and_movement_guards_use_complete_values():
    cmd = (ROOT / "src_2.60/botai/ai_cmd.c").read_text(encoding="utf-8")
    dmq3 = (ROOT / "src_2.60/botai/ai_dmq3.c").read_text(encoding="utf-8")
    main = (ROOT / "src_2.60/botai/ai_main.c").read_text(encoding="utf-8")
    actions = (ROOT / "src_2.60/botai/ai_script_actions.c").read_text(encoding="utf-8")
    pmove = (ROOT / "src_2.60/game/bg_pmove.c").read_text(encoding="utf-8")
    assert "teamleader[sizeof(bs->teamleader) - 1]" in cmd
    assert "!(g_entities[client].r.svFlags & SVF_BOT)" in dmq3
    assert "cl->pers.connected != CON_CONNECTED" in main
    assert "level.clients[0].pers.connected != CON_CONNECTED" in main
    assert "fabsf(forward[2])" in main
    assert "g_entities[i].client->pers.connected != CON_CONNECTED" in actions
    assert "fabsf(AngleDifference" in actions
    assert "!(pm->ps->pm_flags & PMF_LIMBO)" in pmove


if __name__ == "__main__":
    test_bot_and_movement_guards_use_complete_values()
