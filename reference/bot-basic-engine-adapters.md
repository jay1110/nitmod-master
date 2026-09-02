# Basic semantic Omni-bot engine adapters

Four methods from the recovered ETInterface table now have typed C adapters
in g_nitmod_bot_entities.c. These are semantic implementations, not C++ ABI
shims and not installed into a loaded library's vtable.

| Slot | Original method/address | Typed behavior |
| --- | --- | --- |
| 29 | GetGameTime, 0x2220d0 | Return level.time unchanged, including signed values |
| 43 | EntityFromID, 0x224e00 | INDEXENT-style checked slot; unused non-world slots produce invalid handle |
| 45 | IDFromEntity, 0x223900 | Resolve current handle, return slot or -1 |
| 46 | DoesEntityStillExist, 0x2238c0 | Resolve current handle, return boolean |

EntityFromID is deliberately separate from raw G_NITMOD_BotEntityHandle:
original HandleFromEntity packs a non-null entity regardless of inuse, whereas
EntityFromID first calls INDEXENT. World is accepted despite unused/stale state.
Native slot identity is used, not mutable s.number. Malformed indices are
rejected defensively; original existence first rejects negative signed indices
but otherwise delegates to an unchecked original resolver.

The full-qagame test checks all 1024 slots as live, serial-invalidated and unused,
with s.number deliberately wrong. It covers world exceptions, invalid indices,
invalid handles and five signed time values. Actual runtime handle reset and
advance adapters are used. The original accessor/call/failure instruction bytes
are pinned in the reference regression; the slot/function hashes remain in
bot-loader-contract.json.

Native/WASM builds and all 83 CTests pass. Engine object construction, vtable
installation, library load/failure/unload and event delivery remain pending.
No native i386 C++ ABI or loaded Omni-bot/browser compatibility is claimed.
