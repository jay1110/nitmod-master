# Server browser filter and list integration batch

## Original behavior

UI ELF32 `UI_BuildServerDisplayList` VA 0x13fc0, size 0x11aa;
reference `ui/sorted/ui_ui_misc.c` around Ghidra labels 0x24b13..0x24b96.
Disassembly 0x14b51..0x14b77 excludes Nitmod when the Mod filter is 2 and
excludes non-Nitmod when it is 1. 0x14b8b..0x14b90 only enters NxAC filtering
when Mod is 1. Game matching is case-insensitive, exact `nitmod`.
The previous port had the Mod filter reversed and applied NxAC independently.

Restored: 0 = all, 1 = Nitmod only, 2 = exclude Nitmod. Unknown Mod values
behave like no filter as in the original. Original UI Cvar table 0x581c8
registers ui_browserNitmodonly with default 1 and CVAR_ARCHIVE; that default
is restored without forcibly changing users' archived values.

The existing original menu presents All=0 and Nitmod=1 and only shows NxAC
controls with the Nitmod selection. NxAC 0 ignores protection; 1 includes
protected servers; 2 excludes them. Hidden NxAC settings no longer delay or
exclude servers when viewing All/other mods. Invalid NxAC modes do not issue
unnecessary status requests.

## Native adapter safety fixes

Completed sv_NxAC status replies are cached and their engine request slot is
released through trap_LAN_ServerStatus(address, NULL, 0), following the stock
UI status-query lifecycle. Pending replies retain visibility and compensate
the early player total; tests verify two pending frames followed by completion.
This filter only displays advertised protection; it is not an anti-cheat backend.

Server-list insertion used to increment numDisplayServers before shifting,
writing an extra element. At capacity that write aliases numDisplayServers
itself. It now shifts only existing elements, increments afterward and refuses
insertion when MAX_DISPLAY_SERVERS is reached. This is deliberate hardening,
not claimed original-binary parity. The browser builder is declared in ui_local.h
so the fixture calls the real typed implementation, not a copied predicate.

## Verification

The full UI executable tests 128 Mod/NxAC/game-name/protection combinations,
engine request counts and release counts, pending/completed responses, filling
the final list slot and attempting one more insertion. Existing menu/bitflag
tests run in the same executable. Source assertion pins the original default.
No pak, menu, PK3, original module or server protocol was changed.
Actual browser/master-server end-to-end validation remains outstanding.
