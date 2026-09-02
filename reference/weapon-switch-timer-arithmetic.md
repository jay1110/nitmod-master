# Defined weapon-switch timer addition

Original drop adds its selected duration at qagame `0x2a410` and cgame
`0x198f0`. The raise stage adds at qagame `0x2be48` and cgame `0x1b328`;
the alternate zero-duration branch also uses an ADD at `0x2c5e0` /
`0x1baa3`. These are 32-bit machine operations.

Both active native weapon-change functions now use the same defined
32-bit addition as READY reload. The helper was renamed from
`NITMOD_AddReloadTime32` to `NITMOD_AddWeaponTime32` to reflect its scope.
Its implementation and the hardened opt-in reload contract are unchanged.
No timer clamps, new state gates, duration changes or protocol fields were
introduced. Other timer arithmetic sites remain outside this change.

504 executed cases cover 18 reviewed directed alternate transitions,
seven existing timer values, normal/reload-intent switching and separate
drop/raise execution. Tests first verify the known duration from a zero
timer, then compare the extreme-timer call against an independent unsigned
modulo oracle. Whole player and extension state plus animation/condition
call counts must match. This includes positive overflow and zero-duration
transitions, without invoking C signed-overflow arithmetic in the oracle.

The cases call the actual product begin/finish functions; they do not claim
that the full engine scheduler normally reaches these extreme states.
Host Debug build and all 66 CTests pass. Original-ELF replay, sanitizer and
Linux-i386/WASM release checks are still pending.
