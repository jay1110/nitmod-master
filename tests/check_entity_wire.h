static int CheckEntityWire(void) {
    static snapshot_t snap;
    const int wire[] = {15,16,18,31,32,33,34,35,38,39,41,46,47,48};
    const int typed[] = {ET_ALARMBOX,ET_CORONA,ET_GAMEMODEL,ET_CONSTRUCTIBLE_INDICATOR,
        ET_CONSTRUCTIBLE,ET_CONSTRUCTIBLE_MARKER,ET_BOMB,ET_BEAM_2,ET_CORPSE,
        ET_SMOKER,ET_MG42_BARREL,ET_GAMEMANAGER,ET_CABINET_H,ET_CABINET_A};
    const int packs[] = {24,32,33,34,60};
    int i, errors = 0;
    for(i = 0; i < sizeof(wire)/sizeof(wire[0]); ++i) {
        memset(&snap,0,sizeof(snap)); snap.numEntities = 1;
        snap.entities[0].eType = wire[i];
        NITMOD_TranslateSnapshotWeapons(&snap);
        if(snap.entities[0].eType != typed[i]) ++errors;
    }
    for(i = 1; i <= 255; ++i)
        if(NITMOD_EntityTypeFromWire(59+i) != ET_EVENTS+i) ++errors;
    for(i = 0; i < 5; ++i) {
        int item = NITMOD_ItemFromWire(packs[i]);
        if(item <= 0 || item >= bg_numItems ||
           bg_itemlist[item].giTag != (i == 0 || i == 4 ? WP_MEDKIT : WP_AMMO)) ++errors;
    }
    if(NITMOD_ItemFromWire(-1) || NITMOD_ItemFromWire(72) || NITMOD_ItemFromWire(2147483647)) ++errors;
    return errors;
}
