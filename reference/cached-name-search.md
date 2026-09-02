# Cached classname and script-name searches

Original nitrox_FindByClassNameHash (ELF 0x10e820) and
nitrox_FindByScriptNameHash (0x10e890) now have typed C implementations named
G_NITMOD_FindByClassNameHash and G_NITMOD_FindByScriptNameHash.

NULL starts at slot zero; a valid entity pointer starts at the following slot.
Both scan ascending slots strictly below level.num_entities, require inuse
and compare the corresponding cached integer. There is no string comparison,
hash recomputation, world exception, or special rejection of hash zero/-1.
The earliest matching live slot is returned; otherwise NULL.

Defensive differences: foreign/one-past pointers return NULL without pointer
subtraction. Negative entity counts return NULL and counts above MAX_GENTITIES
are clamped. These protect cases where original raw pointer arithmetic could
walk invalid memory. Native string-based lookups are not globally replaced.

The full-source fixture exercises 6144 slot/hash/method profiles: every one
of 1024 slots, hashes 0/-1/12345 and both methods. Each profile checks NULL and
previous-slot starts, exclusive current-slot start, count boundaries, missing
hashes and unused slots. Strings and the other cache deliberately disagree.
Additional cases cover first/next among multiple matches, invalid pointers
and malformed counts. Full entity table and count are restored afterwards.
Original instruction tests pin next-slot addressing, count and field access.

These tested search primitives are ready for individually reconstructed callers.
Call-site migration and G_ModifyTOI remain pending; complete Nitmod lookup or
loaded Omni-bot behavior is not claimed.

Verification: native Windows-host build, all 83 CTests, original instruction,
protocol/inventory checks and real Emscripten builds of all three modules pass.
Linux-i386 ABI and actual engine/browser gameplay remain unverified.
