# Active reload body-animation selection

Original begin-reload dispatches IDs 4..50 through qagame table 0x22e128
and cgame table 0xff468. Entries 4, 9, 15, 28, 48, 49, 50 branch past
the body-script event; all other table entries enter it. The reference test
now checks all 47 destinations in EACH hash-verified original module.

Among reviewed native identities, the exceptions are GRENADE_LAUNCHER,
GRENADE_PINEAPPLE, DYNAMITE, SMOKE_BOMB and TRIPMINE (original ID 49).
LANDMINE (original ID 25) does not skip the event. The original skip target
is qagame 0x28862 / cgame 0x17d72; body handling starts at qagame
0x28820 / cgame 0x17d30. The body path selects normal/prone reload and
calls BG_AnimScriptEvent with continue=false, force=true before joining
the same subsequent first-person/timing/event path.

The reconstructed adapter already implemented the five exceptions privately.
NITMOD_ReloadBodyEventRequired now provides that selection in shared code,
used both by the reconstructed adapter and the active native begin function.
Compared with the previous native implementation this changes only tripmine
body-animation suppression; the other four exceptions and landmine behavior
are retained. Unsupported identities retain the native default at this layer;
eligibility is still the caller's responsibility. No original IDs 48/50 are
guessed as native identities.

The predicate does not suppress first-person animation, reload timing or
EV_FILL_CLIP. Native no-midclip/full-magazine/leaning and eligibility checks
still run before it. Their full Nitmod replacement remains separate work;
this increment does not remove them or activate the full recovered dispatcher.

168 executed native begin scenarios cover the five exception weapons plus
landmine and Luger, prone/non-prone, ready/normal-fire/alternate-fire and four
first-person animation gates. Skipped-body scenarios deliberately provide no
character/model, ensuring no body-script access occurs. Tests verify the body
call distinction, exact native duration overlap/add behavior, one predictable
fill-clip event, appropriate first-person behavior, and unchanged inventory.
Existing reconstructed begin tests continue to exercise the same selection.

Host build and all 66 CTests pass. Body-script invocation is still recorded
by a boundary double; model playback, original-binary engine replays and
Linux-i386/WASM validation remain outstanding.
