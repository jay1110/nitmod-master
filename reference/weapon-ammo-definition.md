# Typed ammo-definition subset

Original qagame `BG_RW_ParseDefinition`: ELF `0x35320`, Ghidra `0x45320`.
The selected `both`/`both_altweap` block writes two distinct destinations:
the private weapon record (including `classes` at +0x6ac) and a separate
ammo record. The latter maps directly to ET 2.60 `struct ammotable_s`.

| Input key / native member | Original ammo offset | PC_Int_Parse call (ELF) |
| --- | --- | --- |
| maxammo | 0x00 | 0x35896 |
| maxclip | 0x08 | 0x35941 |
| defaultStartingAmmo | 0x0c | 0x35861 |
| defaultStartingClip | 0x10 | 0x358d1 |
| reloadTime | 0x14 | 0x35a21 |
| fireDelayTime | 0x18 | 0x35909 |
| nextShotTime | 0x1c | 0x359e9 |
| maxHeat | 0x20 | 0x359b1 |
| coolRate | 0x24 | 0x35811 |

Evidence: inspected sorted pseudocode and original i386 disassembly. Every
listed call loads the separate ammo argument from stack +0x4a0, adds the
listed offset (none for maxammo), then calls PC_Int_Parse. Production code
uses named native members, not these offsets. The parser accepts exact
case-sensitive key spellings. No corresponding assignment for native
`uses` or `mod` is introduced.

`NITMOD_ParseWeaponAmmo` parses into a copy of caller-supplied ammo defaults
and a zero-initialized class mask, then commits both only after the closing
weaponDef brace. Missing ammo fields preserve defaults; repeated selected
assignments use the last value. Unselected blocks do not modify either
destination. This ownership matches the distinction between the original
separate ammo table and the zeroed private weapon record, without claiming
that the caller's defaults have yet been reconstructed from the original.

`G_NITMOD_LoadNativeWeaponAmmo` composes the verified 44-weapon path table,
alternate selector, preferred/fallback opening, token adapter and parser.
The existing mask-only API stays strict and does not silently discard ammo
attributes. No global ammo table, inventory, prediction or protocol is changed.

Tests cover all nine members individually with distinct baseline sentinels,
all members together, both block selectors, every truncation boundary in
the two-block fixture, repeated blocks, negative values, integer limits,
overflow, invalid tokens, reusable borrowed token buffers and null outputs.
Loader doubles additionally check fallback, ignored alternate sections,
quoted-number rejection, failed-open handling and late-failure rollback.

Deliberate differences: failures are transactional; truncated definitions
and unknown selected attributes reject rather than retaining partial writes.
Only strict decimal integers are accepted. Both separate minus plus
2147483648 and combined -2147483648 now work; the magnitude is parsed
unsigned and checked before conversion. A second sign (including -0)
after a separate minus is rejected. Other selected fields (damage, names, recoil, etc.) remain unsupported,
not skipped. Client weaponConfig loading, complete metadata ownership,
reload semantics and native gameplay activation remain pending. Host tests
are not an original-engine runtime or Linux-i386/WASM parity proof.

## Integer token and resource-boundary follow-up

Original PC_Int_Parse (ELF 0x25a10) reads a second token for a leading minus,
checks TT_NUMBER and negates its intvalue at 0x25ad3. The port preserves the
two-token form but does not emulate unchecked engine numeric conversion:
decimal syntax, magnitude bounds and transactional failure remain enforced.
No claim is made that every engine lexer interprets out-of-range positive
tokens identically. The earlier split-INT_MIN limitation is removed, along
with an accidental acceptance of the double sign '- -0'.

New executable boundary tests use reusable borrowed token storage, all nine
ammo destinations and truncation before every token in a signed fixture.
Generated opaque client blocks verify depth 64 succeeds, depth 65 fails,
exactly 65536 reads succeeds when the last token closes the envelope, and
a needed 65537th token fails without calling the reader again. Engine-source
doubles verify the split minimum value and double-sign rollback through
native filename/alternate selection as well.
