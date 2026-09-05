extern void AddMedicTeamBonus(gclient_t *client);
extern void ClientTimerActions(gentity_t *ent, int msec);
extern int Pickup_Health(gentity_t *ent, gentity_t *other);
static int CheckClassHealth(void) {
    static gclient_t client;
    gentity_t player, pack;
    entityState_t item;
    vmCvar_t saved = n_classesMaxHP;
    int connected = level.numConnectedClients;
    const char *settings[] = {"0 0 0 0 0", "90 80 70 60 50", "-1 nope 32768 2147483648 0", "150"};
    int config, cls, skill, health, expected, itemIndex, errors = 0;
    level.numConnectedClients = 0;
    memset(&player, 0, sizeof(player)); memset(&pack, 0, sizeof(pack)); memset(&item, 0, sizeof(item));
    for(itemIndex = 1; itemIndex < bg_numItems; ++itemIndex)
        if(bg_itemlist[itemIndex].giType == IT_HEALTH) break;
    if(itemIndex == bg_numItems) return 1;
    pack.item = &bg_itemlist[itemIndex]; item.modelindex = itemIndex;
    player.client = &client;
    for(config = 0; config < 4; ++config) for(cls = 0; cls < NUM_PLAYER_CLASSES; ++cls)
    for(skill = 0; skill < 2; ++skill) {
        int override = config == 1 ? 90 - cls * 10 : config == 3 && cls == 0 ? 150 : 0;
        Q_strncpyz(n_classesMaxHP.string, settings[config], sizeof(n_classesMaxHP.string));
        memset(&client, 0, sizeof(client));
        client.sess.playerType = client.ps.teamNum = client.ps.stats[STAT_PLAYER_CLASS] = cls;
        client.sess.skill[SK_BATTLE_SENSE] = skill ? 3 : 0;
        AddMedicTeamBonus(&client);
        expected = override ? override : 100 + skill * 15;
        if(client.pers.maxHealth != expected || client.ps.stats[STAT_MAX_HEALTH] != expected) ++errors;
        if(!override && cls == PC_MEDIC) expected = (int)(expected * 1.12);
        if(BG_EffectiveMaxHealth(&client.ps) != expected) ++errors;
        for(health = expected - 1; health <= expected + 1; ++health) {
            client.ps.stats[STAT_HEALTH] = health;
            if(BG_CanItemBeGrabbed(&item, &client.ps, client.sess.skill, TEAM_AXIS) != (health < expected)) ++errors;
        }
        player.health = expected - 1;
        Pickup_Health(&pack, &player);
        if(player.health != expected || client.ps.stats[STAT_HEALTH] != expected) ++errors;
        if(cls == PC_MEDIC) {
            player.health = expected - 1; client.timeResidual = 0;
            ClientTimerActions(&player, 1000);
            if(player.health != expected) ++errors;
        }
    }
    n_classesMaxHP = saved; level.numConnectedClients = connected;
    {
        int war, dm, medics, override, maximum, cap, spawn;
        for(cls = 0; cls < NUM_PLAYER_CLASSES; ++cls)
        for(skill = 0; skill < NUM_SKILL_LEVELS; ++skill)
        for(medics = 0; medics <= MAX_CLIENTS; ++medics)
        for(war = -1; war <= 5; ++war) for(dm = 0; dm < 2; ++dm)
        for(override = 0; override <= 1; ++override) {
            client.sess.playerType = cls; client.sess.skill[SK_BATTLE_SENSE] = skill;
            client.ps.stats[STAT_HEALTH] = 43; client.timeResidual = 57;
            maximum = war || dm ? 100 : (medics >= 3 ? 125 : 100 + medics * 10) + (skill >= 3 ? 15 : 0);
            if(override) maximum = 175;
            cap = cls == PC_MEDIC && !override && !(war && dm) ? (int)(maximum * 1.12) : maximum;
            spawn = maximum - (!war && !dm && !override && skill >= 3 ? 15 : 0);
            G_NITMOD_SetHealthLimits(&client, medics, war, dm ? 8 : GT_WOLF, override ? 175 : 0);
            if(client.pers.maxHealth != maximum || client.ps.stats[STAT_MAX_HEALTH] != maximum ||
               client.ps.stats[STAT_NITMOD_MAX_HEALTH] != cap || client.ps.stats[STAT_HEALTH] != 43 ||
               client.timeResidual != 57 || G_NITMOD_SpawnHealth(&client, war, dm ? 8 : GT_WOLF, override ? 175 : 0) != spawn)
                ++errors;
        }
        maximum = client.pers.maxHealth;
        G_NITMOD_SetHealthLimits(&client, -1, 0, GT_WOLF, 0);
        if(client.pers.maxHealth != maximum) ++errors;
        G_NITMOD_SetHealthLimits(NULL, 0, 0, GT_WOLF, 0);
        if(G_NITMOD_SpawnHealth(NULL, 0, GT_WOLF, 0)) ++errors;
    }
    if(errors) fprintf(stderr, "class health: %d failures\n", errors);
    return errors;
}

static int CheckMedicRegenerationOptions(void) {
    static gclient_t client;
    gentity_t actor;
    const int healthValues[] = {98,99,100,110,111,112,120};
    int cls, option, war, h, skill, expected, rate, active, errors = 0;
    memset(&actor, 0, sizeof(actor)); actor.client = &client;
    for(cls = 0; cls < NUM_PLAYER_CLASSES; ++cls)
    for(option = 0; option < 256; ++option) for(war = -1; war <= 5; ++war)
    for(skill = 0; skill < NUM_SKILL_LEVELS; ++skill)
    for(h = 0; h < 7; ++h) {
        memset(&client, 0, sizeof(client));
        client.sess.playerType = cls;
        client.sess.skill[SK_FIRST_AID] = skill;
        client.ps.stats[STAT_MAX_HEALTH] = 100;
        client.ps.stats[STAT_NITMOD_MAX_HEALTH] = cls == PC_MEDIC ? 112 : 100;
        client.timeResidual = 500;
        actor.health = expected = healthValues[h];
        active = !(war >= 1 && war <= 4) && !(cls == PC_MEDIC && (option & 32));
        rate = option & 64 ? 1 : option & 128 ? 0 : 2;
        if(active) {
            if(cls != PC_MEDIC && !((option & 16) && skill >= 5)) { if(expected > 100) --expected; }
            else if(expected < 100) { expected += rate + 1; if(expected > 100) expected = 100; }
            else if(expected < 112) { expected += rate; if(expected > 112) expected = 112; }
        }
        G_NITMOD_HealthTimer(&actor, 500, option, war);
        if(actor.health != expected || client.timeResidual != (active ? 0 : 500)) ++errors;
    }
    client.sess.playerType = PC_MEDIC; client.timeResidual = 0; actor.health = 90;
    G_NITMOD_HealthTimer(&actor, 2500, 64, 0);
    if(actor.health != 94 || client.timeResidual != 500) ++errors;
    G_NITMOD_HealthTimer(NULL, 1000, 0, 0);
    {
        vmCvar_t savedMode = g_gametype, savedOptions = g_DMOptions;
        int dm, options, flags;
        for(cls = 0; cls < NUM_PLAYER_CLASSES; ++cls)
        for(dm = 0; dm < 2; ++dm) for(options = 0; options < 4; ++options)
        for(flags = 0; flags < 4; ++flags) {
            g_gametype.integer = dm ? 8 : GT_WOLF; g_DMOptions.integer = options;
            client.sess.playerType = cls; client.timeResidual = 0;
            client.ps.eFlags = (flags & 1 ? EF_DEAD : 0) | (flags & 2 ? EF_VIEWING_CAMERA : 0);
            actor.health = 90;
            expected = (dm ? !!(options & 2) : cls == PC_MEDIC && !flags) ? 93 : 90;
            G_NITMOD_HealthTimer(&actor, 1000, 0, 0);
            if(actor.health != expected || client.timeResidual) ++errors;
        }
        g_gametype = savedMode; g_DMOptions = savedOptions;
    }
    if(errors) fprintf(stderr, "medic regeneration: %d failures\n", errors);
    return errors;
}
