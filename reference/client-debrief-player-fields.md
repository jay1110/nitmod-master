# Debrief player fields

Original CG_Debriefing_PlayerACC_Draw, PlayerXP_Draw and PlayerTime_Draw
(sorted cgame_ui.c) paint their labels at button.rect.x, then their values
at x + measured label width. ET instead treats rect.x as the value origin.
The original-protocol path now uses the original alignment for all three
fields; ET-layout clients keep the old placement.

Time lookup now searches only the received cg.numScores entries (bounded by
MAX_CLIENTS), not the entire stale backing array. This is a defensive
deviation from the original maxclients loop. Invalid selection/button/font
inputs are rejected. Weapon-stat iteration also rejects invalid positions
before adding one or indexing the array.

Renderer tests compare ACC/XP/time label placement in both protocol layouts
and verify that an empty scoreboard cannot display a stale time. Null panel
tests cover all three entrypoints. Browser panel-layout parity remains open;
pak and original artifacts are unchanged.

Continuation: PlayerRank_Draw and PlayerMedals_Draw now use the same original
label-origin convention. The original medal row retains seven skill slots,
16-square icons and 18-pixel advance only for nonzero medal entries. Null
panels/fonts are rejected before reading rect.x. Renderer tests cover all
128 medal masks in both protocol layouts, icon identity/order/position, and
rank/medal label placement. Existing rank bounds checks remain in effect.
