# UI launch selection safety

Inspection of the typed menu-script handlers and original sorted UI showed
that several familiar actions already exist; this batch does not claim new
Nitmod menu functionality. It fixes unsafe accesses in the current typed
UI_RunMenuScript launch branches.

playMovie and RunMod previously indexed their lists without checking counts
or selection indices. RunDemo checked against the reported count but not
against the physical array limit or a missing entry. Each now requires a
positive count within MAX_MOVIES/MAX_MODS/MAX_DEMOS, a selected index within
that count, and a nonempty entry. Invalid selections have no side effects:
no preview stop, fs_game write, restart or launch command.

For valid inputs the existing commands are retained verbatim. playMovie
also resets previewMovie to -1 after stopping its old handle, so subsequent
UI processing cannot stop the same stale preview handle again. These are
defensive changes to existing typed behavior, not recovered new protocol.

The full-UI fixture runs 72 cases (three actions, six list states and four
indices), with strict engine callbacks checking command text/order parameters,
fs_game writes, preview stops and retained/reset handle state. Native 90/90
tests pass; WASM build and Node load/entrypoint probes pass. This does not
test actual demo/cinematic playback or mod switching inside the browser.

Preview lifecycle and four selection callbacks are now covered separately in
ui-preview-lifecycle.md. Other feeder lookups, launch-name command escaping,
and deleteDemo still require review. No pak assets,
menus, original binaries, or cgame/qagame protocol contracts are modified.
