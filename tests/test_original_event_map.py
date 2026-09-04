"""Verify all original wire IDs 1..93 against the unmodified ELF tables."""
from pathlib import Path
import re
import struct

root = Path(__file__).resolve().parents[1]
elf = (root / 'original_nitmod_shared_objects_32bit/cgame.mp.i386.so').read_bytes()
source = (root / 'src_2.60/cgame/cg_nitmod_eventmap.h').read_text()
rows = re.findall(r'^X\((\d+), (\w+), ([\w-]+)\)', source, re.M)
assert [int(row[0]) for row in rows] == list(range(1, 94))
for text_id, name, handler in rows:
    event = int(text_id)
    ptr, = struct.unpack_from('<I', elf, 0x1346c0 + event * 4)
    original_name = elf[ptr:elf.index(b'\0', ptr)].decode('ascii')
    jump, = struct.unpack_from('<i', elf, 0x105370 + event * 4)
    assert name == original_name, (event, name, original_name)
    reserved = jump + 0x12dc44 == 0x644eb
    assert reserved == (2 <= event <= 8), event
    expected = '-1' if reserved else 'NITMOD_EVENT_DEATH4' if event == 55 else 'EV_STEP_4' if event == 11 else name
    assert handler == expected, (event, handler, expected)
for event, name in {94: 'EV_BODY_DP', 95: 'EV_THROWKNIFE', 97: 'EV_WEAPALT', 100: 'EV_SOUND',
                    102: 'EV_SLAP', 103: 'EV_SOUND_GLOBAL'}.items():
    ptr, = struct.unpack_from('<I', elf, 0x1346c0 + event * 4)
    assert elf[ptr:elf.index(b'\0', ptr)].decode('ascii') == name
extended = (root / 'src_2.60/cgame/cg_nitmod_events.c').read_text()
assert 'case 94:' in extended
assert 'cg_entities[es->otherEntityNum].pe' in extended
assert 'sizeof(cg_entities[es->otherEntityNum].pe)' in extended
assert 'es->otherEntityNum < MAX_GENTITIES' in extended
print('93 original dispatch entries and six extended event IDs verified; 7 reserved IDs.')
