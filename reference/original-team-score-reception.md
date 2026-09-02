# Original-server tsc receive path

The original CG_ServerCommand branch tests the three characters t/s/c and
terminator, then parses arguments 1 and 2 with strtol. There is no reconstructed
feature negotiation before this branch. Besides storing scores, the original
updates score-change timing/direction state; that presentation behavior is not
implemented by this change.

The reconstructed client now accepts tsc without NITMOD_FEATURE_TEAM_SCORES,
using the existing strict two-signed-integer parser. It commits only the axis
and allies score fields in nitmodGameState. No server capability is inferred,
no outbound command is emitted and other receive gates are unchanged. The
reconstructed server's outbound capability checks remain intact.

The full-source cgame fixture exercises the actual sequenced-command dispatcher
without a prior handshake. Cases include both signed int endpoints, a subsequent
zero/negative score, four malformed values at each argument position, and short
and long argument counts. Rejected tuples preserve the complete Nitmod game
state. Valid tuples preserve all non-score fields and the whole cg object,
including previously received charge times. Capability bits remain unset.

This is receive/storage compatibility only. Original score-change animation,
full HUD rendering, original server joins and browser gameplay remain pending.
