#include "../src_2.60/cgame/cg_nitmod_projectiles.h"

static int missileDrawCount, missileSoundCount;
static refEntity_t missileDraw;
static int QDECL MissilePresentationEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_R_ADDREFENTITYTOSCENE) {
        missileDraw = *va_arg(args, const refEntity_t *); ++missileDrawCount;
    } else if(command == CG_S_ADDLOOPINGSOUND) ++missileSoundCount;
    else exit(2);
    va_end(args); return 0;
}

static int CheckMissilePresentation(void) {
    centity_t cent;
    int original, weapon, frame, stationary, i, errors = 0;
    for(original = 0; original < 2; ++original) for(weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon)
    for(stationary = 0; stationary < 2; ++stationary) {
        vec3_t previous = {0, 0, 0};
        memset(&cent, 0, sizeof(cent));
        cent.currentState.weapon = weapon;
        cent.currentState.pos.trType = stationary ? TR_STATIONARY : TR_GRAVITY;
        cent.currentState.time = 35;
        VectorSet(cent.currentState.pos.trDelta, 0, 1, 0);
        VectorSet(cent.currentState.pos.trBase, 1, 2, 3);
        VectorSet(cent.lerpAngles, 12, 13, 14);
        for(frame = 0; frame < 4; ++frame) {
            vec3_t actual[3], expected[3] = {{0}}, direction, angles;
            int displaced = weapon == WP_MORTAR_SET || (original &&
                (weapon == WP_PANZERFAUST || weapon == WP_GPG40 || weapon == WP_M7));
            /* Last frame repeats the prior position and must point up. */
            VectorSet(cent.lerpOrigin, 11, 2, frame >= 2 ? -7 : 3 - frame * 5);
            if(displaced) {
                VectorSubtract(cent.lerpOrigin, frame ? previous : cent.currentState.pos.trBase, direction);
                VectorCopy(cent.lerpOrigin, previous);
            } else VectorCopy(cent.currentState.pos.trDelta, direction);
            if(VectorNormalize2(direction, expected[0]) == 0) expected[0][2] = 1;
            AxisToAngles(expected, angles);
            RotateAroundDirection(expected, stationary ? 35 : (1000 + frame * 100) / 4);
            if(!CG_NitmodMissileAxis(&cent, actual, 1000 + frame * 100, original)) ++errors;
            for(i = 0; i < 9; ++i)
                if(fabs(((float *)actual)[i] - ((float *)expected)[i]) > .0001f) ++errors;
            for(i = 0; i < 3; ++i) {
                if(cent.rawOrigin[i] != (displaced ? previous[i] : 0)) ++errors;
                if(fabs(cent.lerpAngles[i] - (original ? angles[i] : 12 + i)) > .0001f) ++errors;
            }
        }
    }
    {
        snapshot_t snap, *savedSnap = cg.snap;
        weaponInfo_t savedWeapon = cg_weapons[WP_MP40];
        int savedClient = cg.clientNum, savedTrail = cg_trailparticles.integer;
        int savedTime = cg.time;
        qhandle_t savedModel = cgs.gameModels[1];
        memset(&snap, 0, sizeof(snap)); cg.snap = &snap; cg.clientNum = 0; cg.time = 100000;
        memset(&cent, 0, sizeof(cent)); memset(&cg_weapons[WP_MP40], 0, sizeof(weaponInfo_t));
        cg_weapons[WP_MP40].missileModel = 123;
        cent.currentState.number = 1; cent.currentState.weapon = WP_MP40;
        cent.currentState.eType = ET_MISSILE;
        VectorSet(cent.currentState.pos.trDelta, 0, 1, 0);
        cg_weapons[WP_MP40].missileSound = -1;
        missileDrawCount = missileSoundCount = 0; dllEntry(MissilePresentationEngine);
        CG_Missile(&cent);
        if(missileDrawCount != 1 || missileSoundCount || missileDraw.hModel != 123 ||
           missileDraw.axis[0][1] != 1) ++errors;
        cg_trailparticles.integer = 0; cgs.gameModels[1] = 234;
        for(i = 0; i < 2; ++i) {
            cent.currentState.eType = i ? ET_EXPLO_PART : ET_FP_PARTS;
            cent.currentState.modelindex = 1; missileDrawCount = 0; CG_Missile(&cent);
            if(missileDrawCount != 1 || missileDraw.hModel != 234) ++errors;
            cent.currentState.modelindex = MAX_MODELS; missileDrawCount = 0; CG_Missile(&cent);
            if(missileDrawCount) ++errors;
            cent.currentState.modelindex = -1; CG_Missile(&cent);
            if(missileDrawCount) ++errors;
        }
        cent.currentState.eType = ET_MISSILE;
        for(i = 0; i < 4; ++i) {
            entityState_t before;
            cent.currentState.weapon = i & 1 ? -1 : WP_NUM_WEAPONS;
            cent.currentState.number = i < 2 ? 1 : MAX_GENTITIES;
            before = cent.currentState; missileDrawCount = missileSoundCount = 0;
            CG_Missile(&cent);
            if(missileDrawCount || missileSoundCount || memcmp(&before, &cent.currentState, sizeof(before))) ++errors;
        }
        cent.currentState.weapon = WP_MP40;
        CG_Missile(&cent); CG_Missile(NULL);
        if(missileDrawCount || missileSoundCount) ++errors;
        {
            static const int owners[] = {-1, 0, MAX_CLIENTS - 1, MAX_CLIENTS, INT_MAX};
            weaponInfo_t savedArty = cg_weapons[WP_ARTY];
            vec3_t savedPositions[MAX_CLIENTS];
            int savedTimes[MAX_CLIENTS], owner, j;
            memcpy(savedPositions, cg.artilleryRequestPos, sizeof(savedPositions));
            memcpy(savedTimes, cg.artilleryRequestTime, sizeof(savedTimes));
            memset(&cg_weapons[WP_ARTY], 0, sizeof(weaponInfo_t));
            cent.currentState.weapon = WP_ARTY; cent.currentState.number = 1;
            cent.currentState.otherEntityNum2 = 1;
            cent.currentState.teamNum = cgs.clientinfo[0].team;
            VectorSet(cent.lerpOrigin, 42, 43, 44);
            for(owner = 0; owner < 5; ++owner) {
                memset(cg.artilleryRequestTime, 0, sizeof(cg.artilleryRequestTime));
                cent.currentState.clientNum = owners[owner]; CG_Missile(&cent);
                for(j = 0; j < MAX_CLIENTS; ++j) {
                    if(cg.artilleryRequestTime[j] != (j == owners[owner] ? cg.time : 0)) ++errors;
                    if(j == owners[owner] && !VectorCompare(cg.artilleryRequestPos[j], cent.lerpOrigin)) ++errors;
                }
            }
            if(missileDrawCount || missileSoundCount) ++errors;
            cg_weapons[WP_ARTY] = savedArty;
            memcpy(cg.artilleryRequestPos, savedPositions, sizeof(savedPositions));
            memcpy(cg.artilleryRequestTime, savedTimes, sizeof(savedTimes));
        }
        dllEntry(Engine); cg_weapons[WP_MP40] = savedWeapon; cgs.gameModels[1] = savedModel;
        cg.snap = savedSnap; cg.clientNum = savedClient; cg.time = savedTime;
        cg_trailparticles.integer = savedTrail;
    }
    return errors;
}
