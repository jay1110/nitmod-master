# Shared native firing-clip selection

Current status: the Nitmod path now activates the validated consumption/refill
adapter with synchronized settings; see active-weapon-refill.md. The inactive
policy and native-only limitations below describe the earlier integration.

`PM_WeaponFiringClip` extracts the identical native alias/akimbo selection
previously duplicated in `PM_WeaponUseAmmo` and `PM_WeaponAmmoAvailable`.
Both consumers now resolve the same hand through this function. Main clip
empty selects the sidearm; sidearm empty selects the main clip; otherwise
the existing parity rule selects the hand. Both-empty follows the original
zero-first sidearm result. Native sidearm identity-as-slot is retained.

No refill policy is activated. The hardened recovered
`NITMOD_ConsumeWeaponClip` remains separate until war/noReload settings and
fire admission are bound consistently. Native noWeapClips still reads and
subtracts from reserve, bypassing hand selection. Native negative/sentinel
and overspending behavior is preserved, not silently replaced by the
hardened helper's rejection policy.

The test extractor now compiles the actual two consumers and shared selector.
4224 cases cross 44 mapped native identities, four main/side counts
(-1/0/1/2), clip/reserve mode and amounts 0/1/3. An independent zero-first
and parity oracle checks availability and the exact single-slot mutation.
Full player/extension state and absence of body/condition events are checked.
Adrenaline retains its native reserve alias; this is not an original alias
parity claim. Extreme signed subtraction is outside these fixtures.

Complete host Debug build and all 66 tests pass. This is behavior-preserving
native integration and test coverage, not new Nitmod refill gameplay,
original-ELF execution or Linux-i386/WASM release verification.
