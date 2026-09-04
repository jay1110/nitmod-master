# Original weapon asset compatibility

The unmodified pak/weapons/knife.weap closes its client block but omits the
outer weaponDef closing brace. Original CG_RegisterWeaponFromWeaponFile
(sorted cgame_weapons.c) accepts EOF at this level. The port now accepts it
after a successfully completed client block; nested incomplete blocks still
fail and roll back registration. No asset was edited.

Twelve-row animation tables (including pak/models/weapons2/sten/weapon.cfg
and stock ET weapon.cfg files) previously failed because the local enum has
thirteen entries. Clean EOF after ALTSWITCHTO now copies DROP into optional
DROP2. This is a safe compatibility fallback, not a claim of identical
original missing-row data. A supplied thirteenth row remains authoritative;
partial rows, invalid numbers and short mandatory tables remain errors.
Parse errors now include a newline. Failure previously left the animation
table empty, not necessarily the separately registered model handles.

Tripmine was excluded by the stock BG_WeaponInWolfMP loading gate. The cgame
media preload now explicitly includes it on the original Nitmod protocol,
supplying both first-person and missile models without changing shared
gameplay eligibility. The planted-model renderer consumes this preloaded
missile handle as before.

Tests: check_weapon_config.h covers numeric failures and every truncated
token boundary in both formats; check_weapon_assets.h reads the unchanged
knife/tripmine definitions and sten/knife/tripmine animation files. Renderer
handles are mocked; actual browser visuals still require live verification.
