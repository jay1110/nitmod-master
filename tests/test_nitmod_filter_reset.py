"""Source comparison of original filter reset and display bounds."""
from pathlib import Path
root=Path(__file__).resolve().parents[1]
original=(root/'src_nitmod_decompiled/ui/sorted/ui_ui_misc.c').read_text()
original=original.split('uint32_t UI_OwnerDrawHandleKey(',1)[1]
branch=original.split('case 0xde:',1)[1].split('case 0xf2:',1)[0]
assert 'ui_serverFilterType._12_4_ = 0;' in branch
source=(root/'src_2.60/ui/ui_main.c').read_text()
branch=source.split('static qboolean UI_NetFilter_HandleKey(',1)[1].split('static qboolean UI_OpponentName_HandleKey',1)[0]
assert 'ui_serverFilterType.integer = 0;' in branch
assert 'integer++' not in branch and 'integer--' not in branch
assert 'UI_BuildServerDisplayList(qtrue);' in branch
assert source.count('ui_serverFilterType.integer < 0 || ui_serverFilterType.integer >= numServerFilters') == 2
print('Original filter reset and both display bounds verified')
