# Original Nitmod obituary dispatch

The original protocol now selects a dedicated typed obituary implementation
instead of running its cause numbers through the native ET text switch.
Native ET connections retain that switch unchanged.

## Recovered behavior

- All 69 `Obituaries_killedby` records, including null entries, from cgame ELF
  VA `0x134940`. Exact original capitalization and spelling are preserved.
- Weapon selection from `BG_WeaponForMOD` (ELF `0x135e0`): first matching cause
  in the 52-record `ammoTableMP` at `0x12fd00`, stride 72, cause offset 60.
  Throwing knife (cause 63) explicitly selects knife. Wire IDs are translated
  before accessing typed native weapon media; they are not native enum values.
- The self-kill switch in sorted `cgame_events.c`, labels `_L632` through
  `_L656`: poison, censor, thrown knife, self-gib, bomb, tripmine, poison gas
  and poison mine now get their original specific text.
- World kills use standalone messages or the original died fallback rather
  than adding a fictitious attacker. Null text pairs have a safe fallback.
- Original teamkill prefix preserves cause/weapon text. Deathmatch (gametype 8)
  does not classify same-team player records as teamkills. Syringe is displayed
  as a revival and does not produce a local "You killed" notification.
- Existing kill-print, killer-name, popup modes 0–4 and obituary-audio paths
  are reused. Switch-team notifications are suppressed.

## Verification and limits

`test_original_death_causes.py` compares every text pair and weapon mapping
directly with the immutable ELF. Full-cgame tests exercise all causes across
world/self/team combinations, truncated buffers, all 69 dispatches, special
self messages, revival and thrown-knife graphic popup rendering in modes 3/4.

This is a complete static text-table port, not complete obituary parity.
Original `BG_Weapons` custom obituary overrides are still not connected.
The original dedicated weapon-media slots for poison syringe, bomb and gas
weapons remain unavailable in the typed renderer and use text fallback;
their gameplay implementation is not claimed. World/self graphic rows and
exact original palette/font parity remain outstanding. Translation, final
punctuation and safe handling of malformed causes differ from native ET;
the original strings are intentionally kept intact. No assets, qagame
messages, pak contents or original binaries are modified.
