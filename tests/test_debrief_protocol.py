from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CGAME = (ROOT / "src_2.60/cgame/cg_debriefing.c").read_text(encoding="utf-8")
GAME = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
LOCAL = (ROOT / "src_2.60/cgame/cg_local.h").read_text(encoding="utf-8")
MEDIA = (ROOT / "src_2.60/cgame/cg_main.c").read_text(encoding="utf-8")
ORIGINAL = (ROOT / "src_nitmod_decompiled/cgame/sorted/cgame_client.c").read_text(encoding="utf-8")
for shader in ("hr", "head", "rarm", "larm", "torso", "legs"):
    path = '"gfx/hr/' + shader + '"'
    assert path in MEDIA and path in ORIGINAL, path
assert "{ HR_HEAD, HR_ARMS, HR_ARMS, HR_BODY, HR_LEGS }" in CGAME
assert "{ HR_HEAD, HR_BODY, HR_ARMS, HR_LEGS }" in CGAME
assert "&debriefHitRegionToggle," in CGAME
assert "cgs.dbShowHitRegions = !cgs.dbShowHitRegions" in CGAME
assert "cgs.dbHitRegionPercent[layers[i]] / 100.f" in CGAME
assert "No hit-region data" in CGAME


def require(source: str, token: str, message: str) -> None:
    if token not in source:
        raise AssertionError(message)


require(CGAME, 'va( "imhr %i", cgs.dbSelectedClient )', "cgame does not request original imhr data")
require(CGAME, '!Q_stricmp( cmd, "imhr" )', "cgame does not dispatch original imhr replies")
require(CGAME, "trap_Argc() != HR_NUM_HITREGIONS * 2 + 1", "imhr tuple arity is not enforced")
require(CGAME, "CG_Debriefing_ParseFloatArg", "imhr percentages are not strictly parsed")
require(CGAME, "memcpy( cgs.dbHitRegionHits, hits", "imhr values are not committed atomically")
require(CGAME, "memcpy( cgs.dbWeaponStats, next", "imws values are not committed atomically")
require(CGAME, "trap_Argc() != count * 2 + 1", "impkd arity is not enforced")
require(CGAME, "trap_Argc() != count + 1", "imwa arity is not enforced")
require(CGAME, "NITMOD_UsesOriginalProtocol() ? cgs.maxclients : MAX_CLIENTS", "original server slot count is ignored")
requests = CGAME.split("void CG_Debriefing_InfoRequests( void ) {", 1)[1].split("qboolean CG_Debriefing_Draw", 1)[0]
assert requests.index('"imws %i"') < requests.index('"imhr %i"') < requests.index('"score"')
region_stage = requests.split("if( !cgs.dbHitRegionsRecieved", 1)[1].split("}", 1)[0]
assert "return;" not in region_stage, "optional imhr must not introduce a blocking request stage"
# Full-module received-flag matrix in check_debrief_pages.h verifies scores
# remain reachable without imhr. Counting unrelated guard returns is brittle.
require(CGAME, "cgs.dbSelectedClient >= MAX_CLIENTS", "selected-client upper bound is unsafe")
require(CGAME, "buffer[offset] == '\\0'", "chat edit width scan still compares a pointer with a character")
require(CGAME, "ci->rank >= NUM_EXPERIENCE_LEVELS", "debrief rank lookup is not bounds checked")
require(LOCAL, "dbHitRegionHits[HR_NUM_HITREGIONS]", "typed hit-region counters are missing")
require(LOCAL, "dbHitRegionPercent[HR_NUM_HITREGIONS]", "typed hit-region percentages are missing")

require(GAME, "void Cmd_IntermissionHitRegions_f", "qagame imhr producer is missing")
require(GAME, 'Q_strncpyz( buffer, "imhr "', "qagame does not emit the original imhr command")
require(GAME, "pers.playerStats.hitRegions[i]", "qagame imhr is not sourced from typed player stats")
require(GAME, "clientNum >= MAX_CLIENTS", "qagame intermission client bound is unsafe")
require(GAME, '!Q_stricmp( cmd, "imhr" )', "qagame does not dispatch imhr requests")

print("debrief protocol contract: ok")

# Original live status HUD: source contract and shader provenance.
hud = (ROOT / "src_2.60/cgame/cg_nitmod_hud.c").read_text()
draw = (ROOT / "src_2.60/cgame/cg_draw.c").read_text()
for path in ("sprites/shield", "gfx/flakjacket_axis", "ui/assets/filter_lives.tga",
             "icons/iconw_binoculars_1_select.tga", "sprites/uniform_axis", "sprites/uniform_allied"):
    assert '"' + path + '"' in hud and '"' + path + '"' in ORIGINAL
assert 'CG_NitmodDrawActivePowerups();' in draw
assert 'if(!cg.snap || !NITMOD_UsesOriginalProtocol()) return;' in hud
assert 'if(ps->powerups[5] || ps->powerups[6])' in hud
assert 'else if(ps->powerups[7])' in hud
assert 'ps->persistant[7] == TEAM_AXIS' in hud
assert 'if(disguiseClass < NUM_PLAYER_CLASSES)' in hud
