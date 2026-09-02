"""Read weapon-limit text from hash-pinned original cgame SrvMsgs."""
import hashlib
import json
import pathlib
import struct

ROOT = pathlib.Path(__file__).resolve().parents[1]


def extract(root=ROOT):
    data = (root / 'original_nitmod_shared_objects_32bit/cgame.mp.i386.so').read_bytes()
    if hashlib.sha256(data).hexdigest() != '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f':
        raise ValueError('original cgame hash mismatch')
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    if data[:7] != b'\x7fELF\x01\x01\x01' or size != 40:
        raise ValueError('expected ELF32 section table')
    sections = [struct.unpack_from('<10I', data, start + i * size) for i in range(count)]

    def mapped(address, length):
        for s in sections:
            if s[1] != 8 and s[3] <= address and address + length <= s[3] + s[5]:
                offset = s[4] + address - s[3]
                return data[offset:offset + length]
        raise ValueError('unmapped original address')

    result = {}
    for reason in range(19, 26):
        pointer = struct.unpack('<I', mapped(0x138ac0 + reason * 4, 4))[0]
        text = bytearray()
        for offset in range(1024):
            value = mapped(pointer + offset, 1)
            if value == b'\0':
                break
            text.extend(value)
        else:
            raise ValueError('unterminated message')
        result[reason] = text.decode('ascii')
    return result


if __name__ == '__main__':
    print(json.dumps(extract(), indent=2))
