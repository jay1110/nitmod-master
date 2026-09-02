# Original server messages and hit-event batch

SrvMsgs is the original cgame ELF table at 0x138ac0, size 0xe8 (58 pointers).
tools/extract_server_messages.py verifies the original SHA-256 and maps
virtual addresses through ELF sections. All 58 strings are reproduced in
game/nitmod_server_messages.inc and compared directly by a regression test.
The seven-message weapon-limit API remains a compatibility wrapper.

The client now receives ncp without a reconstructed capability exchange.
IDs outside 0..57 and malformed arguments are rejected. ID 7 uses the scs
dynamite timer divided by 1000 unless it equals 30000, matching original
CG_ServerCommand. These are notifications only: the corresponding server
gameplay/admin mechanics are NOT implemented merely by adding their strings.

Original CG_EntityEvent case 99 dispatches eventParm 3 to team.wav and 4
to hs.wav, using the snapshot client number and channel 3 (CHAN_VOICE).
CG_RegisterSounds maps original cgs offsets 132008 and 132000 to
sound/hitsounds/team.wav and sound/nit/hs.wav respectively. The handler
shares the existing sound backend, preserves its nhs command's prior
CHAN_AUTO behavior, and uses CHAN_VOICE for original events. Unknown types
do not play sounds. Snapshot client bounds are checked. cg_hitSounds is now
registered at ordinary cgame startup with original default 1/flags 1, and
updated before playback. Lazy asset registration differs from original eager
registration. Cached handles are reset at NITMOD_ClearConfigStrings.

Tests exercise all ncp IDs through actual dispatch, exact binary text-table
parity, and 32 hit-event combinations (enabled/disabled, types 2..5 and all
repeat-bit patterns). Sound paths, channel, handle, Cvar default/flags and
target are checked through the engine callback fixture. Browser rendering,
original-server gameplay, and the earlier null indirect call remain unverified.
No pak or original reference artifact was modified.
