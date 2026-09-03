/* Full qagame link: real G_Damage and production handlers, no map/engine. */
#include "g_local.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include "check_doublejump.h"
#include "g_nitmod_entities.h"
extern void dllEntry(int (QDECL *callback)(int, ...));
extern void LandMineTrigger(gentity_t *self);
extern void LandMinePostTrigger(gentity_t *self);
extern void LandminePostThink(gentity_t *self);
extern void G_LandmineThink(gentity_t *self);
extern qboolean etpro_ScriptAction_SetValues(gentity_t *ent, char *params);
extern void target_script_trigger_use(gentity_t *ent, gentity_t *other, gentity_t *activator);
extern qboolean G_ScriptAction_TagConnect(gentity_t *ent, char *params);
extern qboolean G_ScriptAction_Accum(gentity_t *ent, char *params);
extern qboolean G_ScriptAction_Trigger(gentity_t *ent, char *params);
static int accumRecipients[4], accumCalls, accumYieldSelf;
static qboolean ObserveAccumTrigger(gentity_t *ent, char *params) {
    if(accumCalls >= 4 || strcmp(params, "accum_action")) exit(2);
    accumRecipients[accumCalls++] = ent->s.number;
    return ent == &g_entities[0] && accumYieldSelf ? qfalse : qtrue;
}
static int tagFixture, tagReads, tagWrites;
static char tagExpected[MAX_STRING_CHARS];
extern g_script_event_define_t gScriptEvents[];
static gentity_t *expectedTriggerRecipient;
static int triggerScriptCalls, triggerUseCalls;
static qboolean ObserveTriggerScript(gentity_t *ent, char *params) {
    if(ent != expectedTriggerRecipient || strcmp(params, "action_payload") ||
       triggerScriptCalls++ || triggerUseCalls) exit(2);
    return qtrue;
}
static void ObserveTriggerUse(gentity_t *ent, gentity_t *other, gentity_t *activator) {
    if(ent != &g_entities[3] || other != &g_entities[0] || activator != &g_entities[4] ||
       triggerUseCalls++ || triggerScriptCalls != (expectedTriggerRecipient != NULL)) exit(2);
}
static gentity_t *scriptSetTarget;
static int scriptSetLinks, scriptSetHash;
static int mineQueryActive, mineQueryCalls, mineQueryFallback;
static gentity_t *freeTarget;
static int freeCallbackCalls, freeUnlinks;
static nitmodBotHandle_t freedHandle;
static void ObserveFree(gentity_t *entity) {
    if(entity != freeTarget || freeCallbackCalls || freeUnlinks || !entity->inuse) exit(2);
    if(G_NITMOD_BotResolveEntity(freedHandle) ||
       NITMOD_BotHandleSerial(G_NITMOD_BotEntityHandle(MAX_CLIENTS)) != 2) exit(2);
    ++freeCallbackCalls;
}
static gentity_t *triggerLink;
static gentity_t triggerExpected;
static int triggerLinks;
static gentity_t *expectedLink;
static gentity_t *expectedShake;
static int linkCalls, shakeCalls;
static int traceCalls, boxCalls, expectedBoxes;
static int victimMode, blockedSight, chainMode, victimTraces, painCalls;
#define VICTIM_BASE (MAX_CLIENTS + 2 + BODY_QUEUE_SIZE)
static void VictimPain(gentity_t *self, gentity_t *attacker, int damage, vec3_t point) {
    if(self != &g_entities[VICTIM_BASE] || attacker != expectedLink->parent ||
       damage != 75 || self->health != 125 || painCalls ||
       !VectorCompare(point, expectedLink->r.currentOrigin)) exit(2);
    ++painCalls;
}
static int classTest, classWar;
static int dragTest, dragTraces;
static int kickTest, kickQueries;
static int packTest, packLinks;
static int inactivityTest, inactivityWarnings, inactivityDrops, inactivityPrivate;
extern qboolean ClientInactivityTimer(gclient_t *client);
static int QDECL EngineCallback(int command, ...) {
    if(kickTest && command == G_ENTITIES_IN_BOX) {
        va_list args;
        const float *mins, *maxs;
        int *entities;
        va_start(args, command);
        mins = va_arg(args, const float *); maxs = va_arg(args, const float *);
        entities = va_arg(args, int *);
        if(va_arg(args, int) != MAX_GENTITIES || fabs(mins[0] + 8) > .01 ||
           fabs(maxs[0] - 56) > .01 || mins[2] != -24 || maxs[2] != 8) exit(2);
        entities[0] = MAX_CLIENTS;
        ++kickQueries;
        va_end(args); return 1;
    }
    if(dragTest && command == G_TRACE) {
        va_list args;
        trace_t *trace;
        va_start(args, command);
        trace = va_arg(args, trace_t *);
        va_arg(args, const float *); va_arg(args, const float *);
        va_arg(args, const float *); va_arg(args, const float *);
        if(va_arg(args, int) != 2 || va_arg(args, int) != CONTENTS_CORPSE) exit(2);
        memset(trace, 0, sizeof(*trace));
        trace->entityNum = 7;
        ++dragTraces;
        va_end(args); return 0;
    }
    if(inactivityTest && command == G_CVAR_VARIABLE_INTEGER_VALUE) return inactivityPrivate;
    if(inactivityTest && command == G_SEND_SERVER_COMMAND) {
        va_list args; const char *message;
        va_start(args, command);
        if(va_arg(args, int) != 3) exit(2);
        message = va_arg(args, const char *);
        if(!strstr(message, "30 seconds until disconnect")) exit(2);
        ++inactivityWarnings; va_end(args); return 0;
    }
    if(inactivityTest && command == G_DROP_CLIENT) {
        va_list args;
        va_start(args, command);
        if(va_arg(args, int) != 3 || strcmp(va_arg(args, const char *), "Dropped due to inactivity") || va_arg(args, int) != 0) exit(2);
        ++inactivityDrops; va_end(args); return 0;
    }
    if(packTest && command == G_CVAR_VARIABLE_INTEGER_VALUE) return 0;
    if(packTest && command == G_TRACE) {
        va_list args;
        trace_t *trace;
        const float *end;
        va_start(args, command); trace = va_arg(args, trace_t *);
        va_arg(args, const float *); va_arg(args, const float *); va_arg(args, const float *);
        end = va_arg(args, const float *);
        memset(trace, 0, sizeof(*trace)); trace->fraction = 1; VectorCopy(end, trace->endpos);
        va_end(args); return 0;
    }
    if(packTest && command == G_LINKENTITY) { ++packLinks; return 0; }
    if(classTest && command == G_CVAR_VARIABLE_INTEGER_VALUE) {
        va_list args;
        va_start(args, command);
        if(strcmp(va_arg(args, const char *), "g_war")) exit(2);
        va_end(args); return classWar;
    }
    if(tagFixture && command == G_GET_CONFIGSTRING) {
        va_list args;
        int index, size;
        char *value;
        va_start(args, command); index = va_arg(args, int); value = va_arg(args, char *);
        size = va_arg(args, int); va_end(args);
        if(index != CS_TAGCONNECTS + 1 || size < 1 || tagReads++) exit(2);
        value[0] = '\0';
        return 0;
    }
    if(tagFixture && command == G_SET_CONFIGSTRING) {
        va_list args;
        int index;
        const char *value;
        va_start(args, command); index = va_arg(args, int); value = va_arg(args, const char *); va_end(args);
        if(index != CS_TAGCONNECTS + 1 || strcmp(value, tagExpected) || tagWrites++ || tagReads != 1) exit(2);
        return 0;
    }
    if(command == G_LINKENTITY && scriptSetTarget) {
        va_list args;
        gentity_t *entity;
        va_start(args, command); entity = va_arg(args, gentity_t *); va_end(args);
        if(entity != scriptSetTarget || entity->nitmodClassnameHash != scriptSetHash ||
           ++scriptSetLinks > 2) exit(2);
        entity->r.linked = qtrue;
        return 0;
    }
    if(command == G_UNLINKENTITY && freeTarget) {
        va_list args;
        gentity_t *entity;
        va_start(args, command); entity = va_arg(args, gentity_t *); va_end(args);
        if(entity != freeTarget || freeUnlinks || !entity->inuse ||
           (entity->free && freeCallbackCalls != 1)) exit(2);
        if(G_NITMOD_BotResolveEntity(freedHandle)) exit(2);
        ++freeUnlinks;
        return 0;
    }
    if(command == G_ENTITIES_IN_BOX && mineQueryActive) {
        va_list args;
        const float *mins, *maxs;
        int *list, capacity, axis;
        va_start(args, command);
        mins = va_arg(args, const float *); maxs = va_arg(args, const float *);
        list = va_arg(args, int *); capacity = va_arg(args, int);
        va_end(args);
        if(mineQueryCalls || !list || capacity != MAX_GENTITIES) exit(2);
        for(axis = 0; axis < 3; ++axis)
            if(mins[axis] != -64 || maxs[axis] != 64) exit(2);
        ++mineQueryCalls; list[0] = 1; list[1] = 2;
        return mineQueryFallback ? 2 : 1;
    }
    if(command == G_LINKENTITY && triggerLink) {
        va_list args;
        gentity_t *entity;
        va_start(args, command); entity = va_arg(args, gentity_t *); va_end(args);
        if(entity != triggerLink || triggerLinks ||
           memcmp(entity, &triggerExpected, sizeof(*entity))) exit(2);
        ++triggerLinks;
        return 0;
    }
    if(command == G_TRACE && expectedLink && expectedLink->splashDamage) {
        va_list args;
        trace_t *result;
        const float *start, *mins, *maxs, *end;
        int pass, mask;
        va_start(args, command);
        result = va_arg(args, trace_t *);
        start = va_arg(args, const float *); mins = va_arg(args, const float *);
        maxs = va_arg(args, const float *); end = va_arg(args, const float *);
        pass = va_arg(args, int); mask = va_arg(args, int);
        va_end(args);
        if(!result || linkCalls ||
           !VectorCompare(start, expectedLink->r.currentOrigin) ||
           !VectorCompare(mins, vec3_origin) ||
           !VectorCompare(maxs, vec3_origin) || pass != ENTITYNUM_NONE) exit(2);
        if(mask == MASK_SHOT) {
            if(traceCalls || boxCalls || !VectorCompare(start, end)) exit(2);
            ++traceCalls;
        } else {
            static const int offsets[10][3] = {
                {0,0,0}, {16,16,16}, {16,-16,16}, {-16,16,16}, {-16,-16,16},
                {16,16,-16}, {16,-16,-16}, {-16,16,-16}, {-16,-16,-16}, {0,0,0}
            };
            int axis;
            if(!victimMode || traceCalls != 1 || boxCalls != expectedBoxes ||
               victimTraces >= (blockedSight ? 10 : 1) ||
               mask != (victimTraces == 9 ? MASK_SOLID : (CONTENTS_SOLID | CONTENTS_BODY))) exit(2);
            for(axis = 0; axis < 3; ++axis)
                if(end[axis] != g_entities[VICTIM_BASE].r.currentOrigin[axis] + offsets[victimTraces][axis]) exit(2);
            ++victimTraces;
        }
        memset(result, 0, sizeof(*result));
        result->fraction = blockedSight && mask != MASK_SHOT ? 0.5f : 1.0f;
        result->entityNum = blockedSight && mask != MASK_SHOT ? ENTITYNUM_WORLD : ENTITYNUM_NONE;
        VectorCopy(end, result->endpos);
        return 0;
    }
    if(command == G_ENTITIES_IN_BOX && expectedLink && expectedLink->splashDamage) {
        va_list args;
        const float *mins, *maxs;
        int *entities, capacity, i;
        float boxradius = (float)(1.41421356 * expectedLink->splashRadius);
        va_start(args, command);
        mins = va_arg(args, const float *); maxs = va_arg(args, const float *);
        entities = va_arg(args, int *); capacity = va_arg(args, int);
        va_end(args);
        if(traceCalls != 1 || linkCalls || boxCalls >= expectedBoxes ||
           !entities || capacity != MAX_GENTITIES) exit(2);
        for(i = 0; i < 3; ++i) {
            if(fabs(mins[i] - (expectedLink->r.currentOrigin[i] - boxradius)) > 0.001 ||
               fabs(maxs[i] - (expectedLink->r.currentOrigin[i] + boxradius)) > 0.001) exit(2);
        }
        /* Satchel's second pass temporarily excludes players and corpses. */
        if(g_entities[1].r.linked != (boxCalls == 0)) exit(2);
        for(i = 0; i < BODY_QUEUE_SIZE; ++i)
            if(level.bodyQue[i]->r.linked != (boxCalls == 0)) exit(2);
        /* The non-client victim must remain untouched in satchel's client pass. */
        if(victimMode && (painCalls || g_entities[VICTIM_BASE].health != (chainMode ? 40 : 200))) exit(2);
        ++boxCalls;
        if(victimMode) {
            entities[0] = expectedLink->s.number; /* explicitly ignored source */
            for(i = 0; i < 3; ++i) entities[i + 1] = VICTIM_BASE + i;
            return 4;
        }
        return 0;
    }
    if(command == G_LINKENTITY && expectedLink) {
        va_list args;
        gentity_t *entity;
        va_start(args, command); entity = va_arg(args, gentity_t *); va_end(args);
        if(entity == expectedLink) {
            if(linkCalls || boxCalls != expectedBoxes || entity->s.eType != ET_GENERAL ||
               !entity->freeAfterEvent || entity->nextthink != 0) exit(2);
            ++linkCalls;
        } else if(entity == expectedShake) {
            if(linkCalls != 1 || shakeCalls || entity->s.eType != ET_EVENTS + EV_SHAKE ||
               !entity->inuse || !entity->freeAfterEvent || entity->eventTime != level.time ||
               entity->r.eventTime != level.time) exit(2);
            ++shakeCalls;
        } else exit(2);
        return 0;
    }
    fprintf(stderr, "Unexpected engine syscall %d\n", command);
    exit(2);
    return 0;
}
static void NormalThink(gentity_t *entity) { (void)entity; }
static gclient_t ownerClient;
static int CheckNamedHashTrigger(void) {
    gentity_t saved[4];
    g_script_event_t event;
    g_script_stack_action_t action = {"observe_accum", ObserveAccumTrigger, 0};
    vmCvar_t debug = g_scriptDebug;
    int count = level.num_entities, index, self, yielding, unused, bots, errors = 0;
    memcpy(saved, g_entities, sizeof(saved));
    G_Script_EventStringInit();
    memset(&event, 0, sizeof(event));
    for(index = 0; gScriptEvents[index].eventStr; ++index)
        if(!strcmp(gScriptEvents[index].eventStr, "trigger")) break;
    if(!gScriptEvents[index].eventStr) return 1;
    event.eventNum = index; event.params = "payload";
    event.stack.numItems = 1; event.stack.items[0].action = &action;
    event.stack.items[0].params = "accum_action";
    level.num_entities = 4; g_scriptDebug.integer = 0;
    for(self = 0; self < 2; ++self)
    for(yielding = 0; yielding < 2; ++yielding)
    for(unused = 0; unused < 2; ++unused)
    for(bots = 0; bots < 4; ++bots) {
        int expectedCalls = 0;
        memset(g_entities, 0, sizeof(saved));
        for(index = 0; index < 4; ++index) {
            gentity_t *entity = &g_entities[index];
            entity->s.number = index; entity->inuse = qtrue;
            entity->scriptEvents = &event; entity->numScriptEvents = 1;
            entity->scriptStatus.scriptId = 100;
            entity->scriptStatus.scriptEventIndex = -1;
            entity->scriptName = index == 3 ? "requested" : "different_string";
            entity->nitmodScriptNameHash = index == 3 || (index == 0 && !self) ?
                -1 : (int)BG_StringHashValue("requested");
            entity->r.svFlags = ((index == 0 && (bots & 1)) || (index > 0 && (bots & 2))) ? SVF_BOT : 0;
        }
        g_entities[1].inuse = !unused;
        accumCalls = 0; accumYieldSelf = yielding;
        if(G_ScriptAction_Trigger(&g_entities[0], "requested payload") !=
           (self && yielding && !(bots & 1) ? qfalse : qtrue)) ++errors;
        for(index = 0; index < 3; ++index) {
            if((index == 0 && !self) || !g_entities[index].inuse ||
               (g_entities[index].r.svFlags & SVF_BOT)) continue;
            if(expectedCalls >= accumCalls || accumRecipients[expectedCalls] != index) ++errors;
            ++expectedCalls;
        }
        if(accumCalls != expectedCalls || g_entities[0].scriptStatus.scriptId !=
           (self && yielding && !(bots & 1) ? 101 : 100)) ++errors;
    }
    memcpy(g_entities, saved, sizeof(saved));
    level.num_entities = count; g_scriptDebug = debug;
    return errors;
}
static int CheckAccumHashTrigger(void) {
    gentity_t saved[4];
    g_script_event_t event;
    g_script_stack_action_t action = {"observe_accum", ObserveAccumTrigger, 0};
    vmCvar_t debug = g_scriptDebug;
    int count = level.num_entities, index, equal, self, yielding, unused, global, errors = 0;
    int savedGlobal = level.globalAccumBuffer[0];
    memcpy(saved, g_entities, sizeof(saved));
    G_Script_EventStringInit();
    memset(&event, 0, sizeof(event));
    for(index = 0; gScriptEvents[index].eventStr; ++index)
        if(!strcmp(gScriptEvents[index].eventStr, "trigger")) break;
    if(!gScriptEvents[index].eventStr) return 1;
    event.eventNum = index; event.params = "payload";
    event.stack.numItems = 1; event.stack.items[0].action = &action;
    event.stack.items[0].params = "accum_action";
    level.num_entities = 4; g_scriptDebug.integer = 0;
    for(global = 0; global < 2; ++global)
    for(equal = 0; equal < 2; ++equal)
    for(self = 0; self < 2; ++self)
    for(yielding = 0; yielding < 2; ++yielding)
    for(unused = 0; unused < 2; ++unused) {
        int expectedCalls = 0;
        memset(g_entities, 0, sizeof(saved));
        for(index = 0; index < 4; ++index) {
            g_entities[index].s.number = index;
            g_entities[index].inuse = qtrue;
            g_entities[index].scriptEvents = &event;
            g_entities[index].numScriptEvents = 1;
            g_entities[index].scriptStatus.scriptId = 100;
            g_entities[index].scriptStatus.scriptEventIndex = -1;
            g_entities[index].scriptName = index == 3 ? "requested" : "different_string";
            g_entities[index].nitmodScriptNameHash = index == 3 || (index == 0 && !self) ?
                -1 : (int)BG_StringHashValue("requested");
        }
        g_entities[1].inuse = !unused;
        g_entities[0].scriptAccumBuffer[0] = global ? 42 : (equal ? 7 : 6);
        level.globalAccumBuffer[0] = global ? (equal ? 7 : 6) : 42;
        accumCalls = 0; accumYieldSelf = yielding;
        if((global ? G_ScriptAction_GlobalAccum(&g_entities[0], "0 trigger_if_equal 7 requested payload") :
                     G_ScriptAction_Accum(&g_entities[0], "0 trigger_if_equal 7 requested payload")) !=
           (equal && self && yielding ? qfalse : qtrue)) ++errors;
        if(equal) {
            for(index = 0; index < 3; ++index) {
                if((index == 0 && !self) || (index == 1 && unused)) continue;
                if(expectedCalls >= accumCalls || accumRecipients[expectedCalls] != index) ++errors;
                ++expectedCalls;
            }
        }
        if(accumCalls != expectedCalls || g_entities[0].scriptAccumBuffer[0] != (global ? 42 : (equal ? 7 : 6)) ||
           level.globalAccumBuffer[0] != (global ? (equal ? 7 : 6) : 42) ||
           g_entities[0].scriptStatus.scriptId != (equal && self && yielding ? 101 : 100)) ++errors;
    }
    memcpy(g_entities, saved, sizeof(saved));
    level.num_entities = count; g_scriptDebug = debug;
    level.globalAccumBuffer[0] = savedGlobal;
    return errors;
}
static int CheckTagConnectHashLookup(void) {
    gentity_t saved[4];
    int count = level.num_entities, time = level.time, mode, client, errors = 0;
    gclient_t savedClient = ownerClient;
    memcpy(saved, g_entities, sizeof(saved));
    level.num_entities = 4; level.time = 3210;
    for(mode = 0; mode < 4; ++mode)
    for(client = 0; client < 2; ++client) {
        gentity_t *entity = &g_entities[0];
        int index, parent = mode == 0 ? 3 : mode == 2 ? 1 : 2;
        memset(g_entities, 0, sizeof(saved));
        memset(&ownerClient, 0, sizeof(ownerClient));
        for(index = 0; index < 4; ++index) {
            g_entities[index].inuse = qtrue;
            g_entities[index].s.number = index;
        }
        entity->client = client ? &ownerClient : NULL;
        entity->s.eFlags = ownerClient.ps.eFlags = EF_PRONE | EF_PRONE_MOVING;
        VectorSet(entity->s.angles, 1,2,3);
        VectorSet(entity->r.currentAngles, 4,5,6);
        VectorSet(entity->s.apos.trBase, 7,8,9);
        VectorSet(entity->s.apos.trDelta, 10,11,12);
        entity->s.apos.trDuration = 77;
        g_entities[1].scriptName = "requested";
        g_entities[1].nitmodScriptNameHash = mode >= 2 ? (int)BG_StringHashValue("requested") : -1;
        g_entities[2].scriptName = "not_requested";
        g_entities[2].nitmodScriptNameHash = (int)BG_StringHashValue("requested");
        if(mode == 3) g_entities[1].inuse = qfalse;
        if(mode == 0) {
            g_entities[3].targetname = "requested";
            g_entities[3].targetnamehash = (int)BG_StringHashValue("requested");
        }
        Com_sprintf(tagExpected, sizeof(tagExpected), "0 %i tag_head", parent);
        tagFixture = 1; tagReads = tagWrites = 0;
        if(G_ScriptAction_TagConnect(entity, "requested tag_head") != qtrue ||
           entity->tagParent != &g_entities[parent] || strcmp(entity->tagName, "tag_head") ||
           tagReads != 1 || tagWrites != 1 || !(entity->s.eFlags & EF_TAGCONNECT) ||
           entity->s.apos.trTime != level.time || entity->s.apos.trDuration ||
           entity->s.apos.trType != TR_STATIONARY || !VectorCompare(entity->s.angles, vec3_origin) ||
           !VectorCompare(entity->r.currentAngles, vec3_origin) ||
           !VectorCompare(entity->s.apos.trBase, vec3_origin) ||
           !VectorCompare(entity->s.apos.trDelta, vec3_origin)) ++errors;
        if(client && (!(ownerClient.ps.eFlags & EF_TAGCONNECT) ||
           ((ownerClient.ps.eFlags | entity->s.eFlags) & (EF_PRONE | EF_PRONE_MOVING)))) ++errors;
        tagFixture = 0;
    }
    memcpy(g_entities, saved, sizeof(saved));
    ownerClient = savedClient; level.num_entities = count; level.time = time;
    return errors;
}
static int CheckScriptTriggerHashLookup(void) {
    gentity_t saved[5];
    g_script_event_t event;
    g_script_stack_action_t action = {"observe", ObserveTriggerScript, 0};
    int count = level.num_entities, mode, selfScript, index, errors = 0;
    vmCvar_t debug = g_scriptDebug;
    memcpy(saved, g_entities, sizeof(saved));
    g_scriptDebug.integer = 0;
    G_Script_EventStringInit();
    memset(&event, 0, sizeof(event));
    for(index = 0; gScriptEvents[index].eventStr; ++index)
        if(!strcmp(gScriptEvents[index].eventStr, "trigger")) break;
    if(!gScriptEvents[index].eventStr) {
        g_scriptDebug = debug;
        return 1;
    }
    event.eventNum = index; event.params = "payload";
    event.stack.numItems = 1; event.stack.items[0].action = &action;
    event.stack.items[0].params = "action_payload";
    level.num_entities = 5;
    for(mode = 0; mode < 5; ++mode)
    for(selfScript = 0; selfScript < 2; ++selfScript) {
        memset(g_entities, 0, sizeof(saved));
        for(index = 0; index < 5; ++index) g_entities[index].inuse = qtrue;
        for(index = 0; index < 3; ++index) {
            g_entities[index].scriptEvents = &event;
            g_entities[index].numScriptEvents = 1;
        }
        g_entities[0].aiName = mode == 0 ? NULL : "requested";
        g_entities[0].scriptName = selfScript ? "own_script" : NULL;
        g_entities[0].target = "payload";
        g_entities[1].scriptName = "requested"; /* String alone must not match. */
        g_entities[1].nitmodScriptNameHash = -1;
        g_entities[2].scriptName = "different_string";
        g_entities[2].nitmodScriptNameHash = mode >= 2 ? (int)BG_StringHashValue("requested") : -1;
        if(mode >= 3) g_entities[1].nitmodScriptNameHash = (int)BG_StringHashValue("requested");
        if(mode == 4) g_entities[1].inuse = qfalse;
        g_entities[3].targetname = "payload";
        g_entities[3].targetnamehash = (int)BG_StringHashValue("payload");
        g_entities[3].use = ObserveTriggerUse;
        expectedTriggerRecipient = mode < 2 ? (selfScript ? &g_entities[0] : NULL) :
            &g_entities[mode == 3 ? 1 : 2];
        triggerScriptCalls = triggerUseCalls = 0;
        target_script_trigger_use(&g_entities[0], &g_entities[4], &g_entities[2]);
        if(triggerScriptCalls != (expectedTriggerRecipient != NULL) || triggerUseCalls != 1) ++errors;
    }
    memcpy(g_entities, saved, sizeof(saved));
    level.num_entities = count; g_scriptDebug = debug;
    expectedTriggerRecipient = NULL;
    return errors;
}
static int CheckCachedNameSearch(void) {
    static gentity_t saved[MAX_GENTITIES];
    static const int hashes[] = {0, -1, 12345};
    gentity_t foreign;
    int savedCount = level.num_entities;
    int index, kind, sample, errors = 0;
    memcpy(saved, g_entities, sizeof(saved));
    memset(g_entities, 0, sizeof(saved));
    for(kind = 0; kind < 2; ++kind) {
        gentity_t *(*find)(gentity_t *, int) = kind ? G_NITMOD_FindByScriptNameHash : G_NITMOD_FindByClassNameHash;
        for(sample = 0; sample < 3; ++sample)
        for(index = 0; index < MAX_GENTITIES; ++index) {
            gentity_t *entity = &g_entities[index];
            entity->inuse = qtrue;
            entity->classname = entity->scriptName = "unrelated_string";
            entity->nitmodClassnameHash = kind ? 9876 : hashes[sample];
            entity->nitmodScriptNameHash = kind ? hashes[sample] : 9876;
            level.num_entities = index + 1;
            if(find(NULL, hashes[sample]) != entity ||
               find(index ? &g_entities[index - 1] : NULL, hashes[sample]) != entity ||
               find(entity, hashes[sample]) || find(NULL, 4567)) ++errors;
            level.num_entities = index;
            if(find(NULL, hashes[sample])) ++errors;
            entity->inuse = qfalse;
            level.num_entities = MAX_GENTITIES;
            if(find(NULL, hashes[sample])) ++errors;
        }
        for(index = 0; index < 3; ++index) {
            g_entities[index].inuse = qtrue;
            g_entities[index].nitmodClassnameHash = -1;
            g_entities[index].nitmodScriptNameHash = -1;
        }
        if(find(NULL, -1) != &g_entities[0] || find(&g_entities[0], -1) != &g_entities[1] ||
           find(&g_entities[1], -1) != &g_entities[2] || find(&foreign, -1) ||
           find(&g_entities[MAX_GENTITIES], -1)) ++errors;
        level.num_entities = -1;
        if(find(NULL, -1)) ++errors;
        level.num_entities = MAX_GENTITIES + 100;
        if(find(&g_entities[MAX_GENTITIES - 1], -1)) ++errors;
        memset(g_entities, 0, sizeof(saved));
    }
    memcpy(g_entities, saved, sizeof(saved));
    level.num_entities = savedCount;
    return errors;
}
static int CheckTargetScriptNameHashes(void) {
    static char *names[] = {NULL, "", "Mixed_Name"};
    static char *classes[] = {NULL, "", "misc_mg42", "script_multiplayer", "SCRIPT_MULTIPLAYER"};
    gentity_t entity, before;
    vmCvar_t savedDebug = g_scriptDebug;
    int target, script, kind, errors = 0;
    for(target = 0; target < 3; ++target)
    for(script = 0; script < 3; ++script)
    for(kind = 0; kind < 5; ++kind) {
        memset(&entity, 0, sizeof(entity));
        entity.target = names[target]; entity.scriptName = names[script];
        entity.classname = classes[kind]; entity.targetnamehash = 987;
        before = entity;
        before.nitmodTargetHash = target < 2 ? -1 : (int)BG_StringHashValue(names[target]);
        before.nitmodScriptNameHash = script < 2 ? -1 :
            (int)BG_StringHashValue(kind >= 3 ? "game_manager" : names[script]);
        G_NITMOD_InitSpawnNameHashes(&entity);
        if(memcmp(&entity, &before, sizeof(entity))) ++errors;
    }
    G_NITMOD_InitSpawnNameHashes(NULL);
    g_scriptDebug.integer = 0;
    memset(&entity, 0, sizeof(entity));
    entity.classname = "script_multiplayer";
    entity.scriptName = "spawn_name";
    G_NITMOD_InitSpawnNameHashes(&entity);
    if(etpro_ScriptAction_SetValues(&entity, "TARGET first SCRIPTNAME changed target second targetname own_name") != qtrue ||
       entity.nitmodTargetHash != BG_StringHashValue("second") ||
       entity.nitmodScriptNameHash != BG_StringHashValue("changed") ||
       entity.targetnamehash != BG_StringHashValue("own_name")) ++errors;
    before = entity;
    if(etpro_ScriptAction_SetValues(&entity, "origin \"3 4 5\"") != qtrue ||
       entity.nitmodTargetHash != before.nitmodTargetHash ||
       entity.nitmodScriptNameHash != before.nitmodScriptNameHash) ++errors;
    g_scriptDebug = savedDebug;
    level.numSpawnVars = level.numSpawnVarChars = 0;
    return errors;
}
static int CheckScriptClassnameCache(void) {
    static const struct {
        char *params, *name;
        int changed, pairs;
    } cases[] = {
        {"classname noclass", "noclass", 0, 1},
        {"classname NOCLASS", "NOCLASS", 0, 1},
        {"classname_nospawn misc_mg42", "misc_mg42", 1, 1},
        {"CLASSNAME_NOSPAWN made_up_class", "made_up_class", 1, 1},
        {"classname_nospawn noclass classname made_up_class", "made_up_class", 1, 2},
        {"classname made_up_class classname_nospawn noclass", "noclass", 1, 2},
        {"classname team_CTF_redflag", "team_CTF_redflag", 1, 1},
        {"origin \"1 2 3\"", "noclass", 0, 1}
    };
    gentity_t entity;
    vmCvar_t savedGametype = g_gametype, savedDebug = g_scriptDebug;
    int sample, linked, errors = 0;
    g_gametype.integer = GT_WOLF_LMS; /* Real flag spawn rejection, still refresh/link. */
    g_scriptDebug.integer = 0;
    for(sample = 0; sample < 8; ++sample)
    for(linked = 0; linked < 2; ++linked) {
        int pair;
        memset(&entity, 0, sizeof(entity));
        entity.inuse = qtrue; entity.classname = "noclass";
        entity.nitmodClassnameHash = 12345; entity.r.linked = linked;
        scriptSetTarget = &entity; scriptSetLinks = 0;
        scriptSetHash = cases[sample].changed ? (int)BG_StringHashValue(cases[sample].name) : 12345;
        if(etpro_ScriptAction_SetValues(&entity, cases[sample].params) != qtrue ||
           strcmp(entity.classname, cases[sample].name) || entity.nitmodClassnameHash != scriptSetHash ||
           scriptSetLinks != (cases[sample].changed ? 2 : linked) ||
           level.numSpawnVars != cases[sample].pairs) ++errors;
        for(pair = 0; pair < level.numSpawnVars; ++pair)
            if(!Q_stricmp(level.spawnVars[pair][0], "classname_nospawn")) ++errors;
        if(sample == 7 && (entity.r.currentOrigin[0] != 1 || entity.r.currentOrigin[1] != 2 ||
                           entity.r.currentOrigin[2] != 3)) ++errors;
        scriptSetTarget = NULL;
    }
    g_gametype = savedGametype; g_scriptDebug = savedDebug;
    level.numSpawnVars = level.numSpawnVarChars = 0;
    return errors;
}
static int CheckBotWorldAABB(void) {
    gentity_t *entity = &g_entities[MAX_CLIENTS];
    gentity_t saved = *entity, target;
    int selection, client, special, mode, component, errors = 0;
    nitmodBotHandle_t handle;
    G_NITMOD_ResetBotHandles();
    handle = G_NITMOD_BotEntityHandle(MAX_CLIENTS);
    for(selection = 0; selection < 2; ++selection)
    for(client = 0; client < 2; ++client)
    for(special = 0; special < 2; ++special)
    for(mode = 0; mode < 9; ++mode) {
        gentity_t *selected;
        gentity_t before, targetBefore;
        vec3_t mins, maxs, expectedMin, expectedMax;
        int replace = special && mode != 0 && mode != 8;
        memset(entity, 0, sizeof(*entity));
        memset(&target, 0, sizeof(target));
        entity->inuse = qtrue;
        VectorSet(entity->r.currentOrigin, 100, 200, 300);
        VectorSet(entity->r.mins, -4,-5,-6);
        VectorSet(entity->r.maxs, 8,11,14);
        VectorSet(entity->r.currentAngles, 0,90,0);
        selected = selection ? &target : entity;
        if(selection) {
            entity->s.eType = ET_CONSTRUCTIBLE;
            entity->target_ent = &target;
            target.s.eType = ET_CONSTRUCTIBLE;
            VectorSet(target.r.currentOrigin, 500,600,700);
        }
        selected->client = client ? &ownerClient : NULL;
        selected->nitmodClassnameHash = special ? 0x1908e : -1;
        for(component = 0; component < 3; ++component) {
            expectedMin[component] = selected->r.currentOrigin[component] - 10;
            expectedMax[component] = selected->r.currentOrigin[component] + 10;
        }
        if(mode == 1) { VectorClear(expectedMin); VectorClear(expectedMax); }
        if(mode >= 2 && mode <= 7) {
            component = (mode - 2) / 2;
            if(mode % 2 == 0) expectedMin[component] = selected->r.currentOrigin[component] + 1;
            else expectedMax[component] = selected->r.currentOrigin[component] - 1;
        }
        if(mode == 8) {
            VectorCopy(selected->r.currentOrigin, expectedMin);
            VectorCopy(selected->r.currentOrigin, expectedMax);
        }
        VectorCopy(expectedMin, selected->r.absmin);
        VectorCopy(expectedMax, selected->r.absmax);
        /* Build bounds that equal the independently expected values AFTER
         * the original client +2 shift, including the zero-box case. */
        if(client) { selected->r.absmin[2] -= 2; selected->r.absmax[2] -= 2; }
        before = *entity; targetBefore = target;
        if(replace) {
            const vec3_t rotated = {-3,2,4};
            for(component = 0; component < 3; ++component) {
                float position = entity->r.currentOrigin[component] +
                    (!selection && client ? 0 : rotated[component]);
                expectedMin[component] = position - 8;
                expectedMax[component] = position + (component == 2 ? 48 : 8);
            }
        }
        if(G_NITMOD_BotEntityWorldAABB(handle, mins, maxs) != 0) ++errors;
        for(component = 0; component < 3; ++component)
            if(fabs(mins[component] - expectedMin[component]) > 0.0001 ||
               fabs(maxs[component] - expectedMax[component]) > 0.0001) ++errors;
        if(memcmp(entity, &before, sizeof(before)) || memcmp(&target, &targetBefore, sizeof(target))) ++errors;
    }
    for(mode = 0; mode < 5; ++mode) {
        vec3_t mins = {99,98,97}, maxs = {96,95,94};
        nitmodBotHandle_t query = handle;
        entity->inuse = mode != 2;
        if(mode == 3) G_NITMOD_BotEntityDeleted(entity);
        if(mode == 4) query = NITMOD_BOT_INVALID_HANDLE;
        if(G_NITMOD_BotEntityWorldAABB(query, mode == 0 ? NULL : mins, mode == 1 ? NULL : maxs) != 3 ||
           mins[0] != 99 || mins[1] != 98 || mins[2] != 97 ||
           maxs[0] != 96 || maxs[1] != 95 || maxs[2] != 94) ++errors;
    }
    *entity = saved;
    G_NITMOD_ResetBotHandles();
    return errors;
}
static int CheckTeamItemClassnameCache(void) {
    static const int seeds[] = {0, -1, 0x1908e};
    gentity_t entity, expected;
    gitem_t item;
    int type, tag, seed, index, errors = 0, flagsSeen = 0;
    vmCvar_t savedGametype = g_gametype;
    for(type = IT_BAD; type <= IT_TEAM; ++type)
    for(tag = -1; tag <= PW_NUM_POWERUPS; ++tag)
    for(seed = 0; seed < 3; ++seed) {
        memset(&entity, 0, sizeof(entity));
        memset(&item, 0, sizeof(item));
        entity.classname = "deliberately_not_a_flag";
        entity.nitmodClassnameHash = seeds[seed];
        item.giType = type; item.giTag = tag;
        expected = entity;
        if(type == IT_TEAM && tag == PW_REDFLAG) expected.nitmodClassnameHash = 0x3317f;
        if(type == IT_TEAM && tag == PW_BLUEFLAG) expected.nitmodClassnameHash = 0x36af1;
        G_NITMOD_SetTeamItemClassnameHash(&entity, &item);
        if(memcmp(&entity, &expected, sizeof(entity))) ++errors;
    }
    G_NITMOD_SetTeamItemClassnameHash(NULL, &item);
    expected = entity;
    G_NITMOD_SetTeamItemClassnameHash(&entity, NULL);
    if(memcmp(&entity, &expected, sizeof(entity))) ++errors;
    /* Real G_CallSpawn writes the cache BEFORE its LMS rejection. */
    g_gametype.integer = GT_WOLF_LMS;
    for(index = 1; bg_itemlist[index].classname; ++index) {
        if(bg_itemlist[index].giType != IT_TEAM) continue;
        memset(&entity, 0, sizeof(entity));
        entity.classname = bg_itemlist[index].classname;
        if(G_CallSpawn(&entity) != qfalse) ++errors;
        if(bg_itemlist[index].giTag == PW_REDFLAG) {
            if(entity.nitmodClassnameHash != 0x3317f) ++errors;
            ++flagsSeen;
        } else if(bg_itemlist[index].giTag == PW_BLUEFLAG) {
            if(entity.nitmodClassnameHash != 0x36af1) ++errors;
            ++flagsSeen;
        }
    }
    if(flagsSeen != 2 || BG_StringHashValue("team_CTF_redflag") != 0x3317f ||
       BG_StringHashValue("team_CTF_blueflag") != 0x36af1) ++errors;
    g_gametype = savedGametype;
    return errors;
}
static int CheckBotClassnameCache(void) {
    static char *names[] = {NULL, "", "misc_mg42", "MISC_MG42", "freed", "noclass"};
    gentity_t *entity = &g_entities[MAX_CLIENTS];
    gentity_t saved = *entity;
    gentity_t target;
    int sample, component, errors = 0;
    nitmodBotHandle_t handle;
    G_NITMOD_ResetBotHandles();
    handle = G_NITMOD_BotEntityHandle(MAX_CLIENTS);
    memset(entity, 0, sizeof(*entity));
    for(sample = 0; sample < 6; ++sample) {
        entity->classname = names[sample];
        G_NITMOD_RefreshClassnameHash(entity);
        if(entity->nitmodClassnameHash != (sample < 2 ? -1 : (int)BG_StringHashValue(names[sample]))) ++errors;
    }
    entity->classname = "misc_mg42";
    G_NITMOD_RefreshClassnameHash(entity);
    G_InitGentity(entity); /* Changes classname to noclass, NOT the cache. */
    if(entity->nitmodClassnameHash != 0x1908e || strcmp(entity->classname, "noclass")) ++errors;
    for(sample = 0; sample < 3; ++sample) {
        vec3_t mins, maxs;
        if(sample == 1) G_NITMOD_RefreshClassnameHash(entity);
        if(sample == 2) {
            memset(&target, 0, sizeof(target));
            target.s.eType = ET_CONSTRUCTIBLE;
            target.nitmodClassnameHash = 0x1908e;
            entity->s.eType = ET_CONSTRUCTIBLE;
            entity->target_ent = &target;
        }
        if(G_NITMOD_BotEntityLocalAABB(handle, mins, maxs) != 0) ++errors;
        for(component = 0; component < 3; ++component)
            if(mins[component] != (sample == 1 ? 0 : -8) ||
               maxs[component] != (sample == 1 ? 0 : component == 2 ? 48 : 8)) ++errors;
    }
    G_NITMOD_RefreshClassnameHash(NULL);
    *entity = saved;
    G_NITMOD_ResetBotHandles();
    return errors;
}
static int CheckBotBoundsStages(void) {
    gentity_t saved = g_entities[MAX_CLIENTS];
    gentity_t *entity = &g_entities[MAX_CLIENTS];
    gentity_t parent, target, chain;
    int flags, withParent, withTarget, withChain, constructible, sample, errors = 0;
    nitmodBotHandle_t handle;
    G_NITMOD_ResetBotHandles();
    handle = G_NITMOD_BotEntityHandle(MAX_CLIENTS);
    if(BG_StringHashValue("misc_mg42") != 0x1908e) ++errors;
    for(flags = 0; flags < 16; ++flags)
    for(withParent = 0; withParent < 2; ++withParent)
    for(withTarget = 0; withTarget < 2; ++withTarget)
    for(withChain = 0; withChain < 2; ++withChain)
    for(constructible = 0; constructible < 2; ++constructible) {
        gentity_t *expected = entity;
        memset(entity, 0, sizeof(*entity));
        memset(&parent, 0, sizeof(parent));
        memset(&target, 0, sizeof(target));
        memset(&chain, 0, sizeof(chain));
        entity->inuse = qtrue;
        entity->s.eType = ET_CONSTRUCTIBLE;
        entity->parent = withParent ? &parent : NULL;
        (withParent ? &parent : entity)->target_ent = withTarget ? &target : NULL;
        target.s.eType = constructible ? ET_CONSTRUCTIBLE : ET_GENERAL;
        target.spawnflags = flags;
        target.chain = withChain ? &chain : NULL;
        /* Selected targets intentionally unused: original does not recheck. */
        if(withTarget && constructible)
            expected = !(flags & 4) && (flags & 8) && withChain ? &chain : &target;
        if(G_NITMOD_BotBoundsEntity(handle) != expected) ++errors;
        entity->s.eType = ET_GENERAL;
        if(G_NITMOD_BotBoundsEntity(handle) != entity) ++errors;
    }
    entity->inuse = qfalse;
    if(G_NITMOD_BotBoundsEntity(handle)) ++errors;
    entity->inuse = qtrue;
    G_NITMOD_BotEntityDeleted(entity);
    if(G_NITMOD_BotBoundsEntity(handle) ||
       G_NITMOD_BotBoundsEntity(NITMOD_BOT_INVALID_HANDLE)) ++errors;
    for(flags = 0; flags < 2; ++flags)
    for(sample = 0; sample < 7; ++sample) {
        vec3_t mins, maxs;
        int component;
        memset(&target, 0, sizeof(target));
        target.classname = flags ? "not_the_cached_class" : "misc_mg42";
        if(sample > 0) {
            if(sample <= 3) target.r.mins[sample - 1] = -1;
            else target.r.maxs[sample - 4] = 1;
        }
        if(G_NITMOD_BotLocalBounds(&target, flags ? 0x1908e : -1, mins, maxs) != 0) ++errors;
        for(component = 0; component < 3; ++component) {
            if(mins[component] != (flags && sample == 0 ? -8 : target.r.mins[component]) ||
               maxs[component] != (flags && sample == 0 ? (component == 2 ? 48 : 8) : target.r.maxs[component])) ++errors;
        }
    }
    {
        vec3_t mins = {99,98,97}, maxs = {96,95,94};
        if(G_NITMOD_BotLocalBounds(NULL, 0, mins, maxs) != 3 ||
           G_NITMOD_BotLocalBounds(&target, 0, NULL, maxs) != 3 ||
           G_NITMOD_BotLocalBounds(&target, 0, mins, NULL) != 3 ||
           mins[0] != 99 || mins[1] != 98 || mins[2] != 97 ||
           maxs[0] != 96 || maxs[1] != 95 || maxs[2] != 94) ++errors;
    }
    *entity = saved;
    G_NITMOD_ResetBotHandles();
    return errors;
}
static int CheckBotWorldOBB(void) {
    static const int slots[] = {0, MAX_CLIENTS, ENTITYNUM_WORLD};
    static const vec3_t angles[] = {{0,0,0}, {0,90,0}, {90,0,0}, {0,0,90}};
    static const vec3_t rotatedCenter[] = {{2,3,4}, {-3,2,4}, {4,3,-2}, {2,-4,3}};
    static const vec3_t axes[4][3] = {
        {{1,0,0}, {0,1,0}, {0,0,1}},
        {{0,1,0}, {-1,0,0}, {0,0,1}},
        {{0,0,-1}, {0,1,0}, {1,0,0}},
        {{1,0,0}, {0,0,1}, {0,-1,0}}
    };
    int slot, client, rotation, reversed, vector, component, invalid, errors = 0;
    G_NITMOD_ResetBotHandles();
    for(slot = 0; slot < 3; ++slot) {
        gentity_t *entity = &g_entities[slots[slot]];
        gentity_t saved = *entity;
        nitmodBotHandle_t handle = G_NITMOD_BotEntityHandle(slots[slot]);
        for(client = 0; client < 2; ++client)
        for(rotation = 0; rotation < 4; ++rotation)
        for(reversed = 0; reversed < 2; ++reversed) {
            vec3_t output[5];
            gentity_t before;
            memset(entity, 0, sizeof(*entity));
            entity->inuse = qtrue;
            entity->client = client ? &ownerClient : NULL;
            VectorSet(entity->r.currentOrigin, 100, -200, 300);
            VectorSet(entity->r.mins, -4, -5, -6);
            VectorSet(entity->r.maxs, 8, 11, 14);
            if(reversed) {
                VectorSet(entity->r.mins, 8, 11, 14);
                VectorSet(entity->r.maxs, -4, -5, -6);
            }
            VectorCopy(angles[rotation], entity->r.currentAngles);
            before = *entity;
            if(G_NITMOD_BotEntityWorldOBB(handle, output[0], output[1], output[2], output[3], output[4]) != 0) ++errors;
            for(component = 0; component < 3; ++component) {
                if(fabs(output[0][component] - entity->r.currentOrigin[component] -
                        rotatedCenter[rotation][component]) > 0.0001) ++errors;
                if(output[4][component] != (reversed ? -1 : 1) * (6 + 2 * component)) ++errors;
                for(vector = 0; vector < 3; ++vector)
                    if(fabs(output[vector + 1][component] - axes[rotation][vector][component]) > 0.0001) ++errors;
            }
            if(memcmp(entity, &before, sizeof(before))) ++errors;
        }
        for(invalid = 0; invalid < 8; ++invalid) {
            vec3_t output[5];
            nitmodBotHandle_t query = handle;
            for(vector = 0; vector < 5; ++vector) VectorSet(output[vector], 999,998,997);
            /* Each required output independently null; malformed, unused,
             * and stale handles must leave all other outputs untouched. */
            entity->inuse = invalid == 6 ? qfalse : qtrue;
            if(invalid == 5) query = UINT32_C(0x12348000);
            if(invalid == 7) G_NITMOD_BotEntityDeleted(entity);
            if(G_NITMOD_BotEntityWorldOBB(query,
                invalid == 0 ? NULL : output[0], invalid == 1 ? NULL : output[1],
                invalid == 2 ? NULL : output[2], invalid == 3 ? NULL : output[3],
                invalid == 4 ? NULL : output[4]) !=
                (slots[slot] == ENTITYNUM_WORLD && invalid >= 6 ? 0 : 3)) ++errors;
            if(slots[slot] == ENTITYNUM_WORLD && invalid >= 6) {
                if(fabs(output[0][0] - 102) > 0.0001 ||
                   fabs(output[0][1] + 204) > 0.0001 ||
                   fabs(output[0][2] - 303) > 0.0001) ++errors;
            } else {
                for(vector = 0; vector < 5; ++vector)
                for(component = 0; component < 3; ++component)
                    if(output[vector][component] != 999 - component) ++errors;
            }
        }
        *entity = saved;
    }
    G_NITMOD_ResetBotHandles();
    return errors;
}
static int CheckBotEyeAndBonePosition(void) {
    static const int slots[] = {0, MAX_CLIENTS, ENTITYNUM_WORLD};
    static const int heights[] = {-24, 0, 12, 40, 64};
    static const int bones[] = {INT_MIN, -1, 0, 17, INT_MAX};
    int slot, client, sample, kind, component, errors = 0;
    gclient_t savedClient = ownerClient;
    if(offsetof(gclient_t, ps) != 0 || offsetof(playerState_t, viewheight) != 0xbc) ++errors;
    G_NITMOD_ResetBotHandles();
    for(slot = 0; slot < 3; ++slot) {
        gentity_t *entity = &g_entities[slots[slot]];
        gentity_t saved = *entity;
        nitmodBotHandle_t handle = G_NITMOD_BotEntityHandle(slots[slot]);
        for(client = 0; client < 2; ++client)
        for(sample = 0; sample < 5; ++sample)
        for(kind = 0; kind < 2; ++kind) {
            vec3_t result = {999,998,997};
            const vec3_t rotatedCenter = {-3,2,4};
            gentity_t before;
            gclient_t clientBefore;
            memset(entity, 0, sizeof(*entity));
            entity->inuse = qtrue;
            entity->client = client ? &ownerClient : NULL;
            VectorSet(entity->r.currentOrigin, 100, -200, 300);
            VectorSet(entity->r.currentAngles, 0, 90, 0);
            VectorSet(entity->r.mins, -4, -5, -6);
            VectorSet(entity->r.maxs, 8, 11, 14);
            VectorSet(ownerClient.ps.origin, 900, 800, 700);
            ownerClient.ps.viewheight = heights[sample];
            before = *entity;
            clientBefore = ownerClient;
            if((kind ? G_NITMOD_BotEntityBonePosition(handle, bones[sample], result) :
                       G_NITMOD_BotEntityEyePosition(handle, result)) != 0) ++errors;
            for(component = 0; component < 3; ++component) {
                float expected = entity->r.currentOrigin[component] +
                    (client ? 0 : rotatedCenter[component]) +
                    (!kind && client && component == 2 ? heights[sample] : 0);
                if(fabs(result[component] - expected) > 0.0001) ++errors;
            }
            if(memcmp(entity, &before, sizeof(before)) ||
               memcmp(&ownerClient, &clientBefore, sizeof(clientBefore))) ++errors;
            if(G_NITMOD_BotEntityEyePosition(handle, NULL) != 3 ||
               G_NITMOD_BotEntityBonePosition(handle, bones[sample], NULL) != 3) ++errors;
        }
        for(kind = 0; kind < 2; ++kind) {
            nitmodBotHandle_t invalids[4];
            invalids[0] = G_NITMOD_BotEntityHandle(slots[slot]);
            G_NITMOD_BotEntityDeleted(entity);
            invalids[1] = G_NITMOD_BotEntityHandle(slots[slot]);
            invalids[2] = NITMOD_BOT_INVALID_HANDLE;
            invalids[3] = UINT32_C(0x12348000);
            for(sample = 0; sample < 4; ++sample) {
                vec3_t result = {999,998,997};
                entity->inuse = sample == 0 ? qtrue : qfalse;
                if(sample == 0 && slots[slot] == ENTITYNUM_WORLD) continue;
                if((kind ? G_NITMOD_BotEntityBonePosition(invalids[sample], -1, result) :
                           G_NITMOD_BotEntityEyePosition(invalids[sample], result)) != 3 ||
                   result[0] != 999 || result[1] != 998 || result[2] != 997) ++errors;
            }
        }
        *entity = saved;
    }
    ownerClient = savedClient;
    G_NITMOD_ResetBotHandles();
    return errors;
}
static int CheckBotEntityOrientation(void) {
    static const int slots[] = {0, MAX_CLIENTS, ENTITYNUM_WORLD};
    static const vec3_t angles[] = {{0,0,0}, {0,90,0}, {90,0,0}, {0,0,90}};
    /* Forward/right/up, independently specified (right is NOT axis[1]). */
    static const vec3_t expected[4][3] = {
        {{1,0,0}, {0,-1,0}, {0,0,1}},
        {{0,1,0}, {1,0,0}, {0,0,1}},
        {{0,0,-1}, {0,-1,0}, {1,0,0}},
        {{1,0,0}, {0,0,-1}, {0,-1,0}}
    };
    int slot, rotation, client, mask, vector, component, errors = 0;
    gclient_t savedClient = ownerClient;
    if(offsetof(gclient_t, ps) != 0 || offsetof(playerState_t, viewangles) != 0xb0) ++errors;
    G_NITMOD_ResetBotHandles();
    for(slot = 0; slot < 3; ++slot) {
        gentity_t *entity = &g_entities[slots[slot]];
        gentity_t saved = *entity;
        nitmodBotHandle_t handle = G_NITMOD_BotEntityHandle(slots[slot]);
        for(rotation = 0; rotation < 4; ++rotation)
        for(client = 0; client < 2; ++client)
        for(mask = 0; mask < 8; ++mask) {
            vec3_t output[3] = {{99,98,97}, {99,98,97}, {99,98,97}};
            gentity_t before;
            gclient_t clientBefore;
            memset(entity, 0, sizeof(*entity));
            entity->inuse = qtrue;
            entity->client = client ? &ownerClient : NULL;
            VectorCopy(angles[rotation], entity->r.currentAngles);
            VectorCopy(angles[(rotation + 1) % 4], ownerClient.ps.viewangles);
            before = *entity;
            clientBefore = ownerClient;
            if(G_NITMOD_BotEntityOrientation(handle, mask & 1 ? output[0] : NULL,
                mask & 2 ? output[1] : NULL, mask & 4 ? output[2] : NULL) != 0) ++errors;
            for(vector = 0; vector < 3; ++vector)
            for(component = 0; component < 3; ++component) {
                float value = mask & (1 << vector) ?
                    expected[(rotation + client) % 4][vector][component] : (float)(99 - component);
                if(fabs(output[vector][component] - value) > 0.0001) ++errors;
            }
            if(memcmp(entity, &before, sizeof(before)) ||
               memcmp(&ownerClient, &clientBefore, sizeof(clientBefore))) ++errors;
        }
        {
            vec3_t output[3] = {{99,98,97}, {99,98,97}, {99,98,97}};
            entity->inuse = qfalse;
            if(G_NITMOD_BotEntityOrientation(handle, output[0], output[1], output[2]) != 3) ++errors;
            entity->inuse = qtrue;
            G_NITMOD_BotEntityDeleted(entity);
            if(slots[slot] != ENTITYNUM_WORLD &&
               G_NITMOD_BotEntityOrientation(handle, output[0], output[1], output[2]) != 3) ++errors;
            if(G_NITMOD_BotEntityOrientation(NITMOD_BOT_INVALID_HANDLE, output[0], output[1], output[2]) != 3 ||
               G_NITMOD_BotEntityOrientation(UINT32_C(0x12348000), NULL, NULL, NULL) != 3) ++errors;
            for(vector = 0; vector < 3; ++vector)
            for(component = 0; component < 3; ++component)
                if(output[vector][component] != 99 - component) ++errors;
        }
        *entity = saved;
    }
    ownerClient = savedClient;
    G_NITMOD_ResetBotHandles();
    return errors;
}
static int CheckBotEntityVelocity(void) {
    static const int slots[] = {0, MAX_CLIENTS - 1, MAX_CLIENTS, ENTITYNUM_WORLD};
    static const int types[] = {ET_PLAYER, ET_MOVER, ET_MISSILE};
    int slot, type, client, component, errors = 0;
    int savedMaxClients = level.maxclients;
    gclient_t savedClient = ownerClient;
    G_NITMOD_ResetBotHandles();
    level.maxclients = 1; /* This runtime limit must not replace MAX_CLIENTS. */
    VectorSet(ownerClient.ps.velocity, 901, 902, 903);
    for(slot = 0; slot < 4; ++slot) {
        gentity_t *entity = &g_entities[slots[slot]];
        gentity_t saved = *entity;
        nitmodBotHandle_t handle = G_NITMOD_BotEntityHandle(slots[slot]);
        for(type = 0; type < 3; ++type)
        for(client = 0; client < 2; ++client) {
            gentity_t before;
            vec3_t result = {999,998,997};
            const vec3_t moverVelocity = {125,-250,0};
            int moverPath = types[type] == ET_MOVER && !(client && slots[slot] < MAX_CLIENTS);
            memset(entity, 0, sizeof(*entity));
            entity->inuse = qtrue;
            entity->client = client ? &ownerClient : NULL;
            entity->s.eType = types[type];
            entity->s.number = slots[slot] < MAX_CLIENTS ? MAX_CLIENTS : 0;
            VectorSet(entity->s.pos.trDelta, -11, 22, -33);
            VectorSet(entity->r.currentOrigin, 102.5f, -205, 300);
            VectorSet(entity->oldOrigin, 100, -200, 300);
            VectorSet(entity->instantVelocity, 701, 702, 703);
            before = *entity;
            if(G_NITMOD_BotEntityVelocity(handle, result) != 0) ++errors;
            for(component = 0; component < 3; ++component)
                if(result[component] != (moverPath ? moverVelocity[component] :
                                        entity->s.pos.trDelta[component])) ++errors;
            if(memcmp(entity, &before, sizeof(before)) ||
               G_NITMOD_BotEntityVelocity(handle, NULL) != 3) ++errors;
        }
        {
            vec3_t result = {999,998,997};
            entity->inuse = qfalse;
            if(G_NITMOD_BotEntityVelocity(handle, result) != 3) ++errors;
            entity->inuse = qtrue;
            G_NITMOD_BotEntityDeleted(entity);
            if(slots[slot] != ENTITYNUM_WORLD &&
               G_NITMOD_BotEntityVelocity(handle, result) != 3) ++errors;
            if(G_NITMOD_BotEntityVelocity(NITMOD_BOT_INVALID_HANDLE, result) != 3 ||
               G_NITMOD_BotEntityVelocity(UINT32_C(0x12348000), result) != 3 ||
               result[0] != 999 || result[1] != 998 || result[2] != 997) ++errors;
        }
        *entity = saved;
    }
    ownerClient = savedClient;
    level.maxclients = savedMaxClients;
    G_NITMOD_ResetBotHandles();
    return errors;
}
static int CheckBotEntityPosition(void) {
    static const vec3_t angles[] = {{0,0,0}, {0,90,0}, {90,0,0}, {0,0,90}};
    /* Independently specified rotations of local center (2,3,4). */
    static const vec3_t rotated[] = {{2,3,4}, {-3,2,4}, {4,3,-2}, {2,-4,3}};
    static const int slots[] = {0, MAX_CLIENTS, ENTITYNUM_WORLD};
    int slot, rotation, client, brush, component, errors = 0;
    G_NITMOD_ResetBotHandles();
    for(slot = 0; slot < 3; ++slot) {
        gentity_t *entity = &g_entities[slots[slot]];
        gentity_t saved = *entity;
        nitmodBotHandle_t handle = G_NITMOD_BotEntityHandle(slots[slot]);
        for(rotation = 0; rotation < 4; ++rotation)
        for(client = 0; client < 2; ++client)
        for(brush = 0; brush < 2; ++brush) {
            gentity_t before;
            vec3_t result = {999,998,997};
            memset(entity, 0, sizeof(*entity));
            entity->inuse = qtrue;
            entity->client = client ? &ownerClient : NULL;
            entity->r.bmodel = brush;
            VectorSet(entity->r.currentOrigin, 100, -200, 300);
            VectorSet(entity->r.mins, -4, -5, -6);
            VectorSet(entity->r.maxs, 8, 11, 14);
            VectorCopy(angles[rotation], entity->r.currentAngles);
            VectorSet(entity->s.pos.trBase, 777, 888, 999);
            before = *entity;
            if(G_NITMOD_BotEntityPosition(handle, result) != 0) ++errors;
            for(component = 0; component < 3; ++component)
                if(fabs(result[component] - entity->r.currentOrigin[component] -
                        (client ? 0 : rotated[rotation][component])) > 0.0001) ++errors;
            if(memcmp(entity, &before, sizeof(before))) ++errors;
            if(G_NITMOD_BotEntityPosition(handle, NULL) != 3) ++errors;
        }
        entity->inuse = qfalse;
        {
            vec3_t result = {999,998,997};
            if(G_NITMOD_BotEntityPosition(handle, result) != 3 ||
               result[0] != 999 || result[1] != 998 || result[2] != 997) ++errors;
            entity->inuse = qtrue;
            G_NITMOD_BotEntityDeleted(entity);
            if(slots[slot] != ENTITYNUM_WORLD &&
               (G_NITMOD_BotEntityPosition(handle, result) != 3 || result[0] != 999 ||
                result[1] != 998 || result[2] != 997)) ++errors;
            if(G_NITMOD_BotEntityPosition(NITMOD_BOT_INVALID_HANDLE, result) != 3 ||
               G_NITMOD_BotEntityPosition(UINT32_C(0x12348000), result) != 3 ||
               result[0] != 999 || result[1] != 998 || result[2] != 997) ++errors;
        }
        *entity = saved;
    }
    G_NITMOD_ResetBotHandles();
    return errors;
}
static int CheckBotEngineAdapters(void) {
    static const int times[] = {0, -1, 1200, INT_MAX, INT_MIN};
    int index, time, errors = 0;
    G_NITMOD_ResetBotHandles();
    for(time = 0; time < 5; ++time) {
        level.time = times[time];
        if(G_NITMOD_BotGameTime() != times[time]) ++errors;
    }
    for(index = 0; index < MAX_GENTITIES; ++index) {
        gentity_t before = g_entities[index];
        nitmodBotHandle_t handle;
        g_entities[index].inuse = qtrue;
        g_entities[index].s.number = -17; /* Must use slot, not state number. */
        handle = G_NITMOD_BotEntityFromID(index);
        if(NITMOD_BotHandleIndex(handle) != index || !G_NITMOD_BotEntityExists(handle) ||
           G_NITMOD_BotIDFromEntity(handle) != index) ++errors;
        G_NITMOD_BotEntityDeleted(&g_entities[index]);
        if(G_NITMOD_BotEntityExists(handle) != (index == ENTITYNUM_WORLD) ||
           G_NITMOD_BotIDFromEntity(handle) != (index == ENTITYNUM_WORLD ? index : -1)) ++errors;
        g_entities[index].inuse = qfalse;
        handle = G_NITMOD_BotEntityFromID(index);
        if(index == ENTITYNUM_WORLD) {
            if(!G_NITMOD_BotEntityExists(handle) || G_NITMOD_BotIDFromEntity(handle) != index) ++errors;
        } else if(handle != NITMOD_BOT_INVALID_HANDLE || G_NITMOD_BotEntityExists(handle) ||
                  G_NITMOD_BotIDFromEntity(handle) != -1) ++errors;
        g_entities[index] = before;
    }
    if(G_NITMOD_BotEntityFromID(-1) != NITMOD_BOT_INVALID_HANDLE ||
       G_NITMOD_BotEntityFromID(MAX_GENTITIES) != NITMOD_BOT_INVALID_HANDLE ||
       G_NITMOD_BotEntityExists(UINT32_C(0x12348000)) ||
       G_NITMOD_BotIDFromEntity(UINT32_C(0x12340400)) != -1) ++errors;
    G_NITMOD_ResetBotHandles();
    printf("Bot engine adapters: 1024 live/stale/unused slots, 5 times, %d errors\n", errors);
    return errors;
}
static int CheckFreeOrdering(void) {
    gentity_t before, expected;
    gentity_t *entity = &g_entities[MAX_CLIENTS];
    int retained, callback, errors = 0;
    for(retained = 0; retained < 2; ++retained) for(callback = 0; callback < 2; ++callback) {
        memset(entity, 0, sizeof(*entity));
        entity->inuse = qtrue; entity->neverFree = retained;
        entity->s.number = MAX_CLIENTS; entity->classname = "free_order_fixture";
        entity->spawnCount = 17; entity->health = 23;
        entity->nitmodClassnameHash = 0x1908e;
        entity->nitmodTargetHash = 111;
        entity->nitmodScriptNameHash = 222;
        if(callback) entity->free = ObserveFree;
        before = *entity; freeTarget = entity; freeCallbackCalls = freeUnlinks = 0;
        G_NITMOD_ResetBotHandles();
        freedHandle = G_NITMOD_BotEntityHandle(MAX_CLIENTS);
        if(NITMOD_BotHandleSerial(freedHandle) != 1 || G_NITMOD_BotResolveEntity(freedHandle) != entity) ++errors;
        level.time = 1200;
        G_FreeEntity(entity);
        if(freeUnlinks != 1 || freeCallbackCalls != callback) ++errors;
        if(G_NITMOD_BotResolveEntity(freedHandle) ||
           NITMOD_BotHandleSerial(G_NITMOD_BotEntityHandle(MAX_CLIENTS)) != 2) ++errors;
        if(retained) {
            if(memcmp(entity, &before, sizeof(before))) ++errors;
        } else {
            memset(&expected, 0, sizeof(expected));
            expected.classname = entity->classname;
            expected.freetime = 1200; expected.spawnCount = 17;
            if(!entity->classname || strcmp(entity->classname, "freed") ||
               memcmp(entity, &expected, sizeof(expected))) ++errors;
            /* Reuse the real initializer; this counter is distinct from bot serial. */
            G_InitGentity(entity);
            if(!entity->inuse || entity->spawnCount != 18 || entity->s.number != MAX_CLIENTS) ++errors;
        }
        if(G_NITMOD_BotResolveEntity(G_NITMOD_BotEntityHandle(MAX_CLIENTS)) != entity) ++errors;
        freeTarget = NULL;
    }
    memset(entity, 0, sizeof(*entity));
    printf("Real entity free: 4 callback/neverFree profiles and slot reuse, %d errors\n", errors);
    return errors;
}
static int CheckMineThinkPipeline(void) {
    static gclient_t clients[2];
    gentity_t mine, expected;
    int mode, fallback, errors = 0;
    for(mode = 0; mode < 8; ++mode) for(fallback = 0; fallback < 2; ++fallback) {
        int admitted = mode == 0 || mode == 3 || mode == 6 || fallback;
        memset(&mine, 0, sizeof(mine)); memset(clients, 0, sizeof(clients));
        memset(&g_entities[1], 0, sizeof(g_entities[1]) * 3);
        g_entities[1].client = &clients[0]; g_entities[2].client = &clients[1];
        g_entities[1].s.eType = g_entities[2].s.eType = ET_PLAYER;
        g_entities[1].s.clientNum = 1; g_entities[2].s.clientNum = 2;
        g_entities[3].s.clientNum = 3;
        clients[0].sess.sessionTeam = clients[1].sess.sessionTeam = TEAM_ALLIES;
        mine.parent = &g_entities[3]; mine.s.teamNum = TEAM_AXIS;
        mine.s.weapon = WP_LANDMINE; mine.s.eType = ET_MISSILE;
        mine.r.contents = CONTENTS_BODY; mine.s.density = 4;
        mine.think = G_LandmineThink;
        VectorSet(mine.r.mins, -16,-16,0); VectorSet(mine.r.maxs,16,16,16);
        level.time = 1000; g_friendlyFire.integer = 0;
        g_OmniBotFlags.integer = 0; n_preciseLandmineTrigger.integer = 0;
        if(mode == 1) { clients[0].sess.sessionTeam = TEAM_AXIS; g_friendlyFire.integer = 32; }
        if(mode == 2 || mode == 3) {
            g_entities[3].s.clientNum = 1; g_friendlyFire.integer = 256;
            g_entities[1].s.weapon = mode == 3 ? WP_PLIERS : WP_MP40;
        }
        if(mode >= 4 && mode <= 6) {
            g_entities[1].r.svFlags = SVF_BOT;
            if(mode == 4) clients[0].sess.sessionTeam = TEAM_AXIS;
            else mine.s.modelindex2 = 1;
            if(mode == 6) g_OmniBotFlags.integer = 32;
        }
        if(mode == 7) { n_preciseLandmineTrigger.integer = 1; g_entities[1].r.currentOrigin[0] = 24; }
        expected = mine; expected.nextthink = 1100; expected.s.density = 0;
        triggerExpected = expected; triggerLink = &mine; triggerLinks = 0;
        mineQueryActive = 1; mineQueryCalls = 0; mineQueryFallback = fallback;
        G_LandmineThink(&mine);
        if(admitted) {
            expected.think = LandminePostThink; expected.s.teamNum += 8;
            expected.s.time = 1000; expected.s.onFireStart = 1;
        }
        if(mineQueryCalls != 1 || triggerLinks != admitted || memcmp(&mine, &expected, sizeof(mine))) ++errors;
        mineQueryActive = 0; triggerLink = NULL;
    }
    memset(&g_entities[1], 0, sizeof(g_entities[1]) * 3);
    g_friendlyFire.integer = g_OmniBotFlags.integer = n_preciseLandmineTrigger.integer = 0;
    printf("Real mine think: 16 candidate/filter/fallback profiles, %d errors\n", errors);
    return errors;
}
static int CheckMineTransitions(void) {
    static const int times[] = {0, 1000, 200000};
    gentity_t mine, expected;
    static const int latchValues[] = {-3, 0, 7};
    int timeIndex, team, contents, latch, errors = 0;
    if(offsetof(entityState_t, onFireStart) != 0xfc || offsetof(gentity_t, s) != 0) ++errors;
    for(timeIndex = 0; timeIndex < 3; ++timeIndex)
    for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
    for(contents = 0; contents < 2; ++contents)
    for(latch = 0; latch < 3; ++latch) {
        memset(&mine, 0, sizeof(mine));
        mine.s.weapon = WP_LANDMINE; mine.s.eType = ET_MISSILE;
        mine.s.teamNum = team; mine.s.time = -99;
        mine.s.onFireStart = latchValues[latch];
        mine.r.contents = contents ? CONTENTS_CORPSE : CONTENTS_BODY;
        mine.health = 5; mine.takedamage = qtrue;
        mine.nextthink = 9000; mine.think = NormalThink;
        level.time = times[timeIndex];
        triggerExpected = mine;
        triggerExpected.r.contents = CONTENTS_BODY;
        triggerLink = &mine; triggerLinks = 0;
        LandMineTrigger(&mine);
        expected = triggerExpected;
        expected.nextthink = level.time + 100;
        expected.think = LandminePostThink;
        expected.s.teamNum += 8;
        expected.s.time = level.time;
        expected.s.onFireStart = 1;
        if(triggerLinks != 1 || memcmp(&mine, &expected, sizeof(mine))) ++errors;
        triggerLink = NULL; expectedLink = expectedShake = NULL;
        LandMinePostTrigger(&mine);
        expected.nextthink = level.time + 300;
        expected.think = G_ExplodeMissile;
        if(memcmp(&mine, &expected, sizeof(mine))) ++errors;
    }
    printf("Landmine trigger/post-trigger: 36 typed transition profiles, %d errors\n", errors);
    return errors;
}
extern void trigger_heal_think(gentity_t *self);
extern void trigger_ammo_think(gentity_t *self);
static int CheckInactivityOptions(void) {
    static gclient_t clients[4];
    gclient_t *savedClients = level.clients;
    int savedMax = level.maxclients, savedCount = level.numConnectedClients, savedTime = level.time;
    int option, following, full, privateOccupied, i, errors = 0;
    level.clients = clients; level.maxclients = 4; level.time = 100000;
    g_inactivity.integer = g_spectatorInactivity.integer = 60;
    inactivityTest = 1; inactivityPrivate = 2; inactivityDrops = 0;
    for(option = 0; option < 4; ++option) for(following = 0; following < 2; ++following)
        for(full = 0; full < 2; ++full) for(privateOccupied = 0; privateOccupied < 2; ++privateOccupied) {
            int exempt;
            memset(clients, 0, sizeof(clients));
            clients[0].pers.connected = CON_CONNECTED;
            clients[1].pers.connected = privateOccupied ? CON_CONNECTED : CON_DISCONNECTED;
            clients[3].sess.sessionTeam = TEAM_SPECTATOR;
            clients[3].sess.spectatorState = following ? SPECTATOR_FOLLOW : SPECTATOR_FREE;
            clients[3].inactivityTime = 110000;
            g_inactivityOptions.integer = option;
            level.numConnectedClients = (privateOccupied ? 4 : 3) - !full;
            exempt = (following && (option & 1)) || (!full && !(option & 2));
            inactivityWarnings = 0;
            if(!ClientInactivityTimer(&clients[3]) || inactivityWarnings != !exempt ||
               clients[3].inactivityTime != (exempt ? 160000 : 110000) ||
               clients[3].inactivityWarning != !exempt) ++errors;
        }
    memset(clients, 0, sizeof(clients)); clients[3].sess.sessionTeam = TEAM_SPECTATOR;
    g_inactivityOptions.integer = 2; clients[3].inactivityWarning = qtrue; clients[3].inactivityTime = 99999;
    if(ClientInactivityTimer(&clients[3]) || inactivityDrops != 1) ++errors;
    for(i = 0; i < 4; ++i) {
        memset(&clients[3], 0, sizeof(clients[3])); clients[3].sess.sessionTeam = TEAM_AXIS;
        if(i == 0) clients[3].ps.pm_flags = PMF_LIMBO;
        if(i == 1) clients[3].ps.pm_type = PM_DEAD;
        if(i == 2) { clients[3].ps.eFlags = EF_PRONE; clients[3].ps.weapon = WP_MOBILE_MG42_SET; }
        if(i == 3) clients[3].pers.cmd.forwardmove = 1;
        inactivityWarnings = 0;
        if(!ClientInactivityTimer(&clients[3]) || clients[3].inactivityTime != 160000 || inactivityWarnings) ++errors;
    }
    g_inactivity.integer = -1; clients[3].ps.pm_flags = 0; clients[3].pers.cmd.forwardmove = 0;
    if(!ClientInactivityTimer(&clients[3]) || clients[3].inactivityTime != 160000) ++errors;
    inactivityTest = 0; level.clients = savedClients; level.maxclients = savedMax;
    level.numConnectedClients = savedCount; level.time = savedTime;
    g_inactivity.integer = g_spectatorInactivity.integer = g_inactivityOptions.integer = 0;
    printf("Inactivity: 32 spectator option profiles, disconnect and activity resets, %d errors\n", errors);
    return errors;
}
static int CheckIntermissionCvars(void) {
    static gclient_t clients[4];
    gclient_t *savedClients = level.clients;
    int savedCount = level.numConnectedClients, savedTime = level.time, savedStart = level.intermissiontime;
    qboolean savedReady = level.ref_allready;
    int savedSorted[4], savedFlags[4], i, ready, threshold, elapsed, errors = 0;
    const float thresholds[] = {-1, 0, 50, 50.5f, 100, 101};
    memset(clients, 0, sizeof(clients));
    for(i = 0; i < 4; ++i) {
        savedSorted[i] = level.sortedClients[i]; savedFlags[i] = g_entities[i].r.svFlags;
        level.sortedClients[i] = i; g_entities[i].r.svFlags = i == 2 ? SVF_BOT : 0;
        clients[i].pers.connected = i == 3 ? CON_CONNECTING : CON_CONNECTED;
        clients[i].sess.sessionTeam = i == 1 ? TEAM_SPECTATOR : TEAM_AXIS;
    }
    level.clients = clients; level.numConnectedClients = 4; level.intermissiontime = 10000;
    level.ref_allready = qfalse; g_intermissionTime.integer = 1;
    for(ready = 0; ready <= 2; ++ready) for(threshold = 0; threshold < 6; ++threshold)
        for(elapsed = 999; elapsed <= 1000; ++elapsed) {
            clients[0].pers.ready = ready >= 1; clients[1].pers.ready = ready == 2;
            clients[2].pers.ready = clients[3].pers.ready = qtrue;
            level.time = 10000 + elapsed; g_intermissionReadyPercent.value = thresholds[threshold];
            if(NITMOD_IntermissionCanExit() != (ready * 50.0f >= thresholds[threshold] || elapsed == 1000)) ++errors;
        }
    level.numConnectedClients = 0; level.time = 10999;
    if(NITMOD_IntermissionCanExit()) ++errors;
    level.ref_allready = qtrue; if(!NITMOD_IntermissionCanExit()) ++errors;
    level.ref_allready = qfalse; g_intermissionTime.integer = 0;
    if(!NITMOD_IntermissionCanExit()) ++errors;
    if(NITMOD_IntermissionDisplayStart(100000, 60) != 100000 ||
       NITMOD_IntermissionDisplayStart(100000, 30) != 70000 ||
       NITMOD_IntermissionDisplayStart(100000, 90) != 130000 ||
       NITMOD_IntermissionDisplayStart(100000, 0) != 100000 ||
       NITMOD_IntermissionDisplayStart(100000, INT_MAX) != INT_MAX) ++errors;
    for(i = 0; i < 4; ++i) { level.sortedClients[i] = savedSorted[i]; g_entities[i].r.svFlags = savedFlags[i]; }
    level.clients = savedClients; level.numConnectedClients = savedCount; level.time = savedTime;
    level.intermissiontime = savedStart; level.ref_allready = savedReady;
    g_intermissionTime.integer = 60; g_intermissionReadyPercent.value = 100;
    printf("Intermission: 36 readiness/deadline profiles and countdown edges, %d errors\n", errors);
    return errors;
}
static int CheckLimboPacks(void) {
    static gclient_t client;
    static gentity_t bodies[BODY_QUEUE_SIZE];
    gentity_t *savedBodies[BODY_QUEUE_SIZE];
    int errors = 0, count, war, cls, game, skill, i, savedTime = level.time, savedEntities = level.num_entities;
    int delays[] = {-1, 0, 4999, 5000, 30000, 60000, 60001};
    for(count = -1; count <= 11; ++count) for(war = 0; war <= 5; ++war)
        for(cls = 0; cls < 5; ++cls) for(game = 0; game <= 1; ++game) {
            int expected = count > 0 && (war == 0 || war == 5) && game == GS_PLAYING && cls == PC_MEDIC ? (count > 10 ? 10 : count) : 0;
            if(NITMOD_LimboPackCount(count, war, game, cls, PC_MEDIC) != expected) ++errors;
        }
    for(i = 0; i < 7; ++i)
        if(NITMOD_PackSinkDelay(delays[i]) != (delays[i] >= 5000 && delays[i] <= 60000 ? delays[i] : 30000)) ++errors;
    memcpy(savedBodies, level.bodyQue, sizeof(savedBodies));
    memset(bodies, 0, sizeof(bodies));
    for(i = 0; i < BODY_QUEUE_SIZE; ++i) level.bodyQue[i] = &bodies[i];
    packTest = 1; level.time = 100000; level.num_entities = MAX_CLIENTS + 10;
    g_gamestate.integer = GS_PLAYING; g_dropAmmo.integer = g_dropHealth.integer = 12;
    n_medPackSinkDelay.integer = 5000; n_ammoPackSinkDelay.integer = 60000;
    level.medicChargeTime[0] = level.lieutenantChargeTime[0] = 40000;
    for(cls = PC_MEDIC; cls <= PC_FIELDOPS; cls += 2) for(skill = 0; skill < 2; ++skill) {
        memset(&client, 0, sizeof(client)); memset(&g_entities[0], 0, sizeof(g_entities[0]));
        memset(&g_entities[MAX_CLIENTS], 0, sizeof(gentity_t) * 10);
        g_entities[0].client = &client; client.sess.sessionTeam = TEAM_AXIS; client.sess.playerType = cls;
        client.sess.skill[SK_FIRST_AID] = skill * 2; client.sess.skill[SK_SIGNALS] = skill;
        packLinks = 0; NITMOD_DropLimboPacks(&g_entities[0]);
        if(packLinks != 10) ++errors;
        for(i = 0; i < 10; ++i) {
            gentity_t *pack = &g_entities[MAX_CLIENTS + i];
            if(pack->parent != &g_entities[0] || pack->s.teamNum != TEAM_AXIS || pack->s.eType != ET_ITEM ||
               pack->nextthink != level.time + (cls == PC_MEDIC ? 5000 : 60000) ||
               pack->s.pos.trDelta[2] != 25 || fabs(pack->s.pos.trDelta[0]) > 100 || fabs(pack->s.pos.trDelta[1]) > 100) ++errors;
            if(cls == PC_FIELDOPS && (pack->count != skill + 1 || pack->s.density != skill + 1)) ++errors;
        }
    }
    memset(&g_entities[0], 0, sizeof(g_entities[0])); memset(&g_entities[MAX_CLIENTS], 0, sizeof(gentity_t) * 10);
    packTest = 0; level.time = savedTime; level.num_entities = savedEntities;
    memcpy(level.bodyQue, savedBodies, sizeof(savedBodies));
    g_dropHealth.integer = g_dropAmmo.integer = 0;
    printf("Limbo packs: policy matrix, delay boundaries, 40 real launches, %d errors\n", errors);
    return errors;
}
static int CheckClassLimits(void) {
    static gclient_t clients[MAX_CLIENTS];
    static gentity_t ent;
    gclient_t *savedClients = level.clients;
    int savedCount = level.numNonSpectatorClients, savedSorted[MAX_CLIENTS];
    vmCvar_t *limits[] = {&team_maxSoldiers, &team_maxMedics, &team_maxEngineers, &team_maxFieldops, &team_maxCovertops};
    const int maximums[] = {-2, -1, 0, 1, 2, 3};
    int cls, setting, war, spectator, errors = 0;
    memcpy(savedSorted, level.sortedClients, sizeof(savedSorted));
    memset(clients, 0, sizeof(clients)); memset(&ent, 0, sizeof(ent));
    level.clients = clients; level.numNonSpectatorClients = 4;
    ent.client = &clients[0];
    for(cls = 0; cls < 4; ++cls) level.sortedClients[cls] = cls;
    classTest = 1;
    for(cls = 0; cls < 5; ++cls) for(setting = 0; setting < 6; ++setting)
        for(war = 0; war <= 4; ++war) for(spectator = 0; spectator < 2; ++spectator) {
            int expected, exempt;
            clients[0].sess.sessionTeam = spectator ? TEAM_SPECTATOR : TEAM_AXIS;
            clients[0].sess.playerType = clients[0].sess.latchPlayerType = cls;
            clients[1].sess.sessionTeam = clients[2].sess.sessionTeam = TEAM_AXIS;
            clients[3].sess.sessionTeam = TEAM_ALLIES;
            clients[1].sess.playerType = cls; clients[1].sess.latchPlayerType = cls;
            clients[2].sess.playerType = (cls + 1) % 5; clients[2].sess.latchPlayerType = cls;
            clients[3].sess.playerType = clients[3].sess.latchPlayerType = cls;
            limits[cls]->integer = maximums[setting]; classWar = war;
            exempt = (war == 1 && cls == PC_SOLDIER) || (war == 2 && cls == PC_COVERTOPS) || (war == 3 && cls == PC_ENGINEER);
            expected = !spectator && !exempt && maximums[setting] != -1 && maximums[setting] <= 2;
            if(G_IsClassDisabled(&ent, cls, qtrue) != expected) ++errors;
        }
    classWar = 0; clients[0].sess.sessionTeam = TEAM_AXIS;
    for(cls = 0; cls < 5; ++cls) limits[cls]->integer = 0;
    if(NITMOD_SelectAvailableClass(&ent, PC_MEDIC) != -1) ++errors;
    team_maxEngineers.integer = -1;
    if(NITMOD_SelectAvailableClass(&ent, PC_MEDIC) != PC_ENGINEER) ++errors;
    if(G_IsClassDisabled(&ent, -1, qtrue) || G_IsClassDisabled(&ent, 5, qtrue)) ++errors;
    for(cls = 0; cls < 5; ++cls) limits[cls]->integer = -1;
    classTest = 0; level.clients = savedClients; level.numNonSpectatorClients = savedCount;
    memcpy(level.sortedClients, savedSorted, sizeof(savedSorted));
    printf("Class limits: 300 class/limit/war/team profiles plus fallback, %d errors\n", errors);
    return errors;
}
static int CheckLandmineLimitCvar(void) {
    static gentity_t mines[48];
    const int limits[] = {-1, 0, 1, 10, 16, 40};
    int i, limit, errors = 0;
    G_NITMOD_ResetEntityLists();
    memset(mines, 0, sizeof(mines));
    for(i = 0; i < 48; ++i) {
        mines[i].s.teamNum = i < 16 ? TEAM_AXIS : i < 32 ? TEAM_ALLIES : TEAM_AXIS + 4;
        G_NITMOD_RegisterLandmine(&mines[i]);
    }
    for(limit = 0; limit < sizeof(limits)/sizeof(limits[0]); ++limit) {
        int expected = limits[limit] < 16 ? limits[limit] : 16;
        team_maxLandmines.integer = limits[limit];
        if(G_CountTeamLandmines(TEAM_AXIS) != expected || G_CountTeamLandmines(TEAM_ALLIES) != expected) ++errors;
    }
    /* Live arming/team changes and unregister must change the actual count. */
    team_maxLandmines.integer = 40;
    mines[32].s.teamNum = TEAM_AXIS;
    mines[0].s.teamNum = TEAM_ALLIES;
    if(G_CountTeamLandmines(TEAM_AXIS) != 16 || G_CountTeamLandmines(TEAM_ALLIES) != 17) ++errors;
    G_NITMOD_UnregisterLandmine(&mines[0]);
    if(G_CountTeamLandmines(TEAM_ALLIES) != 16) ++errors;
    G_NITMOD_ResetEntityLists();
    if(G_CountTeamLandmines(TEAM_AXIS) != 0) ++errors;
    team_maxLandmines.integer = 10;
    printf("Landmine Cvar: six limits, two teams, live transitions/reset, %d errors\n", errors);
    return errors;
}
static int CheckSupplyAndSpawnCvars(void) {
    static gclient_t client;
    gentity_t cabinet;
    const int seconds[] = {-1, 0, 3, 10, INT_MAX, INT_MIN};
    const int intervals[] = {-1, 0, 10000, 60000};
    int i, team, revived, fast, errors = 0, savedTime = level.time;
    level.time = 100000;
    for(team = TEAM_FREE; team <= TEAM_SPECTATOR; ++team)
        for(revived = 0; revived < 2; ++revived) for(fast = 0; fast <= 2; ++fast)
            for(i = 0; i < sizeof(seconds)/sizeof(seconds[0]); ++i) {
                double expiry;
                int expected;
                memset(&client, 0, sizeof(client)); client.sess.sessionTeam = team;
                client.ps.powerups[PW_INVULNERABLE] = 123;
                g_spawnInvul.integer = seconds[i]; g_fastres.integer = fast;
                expiry = 100000.0 + (revived ? (fast == 1 ? 1000.0 : 3000.0) : (double)seconds[i] * 1000.0);
                expected = team == TEAM_SPECTATOR ? 123 : expiry > INT_MAX ? INT_MAX : expiry < INT_MIN ? INT_MIN : (int)expiry;
                NITMOD_SetSpawnProtection(&client, revived);
                if(client.ps.powerups[PW_INVULNERABLE] != expected) ++errors;
            }
    for(i = 0; i < sizeof(intervals)/sizeof(intervals[0]); ++i) {
        memset(&cabinet, 0, sizeof(cabinet)); cabinet.health = 4; cabinet.damage = 3; cabinet.count = 8;
        g_healthCabinetTime.integer = intervals[i]; g_ammoCabinetTime.integer = intervals[i];
        trigger_heal_think(&cabinet);
        if(cabinet.health != 7 || cabinet.nextthink != level.time + intervals[i]) ++errors;
        trigger_ammo_think(&cabinet);
        if(cabinet.health != 8 || cabinet.nextthink != level.time + intervals[i]) ++errors;
    }
    level.time = savedTime; g_spawnInvul.integer = 3; g_fastres.integer = 0;
    g_healthCabinetTime.integer = 10000; g_ammoCabinetTime.integer = 60000;
    printf("Supply/spawn Cvars: 144 protection profiles and 8 refill calls, %d errors\n", errors);
    return errors;
}
static int CheckCanisterSpawn(void) {
    static gentity_t actor;
    static gclient_t client;
    gentity_t saved = g_entities[MAX_CLIENTS], *missile;
    vmCvar_t savedKick = g_canisterKick, savedDamage = g_damageweapons;
    const int weapons[] = {WP_GRENADE_LAUNCHER, WP_GRENADE_PINEAPPLE,
        WP_SMOKE_MARKER, WP_SMOKE_BOMB, WP_GPG40};
    vec3_t start = {100, 200, 300}, velocity = {10, 20, 30};
    int oldCount = level.num_entities, oldTime = level.time;
    int w, kick, damage, errors = 0;
    memset(&actor, 0, sizeof(actor)); memset(&client, 0, sizeof(client));
    actor.client = &client; actor.s.number = 3;
    actor.s.groundEntityNum = ENTITYNUM_NONE;
    client.sess.sessionTeam = TEAM_AXIS;
    level.num_entities = MAX_CLIENTS + 1; level.time = 1000;
    for(w = 0; w < 5; ++w) for(kick = -1; kick <= 1; ++kick)
    for(damage = 0; damage <= 1; ++damage) {
        memset(&g_entities[MAX_CLIENTS], 0, sizeof(gentity_t));
        g_canisterKick.integer = kick; g_damageweapons.integer = damage ? 13 : 0;
        client.ps.grenadeTimeLeft = 0;
        missile = fire_grenade(&actor, start, velocity, weapons[w]);
        if(missile != &g_entities[MAX_CLIENTS] || missile->parent != &actor ||
           missile->r.ownerNum != 3 || missile->s.teamNum != TEAM_AXIS ||
           !VectorCompare(missile->r.currentOrigin, start) ||
           missile->think != G_ExplodeMissile ||
           missile->nextthink != (w == 4 ? 5000 : 3500)) ++errors;
        if(w < 4 && kick) {
            if(missile->r.contents != CONTENTS_CORPSE ||
               missile->r.mins[0] != -4 || missile->r.mins[1] != -4 || missile->r.mins[2] != 0 ||
               missile->r.maxs[0] != 4 || missile->r.maxs[1] != 4 || missile->r.maxs[2] != 6 ||
               !VectorCompare(missile->r.mins, missile->r.absmin) ||
               !VectorCompare(missile->r.maxs, missile->r.absmax)) ++errors;
        } else if(missile->r.contents != (w < 4 && damage ? CONTENTS_CORPSE : 0)) ++errors;
        if(missile->takedamage != (w < 4 && damage) ||
           missile->die != (w < 4 && damage ? G_NITMOD_WeaponDie : NULL)) ++errors;
    }
    G_NITMOD_ConfigureCanisterKick(NULL);
    g_entities[MAX_CLIENTS] = saved; level.num_entities = oldCount; level.time = oldTime;
    g_canisterKick = savedKick; g_damageweapons = savedDamage;
    return errors;
}

static int CheckCanisterKick(void) {
    static gentity_t actor;
    static gclient_t client;
    static gclient_t bodyClient;
    gentity_t savedBody = g_entities[7];
    gentity_t saved = g_entities[MAX_CLIENTS];
    gentity_t *missile = &g_entities[MAX_CLIENTS];
    vmCvar_t savedKick = g_canisterKick, savedOwner = g_canisterKickOwner;
    const int weapons[] = {WP_GRENADE_LAUNCHER, WP_GRENADE_PINEAPPLE,
        WP_SMOKE_MARKER, WP_SMOKE_BOMB, WP_PANZERFAUST};
    int w, owner, gate, active, changesOwner, admitted, errors = 0, savedTime = level.time;
    memset(&actor, 0, sizeof(actor)); memset(&client, 0, sizeof(client));
    actor.client = &client; actor.s.number = 3;
    client.sess.sessionTeam = TEAM_AXIS;
    level.time = 1000; kickTest = 1;
    for(w = 0; w < 5; ++w) for(owner = 0; owner < 2; ++owner)
    for(gate = 0; gate < 5; ++gate) for(active = 0; active < 2; ++active) {
        memset(missile, 0, sizeof(*missile));
        missile->s.eType = ET_MISSILE; missile->s.weapon = weapons[w];
        missile->s.pos.trBase[2] = 7; missile->nextthink = 4000;
        missile->think = NormalThink;
        missile->r.ownerNum = 9; missile->s.teamNum = TEAM_ALLIES;
        missile->active = active;
        g_canisterKick.integer = gate == 1 ? 0 : 80;
        g_canisterKickOwner.integer = owner;
        client.ps.pm_flags = gate == 2 ? PMF_LIMBO : 0;
        client.ps.pm_type = gate == 3 ? PM_DEAD : PM_NORMAL;
        client.ps.eFlags = gate == 4 ? EF_PRONE : 0;
        kickQueries = 0;
        G_CanisterKick(&actor);
        admitted = gate == 0 && w < 4;
        changesOwner = admitted && owner && (w != 2 || !active);
        if(kickQueries != (gate == 0) || missile->nextthink != 4000 || missile->think != NormalThink ||
           missile->s.pos.trType != (admitted ? TR_GRAVITY : TR_STATIONARY) ||
           missile->s.pos.trBase[2] != (admitted ? 37 : 7)) ++errors;
        if(admitted && (missile->s.pos.trTime != 950 ||
           !VectorCompare(missile->s.pos.trBase, missile->r.currentOrigin) ||
           missile->s.pos.trDelta[0] != 772 || missile->s.pos.trDelta[2] != 367)) ++errors;
        if(missile->parent != (changesOwner ? &actor : NULL) ||
           missile->r.ownerNum != (changesOwner ? 3 : 9) ||
           missile->s.teamNum != (changesOwner ? TEAM_AXIS : TEAM_ALLIES) ||
           missile->active != active) ++errors;
    }
    /* Real secondary activation must kick before the corpse interaction. */
    memset(missile, 0, sizeof(*missile));
    missile->s.eType = ET_MISSILE; missile->s.weapon = WP_SMOKE_MARKER;
    memset(&g_entities[7], 0, sizeof(g_entities[7]));
    memset(&bodyClient, 0, sizeof(bodyClient));
    g_entities[7].client = &bodyClient;
    actor.health = 100; actor.s.number = 2;
    client.ps.pm_flags = client.ps.eFlags = 0; client.ps.pm_type = PM_NORMAL;
    g_canisterKick.integer = 80; g_canisterKickOwner.integer = 1;
    kickQueries = dragTraces = 0; dragTest = 1;
    Cmd_Activate2_f(&actor);
    if(kickQueries != 1 || dragTraces != 1 || missile->parent != &actor ||
       missile->r.ownerNum != 2 || missile->s.pos.trType != TR_GRAVITY) ++errors;
    dragTest = 0; g_entities[7] = savedBody;
    kickTest = 0; level.time = savedTime;
    *missile = saved; g_canisterKick = savedKick; g_canisterKickOwner = savedOwner;
    return errors;
}

static int CheckPlayerShove(void) {
    static gentity_t actor, target;
    static gclient_t ac, tc;
    vmCvar_t savedShove = g_shove, savedNoZ = g_shoveNoZ;
    int savedTime = level.time, savedMax = level.maxclients;
    int strength, noZ, pitch, errors = 0;
    level.maxclients = 0; /* transport is tested separately from physics */
    for(strength = 0; strength <= 80; strength += 80)
    for(noZ = 0; noZ < 2; ++noZ)
    for(pitch = -90; pitch <= 90; pitch += 90) {
        memset(&actor, 0, sizeof(actor)); memset(&target, 0, sizeof(target));
        memset(&ac, 0, sizeof(ac)); memset(&tc, 0, sizeof(tc));
        actor.client = &ac; target.client = &tc;
        actor.health = target.health = 100;
        ac.ps.viewangles[0] = pitch;
        g_shove.integer = strength; g_shoveNoZ.integer = noZ;
        level.time = 1000;
        if(G_PushPlayer(&actor, &target) != (strength != 0)) ++errors;
        if(strength) {
            if(fabs(tc.ps.velocity[2] - (pitch == -90 && !noZ ? 320 : 64)) > 1 ||
               !VectorCompare(tc.ps.velocity, target.s.pos.trDelta) ||
               tc.ps.pm_time != 100 || !(tc.ps.pm_flags & PMF_TIME_KNOCKBACK) ||
               ac.nitmodLastShoveTime != 1000) ++errors;
            level.time = 1499;
            if(G_PushPlayer(&actor, &target)) ++errors;
            level.time = 1500;
            if(!G_PushPlayer(&actor, &target)) ++errors;
        } else if(tc.ps.pm_time || ac.nitmodLastShoveTime) ++errors;
    }
    if(G_PushPlayer(NULL, &target) || G_PushPlayer(&actor, NULL) ||
       G_PushPlayer(&actor, &actor)) ++errors;
    level.time = savedTime; level.maxclients = savedMax;
    g_shove = savedShove; g_shoveNoZ = savedNoZ;
    return errors;
}

static int CheckCorpseDrag(void) {
    static gentity_t actor, body;
    static gclient_t client;
    static gclient_t actorClient;
    gentity_t savedTarget = g_entities[7];
    const float distances[] = {0, 39, 40, 60, 85, 86};
    int setting, d, sign, errors = 0, expected;
    vmCvar_t saved = g_dragCorpse;
    for(setting = -1; setting <= 1; ++setting)
    for(d = 0; d < 6; ++d)
    for(sign = -1; sign <= 1; sign += 2) {
        memset(&actor, 0, sizeof(actor));
        memset(&body, 0, sizeof(body));
        memset(&client, 0, sizeof(client));
        body.client = &client;
        actor.r.currentOrigin[0] = distances[d] * sign;
        actor.r.currentOrigin[2] = 900; /* height is deliberately ignored */
        VectorSet(client.ps.velocity, 12, 20, 30);
        VectorSet(body.s.pos.trDelta, 40, 50, 60);
        g_dragCorpse.integer = setting;
        expected = setting != 0 && d >= 2 && d <= 4;
        if(G_DragCorpse(&actor, &body) != expected) ++errors;
        if(fabs(client.ps.velocity[0] - (expected ? sign * 110 : 12)) > .001 ||
           fabs(client.ps.velocity[1] - (expected ? 0 : 20)) > .001 ||
           client.ps.velocity[2] != 30 || body.s.pos.trDelta[2] != 60 ||
           fabs(body.s.pos.trDelta[0] - (expected ? 28 + sign * 110 : 40)) > .001 ||
           fabs(body.s.pos.trDelta[1] - (expected ? 30 : 50)) > .001)
            ++errors;
    }
    if(G_DragCorpse(NULL, &body) || G_DragCorpse(&actor, NULL) ||
       G_DragCorpse(&body, &body)) ++errors;
    body.client = NULL;
    if(G_DragCorpse(&actor, &body)) ++errors;
    /* Exercise the real activate2 dispatch, including non-covert classes. */
    memset(&actorClient, 0, sizeof(actorClient));
    memset(&actor, 0, sizeof(actor));
    actor.client = &actorClient;
    actor.s.number = 2;
    actor.health = 100;
    actor.r.currentOrigin[0] = 60;
    memset(&g_entities[7], 0, sizeof(g_entities[7]));
    g_entities[7].client = &client;
    dragTest = 1;
    for(d = 0; d < NUM_PLAYER_CLASSES; ++d)
    for(setting = 0; setting <= 1; ++setting) {
        actorClient.sess.playerType = d;
        g_dragCorpse.integer = setting;
        VectorClear(client.ps.velocity);
        dragTraces = 0;
        Cmd_Activate2_f(&actor);
        if(dragTraces != 1 || fabs(client.ps.velocity[0] - setting * 110) > .001)
            ++errors;
    }
    actor.health = 0;
    dragTraces = 0;
    Cmd_Activate2_f(&actor);
    if(dragTraces) ++errors;
    dragTest = 0;
    g_entities[7] = savedTarget;
    g_dragCorpse = saved;
    return errors;
}

int main(void) {
    int kind, enabled, gate, bypass, splash, i, admitted, damageFlags, profiles = 0, errors = 0;
    if(strcmp(GAMEVERSION, "nitmod")) ++errors;
    dllEntry(EngineCallback);
    errors += CheckDoubleJump();
    errors += CheckSupplyAndSpawnCvars();
    errors += CheckLandmineLimitCvar();
    errors += CheckClassLimits();
    errors += CheckLimboPacks();
    errors += CheckIntermissionCvars();
    errors += CheckInactivityOptions();
    errors += CheckCorpseDrag();
    errors += CheckPlayerShove();
    errors += CheckCanisterKick();
    errors += CheckCanisterSpawn();
    errors += CheckBotEngineAdapters();
    errors += CheckBotEntityPosition();
    errors += CheckBotEntityVelocity();
    errors += CheckBotEntityOrientation();
    errors += CheckBotEyeAndBonePosition();
    errors += CheckBotWorldOBB();
    errors += CheckBotBoundsStages();
    errors += CheckBotClassnameCache();
    errors += CheckTeamItemClassnameCache();
    errors += CheckBotWorldAABB();
    errors += CheckScriptClassnameCache();
    errors += CheckTargetScriptNameHashes();
    errors += CheckCachedNameSearch();
    errors += CheckScriptTriggerHashLookup();
    errors += CheckTagConnectHashLookup();
    errors += CheckAccumHashTrigger();
    errors += CheckNamedHashTrigger();
    errors += CheckMineTransitions();
    errors += CheckMineThinkPipeline();
    errors += CheckFreeOrdering();
    for(kind = 0; kind < 5; ++kind) for(enabled = 0; enabled < 2; ++enabled)
    for(gate = 0; gate < 6; ++gate) for(bypass = 0; bypass < 2; ++bypass)
    for(splash = 0; splash < 6; ++splash) {
        gentity_t beforeTarget;
        gclient_t beforeOwner;
        gentity_t *target = &g_entities[MAX_CLIENTS];
        gentity_t *shake = &g_entities[MAX_CLIENTS + 1];
        gentity_t *attacker = &g_entities[ENTITYNUM_WORLD];
        memset(&level, 0, sizeof(level));
        expectedLink = expectedShake = NULL; linkCalls = shakeCalls = 0;
        traceCalls = boxCalls = expectedBoxes = 0;
        victimMode = splash >= 2; blockedSight = splash == 3 || splash == 5;
        chainMode = splash >= 4; victimTraces = painCalls = 0;
        memset(shake, 0, sizeof(*shake));
        memset(target, 0, sizeof(*target)); memset(attacker, 0, sizeof(*attacker));
        memset(&g_entities[1], 0, sizeof(g_entities[1]));
        memset(&ownerClient, 0, sizeof(ownerClient));
        g_entities[1].client = &ownerClient;
        g_entities[1].r.linked = qtrue;
        for(i = 0; i < BODY_QUEUE_SIZE; ++i) {
            gentity_t *body = &g_entities[MAX_CLIENTS + 2 + i];
            memset(body, 0, sizeof(*body));
            body->inuse = qtrue; body->r.linked = qtrue;
            level.bodyQue[i] = body;
        }
        ownerClient.ps.weapon = WP_SATCHEL_DET;
        ownerClient.ps.ammo[WP_SATCHEL_DET] = 2;
        ownerClient.ps.ammoclip[WP_SATCHEL_DET] = 1;
        /* Reserve a reusable slot for the real G_Spawn/G_TempEntity path. */
        level.time = 1000; level.num_entities = VICTIM_BASE + 3;
        level.numActiveAirstrikes[0] = 3; level.numActiveAirstrikes[1] = 5;
        g_gamestate.integer = GS_PLAYING;
        match_warmupDamage.integer = 0;
        target->s.number = MAX_CLIENTS; target->s.eType = ET_MISSILE;
        target->inuse = qtrue; target->health = 5;
        target->entstate = STATE_DEFAULT; target->classname = "test_projectile";
        target->think = NormalThink; target->nextthink = 9000;
        attacker->s.number = ENTITYNUM_WORLD;
        target->s.clientNum = 1;
        target->r.ownerNum = 1;
        VectorSet(target->s.pos.trBase, 12, -24, 36);
        target->s.pos.trType = TR_STATIONARY;
        VectorCopy(target->s.pos.trBase, target->r.currentOrigin);
        target->splashDamage = splash ? 100 : 0;
        target->splashRadius = 128;
        target->parent = attacker;
        for(i = 0; i < 3; ++i) {
            gentity_t *victim = &g_entities[VICTIM_BASE + i];
            memset(victim, 0, sizeof(*victim));
            victim->inuse = qtrue; victim->s.number = VICTIM_BASE + i;
            victim->classname = "test_splash_victim"; victim->health = 200;
            victim->takedamage = i != 2;
            victim->pain = VictimPain;
            VectorCopy(target->r.currentOrigin, victim->r.currentOrigin);
            victim->r.currentOrigin[0] += i == 1 ? 128 : 32;
            VectorCopy(victim->r.currentOrigin, victim->r.absmin);
            VectorCopy(victim->r.currentOrigin, victim->r.absmax);
        }
        if(chainMode) {
            gentity_t *secondary = &g_entities[VICTIM_BASE];
            secondary->s.eType = ET_MISSILE; secondary->s.weapon = WP_SMOKE_BOMB;
            secondary->s.pos.trType = TR_STATIONARY;
            VectorCopy(secondary->r.currentOrigin, secondary->s.pos.trBase);
            secondary->s.clientNum = secondary->r.ownerNum = 1;
            secondary->parent = attacker;
            secondary->think = NormalThink; secondary->nextthink = 9000;
            secondary->methodOfDeath = secondary->splashMethodOfDeath = MOD_SMOKEBOMB;
            secondary->pain = NULL;
            G_NITMOD_ConfigureSmokeDamage(secondary, 8);
            /* The engine double owns the linked absolute bounds. */
            VectorCopy(secondary->r.currentOrigin, secondary->r.absmin);
            VectorCopy(secondary->r.currentOrigin, secondary->r.absmax);
        }
        if(kind == 0 || kind == 4) {
            target->s.weapon = kind == 0 ? WP_GRENADE_LAUNCHER : WP_GRENADE_PINEAPPLE;
            target->methodOfDeath = MOD_GRENADE_LAUNCHER;
            G_NITMOD_ConfigureGrenadeDamage(target, enabled ? 1 : 0);
        } else if(kind == 1) {
            target->s.weapon = WP_SMOKE_BOMB;
            target->methodOfDeath = MOD_SMOKEBOMB;
            G_NITMOD_ConfigureSmokeDamage(target, enabled ? 8 : 0);
        } else if(kind == 2) {
            target->s.weapon = WP_SMOKE_MARKER;
            target->active = qtrue;
            target->s.teamNum = bypass ? TEAM_ALLIES : TEAM_AXIS;
            target->methodOfDeath = MOD_SMOKEGRENADE;
            G_NITMOD_ConfigureAirstrikeMarkerDamage(target, enabled ? 4 : 0);
        } else {
            target->s.weapon = WP_SATCHEL;
            target->methodOfDeath = MOD_SATCHEL;
            G_NITMOD_ConfigureSatchelDamage(target, enabled ? 2 : 0);
        }
        target->splashMethodOfDeath = target->methodOfDeath;
        if(gate == 1) target->entstate = STATE_INVISIBLE;
        if(gate == 2) target->entstate = STATE_UNDERCONSTRUCTION;
        if(gate == 3) level.intermissionQueued = 1;
        if(gate == 4 || gate == 5) g_gamestate.integer = GS_WARMUP;
        if(gate == 5) match_warmupDamage.integer = 2;
        admitted = enabled && (gate == 0 || gate == 5);
        damageFlags = bypass ? DAMAGE_NO_PROTECTION : 0;
        beforeTarget = *target;
        beforeOwner = ownerClient;
        G_Damage(target, attacker, attacker, NULL, NULL, 39, damageFlags, MOD_MP40);
        if(target->health != (admitted ? 1 : enabled ? 40 : 5) || target->think != NormalThink || target->nextthink != 9000) ++errors;
        G_Damage(target, attacker, attacker, NULL, NULL, 1, damageFlags, MOD_MP40);
        if(admitted) {
            if(target->health != 0 || target->think != G_ExplodeMissile ||
               target->nextthink != 1001 || target->r.contents != CONTENTS_CORPSE ||
               target->enemy != attacker) ++errors;
        } else if(memcmp(target, &beforeTarget, sizeof(beforeTarget)) ||
                  memcmp(&ownerClient, &beforeOwner, sizeof(beforeOwner))) ++errors;
        if(kind == 3 && admitted) {
            if(ownerClient.ps.ammo[WP_SATCHEL_DET] || ownerClient.ps.ammoclip[WP_SATCHEL_DET] ||
               ownerClient.ps.ammoclip[WP_SATCHEL] != 1 || ownerClient.ps.eventSequence != 1 ||
               ownerClient.ps.events[0] != EV_NOAMMO || ownerClient.ps.eventParms[0] != 0) ++errors;
        } else if(ownerClient.ps.ammo[WP_SATCHEL_DET] != 2 || ownerClient.ps.ammoclip[WP_SATCHEL_DET] != 1 ||
                  ownerClient.ps.ammoclip[WP_SATCHEL] || ownerClient.ps.eventSequence) ++errors;
        /* Real weapon ids exercise shake allocation and active marker cleanup.
         * The populated query uses non-client victims and scripted visibility;
         * callbacks do not perform world links or real collision detection. */
        G_RunThink(target);
        if(linkCalls || target->nextthink != (admitted ? 1001 : 9000)) ++errors;
        level.time = 1001;
        if(admitted) {
            expectedLink = target;
            expectedBoxes = splash ? (kind == 3 ? 2 : 1) : 0;
            if(kind != 1) expectedShake = shake;
        }
        G_RunThink(target);
        if(admitted) {
            if(linkCalls != 1 || target->s.eType != ET_GENERAL || !target->freeAfterEvent ||
               target->nextthink || target->s.eventSequence != 1 ||
               target->s.events[0] != EV_MISSILE_MISS || target->s.clientNum != 1 ||
               !VectorCompare(target->r.currentOrigin, target->s.pos.trBase)) ++errors;
            if(kind != 1) {
                if(shakeCalls != 1 || !(shake->r.svFlags & SVF_BROADCAST) ||
                   shake->s.onFireStart != target->splashDamage * 4 ||
                   !VectorCompare(shake->r.currentOrigin, target->r.currentOrigin)) ++errors;
            }
        } else if(linkCalls || target->nextthink != 9000 || target->s.eventSequence) ++errors;
        G_RunThink(target);
        if(linkCalls != (admitted ? 1 : 0) || shakeCalls != (admitted && kind != 1 ? 1 : 0) ||
           shake->inuse != (admitted && kind != 1) ||
           level.numActiveAirstrikes[0] != 3 - (admitted && kind == 2 && !bypass) ||
           level.numActiveAirstrikes[1] != 5 - (admitted && kind == 2 && bypass)) ++errors;
        if(traceCalls != (admitted && splash) || boxCalls != expectedBoxes ||
           !g_entities[1].r.linked) ++errors;
        for(i = 0; i < BODY_QUEUE_SIZE; ++i)
            if(!level.bodyQue[i]->r.linked || level.tempTraceIgnoreEnts[MAX_CLIENTS + 2 + i]) ++errors;
        if(level.tempTraceIgnoreEnts[1]) ++errors;
        if(victimTraces != (admitted && victimMode ? (blockedSight ? 10 : 1) : 0) ||
           painCalls != (admitted && victimMode && !blockedSight && !chainMode) ||
           g_entities[VICTIM_BASE].health != (chainMode ?
               (admitted && !blockedSight ? -35 : 40) :
               (admitted && victimMode && !blockedSight ? 125 : 200)) ||
           g_entities[VICTIM_BASE + 1].health != 200 ||
           g_entities[VICTIM_BASE + 2].health != 200) ++errors;
        if(chainMode) {
            gentity_t *secondary = &g_entities[VICTIM_BASE];
            int triggered = admitted && !blockedSight;
            if(secondary->think != (triggered ? G_ExplodeMissile : NormalThink) ||
               secondary->nextthink != (triggered ? 1002 : 9000) ||
               secondary->s.eType != ET_MISSILE || secondary->s.eventSequence ||
               (triggered && (secondary->enemy != attacker ||
                 secondary->r.contents != CONTENTS_CORPSE || secondary->free))) ++errors;
            /* Observe the second timer independently; primary state must remain
             * unchanged. The smoke secondary has no splash or shake branch. */
            beforeTarget = *target; beforeOwner = ownerClient;
            expectedLink = expectedShake = NULL;
            linkCalls = shakeCalls = traceCalls = boxCalls = expectedBoxes = 0;
            G_RunThink(secondary); /* still 1001: deferred, not recursive */
            if(linkCalls || secondary->s.eventSequence ||
               secondary->nextthink != (triggered ? 1002 : 9000)) ++errors;
            level.time = 1002;
            if(triggered) expectedLink = secondary;
            G_RunThink(secondary);
            G_RunThink(secondary);
            if(linkCalls != triggered || shakeCalls || traceCalls || boxCalls ||
               secondary->nextthink != (triggered ? 0 : 9000) ||
               secondary->s.eventSequence != triggered ||
               secondary->s.eType != (triggered ? ET_GENERAL : ET_MISSILE) ||
               secondary->freeAfterEvent != triggered ||
               (triggered && (secondary->s.events[0] != EV_MISSILE_MISS ||
                 secondary->s.clientNum != 1 ||
                 !VectorCompare(secondary->r.currentOrigin, secondary->s.pos.trBase))) ||
               memcmp(target, &beforeTarget, sizeof(beforeTarget)) ||
               memcmp(&ownerClient, &beforeOwner, sizeof(beforeOwner))) ++errors;
        }
        ++profiles;
    }
    printf("Real G_Damage: %d projectile/gate profiles, %d hits, %d errors\n", profiles, profiles * 2, errors);
    return errors != 0;
}
