# Cvar recovery baseline

original-cvar-inventory.csv is reproducible with tools/extract_cvar_inventory.py.
It reads symbol-addressed, SHA-256-pinned original ELF32 tables: cgame
cvarTable 200 x 20 bytes, qagame gameCvarTable 339 x 28 bytes, ui cvarTable
210 x 20 bytes. Each row preserves address, vmCvar address, exact default,
flags, modification counter and (server only) track-change/reset fields.

These 749 registration rows are NOT all engine Cvars or a full inventory
of dynamic trap_Cvar_Register/Set/Get calls. Duplicate names across modules
are intentionally retained. Source mentions are case-insensitive quoted
name matches in that module's .c files, including comments. They do not
prove registration, reachable implementation, matching flags or behavior.
The generated status remains needs-semantic-audit even for working ports.
Future audit must include shared helpers, dynamic registration and aliases.

## cg_pmSounds: implemented, locally tested, remote verification pending

Original cgame registration: default 1, flags 1 (CVAR_ARCHIVE).
Original CG_EntityEvent case 0x62 compares entity number with cg.clientNum
(original cg base 0x1037ac0 plus 4), tests cg_pmSounds.integer and plays
cgs+69656 with channel 3 and volume 255. CG_RegisterSounds initializes
that field to sound/nit/pm.wav. The typed implementation registers the Cvar
in cgame's ordinary table, honors live changes, and dispatches only original
Nitmod event 98. Native event numbers are unchanged.

The sound is loaded lazily when first needed and its handle is reset at
NITMOD_ClearConfigStrings. That differs from original eager registration;
valid enabled events use the same path, target, channel and volume. Invalid
client numbers are additionally rejected. The existing PM text protocol is
not implemented by this sound event.

The full-cgame fixture tests 24 combinations of target, all repeat-bit
patterns and integer values -1/0/1, unchanged event payload, exactly one
sound registration per lifecycle and re-registration after reset. Inventory
test pins the original default/flags and checks the production registration.
This is a small verified portion, not a completed Cvar or event port.
