# Browser list and refresh lifecycle

The production server display-list block is extracted from ui_main.c into
ui_nitmod_browser.c, built by both CMake and SCons. It retains the existing
Nitmod/NxAC filters and asynchronous status classification. This is an
integration and hardening pass, not a claim that all browser behavior is new.

Original UI_BuildServerDisplayList (ui_ui_misc.c) contains the sorted insertion
and favorites removal inline. The decompiled labels 0x24c1d..0x2500e show
comparison, insertion and list shifting. The old native port likewise assumed
LAN comparisons return exactly -1/0/1. The new adapter accepts any signed
comparison result, preserving the original ordering for normalized results.

Each engine server index now owns one player-count contribution, replaced on
later replies rather than added again. Pending NxAC requests roll back that
contribution until answered. Totals still include filtered replies, matching
the existing original policy. Negative counts clamp to zero and oversized
counts to MAX_CLIENTS. These are deliberate hardening differences.

Changing LAN source resets list, selected row, status cache and count ledger.
Master counts are bounded by MAX_GLOBAL_SERVERS; any negative count is treated
as pending. Pending refresh deadlines saturate rather than overflowing. List
insert/remove validate their bounds before accessing storage.

The complete UI fixture exercises existing 128 filter combinations, asynchronous
NxAC replies and the final list slot. New scenarios repeatedly rebuild favorite
lists of 1..128 servers, ascending/descending with comparator values +19/-7,
eight updates each, including negative/oversized and changing player counts.
Every row and total is checked; source changes and maximum clock values are
also tested. Live master-server/browser replay and the rest of the original
browser sort/filter policies remain unverified. No pak file was changed.
