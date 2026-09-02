# Doublejump integrated port (experimental)

Original qagame table entries at ELF 0x2a972c/0x2a9748 register
g_doubleJump="0" and g_DJHeight="1.4", flags/track/reset all zero.
These are now registered and updated through the normal server Cvar table.
Changing either triggers the existing scs/# snapshot refresh. Server Pmove
gets those Cvars; both client setup paths get the received typed snapshots.
The original `#` message is accepted without a reconstruction handshake,
as already done for scs. Reception grants no capabilities. Reconstructed
outgoing messages remain capability-gated to protect unmodified clients.

## Mapped original PM_AirMove and PM_GroundTrace

Reference: sorted qagame/nitmod_pmove.c lines around 686 and 1368.
ps+0xc is pm_flags, ps+0x68 is eFlags (byte +0x6a bit 8 = EF_PRONE),
ps+0x28 is velocity[2], ps+0x50 is groundEntityNum. Mask 0x280 means
PMF_RESPAWNED | the original doublejump-used bit 0x80. That unused ET bit
is named PMF_NITMOD_DOUBLEJUMPED without shifting any existing flags.

The shared BG_NITMOD_CheckAirJump implements mode zero/off, mode two/rising
only, other nonzero modes unrestricted by vertical direction; prone,
respawn, already-used and held-button guards; 270*height vertical impulse;
held/used flags and ground clearing. It retains horizontal velocity. Sprint
cost is 2500 (floored at zero) only when at least 850 ms since pmext.jumpTime;
ps.jumpTime is updated on success. PM_AirMove invokes the existing forward
or backward jump animation, clears pml walking/ground plane, and follows
the original water branch. No invented EV_JUMP is added for the extra jump.
Ground contact clears the used bit as in the original.

The state transition is compiled into both server and client. No extra
playerState_t fields, engine ABI changes or asset edits are introduced.
Only local pmove_t input fields are appended.

## Intentional deviations and limitations

Nonpositive or extremely large/nonfinite height factors are rejected by
the movement helper to keep invalid settings out of prediction. The guard
is 0 < height <= 1e30; original did not explicitly apply this guard.
Original wire formatting uses three decimals for height; the port retains
that format and its possible small precision difference from server Cvars.
The typed panzer restriction stays in integer percentage units rather than
the original receive-side fractional representation; not used by this jump.
Mixed original/native event and weapon layouts remain incomplete. This
change does not establish original-server movement or gameplay parity.

## Verification

check_doublejump.h executes the production state transition in both full
cgame and full qagame test links: 96 mode/flag/vertical/input combinations,
plus repeat-jump prevention, prone, invalid height and sprint timing.
The client dispatcher test receives # without a handshake, checks height
1.4 and atomic rejection of NaN, infinity, trailing junk and overflow.
Cvar inventory tests verify original defaults/flags and registrations.
These are deterministic local tests, not a browser end-to-end or original
binary replay comparison. Ground trace and animation hooks still need an
end-to-end movement scenario on a real map.
