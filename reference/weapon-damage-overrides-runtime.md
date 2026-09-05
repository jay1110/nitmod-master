# Active server weapon damage overrides

Original G_GetWeaponDamage and nitrox_GetWeaponSplashDamage/Radius select
nonzero private definition fields before falling back to ammo defaults.
The reconstructed parser already supports damage, splashdamage and
splashdamage_radius in both/both_altweap blocks, but previously discarded
the parsed options from its map-owned pickup cache.

G_InitGame now loads definitions once after clearing that cache. Successful
records publish classes and options together. Failed records stay failed
until map reset, keeping existing defaults and preventing repeated file I/O.
The existing native-to-original filename/alternate-section mapping is reused.
Damage callbacks only inspect cached records; they never open files.

Active consumers: G_GetWeaponDamage, Bullet_Fire, fire_grenade and fire_rocket. Individual
nonzero fields override independently; zero retains the fallback, matching
original semantics. The grenade airstrike-marker 140 splash/radius override
remains last, as in the original. Negative parsed values are not reinterpreted
as absent. Shared prediction ammo tables are not mutated.

Tests exercise all three fields with zero/positive/negative input, invalid
identities, map reset, repeated failed startup loads and no callback I/O.
The existing projectile fixture continues to verify fallback factory values.
Nonzero overrides through an entire live explosion are not replayed here.

Limits: loader uses weapons/, not a newly reconstructed custom weapon-dir
cvar. The parser is still a recovered subset; unsupported syntax rejects the
record and retains defaults. Bullet_Fire resolves the override once before
penetration/ricochet recursion; caller constants remain the fallback. Spread,
headshot and distance-falloff options are not activated here. UI/cgame,
bomb/poison firing and network protocol
are unchanged. No original assets are modified. Browser gameplay validation
remains pending.
