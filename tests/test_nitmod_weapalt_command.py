"""Reference and command wiring check; +attack2 itself is a separate path."""
from pathlib import Path
import hashlib
root = Path(__file__).resolve().parents[1]
binary = (root / 'original_nitmod_shared_objects_32bit/cgame.mp.i386.so').read_bytes()
assert hashlib.sha256(binary).hexdigest() == '45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f'
assert b'weapAlt is obsolete, please use +attack2.\n\0' in binary
source = (root / 'src_2.60/cgame/cg_weapons.c').read_text()
body = source.split('void CG_AltWeapon_f(void)', 1)[1]
prefix = body.split('if ( !cg.snap )', 1)[0]
assert 'NITMOD_UsesOriginalProtocol() || NITMOD_UsesNitmodHud()' in prefix
assert 'CG_Printf("weapAlt is obsolete, please use +attack2.\\n");' in prefix
assert 'return;' in prefix
commands = (root / 'src_2.60/cgame/cg_consolecmds.c').read_text()
assert '{ "weapalt", CG_AltWeapon_f }' in commands
print('Original weapalt reference and routing passed')
