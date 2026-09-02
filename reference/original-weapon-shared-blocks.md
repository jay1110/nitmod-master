# Original weapon definitions and remote join allocation failure

The September 2 remote-join log reports rejected `both` blocks in mp40,
thompson, sten and fg42 definitions, followed by a zone allocator failure.
The deployed weapon files are not present in the local pak directory. No
asset has been edited or replaced.

## Proven parser behavior

`src_nitmod_decompiled/cgame/sorted/cgame_weapons.c`,
`CG_RegisterWeaponFromWeaponFile`, skips `both` and `both_altweap` blocks
and parses `client` media. The first keyword is an unnamed Ghidra global
at 0x110c1f; original cgame ELF virtual address 0x100c1f contains
`both\0both_altweap`. These blocks are not client weaponInfo_t fields.

The typed cgame parser now skips these shared definitions. Unlike the
original flat scan, it handles balanced nested braces and rejects truncated
blocks, releasing the parser source using CG_RW_ParseError. Existing client
media parsing is unchanged. This does not implement shared gameplay fields
in qagame or resolve original weapon ID differences.

The full-cgame fixture in test_original_charge_dispatch exercises eight
synthetic definitions 100 times through CG_RegisterWeapon: both block names,
nested blocks, stock client-only media, missing opening brace, premature EOF
and an unsupported keyword. It checks one source open/close per attempt,
successful sound registration after valid blocks, and visible errors on
invalid input. This is not a test of the deployed PK3 weapon contents.

## Handshake

NITMOD_AdvertiseCapabilities sends the reconstruction-only `nitcap` command
only when serverinfo explicitly declares nitmod_csLayout=et260, and never
during demo playback. Tests cover stock, original and reconstructed server
identities. Original commands getnguid, fc and kd0 are still unsupported;
they are not silently acknowledged or given invented responses.

## Allocation crash remains unresolved

Local ET:Legacy src/qcommon/common.c Z_TagMalloc raises the reported error
when it cannot find a sufficiently large free zone block. The requested
552 and 44 bytes are allocation sizes including allocator overhead, not
total WASM memory consumption. The second failure occurs while handling
the first. The log alone does not distinguish exhaustion, fragmentation,
a leak or corrupted allocator metadata. It also does not prove these
weapon-parser errors caused the allocation failure.

Need a fresh-tab startup log and `meminfo` before failure; if reproducible,
an engine build with ZONE_DEBUG/allocation diagnostics or an allocator
stack trace is the next step. Do not blindly increase heap/zone defaults
or claim the parser fix resolves this crash. Neither the deployed engine
nor a remote connection was exercised by these local regression tests.
