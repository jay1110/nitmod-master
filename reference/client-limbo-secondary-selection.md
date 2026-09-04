# Secondary selection and STEN visibility

Original references: CG_LimboPanel_WeaponCount_ForSlot, GetWeaponForNumber
and WeaponCount in sorted cgame_ui.c. The original count excludes a disallowed
STEN but retains heavy weapons as visible restricted cards. The port now applies
this distinction only for original protocol. The current original class tables
place conditional STEN entries last (Medic/Field Ops); Covert Ops keeps its STEN.
Existing original-server quota configuration controls the decision.

Secondary weapon inspection confirms the existing typed level-4 rules:
ordinary/silenced pistol according to class, matching akimbo at Light Weapons 4,
and the team's SMG as an additional Soldier choice at Heavy Weapons 4. No new
skill conversion is added: the typed client skill levels are used, not copied
Ghidra byte/bit offsets.

The missing lifecycle repair is now implemented: invalid or no-longer-available
secondary selection indices reset to the default pistol before selected-number
and selected-slot lookup. This is defensive behavior after class/skill changes,
not a claim that the original performed every one of these bounds checks.

The real limbo tests cover both protocols, both teams, all five classes and all
25 light/heavy level pairs from 0..4 (500 combinations). Each checks count and
five requested secondary indices through direct lookup, selected-number lookup
and selected-slot lookup. STEN disabled/enabled primary counts are checked
after parsing # state. The base class list, valid choices and wire conversion
remain unchanged. Original binaries and pak assets are untouched.

Full skill/unlock parity beyond these rules and live browser/server loadout
transitions remain open; native fixtures and Node side-module loads do not
establish full gameplay parity.
