# Local Nitmod HUD and modal global statistics

The reconstructed qagame advertises gamename=nitmod with nitmod_csLayout=et260.
NITMOD_UsesOriginalProtocol must remain false for that server: changing it
would reinterpret weapon/event IDs, XP words and configstrings incorrectly.
The new NITMOD_UsesNitmodHud predicate instead selects visual presentation
by gamename alone. Status bar layout, skill/XP display, portrait suppression,
compact compass/map placement and aspect-ratio anchors use this decision.
Limbo input and camera width follow the same geometry. Full-screen overlays
continue bypassing anchored HUD scaling in both Nitmod protocol modes.

Local skill text reads clientInfo.skill, not the original-only display array;
local XP still reads STAT_XP, not original high/low words. The local status
renderer adapts pmext sprint time, native adrenaline and native medic maximum
health in a temporary player state. It does not mutate snapshots. Missing
original support-availability flags are not fabricated. Original-only powerup,
live-stat and other protocol-dependent widgets are intentionally not enabled
indiscriminately; this is not complete local/original HUD feature parity.

CG_Draw2D now honors the boolean result of CG_NitmodDrawGlobalStats: a visible
or closing panel terminates subsequent HUD drawing. Kill/death popups, spree
labels, center notifications and auxiliary windows can no longer be drawn
over it. Queue reception/console logging are unchanged. When the closing
animation completes, normal rendering resumes in that frame.

Tests extend the geometry/cursor inverse matrix to ETmain, original Nitmod
and reconstructed Nitmod across seven resolutions. Existing full-screen
overlay tests cover all three modes and exposed a fallback that has also
been corrected. Browser visual verification remains pending.

## Omni-bot: confirmed missing implementation, not fixed

src_2.60/CMakeLists.txt links the ET botai sources; game/g_main.c routes
BOTAI_START_FRAME to BotAIStartFrame. The reference nitmod_omnibot.c has
Bot_Interface_Init, a library loader using dlopen, and lookup of
ExportBotFunctionsFromDLL. That interface is not linked into productive
qagame. Typed bot-handle/entity helpers already present are not a working
Omni-bot runtime. The Companion service has no Omni-bot backend either.

Completion requires the typed engine adapter and callbacks, a compatible
Omni-bot runtime built for WASM (or an implemented external bot backend),
navigation/script assets and lifecycle/gameplay integration tests. Native
i386 shared libraries cannot be loaded as WASM. No fake enable switch,
pretend success path or unsupported library loading was added.

No pak/PK3/menu/original reference artifacts changed.
