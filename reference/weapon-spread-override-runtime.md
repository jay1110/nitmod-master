# Active weapon spread definition

Original `G_GetWeaponSpread` in sorted/nitmod_weapons.c selects the nonzero
private spread integer at +0x5d8, otherwise its weapon-specific defaults.
The native defaults already match the listed firearms. Knife, panzerfaust
and poison syringe now explicitly return zero like the original, without
the previous unsupported-weapon diagnostic.

The live getter now consults the map-owned definition cache before its
fallback switch. All existing Bullet_Fire call sites use getter-backed
spread macros, so the base override is applied before aimSpreadScale,
MG stance multipliers and Bullet_Fire's existing skill adjustment. The
cached integer is converted to float once; zero retains the fallback.
Invalid/unloaded identities leave the output untouched; no file I/O is
performed during shooting. Map reset clears it with other weapon options.

Loader/cache tests cover zero, positive, negative and INT_MAX values,
invalid identities, null output and reset. These do not replay actual
shot traces or establish original skill/prone-delay parity.

DistanceFalloff remains inactive: the recovered parser stores yes=1/no=2
at +0x68c, FireWeapon passes that field unchanged, while the recovered
Bullet_Fire_Extended tests it against zero. Exact disassembly verification
is needed before choosing between observed behavior and intended semantics.
No client, UI, protocol or asset changes in this increment.

Follow-up: the complete comparison sequence has now been decoded and the
explicit option is active; see `weapon-falloff-definition-runtime.md`.
