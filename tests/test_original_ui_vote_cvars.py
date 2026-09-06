"""Check UI vote defaults against the reference ELF cvar registration table."""
from pathlib import Path
import struct
import re

root = Path(__file__).resolve().parents[1]
b = (root / 'original_nitmod_shared_objects_32bit/ui.mp.i386.so').read_bytes()
shoff = struct.unpack_from('<I', b, 32)[0]
sections = [struct.unpack_from('<10I', b, shoff + i * 40)
            for i in range(struct.unpack_from('<H', b, 48)[0])]
def offset(address):
    s = next(s for s in sections if s[1] != 8 and s[3] <= address < s[3] + s[5])
    return s[4] + address - s[3]
def string(address):
    p = offset(address)
    return b[p:b.index(b'\0', p)].decode()

if __name__ == '__main__':
    source = (root / 'src_2.60/ui/ui_main.c').read_text()
    checked = 0
    for p in range(offset(0x57d40), offset(0x57d40) + 0x1068, 20):
        vm, name, default, flags, count = struct.unpack_from('<5I', b, p)
        name = string(name)
        if name.startswith('vote_allow_'):
            value = string(default)
            assert flags == 1, (name, flags)
            pattern = (r'\{\s*NULL\s*,\s*"' + re.escape(name) +
                       r'"\s*,\s*"' + re.escape(value) +
                       r'"\s*,\s*CVAR_ARCHIVE\s*\}')
            assert re.search(pattern, source), (name, value, flags)
            checked += 1
    assert checked == 18
    print('18 original UI vote cvar rows match names, defaults and archive flags.')
