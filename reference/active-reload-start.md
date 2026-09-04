# Active reload requests and light-weapon start

Update: scoped decisions and the three scoped start transactions are now
active as documented in active-scoped-reload.md. The exclusions below describe
the earlier light-weapon activation stage.

The production PM_CheckForReload now uses NITMOD_DecideReload for mapped,
unscoped identities when nitmodReloadEnabled is set. It preserves the no-clips
and rifle-grenade exclusions, state/timer gates, reload/alternate key preference,
and native automatic-reload classification. Negative reserve/clip values reject
instead of being treated as nonzero valid ammunition. Manual Akimbo requests
inspect both magazines; automatic requests require both empty.

PM_BeginWeaponReload delegates the twelve reviewed pistol, SMG, FG42 and Akimbo
identities to NITMOD_BeginWeaponReload. That composes inventory validation,
body animation, first-person reload animation, timing and EV_FILL_CLIP. It
prevalidates event-sequence/timer overflow before side effects. Existing native
skill >= 2 is explicitly converted to the fast-reload input; it is NOT claimed
to reproduce arbitrary original server ability tables. Original dynamic options
and all scoped ability/war-mode decisions remain outside this activation.

Both modules use the existing shared activation established in
active-reload-completion.md. No protocol fields, pak assets or binaries are
modified. Current native ammo capacities, reload durations and item data remain
the source; this is not a complete original weapon-definition port.

Evidence: original PM_CheckForReload cgame ELF 0x19c80, qagame 0x2a7a0;
inventory and start effect reconstruction is documented in weapon-reload.md
and the reload helper references. The extracted production-body fixture now
compares enabled/disabled paths over twelve identities, every native state
from READY through RELOADING, three timers, three requests, two automatic
preferences, four inventories and two fast-reload settings. Entire playerState,
body-event selection and event counts must agree on this valid input domain.
Negative inventory, event overflow and timer overflow additionally assert zero
partial mutation. Existing independent helper and complete-module tests remain.

Real browser/dedicated-server replay parity and original ability negotiation
are not established by these deterministic tests.
