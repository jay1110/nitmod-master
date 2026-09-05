# Open Nitmod port bugs

This file tracks user-observed runtime differences. Items stay here until a
verified source change and its validation are recorded. Package files are
read-only inputs and must not be edited.

## Open

- Thrown knives now use a typed dropped `ET_ITEM`, are immediately active like
  the original entity and expose the standard item-use callback. Their full
  bounce, low-gravity trajectory, owner client/team, broadcast visibility,
  configured damage, body/corpse collision mask, 1.0 physics bounce, backdated
  trajectory and 20-second lifetime match original `ThrowKnife`. The dedicated original
  pickup branch restores exactly one knife up to the eight-knife cap instead
  of feeding a bogus max-ammo count into firearm pickup. Live verification remains.
- Chat popup dispatch now preserves the engine ET UI ABI slot 15. The earlier
  reconstructed slot 17 displaced the engine command and prevented global,
  team and fireteam chat from opening. Nitmod-private class popup IDs are now
  appended after all standard ET menu commands; browser verification remains.
- The removed `n_proneDelay`, `n_crouchStandDelay` and `n_standCrouchDelay`
  movement consumers remain intentionally deferred. Re-port them with a
  prediction-history sidecar; do not extend ABI-sensitive `pmoveExt_t` or
  serialized player state. The original qagame writes deadline state at its
  recovered offsets `+0x90/+0x94`, which are not valid offsets in this tree.
- Manually configured top-centre `g_msg1`...`g_msg9` banners (`g_msgpos 2`)
  still require live-browser verification after the centred 4:3 viewport fix.
- Bound `+attack2` now drives an edge-gated knife throw event and distinct
  throw animation. Shared pmove also keeps ET's `buttons` and `wbuttons`
  namespaces separate, so alternate attack can no longer alias primary fire;
  live original-server and localhost verification remains.
- Poison mines no longer run their generic/team-coloured missile trail while
  thrown or armed; only the triggered normalized-green poison cloud remains.
  Client prediction now also selects pliers after placement, matching qagame
  and preventing held attack from selecting/throwing another mine. Live
  verification of colour and transition remains.
- Live verification remains for the removal of ET's large bottom-centre
  `SPECTATOR` label from the Nitmod HUD. The follow/limbo instructions remain.
- Complete live-browser checks for weapon models, poison weapon lifecycle,
  scoreboard/intermission/limbo widescreen layout, HUD parity and commands.
- Verify a downloaded custom PK3 overriding `weapons/*.weap` against a pure
  dedicated server, including media and prediction parameters.

## Recently verified

- The actual localhost spawn loadout now calls the recovered adrenaline grant.
  `g_adrenClasses`, `g_adrenaline`, First Aid reward/bonus bits and war-mode
  suppression are no longer registration-only behavior. ClientThink also
  revokes stale ownership after a class/eligibility change without disturbing
  syringe ammunition or an already active adrenaline effect.
- `team_maxTripmines` now rejects excess placement, assigns typed team state,
  publishes remaining team slots through the original game-manager fields and
  feeds those values into the cgame ammo HUD. `n_tripmineTimeout` removes owned
  mines on disconnect and actual team changes.

- Custom server weapon definitions now commit parsed ammo/clip, reload/fire cadence,
  heat and cooling values into qagame's authoritative `ammoTableMP`; malformed
  definitions remain transactional and leave defaults intact. The directory is
  selected through `g_weaponScriptsDir` and resolved through the engine VFS, so
  loose files and PK3-contained files use the same path.

- qagame now honors `g_weaponScriptsDir` for loose files and PK3 entries via
  the engine VFS, with canonical `weapons/` fallback on open failure.
- Animation condition words, animation commands and character model-info
  records are now completely initialized on 32/64-bit/WASM targets.
- Bot team-leader termination and connected/bot/limbo state predicates no
  longer write out of bounds or collapse multi-valued flags to booleans.
- Normal HUD chat and buffered voice-chat lines now draw the original sender
  team icon (Axis, Allies or spectator) from their preserved per-line team ID.
  Browser presentation still needs live comparison.
- Localhost WASM loads the existing `omnibot_et.wasm32.so` through interface
  17. External bot clients bypass ET 2.60's obsolete AAS/botlib traps, including
  the former fatal trap 304 path.
- Shared weapon `movementSpeedScale` is parsed for normal/alternate definitions
  and applied consistently in client and server movement.
- Initial zero skill-unlock masks are treated as join synchronization rather
  than announcing every already-owned skill reward.
- The bottom chat background and text use the left 4:3-safe HUD anchor on wide
  displays.
- cgame now commits the shared custom-script ammo/timing fields (`maxammo`,
  `maxclip`, starting values, reload/fire delay, shot interval, heat/coolrate)
  from the selected `both` block after a complete successful parse.
- The in-game Server Info action falls back to connected `CS_SERVERINFO` for
  localhost/loopback, where browser WASM has no separate UDP status response.
# Omni-bot on a browser-hosted localhost

The browser bootstrap correctly preloads `omnibot_et.wasm32.so`, installs it
beside `global_scripts/` and `et/`, and sets `omnibot_path` to that directory.
The reconstructed Nitmod qagame did not load any Omni-bot module: its
`omnibot_enable`, `omnibot_path` and `omnibot_playing` entries were registration
only, while gameplay still used the old ET `BOTLIB_*` path.  A status contract
now reports the exact platform module and resolved path through
`nitmod_omnibot_status`, and startup no longer leaves `omnibot_playing` in a
misleading state.  Actual bot operation remains open until the version-17,
55-method typed ETInterface adapter is linked; it must not be replaced by an
i386 vtable cast or a fake successful load.

The vendored ET:Legacy Omni-bot WASM target now builds with current libc++ by
enabling its explicit C++17 compatibility definitions for the old Boost
headers. The resulting module has WebAssembly magic, exports
`ExportBotFunctionsFromDLL`, and is staged beside the Nitmod WASM modules with
`omni-bot-data.zip`. Nitmod qagame now performs a non-initializing export-table
probe at startup and through `omnibot load`/`omnibot reload`; it validates the
11-pointer table and required initialize/update/shutdown callbacks, then closes
the probe handle. This establishes module/preload correctness independently of
the unfinished engine adapter.
