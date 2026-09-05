#!/usr/bin/env python3
"""Static contract checks for the reconstructed Nitmod server-command ABI.

The ET VM needs engine traps, so these deterministic checks protect the
wire-level invariants that can be validated without a running game engine.
"""
from __future__ import annotations

import pathlib
import re
import sys
import hashlib
import struct


def read(root: pathlib.Path, relative: str) -> str:
    return (root / relative).read_text(encoding="utf-8")


def require(text: str, pattern: str, description: str) -> None:
    if not re.search(pattern, text, re.MULTILINE | re.DOTALL):
        raise AssertionError(description)


def main() -> None:
    if len(sys.argv) != 2:
        raise SystemExit("usage: test_nitmod_protocol_contract.py <src_2.60>")
    root = pathlib.Path(sys.argv[1])
    protocol = read(root, "game/nitmod_protocol.h")
    server = read(root, "game/g_nitmod_config.c")
    game_main = read(root, "game/g_main.c")
    game_commands = read(root, "game/g_cmds.c")
    game_client = read(root, "game/g_client.c")
    bg_misc = read(root, "game/bg_misc.c")
    bg_pmove = read(root, "game/bg_pmove.c")
    game_public = read(root, "game/bg_public.h")
    client = read(root, "cgame/cg_nitmod_config.c")
    client_helpers = read(root, "cgame/cg_nitmod.c")
    dispatch = read(root, "cgame/cg_servercmds.c")
    ui = read(root, "ui/ui_main.c")
    browser = read(root, "ui/ui_nitmod_browser.c")

    for name, value in {
        "NITMOD_MAX_CONFIGSTRINGS": "655",
        "NITMOD_CONFIGSTRING_CHARS": "1018",
        "NITMOD_PROTOCOL_VERSION": "1",
        "NITMOD_NCS_MODELS": "0",
        "NITMOD_NCS_MODEL_COUNT": "256",
        "NITMOD_NCS_SOUND_COUNT": "256",
        "NITMOD_NCS_SHADER_COUNT": "32",
        "NITMOD_NCS_SKIN_COUNT": "64",
        "NITMOD_NCS_OBJECTIVE_COUNT": "18",
        "NITMOD_NCS_SPAWN_COUNT": "16",
        "NITMOD_NCS_FIRETEAM_COUNT": "12",
        "NITMOD_FEATURE_SPREE_EVENTS": "( 1u << 8 )",
        "NITMOD_FEATURE_HIT_SOUNDS": "( 1u << 9 )",
        "NITMOD_HIT_SOUND_TEAM": "3",
        "NITMOD_HIT_SOUND_HEAD": "4",
    }.items():
        require(protocol, rf"#define\s+{name}\s+{re.escape(value)}(?:\s|/|$)",
                f"{name} no longer has its recovered value {value}")

    # Fixed command layouts: exact token counts, in both serializer and parser.
    cases = {
        "scs": (11, 12, "NITMOD_SimpleConfigCommand"),
        "#": (20, 21, "NITMOD_GameStateCommand"),
        "mes": (5, 6, "NITMOD_MapEndStatsCommand"),
        "tsc": (2, 3, "NITMOD_TeamScoresCommand"),
        "ob": (5, 6, "NITMOD_ObjectiveEventCommand"),
        "ct": (10, 11, "nitrox_ParseChargeTimes"),
    }
    for command, (fields, argc, parser) in cases.items():
        serializer = re.search(rf'va\(\s*"{re.escape(command)}([^\"]*)"', server)
        if not serializer or serializer.group(1).count("%") != fields:
            raise AssertionError(f"server {command} serializer no longer has {fields} fields")
        if command != "ct":
            require(client, rf'{parser}\( void \).*?NITMOD_HasArgumentCount\(\s*"{re.escape(command)}"\s*,\s*{argc}\s*\)',
                    f"client {command} parser does not validate argc={argc}")

    require(client_helpers, r'nitrox_ParseChargeTimes\( void \).*?trap_Argc\(\)\s*!=\s*11',
            "client ct parser does not validate argc=11")
    require(server,
            r'G_NITMOD_SendConfigString\(.*?NITMOD_CONFIGSTRING_COMMAND\s+" %i \\\"%s\\\"\\n"',
            "server ncs serializer no longer has index and quoted value fields")
    require(client,
            r'nitrox_ConfigStringModified\( void \).*?NITMOD_HasArgumentCount\(\s*NITMOD_CONFIGSTRING_COMMAND\s*,\s*3\s*\)',
            "client ncs parser does not validate argc=3")
    require(client,
            r'void nitrox_ProcessNewCS\( int index \) \{\s*const char \*value;\s*int assetIndex;\s*value = NITMOD_ConfigString\( index \);\s*/\* Empty NCS values',
            "empty NCS updates no longer reach the recovered asset/state dispatcher")
    require(dispatch, r'if \( !Q_stricmp\( cmd, "ct" \) \) \{\s*nitrox_ParseChargeTimes\(\);',
            "original-server ct must not require a reconstructed capability handshake")
    require(dispatch, r'if \( !Q_stricmp\( cmd, "tsc" \) \) \{\s*NITMOD_TeamScoresCommand\(\);',
            "original-server tsc must not require a reconstructed capability handshake")
    require(dispatch, r'if \( !Q_stricmp\( cmd, "scs" \) \) \{\s*NITMOD_SimpleConfigCommand\(\);',
            "original scs must be accepted without a reconstruction handshake")
    require(dispatch, r'if \( !strcmp\( cmd, "#" \) \) \{\s*NITMOD_GameStateCommand\(\);',
            "original # settings must be accepted without a reconstruction handshake")
    require(dispatch, r'if \( !Q_stricmp\( cmd, NITMOD_CONFIGSTRING_COMMAND \) \) \{',
            "original NCS receive must not require a reconstruction handshake")
    for feature in ("OBJECTIVES",
                    "MAP_END_STATS", "SPREE_EVENTS", "HIT_SOUNDS"):
        require(dispatch, rf'NITMOD_ServerSupports\(\s*NITMOD_FEATURE_{feature}\s*\)',
                f"dispatch does not capability-gate {feature}")

    require(server,
            r'void nitmod_Announce\(.*?actor < 0.*?type < 1.*?NITMOD_FEATURE_SPREE_EVENTS.*?"nsp %i %i %i"',
            "server no longer validates and capability-gates the recovered announcement tuple")
    require(client,
            r'void NITMOD_SpreeEventCommand\(.*?NITMOD_HasArgumentCount\( "nsp", 4 \).*?CG_NitmodSpreeStart\(actor, detail, type\)',
            "client no longer validates and routes the announcement tuple")
    # Independently compare all message strings with hash-pinned ELF tables.
    data = (root.parent / "original_nitmod_shared_objects_32bit/cgame.mp.i386.so").read_bytes()
    assert hashlib.sha256(data).hexdigest() == "45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f"
    start = struct.unpack_from("<I", data, 32)[0]
    size, count = struct.unpack_from("<HH", data, 46)
    sections = [struct.unpack_from("<10I", data, start + i * size) for i in range(count)]
    def file_offset(address):
        section = next(s for s in sections if s[1] != 8 and s[3] <= address < s[3] + s[5])
        return section[4] + address - section[3]
    hud = read(root, "cgame/cg_nitmod_hud.c")
    # CG_DrawUpperRight's so-called average is stateless, not an EMA.
    assert struct.unpack_from("<f", data, file_offset(0x1000b0))[0] == 0.0
    assert struct.unpack_from("<f", data, file_offset(0xff348))[0] == 0.5
    offset = file_offset(0x1034d4)
    formats = b"Ping %d\0Avg Ping %0.2f\0"
    assert data[offset:offset + len(formats)] == formats
    offset = file_offset(0x44e25)
    assert data[offset:offset + 16] == bytes.fromhex("db442434d8836c24fdffd88b0417fdff")
    require(hud, r'if\(cg_drawPing.integer\).*?CG_NitmodHudPingText\(text, sizeof\(text\), cg.snap->ping, cg_drawPing.integer\).*?DrawLine\(y, text\)',
            "all nonzero ping modes must reach the actual HUD renderer")
    for name, address, count in (("kills", 0x13b2f0, 6), ("losses", 0x13b2e4, 3),
                                 ("multi", 0x13b2d0, 5), ("revives", 0x13b2c0, 4)):
        expected = []
        for pointer in struct.unpack_from(f"<{count}I", data, file_offset(address)):
            offset = file_offset(pointer)
            expected.append(data[offset:data.index(b"\0", offset)].decode("ascii"))
        body = re.search(rf'\*{name}\[\]\s*=\s*\{{(.*?)\}};', hud, re.S)[1]
        assert re.findall(r'"([^"]*)"', body) == expected, name
    require(server,
            r'void NITMOD_SendHitSound\(.*?NITMOD_HIT_SOUND_TEAM.*?NITMOD_HIT_SOUND_HEAD.*?NITMOD_FEATURE_HIT_SOUNDS.*?"nhs %i"',
            "server no longer capability-gates recovered hit-sound classifications")
    require(client,
            r'void NITMOD_PlayHitSound\(.*?"cg_hitSounds".*?"sound/nit/hs\.wav".*?"sound/hitsounds/team\.wav".*?trap_Cvar_Update\( &nitmodHitSounds \).*?void NITMOD_HitSoundCommand\(.*?NITMOD_HasArgumentCount\("nhs", 2\)',
            "client no longer validates hit-sound commands or registers the recovered assets")

    require(game_commands,
            r'NITMOD_CAPABILITIES_COMMAND\s*\).*?trap_Argc\(\)\s*!=\s*3.*?G_NITMOD_ClientCapabilities',
            "server nitcap parser does not require exactly version and capability fields")
    require(game_commands,
            r'NITMOD_CAPABILITIES_COMMAND.*?trap_Argv\( 1, argument.*?NITMOD_ParseProtocolInteger.*?trap_Argv\( 2, argument.*?NITMOD_ParseProtocolUnsigned.*?G_NITMOD_ClientCapabilities',
            "capability fields must be parsed individually before negotiation")
    require(client,
            r'void nitrox_ConfigStringModified\(.*?NITMOD_ParseProtocolInteger.*?index >= NITMOD_MAX_CONFIGSTRINGS.*?NITMOD_ConfigStringModified\( index,',
            "NCS command must validate its numeric index before changing storage")
    require(server,
            r'void G_NITMOD_CacheClientAddress\(.*?cached->address.*?cached->host.*?strchr\( cached->host, \':\' \).*?cached->port\s*=\s*atoi',
            "typed client address cache no longer retains address, host and port")
    require(game_client,
            r'ClientUserinfoChanged.*?Info_ValueForKey\( userinfo, "ip" \).*?G_NITMOD_CacheClientAddress\( ent, s \)',
            "userinfo changes no longer refresh the typed Nitmod address cache")
    require(server,
            r'qboolean NITMOD_ValidateNGuid\(.*?strlen\( nguid \) != 33.*?character >= \'0\'.*?character <= \'9\'.*?checksum % 100 != 0',
            "NGUID validation no longer enforces length, alphanumeric bytes and checksum")
    require(server,
            r'void NITMOD_SendChunkedPrint\(.*?!text \|\| !text\[0\].*?character == \'\\n\'.*?character == \'"\'.*?character == \'\\\\\'.*?trap_SendServerCommand',
            "chunked Nitmod print delivery no longer splits and escapes server commands")
    require(server,
            r'void NITMOD_PlaySoundEvent\(.*?!source \|\| soundIndex <= 0.*?G_TempEntity\( source->r\.currentOrigin, EV_NITMOD_SOUND \).*?event->s\.eventParm = soundIndex',
            "Nitmod spatial sound events no longer preserve the private event/index contract")
    require(game_public,
            r'Original Nitmod transports this as 100.*?EV_NITMOD_SOUND',
            "reconstructed spatial sound event is no longer separated from the original wire ID")
    require(server,
            r'void nitmod_Sound_Global\(.*?G_TempEntity\( vec3_origin, EV_GLOBAL_SOUND \).*?event->s\.eventParm = soundIndex.*?SVF_BROADCAST',
            "Nitmod global sounds no longer use the recovered broadcast event layout")
    require(server,
            r'qboolean NITMOD_BuildFilePath\(.*?directoryLength > 0.*?directory\[directoryLength - 1\] != \'/\'.*?!= \'\\\\\'.*?Q_strcat\( path, pathSize, name \).*?Q_strcat\( path, pathSize, extension \)',
            "Nitmod path construction no longer preserves the recovered separator and suffix behavior")
    require(server,
            r'void nitrox_ClampFloat\(.*?\*value < minimum.*?\*value > maximum.*?void nitrox_ClampInt\(.*?minimum >= 0\.0f.*?maximum >= 0\.0f.*?void nitrox_stripLeadingSpaces\(.*?while\( \*first == \' \' \).*?memmove',
            "typed Nitmod clamp and leading-space helpers no longer preserve their recovered behavior")
    require(game_main,
            r'nitmodSettingsChanged.*?cv->vmCvar == &g_filtercams.*?cv->vmCvar == &g_heavyWeaponRestriction.*?cv->vmCvar == &team_maxPanzers.*?cv->vmCvar == &g_gravity.*?if\( nitmodSettingsChanged \) \{\s*nitmod_RefreshBaseSettings\(\);',
            "typed NCS cvars no longer refresh their protocol snapshots on change")
    if len(re.findall(r'\bnitmod_RefreshBaseSettings\(\);', game_main)) != 2:
        raise AssertionError("Nitmod cvar snapshots must be seeded at init and refreshed on change only")

    require(ui, r'"ui_browserNitmodonly"',
            "UI no longer registers the Nitmod browser filter")
    require(ui, r'"ui_browserNxAConly"',
            "UI no longer registers the NxAC browser filter")
    require(browser, r'Info_ValueForKey\(\s*status\s*,\s*"sv_NxAC"\s*\)',
            "NxAC filter no longer uses the authoritative server-status field")
    require(browser, r'nxacStatus\s*<\s*0\s*\).*?numPlayersOnServers\s*-=\s*clients',
            "pending NxAC queries no longer compensate the repeated player total")
    require(server, r'void G_NITMOD_ResyncEngineConfigStrings\( void \).*?trap_GetConfigstring.*?G_NITMOD_MirrorEngineConfigString',
            "NCS map-start resync no longer mirrors native configstrings")
    game_team = read(root, "game/g_team.c")
    require(game_team,
            r'team_wolf_objective_use.*?trap_SetConfigstring\( self->count, cs \).*?G_NITMOD_MirrorEngineConfigString\( self->count, cs \)',
            "spawn ownership changes no longer reach negotiated NCS clients")
    require(game_team,
            r'objective_Register.*?trap_SetConfigstring\( cs_obj, cs \).*?G_NITMOD_MirrorEngineConfigString\( cs_obj, cs \)',
            "registered spawn targets no longer reach negotiated NCS clients")
    require(game_main, r'G_SpawnEntitiesFromString\(\);.*?InitialServerEntitySetup\(\);.*?G_NITMOD_ResyncEngineConfigStrings\(\);',
            "NCS map-start resync is no longer run after entity spawning")
    require(bg_misc,
            r'void BG_AddPredictableDamage\(.*?ps->damageEvent\+\+;.*?ps->damageYaw\s*=\s*yaw;.*?ps->damagePitch\s*=\s*pitch;.*?ps->damageCount\s*=\s*count;',
            "typed predictable-damage feedback no longer updates every playerState field")
    for count in (50, 25, 15, 10):
        require(bg_pmove, rf'BG_AddPredictableDamage\(\s*{count}\s*,\s*255\s*,\s*255\s*,\s*pm->ps\s*\)',
                f"fall-damage tier {count} no longer produces predicted damage feedback")
    game_weapon = read(root, "game/g_weapon.c")
    game_combat = read(root, "game/g_combat.c")
    require(game_weapon,
            r'usedSyringe && g_gamestate\.integer == GS_PLAYING\s*\)\s*\{\s*ent->client->sess\.aWeaponStats\[WS_SYRINGE\]\.hits\+\+',
            "syringe statistics no longer count only successful revives")
    require(game_combat,
            r'G_NITMOD_ApplySniperWarHeadshot\(.*?g_war", 0 \) != 2.*?mod != MOD_K43_SCOPE && mod != MOD_GARAND_SCOPE.*?NITMOD_SendHitSound\( attacker->s.number, NITMOD_HIT_SOUND_HEAD \);',
            "head-hit feedback must remain confined to the typed scoped sniper-war branch")
    require(game_combat,
            r'if\( self->client->ps.pm_type == PM_DEAD \|\| g_gamestate.integer == GS_INTERMISSION \) \{\s*return;\s*\}.*?self->client->ps.pm_type = PM_DEAD;.*?NITMOD_UpdateKillSpree\( self, attacker \)',
            "kill-spree update must follow the duplicate-death/intermission guard")
    if game_combat.count("NITMOD_UpdateKillSpree( self, attacker );") != 1:
        raise AssertionError("player death must update the kill spree exactly once")
    missile = read(root, "game/g_missile.c")
    require(game_client, r'client->airOutTime = NITMOD_AirDeadline\( level.time, 0u \);',
            "spawn must share the air deadline calculation without enabling new skills")
    active = read(root, "game/g_active.c")
    for assignment in ('cg_pmove.nitmodWarMode = NITMOD_SimpleConfig()->war;',
                       'cg_pmove.nitmodNoReload = (unsigned int)NITMOD_SimpleConfig()->noReload;'):
        assert read(root, "cgame/cg_predict.c").count(assignment) == 2, "both prediction paths need refill settings"
    for assignment in ('pm.nitmodWarMode = G_NITMOD_ConfiguredWarMode();',
                       'pm.nitmodNoReload = (unsigned int)G_NITMOD_ConfiguredNoReload();'):
        assert active.count(assignment) == 2, "both server paths need refill settings"
    assert 'simple.noReload = G_NITMOD_ConfiguredNoReload();' in server
    require(active, r'client->pmext.airleft = NITMOD_AirRemaining\( ent->client->airOutTime, level.time \);',
            "movement must use checked signed remaining air")
    require(active, r'if\(level.match_pause != PAUSE_NONE\).*?NITMOD_ShiftAirDeadline\( ent->client->airOutTime, time_delta \)',
            "match pause must preserve remaining air through checked deadline shifts")
    require(read(root, "game/g_active.c"),
            r'drowningDamage = G_NITMOD_UpdateClientAir\( ent, level.time, 0u \);.*?if\( ent->client->noclip \).*?return;.*?MOD_WATER',
            "air adapter must preserve noclip return and keep unreconstructed skill activation off")
    players = read(root, "cgame/cg_players.c")
    require(players, r'NITMOD_DecodeClientSkills\(v, newInfo.skill, newInfo.nitmodSkillLevels\)',
            "original display skills must be separated from native ability indices")
    require(read(root, "cgame/cg_nitmod_config.c"),
            r'nativeLevels\[i\] = levels\[i\] < NUM_SKILL_LEVELS \? levels\[i\] : NUM_SKILL_LEVELS - 1',
            "native skill consumers must retain their supported index bounds")
    require(players, r'if\( newInfo.skill\[i\] > 0 && newInfo.skill\[i\] < NUM_SKILL_LEVELS \).*?cg_skillRewards\[ i \]\[ newInfo.skill\[i\]-1 \]',
            "skill rewards must check both table bounds")
    commands = read(root, "cgame/cg_servercmds.c")
    if commands.count('int threshold = NITMOD_ClientSkillNextThreshold(i, level);') != 2:
        raise AssertionError("both XP displays must bound next-threshold indices")
    require(read(root, "cgame/cg_nitmod_config.c"),
            r'level < NUM_SKILL_LEVELS - 1 \? skillLevels\[level \+ 1\] : -1',
            "native next-threshold lookup must retain its index bound")
    require(missile, r'qboolean G_ExplodeSatchels\(.*?G_NITMOD_ExplodeSatchels\( ent, G_ExplodeMissile \) \? qtrue : qfalse;',
            "satchel detonation must use the mutation-safe registry adapter")
    require(missile, r'void G_FadeItems\(.*?MOD_SATCHEL.*?G_NITMOD_FadeSatchels\( ent, G_FreeEntity \);.*?MOD_LANDMINE.*?G_NITMOD_FadeLandmines\( ent, NITMOD_FreeFadedLandmine \);',
            "owner cleanup must dispatch through typed registries")
    require(read(root, "game/g_nitmod_map_cleanup.c"), r'void NITMOD_FreeFadedLandmine\(.*?team < 2.*?G_FindMapEntityData.*?G_FreeMapEntityData.*?G_FreeEntity\( mine \);',
            "mine cleanup must remove both team markers before freeing")
    require(missile, r'case WP_LANDMINE:.*?G_NITMOD_RegisterLandmine\( bolt \)',
            "thrown mines must enter the landmine registry")
    require(missile, r'G_CountTeamLandmines \( team_t team \).*?G_NITMOD_CountTeamLandmines\( team, team_maxLandmines.integer \)',
            "team count must use the registry with the live original Nitmod limit")
    require(read(root, "game/g_misc.c"),
            r'void landmine_setup\(.*?G_FreeEntity\( ent \);\s*return;.*?G_NITMOD_RegisterLandmine\( ent \);\s*trap_LinkEntity\( ent \);',
            "map mines must register only after successful placement")
    require(read(root, "game/g_utils.c"),
            r'void G_FreeEntity\(.*?G_NITMOD_UnregisterLandmine\( ed \);.*?if\(ed->free\)',
            "mine removal must precede free callbacks")
    require(missile, r'case WP_SATCHEL:.*?G_NITMOD_RegisterSatchel\( bolt \)',
            "satchel creation must register the entity")
    require(missile, r'G_NITMOD_UnregisterSatchel\( ent \);\s*G_NITMOD_UnregisterLandmine\( ent \);\s*ent->s.eType = ET_GENERAL;',
            "explosion must unregister before converting the missile to an event")
    require(read(root, "game/g_utils.c"),
            r'void G_FreeEntity\(.*?G_NITMOD_UnregisterSatchel\( ed \);.*?if\(ed->free\)',
            "free must unregister before callbacks or entity reuse")
    require(game_main, r'G_NITMOD_ResetEntityLists\(\);\s*memset\( g_entities',
            "map initialization must reset borrowed entity pointers")
    require(missile, r'G_FindSatchel\(gentity_t\* ent\).*?return G_NITMOD_FindSatchel\( ent \);',
            "satchel lookup must use creation-ordered registry")
    client_main = read(root, "cgame/cg_main.c")
    require(client_main, r'&cg_weapAltReloads, "cg_weapAltReloads", "0", CVAR_ARCHIVE',
            "secondary reload preference must default off and persist")
    require(client_main, r'cv->vmCvar == &cg_weapAltReloads',
            "preference changes must trigger userinfo publication")
    require(client_main, r'void CG_setClientFlags\(void\).*?if\(cg.demoPlayback\) return;.*?NITMOD_EncodeReloadPreferences.*?\(NITMOD_UsesOriginalProtocol\(\) \|\| NITMOD_ServerSupports\(NITMOD_FEATURE_RELOAD_PREFS\)\) \? cg_weapAltReloads.integer : 0',
            "secondary reload requires the original protocol or a capability and must be demo-safe")
    require(client_main, r'CG_ParseWolfinfo\(\);.*?CG_setClientFlags\(\);',
            "initial preferences must be republished once the server protocol is known")
    require(client, r'nitmodServerCapabilities = capabilities & NITMOD_FEATURES_CLIENT;\s*CG_setClientFlags\(\);',
            "capability acknowledgement/revocation must republish preferences")
    require(client, r'protocolVersion != NITMOD_PROTOCOL_VERSION.*?nitmodServerCapabilities = 0;\s*CG_setClientFlags\(\);',
            "protocol mismatch must withdraw the preference flag")
    require(game_client, r'client->pers.bAltReloadAux = qfalse;',
            "bot preference must reset deterministically")
    require(game_client, r'client->pers.bAltReloadAux =\s*\(client->pers.clientFlags & NITMOD_CGF_ALT_RELOAD\) != 0;',
            "server userinfo must decode the same named preference bit")
    prediction = read(root, "cgame/cg_predict.c")
    pmove_source = read(root, "game/bg_pmove.c")
    require(pmove_source, r'reloadRequested = \(qboolean\)NITMOD_ManualReloadRequested\(&pm->cmd, pm->nitmodReloadPreferenceFlags\);',
            "active reload input must use the same synchronized preference predicate as the recovered policy")
    reload_begin = pmove_source.split("static void PM_BeginWeaponReload( int weapon ) {", 1)[1].split("static void PM_ReloadClip", 1)[0]
    require(reload_begin, r'WEAPON_READY\s*\).*?weaponTime = NITMOD_AddWeaponTime32\(pm->ps->weaponTime, reloadTime\);',
            "READY reload must reproduce original 32-bit addition without C signed overflow")
    require(reload_begin, r'else if\( pm->ps->weaponTime < reloadTime\).*?pm->ps->weaponTime = reloadTime;',
            "firing reload overlap must use original compare/store without an overflowing difference")
    if "reloadTime - pm->ps->weaponTime" in reload_begin:
        raise AssertionError("firing reload overlap must not subtract signed timer extremes")
    require(reload_begin, r'!NITMOD_ReloadUsesOuterClipGate\(weapon\).*?ammoclip\[item->giAmmoIndex\] >= GetAmmoTableData\(weapon\)->maxclip',
            "reviewed light/akimbo identities must use outer clip gating; others retain the native inner veto")
    require(reload_begin, r'!NITMOD_ReloadStateAllowed\(pm->ps->weaponstate\).*?return;.*?WP_CARBINE.*?BG_FindItemForWeapon.*?leanf.*?BG_AnimScriptEvent',
            "active native reload must accept mapped normal/alternate firing before inventory and scoped lean checks")
    require(reload_begin, r'if\(pm->ps->leanf && !NITMOD_ReloadWeaponEligible\(weapon\)\)\s*return;',
            "lean veto must be retained only for identities outside the reviewed reload mapping")
    require(reload_begin, r'!NITMOD_ReloadStateAllowed.*?NITMOD_ResetReloadWithoutReserve\(pm->ps, BG_FindAmmoForWeapon\(pm->ps->weapon\)\).*?return;.*?WP_CARBINE',
            "current-weapon reserve reset must follow the state gate and precede target restrictions")
    require(reload_begin, r'leanf.*?NITMOD_ReloadBodyEventRequired\(weapon\).*?ANIM_ET_RELOADPRONE.*?ANIM_ET_RELOAD.*?PM_ContinueWeaponAnim.*?EV_FILL_CLIP',
            "shared body predicate must not suppress later first-person timing or predictable reload event")
    require(reload_begin, r'pm->skill\[SK_LIGHT_WEAPONS\] >= 2 && BG_isLightWeaponSupportingFastReload\( weapon \).*?reloadTime = NITMOD_ScaleFastReloadDuration\(reloadTime\);',
            "exact fast-reload arithmetic must retain native skill and weapon eligibility")
    raise_finish = pmove_source.split("static int PM_FinishWeaponRaise( void ) {", 1)[1].split("void PM_BeginWeaponChange", 1)[0]
    require(raise_finish, r'weaponTime > 0 \|\| pm->ps->weaponDelay > 0.*?WEAPON_RAISING\s*\).*?weaponstate = WEAPON_READY;.*?PM_StartWeaponAnim\(PM_IdleAnimForWeapon.*?WEAPON_RAISING_TORELOAD.*?weaponstate = WEAPON_READY;\s*PM_BeginWeaponReload',
            "raise completion must guard timers and reset READY before native reload dispatch")
    weapon_loop = pmove_source.split("void PM_Weapon(", 1)[1]
    require(weapon_loop, r'PM_BeginWeaponChange.*?if\( PM_ProcessWeaponTransitions\(\) \) return;.*?WP_NONE',
            "weapon frame must run the transition stage after change requests and before firing checks")
    transitions = pmove_source.split("static int PM_ProcessWeaponTransitions( void ) {", 1)[1].split("static void PM_SwitchIfEmpty", 1)[0]
    require(transitions, r'weaponDelay > 0.*?return 1;.*?PM_CheckForReload.*?weaponTime > 0 \|\| pm->ps->weaponDelay > 0.*?return 1;.*?PM_FinishWeaponReload.*?PM_FinishWeaponChange.*?return 1;.*?PM_FinishWeaponRaise.*?return 0;',
            "extracted transition stage must preserve delay, request, timers, reload, drop and raise ordering")
    change = pmove_source.split("void PM_BeginWeaponChange(", 1)[1].split("PM_FinishWeaponChange", 1)[0]
    require(change, r'PMF_RESPAWNED.*?COM_BitCheck.*?!NITMOD_WeaponChangeStateAllowed\(pm->ps->weaponstate\).*?weaponDelay.*?grenadeTimeLeft.*?nextWeapon = newweapon',
            "weapon switch must preserve ordered native guards and add original reload-state exclusion")
    require(change, r'switchtime = 250;.*?NITMOD_ScopeSwitchDuration\( oldweapon, newweapon, &switchtime \);.*?NITMOD_DeploySwitch',
            "drop must use shared scope duration before other family-specific effects")
    finish_change = pmove_source.split("static void PM_FinishWeaponChange( void ) {", 1)[1]
    require(finish_change, r'oldweapon = pm->ps->weapon;\s*newweapon = NITMOD_CommitWeaponChange\( pm->ps \);\s*pm->pmext->silencedSideArm = NITMOD_PistolModeFlags\(newweapon, pm->pmext->silencedSideArm\);\s*pm->pmext->silencedSideArm = NITMOD_RifleGrenadeModeFlags\(newweapon, pm->pmext->silencedSideArm\);\s*switch\(newweapon\)',
            "shared finish must preserve old weapon before committing target and raising state")
    require(change, r'NITMOD_PistolSwitch\(oldweapon, newweapon, &pistolSwitch\).*?switchtime = pistolSwitch.dropTime;.*?altSwitchAnim = pistolSwitch.dropAltAnimation;',
            "begin must use the pistol drop plan")
    require(finish_change, r'NITMOD_PistolModeFlags.*?NITMOD_WeaponChangeNeedsRaise.*?NITMOD_PistolSwitch\(oldweapon, newweapon, &pistolSwitch\).*?switchtime = pistolSwitch.raiseTime;.*?altSwitchAnim = pistolSwitch.raiseAltAnimation;',
            "finish must commit mode before same-weapon return and use pistol raise plan afterwards")
    require(change, r'NITMOD_RifleGrenadeDrop\(pm->ps, oldweapon, newweapon, &grenadeReloadWeapon\).*?switchtime = 0;.*?if\( grenadeReloadWeapon != WP_NONE \) PM_ReloadClip\( grenadeReloadWeapon \);',
            "grenade drop must retain the native transfer boundary and zero duration")
    require(finish_change, r'NITMOD_RifleGrenadeModeFlags.*?NITMOD_WeaponChangeNeedsRaise.*?NITMOD_RifleGrenadeRaise\(pm->ps, oldweapon, newweapon, &rifleRaise\).*?switchtime = rifleRaise.duration;.*?doSwitchAnim = rifleRaise.animate;.*?altSwitchAnim = qtrue;',
            "grenade finish must preserve remembered mode and the empty-clip animation skip")
    require(finish_change, r'NITMOD_CommitWeaponChange.*?!NITMOD_WeaponChangeNeedsRaise\(oldweapon, newweapon\).*?return;.*?switchtime = 250;.*?weaponTime = NITMOD_AddWeaponTime32\(pm->ps->weaponTime, switchtime\);.*?BG_UpdateConditionValue',
            "knife/smoke reselection must reach existing raise timing and animation condition update after commit")
    require(finish_change, r'switchtime = 250;\s*NITMOD_ScopeSwitchDuration\( oldweapon, newweapon, &switchtime \);.*?NITMOD_DeploySwitch',
            "raise must use the same scope duration before other family-specific effects")
    require(change, r'case WP_MORTAR_SET:.*?EF_PRONE.*?return;.*?waterlevel == 3.*?return;.*?NITMOD_DeploySwitch\(oldweapon, newweapon, &deploySwitch\).*?switchtime = 0;.*?if\( deploySwitch.captureDirection \).*?VectorCopy\( pml.forward, axis\[0\] \);.*?VectorCopy\( pml.right, axis\[2\] \);.*?CrossProduct\( axis\[0\], axis\[2\], axis\[1\] \);.*?AxisToAngles\( axis, pm->pmext->mountedWeaponAngles \);',
            "deployment must retain mortar guards and gated native direction construction")
    if change.count('AxisToAngles( axis, pm->pmext->mountedWeaponAngles );') != 1:
        raise AssertionError("deployment direction should have exactly one shared implementation")
    require(finish_change, r'NITMOD_DeploySwitch\(oldweapon, newweapon, &deploySwitch\).*?switchtime = deploySwitch.raiseTime;.*?altSwitchAnim = deploySwitch.raiseAltAnimation;.*?weaponTime = NITMOD_AddWeaponTime32\(pm->ps->weaponTime, switchtime\);',
            "deployment finish must consume the typed raise plan")
    active = read(root, "game/g_active.c")
    if prediction.count('cg_pmove.nitmodReloadPreferenceFlags = CG_NITMOD_ReloadPreferenceFlags();') != 2:
        raise AssertionError("both client Pmove setup paths must refresh preferences")
    if active.count('pm.nitmodReloadPreferenceFlags = NITMOD_EncodeReloadPreferences(0,') != 2:
        raise AssertionError("both server Pmove setup paths must refresh preferences")
    require(client_main, r'unsigned int CG_NITMOD_ReloadPreferenceFlags\( void \).*?\(NITMOD_UsesOriginalProtocol\(\) \|\| NITMOD_ServerSupports\(NITMOD_FEATURE_RELOAD_PREFS\)\) \? cg_weapAltReloads.integer : 0',
            "prediction preferences must match userinfo capability gating")
    capability_handler = server.split("void G_NITMOD_ClientCapabilities(", 1)[1].split("const char *G_NITMOD_ConfigString", 1)[0]
    if "G_NITMOD_ResetClient(" in capability_handler:
        raise AssertionError("capability negotiation must not reset gameplay state")
    require(game_client, r'void ClientDisconnect\(.*?G_NITMOD_ResetClient\( clientNum \)',
            "disconnect must clear Nitmod state before a client slot can be reused")


if __name__ == "__main__":
    main()
