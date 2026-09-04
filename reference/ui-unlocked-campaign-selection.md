# Unlocked campaign selection safety

UI_CampaignCount now rejects negative/oversized counts before scanning the
campaign array. UI_SelectedCampaign initializes actual=-1 and preserves it
for missing or locked orders, instead of silently returning physical entry 0.
Null display names return an empty string. Existing order/unlocked matching
semantics are retained; this does not redesign campaign sorting or filtering.

The selection callback validates count, requested row and resolved entry
before stopping a previous cinematic or writing cvars. An invalid previous
campaign index is no longer dereferenced. Out-of-range requests are rejected
instead of clamped into an unrelated campaign. The completion flag now compares
the selected campaign's progress with its own mapCount, not the mapCount of
the physical entry at unlockedCount-1.

These are corrections to the existing typed UI, not new recovered Nitmod
gameplay or protocol. Tests cover empty/oversized lists, locked and nonexistent
orders, differing physical/order indices, valid completion/incompletion with
a different final campaign map count, invalid previous selection, and exact
cvar/stop callbacks. Native 90/90 tests and WASM build/Node entrypoint probes
pass. No pak assets changed. Browser menu testing and complete campaign
filtering/preview parity remain open.
