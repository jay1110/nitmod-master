# Custom weapon PK3 client path

Original Nitmod and this port request canonical virtual paths such as
`weapons/mp40.weap`. The engine filesystem selects an overriding file from a
downloaded custom PK3; the module must not use host filesystem paths.

The cgame loader now consumes both parts of that selected file:

- `client`: models, sounds, icons, links and other presentation media.
- selected `both`/`both_altweap`: ammo limits, starting ammo/clip, reload and
  fire delays, next-shot interval, heat/cooling and movement speed scale.

Shared values are parsed into a temporary copy and committed to
`ammoTableMP[weapon]` only after the complete weapon definition succeeds.
Malformed custom files therefore retain the previous prediction record.

Server-only damage and authoritative gameplay remain owned by qagame. Client
ammo/timing values are needed because `bg_pmove.c` performs local prediction;
discarding them causes a WASM client to behave unlike the native Nitmod client
even when the engine has mounted the custom PK3 correctly.
The cgame parser also consumes optional `server { ... }` blocks without
applying them. This permits combined server/client override files while
keeping qagame authoritative. The existing `loadweapons` console command
force-reloads every weapon through the current engine VFS and reports the
number of definitions visited, which is useful after a downloaded-pk3 restart.

`g_weaponScriptsDir` is intentionally qagame-only in the original binaries.
At map startup qagame now reads that Cvar and asks the engine VFS for
`<configured-directory>/<weapon>.weap`, falling back to `weapons/<weapon>.weap`
only when the preferred file cannot be opened. Consequently `weapss/mp40.weap`
works both as a loose file below the active `nitmod` game directory and as an
entry in any mounted PK3. Cgame/UI do not invent or mirror this server Cvar;
their visual definitions remain the canonical `weapons/*.weap` files.

On successful map-start parsing qagame atomically commits the recovered ammo
record to its local `ammoTableMP`. Thus `defaultStartingAmmo`,
`defaultStartingClip`, `maxammo`, `maxclip`, `reloadTime`, `fireDelayTime`,
`nextShotTime`, `maxHeat` and `coolRate` affect authoritative movement and
weapon timing. Omitted keys retain native defaults; malformed files commit
nothing. Recoil/options are cached alongside the same successful record.
