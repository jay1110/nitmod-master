# Filtered map-row mapping

The typed UI_SelectedMap campaign branch incorrectly iterated mapCount while
accessing campaignList. It now uses campaignCount and validates its physical
limit. The ordinary map branch likewise checks mapCount against MAX_MAPS.
Single-player game-type indexing is checked before accessing gameTypes.

A missing row now returns actual=-1 instead of actual=0. Map-row selection
and image consumers reject that result before accessing another entry or
writing selection cvars. Valid row order remains unchanged: active maps or
campaigns whose typeBits include GT_WOLF. Null display names return empty text.
This is a typed-code correctness fix, not a newly recovered Nitmod feature.

Tests exercise campaignCount differing from mapCount, filtering an intervening
campaign/map, empty/oversized campaign lists, invalid rows and invalid game-type
indices. A strict no-syscall fixture checks that rejected selections do not
produce engine side effects. Native 90/90 tests pass; WASM build and Node
load/entrypoint probes pass. Pak assets remain unchanged.

The separate ordering/unlocked selection and count guards are now covered in
ui-unlocked-campaign-selection.md. Full campaign filtering/preview lifecycle
and browser menu behavior remain open. No complete UI parity claim is made.
