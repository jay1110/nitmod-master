"""Check the recorded real-engine run from serve_nitmod_lua_acceptance.py."""
import argparse
import hashlib
import json
import re
import zipfile
from pathlib import Path


def check(directory):
    run = json.loads((directory / 'run.json').read_text()) if (directory / 'run.json').exists() else {}
    rows = [entry for line in (directory / 'browser.jsonl').read_text().splitlines()
            for entry in json.loads(line)]
    output = '\n'.join(row['text'] for row in rows)
    checks = {}
    for marker in ('INIT', 'CONNECT', 'BEGIN', 'FRAMES', 'CONSOLE', 'CLIENTCOMMAND',
                   'DAMAGE_PASS 100 90', 'OBITUARY 0 1022 31', 'DEAD -60',
                   'SPAWN 0 1 0 1', 'REVIVE_PASS 50', 'RESPAWN_DEAD',
                   'SPAWN 0 0 0 1', 'SHUTDOWN 1', 'QUIT', 'IPC_PASS', 'VFS_PASS'):
        checks[marker] = 'LUA_ACCEPT ' + marker in output
    checks['two loaded modules'] = 'Lua API: 2 modules loaded' in output
    checks['ACL unload'] = 'Lua API: 0 modules loaded' in output
    checks['engine exited'] = 'WebSocket networking shutdown' in output
    if run.get('demo'):
        checks['demo recorded'] = 'DEMO: Recording server-side demo' in output
        checks['demo recording stopped'] = 'DEMO: Stopped recording server-side demo' in output
        checks['Lua observes recorded client 0'] = 'LUA_ACCEPT DEMO_PASS 0 ' in output
        playback_output = output[output.rfind('LUA_ACCEPT INIT '):]
        checks['recorded client has no Begin callback'] = 'LUA_ACCEPT BEGIN 0' not in playback_output
    else:
        checks['begin only on initial connection and restart'] = (
            output.count('LUA_ACCEPT BEGIN 0') == output.count('LUA_ACCEPT INIT ') == 2)
    checks['no Lua hook failure'] = not re.search(r'Lua API: et_\w+:', output)
    checks['no UI macro failure'] = not re.search(r'_WINDOW_(WIDTH|HEIGHT).*undefined', output)
    checks['no browser exception'] = not any(row['kind'] in ('error', 'rejection') for row in rows)
    # Rows in lua_status end with an error counter; inspect every observed VM row.
    vm_rows = re.findall(r'^\d+ Nitmod Lua .* [0-9a-fA-F]{40} lua_acceptance(?:_peer)?\.lua (\d+)\s*$', output, re.M)
    checks['status reports zero errors for both VMs'] = len(vm_rows) >= 2 and all(int(n) == 0 for n in vm_rows)
    packs = list(directory.glob('nitmod_lua_acceptance_*.pk3'))
    checks['one isolated module package'] = len(packs) == 1
    if len(packs) == 1:
        expected = json.loads((directory / 'modules.json').read_text())
        with zipfile.ZipFile(packs[0]) as pack:
            checks['package fingerprints'] = all(
                hashlib.sha256(pack.read(name + '.mp.wasm32.so')).hexdigest() == digest
                for name, digest in expected.items())
        checks['engine used acceptance package'] = packs[0].name in output
    return dict(passed=all(checks.values()), checks=checks,
                log_sha256=hashlib.sha256((directory / 'browser.jsonl').read_bytes()).hexdigest())


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    args = parser.parse_args()
    result = check(args.directory)
    # Print only: repeated checks never replace old acceptance artifacts.
    print(json.dumps(result, indent=2))
    raise SystemExit(0 if result['passed'] else 1)
