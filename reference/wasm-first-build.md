# First verified local WASM build (2026-09-02)

The previously PATH-invisible toolchain was found via the local ET:Legacy
CMake cache: `C:/Users/micha/emsdk`, Emscripten 4.0.23, Node 24.19.0,
and `C:/ninja/ninja.exe`. Environment variables were set only in the build
process; no system configuration or SDK installation was changed.

`tools/run_wasm_build.py` completed a real Debug build of cgame, qagame and
ui from src_2.60. The first link exposed a signature mismatch: g_svcmds.c
declared ReviveEntity as void while its implementation returns qboolean.
g_local.h now owns the consistent declaration. Emscripten targets now use
`--fatal-warnings`; the subsequent build passed without linker warnings.
This fixes the interface, not revive gameplay semantics.

All outputs passed the post-link framing/dylink/export checks. Node's
WebAssembly.Module constructor also successfully validated each complete
binary and reported both vmMain and dllEntry as function exports:

| Artifact under build/wasm | Bytes | Imports | SHA-256 |
| --- | ---: | ---: | --- |
| cgame.mp.wasm32.so | 2423183 | 33 | 9ba0636986714bd44ae53cec45f38d31cde481bfb08c03a24286a1a3b11f055a |
| qagame.mp.wasm32.so | 3422867 | 34 | 8585da03d515b9e83df0b5ad03dba7f2e54a5dd72770b4ee3c5a555c418cee63 |
| ui.mp.wasm32.so | 775707 | 24 | 35b1b344d7853c6d86043539a7ae3307e81e2b622ec138fd09a54c854f24b7cf |

These hashes identify this build only, not reproducible or original-byte
parity. Outputs remain ignored build products. The full Windows host build
and 71/71 CTests also pass with the shared signature correction.

Node validation did not instantiate the modules or resolve their imports.
No engine entrypoint, browser gameplay or companion bridge was executed.
Compiler warnings from historical source remain; only linker warnings are
fatal. Full Nitmod reconstruction, browser integration and Linux-i386 build
remain unfinished. No Legacy mod source was copied.
