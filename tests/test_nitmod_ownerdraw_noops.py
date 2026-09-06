"""Compare selected original ownerdraw no-ops with production dispatch."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[1]
original = (root/'src_nitmod_decompiled/ui/sorted/ui_ui_draw.c').read_text()
group = original.split('  case 0xca:',1)[1].split('    break;',1)[0]
ids = {202} | {int(n,0) for n in re.findall(r'case (0x[0-9a-f]+|\d+):',group)}
defines = dict(re.findall(r'#define\s+(UI_\w+)\s+(\d+)\b',
                         (root/'pak/ui/menudef.h').read_text()))
source = (root/'src_2.60/ui/ui_main.c').read_text()
defines.update(re.findall(r'#define\s+(UI_\w+)\s+(\d+)\b', source))
assert 'UI_DrawSaveGameShot(' not in source
source = source.split('static void UI_OwnerDraw(float ',1)[1].split('qboolean UI_OwnerDrawVisible',1)[0]
source = re.sub(r'/\*.*?\*/|//[^\n]*','',source,flags=re.S)
names = ['UI_PLAYERMODEL','UI_CLANLOGO','UI_ALLMAPS_SELECTION',
         'UI_MAPS_SELECTION','UI_BOTNAME','UI_SELECTEDPLAYER','UI_SAVEGAME_SHOT']
names += ['UI_'+team+'TEAM'+str(i) for team in ('BLUE','RED') for i in range(1,6)]
for name in names:
    assert int(defines[name]) in ids, name
    branch = source.split('case '+name+':',1)[1].split('break;',1)[0]
    assert not re.sub(r'case\s+\w+\s*:','',branch).strip(), name
for active in ('UI_DrawTeamName','UI_DrawServerMOTD','UI_DrawMapPreview','UI_DrawCrosshair'):
    assert active+'(' in source
print(f'{len(names)} original no-op ownerdraws and retained active paths verified')
