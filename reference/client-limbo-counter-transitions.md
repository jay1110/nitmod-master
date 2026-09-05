# Limbo counter transition safety

The typed counter retains the original step limits (five for XP/statistics,
one otherwise), direction rules and decimal rollers. Reference:
`cgame_ui.c`, `CG_LimboPanel_RenderCounter` and its counter helpers.

Intentional safety extensions, not newly reconstructed gameplay:
- Calculate elapsed time and target distance in double before subtraction.
- On time rewind settle both endpoints to the current value; do not render
  a negative interpolation fraction.
- Skip zero-digit counters (including LMS XP) before dividing width.
- Calculate accuracy without overflowing hits * 100. Retain integer
  truncation and percentages above 100; saturate only at INT_MAX.

CheckLimboCounterTransitions calls the actual renderer under both protocols,
checks step state across integer extremes and time rewind, verifies LMS
suppression, and checks normal, zero-denominator and extreme accuracy.
No assets or network fields change. Browser visual verification is pending.
