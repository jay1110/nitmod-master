# Reload decision dispatch

NITMOD_ProcessReloadRequest recomputes the outer decision from current state
and dispatches it once. BEGIN uses the already reconstructed begin adapter
with the target ammo record; UNSCOPE calls an explicit weapon-change boundary
with original scoped weapon, native base weapon, and reload=true. NONE does
not invoke either path. The dispatcher installs no global registry or Pmove
hook and does not assume the requested switch succeeded.

The original PM_CheckForReload sends PM_BeginWeaponChange(weapon,
weapAlts[weapon], true) on the unscoping path (qagame 0x2a8c1..0x2a8da,
cgame 0x19da4..0x19dbd). Native PM_BeginWeaponChange already accepts this
reload intent and uses WEAPON_DROPPING_TORELOAD, then the finish path uses
WEAPON_RAISING_TORELOAD before beginning reload. Its own weapon ownership,
respawn, spinup, grenade and already-dropping gates must remain in that
boundary. No second copy of those gates is guessed here.

The switch callback is synchronous and has no success result, matching the
existing void engine adapter. SWITCH_REQUESTED explicitly means dispatch,
not a completed state change. A missing callback on a required switch returns
invalid without mutation. Direct reload does not require a switch callback.
The begin result is translated without dropping empty-reserve/reset or
invalid distinctions. The callback's context is caller-owned and not retained.

Integration tests exercise all three scoped/base pairs under ordinary,
scoped-ability and war=2 policy, including positive weaponTime. They verify
exact callback arguments/context/reload intent; direct paths use the actual
composed begin and native event helper with a body-animation boundary double.
Repeated requests while RELOADING do nothing. Missing callback and malformed
input tests ensure no accidental animation/switch effects.

This is a tested dispatch boundary, not active engine weapon-change wiring.
The existing native weapon-change implementation has not been declared fully
Nitmod-equivalent. A live PM_BeginWeaponChange binding and end-to-end
drop/raise/reload prediction tests remain outstanding.
