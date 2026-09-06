"""Source regression for the original empty-bank termination branch."""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
source = (root / 'src_2.60/cgame/cg_weapons.c').read_text()
body = source.split('void CG_WeaponBank_f(void)', 1)[1].split('void CG_Weapon_f(', 1)[0]
lookup = body.index('num = getNextWeapInBank(bank, cycle+i);')
sentinel = body.index('if(num == WP_NONE && (NITMOD_UsesOriginalProtocol() || NITMOD_UsesNitmodHud())) break;')
select = body.index('if(CG_WeaponSelectable(num))')
assert lookup < sentinel < select
assert 'CG_FinishWeaponChange(curweap, num);' in body
print('Nitmod bank sentinel wiring passed')
