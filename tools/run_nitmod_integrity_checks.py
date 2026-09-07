"""Build and execute the active NxAC checksum path without replacing old tests."""
from pathlib import Path
from datetime import datetime, timezone
import json
import hashlib
import shutil
import subprocess
root=Path(__file__).resolve().parents[1]
compiler=shutil.which('emcc') or str(Path.home()/'emsdk/upstream/emscripten/emcc.bat')
node=shutil.which('node')
if not Path(compiler).is_file() or not node: raise SystemExit('Emscripten and Node required')
out=root/'build'/('nxac-verification-'+datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ'))
out.mkdir()
sources=['tests/test_nitmod_integrity.c','src_2.60/game/g_nitmod_integrity.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
command=[compiler,*sources,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'test.js')]
subprocess.run(command,cwd=root,check=True)
result=subprocess.run([node,str(out/'test.js')],cwd=root,capture_output=True,text=True)
(out/'result.json').write_text(json.dumps(dict(command=command,exit_code=result.returncode,stdout=result.stdout,stderr=result.stderr,
    sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in sources}),indent=2),encoding='utf-8')
print(result.stdout,end=''); print(result.stderr,end=''); print(out)
raise SystemExit(result.returncode)
