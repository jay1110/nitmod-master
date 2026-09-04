static int CheckObituaryPlan(void) {
    static cgs_t saved;
    static weaponInfo_t weapons[WP_NUM_WEAPONS];
    entityState_t es;
    nitmodObituaryPlan_t plan;
    int cause, mode, relation, dm, media, i, errors = 0;
    saved = cgs; memcpy(weapons, cg_weapons, sizeof(weapons));
    strcpy(cgs.clientinfo[1].name, "V"); strcpy(cgs.clientinfo[2].name, "A");
    cgs.clientinfo[1].team = TEAM_AXIS;
    for(cause = 0; cause < 69; ++cause) for(mode = 3; mode <= 4; ++mode)
    for(relation = 0; relation < 4; ++relation) for(dm = 0; dm < 2; ++dm)
    for(media = 0; media < 2; ++media) {
        int weapon = CG_NitmodObituaryWeapon(cause);
        memset(&es, 0, sizeof(es)); es.eventParm = cause; es.otherEntityNum = 1;
        es.otherEntityNum2 = relation == 0 ? ENTITYNUM_WORLD : relation == 1 ? 1 : 2;
        cgs.clientinfo[2].team = relation == 2 ? TEAM_AXIS : TEAM_ALLIES;
        cgs.gametype = dm ? 8 : GT_WOLF;
        memset(cg_weapons, 0, sizeof(weapons));
        if(weapon > WP_NONE && media) {
            cg_weapons[weapon].weaponIcon[0] = 901;
            cg_weapons[weapon].weaponIconScale = 2;
        }
        if(CG_NitmodPlanGraphicObituary(&es, mode, 789, &plan) != (cause != 57)) ++errors;
        if(cause == 57) continue;
        if(plan.shader != (weapon > WP_NONE && media ? 901 : 789) ||
            plan.scale != (weapon > WP_NONE && media ? 2 : 1)) ++errors;
        if(relation == 0 && (strcmp(plan.first, "V") || *plan.second ||
            plan.color[0] != 1 || plan.color[1] != 1 || plan.color[2] != 0)) ++errors;
        if(relation >= 2 && cause == 8) {
            if(strcmp(plan.first, mode == 3 ? "A" : "V") ||
                strcmp(plan.second, mode == 3 ? "V" : "A")) ++errors;
            for(i = 0; i < 3; ++i)
                if(plan.color[i] != (i == 0 || relation != 2 || dm ? 1 : 0)) ++errors;
        }
        if(relation >= 2 && cause == 23 && (strcmp(plan.first, "A") ||
            strcmp(plan.second, "V") || plan.color[0] || plan.color[1] != 1 || plan.color[2])) ++errors;
        if(relation >= 2 && (cause == 24 || cause == 42 || cause == 61 || cause == 64) &&
            (strcmp(plan.first, "V") || strcmp(plan.second, "A") ||
             plan.color[0] != 1 || plan.color[1] != 1 || plan.color[2])) ++errors;
        if(relation == 1 && cause == 65 && *plan.second) ++errors;
    }
    memset(&es, 0, sizeof(es)); es.otherEntityNum = 1; es.otherEntityNum2 = ENTITYNUM_WORLD;
    memset(cg_weapons, 0, sizeof(weapons));
    es.eventParm = 8; cg_weapons[WP_MP40].weaponIcon[0] = 901;
    if(!CG_NitmodPlanGraphicObituary(&es, 3, 789, &plan) || plan.shader != 901 || plan.scale != 2) ++errors;
    es.eventParm = 63; cg_weapons[WP_KNIFE].weaponIcon[0] = 901;
    if(!CG_NitmodPlanGraphicObituary(&es, 3, 789, &plan) || plan.shader != 901 || plan.scale != 1) ++errors;
    cg_weapons[WP_KNIFE].weaponIconScale = -1;
    if(!CG_NitmodPlanGraphicObituary(&es, 3, 789, &plan) || plan.shader != 789 || plan.scale != 1) ++errors;
    es.eventParm = 0;
    for(mode = -1; mode < 7; ++mode)
        if(CG_NitmodPlanGraphicObituary(&es, mode, 789, &plan) != (mode == 3 || mode == 4)) ++errors;
    if(CG_NitmodPlanGraphicObituary(&es, 3, 0, &plan)) ++errors;
    es.otherEntityNum = MAX_CLIENTS;
    if(CG_NitmodPlanGraphicObituary(&es, 3, 789, &plan) ||
        CG_NitmodPlanGraphicObituary(NULL, 3, 789, &plan) ||
        CG_NitmodPlanGraphicObituary(&es, 3, 789, NULL)) ++errors;
    cgs = saved; memcpy(cg_weapons, weapons, sizeof(weapons));
    return errors;
}
