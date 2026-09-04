# Client output log reconstruction

Original evidence comes from `CG_WriteToLog` in the reference cgame ELF and
the decompiled call sites in `cgame_servercmds.c`, `cgame_sound.c`, and
`cgame_ents.c`. The original owns one file handle for the cgame lifetime,
opens `cg_logFile.string` in append mode when `cg_clientLog` is nonzero, and
prefixes each write with the local real-time clock.

The typed implementation is isolated in `cg_nitmod_log.c`. It opens after
Cvar registration and closes during `CG_Shutdown`, including cgame restarts.
The output buffer is bounded to 1024 bytes and the caller passes text as data,
not as a printf format string. Current mapped call sites cover:

- server `print` output;
- global `chat` and team `tchat`;
- private/local `lc` messages;
- displayed buffered voice-chat text.

Lines use `[HH:MM:SS] text`, reconstructed from the original `qtime_t` field
loads and format construction. Empty/disabled file names leave the handle
closed; opening failure is reported through the cgame console. The virtual
filesystem syscall is shared by native and WASM builds, so this code makes no
native host-filesystem assumptions.

Remaining original call sites include several Nitmod-private event and sound
messages whose typed dispatch is not fully reconstructed. They must be wired
when those commands are ported; this document does not claim complete output
coverage. `CheckClientLogFormatting` verifies timestamp order, zero padding,
termination/truncation, and null inputs. Full CTest and the WASM loader smoke
test verify linking and ABI, but not browser filesystem persistence.
