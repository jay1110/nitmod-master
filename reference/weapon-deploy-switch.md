# MG42 and mortar deployment switch plan

Original alternate pairs are MG42 IDs 29/46 and mortar IDs 33/42.
The existing hash-pinned alternate-table test maps both pairs to native
identities and confirms the same pairs in cgame and qagame.

| Transition | Drop | Raise | Capture direction during drop | Alternate body raise |
| --- | --- | --- | --- | --- |
| MOBILE_MG42 to MOBILE_MG42_SET | 0 ms | 1250 ms | yes | no |
| MOBILE_MG42_SET to MOBILE_MG42 | 0 ms | 1722 ms | no | no |
| MORTAR to MORTAR_SET | 0 ms | 1667 ms | yes | yes |
| MORTAR_SET to MORTAR | 0 ms | 1000 ms | no | yes |

Raise branches compare against weapAlts[oldweapon], falling back to 250 ms
for unrelated targets. Evidence:

- MG42 deployed: qagame 0x2c2bf..0x2c2d6 / cgame 0x1b79f..0x1b7b6.
- MG42 packed: qagame 0x2c662..0x2c679 / cgame 0x1bb23..0x1bb3a.
- Mortar deployed: qagame 0x2c965..0x2c97a / cgame 0x1be25..0x1be3a.
- Mortar packed: qagame 0x2c928..0x2c93d / cgame 0x1bde8..0x1bdfd.

Mortar branches join the alternate-animation path at qagame 0x2c5da /
cgame 0x1ba9d; MG42 branches join the ordinary-raise path at qagame
0x2be42 / cgame 0x1b322. Existing prone event selection remains native.

Drop direction capture for MG42 is visible at qagame 0x2a71a..0x2a79a:
copy forward and right vectors, CrossProduct, AxisToAngles into the extended
movement state, then zero drop duration. Mortar uses the corresponding
sequence at 0x2a4aa..0x2a524. Packing-up paths only select zero time.
The native axis ordering is deliberately retained: forward in axis[0], right
in axis[2], their cross product in axis[1]. This is not replaced with a generic
Euler-angle approximation or a viewangles copy.

NITMOD_DeploySwitch is a pure typed four-transition plan. Shared native begin
uses zero drop time and one consolidated direction block, gated by the plan;
finish uses the raise duration and animation choice. Unsupported/same/cross-
family pairs and null output reject without modifying the output. Existing
prone/water rejection, event order, first-person animation, and movement
eligibility remain in their native callers; this helper is not permission to
deploy. Native drop/raise behavior is preserved, not extended.

Tests cover 2704 native/boundary pairs, null output for every pair and integer
extremes. Actual native alternate entries are checked, and the reference test
pins all eight raise immediates directly in the two hash-verified modules.
Source contracts check both consumers, the retained mortar guards and exact
gated direction construction. They do not execute engine placement or prove
original floating-point numerical parity; deployment replays, full movement
constraints and Linux-i386/WASM validation remain outstanding.
