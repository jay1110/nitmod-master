# Original command-map entity stream and disguise positions

## Reference and scope

Original cgame ELF functions: `CG_ParseMapEntity` at `0x2bac0`,
`CG_ParseMapEntityInfo` at `0x2be00`, `CG_DisguiseMapCheck` at `0x2bf30`.
See `src_nitmod_decompiled/cgame/sorted/cgame_servercmds.c` (first two functions)
and `cgame_client.c` (`CG_DisguiseMapCheck`, inlined condition in `CG_DrawMapEntity`).

`entnfo axisCount alliedCount ...` contains Axis records followed by Allied records.
All ten original record types contain X/Y, plus Z when command-map layers are enabled.
Each coordinate is a signed integer multiplied by 128. Types 0/1/2 (players) and
6 (landmines) also contain yaw, then data. Types 3/4/5/7/8/9 omit yaw, not coordinates.
The previous ET parser skipped coordinates entirely for types 3/4/5/9 and consequently
misaligned subsequent original-server records. No new server command is introduced.

The original path now decodes into typed `mapEntityData_t` records, computes command-map
and automap coordinates, and publishes one complete update. Native ET and reconstructed
servers advertising `nitmod_csLayout=et260` retain their existing compact record layout.
Objective rendering still uses existing entity/OID positions where the original does;
the transmitted coordinates must nevertheless be consumed and supply initial/fallback
positions and the layer Z value.

Original player-position refresh accepts teammates without the ET `currentValid` gate,
and disguised players at distance >=512 from snapshot player origin. The latter is
the original comparison (not <=512), using the already-normalized disguise powerup.
Native ET retains its current-valid teammate rule. This does not create map records
or reveal players absent from the server's command-map stream.

## Defensive deviations

Malformed counts, signed integer overflow, unknown types, invalid record-data indices,
coordinate multiplication overflow, missing and surplus arguments reject the whole
original message, retaining the last complete list. Original unchecked `strtol`/array
writes are not reproduced. Unused yaw/Z fields are cleared on each update. Rendering
also bounds player, entity and objective lookups; invalid disguise inputs return false.
No assets, menu files, original modules, qagame protocol or UI ABI are modified.

## Verification

`CheckCommandMapProtocol` in the full-cgame dispatcher fixture checks 60 combinations
of ten types, layer on/off, original/native/reconstructed layout. Each message includes
a following Allied player to detect stream misalignment. It checks all truncation
positions of original messages, extra fields, overflow and malformed counts, atomic
retention and empty updates. Disguise distance boundaries are tested, plus 24 actual
`CG_DrawMapEntity` position-update combinations (culled before renderer calls).

## Player presentation follow-up

The original `CG_DrawMapEntity` player branches suppress all player class, arrow,
highlight, voice and revive markers in gametype 8 (DM). Its initial player check
also suppresses the local marker when the supplied snapshot has `PMF_LIMBO`.
Both rules are now original-protocol-only; TDM and ET/reconstructed behavior remain
separate. The DM early return is moved before coordinate calculations because this
branch submits no player drawing in the original. It therefore does not update cached
player map positions during DM (an intentional internal-state difference).

Original automap player icons subtract their zoom-scaled half-width from the center,
unlike the ET path's fixed `icon_size` offset. That positioning is restored for player,
disguise and revive icons. Revive icons retain their original +3 inset and size-3,
including the existing DrawPic texture flip at very small zoom; no asset edits occur.

The shared revive pulse uses the same sine/square-root expression with bounded phase,
double intermediate arithmetic and a defined alpha=.75 for missing/nonpositive
reinforcement periods. Invalid viewer slots are checked before clientinfo lookup.
Positive ordinary clocks match within float tolerance; negative clocks clamp the phase
instead of allowing an out-of-range fraction. Command-map layer lookup now checks the
array bound before reading, including the case above the highest of all 16 layers.

`CheckCommandMapPresentation` adds 324 actual render-dispatch profiles: three protocol
layouts, gametypes 6/7/8, limbo on/off, self/other, three player entry types and three
zooms. It checks picture/arrow suppression and submitted first-picture coordinates,
width and revive alpha. Another 241 ordinary pulse samples plus extreme clocks,
nonpositive intervals and layer edges are checked. Tests use an engine syscall fixture,
not a live original-server capture or a browser visual parity claim. Other command-map
presentation differences remain subject to reconstruction.
