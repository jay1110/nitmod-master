# Original forwarded Nitmod client commands

Original cgame `CG_InitConsoleCommands` registers `playdead`, `dropobj`,
`damage`, `sslogin`, `sslogout`, `sclogin` and `sclogout` without local
handlers. The engine therefore recognizes binds/completion and forwards the
commands to authoritative qagame when `CG_ConsoleCommand` returns false.

The reconstructed cgame now exposes the same surface. This change does not
invent local behavior, alter menu files or modify package assets. Server-side
runtime consumers remain independently gated by their reconstruction status;
`playdead` is now consumed by qagame and uses the original protocol value
`PM_PLAYDEAD` plus persistent `EF_SPARE0`.  The transition lives in shared
`bg_pmove.c`, so server movement and cgame prediction agree.  Entering uses the
death body animation without setting `EF_DEAD`; leaving first verifies a
crouched bounding box and remains down when obstructed.
