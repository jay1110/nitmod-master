static refEntity_t bipodDraws[2];
static int bipodTags, bipodCount;
static int QDECL BipodEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_R_LERPTAG) {
        orientation_t *tag = va_arg(args, orientation_t *);
        const refEntity_t *parent = va_arg(args, const refEntity_t *);
        const char *name = va_arg(args, const char *);
        if(bipodTags >= 2 || parent->hModel != 55 || va_arg(args, int) != 0 ||
           strcmp(name, bipodTags ? "tag_barrel5" : "tag_barrel4")) exit(2);
        memset(tag, 0, sizeof(*tag)); AxisClear(tag->axis);
        tag->origin[0] = ++bipodTags;
    } else if(command == CG_R_ADDREFENTITYTOSCENE) {
        const refEntity_t *entity = va_arg(args, const refEntity_t *);
        if(bipodCount >= 2) exit(2);
        bipodDraws[bipodCount++] = *entity;
    } else exit(2);
    va_end(args); return 1;
}
static int CheckMortarBipod(void) {
    static weaponInfo_t weapon;
    refEntity_t parent, barrel;
    int team, mask, leg, errors = 0;
    memset(&parent, 0, sizeof(parent)); memset(&barrel, 0, sizeof(barrel));
    parent.lightingOrigin[0] = 12; parent.lightingOrigin[1] = 13;
    parent.shadowPlane = 14; parent.renderfx = RF_FIRST_PERSON;
    barrel.hModel = 55; barrel.origin[0] = 100; AxisClear(barrel.axis);
    dllEntry(BipodEngine);
    for(team = -1; team <= TEAM_SPECTATOR + 1; ++team) for(mask = 0; mask < 16; ++mask) {
        memset(&weapon, 0, sizeof(weapon));
        for(leg = 0; leg < 2; ++leg) {
            partModel_t *part = &weapon.partModels[W_FP_MODEL][W_PART_4 + leg];
            part->model = 10 + leg; part->skin[0] = 20 + leg;
            if(team == TEAM_AXIS || team == TEAM_ALLIES) {
                part->teamModel[team] = mask & (1 << (2 * leg)) ? 30 + leg : 0;
                part->skin[team] = mask & (2 << (2 * leg)) ? 40 + leg : 0;
            }
        }
        bipodTags = bipodCount = 0;
        CG_NitmodDrawMortarBipod(&weapon, &parent, &barrel, team);
        if(bipodTags != 2 || bipodCount != 2) ++errors;
        for(leg = 0; leg < 2; ++leg) {
            refEntity_t expected;
            int isTeam = team == TEAM_AXIS || team == TEAM_ALLIES;
            memset(&expected, 0, sizeof(expected)); AxisClear(expected.axis);
            expected.hModel = isTeam && (mask & (1 << (2 * leg))) ? 30 + leg : 10 + leg;
            expected.customSkin = isTeam && (mask & (2 << (2 * leg))) ? 40 + leg : 20 + leg;
            expected.origin[0] = 101 + leg;
            VectorCopy(parent.lightingOrigin, expected.lightingOrigin);
            expected.renderfx = parent.renderfx; expected.shadowPlane = parent.shadowPlane;
            if(memcmp(&bipodDraws[leg], &expected, sizeof(expected))) ++errors;
        }
    }
    bipodTags = bipodCount = 0;
    CG_NitmodDrawMortarBipod(NULL, &parent, &barrel, TEAM_AXIS);
    CG_NitmodDrawMortarBipod(&weapon, NULL, &barrel, TEAM_AXIS);
    CG_NitmodDrawMortarBipod(&weapon, &parent, NULL, TEAM_AXIS);
    if(bipodTags || bipodCount) ++errors;
    dllEntry(Engine);
    return errors;
}
