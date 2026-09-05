# Original Nitmod true-ping runtime

The qagame decompilation at `ClientEndFrame` (`0x502a0`) exposes a typed,
self-contained `g_truePing` behavior.  Each connected client owns a 64-entry
ring.  Every end frame stores `level.time - pers.cmd.serverTime`; when
`g_truePing` is enabled, `playerState_t::ping` becomes the arithmetic mean of
all 64 samples and is clamped to zero when negative.  With the cvar disabled,
the engine-provided ping remains unchanged.

The history is private qagame memory and therefore changes neither the engine
ABI nor the network layout.  The adjacent original anti-warp fields were not
ported from anonymous offsets because they cannot yet be mapped safely to ET
2.60 structures.
