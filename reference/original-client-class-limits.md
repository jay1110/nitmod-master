# Client class limits and latched class

Original qagame nitmod_client.c ClientUserinfoChanged emits lc from session
offset 0xbd8, the same latchPlayerType used by G_IsClassDisabled. cgame's
CG_LimboPanel_ClassIsDisabled counts other valid clients of the selected
team when current or latched class matches. It uses the five # limit fields,
with -1 unlimited and no g_war exemption in the client predicate.

The reconstructed qagame adds lc to the existing player configstring for
both bots and humans. Unknown keys are ignored by stock clients. cgame
appends latchedClass to its module-local clientInfo_t and parses lc; missing
or invalid lc falls back to the current class for stock compatibility.
No engine-shared playerstate/entity struct is changed.

The limbo class button refuses disabled selections. The renderer overlays
the existing friendShader, matching original cgs+67964, registered as
gfx/2d/friendlycross.tga. No menu or asset changes are required.

Restrictions become active only after a valid # snapshot and reset on new
sessions, preventing zero-initialized limits from disabling stock-server
classes. This is intentional hardening. Client counts use at most MAX_CLIENTS.
The predicate retains original client/server differences for war exemptions.

Full-cgame tests exercise 30 class/limit combinations, spectator exemption,
current/latched union without double counting, self/opponent/invalid-info
exclusion, lc parsing fallback and session reset. They call the predicate
after real # parsing, not a graphical renderer or end-to-end player-info
asset registration. Visual parity and live original-server joins still need
browser testing. This completes the client block deferred in
original-class-limits.md, not all Nitmod UI functionality.
