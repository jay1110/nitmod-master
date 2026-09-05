# Original browser population display

Reference: `ui_ui_misc.c`, `UI_FeederItemText_part_33`, server feeder cases 2/3.
The original formats `^7%i^9(+%i)/%s` for humans plus bots and `^7%i^9/%s`
when all clients are human. Cases 5/6/7/8 use LMS/Vote/TDM/DM labels.

The production feeder now consumes the existing typed human-count status cache
and these labels. No offset-based global or decompiled function body is copied.
Unknown population uses the master total; ET Legacy's explicit humans field is
also supported. No status requests are initiated during painting. Therefore a
server without a resolved status (e.g. hostname sorting without NxAC filtering)
can still show only its total, rather than a guessed bot count.

Intentional safety differences: counts/capacity are bounded to MAX_CLIENTS;
human count is bounded to the current master total when replies have different
ages; another source's cache is never used. Numeric capacity replaces raw text.

Tests cover eight cached populations, humans exceeding a newer total, source
switch, missing cache, Legacy master data, invalid indices/counts and all four
original labels with no menu catalog. No assets, cgame/qagame protocol, or engine
protection behavior is changed. This does not complete browser parity.
