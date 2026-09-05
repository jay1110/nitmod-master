from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
COMBAT = (ROOT / "src_2.60/game/g_combat.c").read_text(encoding="utf-8")
ITEMS = (ROOT / "src_2.60/game/g_items.c").read_text(encoding="utf-8")
WEAPON = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")


def test_typed_chat_shortcuts_are_expanded_centrally():
    assert 'G_NITMOD_LegacyCvarInteger("g_shortcuts", 1)' in SOURCE
    for code in ("'a'", "'d'", "'h'", "'k'", "'l'", "'n'", "'r'", "'p'", "'s'", "'w'", "'t'"):
        assert f"case {code}:" in SOURCE
    assert "BG_GetLocationString(ent->r.currentOrigin)" in SOURCE
    assert "BG_FindItemForWeapon(weapon)" in SOURCE
    assert "BG_FindAmmoForWeapon(weapon)" in SOURCE
    assert "BG_FindClipForWeapon(weapon)" in SOURCE
    assert "G_NITMOD_ExpandChatShortcuts(ent, chatText, text, sizeof(text))" in SOURCE
    assert 'return "*unknown*"' in SOURCE


def test_expansion_is_bounded_and_preserves_unknown_tokens():
    assert "used < outputSize - 1" in SOURCE
    assert "default: return NULL" in SOURCE
    assert "output[used] = '\\0'" in SOURCE


def test_history_is_recorded_at_authoritative_events():
    assert "nitmodLastKillerClient = attacker - g_entities" in COMBAT
    assert "nitmodLastKilledClient = self - g_entities" in COMBAT
    assert "nitmodLastAmmoClient = ent->parent - g_entities" in ITEMS
    assert "nitmodLastHealthClient = ent->parent - g_entities" in ITEMS
    assert "nitmodLastReviverClient = ent - g_entities" in WEAPON
    assert "OnSameTeam(ent, &g_entities[clientNum])" in SOURCE


if __name__ == "__main__":
    test_typed_chat_shortcuts_are_expanded_centrally()
    test_expansion_is_bounded_and_preserves_unknown_tokens()
    test_history_is_recorded_at_authoritative_events()
    print("nitmod chat-shortcut checks passed")
