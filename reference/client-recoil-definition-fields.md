# Client recoil definition compatibility

Original CG_RW_ParseClient in sorted/cgame_weapons.c parses recoil_pitchAdd,
recoil_yawRandom and recoil_pitchAddRandom as integers into offsets 0x1770,
0x1774 and 0x1778. Typed weaponInfo_t now retains these values, allowing
otherwise valid original weapon files containing the keys to load.

The inspected original CG_WeaponFireRecoil uses a fixed weapon switch and
does not read those fields. No speculative custom recoil effect is activated;
these client fields are distinct from the shared movement recoilDuration,
recoilYaw and recoilPitch definitions. Physics and protocol are unchanged.

Full-cgame tests exercise active file registration, stored values, all three
truncated field failures with whole-weapon rollback, and clearing fields on
successful replacement by a definition without them. Existing integer-token
semantics of PC_Int_Parse are retained. No pak files are changed.
This is parser compatibility, not completion of custom recoil/gameplay.
