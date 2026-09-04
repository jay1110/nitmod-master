# Class and team respawn configurations

New cg_nitmod_autoexec.c/.h implements the original optional-config lifecycle,
not just cvar registration. It is called at the end of the actual CG_Respawn
path and resets its transition state during CG_Init. Both CMake and SCons
include the new unit. No configuration, menu, pak or original binary is edited.

Evidence:

- sorted cgame_client.c CG_Respawn, around lines 18755-18785: no execution
  for revives/demos, class changes on Axis/Allies before team changes.
- sorted cgame_bg.c BG_ClassnameForNumber_Filename, around 6425: exact
  capitalization Soldier, Medic, Engineer, Fieldops, Covertops.
- sorted cgame_client.c CG_execFile, around 14267: PC_LoadSource check,
  free the source, then queue `exec %s.cfg\n` only if it exists.
- Original cgame ELF function addresses: CG_Respawn 0x984c0, CG_execFile
  0x83b40, BG_ClassnameForNumber_Filename 0x21be0.
- Original ELF symbol data: oldTeam.12005 at VA 0x1389e4 and oldCls.12006
  at VA 0x1389e8 each contain signed -1 initially (read through ELF32 section
  and symbol tables, not inferred from the decompiler's zero declarations).

Files are autoexec_Soldier.cfg, autoexec_Medic.cfg, autoexec_Engineer.cfg,
autoexec_Fieldops.cfg, autoexec_Covertops.cfg, autoexec_free.cfg,
autoexec_axis.cfg, autoexec_allies.cfg and autoexec_spectator.cfg.
Only these fixed stems enter console commands. Optional files use the
engine virtual filesystem and normal engine exec semantics; this is not a
new sandbox for commands contained in user configurations or loaded PK3s.

State tracks attempts even when a file is absent, matching the original:
the same class/team is not repeatedly probed on every spawn. Spectator
transitions leave the previous class unchanged. Revives and demos neither
execute files nor consume pending transitions. Invalid client/team/class
indices never become filenames; an invalid class does not prevent a valid
team transition. Native ET and reconstructed-layout sessions are unaffected.

Defensive differences: missing/negative parser handles are never freed;
invalid enum values do not produce the original ERROR filename. CG_Init
explicitly resets state for a reused module instance, rather than relying
solely on shared-object static reinitialization. Map-restart respawns retain
state and do not re-execute an unchanged class/team.

Tests: 1008 protocol/demo/revive/team/class/file-presence combinations,
case-exact paths, free-before-exec order, unchanged-spawn suppression, and
real CG_Respawn calls covering revive deferral and spectator return.
Invalid client IDs and absent snapshot are also covered. No profile backup
or restoration is claimed by this change. Browser virtual-file persistence,
configuration contents and live original-server replay remain unverified.

## Map initialization

CG_Init also attempts autoexec_<rawmapname>.cfg, falling back to
autoexec_default.cfg only if the map file is absent/unavailable. This is
after server/wolf info parsing and before arena/campaign/media loading,
matching sorted cgame_client.c around 14478-14494. Unlike the respawn
branch, original map initialization has no demo exclusion; the port retains
that distinction. The map file and default are never both executed.

Remote map names must fit the complete 64-byte virtual filename and consist
only of ASCII letters, digits, underscore, hyphen or period. Unsafe, empty,
unterminated or overlong names select the fixed default instead. No path
separator, console delimiter or truncated alternate filename is accepted.
This is a deliberate safety difference from the original interpolation.

Another 168 protocol/demo/map/file-presence combinations test map priority,
fallback ordering, exact paths/commands and absence of commands when neither
file exists; an unterminated maximum-size mapname also falls back safely.
