"""Decode the original 52-entry alternate-weapon tables, not native enums."""
import hashlib
import json
import pathlib
import struct

ROOT = pathlib.Path(__file__).resolve().parents[1]
REFERENCES = {
    'qagame': (0x2a5300, '84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49'),
    'cgame': (0x12e660, '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f'),
}


def extract(root=ROOT, module='qagame'):
    address, digest = REFERENCES[module]
    data = (root / 'original_nitmod_shared_objects_32bit' / (module + '.mp.i386.so')).read_bytes()
    if hashlib.sha256(data).hexdigest() != digest:
        raise ValueError('original ' + module + ' hash mismatch')
    if data[:7] != b'\x7fELF\x01\x01\x01':
        raise ValueError('expected ELF32 little endian')
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    if size != 40:
        raise ValueError('unexpected section header size')
    for index in range(count):
        section = struct.unpack_from('<10I', data, start + index * size)
        if section[1] != 8 and section[3] <= address and address + 208 <= section[3] + section[5]:
            values = struct.unpack_from('<52i', data, section[4] + address - section[3])
            if any(value < 0 or value >= 52 for value in values):
                raise ValueError('out-of-range original alternate')
            return dict(enumerate(values))
    raise ValueError('unmapped alternate table')


if __name__ == '__main__':
    print(json.dumps({module: extract(module=module) for module in REFERENCES}, indent=2))
