"""Reproducible acceptance census. No inferred functional passes, no overwritten runs."""
from __future__ import annotations
import argparse
import csv
import hashlib
import json
import os
import re
import subprocess
import sys
from collections import Counter
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'reference/acceptance'

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def readcsv(path):
    with path.open(encoding='utf-8-sig', newline='') as f:
        return list(csv.DictReader(f))

def writecsv(path, rows):
    with path.open('x', encoding='utf-8-sig', newline='') as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0]))
        w.writeheader(); w.writerows(rows)

def normalized(name):
    return re.sub(r'[^A-Za-z0-9_]', '_', name)

def census():
    symbols = readcsv(ROOT/'reference/original_function_symbols.csv')
    inventory = readcsv(ROOT/'reference/port_inventory.csv')
    unique = {}
    for r in inventory:
        key = (r['component'], r['source_file'], r['function'])
        if key in unique and unique[key] != r:
            raise ValueError(f'Conflicting inventory rows: {key}')
        unique[key] = r
    # Names only reconcile identity candidates, never acceptance status.
    index = {}
    for key, r in unique.items():
        index.setdefault((r['component'], normalized(r['function'])), []).append((key, r))
    rows, used, ids = [], set(), set()
    for s in symbols:
        module = s['module'].split('.')[0]
        identity = f"{module}:elf:{s['elf_address']}:{s['symbol']}"
        if identity in ids: raise ValueError(f'Duplicate ELF identity: {identity}')
        ids.add(identity)
        matches = index.get((module, normalized(s['symbol'])), [])
        used.update(k for k, _ in matches)
        rows.append(row(identity, module, s['symbol'], s, matches))
    for key, r in unique.items():
        if key not in used:
            identity = f"{r['component']}:decompile:{r['source_file']}:{r['function']}"
            rows.append(row(identity, r['component'], r['function'], {}, [(key, r)]))
    return sorted(rows, key=lambda r:r['id']), symbols, inventory

def row(identity, module, name, symbol, matches):
    return dict(id=identity, module=module, original_function=name,
        identity_status=('elf_with_name_candidates' if matches else 'elf_only') if symbol else 'decompile_only_unresolved',
        original_binary=f'original_nitmod_shared_objects_32bit/{module}.mp.i386.so',
        original_binary_sha256=symbol.get('module_sha256',''),
        original_address=symbol.get('elf_address',''), original_size=symbol.get('size',''),
        original_code_sha256=symbol.get('code_sha256',''),
        decompile_candidates=';'.join(f"src_nitmod_decompiled/{module}/sorted/{r['source_file']}#{r['function']}" for _,r in matches),
        legacy_port_status=';'.join(sorted({r['port_status'] for _,r in matches})),
        legacy_target=';'.join(sorted({r['target_module'] for _,r in matches if r['target_module']})),
        legacy_evidence=';'.join(sorted({r['parity_evidence'] for _,r in matches if r['parity_evidence']})),
        legacy_notes=' | '.join(sorted({r['notes'] for _,r in matches if r['notes']})),
        specification_status='NOT_SPECIFIED', expected_behavior='', preconditions='', inputs='',
        expected_outputs='', expected_side_effects='', tolerances='', oracle='',
        case_ids='', actual_result='NOT_RUN', acceptance_status='NOT_ACCEPTED',
        blocker='Originalvertrag und reproduzierbare Verhaltensfälle noch einzeln zu prüfen',
        reviewer='', reviewed_at='')

def main():
    if not __debug__: raise SystemExit('Do not use Python -O: original contracts require assertions')
    parser=argparse.ArgumentParser()
    parser.add_argument('--run',action='store_true',help='Execute explicitly registered contracts')
    args=parser.parse_args()
    rows, symbols, inventory=census()
    cases=json.loads((BASE/'cases.json').read_text(encoding='utf-8'))
    contracts=json.loads((BASE/'contracts.json').read_text(encoding='utf-8'))
    ids={r['id'] for r in rows}
    assert len(ids)==len(rows)
    assert all(i in ids for i in contracts), 'Unknown contract identity'
    allowed={'expected_behavior','preconditions','inputs','expected_outputs',
             'expected_side_effects','tolerances','oracle','case_ids','blocker'}
    for r in rows:
        if r['id'] in contracts:
            assert set(contracts[r['id']]) <= allowed
            r.update(contracts[r['id']])
            r['specification_status']='BOUNDED_CONTRACT_ONLY'
    assert len({c['id'] for c in cases})==len(cases)
    for c in cases:
        assert c['scope']=='bounded_contract', 'Full function acceptance requires separate review'
        assert (ROOT/c['script']).is_file()
        assert all(i in ids for i in c['function_ids'])
    case_ids={c['id'] for c in cases}
    for r in rows:
        assert all(i in case_ids for i in r['case_ids'].split(';') if i)
    # Verify pinned originals before producing any report or running a contract.
    for name in sorted({s['module'] for s in symbols}):
        binary=ROOT/'original_nitmod_shared_objects_32bit'/name
        assert {s['module_sha256'] for s in symbols if s['module']==name}=={sha(binary)}, name
    run=BASE/'runs'/datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ')
    run.mkdir(parents=True,exist_ok=False)
    results=[]
    for case in cases:
        result=dict(case_id=case['id'],scope=case['scope'],expected=case['expected'],
                    script_sha256=sha(ROOT/case['script']),result='NOT_RUN')
        if args.run:
            command=[sys.executable,case['script'],*case.get('args',[])]
            try:
                p=subprocess.run(command,cwd=ROOT,capture_output=True,text=True,timeout=60,
                    env=dict(os.environ,NITMOD_ACCEPTANCE_RUN=str(run)))
                result.update(result='PASS' if p.returncode==0 else 'FAIL',exit_code=p.returncode,
                              command=command,stdout=p.stdout,stderr=p.stderr)
            except subprocess.TimeoutExpired:
                result.update(result='TIMEOUT',command=command)
        results.append(result)
    result_index={r['case_id']:r['result'] for r in results}
    for r in rows:
        if r['case_ids']:
            r['actual_result']=';'.join(i+':'+result_index[i] for i in r['case_ids'].split(';'))
    writecsv(run/'functions.csv',rows)
    # Catalog all existing test files; discovery is not evidence of execution.
    tests=[dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(p),
                mapping_status='UNREVIEWED',execution_status='NOT_INFERRED')
           for p in sorted((ROOT/'tests').rglob('*'))
           if p.is_file() and p.suffix in {'.py','.c','.cpp','.cjs','.js'}]
    writecsv(run/'test-catalog.csv',tests)
    inputs=[ROOT/'reference/original_function_symbols.csv',ROOT/'reference/port_inventory.csv',
            BASE/'cases.json',BASE/'contracts.json',Path(__file__)]
    inputs += list((ROOT/'original_nitmod_shared_objects_32bit').glob('*.so'))
    inputs += [ROOT/c['script'] for c in cases]
    inputs += [p for p in (ROOT/'tests').rglob('*') if p.is_file() and p.suffix in {'.c','.cpp','.h','.py','.cjs','.js'}]
    sources=[p for p in (ROOT/'src_2.60').rglob('*') if p.is_file() and p.suffix in {'.c','.h','.cpp','.txt'}]
    fingerprints={p.relative_to(ROOT).as_posix():sha(p) for p in sorted(set(inputs+sources))}
    artifacts={p.relative_to(ROOT).as_posix():sha(p) for p in sorted((ROOT/'build/wasm').glob('*.wasm32.so'))}
    summary=dict(created_utc=run.name,python=sys.version,original_symbol_rows=len(symbols),
        legacy_raw_rows=len(inventory),acceptance_rows=len(rows),
        by_module=dict(Counter(r['module'] for r in rows)),
        identities=dict(Counter(r['identity_status'] for r in rows)),
        fully_accepted_functions=0,meaning='Zero full acceptances is not zero implemented functionality.',
        bounded_contract_results=dict(Counter(r['result'] for r in results)),
        test_catalog_files=len(tests),fingerprints=fingerprints,artifacts=artifacts)
    for name,data in [('results.json',results),('manifest.json',summary)]:
        with (run/name).open('x',encoding='utf-8') as f: json.dump(data,f,indent=2,ensure_ascii=False)
    content=f'''# Abnahmelauf {run.name}

- {len(symbols)} Original-Symbolzeilen vollständig aufgenommen.
- {len(rows)} Abnahmeidentitäten einschließlich nicht zugeordneter Dekompilat-Einträge.
- Module: {summary['by_module']}.
- Begrenzte Vertragsprüfungen: {summary['bounded_contract_results']}.
- {len(tests)} vorhandene Testdateien katalogisiert, nicht pauschal als ausgeführt gewertet.
- Vollständige Funktionsabnahmen: 0; dies ist keine Implementierungsquote.

[Vollständige Funktionsliste](functions.csv) · [Testkatalog](test-catalog.csv) · [Ist-Ergebnisse](results.json) · [Versionsnachweis](manifest.json)

Die Sollverträge jeder Funktion müssen einzeln aus dem Original geprüft werden. Leere Sollfelder sind offene Arbeit, keine bestandene Abnahme. Namensabgleich und alte Portstatusfelder sind nur Hinweise. Der Lauf überschreibt keine früheren Ergebnisse.
'''
    (run/'README.md').write_text(content,encoding='utf-8')
    print(run)
    print(json.dumps({k:v for k,v in summary.items() if k not in {'fingerprints','artifacts'}},ensure_ascii=False,indent=2))
    if any(r['result'] in {'FAIL','TIMEOUT'} for r in results): raise SystemExit(1)

if __name__=='__main__': main()
