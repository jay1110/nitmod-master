# Global player statistics refresh

Original `nitrox_DrawGlobalStats` in sorted/cgame_nitrox.c invalidates
received/requested state when its deadline has passed or the snapshot
client changes. It requests `ggs <client>` and sets a 15000 ms deadline.
The `glstats ... -` branch in sorted/cgame_servercmds.c sets a 5000 ms
deadline. Successful results display the remaining seconds plus one.

The typed client now refreshes the open window on those same conditions,
instead of requesting once and hiding on a followed-player change. At the
exact deadline it retains the current result; the next millisecond triggers
one new request. Missing replies retry after 15 seconds; explicit failure
retries after 5 seconds. The successful-result footer shows the countdown.
The existing engine adapter sends ggs directly as a client command, rather
than passing it through the original console-command dispatcher.

Deadlines use double arithmetic to avoid signed overflow; backward clock
movement triggers a fresh request. Invalid snapshot client IDs suppress the
window without indexing clientinfo or sending a request. These are deliberate
safety differences. No server-side statistics service is implemented here.

Full-cgame tests exercise opening, successful response, both deadline edges,
explicit failure, invalid/followed player transitions, backward time and
INT_MAX using the real drawing and command paths. Browser/server integration
and detailed visual comparison remain open. No pak or reference binary edits.

## Original statistics column typography

The thirteen result columns now use limboFont2 and style 7 as in original
nitrox_DrawGlobalStats. The original measures text at .18*scale but paints
at .19*scale and applies another panel-scale factor to the half-width when
centering during the animation; this asymmetry is preserved. Single-line
headings sit at row 55, two-line headings at 50/60, and values at 80 relative
to panel y. The existing first-font title/status paths remain separate.
The rendering test checks all thirteen numeric values actually use the
second font, including shadow and foreground draws. Browser visual parity
remains unverified.

## Window lifecycle isolation

Original nitrox_GlobalStatsCmd_f changes only its own visibility/animation
state. The port no longer calls the full map reset on opening or finishing
the close animation, so awards and cached statistics survive a toggle.
The full reset still clears both on map/protocol reset. Closing restarts
the animation timestamp only after more than 450 ms since opening; faster
toggles reuse the original timestamp. Backward-clock handling is retained
as defensive behavior. Tests cover six quick/slow close timings and verify
that an active award survives opening, closing and reopening the window.

## Demo playback exclusion

Original nitrox_GlobalStatsCmd_f clears visibility when g_unk_01047aec
(demo playback, also used by original prediction and demo-wallhack guards)
is set. The typed command now rejects demo playback as well. As a defensive
extension, the drawing path closes a previously opened window when playback
starts, preventing refresh commands without another explicit globalstats
invocation. Tests assert no draw or ggs request during either entry path
and no automatic reopening when returning from playback.
