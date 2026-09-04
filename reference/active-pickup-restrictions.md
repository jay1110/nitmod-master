# Active weapon pickup restrictions

G_CanPickupWeapon now runs a typed Nitmod precheck before its native class
fallback. It uses the same recovered counts and configuration as selection:
heavy percentage, panzer population restriction, individual heavy caps,
rifle-grenade combined caps, Sten rule and spectator handling. Denials can
send the existing capability-gated ncp reason; no new wire format is added.

After these restrictions, war modes 1..4 use their original final allowlists
(panzer; Garand/K43; Kar98/Carbine; knife). PickAny cannot override a war
allowlist or a restriction denial. Outside those modes knife and pickAny
follow the recovered early returns before class/skill data. Thus the stock
heavy-skill SMG veto no longer defeats an explicitly permitted pickAny request.

Ordinary class policy and unavailable configuration fall back to the native
code. A missing original class mask is NOT assumed zero. The full original
classes/medic option override requires the still-unintegrated weapon registry.
Only new weapon acquisitions pass this existing pickup hook: adding ammo to
an already-owned weapon retains the original native path.

Evidence: G_CanPickupWeapon in original nitmod_weapons.c; final war returns
precede BG_Weapons class-mask reads, and G_IsWeaponDisabled precedes both.
The full qagame fixture checks all native weapon IDs, five classes, four modes
and pickAny on/off, default heavy caps on both teams, actual Pickup_Weapon
denial with whole-client immutability, pickAny admission/limit precedence and
invalid pointers/IDs. Existing isolated policy tests cover explicit class masks.

This does not port the complete grant/drop transaction or synchronize rifle
attachment grants. No pak files are modified. Browser replay remains unverified.
