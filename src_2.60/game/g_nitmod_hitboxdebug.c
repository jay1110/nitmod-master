#include "g_local.h"
#include "g_nitmod_mdx.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_hitboxdebug.h"
#include "nitmod_entity_ids.h"

/* Original G_EntitiesFree 0xe7160 counts every unallocated entity slot,
 * including the tail beyond level.num_entities; ET's boolean helper does not. */
static int FreeDebugSlots(void) {
    int i, used = MAX_CLIENTS;
    for(i = MAX_CLIENTS; i < level.num_entities && i < MAX_GENTITIES; ++i)
        if(g_entities[i].inuse) ++used;
    return MAX_GENTITIES - used;
}

/* Original G_RailBox 0x6b300. The event encodes two corners and 0..255
 * RGB, not ET's clientinfo color index. Its stable group is entityId+1.
 * Float-to-int color conversion is truncation, including .5*255 -> 127. */
static void DebugRailBox(const vec3_t origin, const vec3_t mins,
    const vec3_t maxs, const vec3_t color, int group) {
    vec3_t start;
    gentity_t *event;
    int i;
    VectorAdd(origin, mins, start);
    event = G_TempEntity(start, EV_RAILTRAIL);
    VectorAdd(origin, maxs, event->s.origin2);
    for(i = 0; i < 3; ++i) event->s.angles[i] = (float)(int)(color[i] * 255.f);
    event->s.dmgFlags = 1;
    event->s.effect1Time = group + 1;
}

void G_NITMOD_DrawEntityHitbox(gentity_t *ent) {
    char selector[MAX_CVAR_VALUE_STRING];
    int mode, category;
    vec3_t color = {0,1,0};
    if(!ent || !ent->inuse) return;
    mode = G_NITMOD_LegacyCvarInteger("g_debugHitboxes", 0);
    G_NITMOD_LegacyCvarString("g_debugHitboxes", selector, sizeof(selector), "0");
    if(!mode && strlen(selector) <= 2) return;
    if(FreeDebugSlots() <= 63) return;
    if(selector[0] && Q_isalpha((signed char)selector[0])) {
        if(!ent->classname || strcmp(selector, ent->classname)) return;
        VectorSet(color, .5f, 0, .5f);
    } else {
        /* Jump table from G_DrawEntBBox 0x7d8be..0x7db00. Convert the
         * original eType ABI explicitly; native enum contains extra types. */
        switch(NITMOD_OriginalEntityType(ent->s.eType)) {
        case 0: category = 14; break;
        case 1: case 38: category = 3; break;
        case 2: category = 6; break;
        case 3: case 34: category = 4; break;
        case 4: case 30: category = 7; break;
        case 8: case 9: case 11: case 12: case 43: case 44: case 45: category = 10; break;
        case 14: category = 5; break;
        case 15: case 17: case 19: case 27: category = 12; break;
        case 18: category = 13; break;
        case 31: case 32: case 33: category = 9; break;
        case 41: category = 8; break;
        case 47: case 48: case 49: case 50: category = 11; break;
        default: return;
        }
        if(mode != category) return;
    }
    DebugRailBox(ent->r.currentOrigin, ent->r.mins, ent->r.maxs, color, ent->s.number);
}

static void DebugPlayerBounds(gentity_t *ent, qboolean endFrame) {
    vec3_t mins, maxs, bodyColor = {0,0,1}, headColor = {0,0,1}, legColor = {0,0,1};
    gentity_t *part;
    int hitboxes = G_NITMOD_LegacyCvarInteger("g_hitboxes", 0);
    if(endFrame && hitboxes != 0) {
        G_NITMOD_MDXDrawPlayer(ent);
        return;
    }
    VectorCopy(ent->r.mins, mins);VectorCopy(ent->r.maxs, maxs);
    if(hitboxes < 1) {
        if(G_NITMOD_LegacyCvarInteger("g_realBody", 0) & 1) {
            mins[0] += 3;mins[1] += 3;maxs[0] -= 3;maxs[1] -= 3;
        }
        maxs[2] = G_NITMOD_HitboxHeight(ent, NULL);
    }
    if(endFrame) { VectorSet(headColor, 1,0,0);VectorSet(legColor, 1,0,1); }
    DebugRailBox(ent->r.currentOrigin, mins, maxs, bodyColor, ent->s.number);
    part = G_BuildHead(ent);
    if(part) {
        /* EndFrame uses the player key for the head; Think uses the
         * temporary head entity number. This asymmetry is in the ELF. */
        DebugRailBox(part->r.currentOrigin, part->r.mins, part->r.maxs,
            headColor, (endFrame ? ent->s.number : part->s.number) | 0x400);
        G_FreeEntity(part);
    }
    if(!endFrame || (ent->client->ps.eFlags & (EF_PRONE | EF_DEAD))) {
        part = G_BuildLeg(ent);
        if(part) {
            DebugRailBox(part->r.currentOrigin, part->r.mins, part->r.maxs,
                legColor, part->s.number | 0x800);
            G_FreeEntity(part);
        }
    }
}

void G_NITMOD_DrawClientThinkHitboxes(gentity_t *ent) {
    if(ent && ent->client &&
       (G_NITMOD_LegacyCvarInteger("g_debugPlayerHitboxes", 0) & 2))
        DebugPlayerBounds(ent, qfalse);
}
void G_NITMOD_DrawClientEndHitboxes(gentity_t *ent) {
    if(ent && ent->client &&
       (G_NITMOD_LegacyCvarInteger("g_debugPlayerHitboxes", 0) & 1))
        DebugPlayerBounds(ent, qtrue);
}

/* Original nitrox_DrawHitboxesOnShoot 0xf92a0: before historical rewind. */
void G_NITMOD_DrawShotHitboxes(gentity_t *attacker) {
 int i;vec3_t mins,maxs;const vec3_t white={1,1,1};
 for(i=0;i<level.numConnectedClients;i++) {
  gentity_t *target=&g_entities[level.sortedClients[i]];
  if(!target->inuse || !target->client || target==attacker || target->client->sess.sessionTeam==TEAM_SPECTATOR ||
   !target->r.linked || (target->client->ps.pm_flags&PMF_LIMBO) ||
   (target->client->ps.pm_type!=PM_NORMAL && target->client->ps.pm_type!=PM_DEAD)) continue;
  VectorCopy(target->r.mins,mins);VectorCopy(target->r.maxs,maxs);
  if(G_NITMOD_LegacyCvarInteger("g_hitboxes",0)<1) {
   if(G_NITMOD_LegacyCvarInteger("g_realBody",0)&1) {mins[0]+=3;mins[1]+=3;maxs[0]-=3;maxs[1]-=3;}
   maxs[2]=G_NITMOD_HitboxHeight(target,attacker);
  }
  DebugRailBox(target->r.currentOrigin,mins,maxs,white,-1);
 }
}
void G_NITMOD_DrawHistoricalHitbox(gentity_t *target) {
 int color=target->client->ps.clientNum;
 if(color>31) {color>>=1;if(color==32) color=31;}
 if(color<0) color=0;if(color>31) color=31;
 DebugRailBox(target->r.currentOrigin,target->r.mins,target->r.maxs,g_color_table[color],target->s.number|0x1000);
}
