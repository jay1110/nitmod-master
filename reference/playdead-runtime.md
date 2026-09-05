# Play-dead runtime reconstruction

Original qagame `G_PlayDead` accepts a living, non-camera player only when the
movement flags are clear.  With `g_playDead` enabled, `PM_NORMAL` changes to
the original protocol value 6; an existing `EF_SPARE0` body may request the
reverse transition from `PM_DEAD`.

The reconstructed command uses typed `playerState_t` members.  Shared Pmove
consumes `PM_PLAYDEAD`, so qagame authority and cgame prediction both persist
the pose as `PM_DEAD | EF_SPARE0`.  This does not set `EF_DEAD` or alter health.
Standing back up first traces the crouched player bounds and leaves the player
down when obstructed.

The original address-derived write outside `playerState_t` has deliberately
not been copied: its owning `gentity_t` member has not yet been proven.  The
network state machine does not depend on an untyped offset.
