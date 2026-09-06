"""Read the pinned original qagame grenade class map and seven skill rows."""
import hashlib
import json
import pathlib
import struct

ROOT = pathlib.Path(__file__).resolve().parents[1]

def extract(module='qagame'):
    base, digest = {
        'qagame': (0x2a5160, '84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49'),
        'cgame': (0x12e4c0, '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f'),
    }[module]
    data = (ROOT / ('original_nitmod_shared_objects_32bit/'+module+'.mp.i386.so')).read_bytes()
    assert hashlib.sha256(data).hexdigest() == digest
    assert data[:7] == b'\x7fELF\x01\x01\x01'
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    assert size == 40
    def read(address, fmt):
        length = struct.calcsize(fmt)
        for index in range(count):
            section = struct.unpack_from('<10I', data, start + index * size)
            if section[1] != 8 and section[3] <= address and address + length <= section[3] + section[5]:
                return struct.unpack_from(fmt, data, section[4] + address - section[3])
        raise ValueError('unmapped address')
    result = {'skillRows': [read(base + i * 24, '<6f') for i in range(7)]}
    if module == 'qagame':
        result['classSkills'] = [5, *read(0x22df90, '<4i')]
    return result

if __name__ == '__main__':
    server, client = extract(), extract('cgame')
    assert server['skillRows'] == client['skillRows']
    print(json.dumps(server, indent=2))
    print('Pinned cgame/qagame grenade tables match')
