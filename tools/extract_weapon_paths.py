"""Decode the hash-pinned i386 BG_RegisterWeapon jump table and case operands.
No disassembler dependency: accept only the verified xor/mov edi and lea ebp
case operands. Unknown operand shapes fail closed. Loader control flow was
checked separately against disassembly, not emulated by this extractor.
Addresses below are ELF virtual addresses, not Ghidra rebased addresses.
"""
import hashlib
import json
import pathlib
import struct

ROOT = pathlib.Path(__file__).resolve().parents[1]


def extract(root=ROOT):
    data = (root / 'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
    if hashlib.sha256(data).hexdigest() != '84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49':
        raise ValueError('original qagame hash mismatch')
    if data[:7] != b'\x7fELF\x01\x01\x01':
        raise ValueError('expected little-endian ELF32')
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    if size != 40:
        raise ValueError('unexpected section header size')
    sections = [struct.unpack_from('<10I', data, start + i * size) for i in range(count)]

    def mapped(address, length):
        for section in sections:
            if section[1] != 8 and section[3] <= address and address + length <= section[3] + section[5]:
                offset = section[4] + address - section[3]
                return data[offset:offset + length]
        raise ValueError('unmapped original address')

    # call/pop thunk return 0x363d8 plus the EBX add immediate.
    if mapped(0x363d8, 2) != b'\x81\xc3':
        raise ValueError('unexpected GOT base instruction')
    base = 0x363d8 + struct.unpack('<I', mapped(0x363da, 4))[0]
    if mapped(0x36492, 3) != b'\x8b\x84\xb3':
        raise ValueError('unexpected jump table instruction')
    table = base + struct.unpack('<i', mapped(0x36495, 4))[0]
    result = {}
    for weapon in range(52):
        case = base + struct.unpack('<i', mapped(table + weapon * 4, 4))[0]
        if case == 0x36403:  # no definition / return
            continue
        address = case
        if mapped(address, 2) == b'\x31\xff':
            alternate, address = 0, address + 2
        elif mapped(address, 5) == b'\xbf\x01\x00\x00\x00':
            alternate, address = 1, address + 5
        else:
            raise ValueError('unexpected alternate flag instruction')
        if mapped(address, 2) != b'\x8d\xab':
            raise ValueError('unexpected filename instruction')
        filename_address = base + struct.unpack('<i', mapped(address + 2, 4))[0]
        filename = bytearray()
        for i in range(128):
            value = mapped(filename_address + i, 1)
            if value == b'\0':
                break
            filename.extend(value)
        else:
            raise ValueError('unterminated filename')
        result[weapon] = dict(case=case, filename=filename.decode('ascii'), alternate=alternate)
    return result


if __name__ == '__main__':
    print(json.dumps(extract(), indent=2))
