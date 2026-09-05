# Deathmatch option runtime mapping

The following original `g_DMOptions` behaviors are mapped to typed ET 2.60
state:

| Bit | Runtime behavior |
| --- | --- |
| 1 | A hostile kill restores up to 20 health, capped at `STAT_MAX_HEALTH`, and sends the original `hpb` feedback command. |
| 2 | Enables the original Deathmatch medic regeneration branch. |
| 4 | Blocks `/kill` during Deathmatch. |
| 32 | Disables binocular artillery before charge consumption. |
| 128 | Removes `misc_cabinet_supply` entities before they are linked. |
| 16384 | Enables the intermission map-vote/map-cycle path. |

The client already consumes the `hpb` command and the shared settings snapshot,
so these server rules do not introduce a parallel protocol.
