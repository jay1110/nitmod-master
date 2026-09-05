"""Compare all 480 ported ammo/timing/uses values with original bytes."""
import importlib.util
import pathlib
import re
import sys
root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('ammo', root / 'tools/extract_weapon_ammo.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
original = module.extract(root)
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
fields = ["maxammo","uses","maxclip","defaultStartingAmmo","defaultStartingClip","reloadTime","fireDelayTime","nextShotTime","maxHeat","coolRate"]
source = (root / 'src_2.60/game/nitmod_weapon_defaults.c').read_text()
rows = re.findall(r'\{ (WP_\w+), ([0-9, -]+) \}', source)
assert len(rows) == len(identities) == 48
assert {row[0] for row in rows} == set(identities)
for name, numbers in rows:
    values = [int(value.strip()) for value in numbers.split(',')]
    assert values == [original[identities[name]][field] for field in fields], name
assert 'ammo->uses = entry->uses;' in source and 'ammo->mod =' not in source
print('480 original ammo/timing/uses defaults match for 48 native identities')
blast_rows = re.findall(r'\{(WP_\w+), (\d+), (\d+), (\d+)\}', source)
assert len(blast_rows) == 15
for name, damage, splash, radius in blast_rows:
    row = original[identities[name]]
    assert [int(damage), int(splash), int(radius)] == [row[k] for k in ('damage','splashDamage','splashRadius')], name
print('45 original blast defaults match for 15 native identities')
