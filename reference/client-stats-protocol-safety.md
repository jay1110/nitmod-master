# Client statistics protocol safety

The original `wstats`, `gstats`, `astats`, `astatsb`, `bstats`, `bstatsb` and
`wbstats` presentation code consumes variable server tuples. The ET 2.60 base
used `atoi(CG_Argv(...))` directly and then indexed `clientinfo[]` and
`aWeaponInfo[]`; malformed or truncated dedicated-server messages could
therefore read beyond either table, particularly under WASM.

`CG_NitmodStatsArg` now enforces `argc` and strict signed-integer parsing for
the shared ranking paths. Topshot and best/worst-shot records require complete
five-integer payloads, weapon statistics require exactly two nonnegative
values, client indices stay below `MAX_CLIENTS`, weapon-stat indices stay in
the `WS_*` range, and list counts cannot exceed `MAX_CLIENTS`. A malformed
tail stops parsing without indexing an attacker-controlled slot.

Valid original tuple order, accuracy arithmetic, text formatting, fade state,
commands and weapon names remain unchanged. This is a cgame-only receive-side
hardening and changes no pak/menu asset or qagame wire identifier.

The shared `gstats`/`wstats` payload additionally receives an atomic preflight.
It validates the client and round header, rejects mask bits outside `WS_MAX`,
requires five nonnegative counters for every selected weapon, consumes the
three damage counters only when the original presentation would consume them,
rejects skill bits outside `SK_NUM_SKILLS`, requires every selected XP value,
and rejects trailing fields. Cached rows and `clientInfo_t.skillpoints` are
therefore unchanged when any part of the packet is malformed.
