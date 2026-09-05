# Rank runtime integration and download validation

## Active changes

- qagame recalculates rank from the sum of seven skill levels on session
  restoration/recalculation and skill upgrades. See skill-rank-disassembly.md
  for original addresses, thresholds and remaining ability/Lua limitations.
- cgame validates the userinfo rank before later rank-name, icon and sound
  lookups. Invalid values become rank zero; the wire format is unchanged.
- The active UI_DownloadInfo uses shared bounded counter, percentage and
  transfer-rate helpers. Tests cover large counters, small/unknown totals,
  sub-second durations and clock rollback. Existing ETA and size-format
  boundary tests remain in check_ui_download_bounds.h.

UI_DisplayDownloadInfo in ui_main.c is inside #if 0. Its equivalent cleanup
is maintenance only, not an additional active UI feature or runtime test.

## Verification

- Native Debug build: all 97 CTest tests passed.
- Rank numeric oracle: 279936 level combinations; linked qagame recalculation:
  78125 native XP profiles. Upgrade side effects are not replay-tested.
- All three WASM artifacts rebuilt; Node dlopen/dlsym, ABI and entrypoint
  smoke tests passed individually and concurrently.
- Pak read-only check and git diff whitespace check passed.

No original assets were changed. Browser screenshots, dedicated-server
gameplay parity and complete six-level server skill behavior remain unverified.
