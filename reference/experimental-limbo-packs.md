# Experimental limbo packs and pack lifetimes

Four original Cvars are registered with original defaults/flags (all flags
zero, track/reset false): g_dropHealth=0, g_dropAmmo=0,
n_medPackSinkDelay=30000, n_ammoPackSinkDelay=30000.

Original G_DropLimboHealth/G_DropLimboAmmo (sorted nitmod_game.c and
nitmod_weapons.c) require medic/fieldops, active gameplay, a positive count,
and war outside 1..4. Count is capped at 10. Two rand() samples per pack
produce horizontal velocity in [-100,100], vertical velocity 25. The original
limbo makeCorpse branch calls these before CopyToBodyQue. The port installs
the same hook, filters nonplaying teams, launches typed items through ET's
LaunchItem, assigns owner/team, and schedules MagicSink.

Original Weapon_Medic_Ext/Weapon_MagicAmmo_Ext use a configured sink delay
only in inclusive [5000,60000], otherwise 30000 (not clamping to endpoints).
This policy now applies both to the new limbo drops and existing regular
health/ammo throws. Nothing changes when the four Cvars have defaults.

This is explicitly an experimental ET-backed port, NOT full original parity:

- Charge and ammo-pack size use existing ET skill thresholds. Original
  BG_GetFromTable/jP_DoChargeCost, ability bits and Huge Ammo Pack remain open.
- Collision uses the ET trace/LaunchItem adapter. Start-solid fallback uses
  an explicit local view direction rather than original global forward;
  the original aliased start/end pointer behavior is not reproduced.
- Original LaunchItem's fifth flag argument and Omni-bot FireWeapon callback
  are not represented by the native ET LaunchItem signature.
- The normal throws gain sink-delay configuration only; their other original
  Nitmod differences have not been reconstructed by this patch.

Tests cover the class/war/gamestate/count policy, seven delay boundaries and
40 actual LaunchItem calls with open-space trace stubs, owner/team, velocity,
count/density and cleanup deadlines. Collision/start-solid, full limbo
lifecycle, pickups and actual timed cleanup still need engine testing.
Original PK3 files and reference binaries remain unchanged.
