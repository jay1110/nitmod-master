# WASM import-provider audit

Static audit executed on 2026-09-02 using `tools/audit_wasm_imports.cjs`
and the actual three outputs recorded in `wasm-first-build.md`.
No engine JavaScript was executed and no module was instantiated.

Inspected local ET:Legacy `build-wasm` artifacts (reference only, unchanged):

- etl.wasm SHA-256: `c05ea8bd467864a0a2c73e08a95e34f2a72c27c49da0f78faa74262095025f03`
- etl.js SHA-256: `895d5c5d4e6839419324e38dfcc4d4e1a8ffa0e17ac451e7fb5c59ed8bf151c2`

| Side module | Imports | Engine export name/kind | Loader base convention | Engine symbol via GOT | JS binding candidate | Not found |
| --- | --- | --- | --- | --- | --- | --- |
| cgame | 33 | 30 | 2 | 1 | 0 | 0 |
| qagame | 34 | 31 | 2 | 0 | 1 | 0 |
| ui | 24 | 22 | 2 | 0 | 0 | 0 |

The two bases are `env.__memory_base` and `env.__table_base`; the inspected
JavaScript loader supplies memoryBase/tableBase for these names. The generic
audit labels them as conventions, not verified loader values.
cgame imports `GOT.mem.stdout`, for which the engine exports a global symbol.
qagame imports `env.__assert_fail`; etl.wasm does not export that function.
etl.js contains both the `___assert_fail` function definition and the
`__assert_fail:___assert_fail` runtime binding, so this is recorded separately
as a candidate rather than silently counted as an engine export.

The report includes input hashes and per-import classifications. Constructing
WebAssembly.Module validates the binaries in Node, but does not resolve imports.
Name/kind matches do not validate function signatures, global mutability,
memory/table limits, relocation, loader execution order or ET syscall ABI.
The JavaScript check is a narrow textual heuristic, not JavaScript execution
or semantic analysis. Successful CLI exit means the audit ran, not runtime
compatibility; inspect each import's classification.

Verification: complete Windows host build and 72/72 CTests passed, including
nine classifier cases for namespace/kind mismatches, GOT and missing JS binding.
Browser loading, syscall initialization and gameplay parity remain unverified.
