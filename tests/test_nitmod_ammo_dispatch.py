"""Pin dispatch wiring separately from the executable selection fixture.

This is source coverage, not an engine sound/zoom integration test.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
source = (root / 'src_2.60/cgame/cg_weapons.c').read_text()
dispatch = source.split('void CG_OutOfAmmoChange(', 1)[1].split('// trivial switching', 1)[0]
assert 'if(action == NITMOD_AMMO_KEEP) return;' in dispatch
assert 'if(action == NITMOD_AMMO_NEXT) { CG_NextWeap(qtrue); return; }' in dispatch
assert dispatch.index('cg.weaponSelect = choice;') < dispatch.index('if(action == NITMOD_AMMO_FINISH)')
assert 'if(action == NITMOD_AMMO_FINISH) CG_FinishWeaponChange(cg.predictedPlayerState.weapon, choice);' in dispatch
assert dispatch.count('CG_FinishWeaponChange(') == 1
finish = source.split('void CG_FinishWeaponChange(', 1)[1].split('extern pmove_t cg_pmove;', 1)[0]
assert finish.index('if( cg.binocZoomTime )') < finish.index('cg.mortarImpactTime = -2;')
assert finish.index('if(lastweap == newweap)') < finish.index('CG_PlaySwitchSound(lastweap, newweap);')
assert 'CG_SetSniperZoom(lastweap, newweap);' in finish
for weapon in ('WP_FG42SCOPE', 'WP_GARAND_SCOPE', 'WP_K43_SCOPE'):
    assert f'case {weapon}:' in finish
print('Ammo dispatch and finish wiring checks passed')
