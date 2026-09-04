# Class console command

Reconstructed `class <class> [weapon number]` in the typed cgame console
dispatcher. Original CG_Class_f ELF VA 0x33700, SHA-256 of reference cgame:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

Original first-character switch table at 0x102ec0 maps lowercase c/e/f/m to
Covert Ops/Engineer/Field Ops/Medic; other input defaults to Soldier. Command
requires a snapshot, an argument and an Axis/Allied local client. Optional
one-based weapon choice uses strtol numeric-prefix semantics; absent, empty,
zero, negative, >6 and empty slots fall back to the class default.

Original class tables: Axis 0x130d20, Allies 0x130e20, 48-byte records with
six weapon IDs starting at +16. Typed constant lists reproduce those choices
for original servers, including opposing SMGs in Medic/Engineer/Field Ops
and STEN for Medic/Field Ops. Native reconstructed servers retain their ET
class lists. Wire conversion occurs only when sending to original servers.
The emitted original command is `team <r|b> <class> <weapon> ` plus newline;
no new server handler or capability is required.

Successful selection updates the typed primary menu slot, marks loadout
selection and provides a center message using existing weapon descriptions.
The menu index is normalized to the resolved valid slot rather than preserving
the original -1/out-of-range request. This deliberate safety difference and
the reused descriptions mean presentation parity is not claimed. This batch
does not port the additional class weapons into reconstructed qagame gameplay.
The limbo list integration is now documented in client-limbo-class-lists.md.

Tests execute the console dispatcher for both protocols, two teams, five
classes and eight weapon selections (160 cases), checking exact team commands,
selection and loadout state. Original wire expectations are independent numeric
tables transcribed from the ELF. Spectator/no-argument rejection is tested.
Pak assets and original binaries remain unchanged. Browser join, class changes
and visual feedback still require live testing.
