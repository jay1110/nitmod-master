#ifndef NITMOD_SUPPORT_TIME_H
#define NITMOD_SUPPORT_TIME_H
#include <stdint.h>

/* Original support counters use 32-bit imul/add/sub. Unsigned arithmetic
 * preserves these bits without signed overflow or an out-of-range int cast. */
static int NITMOD_SupportSignedTime(uint32_t bits) {
 return bits <= UINT32_C(0x7fffffff) ? (int)bits :
  -1 - (int)(UINT32_C(0xffffffff) - bits);
}
static int NITMOD_SupportAddTime(int remaining, int seconds) {
 return NITMOD_SupportSignedTime((uint32_t)remaining + (uint32_t)seconds * UINT32_C(1000));
}
static int NITMOD_SupportDecayTime(int remaining, int elapsed) {
 int next=NITMOD_SupportSignedTime((uint32_t)remaining - (uint32_t)elapsed);
 return next < 0 ? 0 : next;
}
#endif
