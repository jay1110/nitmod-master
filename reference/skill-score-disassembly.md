# Player score: active typed integration

Reference qagame SHA-256:
`84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49`.
`G_SetPlayerScore` ELF address `0x000cec00`, size `0xae`.

The original starts with fldz, adds the seven float skillpoint fields at
0xbf4..0xc0c in order, and converts to signed integer after EACH addition.
At 0xcec19 the x87 control word is ORed with 0xc00 (truncate toward zero);
fistpl stores each intermediate before fildl reloads it for the next addition.
The final store at 0xcec9f targets 0x110, mapped to ps.persistant[PERS_SCORE].
G_SetPlayerSkill duplicates this sequence at 0xceea0..0xcef48.
Ghidra's nested ROUND output therefore must not become round-to-nearest,
nor may all float points be summed before a single final integer cast.

The active G_SetPlayerScore now lives in game/g_nitmod_score.c and reads
sess.skillpoints directly. game/nitmod_score.c owns the pure calculation.
Existing callers, skill levels, network messages and UI fields are unchanged.
A compile-time check ensures the native and recovered skill counts agree.

Validation: 7^7 = 823543 combinations of signed/fractional skillpoints are
compared with the native numerical loop, using exactly representable sums.
Each combination also calls the actual engine adapter and byte-compares the
client against the expected result: only PERS_SCORE may change. Additional
cases cover accumulation beyond float's exact-integer range, INT_MIN/MAX,
intermediate overflow despite later cancellation, NaN, infinities and nulls.

Intentional portability differences: the helper uses double for intermediates,
not x87 extended precision. This preserves integer accumulation above 2^24,
but does not claim bit parity for all extreme-magnitude/tiny-fraction mixes
or altered floating-point modes. Invalid/out-of-range intermediates reject the
whole update and preserve the previous score instead of relying on undefined
C casts or x87's indefinite integer result. Values just outside signed integer
bounds are conservatively rejected even when truncation could fit.

The host tests do not execute the original module. Native-i386/browser replay
and platform floating-point edge comparisons remain release requirements.
