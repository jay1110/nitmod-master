#include "nitmod_skills.h"
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

/* Exact rational oracle for original binary32 .15 and .25 table entries. */
static int expected(int now, int duration, int mask, int bypass, int war, int *stamp) {
    const long long denominator=33554432LL;
    long long cost=(long long)duration*((mask&2) ? 5033165 : 8388608);
    long long elapsed=(long long)now-*stamp;
    if(bypass || war==1 || war==3) return 1;
    if(elapsed>duration) { *stamp=now-duration; elapsed=duration; }
    if(elapsed*denominator<cost) return 0;
    *stamp=(int)(((long long)*stamp*denominator+cost)/denominator);
    return 1;
}
int main(void) {
    const int durations[]={0,1,1000,40000,60001};
    const int times[]={-100000,0,100000};
    const int available[]={-1,0,1,149,150,151,250,6000,6001,10000,40000,90000};
    int table,mask,d,t,a,war,bypass,repeat,count=0;
    for(table=NITMOD_TABLE_AMMO;table<=NITMOD_TABLE_HEALTH;++table)
    for(mask=0;mask<64;++mask)
    for(d=0;d<5;++d)
    for(t=0;t<3;++t)
    for(a=0;a<12;++a)
    for(war=-1;war<=5;++war)
    for(bypass=0;bypass<2;++bypass) {
        float fraction;
        int actual=times[t]-available[a], reference=actual;
        assert(NITMOD_GameplayTableValue(table,mask,&fraction));
        for(repeat=0;repeat<3;++repeat) {
            int result=expected(times[t],durations[d],mask,bypass,war,&reference);
            assert(NITMOD_ApplyChargeCost(times[t],durations[d],fraction,bypass,war,&actual)==result);
            assert(actual==reference);
            ++count;
        }
    }
    {
        int stamp=42;
        assert(NITMOD_ApplyChargeCost(0,1,0.25f,0,0,NULL)==-1);
        assert(NITMOD_ApplyChargeCost(0,-1,0.25f,0,0,&stamp)==-1 && stamp==42);
        assert(NITMOD_ApplyChargeCost(0,1,NAN,0,0,&stamp)==-1 && stamp==42);
        assert(NITMOD_ApplyChargeCost(0,1,INFINITY,0,0,&stamp)==-1 && stamp==42);
        assert(NITMOD_ApplyChargeCost(0,1,-0.25f,0,0,&stamp)==-1 && stamp==42);
        assert(NITMOD_ApplyChargeCost(0,1,1.1f,0,0,&stamp)==-1 && stamp==42);
        assert(NITMOD_ApplyChargeCost(0,-1,NAN,1,0,&stamp)==1 && stamp==42);
        stamp=INT_MIN;
        assert(NITMOD_ApplyChargeCost(INT_MAX,40000,0.25f,0,0,&stamp)==1);
        assert(stamp==INT_MAX-30000);
    }
    printf("Charge calculation: %d rational-oracle table/timing/bypass/repeat cases passed\n",count);
    return 0;
}
