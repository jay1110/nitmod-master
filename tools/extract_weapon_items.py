"""Read original weapon identities; IDs are NOT the native ET weapon enum.

BG_InitWeaponStrings confirms 56-byte items, type +36, tag +40,
pickup-name pointer +28. Original bg_itemlist symbol: 0x2a59a0, 4088 bytes.
"""
import hashlib
import json
import pathlib
import struct

ROOT = pathlib.Path(__file__).resolve().parents[1]


def extract(root=ROOT, module='qagame'):
    references = {
        'qagame': (0x2a59a0, '84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49'),
        'cgame': (0x12ed00, '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f'),
    }
    base, digest = references[module]
    data = (root / ('original_nitmod_shared_objects_32bit/' + module + '.mp.i386.so')).read_bytes()
    if hashlib.sha256(data).hexdigest() != digest:
        raise ValueError('original ' + module + ' hash mismatch')
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

    def string(address):
        if not address:
            return ''
        result = bytearray()
        for offset in range(1024):
            value = mapped(address + offset, 1)
            if value == b'\0':
                return result.decode('ascii')
            result.extend(value)
        raise ValueError('unterminated item string')

    result = []
    for index in range(1, 4088 // 56):
        item = struct.unpack('<14I', mapped(base + index * 56, 56))
        if not item[0]:
            break
        if item[9] == 1:
            result.append({'id': item[10], 'classname': string(item[0]), 'name': string(item[7]),
                           'ammo': item[12], 'clip': item[13], 'address': base + index * 56})
    return result


if __name__ == '__main__':
    print(json.dumps(extract(), indent=2))
