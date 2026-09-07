"""Rebuild the database/VFS integration fixture in a fresh output directory."""
from pathlib import Path
from datetime import datetime,timezone
import subprocess,shutil,json,hashlib
root=Path(__file__).resolve().parents[1]
out=root/'build'/('db-verification-'+datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ'));out.mkdir()
emcc=shutil.which('emcc') or str(Path.home()/'emsdk/upstream/emscripten/emcc.bat')
sources=['tests/test_nitmod_database.c','src_2.60/game/nitmod_database.c','src_2.60/game/g_nitmod_database.c','src_2.60/game/g_nitmod_config.c','src_2.60/game/g_nitmod_accounts.c','src_2.60/game/nitmod_sha1.c','src_2.60/game/nitmod_xp.c','src_2.60/game/g_nitmod_records.c','src_2.60/game/g_nitmod_admin.c','src_2.60/sqlite/sqlite3.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
cmd=[emcc,*sources,'-Isrc_2.60/game','-DGAMEDLL','-DSQLITE_THREADSAFE=0','-DSQLITE_OMIT_LOAD_EXTENSION=1','-DSQLITE_OS_OTHER=1','-DSQLITE_OMIT_WAL=1','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-o',str(out/'test.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'test.js')],cwd=root,capture_output=True,text=True)
(out/'result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in sources}),indent=2),encoding='utf-8')
print(r.stdout,end='');print(r.stderr,end='');print(out)
raise SystemExit(r.returncode)
