# Original client/UI Cvar surface

The static registration inventory was extracted from the original i386 cgame
and UI ELF modules. This batch closes every previously missing literal
registration in those two modules: 14 cgame records and 13 UI records.

The cgame module now owns typed handles for `cg_countryflags`,
`cg_optimizePrediction`, `cg_locations`, `cg_logFile`, `cg_clientLog`,
`cg_drawCam`, `cg_locationMaxChars`, `cg_TDMScorePos`, and
`cg_earlyTransition`. The original defaults and archive flags are retained.
Cheat-only diagnostic controls remain registered but are deliberately not
wired to untyped Ghidra drawing code.

The UI registers the original vote controls and all shared Nitmod client
settings used by the unchanged original menu files. `g_mapScriptDirectory`
uses the original empty default and flags zero. Registration uses `NULL`
handles where UI only exposes a cvar to menu scripts and does not consume its
value in C.

`etVersion` and `build` retain original flag value 66 (userinfo plus read-only).
The reconstructed WASM module reports `wasm32` as its build default instead of
misreporting the original `linux-i386` target. This is an intentional platform
difference. No pak/menu/PK3 file is altered.

This closes the static Cvar registration surface, not behavioral parity for
every setting. In particular location-file loading, country-flag rendering,
missile-camera rendering, optimized prediction caches, client disk logging,
and TDM scoreboard positioning still require separately mapped typed paths.
