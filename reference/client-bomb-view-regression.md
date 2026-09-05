# Bomb first-person rendering regression

Read-only asset inspection confirms `weapons/bomb.weap` names the existing
`models/multiplayer/bomb/v_bomb.md3` and the base ET smoke-grenade hand model
and animation file. The MD3 has one frame and two surfaces; the world model has
one frame and one surface. Base ET pak0's smoke config keeps the primary model
static while animating its parent. No replacement model or pak edit is needed.

Three client rendering inconsistencies were corrected:

- First-person `CG_AddPlayerWeapon` now selects media from the supplied player
  state, like `CG_AddViewWeapon`, rather than potentially using a different
  weapon from the interpolated entity. Third-person rendering still uses the
  entity weapon. Invalid/unarmed IDs return before indexing weapon media.
- `CG_RunWeapLerpFrame` rebinds animation state when its pointer belongs to a
  previous weapon, even when the requested animation number is unchanged.
  This prevents old weapon frames from being applied to a newly selected hand.
- Animation-disabled modes use static part frame zero instead of hiding the
  primary model when the animation pointer was never initialized.

Tests exercise the real `CG_AddPlayerWeapon` draw submission for bomb, poison
bomb, poison mine and tripmine with a stale entity weapon, preserving model
handles, render flags and static frames. Lerp tests switch weapon animation
ownership for every animation slot. Part-frame tests cover both disabled modes
alongside the existing animated/hidden-part matrix.

These are verified render-path defects, not proof that the reported live-browser
symptom had only these causes. Model registration can also fail due to missing
base assets or deployment differences. `nitmod_weapondebug` reports active and
entity weapon IDs, model handles, animation frames and relevant cvars without
changing state. A zero firstPerson/hands handle points to asset registration;
a nonzero handle is not itself proof of visible pixels.

No weapon-grant, damage, fuse, explosion or wire-format changes. No UI/qagame
behavior is claimed added by this client-focused fix. Live original-server
selection, throw, weapon return and switching still require browser confirmation.
