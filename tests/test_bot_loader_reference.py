"""Check loader identity/units and fail closed for an altered reference."""
import importlib.util
import pathlib
import sys
import json
import hashlib
import struct
from unittest.mock import patch

root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('bot_loader', root / 'tools/extract_bot_loader.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
result = module.extract(root)
assert result['schema_version'] == 2
slots = result['engine_vtable']
assert len(slots) == 55 and [row['slot'] for row in slots] == list(range(55))
assert slots[0]['symbol'] == '_ZN11ETInterface6AddBotERK13MessageHelper'
assert slots[1]['symbol'] == '_ZN11ETInterface9RemoveBotERK13MessageHelper'
assert slots[-1]['symbol'] == '_ZN11ETInterfaceD0Ev'
assert all(len(row['code_sha256']) == 64 and row['elf_address'] > 0 for row in slots)
assert json.loads((root / 'reference/bot-loader-contract.json').read_text()) == result
assert result['version'] == 17
assert result['table_bytes_i386'] == 44
assert result['library_basename'] == 'omnibot_et'
assert result['export_symbol'] == 'ExportBotFunctionsFromDLL'
assert result['path_format'] == '%s/%s.so'
assert result['bare_format'] == './%s.so'
assert result['home_format'] == '%s/omni-bot/%s.so'
assert result['init_success_code'] == 0
assert result['runtime_compatible'] is False
with patch.object(pathlib.Path, 'read_bytes', return_value=b'not the original'):
    try:
        module.extract(root)
    except ValueError as error:
        assert 'hash mismatch' in str(error)
    else:
        raise AssertionError('altered artifact accepted')
# Deliberately bypass only the fixture digest to exercise relocation rejection.
data = bytearray((root / 'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes())
section_start = struct.unpack_from('<I', data, 32)[0]
section_size, section_count = struct.unpack_from('<HH', data, 46)
changed = False
for i in range(section_count):
    section = struct.unpack_from('<10I', data, section_start + i * section_size)
    if section[1] == 9:
        for offset in range(section[4], section[4] + section[5], 8):
            address, info = struct.unpack_from('<II', data, offset)
            if address == 0x2a4248:
                struct.pack_into('<I', data, offset + 4, (info & ~255) | 2)
                changed = True
assert changed
with patch.object(pathlib.Path, 'read_bytes', return_value=bytes(data)), \
     patch.object(module, 'EXPECTED_SHA256', hashlib.sha256(data).hexdigest()):
    try:
        module.extract(root)
    except ValueError as error:
        assert 'unsupported vtable relocation' in str(error)
    else:
        raise AssertionError('wrong relocation kind accepted')
print('Original Omni-bot loader: version 17, 44-byte table, export/path operands verified')
