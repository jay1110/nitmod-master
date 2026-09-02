# attachtotag script-name fallback

G_ScriptAction_TagConnect (ELF 0xb2fd0) now uses the cached script-name search
only after the existing targetname lookup fails. Original calls at 0xb3028
and 0xb313b establish targetname priority and script hash fallback. Native
targetname lookup already combines a cached hash and case-insensitive string
check; no change is made to that path.

The fallback returns the first live cached match. Current scriptName strings
are not consulted. The remainder stays in the existing typed ET 2.60 tag
implementation: tagParent/tagName, G_ProcessTagConnect, entity/client flags,
tag configstring registration and stationary angle trajectory reset.

Eight full-source scenarios exercise targetname priority over a hash match,
string-only false matches, first duplicate hash, and skipping an unused first
match, each with/without a client. Real G_ProcessTagConnect and configstring
index logic run with an engine boundary that supplies an empty slot and
verifies the exact "0 <parent> tag_head" write at CS_TAGCONNECTS+1. Flags,
client prone-state clearing, tag fields and angle/trajectory reset are checked.

No new protocol format or cgame handler is introduced. These are server-side
fixture checks; renderer tag attachment and browser/client end-to-end behavior
are not certified. Missing-parent/malformed-command fatal paths are unchanged.

Verification: native Windows-host build, 83/83 CTests, original instruction,
protocol/inventory checks and real Emscripten builds of all three modules pass.
Linux-i386 ABI and actual loaded engine/browser gameplay remain unverified.
