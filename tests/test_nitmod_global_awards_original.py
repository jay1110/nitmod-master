"""Compare every shared award row to both original ELF tables, read-only."""
from pathlib import Path
import hashlib
import json
import re
import struct

ROOT = Path(__file__).resolve().parents[1]


def read_rows(name, table, count_address):
    binary = ROOT / 'original_nitmod_shared_objects_32bit' / (name + '.mp.i386.so')
    data = binary.read_bytes()
    ph = struct.unpack_from('<I', data, 28)[0]
    size, count = struct.unpack_from('<HH', data, 42)
    segments = [struct.unpack_from('<8I', data, ph + i * size) for i in range(count)]

    def offset(address):
        return next(off + address - va for typ, off, va, _, length, _, _, _ in segments
                    if typ == 1 and va <= address < va + length)

    def string(address):
        start = offset(address)
        return data[start:data.index(b'\0', start)].decode('ascii')

    rows = []
    for i in range(struct.unpack_from('<I', data, offset(count_address))[0]):
        stat, threshold, mask, title, description = struct.unpack_from('<5I', data, offset(table) + i * 20)
        rows.append((stat, threshold, mask, string(title), string(description)))
    return rows, hashlib.sha256(data).hexdigest()


def main():
    header = (ROOT / 'src_2.60/game/nitmod_global_awards.h').read_text()
    actual = [(int(a), int(b), int(c), d, e) for a, b, c, d, e in
              re.findall(r'\{(\d+),(\d+),(\d+),"([^"]*)","([^"]*)"\}', header)]
    evidence = {}
    for name, table, count in [('qagame', 0x2a5700, 0x2a4f60), ('cgame', 0x12ea60, 0x12e2c0)]:
        original, digest = read_rows(name, table, count)
        assert actual == original, name + ': award index/stat/threshold/mask/text mismatch'
        evidence[name] = dict(sha256=digest, rows=len(original), table=hex(table))
    print(json.dumps(evidence, indent=2))
    print('Both original ELF award tables: all 12 rows match shared game/client table: PASS')


if __name__ == '__main__':
    main()
