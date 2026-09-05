# Active camera-shake lifecycle

Reference `cgame_client.c` CG_StartShakeCamera (line 6677) sets scale,
computes strength squared times 1000, clamps duration to 0..1000, sets the
deadline and random phase. CG_ShakeCamera clears scale, length, phase and
deadline after expiry. The end of original CG_PredictPlayerState repeats
that expiry reset and applies its distinct origin oscillation.

The live port now restores the one-second maximum and full expiry reset.
Both render and prediction consumers use CG_CameraShakeFraction instead
of independently dividing by a possibly zero duration. Their existing
waveforms are preserved, including the original prediction Z constant.

Intentional hardening: zero/non-finite or dangerously large strength resets
the state; non-positive/non-finite duration cannot produce NaN coordinates;
clock subtraction uses double to avoid signed overflow; deadlines saturate
at INT_MAX; backward clocks cannot amplify the effect above its initial
envelope. At exactly zero envelope the consumer returns without changing
position. Arithmetic is not claimed bit-identical to original x87 float
rounding. No original binary or asset was changed.

The full cgame fixture exercises six strengths and 45 elapsed-time samples,
checks duration/deadline/fraction and the real render consumer, verifies
unchanged origin after expiry/disabled effects, full reset, backward time,
time zero and INT_MAX. Prediction uses the same helper but a full movement
replay is not part of this fixture. Browser/explosion visual parity remains
an end-to-end test, not established by the native suite or WASM load smoke.

This is a cgame lifecycle correction, not a new UI/qagame feature. It does
not complete missile cameras, prediction caching or other outstanding ports.
