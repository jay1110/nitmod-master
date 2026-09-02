# Original scoreboard and banner commands (experimental batch)

Original reference: sorted cgame_servercmds.c CG_ParseScore, CG_ParseKD
and the bp dispatch; cgame_client.c CG_BannerPrint; cgame_ui.c
CG_DrawBannerPrint. SHA-pinned inventory records cg_drawBanners=1, flags=1.

Implemented in this batch:

- sc0/sc1: original packets have count at argument 1 and seven fields per
  row from argument 2. ET sc0 instead has two team scores before count.
  NITMOD_UsesOriginalProtocol selects the format; original sc0 preserves
  team scores. All numbers, complete packet length, row capacity and client
  bounds are validated before committing. Original invalid-client fallback
  to slot zero is intentionally replaced with atomic packet rejection.
- kd0/kd1: original consumes kills/deaths at arguments 3+3*i and 4+3*i,
  with a reset/append cursor in existing scoreboard order. The port stores
  these in typed clientinfo kills/deaths, preserving cg.numScores. It rejects
  packets exceeding the already received scoreboard or containing malformed
  integers. Original reuses numScores as cursor and stores additional score
  fields; this port uses a separate cursor. Nitmod's complete K/D scoreboard
  layout is not implemented, nor is arbitrary packet reordering buffered.
- bp: mode 0 team chat, mode 1 console, mode 2 independently timed banner.
  All use server-command localization and honor live cg_drawBanners changes.
  Banner drawing uses existing font 0 at scale 0.2, centered lines, ten-second
  fade. Fixed line spacing, lack of original whitespace reflow, and color
  continuation across lines differ from original; exact HUD parity is pending.

Tests execute actual server-command dispatch for stock/original score
headers, appending rows, excessive counts, K/D chunks, malformed partial
updates, and enabled/disabled banner routing. Visual rendering and original
server packet order still need browser testing. This batch does not fix or
silence getnguid/fc. The earlier null indirect call has no supplied stacktrace
and is not declared resolved by these changes. No pak assets were modified.
