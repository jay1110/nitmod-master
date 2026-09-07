#include "cg_local.h"
#include "cg_nitmod_stats.h"
#include <assert.h>
static const char *args[32];
static const char *Arg(int n) { assert(n>=0 && n<32); return args[n]; }
void Com_Error(int code,const char *fmt,...) { abort(); }
void Com_Printf(const char *fmt,...) {}
int main(void) {
    int values[NITMOD_GLOBAL_STAT_COUNT],before[NITMOD_GLOBAL_STAT_COUNT],i;
    qboolean failed=qfalse;
    assert(!strcmp(CG_NitmodGlobalAwardTitle(2),""));
    assert(!strcmp(CG_NitmodGlobalAwardTitle(3),"NEED A MEDIC?"));
    assert(!strcmp(CG_NitmodGlobalAwardTitle(11),"BUTCHER"));
    assert(!strcmp(CG_NitmodGlobalAwardDescription(1),"and it's not over! Hopefully..."));
    assert(!CG_NitmodGlobalAwardTitle(12));
    for(i=0;i<NITMOD_GLOBAL_STAT_COUNT;++i) values[i]=before[i]=123;
    args[0]="glstats";args[1]="0";args[2]="NR";
    assert(CG_NitmodParseGlobalStats(3,Arg,values,&failed) && failed);
    assert(!memcmp(values,before,sizeof(values)));
    args[2]="nr";failed=qfalse;assert(CG_NitmodParseGlobalStats(3,Arg,values,&failed) && failed);
    args[2]="-";failed=qfalse;assert(CG_NitmodParseGlobalStats(3,Arg,values,&failed) && failed);
    args[2]="NR";failed=qfalse;assert(!CG_NitmodParseGlobalStats(4,Arg,values,&failed) && !failed);
    for(i=2;i<NITMOD_GLOBAL_STAT_COUNT+2;++i) args[i]="7";
    assert(CG_NitmodParseGlobalStats(NITMOD_GLOBAL_STAT_COUNT+2,Arg,values,&failed) && !failed);
    for(i=0;i<NITMOD_GLOBAL_STAT_COUNT;++i) assert(values[i]==7);
    memcpy(before,values,sizeof(before));args[NITMOD_GLOBAL_STAT_COUNT+1]="2147483648";
    assert(!CG_NitmodParseGlobalStats(NITMOD_GLOBAL_STAT_COUNT+2,Arg,values,&failed));
    assert(!memcmp(values,before,sizeof(values)));
    puts("Global stats original NR reply, legacy failure, tuple bounds and atomic rejection: PASS");return 0;
}
