"""Reproduce original function index and pin independently disassembled facts."""
import csv
import importlib.util
import io
import pathlib
import sys

root = pathlib.Path(sys.argv[1]).resolve()
sys.dont_write_bytecode = True
spec = importlib.util.spec_from_file_location('reference_symbols', root / 'tools/build_reference_symbols.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
actual = module.render(root)
assert actual == (root / 'reference/original_function_symbols.csv').read_text(encoding='utf-8')
rows = list(csv.DictReader(io.StringIO(actual)))
assert {r['module'] for r in rows} == {'cgame.mp.i386.so', 'qagame.mp.i386.so', 'ui.mp.i386.so'}
data = (root / 'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
for name, address, size in [('G_SweepForLandmines', '0x0008dbe0', 316),
                            ('G_ExplodeSatchels', '0x0008dd80', 232)]:
    match = [r for r in rows if r['module'] == 'qagame.mp.i386.so' and r['symbol'] == name]
    assert len(match) == 1
    row = match[0]
    assert row['elf_address'] == address and int(row['size']) == size
    if name == 'G_SweepForLandmines':
        start = int(row['file_offset'], 16)
        # Independently confirmed with objdump: xor eax,eax; pop ebx; pop esi; ret.
        assert data[start + size - 5:start + size] == bytes.fromhex('31 c0 5b 5e c3')
for malformed in [b'', data[:51], data[:100], b'NOTELF' + data[6:]]:
    try:
        module.function_symbols(malformed)
    except ValueError:
        pass
    else:
        raise AssertionError('malformed ELF accepted')
