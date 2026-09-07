"""Compile a reviewed fixture into its unique acceptance run, never build/wasm."""
import argparse
import hashlib
import json
import os
import re
from pathlib import Path
import shutil
import subprocess

root=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser()
p.add_argument('fixture',choices=['charge_cost','pack_team','limbo_charge','native_pack_charge','pack_sink','pack_prediction','loadout','loadout_order','pack_mask_handshake','pack_settings_sender','weapon_limits','teamcount','ui_behavior','ui_browser','ui_search'])
a=p.parse_args()
out=Path(os.environ['NITMOD_ACCEPTANCE_RUN']).resolve()/'fixtures'/a.fixture
out.mkdir(parents=True,exist_ok=False)
emcc=shutil.which('emcc')
if not emcc:
    candidate=Path.home()/'emsdk/upstream/emscripten/emcc.bat'
    if candidate.is_file(): emcc=str(candidate)
node=shutil.which('node')
if not emcc or not node: raise SystemExit('Emscripten and Node are required')
sources=['src_2.60/game/nitmod_skills.c','src_2.60/game/nitmod_protocol.c']
test='tests/test_nitmod_'+a.fixture+'_wasm.c'
defines=['-DGAMEDLL']
if a.fixture in ['ui_behavior','ui_browser','ui_search']:
    cmake=(root/'src_2.60/CMakeLists.txt').read_text()
    block=re.search(r'set\(NITMOD_UI_SRC(.*?)\)',cmake,re.S).group(1)
    shared=re.search(r'nitmod_module\(ui ui UIDLL \$\{NITMOD_UI_SRC\}(.*?)\)',cmake,re.S).group(1)
    sources=['src_2.60/'+s for s in (block+shared).split()]
    assert all((root/s).is_file() for s in sources)
    test='tests/test_nitmod_ui_acceptance.c'
    # This existing fixture supplies native variadic engine doubles. Compile
    # only its syscall boundary with that ABI; do not claim browser ABI coverage.
    boundary=out/'native_fixture_syscalls.c'
    boundary.write_text('#include "ui_local.h"\n#define NITMOD_SYSCALL_ABI_H\n'
        '#define NITMOD_WASM_ABI_EXPORT\ntypedef int (QDECL *nitmod_syscall_t)(int, ...);\n'
        '#define NITMOD_SYSCALL nitmodSyscall\n#include "'+
        (root/'src_2.60/ui/ui_syscalls.c').as_posix()+'"\n',encoding='utf-8')
    sources=[str(boundary) if s=='src_2.60/ui/ui_syscalls.c' else s for s in sources]
    defines=['-DUIDLL=1','-Isrc_2.60/ui','-Isrc_2.60/cgame',
             '-DNITMOD_GAMEINFO_PATH="'+(root/'pak/gameinfo.txt').as_posix()+'"',
             '-sNODERAWFS=1','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=8388608','-sEXIT_RUNTIME=1','-g']
    if a.fixture=='ui_browser': defines+=['-DNITMOD_ACCEPT_BROWSER=1']
    if a.fixture=='ui_search': defines+=['-DNITMOD_ACCEPT_SEARCH=1']
if a.fixture in ['pack_mask_handshake','pack_settings_sender']:
    sources=['src_2.60/game/q_shared.c','src_2.60/game/q_math.c','src_2.60/game/nitmod_protocol.c']
    if a.fixture=='pack_mask_handshake':
        sources+=['src_2.60/cgame/cg_nitmod_config.c','src_2.60/game/bg_classes.c']
        defines=['-DCGAME','-Isrc_2.60/cgame']
if a.fixture in ['weapon_limits','teamcount']:
    test='tests/test_nitmod_'+a.fixture+'.c'
    sources=['src_2.60/game/'+('nitmod_weapon_limits.c' if a.fixture=='weapon_limits' else 'g_nitmod_teamcount.c')]
if a.fixture in ['pack_team','limbo_charge','native_pack_charge','pack_sink']:
    sources+=['src_2.60/game/bg_misc.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']
if a.fixture in ['loadout','loadout_order']:
    test='tests/test_nitmod_'+a.fixture+'.c'
    sources=['src_2.60/game/g_nitmod_loadout.c']
if a.fixture=='pack_prediction':
    client=(root/'src_2.60/cgame/cg_predict.c').read_text()
    move=(root/'src_2.60/game/bg_pmove.c').read_text()
    assert client.count('NITMOD_PackPredictionInputs(&cg_pmove,cg.snap->ps.clientNum);')==2
    assert '!PM_NITMOD_PackChargeAvailable(pm)' in move
    for weapon in ['WP_AMMO','WP_MEDKIT']:
        assert '!pm->nitmodPackChargeEnabled && pm->ps->weapon == '+weapon in move
command=[emcc,test,*sources,'-Isrc_2.60/game',*defines,'-O1','-sASSERTIONS=1','-sENVIRONMENT=node','-o',str(out/'test.js')]
versions={name:subprocess.check_output([exe,'--version'],text=True,cwd=root) for name,exe in [('emcc',emcc),('node',node)]}
(out/'build.json').write_text(json.dumps(dict(command=command,versions=versions),indent=2),encoding='utf-8')
subprocess.run(command,cwd=root,check=True)
(out/'artifacts.json').write_text(json.dumps({f.name:hashlib.sha256(f.read_bytes()).hexdigest() for f in out.glob('test.*')},indent=2),encoding='utf-8')
subprocess.run([node,str(out/'test.js')],cwd=root,check=True)
print('PASS fixture '+a.fixture)
