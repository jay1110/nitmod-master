# Entity freeing and the pending bot serial hook

Update: the serial reset/free hooks are now active; the historical pending
notes below are superseded by the runtime-hook section.

Original G_FreeEntity (ELF 0xe71d0) calls Bot_Event_EntityDeleted at 0xe71f5,
before entity-array removal, the optional entity free callback, unlink at
0xe7292 and neverFree test at 0xe7297. Therefore serial advancement happens
even when neverFree subsequently retains the entity. A hook only after the
neverFree check or memset would not match. The bot event itself sends the old
handle before advancing its serial, as documented in bot-entity-handles.md.
Original call/test bytes are now pinned by the reference regression.

Bot_Interface_InitHandles is called by the original console load and reload
paths before Bot_Interface_Init; reload first shuts the interface down. A
complete initial-startup/reset graph is still required. Native spawnCount is
a different lifetime counter, not a substitute for the bot serial.

The full-qagame test now executes actual G_FreeEntity in four free-callback /
neverFree combinations. The callback observes the live entity before unlink;
the engine double observes unlink before memory clearing. Retained entities
must remain byte-identical. Freed entities must be cleared except classname,
freetime and preserved spawnCount. Actual G_InitGentity then reuses the slot
and increments spawnCount. This proves current typed free ordering, not bot
notification delivery. Registry contents in this fixture are empty.

No bot table reset or deletion hook is activated in production in this step.
Runtime table ownership, loader/reset transactions, old-handle event dispatch
and the original smoke-cache cleanup remain open. The verified ordering now
provides a regression baseline for that later integration. Native build,
82 CTests and protocol checks pass; no engine/world/browser replay is claimed.

## Runtime serial hooks enabled

The startup graph is now confirmed by original vmMain instructions: call to
Bot_Interface_InitHandles at 0x812de precedes G_InitGame at 0x812fa. Both calls
are byte-pinned. The native GAME_INIT dispatch now resets a module-owned typed
handle table immediately before G_InitGame. Original console load/reload reset
paths remain obligations for the future loader, which is not implemented.

g_nitmod_bot_entities.c owns the table and provides checked index-to-handle and
handle-to-entity adapters. G_FreeEntity advances its slot at entry, before
registry cleanup, callbacks, unlink and neverFree. The adapter finds the slot
by bounded pointer equality rather than pointer subtraction on foreign objects
or trusting mutable s.number. This is O(MAX_GENTITIES) per free and can later
be optimized with equivalent validated address arithmetic. World resolution
retains the original special case. SpawnCount remains independent.

The existing full-source free test now proves old-handle invalidation before
the callback and unlink, serial 1->2 even with neverFree, and current-handle
resolution after retained/free-and-reused entities. Source checks pin reset and
free-hook placement. Native/WASM builds and 82 CTests pass.

Only table maintenance is active. No Omni-bot deletion event is sent, no library
is loaded, and no original smoke-cache cleanup is added. A future loaded event
must run inside the adapter before its serial mutation. Original initialization
timing is instruction-verified; the full game-init path is not executed by the
host fixture. No complete Omni-bot or browser gameplay parity is claimed.
