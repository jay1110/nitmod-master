# Composed begin-reload adapter

NITMOD_BeginWeaponReload composes the reviewed state/inventory checks,
empty-reserve READY reset, target weapon's duration, body-script animation,
first-person animation and predictable fill-clip event. All inputs use native
ET structures and explicit ability words. This adapter is not yet installed
in PM_CheckForReload/PM_BeginWeaponReload; outer request/scoped-mode policy
and live ability synchronization remain necessary.

Original body-event selection in qagame PM_BeginWeaponReload uses the jump
table at 0x22e128 for IDs 4..50, before the event call at 0x2885d. Targets
4,9,15,28,48,49,50 skip that call. Of the 44 supported identities these are
grenade launcher, pineapple grenade, dynamite, smoke bomb and tripmine.
Landmine does NOT skip it. Other eligible targets use normal/prone reload
according to EF_PRONE, isContinue=false, force=true. Original event values
11/22 are translated to native ANIM_ET_RELOAD/ANIM_ET_RELOADPRONE, NOT used
as raw indices (native prone reload is differently numbered).

Character/model information is required only when a body event is needed.
The return from BG_AnimScriptEvent is ignored like the original, so a model
without a matching script does not prevent reload timing or sound. The body
event runs before timing/weapon feedback. Native bg_animation.c modifies body
animation fields, not weaponstate, weaponTime or eventSequence. Arithmetic,
duration and event-sequence errors are checked before calling the animation
system; this is deliberate hardening against partial failure.

176 composition cases cover every supported target, prone/not prone, and a
successful/missing body script. An explicit boundary double checks the actual
player/model pointers, native event, continuation/force arguments and call
order, and simulates a torsoTimer effect to verify its preservation. The
existing real native predictable-event helper is retained. Missing character,
body-event exceptions, empty reserve before model/default validation and
overflow before callbacks have additional tests.

This verifies adapter composition, not real animation-script selection,
random command choice or visual equivalence. Actual model-script and engine
replay tests remain outstanding. No active gameplay or protocol hook changed.
