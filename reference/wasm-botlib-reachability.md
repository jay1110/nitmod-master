# Bounded bot frame reachability probe

Executed on 2026-09-02 against the actual rebuilt qagame WASM from
`wasm-array-syscall-abi.md`, using Emscripten 4.0.23 and SDK Node 24.19.0.

The `--entrypoints` smoke driver now starts an additional isolated process:
`module_entrypoints.js --botlib-probe /nitmod/qagame.mp.wasm32.so`.
It installs a narrow array callback, calls BOTAI_START_FRAME at time zero and
requires this exact observed prefix:

1. Seven G_CVAR_UPDATE callbacks with non-null cvar pointers. The callback
   leaves the module's initial zero-valued fields unchanged.
2. BOTLIB_START_FRAME (205), with the zero float bit pattern as its time slot.
3. Stop immediately at that boundary with successful diagnostic exit; any
   unexpected syscall or return before that boundary fails the probe.

This prefix was observed in the actual dynamically loaded module. It confirms
one missing-header syscall is reachable through an exported dispatch command;
it does not claim normal bot operation or a successful bot frame. No GAME_INIT,
map setup or real engine dispatcher ran. The process intentionally stops before
attempting to emulate Botlib or proceeding into further bot behavior.

## Source-path qualifications

- BotAIStartFrame is compiled into the CMake qagame target. Its vmMain dispatch
  does not test bot_enable before calling it.
- G_InitGame and G_ShutdownGame gate BotAISetup/Shutdown on bot_enable, whose
  registered default is 0. This probe bypasses those lifecycle calls.
- trap_AAS_SetCurrentWorld is already a no-op in g_syscalls.c: the syscall line
  is commented out. A source-level call to that helper is not evidence of an
  AAS syscall. The executed trace correctly passes it without a callback.
- BotAILoadMap is commented out at the inspected G_InitGame setup site.
- Legacy's retained BOTLIB_SETUP/LIBVAR_SET imports return dummy success;
  equal syscall numbers alone cannot establish a working Botlib.

The local Legacy server-source search did not find a BOTAI_START_FRAME call
site. Therefore this is not evidence that its ordinary server loop invokes
the failing path, nor proof that a default bot-disabled browser session fails.
The 147 absent qagame enum names must not all be labelled active blockers.

No product bot behavior was silently disabled or replaced with successful
stubs. Resolving actual bot support still requires a backend decision grounded
in recovered behavior and engine capabilities; the test records the boundary.
