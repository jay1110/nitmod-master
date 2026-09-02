# Active empty-current-reserve reset

Original begin-reload first validates the weapon state, then reads reserve
for playerState.weapon (CURRENT weapon, not the requested target). Exactly
zero reserve resets weaponstate to READY and returns before target midclip,
eligibility or animation checks. Evidence:

- qagame current read/alias lookup 0x28782..0x28793; zero test 0x28796;
  reset 0x287e8..0x287f8.
- cgame current read/alias lookup 0x17c92..0x17ca3; zero test 0x17ca6;
  reset 0x17cf8..0x17d08.

The shared native PM_BeginWeaponReload now invokes
NITMOD_ResetReloadWithoutReserve immediately after its state gate. The helper
only changes weaponstate and returns handled for an exact-zero reserve.
Negative reserve is not silently treated as empty; positive and negative
values continue to existing native checks. This is not general validation of
invalid inventory. No timers, animations, predictable events or ammo change
on the reset path.

## Deliberately bounded migration

The adapter takes the native BG_FindAmmoForWeapon result and compares it to
the reviewed recovered alias before applying the rule. All 43 agreeing known
identities can use the reset. Adrenaline's native syringe-sharing alias does
not agree with the recovered independent slot, so it is deliberately left
unchanged, as are unmapped identities/NONE. This prevents a partial lifecycle
port from inspecting the wrong inventory slot or prematurely changing
adrenaline/syringe behavior. The existing hash-pinned inventory tests establish
that adrenaline is the sole alias mismatch among the 44 reviewed identities.

## Verification

1800 cases execute the actual native begin function with all 50 native current
identities, 12 native/adjacent states and negative/zero/positive reserve, using
an ineligible target to check ordering. The helper is also tested with the
actual native slot, mismatched slots and null state. Another 600 cases cover
every native target with empty current Luger reserve, populated target reserve,
full target clip and leaning: the reserve reset must take precedence for
allowed states. Whole-state comparisons require all unrelated state to remain
unchanged, and boundary counters require no body/condition calls.

Host build succeeds and all 66 CTests pass. This activates a narrow original
behavior correction, not the full recovered begin-reload implementation.
Adrenaline lifecycle, remaining native restrictions, original-module engine
replays and Linux-i386/WASM release verification remain outstanding.
