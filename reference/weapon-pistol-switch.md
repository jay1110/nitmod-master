# Single-pistol silencer transitions

The original alternate tables establish two pairs: IDs 2/14 (native
WP_LUGER/WP_SILENCER) and 7/38 (WP_COLT/WP_SILENCED_COLT).
The existing hash-pinned alternate-table test verifies both modules.

| Direction, either pair | Drop time | Raise time | Drop body mode | Raise body mode |
| --- | --- | --- | --- | --- |
| Attach silencer | 0 ms | 1190 ms | normal drop | do alternate mode |
| Remove silencer | 1000 ms | 0 ms | undo alternate mode | do alternate mode |

Drop removal compares the alternate then selects 1000 and undo-mode event
(prone variant when appropriate): qagame 0x2a670..0x2a6d2 / cgame
0x19b50..0x19bb2. Drop attachment uses the zero-duration path at qagame
0x2a3a6..0x2a3b3 to 0x2a522 / corresponding cgame 0x19886 to 0x19902.
Raise attachment compares the alternate and loads 1190 at qagame
0x2c714..0x2c728 / cgame 0x1bbd4..0x1bbe8. Raise removal selects zero
at qagame 0x2c5c9..0x2c5da / cgame 0x1ba8c..0x1ba9d. Both raise
directions continue through alternate body-event handling, not normal raise.

Committed silenced pistols set bit 0 of remembered sidearm mode before the
same-weapon return: qagame 0x2c705..0x2c70e / cgame 0x1bbc5..0x1bbce.
Unsilenced pistols clear it at qagame 0x2c5ba..0x2c5c3 / cgame
0x1ba7d..0x1ba86. All other bits survive. Rifle-grenade bit handling and
the commented-out syringe/adrenaline behavior are not changed.

NITMOD_PistolSwitch returns a typed four-field plan only for these four
directed transitions. Active shared begin/finish callers consume the matching
phase's duration and body-animation choice; first-person animations, events,
prone selection and authorization remain in native Pmove. NITMOD_PistolModeFlags
is applied to the committed target, before the same-weapon early return.
This is an ET-equivalent extraction, not a new timing or protocol behavior.
No akimbo or cross-faction transition is inferred.

Tests cover all native pairs plus adjacent invalid identities (2704 plans),
null outputs, unchanged output on rejection, integer extremes, and 572 mode
updates including negative/high-bit flags and idempotence. Source contracts
pin both live plan consumers and mode-update ordering. Host tests do not
establish original-binary execution, animation replay or Linux/WASM parity.
