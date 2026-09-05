# Limbo counter timing

Reference: `src_nitmod_decompiled/cgame/sorted/cgame_ui.c`,
`CG_LimboPanel_RenderCounter_RollTimeForButton` (line 13097).
The original returns 15 ms for XP, 100 ms for class/team counts,
1000 ms for skills, and 50 ms for respawn/clock counters. Statistics
use 200 / absolute difference for distances 1 through 4, otherwise 50 ms.

The typed implementation now selects the original 15 ms XP timing only
for the original Nitmod protocol; ET 2.60 retains 50 ms.

Intentional safety differences: a zero statistics difference returns 50 ms
instead of converting infinity to an integer. Difference calculation uses
double before subtraction, avoiding signed overflow for extreme inputs.
No assets, wire fields, or server behavior change.

`CheckLimboRollTimes` exercises both protocols, all six non-statistic counter
types, positive/negative distances including zero, and integer extremes.
Visual parity in the browser remains unverified.
