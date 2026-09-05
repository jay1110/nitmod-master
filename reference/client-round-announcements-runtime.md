# Original round-announcement mode gate

Original CG_CheckLocalSounds in sorted cgame_client.c returns before time-limit
warnings for gametypes 7 and 8 (TDM/DM). The native implementation lacked that
gate. The active path now suppresses the 5-minute, 2-minute and 30-second
objective announcements in these modes without altering snapshot hit sounds.
Elapsed-time subtraction uses double to avoid signed integer overflow.

The existing positive time limit, playing-state gate, one-second open timing
windows, Axis/Allies samples and one-shot warning mask remain unchanged.
Spectators consume the warning bit without playing a team sample, as before.

A full linked cgame fixture tests 3240 combinations: modes 0..8, six states,
four teams, three warnings, five boundary times. It verifies exact sound handle,
channel, warning-mask mutation and no replay on a second call. This test covers
direct sound handles, not the -1 sound-script fallback or live browser playback.
No new UI/qagame feature, asset or wire format is introduced by this change.
