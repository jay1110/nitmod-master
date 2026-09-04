# Consistent original class lists in the limbo menu

The original class tables recovered in client-class-command.md now serve the
limbo menu as well as the class command. CG_NitmodPlayerClass supplies a typed
view per team/class: for original protocol it copies the base class metadata
and replaces only classWeapons with the recovered list, zero-padded to the
typed capacity. For the native protocol it returns the unchanged ET class.
Shared BG tables and qagame gameplay are never rewritten by the client view.

CG_LimboPanel_GetPlayerClass is the common entry for menu weapon counting,
primary selection, latched-weapon restoration and existing heavy-weapon quota
checks. These now agree on the same list: opposing SMGs and the additional
STEN choices no longer exist only in the console command. Invalid primary
indices and empty slots return WP_NONE; restriction checks reject those slots
before indexing. Secondary weapons and existing quota algorithms are unchanged.

Tests compare all ten typed slots for both protocols, both teams and all five
classes, including empty-slot rejection, count, negative/over-capacity indices
and immutability of the underlying BG class record. Existing 160 real class
command cases continue to verify exact original/native weapon IDs.

This establishes list consistency, not full limbo UI parity. Original quota
cvars, skills/unlocks, weapon card presentation and end-to-end server spawning
still require further verification. Original assets/binaries remain untouched;
native tests and WASM load probes do not substitute for browser interaction.
