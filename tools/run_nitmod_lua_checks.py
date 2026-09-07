from pathlib import Path
from datetime import datetime,timezone
import subprocess,json,hashlib,re
root=Path(__file__).resolve().parents[1]
out=root/'build'/('lua-verification-'+datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ'));out.mkdir()
awards=subprocess.run(['python',str(root/'tests/test_nitmod_global_awards_original.py')],cwd=root,capture_output=True,text=True)
(out/'awards-original-result.json').write_text(json.dumps(dict(exit_code=awards.returncode,stdout=awards.stdout,stderr=awards.stderr),indent=2))
if awards.returncode: raise SystemExit(awards.stdout+awards.stderr)
mods=subprocess.run(['python',str(root/'tests/test_nitmod_lua_mod_original.py')],cwd=root,capture_output=True,text=True)
(out/'mods-original-result.json').write_text(json.dumps(dict(exit_code=mods.returncode,stdout=mods.stdout,stderr=mods.stderr),indent=2))
if mods.returncode: raise SystemExit(mods.stdout+mods.stderr)
weapons=subprocess.run(['python',str(root/'tests/test_nitmod_lua_weapons_original.py')],cwd=root,capture_output=True,text=True)
(out/'weapons-original-result.json').write_text(json.dumps(dict(exit_code=weapons.returncode,stdout=weapons.stdout,stderr=weapons.stderr),indent=2))
if weapons.returncode: raise SystemExit(weapons.stdout+weapons.stderr)
statistics=subprocess.run(['python',str(root/'tests/test_nitmod_lua_statistics_original.py')],cwd=root,capture_output=True,text=True)
(out/'statistics-original-result.json').write_text(json.dumps(dict(exit_code=statistics.returncode,stdout=statistics.stdout,stderr=statistics.stderr),indent=2))
if statistics.returncode: raise SystemExit(statistics.stdout+statistics.stderr)
events=subprocess.run(['python',str(root/'tests/test_original_event_map.py')],cwd=root,capture_output=True,text=True)
(out/'events-original-result.json').write_text(json.dumps(dict(exit_code=events.returncode,stdout=events.stdout,stderr=events.stderr),indent=2))
if events.returncode: raise SystemExit(events.stdout+events.stderr)
original=json.loads((root/'reference/acceptance/lua-original-spawn-fields.json').read_text())
mapped=re.findall(r'\{"([^"]+)"',(root/'src_2.60/game/nitmod_lua_spawn_fields.h').read_text())
assert len(mapped)==len(set(mapped)), 'duplicate spawn field'
assert {f['name'] for f in original}==set(mapped), 'spawn field inventory mismatch'
(out/'spawn-inventory.json').write_text(json.dumps(dict(original_count=len(original),mapped_count=len(mapped),names=mapped),indent=2))
fields=json.loads((root/'reference/acceptance/lua-original-fields.json').read_text())
expected={(f['name'],f['flags']&3) for rows in fields.values() for f in rows}
actual={(name,int(flags)&3) for name,flags in re.findall(r'\{"([^"]+)"\s*,\s*\d+\s*,\s*(\d+)\s*,',(root/'src_2.60/game/nitmod_lua_fields.h').read_text())}
assert expected==actual, 'entity/client field inventory mismatch'
expected_metadata={(f['name'],f['flags']&3):(f['type'],f['flags']) for rows in fields.values() for f in rows}
actual_metadata={(name,int(flags)&3):(int(kind),int(flags)) for name,kind,flags in re.findall(r'\{"([^"]+)"\s*,\s*(\d+)\s*,\s*(\d+)\s*,',(root/'src_2.60/game/nitmod_lua_fields.h').read_text())}
assert expected_metadata==actual_metadata, 'entity/client field type or access flags mismatch'
(out/'entity-inventory.json').write_text(json.dumps(dict(original_rows=sum(map(len,fields.values())),missing=sorted(expected-actual),extra=sorted(actual-expected)),indent=2))
sources=['tests/test_nitmod_lua.c','src_2.60/game/g_nitmod_lua.c','src_2.60/game/nitmod_sha1.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']+[str(p.relative_to(root)) for p in sorted((root/'src_2.60/lua51').glob('*.c'))]
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*sources,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sALLOW_MEMORY_GROWTH=1','-sENVIRONMENT=node','-o',str(out/'test.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'test.js')],cwd=root,capture_output=True,text=True)
(out/'result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in sources+['src_2.60/game/nitmod_lua_events.h','src_2.60/game/nitmod_entity_ids.h','src_2.60/game/nitmod_powerup_ids.h','src_2.60/game/nitmod_weapon_ids.h','src_2.60/game/g_local.h','src_2.60/game/nitmod_lua_fields.h','src_2.60/game/nitmod_lua_spawn_fields.h','src_2.60/game/g_nitmod_lua.h']}),indent=2))
print(r.stdout+r.stderr);print(out)
if r.returncode: raise SystemExit(r.returncode)
deps=['tests/test_nitmod_lua_trigger.c','src_2.60/game/g_trigger.c','src_2.60/game/g_match.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*deps,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'dependencies.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'dependencies.js')],cwd=root,capture_output=True,text=True)
(out/'dependencies-result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in deps+['src_2.60/game/g_local.h']}),indent=2))
print(r.stdout+r.stderr)
if r.returncode: raise SystemExit(r.returncode)
health=['tests/test_nitmod_health_rewards_wasm.c','src_2.60/game/bg_misc.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*health,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'health.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'health.js')],cwd=root,capture_output=True,text=True)
(out/'health-result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in health+['src_2.60/game/g_client.c','src_2.60/game/g_local.h']}),indent=2))
print(r.stdout+r.stderr)
if r.returncode: raise SystemExit(r.returncode)
sc=['tests/test_nitmod_shoutcaster.c','src_2.60/game/g_nitmod_shoutcaster.c','src_2.60/game/g_team.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*sc,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'shoutcaster.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'shoutcaster.js')],cwd=root,capture_output=True,text=True)
(out/'shoutcaster-result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in sc}),indent=2))
print(r.stdout+r.stderr)
if r.returncode: raise SystemExit(r.returncode)
geo=['tests/test_nitmod_geoip.c','src_2.60/game/g_nitmod_geoip.c']
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*geo,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'geoip.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'geoip.js')],cwd=root,capture_output=True,text=True)
(out/'geoip-result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in geo}),indent=2))
print(r.stdout+r.stderr)
if r.returncode: raise SystemExit(r.returncode)
session=['tests/test_nitmod_lua_session.c','src_2.60/game/g_session.c','src_2.60/game/nitmod_skills.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*session,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'session.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'session.js')],cwd=root,capture_output=True,text=True)
(out/'session-result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in session}),indent=2))
print(r.stdout+r.stderr)
if r.returncode: raise SystemExit(r.returncode)
stats=['tests/test_nitmod_global_stats_message.c','src_2.60/cgame/cg_nitmod_stats.c','src_2.60/game/nitmod_protocol.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*stats,'-Isrc_2.60/game','-Isrc_2.60/cgame','-DCGAME','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'global-stats.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'global-stats.js')],cwd=root,capture_output=True,text=True)
(out/'global-stats-result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in stats}),indent=2))
print(r.stdout+r.stderr)
if r.returncode: raise SystemExit(r.returncode)
core=['tests/test_nitmod_global_stats_core.c','src_2.60/game/g_nitmod_global_stats.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*core,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'stats-core.js')]
subprocess.run(cmd,cwd=root,check=True)
r=subprocess.run(['node',str(out/'stats-core.js')],cwd=root,capture_output=True,text=True)
(out/'stats-core-result.json').write_text(json.dumps(dict(command=cmd,exit_code=r.returncode,stdout=r.stdout,stderr=r.stderr,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in core}),indent=2))
print(r.stdout+r.stderr)
if r.returncode: raise SystemExit(r.returncode)
subprocess.run(['python',str(root/'tools/run_nitmod_lua_skill_checks.py')],cwd=root,check=True)
subprocess.run(['python',str(root/'tools/run_nitmod_gameplay_wasm_checks.py'),'--lua-death'],cwd=root,check=True)
