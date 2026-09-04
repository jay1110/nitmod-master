# Continuous entity sound dispatch

Reference: `src_nitmod_decompiled/cgame/sorted/cgame_ents.c`,
`CG_EntityEffects` (loop-sound branch, lines 670–718), and `CG_GetGameSound`
in `cgame_client.c`. The original getter selects a private table for slots
0–83 and the ordinary table above that. The existing typed NCS registration
already flattens these slots into `cgs.gameSounds`; no second wire-index
translation is introduced.

The active renderer now delegates continuous sounds to `CG_EntityLoopSound`.
Speaker range defaults to 1250; speakers and movers retain their transmitted
volume. Brush entities use the inline-model midpoint and transmitted volume;
ordinary entities use volume 255. Start time is acquired once and reset when
the loop stops. Automatic speakers retain their delay/jitter scheduling.

Deliberate safety differences: out-of-range indices, nonpositive handles and
invalid brush-model indices do not reach the sound backend. A rejected loop
resets its start time, allowing later valid registration to start normally.
Entity sound-position updates and lightstyle sound triggers are also guarded.
NCS sound replacement clears the previous WAV handle before processing script,
custom or empty values, preventing playback of an obsolete sound.

`tests/check_entity_sound.h` exercises every sound slot plus both boundary
violations across all four loop variants, repeated frames, timing, volume,
range, brush position, automatic speakers and invalid handles. It is included
in the full cgame dispatch executable. Native and WASM builds are separate
checks; these tests do not establish live dedicated-server or audio parity.
No pak assets or server protocol messages are changed.
