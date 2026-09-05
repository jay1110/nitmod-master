# Team support cooldowns

Original qagame maintains four independent remaining-time counters: airstrike
and artillery for Axis and Allies. `team_airstrikeTime` and `team_artyTime`
add their respective number of seconds after a successful call. `G_RunFrame`
decrements and clamps all four counters.

The reconstructed ET 2.60 path stores these counters in typed `level_locals_t`
arrays. Artillery no longer checks or increments the airstrike pool. Invalid
teams are rejected, negative delays behave as zero, and multiplication is
bounded before converting seconds to milliseconds.
