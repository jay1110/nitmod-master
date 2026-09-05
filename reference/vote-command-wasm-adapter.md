# Vote command callback signature

The active qagame command table stores void-returning callbacks. Cmd_CallVote_f
returns qboolean because its referee callers consume a status. The old table
cast its address to the void callback type. Calling through an incompatible
function type is undefined in C and is incompatible with WASM indirect-call
signature checking.

G_CallVoteCommand now has the table's exact signature and invokes the existing
vote API directly, explicitly discarding its result. Referee callers retain
the original return-value contract. Command names, privilege gates, vote
messages and menu assets are unchanged. This is a portability correction of
an active path, not a new Nitmod voting system or original-binary parity claim.

check_vote_dispatch.h exercises G_commandCheck through the real table, including
the command-help argv callback, mixed-case matching, dispatch phase and two
rejection messages (existing vote/intermission). The test does not simulate
an accepted vote or prove a browser menu interaction. Existing WASM Node
smoke tests validate module loading/entrypoints, not this in-game vote path.
