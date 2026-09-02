# Original event 17 and sound-index hardening

User's remote-join logs report invalid sound handles, a WASM indirect call
to null, and separately Unknown event: 17. Only the last fatal error has
an identified dispatch mismatch in this change. No browser stack trace
was supplied for the indirect call; its cause remains unknown.

Original sorted cgame_events.c CG_EntityEvent case 0x11 plays the surface
landing sound unless surface 9, plays landHurt, updates pe.painTime and
sets local landChange=-24 and landTime. This matches ET EV_FALL_DMG_50.
Dispatch now maps original-server 17 to that handler without modifying
the entityState_t payload or shared enum. Native 17 (EV_FALL_MEDIUM) is
unhandled in the baseline. This is a narrow fix, not a full event mapping.

Six native landing handlers shared unchecked landSound[eventParm] and
character->animModelInfo->footsteps accesses. They now use a bounded helper;
missing model metadata, invalid surface indices and nonpositive landing
handles do not dispatch surface audio. Pain and camera effects still run.
Footstep surface indexing also checks bounds and absent model metadata.
These are intentional hardening differences from the original's unchecked
accesses, not evidence that they caused the reported handles or null call.

Full-cgame tests exercise 257 surface values (-1 through 255), four repeat
bit patterns, exact sound handles, pain timestamp, local view dip and
unchanged event payload (1028 cases). Existing stock/reconstructed medic,
PM, parser and protocol tests remain in the same suite.

Original versus native predictable-event provenance and the remaining
event table still need a coherent translation. Do not generalize by a
constant event-number offset. Original weapon IDs and sound/configstring
ranges are additional unresolved compatibility areas. The overflow warning
and unknown getnguid/fc/bp/kd commands are not fixed by this change.
