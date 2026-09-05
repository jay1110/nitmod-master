# Nitmod fall-damage base values

Update: the ordinary base path is now part of the active Goomba adapter.
See `goomba-runtime.md` for current integration, transport and remaining gaps;
the unimplemented-Goomba paragraph below records the earlier audit state.

Original qagame G_FallDamage in `nitmod_game.c` (around line 168) maps
events 0x0d..0x11 to damage 500, 10, 15, 25, 50 and movement lock
durations 0, 250, 250, 500, 1000 milliseconds. With goomba disabled or
no eligible player underneath, it applies the ordinary falling damage.
A zero duration does not clear an already present pm_time.

The active ClientEvents base path now uses these values, replacing native
ET's 9999 fatal damage and 1000/1000/250 durations for 10/15/25 damage.
The ET_PLAYER guard, unrelated pm_flags, 200ms pain debounce and MOD_FALLING
attribution remain unchanged. No new event ID or protocol field is added.

The full qagame test calls ClientEvents for all five events with player and
nonplayer entities. It verifies movement locks, preserved flags and pain
debounce. Targets are deliberately not damageable to isolate this dispatch
test; the 500 damage constant is source-reference checked, not a new live
health/death replay test. Existing suite checks still apply separately.

Still open: goomba target resolution, team/option rules, sounds, statistics,
and a consistent reconstructed-server death cause. The original wire death
cause 58 already has cgame handling but cannot simply be substituted for the
native server enum. g_goomba and g_goombaFlags are not activated by this patch.
This is a limited base-path correction, not a completed goomba port.
UI/cgame and all pak assets are unchanged.
