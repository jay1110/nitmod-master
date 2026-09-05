# Reconstructed-server award compatibility

The ET-layout award fallback used by reconstructed local servers advanced
name pointers by strlen+1 but subtracted only strlen from the remaining
1024-byte storage. It also published partial tables on truncated input.
The parser now validates all 14 name/team pairs into temporary bounded
storage before publishing pointers. Every terminator counts toward capacity.
Invalid or oversized input clears all entries to the native -1 sentinel.

Valid native wire data from g_stats.c remains unchanged; native and original
Nitmod award counts/sentinels remain separate. This hardens the fallback and
does not claim to port the original server's 16 award calculations.

Tests cover 14 valid rows, every incomplete input prefix, and an oversized
single name, checking cleared teams and in-buffer name pointers. Native
tests and WASM load smoke tests are run. Browser intermission replay remains
outstanding. Pak unchanged.
