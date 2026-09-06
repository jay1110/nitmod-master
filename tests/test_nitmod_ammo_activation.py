"""Activation wiring regression, not engine integration coverage."""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
source = (root / 'src_2.60/cgame/cg_nitmod_ammo.c').read_text()
assert '(!NITMOD_UsesOriginalProtocol() && !NITMOD_UsesNitmodHud())' in source
assert 'current == WP_TRIPMINE || current == WP_POISON_MINE' in source
assert '*choice = WP_PLIERS;' in source
assert 'current == WP_SATCHEL && CG_WeaponSelectable(WP_SATCHEL_DET)' in source
for original in (False, True):
    for nitmod in (False, True):
        assert (not (not original and not nitmod)) == (original or nitmod)
print('Nitmod ammo activation wiring passed')
