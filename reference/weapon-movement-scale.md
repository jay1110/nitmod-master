# Weapon movement scale reconstruction

## Recovered contract

The original cgame and qagame weapon records have stride `0x6b0`. The
`movementSpeedScale` parser stores its float at record offset `0x600`.
`PM_CmdScale` reads the selected weapon record at that offset and multiplies
the current command scale when the value is nonzero. This happens after the
run/sprint/noclip factors and before the native heavy-weapon and flamethrower
penalties.

Evidence:

- `src_nitmod_decompiled/cgame/sorted/cgame_bg.c`: parser destination `+0x600`
- `src_nitmod_decompiled/qagame/sorted/nitmod_bg.c`: parser destination `+0x600`
- `src_nitmod_decompiled/cgame/sorted/cgame_pmove.c`: nonzero test and multiply

## Typed implementation

- qagame keeps the value in its map-owned `nitmodWeaponOptions_t` cache.
- cgame captures the value while its existing media parser traverses the
  selected `both` or `both_altweap` block; it does not reopen the file.
- shared `PM_CmdScale` obtains the value through module-specific typed
  accessors and applies it at the recovered ordering point.
- zero and unavailable definitions retain ET 2.60 movement behavior.

No package asset is modified by this implementation.
