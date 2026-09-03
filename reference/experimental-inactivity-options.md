# Inactivity timer integration (partial original behavior)

g_inactivityOptions registers with original default 0, flags 0, track-change
true, reset false. Original ClientInactivityTimer (nitmod_client.c) provides:
bit 1 protects following spectators; bit 2 permits spectator disconnection
without a full public server; bit 4 disables the admin inactivity exemption
for active players. Bits here are masks 1, 2, 4, not ordinal bit indices.

The port implements masks 1/2, private-slot occupancy and public-slot pressure,
half-duration warnings without deadline extension, active-player transfer to
spectators, and spectator disconnection. Movement/fire/lean remain activity;
dead, limbo, and prone deployed-MG42 states reset the deadline as in original.
Nonpositive inactivity durations are disabled. Local-client immunity remains.

Scope limitations: original permission 9 and TV-client exemptions cannot yet
be mapped to existing typed admin/TV state. Mask 4 therefore has no effect
until that permission backend is integrated. Existing ET lacked these
exemptions too; this patch does not claim full admin immunity parity.
Warnings use stock cp, not original pop; the spectator-move notification is
fixed text to the affected client, not a broadcast containing the player name.

Full-qagame tests cover 32 option/follow/occupancy/private-capacity profiles,
warning deadlines, spectator drop callback, disabled timers and four activity
reset cases. Full SetTeam/ClientBegin transfer and permission/TV behavior are
not exercised. No assets or original reference artifacts are changed.
