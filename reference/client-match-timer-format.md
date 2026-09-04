# Match timer formatting

Recovered from CG_DrawUpperRight in sorted cgame_ui.c, original ELF function
0x44b50. Original .rodata at 0x103469 and following contains `^7WARMUP`,
`^N0:00`, and the minute/hour/day format strings. Reference cgame SHA-256:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

CG_NitmodMatchTimerText replaces the inline ET minute-only formatting:

- Below one hour: white minutes:two-digit-seconds.
- One hour or more: hours:minutes:two-digit-seconds.
- One day or more: days followed by d, then hours:minutes:two-digit-seconds.
- Minutes within hour/day formats deliberately have no leading zero, as in
  the original format strings.
- Warmup is white; expired limited matches retain `^N0:00`.
- Unlimited matches keep only the reinforcement prefix.

The actual timer renderer calls the formatter, preserves the existing alpha
pulse, and applies the manual spawn-timer prefix afterwards. No network fields,
cvars or assets change. Existing typed GS_PLAYING classification is retained;
this does not establish original warmup-state-field parity. Full timer
placement and screenshot parity remain open.

The manual timer reset now subtracts the two integer clock values before
converting their difference to float, avoiding loss from first rounding a
large absolute clock. Double subtraction avoids signed overflow in this step.

Fixtures cover 48 combinations of boundary times, match state and time-limit
presence, plus absent reinforcement text. Existing 10860 spawn-cycle profiles
continue testing the following prefix stage. Full native tests, WASM build
and Node ABI/load probes are run; none replace a live browser gameplay test.

## Round-timer integration

CG_NitmodRoundTimerText now supplies the actual original-protocol HUD:
free spectators have no reinforcement prefix, following spectators use the
viewed player's team, and LMS suppresses reinforcement time. Original modes
7/8 retain the leading space and reinforcement prefix but omit the ordinary
match countdown, including its expired-time pulse. Warmup and the manual
spawn prefix retain their precedence. Reconstructed/native sessions keep
their previous formatting path.

The shared reinforcement calculation used by HUD, limbo and scoreboard now
validates client/team indices and positive intervals before indexing/modulo.
Double arithmetic prevents signed clock-sum overflow; the existing final
float arithmetic and truncation are preserved. The original HUD saturates
out-of-range remaining times before integer conversion, a defensive
deviation rather than original overflow emulation.

The runtime fixture adds 336 mode/team/follow/state/limit/elapsed combinations,
manual-prefix precedence, invalid intervals/clients/teams, limbo team choice,
and extreme clocks. Original behavior evidence is CG_DrawUpperRight in
sorted cgame_ui.c around lines 7314-7426. No new wire fields, menu or pak edits.
