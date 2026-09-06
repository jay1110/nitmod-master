"""Source routing check; no original renderer replay."""
from pathlib import Path
root=Path(__file__).resolve().parents[1]
source=(root/'src_2.60/ui/ui_main.c').read_text()
body=source.split('static void UI_DrawMissionBriefingObjectives(',1)[1].split('static qboolean updateModel',1)[0]
assert 'UI_FindMapInfoByMapname(mapname)' in body
assert 'if(!info || !info->objectives) return;' in body
assert 'UI_DrawDescriptionText(rect, scale, color, text_x, text_y, textStyle, align,' in body
assert 'info->objectives, 0);' in body
assert 'buff[' not in body
renderer=(root/'src_2.60/ui/ui_nitmod_description.c').read_text()
assert 'length==(int)sizeof(line)-1' in renderer
print('Objectives map lookup, null handling, offsets and bounded renderer verified')
