"""Compare every typed filename/section selection with original machine operands."""
import importlib.util
import pathlib
import re
import sys

root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('weapon_paths', root / 'tools/extract_weapon_paths.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
original = module.extract(root)
assert original[20]['filename'] == 'pliers.weap' and original[20]['alternate'] == 0
mine_contact = (root / 'src_2.60/game/g_nitmod_mine_contact.c').read_text()
assert 'candidate->s.weapon != WP_PLIERS' in mine_contact
# Explicit semantic translation; original numeric IDs must never index native enums.
identities = {
    'WP_KNIFE': 1,
    'WP_LUGER': 2,
    'WP_MP40': 3,
    'WP_GRENADE_LAUNCHER': 4,
    'WP_PANZERFAUST': 5,
    'WP_FLAMETHROWER': 6,
    'WP_COLT': 7,
    'WP_THOMPSON': 8,
    'WP_GRENADE_PINEAPPLE': 9,
    'WP_STEN': 10,
    'WP_MEDIC_SYRINGE': 11,
    'WP_AMMO': 12,
    'WP_SILENCER': 14,
    'WP_DYNAMITE': 15,
    'WP_SMOKETRAIL': 16,
    'WP_MEDKIT': 18,
    'WP_BINOCULARS': 19,
    'WP_PLIERS': 20,
    'WP_SMOKE_MARKER': 21,
    'WP_KAR98': 22,
    'WP_CARBINE': 23,
    'WP_GARAND': 24,
    'WP_LANDMINE': 25,
    'WP_SATCHEL': 26,
    'WP_SATCHEL_DET': 27,
    'WP_SMOKE_BOMB': 28,
    'WP_MOBILE_MG42': 29,
    'WP_K43': 30,
    'WP_FG42': 31,
    'WP_MORTAR': 33,
    'WP_AKIMBO_COLT': 34,
    'WP_AKIMBO_LUGER': 35,
    'WP_GPG40': 36,
    'WP_M7': 37,
    'WP_SILENCED_COLT': 38,
    'WP_GARAND_SCOPE': 39,
    'WP_K43_SCOPE': 40,
    'WP_FG42SCOPE': 41,
    'WP_MORTAR_SET': 42,
    'WP_MEDIC_ADRENALINE': 43,
    'WP_AKIMBO_SILENCEDCOLT': 44,
    'WP_AKIMBO_SILENCEDLUGER': 45,
    'WP_MOBILE_MG42_SET': 46,
    'WP_TRIPMINE': 49,
    'WP_BOMB': 48,
    'WP_POISON_SYRINGE': 47,
    'WP_POISON_BOMB': 50,
    'WP_POISON_MINE': 51,
}
source = (root / 'src_2.60/game/nitmod_weapon_paths.c').read_text()
rows = re.findall(r'\{ (WP_\w+), \{ "([^"]+)", ([01]) \} \}', source)
assert len(rows) == len(identities) == 48
assert len({row[0] for row in rows}) == len(rows)
assert {row[0] for row in rows} == set(identities)
for name, filename, alternate in rows:
    reference = original[identities[name]]
    assert (filename, int(alternate)) == (reference['filename'], reference['alternate']), name
assert set(original) - set(identities.values()) == set()
assert {key for key, row in original.items() if row['alternate']} == {39, 40, 41, 46}
print('48 native identities match original filenames and alternate selectors; all original selectable weapon paths covered')
