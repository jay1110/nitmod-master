extern void CG_LoseACC(centity_t *, vec3_t, int, char *, qboolean);
extern localEntity_t cg_activeLocalEntities;
static int accessoryHead;
static int QDECL AccessoryEngine(int command, ...) {
    va_list args; orientation_t *tag; const refEntity_t *parent;
    if(command != CG_R_LERPTAG) exit(2);
    va_start(args, command); tag = va_arg(args, orientation_t *);
    parent = va_arg(args, const refEntity_t *);
    if(parent->hModel != (accessoryHead ? 10 : 20) || strcmp(va_arg(args, char *), "tag_test")) exit(2);
    memset(tag, 0, sizeof(*tag)); AxisClear(tag->axis); tag->origin[0] = 2;
    va_end(args); return 0;
}
static int CheckAccessory(void) {
    bg_character_t character;
    clientInfo_t saved = cgs.clientinfo[0];
    centity_t cent;
    snapshot_t snapshot, *savedSnap = cg.snap;
    vec3_t dir = {0, 0, 1};
    int acc, errors = 0, savedTime = cg.time;
    memset(&character, 0, sizeof(character)); memset(&cent, 0, sizeof(cent));
    memset(&snapshot, 0, sizeof(snapshot)); cg.snap = &snapshot;
    cent.pe.headRefEnt.hModel = 10; cent.pe.bodyRefEnt.hModel = 20;
    AxisClear(cent.pe.headRefEnt.axis); AxisClear(cent.pe.bodyRefEnt.axis);
    cgs.clientinfo[0].character = &character; cg.time = 100000;
    dllEntry(AccessoryEngine);
    for(accessoryHead = 0; accessoryHead < 2; ++accessoryHead) for(acc = 0; acc < ACC_MAX; ++acc) {
        localEntity_t *le;
        character.accModels[acc] = 100 + acc; character.accSkins[acc] = 200 + acc;
        CG_InitLocalEntities(); CG_LoseACC(&cent, dir, acc, "tag_test", accessoryHead);
        le = cg_activeLocalEntities.next;
        if(le == &cg_activeLocalEntities || le->refEntity.hModel != 100 + acc ||
           le->refEntity.customSkin != 200 + acc || le->pos.trBase[0] != 2 ||
           le->angles.trDelta[2] != (accessoryHead ? 400 : 50) ||
           !!(le->effectFlags & 2) != !accessoryHead || le->leType != LE_FRAGMENT) ++errors;
        character.accModels[acc] = 0;
    }
    CG_InitLocalEntities(); CG_LoseACC(&cent, dir, ACC_MAX, "tag_test", qtrue);
    if(cg_activeLocalEntities.next != &cg_activeLocalEntities) ++errors;
    cgs.clientinfo[0] = saved; cg.time = savedTime; cg.snap = savedSnap; dllEntry(Engine);
    return errors;
}
