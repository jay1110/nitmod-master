# Full-source projectile damage integration test

Current extension: the test also executes real G_RunThink/G_ExplodeMissile
in a no-splash fixture. Earlier statements below that the scheduled explosion
was not executed describe the preceding test stage; see the timer section.

Expanded coverage: the original eight profiles below now run across six
admission states and with/without DAMAGE_NO_PROTECTION: 96 profiles and 192
real G_Damage calls. This supersedes the initial eight-profile count.

`nitmod_projectile_damage_test` links the current complete qagame source list
into a native executable with GAMEDLL enabled. It calls the real G_Damage,
the production configuration/death handlers and G_AddEvent; none of these are
replaced by test doubles. Engine syscalls are rejected immediately.

Eight controlled profiles cover grenade, smoke bomb, airstrike marker and
satchel, each with its damage option disabled/enabled. Target entities are
placed outside the client slots, game state is GS_PLAYING and there is no
loaded map or player attacker. For each profile two bullet hits are applied:

- 39 damage: enabled targets go from 40 HP to 1 and retain their normal think
  callback/deadline; disabled targets remain at baseline 5 HP.
- 1 damage: enabled targets reach zero and schedule G_ExplodeMissile at time+1
  with corpse contents and recorded attacker; disabled targets stay unchanged.
- For enabled satchels, the real death callback restores owner inventory and
  G_AddEvent writes one EV_NOAMMO with parameter 0 into the owner's playerState
  event ring. Other profiles do not alter that inventory/event ring.

The actual source's client event ring is playerState, not entityState. The
test checks this real behavior, beyond the earlier mocked event callback.
This is a native Windows full-source test, not an i386 ABI or WASM runtime
test. It does not execute the scheduled explosion, physics/collision, map
scripting content, radial chain reactions or original binary comparisons.

The target is added only when qagame exists and native host tests are enabled;
it obtains its source list directly from the qagame target. Full host build
and all 80 CTests pass. Production damage code was not modified in this step.

## Admission gates

The six states are normal play, invisible target, under-construction target,
queued intermission, warmup with damage disabled, and warmup with damage mode 2.
Each is combined with all four projectile families and option enabled/disabled.
The attacker is a non-client world entity, so this does not establish team-
damage or player-protection behavior for warmup modes.

Blocked calls must preserve every byte of the target and owner client objects,
not merely health/think. The option-disabled case retains 5 HP; a blocked
enabled projectile retains 40 HP. Both blocked hits are checked. Normal play
and permitted warmup execute the previously tested 39+1 threshold sequence.
DAMAGE_NO_PROTECTION does not bypass the early takedamage, visibility,
construction, intermission or warmup-disabled gates in this source.

The expanded native full-source test, host build, all 80 CTests and protocol
contract pass. No production gating was changed, and no original-engine or
WASM gameplay parity is claimed for this host-only integration fixture.

## Timer-to-explosion integration (initial fixture, expanded below)

All 96 profiles now call real G_RunThink three times: before the 1001 deadline,
at the deadline, and again without advancing time (288 timer calls). The 16
admitted profiles execute the real G_ExplodeMissile body exactly once, become
ET_GENERAL, set freeAfterEvent, append EV_MISSILE_MISS and clear nextthink.
The engine double accepts exactly one G_LINKENTITY with that target pointer
and validates state at the callback boundary. Other engine syscalls remain
fatal. Blocked profiles retain their future 9000 deadline and emit no event.

This minimal fixture intentionally retains weapon id 0 and splashDamage=0.
The damage/death configuration and MOD are set for each family, but explosion
radius, camera shake/temp entities and weapon-specific branches are excluded.
The callback only observes a linking request; it does not perform world linking.
No real map, collision or radial damage is simulated. The common timer and
explosion transition, not each weapon's full explosion behavior, is verified.
Host rebuild, 80/80 CTests and protocol checks pass; production code unchanged.

## Weapon-specific explosion and empty-world splash integration

The fixture now sets real WP_GRENADE_LAUNCHER, WP_GRENADE_PINEAPPLE,
WP_SMOKE_BOMB, WP_SMOKE_MARKER and WP_SATCHEL identities. Each combines the
existing admission gates with zero or 100 splash damage (test input, not a
reconstructed weapon balance value). This yields 240 profiles, 480 damage
calls, 720 timer calls and 40 admitted explosions.

The actual G_Spawn/G_TempEntity path reuses a reserved entity slot. The engine
double checks the target link before the shake link, event identity/time and
single allocation. After return, the test checks broadcast visibility, matching
origin and shake strength splashDamage*4. Both grenades, marker and satchel
produce 32 shake entities in total; smoke bombs produce none. Active markers
decrement only their team's airstrike count, exactly once, across Axis/Allies.

Nonzero splash invokes real G_RadiusDamage or both etpro_RadiusDamage passes
for satchels. The double validates 20 point traces (origin, zero bounds,
MASK_SHOT, ENTITYNUM_NONE) and 24 expanded-radius queries with capacity
MAX_GENTITIES, returning an explicitly empty candidate list. Satchel's second
pass must temporarily clear linked flags on the fixture player and all body
queue entries; flags and ignore bookkeeping must be restored afterward.
Repeated timer calls must not repeat any trace, query, event or counter change.

This expands the preceding weapon-id-0/zero-splash fixture, not the production
port. It verifies current typed ET source integration, not original Nitmod
runtime parity. No actual victim damage, obstruction, world linking, camera
rendering, entity-pool growth, spawn path or browser execution is simulated.

## Non-client splash victims and blocked visibility

Two additional splash fixtures extend the matrix to 480 profiles, 960 direct
damage calls and 1440 timer calls. They return four candidates: the explicitly
ignored exploding source, a damageable non-client at distance 32, a damageable
non-client exactly at radius 128, and a non-damageable non-client at distance 32.
All victims start with 200 health; synthetic splash damage remains 100.

With clear visibility, the real radius and G_Damage implementations reduce the
first victim to 125 health and invoke its observation-only pain callback once
with 75 damage, the world attacker and explosion origin. The radius-boundary
and non-damageable victims remain at 200. Satchel's client-only first pass must
leave the non-client untouched; its second pass causes the single hit.

The blocked-visibility fixture returns a world collision for all nine
CanDamage rays and the fallback MASK_SOLID trace. Exact endpoints, masks and
call order are checked. Distance 32 lies outside the near-wall fallback range
(128*0.2), so all victims retain 200 health and no pain callback is invoked.
In total the matrix executes 80 explosions, 64 shake entities, 60 initial
point traces, 72 radius queries, and 220 victim visibility/fallback traces.
Only 20 explosions produce the expected non-client victim hit.

This tests actual typed source damage calculations against deterministic engine
responses, not an original-binary golden result. Player damage, friendly fire,
near-wall reduced damage, actual collision geometry and gameplay replay remain
unverified. Production sources and cgame/qagame/ui wire contracts are unchanged.

## Delayed secondary-projectile destruction

Two further fixtures replace the near victim with a typed WP_SMOKE_BOMB,
configured through the production G_NITMOD_ConfigureSmokeDamage mask-8 path.
It begins at 40 HP with a normal think deadline of 9000 and no splash damage.
The clear and blocked visibility variants run across all five primary weapon
identities, option states, admission gates and protection flags. The complete
matrix now has 720 profiles, 1440 direct damage calls and 2880 timer calls
(2160 primary, 720 secondary).

In 20 clear admitted cases, the real radius/G_Damage/WeaponDie chain applies
75 damage, leaves -35 HP, records the world attacker and schedules the smoke
secondary at 1002, after the primary explosion at 1001. Corpse contents and
the cleared free callback are checked. Running the secondary timer at 1001
must not explode it; at 1002 it becomes ET_GENERAL, emits EV_MISSILE_MISS,
sets freeAfterEvent and issues exactly one link request. A repeated timer call
must not repeat the event/link. Primary entity and owner client are compared
byte-for-byte before and after the secondary timer sequence.

Blocked sight and non-admitted primary damage leave the secondary at 40 HP,
ET_MISSILE and its original deadline, with no event or link request. The
matrix executes 120 primary and 20 secondary explosions. This establishes
the deferred integration of the already ported death handler, not a new
production feature or original binary parity. Only a smoke secondary without
splash is covered: cyclic/multi-hop chains, other secondary weapon families,
real collision, player targets and browser execution remain unverified.
