#define main ExistingLuaMain
#include "test_nitmod_lua.c"
#undef main
#include <emscripten.h>
#include "g_nitmod_global_stats.h"
static int baseline,phase,ticks;
vmCvar_t g_gamestate;
static const char *guid="PP000000000000000000000000000000";
static void Tick(void) {
    ++ticks; assert(ticks<600);
    G_NITMOD_GlobalStatsFrame();
    if(!phase && frames==baseline+1) {
        assert(G_NITMOD_GlobalStatsCommand(3,"ggs"));
        assert(!strcmp(statsReply,"glstats 0 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14\n"));
        G_NITMOD_GlobalStatsFrame();assert(frames==baseline+1);
        G_NITMOD_GlobalStatsEvent(3,4);
        G_NITMOD_GlobalStatsUpload(3);
        G_NITMOD_GlobalStatsReset(3);
        G_NITMOD_GlobalStatsRequest(3,guid);
        G_NITMOD_GlobalStatsReset(3); /* response cannot enter a reused client slot */
        G_NITMOD_GlobalStatsCommand(3,"ggs");assert(!strcmp(statsReply,"glstats 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"));
        phase=ticks;
    }
    if(phase && ticks>phase+10) {
        assert(frames==baseline+1);
        G_NITMOD_LuaShutdown(0);G_NITMOD_GlobalStatsShutdown();
        emscripten_cancel_main_loop();
        puts("WASM fetch -> HTTP bridge -> UDP -> game cache -> real Lua callback -> client reply, cancellation: PASS");
        return;
    }
}
int main(int argc,char **argv) {
    assert(argc==2);ExistingLuaMain();
    EM_ASM({ if(typeof process!=="undefined" && process.versions?.node) { const original=globalThis.fetch; globalThis.fetch=(url,options)=>original(url,{...options,headers:{Origin:"http://nitmod-test.local"}}); } });
    fixtureStatsURL=argv[1];fixtureArgument="3";modules="test.lua";level.maxclients=4;
    source="function et_ReceivedGlobalStats(c,s) assert(c==3 and s=='0 1 2 3 4 5 6 7 8 9 10 11 12 13 14'); et.trap_Cvar_Set('frame','1') end";
    G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);baseline=frames;
    G_NITMOD_GlobalStatsInit();
    g_gamestate.integer=GS_PLAYING;level.time=120000;g_entities[3].client->pers.connectTime=0;
    Q_strncpyz(g_entities[3].client->pers.netname,"E2E Player",sizeof(g_entities[3].client->pers.netname));
    G_NITMOD_GlobalStatsRequest(3,"invalid");
    G_NITMOD_GlobalStatsRequest(3,guid);G_NITMOD_GlobalStatsRequest(3,guid);
    emscripten_set_main_loop(Tick,60,1);return 0;
}
