#include "cg_nitmod_skill_rewards.h"
#include "../game/nitmod_skills.h"

/* Original cgame ELF cg_skillRewards at 0x138a00 (7 rows, 5 pointers).
 * Text recovery does not implement the advertised gameplay abilities.
 * Kept separate from the active four-level native reward table. */
static const char *const nitmodSkillRewards[NITMOD_SKILL_COUNT][NITMOD_SKILL_LEVEL_COUNT - 1] = {
	{ "Binoculars", "Improved Physical Fitness", "Improved Health", "Trap Awareness", "Improved lungs capacity" },
	{ "Additional Explosive Ammunition", "Faster Arming and Defusing", "Improved Construction and Demolitions", "a Flak Jacket", "Bombs" },
	{ "Additional Ammo", "Improved Resources", "Full Revive", "Adrenaline Self", "Improved Health Care" },
	{ "Improved Resources", "Improved Signals", "Improved Air and Ground Support", "Enemy Recognition", "Faster stamina recharge & Improved ammopacks" },
	{ "Extra Light Weapon Ammunition", "Faster Reload", "Improved Light Weapon Handling", "Dual-Wield Pistols", "Throwing knives" },
	{ "Extra Heavy Weapon Ammunition", "Reduced Overheating", "Increased Movement Speed", "SMG Sidearm", "Mid Clip Reload" },
	{ "Extra Scoped Weapon Ammunition", "Improved use of Sabotage and Misdirection", "Improved Accuracy", "Backstab", "Reload in scoped view" }
};

const char *CG_NITMOD_SkillRewardText( int skill, int level ) {
	if( skill < 0 || skill >= NITMOD_SKILL_COUNT || level < 1 || level >= NITMOD_SKILL_LEVEL_COUNT ) {
		return 0;
	}
	return nitmodSkillRewards[skill][level - 1];
}
