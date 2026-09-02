# Bot entity position adapter

Original ETInterface slot 19, ELF `0x223ec0`, is implemented by the typed
`G_NITMOD_BotEntityPosition` adapter. The slot and entire original function
hash are recorded in `bot-loader-contract.json`; instruction/constant checks
also run in `test_weapon_cvars_reference.py` against the hash-pinned qagame ELF.

The original resolves the handle, then independently requires `inuse` (including
world). Failure returns 3 without writing output; success returns 0. A non-null
client selects `r.currentOrigin`, independent of slot number. Every non-client
uses `AnglesToAxis(r.currentAngles)` and transforms `(r.maxs + r.mins) / 2`
into world space, adding `r.currentOrigin`. There is no brush-model condition.
The original scalar at ELF `0x22e008` is the float 0.5. Original shared offsets
are mins 0x134, maxs 0x140, currentOrigin 0x168 and currentAngles 0x174.

The full-source qagame fixture checks 48 combinations: three slots (player,
non-player, world), four independently specified cardinal rotations, both
client-pointer states and both brush-model states. Asymmetric bounds expose
incorrect origin-only/center calculations. The fixture also checks untouched
entity state, untouched output on stale/unused/malformed handles, and null
output rejection. State-trajectory origin is deliberately different.

Defensive difference: null output returns 3 rather than dereferencing it.
Intermediate arithmetic uses double before float output to avoid premature
float rounding; this is not a claim of bit-exact x87 extended-precision parity.
No C++ vtable shim or loaded Omni-bot runtime is installed by this change.
Velocity slot 18 was subsequently mapped through G_RunEntity's save/compute
sequence and ported separately; see bot-entity-velocity.md.

Verification: Windows-host native build, all 83 CTests, protocol contract test,
and the real Emscripten build of all three modules pass. These are build and
fixture checks, not native Linux-i386 or browser gameplay validation.
