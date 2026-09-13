#ifndef G_NITMOD_HITBOXDEBUG_H
#define G_NITMOD_HITBOXDEBUG_H
/* Include after g_local.h. Hooks correspond to Original RunEntity,
 * ClientThink_real and ClientEndFrame respectively. */
void G_NITMOD_DrawEntityHitbox(gentity_t *ent);
void G_NITMOD_DrawClientThinkHitboxes(gentity_t *ent);
void G_NITMOD_DrawClientEndHitboxes(gentity_t *ent);
void G_NITMOD_DrawShotHitboxes(gentity_t *attacker);
void G_NITMOD_DrawAttachedHitboxes(gentity_t *target);
void G_NITMOD_DrawHistoricalHitbox(gentity_t *target);
void G_NITMOD_DebugRailBox(const vec3_t origin, const vec3_t mins,
    const vec3_t maxs, const vec3_t color, int group);
#endif
