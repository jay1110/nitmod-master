# Finish-stage same-weapon exceptions

Stock PM_FinishWeaponChange returns after committing weapon/state and updating
scope/sidearm state whenever oldweapon equals newweapon. Nitmod explicitly
continues the raise phase for original weapon IDs 1, 28, 48 and 50.
Only 1 (WP_KNIFE) and 28 (WP_SMOKE_BOMB) have reviewed native identities in
this port. IDs 48 and 50 remain outside this implementation; they are NOT
interpreted as native enum values 48 and 50.

| Branch | qagame ELF address | cgame ELF address |
| --- | --- | --- |
| Equal old/new target dispatch | 0x2c281..0x2c289 | 0x1b761..0x1b769 |
| Exceptions 28, 48, 50; continuation | 0x2c6a6..0x2c6c1 | 0x1bb66..0x1bb81 |
| Exception 1; otherwise return | 0x2c74e..0x2c757 | 0x1bc0e..0x1bc17 |
| Default 250 ms raise addition path | 0x2c696..0x2c6a1 to 0x2be42 | 0x1bb56..0x1bb61 to 0x1b322 |

The shared native finish function now uses NITMOD_WeaponChangeNeedsRaise.
Different weapons continue as before. Same knife/smoke targets reach existing
250 ms timing, animation-condition update and raise animations; other same
targets return as before. The predicate is evaluated against the committed
target, not the requested target: lost ownership becomes NONE. Commit and
reload-intent raising states still happen before this predicate. No change
is made to begin-change authorization, event generation, usercmd or protocol.

Tests cover all 2500 native old/new pairs and 10000 compositions with target
commit, ownership loss and reload intent. The real-call source contract pins
the order and continuation into existing timing/animation code. These are
unit/source tests, not an engine replay or original-binary execution proof.

During this review, the FG42 alternate timing branch was also inspected:
drop chooses 50 ms on matching alternate, otherwise 250 ms at qagame
0x2a5fd..0x2a617 / cgame 0x19add..0x19af7. Raise makes the same selection
at qagame 0x2c6ea..0x2c700 / cgame 0x1bbaa..0x1bbc0. No timing constants
were changed. Complete dispatch-table/path coverage for all scope pairs and
all animation gates remains pending; this inspection does not establish
full switch parity.
