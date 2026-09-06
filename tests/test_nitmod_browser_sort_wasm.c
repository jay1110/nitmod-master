#include "../src_2.60/ui/ui_nitmod_browser.c"
#include <assert.h>
#include <stdio.h>
uiInfo_t uiInfo;
vmCvar_t ui_netSource;
static int engineCalls;
int trap_LAN_CompareServers(int source,int key,int dir,int a,int b) {
    ++engineCalls; return 7;
}
int main(void) {
    int dir,a,b,c,cases=0;
    const int effective[]={0,0,2,9};
    browserHumans[0]=50; browserHumanKnown[0]=qfalse;
    browserHumans[1]=0; browserHumanKnown[1]=qtrue;
    browserHumans[2]=2; browserHumanKnown[2]=qtrue;
    browserHumans[3]=9; browserHumanKnown[3]=qtrue;
    uiInfo.serverStatus.sortKey=SORT_CLIENTS;
    for(dir=0;dir<2;++dir) {
        uiInfo.serverStatus.sortDir=dir;
        for(a=0;a<4;++a) for(b=0;b<4;++b) {
            int expected=(effective[a]>effective[b])-(effective[a]<effective[b]);
            assert(UI_CompareBrowserServers(a,b)==(dir?-expected:expected));
            for(c=0;c<4;++c)
                if(UI_CompareBrowserServers(a,b)<=0 && UI_CompareBrowserServers(b,c)<=0)
                    assert(UI_CompareBrowserServers(a,c)<=0);
            ++cases;
        }
    }
    assert(engineCalls==0);
    uiInfo.serverStatus.sortKey=SORT_HOST;
    assert(UI_CompareBrowserServers(0,1)==7 && engineCalls==1);
    for(a=0;a<MAX_GLOBAL_SERVERS;++a) {
        browserHumans[a]=17; browserHumanKnown[a]=qtrue;
        browserHumanPending[a]=qtrue; browserHumanStarted[a]=123;
        nitmodNxacStatus[a]=1; nitmodBrowserPlayers[a]=9;
    }
    UI_ResetBrowserStatusCache(AS_FAVORITES);
    assert(nitmodNxacStatusSource==AS_FAVORITES);
    for(a=0;a<MAX_GLOBAL_SERVERS;++a) {
        assert(!browserHumans[a] && !browserHumanKnown[a]);
        assert(!browserHumanPending[a] && !browserHumanStarted[a]);
        assert(nitmodNxacStatus[a]==-1 && !nitmodBrowserPlayers[a]);
    }
    puts("Full browser cache reset: every server slot passed");
    printf("Browser sort: %d comparisons plus transitivity and engine delegation passed\n",cases);
    return 0;
}
