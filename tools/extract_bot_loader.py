"""Recover the loader contract from hash-pinned ELF operands; never load code."""
import hashlib
import json
import pathlib
import struct
import argparse

ROOT = pathlib.Path(__file__).resolve().parents[1]
EXPECTED_SHA256 = '84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49'

def extract(root=ROOT):
    data = (pathlib.Path(root) / 'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
    if hashlib.sha256(data).hexdigest() != EXPECTED_SHA256:
        raise ValueError('original qagame hash mismatch')
    if data[:7] != b'\x7fELF\x01\x01\x01':
        raise ValueError('expected little-endian ELF32')
    start = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    if size != 40:
        raise ValueError('unexpected section entry size')
    sections = [struct.unpack_from('<10I', data, start + i * size) for i in range(count)]
    def mapped(address, length):
        for section in sections:
            if section[1] != 8 and section[3] <= address and address + length <= section[3] + section[5]:
                offset = section[4] + address - section[3]
                return data[offset:offset + length]
        raise ValueError('unmapped address')
    def check(address, expected):
        if mapped(address, len(expected)) != expected:
            raise ValueError('unexpected instruction at %#x' % address)
    def string(address):
        value = bytearray()
        for i in range(256):
            char = mapped(address + i, 1)
            if char == b'\0':
                return value.decode('ascii')
            value.extend(char)
        raise ValueError('unterminated loader string')
    def lea_string(address, base):
        check(address, b'\x8d\x83')
        return string(base + struct.unpack('<i', mapped(address + 2, 4))[0])
    check(0x21f436, b'\x81\xc3')
    init_base = 0x21f436 + struct.unpack('<I', mapped(0x21f438, 4))[0]
    check(0x22a0a0, b'\x81\xc3')
    loader_base = 0x22a0a0 + struct.unpack('<I', mapped(0x22a0a2, 4))[0]
    check(0x21f485, b'\xc7\x04\x24')
    version = struct.unpack('<I', mapped(0x21f488, 4))[0]
    check(0x22a14a, b'\xba')
    table_bytes = struct.unpack('<I', mapped(0x22a14b, 4))[0]
    check(0x22a156, b'\xff\xd0')  # export(table, byte count)
    check(0x22a17d, b'\xff\x16')  # first table member(engine interface, version)
    check(0x22a187, b'\x0f\x94\x02')  # loaded flag iff init returns zero
    # Vtable words in the file are zero: resolve R_386_32 relocations, not
    # raw table contents. Retain mangled symbols, which do not prove returns.
    dynsym = next(section for section in sections if section[1] == 11)
    names_section = sections[dynsym[6]]
    names = data[names_section[4]:names_section[4] + names_section[5]]
    if dynsym[9] != 16:
        raise ValueError('unexpected dynamic symbol size')
    symbols = []
    for offset in range(dynsym[4], dynsym[4] + dynsym[5], 16):
        name, address, length, info, other, section_index = struct.unpack_from('<IIIBBH', data, offset)
        symbols.append(dict(name=names[name:names.index(b'\0', name)].decode('ascii'),
                            address=address, size=length, kind=info & 15, section=section_index))
    table = [symbol for symbol in symbols if symbol['name'] == '_ZTV11ETInterface']
    if len(table) != 1 or table[0]['size'] != 0xe4:
        raise ValueError('unexpected ETInterface vtable')
    table = table[0]
    begin, end = table['address'] + 8, table['address'] + table['size']
    slots = {}
    for section in sections:
        if section[1] != 9:  # SHT_REL
            continue
        if section[9] != 8 or sections[section[6]] != dynsym:
            raise ValueError('unexpected relocation table')
        for offset in range(section[4], section[4] + section[5], 8):
            address, info = struct.unpack_from('<II', data, offset)
            if not begin <= address < end:
                continue
            if info & 255 != 1 or (address - begin) % 4:
                raise ValueError('unsupported vtable relocation')
            symbol = symbols[info >> 8]
            if symbol['kind'] != 2 or not symbol['section'] or not symbol['size']:
                raise ValueError('vtable target is not a defined function')
            if mapped(address, 4) != b'\0' * 4:
                raise ValueError('unexpected vtable addend')
            slot = (address - begin) // 4
            if slot in slots:
                raise ValueError('duplicate vtable slot')
            slots[slot] = dict(slot=slot, symbol=symbol['name'], elf_address=symbol['address'],
                               code_sha256=hashlib.sha256(mapped(symbol['address'], symbol['size'])).hexdigest())
    if set(slots) != set(range(55)):
        raise ValueError('incomplete vtable relocations')
    return dict(schema_version=2, original_sha256=EXPECTED_SHA256,
                engine_vtable=[slots[index] for index in range(55)],
                version=version, table_bytes_i386=table_bytes,
                library_basename=lea_string(0x21f490, init_base),
                export_symbol=lea_string(0x22a132, loader_base),
                path_format=lea_string(0x22a0c2, loader_base),
                bare_format=lea_string(0x22a1f8, loader_base),
                home_format=lea_string(0x22a236, loader_base),
                init_success_code=0, runtime_compatible=False)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=pathlib.Path)
    args = parser.parse_args()
    report = json.dumps(extract(), indent=2) + '\n'
    if args.output:
        args.output.write_text(report, encoding='utf-8')
        print('wrote ' + str(args.output))
    else:
        print(report, end='')
