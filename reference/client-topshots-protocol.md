# Original Topshots categories

CG_topshotsParse_cmd in sorted/cgame_client.c (line 20295) reads repeated
one-based category/client/hits/attempts/kills/deaths records terminated by
category zero. It indexes original aWeaponInfo and accepts 52 display rows.
The unused deaths field is consumed to preserve the six-field stride.

The port now accepts all 26 original categories and stores up to 52 rows.
ET retains 22 categories and a 44-row limit. Names are shared with the
debriefing renderer through NITMOD_WeaponStatName, avoiding divergent
category labels. Invalid categories/client numbers remain rejected.
Accuracy multiplication is widened before division to avoid signed overflow.

The full cgame fixture exercises all 26 original and 22 ET categories through
the actual parser, checking label, rounded accuracy, player name and rejection
of the first invalid category. No asset or engine ABI structures change;
topshotStats_t is private cgame state. Live server/browser parity is pending.
