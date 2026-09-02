# Raising completion and native reload handoff

Original PM_Weapon distinguishes ordinary raising from raising-to-reload:

- qagame 0x2bd55 / cgame 0x1b237 stores READY, then selects/starts idle.
- qagame 0x2bd39..0x2bd50 / cgame 0x1b21b..0x1b232 stores READY,
  reads the current weapon and calls PM_BeginWeaponReload, then returns.

The original numerical states are translated using the previously reviewed
raising states, not copied into native enums. The reset before the call is
essential: begin-reload would reject a still-raising weapon state.

The native shared function PM_FinishWeaponRaise now encapsulates this existing
block, and PM_Weapon calls it at the same position, after timer guards and
reload/drop handling. It returns handled only for a raising state with both
weapon timers <= 0; ordinary raising starts idle, reload-intent raising
enters the existing native PM_BeginWeaponReload. Other states return unchanged.
The extra local timer guard is defensive for direct calls; the real loop
already guarded these timers, so normal product behavior is unchanged.

## Executed integration coverage

The test generator now also extracts verbatim PM_IdleAnimForWeapon,
PM_ReloadAnimForWeapon, PM_ContinueWeaponAnim, PM_BeginWeaponReload and the
new raise-completion function. The animation boundary double accepts forced
reload events only while state is READY. Inventory tables, reload timing,
first-person animation gates and predictable EV_FILL_CLIP remain real code.

144 complete scoped-return scenarios exercise GARAND, K43 and FG42 through
begin-change, finish-change and finish-raise: both reload intents, prone or
not, four first-person gates, and allowed/full-magazine/leaning native reload
conditions. Each tests both timer blockers, correct READY/RELOADING outcome,
unchanged inventory, idle versus reload animation, predictable event, and a
repeated completion call which must do nothing. Additional cases cover every
non-raising state with negative, zero and positive time. Source contracts pin
the new function in the actual PM_Weapon loop and READY-before-reload order.

This activates a small ET-equivalent refactoring, NOT the reconstructed reload
dispatcher. Native full-magazine and leaning restrictions are tested as current
behavior, not certified Nitmod parity. Recovered ammo/default/ability binding
and original reload semantics still require integration. The test simulates
timer expiry between phases; it does not execute the whole PM_Weapon scheduler
or original ELF code. Full engine, Linux-i386 and WASM validation remain open.
