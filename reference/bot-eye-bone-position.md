# Bot eye and bone positions

Typed C adapters implement the concrete ETInterface behavior for eye position
(slot 15, ELF 0x224750) and bone position (slot 16, ELF 0x2245d0).
Both reuse G_NITMOD_BotEntityPosition, preserving client origin versus rotated
non-client bounds center and handle/inuse validation.

Eye position adds the client's signed ps.viewheight to output Z after a
successful position query. It uses neither ps.origin nor a fixed standing
height. Original fildl at 0x224802 reads client + 0xbc. Native assertions check
gclient_t.ps offset zero and playerState_t.viewheight offset 0xbc; the separately
compiled WASM comparison now includes viewheight too.

Bone position ignores the entire signed bone argument and returns position,
not eye position. This is original behavior, not a temporary skeleton stub.
Original code never reads the bone stack argument at +0x68; it uses output
at +0x6c, and delegates to virtual slot 19 at 0x224637. Compiler-generated
fast paths inline the same position calculation when slot 19 is unchanged.

Scope: these adapters represent the recovered concrete ETInterface. Custom
C++ subclasses overriding virtual GetEntityPosition are not supported by the
current C adapters. Eye maps a delegated failure to 3; bone propagates it.
Null outputs defensively return 3 through the position adapter. Floating-point
limitations of that adapter apply here too. No library/vtable is installed.

The full-source fixture checks 60 valid profiles: three slots including world,
client present/absent, five signed heights or bone IDs, and both methods.
Bone IDs include INT_MIN and INT_MAX. Asymmetric rotated bounds, deliberately
different ps.origin, unchanged entity/client state and null output are checked.
Additional stale, unused-world, invalid and malformed handle cases verify
failure leaves output untouched. Hash-pinned instruction tests and complete
slot hashes in bot-loader-contract.json preserve original evidence.

The split-source CSV has an eye-position row but no named bone-position row;
the latter is tracked here and in the ELF-derived slot inventory, not invented
as a generated split-source entry.

Verification: native Windows-host build, all 83 CTests, protocol/inventory
checks and real Emscripten builds of all three modules pass. The separately
executed WASM layout comparison against ET:Legacy reports no differences for
the selected fields including viewheight. These checks do not establish
native Linux-i386 ABI, loaded Omni-bot or browser gameplay parity.
