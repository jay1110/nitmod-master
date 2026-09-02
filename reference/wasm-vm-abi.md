# WASM VM ABI declaration and entrypoint correction

The reported `ui.mp.wasm32.so` loader message is a warning about a missing
`vmWasmAbi1` export, not a failed load. The existing WASM syscall adapter
already passes an `intptr_t` command/argument array to the engine callback.

Local ET:Legacy reference sources:

- `src/qcommon/q_shared.h`: `VM_WASM_ABI_VERSION`, `VM_WASM_ABI_EXPORT`.
- `src/sys/sys_main.c`: lookup of the marker and missing-marker warning.
- `src/qcommon/qcommon.h`: `VM_EntryPoint_t`, command plus twelve argument slots.
- `src/web/shell.html`: marker and independent vmMain signature checks.

All three reconstructed modules now export `int vmWasmAbi1(void)` returning
one, only under Emscripten. The existing native variadic syscall ABI is unchanged.
An additional real mismatch was found: qagame's vmMain accepted only eight
integers, while the browser engine calls thirteen. Five ignored trailing slots
are now added for WASM only; the native eight-integer signature is retained.
Neither marker nor signature changes introduce a new gameplay protocol.

## Evidence and limits

- Emscripten builds all three side modules; the post-link artifact verifier now
  requires the marker to be a function export, alongside vmMain and dllEntry.
- Artifact fixtures reject missing or wrong-kind markers. These fixtures test
  framing/exports, not function signatures or complete WASM validity.
- The real Node/Emscripten entrypoint harness calls the marker and checks return
  value one, then calls qagame through the engine's thirteen-integer signature.
  Previously its eight-integer qagame typedef masked the engine mismatch.
- Individual/concurrent loads, pre-init queries, console/argv callbacks and
  array syscall probes passed, including expected missing-file rejection and
  known unsupported botlib/cgame-extension boundaries. Native CTest: 83/83.
- This is not a browser gameplay or full engine ABI/parity certification.

## Deployment

Rebuilt files are `build/wasm/cgame.mp.wasm32.so`,
`build/wasm/ui.mp.wasm32.so`, and `build/wasm/qagame.mp.wasm32.so`.
Publish them together in the site's module distribution and ensure its download
or persistent-filesystem cache refreshes the old Nitmod modules. The logged
`/home/web_user/.etlegacy/nitmod/` path is inside the browser filesystem; a local
build alone does not replace that copy. No remote deployment was performed.
After replacement, verify absence of the missing-marker warning and continue
with map/join/gameplay testing. Original i386 reference artifacts are untouched.
