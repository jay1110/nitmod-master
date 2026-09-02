# Satchel release inventory restoration

Original qagame G_FreeSatchel at ELF 0x8a570 was inspected directly with
objdump from the unchanged reference artifact (SHA-256
84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49).

The function clears the entity free callback, requires missile type, resolves
the client through s.clientNum, requires a connected client and covert-op class,
then performs three inventory writes and returns. After its PIC-address helper
there are no additional calls; in particular no G_AddEvent call appears.
The existing ET 2.60 function has the same inventory roles but additionally
emits EV_NOAMMO when the player holds the detonator. That event is absent in
the reference and has now been removed.

`game/g_nitmod_satchel_free.c` owns the typed implementation, linked in CMake
and SCons; the old definition was removed from g_missile.c. It clears detonator
reserve/clip and restores one satchel in the connected covert-op's clip, leaving
all other client fields untouched. Numeric decompiler offsets are not used.
The named inventory roles use the existing ET weapon identities; complete
private original structure/weapon-table ABI parity is not implied.

Null input and out-of-array s.clientNum return safely. Those bounds checks
are intentional defensive differences; the original would dereference invalid
input. Valid entity-array indices, including the last slot, retain the normal
client/type/class checks. No protocol command or cgame/UI handler is added.

600 compiled cases combine five owner indices, two entity types, three
connection states, five player classes, two held weapons and client presence.
Tests compare the entire client object against the expected three-field edit,
including eventSequence, and check callback removal. The test executable links
without G_AddEvent, so accidentally restoring that dependency also fails linking.
Native and WASM builds, 77/77 host CTests and protocol checks pass.
No original-engine replay or full satchel gameplay parity is claimed.
