# Separate projectile damage and blast defaults

Original qagame ammoTableMP at VA 0x2a69a0 uses 72-byte records.
`G_GetWeaponDamage` reads +0x28 after a zero private override;
`nitrox_GetWeaponSplashDamage` and `nitrox_GetWeaponSplashDamageRadius`
read +0x2c and +0x30 respectively. See sorted/nitmod_weapons.c.
The existing SHA-256-pinned extractor now exposes those three fields.

Fifteen typed projectile identities have 45 defaults checked directly
against the original ELF. Native weapon numbers are not used as original
table indices. This includes bomb (0/350/300), poison canisters (20/0/250),
ordinary grenades (0/250/250), dynamite (0/400/400), and smoke (0/0/0).

The live fire_grenade factory now applies the separate values instead of
using G_GetWeaponDamage for both blast strength and radius. The original
airstrike marker branch's explicit splash/radius 140 override is retained.
Weapon_Grenade's subsequent zero-contact-damage policy remains unchanged.
Rifle grenades now retain their separate original 250-radius default.

The projectile integration fixture asserts all three fields for five
already-live factory paths, under kick and shootable-canister flags.
The ELF audit covers all fifteen default rows. Full explosion/gameplay
replays and browser verification remain outstanding.

Scope: default projectile data only. Private weapon-file damage overrides
are still not wired into this factory. This does not activate unfinished
bomb/poison firing, loadout, gas-think or obituary paths. Rocket creation,
bullet damage, UI and cgame sources are unchanged. No assets are modified.
