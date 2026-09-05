"""Read original qagame ammoTableMP's verified ten-int prefix, ELF32.

The full record is 72 bytes, NOT sizeof(native ammotable_t). Only the first
40 bytes, damage/splash/radius at +40/+44/+48, and the independently
verified auto-reload flag at +56 are decoded. Other fields differ.
"""
import hashlib
import json
import pathlib
import struct

ROOT = pathlib.Path(__file__).resolve().parents[1]
FIELDS = ('maxammo', 'uses', 'maxclip', 'defaultStartingAmmo',
          'defaultStartingClip', 'reloadTime', 'fireDelayTime',
          'nextShotTime', 'maxHeat', 'coolRate')


def extract(root=ROOT, module='qagame'):
    references = {
        'qagame': (0x2a69a0, '84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49'),
        'cgame': (0x12fd00, '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f'),
    }
    base, digest = references[module]
    data = (root / ('original_nitmod_shared_objects_32bit/' + module + '.mp.i386.so')).read_bytes()
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
        if section[1] != 8 and section[3] <= base and base + 0xea0 <= section[3] + section[5]:
            offset = section[4] + base - section[3]
            result = {i: dict(zip(FIELDS, struct.unpack_from('<10i', data, offset + i * 72)))
                      for i in range(52)}
            for i, row in result.items():
                row.update(zip(('damage', 'splashDamage', 'splashRadius'),
                               struct.unpack_from('<3i', data, offset + i * 72 + 40)))
                row['requiresAutoReloadSetting'] = struct.unpack_from('<i', data, offset + i * 72 + 56)[0]
            return result
    raise ValueError('unmapped ammo table')


if __name__ == '__main__':
    print(json.dumps(extract(), indent=2))
