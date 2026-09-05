"""Compare executed native item lookups to hash-pinned original aliases."""
import ast
import importlib.util
import pathlib
import re
import subprocess
import struct
import sys

root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('items', root / 'tools/extract_weapon_items.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
original = {}
for item in module.extract(root):
    original.setdefault(item['id'], item)  # original/native lookup: first match
client = {}
for item in module.extract(root, 'cgame'):
    client.setdefault(item['id'], item)
# These files have just passed the extractor's module-specific hash checks.
# Pin the factor used by the inspected PM_BeginWeaponReload x87 instructions.
for name, address in [('qagame', 0x22ee68), ('cgame', 0x1000ec)]:
    data = (root / ('original_nitmod_shared_objects_32bit/' + name + '.mp.i386.so')).read_bytes()
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    sections = [struct.unpack_from('<10I', data, start + i * size) for i in range(count)]
    section = next(s for s in sections if s[1] != 8 and s[3] <= address and address + 4 <= s[3] + s[5])
    factor = struct.unpack_from('<I', data, section[4] + address - section[3])[0]
    assert factor == 0x3f266666
    # Both compiler-generated drop dispatch tables: animation-suppressed
    # non-alternate path and normal/alternate path. A matching alternate
    # reaches the latter even when its first-person animation is suppressed.
    got, first, second, default, normal, fast = {
        'qagame': (0x2a4614, -0x76364, -0x762e0, 0x2a3c0, 0x2a492, 0x2a5fd),
        'cgame': (0x12dc44, -0x2e654, -0x2e5d0, 0x198a0, 0x19972, 0x19add),
    }[name]
    def signed_word(address):
        section = next(s for s in sections if s[1] != 8 and s[3] <= address and address + 4 <= s[3] + s[5])
        return struct.unpack_from('<i', data, section[4] + address - section[3])[0]
    for weapon_id in (24, 30, 31, 39, 40, 41):
        assert got + signed_word(got + first + (weapon_id - 14) * 4) == default
        assert got + signed_word(got + second + weapon_id * 4) == (fast if weapon_id in (31, 41) else normal)
    # Reviewed deployment raise immediates (not native enum-indexed data).
    deploy_immediates = {
        'qagame': ((0x2c2c6, 1250), (0x2c669, 1722), (0x2c976, 1667), (0x2c939, 1000)),
        'cgame': ((0x1b7a6, 1250), (0x1bb2a, 1722), (0x1be36, 1667), (0x1bdf9, 1000)),
    }[name]
    for immediate, milliseconds in deploy_immediates:
        assert signed_word(immediate) == milliseconds
    body_table, body_call, body_skip = {
        'qagame': (0x22e128, 0x28820, 0x28862),
        'cgame': (0xff468, 0x17d30, 0x17d72),
    }[name]
    for weapon_id in range(4, 51):
        destination = got + signed_word(body_table + (weapon_id - 4) * 4)
        assert destination == (body_skip if weapon_id in (4, 9, 15, 28, 48, 49, 50) else body_call)
tree = ast.parse((root / 'tests/test_weapon_paths_reference.py').read_text())
identities = next(ast.literal_eval(node.value) for node in tree.body
                  if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == 'identities' for t in node.targets))
inverse = {value: key for key, value in identities.items()}
inverse[0] = 'WP_NONE'
header = (root / 'src_2.60/game/bg_public.h').read_text()
enum = re.split(r'^\s*WP_NUM_WEAPONS\b', header.split('WP_NONE,', 1)[1], maxsplit=1, flags=re.M)[0]
names = ['WP_NONE'] + re.findall(r'^\s*(WP_\w+|VERYBIGEXPLOSION)\s*,', enum, re.M)
assert len(names) == 54
native = {}
ammo_spec = importlib.util.spec_from_file_location('ammo_defaults', root / 'tools/extract_weapon_ammo.py')
ammo_module = importlib.util.module_from_spec(ammo_spec)
ammo_spec.loader.exec_module(ammo_module)
server_ammo = ammo_module.extract(root)
client_ammo = ammo_module.extract(root, 'cgame')
recovered = {}
switch_spec = importlib.util.spec_from_file_location('weapon_switch', root / 'tools/extract_weapon_switch.py')
switch_module = importlib.util.module_from_spec(switch_spec)
switch_spec.loader.exec_module(switch_module)
server_alts = switch_module.extract(root)
client_alts = switch_module.extract(root, 'cgame')
assert server_alts == client_alts
for line in subprocess.check_output([sys.argv[2]], text=True).splitlines():
    weapon, ammo, clip, supported, own_ammo, own_clip, reload_eligible, reload_flag, alternate = map(int, line.split())
    original_id = identities.get(names[weapon])
    if original_id is not None:
        assert names[alternate] == inverse[server_alts[original_id]], names[weapon]
        assert reload_flag == server_ammo[original_id]['requiresAutoReloadSetting']
        assert reload_flag == client_ammo[original_id]['requiresAutoReloadSetting']
    else:
        assert reload_flag == -19
    # Original unsigned range tests: (id - 22 <= 29) || (id - 1 <= 14).
    assert reload_eligible == int(original_id is not None and
                                  (1 <= original_id <= 15 or 22 <= original_id <= 51))
    assert weapon not in native and 0 <= ammo < len(names) and 0 <= clip < len(names)
    native[weapon] = (names[ammo], names[clip])
    assert supported in (0, 1)
    if supported:
        assert 0 < own_ammo < len(names) and 0 < own_clip < len(names)
        recovered[names[weapon]] = (names[own_ammo], names[own_clip])
    else:
        assert (own_ammo, own_clip) == (-7, -9)
assert set(native) == set(range(len(names)))
assert set(recovered) == set(identities)
differences = {}
for name, weapon in identities.items():
    row = original[weapon]
    expected = (inverse[row['ammo']], inverse[row['clip']])
    assert (row['ammo'], row['clip']) == (client[weapon]['ammo'], client[weapon]['clip']), name
    assert recovered[name] == expected, name
    actual = native[names.index(name)]
    if actual != expected:
        differences[name] = (expected, actual)
assert differences == {}, differences
print('48 alias pairs match, including independent adrenaline inventory')
print('48 recovered alias pairs match both original modules; unsupported identities reject unchanged')
seen = set()
for line in subprocess.check_output([sys.argv[2], '--switch-times'], text=True).splitlines():
    old, new, supported, duration = map(int, line.split())
    assert (old, new) not in seen
    seen.add((old, new))
    original_old = identities.get(names[old])
    original_new = identities.get(names[new])
    paired = original_old in (24, 30, 31, 39, 40, 41) and server_alts[original_old] == original_new
    assert supported == int(paired)
    expected_duration = (50 if original_old in (31, 41) else 250) if paired else -19
    assert duration == expected_duration
assert seen == {(a, b) for a in range(len(names)) for b in range(len(names))}
print('48 native alternate entries match both originals; 2916 executed scope timing lookups checked')
