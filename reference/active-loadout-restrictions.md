# Active loadout restriction block

G_IsWeaponDisabled now runs the recovered full restriction composition, not
just the old heavy-weapon percentage check. The existing ClientSpawn checks
therefore enforce mapped panzer population/percentage limits, individual caps
for panzer/flamer/MG42/mortar, combined rifle-grenade family caps and the Sten
class/option rule. War exemptions precede caps, but are not exclusive mode
allowlists. Spectator handling follows the recovered bot exception.

G_SetClientWeapons delegates to the recovered latch transaction: denied primary
becomes NONE, secondary is retained, and changed clientinfo is published only
when requested. Both team changes and ordinary loadout selection use this path.
Limit messages use existing capability-gated ncp reasons and their cgame
handler; no new protocol format is introduced. Spawn validation is silent.
Malformed/unavailable reconstructed settings retain the existing native
fallback; invalid weapon IDs are rejected before changing latches.

The recovered setclass handler is now registered in the real command table,
using native weapon IDs like this tree's team/loadout commands. Its existing
SetTeam and same-team paths reach the same restrictions. This does not add
support for raw original weapon IDs on the reconstructed server protocol.

Evidence: original G_IsWeaponDisabled and G_SetClientWeapons in
nitmod_weapons.c; Cmd_SetClass_f in nitmod_cmds.c. Detailed table/branch
evidence remains in weapon-restrictions.md. The full qagame fixture exercises
both teams, six limited weapon identities, five cap values, three teammate
counts, enemy/requester exclusion, rifle-family combination, latch idempotence,
all war modes for panzer exemption, Sten class/option combinations, spectators,
invalid IDs and malformed-setting fallback. Real setclass dispatch is tested
for query/help/spectator/malformed input; existing handler tests cover selection.

Automatic removal of already-held disabled weapons is NOT activated: its
original ammo-record eligibility flag and complete drop/regrant lifecycle
still require reconstruction. Original dynamic weapon definitions, browser
gameplay parity and complete original-client interoperability remain open.
No pak assets or original reference binaries are modified.
