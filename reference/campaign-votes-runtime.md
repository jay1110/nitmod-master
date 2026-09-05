# Campaign voting: original menu to reconstructed server

G_NextCampaign_v (original qagame ELF 0xe90a0) and G_RestartCampaign_v
(0xe91e0) now have typed adapters in g_nitmod_campaign_vote.c, linked into
native and WASM qagame through CMake and historical SCons. Request admission
requires gametype 4 and the respective vote_allow_nextcampaign or
vote_allow_restartcampaign cvar (both original default 1, flags 0). Console
requests retain the original cvar bypass, but not the gametype bypass.
As in the preceding vote port, player permission-6 overrides remain denied
until a real Nitmod permission owner is available.

The accepted next-campaign callback reads nextcampaign and queues exactly
`vstr nextcampaign\n` if nonempty. The restart callback uses the selected
typed g_campaigns entry and queues `campaign <shortname>`, optionally followed
by `; set nextcampaign "<value>"`. This preserves the configured rotation.
Evidence: sorted nitmod_game.c G_NextCampaign_v_part_0 and
G_RestartCampaign_v_part_1; original aVoteInfo at ELF 0x29e8e0 confirms command
names, labels and help strings, including the original help spelling.

The shared original vote bits 0x40000 and 0x80000 are no longer permanently
disabled. Cvar changes update the existing server voteFlags field, which
cgame forwards to the UI. Existing CS_VOTE_* publication, cgame rendering,
counting and vote-completion ownership are reused, not duplicated.

The unmodified pak/ui/ingame_vote_misc.menu calls `cmd callvote restartcamaign`.
The original server table accepts `restartcampaign`, not that typo.
Shared Script_Exec corrects only that exact invocation (case-insensitively);
arbitrary commands and textual occurrences are unchanged. Thus the menu
works with either original or reconstructed server command spelling without
editing pak. This correction is an intentional compatibility fix, not
claimed original bug-for-bug behavior.

Safety deviations: restart rejects invalid campaign count/index, empty or
unterminated names, unsafe unquoted shortname characters, and quoted rotation
values containing quotes, backslashes or controls. A possibly truncated
rotation value is rejected instead of being executed. Semicolons within a
valid quoted server-owned rotation value remain permitted. Next-campaign
execution uses the fixed vstr command, not string interpolation.

Tests exercise 144 request combinations across modes, enable flags, caller
presence and referee-command flags; both accepted callbacks; rotation values;
campaign-name and index boundaries; and five menu command/case/unrelated-text
cases. Existing vote-mask tests automatically cover both new cvar bits.
No real server command or map transition is sent by the tests. Live browser
campaign transitions and original server screenshots remain unverified.
Pak assets and reference binaries are untouched.
