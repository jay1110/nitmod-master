from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")


def test_constructible_xp_is_awarded_per_progress_step_when_sharing_is_enabled():
    start = SOURCE.index("static qboolean TryConstructing")
    end = SOURCE.index("void Weapon_Engineer", start)
    body = SOURCE[start:end]

    assert 'G_NITMOD_LegacyCvarInteger("g_constructiblexpsharing", 0)' in body
    assert "constructxpbonus /" in body
    assert "(255.f / constructionStep) + 0.01f" in body
    assert '"construction sharing."' in body


def test_full_completion_xp_is_not_duplicated_in_sharing_mode():
    start = SOURCE.index("static qboolean TryConstructing")
    end = SOURCE.index("void Weapon_Engineer", start)
    body = SOURCE[start:end]

    completion = body.index('"finishing a construction"')
    guard = body.rfind('!G_NITMOD_LegacyCvarInteger("g_constructiblexpsharing", 0)', 0, completion)
    assert guard >= 0
