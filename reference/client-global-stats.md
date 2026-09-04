# Original Nitmod global statistics overlay

The reconstructed cgame now owns the complete safe lifecycle for the original
`globalstats` / `ggs` / `glstats` path:

- `globalstats` toggles the overlay and binds it to the current snapshot client.
- Opening sends exactly one `ggs <client>` request.
- A successful `glstats` response atomically parses all 15 signed wire values.
- `glstats ... -` selects the original error state.
- Missing responses time out after 15 seconds.
- Map changes, disconnects and client changes clear the state.

The original 600 by 120 centered panel, heading, waiting state, error state and
numeric payload are rendered. The private ELF tables at `0x133e60`, `0x133f00`
and `0x133f40` recover all 13 visible positions and two-line labels: Kills,
Deaths, Team kills, Time played, Revives, Tripmine kills, Goomba kills, Scoped
HS, Fthrower kills, objectives constructed/destroyed, rounds played and Satchel
kills. The original protocol carries 15 signed values; all are retained, while
the last two remain hidden because the original has no label/position entries.

Opening expands the panel over 250 ms from its center. Closing contracts using
the original 0.8-minus-progress curve and releases the state at zero. Geometry,
font scale, panel alpha and border alpha follow the transition rather than
leaving a full-sized stock overlay visible for the entire animation.

No files below the package tree are used or modified by this implementation.
