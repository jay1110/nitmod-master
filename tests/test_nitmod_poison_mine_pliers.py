"""Wiring regression, not an engine simulation of the engineer trace."""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
source = (root / 'src_2.60/game/g_weapon.c').read_text()
start = source.index('if ( traceEnt->methodOfDeath == MOD_LANDMINE ||')
end = source.index('} else if', start)
branch = source[start:end]
assert 'MOD_POISON_GAS_MINE' in branch
assert branch.index('int mineWeapon') < branch.index('G_FreeEntity( traceEnt )')
# Full function contains exactly the three saved-identity refunds.
assert source.count('Add_Ammo(ent, mineWeapon, 1, qfalse)') == 3
missile = (root / 'src_2.60/game/g_missile.c').read_text()
assert 'grenadeWPID == WP_POISON_MINE ? MOD_POISON_GAS_MINE : MOD_LANDMINE' in missile
print('Poison mine producer/pliers dispatch and three refund paths wired consistently')
