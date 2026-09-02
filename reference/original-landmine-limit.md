# team_maxLandmines integration

The original registration uses default 10, flags 0, track-change=false,
reset=false. The recovered G_CountTeamLandmines (sorted nitmod_weapons.c)
counts registered mines with teamNum % 4 == team and teamNum < 4, then
returns min(count, team_maxLandmines.integer). The existing typed entity-list
helper already implements this. Its production wrapper now passes the live
Cvar rather than MAX_TEAM_LANDMINES.

The Engineer mine arming limit now compares against the same Cvar, preserving
the original enemy-mine exception: having reached your own team limit must
not prevent disarming enemy mines. Existing refund/charge logic is unchanged.
The game-manager initialization (original nitmod_spawn.c) publishes the limit
in otherEntityNum/otherEntityNum2. Each server frame (original nitmod_game.c)
publishes limit minus the capped team count. Existing cgame weapon-ammo HUD
reads these exact fields; no new message or client Cvar is needed.

Two ET bot-goal checks also use the live limit for consistency. This is an
adapter update, not proof of original Omni-bot behavior. The original
Omni-bot request 0x33 count/maximum response remains outside this patch.

Zero and negative limits retain original capped-count behavior; they do not
mean unlimited. Already placed or map-created excess mines are not deleted.
Changing the Cvar takes effect in subsequent count/arming/frame operations.

The full-qagame fixture uses 48 registered entities, six limit values, both
teams, unarmed mines, live team/arming changes, unregister and list reset.
An integration source check rejects remaining fixed MAX_TEAM_LANDMINES uses
at the production call sites. This does not exercise an actual Engineer
trace or an engine-rendered HUD and does not establish live-server parity.
No PK3, map assets or original reference binary were modified.
