/* Real ACK parser, protocol detection, class command and class-list adapter. */
#include "../src_2.60/cgame/cg_consolecmds.c"
#include <assert.h>
#include <stdio.h>
cg_t cg;
cgs_t cgs;
static const char *serverInfo, *args[3];
static const char *playerInfo="";
static int argumentCount=3;
static int selected, sentCommands;
static char sent[128];
const char *CG_ConfigString(int index) {
    if(index>=CS_PLAYERS && index<CS_PLAYERS+MAX_CLIENTS) return playerInfo;
    assert(index==CS_SERVERINFO); return serverInfo;
}
const char *CG_Argv(int index) { return args[index]; }
int trap_Argc(void) { return argumentCount; }
void CG_setClientFlags(void) {}
void CG_NitmodObituaryReset(void) {}
void CG_NitmodHudReset(void) {}
void CG_NitmodGlobalStatsReset(void) {}
void CG_Printf(const char *format,...) {}
void Com_Error(int code,const char *format,...) { abort(); }
void CG_LimboPanel_SetSelectedWeaponNumForSlot(int slot,int number) { assert(slot==0); selected=number; }
void trap_SendClientCommand(const char *text) { ++sentCommands; Q_strncpyz(sent,text,sizeof(sent)); }
weaponType_t *WM_FindWeaponTypeForWeapon(weapon_t weapon) { return NULL; }
void CG_CenterPrint(const char *text,int y,int width) {}

int main(void) {
    static const char *classArgs[]={"s","m","e","f","c"};
    static const int wire[2][5][6]={
      {{3,29,6,5,33,0},{3,8,10,0,0,0},{3,8,22,0,0,0},{3,8,10,0,0,0},{10,31,30,0,0,0}},
      {{8,29,6,5,33,0},{8,3,10,0,0,0},{8,3,23,0,0,0},{8,3,10,0,0,0},{10,31,24,0,0,0}}};
    int original,capable,team,cls,slot,count=0;
    char caps[32],choice[16],expected[128];
    for(original=0;original<2;++original)
    for(capable=0;capable<2;++capable)
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(cls=0;cls<5;++cls) {
        bg_playerclass_t *base=BG_GetPlayerClassInfo(team,cls), saved=*base, *view;
        serverInfo=original ? "\\gamename\\nitmod" : "\\gamename\\nitmod\\nitmod_csLayout\\et260";
        sprintf(caps,"%u",capable ? NITMOD_FEATURE_CLASS_PRIMARIES : NITMOD_FEATURE_SCORE_KD);
        args[0]=NITMOD_CAPABILITIES_ACK_COMMAND; args[1]="1"; args[2]=caps;
        assert(NITMOD_ProtocolCommand(args[0]));
        view=CG_NitmodPlayerClass(team,cls);
        for(slot=0;slot<MAX_WEAPS_PER_CLASS;++slot) {
            int expectedWeapon=original || capable ? (slot<6 ? NITMOD_WeaponFromWire(wire[team-TEAM_AXIS][cls][slot]) : WP_NONE) : base->classWeapons[slot];
            if(view->classWeapons[slot]!=expectedWeapon) {
                fprintf(stderr,"class mismatch original=%d capable=%d team=%d class=%d slot=%d actual=%d expected=%d\n",original,capable,team,cls,slot,view->classWeapons[slot],expectedWeapon);
                return 1;
            }
        }
        assert(!memcmp(base,&saved,sizeof(saved)));
        cg.clientNum=0; cgs.clientinfo[0].team=team;
        for(slot=0;slot<8;++slot) {
            int index=slot>=1 && slot<=6 && view->classWeapons[slot-1] ? slot-1 : 0;
            int weapon=view->classWeapons[index];
            sprintf(choice,"%d",slot);
            args[0]="class"; args[1]=classArgs[cls]; args[2]=choice;
            sentCommands=0;
            CG_NitmodClass_f();
            sprintf(expected,"team %s %i %i \n",team==TEAM_AXIS ? "r" : "b",cls,original ? NITMOD_WeaponToWire(weapon) : weapon);
            assert(sentCommands==1 && selected==index && !strcmp(sent,expected));
            ++count;
        }
        /* Unsupported ACK revokes the new native list immediately. */
        args[0]=NITMOD_CAPABILITIES_ACK_COMMAND; args[1]="2"; args[2]=caps;
        NITMOD_ProtocolCommand(args[0]);
        if(!original) assert(CG_NitmodPlayerClass(team,cls)==base);
        args[1]="1"; NITMOD_ProtocolCommand(args[0]);
        NITMOD_ClearConfigStrings();
        if(!original) assert(CG_NitmodPlayerClass(team,cls)==base);
    }
    printf("Client class negotiation/commands: %d cases passed\n",count);
    return 0;
}
