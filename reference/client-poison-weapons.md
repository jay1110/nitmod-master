# Original-server poison weapon client port

The three original poison identities now have typed inventories, preserving all
previous native IDs and the 64-slot engine player-state arrays:

| Weapon | Original ID | Native ID | Bank | Original item index | Weapon file |
| --- | ---: | ---: | ---: | ---: | --- |
| Poison Syringe | 47 | 51 | 1 | 30 | poison.weap |
| Poison Bomb | 50 | 52 | 5 | 53 | poisongas.weap |
| Poison Landmine | 51 | 53 | 7 | 49 | landmine_pgas.weap |

Both hash-pinned ELF32 item/ammo tables agree on independent ammo and clip slots.
The ordinary and poison landmine share the original `weapon_landmine` classname;
the latter gets local `weapon_poison_landmine` to avoid first-match aliasing.
Snapshot item index 49 resolves explicitly to that local item, while 48 remains
the ordinary landmine. No PK3 or pak edits are needed.

The existing wire adapter now maps every original ID 0–51. Ownership, ammo,
clip, heat, active/next weapon, entity weapons, cursor hints and outgoing
selection use the same translation. The original bank table (cgame 0x12e7a0)
is checked without excluding poison weapons. Poison animation condition names
now resolve to their real typed identities rather than animation-only bits.
Media registration uses the canonical `cg_weapons` cache, not duplicate private
handles. First/third-person models and skins come from the original weapon files.

## Presentation evidence

- Original `CG_Missile` (ELF 0x55a20, Ghidra labels around 0x65a7f and
  0x66240) calls smoke rendering for original weapons 28/50/51 and shares
  the guarded mine/marker branch between original weapons 25 and 51.
- The typed poison mine uses the same spectator/caster, spotting, owner hint,
  burial and team-modulo-four media rules as the original ordinary mine.
- `CG_SpawnSmokeSprite` uses the compact gas profile (size 7, alpha .25).
  Renderer input is normalized explicitly to green. Passing reconstructed
  byte-range constants through the stock float-to-byte conversion produced
  architecture-dependent overflow and black smoke in WASM.
- Poison landmines enter the smoke renderer only after their server trigger
  state (`teamNum >= 8`), not while flying or armed.

## Scope / remaining gameplay work

This is the client port for original dedicated servers. The server must grant
the weapon and ammunition. Poison application, damage ticks, antidote/revive
interactions, mine arming and local qagame loadouts are NOT implemented here.
Like the bomb, these weapons retain authoritative server weapon state instead
of running stock ET gun/revive prediction. This can add network latency to hand
animation feedback; full original prediction remains a separate port.

Verification covers original filenames, both ELF inventories/defaults, all bank
orders, native bank selection and empty-ammo rejection, all wire IDs, mine
visibility matrices, smoke style, and unmodified weapon/animation files.
Native/WASM builds and ABI smoke checks cannot establish browser gameplay parity;
dedicated-server throwing, injecting, planting and map changes still need a live test.
