# Persisted limbo secondary preference

The original cgame cvar table entry 0x138774 registers cg_limbo_secondary=0
with flags 1 (CVAR_ARCHIVE). It is now registered with typed storage in cgame.
The original slot setter in sorted cgame_ui.c writes this cvar for secondary
selection, and CG_LimboPanel_Setup restores it when no loadout was selected.

The typed slot setter now saves the preference; the actual secondary menu
selection path routes through that setter. Invalid interactive secondary
indices are rejected before saving. Primary selection does not write it.
Restoration clamps an oversized preference to the last available secondary
choice, preserving the saved value so that a later skill/class configuration
can offer it again. Negative values resolve to the default pistol. Already
chosen loadouts are not overwritten. Cvar synchronization uses the normal
registered-cvar update loop.

Restoration occurs after adopting the player's team/class, so the available
secondary count belongs to the resulting selection. This is a deliberate
ordering correction to the old setup sequence. Primary latched-weapon lookup
still precedes that adoption and needs separate correction/verification.
Setup also rejects invalid local client indices before any cvar access.

Tests exercise preference values -1..3 across the existing 500 protocol/team/
class/skill profiles (2500 combinations), both selected/unselected loadouts,
preservation of saved values and exact cvar writes from the slot setter and
interactive selection path. The cvar inventory has been regenerated; source
mention counts are not a measure of completed functional parity. Original
binaries and pak assets remain unchanged. Browser persistence remains to be
tested end-to-end.
