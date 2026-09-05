# Constructible XP sharing

Original qagame `TryConstructing` distributes construction XP on every accepted
progress step when `g_constructiblexpsharing` is nonzero.  The recovered award
is `constructxpbonus / (duration / FRAMETIME) + 0.01`; the small bias is retained
because construction progress is accumulated into the integer-networked
`entityState_t::angles2[0]` field and completes at 250.

The normal zero/default mode still grants the complete construction bonus to
the player who finishes the stage.  Sharing mode suppresses that completion
award, preventing the finisher from receiving both incremental and full XP.
All state is mapped through typed ET 2.60 `gentity_t` and constructible fields.
