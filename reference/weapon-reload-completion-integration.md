# Executed native reload completion

The integration test now extracts PM_FinishWeaponReload verbatim from the
product source in addition to PM_ReloadClip and the existing begin/raise
functions. Completion executes actual native item aliases, ammo capacities,
recursive akimbo transfer, READY transition and gated idle animation. It
requires no character/model services and emits no completion event.

6336 direct completion cases cover 44 reviewed weapon identities, three
reserve amounts, empty/one/full/overfull main magazines, three sidearm magazine
conditions and four first-person animation gates. For non-akimbo identities
the sidearm parameter is deliberately irrelevant. An independent transfer
oracle applies the weapon-indexed capacity and shared-reserve arithmetic,
main hand before sidearm. The sidearm identities and idle-animation exceptions
are explicit test expectations rather than calls to the product's selectors.

Whole-player-state and extended-state comparisons check that only inventory,
weaponstate and the permitted idle animation change. Event arrays/parameters,
event sequence, timers and unrelated state remain unchanged. Overfull
magazines return excess to reserve, preserving existing native behavior.
Adrenaline is covered as a native regression case only: its native syringe
alias is not changed or claimed equal to the original Nitmod independent slot.

The 840 previously introduced fast-reload begin scenarios now continue through
actual native completion after simulated timer expiry. These cover eight fast
weapons, two non-fast controls including akimbo, multiple native skill levels,
three starting states and duration boundaries. Expected inventory transfer,
idle animation and no additional event/body callback are checked across the
combined begin/finish sequence. Temporary timing fixtures are restored before
completion; magazine capacities remain unmodified throughout.

This tests functions used by the live shared client/server path, not copied
approximations. Nevertheless, it does not execute the enclosing PM_Weapon
scheduler or original ELF modules. Direct completion assumes its caller has
already gated state and timers; no new product guard or behavior is introduced.
Full recovered inventory/default/ability integration, engine replays and
Linux-i386/WASM release validation remain outstanding. Host build and all
66 CTests pass.
