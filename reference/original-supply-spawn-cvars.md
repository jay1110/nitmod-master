# Supply regeneration and spawn protection

Three original server registrations are now functional in the ordinary
g_main Cvar table (flags=0, track-change=false, reset=false):

| Cvar | Default | Unit |
| --- | --- | --- |
| g_spawnInvul | 3 | seconds |
| g_healthCabinetTime | 10000 | milliseconds |
| g_ammoCabinetTime | 60000 | milliseconds |

Original nitmod_client.c ClientSpawn sets powerups[PW_INVULNERABLE] to
level.time + g_spawnInvul.integer * 1000 for non-revive spawns. Revives use
1000 ms when g_fastres==1, otherwise 3000 ms. Spectators are excluded.
NITMOD_SetSpawnProtection applies this to the existing typed gclient_t;
extreme expiration times saturate to signed int bounds rather than overflow.
Negative and zero settings otherwise retain the original arithmetic.

Original nitmod_spawn.c trigger_heal_think/trigger_ammo_think use the
respective live Cvar for nextthink, add damage to health and clamp to count.
Both SP_trigger initial non-target scheduling paths use the same intervals.
The existing target-setup FRAMETIME scheduling and infinite-supply sentinel
-9999 remain unchanged. This controls stock replenishment, not the per-touch
healing/ammo rate. Changes take effect when the next think is scheduled.

No new client wire message is required: the protection expiration uses the
existing playerstate powerup and cabinets use existing entity behavior.
The full-qagame fixture checks 144 team/revive/fastres/duration profiles and
eight refill calls with custom, zero and negative intervals and supply caps.
The Cvar inventory test pins exact original defaults and registration flags.
No map or PK3 changes are involved. Full ClientSpawn/map-loading and browser
gameplay were not exercised by these direct-handler tests.
