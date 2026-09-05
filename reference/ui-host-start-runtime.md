# Active host-menu startup validation

`UI_RunMenuScript("StartServer")` now resolves a typed launch map before
changing startup cvars. Normal games use `ui_currentNetMap`; campaigns use
the first map of the selected campaign, checked against the current map
catalogue before dereferencing its borrowed pointer.

The previous native path indexed both catalogues without checking bounds,
and read timelimit/respawn defaults from the separate `ui_mapIndex` even
when launching a different map or a campaign. The new path consistently
uses the resolved launch map for all three overrides. An override of zero
or equal to the map default still writes zero, preserving native semantics.
All settings are written before the deferred map command is appended.

Original Nitmod reference: `ui_ui_misc.c` UI_RunMenuScript, decompiled
return sites 0x31129..0x314e2 show the start action, dedicated/PunkBuster
guard, startup cvars, deferred map command and three map-default overrides.
This change preserves that workflow but deliberately hardens its unchecked
selection handling; it is not a claim of byte or full original UI parity.

Rejected states include invalid game IDs, empty/oversized catalogues, out of
range selections, campaigns with no maps, stale/null start-map pointers,
and missing/unsafe map tokens. Rejection writes only `com_errorMessage`,
without setting ui_connecting or appending commands. Map tokens currently
allow ASCII letters, digits, underscores and hyphens, shorter than MAX_QPATH.
This intentionally excludes command separators, whitespace and path syntax.

Tests in `tests/check_ui_host_start.h` execute the real menu dispatcher:
9 game modes x 13 catalogue/input states x 3 override values x 3 dedicated
settings = 1,053 cases. They verify command text, error-only rejection,
the nine startup cvar writes and override-before-command ordering. The
PunkBuster rejection popup is retained unchanged, not covered by these cases.

No new cgame/qagame feature or protocol is claimed here. Browser map loading
and remote-server gameplay still require end-to-end testing. No pak files,
menu assets, original binaries or PK3s were modified.
