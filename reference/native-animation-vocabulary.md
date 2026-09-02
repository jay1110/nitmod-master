# Original script vocabulary on the typed ET baseline

The shared animation parser now distinguishes four additional animation-only
conditions: Poison Syringe, Bomb, Poison Bomb and Poison Landmine. Their slots
start at WP_NUM_WEAPONS, after all existing native weapon conditions, and stay
within the two-word/64-bit animation condition representation. Tripmine already
has its own native condition. These slots are NOT snapshot IDs or weapon_t
members; original Nitmod wire IDs remain different and still need integration.

This is an intermediate internal representation: existing native weapons keep
their condition bits, and the four extra names map to distinct bits instead of
being ignored, treated as unconditional or aliased to native weapons. Native
gameplay currently cannot select the additional bits because the corresponding
weapons are not ported. This does not implement poison damage, weapon spawning,
prediction, rendering or original-server snapshot compatibility.

BG_InitWeaponStrings also supplies an explicit zero sentinel, avoiding a scan
past its array when BG_IndexForString searches an unknown name. The strict
unknown-token error remains for names outside the supported vocabulary.

The full-source client fixture checks existing item-name mappings, individual
bits for each new condition, safe missing-name lookup, executes the DEFINES
section from the unchanged human_base.script, and invokes BG_ParseConditions
on its weapon-condition lines. It also parses the full unmodified script with
synthetic model-name metadata discovered from its both/legs/torso operands.
Generated command animation references are checked against that metadata.
This tests script grammar and construction, not whether the original MDX assets
provide those animations. It does not execute animation commands or load a map;
further map-start failures and missing animation models remain possible.

The fixture also executes BG_UpdateConditionValue/BG_EvaluateConditions for
all 64 client slots, all 54 current animation weapon bits and each of the four
new singleton conditions (13,824 evaluations). Each accepts only its own bit;
sequential updates verify that a previous weapon bit is cleared. These are
test-supplied animation condition IDs, not newly supported gameplay weapons.
Seven BG_GetAnimScriptAnimation combat-idle cases select the original script's
stand_knife, stand_grenade or stand_medpack entry for Poison Syringe, Bomb,
Poison Bomb, Poison Landmine, Tripmine, Smoke Bomb and Landmine. All other
conditions are zero for these cases. This checks internal script selection,
not model-frame accuracy, weapon wire IDs, prediction or live rendering.

GAMEVERSION in the normal reconstructed qagame build is now nitmod instead of
etmain. This updates gamename registration/logging and the existing map-XP cvar
prefixes. It does not change fs_game, the engine's base directory or the original
PK3. No assets are modified and no override package is required.
