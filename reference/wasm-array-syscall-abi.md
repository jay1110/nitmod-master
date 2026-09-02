# WASM engine array callback adapter

## Evidence and change

The local ET:Legacy web engine source uses an array callback:
`src/qcommon/vm.c:VM_DllSyscall(intptr_t *args)` and the Emscripten branch
of `src/sys/sys_main.c:Sys_LoadGameDll` supply that type to dllEntry.
The previous Nitmod WASM adapters expected a variadic callback instead.
Earlier successful variadic smoke tests used a matching test callback and
did not demonstrate compatibility with this different engine contract.

All three production adapters now include `game/nitmod_syscall_abi.h`.
Only under __EMSCRIPTEN__, each syscall invocation constructs command/argument
slots, converting each supplied expression to intptr_t before the call.
The exact call-site arity is used (one through sixteen slots supported);
no va_arg type guessing or reads of nonexistent arguments occur. The array
has automatic lifetime through the synchronous callback and must not be retained.
Existing PASSFLOAT conversions stay at the call sites; raw floats are not
introduced. Native builds retain the original int-returning variadic callback.
No ET:Legacy mod code or engine files were copied or modified.

## Executed verification

- Real Emscripten 4.0.23 builds of all three modules pass post-link checks.
- Complete native Windows host build passes.
- Actual SDK Node loader/entrypoint test passes individually and concurrently.
- qagame G_ARGV and UI UI_ARGV callbacks decode array slots, check command,
  index, pointer and capacity, and write the module-owned output buffer.
- Shared packing tests check one/four/sixteen slots, ordered negative/zero/
  positive integers, negative callback return and single expression evaluation.
- 73/73 host CTests pass; the WASM source contract now protects all adapters
  and the separate native/array typedef branches.

Rebuilt SHA-256 values (supersede the original WASM build hashes):

| Module | SHA-256 |
| --- | --- |
| cgame | 017678ca70a3df9a2a6007c168b76a4fa6058a2788db1074d5a201153ee23528 |
| qagame | b198cf9e87122a28b5d08ea4228f6e679342fbc976881d47c1c9b171e24a8ceb |
| ui | 054f5c5b75f018e825f9fdfe3acbea4249e97073393a5de303c51c6663021f75 |

## Limits

This corrects the callback transport shape, not all engine ABI differences.
Command enum numbering, structure layouts, float bit patterns and all remaining
syscall behaviors still need comparison to the actual browser engine. There
has been no browser initialization, map start or original-binary parity run.
cgame's callback execution remains untested by the pre-init probes.

The inspected Legacy `Sys_CallGameDll` invokes a captured WASM export through
JavaScript with thirteen arguments, rather than its native C function pointer.
Nitmod qagame retains its eight-int vmMain signature; cgame/ui retain thirteen.
Do not infer a native C indirect-call mismatch from that JavaScript path or
change the original native signature merely to match the client modules.
