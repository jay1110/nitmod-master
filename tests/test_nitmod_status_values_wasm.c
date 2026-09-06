#include "ui_local.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static const char *value;
void QDECL Com_Printf(const char *fmt, ...) { }
void QDECL Com_Error(int code,const char *fmt, ...) { assert(0); }
int trap_LAN_ServerStatus(const char *address,char *out,int size) {
    if(!out) return 0;
    snprintf(out,size,"\\g_gametype\\%s\\sv_hostname\\Test",value);
    return 1;
}
int main(void) {
    const char *values[]={"2","4","6","0002","unknown","-1","999"};
    serverStatusInfo_t info;
    int i,row,found;
    for(i=0;i<7;++i) {
        value=values[i]; found=0;
        assert(UI_QueryServerStatus("test",&info));
        for(row=0;row<info.numLines;++row)
            if(!strcmp(info.lines[row][0],"Game type")) {
                assert(!strcmp(info.lines[row][3],value)); ++found;
            }
        assert(found==1);
    }
    puts("Server status WASM: seven raw gametype values preserved");
    return 0;
}
