/* Exercise the live kill award dispatcher, not a duplicate reward table. */
static int specialXpReports;
static int QDECL SpecialXpEngine(int command, ...) {
    if(command == PB_STAT_REPORT) { ++specialXpReports; return 0; }
    fprintf(stderr, "special XP: unexpected syscall %ld\n", (long)command);
    exit(2);
    return 0;
}
static int CheckSpecialKillXP(void) {
    static level_locals_t savedLevel;
    static gclient_t client;
    gentity_t savedEntity = g_entities[0];
    vmCvar_t oldState=g_gamestate, oldGame=g_gametype, oldDebug=g_debugSkills;
    const meansOfDeath_t causes[]={MOD_GOOMBA, MOD_TRIPMINE, MOD_KNIFE};
    const skillType_t skills[]={SK_BATTLE_SENSE, SK_EXPLOSIVES_AND_CONSTRUCTION, SK_LIGHT_WEAPONS};
    const int rewards[]={5,4,3};
    int cause,team,playing,lms,splash,hr,skill,errors=0;
    savedLevel=level;
    dllEntry(SpecialXpEngine);
    g_debugSkills.integer=0;
    for(cause=0;cause<3;++cause) for(team=TEAM_FREE;team<=TEAM_SPECTATOR;++team)
    for(playing=0;playing<2;++playing) for(lms=0;lms<2;++lms)
    for(splash=0;splash<2;++splash) for(hr=0;hr<HR_NUM_HITREGIONS;++hr) {
        int expected=playing && !lms && (team==TEAM_AXIS || team==TEAM_ALLIES) ? rewards[cause] : 0;
        memset(&level,0,sizeof(level)); memset(&client,0,sizeof(client));
        memset(&g_entities[0],0,sizeof(g_entities[0]));
        g_entities[0].client=&client;
        client.sess.sessionTeam=team; client.ps.persistant[PERS_TEAM]=team;
        g_gamestate.integer=playing ? GS_PLAYING : GS_WARMUP;
        g_gametype.integer=lms ? GT_WOLF_LMS : GT_WOLF;
        specialXpReports=0;
        G_AddKillSkillPoints(&g_entities[0],causes[cause],hr,splash);
        for(skill=0;skill<SK_NUM_SKILLS;++skill)
            if(client.sess.skillpoints[skill] != (skill==skills[cause] ? expected : 0)) ++errors;
        if(level.teamScores[team] != expected || specialXpReports != (expected!=0)) ++errors;
        for(skill=0;skill<SK_NUM_SKILLS;++skill) {
            if(level.teamXP[skill][0] != (team==TEAM_AXIS && skill==skills[cause] ? expected : 0)) ++errors;
            if(level.teamXP[skill][1] != (team==TEAM_ALLIES && skill==skills[cause] ? expected : 0)) ++errors;
        }
    }
    level=savedLevel; g_entities[0]=savedEntity;
    g_gamestate=oldState; g_gametype=oldGame; g_debugSkills=oldDebug;
    dllEntry(EngineCallback);
    if(errors) fprintf(stderr,"special kill XP: %d errors\n",errors);
    return errors;
}
