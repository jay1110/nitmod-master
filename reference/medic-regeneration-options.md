# Active medicinal regeneration options

Original ClientTimerActions in sorted qagame/nitmod_client.c gates residual
accumulation before its one-second loop. War values 1..4 disable the timer;
g_medics mask 32 disables it for medics. Mask 64 selects healing rates 2/1
(below base/above base); otherwise mask 128 selects 1/0; default is 3/2.
Mask 64 takes precedence when both rate bits are set. Healing first clamps to
the base maximum, then on subsequent ticks to the effective healing maximum.

The active ClientTimerActions now delegates to G_NITMOD_HealthTimer using
the already registered/updated g_medics and g_war cache. No extra per-usercmd
cvar syscalls or network fields are introduced. Existing health snapshots
provide the HUD and shared pickup code with the resulting limits.
Overhealth decay for non-medics uses the effective cap and does not go below
one. Negative/overflowing timer inputs are rejected deliberately.

Tests cover 5 classes, all 256 low-byte option combinations, 7 war values and
7 health boundaries (62720 cases), plus catch-up ticks and residual retention.
The configuration getter is tested across all 256 values.

The deathmatch branch now follows the original mode-8 check: g_DMOptions
mask 2 allows regeneration for every class. Outside deathmatch, the ordinary
medic path requires neither EF_DEAD nor EF_VIEWING_CAMERA (original mask
0x200001). In deathmatch without mask 2, ordinary medic regeneration is not
enabled. Another 160 cases cover all classes, both mode branches, options
0..3 and all four combinations of these flags. The cvar is registered with
the original default 0 and flags 0; its value uses the existing dmOptions
field in the capability-gated # state message, without changing the format.

This is the mapped regeneration-options subset, not full original parity:
the six-level first-aid unlock granting regeneration to other classes remains
unported. The mode-8 check does not imply a complete deathmatch implementation.
Existing behavior for these paths is not presented as reconstructed. UI assets remain untouched;
no additional ui-module feature is introduced by this change.
## Sixth First Aid reward

The original sixth First Aid reward is represented by reward-mask bit 32.
With `g_medics` bit 16 it admits non-medics to the same timed regeneration
branch, matching the original `ClientTimerActions` check at ELF 0x4e399.
War-mode and DM precedence remain unchanged.
