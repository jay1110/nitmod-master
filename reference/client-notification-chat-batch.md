# Server notifications and local chat batch

## Generic pop notifications

Original nitrox_DrawPopup: ELF32 0x49750, 2590 bytes. Reference in sorted
cgame_nitrox.c; `pop`/`popaw` dispatch is in sorted cgame_servercmds.c around
LAB_000b9973. This batch implements **generic pop only**, not award popups.

`pop <text>` localizes, copies up to 1023 bytes, restarts the generic notice
and prints `%s^7\n`. New messages replace the previous generic notice.
Archive Cvars cg_notificationTime=8000 and cg_notificationFadeTime=250 are
registered with typed cgame handles; UI also registers them for menu access.
The original UI inventory lacks these registrations, an adapter addition.

The timer clamps hold to 1500..10000 ms and fade to 0..250 ms. Fade=0 hides
without progressing state. Fade-in transitions to a hold deadline when sampled
at full opacity; after that deadline opacity fades out. Text, white border and
the shared HUD background slide in from x=639-width*alpha at y=0; background
opacity is half text opacity, panel height 24. Map/reset clears the notice.

Safe deviations: bounded/nonfinite handling, double timestamp arithmetic,
negative-opacity clamping and working start-time zero. The original global
award table, award priority over pop, award sound, award rendering and spree
coordination remain unported. Unknown popaw is not falsely accepted as handled.
Server protocol sending is unchanged.

## lc messages and chat safety

Original `lc <text>` branch uses a two-byte cg_pmColor prefix, otherwise ^7;
it copies into 256 bytes, strips chat escape byte 0x19, submits sender -2 to
team-chat storage and prints `^7%s\n`. Registered cg_pmColor default ^7,
CVAR_ARCHIVE in cgame and UI. Native handling follows that text path; the
optional original client-log writer remains unported.

Native CG_AddToTeamChat previously indexed clientinfo with arbitrary sender
numbers, including -2. It now resolves valid client teams normally and assigns
TEAM_FREE to invalid/system senders, both for wrapped and final lines. This
is safety hardening; it does not claim original sentinel-specific styling.
Invalid command argument counts do not replace existing notification/chat state.

## Checks

Full cgame fixture: 54 notification timelines with six samples each, clamped
durations, disabled fade, replacement, truncation, rendering callback and reset;
real pop and lc command dispatch; four color-prefix/escape profiles and malformed
commands. Cvar inventory assertions cover defaults and registrations.
Native Debug build and all 88 CTest cases pass. No pak, menu, PK3 or reference
ELF changes. Actual browser rendering and dedicated-server parity remain open.
