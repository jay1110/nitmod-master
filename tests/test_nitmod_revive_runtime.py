from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GAME = ROOT / "src_2.60" / "game"
LOCAL = (GAME / "g_local.h").read_text(encoding="utf-8")
WEAPON = (GAME / "g_weapon.c").read_text(encoding="utf-8")
COMBAT = (GAME / "g_combat.c").read_text(encoding="utf-8")
MAIN = (GAME / "g_main.c").read_text(encoding="utf-8")

for field in (
    "nitmodReviveSpree",
    "nitmodBestReviveSpree",
    "nitmodLastReviveTime",
    "nitmodMultiReviveCount",
):
    assert field in LOCAL

revive = WEAPON.split("static void G_NITMOD_RecordRevive", 1)[1].split(
    "qboolean ReviveEntity", 1
)[0]
assert 'G_NITMOD_LegacyCvarInteger("n_reviveSpreeOptions", 1)' in revive
assert 'G_NITMOD_LegacyCvarInteger("n_multiReviveTime", 2000)' in revive
assert "nitmod_Announce(medic->s.number, count, 4)" in revive
assert "medic->client->nitmodMultiReviveCount - 2, 5" in revive
assert WEAPON.index("G_NITMOD_RecordRevive(ent)") < WEAPON.index("return usedSyringe")

ended = COMBAT.split("static void G_NITMOD_EndReviveSpree", 1)[1].split(
    "int G_NITMOD_ForceLimboThreshold", 1
)[0]
assert "options & 8" in ended
assert "count > 4" in ended
assert "TEAMMATE" in ended
assert "nitmodReviveSpree = 0" in ended
assert "G_NITMOD_EndReviveSpree(self, attacker)" in COMBAT

runtime = MAIN.split("static void G_NITMOD_RunServerAutomation", 1)[1].split(
    "void G_RunFrame", 1
)[0]
for cvar in (
    "n_crazyGravity",
    "n_crazyGravityMin",
    "n_crazyGravityMax",
    "n_crazyGravityInterval",
    "g_autoQuitDelay",
):
    assert f'G_NITMOD_LegacyCvarInteger("{cvar}"' in runtime
assert 'trap_Cvar_Set("g_gravity", "800")' in runtime
assert 'trap_SendConsoleCommand(EXEC_NOW, "quit\\n")' in runtime
assert "G_NITMOD_RunServerAutomation();" in MAIN

print("Nitmod revive and server-automation checks passed")
