# Original shove sound: event 96

Original sorted cgame_events.c, CG_EntityEvent case 0x60, tests
cg_shoveSounds.integer and calls StartSoundVControl(NULL, entity number,
channel 0, cgs field 69264, 255). The static original Cvar table registers
cg_shoveSounds with default 1 and CVAR_ARCHIVE.

The sound registration in sorted cgame_client.c uses the misleading
Ghidra expression &__DT_REL[0x7f].r_info as an offset from cgs. The original
ELF .rel.dyn address 0xa94 plus Ghidra's 0x10000 image base plus
0x7f * 8 + 4 equals 0x10e90 (69264). The loop registers
sound/weapons/impact/flesh1.wav first. The typed ET equivalent is therefore
cgs.media.sfx_bullet_fleshhit[0], already registered during media loading.

The client handles event 96 only for original Nitmod server identity, without
changing the native event enum or snapshot. It refreshes the Cvar before
dispatch. Invalid entity numbers and nonpositive sound handles are rejected
as intentional hardening beyond the original. No assets are changed.

The full-cgame fixture covers 180 combinations: three Cvar values (including
negative/nonzero), four repeat-bit patterns, five entity numbers and three
sound handles. It verifies entity, channel, volume, sound and unchanged event.
This covers the sound receiver, not server shove gameplay or full protocol
parity. Dedicated-server and browser integration still require live testing.
