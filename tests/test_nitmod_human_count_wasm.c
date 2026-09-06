#include "ui_local.h"
#include <assert.h>
#include <stdio.h>
void QDECL Com_Printf(const char *fmt, ...) { }
void QDECL Com_Error(int code,const char *fmt, ...) { assert(0); }
int main(void) {
    const char *players="\\hostname\\test\\\\1 20 Alice\\2 0 Bot\\3 40 Bob";
    assert(UI_ServerHumanCount(players,"")==2);
    assert(UI_ServerHumanCount(players,"\\version\\ET Legacy")==0);
    assert(UI_ServerHumanCount(players,"\\version\\ET Legacy\\humans\\1")==1);
    assert(UI_ServerHumanCount(players,"\\version\\Other\\humans\\1")==2);
    assert(UI_ServerHumanCount("\\humans\\3", "\\version\\ET Legacy\\humans\\1")==3);
    assert(UI_ServerHumanCount("\\humans\\0", "\\version\\ET Legacy\\humans\\1")==0);
    assert(UI_ServerHumanCount("\\humans\\-2", "")==0);
    assert(UI_ServerHumanCount("\\humans\\999", "")==MAX_CLIENTS);
    assert(UI_ServerHumanCount(NULL,NULL)==0);
    puts("Human count WASM: nine precedence, player/bot and bounds cases passed");
    return 0;
}
