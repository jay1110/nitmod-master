# Client skill threshold reception

Original server command `sl` (ELF string VA 0x10dc91) passes trap_Args,
256 bytes, to CG_UpdateSkills. It reads S/M/E/F/C/B/L and calls
InitSkillLevelStructure for seven rows of five thresholds. The existing
typed nitmod_skills parser now feeds a separate client matrix. Map/config
reset discards it; defaults are 0/20/50/90/140/200.

Cached and text/window player statistics use nitmodSkillLevels and this
matrix under the original protocol, including the level-four target for
level five. ET retains its existing levels and thresholds. Level five has
no next threshold. Negative thresholds are displayed without a next-level
denominator (intentional handling of disabled upgrades).

Malformed/incomplete updates leave the entire matrix intact instead of
copying uninitialized original parser locals. Tests check seven independent
rows, all levels, malformed update preservation, ET isolation and reset.
The shared numeric parser already has its own tests. Rank presentation and
live server/browser verification remain open. Pak files remain untouched.

Integration follow-up: the full cgame fixture now dispatches the actual `sl`
server command via CG_ExecuteNewServerCommands/trap_Args, then an invalid
replacement, and renders all seven skills at levels 0..5 through both stats
parsers. Native levels deliberately disagree to catch incorrect field use.
Reset restores defaults. The original eleven rank names at ELF 0x12ec00
and 0x12ec40 were compared with bg_misc.c and already match exactly; no
replacement rank-name table is needed. This does not certify other rank
consumers or browser rendering.
