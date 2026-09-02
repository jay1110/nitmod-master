# Caller-owned weapon subset registry

Original BG_RegisterWeapon (ELF 0x363c0) returns for an already registered
weapon unless force is nonzero. Otherwise it zeroes the private record,
marks it registered, stores its weapon ID and loads its selected file.
The qagame initialization loop in sorted nitmod_game.c calls registration
with force=1 for BG_WeaponInWolfMP identities and zero, across IDs 0..51.
This is evidence for cache/force semantics, not authority to enable a partial
replacement of that initialization loop.

g_nitmod_weapon_registry.c now owns the recovered subset in caller-provided
storage indexed by native ET weapon enums. Each record contains loaded ammo,
class mask, recoil and registration state. Only the 44 verified path-table
identities can be registered or retrieved. Reset clears every record; callers
must reset or zero-initialize storage before use. Retrieval is read-only and
returns NULL for unsupported or unloaded identities. No original offsets or
private weapon IDs are used to index the native array.

Registration without force reuses a loaded record without opening a file.
A new or forced load copies explicit caller ammo defaults into a temporary
record and uses the real native-path/source/parser adapter. Success publishes
the complete record. Mask/recoil start zero, ammo omissions retain the supplied
defaults. Base and scoped weapons keep separate records even when sharing a
filename. Successful empty reload clears old overrides.

Deliberate safety deviation: failure does not set registered and does not
overwrite the last good record. The original marks/clears before attempting
the parse. First-load failure is retryable here; failed forced reload keeps
the previous value. No automatic invalidation on directory changes is added:
the caller must force reload, as with the original cache gate.

Evidence: engine-source integration test covers first load, cache hit with
no I/O, independent base/alternate records, failed parse/open rollback across
the whole registry, successful empty reload, reset, invalid identities and
retry after first-load failure. Existing parser/path tests remain in place.

This is a subset registry, not a complete BG_Weapons replacement. No global
instance or G_InitGame/PM_Weapon/pickup hook is installed. Full attributes,
authoritative ammo defaults, multi-weapon initialization/failure policy and
matching cgame ownership must be reconstructed before activation. The source
build and mocked engine tests do not prove original runtime or i386 parity.
