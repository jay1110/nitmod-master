"""Original cgame SrvMsgs table, hash-pinned ELF virtual-address mapping."""
import hashlib
from pathlib import Path
import struct
import json

ROOT = Path(__file__).resolve().parents[1]

def extract(root=ROOT):
    data = (root / 'original_nitmod_shared_objects_32bit/cgame.mp.i386.so').read_bytes()
    if hashlib.sha256(data).hexdigest() != '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f':
        raise ValueError('original cgame hash mismatch')
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    sections = [struct.unpack_from('<10I', data, start + size*i) for i in range(count)]
    def mapped(address, length):
        for s in sections:
            if s[1] != 8 and s[3] <= address and address + length <= s[3] + s[5]:
                offset = s[4] + address - s[3]
                return data[offset:offset+length]
        raise ValueError('unmapped address')
    result = []
    for index in range(58):
        address = struct.unpack('<I', mapped(0x138ac0 + 4*index, 4))[0]
        if not address:
            result.append(None)
            continue
        text = bytearray()
        for j in range(4096):
            value = mapped(address+j, 1)
            if value == b'\0': break
            text.extend(value)
        else: raise ValueError('unterminated message')
        result.append(text.decode('ascii'))
    return result

if __name__ == '__main__':
    print(json.dumps(extract(), indent=2))
