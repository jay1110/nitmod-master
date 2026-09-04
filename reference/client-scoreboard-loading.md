# Nitmod scoreboard and loading refresh

## Loading refresh

The original `CG_DrawInformation` at the reconstructed cgame path throttles
connect/loading rendering to 50 ms. ET 2.60 used 500 ms. The client now uses
the original 50 ms cadence, while retaining the existing engine-owned connect
screen and all assets from the loaded PK3. No loading-screen asset or menu was
changed.

## Scoreboard layout

The original `CG_DrawScoreboard` call sites establish these row plans:

- normal play: 25 rows per team, compact fallback 33;
- intermission: 20 rows per team, compact fallback 33;
- Stopwatch intermission: two 15-row panels at y=90;
- gametype 8: one 610-pixel Death Match / Free For All table.

The typed port now selects those plans instead of the ET 2.60 8/9-row
intermission limits. Gametype 8 uses a single full-width table with server
name, player, K/D, XP and colored ping columns. K/D comes from the already
validated original `kd0`/`kd1` command path, score/ping from `score_t`, and
player identity from bounded `clientInfo_t` indexes. Spectators and connecting
clients receive explicit status text.

The reconstructed Deathmatch table deliberately does not guess the private
country-code wire table or missing country-flag atlas handle. `cg_countryflags`
remains registered but flag rendering awaits a typed source and registered
shader. Team boards still reuse ET's class/icon drawing where the underlying
types match.

`CheckScoreboardPlans` covers all gametype IDs 0..9 in live/intermission modes.
Native compilation, full CTest and WASM loader smoke verify the module paths;
they are not a pixel comparison with the original client.
