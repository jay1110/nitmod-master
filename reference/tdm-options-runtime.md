# TDM option runtime mapping

The typed ET 2.60 qagame now implements the independently verified Nitmod
`g_TDMOptions` bits below.

| Bit | Runtime behavior | Original evidence |
| --- | --- | --- |
| 1 | Team score is one point per credited hostile kill; XP still advances skills but no longer adds to the TDM team score. | `G_AddSkillPoints` at qagame `0x000dedef` and `G_AddKillSkillPoints` at `0x000df8d0`. |
| 2 | Blocks `/kill` in Team Deathmatch. | Original command path and typed `Cmd_Kill_f`. |
| 4 | Disables binocular artillery before charge consumption or target tracing. | Original `Weapon_Artillery` at qagame `0x001083aa`. |
| 8 | Enables the map-vote/map-cycle path for Team Deathmatch. | Original map-vote initialization and exit paths. |
| 16 | Enables normal timelimit termination in Team Deathmatch; without it only the TDM score limit ends play. | Original `CheckExitRules` at qagame `0x0008c383`. |

Other weapon/charge-related bits remain deferred until their complete call
paths can be mapped without changing unrelated ET 2.60 weapon semantics.
