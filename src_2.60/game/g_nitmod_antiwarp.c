#include "g_local.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_antiwarp.h"

/* Original i386 time/frame subtraction wraps before signed comparison. */
static int WarpDelta(int newer, int older) {
    return (int)((unsigned int)newer - (unsigned int)older);
}

extern void ClientThink_real(gentity_t *ent);
extern void PmovePredict(pmove_t *move, float seconds);

qboolean G_NITMOD_DoAntiwarp(gentity_t *ent) {
    gclient_t *cl;
    if (!G_NITMOD_LegacyCvarInteger("g_antiwarp", 1) ||
        g_gamestate.integer == GS_INTERMISSION) return qfalse;
    if (!ent || !ent->client) return qtrue;
    cl = ent->client;
    return cl->sess.sessionTeam != TEAM_SPECTATOR &&
        !(cl->ps.pm_flags & PMF_LIMBO) && !cl->pers.localClient &&
        WarpDelta(level.time, cl->pers.connectTime) > 4999;
}

/* Original etpro_AddUsercmd: 512 commands; an overflowing enqueue replaces
 * the oldest entry and advances the head without increasing the count. */
void G_NITMOD_QueueUsercmd(gentity_t *ent, const usercmd_t *cmd) {
    gclient_t *cl = ent->client;
    cl->nitmodWarpCommands[(cl->nitmodWarpHead + cl->nitmodWarpCount) % 512] = *cmd;
    if (cl->nitmodWarpCount >= 512) cl->nitmodWarpHead = (cl->nitmodWarpHead + 1) % 512;
    else ++cl->nitmodWarpCount;
}

static void RunCommand(gentity_t *ent, const usercmd_t *cmd) {
    ent->client->pers.oldcmd = ent->client->pers.cmd;
    ent->client->pers.cmd = *cmd;
    ClientThink_real(ent);
}

/* DoClientThinks ELF 0x3c770. The debt at original +0x1a88 is FLOAT
 * (flds/fstps); integer-looking decompiler assignments are not its contract. */
void G_NITMOD_RunUsercmds(gentity_t *ent) {
    gclient_t *cl = ent->client;
    int now, before, latest, previous, dropAge = 800;
    if (cl->nitmodWarpCount <= 0) return;
    before = cl->nitmodWarpCount;
    now = trap_Milliseconds();
    if (now < cl->nitmodWarpTime) cl->nitmodWarpBudget = 0;
    else cl->nitmodWarpBudget -= (float)(WarpDelta(now, cl->nitmodWarpTime));
    if (cl->nitmodWarpCount < 2 && cl->nitmodWarpBudget < 0) cl->nitmodWarpBudget = 0;
    cl->nitmodWarpTime = now;
    previous = cl->ps.commandTime;
    latest = cl->nitmodWarpCommands[(cl->nitmodWarpHead + cl->nitmodWarpCount - 1) % 512].serverTime;
    while (cl->nitmodWarpCount > 0) {
        usercmd_t *cmd = &cl->nitmodWarpCommands[cl->nitmodWarpHead];
        int originalTime = cmd->serverTime, age = WarpDelta(latest, originalTime);
        int msec = WarpDelta(originalTime, previous), step;
        float scale, cost;
        if (age >= dropAge) {
            cl->ps.commandTime = previous = originalTime;
            dropAge = 600;
        } else if (msec > 0 && age >= 0) {
            int movement = abs((int)cmd->forwardmove);
            if (abs((int)cmd->rightmove) > movement) movement = abs((int)cmd->rightmove);
            if (ent->waterlevel && abs((int)cmd->upmove) > movement) movement = abs((int)cmd->upmove);
            scale = movement / 127.0f;
            step = msec > 50 ? 50 : msec;
            cost = step * scale * 0.98039216f;
            if (cost + cl->nitmodWarpBudget >= 75.0f) {
                if (cost < 75.0f && age + cost < 600.0f) break;
                if (scale <= 0.0f) break;
                step = (int)ceilf((75.0f - cl->nitmodWarpBudget) / scale);
                if (step < 1) break;
                cost = step * scale * 0.98039216f;
            }
            cl->nitmodWarpBudget += cost;
            cl->ps.commandTime = previous;
            if (msec <= 50 && step == msec) {
                RunCommand(ent, cmd);
                previous = cl->ps.commandTime;
            } else {
                cmd->serverTime = (int)((unsigned int)previous + (unsigned int)step);
                RunCommand(ent, cmd);
                cmd->serverTime = originalTime;
                /* A denial/disconnect in the native think path must not spin. */
                if (cl->ps.commandTime <= previous) break;
                previous = cl->ps.commandTime;
                if (cost <= 0.1f) break;
                continue;
            }
        }
        if (cl->nitmodWarpCount <= 0) break;
        cl->nitmodWarpHead = (cl->nitmodWarpHead + 1) % 512;
        --cl->nitmodWarpCount;
    }
    /* Original ps +0xec, the otherwise unused multiplayer stats[7]. */
    cl->ps.stats[STAT_CAPTUREHOLD_BLUE] = WarpDelta(latest, previous);
    if (G_NITMOD_LegacyCvarInteger("g_antiwarp", 1) & 32)
        trap_SendServerCommand(ent - g_entities, va("cp \"%d %d\n\"",
            WarpDelta(latest, previous), before - cl->nitmodWarpCount));
}

void G_NITMOD_PrepareUsercmd(gentity_t *ent) {
    gclient_t *cl = ent->client;
    int maximum = G_NITMOD_LegacyCvarInteger("g_maxWarp", 4);
    if (cl->nitmodWarpPending && maximum && G_NITMOD_DoAntiwarp(ent)) {
        int frames = WarpDelta(level.framenum, cl->nitmodLastUpdateFrame);
        if (frames > maximum) frames = maximum;
        cl->nitmodWarpCorrected = qtrue;
        cl->ps.commandTime = (int)((unsigned int)level.previousTime + (unsigned int)frames *
            (unsigned int)WarpDelta(level.previousTime, level.time));
    }
    cl->nitmodWarpPending = qfalse;
    cl->nitmodLastUpdateFrame = level.framenum;
}

/* Original G_PredictPmove only advances the linked entity/snapshot. Restore
 * authoritative player movement afterwards, so missing commands earn no XP,
 * trigger no weapons and do not run timers a second time. */
void G_NITMOD_PredictPmove(gentity_t *ent, float seconds) {
    gclient_t *cl;
    pmove_t move;
    vec3_t origin, velocity;
    int flags, pmFlags, ground, pmTime;
    if (!ent || !ent->inuse || !ent->r.linked || !ent->client) return;
    cl = ent->client;
    if ((cl->sess.sessionTeam != TEAM_AXIS && cl->sess.sessionTeam != TEAM_ALLIES) ||
        (cl->ps.pm_flags & (PMF_LIMBO | PMF_TIME_LOCKPLAYER)) || ent->health <= 0 ||
        cl->ps.pm_type != PM_NORMAL || (cl->ps.eFlags & (EF_PRONE | EF_MOUNTEDTANK)) ||
        ent->waterlevel >= 2 || (!cl->ps.velocity[0] && !cl->ps.velocity[1])) return;
    VectorCopy(cl->ps.origin, origin); VectorCopy(cl->ps.velocity, velocity);
    flags = cl->ps.eFlags; pmFlags = cl->ps.pm_flags;
    ground = cl->ps.groundEntityNum; pmTime = cl->ps.pm_time;
    memset(&move, 0, sizeof(move));
    move.ps = &cl->ps; move.pmext = &cl->pmext; move.character = cl->pers.character;
    /* Original G_PredictPmove 0x46e2f: 0x02010001. */
    move.tracemask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_BODY;
    move.trace = trap_TraceCapsuleNoEnts; move.pointcontents = trap_PointContents;
    move.noFootsteps = qtrue;
    VectorCopy(ent->r.mins, move.mins); VectorCopy(ent->r.maxs, move.maxs);
    PmovePredict(&move, seconds);
    VectorCopy(cl->ps.origin, ent->s.pos.trBase); VectorCopy(cl->ps.velocity, ent->s.pos.trDelta);
    ent->s.groundEntityNum = cl->ps.groundEntityNum; ent->s.eFlags = cl->ps.eFlags;
    VectorCopy(cl->ps.origin, ent->r.currentOrigin); trap_LinkEntity(ent);
    cl->ps.eFlags = flags; cl->ps.pm_flags = pmFlags;
    cl->ps.groundEntityNum = ground; cl->ps.pm_time = pmTime;
    VectorCopy(origin, cl->ps.origin); VectorCopy(velocity, cl->ps.velocity);
}

void G_NITMOD_SkipCorrection(gentity_t *ent) {
    gclient_t *cl = ent->client;
    int missed = WarpDelta(WarpDelta(level.framenum, cl->nitmodLastUpdateFrame), 1);
    int maximum = G_NITMOD_LegacyCvarInteger("g_maxWarp", 4);
    cl->ps.eFlags &= ~EF_CONNECTION;
    if (maximum && missed > maximum && G_NITMOD_DoAntiwarp(ent)) cl->nitmodWarpPending = qtrue;
    if (G_NITMOD_LegacyCvarInteger("g_skipCorrection", 1) && missed > 0 && !cl->nitmodWarpCorrected && !G_NITMOD_DoAntiwarp(ent)) {
        int fps = trap_Cvar_VariableIntegerValue("sv_fps");
        if (missed >= 3) { cl->ps.eFlags |= EF_CONNECTION; ent->s.eFlags |= EF_CONNECTION; missed = 2; }
        if (fps > 0) G_NITMOD_PredictPmove(ent, missed / (float)fps);
        SnapVector(ent->s.pos.trBase);
    }
    cl->nitmodWarpCorrected = qfalse;
}
