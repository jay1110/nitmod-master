# Numeric lagometer snapshot rate

Original cgame_snapshot.c computes 1000 / (nextSnap.serverTime -
snap.serverTime) when cg_lagometer bit 2 is enabled, publishing the latest
value after strictly more than 1000 ms. Original cgame_ui.c draws that
value only with current and next snapshots available. This is a snapshot
interval-derived rate, not ping and not a counted average of received packets.

The native snapshot transition now feeds a bounded accumulator. The
Nitmod lagometer draws the published number at scale .15 in its right-anchored
panel, with a right-aligned inset to keep digits inside the panel. The
existing map/HUD reset clears all rate state. Plain ET HUD is unchanged.

Deliberate hardening: nonpositive intervals do not divide; arithmetic uses
double to avoid signed subtraction overflow; a backward clock clears stale
values. Native snapshot handling still owns rejection of invalid snapshots.

Tests check strict refresh boundary, 20/25/1000 rates, zero/reversed
intervals, disabled sampling, backward time and reset. Existing lagometer
layout tests cover protocol/aspect/local-server placement; they do not
verify numeric glyph output. Browser visual validation remains outstanding.
No UI/qagame protocol, menu or original asset changes.
