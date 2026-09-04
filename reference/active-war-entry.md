# Active war-mode inventory entry

The recovered war=4 branch of ClientThink_checkWeapons now runs after
ClientEndFrame in G_RunFrame, matching the original call order in
nitmod_game.c. Only connected Axis/Allies clients enter the adapter; dead
and following clients are rejected by the existing recovered guard.

The per-spawn latch belongs to gclient_t, not playerState_t or the network
ABI. ClientSpawn's whole-client clear resets it; changing g_war does not.
The existing mapped removal selects knife, queues native EV_NOAMMO and
then sets the latch. Ammo and surviving inventory bits remain unchanged.
ET 2.60 has no server demo-client facility; the adapter supplies false rather
than interpreting original private offsets.

The full qagame test covers teams, connection states, health, following,
modes 0..4, repeated frames, event identity and explicit latch reset.
This activates inventory stripping, not complete original war gameplay or
the remainder of ClientThink_checkWeapons (dynamic weapon-definition policy).
No pak assets are changed. Live dedicated-server parity remains unverified.
