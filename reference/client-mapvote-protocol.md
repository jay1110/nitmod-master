# Original Nitmod map-vote client protocol

The reconstructed cgame accepts the original intermission commands without
changing PK3 content:

- `immaplist <multi> (<map> <id> <last-played> <times-played>)*`
- `imvotetally <votes>...`

The client owns a typed, bounded cache for at most 32 maps. Map names use
`MAX_QPATH`; display names use the arena parser and a fixed 128-byte buffer.
Malformed records are rejected and oversized lists are truncated before any
array access.

`/nitmaplist` exposes the received state for testing. `/nitmapvote <row>` sends
the original single-vote request. Multi-vote servers additionally accept a
choice slot from 1 through 3 and reject duplicate map selections locally.

For original-protocol map-vote intermissions, cgame now owns the complete
screen lifecycle. It requests `immaplist` until the bounded list arrives and
then refreshes `imvotetally` once per second. The screen renders 19 scrollable
rows, tally percentages, the selected map's levelshot (with the stock unknown
map fallback), last-played and play-count metadata, and one or three explicit
vote buttons. Mouse wheel/arrow keys scroll; clicking a row only selects it;
Enter or a vote button submits the selected original map id.

Reference functions: original cgame `CG_parseMapVoteListInfo` at approximately
`0x45230`, `CG_parseMapVoteTally` at approximately `0x454e0`, and the map-vote
button handlers around `0x46900`.
