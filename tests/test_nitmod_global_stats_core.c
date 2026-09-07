#include "g_local.h"
#include "nitmod_stats_transport.h"
#include <assert.h>
#undef vsnprintf
int Q_vsnprintf(char *out,int size,const char *fmt,va_list args) { return vsnprintf(out,size,fmt,args); }
gentity_t g_entities[MAX_GENTITIES];level_locals_t level;
vmCvar_t g_gamestate;
static gclient_t client;
static const char *guid="PP000000000000000000000000000000",*argument="0";
static char packet[1024],reply[256];static int starts,result,hooks;
static char popup[64];static int popups;
static char upload[512];static int uploads,uploadOK=1;
int NITMOD_StatsUpload(const char *url,const char *text) { ++uploads;Q_strncpyz(upload,text,sizeof(upload));return uploadOK; }
void Com_Error(int code,const char *fmt,...) { abort(); }
void Com_Printf(const char *fmt,...) {}
void trap_Cvar_VariableStringBuffer(const char *n,char *out,int size) { Q_strncpyz(out,"http://localhost",size); }
int trap_Argc(void) { return 2; }
void trap_Argv(int n,char *out,int size) { Q_strncpyz(out,argument,size); }
void trap_SendServerCommand(int n,const char *text) { if(n==-1) { ++popups;Q_strncpyz(popup,text,sizeof(popup));return; } assert(n==0);Q_strncpyz(reply,text,sizeof(reply)); }
int NITMOD_StatsStart(int n,const char *url,const char *id) { ++starts;return 1; }
void NITMOD_StatsCancel(int n) { result=0; }
int NITMOD_StatsRead(int n,char *out,int size) { int r=result;result=0;Q_strncpyz(out,packet,size);return r; }
void G_NITMOD_LuaReceivedGlobalStats(int n,const char *text) { assert(n==0);++hooks; }
static void Receive(const char *text) {
    G_NITMOD_GlobalStatsReset(0);G_NITMOD_GlobalStatsRequest(0,guid);
    Q_strncpyz(packet,text,sizeof(packet));result=1;G_NITMOD_GlobalStatsFrame();
    assert(G_NITMOD_GlobalStatsCommand(0,"ggs"));
}
int main(void) {
    const char *bad[]={
        "PP000000000000000000000000000000 0 1",
        "QQ000000000000000000000000000000 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14",
        "PP000000000000000000000000000000 0 1 2 3 4 5 6 7 8 9 10 11 12 13 2147483648",
        "PP000000000000000000000000000000 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 extra"};
    int i;
    level.maxclients=1;g_entities[0].client=&client;G_NITMOD_GlobalStatsInit();
    for(i=0;i<4;++i) { Receive(bad[i]);assert(!hooks && !strcmp(reply,"glstats 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n")); }
    i=starts;level.time=3000;G_NITMOD_GlobalStatsRequest(0,guid);assert(starts==i);
    level.time=3001;G_NITMOD_GlobalStatsRequest(0,guid);assert(starts==i+1);
    G_NITMOD_GlobalStatsRequest(0,guid);assert(starts==i+1);
    Receive("PP000000000000000000000000000000 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14\r\n");
    assert(hooks==1 && !strcmp(reply,"glstats 0 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14\n"));
    G_NITMOD_GlobalStatsFrame();assert(hooks==1);
    argument="99999999999999999999";*reply=0;G_NITMOD_GlobalStatsCommand(0,"ggs");assert(!*reply);
    G_NITMOD_GlobalStatsReset(0);result=1;G_NITMOD_GlobalStatsFrame();assert(hooks==1);
    argument="0";
    {
        static gclient_t victim;
        level.maxclients=2;g_entities[1].client=&victim;
        client.sess.sessionTeam=TEAM_AXIS;victim.sess.sessionTeam=TEAM_ALLIES;
        g_gamestate.integer=GS_PLAYING;
        G_NITMOD_GlobalStatsDeath(1,0,MOD_SATCHEL);
        G_NITMOD_GlobalStatsCommand(0,"ggs");
        assert(!strcmp(reply,"glstats 1025 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0\n"));
        argument="1";G_NITMOD_GlobalStatsCommand(0,"ggs");
        assert(!strcmp(reply,"glstats 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0\n"));
        g_entities[1].r.svFlags=SVF_BOT;G_NITMOD_GlobalStatsDeath(1,0,MOD_SATCHEL);
        argument="0";G_NITMOD_GlobalStatsCommand(0,"ggs");
        assert(!strcmp(reply,"glstats 1025 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0\n"));
        g_entities[1].r.svFlags=0;victim.sess.sessionTeam=TEAM_AXIS;
        G_NITMOD_GlobalStatsDeath(1,0,MOD_SATCHEL);G_NITMOD_GlobalStatsCommand(0,"ggs");
        assert(!strcmp(reply,"glstats 1029 1 0 1 0 0 0 0 0 0 0 0 0 1 0 0\n"));
        G_NITMOD_GlobalStatsDeath(0,0,MOD_SUICIDE);G_NITMOD_GlobalStatsCommand(0,"ggs");
        assert(!strcmp(reply,"glstats 1029 1 1 1 0 0 0 0 0 0 0 0 0 1 0 0\n"));
        G_NITMOD_GlobalStatsReset(0);G_NITMOD_GlobalStatsReset(1);level.maxclients=1;
    }
    {
        /* Independent decoded ELF rows, including blank award 2. */
        const int indices[]={0,0,2,4,5,6,7,8,9,10,12,13};
        const int thresholds[]={1,100,1,1,1,1,1,1,1,1,1,100};
        int row,j;char input[512],expected[64];
        for(row=0;row<12;++row) {
            Q_strncpyz(input,guid,sizeof(input));
            for(j=0;j<15;++j) Q_strcat(input,sizeof(input),va(" %i",j==indices[row]?thresholds[row]-1:0));
            Receive(input);popups=0;g_gamestate.integer=GS_PLAYING;
            G_NITMOD_GlobalStatsEvent(0,indices[row]);
            Com_sprintf(expected,sizeof(expected),"popaw 0 %i",row);
            assert(popups==1 && !strcmp(popup,expected));
            G_NITMOD_GlobalStatsCommand(0,"ggs");
            Com_sprintf(expected,sizeof(expected),"glstats %i ",(1<<row)|(row==1?1:0));
            assert(!strncmp(reply,expected,strlen(expected)));
            G_NITMOD_GlobalStatsEvent(0,indices[row]);assert(popups==1);
        }
        G_NITMOD_GlobalStatsReset(0);popups=0;
        g_gamestate.integer=GS_WARMUP;G_NITMOD_GlobalStatsEvent(0,0);
        G_NITMOD_GlobalStatsCommand(0,"ggs");assert(!strcmp(reply,"glstats 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"));
        g_gamestate.integer=GS_PLAYING;G_NITMOD_GlobalStatsEvent(0,0);
        assert(!popups);G_NITMOD_GlobalStatsCommand(0,"ggs");
        assert(!strcmp(reply,"glstats 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"));
        g_entities[0].r.svFlags=SVF_BOT;G_NITMOD_GlobalStatsEvent(0,0);
        G_NITMOD_GlobalStatsCommand(0,"ggs");assert(!strcmp(reply,"glstats 0 NR\n"));
        g_entities[0].r.svFlags=0;
        G_NITMOD_GlobalStatsEvent(0,-1);G_NITMOD_GlobalStatsEvent(0,16);
        G_NITMOD_GlobalStatsReset(0);G_NITMOD_GlobalStatsRequest(0,guid);
        level.time=120001;client.pers.connectTime=1;Q_strncpyz(client.pers.netname,"^1Player Name",sizeof(client.pers.netname));
        G_NITMOD_GlobalStatsUpload(0);assert(!uploads); /* time alone */
        G_NITMOD_GlobalStatsEvent(0,4);g_gamestate.integer=GS_WARMUP;
        G_NITMOD_GlobalStatsUpload(0);assert(!uploads);
        g_gamestate.integer=GS_PLAYING;uploadOK=0;G_NITMOD_GlobalStatsUpload(0);assert(uploads==1);
        uploadOK=1;G_NITMOD_GlobalStatsUpload(0);assert(uploads==2);
        assert(!strcmp(upload,"ps PP000000000000000000000000000000 0 0 0 2 1 0 0 0 0 0 0 0 0 0 0 0 ^1Player Name"));
        G_NITMOD_GlobalStatsUpload(0);assert(uploads==2);
        G_NITMOD_GlobalStatsCommand(0,"ggs");assert(!strcmp(reply,"glstats 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"));
    }
    G_NITMOD_GlobalStatsShutdown();puts("Stats core validation/retry/reset, 12 original award thresholds/masks, warmup/bot gates and pending local totals: PASS");return 0;
}
