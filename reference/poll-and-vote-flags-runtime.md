# Poll and original vote-mask integration

The UI's already implemented votePoll action now has a reconstructed qagame
receiver. G_NITMOD_PollVote is dispatched through the real vote table; it
joins arguments starting at 2, rejects fewer than two characters, and has a
no-op acceptance callback. A successful poll changes no server settings.
Existing CS_VOTE_* publication and cgame rendering are reused unchanged;
this is not a new vote wire format or a new cgame renderer.

Evidence: hash-pinned original qagame G_Poll_v at ELF 0xe8f30, size 255.
Disassembly confirms argv concatenation, the 256-byte output boundary and
zero-return acceptance branch. aVoteInfo at 0x29e8e0 identifies the label
`[poll]` and help ` <text>^7\n  Poll majority opinion.` The original output
format at 0x23e6e9 is `%s`. vote_allow_poll default 1/flags 0 is registered.

Original G_MapRestart_v's separate vote_allow_maprestart gate is also active
(default 1/flags 0). Its existing reset-match action is unchanged. Previously
the native request path had no independent enable/disable cvar.

Original voteToggles at ELF 0x29e5e0 contains 24 eight-byte records. Poll uses
0x100000 and maprestart 0x200000, not the next free native ET bits. The shared
disabled mask is therefore explicitly 0xffffff, not (1 << tableSize)-1.
Surrender now has an active adapter (surrender-runtime.md). Campaign restart/next are
active (campaign-votes-runtime.md), as are the team-operation command adapters
(team-votes-runtime.md). The latter still use native ET team selection and
are not a claim of original K/D shuffle parity.
The UI recognizes both the original 24-bit and legacy ET 17-bit all-disabled
masks. Enabling only poll correctly keeps the vote menu available. Normal
cvar modification updates use the existing voteFlags publication hook.

Deliberate deviations: unsafe quotes, backslashes, semicolons and control
characters and overlong questions are rejected atomically, including an
overlong later argument. No silently truncated argument sequence is accepted.
The original permission-6 admin override has no reconstructed permission
owner yet. A disabled poll/maprestart is denied to player referees as well;
the trusted console path remains allowed. This is not complete admin parity.

Tests exercise the real server vote dispatcher and poll callback, disabled
requests, multi-argument questions, length boundaries, text rejection, the
maprestart gate, unknown commands, every supported vote bit and no-change
publication. UI tests run clientCheckVote for all 24 single-enabled cases and
both all-disabled masks; existing tests cover the original votePoll sender.
Native builds/tests and WASM load probes are separate from live browser,
accepted-vote timing and dedicated-server screenshot parity, which remain open.
No pak assets or original reference binaries are modified.
