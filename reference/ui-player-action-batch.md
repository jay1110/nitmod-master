# UI vote/referee/player action batch

`ui_nitmod_actions.c` consolidates 24 UI menu actions. Twenty-one existing
player actions and the existing refWarning/refWarmup actions move out of the
monolithic UI_RunMenuScript. The missing original votePoll action is new,
along with resetting ui_poll in voteInitToggles. This is not a claim of 24
previously missing features.

Evidence: original ui.mp.i386.so UI_RunMenuScript at ELF 0x210d0 (size 0x5dcc).
The PIC base is 0x54414. Original menu names and emitted format strings were
checked through the disassembly and the unchanged ELF string data. Poll
branch 0x230fc..0x23176 checks playerIndex against playerCount, reads ui_poll
into 256 bytes, and appends `callvote poll "%s"\n`. The seemingly unrelated
player selection guard is deliberately preserved. Original player commands
use quoted player names, not numeric row IDs; that protocol stays unchanged.

The dispatcher validates count/index against the real MAX_CLIENTS arrays,
rejects unterminated names, and rejects empty/control/quote/backslash/semicolon
arguments instead of placing them into executable text. Colors and ordinary
spaces are preserved. These are deliberate safety deviations for malformed
input. Warning and warmup retain their original 128-byte cvar read limit.
Unsupported menu actions continue into the existing dispatcher.

Verification: 2,520 player-action cases cover all 21 actions, count/index
boundaries and normal/unsafe names. Additional cases cover poll/warning/
warmup cvars, command text, unknown actions and case-insensitive dispatch.
An ELF reference test checks action names and formats. Native CTest and WASM
load checks are run; live administrative actions are not sent during testing.

No pak/menu/PK3 or original binary is changed. This is client-side support
for the original server command interface, not a new server permission system
or a claim that reconstructed qagame implements every corresponding action.
