# UI list counts and text lookup

The typed mod, cinematic, demo, profile and legacy savegame feeders now
validate list counts against their physical arrays. A negative or oversized
count is presented as empty rather than allowing the widget to request
out-of-range rows. Text lookup rejects invalid indices using the same count.
Missing movie/demo names produce an empty string; mod descriptions still
take precedence over names, with an empty fallback if neither exists.
Profile names are checked before copying, cleaning and applying active/default
profile decorations. Other feeder behavior remains unchanged.

This is defensive maintenance of existing typed UI code, not a newly recovered
Nitmod feature. The legacy savegame feeder's code-only numeric identifier is
kept; no original menu header or pak data was changed. UI_FeederCount and
UI_FeederItemText are internally declared for linked tests, not new VM exports.

Tests cover 120 invalid count/index combinations across five feeders,
zeroed output handle counts, valid names, description/name fallback, and
null names. Native 90/90 tests pass; WASM build and Node load/entrypoint
probes pass. Actual browser menu rendering and full original UI parity
remain unverified. Map/campaign/server feeder bounds, deletion paths and
command escaping are still outside this batch.
