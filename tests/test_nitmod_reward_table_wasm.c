#include "nitmod_reward_table.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
    float values[6];
    unsigned int table, mask;
    int i,cases=0;
    for(table=0;table<729;++table) {
        unsigned int digits=table;
        for(i=0;i<6;++i) { values[i]=(float)(digits%3); digits/=3; }
        for(mask=0;mask<64;++mask) {
            float expected=values[0];
            if((mask&2) && values[1]!=values[0]) expected=values[1];
            if((mask&4) && values[2]!=values[1]) expected=values[2];
            if((mask&8) && values[3]!=values[2]) expected=values[3];
            if((mask&16) && values[4]!=values[3]) expected=values[4];
            if((mask&32) && values[5]!=values[4]) expected=values[5];
            assert(NITMOD_RewardTableValue(values,mask)==expected);
            ++cases;
        }
    }
    printf("Reward table WASM: %d original-branch comparisons passed\n",cases);
    return 0;
}
