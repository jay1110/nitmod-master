#!/usr/bin/env python3
"""Read the 7x5 reward table from the hash-pinned original cgame ELF."""
import hashlib
import json
import pathlib
import struct

ROOT = pathlib.Path(__file__).resolve().parents[1]
ADDRESS = 0x138A00  # cg_skillRewards, ELF SYMTAB: 140 bytes


def extract(root=ROOT):
    data = (root / 'original_nitmod_shared_objects_32bit/cgame.mp.i386.so').read_bytes()
    expected = '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f'
    if hashlib.sha256(data).hexdigest() != expected:
        raise ValueError('cgame reference hash mismatch')
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
        raise ValueError(f'unmapped address {address:x}')

    rewards = []
    for pointer in struct.unpack('<35I', mapped(ADDRESS, 140)):
        value = bytearray()
        for offset in range(1024):
            byte = mapped(pointer + offset, 1)
            if byte == b'\0':
                break
            value.extend(byte)
        else:
            raise ValueError('unterminated reward')
        rewards.append(value.decode('ascii'))
    return [rewards[i:i + 5] for i in range(0, 35, 5)]


if __name__ == '__main__':
    print(json.dumps(extract(), indent=2))
