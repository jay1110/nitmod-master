# Omni-bot entity handle codec (not runtime-connected)

Current status: runtime table reset/free maintenance and checked entity adapters
are now connected; see bot-handle-free-order.md. Earlier isolated-state notes
are historical. Loaded bot-interface/event delivery remains unimplemented.

Latest extension: typed table initialization and per-slot serial advancement
are implemented below; the older lifecycle-pending note concerns runtime hookup.

Original HandleFromEntity at ELF 0x21e520 returns a four-byte C++ value via a
hidden result pointer. Its two 16-bit stores at 0x21e556/0x21e559 encode entity
index in the low half and the current m_EntityHandles serial in the high half.
Null entity encodes low 0xffff/high 0. Original EntityFromHandle (0x21e490)
compares the serial's bit pattern and entity inuse. World index 1022 is accepted
even on serial mismatch or unused state. Original table stride is four bytes;
it includes other flags, so it must not be aliased to a native short array.

nitmod_bot_handle.c/.h now provide pure typed packing, checked index/serial
extraction and resolution against caller-supplied serial/inuse arrays. They
borrow the arrays and never manage entity lifetimes. The codec uses fixed-width
bits, not pointer truncation or compiler-dependent C++ return conventions.
Original instruction pairs/world constant are hash-pinned in reference tests.

Tests exhaust all 65536 serial values (including sign-bit values), all valid
slots and all invalid low-half bit patterns. Matching, stale, unused, world and
null-table cases are checked. Malformed indices reject before table access:
this intentionally avoids the original unchecked signed-index lookup. Null
tables reject even for world handles as a defensive API contract.

The codec is built into qagame by CMake/SCons but has no gameplay caller yet.
It does not substitute spawnCount for the original serial table. Serial-table
initialization, deletion ordering/rollover, flag storage, loaded-interface ABI
and Bot_Event_PreTriggerMine delivery remain to be reconstructed/integrated.
Native/WASM builds and 82 CTests pass; no live Omni-bot or browser runtime parity
is claimed. Existing original artifacts and module wire contracts are unchanged.

## Serial table mutation, isolated

Bot_Interface_InitHandles (ELF 0x21f3f0) iterates 1024 four-byte records. At
0x21f415 it writes serial=1; it clears only flag bits 0/1 at byte offset 2.
Byte offset 3 and upper flag bits remain unchanged. Bot_Event_EntityDeleted
(0x221910) performs the same flag clear and increments the 16-bit serial,
replacing a wrapped zero with 1. Its loaded-interface branch sends event 0x0d
with the OLD handle before reaching that mutation. Mutation occurs even if
Omni-bot is not loaded. Subsequent smoke-cache cleanup is not part of the codec.

nitmodBotHandleEntry_t gives these bytes explicit serial/flags/reserved fields.
NITMOD_BotInitHandles and NITMOD_BotAdvanceHandle implement only the recovered
table mutation. Caller-owned storage must already be initialized (for example
zeroed) before preserving flags/reserved bytes. There is no hidden global table,
automatic spawnCount substitution, event dispatch or game-entity cleanup hook.
A future adapter must notify with the old handle before calling AdvanceHandle.

Tests exhaust all 65536 serial inputs and all 256 flag bytes, validate all 1024
initialization slots, preserved reserved bytes and untouched neighboring slots,
and reject invalid indices/null tables defensively. Original reset/increment
instructions are pinned to the reference hash. Native/WASM builds and 82 CTests
pass. The original 16-bit serial can repeat after 65535 nonzero generations;
this is not an indefinitely unique identity or a security token.
