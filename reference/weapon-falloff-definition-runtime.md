# Weapon DistanceFalloff integration and original anomaly

The original parser stores yes=1/no=2 at private weapon offset +0x68c.
FireWeapon passes that integer through Bullet_Fire to Bullet_Fire_Extended.
The binary resolves the ambiguous decompilation:

- Bullet_Fire_Extended at VA 0xf9440 reads argument 7 from esp+0x118.
- 0xf978c tests it against zero; jne at 0xf979d enters base falloff.
- 0xf98ec compares it with 1, followed by sbb edx,edx; not edx; and edx,0x10.
  This is an unsigned >=1 test, NOT equality. Both defined values set the flag.

The live server now passes explicitly defined values 1 and 2 from its map
cache into the existing falloff path. Thus original `no` also enables
falloff; this is intentional preservation of observed binary behavior,
not a claim that the option behaves as its label suggests.

Absent/invalid definitions retain the existing native caller default.
That fallback is a compatibility choice; original default record setup is
not fully reconstructed here. Mobile MG branches retain their fixed caller
mode rather than consulting the definition, matching original dispatch.
Penetration recursion retains the resolved mode without additional I/O.

Tests cover yes/no/invalid parsing and cache resolution for both caller
defaults, invalid indices, MG exclusion and reset. They do not replay
distance-dependent damage through the entire hit pipeline. No UI/cgame,
protocol, PK3 or asset changes. Browser validation remains outstanding.
