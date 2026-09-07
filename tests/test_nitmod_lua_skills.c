/* Reuse the engine boundary of the Lua fixture, replacing its skill doubles
 * with production g_stats, g_session and score/player-state implementations. */
#define main UnusedBindingFixture
#define G_AddSkillPoints FixtureAddSkill
#define G_LoseSkillPoints FixtureLoseSkill
#define G_CalcRank FixtureCalcRank
#define BG_PlayerStateToEntityState FixturePlayerState
#define Q_vsnprintf FixtureVsnprintf
#include "test_nitmod_lua.c"
#undef main
#undef G_AddSkillPoints
#undef G_LoseSkillPoints
#undef G_CalcRank
#undef BG_PlayerStateToEntityState
#undef Q_vsnprintf
vmCvar_t g_gamestate,g_gametype,g_debugSkills;
static int disabled,ceiling=-1,granted,war,adrenClasses=2,adrenOptions;
int G_NITMOD_LegacyCvarInteger(const char *name,int fallback) {
    if(!strcmp(name,"n_noSkillUpgrades")) return disabled;
    if(!strcmp(name,"g_maxXP")) return ceiling;
    if(!strcmp(name,"g_war")) return war;
    if(!strcmp(name,"g_adrenClasses")) return adrenClasses;
    if(!strcmp(name,"g_adrenaline")) return adrenOptions;
    return fallback;
}
float G_NITMOD_LegacyCvarValue(const char *name,float fallback) { return fallback; }
void trap_PbStat(int n,char *category,char *value) { assert(n==3); }
int trap_RealTime(qtime_t *time) { memset(time,0,sizeof(*time));return 0; }
qboolean AddWeaponToPlayer(gclient_t *c,weapon_t weapon,int ammo,int clip,qboolean current) { ++granted;return qtrue; }
static gclient_t clients[MAX_CLIENTS];
static void Start(const char *script,float xp) {
    G_NITMOD_LuaShutdown(0);memset(clients,0,sizeof(clients));memset(&level,0,sizeof(level));
    level.clients=clients;level.maxclients=4;g_entities[3].client=clients+3;g_entities[3].s.number=3;
    clients[3].pers.connected=CON_CONNECTED;clients[3].sess.sessionTeam=TEAM_AXIS;
    clients[3].ps.persistant[PERS_TEAM]=TEAM_AXIS;clients[3].sess.skillpoints[2]=xp;
    level.teamXP[2][0]=xp;level.teamScores[TEAM_AXIS]=(int)xp;
    g_gamestate.integer=GS_PLAYING;g_gametype.integer=GT_WOLF;
    modules="test.lua";acl="";source=script;changed=frames=granted=0;
    G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
}
int main(void) {
    int before;
    /* Offsets used by original G_ResetXP and its metadata-only spawn wrapper. */
    assert(offsetof(playerState_t,weapons)==0x3d4);
    assert(offsetof(playerState_t,teamNum)==0x420);
    assert(offsetof(playerState_t,stats)+STAT_PLAYER_CLASS*sizeof(int)==0xe4);
    assert(offsetof(playerState_t,powerups)+PW_FIRE*sizeof(int)==0x158);
    Start("function et_SetPlayerSkill(c,s) assert(c==3 and s==2); et.trap_Cvar_Set('frame','1') end; function et_UpgradeSkill(c,s) assert(c==3 and s==2); et.trap_Cvar_Set('init','1') end; function et_RunFrame() et.G_AddSkillPoints(3,2,10) end",195);
    clients[3].sess.skill[2]=4;before=inits;G_NITMOD_LuaFrame(1);
    assert(clients[3].sess.skillpoints[2]==205 && clients[3].sess.skill[2]==5 && clients[3].sess.nitmodSkillMasks[2]==62);
    assert(clients[3].ps.persistant[PERS_SCORE]==205 && clients[3].sess.rank==5 && changed==1 && frames==1 && inits==before+1);
    source="function et_SetPlayerSkill(c,s) assert(c==3 and s==2); et.trap_Cvar_Set('frame','1') end; function et_UpgradeSkill(c,s) et.trap_Cvar_Set('init','1') end; function et_RunFrame() et.G_LoseSkillPoints(3,2,10) end";
    G_NITMOD_LuaShutdown(0);G_NITMOD_LuaInit(0,0,0);G_NITMOD_LuaFrame(2);
    assert(clients[3].sess.skillpoints[2]==195 && clients[3].sess.skill[2]==4 && clients[3].sess.nitmodSkillMasks[2]==30);
    assert(clients[3].ps.persistant[PERS_SCORE]==195 && clients[3].sess.rank==4 && changed==2 && frames==2 && inits==before+2);
    assert(level.teamXP[2][0]==195 && level.teamScores[TEAM_AXIS]==195);
    /* Original downgrade upgrades/userinfo only for fully connected clients. */
    Start("function et_SetPlayerSkill() et.trap_Cvar_Set('frame','1') end; function et_UpgradeSkill() error('connecting client upgrade') end; function et_RunFrame() et.G_LoseSkillPoints(3,2,10) end",205);
    clients[3].pers.connected=CON_CONNECTING;clients[3].sess.skill[2]=5;
    before=errors;G_NITMOD_LuaFrame(1);
    assert(clients[3].sess.skillpoints[2]==195 && clients[3].sess.skill[2]==4 && frames==1 && !changed && errors==before);
    /* Returning minus one consumes evaluation, not the earlier XP debit. */
    Start("function et_SetPlayerSkill() return -1 end; function et_RunFrame() et.G_LoseSkillPoints(3,2,30) end",205);
    clients[3].sess.skill[2]=5;clients[3].sess.nitmodSkillMasks[2]=62;G_NITMOD_LuaFrame(1);
    assert(clients[3].sess.skillpoints[2]==175 && clients[3].sess.skill[2]==5 && clients[3].sess.nitmodSkillMasks[2]==62 && !changed);
    /* An error is counted, restores the Lua stack and permits stock behavior. */
    Start("function et_SetPlayerSkill() error('skill failure') end; function et_RunFrame() et.G_AddSkillPoints(3,2,20) end",0);
    before=errors;G_NITMOD_LuaFrame(1);assert(errors==before+1 && clients[3].sess.skill[2]==1 && changed==1);
    G_NITMOD_LuaFrame(2);assert(errors==before+2 && clients[3].sess.skillpoints[2]==40 && clients[3].sess.skill[2]==1);
    /* Upgrade interception preserves the new level while suppressing userinfo. */
    Start("function et_UpgradeSkill() return -1 end; function et_RunFrame() et.G_AddSkillPoints(3,2,20) end",0);
    G_NITMOD_LuaFrame(1);assert(clients[3].sess.skill[2]==1 && !changed);
    g_gamestate.integer=GS_WARMUP;G_NITMOD_LuaFrame(2);assert(clients[3].sess.skillpoints[2]==20);
    ceiling=0; /* The original suppresses the reset message for zero. */
    Start("function et_SetPlayerSkill(c,s) assert(c==3 and s>=0 and s<7); et.trap_Cvar_Set('frame','1') end; function et_RunFrame() et.G_AddSkillPoints(3,2,1) end",200);
    clients[3].sess.skill[2]=5;clients[3].sess.nitmodSkillMasks[2]=62;clients[3].sess.medals[2]=4;
    clients[3].ps.persistant[PERS_SCORE]=200;clients[3].ps.stats[STAT_XP]=200;
    G_NITMOD_LuaFrame(1);
    assert(frames==7 && clients[3].sess.skill[2]==0 && clients[3].sess.nitmodSkillMasks[2]==0 && changed==1);
    assert(clients[3].sess.medals[2]==4 && clients[3].ps.stats[STAT_XP]==0 && clients[3].ps.persistant[PERS_SCORE]==0);
    assert(level.teamXP[2][0]==201 && level.teamScores[TEAM_AXIS]==200);
    for(war=0;war<=5;++war) {
        playerState_t saved;
        Start("function et_RunFrame() et.G_AddSkillPoints(3,2,1) end",200);
        clients[3].sess.playerType=PC_MEDIC;
        clients[3].ps.weapons[0]=123;clients[3].ps.weapons[1]=456;
        clients[3].ps.ammo[WP_MP40]=71;clients[3].ps.ammoclip[WP_MP40]=13;
        clients[3].ps.classWeaponTime=9876;
        clients[3].ps.stats[STAT_PLAYER_CLASS]=PC_ENGINEER;
        clients[3].ps.teamNum=TEAM_ALLIES;saved=clients[3].ps;
        G_NITMOD_LuaFrame(1);
        assert(clients[3].ps.weapons[0]==((war==0 || war==5)?0:123));
        assert(clients[3].ps.weapons[1]==456);
        assert(!memcmp(clients[3].ps.ammo,saved.ammo,sizeof(saved.ammo)));
        assert(!memcmp(clients[3].ps.ammoclip,saved.ammoclip,sizeof(saved.ammoclip)));
        assert(clients[3].ps.classWeaponTime==9876 && !granted);
        assert(clients[3].ps.stats[STAT_PLAYER_CLASS]==((war==0 || war==5)?PC_MEDIC:PC_ENGINEER));
        assert(clients[3].ps.teamNum==((war==0 || war==5)?TEAM_AXIS:TEAM_ALLIES));
    }
    ceiling=-1;
    for(war=0;war<=5;++war) for(adrenClasses=0;adrenClasses<32;++adrenClasses)
    for(adrenOptions=0;adrenOptions<8;++adrenOptions) {
        int pc;
        for(pc=PC_SOLDIER;pc<=PC_COVERTOPS;++pc) {
            int allowed=(adrenClasses & (1<<pc))!=0;
            int clip=(adrenOptions&4)?1:((adrenOptions&1)?0:12);
            if(war==0 || war==5) clip+=2;
            Start("function et_RunFrame() et.G_AddSkillPoints(3,2,10) end",135);
            clients[3].sess.playerType=pc;clients[3].sess.skill[SK_FIRST_AID]=3;
            clients[3].ps.ammo[WP_MEDIC_SYRINGE]=73;clients[3].ps.ammoclip[WP_MEDIC_SYRINGE]=17;
            G_NITMOD_LuaFrame(1);
            assert(clients[3].sess.skill[SK_FIRST_AID]==4 && changed==1);
            assert(!!COM_BitCheck(clients[3].ps.weapons,WP_MEDIC_ADRENALINE)==allowed);
            assert(clients[3].ps.ammo[WP_MEDIC_ADRENALINE]==0);
            assert(clients[3].ps.ammoclip[WP_MEDIC_ADRENALINE]==(allowed?clip:0));
            assert(clients[3].ps.ammo[WP_MEDIC_SYRINGE]==73 && clients[3].ps.ammoclip[WP_MEDIC_SYRINGE]==17);
        }
    }
    war=0;adrenClasses=31;adrenOptions=0;
    Start("function et_UpgradeSkill() return -1 end; function et_RunFrame() et.G_AddSkillPoints(3,2,10) end",135);
    clients[3].sess.skill[SK_FIRST_AID]=3;G_NITMOD_LuaFrame(1);
    assert(!COM_BitCheck(clients[3].ps.weapons,WP_MEDIC_ADRENALINE) && !changed);
    Start("function et_RunFrame() et.G_AddSkillPoints(3,0,50) end",145);
    clients[3].sess.nitmodSkillMasks[SK_FIRST_AID]=30;
    G_NITMOD_LuaFrame(1);assert(granted==1 && !COM_BitCheck(clients[3].ps.weapons,WP_MEDIC_ADRENALINE));
    /* Engineer flak is a fallback: an eligible adrenaline grant wins. */
    for(adrenClasses=0;adrenClasses<=4;adrenClasses+=4) {
        Start("function et_RunFrame() et.G_AddSkillPoints(3,1,10) end",145);
        clients[3].sess.playerType=PC_ENGINEER;
        clients[3].sess.skillpoints[1]=135;clients[3].sess.skill[1]=3;
        clients[3].sess.nitmodSkillMasks[SK_FIRST_AID]=30;
        G_NITMOD_LuaFrame(1);
        assert(clients[3].ps.powerups[PW_FIRE]==(adrenClasses?0:0x7fffffff));
        assert(!!COM_BitCheck(clients[3].ps.weapons,WP_MEDIC_ADRENALINE)==!!adrenClasses);
    }
    G_NITMOD_LuaShutdown(0);puts("Real Lua -> production XP/skill/score/rank: reset metadata, 7680 adrenaline configurations, binocular/flak priority, callbacks and error recovery: PASS");return 0;
}
