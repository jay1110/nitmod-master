"""Reference/source check; not a rendered browser test."""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
source = (root/'src_2.60/ui/ui_main.c').read_text()
body = source.split('static void UI_DrawServerRefreshDate(',1)[1].split('static void UI_DrawServerMOTD(',1)[0]
reference = (root/'src_nitmod_decompiled/ui/sorted/ui_ui_draw.c').read_text()
original = reference.split('  case 0xf7:',1)[1].split('  case 0xf8:',1)[0]
for text in ('Getting info for %d servers (ESC to cancel)',
             'Waiting for response from Master Server', 'Refresh Time: %s'):
    assert text in body and text in original
assert 'trap_TranslateString' not in body
print('Three original server refresh messages verified')
