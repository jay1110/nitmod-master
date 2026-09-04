# Original Nitmod team scoreboard row presentation

Sources: sorted/cgame_ui.c WM_DrawClientScore (line 17249),
WM_DrawClientScore_Small_isra_1 (16802), WM_TeamScoreboard (17469).
The implementation uses a typed presentation plan in cg_nitmod_scoreboard.c/h,
called from both normal/compact team and spectator loops. ET protocol rows
keep their previous renderer. Existing DM rows are not replaced by this port.

Recovered behavior:
- Normal 7x14 and compact 6x12 shadowed text, name limits, original K/D
  offsets, score/ping/lives placement, and 285-pixel own-row highlight.
- Country atlas positions differ between row sizes. Ping -1 and 999 suppress
  country flags. Connecting, spectator, shoutcaster and TV labels reuse the
  already ported label formatter; this batch supplies their row positioning.
- Original sc word 6 contains status bits, not an ET player class. The parser
  stores these independently as score_t.nitmodFlags (a private struct field).
  Bit 4 selects friendlycross; bit 2 selects BOT instead of numeric ping;
  low two bits select the stamina/ready marker outside GS_PLAYING.
- Original client powerup masks 0x60/0x80 select objective/disguise icons.
  Death/revive markers use respawnsLeft and same-team health. Normal rows
  choose one status marker; compact rows can accumulate several. Class icons
  use clientInfo.cls via BG_ClassSkillForClass, visible to same-team viewers
  and spectators, never the packed score flags as an array index.
- g_maxlives/g_alliedmaxlives/g_axismaxlives control the lives column; missing
  g_maxlives preserves the original enabled default. Column headers and the
  first-row offset are adjusted with the same original layout. Existing
  headers, row ordering, counts, backgrounds and intermission logic remain.

Defensive differences: invalid client/class indices are rejected or omit
the class icon; absent shaders are not submitted. Input strings are copied
into bounded presentation records. Cgame private score_t grows by one int;
network packets, playerState/entityState, qagame and UI ABI are unchanged.
No pak, menu, PK3 or original shared object is edited.

Tests: 6,912 combinations of row size, status flags, powerups, team, health,
max-lives mode, ping and game state; extra exact default-column assertions,
LMS, clipping and invalid input checks. A renderer fixture captures actual
shader/rectangle calls for both sizes and checks highlights, flags and all
icon placements plus real glyph emission. The command fixture checks sc0
status-bit ingestion. All 97 native CTest tests pass; WASM build and Node
load/entrypoint probes pass. Browser screenshot/original-server visual parity,
all original compact-row corner-case offsets, full scoreboard and full
Nitmod completion remain unverified.
