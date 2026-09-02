# AABB construction selection and local bounds stages

The local/world AABB methods share a construction-selection stage. It is now
implemented in G_NITMOD_BotBoundsEntity using typed parent, target_ent, chain,
spawnflags and ET_CONSTRUCTIBLE fields. It resolves the handle and checks inuse,
then for constructibles queries G_ConstructionForTeam using parent if present,
otherwise the entity itself. Axis is preferred, then Allies, then the original
entity. The existing ET 2.60 team helper matches original ELF 0x88ec0. Selected
target/chain entities are not independently required to be inuse.

Evidence: local method 0x223ca0, constructible test 0x223d18, parent load
0x223e00 and team calls 0x223e17/0x223e35. The native fixture covers 256
combinations of flags 0..15, parent, target, chain and target type, plus
non-constructible bypass and invalid/unused/stale input handles.

The field at original 0x5c0 is a cached classname hash, not a bot class enum.
G_SpawnGEntityFromSpawnVars loads classname at 0xcd08b, calls BG_StringHashValue
at 0xcd20b and stores the result at 0xcd219. The native hash of misc_mg42 is
0x1908e, the exact local-bounds special-case value.

G_NITMOD_BotLocalBounds accepts a selected entity and an explicit cached hash.
It copies local mins/maxs, replacing all-six-zero bounds with (-8,-8,-8) and
(8,8,48) only for hash 0x1908e. Fourteen cases check the cache condition and
each individual nonzero component. Current classname intentionally contradicts
the supplied cache: recomputing from classname would be a semantic change.
Null arguments reject with 3 before output writes; success returns 0.

Follow-up: a handle-to-local-AABB adapter and the map-spawn cache lifecycle
are now connected; see bot-classname-cache.md. Dynamic writers remain pending.
The original stage-only scope was:
Cached-hash initialization, invalidation and dynamic classname changes still
need full lifecycle reconstruction. World AABB's player Z offset and special
replacement positioning remain unported. No fabricated cache default or
fresh-hash shortcut is introduced. No C++ interface connection is claimed.

Verification: native Windows-host build, all 83 CTests, original instruction,
protocol and inventory checks, plus real Emscripten builds of cgame/qagame/ui
pass. Linux-i386 ABI and loaded-library/browser gameplay remain unverified.
