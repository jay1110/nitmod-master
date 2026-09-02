# Cached classname lifecycle: map-spawn subset

The original entity field at 0x5c0 is represented by the typed integer
gentity_t.nitmodClassnameHash, appended outside the engine-shared prefix.
Zero-initialized entities start at zero. G_InitGentity does not refresh/reset
this field (original complete function 0xe6e10..0xe6e9e). G_FreeEntity's normal
whole-entity clear resets it to zero; neverFree preserves it. The existing
full-source free-order fixture now seeds a nonzero hash and checks both paths.

G_NITMOD_RefreshClassnameHash uses BG_StringHashValue for a nonempty classname
and -1 for null/empty names. It is called after the native map-spawn
G_CallSpawn/failure-G_FreeEntity sequence, matching original 0xcd087..0xcd219.
Thus a failed spawn may hold the hash of "freed" after deletion. It is not
refreshed automatically on every classname assignment or entity initialization.

G_NITMOD_BotEntityLocalAABB now composes the typed construction selector and
local-bounds stage with the SELECTED entity's stored hash. Tests check empty,
null and case-varied names, stale cache retained across G_InitGentity, explicit
refresh, and replacement construction's hash rather than the queried hash.

Follow-up: G_CallSpawn and dropped-item team hashes (0x3317f/0x36af1) are now
connected; see team-item-classname-cache.md. Scope remains partial:
etpro_ScriptAction_SetValues can
recompute or invalidate the hash after changes/respawn. Those script paths are not
implemented by this change. Therefore complete dynamic-entity AABB parity and
global cached-classname compatibility are NOT claimed. World AABB has since
been implemented using this cache; see bot-world-aabb.md.
No engine-shared structure or wire protocol is changed; private entity stride
changes and must be supplied by the rebuilt module as usual.

Verification: native Windows-host build, 83/83 CTests, protocol checks and
real Emscripten builds of all three modules pass. Spawn call ordering has a
source regression check, not a full map-load test. Actual engine map startup,
Linux-i386 ABI and browser gameplay remain unverified.
