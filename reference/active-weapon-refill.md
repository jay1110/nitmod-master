# Active shot consumption and exact-zero refill

The previously isolated NITMOD_ConsumeSelectedWeaponClip is now called by
PM_WeaponUseAmmo for mapped weapons when the shared Nitmod movement path is
enabled. The same hand-selection rule is used for admission and consumption:
empty main hand selects sidearm, empty sidearm selects main, otherwise parity
selects the Akimbo hand. Clip aliases and native playerState fields are used.

g_noReload is registered with original default 0 and flags 0 (hash-pinned
original Cvar table checked by test_weapon_cvars_reference.py). The tracked
weapon configuration detects changes; nitmod_RefreshBaseSettings publishes
noReload in the existing simple-config field, alongside war. Both qagame and
both cgame Pmove setup paths project these settings into mod-local pmove inputs.
No new network field or engine playerState layout is introduced.

The original PM_WeaponUseAmmo evidence at qagame ELF 0x2aa40..0x2aaec is
documented in weapon-consumption.md. At exact zero after subtraction, g_noReload
bit 0 OR panzer with war==1 refills from the selected clip's defaultStartingClip,
not maxclip and not reserve. Other bits/modes do not enable this effect.
Current native ammo-table defaults remain in use; original dynamic definition
loading is still pending. Negative/overspent inputs reject atomically. Native
protocol and noWeapClips retain their existing subtraction path. PM_Weapon's
infinite-ammo and mounted-weapon admission guards remain unchanged.

Each complete cgame and qagame fixture runs the same consumption matrix over
44 mapped identities, three clip counts per hand, four war modes, four flag
patterns, two amounts and enabled/disabled paths: 25,344 cases per module.
Expected hand selection/refill is computed independently, and whole playerState
is compared. The reserve-only path is tested separately. Registration/update
tests now include the tenth tracked Cvar; source-contract tests verify both
prediction/server inputs and simple-config publication.

This activates a coherent consumption/refill feature, not all g_war modes or
all g_noReload bit semantics. Live browser/dedicated-server replay remains open.
Pak files and reference binaries remain untouched.
