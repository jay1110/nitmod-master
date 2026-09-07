/* Full production qagame objects, real Lua, synthetic engine boundary. */
#include "g_local.h"
#include "g_nitmod_lua.h"
#include "g_nitmod_config.h"
#include "g_nitmod_records.h"
#include "g_nitmod_legacy_cvars.h"
#include <assert.h>
extern void dllEntry(int (QDECL *)(int,...));
extern void ClientEvents(gentity_t *,int);
static const char *script;
static int callbacks,obituaries,customMessages;
static int announcerFlags,spreeChats,spreeEvents;
static vmCvar_t *reviveOptions,*moduleCvar,*aclCvar,*changedCvar;
static int quitCallbacks,shutdownCallbacks,demoState,demoClients;
static int extensionMode,demoSupportCalls;
static char spreeChat[512],spreeEvent[64];
static char userinfo[MAX_INFO_STRING]="\\name\\fixture\\ip\\localhost";
static char configs[MAX_CONFIGSTRINGS][MAX_STRING_CHARS];
static gclient_t clients[MAX_CLIENTS];
static bg_character_t character;
static animModelInfo_t animations;
static int QDECL Engine(int command,...) {
    va_list args;va_start(args,command);
    switch(command) {
    case 700: {
        char *out=va_arg(args,char *);int size=va_arg(args,int);const char *key=va_arg(args,const char *);
        assert(!strcmp(key,"trap_DemoSupport_Legacy"));Q_strncpyz(out,extensionMode==2?"701":"",size);
        va_end(args);return extensionMode==2;
    }
    case 701: {
        const char *commands=va_arg(args,const char *);assert(strstr(commands,"gstats\\sgstats\\sc0\\score"));++demoSupportCalls;break;
    }
    case G_PRINT: fputs(va_arg(args,const char *),stderr);break;
    case G_ERROR: fprintf(stderr,"Engine error: %s\n",va_arg(args,const char *));abort();
    case G_CVAR_REGISTER: {
        vmCvar_t *c=va_arg(args,vmCvar_t *);const char *value,*name;
        name=va_arg(args,const char *);value=va_arg(args,const char *);
        if(!strcmp(name,"lua_modules")) value="death.lua";
        if(!strcmp(name,"n_reviveSpreeOptions")) reviveOptions=c;
        if(!strcmp(name,"lua_modules")) moduleCvar=c;
        if(!strcmp(name,"lua_allowedModules")) aclCvar=c;
        memset(c,0,sizeof(*c));Q_strncpyz(c->string,value,sizeof(c->string));c->integer=atoi(value);c->value=atof(value);break;
    }
    case G_CVAR_UPDATE: {
        vmCvar_t *c=va_arg(args,vmCvar_t *);
        if(c==changedCvar) { ++c->modificationCount;changedCvar=NULL; }
        break;
    }
    case G_CVAR_VARIABLE_STRING_BUFFER: {
        const char *name=va_arg(args,const char *);char *out=va_arg(args,char *);int size=va_arg(args,int);
        Q_strncpyz(out,!strcmp(name,"lua_modules")?"death.lua":!strcmp(name,"//trap_GetValue") && extensionMode?"700":"",size);break;
    }
    case G_CVAR_VARIABLE_INTEGER_VALUE: {
        const char *name=va_arg(args,const char *);int value=!strcmp(name,"g_announcer")?announcerFlags:!strcmp(name,"sv_demoState")?demoState:!strcmp(name,"sv_demoClients")?demoClients:0;
        va_end(args);return value;
    }
    case G_CVAR_SET: {
        const char *name=va_arg(args,const char *);(void)va_arg(args,const char *);
        if(!strcmp(name,"lua_quit")) ++quitCallbacks;
        else if(!strcmp(name,"lua_shutdown")) ++shutdownCallbacks;
        else if(!strcmp(name,"death_callback")) ++callbacks;
        else if(!strcmp(name,"wstats0")) break;
        else if(strncmp(name,"P",1) && strncmp(name,"g_",2) && strncmp(name,"session",7) && strncmp(name,"nitmod_",7)) { fprintf(stderr,"Unexpected cvar %s\n",name);abort(); }
        break;
    }
    case G_FS_FOPEN_FILE: {
        const char *name=va_arg(args,const char *);fileHandle_t *f=va_arg(args,fileHandle_t *);int mode=va_arg(args,int);
        assert(mode==FS_READ);*f=!strcmp(name,"death.lua")?1:0;va_end(args);return *f?(int)strlen(script):-1;
    }
    case G_FS_READ: {
        void *out=va_arg(args,void *);int count=va_arg(args,int);assert(va_arg(args,int)==1 && count==(int)strlen(script));memcpy(out,script,count);break;
    }
    case G_FS_FCLOSE_FILE: assert(va_arg(args,int)==1);break;
    case G_GET_CONFIGSTRING: {
        int n=va_arg(args,int);char *out=va_arg(args,char *);int size=va_arg(args,int);assert(n>=0 && n<MAX_CONFIGSTRINGS);Q_strncpyz(out,configs[n],size);break;
    }
    case G_SET_CONFIGSTRING: {
        int n=va_arg(args,int);const char *value=va_arg(args,const char *);assert(n>=0 && n<MAX_CONFIGSTRINGS);Q_strncpyz(configs[n],value,sizeof(configs[n]));break;
    }
    case G_GET_USERCMD: {
        int n=va_arg(args,int);usercmd_t *cmd=va_arg(args,usercmd_t *);assert(n>=0 && n<MAX_CLIENTS);memset(cmd,0,sizeof(*cmd));break;
    }
    case G_GET_USERINFO: {
        int n=va_arg(args,int);char *out=va_arg(args,char *);int size=va_arg(args,int);assert(n>=0 && n<MAX_CLIENTS);Q_strncpyz(out,userinfo,size);break;
    }
    case G_SEND_SERVER_COMMAND: {
        int n=va_arg(args,int);const char *text=va_arg(args,const char *);assert(n>=-1 && n<MAX_CLIENTS);
        if(!strncmp(text,"cpm ",4)) ++customMessages;
        if(!strncmp(text,"chat ",5) && strstr(text,"spree")) { ++spreeChats;Q_strncpyz(spreeChat,text,sizeof(spreeChat)); }
        if(!strncmp(text,"nsp ",4)) { ++spreeEvents;Q_strncpyz(spreeEvent,text,sizeof(spreeEvent)); }
        break;
    }
    case G_LOCATE_GAME_DATA: {
        assert(va_arg(args,gentity_t *)==g_entities);assert(va_arg(args,int)==level.num_entities);assert(va_arg(args,int)==sizeof(gentity_t));
        assert(va_arg(args,playerState_t *)==&clients[0].ps);assert(va_arg(args,int)==sizeof(gclient_t));break;
    }
    case G_LINKENTITY: {
        gentity_t *e=va_arg(args,gentity_t *);assert(e>=g_entities && e<g_entities+MAX_GENTITIES);e->r.linked=qtrue;
        if(e->s.eType==ET_EVENTS+EV_OBITUARY) ++obituaries;break;
    }
    case G_UNLINKENTITY: {gentity_t *e=va_arg(args,gentity_t *);assert(e>=g_entities && e<g_entities+MAX_GENTITIES);e->r.linked=qfalse;break;}
    case G_MILLISECONDS: break;
    case PB_STAT_REPORT: break;
    default: fprintf(stderr,"Unexpected death engine syscall %d\n",command);abort();
    }
    va_end(args);return 0;
}
static void Start(int pushed,int custom) {
    static char source[512];int i;
    G_NITMOD_LuaShutdown(0);memset(&level,0,sizeof(level));memset(g_entities,0,sizeof(gentity_t)*MAX_GENTITIES);memset(clients,0,sizeof(clients));
    level.gentities=g_entities;level.clients=clients;level.maxclients=2;level.num_entities=MAX_CLIENTS;level.time=1000;level.timeCurrent=1000;
    g_gamestate.integer=GS_WARMUP;g_gametype.integer=GT_WOLF;
    character.animModelInfo=&animations;
    for(i=0;i<2;++i) {
        g_entities[i].client=clients+i;g_entities[i].inuse=qtrue;g_entities[i].s.number=i;g_entities[i].s.eType=ET_PLAYER;
        g_entities[i].health=100;g_entities[i].takedamage=qtrue;g_entities[i].die=player_die;clients[i].sess.sessionTeam=i?TEAM_ALLIES:TEAM_AXIS;
        clients[i].pers.character=&character;clients[i].ps.clientNum=i;clients[i].ps.persistant[PERS_TEAM]=clients[i].sess.sessionTeam;
    }
    g_entities[ENTITYNUM_WORLD].s.number=ENTITYNUM_WORLD;
    clients[0].nitmodPushed=pushed;clients[0].nitmodPushedBy=1;
    snprintf(source,sizeof(source),"function et_Obituary(v,k,m) assert(v==0 and k==%d and m==%d); assert(et.gentity_get(0,'sess.newton')==%d); et.trap_Cvar_Set('death_callback','1'); %s end",pushed?1:ENTITYNUM_WORLD,pushed?62:31,pushed?0:1,custom?"return 'custom death'":"");
    script=source;callbacks=obituaries=customMessages=0;G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
}
int main(void) {
    int pushed,custom;
    dllEntry(Engine);G_NITMOD_RegisterLegacyGameplayCvars();
    for(extensionMode=0;extensionMode<3;++extensionMode) trap_NITMOD_DemoSupport();
    assert(demoSupportCalls==1);extensionMode=0;
    for(pushed=0;pushed<2;++pushed) for(custom=0;custom<2;++custom) {
        Start(pushed,custom);g_entities[0].health=0;
        player_die(g_entities,g_entities+ENTITYNUM_WORLD,g_entities+ENTITYNUM_WORLD,100,MOD_FALLING);
        assert(callbacks==1 && customMessages==custom && obituaries==!custom);
        assert(clients[0].sess.nitmodNewton==!pushed && clients[0].ps.pm_type==PM_DEAD);
        if(pushed) assert(g_entities[0].enemy==g_entities+1);
    }
    for(pushed=0;pushed<2;++pushed) {
        Start(pushed,0);clients[0].nitmodPushed=qfalse;
        g_gamestate.integer=GS_PLAYING;g_shove.integer=80;g_shoveNoZ.integer=0;g_goomba.integer=0;
        if(pushed) {
            assert(G_PushPlayer(g_entities+1,g_entities));
            assert(clients[0].nitmodPushed && clients[0].nitmodPushedBy==1);
        }
        g_entities[0].health=5;clients[0].ps.stats[STAT_HEALTH]=5;
        clients[0].ps.events[0]=EV_FALL_DMG_10;clients[0].ps.eventSequence=1;
        ClientEvents(g_entities,0);
        assert(callbacks==1 && obituaries==1 && !clients[0].nitmodPushed);
        assert(clients[0].sess.nitmodNewton==!pushed);
        assert(clients[1].sess.skillpoints[SK_BATTLE_SENSE]==(pushed?5:0));
    }
    Start(0,0);g_shove.integer=80;
    clients[1].ps.powerups[PW_INVULNERABLE]=5000;
    assert(!G_PushPlayer(g_entities+1,g_entities) && !clients[0].nitmodPushed);
    {
        int air,explosive,team,ff,dm;
        const int friendly[]={0,1,16,17,2};
        for(air=0;air<2;++air) for(explosive=0;explosive<2;++explosive)
        for(team=0;team<2;++team) for(ff=0;ff<5;++ff) for(dm=0;dm<2;++dm) {
            vec3_t direction={1,0,0};int expected=(!air || explosive) && (!team || dm || (friendly[ff]&17));
            Start(0,0);g_gamestate.integer=GS_PLAYING;g_gametype.integer=dm?GT_WOLF_DM:GT_WOLF;
            g_friendlyFire.integer=friendly[ff];g_knockback.value=1000;
            if(team) clients[1].sess.sessionTeam=TEAM_AXIS;
            clients[0].ps.groundEntityNum=air?ENTITYNUM_NONE:ENTITYNUM_WORLD;
            G_Damage(g_entities,g_entities+1,g_entities+1,direction,NULL,1,0,explosive?MOD_DYNAMITE:MOD_MACHINEGUN);
            assert(!!clients[0].nitmodPushed==!!expected && !callbacks);
            if(expected) assert(clients[0].nitmodPushedBy==1);
        }
    }
    Start(0,0);G_NITMOD_LuaShutdown(0);
    script="function et_ClientConnect(c,f,b) assert(c==0 and f==1 and b==0); assert(et.gentity_get(c,'sess.sessionTeam')==3); et.trap_Cvar_Set('death_callback','1'); return 'fixture denial' end";
    G_NITMOD_LuaInit(0,0,0);g_entities[0].inuse=qfalse;g_filterBan.integer=1;
    { const char *denial=ClientConnect(0,qtrue,qfalse);assert(denial && !strcmp(denial,"You are excluded from this server. fixture denial\n") && callbacks==1); }
    Start(0,0);G_NITMOD_LuaShutdown(0);
    script="function et_ClientConnect(c,f,b) assert(c==0 and f==0 and b==1); assert(et.gentity_get(c,'r.svFlags')%16>=8); et.trap_Cvar_Set('death_callback','1'); return 'ignored bot denial' end";
    G_NITMOD_LuaInit(0,0,0);g_entities[0].inuse=qfalse;
    Q_strncpyz(userinfo,"\\name\\fixture\\ip\\localhost\\respawn\\NO",sizeof(userinfo));
    { const char *denial=ClientConnect(0,qfalse,qtrue);assert(denial && !strcmp(denial,"BotConnectFailed (no respawn)") && callbacks==1); }
    {
        const int original[]={60,61,63,64};int n;
        for(n=0;n<4;++n) {
            char source[400];
            Start(0,0);G_NITMOD_LuaShutdown(0);g_gamestate.integer=GS_PLAYING;
            snprintf(source,sizeof(source),"function et_RunFrame() et.G_Damage(0,1,1,10,0,%d) end; function et_Obituary(v,k,m) assert(v==0 and k==1 and m==%d); et.trap_Cvar_Set('death_callback','1') end",original[n],original[n]);
            script=source;G_NITMOD_LuaInit(0,0,0);g_entities[0].health=5;
            G_NITMOD_LuaFrame(1);
            assert(callbacks==1 && obituaries==1 && clients[0].ps.pm_type==PM_DEAD);
            assert(g_entities[MAX_CLIENTS].s.eventParm==MOD_UNKNOWN && g_entities[MAX_CLIENTS].s.effect3Time==NITMOD_OBITUARY_EXTRA+n);
            if(n==2) {
                assert(clients[1].sess.skillpoints[SK_LIGHT_WEAPONS]==3);
                assert(G_weapStatIndex_MOD(MOD_THROWKNIFE)==WS_KNIFE && BG_WeaponForMOD(MOD_THROWKNIFE)==WP_KNIFE);
                assert(clients[1].sess.aWeaponStats[WS_KNIFE].kills==1);
            }
        }
        Start(0,0);G_NITMOD_LuaShutdown(0);g_gamestate.integer=GS_PLAYING;
        script="function et_Obituary(v,k,m) assert(m==60); et.trap_Cvar_Set('death_callback','1') end";
        G_NITMOD_LuaInit(0,0,0);clients[0].lasthurt_mod=MOD_LUGER;g_entities[0].health=0;
        player_die(g_entities,g_entities+1,g_entities+1,10,MOD_FEAR);
        assert(callbacks==1 && clients[1].sess.skillpoints[SK_LIGHT_WEAPONS]==5);
    }
    {
        const int causes[]={59,65,66,67,68};
        const int weapons[]={WP_POISON_SYRINGE,WP_BOMB,WP_TRIPMINE,WP_POISON_BOMB,WP_POISON_MINE};
        const int stats[]={WS_POISON,WS_BOMB,WS_TRIPMINE,WS_POISON_GAS,WS_POISON_MINE};
        int n;
        for(n=0;n<5;++n) {
            char source[800];
            Start(0,0);G_NITMOD_LuaShutdown(0);g_gamestate.integer=GS_PLAYING;
            assert(BG_WeapStatForWeapon(weapons[n])==stats[n]);
            clients[1].sess.aWeaponStats[stats[n]].atts=1;
            snprintf(source,sizeof(source),"function et_RunFrame() et.gentity_set(100,'methodOfDeath',%d); et.G_Damage(0,1,1,1,0,et.gentity_get(100,'methodOfDeath')); local t=et.gentity_get(1,'sess.aWeaponStats',%d); assert(t[1]==1 and t[4]==1 and t[5]==0); et.trap_Cvar_Set('death_callback','1') end",causes[n],21+n);
            script=source;G_NITMOD_LuaInit(0,0,0);G_NITMOD_LuaFrame(1);
            assert(callbacks==1 && clients[1].sess.aWeaponStats[stats[n]].hits==1);
            assert(clients[1].nitmodLuaPersistant[2]==(n!=0) && clients[1].nitmodLuaPersistant[6]==(n!=0));
            assert(!clients[1].nitmodLuaPersistant[1] && !clients[1].nitmodLuaPersistant[5]);
            assert(clients[1].sess.aWeaponStats[WS_MAX].hits==0 && clients[1].sess.aWeaponStats[WS_LANDMINE].hits==0);
        }
    }
    assert(G_weapStatIndex_MOD(MOD_BROWNING)==WS_MG42 && G_weapStatIndex_MOD(MOD_MG42)==WS_MG42);
    {
        weapon_stat_t saved[WS_MAX+1];char encoded[4096];int n;
        Start(0,0);G_NITMOD_LuaShutdown(0);
        for(n=0;n<WS_MAX;++n) { clients[0].sess.aWeaponStats[n].atts=n+1;clients[0].sess.aWeaponStats[n].hits=n+2;clients[0].sess.aWeaponStats[n].kills=n+3;clients[0].sess.aWeaponStats[n].deaths=n+4;clients[0].sess.aWeaponStats[n].headshots=n+5; }
        memcpy(saved,clients[0].sess.aWeaponStats,sizeof(saved));
        Q_strncpyz(encoded,G_createStats(g_entities),sizeof(encoded));
        G_deleteStats(0);assert(!clients[0].sess.aWeaponStats[WS_POISON_MINE].hits);
        G_parseStats(encoded);assert(!memcmp(saved,clients[0].sess.aWeaponStats,sizeof(saved)));
        script="local t=et.gentity_get(0,'sess.aWeaponStats',25); assert(t[1]==27 and t[2]==30 and t[3]==31 and t[4]==28 and t[5]==29)";
        G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
    }
    {
        int disguise,ff,fieldops,reward;
        for(disguise=0;disguise<2;++disguise) for(ff=0;ff<2;++ff)
        for(fieldops=0;fieldops<2;++fieldops) for(reward=0;reward<2;++reward) {
            Start(0,0);g_gamestate.integer=GS_PLAYING;g_friendlyFire.integer=ff;
            clients[0].ps.powerups[PW_OPS_DISGUISED]=disguise;
            clients[1].sess.playerType=fieldops?PC_FIELDOPS:PC_COVERTOPS;
            clients[1].sess.nitmodSkillMasks[SK_SIGNALS]=reward?16:0;
            G_Damage(g_entities,g_entities+1,g_entities+1,NULL,NULL,1,0,MOD_BOMB);
            assert(clients[1].nitmodLuaPersistant[2]==(!disguise || !ff || (fieldops && reward)));
            assert(clients[1].nitmodLuaPersistant[6]==1 && clients[1].sess.nitmodBodyHits==1);
        }
    }
    Start(0,0);G_NITMOD_LuaShutdown(0);g_gamestate.integer=GS_PLAYING;
    script="et.gentity_set(0,'ps.persistant',15,7); et.gentity_set(0,'ps.persistant',14,4); et.gentity_set(1,'ps.persistant',15,-9)";
    G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
    clients[0].sess.nitmodKillingSpree=37;
    NITMOD_UpdateKillSpree(g_entities,g_entities+1);
    assert(clients[0].sess.nitmodKillingSpree==37);
    assert(clients[0].nitmodLuaPersistant[15]==0 && clients[0].nitmodLuaPersistant[14]==7);
    assert(clients[1].nitmodLuaPersistant[15]==1);
    NITMOD_UpdateKillSpree(g_entities,g_entities);
    assert(clients[0].nitmodLuaPersistant[15]==-1 && clients[0].nitmodLuaPersistant[14]==7);
    assert(G_NITMOD_BestKillSpree(0)==7 && G_NITMOD_BestKillSpree(1)==1);
    G_AddKillSkillPoints(g_entities+1,MOD_GOOMBA,HR_HEAD,qfalse);
    assert(clients[1].nitmodLuaPersistant[13]==1);
    G_deleteStats(0);assert(!clients[0].sess.nitmodKillingSpree);
    Start(0,0);G_NITMOD_LuaShutdown(0);
    clients[0].sess.sessionTeam=TEAM_SPECTATOR;
    g_entities[MAX_CLIENTS].inuse=qtrue;g_entities[MAX_CLIENTS].classname="info_player_intermission";
    level.num_entities=MAX_CLIENTS+1;
    clients[0].nitmodLuaPersistant[3]=12;clients[0].nitmodLuaPersistant[13]=4;
    clients[0].nitmodLuaPersistant[14]=8;clients[0].nitmodLuaPersistant[15]=-3;
    clients[0].ps.persistant[PERS_HITS]=123;
    script="function et_ClientSpawn(c,r,t,h) assert(c==0 and r==0); assert(et.gentity_get(c,'ps.persistant',3)==12); assert(et.gentity_get(c,'ps.persistant',13)==4); assert(et.gentity_get(c,'ps.persistant',14)==8); assert(et.gentity_get(c,'ps.persistant',15)==-3); et.trap_Cvar_Set('death_callback','1') end";
    G_NITMOD_LuaInit(0,0,0);ClientSpawn(g_entities,qfalse);
    assert(callbacks==1 && clients[0].ps.persistant[PERS_HITS]==123);
    G_NITMOD_LuaShutdown(0);callbacks=0;
    clients[0].sess.kills=23;clients[0].sess.deaths=11;clients[0].sess.nitmodHeadHits=7;clients[0].sess.nitmodBodyHits=19;
    script="function et_ClientSpawn(c,r,t,h) assert(c==0 and r==0 and t==1); assert(et.gentity_get(c,'ps.persistant',3)==23); assert(et.gentity_get(c,'ps.persistant',4)==11); assert(et.gentity_get(c,'ps.persistant',5)==7); assert(et.gentity_get(c,'ps.persistant',6)==19); for _,i in ipairs({1,2,13,14,15}) do assert(et.gentity_get(c,'ps.persistant',i)==0) end; et.trap_Cvar_Set('death_callback','1') end";
    G_NITMOD_LuaInit(0,0,0);ClientBegin(0);assert(callbacks==1);

    Start(0,0);G_NITMOD_LuaShutdown(0);g_goomba.integer=0;g_gamestate.integer=GS_PLAYING;
    script="function et_RunFrame() et.G_AddEvent(0,14,0) end; function et_Obituary(v,k,m) assert(v==0 and k==1022 and m==31); et.trap_Cvar_Set('death_callback','1') end";
    G_NITMOD_LuaInit(0,0,0);g_entities[0].health=5;
    G_NITMOD_LuaFrame(1);assert(clients[0].ps.events[0]==EV_NITMOD_LUA_FIRST+14);
    ClientEvents(g_entities,0);assert(callbacks==1 && clients[0].ps.pm_type==PM_DEAD);
    Start(0,0);G_NITMOD_LuaShutdown(0);
    script="local e=et.G_TempEntity({1,2,3},100); et.gentity_set(e,'s.eventParm',2147483647); assert(et.gentity_get(e,'s.eType')==159)";
    G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
    assert(g_entities[MAX_CLIENTS].s.eType==ET_EVENTS+EV_NITMOD_LUA_FIRST && g_entities[MAX_CLIENTS].s.eType<256);
    assert(g_entities[MAX_CLIENTS].s.event==EV_NITMOD_LUA_FIRST+100 && g_entities[MAX_CLIENTS].s.eventParm==2147483647);
    assert(g_entities[MAX_CLIENTS].freeAfterEvent && g_entities[MAX_CLIENTS].r.linked);

    Start(1,0);assert(reviveOptions);reviveOptions->integer=8;
    strcpy(clients[0].pers.netname,"Victim");strcpy(clients[1].pers.netname,"Killer");
    clients[0].nitmodReviveSpree=6;spreeChats=0;g_entities[0].health=0;
    player_die(g_entities,g_entities+ENTITYNUM_WORLD,g_entities+ENTITYNUM_WORLD,100,MOD_FALLING);
    assert(spreeChats==1 && !strcmp(spreeChat,"chat \"Victim^g's revive spree ended by ^7Killer ^gafter ^26 ^grevives!\" -2"));
    assert(!clients[0].nitmodReviveSpree && clients[0].nitmodBestReviveSpree==6);
    player_die(g_entities,g_entities+ENTITYNUM_WORLD,g_entities+ENTITYNUM_WORLD,100,MOD_FALLING);
    assert(spreeChats==1);reviveOptions->integer=1;
    {
        int mask,previous,kind;char expected[512];
        for(mask=0;mask<128;++mask) for(previous=-31;previous<=31;++previous) {
            Start(0,0);G_NITMOD_LuaShutdown(0);announcerFlags=mask;
            G_NITMOD_ClientCapabilities(0,NITMOD_PROTOCOL_VERSION,NITMOD_FEATURE_SPREE_EVENTS);
            G_NITMOD_ClientCapabilities(1,NITMOD_PROTOCOL_VERSION,0);
            strcpy(clients[0].pers.netname,"Victim");strcpy(clients[1].pers.netname,"Killer");
            clients[0].nitmodLuaPersistant[15]=previous;
            spreeChats=spreeEvents=0;NITMOD_UpdateKillSpree(g_entities,g_entities+1);
            assert(spreeChats==((mask&32)!=0 && previous>=5));
            if(spreeChats) {
                snprintf(expected,sizeof(expected),"chat \"Victim^g's killing spree ended by ^7Killer ^gafter ^2%d ^gkills!\" -2",previous);
                assert(!strcmp(spreeChat,expected));
            }
            assert(spreeEvents==((mask&2)!=0 && (previous==-9 || previous==-19 || previous==-29)));
            if(spreeEvents) { snprintf(expected,sizeof(expected),"nsp 0 %d 2",(-previous-1)/10);assert(!strcmp(spreeEvent,expected)); }
            clients[0].nitmodLuaPersistant[15]=0;clients[1].nitmodLuaPersistant[15]=previous;
            spreeChats=spreeEvents=0;NITMOD_UpdateKillSpree(g_entities,g_entities+1);
            assert(spreeChats==((mask&64)!=0 && previous<=-10));
            assert(clients[1].nitmodLuaPersistant[15]==(previous<0?1:previous+1));
            assert(spreeEvents==((mask&1)!=0 && previous>=4 && previous<=29 && (previous+1)%5==0));
            if(spreeEvents) { snprintf(expected,sizeof(expected),"nsp 1 %d 1",(previous+1)/5-1);assert(!strcmp(spreeEvent,expected)); }

            if(spreeChats) {
                snprintf(expected,sizeof(expected),"chat \"Killer^g's death spree ended after ^1%d ^gdeaths!\" -2",-previous);
                assert(!strcmp(spreeChat,expected));
            }
        }
        for(kind=0;kind<3;++kind) {
            Start(0,0);G_NITMOD_LuaShutdown(0);announcerFlags=32;
            strcpy(clients[0].pers.netname,"Victim");strcpy(clients[1].pers.netname,"Killer");
            clients[0].nitmodLuaPersistant[15]=5;
            clients[1].sess.sessionTeam=TEAM_AXIS;spreeChats=0;
            NITMOD_UpdateKillSpree(g_entities,kind==0?g_entities+1:kind==1?g_entities:g_entities+ENTITYNUM_WORLD);
            assert(spreeChats==1);
            assert(!strcmp(spreeChat,kind==0?"chat \"Victim^g's killing spree ended by ^1TEAMMATE ^7Killer ^gafter ^25 ^gkills!\" -2":"chat \"Victim ^gended his own killing spree after ^25 ^gkills!\" -2"));
        }
        announcerFlags=0;
    }

    Start(0,0);G_NITMOD_LuaShutdown(0);g_gamestate.integer=GS_PLAYING;
    script="et.gentity_set(0,'ps.powerups',1,5000); et.gentity_set(0,'ps.powerups',11,6000)";
    G_NITMOD_LuaInit(0,0,0);assert(clients[0].ps.powerups[PW_INVULNERABLE]==5000 && clients[0].ps.powerups[PW_ADRENALINE]==6000);
    G_Damage(g_entities,g_entities+1,g_entities+1,NULL,NULL,20,0,MOD_BOMB);assert(g_entities[0].health==100);
    G_NITMOD_LuaShutdown(0);script="et.gentity_set(0,'ps.powerups',1,0)";G_NITMOD_LuaInit(0,0,0);
    G_Damage(g_entities,g_entities+1,g_entities+1,NULL,NULL,20,0,MOD_BOMB);assert(g_entities[0].health==90);
    {
        int connected,bot,demo;
        for(connected=0;connected<=2;++connected) for(bot=0;bot<2;++bot) for(demo=0;demo<2;++demo) {
            Start(0,0);G_NITMOD_LuaShutdown(0);
            clients[0].sess.sessionTeam=TEAM_SPECTATOR;clients[0].pers.connected=connected;
            clients[0].pers.nitmodDemoClient=demo;g_entities[0].r.svFlags=bot?SVF_BOT:0;
            g_entities[MAX_CLIENTS].inuse=qtrue;g_entities[MAX_CLIENTS].classname="info_player_intermission";level.num_entities=MAX_CLIENTS+1;
            script="function et_ClientBegin(c) assert(c==0); et.trap_Cvar_Set('death_callback','1') end";
            G_NITMOD_LuaInit(0,0,0);ClientBegin(0);
            assert(callbacks==(connected==CON_CONNECTING && !bot && !demo));
        }
        Start(0,0);G_NITMOD_LuaShutdown(0);script="function et_ClientUserinfoChanged(c) et.trap_Cvar_Set('death_callback','1') end";
        G_NITMOD_LuaInit(0,0,0);configs[CS_PLAYERS][0]=0;ClientUserinfoChanged(0);assert(callbacks==1);
        ClientUserinfoChanged(0);assert(callbacks==1);
        for(demoState=0;demoState<=5;++demoState) {
            demoClients=1;ClientUserinfoChanged(0);
            assert(clients[0].pers.nitmodDemoClient==(demoState>=1 && demoState<=3));
        }
        demoState=demoClients=0;
    }
    {
        int which;
        for(which=0;which<2;++which) {
            Start(0,0);G_NITMOD_LuaShutdown(0);
            script="function et_Quit() et.trap_Cvar_Set('lua_quit','1') end; function et_ShutdownGame() et.trap_Cvar_Set('lua_shutdown','1') end";
            G_NITMOD_LuaInit(0,0,0);quitCallbacks=shutdownCallbacks=0;
            changedCvar=which?aclCvar:moduleCvar;assert(changedCvar);
            G_UpdateCvars();
            assert(G_NITMOD_LuaCount()==0 && quitCallbacks==1 && shutdownCallbacks==0);
            G_UpdateCvars();assert(quitCallbacks==1);
            G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
            G_NITMOD_LuaShutdown(1);assert(quitCallbacks==2 && shutdownCallbacks==1);
        }
    }
    G_NITMOD_LuaShutdown(0);puts("Production client connect/death -> real Lua: spectator initialization, original denial, normal/pushed obituary, XP, Newton and knockback: PASS");return 0;
}
