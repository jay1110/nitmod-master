# Manual spawn timer

Reference: cgame_client.c CG_TimerSet_f and CG_ResetTimer_f, and the timer
prefix in cgame_ui.c CG_DrawUpperRight. Original ELF addresses are 0x32080
and 0x31fd0; command strings are timerSet/resetTimer. Original cgame hash:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

Both cvars are now backed by typed vmCvar_t state in cgame and registered
with original defaults/flags: cg_spawnTimer_set=-1, cg_spawnTimer_period=0,
CVAR_TEMP (256). They are client-local, not server commands or negotiation
fields, so no qagame/UI protocol addition is needed.

timerSet with no argument disables the timer by setting its anchor to -1.
One argument is read through a 32-byte buffer and strtol, retaining original
numeric-prefix parsing; only parsed values 1..60 are accepted. The period
string is stored and the anchor is set to remaining match seconds. Additional
arguments produce usage text. resetTimer updates only the anchor. The normal
console snapshot guard remains in force.

The existing match timer now gets the original red prefix:
`(remainingSeconds - anchor) % period + period`. A disabled anchor or nonpositive
period omits the prefix. At a cycle boundary it displays the full period, not
zero. This is a manual timer; it does not reveal server-only spawn information.

Hardening differences: non-finite/out-of-int-range reset times are rejected;
prefix subtraction/remainder uses double to avoid signed overflow on arbitrary
cvars. Full original timer formatting, long matches and placement are separate
work. No assets or original binaries change.

Tests cover periods 1..60 over 181 elapsed-second positions, disabled states,
real timerSet/resetTimer console dispatch and exact cvar writes, no-argument
disable, and rejection of period 61. Browser visual verification remains open.
