# Auto-reload preference defaults

Original ammoTableMP has 52 records of 72 bytes. Its auto-reload preference
flag is the int at +0x38 used by PM_CheckForReload, not any member after
coolRate in native ET's smaller ammotable_t. The extractor now reads this
field independently of its ten-int prefix and supports both hash-pinned
original modules: qagame table 0x2a69a0, cgame 0x12fd00 (each size 0xea0).

Both original modules agree. Among the 44 mapped identities, 21 require the
auto-reload preference and 23 bypass it. NITMOD_WeaponAutoReloadDefault
returns the original flag through a separate typed lookup; native ammo
structure/layout and global defaults remain unchanged. Unknown identities
and null output reject, with output unchanged. The existing explicit semantic
identity translation remains mandatory; original IDs never index ET arrays.

The diagnostic executes the C lookup for every native identity. Its Python
reference test compares all 44 returned flags to both hash-pinned binaries,
and asserts unsupported identities retain the output sentinel. Another 88
checks compose the returned defaults with NITMOD_BuildReloadPolicy under
enabled/disabled user preference, preserving the 21/23 split.

This provides original static defaults only. The extra secondary-attack
reload setting still needs a verified live binding, and possible runtime
definition overrides must not be invented from unrelated native fields.
No active gameplay or protocol hooks are changed.
