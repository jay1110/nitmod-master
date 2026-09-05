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
assert {i for i, token in enumerate(wire) if token == '-1'} == set()

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
assert rows[7][:4] == ['WP_LANDMINE', 'WP_POISON_MINE', 'WP_TRIPMINE', 'WP_MEDIC_ADRENALINE']
print('All 10 typed banks match original order including all original poison weapons')

# Original gas sprite style, and the signed 16-bit x87 conversions which make
# its out-of-range red/green values black (masked invalid -> 0x8000 -> low byte 0).
def code(address, length):
    section = next(s for s in sections if s[1] != 8 and s[3] <= address and address + length <= s[3] + s[5])
    return data[section[4] + address - section[3]:section[4] + address - section[3] + length]

assert code(0x54802, 6) == bytes.fromhex('83 e8 32 83 f8 01')
assert code(0x54920, 7) == bytes.fromhex('c7 46 14 00 00 7f 43')  # red 255.f
assert code(0x5492d, 7) == bytes.fromhex('c7 46 18 00 00 34 43')  # green 180.f
assert code(0x5493b, 7) == bytes.fromhex('c7 46 20 00 00 80 3e')  # alpha .25f
assert struct.unpack('<f', code(0x12dc44 - 0x2e8bc, 4))[0] == 7.0
assert struct.unpack('<f', code(0x12dc44 - 0x2e8c4, 4))[0] == 255.0
assert code(0x550ef, 4) == bytes.fromhex('df 5c 24 30')
assert code(0x55104, 4) == bytes.fromhex('df 5c 24 4a')
