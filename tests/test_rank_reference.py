"""Compare compiled numeric ranks against the pinned original ELF data table.

The ten-entry consumption boundary comes from disassembly, not symbol size.
This test does not execute original game code or prove gameplay parity.
"""
import hashlib
import pathlib
import struct
import subprocess
import sys

root = pathlib.Path(sys.argv[1]).resolve()
data = (root / 'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
assert hashlib.sha256(data).hexdigest() == '84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49'
assert data[:7] == b'\x7fELF\x01\x01\x01'
start = struct.unpack_from('<I', data, 32)[0]
size, count = struct.unpack_from('<HH', data, 46)
assert size == 40
address = 0x2AB360
tables = []
for index in range(count):
    section = struct.unpack_from('<10I', data, start + index * size)
    if section[1] != 8 and section[3] <= address and address + 44 <= section[3] + section[5]:
        offset = section[4] + address - section[3]
        tables.append(struct.unpack_from('<11i', data, offset))
assert len(tables) == 1
table = tables[0]
assert table == (1, 2, 3, 4, 5, 7, 9, 11, 14, 17, 20)
actual = [int(line) for line in subprocess.check_output([sys.argv[2]], text=True).splitlines()]
assert actual == [sum(total >= threshold for threshold in table[:10]) for total in range(36)]
