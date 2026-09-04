# Dynamite world countdown and crosshair display

Reference module: original cgame.mp.i386.so, SHA-256
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

## Recovered behavior

- CG_Missile (ELF 0x55a20; sorted/cgame_effects.c) supplies floating text
  for armed teamNum 1..3, local spectator team and explicit shoutcaster role.
  The format at ELF/file 0x10cbd7 (Ghidra 0x11cbd7) is `^1%i`.
  Countdown is 30 minus truncated elapsed seconds since effect1Time.
- CG_PlayerFloatText (ELF 0x92580; sorted/cgame_players.c) adds height 20
  and the existing duck correction, projects and distance-scales text into
  the shared 16-entry world-label queue. The port copies text, uses an entity
  key separate from clients/locations, and preserves fading across second
  changes. Entity reuse with a new effect1Time resets its fade.
- CG_ScanForCrosshairDynamite (ELF 0x46480; sorted/cgame_client.c)
  traces 512 units with CONTENTS_SOLID. The trace endpoint must be strictly
  within 16 units on every axis of pos.trBase. It records entity, owner and
  observation time. The trace is not a ray against the dynamite collision model.
- CG_DrawCrosshairNames (sorted/cgame_ui.c) draws the friendly owner's name
  at baseline 182 with limboFont2, scale .18, style 7. The armed bar at
  (290,193,60,7) uses (effect1Time + time2 - now) / time2, clamped 0..1.
  This is deliberately distinct from the shoutcaster's fixed 30-second timer.
  Friendly unarmed charges retain the owner label without the bar.

## Integration and intentional limits

Implemented in cg_nitmod_names.c and cg_nitmod_hints.c; CG_Missile produces
the records and CG_DrawCrosshairNames consumes the crosshair record after its
normal scan, so a directly targeted player takes precedence. Native protocol
paths do not produce these records. The crosshair's client/entity split now
correctly treats index 64 as an entity; invalid indices are rejected.

The original additional enemy-dynamite scan eligibility depends on a private
engineer skill mask that is not mapped yet. It is NOT enabled by guessing from
the native skill levels. Only friendly crosshair dynamite is implemented here.
Spectators require explicit shoutcaster status for floating countdowns;
spectatorNames alone does not grant it.

Safety deviations: bounded entity/owner indices, finite hit comparisons,
positive denominator requirement, overflow-safe double timer arithmetic,
owned state/text, valid owner information, no hint in DM/third-person mode.
Start-at-zero and per-entity fade state are defined rather than relying on
uninitialized original global slots. This is not full original HUD parity.

## Checks

CheckDynamiteDisplay in test_original_charge_dispatch.c covers 108 combinations
of protocol/team/role/arming values, strict hit-box boundaries on all axes,
half-duration bar geometry, player precedence, expiration, zero duration,
invalid owner/entity indices, countdown changes without fade reset, and the
shared 16-label limit. It calls the actual renderers with mocked engine traps.
Live dedicated-server/browser comparison is still required. No assets, PK3s,
qagame messages or UI protocol fields were changed.
