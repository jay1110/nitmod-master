"""Source wiring regression; does not simulate the engine's cvar store."""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
source = (root / 'src_2.60/game/g_script_actions.c').read_text()
body = source.split('qboolean G_ScriptAction_Cvar(', 1)[1].split('G_ScriptAction_AbortIfWarmup', 1)[0]
for expression in ('cvarValue |= NITMOD_ScriptBitMask(atoi(token));',
                   'cvarValue &= ~NITMOD_ScriptBitMask(atoi(token));',
                   'cvarValue = atoi(token);', 'cvarValue = rand() % atoi(token);'):
    assert expression + '\n\t\ttrap_Cvar_Set(cvarName, va("%i", cvarValue));' in body
assert '(int)((unsigned int)cvarValue + 1u)' in body  # Original inc ignores the operand.
assert body.count('NITMOD_ScriptBitMask(atoi(token))') == 4
assert body.count('trap_Cvar_Set(') == 5
assert 'BG_StringHashValue(name)' in body
assert 'G_NITMOD_FindByScriptNameHash( trent, scriptNameHash )' in body
assert 'G_Find( trent, FOFS(scriptName)' not in body
binary = (root / 'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
# EDI receives COM_ParseExt's second-token pointer; that pointer is hashed.
assert binary[0xb5988:0xb598a] == bytes.fromhex('89 c7')
assert binary[0xb59a7:0xb59aa] == bytes.fromhex('89 3c 24')
assert binary[0xb59ac:0xb59b1] == bytes.fromhex('e8 6f 61 f6 ff')
print('Script cvar: five modifying paths write back; bit tests use original mask.')
