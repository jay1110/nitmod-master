from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
WEAPON = (ROOT / "src_2.60" / "game" / "g_weapon.c").read_text(encoding="utf-8")
COMBAT = (ROOT / "src_2.60" / "game" / "g_combat.c").read_text(encoding="utf-8")
TRIGGER = (ROOT / "src_2.60" / "game" / "g_trigger.c").read_text(encoding="utf-8")
VOTE = (ROOT / "src_2.60" / "game" / "g_vote.c").read_text(encoding="utf-8")
UI = (ROOT / "src_2.60" / "ui" / "ui_main.c").read_text(encoding="utf-8")
UI_DESCRIPTION = (ROOT / "src_2.60" / "ui" / "ui_nitmod_description.c").read_text(encoding="utf-8")
UI_GAMEINFO = (ROOT / "src_2.60" / "ui" / "ui_gameinfo.c").read_text(encoding="utf-8")
CGAME = (ROOT / "src_2.60" / "cgame" / "cg_nitmod_config.c").read_text(encoding="utf-8")
CGMAIN = (ROOT / "src_2.60" / "cgame" / "cg_main.c").read_text(encoding="utf-8")
CGSERVER = (ROOT / "src_2.60" / "cgame" / "cg_servercmds.c").read_text(encoding="utf-8")
LOADPANEL = (ROOT / "src_2.60" / "cgame" / "cg_loadpanel.c").read_text(encoding="utf-8")
UI_STATUS = (ROOT / "src_2.60" / "ui" / "ui_nitmod_status.c").read_text(encoding="utf-8")
GAME_CONFIG = (ROOT / "src_2.60" / "game" / "g_nitmod_config.c").read_text(encoding="utf-8")
GAME_CVARS = (ROOT / "src_2.60" / "game" / "g_nitmod_legacy_cvars.c").read_text(encoding="utf-8")
GAME_MAIN = (ROOT / "src_2.60" / "game" / "g_main.c").read_text(encoding="utf-8")


def run():
    artillery = WEAPON[WEAPON.index("void Weapon_Artillery"):WEAPON.index("G_NITMOD_ConsumeFieldOpsSupport", WEAPON.index("void Weapon_Artillery"))]
    assert 'G_NITMOD_LegacyCvarInteger("g_TDMOptions", 0) & 4' in artillery
    assert 'G_NITMOD_LegacyCvarInteger("g_DMOptions", 0) & 32' in artillery
    assert 'G_NITMOD_LegacyCvarInteger("g_DMOptions", 0) & 1' in COMBAT
    assert 'va("hpb %i", bonus)' in COMBAT
    assert 'G_NITMOD_LegacyCvarInteger("g_DMOptions", 0) & 128' in TRIGGER
    assert "G_FreeEntity(self);" in TRIGGER
    assert "static qboolean UI_SelectedNetGameType" in UI
    assert "static qboolean UI_GameTypeForCatalogRow" in UI
    assert 'va("callvote gametype %i\\n", game )' in UI
    assert 'va("ref gametype %i\\n", game )' in UI
    assert "BG_NitmodGametypeName(gametype, qfalse)" in VOTE
    assert "G_GametypeName(g_gametype.integer)" in VOTE
    assert "static qboolean UI_DescriptionGameType" in UI_DESCRIPTION
    assert "text=game==GT_WOLF_LMS" in UI_DESCRIPTION
    assert "uiInfo.gameTypes[row].gameTypeDescription" in UI_DESCRIPTION
    assert "static void UI_AddWolfMpModes" in UI_GAMEINFO
    assert UI_GAMEINFO.count("UI_AddWolfMpModes(&uiInfo.mapList[uiInfo.mapCount])") >= 2
    assert 'trap_Cvar_SetValue( "g_gametype", game )' in UI
    assert 'va("rcon g_gametype %i\\n", game )' in UI
    assert "else if(!UI_SelectedNetGameType(&game)) return 0;" in UI
    assert 'if(singlePlayer) game = uiInfo.gameTypes[ui_gameType.integer].gtEnum;' in UI
    assert 'nitmodGameState.tdmOptions & 4' in CGAME
    assert "cgs.gametype == GT_WOLF_TDM" in CGMAIN
    assert "cgs.gametype == GT_WOLF_DM" in CGMAIN
    assert "cgs.gametype == GT_WOLF_TDM" in LOADPANEL
    assert "cgs.gametype == GT_WOLF_DM" in LOADPANEL
    assert 'value < GT_WOLF || value >= GT_MAX_GAME_TYPE' in CGSERVER
    assert 'NITMOD_ParseProtocolFloat(Info_ValueForKey(info, "timelimit")' in CGSERVER
    assert 'BG_NitmodGametypeName(gametype, qfalse)' in UI_STATUS
    assert 'state.tdmOptions = G_NITMOD_LegacyCvarInteger( "g_TDMOptions", 0 )' in GAME_CONFIG
    assert 'state.adrenaline = G_NITMOD_LegacyCvarInteger( "g_adrenaline", 0 )' in GAME_CONFIG
    assert 'state.keepAwards = G_NITMOD_LegacyCvarInteger( "jp_keepAwards", 0 )' in GAME_CONFIG
    assert 'simple.missileCams = G_NITMOD_LegacyCvarInteger( "g_missileCams", 0 )' in GAME_CONFIG
    assert 'simple.misc = G_NITMOD_LegacyCvarInteger( "g_misc", 0 )' in GAME_CONFIG
    assert 'simple.proneDelay = G_NITMOD_LegacyCvarInteger( "n_proneDelay", 0 )' in GAME_CONFIG
    assert 'simple.crouchStandDelay = G_NITMOD_LegacyCvarInteger( "n_crouchStandDelay", 0 )' in GAME_CONFIG
    assert 'simple.standCrouchDelay = G_NITMOD_LegacyCvarInteger( "n_standCrouchDelay", 0 )' in GAME_CONFIG
    assert '{{0},"g_adrenaline","0",0}, {{0},"jp_keepAwards","0",0}' in GAME_CVARS
    assert 'qboolean G_NITMOD_UpdateLegacyGameplayCvars(void)' in GAME_CVARS
    assert 'G_NITMOD_LegacyCvarPublishesSnapshot' in GAME_CVARS
    for cvar in ("g_missileCams", "g_misc", "n_proneDelay", "n_dynamiteTimer",
                 "n_crouchStandDelay", "n_standCrouchDelay", "g_adrenaline",
                 "jp_keepAwards", "g_TDMOptions"):
        assert f'"{cvar}"' in GAME_CVARS
    assert 'if(G_NITMOD_UpdateLegacyGameplayCvars())' in GAME_MAIN
    teammate_message = WEAPON.index("You cannot defuse a teammate's dynamite!")
    armed_dynamite = WEAPON[teammate_message - 500:teammate_message + 500]
    assert 'G_NITMOD_LegacyCvarInteger("g_misc", 0) & 1' in armed_dynamite
    assert "traceEnt->parent != ent" in armed_dynamite
    assert armed_dynamite.index('g_misc') < armed_dynamite.index('traceEnt->timestamp')
    assert 'gametype >= 0 && gametype < GT_MAX_GAME_TYPE' in UI_STATUS


if __name__ == "__main__":
    run()
    print("Nitmod cross-module mode runtime checks passed")
