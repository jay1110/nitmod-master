"""Pin original identities that must not be copied as native weapon IDs."""
import importlib.util
import pathlib
import sys
import re
import struct

root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('weapon_items', root / 'tools/extract_weapon_items.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
items = module.extract(root)
by_name = {item['name']: item['id'] for item in items}
assert len(items) == 53
assert by_name['Adrenaline Syringe'] == 43
assert by_name['Binoculars'] == 19
assert by_name['Satchel Charge Detonator'] == 27
assert by_name['Mobile MG42'] == 29
assert by_name['Mobile MG42 Bipod'] == 46
assert by_name['Poison Syringe'] == 47
assert by_name['Bomb'] == 48
assert by_name['Tripmine'] == 49
assert by_name['Poison Bomb'] == 50
assert by_name['Poison Landmine'] == 51
assert [item['id'] for item in items if item['classname'] == 'weapon_landmine'] == [25, 51]

# The client animation parser indexes its first item match by ORIGINAL ID.
# Verify both binaries, not just the server's pickup names.
client_items = module.extract(root, 'cgame')
identity = lambda row: (row['id'], row['classname'], row['name'], row['ammo'], row['clip'])
assert list(map(identity, client_items)) == list(map(identity, items))
first = {}
for row in items:
    first.setdefault(row['id'], row)
assert all(0 <= weapon < 52 for weapon in first)
names = {row['name'].lower() for row in first.values()}

# BG_InitWeaponStrings: clear 52 eight-byte entries and iterate 52 IDs.
for binary, address in [('cgame', 0xbd00), ('qagame', 0x1c7c0)]:
    data = (root / 'original_nitmod_shared_objects_32bit' / (binary + '.mp.i386.so')).read_bytes()
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    sections = [struct.unpack_from('<10I', data, start + index * size) for index in range(count)]
    section = next(s for s in sections if s[1] != 8 and s[3] <= address < s[3] + s[5])
    offset = section[4] + address - section[3]
    assert data[offset + 0x29:offset + 0x2e] == bytes.fromhex('3d a0010000')
    assert data[offset + 0x10c:offset + 0x10f] == bytes.fromhex('83 fa34')

# Read-only audit of union operands in the actual original asset. This is not
# a replacement animation parser: only this script's weapon union grammar.
definitions = set()
checked = 0
for number, line in enumerate((root / 'pak/animations/scripts/human_base.script').read_text().splitlines(), 1):
    line = line.split('//', 1)[0]
    definition = re.match(r'\s*set weapons (\w+)\s*=\s*(.*)', line)
    condition = re.match(r'\s*weapons\s+([^,]+)', line)
    if not definition and not condition:
        continue
    expression = definition[2] if definition else condition[1]
    for operand in re.split(r'\s+AND\s+', expression, flags=re.I):
        operand = operand.strip().lower()
        assert operand in names or operand in definitions or operand == 'none', (number, operand)
        checked += 1
    if definition:
        definitions.add(definition[1].lower())
assert checked > 100
