#ifndef NITMOD_CLAMP_H
#define NITMOD_CLAMP_H
#include <limits.h>

/* Original i386 ClampInt sets x87 rounding control to truncate (0x0c00).
 * Invalid masked FISTP conversion yields the integer-indefinite value.
 * Check in double precision: (float)INT_MAX is already 2147483648. */
static int NITMOD_ClampIntegerBound(float bound) {
    if(!((double)bound >= INT_MIN && (double)bound <= INT_MAX)) return INT_MIN;
    return (int)bound;
}
static void NITMOD_ClampInteger(int *value, float minimum, float maximum) {
    if(!value) return;
    if((double)*value < minimum) *value = NITMOD_ClampIntegerBound(minimum);
    if((double)*value > maximum) *value = NITMOD_ClampIntegerBound(maximum);
}
static void NITMOD_ClampFloating(float *value, float minimum, float maximum) {
    if(!value) return;
    if(*value < minimum) *value = minimum;
    if(*value > maximum) *value = maximum;
}
#endif
