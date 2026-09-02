#!/usr/bin/env python3
"""Index defined ELF32-i386 functions without third-party dependencies.

Addresses are ELF virtual addresses, NOT assumed Ghidra project addresses.
Every row is bound to both the module digest and the function byte digest.
"""
import argparse
import csv
import hashlib
import io
import pathlib
import struct

FIELDS = ['module', 'module_sha256', 'symbol', 'elf_address', 'size',
          'file_offset', 'code_sha256']


def function_symbols(data):
    def region(offset, size):
        if offset < 0 or size < 0 or offset + size > len(data):
            raise ValueError('ELF region outside file')
        return data[offset:offset + size]

    header = region(0, 52)
    if header[:7] != b'\x7fELF\x01\x01\x01':
        raise ValueError('expected little-endian ELF32')
    if struct.unpack_from('<H', header, 18)[0] != 3:
        raise ValueError('expected i386 machine')
    section_offset = struct.unpack_from('<I', header, 32)[0]
    entry_size, count = struct.unpack_from('<HH', header, 46)
    if entry_size != 40 or not count:
        raise ValueError('unsupported section table')
    sections = [struct.unpack('<10I', region(section_offset + i * 40, 40))
                for i in range(count)]
    result = set()
    for section in sections:
        if section[1] not in (2, 11):  # SYMTAB, DYNSYM
            continue
        if section[9] != 16 or section[5] % 16 or section[6] >= count:
            raise ValueError('invalid symbol table')
        strings = sections[section[6]]
        if strings[1] != 3:
            raise ValueError('symbol names must use STRTAB')
        names = region(strings[4], strings[5])
        symbols = region(section[4], section[5])
        for position in range(0, len(symbols), 16):
            name, address, size, info, _, index = struct.unpack_from('<IIIBBH', symbols, position)
            if info & 15 != 2 or index == 0:  # defined STT_FUNC only
                continue
            if index >= count or name >= len(names):
                raise ValueError('invalid function section/name')
            end = names.find(b'\0', name)
            if end < 0:
                raise ValueError('unterminated symbol name')
            target = sections[index]
            if target[1] == 8 or not target[2] & 4:
                continue  # not file-backed executable code
            relative = address - target[3]
            if relative < 0 or relative + size > target[5]:
                raise ValueError('function extends outside its section')
            offset = target[4] + relative
            digest = hashlib.sha256(region(offset, size)).hexdigest()
            result.add((names[name:end].decode('utf-8'), address, size, offset, digest))
    return sorted(result, key=lambda row: (row[1], row[0], row[2:]))


def render(root):
    output = io.StringIO(newline='')
    writer = csv.writer(output, lineterminator='\n')
    writer.writerow(FIELDS)
    manifest = root / 'reference/original_nitmod_i386.sha256'
    for line in manifest.read_text().splitlines():
        if not line or line.startswith('#'):
            continue
        expected, name = line.split()
        if pathlib.Path(name).name != name:
            raise ValueError('module must be a basename')
        data = (root / 'original_nitmod_shared_objects_32bit' / name).read_bytes()
        digest = hashlib.sha256(data).hexdigest()
        if digest != expected:
            raise ValueError('reference checksum mismatch: ' + name)
        for symbol, address, size, offset, code_digest in function_symbols(data):
            writer.writerow((name, digest, symbol, f'0x{address:08x}', size,
                             f'0x{offset:08x}', code_digest))
    return output.getvalue()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=pathlib.Path, default=pathlib.Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    text = render(args.root)
    destination = args.root / 'reference/original_function_symbols.csv'
    destination.write_text(text, encoding='utf-8', newline='')
    print(f'wrote {len(text.splitlines()) - 1} function symbols to {destination}')


if __name__ == '__main__':
    main()
