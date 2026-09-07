"""Run the existing complete damage fixture against current WASM game objects.

Build qagame in build/wasm first. No substitute gameplay implementation is used.
"""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import subprocess
import sys

root = Path(__file__).resolve().parents[1]
fixture = 'tests/test_nitmod_lua_death.c' if '--lua-death' in sys.argv else 'tests/test_nitmod_projectile_damage.c'
out = root / 'build' / ('lua-gameplay-' + datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ'))
out.mkdir()
em = Path.home() / 'emsdk/upstream/emscripten'
if '--lua-death' in sys.argv:
    with (out/'production-build.log').open('w') as log:
        result=subprocess.run(['cmake','--build','build/wasm','--target','qagame','-j','8'],cwd=root,stdout=log,stderr=log)
    if result.returncode:
        print(out);raise SystemExit(result.returncode)
objects = sorted(p for p in (root / 'build/wasm/CMakeFiles/qagame.dir').rglob('*.o') if p.name!='g_syscalls.c.o')
if not objects:
    raise SystemExit('Build qagame in build/wasm first')
commands = [
    [str(em / 'emcc.bat'), fixture, '-Isrc_2.60/game',
     '-DGAMEDLL', '-O1', '-c', '-o', str(out / 'fixture.o')],
    [str(em / 'emcc.bat'), 'tests/nitmod_gameplay_fixture_syscalls.c', '-Isrc_2.60/game',
     '-DGAMEDLL', '-O1', '-c', '-o', str(out / 'fixture-syscalls.o')],
    [str(em / 'em++.bat'), str(out / 'fixture.o'), str(out / 'fixture-syscalls.o'), *map(str, objects),
     '-sALLOW_MEMORY_GROWTH=1', '-sASSERTIONS=1', '-sENVIRONMENT=node', '-o', str(out / 'test.js')]
]
with (out / 'build.log').open('w') as log:
    for cmd in commands:
        # em++.bat goes through cmd.exe's short command-line limit. This is a
        # compiler response file, not shell code; use slash-separated paths.
        response = out / 'compile.rsp'
        response.write_text('\n'.join(json.dumps(arg.replace('\\', '/')) for arg in cmd[1:]))
        result = subprocess.run([cmd[0], '@' + str(response)], cwd=root, stdout=log, stderr=log)
        if result.returncode:
            print(out)
            raise SystemExit(result.returncode)
result = subprocess.run(['node', str(out / 'test.js')], cwd=root, capture_output=True, text=True)
(out / 'result.json').write_text(json.dumps(dict(
    commands=commands, fixture=fixture, fixture_sha256=hashlib.sha256((root/fixture).read_bytes()).hexdigest(), exit_code=result.returncode, stdout=result.stdout, stderr=result.stderr,
    objects={str(p.relative_to(root)): hashlib.sha256(p.read_bytes()).hexdigest() for p in objects}
), indent=2))
print(result.stdout + result.stderr)
print(out)
raise SystemExit(result.returncode)
