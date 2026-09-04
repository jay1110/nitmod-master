# Weapon HUD presentation

Original sources: `cgame/sorted/cgame_ui.c`, `CG_DrawPlayerWeaponIcon`
(branch label 0x98962), `CG_DrawWeapStability`, `CG_DrawWeapHeat`, and
`CG_DrawLivesLeft` (call-site return 0x55e99).

Ported original-protocol behavior:

- Weapon icons retain the existing typed icon-size mapping and parsed
  weaponIconScale override. Mounted weapons select MG42 or the Browning
  tank icon; both parent indices are checked before dereference.
- Pulse size is grenadeTimeLeft / 50 for the knife and its remainder modulo
  1000 divided by 100 for other weapons. Half-width icons retain their
  left/center/right alignment. The icon tint uses RGB with opaque alpha.
- Unlike native ET, this original HUD path emits no grenade countdown audio.
  This does not disable sound events or other weapon audio producers.
- Icons and heat use the right HUD anchor. The original heat bar is horizontal,
  grows from its left edge, uses red alpha .2, and has no ET background,
  inset border, color interpolation, or direction flag.
- Spread keeps its scope-mode, ready-state and third-person gates and the
  centered vertical green/red bar, now using the original left HUD anchor.
- Rest-life digits and helmet retain their existing ET geometry, with the
  original left anchor. This is placement integration, not new respawn logic.

Original-only branches leave native ET pulse audio and heat layout unchanged.
Null inputs, invalid weapon IDs and invalid tank links are rejected or use
the ordinary mounted icon; negative original pulse times are treated as zero.
These are intentional malformed-input differences from the reference.

The cgame syscall fixture executes 90 protocol/weapon/time/alignment icon
cases, verifies both silence on original protocol and native countdown audio,
tests mounted/Browning/invalid-parent selection, and exercises 258 heat values
with exact 1280x720 rectangle/color assertions. Additional checks cover spread,
third-person suppression and rest-life digit placement. No browser or original
dedicated-server visual replay has been performed for this batch.

No pak, menu, PK3, original binary, protocol layout, or qagame source changes.
