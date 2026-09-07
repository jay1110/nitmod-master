# Building Nitmod

The repository contains `src_2.60/` (including Lua and SQLite sources), the
complete mod assets in `pak/`, GitHub workflows and required build/runtime tools.
CMake 3.20 or newer and a C/C++ compiler are required. Windows builds support
Visual Studio; Linux builds also require the platform development libraries.

## Native modules

```sh
cmake -S src_2.60 -B build/native -DCMAKE_BUILD_TYPE=Release
cmake --build build/native --config Release --target cgame qagame ui
```

For Linux i386, use a multilib compiler with `-DCMAKE_C_FLAGS=-m32`,
`-DCMAKE_CXX_FLAGS=-m32`, `-DCMAKE_MODULE_LINKER_FLAGS=-m32`,
`-DNITMOD_ARCH=i386` and `-DNITMOD_REQUIRE_LINUX_I386=ON`.
The GitHub workflow provides the Windows, Linux, macOS, Android and WASM recipes.

## WebAssembly

Activate Emscripten and ensure Python 3 and CMake are in PATH, then run:

```sh
python tools/run_wasm_build.py
```

This produces and checks the three side modules under `build/wasm/`.
`tools/nitmod_global_stats_bridge.py` supplies the optional browser statistics
transport; use `--help` for its runtime configuration.

## Local verification

Tests are disabled by default and are not needed to compile the mod.
The local `tests/`, analysis/extraction tools, `reference/`, original binaries
and decompiler output are deliberately ignored. Existing local copies remain
available; a developer with those inputs can enable `-DBUILD_TESTING=ON`.
The unused `companion/` prototype is also local-only.

The complete `pak/` directory stays versioned. Generated binaries and packages
are distributed as build artifacts, rather than committed to Git.
