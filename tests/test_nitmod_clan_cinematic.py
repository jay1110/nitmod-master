"""Check original no-op ownerdraw dispatch, not video playback."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[1]
original = (root / 'src_nitmod_decompiled/ui/sorted/ui_ui_draw.c').read_text()
source = (root / 'src_2.60/ui/ui_main.c').read_text()
reference = original.split('  case 0xfb:', 1)[1].split('    break;', 1)[0]
assert all(not line.strip() or line.strip().startswith('case ') for line in reference.splitlines())
branch = source.split('case UI_CLANCINEMATIC:', 1)[1].split('break;', 1)[0]
assert not re.sub(r'/\*.*?\*/', '', branch, flags=re.S).strip()
assert 'UI_DrawClanCinematic(' not in source
assert 'UI_DrawPreviewCinematic(&rect, scale, color);' in source
print('Original clan cinematic no-op and retained movie dispatch verified')
