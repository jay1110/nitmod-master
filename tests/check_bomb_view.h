static int bombViewDraws;
static refEntity_t bombViewEntity;
static int QDECL BombViewEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_R_LERPTAG) {
        orientation_t *tag = va_arg(args, orientation_t *);
        memset(tag, 0, sizeof(*tag)); AxisClear(tag->axis);
    } else if(command == CG_R_ADDREFENTITYTOSCENE) {
        bombViewEntity = *va_arg(args, const refEntity_t *); ++bombViewDraws;
    } else { fprintf(stderr, "unexpected bomb view syscall %d\n", command); exit(2); }
    va_end(args); return 0;
}
static int CheckBombView(void) {
    static cg_t savedCg;
    static weaponInfo_t savedWeapon;
    snapshot_t snapshot;
    centity_t cent;
    refEntity_t hand;
    int i, errors = 0;
    int oldSpeed = cg_animSpeed.integer, oldDisabled = cg_noPlayerAnims.integer;
    const int weapons[] = {WP_BOMB, WP_POISON_BOMB, WP_POISON_MINE, WP_TRIPMINE};
    savedCg = cg; memset(&cg, 0, sizeof(cg)); memset(&snapshot, 0, sizeof(snapshot));
    cg_animSpeed.integer = 1; cg_noPlayerAnims.integer = 0;
    cg.snap = &snapshot; cg.time = 1000;
    memset(&cent, 0, sizeof(cent)); memset(&hand, 0, sizeof(hand)); AxisClear(hand.axis);
    hand.renderfx = RF_FIRST_PERSON | RF_DEPTHHACK;
    /* Network entity can still describe the previous weapon when the view
     * already uses the new player-state weapon. */
    cent.currentState.weapon = WP_NONE;
    dllEntry(BombViewEngine);
    for(i = 0; i < 4; ++i) {
        weaponInfo_t *weapon = &cg_weapons[weapons[i]];
        savedWeapon = *weapon; memset(weapon, 0, sizeof(*weapon));
        weapon->registered = qtrue; weapon->weaponModel[W_FP_MODEL].model = 600 + i;
        cent.pe.weap.animation = &weapon->weapAnimations[0];
        snapshot.ps.weapon = weapons[i]; bombViewDraws = 0;
        CG_AddPlayerWeapon(&hand, &snapshot.ps, &cent);
        if(bombViewDraws != 1 || bombViewEntity.hModel != 600 + i ||
           bombViewEntity.frame || bombViewEntity.oldframe || bombViewEntity.renderfx != hand.renderfx) ++errors;
        *weapon = savedWeapon;
    }
    cg = savedCg; cg_animSpeed.integer = oldSpeed; cg_noPlayerAnims.integer = oldDisabled;
    dllEntry(Engine);
    if(errors) fprintf(stderr, "bomb view: %d failures\n", errors);
    return errors;
}
