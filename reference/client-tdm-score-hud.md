# Original Nitmod TDM score HUD

The reconstructed client keeps the original TDM wire state separate from the
`#` game-state snapshot:

- `z1 <limit>` sets the score required to win.
- `tsc <axis> <allies>` updates both team scores.
- game type `7` selects Team Deathmatch; game type `8` remains Deathmatch/FFA.

This mapping comes from `CG_ServerCommand` and `Nit_TDMScore_C` /
`Nit_TDMScore_R` in the supplied cgame reference. The centered widget uses the
original 240..400 score area and two 80-unit progress bars. Score changes flash
green when increasing and red when decreasing for 750 ms. `cg_TDMScorePos 1`
selects the two-line upper-right version; other values select the centered
version. The widget is disabled outside active TDM play or when `z1 <= 0`.

`/tdminfo` also consumes the typed score limit and the already reconstructed
`tdmOptions` bits from `#`: kill-based scoring (1), disabled artillery (4),
intermission voting (8), and timelimit ending (16).

No package/menu/script asset is modified by this port.
