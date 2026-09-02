# Script set classname lifecycle

The existing ET 2.60 etpro_ScriptAction_SetValues now implements the original
classname_nospawn alias and classname-cache update path (ELF 0xb61a0).
The alias normalizes to classname before adding spawnVars and parsing fields.
Its no-spawn flag is sticky for the entire invocation, even when an unchanged
classname_nospawn precedes a changed regular classname. The existing changed
flag is also sticky: changing away and back still triggers the final action.
Comparison is case-insensitive; case-only changes retain the old cache.

After a detected change, G_CallSpawn runs unless no-spawn was requested. Its
return value is ignored as in the original. Cache refresh follows, then the
first trap_LinkEntity. The existing second link-if-linked is retained. Other
field edits or unchanged classnames do not implicitly refresh stale caches.

Sixteen full-source scenarios call the real parser with initially linked and
unlinked entities. Cases cover unchanged/case-only names, alias case-insensitive
matching, unknown classes with no-spawn, sticky alias across multiple keys,
change-away-and-back, real flag-spawn rejection in LMS and ordinary origin
editing. An engine callback checks the cache at every link boundary and models
link state updates. SpawnVars must contain normalized keys. No engine/world
simulation is claimed by the callback fixture.

Reference regression pins original nospawn state, spawn/hash calls, cache stores
and relink instructions. Additional target/scriptname cache lifecycle has since
been connected; see target-script-name-hashes.md. G_ModifyTOI and original hash
lookup consumers still require reconstruction.
Missing-value fatal paths and complete script execution are not newly certified.

Verification: native Windows-host build, 83/83 CTests, original instruction,
protocol/inventory checks and real Emscripten builds of all three modules pass.
Linux-i386 ABI and loaded Omni-bot/browser gameplay remain unverified.
