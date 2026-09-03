# Experimental player shove

G_PushPlayer follows sorted nitmod_game.c: g_shove default 80, g_shoveNoZ
default zero, both flags/track/reset zero; 500 ms actor cooldown; normalized
view forward scaled by strength * 5; upward-dominant impulse uses strength
* forward.z * 4, otherwise Z is 64 (also when g_shoveNoZ is enabled).
The impulse adds to player velocity and entity trajectory; pm_time becomes
100 and PMF_TIME_KNOCKBACK is set. Time subtraction avoids signed overflow.
The server-private cooldown field is reset with the client struct, without
changing the shared playerState/snapshot ABI.

Activate2 now traces CONTENTS_BODY after the corpse trace. A living target
is pushed, a dead client-backed target is pulled. The existing actor alive
and deployed-weapon guards remain. This is experimental, not complete parity:
original extended client +0x154 admission data, pushed-by attribution fields,
playdead flag, live uniform theft, and Omni-bot gate remain unresolved. Native
PERS_HWEAPON_USE rejects mounted actors as an explicit safety restriction;
it is not claimed as the mapping of original +0x154. Target health and null/self
guards are additional hardening. Full push kill credit is not implemented.

Original event 96 cannot be emitted into native ET's event enum. Reconstructed
peers instead negotiate feature bit 12 and use `nsh entityNum`, which invokes
the existing validated NITMOD_ShoveSound respecting cg_shoveSounds. Unsupported
peers receive no command. Original-server event 96 handling is unchanged.
Unlike the original PVS snapshot event, this reliable notification is sent to
all connected supporting clients; it retains entity-local sound playback but
is not identical in visibility/timing/bandwidth. UI uses the shared capability
contract and needs no shove UI command.

Twelve physics profiles cover enabled/disabled, vertical directions, no-Z,
trajectory/velocity equality, movement flags and exact cooldown boundary.
Fifteen command-parser profiles check valid, negative, out-of-range, malformed
and overflowing entity numbers with wrong/correct argument counts. Existing
original shove sound tests remain. Browser/PVS/audio parity and
end-to-end reconstructed command transport are still pending.
