# Receiving original-server charge times without a new handshake

The original cgame_servercmds.c dispatches exact `ct` to nitrox_ParseChargeTimes
without a reconstruction-specific capability exchange. Its ten arguments are
the two-team values for soldier, medic, engineer, fieldops and covertops.
The existing typed parser already implements this tuple with strict count and
integer checks and commits only after all ten values are valid.

The reconstructed client now accepts this message without requiring
NITMOD_FEATURE_CHARGE_TIMES. This is receive-only: it does not infer or enable
other server capabilities, switch weapon models, enable NCS or send a reply.
The reconstructed server still capability-gates its outgoing extensions to
protect stock clients. Other client message gates remain pending individual
original-server analysis; this change is not a blanket protocol bypass.

A new full-source cgame fixture calls CG_ExecuteNewServerCommands through the
real dispatcher with no prior handshake. It checks all ten destination values,
each malformed integer position and short argc, and verifies that rejected
messages preserve the entire cg object. Unexpected syscalls fail the test.
Neither charge reception nor passing this fixture establishes a successful
original-server join, snapshot weapon compatibility or browser gameplay parity.

Recompiling cg_servercmds.c after restoration of the original menudef.h also
revealed five missing legacy ET VOICECHAT macros previously supplied by the
modified asset header. Their existing string comparisons now live directly in
code (kill_insult, taunt, death_insult, kill_gauntlet, praise), matching the
historical ET header in the local reference tree. No asset definition is added.
The earlier incremental build pass was insufficient evidence for this dependency.
