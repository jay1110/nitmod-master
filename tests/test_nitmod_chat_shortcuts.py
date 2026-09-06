from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
COMBAT = (ROOT / "src_2.60/game/g_combat.c").read_text(encoding="utf-8")
ITEMS = (ROOT / "src_2.60/game/g_items.c").read_text(encoding="utf-8")
WEAPON = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")


def test_typed_chat_shortcuts_are_expanded_centrally():
    assert 'strchr("adhklnrpsw", clean[i + 1])' in SOURCE
    assert "clean[35] = '\\0';" in SOURCE
    assert "G_NITMOD_ShortcutName(ent->client->pers.netname)" in SOURCE
    assert "G_NITMOD_ShortcutName(g_entities[clientNum].client->pers.netname)" in SOURCE
    assert 'G_NITMOD_LegacyCvarInteger("g_shortcuts", 1)' in SOURCE
    for code in ("'a'", "'d'", "'h'", "'k'", "'l'", "'n'", "'r'", "'p'", "'s'", "'w'", "'t'"):
        assert f"case {code}:" in SOURCE
    assert "BG_GetLocationString(ent->client->ps.origin)" in SOURCE
    assert "static char label[32];" in SOURCE
    assert 'Q_strncpyz(label, item && item->pickup_name ? item->pickup_name : "Nothing", sizeof(label));' in SOURCE
    assert "BG_FindItemForWeapon(weapon)" in SOURCE
    assert "BG_FindAmmoForWeapon(weapon)" in SOURCE
    assert "BG_FindClipForWeapon(weapon)" in SOURCE
    assert "(weapon == WP_KNIFE ? 0 : ent->client->ps.ammo[BG_FindAmmoForWeapon(weapon)]) +" in SOURCE
    weapon_name = SOURCE.split("case 'w':", 1)[1].split("case 't':", 1)[0]
    assert weapon_name.index("weapon >= WP_NUM_WEAPONS") < weapon_name.index("BG_FindItemForWeapon")
    assert "G_NITMOD_ExpandChatShortcuts(ent, chatText, text, sizeof(text))" in SOURCE
    assert 'return "*unknown*"' in SOURCE


def test_expansion_is_bounded_and_preserves_unknown_tokens():
    assert "used < outputSize - 1" in SOURCE
    assert "default: return NULL" in SOURCE
    assert "output[used] = '\\0'" in SOURCE


def test_history_is_recorded_at_authoritative_events():
    assert "nitmodLastKillerClient = attacker - g_entities" in COMBAT
    assert "nitmodLastKilledClient = victimNum" in COMBAT
    assert "nitmodLastAmmoClient = ent->parent - g_entities" in ITEMS
    assert "nitmodLastHealthClient = ent->parent - g_entities" in ITEMS
    assert "nitmodLastReviverClient = ent - g_entities" in WEAPON
    assert "OnSameTeam(ent, &g_entities[clientNum])" in SOURCE


if __name__ == "__main__":
    test_typed_chat_shortcuts_are_expanded_centrally()
    test_expansion_is_bounded_and_preserves_unknown_tokens()
    test_history_is_recorded_at_authoritative_events()
    print("nitmod chat-shortcut checks passed")
