# Real-time game log prefixes

Original qagame `G_LogPrintf` at `0x89b70` reads `n_LogCurrentTime` before
building each logfile prefix.  Zero retains ET's elapsed `minutes:ss` prefix.
A nonzero value now calls the typed `trap_RealTime` API and writes a bounded,
zero-padded `HH:MM:SS` prefix.  Dedicated-console output remains the message
without the prefix, matching the existing/original path.

This changes neither logfile destinations nor package content.
