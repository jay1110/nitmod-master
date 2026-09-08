#ifndef G_NITMOD_CHARGE_H
#define G_NITMOD_CHARGE_H
#include "nitmod_skills.h"
/* Caller has included g_local.h. A read-only probe never normalizes state. */
qboolean G_NITMOD_ChargeAction(gentity_t *ent, nitmodSkillTable_t table, int skill, qboolean updateState);
qboolean G_NITMOD_ChargeWeapon(gentity_t *ent, int weapon);
void G_NITMOD_RefundCharge(gentity_t *ent, nitmodSkillTable_t table, int skill, float scale);
#endif
