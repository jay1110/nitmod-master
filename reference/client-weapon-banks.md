# Original weapon bank ordering

The original cgame ELF symbol weapBanksMultiPlayer is at virtual address
0x12e7a0, size 0x1e0: ten banks of twelve little-endian weapon IDs.
Its nonzero bank-7 entries are 25, 51, 49, 43 (landmine, poison mine,
tripmine, adrenaline). The typed ET table previously omitted tripmine.

The shared bg_misc.c table now uses WP_LANDMINE, WP_TRIPMINE,
WP_MEDIC_ADRENALINE for bank 7. All other representable entries already
matched original order. Shared weapon IDs and network values are unchanged.
This table is compiled into cgame, qagame and ui; it does not grant weapons
or implement new firing mechanics. Selection still requires ownership/ammo.

Original IDs 47, 48, 50 and 51 remain unimplemented, not aliased. Their
entries are omitted and rows compacted, because zero terminates bank scans.
Leaving a zero hole before Tripmine would make later entries unreachable.

tests/test_weapon_banks_reference.py pins the original cgame SHA-256,
maps the ELF data section and compares every entry of every typed bank
against the existing wire-to-typed identities after those exclusions.
It is registered in CTest. The full-cgame test executes bank-7 selection
through three complete cycles and verifies that a depleted Tripmine is
skipped without blocking selection of adrenaline.

Verification: native build and 90 CTest tests; WASM builds and Node
loading/entrypoint probes. Pak content and original artifacts are unchanged.
No browser join test or complete Tripmine gameplay parity is claimed.
