# noMidclipReload definition flag

## Midclip restriction consumer

NITMOD_MidclipReloadAllowed now consumes the loaded typed option. For regular
mapped weapons, a nonempty clip is disallowed only when noMidclipReload is
nonzero. For WP_MOBILE_MG42 and WP_MOBILE_MG42_SET, the option is ignored:
an empty shared MG42 clip passes; otherwise the explicitly supplied ability
word must contain bit 0x20. That word is NOT a native ET skill level.

Server evidence: the two identity branches precede the option read at
0x2879a..0x287ba. The MG42 clip read is 0x28808 (original player state +0x304
= ammoclip base 0x290 + original MG42 ID 29 * 4); ability test at 0x28812
uses pm +0x138, bit 0x20. Client equivalents are 0x17d18 and 0x17d22,
with option read at 0x17cc2. The typed helper uses verified native aliases,
not these offsets. It rejects negative clips/null inputs/unknown identities.

95744 cases cover 44 identities, 17 clip values, 64 ability words and both
option values, checking whole-state immutability. Additional tests cover
invalid inputs, INT_MAX counts and high ability bits. The actual source
loader/registry test also composes loaded options with this consumer and
checks that successful empty reload clears the restriction.

This remains one restriction, not the complete begin-reload gate: reserve,
weapon states, timers, original weapon-range eligibility and animation/event
effects are not activated. Binding the ability word to live pmove state also
remains pending. No active gameplay or protocol change is made.

BG_RW_ParseDefinition recognizes the bare `noMidclipReload` token and writes
one to private weapon-record offset +0x5fc: qagame ELF 0x35b1e, cgame
0x2620e. The next jump returns directly to the token loop; no integer value
is read. Repetition is idempotent. The registry's initially cleared record
supplies zero when the selected definition block omits the flag.

The typed replacement is nitmodWeaponOptions_t.noMidclipReload, loaded by
NITMOD_ParseWeaponOptions and G_NITMOD_LoadNativeWeaponOptions into the
caller-owned registry. Existing narrower parsers retain their strict contracts.
The extended parser accepts the previous ammo/classes/recoil subset plus
this flag. Both/both_altweap selection, bounded token traversal, quoted-token
rejection and fallback-only-on-open-failure remain unchanged. All four outputs
commit atomically; forced reload failure preserves the prior complete record.
An empty successful reload clears the option instead of retaining stale state.

The real source/registry test covers repeated flags followed immediately by
another field, both section selections, 30 truncated-stream cases, fallback,
unexpected numeric value, quoted flag, null output, failure rollback and reset.
All source handles opened by these scenarios are checked for release.

Consumer evidence: qagame PM_BeginWeaponReload reads +0x5fc at 0x287b2 and
branches to its nonempty-clip check at 0x289f0. Mobile MG42 identities 29/46
bypass this field via their own ability-bit rule. The isolated consumer above
does not activate the incomplete begin-reload policy or map
original numeric weapon states to ET's differently numbered enum. No global
weapon table or network message is changed. Full definitions and the client
source adapter remain unfinished; the parser is shared-capable typed C, not
a claim of complete cgame loading or original-engine replay parity.
