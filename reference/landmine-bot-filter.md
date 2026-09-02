# Initial mine trigger bot filter

Original G_LandmineThink checks Omni-bot bit 0x20 at ELF 0x8ac87 and SVF_BOT
at 0x8ac93. Without the override bots skip own-team and spotted enemy mines.
Humans and override-enabled bots proceed to geometry. G_LandmineSpotted
checks modelindex2 at 0xa8, matching the existing native accessor. Tests pin
these instructions and the typed field offset/flag constant.

g_OmniBotFlags is registered under the original Cvar name omnibot_flags,
default 0, flags 1025 (CVAR_ARCHIVE | CVAR_NORESTART), tracking/reset zero.
The hash-pinned registration test checks these values. Only the recovered
mine bit is implemented; registration does not implement other bot features.

G_NITMOD_MineBotContact runs after team/owner filtering and before geometry
in G_LandmineThink, not LandminePostThink. Default zero intentionally changes
native bot eligibility to this recovered policy. No wire message changes.

2048 cases cover flags 0..255, bot/human, own/enemy team and spotted/unspotted,
plus defensive null guards. Unrelated SVF_BROADCAST is set during testing.
Original-byte/Cvar and source-order checks complement these isolated tests.
Native/WASM builds and all 81 CTests pass. Bot_Event_PreTriggerMine delivery,
complete Omni-bot integration, private mine variant and live engine/browser
replay remain pending; a working Omni-bot subsystem is not claimed.
