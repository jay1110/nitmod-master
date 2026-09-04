# Graphic obituary classification, single-name rows and default media

The active modes 3/4 now use a typed render plan for every original cause,
not only two-player kills with explicitly sized weapon icons.

Original evidence: sorted `cgame_events.c` case 0x38, particularly
`LAB_0007562b`, `LAB_00075ec9` and `LAB_0007466b`. World deaths and explicit
self-death branches retain target-first order with an empty second name;
null obituary pairs retain target/attacker order regardless of mode. Defined
two-player pairs use attacker/target in mode 3, reversed in mode 4, except
revivals which stay attacker-first. Ordinary paired deaths use white,
teamkills red, revivals green, and single/null-pair cases yellow. Color
constants OB_GREEN/RED/YELLOW were read from ELF VA 0x134698/0x1346a4/0x1346b0.

Missing weapon media now uses the caller's death icon at scale 1, preserving
graphic layout. Present weapon icons use `CG_NitmodWeaponIconScale`, including
the original default scale when a weapon file omits weaponIconScale. The
previous explicit-scale-only check incorrectly discarded otherwise valid
icons. Invalid explicit scales still fall back safely.

The shared popup pool now owns an explicit graphic-row flag. An empty second
name is valid and no longer misclassifies a world/self row as ordinary text.
Pool allocation, reuse, fade and ordinary-message reset remain shared. Native
ET dispatch and original assets/protocol messages are unchanged.

Tests: 2,208 cause/mode/relation/gametype/media combinations; explicit world,
self, null-pair, revival and team/DM order/color assertions; standard default
icon widths; malformed inputs; actual popup drawing for world/self/private
fallbacks in both modes; existing queue saturation/reuse tests.

Limits: private weapon-specific media not yet registered by the typed weapon
system still uses the death icon. This does not implement their gameplay.
No screenshot/browser parity claim; original code uses an initial space in
the unused name buffer, whereas this implementation stores an empty string.
