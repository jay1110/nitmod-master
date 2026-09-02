#include "g_local.h"

static nitmodBotHandleEntry_t botHandles[NITMOD_BOT_ENTITY_COUNT];

static gentity_t *FindCachedNameHash(gentity_t *from, int hash, qboolean scriptName) {
    int index = 0, limit = level.num_entities;
    if(limit < 0) return NULL;
    if(limit > MAX_GENTITIES) limit = MAX_GENTITIES;
    if(from) {
        /* Reject foreign pointers without undefined pointer subtraction. */
        for(index = 0; index < MAX_GENTITIES; ++index)
            if(from == &g_entities[index]) break;
        if(index == MAX_GENTITIES) return NULL;
        ++index;
    }
    for(; index < limit; ++index) {
        gentity_t *entity = &g_entities[index];
        if(entity->inuse && (scriptName ? entity->nitmodScriptNameHash :
                            entity->nitmodClassnameHash) == hash) return entity;
    }
    return NULL;
}

gentity_t *G_NITMOD_FindByClassNameHash(gentity_t *from, int hash) {
    return FindCachedNameHash(from, hash, qfalse);
}
gentity_t *G_NITMOD_FindByScriptNameHash(gentity_t *from, int hash) {
    return FindCachedNameHash(from, hash, qtrue);
}

void G_NITMOD_InitSpawnNameHashes(gentity_t *entity) {
    const char *scriptName;
    if(!entity) return;
    entity->nitmodTargetHash = entity->target && entity->target[0] ?
        (int)BG_StringHashValue(entity->target) : -1;
    scriptName = entity->scriptName;
    if(!scriptName || !scriptName[0]) {
        entity->nitmodScriptNameHash = -1;
    } else {
        if(entity->classname && !Q_stricmp(entity->classname, "script_multiplayer"))
            scriptName = "game_manager";
        entity->nitmodScriptNameHash = (int)BG_StringHashValue(scriptName);
    }
}

int G_NITMOD_BotEntityWorldAABB(nitmodBotHandle_t handle, vec3_t mins, vec3_t maxs) {
    gentity_t *selected = G_NITMOD_BotBoundsEntity(handle);
    int component;
    qboolean replace;
    vec3_t position = {0, 0, 0};
    if(!selected || !mins || !maxs) return 3;
    VectorCopy(selected->r.absmin, mins);
    VectorCopy(selected->r.absmax, maxs);
    if(selected->client) {
        mins[2] += 2.0f;
        maxs[2] += 2.0f;
    }
    if(selected->nitmodClassnameHash != 0x1908e) return 0;
    replace = VectorCompare(mins, vec3_origin) && VectorCompare(maxs, vec3_origin);
    for(component = 0; component < 3; ++component)
        if(selected->r.currentOrigin[component] < mins[component] ||
           selected->r.currentOrigin[component] > maxs[component]) replace = qtrue;
    if(replace) {
        /* Original tests SELECTED bounds but positions the replacement via
         * the ORIGINAL handle. It ignores that virtual query's return code. */
        G_NITMOD_BotEntityPosition(handle, position);
        for(component = 0; component < 3; ++component) {
            mins[component] = position[component] - 8.0f;
            maxs[component] = position[component] + (component == 2 ? 48.0f : 8.0f);
        }
    }
    return 0;
}

void G_NITMOD_SetTeamItemClassnameHash(gentity_t *entity, const gitem_t *item) {
    if(!entity || !item || item->giType != IT_TEAM) return;
    /* Original item table: type 5/tag 5 = red, type 5/tag 6 = blue.
     * ET 2.60 enums differ; preserve untouched cache for all other items. */
    if(item->giTag == PW_REDFLAG) entity->nitmodClassnameHash = 0x3317f;
    else if(item->giTag == PW_BLUEFLAG) entity->nitmodClassnameHash = 0x36af1;
}

void G_NITMOD_RefreshClassnameHash(gentity_t *entity) {
    if(!entity) return;
    entity->nitmodClassnameHash = entity->classname && entity->classname[0] ?
        (int)BG_StringHashValue(entity->classname) : -1;
}

int G_NITMOD_BotEntityLocalAABB(nitmodBotHandle_t handle, vec3_t mins, vec3_t maxs) {
    gentity_t *selected = G_NITMOD_BotBoundsEntity(handle);
    if(!selected) return 3;
    return G_NITMOD_BotLocalBounds(selected, selected->nitmodClassnameHash, mins, maxs);
}

gentity_t *G_NITMOD_BotBoundsEntity(nitmodBotHandle_t handle) {
    gentity_t *entity = G_NITMOD_BotResolveEntity(handle);
    gentity_t *axis, *allies, *objective;
    if(!entity || !entity->inuse) return NULL;
    if(entity->s.eType != ET_CONSTRUCTIBLE) return entity;
    objective = entity->parent ? entity->parent : entity;
    axis = G_ConstructionForTeam(objective, TEAM_AXIS);
    allies = G_ConstructionForTeam(objective, TEAM_ALLIES);
    return axis ? axis : (allies ? allies : entity);
}

int G_NITMOD_BotLocalBounds(const gentity_t *selected, int cachedClassHash,
                          vec3_t mins, vec3_t maxs) {
    /* Internal stage: caller supplies the ORIGINAL cached class hash, not
     * a freshly computed classname. Map-spawn lifecycle is connected; other
     * original dynamic item/script write paths still require reconstruction.
     * The original does not recheck selected construction's inuse flag. */
    if(!selected || !mins || !maxs) return 3;
    VectorCopy(selected->r.mins, mins);
    VectorCopy(selected->r.maxs, maxs);
    if(cachedClassHash == 0x1908e &&
       VectorCompare(mins, vec3_origin) && VectorCompare(maxs, vec3_origin)) {
        VectorSet(mins, -8, -8, -8);
        VectorSet(maxs, 8, 8, 48);
    }
    return 0;
}

int G_NITMOD_BotEntityWorldOBB(nitmodBotHandle_t handle, vec3_t center,
    vec3_t axis0, vec3_t axis1, vec3_t axis2, vec3_t halfExtents) {
    gentity_t *entity = G_NITMOD_BotResolveEntity(handle);
    vec3_t axis[3];
    double localCenter[3];
    int component;
    /* Slot 22 has NO extra inuse/client check. In particular unused world
     * remains accepted through EntityFromHandle's world exception. */
    if(!entity || !center || !axis0 || !axis1 || !axis2 || !halfExtents) return 3;
    AnglesToAxis(entity->r.currentAngles, axis);
    for(component = 0; component < 3; ++component)
        localCenter[component] = ((double)entity->r.maxs[component] + entity->r.mins[component]) * 0.5;
    for(component = 0; component < 3; ++component)
        center[component] = (float)(entity->r.currentOrigin[component] +
            axis[0][component] * localCenter[0] + axis[1][component] * localCenter[1] +
            axis[2][component] * localCenter[2]);
    VectorCopy(axis[0], axis0);
    VectorCopy(axis[1], axis1);
    VectorCopy(axis[2], axis2);
    for(component = 0; component < 3; ++component)
        halfExtents[component] = (float)(((double)entity->r.maxs[component] - entity->r.mins[component]) * 0.5);
    return 0;
}

int G_NITMOD_BotEntityEyePosition(nitmodBotHandle_t handle, vec3_t position) {
    gentity_t *entity;
    if(G_NITMOD_BotEntityPosition(handle, position) != 0) return 3;
    entity = G_NITMOD_BotResolveEntity(handle);
    if(entity && entity->client)
        position[2] = (float)((double)position[2] + entity->client->ps.viewheight);
    return 0;
}

int G_NITMOD_BotEntityBonePosition(nitmodBotHandle_t handle, int bone, vec3_t position) {
    /* Original slot 16 ignores bone and delegates to GetEntityPosition. */
    (void)bone;
    return G_NITMOD_BotEntityPosition(handle, position);
}

int G_NITMOD_BotEntityOrientation(nitmodBotHandle_t handle, vec3_t forward,
                                vec3_t right, vec3_t up) {
    gentity_t *entity = G_NITMOD_BotResolveEntity(handle);
    if(!entity || !entity->inuse) return 3;
    /* Original slot 17 delegates optional outputs to AngleVectors. Right
     * is its right vector, not the negated axis[1] used by AnglesToAxis. */
    AngleVectors(entity->client ? entity->client->ps.viewangles : entity->r.currentAngles,
                 forward, right, up);
    return 0;
}

int G_NITMOD_BotEntityVelocity(nitmodBotHandle_t handle, vec3_t velocity) {
    gentity_t *entity = G_NITMOD_BotResolveEntity(handle);
    int component;
    if(!entity || !entity->inuse || !velocity) return 3;
    /* Original slot 18 tests client pointer AND physical client slot, not
     * s.number or level.maxclients. Movers outside that exception use the
     * saved pre-run origin with a fixed factor, not instantVelocity/msec. */
    if((entity->client && NITMOD_BotHandleIndex(handle) < MAX_CLIENTS) ||
       entity->s.eType != ET_MOVER) {
        VectorCopy(entity->s.pos.trDelta, velocity);
    } else {
        for(component = 0; component < 3; ++component)
            velocity[component] = (float)(((double)entity->r.currentOrigin[component] -
                entity->oldOrigin[component]) * 50.0);
    }
    return 0;
}

int G_NITMOD_BotEntityPosition(nitmodBotHandle_t handle, vec3_t position) {
    gentity_t *entity = G_NITMOD_BotResolveEntity(handle);
    vec3_t axis[3];
    double center[3];
    int component;
    /* ETInterface slot 19, original ELF 0x223ec0: success 0, invalid 3.
     * Even the world-handle exception must pass this additional inuse check.
     * A null output is rejected defensively, without modifying the entity. */
    if(!entity || !entity->inuse || !position) return 3;
    if(entity->client) {
        VectorCopy(entity->r.currentOrigin, position);
        return 0;
    }
    AnglesToAxis(entity->r.currentAngles, axis);
    for(component = 0; component < 3; ++component)
        center[component] = ((double)entity->r.maxs[component] + entity->r.mins[component]) * 0.5;
    for(component = 0; component < 3; ++component)
        position[component] = (float)(entity->r.currentOrigin[component] +
            axis[0][component] * center[0] + axis[1][component] * center[1] +
            axis[2][component] * center[2]);
    return 0;
}

int G_NITMOD_BotGameTime(void) {
    return level.time;
}
nitmodBotHandle_t G_NITMOD_BotEntityFromID(int index) {
    if(index < 0 || index >= MAX_GENTITIES || index >= NITMOD_BOT_ENTITY_COUNT)
        return NITMOD_BOT_INVALID_HANDLE;
    /* Unlike raw handle packing, original INDEXENT rejects unused slots. */
    if(index != ENTITYNUM_WORLD && !g_entities[index].inuse)
        return NITMOD_BOT_INVALID_HANDLE;
    return G_NITMOD_BotEntityHandle(index);
}
int G_NITMOD_BotIDFromEntity(nitmodBotHandle_t handle) {
    if(!G_NITMOD_BotResolveEntity(handle)) return -1;
    return NITMOD_BotHandleIndex(handle);
}
qboolean G_NITMOD_BotEntityExists(nitmodBotHandle_t handle) {
    return G_NITMOD_BotResolveEntity(handle) != NULL;
}

void G_NITMOD_ResetBotHandles(void) {
    NITMOD_BotInitHandles(botHandles);
}
nitmodBotHandle_t G_NITMOD_BotEntityHandle(int index) {
    if(index < 0 || index >= MAX_GENTITIES || index >= NITMOD_BOT_ENTITY_COUNT)
        return NITMOD_BOT_INVALID_HANDLE;
    return NITMOD_BotPackHandle(index, botHandles[index].serial);
}
gentity_t *G_NITMOD_BotResolveEntity(nitmodBotHandle_t handle) {
    int index = NITMOD_BotHandleIndex(handle);
    if(index < 0 || index >= MAX_GENTITIES) return NULL;
    if(index == ENTITYNUM_WORLD || (g_entities[index].inuse &&
       botHandles[index].serial == NITMOD_BotHandleSerial(handle))) return &g_entities[index];
    return NULL;
}
void G_NITMOD_BotEntityDeleted(gentity_t *entity) {
    int index;
    if(!entity) return;
    /* Equality avoids undefined subtraction of a foreign pointer. Do not
     * trust s.number, which callbacks and temporary entities may overwrite. */
    for(index = 0; index < MAX_GENTITIES && index < NITMOD_BOT_ENTITY_COUNT; ++index) {
        if(entity == &g_entities[index]) {
            /* Future loaded-interface event must precede this mutation and
             * carry the OLD handle. No event delivery is claimed today. */
            NITMOD_BotAdvanceHandle(botHandles, index);
            return;
        }
    }
}
