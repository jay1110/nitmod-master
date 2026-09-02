"""Extract hash-pinned original registration tables; source mentions are NOT parity."""
import csv
import hashlib
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[1]
MODULES = {
    'cgame': ('45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f', 'cvarTable', 20, 200),
    'qagame': ('84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49', 'gameCvarTable', 28, 339),
    'ui': ('886fb9526ed7366261b94949f1a170c17d9d21140780f8bd557bd5540b2b006b', 'cvarTable', 20, 210),
}

def extract(root=ROOT):
    records = []
    for module, (digest, table_name, stride, count) in MODULES.items():
        data = (root / 'original_nitmod_shared_objects_32bit' / (module + '.mp.i386.so')).read_bytes()
        if hashlib.sha256(data).hexdigest() != digest:
            raise ValueError(module + ': reference hash mismatch')
        if data[:7] != b'\x7fELF\x01\x01\x01':
            raise ValueError('expected little-endian ELF32')
        start = struct.unpack_from('<I', data, 32)[0]
        size, nsections = struct.unpack_from('<HH', data, 46)
        if size != 40:
            raise ValueError('unexpected section size')
        sections = [struct.unpack_from('<10I', data, start + i * size) for i in range(nsections)]

        def mapped(address, length):
            for s in sections:
                if s[1] != 8 and s[3] <= address and address + length <= s[3] + s[5]:
                    offset = s[4] + address - s[3]
                    return data[offset:offset + length]
            raise ValueError('unmapped address')

        def string(address):
            result = bytearray()
            for i in range(4096):
                value = mapped(address + i, 1)
                if value == b'\0':
                    return result.decode('ascii')
                result.extend(value)
            raise ValueError('unterminated string')

        symbols = {}
        for section in sections:
            if section[1] != 2:
                continue
            names = sections[section[6]]
            names = data[names[4]:names[4] + names[5]]
            for offset in range(section[4], section[4] + section[5], section[9]):
                name, address, length, _, _, _ = struct.unpack_from('<IIIBBH', data, offset)
                name = names[name:].split(b'\0', 1)[0].decode('ascii')
                symbols[name] = (address, length)
        address, length = symbols[table_name]
        if length != stride * count:
            raise ValueError(module + ': unexpected table size')
        source_dir = root / 'src_2.60' / ('game' if module == 'qagame' else module)
        sources = [(p.relative_to(root).as_posix(), p.read_text(errors='replace'))
                   for p in sorted(source_dir.glob('*.c'))]
        for i in range(count):
            row = struct.unpack('<' + 'I' * (stride // 4), mapped(address + i * stride, stride))
            name = string(row[1])
            pattern = re.compile(r'"' + re.escape(name) + r'"', re.IGNORECASE)
            mentions = [path for path, text in sources if pattern.search(text)]
            records.append(dict(module=module, address=hex(address + i * stride),
                vm_address=hex(row[0]), name=name, default=string(row[2]), flags=row[3],
                modification_count=row[4], track_change=row[5] if stride == 28 else '',
                reset=row[6] if stride == 28 else '', source_mentions=';'.join(mentions),
                status='needs-semantic-audit' if mentions else 'no-literal-source-mention'))
    return records

if __name__ == '__main__':
    records = extract()
    target = ROOT / 'reference/original-cvar-inventory.csv'
    with target.open('w', newline='', encoding='utf-8') as output:
        writer = csv.DictWriter(output, fieldnames=list(records[0]))
        writer.writeheader()
        writer.writerows(records)
    for module in MODULES:
        rows = [r for r in records if r['module'] == module]
        print(module, len(rows), 'records;', sum(not r['source_mentions'] for r in rows), 'without literal source mention')
