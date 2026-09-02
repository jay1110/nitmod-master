# Alternate tables and scope-switch duration

Original weapAlts contains 52 signed 32-bit weapon IDs, at qagame ELF
0x2a5300 and cgame 0x12e660 (symbol size 0xd0). The new extractor verifies
each complete module's SHA-256 before decoding its ELF-mapped table. Both
tables are identical. All 44 reviewed native weapon identities map to the
same alternate identity as the executed native weapAlts table, including
NONE for weapons without an alternate. No native table entries change.

| Typed pair (both directions) | Original IDs | Drop | Raise |
| --- | --- | --- | --- |
| GARAND / GARAND_SCOPE | 24 / 39 | 250 ms | 250 ms |
| K43 / K43_SCOPE | 30 / 40 | 250 ms | 250 ms |
| FG42 / FG42SCOPE | 31 / 41 | 50 ms | 50 ms |

NITMOD_ScopeSwitchDuration centralizes these six directed transitions.
The shared native begin/finish paths call it after initializing the default
250 ms and before other weapon-family effects. The two duplicate FG42 cases
are removed. Non-pairs leave the caller's output unchanged; callers retain
the default and their existing non-scope overrides. Null output and invalid
identities are rejected without mutation. This is behavior-preserving
extraction, not a timing change or authorization to switch weapons.

## Original control-flow evidence

Drop FG42 duration: qagame 0x2a5fd..0x2a617 / cgame
0x19add..0x19af7 selects 50 for the alternate and 250 otherwise.
The two drop dispatch tables are decoded in the reference test:

- qagame GOT 0x2a4614, tables at GOT-0x76364 (IDs offset by 14)
  and GOT-0x762e0 (IDs directly indexed).
- cgame GOT 0x12dc44, tables at GOT-0x2e654 and GOT-0x2e5d0.
- In the first table all six identities reach the default-250 block.
  In the second only FG42 variants reach the 50/250 comparison; the other
  four identities reach the default-250 block.

Importantly, a matching alternate enters the second table even if the
first-person animation is suppressed: qagame 0x2a6d4..0x2a715 branches
to 0x2a5a6 on every animation-gate outcome. It must not be interpreted as
a 250 ms FG42 alternate delay when animation is suppressed.

Raise FG42: qagame 0x2c289 and 0x2c6e5 dispatch IDs 31/41 to
0x2c6ea..0x2c700; cgame 0x1b769 and 0x1bba5 dispatch to
0x1bbaa..0x1bbc0. Each compares against weapAlts[oldweapon], choosing
50 or 250. Other reviewed scope identities take the default-250 path
(qagame 0x2c696 / cgame 0x1bb56). Same-weapon early return is still
handled before duration selection; other timing/animation effects remain
native and are not claimed fully reconstructed here.

## Verification scope

The diagnostic checks actual native alternates against both original tables
and executes all 2500 native old/new duration lookups against the reviewed
original identity map. Separate C cases cover 400 invalid-identity pairs and
2500 null-output pairs. Source contracts pin both live call sites. Original
drop-table destinations are checked directly from the hash-pinned ELF data.
These checks do not execute original machine code or validate engine replays;
Linux-i386, browser/WASM and complete non-scope switch parity remain pending.
