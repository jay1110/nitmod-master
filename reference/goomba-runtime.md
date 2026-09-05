# Active reconstructed Goomba gameplay

## Original evidence

`nitmod_game.c` G_FallDamage (around lines 168..300) and the inlined
ClientEvents equivalent in `nitmod_client.c` establish the ground-client
lookup, four-unit downward trace with mask 0x06000001, damage/stun values,
option precedence and MOD 0x3a. The existing original modNames ELF audit
independently identifies original wire cause 58 as MOD_GOOMBA.

Original cvar table: g_goomba, address 0x2a902c, default 10, flags 0;
g_goombaFlags, address 0x2a925c, default 25, flags 0.

## Active behavior

The real ClientEvents path now calls typed G_NITMOD_FallDamage for short
falls and all five damaging fall events. It first checks the grounded
entity, then falls back to the original downward trace. Invalid indices,
non-client/non-damageable targets and self-targeting cannot be stomped.
Disabling g_goomba retains ordinary falling damage without extra traces.

Flags are independent:

- 1: suppress teammate stomps outside DM (game type 8).
- 2: suppress short-fall stomps.
- 4: suppress short-fall teammate stomps, including DM.
- 8: no residual falling damage after a damaging stomp.
- 16: target-health damage with DAMAGE_NO_PROTECTION instead of multiplier.

Without bit 16, target damage is fall damage times g_goomba; short falls
use 5 as the base. Without bit 8, longer falls retain 20% falling damage
on the attacker. The stun is applied to the target, not the attacker.
Native G_Damage remains responsible for protection/team damage rules.
Multiplication is checked before integer conversion; overflow is rejected
instead of invoking undefined behavior. This is intentional hardening.

## Server/client contract

MOD_GOOMBA is appended to the internal native enum without renumbering any
existing cause. Server logs use its own name. The obituary transport uses
the existing native ET MOD_CRUSH plus effect3Time=NITMOD_OBITUARY_GOOMBA.
The reconstructed cgame recognizes that pair and displays the stomp text.
Native ET clients that ignore the marker still receive a valid crush event;
that fallback is intentionally less specific. This does not claim original
Nitmod client compatibility with the reconstructed native wire layout.

Original-server cgame decoding remains separate: original cause 58 is
still read through the existing original obituary path, and the native
cause adapter now maps it to the named MOD_GOOMBA rather than UNKNOWN.
No new client/server console command or asset is required.

## Verification and remaining gaps

The real qagame damage function is exercised with six events, 32 option
masks, both same/opposite teams, DM/non-DM and enabled/disabled settings:
1,536 profiles. Custom pain/death callbacks capture applied damage without
running unrelated corpse/map/scoreboard operations. Target stuns and death
cause are checked. The fixture supplies a direct grounded target; fallback
trace, attacker residual health loss and full player_die are not replayed.

The full cgame event dispatcher test compares a normal crush event with
the marked stomp event and checks the actual emitted popup text. The
existing 69-row ELF death-cause audit continues to verify original mapping.

The original short-stomp sound is now emitted through the typed
`NITMOD_PlaySoundEvent(target, 5)` path after short-fall damage. Still missing:
separate Goomba kill counters/awards, full protection parity with original
G_Damage, and native/browser gameplay end-to-end validation. UI has no new
menu option in this patch; both existing cvars are configurable in console.
No pak, original binary, menu or model file is changed.

Follow-up: Goomba kills now award the original five Battle Sense XP via
the live kill dispatcher; see `special-kill-xp-runtime.md`. Separate
Goomba counters and global awards are still not implemented.
