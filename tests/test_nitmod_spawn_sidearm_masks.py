"""Source wiring regression, not a full spawn simulation."""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
source = (root / 'src_2.60/game/g_client.c').read_text()
assert 'client->sess.skill[SK_LIGHT_WEAPONS] >= 4' not in source
assert 'client->sess.skill[SK_HEAVY_WEAPONS] >= 4' not in source
assert source.count('G_NITMOD_GrantSelectedSecondary(client, g_dualSMG.integer, medicOptions);') == 1
assert 'if(!G_NITMOD_GrantSelectedSecondary' not in source
assert 'client->sess.nitmodSkillMasks[SK_LIGHT_WEAPONS]' in source
assert 'client->sess.nitmodSkillMasks[SK_HEAVY_WEAPONS], client->pers.clientFlags' in source
print('Unified secondary spawn path and reward-mask wiring verified')
