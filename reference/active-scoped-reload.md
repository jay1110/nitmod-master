# Active scoped reload transaction

PM_CheckForReload now routes all three mapped scoped identities through the
recovered request decision in both qagame and cgame prediction. The existing
replicated war field is passed instead of zero. At war=2 manual reload keeps
the scope; other modes request the mapped base weapon with reload intent.
Automatic reload alone never triggers either scoped path. The original
scoped decision precedes the weaponTime gate, including positive timers.

PM_BeginWeaponReload now uses the validated animation/timing/event transaction
for GARAND_SCOPE, K43_SCOPE and FG42SCOPE. Finish uses the previously active
atomic transfer and returns READY without changing the selected scoped weapon.
Overflow is rejected before animation or event writes. Native Garand
no-midclip policy is deliberately preserved until original dynamic weapon
options are connected. No original ability masks are fabricated from skills.

Evidence: original cgame PM_CheckForReload ELF 0x19c80, scoped branches
0x19d50..0x19dbd; qagame 0x2a7a0 and 0x2a870..0x2a8da. See
weapon-reload-decision.md and weapon-reload-begin.md for helper reconstruction.
The extracted production-body test covers 21,600 cases: all three rifles, modes 0..4,
states READY..RELOADING, timers -1/0/1, manual/automatic/alternate requests,
negative/empty/positive reserve and negative/empty/partial/full magazines.
It checks unchanged inventories at start, scope retention or reload-intent
switch, timing, EV_FILL_CLIP and completion. Additional overflow and no-clips
cases must have no partial mutation.

Native non-Nitmod fallback is retained. No wire fields or pak assets change.
Original scoped ability word 0x20 and dynamic definitions remain unported;
this is not a claim of complete weapon or browser replay parity.
