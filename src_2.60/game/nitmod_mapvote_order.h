#ifndef NITMOD_MAPVOTE_ORDER_H
#define NITMOD_MAPVOTE_ORDER_H

/* Original G_SortMapsByzOrder, ELF 0x76030: signed descending random
 * key at record +0x94, not the vote_eligible counter at +0x90.
 * This helper receives eligible records only; rejected IDs are filtered out
 * before sorting. Equal keys preserve the existing enumeration order. */
static int NITMOD_MapVoteOrderCompare(int flags, int leftKey, int rightKey) {
    if(flags & 8) return 0;
    if(leftKey > rightKey) return -1;
    return leftKey < rightKey ? 1 : 0;
}

#endif
