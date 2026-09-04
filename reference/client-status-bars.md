# Original player status bars

Reference: CG_DrawPlayerStatus in
src_nitmod_decompiled/cgame/sorted/cgame_ui.c, especially the block beginning
at LAB_00051724. This batch ports the health/stamina/breath/charge section;
the existing weapon/ammo renderer remains and now gets the right HUD anchor.

Snapshot.ps starts at 0x2c; stats starts at ps+0xd0. Original offsets map to:

| Snapshot offset | Typed field | Meaning |
| --- | --- | --- |
| 0xfc | stats[0] | health |
| 0x10c | stats[4] | ordinary maximum health |
| 0x114 | stats[6] | stamina, full at 20000 |
| 0x120 | stats[9] | medic maximum health |
| 0x1a8 | powerups[11] | adrenaline expiry |
| 0x1f0 | original ammo[13] | fieldops support indicator bits |

The medic denominator applies outside gametype 8 when simple-config `war`
is zero (original cgs+33787756, third nitmod_GetSimpleCS argument). It replaces
the stock 1.12 multiplier. Ordinary original stamina uses the authoritative
snapshot counter instead of local pmext.sprintTime, including spectator follow.
Adrenaline interpolates green to white using the original expiry sine curve;
the native powerup enum is deliberately not used for this wire field.

Underwater condition ANIM_COND_UNDERWATER switches to the waterHint icon and
(waterundertime - now) / 12000. The existing event-driven deadline is reused;
the separate original skill-mask extension to 15 seconds is still unported.
This change does not alter movement, oxygen damage or powerup normalization.

Class recharge reads the normalized PERS_TEAM and matching class/team charge
time. Original support bits 1/2/3 tint the fieldops power icon yellow/orange/red.
Weapon normalization moves original ammo[13] to native ammo[WP_ARTY], so this
consumer must use the latter. Other classes retain a white icon.

Health frame is (18,388,12,72), stamina (4,388,12,72), recharge
(624,388,12,72). Icons and bars use the original positions and 0x55 flags.
Left/right aspect anchors are scoped and restored. Native ET retains its
existing rendering and calculations.

Defensive differences: invalid team/class yields no bars, nonpositive
denominators produce empty bars, fractions saturate to [0,1], and time
differences use double arithmetic to avoid signed overflow. No claim is
made that zero/malformed denominators match original undefined behavior.

Full-cgame tests cover all five classes, both teams, six stamina boundaries,
charge midpoint, support colors, adrenaline expiry, integer-limit times,
invalid-state atomicity and denominator guards. Actual renderer calls check
all three frame rectangles and stamina/water icon choice at 640x480 and
1920x1080, plus native-protocol exclusion. Browser visual parity remains
unverified. No pak, menu, original module or server protocol is changed.
