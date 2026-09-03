# Live weapon configuration synchronization

The nine previously registered weapon Cvars now have vmCvar handles and
modification-count tracking: g_war, g_pickAnyWeapon, g_weapons,
team_panzerRestriction, team_maxFlamers, team_maxMG42s, team_maxMortars,
team_maxriflegrenades and g_medics. Defaults and flags are unchanged. The
three preexisting engine/native-owned settings are not registered twice.

G_UpdateCvars updates this group once and folds its dirty state into the
existing Nitmod snapshot refresh. Multiple changed settings produce one
refresh; unchanged frames do not refresh. The existing snapshot setters
still compare values and gate sending by capabilities. Pick-any/medic options
have no new invented wire field; their changes can leave wire snapshots
unchanged. Gameplay continues to read them through the existing adapters.

The scs.war field now receives the registered g_war value at initialization
and updates, instead of remaining zero. Existing # weapon option/limit fields
are refreshed on the relevant modifications, not only on unrelated native
Cvar changes. This repairs synchronization, not all war-mode gameplay.

Tests validate handles, repeated registration, initial baseline, each of nine
individual modification counters, no repeated dirty signal and cached war
values. The existing complete read/validation tests remain active. Full
G_UpdateCvars-to-client engine transport is not replayed in these unit tests.
No extra protocol fields, assets or reference binaries were modified.
