# Sniper-war loadout reconstruction

The `g_war == 2` branch is reconstructed from original qagame
`SetWolfSpawnWeapons` code around address `0x0005c5c7`.

- every player retains the base knife;
- `n_sniperWarOptions` bit 1 grants binoculars and the binocular inventory key;
- bit 4 grants the K43 scoped variant independently of team;
- Axis receives K43 plus K43 scope, Allies receives Garand plus Garand scope;
- both team rifles receive the original 500 reserve rounds and 10-round clip;
- the branch returns before the ordinary class loadout is added.

Bit 2 belongs to the sniper headshot/damage path and is intentionally tracked
separately from this spawn-loadout reconstruction.

The same typed adapter now covers the other recovered `g_war` branches:

- mode 1 grants a Panzerfaust with one reserve rocket;
- mode 3 grants Axis KAR98/GPG40 or Allies Carbine/M7 with the original
  500-round reserve and ten-round rifle clip;
- mode 4 returns with the common knife and no class equipment.

All four modes return before the ordinary class/tool grant, matching the
original control flow.
