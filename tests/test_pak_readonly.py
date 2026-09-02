"""Read-only guard: do not regenerate the baseline to accommodate port edits."""
import hashlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
expected = {}
for line in (ROOT / 'reference/pak-readonly.sha256').read_text().splitlines():
    if not line or line.startswith('#'):
        continue
    digest, path = line.split('  ', 1)
    assert path not in expected, ('duplicate manifest path', path)
    expected[path] = digest
actual = {path.relative_to(ROOT / 'pak').as_posix(): hashlib.sha256(path.read_bytes()).hexdigest()
          for path in (ROOT / 'pak').rglob('*') if path.is_file()}
missing = sorted(expected.keys() - actual.keys())
added = sorted(actual.keys() - expected.keys())
changed = sorted(path for path in expected.keys() & actual.keys() if expected[path] != actual[path])
assert not (missing or added or changed), (
    'pak is read-only for porting; investigate, do not auto-update the manifest',
    {'missing': missing, 'added': added, 'changed': changed})
assert len(expected) == 153
