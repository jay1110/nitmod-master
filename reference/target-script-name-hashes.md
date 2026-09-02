# Target and script-name caches

Original entity target hash (0x5bc) and script-name hash (0x5b0) now have typed
private fields nitmodTargetHash and nitmodScriptNameHash. The existing native
targetnamehash remains separate. No shared engine prefix/wire fields change.

G_NITMOD_InitSpawnNameHashes runs after targetnamehash initialization and before
G_CallSpawn. Null/empty target or scriptName yields -1. A nonempty scriptName
on a case-insensitive script_multiplayer classname instead hashes game_manager;
otherwise the actual scriptName is hashed. The original strings, field stores
and alias branch are pinned in the SHA-checked reference regression.

Script set updates each cache immediately after G_ParseField for the matching
case-insensitive key, using BG_StringHashValue directly. In particular script
set does NOT apply the spawn-only game_manager alias. Repeated keys use the
last parsed value. Unrelated keys do not refresh either cache.

Tests cover 45 combinations of null/empty/nonempty names and five classname
variants, comparing the entire entity. Real script parsing checks mixed-case
keys, repeated target assignments, separate targetnamehash and no-alias
scriptName updates. Real free/neverFree fixtures seed both caches and verify
clear/preservation. This does not certify the complete script subsystem.

Consumers of these additional hashes and original G_ModifyTOI behavior remain
unported. The fields establish the lifecycle without replacing existing
string-based native lookups or claiming complete Nitmod lookup semantics.

Verification: native Windows-host build, 83/83 CTests, original instruction,
protocol/inventory checks and real Emscripten builds of all three modules pass.
Linux-i386 ABI and actual engine/browser gameplay remain unverified.
