# Greeting sound command

Original cgame_servercmds.c CG_ServerCommand handles `gsnd` without a
capability handshake. cg_noGreetingSounds (default 0, CVAR_ARCHIVE) suppresses
registration and playback when nonzero. Otherwise it registers argv[1] with
compressed=false and plays on the snapshot player's entity, CHAN_VOICE.

The reconstructed handler implements that receive path and refreshes the
Cvar before testing it. Intentional hardening rejects wrong argument counts,
missing snapshots, invalid client numbers, empty or overlong MAX_QPATH paths,
and nonpositive sound handles. This is not a server greeting generator.

The full-cgame command-dispatch fixture exercises 144 combinations of Cvar
values, snapshot validity, sound registration results and malformed commands.
It checks both registration suppression and playback entity/channel/handle.
No PK3 assets are changed. Browser and original-server parity are not proven
by these synthetic syscall fixtures.
