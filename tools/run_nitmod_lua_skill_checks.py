"""Real Lua callbacks using production skill/XP/rank code, with engine doubles."""
from pathlib import Path
from datetime import datetime, timezone
import subprocess, json, hashlib
root=Path(__file__).resolve().parents[1]
out=root/'build'/('lua-skills-'+datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ'));out.mkdir()
sources=['tests/test_nitmod_lua_skills.c','src_2.60/game/g_nitmod_lua.c','src_2.60/game/g_stats.c','src_2.60/game/g_session.c','src_2.60/game/g_nitmod_score.c','src_2.60/game/nitmod_score.c','src_2.60/game/nitmod_skills.c','src_2.60/game/nitmod_protocol.c','src_2.60/game/nitmod_sha1.c','src_2.60/game/bg_misc.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']+[str(p.relative_to(root)) for p in sorted((root/'src_2.60/lua51').glob('*.c'))]
sources+=['src_2.60/game/g_nitmod_abilities.c','src_2.60/game/g_nitmod_adrenaline_grant.c']
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*sources,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sALLOW_MEMORY_GROWTH=1','-sENVIRONMENT=node','-o',str(out/'test.js')]
compiled=subprocess.run(cmd,cwd=root,capture_output=True,text=True)
(out/'build.log').write_text(compiled.stdout+compiled.stderr)
if compiled.returncode:
    print('\n'.join(line for line in compiled.stderr.splitlines() if 'error:' in line));print(out);raise SystemExit(compiled.returncode)
r=subprocess.run(['node',str(out/'test.js')],cwd=root,capture_output=True,text=True)
(out/'result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in sources+['tests/test_nitmod_lua.c']}),indent=2))
print(r.stdout+r.stderr);print(out);raise SystemExit(r.returncode)
