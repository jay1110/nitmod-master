"""Original key dispatcher comparison; source-level, not input replay."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[1]
original = (root/'src_nitmod_decompiled/ui/sorted/ui_ui_misc.c').read_text()
original = original.split('uint32_t UI_OwnerDrawHandleKey(',1)[1].split('void AssetCache(',1)[0]
ids = {int(x,0) for x in re.findall(r'^  case (0x[0-9a-f]+|\d+):',original,re.M)}
assert 'default:\n    return 0;' in original
defines = dict(re.findall(r'#define\s+(UI_\w+)\s+(\d+)\b',
                         (root/'pak/ui/menudef.h').read_text()))
source = (root/'src_2.60/ui/ui_main.c').read_text()
source = source.split('static qboolean UI_OwnerDrawHandleKey(',1)[1].split('static float UI_GetValue(',1)[0]
source = re.sub(r'/\*.*?\*/|//[^\n]*','',source,flags=re.S)
for name in ('UI_OPPONENT_NAME','UI_BOTNAME','UI_REDBLUE','UI_SELECTEDPLAYER'):
    assert int(defines[name]) not in ids
    branch=source.split('case '+name+':',1)[1].split('break;',1)[0]
    assert not branch.strip(), name
for name in ('UI_BLUETEAM1','UI_REDTEAM1','UI_CROSSHAIR','UI_NETFILTER'):
    assert int(defines[name]) in ids
    assert 'case '+name+':' in source
assert 'UI_TeamMember_HandleKey(' in source
assert 'return qfalse;' in source
print('Four original default key paths and active team/browser handlers verified')
