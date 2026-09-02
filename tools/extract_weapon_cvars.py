"""Hash-pinned original qagame registration records for weapon policy.

gameCvarTable: ELF 0x2a7e20, 0x2514 bytes, 339 records of 28 bytes.
G_RegisterCvars passes fields 0..3 to trap_Cvar_Register.
"""
import hashlib
import json
import pathlib
import struct

ROOT = pathlib.Path(__file__).resolve().parents[1]
NAMES = ('g_war', 'g_pickAnyWeapon', 'g_weapons', 'g_heavyWeaponRestriction',
         'sv_maxclients', 'team_panzerRestriction', 'team_maxPanzers',
         'team_maxFlamers', 'team_maxMG42s', 'team_maxMortars', 'team_maxriflegrenades')


def extract(root=ROOT, names=NAMES):
    data = (root / 'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
    if hashlib.sha256(data).hexdigest() != '84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49':
        raise ValueError('original qagame hash mismatch')
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    if data[:7] != b'\x7fELF\x01\x01\x01' or size != 40:
        raise ValueError('expected ELF32 section table')
    sections = [struct.unpack_from('<10I', data, start + i * size) for i in range(count)]

    def mapped(address, length):
        for section in sections:
            if section[1] != 8 and section[3] <= address and address + length <= section[3] + section[5]:
                offset = section[4] + address - section[3]
                return data[offset:offset + length]
        raise ValueError('unmapped original address')

    def string(address):
        result = bytearray()
        for offset in range(1024):
            value = mapped(address + offset, 1)
            if value == b'\0':
                return result.decode('ascii')
            result.extend(value)
        raise ValueError('unterminated string')

    result = {}
    for index in range(339):
        address = 0x2a7e20 + 28 * index
        row = struct.unpack('<7I', mapped(address, 28))
        name = string(row[1])
        if name in names:
            if name in result:
                raise ValueError('duplicate weapon Cvar')
            result[name] = dict(address=address, vm_address=row[0], default=string(row[2]),
                                flags=row[3], modification_count=row[4],
                                track_change=row[5], reset=row[6])
    if set(result) != set(names):
        raise ValueError('missing weapon Cvar')
    return result


if __name__ == '__main__':
    print(json.dumps(extract(), indent=2))
