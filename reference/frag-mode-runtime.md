# TDM and DM round-limit runtime

Original references are `CheckExitRules` in split qagame `nitmod_unknown.c`,
the death-match winner branch in `nitmod_client.c`, and
`G_ScriptAction_EndRound` in `nitmod_script.c`.

The shared gametype enum now represents Nitmod's complete public catalog:
map-vote 6, team deathmatch 7 and deathmatch 8. This also prevents qagame's
startup range validation from replacing these modes with objective mode.

During active play, TDM compares the two authoritative team scores with
`g_TDMScore`, records the winning team, prints the original-style result and
queues intermission. A map script `wm_endround` awards `g_TDMObjBonus` to the
script-selected winner and publishes the updated scores instead of ending the
whole match immediately.

DM compares each connected non-spectator's `sess.game_points` with
`g_DMFragLimit`. The winner is published through the original `DM <client>`
server command already consumed by cgame, announced, logged and sent to
intermission. Non-positive limits disable their respective limit check.

No package assets or reference binaries are changed.
