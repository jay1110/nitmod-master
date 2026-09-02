# Actual Cvar writeback consumption

The entrypoint smoke driver now runs an additional isolated `--cvar-probe`
process against qagame. Executed successfully with Emscripten 4.0.23 and SDK
Node 24.19.0; the production module is unchanged from the array-ABI build.

The pre-init BOTAI_START_FRAME probe receives seven G_CVAR_UPDATE callbacks.
At the seventh, the known memorydump update site, the test writes through the
actual module-provided vmCvar_t pointer: integer=1, value=1.0f, string="1".
It leaves the other cvars and handle/modificationCount untouched. The expected
subsequent callback sequence is checked strictly:

1. BOTLIB_LIBVAR_SET with strings "memorydump", "1".
2. G_CVAR_SET with strings "memorydump", "0".
3. BOTLIB_START_FRAME with zero time bits; stop at this unsupported boundary.

The baseline isolated bot probe leaves memorydump zero and requires neither
of the two set calls. Both probes pass in the actual loaded WASM module.
This demonstrates that a typed callback write reaches module-owned memory and
changes the observed dispatch path, beyond merely matching field offsets.

This is a controlled engine double, not a real engine Cvar registry. Identity
is based on the inspected pre-init callback order, not registered Cvar handles.
Only the integer field's consumption is demonstrated; setting the float/string
consistently does not establish they were read. Set callbacks are observed but
do not mutate a real engine registry or implement Botlib. There is no bot
initialization, completed bot frame, map start or browser verification.

All 75 host CTests and the protocol contract check pass. Production source,
Legacy files and original reference binaries are unchanged by this step.
