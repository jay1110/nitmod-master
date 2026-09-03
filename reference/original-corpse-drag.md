# Corpse pull, experimental activation integration

Original qagame G_DragCorpse at 0x5b860 (275 bytes), also inlined in
Cmd_Activate2_f in sorted/nitmod_cmds.c, uses horizontal currentOrigin distance
40 through 85 inclusive. It normalizes the horizontal displacement toward the
actor, targets speed 110, and adds the difference from ps.velocity to both
ps.velocity and s.pos.trDelta. Vertical velocity is unchanged. The original
g_dragCorpse registration is 1, flags/track/reset zero.

The typed helper and original corpse-only activation trace are active for all
classes, before the retained native covert-ops interaction. A client-backed
corpse consumes the action even when dragging is disabled/out of range.
Null/self targets and invalid trace entity indices are additionally rejected.
The actor must be alive and not wielding a deployed mortar/MG42.

This is not the complete Nitmod activate2 port: the original extended eFlag
0x800000, canister kick, live-player shove, uniform-steal options and Omni-bot
gates are not reconstructed here. The subsequent native interaction remains.
No new events, wire fields, playerState layout or pak assets are introduced.

The full-qagame fixture checks 36 distance/direction/Cvar profiles, horizontal
trajectory deltas, preserved vertical velocity and null/clientless/self input.
Ten additional profiles exercise real Cmd_Activate2_f across all five classes
with enabled/disabled dragging and a corpse-trace engine double; the dead
actor does not trace. Actual collision-world selection and browser gameplay
still need runtime testing.
