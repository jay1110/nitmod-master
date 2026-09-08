#ifndef NITMOD_BUILD_H
#define NITMOD_BUILD_H
/* Original Windows32 metadata is win-x86. Windows64 must not advertise
 * a 32-bit binary; the pre-existing Linux/WASM branches remain unchanged. */
#if defined(__EMSCRIPTEN__)
#define NITMOD_BUILD_STRING "wasm32"
#elif defined(_WIN64)
#define NITMOD_BUILD_STRING "win-x86_64"
#elif defined(_WIN32)
#define NITMOD_BUILD_STRING "win-x86"
#else
#define NITMOD_BUILD_STRING "linux-i386"
#endif
#endif
