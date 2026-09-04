static int CheckOriginalObituary(void) {
    static const struct { int cause; const char *text; } selfCases[] = {
        {59, "poisonned himself"}, {61, "was killed (Censor)"},
        {63, "played with knives!"}, {64, "gibbed himself"},
        {65, "was detonated by his own bomb"}, {66, "forgot where his tripmine was"},
        {67, "choked on his own poison gas"}, {68, "choked on his own poison gas landmine"}
    };
    char out[512], expected[512], small[4];
    int cause, world, self, team, i, errors = 0;
    for(cause = -1; cause <= 69; ++cause) for(world = 0; world < 2; ++world)
    for(self = 0; self < 2; ++self) for(team = 0; team < 2; ++team) {
        qboolean result = CG_NitmodFormatObituary(cause, "Victim", world ? NULL : "Attacker",
            self, team, out, sizeof(out));
        if(result != (cause != 57) || (cause == 57 ? out[0] != 0 : !strstr(out, "Victim"))) ++errors;
        memset(small, 42, sizeof(small));
        CG_NitmodFormatObituary(cause, "Victim", world ? NULL : "Attacker", self, team, small, 3);
        if(small[3] != 42 || !memchr(small, 0, 3)) ++errors;
        if(world && strstr(out, "Attacker")) ++errors;
    }
    for(i = 0; i < sizeof(selfCases)/sizeof(selfCases[0]); ++i) {
        CG_NitmodFormatObituary(selfCases[i].cause, "Victim", "Victim", qtrue, qfalse, out, sizeof(out));
        Com_sprintf(expected, sizeof(expected), "Victim %s", selfCases[i].text);
        if(strcmp(out, expected)) ++errors;
    }
    CG_NitmodFormatObituary(8, "V", "A", qfalse, qtrue, out, sizeof(out));
    if(strcmp(out, "^1TEAM KILL^7:V was killed by A's MP40")) ++errors;
    CG_NitmodFormatObituary(23, "V", "A", qfalse, qtrue, out, sizeof(out));
    if(strcmp(out, "V was revived by A")) ++errors;
    CG_NitmodFormatObituary(28, "V", NULL, qfalse, qfalse, out, sizeof(out));
    if(strcmp(out, "V was burned by lava")) ++errors;
    CG_NitmodFormatObituary(65, "V", NULL, qfalse, qfalse, out, sizeof(out));
    if(strcmp(out, "V ^7died")) ++errors;
    if(CG_NitmodObituaryWeapon(63) != WP_KNIFE || CG_NitmodObituaryWeapon(8) != WP_MP40 ||
       CG_NitmodObituaryWeapon(-1) != WP_NONE || CG_NitmodObituaryWeapon(69) != WP_NONE) ++errors;
    {
        cgs_t *saved = malloc(sizeof(cgs));
        entityState_t es;
        int savedMode = cg_obituary.integer, savedTK = cg_tkSounds.integer, savedGoat = cg_goatSound.integer;
        snapshot_t *savedSnap = cg.snap;
        *saved = cgs; cg.snap = NULL;
        cg_obituary.integer = 0; cg_tkSounds.integer = cg_goatSound.integer = 0;
        strcpy(cgs.clientinfo[1].name, "Victim"); strcpy(cgs.clientinfo[2].name, "Attacker");
        cgs.clientinfo[1].team = cgs.clientinfo[2].team = TEAM_AXIS;
        graphicPopupTest = 1;
        for(cause = 0; cause < 69; ++cause) {
            memset(&es, 0, sizeof(es)); es.otherEntityNum = 1; es.otherEntityNum2 = 2; es.eventParm = cause;
            graphicPrints = 0; CG_NitmodObituary(&es);
            if(graphicPrints != (cause != 57)) ++errors;
        }
        graphicPopupTest = 0; cgs = *saved; free(saved); cg.snap = savedSnap;
        cg_obituary.integer = savedMode; cg_tkSounds.integer = savedTK; cg_goatSound.integer = savedGoat;
    }
    return errors;
}
