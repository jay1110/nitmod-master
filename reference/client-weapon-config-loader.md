# Weapon animation file loader

The active CG_ParseWeaponConfig now parses into temporary animation records
and commits only after MAX_WP_ANIMATIONS complete rows. COM_Parse returns
an empty string at EOF, not NULL: checking both prevents the header scan
from looping forever and incomplete rows from silently becoming zero.
Empty/oversized opened files are closed; rejected reads do not mutate the
existing weapon. The 20000-byte bound and optional newfmt header remain.

Original format evidence is in sorted/cgame_servercmds.c: first frame,
frame count, FPS, loop count; newfmt additionally packs animated part bits,
primary-model bit 16 and hide bits shifted eight. Zero FPS still means one,
loop counts clamp to [0,numFrames], and unknown header tokens retain their
diagnostic. Stricter numeric conversion rejects non-finite, out-of-int-range,
fractional integer fields, negative lengths/FPS and unrepresentable frame
intervals. Double division precedes the checked integer conversion; this
is not a claim of bit-identical x87 rounding for every fractional FPS.

Full-cgame engine-callback tests cover every token truncation in both formats,
successful row values/masks, zero-FPS and negative-loop behavior, missing,
empty and oversized files, handle ownership, and bad numeric fields followed
by otherwise complete valid rows. Failed loads preserve the entire weapon.
Native/WASM build and module probes do not establish live browser animation
parity. No pak files or original reference binaries are modified.
