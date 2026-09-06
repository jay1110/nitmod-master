#include "nitmod_clamp.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
int main(void) {
    int n = 0;
    float f = 0;
    NITMOD_ClampInteger(&n, 1.9f, 10); assert(n == 1);
    n = 0; NITMOD_ClampInteger(&n, -10, -1.9f); assert(n == -1);
    n = 0; NITMOD_ClampInteger(&n, 10, 5); assert(n == 5);
    n = INT_MAX; NITMOD_ClampInteger(&n, 0, 2147483648.f); assert(n == INT_MAX);
    n = 0; NITMOD_ClampInteger(&n, INFINITY, INFINITY); assert(n == INT_MIN);
    n = 42; NITMOD_ClampInteger(&n, NAN, NAN); assert(n == 42);
    NITMOD_ClampFloating(&f, 10, 5); assert(f == 5);
    f = NAN; NITMOD_ClampFloating(&f, 0, 1); assert(isnan(f));
    NITMOD_ClampInteger(NULL, 0, 1); NITMOD_ClampFloating(NULL, 0, 1);
    puts("WASM clamp: truncation, sequential bounds, precision and invalid conversion passed");
    return 0;
}
