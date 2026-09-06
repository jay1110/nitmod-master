"""Source wiring check; not a live spawn/gameplay parity test."""
from pathlib import Path

root = Path(__file__).resolve().parents[1]
source = (root / "src_2.60/game/g_client.c").read_text()
assert "client->sess.skill[SK_BATTLE_SENSE] >= 1" not in source
assert source.count("if( client->sess.nitmodSkillMasks[SK_BATTLE_SENSE] & 2u )") == 3
assert "client->sess.nitmodSkillMasks[SK_SIGNALS] & 2u" in source
reference = (root / "src_nitmod_decompiled/qagame/sorted/nitmod_game.c").read_text()
tools = reference[reference.index("void G_AddClassSpecificTools_part_3"):]
assert "*(uint *)(param_1 + 0xed0) >> 1" in tools
print("Spawn binocular reward-mask source wiring passed")
