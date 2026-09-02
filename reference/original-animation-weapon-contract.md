# Original animation weapon identity contract

The hash-pinned cgame and qagame item tables agree on all 53 weapon item
records, including order, pickup names, weapon IDs and ammo/clip aliases.
BG_InitWeaponStrings (client ELF 0xbd00, server 0x1c7c0) clears 416 bytes and
iterates 52 IDs: these are 52 eight-byte string/hash entries, not the native
ET 2.60 count of 50. For each ID the first matching weapon item supplies the
name. Duplicate item records must not change first-match selection.

| Original name | Original ID | Current native ET interpretation of that ID |
| --- | --- | --- |
| Poison Syringe | 47 | WP_AKIMBO_SILENCEDCOLT |
| Bomb | 48 | WP_AKIMBO_SILENCEDLUGER |
| Tripmine | 49 | WP_MOBILE_MG42_SET |
| Poison Bomb | 50 | WP_NUM_WEAPONS boundary, not a weapon |
| Poison Landmine | 51 | outside the native weapon enum |

Tripmine already exists natively as ID 29, while original ID 29 is Mobile MG42.
Thus adding just the two missing array entries or accepting unknown names
cannot make the original server protocol safe. Several existing identities
need translation or an explicitly selected original protocol model too.

The extended test_weapon_items_reference.py now checks both item tables,
pins the 52-entry loop instructions in both binaries, and reads the unchanged
human_base.script. Every weapon union operand in that asset resolves against
the original first-match names, earlier definitions, or the special none token.
It checks over 100 operands, including the reported Poison Bomb occurrence.
This limited read-only grammar audit is not execution of the animation parser.

Conclusion: the reported unknown name is a reconstruction/identity gap, not
evidence of a broken original PK3. No assets or productive weapon enums were
changed in this step. Next work must establish original snapshot weapon IDs,
inventory/ammo bitset indexing, animation conditions and prediction together;
the runtime error remains open until that implementation is verified.
