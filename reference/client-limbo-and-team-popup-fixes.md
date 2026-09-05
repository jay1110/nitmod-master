# Limbo aspect ratio, team popups and skill-upgrade notifications

Limbo now scopes the existing original-protocol centered, height-scaled HUD
transform around panel rendering. The 3D camera rectangle uses the same
transform; letterboxing receives its physical width rather than overwriting
it with a stretched screen-relative width. Input remains in the engine's
640-wide full-screen space and is inverse-transformed for the panel cursor,
both before rendering and before hit testing. Mouse events refresh this
cursor after movement. Integer display-context coordinates introduce less
than one logical pixel of quantization. ET260 remains stretched as before.
This is aspect-preserving centered presentation, not an expanded ultrawide
map layout. Actual browser screenshots and clicking remain to be checked.

Original CG_GetPMItemText (sorted cgame_client.c) dispatches type 6 to team
join/disconnect, whereas ET260 uses PM_TEAM=7 and PM_DESTRUCTION=6. Event 90
now maps that payload in a temporary entity copy, used consistently for text,
icon, queue type and sound. Original snapshot values remain untouched.
Client indices for team/mine messages are checked before array access.
Tests execute the real event handler for both protocols, all three teams,
join and disconnect, plus invalid clients; they check the printed text and
that the snapshot payload did not change.

Original CG_NewClientInfo compares old/new xp unlock bitmasks and announces
each newly set level bit. It does not require an increased s display level.
The adapter now follows this rule for levels 1..5, with typed reward lookup
by the newly unlocked level. First client-info receipt is suppressed via
infoValid (an intentional alternative to the original frame-count gate).
Native notifications are retained; duplicate original level-based messages
are removed. All 4096 low-six-bit mask transitions are tested.

The report of every star remaining zero is NOT established as fixed by the
notification correction. Existing digit decoding still reads the original
s field and keeps level-five presentation separate from native 0..4 tables.
The read-only console command nitmod_skilldebug prints the selected client's
protocol, raw s/xp fields, parsed levels, masks and next thresholds. It prints
no GUID/key data and sends no server commands. A failing live-server sample
is needed to distinguish zero server levels from a client decode/update gap.

No pak/menu/PK3/original binary edits. No new server authority or invented
XP/skill grants. Browser and live-server verification remain pending.
