# Spree receive paths and HUD

The typed receiver now handles original entity event 101, original command
`z2 actor detail` (multi-kill), and negotiated `nsp actor detail type` through
one validated handler. Native ET event numbers and qagame's capability-gated
transport are unchanged. UI's existing cg_HUDFlags bit 8 selects the left
placement without modifying any menu or pak asset.

## Original evidence

- cgame_events.c case 0x65 reads actor/detail/type from entity words
  0x43/0x44/0x45. The typed fields are effect1Time/effect2Time/effect3Time,
  offsets 0x10c/0x110/0x114. The original qagame nitmod_Announce producer
  independently writes these same offsets.
- cgame_servercmds.c `z2` reads two integers and selects type 3.
- cgame_nitrox.c nitmod_AddSpreePrint and nitmod_SpreePrint provide lifetime
  4250 ms, console formats, revive teamchat and animated text placement.
- Original ELF tables: KSpreeMsg 0x13b2f0 (6), LSpreeMsg 0x13b2e4 (3),
  MKName 0x13b2d0 (5), MRName 0x13b2c0 (4). All 18 strings are checked
  directly against the hash-pinned original ELF by the protocol-contract test.

HUD label scale is `(remaining/4250 + .5 + sin(time/150)*.5)*.1 + .1`.
Default label/name coordinates are (520,15)/(520,25); bit 8 selects
(10,200)/(10,210). Active pop notifications now force that same left position
regardless of bit 8, until the notification transition state returns to zero.
Name scale is .2 with a 16-character draw limit.
Type 4 uses console/teamchat rather than starting a HUD notice.

## Defensive behavior and remaining gaps

Invalid actor, invalid client info, empty name and out-of-range table indices
are rejected before state changes. Invalid messages cannot replace a current
notice. Shared server/client validation now limits multi-kill detail to 0..4,
matching the recovered table; its return value remains a tier, not kill count.
Time arithmetic avoids signed overflow and clamps rollback remaining time.
Unlike the original global-state order, a revive-chat event does not replace
the actor of an unrelated HUD notice already on screen.

Spree sounds are now registered during game-media initialization:
`sound/nit/mk1.wav` through `mk5.wav`, `mr1.wav` through `mr4.wav`, and
`ks1.wav` through `ks6.wav`. Type 1 uses ks, type 3 uses mk, type 5 uses mr;
losing-spree and ordinary revive-spree messages do not play a sound.
All registrations use qfalse for compression and are replaced on subsequent
media initialization; notification/HUD resets do not invalidate sound handles.

Evidence: cgame_client.c's sound registration loops write cgs offsets
0x204d8 (mk), 0x20518 (mr) and 0x204ec (ks). The original ELF's
CG_RegisterSounds is at 0x808a0 and nitmod_AddSpreePrint at 0xf6a60.
Disassembly confirms the common trap_S_StartSound call at 0xf6b3b uses
NULL origin, channel 0/CHAN_AUTO and the snapshot player client number
(snapshot + 0xcc), not the announced actor. The typed receiver follows this
path only with a positive registered handle and a valid snapshot client;
missing handles/snapshots are defensively silent.

The private placement override is now mapped: g_unk_010ef260 is the same
fade/hold transition state used by the notification renderer. The typed
renderer checks notificationStage, matching the original bit-8 OR state test.
Zero notification fade leaves this state active, matching the original early
return; an empty replacement or HUD reset clears it. Notification rendering
runs before spree rendering, so expiry restores the normal position in-frame.
Aspect-aware CG_HudPlacement behavior is not ported; this renderer uses typed
virtual coordinates and limboFont1.
Font, placement and animation fidelity require screenshot comparison.
This is a partial feature port, not full original-client parity.

## Verification

The full-cgame fixture exercises all table bounds, all 32 HUD flag combinations,
expiry/reset, invalid clients, revive counts, original event payload offsets,
actual z2 dispatch, malformed commands, and the negotiated tuple receiver.
Sound fixtures additionally verify all 15 exact paths, table-index-to-handle
mapping, registration replacement, silent categories, null origin, channel,
snapshot recipient, failed registrations and absent snapshots.
The shared announcement tests cover the new multi-kill upper bound.
Notification placement tests cover all 32 flag combinations, fade-in, hold,
fade-out, expiry, disabled fading, empty replacement and reset.
Native 90-test suite and WASM build/load/entrypoint probes are run. No browser
dedicated-server replay or Linux-i386 rebuild is claimed for this batch.
