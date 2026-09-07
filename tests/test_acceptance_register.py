"""Acceptance-register integrity: no lost identities or fabricated passes."""
import importlib.util
from pathlib import Path

root=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('acceptance',root/'tools/nitmod_acceptance.py')
module=importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
rows,symbols,inventory=module.census()
ids={r['id'] for r in rows}
assert len(ids)==len(rows)
for s in symbols:
    expected=f"{s['module'].split('.')[0]}:elf:{s['elf_address']}:{s['symbol']}"
    assert expected in ids, expected
for r in inventory:
    reference=f"src_nitmod_decompiled/{r['component']}/sorted/{r['source_file']}#{r['function']}"
    assert any(reference in x['decompile_candidates'].split(';') for x in rows), reference
assert all(r['acceptance_status']=='NOT_ACCEPTED' for r in rows)
assert all(r['actual_result']=='NOT_RUN' for r in rows)
assert module.census()[0]==rows, 'Census must be deterministic'
print(f'PASS: {len(symbols)} ELF rows and all legacy identities preserved; no inferred passes.')
