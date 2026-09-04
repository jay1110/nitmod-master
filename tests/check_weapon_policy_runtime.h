#include "g_nitmod_teamcount.h"

static int policyValues[11], policyBadInput;
static int policyMedicOptions;
static int policyClassMode, policyClassPrints;
static const char *policyClassArgs[4];
static char policyClassMessage[512];
static const char *policyNames[] = {
    "g_war", "g_pickAnyWeapon", "g_weapons", "g_heavyWeaponRestriction",
    "sv_maxclients", "team_panzerRestriction", "team_maxPanzers",
    "team_maxFlamers", "team_maxMG42s", "team_maxMortars", "team_maxriflegrenades"
};
static int QDECL PolicyRuntimeEngine(int command, ...) {
    va_list args;
    const char *name;
    char *output;
    int size, i;
    if(policyClassMode && command==G_ARGC) return policyClassMode==1 ? 1 : 4;
    if(policyClassMode && command==G_ARGV) {
        va_start(args,command); i=va_arg(args,int); output=va_arg(args,char *);
        size=va_arg(args,int); va_end(args);
        Q_strncpyz(output,i>=0 && i<4 ? policyClassArgs[i] : "",size); return 0;
    }
    if(policyClassMode && command==G_SEND_SERVER_COMMAND) {
        va_start(args,command); i=va_arg(args,int); name=va_arg(args,const char *);
        if(i!=0) exit(2);
        Q_strncpyz(policyClassMessage,name,sizeof(policyClassMessage));
        ++policyClassPrints; va_end(args); return 0;
    }
    if(command != G_CVAR_VARIABLE_STRING_BUFFER) {
        fprintf(stderr,"unexpected weapon policy syscall %d\n",command); exit(2);
    }
    va_start(args,command); name=va_arg(args,const char *);
    output=va_arg(args,char *); size=va_arg(args,int); va_end(args);
    if(!strcmp(name,"g_medics")) { Com_sprintf(output,size,"%d",policyMedicOptions); return 0; }
    for(i=0;i<11;++i) if(!strcmp(name,policyNames[i])) {
        if(policyBadInput) Q_strncpyz(output,"invalid",size);
        else Com_sprintf(output,size,"%d",policyValues[i]);
        return 0;
    }
    fprintf(stderr,"unexpected weapon policy cvar %s\n",name); exit(2);
    return 0;
}
static int CheckWeaponPolicyRuntime(void) {
    static level_locals_t savedLevel;
    static gclient_t clients[4], before;
    gentity_t savedEntities[4];
    vmCvar_t savedHeavy=g_heavyWeaponRestriction;
    vmCvar_t savedDual=g_dualSMG;
    static const int weapons[]={WP_PANZERFAUST,WP_FLAMETHROWER,WP_MOBILE_MG42,WP_MORTAR,WP_GPG40,WP_M7};
    int w, cap, count, i, team, disabled, errors=0;
    savedLevel=level; memcpy(savedEntities,g_entities,sizeof(savedEntities));
    memset(&level,0,sizeof(level)); memset(clients,0,sizeof(clients));
    memset(g_entities,0,sizeof(savedEntities));
    level.clients=clients; level.numConnectedClients=4; level.numNonSpectatorClients=4;
    for(i=0;i<4;++i) {
        g_entities[i].client=&clients[i]; g_entities[i].s.number=i;
        level.sortedClients[i]=i; clients[i].pers.connected=CON_CONNECTED;
    }
    memset(policyValues,0,sizeof(policyValues)); policyValues[3]=100; policyValues[4]=8;
    for(i=6;i<11;++i) policyValues[i]=-1;
    policyBadInput=0; dllEntry(PolicyRuntimeEngine);
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(w=0;w<6;++w) for(cap=-1;cap<=3;++cap) for(count=0;count<3;++count) {
        for(i=0;i<4;++i) {
            clients[i].sess.sessionTeam=i==3 ? (team==TEAM_AXIS ? TEAM_ALLIES : TEAM_AXIS) : team;
            clients[i].sess.playerType=PC_SOLDIER;
            clients[i].sess.playerWeapon=WP_NONE; clients[i].sess.latchPlayerWeapon=WP_NONE;
            clients[i].sess.rifleGrenadeStatus=0;
        }
        for(i=6;i<11;++i) policyValues[i]=-1;
        policyValues[w<4 ? 6+w : 10]=cap;
        for(i=1;i<=count;++i) {
            clients[i].sess.playerWeapon=w<4 ? weapons[w] : i==1 ? WP_KAR98 : WP_CARBINE;
            clients[i].sess.rifleGrenadeStatus=1;
        }
        clients[3].sess.playerWeapon=weapons[w]; /* Enemy must not count. */
        clients[0].sess.playerWeapon=weapons[w]; /* Requester must not count. */
        G_NITMOD_RefreshTeamPopulation();
        disabled=cap!=-1 && count>=cap;
        before=clients[0];
        if(G_IsWeaponDisabled(&g_entities[0],weapons[w])!=disabled || memcmp(&before,&clients[0],sizeof(before))) ++errors;
        if(w<4 && G_CanPickupWeapon(weapons[w],&g_entities[0])!=!disabled) ++errors;
        if(w<4 && disabled) {
            gentity_t dropped;
            memset(&dropped,0,sizeof(dropped)); dropped.item=BG_FindItemForWeapon(weapons[w]);
            dropped.count=7; level.time=2000;
            if(Pickup_Weapon(&dropped,&g_entities[0])!=0 || memcmp(&before,&clients[0],sizeof(before))) ++errors;
        }
        G_SetClientWeapons(&g_entities[0],weapons[w],WP_LUGER,qfalse);
        before.sess.latchPlayerWeapon=disabled ? WP_NONE : weapons[w];
        before.sess.latchPlayerWeapon2=WP_LUGER;
        if(memcmp(&before,&clients[0],sizeof(before))) ++errors;
        G_SetClientWeapons(&g_entities[0],weapons[w],WP_LUGER,qfalse);
        if(memcmp(&before,&clients[0],sizeof(before))) ++errors;
    }
    for(i=6;i<11;++i) policyValues[i]=-1;
    for(i=0;i<4;++i) { clients[i].sess.playerWeapon=WP_NONE; clients[i].sess.latchPlayerWeapon=WP_NONE; }
    clients[0].sess.sessionTeam=TEAM_AXIS; G_NITMOD_RefreshTeamPopulation();
    policyValues[6]=0;
    for(i=0;i<=4;++i) {
        policyValues[0]=i;
        if(G_IsWeaponDisabled(&g_entities[0],WP_PANZERFAUST)!=(i!=1)) ++errors;
    }
    policyValues[0]=0; policyValues[6]=-1;
    for(i=PC_SOLDIER;i<=PC_COVERTOPS;++i) for(cap=0;cap<2;++cap) {
        clients[0].sess.playerType=i; policyValues[2]=cap ? 512 : 0;
        if(G_IsWeaponDisabled(&g_entities[0],WP_STEN)!=(i!=PC_COVERTOPS && !cap)) ++errors;
    }
    clients[0].sess.sessionTeam=TEAM_SPECTATOR;
    if(!G_IsWeaponDisabled(&g_entities[0],WP_MP40)) ++errors;
    if(!G_IsWeaponDisabled(NULL,WP_MP40) || !G_IsWeaponDisabled(&g_entities[0],WP_NUM_WEAPONS)) ++errors;
    before=clients[0]; G_SetClientWeapons(&g_entities[0],WP_MP40,WP_NUM_WEAPONS,qfalse);
    if(memcmp(&before,&clients[0],sizeof(before))) ++errors;
    clients[0].sess.sessionTeam=TEAM_AXIS;
    policyBadInput=1; g_heavyWeaponRestriction.integer=100;
    if(G_IsWeaponDisabled(&g_entities[0],WP_MP40)) ++errors; /* Explicit native fallback. */
    /* Real command-table dispatch, not a direct call to the handler. */
    for(policyClassMode=1;policyClassMode<=4;++policyClassMode) {
        clients[0].sess.sessionTeam=policyClassMode==3 ? TEAM_SPECTATOR : TEAM_AXIS;
        clients[0].sess.latchPlayerType=PC_ENGINEER;
        policyClassArgs[0]="setclass";
        policyClassArgs[1]=policyClassMode==1 ? "" : policyClassMode==2 ? "?" : "2";
        policyClassArgs[2]="999"; policyClassArgs[3]="2";
        policyClassPrints=0; policyClassMessage[0]=0; before=clients[0];
        if(!G_commandCheck(&g_entities[0],"setclass",qtrue) || memcmp(&before,&clients[0],sizeof(before))) ++errors;
        if(policyClassPrints!=(policyClassMode==4 ? 0 : 1)) ++errors;
        if(policyClassMode==1 && !strstr(policyClassMessage,"Engineer class")) ++errors;
        if(policyClassMode==2 && !strstr(policyClassMessage,"Selects a class")) ++errors;
        if(policyClassMode==3 && !strstr(policyClassMessage,"Cannot pick a class")) ++errors;
    }
    policyClassMode=0;
    /* Actual spawn equipment: a restricted attachment must not remove its
     * base rifle, and its persisted/client-visible rn state must be zero. */
    policyBadInput=0; policyValues[0]=0; policyValues[2]=0;
    for(i=6;i<11;++i) policyValues[i]=-1;
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team) for(cap=-1;cap<=2;++cap)
    for(count=0;count<=2;++count) {
        int grenade=team==TEAM_AXIS ? WP_GPG40 : WP_M7;
        int rifle=team==TEAM_AXIS ? WP_KAR98 : WP_CARBINE;
        memset(clients,0,sizeof(clients));
        for(i=0;i<4;++i) {
            clients[i].sess.sessionTeam=i==3 ? TEAM_SPECTATOR : team;
            clients[i].ps.clientNum=i;
        }
        clients[0].sess.playerType=PC_ENGINEER; clients[0].sess.playerWeapon=rifle;
        clients[0].sess.rifleGrenadeStatus=1;
        for(i=1;i<=count;++i) {
            clients[i].sess.playerWeapon=i==1 ? WP_KAR98 : WP_CARBINE;
            clients[i].sess.rifleGrenadeStatus=1;
        }
        policyValues[10]=cap; G_NITMOD_RefreshTeamPopulation();
        SetWolfSpawnWeapons(&clients[0]);
        disabled=cap!=-1 && count>=cap;
        if(!COM_BitCheck(clients[0].ps.weapons,rifle) ||
           !!COM_BitCheck(clients[0].ps.weapons,grenade)==disabled ||
           clients[0].sess.rifleGrenadeStatus!=!disabled) ++errors;
        if(disabled && (clients[0].ps.ammo[BG_FindAmmoForWeapon(grenade)] ||
            clients[0].ps.ammoclip[BG_FindClipForWeapon(grenade)])) ++errors;
    }
    policyBadInput=0; policyValues[3]=100;
    policyValues[10]=-1;
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(cap=PC_SOLDIER;cap<PC_COVERTOPS;++cap) for(count=0;count<2;++count) {
        int extra;
        memset(&clients[0],0,sizeof(clients[0]));
        clients[0].sess.sessionTeam=team; clients[0].sess.playerType=cap;
        clients[0].sess.playerWeapon=count ? (team==TEAM_AXIS ? WP_KAR98 : WP_CARBINE) :
            (team==TEAM_AXIS ? WP_MP40 : WP_THOMPSON);
        g_dualSMG.integer=0; SetWolfSpawnWeapons(&clients[0]); before=clients[0];
        extra=before.ps.weapon==WP_MP40 ? WP_THOMPSON : before.ps.weapon==WP_THOMPSON ? WP_MP40 :
            team==TEAM_AXIS ? WP_MP40 : WP_THOMPSON;
        g_dualSMG.integer=1; SetWolfSpawnWeapons(&clients[0]);
        COM_BitSet(before.ps.weapons,extra);
        before.ps.ammo[BG_FindAmmoForWeapon(extra)]=cap==PC_MEDIC ? 0 : GetAmmoTableData(extra)->defaultStartingAmmo;
        before.ps.ammoclip[BG_FindClipForWeapon(extra)]=GetAmmoTableData(extra)->defaultStartingClip;
        if(memcmp(&before,&clients[0],sizeof(before))) ++errors;
    }
    g_dualSMG=savedDual;
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team) for(cap=0;cap<8;++cap)
    for(count=0;count<2;++count) for(w=0;w<2;++w) {
        int primary=team==TEAM_AXIS ? WP_MP40 : WP_THOMPSON;
        int extra=team==TEAM_AXIS ? WP_THOMPSON : WP_MP40;
        int pistol=team==TEAM_AXIS ? WP_LUGER : WP_COLT;
        int akimbo=team==TEAM_AXIS ? WP_AKIMBO_LUGER : WP_AKIMBO_COLT;
        memset(&clients[0],0,sizeof(clients[0]));
        clients[0].sess.sessionTeam=team; clients[0].sess.playerType=PC_MEDIC;
        clients[0].sess.playerWeapon=primary; clients[0].sess.playerWeapon2=akimbo;
        clients[0].sess.skill[SK_LIGHT_WEAPONS]=w ? 4 : 0;
        policyMedicOptions=cap; g_dualSMG.integer=count;
        SetWolfSpawnWeapons(&clients[0]);
        if(!!COM_BitCheck(clients[0].ps.weapons,primary)!=!(cap&4) ||
           !!COM_BitCheck(clients[0].ps.weapons,extra)!=count ||
           clients[0].ps.weapon!=((cap&4) ? (w ? akimbo : pistol) : primary) ||
           !COM_BitCheck(clients[0].ps.weapons,WP_MEDIC_SYRINGE) ||
           !COM_BitCheck(clients[0].ps.weapons,WP_MEDKIT)) ++errors;
    }
    policyMedicOptions=0; g_dualSMG=savedDual;
    for(i=6;i<11;++i) policyValues[i]=-1;
    for(i=0;i<4;++i) {
        clients[i].sess.sessionTeam=TEAM_AXIS;
        clients[i].sess.playerWeapon=clients[i].sess.latchPlayerWeapon=WP_NONE;
        clients[i].sess.rifleGrenadeStatus=0;
    }
    G_NITMOD_RefreshTeamPopulation();
    /* Every weapon and class: war allowlists override pickAny, but not caps. */
    for(team=PC_SOLDIER;team<=PC_COVERTOPS;++team)
    for(cap=1;cap<=4;++cap) for(count=0;count<2;++count)
    for(w=WP_NONE;w<WP_NUM_WEAPONS;++w) {
        int allowed=cap==1 ? w==WP_PANZERFAUST : cap==2 ? (w==WP_GARAND || w==WP_K43) :
            cap==3 ? (w==WP_KAR98 || w==WP_CARBINE) : w==WP_KNIFE;
        clients[0].sess.playerType=team; policyValues[0]=cap; policyValues[1]=count;
        before=clients[0];
        if(G_CanPickupWeapon(w,&g_entities[0])!=allowed || memcmp(&before,&clients[0],sizeof(before))) ++errors;
    }
    policyValues[0]=0; policyValues[1]=1; policyValues[2]=0;
    for(w=1;w<WP_NUM_WEAPONS;++w)
        if(!G_CanPickupWeapon(w,&g_entities[0])) ++errors;
    policyValues[6]=0;
    if(G_CanPickupWeapon(WP_PANZERFAUST,&g_entities[0])) ++errors;
    if(G_CanPickupWeapon(WP_MP40,NULL) || G_CanPickupWeapon(WP_NUM_WEAPONS,&g_entities[0])) ++errors;
    level=savedLevel; memcpy(g_entities,savedEntities,sizeof(savedEntities));
    g_heavyWeaponRestriction=savedHeavy; G_NITMOD_ResetTeamPopulation();
    if(errors) fprintf(stderr,"%d active weapon policy failures\n",errors);
    return errors;
}
