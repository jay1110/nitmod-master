# Actual WASM dynamic-load smoke test

Current ABI update: the variadic callback results below are historical.
All three WASM adapters and the current harness now use the engine's array
callback contract. Rebuilt hashes and executed checks are in
`wasm-array-syscall-abi.md`; native adapters remain variadic.

Executed successfully on 2026-09-02 with Emscripten 4.0.23 and the SDK's
Node 24.19.0 runtime. Inputs are the three unchanged side modules hashed in
`wasm-first-build.md`. No original i386 or ET:Legacy files were modified.

`tools/run_wasm_load_smoke.py` compiles the existing
`tests/test_linux_module_load.c` loader as a fresh Emscripten MAIN_MODULE=1
Node executable. The side modules are embedded under `/nitmod/` in its virtual
filesystem. Assertions, fatal linker warnings and memory growth are enabled.
No placeholder import functions are injected.

Executed scenarios:

| Scenario | Result |
| --- | --- |
| Load cgame, find vmMain and dllEntry | exit 0 |
| Load qagame, find vmMain and dllEntry | exit 0 |
| Load ui, find vmMain and dllEntry | exit 0 |
| Keep all three loaded, check both entrypoints per handle | exit 0 |
| Load nonexistent /nitmod/missing.so | expected exit 1 and dlopen diagnostic |

Each scenario starts a fresh Node process. The shared harness uses
RTLD_NOW|RTLD_LOCAL and invokes dlclose in reverse order, including error paths.
Emscripten's dlclose behavior does not establish physical unloading.
Dynamic instantiation and entrypoint lookup work in this harness. It does not
invoke dllEntry/vmMain, initialize syscalls, start maps or access game assets.
MAIN_MODULE=1 provides a broad SDK runtime; success does not establish that the
existing etl.wasm/etl.js supplies identical imports or compatible signatures.
This is not the actual engine and is not a browser test.

The local Legacy reference's `src/sys/sys_web.c:Sys_PreloadGameDlls` uses
dlopen after shell precompilation into Emscripten's preloadedWasm cache. It
targets DEFAULT_MODGAME paths under `/etlegacy` and `/home/web_user/.etlegacy`.
The Node embedded-filesystem test deliberately does not claim to exercise
that browser cache, mod selection or packaging path.

Five host Python tests cover command construction, absent tools, fail-fast
compilation/load steps, mandatory negative-control failure and bad artifacts.
Those tests mock subprocess execution; the five scenarios above were run
separately using the actual compiler and runtime.

## Executed pre-init entrypoint probes

The follow-up `python -B tools/run_wasm_load_smoke.py --entrypoints` also
passed with the same actual SDK and side modules. The optional harness is
`tests/test_wasm_entrypoints.c`; the default load-only mode is unchanged.
It resolves each module's own dllEntry and vmMain with its local dlopen handle,
calls dllEntry with a rejecting syscall callback, then checks these branches:

| Module | Commands | Expected values |
| --- | --- | --- |
| cgame | CG_MESSAGERECEIVED, CG_WANTSBINDKEYS | -1, 0 |
| qagame | GAME_MESSAGERECEIVED, unknown command -1 | -1, -1 |
| ui | UI_GETAPIVERSION, UI_HASUNIQUECDKEY, UI_WANTSBINDKEYS | UI_API_VERSION (4), qtrue, qfalse |

All seven checks passed individually and again with all three modules kept
loaded together (14 checked vmMain calls, six dllEntry calls across four
processes). The missing-file negative control still returned exactly 1.
Command constants come directly from the ET 2.60 public headers. The inspected
dispatch branches either return constants or read zero-initialized binding
state and do not need a world, snapshot, asset or engine callback.

The harness uses the source signatures: qagame vmMain takes eight ints;
cgame/ui take thirteen. Distinct typed indirect calls are required by WASM;
no function-pointer-cast emulation is enabled. dllEntry takes the variadic
integer syscall function pointer used by the current adapters. Any syscall
would print its command and exit 2; none occurred. This does not test the
variadic callback ABI itself because the selected branches never call it.
Actual engine calling conventions, initialization and gameplay remain open.

Verification after this extension: six Python orchestration tests, all 73
host CTests, and the separate actual SDK/Node entrypoint run passed.

## Executed variadic argv callback round trips

The entrypoint harness now additionally exercises two actual module-to-harness
syscall paths. Both passed individually and with all modules loaded, using the
same Emscripten 4.0.23 / Node 24.19.0 setup and unchanged side-module inputs:

| Module entry call | Required callback tuple | Injected response | Expected result |
| --- | --- | --- | --- |
| qagame GAME_CONSOLE_COMMAND | G_ARGV, index 0, non-null char pointer, MAX_TOKEN_CHARS capacity | __nitmod_smoke_unknown__ | qfalse |
| ui UI_CONSOLE_COMMAND | UI_ARGV, index 0, non-null char pointer, MAX_STRING_CHARS capacity | ui_cdkey | qtrue |

The callback decodes the actual variadic int/pointer/int arguments with va_arg,
validates index and exact capacity, and copies a bounded NUL-terminated string
into module-owned memory. Exactly one callback is required per probe; other
commands, repeated calls or malformed tuples exit 2. The default rejecting
callback is restored afterward. This tests the C variadic calling convention
across the dynamically loaded module boundary and pointer-based output in
shared WASM memory, without exporting internal trap functions.

The qagame command is deliberately unknown and returns without gameplay work.
The UI's existing ui_cdkey branch is a no-op returning qtrue; it is not a CD-key
validation test. UI_ConsoleCommand also updates its frame-time fields with the
zero timestamp supplied by the harness. cgame's console entry is snapshot-gated,
so no cgame argv callback claim is made and no snapshot/global state is forged.

The expanded run checks nine vmMain calls individually and again concurrently
(18 total), including four actual argv callbacks. Passing this narrow test
does not establish compatibility with ET:Legacy's engine callback implementation,
other syscall signatures, browser execution, networking or gameplay parity.
