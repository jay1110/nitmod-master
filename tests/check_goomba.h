static int goombaDamage, goombaCause;
static void GoombaPain(gentity_t *target, gentity_t *attacker, int damage, vec3_t point) {
    (void)target; (void)attacker; (void)point; goombaDamage += damage;
}
static void GoombaDie(gentity_t *target, gentity_t *inflictor, gentity_t *attacker, int damage, int cause) {
    (void)inflictor; (void)attacker; goombaDamage += damage; goombaCause = cause;
    target->inuse = qfalse;
}
static int CheckGoomba(void) {
    static level_locals_t savedLevel;
    static gclient_t clients[2];
    gentity_t saved[2];
    vmCvar_t oldGoomba=g_goomba, oldFlags=g_goombaFlags, oldGame=g_gametype,
        oldState=g_gamestate, oldFriendly=g_friendlyFire;
    const int events[]={EV_FALL_SHORT,EV_FALL_NDIE,EV_FALL_DMG_10,EV_FALL_DMG_15,EV_FALL_DMG_25,EV_FALL_DMG_50};
    const int damage[]={5,500,10,15,25,50}, stun[]={0,0,250,250,500,1000};
    int e, flags, team, dm, enabled, errors=0;
    savedLevel=level; memcpy(saved,g_entities,sizeof(saved));
    goombaXpFixture=1;
    for(e=0;e<6;++e) for(flags=0;flags<32;++flags) for(team=0;team<2;++team)
    for(dm=0;dm<2;++dm) for(enabled=0;enabled<2;++enabled) {
        int hit=enabled && !(e==0 && ((flags&2) || (team && (flags&4)))) &&
            !(team && !dm && (flags&1));
        memset(&level,0,sizeof(level)); memset(clients,0,sizeof(clients));
        memset(g_entities,0,sizeof(saved));
        level.time=1000; level.maxclients=2; level.clients=clients;
        g_goomba.integer=enabled ? 10 : 0; g_goombaFlags.integer=flags;
        g_gametype.integer=dm ? 8 : GT_WOLF; g_gamestate.integer=GS_PLAYING; g_friendlyFire.integer=1;
        g_entities[0].client=&clients[0]; g_entities[1].client=&clients[1];
        g_entities[0].s.eType=g_entities[1].s.eType=ET_PLAYER;
        g_entities[0].s.number=0; g_entities[1].s.number=1;
        g_entities[0].s.groundEntityNum=1;
        g_entities[0].health=g_entities[1].health=100;
        g_entities[1].takedamage=qtrue; g_entities[1].inuse=qtrue;
        g_entities[1].pain=GoombaPain; g_entities[1].die=GoombaDie;
        clients[0].sess.sessionTeam=TEAM_AXIS; clients[1].sess.sessionTeam=team ? TEAM_AXIS : TEAM_ALLIES;
        goombaDamage=goombaCause=0;
        G_NITMOD_FallDamage(&g_entities[0],events[e]);
        if(goombaDamage != (hit ? ((flags&16) ? 100 : damage[e]*10) : 0) ||
           clients[1].ps.pm_time != (hit ? stun[e] : 0) ||
           (goombaCause && goombaCause != MOD_GOOMBA)) ++errors;
    }
    level=savedLevel; memcpy(g_entities,saved,sizeof(saved));
    goombaXpFixture=0;
    g_goomba=oldGoomba; g_goombaFlags=oldFlags; g_gametype=oldGame;
    g_gamestate=oldState; g_friendlyFire=oldFriendly;
    if(errors) fprintf(stderr,"goomba: %d errors\n",errors);
    return errors;
}
