# Player action visibility integration

The original menu action vocabulary is already implemented. This change
repairs the typed ET adapter's four player visibility rules, rather than
claiming new menu actions: muted, not muted, no referee, referee.

UI_BuildPlayerList can invalidate playerIndex to -1 after a disconnect or
empty refresh. UI_OwnerDrawVisible previously indexed playerMuted and
playerRefereeStatus unconditionally with that value. The same bounded
selection predicate now gates both visibility and action dispatch (including
poll/warning). Invalid selections hide all four conditions; they never read
player arrays. Valid selections keep the existing status comparisons,
including RL_REFEREE versus RL_RCON distinction. Combined rules remain ANDed.

The actual UI executable exercises all four conditions over five list sizes,
four indices, both mute states, all referee states and contradictory flags.
Existing player-action dispatch tests continue to run. No pak/menu edits;
interactive original-server menu checks and roster identity across reorder
remain separate work.
