from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
POISON = (ROOT / "src_2.60/game/g_nitmod_poison.c").read_text(encoding="utf-8")
ITEMS = (ROOT / "src_2.60/game/g_items.c").read_text(encoding="utf-8")
TRIGGER = (ROOT / "src_2.60/game/g_trigger.c").read_text(encoding="utf-8")
CLIENT = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")


assert "if(!(poisonOptions & 2)) return;" in POISON
assert "(poisonOptions & 8)" in POISON
assert "nitmodPoisonAttacker == provider->s.number" in POISON
assert "nitmodPoisonAttacker = -1;" in POISON
assert "nitmodPoisonStacks = 0;" in POISON
assert "G_NITMOD_CurePoisonFromHealth(other, ent->parent, qfalse);" in ITEMS
assert "G_NITMOD_CurePoisonFromHealth(touchClients[i], NULL, qtrue);" in TRIGGER
assert "if(g_poison.integer && (G_NITMOD_FirstAidUnlocks(client) & 16u))" in CLIENT
assert "AddWeaponToPlayer(client, WP_POISON_SYRINGE" in CLIENT
assert "poisonAmmo->defaultStartingAmmo" in CLIENT
assert "poisonAmmo->defaultStartingClip" in CLIENT
assert "NITMOD_PlaySoundEvent(victim, 8);" in POISON

print("Nitmod poison health-pack/cabinet cure checks passed")
