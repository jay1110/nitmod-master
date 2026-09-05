static int CheckFallRecovery(void) {
    static gclient_t client;
    gentity_t ent;
    const int events[] = { EV_FALL_NDIE, EV_FALL_DMG_10, EV_FALL_DMG_15,
        EV_FALL_DMG_25, EV_FALL_DMG_50 };
    const int durations[] = { 73, 250, 250, 500, 1000 };
    int e, type, errors = 0, savedTime = level.time;
    for(e = 0; e < 5; ++e) for(type = 0; type < 2; ++type) {
        memset(&ent, 0, sizeof(ent)); memset(&client, 0, sizeof(client));
        ent.client = &client;
        ent.s.eType = type ? ET_PLAYER : ET_GENERAL;
        /* No damageable target: exercise real event dispatch/recovery without
         * unrelated death, corpse, rank, logging and map engine calls. */
        ent.takedamage = qfalse;
        client.ps.pm_time = 73; client.ps.pm_flags = PMF_DUCKED;
        client.ps.events[0] = events[e]; client.ps.eventSequence = 1;
        level.time = 1000;
        ClientEvents(&ent, 0);
        if(client.ps.pm_time != (type ? durations[e] : 73) ||
           client.ps.pm_flags != (PMF_DUCKED | (type && e ? PMF_TIME_KNOCKBACK : 0)) ||
           ent.pain_debounce_time != (type ? 1200 : 0)) ++errors;
    }
    level.time = savedTime;
    return errors;
}
