# Fireteam selection and original client preference flags

cg_FTAutoSelect (default 1, ARCHIVE) now selects up to six sorted members
of the local fireteam each rendered frame after cvar updates, matching
sorted/cgame_ui.c:18220. The existing leader/rank sort and selected fields
are reused. Missing fireteam, invalid client, native protocol or disabled
cvar leave manual selections untouched; no blanket deselection is added.

n_forceSinglePistol (default 0, ARCHIVE) now contributes bit 0x40 to the
original cg_uinfo word; positive pmove_fixed contributes bit 0x20.
Evidence: original CG_setClientFlags and its inlined cvar-update copy in
sorted/cgame_client.c:13537 and 13732. Negative/zero values clear the bit.
The helper preserves unrelated bits and changes neither option for native
or reconstructed et260-layout servers. It does not locally fake a weapon
inventory: original qagame remains responsible for the single-pistol grant.

Original servers do not acknowledge the reconstructed capability command.
Therefore alternative-reload bit 0x10 is now enabled by either original
protocol detection or negotiated RELOAD_PREFS support, in both outgoing
userinfo and local movement preference construction. Native servers still
require the capability for that extension. pmove_fixed and
n_forceSinglePistol changes trigger the existing client-flag update path.

Initialization previously set flags during cvar registration, before the
engine gamestate identified the protocol. CG_Init now sets them again
after parsing server/wolf info. Existing demo suppression remains active.
No new commands, server extensions, qagame emission or asset edits.

Tests: 12,288 helper combinations (three protocols, 256 base words,
four fixed-move and four single-pistol inputs), including preservation of
the high bit. The actual CG_setClientFlags syscall is captured for 48
combinations plus demo suppression. Fireteam selection covers three
protocols, enabled/disabled and 0–8 members (54 cases), checking the
six-player limit, leader/rank ordering and unchanged outside selections.
Full native tests and WASM build/load checks are separate from the still
outstanding live original-server gameplay/weapon-grant comparison.
