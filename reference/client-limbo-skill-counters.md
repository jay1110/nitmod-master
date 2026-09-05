# Five-level Limbo skill counters

Original CG_LimboPanel_RenderCounter_ValueForButton case 4 derives
(1 << displayed level) - 1 for Battle Sense, Light Weapons and selected
class skill. CG_LimboPanel_RenderCounter_NumRollers returns five for skills,
except in LMS where it returns zero. These are displayed levels, not unlock
masks; holes in the unlock mask must not remove displayed progress.

The original-protocol adapter now reads nitmodSkillLevels (0..5) and draws
five rollers. Native ET retains its 0..4 levels and four rollers. Invalid
client/skill-counter selectors and out-of-range original levels return zero
without indexing or shifting invalid values. Existing roller drawing uses
the returned count and fits them within the unchanged panel rectangle.

Tests cover both protocol counts, Battle Sense and Light Weapons levels,
LMS hiding, divergent native/original levels and invalid client/level values.
Browser layout comparison and class-button wedge presentation remain open.
No pak, menus or shared gameplay ABI changes.
