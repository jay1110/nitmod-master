# Custom weapon recoil: typed subset

Original qagame BG_RW_ParseDefinition (ELF 0x35320) sets the private weapon
record's +0x5dc enable flag on any of recoilDuration, recoilYaw, recoilPitch.
Duration is PC_Int_Parse at +0x5e0; yaw/pitch are PC_Float_Parse at +0x5e4/+0x5e8.
Registration clears the private record, so omitted fields start at zero;
the presence of a key, not its nonzero value, enables the override.

Original PM_Weapon custom branch (ELF 0x2d3be..0x2d448, Ghidra rebased
0x3d3be..0x3d448) checks that flag and transfers the configuration to the
movement extension. Native equivalents are weapRecoilTime (command serverTime),
weapRecoilDuration, weapRecoilYaw and weapRecoilPitch. Original lastRecoilDeltaTime
is reset at 0x2d3a6 before choosing the custom or normal branch.

Yaw is cos((double)serverTime) * configuredYaw. Pitch is
fabs(cos((double)serverTime)) * configuredPitch. Time is not divided by 1000
and pitch's configured sign is not made positive. The original uses x87
fmuls followed by fstps (yaw 0x2d410/0x2d417, pitch 0x2d43e/0x2d445), so the
decompiler's apparent intermediate float cast of cos is not reproduced.

The implementation keeps a small typed configuration, not an offset-based
weapon record. NITMOD_ParseWeaponRecoil extends the ammo/classes subset with
the three recovered fields, handles split unary minus for integers/floats,
and commits ammo, classes and recoil together. The older narrow APIs keep
rejecting recoil keys. Client assets and other attributes remain unsupported.

NITMOD_ApplyWeaponRecoil applies only the custom branch to native pmoveExt_t.
It changes exactly five recoil members, including resetting lastRecoilDeltaTime;
it does not choose a weapon or use random state. Disabled overrides leave all
state unchanged, so this helper alone does not perform the original common
reset for ordinary recoil. Future integration must retain that reset before
branch selection. This helper is compiled into both cgame and qagame, but
PM_Weapon call sites and engine protocol remain unchanged.

Safety deviations: non-finite angles and nonpositive duration are rejected
at application with no state change. The parser still permits zero/negative
duration like an integer field, keeping syntax separate from safe application.
Strict decimal floats replace engine numeric-token coercion; failed parses
roll back instead of retaining partial writes. Double arithmetic preserves
the operation ordering but is not claimed bit-identical to x87 extended
precision or a different platform's libm cosine implementation.

Tests compose parsing and native-state application for both sections, verify
all untouched state bytes, token-by-token truncation, invalid floats, double
signs, zero-only enabling, unselected zero defaults, nulls and invalid durations.
Reference arithmetic at times 0/1/2 tests phase and pitch sign independently;
additional integer boundary times exercise the full command-time domain.
Registry lifecycle remains pending. Preferred/fallback loading of this larger
subset is now exposed by G_NITMOD_LoadNativeWeaponRecoil.

## Composed engine-source adapter

The existing native-identity path selector and engine token adapter now route
the expanded subset to NITMOD_ParseWeaponRecoil. Caller-owned ammo defaults
are retained for missing fields; class mask and recoil start cleared. All
three outputs remain unchanged if opening, path validation or parsing fails.
Every successfully opened source is released once. As with the smaller APIs,
fallback occurs only after open failure, never after malformed contents;
identical preferred/fallback paths are not retried.

The composed test links the actual path selector, source adapter, parser and
native recoil application, replacing only engine source syscalls. It covers
base/scoped K43 using the same filename but different blocks, preferred and
fallback success, truncation at all 28 token boundaries for both selections,
quoted numeric tokens, nonterminated engine token strings, both opens failing,
identical-path failure, invalid paths/outputs and unsupported weapon identity.
A subsequent empty definition clears a stale recoil override and mask while
preserving ammo defaults. This is a caller-level load test, not proof of an
engine registry reload lifecycle or original-engine gameplay parity.
