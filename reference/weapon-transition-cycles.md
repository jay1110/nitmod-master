# Executed multi-phase weapon transition cycles

`PM_ProcessWeaponTransitions` extracts the existing ordered stage of
`PM_Weapon` without changing its decisions. It runs after the existing
weapon-change request and before firing checks:

1. Return while weaponDelay is positive.
2. Check reload input.
3. Return while either weapon timer is positive.
4. Complete an active reload.
5. Complete dropping and return for this frame.
6. Complete raising and return for this frame, or continue to firing checks.

The return value explicitly communicates whether PM_Weapon must stop this
frame. Timer advancement, delayed fire, earlier movement guards and later
firing logic remain in PM_Weapon. This is an extraction of the current
typed product code, not a new claim of complete original scheduler parity.

The test extractor now includes this function verbatim, alongside its actual
reload, switch, transfer and first-person-animation dependencies. Only the
body-script and condition services remain test doubles.

64 multi-step cycles cover Luger, four akimbo identities and three scoped
rifles; reload versus enabled alternate key; neutral/right lean; and reserve
1 versus 100. Tests cover the initial weaponDelay veto, repeated calls while
timers remain positive, scoped drop-to-raise-to-reload flow, held reload
input, an attempted switch during reload, final main-first clip transfer,
idle animation and a repeated call after completion. Whole-state checks
detect timer resets, duplicate events and unintended inventory changes.

Tests explicitly expire timers between stages; they do not simulate the
complete PM_Weapon time-advancement or firing path. A successful final stage
returns zero to permit later firing checks, as before. Host Debug build and
66/66 CTests pass; original-ELF, full engine and Linux-i386/WASM validation
remain separate work.

## Timer-boundary completion coverage

`TestTransitionTimerBoundaries` adds 3168 executed transition-stage cases:
44 mapped identities, weaponTime and weaponDelay independently -1/0/1,
four first-person animation gates (normal, dead, active animation timer,
no command weapon), and held reload/alternate input. Any positive timer
must return without mutation. Otherwise the stage must transfer native
inventory and reset READY, preserving negative timer values. Animation
suppression must not suppress completion. Pre-populated predictable-event
ring entries, the complete player state and pmove extension are checked.
Character/skill pointers are deliberately absent: an already-running
reload must not re-enter begin processing because a reload key is held.

This tests the existing native completion behavior, including the retained
adrenaline alias; it does not claim original inventory parity for that alias.
No product behavior changed in this additional test increment. The complete
host build and all 66 tests pass.
