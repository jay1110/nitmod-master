import importlib.util
import json
from pathlib import Path
import sys

root = Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('messages', root / 'tools/extract_server_messages.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
lines = (root / 'src_2.60/game/nitmod_server_messages.inc').read_text().splitlines()
actual = [json.loads(line.rstrip(',')) for line in lines if line.startswith('"')]
assert actual == module.extract(root)
assert len(actual) == 58
print('58 original SrvMsgs entries match the SHA-pinned ELF')
