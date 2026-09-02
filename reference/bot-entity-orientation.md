# Bot entity orientation adapter

ETInterface slot 17, ELF 0x2240e0, is implemented by the typed C adapter
G_NITMOD_BotEntityOrientation. It resolves the handle and independently checks
inuse, including world. Failure returns 3 without touching output; success
returns 0. This is not an installed C++ ABI shim.

A non-null client selects client->ps.viewangles (original client + 0xb0);
otherwise r.currentAngles (entity + 0x174) is selected. No physical client-slot
restriction exists here, unlike GetEntityVelocity. Both paths call the original
AngleVectors at 0xfeda0, forwarding forward/right/up in that order. Its three
output-pointer checks make each vector optional, including all-null success.
The right vector is not the negated right vector used for AnglesToAxis axis[1].

Evidence: the loader contract pins the complete original slot function hash;
the reference regression pins accessor, call and null-output-check instructions.
The native full-source fixture asserts gclient_t.ps starts at zero and
playerState_t.viewangles starts at 0xb0. The separately compiled WASM layout
probe also includes viewangles for both ET 2.60 and ET:Legacy headers.

Tests cover 192 profiles: three slots including non-client and world, four
cardinal rotations, client pointer present/absent, and eight optional-output
masks. Player view angles deliberately differ from entity angles; expected
forward/right/up vectors are literal independent values. Entity and client
state remain unchanged. Additional checks cover unused/stale/malformed handles
and untouched output on failure.

Arbitrary-angle floating-point/x87 bit parity and actual loaded-library
callbacks remain unverified; the existing ET 2.60 AngleVectors is reused.
No wire commands or cgame/ui protocol changes are introduced.

Verification: native Windows-host build and all 83 CTests pass, as do the
protocol/inventory checks and real Emscripten builds of all three modules.
The separately executed ET 2.60/ET:Legacy WASM layout comparison reports no
differences for the selected fields, including the newly added viewangles.
This selected-field comparison is not a full ABI or gameplay certification.
