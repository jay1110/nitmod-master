# Attacker-health death report

Original qagame `player_die`, address `0x77b9e`, consumes
`g_drawAttackerHP`.  A positive value sends the victim
`chat "<attacker> ^ghad ^3<health> HP" -2` when the attacker is a live client.
The original suppresses the report for bot victims and deaths while mounted
in a tank.  The typed port uses `r.svFlags & SVF_BOT`, `killedintank`,
`attacker->health` and `clientPersistant_t::netname`.

The message deliberately stays on the established chat server-command path,
so original native clients and the WASM cgame receive identical payloads.
No package asset or UI menu definition is involved.
