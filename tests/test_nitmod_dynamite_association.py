"""Planting association wiring, not a gameplay replay."""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
weapon = (root / 'src_2.60/game/g_weapon.c').read_text()
utils = (root / 'src_2.60/game/g_utils.c').read_text()
assert weapon.count('traceEnt->nitmodDynamiteObjective = hit->s.number;') == 1
assert weapon.index('traceEnt->nitmodDynamiteObjective = hit->s.number;') < weapon.index('//bani - reordered this check')
init = utils.split('void G_InitGentity(', 1)[1].split('\n}', 1)[0]
assert 'e->nitmodDynamiteObjective = 0;' in init
assert 'memset (ed, 0, sizeof(*ed));' in utils
print('Primary-objective association recorded; init/free reset storage; constructible unchanged.')
