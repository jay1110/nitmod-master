/* The longstanding gameplay fixture supplies native variadic engine doubles.
 * Keep that test interface when executing the gameplay code in WASM. Actual
 * browser slot-array ABI is covered separately by the module-load fixture. */
#undef __EMSCRIPTEN__
#include "../src_2.60/game/g_syscalls.c"
