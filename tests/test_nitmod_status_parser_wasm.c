/* Actual parser, synthetic protocol inputs; no engine or original replay. */
#include "ui_local.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
void QDECL Com_Printf(const char *fmt, ...) { }
void QDECL Com_Error(int code,const char *fmt, ...) { assert(0); }
static serverStatusInfo_t info;
static void Parse(const char *text) {
    memset(&info,0,sizeof(info));
    Q_strncpyz(info.text,text,sizeof(info.text));
    UI_ParseServerStatus(&info,"example:27960");
}
int main(void) {
    int n,i,row,j,used;
    char input[MAX_SERVERSTATUS_TEXT],expected[16];
    for(n=0;n<=MAX_CLIENTS;++n) {
        strcpy(input,"\\sv_hostname\\Example\\\\"); used=strlen(input);
        for(i=0;i<n;++i)
            used+=snprintf(input+used,sizeof(input)-used,"%s%d %d ^1P%d",i?"\\":"",i,i+1,i);
        assert(used<sizeof(input)); Parse(input);
        assert(info.numLines==4+n);
        for(i=0;i<n;++i) {
            row=4+i;
            snprintf(expected,sizeof(expected),"%d",i);
            assert(!strcmp(info.lines[row][0],expected));
            assert(!strcmp(info.lines[row][1],expected));
            snprintf(expected,sizeof(expected),"%d",i+1);
            assert(!strcmp(info.lines[row][2],expected));
            snprintf(expected,sizeof(expected),"^1P%d",i);
            assert(!strcmp(info.lines[row][3],expected));
        }
        for(row=0;row<info.numLines;++row) for(j=0;j<4;++j)
            assert(info.lines[row][j]!=NULL);
    }
    Parse("\\hostname\\Example\\\\broken\\1 20 Alice");
    assert(info.numLines==4); /* Never borrow fields from the next record. */
    Parse("\\hostname\\Example\\\\1 20 Alice Smith");
    assert(info.numLines==5 && !strcmp(info.lines[4][3],"Alice Smith"));
    Parse(""); assert(info.numLines==3);
    memset(input,'x',sizeof(input)); input[sizeof(input)-1]=0;
    Parse(input); assert(info.numLines<=MAX_SERVERSTATUS_LINES);
    puts("Status parser WASM: 0..64 players, malformed record, spaced name and boundary inputs passed");
    return 0;
}
