# Bot entity velocity adapter

ETInterface slot 18, ELF 0x224010, is reconstructed as
`G_NITMOD_BotEntityVelocity` using typed ET 2.60 fields. This is a semantic C
adapter, not an installed C++ virtual method.

After handle resolution the original independently checks inuse, even for
world. Failure returns 3 without changing output; success returns 0.
For a client pointer in physical slots 0..63, or any non-mover entity, output
is s.pos.trDelta (original 0x24/0x28/0x2c), not client ps.velocity.
The original compares the entity byte displacement to 0x17fff: 64 slots of
0x600 bytes. The typed implementation uses MAX_CLIENTS, not level.maxclients
or mutable s.number. Other ET_MOVER entities return
`(r.currentOrigin - oldOrigin) * 50`. The float constant at ELF 0x22e04c
is exactly 50; using frame duration or instantVelocity would change behavior.

The previously unknown original vector at 0x4d8/0x4dc/0x4e0 is oldOrigin:
G_RunEntity copies currentOrigin there at 0x7ea06..0x7ea3b, then subtracts
it for instantaneous velocity at 0x7ebc2..0x7ebf2. This matches the native
G_RunEntity save-before-simulation and delta-after-simulation sequence.
Original instruction and scalar bytes are regression-pinned against the
SHA-256-checked ELF. The complete slot function hash remains in the loader
contract report.

The full-qagame test exercises 24 profiles: four physical slots including the
63/64 boundary and world, three entity types, and client present/absent.
All candidate velocity fields contain different values, level.maxclients is
deliberately 1, and s.number contradicts the actual slot. Positive, negative
and zero mover deltas are checked. Additional tests cover unused/stale/invalid
handles, unchanged output on failure and unchanged entity data.

Defensive difference: null output returns 3. Intermediate subtraction uses
double before float output; bit-identical extreme-value x87 behavior is not
claimed. Real library callbacks, native i386 ABI and browser gameplay remain
outside this fixture's coverage.

Verification: Windows-host native build, 83/83 CTests, protocol and inventory
checks, and real Emscripten builds of cgame/qagame/ui pass. No new wire commands
or cgame/ui protocol changes are introduced.
