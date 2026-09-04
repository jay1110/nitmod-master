"""Compare typed banks with the hash-pinned original cgame data table."""
import hashlib
import pathlib
import re
import struct
import sys

root = pathlib.Path(sys.argv[1]).resolve()
data = (root / 'original_nitmod_shared_objects_32bit/cgame.mp.i386.so').read_bytes()
assert hashlib.sha256(data).hexdigest() == '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f'
assert data[:7] == b'\x7fELF\x01\x01\x01'
start = struct.unpack_from('<I', data, 32)[0]
size, count = struct.unpack_from('<HH', data, 46)
assert size == 40
sections = [struct.unpack_from('<10I', data, start + i * size) for i in range(count)]
address, length = 0x12e7a0, 480  # weapBanksMultiPlayer, llvm-nm -S
section = next(s for s in sections if s[1] != 8 and s[3] <= address and address + length <= s[3] + s[5])
original = struct.unpack_from('<120I', data, section[4] + address - section[3])

source = (root / 'src_2.60/cgame/cg_nitmod_config.c').read_text()
wire = re.search(r'nitmodWireWeapons\[52\]\s*=\s*\{(.*?)\};', source, re.S)[1]
wire = [token.strip() for token in wire.split(',') if token.strip()]
assert len(wire) == 52
assert {i for i, token in enumerate(wire) if token == '-1'} == {47, 48, 50, 51}

source = (root / 'src_2.60/game/bg_misc.c').read_text()
body = re.search(r'int weapBanksMultiPlayer\[[^;]*?=\s*\{(.*?)\n\};', source, re.S)[1]
body = re.sub(r'//[^\n]*', '', body)
rows = [[token.strip() for token in row.split(',') if token.strip()]
        for row in re.findall(r'\{([^{}]*)\}', body)]
assert len(rows) == 10
for bank, row in enumerate(rows):
    expected = [wire[i] for i in original[bank * 12:(bank + 1) * 12] if i and wire[i] != '-1']
    expected += ['0'] * (12 - len(expected))
    assert len(row) == 12 and row == expected, (bank, row, expected)
assert rows[7][:3] == ['WP_LANDMINE', 'WP_TRIPMINE', 'WP_MEDIC_ADRENALINE']
print('All 10 typed banks match original order after excluding four unimplemented weapons')
