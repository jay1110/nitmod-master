# Statistics transport boundary correction

Existing qagame G_weaponStatsLeaders_cmd and G_weaponRankings_cmd appended
unbounded numbers of rows to a 1024-byte string. Q_strcat could leave a partial
last row; single-weapon rankings still advertised the original count. This
made the existing cgame statistics protocol internally inconsistent for large
rosters/counters. No new original category or weapon gameplay is claimed here.

Both producers now format a row separately and reserve space for the command
header and leaders' zero sentinel before appending it. A ranking's advertised
count and best-accuracy bucket describe the emitted rows only. An out-of-range
floating-point accuracy is saturated before integer conversion, including the
float-rounded INT_MAX boundary relevant to WASM.

The original command names and row field order remain unchanged. Overflow
deliberately truncates the list at a whole-row boundary: this does NOT provide
all 64 players or every tied category in one packet. Fragmentation would need
an explicit compatible protocol and receiver and is not invented here.

CG_topshotsParse_cmd now builds a temporary private result and commits only
after the terminating category zero with no trailing fields. Invalid category,
client, negative counters, incomplete rows and missing terminators preserve
the last valid display. A valid empty list clears it. Existing original
26-category and native 22-category layouts and display row limits are retained.
This is intentional malformed-input hardening, not original undefined behavior.

Server fixtures exercise all 0..64 roster sizes for four message variants,
INT_MAX counters, row integrity, command-size limit, sentinel and count
consistency. cgame fixtures check both layouts, truncated prefixes, a malformed
second row, negative counters, trailing tokens and valid empty replacement.
These are native executable tests and WASM build/load checks, not a live
dedicated-server statistics replay. No ui module feature, pak edit or reference
binary change is part of this correction.
