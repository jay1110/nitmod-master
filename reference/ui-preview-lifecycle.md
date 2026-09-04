# UI cinematic preview lifecycle and selection guards

The typed UI_DrawPreviewCinematic previously called PlayCinematic on every
draw whenever previewMovie was greater than -2, including a live handle.
It also indexed the movie list without validating the count or selection.
This is a correction to the existing typed UI, not a new original-Nitmod
feature or a claim of reconstructed cinematic parity.

The corrected lifecycle uses the existing sentinel convention: -1 starts
once, nonnegative handles run/set-extents/draw, and -2 suppresses retries
after a failed start. A valid cinematic selection stops the previous live
handle and resets to -1. If the list becomes empty, oversized, or its selected
entry is invalid/missing, a live preview is stopped once and drawing returns.
No map/clan cinematic path is changed.

Mod, movie, demo and profile selection callbacks now validate counts against
their physical array sizes and reject out-of-range indices before changing
selection or producing side effects. Profile selection additionally rejects
null/empty names before writing ui_profile. Movie/mod/demo start actions keep
the checks from ui-launch-selection-safety.md.

UI_DrawPreviewCinematic and UI_FeederSelection have internal C declarations
for direct linked tests; no VM entrypoint or engine ABI was added.

The full-UI fixture checks one start across ten successful frames, failed
start suppression across ten frames, selection-triggered retry, one-time
cleanup after list removal, invalid counts/entries, invalid selection indices
for all four feeders, valid profile writes, and exact cinematic flags/extents.
Native 90/90 tests and WASM build/Node load probes pass. Actual browser ROQ
decoding and visual behavior remain unverified. Other feeder text lookups,
deleteDemo, command escaping and full UI parity remain open. No pak edits.
