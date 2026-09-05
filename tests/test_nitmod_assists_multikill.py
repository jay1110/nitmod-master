from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GAME = ROOT / "src_2.60" / "game"
COMBAT = (GAME / "g_combat.c").read_text(encoding="utf-8")
LOCAL = (GAME / "g_local.h").read_text(encoding="utf-8")

assert "nitmodDamageReceived[MAX_CLIENTS]" in LOCAL
assert "nitmodMultiKillCount" in LOCAL
assist = COMBAT.split("static void G_NITMOD_AwardKillAssists", 1)[1].split(
    "static void G_NITMOD_RecordMultiKill", 1
)[0]
assert 'G_NITMOD_LegacyCvarInteger("n_killAssistances", 1)' in assist
for bit, wire in ((1, "an 1 %i"), (2, "an 2 %i"), (4, "an 3 -%i")):
    assert f"options & {bit}" in assist
    assert wire in assist
assert "G_AddSkillPoints(helper, SK_BATTLE_SENSE" in assist
assert "G_LoseSkillPoints(helper, SK_BATTLE_SENSE" in assist
assert "victim->client->nitmodDamageReceived[clientNum] = 0" in assist

damage = COMBAT.split("void G_Damage", 1)[1]
assert "targ->client->nitmodDamageReceived[attacker->s.number]" in damage
assert damage.index("nitmodDamageReceived[attacker->s.number]") < damage.index("targ->health -= take")

multi = COMBAT.split("static void G_NITMOD_RecordMultiKill", 1)[1].split(
    "int G_NITMOD_ForceLimboThreshold", 1
)[0]
assert 'G_NITMOD_LegacyCvarInteger("g_multikillTime", 2000)' in multi
assert 'trap_Cvar_VariableIntegerValue("g_announcer") & 4' in multi
assert 'va("z2 %i %i"' in multi
assert "if( detail > 4 ) detail = 4" in multi

print("Nitmod kill-assistance and multikill checks passed")
