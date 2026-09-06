#include <limits.h>
#include <stdio.h>
#include "nitmod_mapvote_order.h"

int main(void) {
    const int keys[] = { INT_MIN, -1, 0, 1, 123, INT_MAX };
    int flags, left, right;
    for(flags = 0; flags < 32; ++flags) {
        for(left = 0; left < 6; ++left) {
            for(right = 0; right < 6; ++right) {
                int expected = (flags & 8) || left == right ? 0 :
                    (left > right ? -1 : 1);
                if(NITMOD_MapVoteOrderCompare(flags, keys[left], keys[right]) != expected)
                    return 1;
            }
        }
    }
    puts("Mapvote original descending-key comparator: 1152 cases passed");
    return 0;
}
