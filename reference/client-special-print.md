# Original special notifications

Original-server `an type xp` now handles types 1 (kill assistance), 2
(suicide helper), 3 (teamkill assistance), 4 (first blood), 5 (first headshot)
and -2 (revenge). `hpb amount` displays the original `+%i HP` format in green.
Both commands are gated to the original Nitmod protocol. No qagame command,
capability or wire ID is changed, and no menu/PK3 modification is required.

Evidence: sorted cgame_servercmds.c's `an` switch and `hpb` branch call
nitrox_AddSpecialPrint with y=90, the recovered RGB colors and signed XP.
The native original ELF symbols are nitrox_AddSpecialPrint 0xf7150 and
nitrox_DrawSpecialPrint 0xf71f0; disassembly confirms the negative-alpha
`fchs` instruction at 0xf726c. These are distinct from Ghidra source labels.

The typed state owns a 128-byte text buffer, RGB, start time and signed XP.
A new notification replaces the previous one. Lifetime is 1400 ms; the
initial 200 ms scale expression is `(200-elapsed)/200`, floored at .28.
Settled text is centered at (320,90), alpha .7, style 3. Nonzero signed XP
appears at (320,100), scale .2, after settling; positive XP has a plus sign.
Types 1/2 are white; other supported `an` types are red. HP bonuses have no
XP line. Expiry and HUD/lifecycle reset clear state.

Defensive differences: exact argument counts and bounded signed-integer
parsing reject malformed messages without replacing the active notification.
Time calculations avoid signed overflow and clamp rollback elapsed time to
zero. The original negative alpha during the initial pulse is explicitly
clamped to zero here, instead of passing out-of-range color to the renderer.

The separate single-slot announcer for `an 0` (FIGHT) and `an -1`
(PREPARE TO FIGHT) is now covered in client-announcer.md. Other unsupported
types do not change the notification. Font and aspect-aware HUD placement
still need original-client visual comparison; limboFont1 and the existing
typed virtual-coordinate renderer are used. No gameplay parity claim.

Verification: full-cgame tests dispatch all six signed `an` categories and
`hpb`, check RGB/scale/alpha before and at the settling boundary and expiry,
reject malformed integers, verify zero/positive/negative XP draw counts,
replacement and reset. Native 90/90 tests pass; WASM build and Node
load/entrypoint probes pass. Browser/dedicated-server replay remains open.
