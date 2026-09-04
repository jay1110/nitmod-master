# Original player config extras and spectator roles

CG_NewClientInfo in sorted cgame_players.c reads token 0x59 (sc), 0x5a
(tv) and 0x70 (xp). The names are verified through the hash-pinned original
ELF wordlist extractor tools/extract_client_tokens.py. Stack members
local_824/local_820 follow the seven-int XP vector at local_840, matching
the role reads at cgs client offsets 0x95a8/0x95ac in WM_DrawClientScore.

Typed integration adds presentation-only nitmodShoutcaster beside nitmodTV
and parses up to seven space-separated signed XP counters into skillpoints.
Missing trailing values are zero, matching original zero initialization.
Unlike original strtol, invalid, overflowing, or excess values reject the
whole XP vector to zero. Roles are reset on each update; malformed role
values cannot grant a presentation flag. Native ET skillpoints are unchanged.
The medal-digit loop also stops at the actual string terminator.

Normal, compact and FFA scoreboards now distinguish SPECTATOR, SHOUTCASTER,
TV|SPECTATOR and TV|SHOUTCASTER, with CONNECTING taking precedence. This
follows the original normal/compact scoreboard role branches. FFA uses the
same label helper; its x position is adapted to fit the longest label within
the existing panel. It is not a pixel-parity claim. No extra game rights,
wall visibility, server authorization, or protocol messages are introduced.

Tests cover all role combinations, connecting precedence, partial/full XP,
negative counters, malformed values, overflow, excess values, reset and native
protocol isolation. Browser rendering and original-server update timing still
need live verification. Pak/PK3 assets remain untouched.
