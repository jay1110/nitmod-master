# Legacy extension gates and cgame error callback

Inspected the local engine sources on 2026-09-02; no Legacy files changed.

| Engine-only command | Observed source condition |
| --- | --- |
| CG_CONSOLE_COMPLETE_ARGUMENT (1338) | CL_GameCompleteCommand requires cgvm and VM_Ext_IsActive(CG_COMMAND_COMPLETE) |
| CG_LEGACY_CUSTOM (1337) | Only enum/padding declaration found in the inspected src C/header search; no call site found |
| GAME_SNAPSHOT_CALLBACK_EXT (16) | Entity snapshotCallback flag and sv.snapshotCallbackExt; otherwise engine uses baseline GAME_SNAPSHOT_CALLBACK |
| GAME_DEMOSTATECHANGED (15) | SV_DemoStateChanged itself calls unconditionally; callers include demo lifecycle and SV_DemoSupport |

`vm_ext.h:VM_Ext_GetValue` marks a found extension active on lookup, not after
a separate implementation confirmation. `CL_InitCGame` resets the active
flags before initialization; the initial completion entry is qfalse.
Thus merely querying this extension can opt a module into future calls.
Nitmod must not query/activate it before implementing the corresponding handler.

The snapshot extension flag is enabled by G_SNAPSHOT_CALLBACK_EXT in the server
syscall dispatcher. SV_DemoSupport sets demoSupported and immediately calls
SV_DemoStateChanged. Recording/playback entry paths include demoSupported
checks, but this inspection does not prove every lifecycle/reset path is gated.
No universal safety claim is made for all four commands.

## Actual isolated negative test

`run_wasm_load_smoke.py --entrypoints` now adds a fresh Node process which
loads cgame, installs an array callback and deliberately calls vmMain(1338).
The actual module emits CG_ERROR with the exact text
`vmMain: unknown command 1338`. The callback verifies both slots and stops
the process at that boundary; a different callback or normal return fails.

This passed using Emscripten 4.0.23 / Node 24.19.0 and the cgame artifact hash
recorded in `wasm-array-syscall-abi.md`. It exercises the real cgame error
formatter, syscall adapter and module-owned string pointer across the WASM
boundary. It is not a test of the browser engine's error recovery and does not
add extension support. Existing positive and bot-boundary probes still pass.

All 74 host CTests and the protocol contract check pass. No production enums,
extension capabilities or error behavior were changed.
