# Nitmod lagometer layout integration

Original reference: `cgame_ui.c`, `CG_DrawLagometer(float)` at line 7093
and its caller `CG_DrawUpperRight`. The original draws a 48 by 48 panel
at x=592 and the caller's current y, with right HUD placement, shared
HUD_Background/HUD_Border and a fixed border. It does not suppress the
graph just because the server is local.

The live reconstructed cgame now calls the graph after its upper-right
HUD widgets. Both original-server and reconstructed Nitmod HUD modes use
this placement, palette and aspect-preserving right anchor. Stock ET
retains the fixed y=280 texture and local-server suppression. The graph's
sample colors/ranges and sampling remain unchanged. Anchor state is
restored on normal and disabled paths.

The disconnect icon follows the panel; its centered message temporarily
uses the center anchor. The no-prediction label now receives virtual
coordinates instead of already scaled coordinates, avoiding double scaling.

The full cgame fixture exercises the real draw function in 48 combinations:
three protocol modes, four display sizes, local/remote and enabled/disabled.
It checks the actual first render rectangle, background shader, suppression
and anchor restoration. Disconnect rendering and graph sample values are
not covered by that fixture. Optional original numeric ping overlay
(cg_lagometer bit 2) was not ported in that increment. Follow-up correction:
the number is snapshot rate, not ping; it is now implemented as described
in `client-snapshot-rate-runtime.md`.

No UI/qagame protocol, menu or pak asset change is needed. This increment
does not establish browser visual parity or complete HUD parity.
