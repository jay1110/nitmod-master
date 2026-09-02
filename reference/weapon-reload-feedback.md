# First-person reload animation and predictable event

NITMOD_ApplyReloadFeedback combines the already recovered timer/state effect
with gated first-person animation and the native predictable EV_FILL_CLIP
event (parameter zero). It is an effect bundle AFTER all reload eligibility
checks and duration calculation, not a replacement for the entire begin flow.
Body-script animation is not performed; it needs character animation context.

Original PM_BeginWeaponReload selects animation from the CURRENT weapon
(qagame 0x288e2): original GPG40/M7 IDs 36/37 use animation 8 (RELOAD2),
deployed MG42 ID 46 uses 9 (RELOAD3), fast-reload eligible current weapons
with light ability bit 4 use RELOAD2, others RELOAD1 (7). The requested TARGET
weapon controls mortar/deployed-mortar suppression at 0x28862..0x28870.
Continue-animation gates at 0x28908..0x2894c preserve an identical current
animation; otherwise require a command weapon, expired animation timer and
pm_type below PM_DEAD before toggling ANIM_TOGGLEBIT. Native enum names and
the existing verified BG_isLightWeaponSupportingFastReload helper are used.

Original event 0x1c/parameter 0 is submitted at qagame 0x288b8..0x288c3
after the timer/state transition. The adapter uses native EV_FILL_CLIP, not
the numeric original event ID, and calls the real native
BG_AddPredictableEventToPlayerstate. Suppressing first-person animation does
not suppress that event. There is no corresponding completion event.

4224 combinations cover 44 current identities, normal/mortar/deployed-mortar
targets, ability on/off, matching/different animation, four animation-gate
conditions and both toggle phases. Real native event-ring writes are checked
at wrap boundaries along with the entire player state and immutable pmove/
pmoveExt context. The debug-only showevents query is answered with zero by
the test engine stub; unexpected engine requests still abort. Repeated calls
in RELOADING do not emit another event. Invalid duration, timer/event-sequence
overflow, unknown target and null input are covered.

The original updates animation before timing; this adapter validates/applies
timing first so invalid arithmetic cannot leave partial animation/event state.
This is deliberate hardening. Negative/INT_MAX eventSequence is rejected to
avoid undefined signed increment in the historical helper. Valid effects
match the inspected order's final state; no callback runs between them.
Compiled in cgame/qagame, but no active PM_BeginWeaponReload hook yet.
