"""Source-reference regression, not an interactive menu test."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[1]
original = (root/'src_nitmod_decompiled/ui/sorted/ui_ui_misc.c').read_text()
original = original.split('uint32_t UI_OwnerDrawVisible(uint param_1)',1)[1].split('void UI_SortMods',1)[0]
masks = [int(x,0) for x in re.findall(r'param_1 & (0x[0-9a-f]+|\d+)\)',original)]
assert masks and all(not (mask & 3) for mask in masks)
source = (root/'src_2.60/ui/ui_main.c').read_text()
source = source.split('qboolean UI_OwnerDrawVisible(int flags)',1)[1].split('static qboolean UI_Handicap_HandleKey',1)[0]
assert 'flags &= ~(UI_SHOW_LEADER | UI_SHOW_NOTLEADER);' in source
assert 'teamClientNums' not in source and 'uiInfo.teamLeader' not in source
for retained in ('UI_SHOW_FAVORITESERVERS','UI_SHOW_PLAYERMUTED','UI_SHOW_DEMOAVAILABLE','UI_NitmodCampaignVisible'):
    assert retained in source
print('Original ignored leader bits and retained visibility rules verified')
