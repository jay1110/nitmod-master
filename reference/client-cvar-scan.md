# Original cvar scan response

The existing NITMOD_DisplayCommand handler already supported `cvs`; this
batch corrects and tests it rather than claiming it as a new subsystem.
Evidence: original cgame_servercmds.c CG_ServerCommand around 1248-1269
reads a 256-byte value and sends `cvs %i %s "%s"\n`. Original qagame
nitmod_client.c around 5446-5538 consumes the index, name and actual value.

Responses now retain the original trailing newline. Demo playback performs
neither cvar reads nor replies. Unrepresentable quoted values are not sent:
the old handler substituted an empty string, falsely reporting a different
setting. This deliberate safety difference can cause a scan timeout; it does
not spoof a successful check. Existing strict unsigned integer/name/arity
checks remain. The original 255-character value truncation remains as well.
This is not an integrity attestation or a qagame scan-enforcement port.

The full cgame fixture covers 1120 demo/value/request/name combinations,
four malformed arities, and the 256-byte read through the actual server
command dispatcher. No assets or original binaries change. Live server
acceptance remains untested.
