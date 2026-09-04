"""Compare registration defaults with hash-pinned original ELF records."""
import importlib.util
import pathlib
import re
import sys
import struct

root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('weapon_cvars', root / 'tools/extract_weapon_cvars.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
records = module.extract(root)
assert len(records) == 11
records.update(module.extract(root, names=('g_medics', 'g_noReload')))
source = (root / 'src_2.60/game/g_nitmod_weapon_config.c').read_text()
rows = re.findall(r'\{ "([^"]+)", "([^"]+)", (\d+) \}', source)
assert len(rows) == 10 and len({row[0] for row in rows}) == 10
for name, default, flags in rows:
    original = records[name]
    assert (default, int(flags)) == (original['default'], original['flags']), name
    assert original['track_change'] == original['reset'] == 0
assert (records['sv_maxclients']['default'], records['sv_maxclients']['flags']) == ('20', 37)
assert (records['g_heavyWeaponRestriction']['default'], records['g_heavyWeaponRestriction']['flags']) == ('100', 5)
assert (records['team_maxPanzers']['default'], records['team_maxPanzers']['flags']) == ('-1', 0)
main = (root / 'src_2.60/game/g_main.c').read_text()
omni = module.extract(root, names=('omnibot_flags',))['omnibot_flags']
assert (omni['default'], omni['flags'], omni['track_change'], omni['reset']) == ('0', 1025, 0, 0)
assert len(re.findall(r'\{\s*&g_OmniBotFlags,\s*"omnibot_flags",\s*"0",\s*CVAR_ARCHIVE\s*\|\s*CVAR_NORESTART,\s*0,\s*qfalse,\s*qfalse\s*\}', main)) == 1
precise = module.extract(root, names=('n_preciseLandmineTrigger',))['n_preciseLandmineTrigger']
assert (precise['default'], precise['flags'], precise['track_change'], precise['reset']) == ('0', 1, 0, 0)
assert len(re.findall(r'\{\s*&n_preciseLandmineTrigger,\s*"n_preciseLandmineTrigger",\s*"0",\s*CVAR_ARCHIVE,\s*0,\s*qfalse,\s*qfalse\s*\}', main)) == 1
damage = module.extract(root, names=('g_damageweapons',))['g_damageweapons']
assert (damage['default'], damage['flags'], damage['track_change'], damage['reset']) == ('0', 0, 0, 0)
assert len(re.findall(r'\{\s*&g_damageweapons,\s*"g_damageweapons",\s*"0",\s*0,\s*0,\s*qfalse,\s*qfalse\s*\}', main)) == 1
missile = (root / 'src_2.60/game/g_missile.c').read_text()
# extract() above pins this artifact's SHA-256. Map virtual addresses through
# ELF sections rather than treating decompiler labels as file offsets.
original_bytes = (root / 'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
section_start = struct.unpack_from('<I', original_bytes, 32)[0]
section_size, section_count = struct.unpack_from('<HH', original_bytes, 46)
def original_code(address, length):
    for index in range(section_count):
        section = struct.unpack_from('<10I', original_bytes, section_start + index * section_size)
        if section[1] != 8 and section[3] <= address and address + length <= section[3] + section[5]:
            offset = section[4] + address - section[3]
            return original_bytes[offset:offset + length]
    raise AssertionError('unmapped original instruction')

# mov eax,0x04000000; mov [esi+0x2c8],ebp; mov [esi+0x14c],eax
# Bot position: failure code, client origin, angles, local bounds, half factor.
assert original_code(0x223ee4, 5) == bytes.fromhex('b8 03000000')
assert original_code(0x223f16, 6) == bytes.fromhex('d986 68010000')
assert original_code(0x223f50, 6) == bytes.fromhex('8d86 74010000')
assert original_code(0x223f64, 18) == bytes.fromhex('d986 40010000 d886 34010000 d88b f499f8ff')
assert original_code(0x22e008, 4) == struct.pack('<f', 0.5)
# World AABB copies abs bounds, shifts client Z by 2 and tests selected hash.
assert original_code(0x22497a, 6) == bytes.fromhex('d986 50010000')
assert original_code(0x2249bb, 6) == bytes.fromhex('d883 e8a9f8ff')
assert original_code(0x22effc, 4) == struct.pack('<f', 2.0)
assert original_code(0x2249e2, 10) == bytes.fromhex('81be c0050000 8e900100')
# Replacement re-resolves original argument, not the selected construction.
assert original_code(0x224ad0, 15) == bytes.fromhex('8b8424 a4000000 890424 e8 91d3deff')
# Bounds selection: constructible type, parent, both team queries and hash.
assert original_code(0x223d18, 4) == bytes.fromhex('837e04 20')
assert original_code(0x223e00, 6) == bytes.fromhex('8b86 18020000')
assert original_code(0x223e17, 5) == bytes.fromhex('e8 a450e6ff')
assert original_code(0x223e35, 5) == bytes.fromhex('e8 8650e6ff')
assert original_code(0x223d2a, 10) == bytes.fromhex('81be c0050000 8e900100')
assert original_code(0x223df0, 7) == bytes.fromhex('c74714 00004042')
# Spawn derives the cached value from classname through BG_StringHashValue.
assert original_code(0xcd08b, 6) == bytes.fromhex('8b80 a4010000')
assert original_code(0xcd20b, 5) == bytes.fromhex('e8 10e9f4ff')
assert original_code(0xcd219, 6) == bytes.fromhex('8987 c0050000')
# Local accum trigger_if_equal: cached-name iteration and caller script ID.
# Named trigger uses cached matches and skips SVF_BOT without bot dispatch.
assert original_code(0xb0cbd, 5) == bytes.fromhex('e8 5eaef6ff')
assert original_code(0xb0cec, 5) == bytes.fromhex('e8 9fdb0500')
assert original_code(0xb0cf9, 9) == bytes.fromhex('f680 28010000 08 75de')
assert original_code(0xb0d1b, 5) == bytes.fromhex('e8 50b2ffff')
assert original_code(0xb0d2d, 6) == bytes.fromhex('39b0 c4030000')
# Global counterpart: one hash, ascending cached iteration, event and ID check.
assert original_code(0xb2931, 5) == bytes.fromhex('e8 ea91f6ff')
assert original_code(0xb2960, 5) == bytes.fromhex('e8 2bbf0500')
assert original_code(0xb2982, 5) == bytes.fromhex('e8 e995ffff')
assert original_code(0xb2998, 6) == bytes.fromhex('3990 c4030000')
assert original_code(0xb2335, 5) == bytes.fromhex('e8 e697f6ff')
assert original_code(0xb235c, 5) == bytes.fromhex('e8 2fc50500')
assert original_code(0xb237e, 5) == bytes.fromhex('e8 ed9bffff')
assert original_code(0xb2390, 6) == bytes.fromhex('39b8 c4030000')
# TagConnect: targetname first, script hash fallback, then existing tag setup.
assert original_code(0xb3028, 5) == bytes.fromhex('e8 f3360300')
assert original_code(0xb312b, 5) == bytes.fromhex('e8 f089f6ff')
assert original_code(0xb313b, 5) == bytes.fromhex('e8 50b70500')
assert original_code(0xb3093, 5) == bytes.fromhex('e8 684b0300')
# target_script_trigger_use hashes aiName, searches once, then uses targets.
assert original_code(0xd8144, 6) == bytes.fromhex('8b86 40030000')
assert original_code(0xd8151, 5) == bytes.fromhex('e8 ca39f4ff')
assert original_code(0xd8161, 5) == bytes.fromhex('e8 2a670300')
assert original_code(0xd8181, 5) == bytes.fromhex('e8 ea3dfdff')
assert original_code(0xd8191, 5) == bytes.fromhex('e8 8ae80000')
# Forward cached-name searches: level count, next slot, inuse and field match.
assert original_code(0x10e842, 3) == bytes.fromhex('8b4008')
assert original_code(0x10e84f, 9) == bytes.fromhex('8d86 00060000 0f44c7')
assert original_code(0x10e860, 6) == bytes.fromhex('8bb0 94010000')
assert original_code(0x10e86a, 6) == bytes.fromhex('3988 c0050000')
assert original_code(0x10e8da, 6) == bytes.fromhex('3988 b0050000')
# Distinct spawn target/script caches and spawn-only game_manager alias.
assert original_code(0xcd1d4, 6) == bytes.fromhex('8987 bc050000')
assert original_code(0xcd049, 6) == bytes.fromhex('8987 b0050000')
assert original_code(0x247427, 19) == b'script_multiplayer\0'
assert original_code(0x23eecd, 13) == b'game_manager\0'
assert original_code(0xcd2cd, 6) == bytes.fromhex('8d83 b9a8f9ff')
# Script updates hash the parsed fields without the spawn alias.
assert original_code(0xb6380, 20) == bytes.fromhex('8b87 ac030000 890424 e8 9257f6ff 8987 b0050000')
assert original_code(0xb6478, 20) == bytes.fromhex('8b87 54020000 890424 e8 9a56f6ff 8987 bc050000')
# Script set: sticky nospawn flag and refresh before relink.
assert original_code(0xb6409, 5) == bytes.fromhex('b8 01000000')
assert original_code(0xb6412, 4) == bytes.fromhex('894424 3c')
assert original_code(0xb64d8, 8) == bytes.fromhex('8b4c24 3c 85c9 7458')
assert original_code(0xb653b, 5) == bytes.fromhex('e8 80650100')
assert original_code(0xb6553, 11) == bytes.fromhex('e8 c855f6ff 8987 c0050000')
assert original_code(0xb64f4, 6) == bytes.fromhex('8997 c0050000')
assert original_code(0xb64fd, 5) == bytes.fromhex('e8 fe070200')
# Original team-item records: classname pointer, type at +36, tag at +44.
assert original_code(0x2a68f0, 4) == struct.pack('<I', 0x22cbfb)
assert original_code(0x2a6928, 4) == struct.pack('<I', 0x22cc16)
assert original_code(0x22cbfb, 17) == b'team_CTF_redflag\0'
assert original_code(0x22cc16, 18) == b'team_CTF_blueflag\0'
assert original_code(0x2a68f0 + 36, 12) == struct.pack('<3I', 5, 0, 5)
assert original_code(0x2a6928 + 36, 12) == struct.pack('<3I', 5, 0, 6)
assert original_code(0x72c01, 11) == bytes.fromhex('b8 7f310300 8986 c0050000')
assert original_code(0x72c18, 11) == bytes.fromhex('b8 f16a0300 8986 c0050000')
assert original_code(0xccbf1, 11) == bytes.fromhex('ba 7f310300 8997 c0050000')
assert original_code(0xccc16, 11) == bytes.fromhex('b9 f16a0300 898f c0050000')
items_source = (root / 'src_2.60/game/g_items.c').read_text()
assert re.search(r'dropped->classname = item->classname;\s*G_NITMOD_SetTeamItemClassnameHash\(\s*dropped,\s*item\s*\);', items_source)
spawn_source = (root / 'src_2.60/game/g_spawn.c').read_text()
assert re.search(r'if\s*\(\s*!G_CallSpawn\(\s*ent\s*\)\s*\)\s*\{\s*G_FreeEntity\(\s*ent\s*\);\s*\}\s*/\*.*?\*/\s*G_NITMOD_RefreshClassnameHash\(\s*ent\s*\);', spawn_source, re.S)
# OBB resolves then goes straight to AnglesToAxis (no additional inuse guard).
assert original_code(0x223b54, 13) == bytes.fromhex('b8 03000000 85f6 0f84 2b010000')
assert original_code(0x223b69, 6) == bytes.fromhex('8d86 74010000')
assert original_code(0x223b72, 5) == bytes.fromhex('e8 49a1edff')
assert original_code(0x223c58, 12) == bytes.fromhex('d986 40010000 d8a6 34010000')
# Eye/bone wrappers use virtual slot 19 (0x4c); eye adds signed viewheight.
assert original_code(0x224778, 3) == bytes.fromhex('8b40 4c')
assert original_code(0x2247bb, 6) == bytes.fromhex('ffd0 85c0 75d8')
assert original_code(0x224802, 6) == bytes.fromhex('db80 bc000000')
assert original_code(0x22480a, 3) == bytes.fromhex('d847 08')
assert original_code(0x2245f0, 3) == bytes.fromhex('8b40 4c')
assert original_code(0x224628, 17) == bytes.fromhex('8b7424 6c 894c24 04 891424 897424 08 ffd0')
# Orientation: client viewangles / entity currentAngles, both AngleVectors.
assert original_code(0x2240fd, 5) == bytes.fromhex('b8 03000000')
assert original_code(0x224126, 5) == bytes.fromhex('05 b0000000')
assert original_code(0x224142, 5) == bytes.fromhex('e8 59acedff')
assert original_code(0x224154, 6) == bytes.fromhex('81c2 74010000')
assert original_code(0x224171, 5) == bytes.fromhex('e8 2aacedff')
# Original AngleVectors tolerates each null output independently.
assert original_code(0xfee9c, 2) == bytes.fromhex('85c0')
assert original_code(0xfeee6, 4) == bytes.fromhex('85d2 742a')
assert original_code(0xfef14, 4) == bytes.fromhex('85f6 7430')
# Velocity: fixed 64-slot boundary, raw trajectory delta, mover old origin.
assert original_code(0x22405d, 5) == bytes.fromhex('3d ff7f0100')
assert original_code(0x224068, 3) == bytes.fromhex('d942 24')
assert original_code(0x224088, 3) == bytes.fromhex('83f9 04')
assert original_code(0x224093, 6) == bytes.fromhex('d8a2 d8040000')
assert original_code(0x22409d, 6) == bytes.fromhex('d88b 389af8ff')
assert original_code(0x22e04c, 4) == struct.pack('<f', 50.0)
# G_RunEntity saves currentOrigin in oldOrigin before entity simulation.
assert original_code(0x7ea06, 6) == bytes.fromhex('d986 68010000')
assert original_code(0x7ea13, 6) == bytes.fromhex('d99e d8040000')
assert original_code(0x7ea1f, 6) == bytes.fromhex('d986 6c010000')
assert original_code(0x7ea29, 6) == bytes.fromhex('d99e dc040000')
assert original_code(0x7ea35, 12) == bytes.fromhex('d986 70010000 d99e e0040000')
assert original_code(0x8f246, 17) == bytes.fromhex('b8 00000004 89ae c8020000 8986 4c010000')
assert original_code(0x8de73, 5) == bytes.fromhex('b9 00000004')
assert original_code(0x8de93, 6) == bytes.fromhex('898e 4c010000')
assert original_code(0x8ded2, 11) == bytes.fromhex('b8 01000000 8986 fc000000')
assert original_code(0x8e1cf, 10) == bytes.fromhex('8b81 fc000000 85c0 750d')
assert original_code(0x8e1d9, 7) == bytes.fromhex('f746 68 01008800')
assert original_code(0x8e2e9, 4) == bytes.fromhex('660d 000c')
assert original_code(0x8e302, 6) == bytes.fromhex('83c0 17 83f8 2e')
assert original_code(0x8ad17, 6) == bytes.fromhex('f7c7 20000000')
assert original_code(0x8af54, 6) == bytes.fromhex('8bb8 ac000000')
assert original_code(0x8af5a, 7) == bytes.fromhex('39bc2a ac000000')
assert original_code(0x8ac60, 6) == bytes.fromhex('81e7 00010000')
assert original_code(0x8ade0, 8) == bytes.fromhex('83bc2a e8000000 14')
assert original_code(0x8ac87, 4) == bytes.fromhex('f640 0c 20')
assert original_code(0x8ac93, 8) == bytes.fromhex('f6842f 28010000 08')
assert original_code(0xf4274, 6) == bytes.fromhex('8b80 a8000000')
# Original Omni-bot handle field writes and world-index exception.
assert original_code(0x21e556, 7) == bytes.fromhex('668910 66894802')
assert original_code(0x21e56f, 7) == bytes.fromhex('66894802 668910')
assert original_code(0x21e4bd, 6) == bytes.fromhex('81fa fe030000')
assert original_code(0x21f415, 9) == bytes.fromhex('66c70486 0100 80e2fc')
assert original_code(0x221956, 5) == bytes.fromhex('8064bd02 fc')
assert original_code(0x22195b, 12) == bytes.fromhex('40 98 85c0 0f44c2 668944bd00')
assert original_code(0xe71f5, 5) == bytes.fromhex('e8 06acf2ff')
assert original_code(0xe7292, 5) == bytes.fromhex('e8 a9fafeff')
assert original_code(0xe7297, 10) == bytes.fromhex('8b96 ac010000 85d2 7417')
assert original_code(0x812de, 5) == bytes.fromhex('e8 6d14f9ff')
assert original_code(0x812fa, 5) == bytes.fromhex('e8 91dfffff')
assert original_code(0x2220e1, 4) == bytes.fromhex('8b4068 c3')
assert original_code(0x224e21, 5) == bytes.fromhex('e8 6ad3deff')
assert original_code(0x223916, 5) == bytes.fromhex('e8 55e5deff')
assert original_code(0x223942, 5) == bytes.fromhex('b8 ffffffff')
assert original_code(0x2238d3, 4) == bytes.fromhex('f64001 80')
assert main.index('G_NITMOD_ResetBotHandles();') < main.index('G_InitGame( arg0, arg1, arg2 );')
free_source = (root / 'src_2.60/game/g_utils.c').read_text().split('void G_FreeEntity( gentity_t *ed ) {', 1)[1].split('\n}', 1)[0]
assert free_source.index('G_NITMOD_BotEntityDeleted( ed );') < free_source.index('G_NITMOD_UnregisterSatchel') < free_source.index('if(ed->free)') < free_source.index('if ( ed->neverFree )')
mine_think = missile.split('void G_LandmineThink( gentity_t *self ) {', 1)[1].split('void LandminePostThink', 1)[0]
assert mine_think.count('G_NITMOD_MineTeamContact(') == 1
assert mine_think.index('G_NITMOD_MineTeamContact(') < mine_think.index('sEntWillTriggerMine(')
assert mine_think.index('G_NITMOD_MineTeamContact(') < mine_think.index('G_NITMOD_MineBotContact(') < mine_think.index('sEntWillTriggerMine(')
post_think = missile.split('void LandminePostThink( gentity_t *self ) {', 1)[1].split('void G_LandminePrime', 1)[0]
assert 'G_NITMOD_MineTeamContact' not in post_think
assert 'G_NITMOD_MineBotContact' not in post_think
trigger = missile.split('void LandMineTrigger(gentity_t* self) {', 1)[1].split('\n}', 1)[0]
assert re.findall(r'self->r.contents\s*=\s*(\w+)\s*;', trigger) == ['CONTENTS_BODY']
assert re.search(r'self->s.onFireStart\s*=\s*1\s*;', trigger)
dynamite = missile.split('case WP_DYNAMITE:', 1)[1].split('\n\t}', 1)[0]
assert re.search(r'bolt->r.contents\s*=\s*CONTENTS_BODY\s*;', dynamite)
assert re.search(r'bolt->takedamage\s*=\s*qfalse\s*;', dynamite)
assert re.search(r'bolt->health\s*=\s*5\s*;', dynamite)
assert 'g_damageweapons' not in re.sub(r'/\*.*?\*/|//[^\n]*', '', dynamite, flags=re.S)
satchel = missile.split('case WP_SATCHEL:', 1)[1].split('case WP_DYNAMITE:', 1)[0]
landmine = missile.split('case WP_LANDMINE:', 1)[1].split('case WP_SATCHEL:', 1)[0]
for branch, address, damageable in ((landmine, 0x8f12d, 'qtrue'), (satchel, 0x8ee09, 'qfalse')):
    assert original_code(address, 11) == bytes.fromhex('b8 00000004 8986 4c010000')
    assert re.findall(r'bolt->r.contents\s*=\s*(\w+)\s*;', branch) == ['CONTENTS_BODY']
    assert re.search(r'bolt->health\s*=\s*5\s*;', branch)
    assert re.search(r'bolt->takedamage\s*=\s*' + damageable + r'\s*;', branch)
assert re.search(r'bolt->r.snapshotCallback\s*=\s*qtrue\s*;', landmine)
assert 'G_NITMOD_RegisterLandmine( bolt );' in landmine
assert 'G_NITMOD_RegisterSatchel( bolt );' in satchel
assert satchel.count('G_NITMOD_ConfigureSatchelDamage( bolt, g_damageweapons.integer );') == 1
assert satchel.index('bolt->takedamage') < satchel.index('G_NITMOD_ConfigureSatchelDamage')
smoke = missile.split('case WP_SMOKE_BOMB:', 1)[1].split('case WP_GRENADE_LAUNCHER:', 1)[0]
assert smoke.count('G_NITMOD_ConfigureSmokeDamage( bolt, g_damageweapons.integer );') == 1
marker = missile.split('case WP_SMOKE_MARKER:', 1)[1].split('case WP_MORTAR_SET:', 1)[0]
assert marker.count('G_NITMOD_ConfigureAirstrikeMarkerDamage( bolt, g_damageweapons.integer );') == 1
for name, following in (('WP_GRENADE_LAUNCHER', 'WP_GRENADE_PINEAPPLE'), ('WP_GRENADE_PINEAPPLE', 'WP_SMOKE_MARKER')):
    branch = missile.split('case ' + name + ':', 1)[1].split('case ' + following + ':', 1)[0]
    assert branch.count('G_NITMOD_ConfigureGrenadeDamage( bolt, g_damageweapons.integer );') == 1
body = main.split('void G_RegisterCvars( void )', 1)[1].split('void G_UpdateCvars', 1)[0]
assert body.count('G_NITMOD_RegisterWeaponConfiguration();') == 1
config = (root / 'src_2.60/game/g_nitmod_config.c').read_text()
assert 'G_NITMOD_RefreshWeaponSnapshot( &state );' in config
assert 'state.panzerRestriction = g_heavyWeaponRestriction.integer' not in config
