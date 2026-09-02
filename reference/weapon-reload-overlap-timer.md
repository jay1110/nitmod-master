# Active firing reload timer compare/store

The original qagame instructions at `0x288d0..0x288d8` compare reload
duration with weaponTime and directly store the duration only if greater.
Cgame does the same at `0x17de0..0x17de8`. This is max(existing, duration)
for the already accepted firing states, not an addition of durations.

Native begin previously expressed the store as
`weaponTime += reloadTime - weaponTime`. Although equivalent over unbounded
integers, the intermediate subtraction can overflow signed int, for example
with weaponTime INT_MIN and duration INT_MAX. Shared Pmove now uses the
original direct assignment. This removes undefined arithmetic without
changing normal timing, animation, state or event behavior.

196 native begin executions cross seven existing timer and duration values
(INT_MIN, -1, 0, 1, 20, 1000, INT_MAX), both firing states and native fast
reload off/on. Tests compare whole player and extension state against an
independent max/scaling oracle, with one body event and one fill event.
The temporarily modified ammo-table duration is restored before assertions.
The source contract prohibits reintroducing the subtract/add expression.

Complete host Debug build and 66/66 CTests pass. No sanitizer or original
ELF execution is claimed. READY-state addition, original negative-duration
policy and other arithmetic sites are not modified or certified by this
change; Linux-i386/WASM release validation remains pending.
