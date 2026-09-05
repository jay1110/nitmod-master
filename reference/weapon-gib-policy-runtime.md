# Active weapon gib permission

Original G_WeaponCanGib and the inlined G_Damage health clamp consult the
private GibbingWeapon field (+0x688) via BG_WeaponForMOD. Values 1/2 force
allow/deny; zero uses G_WeaponIsExplosive. The typed map-owned cache now
feeds that decision into G_Damage's existing gib-health clamp.

The explosive classification itself is unchanged: constructibles, movers,
explosive-only targets and damage protection must not inherit a cosmetic
gib permission. No cgame event or protocol change is needed; the existing
death/gib path produces the visuals.

Original control flow subsequently forces gib health for player hits above
190 damage. That later override is preserved, including the existing native
POW exception. Consequently GibbingWeapon=no is not an absolute guarantee
against gibbing on a sufficiently large hit. This is not silently redesigned.

Tests cover yes/no/invalid, explosive and nonexplosive fallbacks, invalid
weapon IDs and map reset using the real loader/cache. They do not replay
complete deaths. The original gib-aware trace filtering is not ported by
this change; native G_Trace behavior remains. UI/cgame sources and original
assets are unchanged. Browser visual verification remains outstanding.
