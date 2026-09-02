# Engine-to-module command audit

The existing `audit_engine_syscall_numbers.py` now emits schema version 2.
Each module retains its import report and adds an `exports` report, comparing
both directions and listing names occupying the opposite side's numeric slot.
This distinguishes absent names from dangerous numeric collisions.
COM_TRAP_GETVALUE and MOD_EXPORT_PADDING are read from the inspected Legacy
q_shared.h; unresolved constants still stop the audit rather than being guessed.

Actual local source comparison on 2026-09-02:

| Module | Shared names/numbers | Changed numbers | Mod-only names | Engine-only names |
| --- | --- | --- | --- | --- |
| qagame | 12 | 0 | 3 | 2 |
| cgame | 13 | 0 | 0 | 2 |
| ui | 14 | 0 | 0 | 0 |

No cross-name numeric collisions were found. The three old qagame bot commands
remain slots 11-13, unused in the inspected engine export enum. Both sides
explicitly/implicitly retain GAME_MESSAGERECEIVED at 14, so removing the old
bot names in Legacy did not shift that command.

Engine-only commands:

- GAME_DEMOSTATECHANGED: 15
- GAME_SNAPSHOT_CALLBACK_EXT: 16
- CG_LEGACY_CUSTOM: 1337
- CG_CONSOLE_COMPLETE_ARGUMENT: 1338

These are not implemented merely by matching the baseline enum values.
The current qagame unknown-command branch returns -1; cgame reports an error
on unknown commands. Do not invoke these extensions without verifying their
engine-side gating and negotiating support. No production enum, handler or
engine file was modified in this audit.

Tests add cross-name collision and engine-only extension fixtures, plus the
commented bot-command/explicit message-number case. All 74 host CTests pass.
The report remains source-only, with inspected-header SHA-256 values; it does
not prove call-site reachability, extension gating, argument layouts or browser
execution. The earlier import-number findings are unchanged.
