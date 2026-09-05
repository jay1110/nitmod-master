# Nitmod map-vote server runtime

The reconstructed cgame already implemented the original `immaplist`,
`imvotetally` and `mapvote` protocol, but qagame had no matching dispatch.
The server side now enumerates maps through the engine VFS, filters the current
and explicitly excluded maps, limits the list with `g_maxMapsVotedFor`, and
uses the original four-field list records consumed by cgame.

Votes are accepted only during intermission and only for IDs in the transmitted
window. `g_mapVoteFlags` bit 4 enables the recovered three-choice mode. Each
client can replace a choice, cannot select the same map in two slots, and all
tallies are bounds checked. Choice slots retain the original 1/2/3 vote
weights, including subtraction when a choice is replaced. Numeric command
arguments use the shared strict protocol parser instead of `atoi` aliases.

Flag bit 2 is enforced in the shared intermission-exit decision: the configured
ready percentage must also have cast map votes before the normal timeout or
player-ready path may advance. Referee `allready` remains the explicit
override, and bots are excluded from both sides of the ratio.

`mapvoteinfo.cfg` is read and written through the engine VFS in the original
section/key format. It carries times played, maps since last play, accumulated
votes and eligibility for at most 64 maps. ExitLevel selects the highest
weighted tally and uses the recovered bit-1 age rule for ties: without bit 1
the smaller age wins, while bit 1 reverses the comparison. Never-played maps
use the original 9999 sentinel. History is then updated before starting the
winner. Other `g_mapVoteFlags` policies remain separate work.
