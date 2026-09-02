# Bot axis-aligned world bounds

ETInterface slot 21, ELF 0x2248f0, is reconstructed as
G_NITMOD_BotEntityWorldAABB. It uses the same typed construction selector as
local AABB. The queried handle must resolve and be inuse; the selected
construction is not independently checked for inuse.

Normal output copies selected r.absmin/r.absmax. If selected has a client,
both Z limits gain 2 (original constant 0x22effc). No rotation/recomputation
from local bounds occurs in the normal path.

Only selected cached classname hash 0x1908e enables fallback. The fallback
condition is all-six-zero output bounds OR selected currentOrigin strictly
outside any limit. This test happens AFTER the client Z shift. Equality at
a boundary is inside. Fallback uses a fixed (-8,-8,-8)/(8,8,48) box translated
by GetEntityPosition of the ORIGINAL handle, not the selected construction.
The original ignores that position call's return value, starting at zero.
The C adapter represents the concrete original class, not custom C++ overrides.

The full-source fixture checks 72 profiles: selection yes/no, client yes/no,
special hash yes/no and nine box cases (inside, all zero, each of six outside
limits, exactly at both limits). Selected and queried origins differ; selected
construction is intentionally unused. Expected fallback uses independently
specified rotated center. Entity state, null outputs and stale/unused/invalid
input errors are checked. Reference tests pin the scalar, source fields, cache
comparison and original-handle reload. Complete method hash is in the slot
inventory.

Defensive null outputs return 3 before writes. Aliased output buffers and
extreme-value x87 rounding remain unverified. Script SetValues classname-cache
updates have since been connected; see script-classname-cache.md for scope.
No fresh-name workaround is used.
No loaded Omni-bot or engine/browser gameplay parity is claimed.

Verification: native Windows-host build, all 83 CTests, original instruction,
protocol and inventory checks, plus real Emscripten builds of cgame/qagame/ui
pass. These do not certify Linux-i386 ABI or actual engine runtime parity.
