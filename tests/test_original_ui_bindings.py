"""Read original ELF binding records, not strings found incidentally elsewhere."""
from pathlib import Path
import re
import struct

root = Path(__file__).resolve().parents[1]
data = (root / 'original_nitmod_shared_objects_32bit/ui.mp.i386.so').read_bytes()
section_offset = struct.unpack_from('<I', data, 32)[0]
section_count = struct.unpack_from('<H', data, 48)[0]
sections = [struct.unpack_from('<10I', data, section_offset + i * 40)
            for i in range(section_count)]

def offset(address):
    return next(s[4] + address - s[3] for s in sections
                if s[1] != 8 and s[3] <= address < s[3] + s[5])

# nm: g_bindings 0x593e0, size 0x7a0; 61 records of eight i386 words.
records = {}
for i in range(61):
    record = struct.unpack_from('<8i', data, offset(0x593e0) + i * 32)
    name = data[offset(record[0]):].split(b'\0', 1)[0].decode('ascii')
    records[name] = record[1:]
assert 'mvactivate' not in records
# Controls_GetConfig/SetConfig use two active keys at record +24/+28.
# Do not treat the extra word as a third binding or infer field semantics
# from the raw initializer values alone.
assert data[offset(0x37690):offset(0x37690)+3] == bytes.fromhex('8b 46 18')
assert data[offset(0x376ad):offset(0x376ad)+3] == bytes.fromhex('8b 46 1c')
# SetDefaults right-hand branch starts at record +8, not +4.
assert data[offset(0x37715):offset(0x37715)+6] == bytes.fromhex('8d 83 d4 4f 00 00')
assert records['+attack2'][:4] == (179, -1, 179, -1)
source = (root / 'src_2.60/ui/ui_shared.c').read_text()
assert re.search(r'\{ "mvactivate",\s*-1,\s*-1,\s*-1,\s*-1,\s*-1,\s*-1\s*\}', source)
print('Original 61 binding records read; compatibility-only mvactivate has no default key.')
