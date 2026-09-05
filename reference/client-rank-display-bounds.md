# Player-statistics rank bounds

Both statistics output paths now use a bounded rank-name lookup. Valid
indices preserve the existing eleven names, previously compared with the
original rankNames tables at ELF 0x12ec00 and 0x12ec40. As in the original,
non-Axis clients use Allied names. Invalid ranks display UNKNOWN instead
of indexing outside the table; this is intentional safety hardening.

Tests invoke both actual statistics parsers for Axis, Allies and spectator
with all valid ranks and both adjacent invalid indices, plus integer extrema
on the shared lookup. No client state, rank calculation, assets or protocol
fields are changed. This is not an additional gameplay-feature port.
