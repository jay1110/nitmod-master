# Spawn reward independent-mask execution

Evidence: original qagame `AddExtraSpawnAmmo`, recovered in
`src_nitmod_decompiled/qagame/sorted/nitmod_unknown.c` at line 897.
The original module SHA256 matches the checked-in original manifest.

The switch distinguishes Light Weapons bit 2; First Aid bits 2 and 4;
Engineering bit 2; and Covert bit 2. SMGs accept Light OR medic First Aid,
rifles accept Light OR Covert, and either combination grants only one bonus.
Grenade increments depend on class as well as the corresponding reward.
War modes 1 through 4 suppress all bonuses.

`tests/test_nitmod_spawn_rewards_wasm.c` includes the actual production
`g_client.c` function. The expanded matrix uses 32 independent gate combinations,
all native weapon values, five classes, low/high numeric skills, and nine war
values including signed extremes. Every case starts with nonzero inventory;
whole-client comparisons reject unrelated writes. All 155,520 cases pass.

`python tools/run_wasm_spawn_checks.py` compiles and executes this fixture and
the existing health, secondary selection and secondary grant fixtures using
Emscripten and Node. Compilation/execution failures stop the command. This is
adapter verification with engine stubs, not original binary or full spawn replay.
