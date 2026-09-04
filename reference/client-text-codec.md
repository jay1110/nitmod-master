# Original Nitmod text transport

Reference: `cgame_shared.c` functions `need_escape`, `escape_string`,
`unescape_string`; incoming `print`, `chat`, `tchat` in
`cgame_servercmds.c`; debrief chat in `cgame_ui.c`.

The bounded shared codec encodes percent, equals and bytes >= 127 with
uppercase =XX. Decoding accepts only uppercase =20 through =FF, performs
one pass, and leaves malformed/truncated escapes literal. It never decodes
embedded NUL/control bytes. Encoder overflow leaves the destination intact.

Original-server message menus (public/team/fireteam/admin) and debrief chat
now encode before direct reliable transmission. Quotes/control input is
explicitly rejected, unlike the unsafe original interpolation. Native ET
paths are unchanged. Incoming print/chat/tchat decode private copies before
display; chat decoding precedes the displayed-length limit. No PK3 edits.

Console interception now covers all seven original commands: say, say_team,
say_teamnl, say_buddy, ma, m and pm. Literal resolution was checked in the
original cgame ELF: Ghidra addresses 0x11288a/0x112768/0x113436/0x113439
map to ELF VAs 0x10288a/0x102768/0x103436/0x103439 (image-base delta 0x10000),
containing say/ma/m/pm. This follows CG_ConsoleCommand's ConcatArgs(1):
join tokenized arguments with spaces and intercept only text requiring
encoding. ASCII-only commands keep engine forwarding. Native protocol and
the pre-snapshot gate remain unchanged. Overflow is consumed with a diagnostic,
never forwarded truncated. Menu and console sends share a bounded atomic
command builder with the same seven-command allowlist.

Runtime tests now cover all 255 non-NUL byte values, all seven command
envelopes, mixed-case recognition, exact output capacity, invalid command
names and delimiter rejection. This does not implement qagame admin-chat
authorization or establish full
server chat parity. Runtime C tests cover bytes, malformed escapes, capacity
and single-pass decoding. Live original-server chat remains to be tested.
