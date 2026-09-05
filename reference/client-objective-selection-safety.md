# Limbo objective selection safety

The original objective menu cycles 0..numobjectives inclusive; the last
entry is the map overview and sends obj -1. The existing typed path had
unbounded numobjectives parsing and unchecked description-array indices.

Count parsing is now strict and bounded to MAX_OBJECTIVES. Invalid or
stale selected indices normalize to the overview before rendering,
increment/decrement or requests. Null buttons/fonts are rejected. Valid
selection and wire commands are unchanged; malformed input handling is a
deliberate safety difference, not original undefined-behavior parity.

Tests cover both protocols, zero/normal/excessive/negative/malformed counts,
integer overflow, invalid selection fallback and valid obj 0 requests.
No pak assets or server-side objective gameplay changes. Browser testing
of joins/map transitions remains necessary.
