# Building Nitmod

The historical 2.60 build remains `src_2.60/SConstruct`.  The CMake entrypoint
is `src_2.60/CMakeLists.txt` and is the supported route for modern native and
WASM module builds.

Native i386 example (inside a Linux image with a 32-bit toolchain):

```sh
cmake -S src_2.60 -B build/i386 -DNITMOD_ARCH=i386 \
  -DCMAKE_C_COMPILER=i686-linux-gnu-gcc
cmake --build build/i386
```

## Reproducible Linux-i386 container

The source-controlled [Dockerfile](../tools/linux-i386/Dockerfile) contains the
required Debian multilib compiler, CMake and Python test runtime. On a host
with Docker, run:

```powershell
.\tools\build_linux_i386_container.ps1
```

It builds the image, mounts the current checkout, produces the three native
i386-named modules under `build/linux-i386`, and runs CTest inside the
container. All targets, including test executables, are built before CTest.
The driver fails on configuration/build/test errors or an empty test suite,
then checks that all three output headers identify little-endian ELF32 i386
shared objects. `readelf` then verifies that `vmMain` and `dllEntry` are
defined, externally visible dynamic function symbols in each module.
Linux targets explicitly link libm and reject unresolved link symbols.
These checks do not certify calling conventions or full ABI compatibility.
The container also enables `NITMOD_REQUIRE_LINUX_I386`: configure rejects
non-Linux/WASM targets, a non-i386 suffix or non-32-bit pointers. A fresh
compiler probe requires Linux/i386 predefined macros, 8-bit bytes and
32-bit int/long/pointer/float. This prevents an x64 or non-x86 toolchain
from qualifying solely through output naming. Host source checks leave this
option off; a manually configured release build should enable it explicitly.
Seven host-executed CMake policy cases cover acceptance and rejection;
the successful real Linux compiler probe still awaits a working Linux runtime.
Native Linux CTest also registers individual module-load smoke tests and a
combined load test. They use a compiler-matched executable with
`dlopen(RTLD_NOW | RTLD_LOCAL)`, resolve both entrypoints, retain all requested
handles concurrently and close them in reverse order, including after errors.
They do not call `dllEntry` or `vmMain`; dynamic-loader constructors may run.
A portable fake-loader test exercises the shared orchestration and cleanup
on the host. Passing it is not evidence of successful Linux module loading.
After all build/test/header/export checks, the driver revalidates the three
original SHA-256 values and atomically writes a uniquely named
`build/linux-i386/verification-<id>.json`. It records reconstructed and
original hashes separately, commands, UTC creation time and
`full_parity_verified: false`. Failed runs produce no new success report.
Older reports remain historical evidence, not proof for subsequently changed
files; consumers must compare their hashes with the artifacts being used.
This is a build-verification record, not a final release or gameplay parity
certificate. No real Linux success report has been generated on this host.
The Docker image is not invoked automatically by local builds. Its base tag
and package versions are not pinned; bit-reproducible toolchains remain work.

The previous local `build/linux-i386/Dockerfile` was ignored by Git and is
no longer used. It is left intact; generated output stays under `build/`.

Local verification on 2026-09-02: Docker could not connect to its Linux engine.
Ubuntu WSL startup reported `HCS_E_HYPERV_NOT_INSTALLED` and unavailable
virtualization support. No Linux-i386 build was completed. Enable the required
virtualization/VM platform and start the Linux container engine before retrying.
Host driver tests check command ordering, failure propagation and rejection of
wrong/missing artifact headers and missing/private/undefined entrypoints;
they do not substitute for that Linux run. The export parser has also passed
against all three preserved original ELF modules using host readelf. The new
Linux linker settings have not yet been exercised by a real Linux build.

WASM example (after activating an Emscripten SDK):

```sh
python -B tools/run_wasm_build.py
```

The driver requires emcmake, emcc and cmake in PATH, explicitly enables all
three module targets, disables host CTest executables for this cross-build,
and disables strict native-i386 mode. It builds Debug modules in `build/wasm`
and independently checks all three output files even if targets were up to
date. Missing tools, failed configure/link steps and wrong/missing outputs
fail the command. Browser loading is explicitly not reported as verified.
The initial preflight failed because emcmake/emcc were absent from PATH.
The existing SDK was subsequently located at `C:/Users/micha/emsdk` through
the ET:Legacy cache. Emscripten 4.0.23 now successfully builds all three
modules. Host driver tests still use mocked commands; the separate actual
build and Node validation are recorded in `reference/wasm-first-build.md`.
For this machine, activate the existing SDK in the current terminal with
`& C:/Users/micha/emsdk/emsdk_env.ps1` and make `C:/ninja` available in PATH
before invoking the driver. No machine-wide environment change is required.

The WASM build emits `cgame.mp.wasm32.so`, `ui.mp.wasm32.so` and
`qagame.mp.wasm32.so` as Emscripten side modules. They must be packed by the
existing browser client as raw `.so` side modules, not prelinked into its main
WASM binary.

The WASM configuration enables CMake's shared-library support before creating
MODULE targets, following the local ET:Legacy build reference. Otherwise some
Emscripten CMake toolchains downgrade MODULE libraries to archives and skip
the side-module link step. Internal symbols remain hidden; all six vmMain /
dllEntry definitions now explicitly use default visibility under Emscripten.
Native builds expand this annotation to nothing. No Legacy mod code was copied.
Source-contract tests cover target setup and annotations, not generated WASM
exports or browser loading. The actual build now passes with linker warnings
treated as errors. A stale void declaration of the qboolean-returning
ReviveEntity was removed in favor of a shared g_local.h declaration.
Each WASM target now runs `tools/verify_wasm_module.py` after linking. This
checks the version-1 magic, bounded section/LEB128 framing, dylink/dylink.0
marker and function-kind vmMain/dllEntry exports. It rejects native binaries,
archives, truncated inspected fields and missing/duplicate inspected metadata.
It is deliberately not a full validator of code, indices, imports, section
ordering or dynamic-link metadata contents. An actual Emscripten validation
and browser load remain required. The parser follows the
[core binary format](https://webassembly.github.io/spec/core/binary/modules.html)
and [dynamic-linking convention](https://github.com/WebAssembly/tool-conventions/blob/main/DynamicLinking.md).

## Static WASM import audit

With Node available, compare generated modules to an existing browser engine:

```powershell
node tools/audit_wasm_imports.cjs ../etlegacy/build-wasm/etl.wasm ../etlegacy/build-wasm/etl.js build/wasm/cgame.mp.wasm32.so build/wasm/qagame.mp.wasm32.so build/wasm/ui.mp.wasm32.so
```

This emits JSON with input hashes and per-import provider classifications.
It validates WASM binaries through Node but never instantiates them or executes
engine JavaScript. Exit success means the audit ran, not compatibility: review
unmatched imports and candidate providers. Function signatures, relocation,
syscall ABI and browser execution still require runtime tests. The initial
actual results are recorded in `reference/wasm-import-audit.md`.
When Node is available, native CTest configurations additionally register
`nitmod_wasm_import_audit` for classifier regression tests.

## Executable WASM loader smoke test

After building the side modules, activate Emscripten and Node in PATH and run:

```powershell
python -B tools/run_wasm_load_smoke.py
```

This compiles a standalone MAIN_MODULE=1 Node harness in `build/wasm-load-smoke`
with the actual modules embedded in its virtual filesystem. It runs individual
and simultaneous dlopen/dlsym checks and requires a missing-file control to
fail with exit code 1. The missing-file diagnostic is expected. No ET entrypoint
is called and no browser/engine compatibility is certified. The first successful
SDK execution is recorded in `reference/wasm-load-smoke.md`.
CTest's `nitmod_wasm_load_smoke_driver` tests orchestration with mocked processes;
it does not automatically run the SDK integration test.

Use `python -B tools/run_wasm_load_smoke.py --entrypoints` to additionally
execute dllEntry and seven safe pre-init vmMain branches, individually and
with all modules loaded. The harness uses separate eight-/thirteen-int
function signatures and rejects engine syscalls outside the explicit callback
probes below. This checks real indirect calls, not game initialization or browser ABI.

The entrypoint mode now additionally permits two narrowly checked argv
callbacks for qagame/UI console probes. Each validates the array-slot index,
buffer pointer and capacity, writes a bounded command response, and requires
exactly one call. All other syscalls remain fatal. This verifies these two
module-to-harness round trips, not the actual engine's general syscall ABI.

The production WASM adapters use the browser engine's intptr_t-array callback
contract; native builds retain ET 2.60's variadic callback. Earlier variadic
WASM smoke results describe a superseded transport. See
`reference/wasm-array-syscall-abi.md` for the correction and rebuilt hashes.

Entrypoint mode also runs an isolated bot reachability probe. Success means
the known BOTLIB_START_FRAME boundary was reproduced after seven Cvar updates,
not that bots work. The process stops at that boundary. See
`reference/wasm-botlib-reachability.md` for lifecycle and reachability limits.

The same mode also runs an isolated unsupported-cgame-extension probe. It
requires the exact CG_ERROR string for command 1338 and exits at that callback.
This intentionally exercises an error path, not successful extension support.
Engine gate findings are in `reference/engine-extension-gates.md`.

Entrypoint mode also compares the zero-Cvar bot probe with a typed memorydump
writeback probe. The latter requires the observed Botlib set and engine reset
calls before stopping at the known unsupported frame boundary. This tests
module consumption of callback-written memory, not a live Cvar registry or bots.
Details: `reference/wasm-cvar-writeback.md`.

## Local source-manifest check

With Emscripten and Node active, run
`python -B tools/run_wasm_layout_audit.py ../etlegacy` for a compiled wasm32
layout sample. Separate probes against each tree's own headers compare six
structure sizes, 45 selected fields and two constants. Differences cause exit 1. This does
not validate all fields, flags or the existing engine binary; results and limits
are recorded in `reference/wasm-shared-layout.md`.

For a read-only source-level syscall number comparison, run
`python -B tools/audit_engine_syscall_numbers.py ../etlegacy`.
The JSON includes input hashes, matching/mismatched numbers and missing names.
Schema version 2 also compares vmMain export commands in both directions,
including engine-only extensions and names occupying the same numeric slot.
Exit success means parsing completed, not engine compatibility. It does not
evaluate reachability, dispatcher support, signatures or structure layouts.
See `reference/engine-syscall-numbers.md` for the initial results.

On a Windows development machine, a normal CMake build is useful for checking
that the complete cgame/qagame/ui source manifests and their headers compile:

```powershell
cmake -S src_2.60 -B $env:TEMP/nitmod-260-cmake
cmake --build $env:TEMP/nitmod-260-cmake --config Release
ctest --test-dir $env:TEMP/nitmod-260-cmake -C Release --output-on-failure
```

This is not an i386 release validation: the produced files use the host ABI
even though their compatibility names contain `.i386.so`. Perform the Linux
i386 and Emscripten builds above for release artifacts.

The CTest suite includes `nitmod_protocol_contract`, which protects the
recovered NCS layout, fixed command field counts, parser validation, and
capability gates without needing a live ET engine. `nitmod_reference_artifacts`
also verifies the three supplied original i386 modules by SHA-256.
`nitmod_port_inventory` regenerates the function inventory in a temporary
location and requires it to match the committed forensic ledger exactly.
