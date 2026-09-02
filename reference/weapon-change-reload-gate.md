# Active weapon-change exclusion while reloading

Original PM_BeginWeaponChange subtracts 3 from weaponstate, bounds the result
to 0..4 and tests mask 0x13. Thus original states 3,4,7 reject: dropping,
dropping-to-reload and reloading. Evidence: qagame 0x2a2c5..0x2a2dd,
cgame 0x197a5..0x197bd. Original reload state 7 was independently mapped
to native WEAPON_RELOADING through the begin-reload transition. It must not
be mistaken for native state 7 (WEAPON_FIRING).

Stock ET PM_BeginWeaponChange only rejected the two dropping states here.
It now calls NITMOD_WeaponChangeStateAllowed, adding the original reloading
exclusion in the shared cgame/qagame source. The ordering of respawn, range,
ownership, state, weaponDelay and grenadeTimeLeft checks remains unchanged;
the state gate still precedes nextWeapon assignment and all effects.

This narrow change IS gameplay-active in both reconstructed modules. It does
not activate the recovered reload dispatcher, replace the weapon table, or
claim full weapon-change parity. The ordinary and reload-intent switch paths
both use it. No networking or capability bit is added for this gameplay rule.

Tests exercise native states and adjacent invalid values; other state values
keep the original/native pass-through semantics of this particular predicate.
The source-contract test pins the call inside the real native function and
the surrounding guard order. All host modules are rebuilt. Full engine
weapon-change/reload replay and i386/WASM ABI verification remain pending.
