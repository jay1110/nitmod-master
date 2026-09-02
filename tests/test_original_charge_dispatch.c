#include "cg_local.h"
#include "cg_nitmod_config.h"
#include <stdio.h>
#include <stdlib.h>
#include "check_doublejump.h"
extern void dllEntry(int (QDECL *)(int, ...));
extern animStringItem_t weaponStrings[];
extern qboolean BG_ParseConditions(char **, animScriptItem_t *);
extern qboolean BG_EvaluateConditions(int, animScriptItem_t *);
static int CheckOriginalAnimationConditions(const char *path) {
    static animModelInfo_t model;
    static animScriptData_t scripts;
    static animation_t animationStubs[MAX_MODEL_ANIMATIONS];
    const char *extra[] = {"Poison Syringe", "Bomb", "Poison Bomb", "Poison Landmine"};
    char *text, *end, *line;
    long size;
    FILE *file = fopen(path, "rb");
    int i, count = 0, errors = 0;
    if(!file) return 1;
    fseek(file, 0, SEEK_END); size = ftell(file); rewind(file);
    if(size <= 0 || size > 1024 * 1024) { fclose(file); return 1; }
    text = malloc(size + 1);
    if(!text) { fclose(file); return 1; }
    if(fread(text, 1, size, file) != (size_t)size) { fclose(file); free(text); return 1; }
    fclose(file); text[size] = 0;
    /* Supply only synthetic model metadata for script-referenced names.
     * This exercises the full script grammar, not real MDX/model loading. */
    {
        char *cursor = text, *token;
        while(*(token = COM_Parse(&cursor))) {
            if(!Q_stricmp(token, "both") || !Q_stricmp(token, "legs") || !Q_stricmp(token, "torso")) {
                token = COM_Parse(&cursor);
                for(i = 0; i < model.numAnimations; ++i)
                    if(!Q_stricmp(animationStubs[i].name, token)) break;
                if(i == model.numAnimations) {
                    if(!*token || i >= MAX_MODEL_ANIMATIONS) { free(text); return 1; }
                    Q_strncpyz(animationStubs[i].name, token, sizeof(animationStubs[i].name));
                    animationStubs[i].nameHash = BG_StringHashValue(token);
                    animationStubs[i].duration = 100;
                    animationStubs[i].numFrames = 1;
                    model.animations[model.numAnimations++] = &animationStubs[i];
                }
            }
        }
    }
    BG_InitWeaponStrings();
    for(i = 1; i < WP_NUM_WEAPONS; ++i) {
        gitem_t *item;
        for(item = bg_itemlist + 1; item->classname; ++item)
            if(item->giType == IT_WEAPON && item->giTag == i) break;
        if(item->classname && BG_IndexForString(item->pickup_name, weaponStrings, qfalse) != i) ++errors;
    }
    for(i = 0; i < 4; ++i) {
        char condition[128], *cursor = condition;
        animScriptItem_t item;
        int bit;
        memset(&item, 0, sizeof(item));
        Com_sprintf(condition, sizeof(condition), "weapons %s\n", extra[i]);
        BG_ParseConditions(&cursor, &item);
        if(item.numConditions != 1) ++errors;
        for(bit = 0; bit < 64; ++bit)
            if(!!COM_BitCheck(item.conditions[0].value, bit) != (bit == WP_NUM_WEAPONS + i)) ++errors;
    }
    if(BG_IndexForString("not-a-weapon", weaponStrings, qtrue) != -1) ++errors;
    end = strstr(text, "\nANIMATIONS");
    if(!end) { free(text); return 1; }
    *end = 0;
    /* Execute the original definitions, not rewritten/filtered operands. */
    BG_AnimParseAnimScript(&model, &scripts, path, text);
    *end = '\n';
    BG_AnimParseAnimScript(&model, &scripts, path, text);
    if(model.numScriptItems < 50 || model.numAnimations < 50) ++errors;
    {
        int extraIndex, candidate, client, evaluated = 0;
        for(extraIndex = 0; extraIndex < 4; ++extraIndex) {
            char expression[128], *cursor = expression;
            animScriptItem_t item;
            memset(&item, 0, sizeof(item));
            Com_sprintf(expression, sizeof(expression), "weapons %s\n", extra[extraIndex]);
            BG_ParseConditions(&cursor, &item);
            for(client = 0; client < MAX_CLIENTS; ++client) {
                for(candidate = 0; candidate < WP_NUM_WEAPONS + 4; ++candidate) {
                    BG_UpdateConditionValue(client, ANIM_COND_WEAPON, candidate, qtrue);
                    if(!!BG_EvaluateConditions(client, &item) !=
                       (candidate == WP_NUM_WEAPONS + extraIndex)) ++errors;
                    ++evaluated;
                }
            }
        }
        printf("Animation-only condition separation: %d evaluations\n", evaluated);
    }
    {
        struct { const char *weapon; const char *animation; } cases[] = {
            {"Poison Syringe", "stand_knife"},
            {"Bomb", "stand_grenade"},
            {"Poison Bomb", "stand_grenade"},
            {"Poison Landmine", "stand_medpack"},
            {"Tripmine", "stand_grenade"},
            {"Smoke Bomb", "stand_grenade"},
            {"Landmine", "stand_medpack"}
        };
        int test;
        for(test = 0; test < sizeof(cases) / sizeof(cases[0]); ++test) {
            int selected, weapon = BG_IndexForString((char *)cases[test].weapon, weaponStrings, qfalse);
            memset(scripts.clientConditions[0], 0, sizeof(scripts.clientConditions[0]));
            BG_UpdateConditionValue(0, ANIM_COND_WEAPON, weapon, qtrue);
            selected = BG_GetAnimScriptAnimation(0, &model, AISTATE_COMBAT, ANIM_MT_IDLE);
            if(selected < 0 || selected >= model.numAnimations ||
               strcmp(model.animations[selected]->name, cases[test].animation)) ++errors;
        }
    }
    {
        int itemIndex, commandIndex, part, commands = 0;
        for(itemIndex = 0; itemIndex < model.numScriptItems; ++itemIndex) {
            animScriptItem_t *item = &model.scriptItems[itemIndex];
            for(commandIndex = 0; commandIndex < item->numCommands; ++commandIndex) {
                animScriptCommand_t *command = &item->commands[commandIndex];
                ++commands;
                for(part = 0; part < 2; ++part) {
                    if(command->bodyPart[part] > 0 &&
                       (command->animIndex[part] < 0 || command->animIndex[part] >= model.numAnimations)) ++errors;
                }
            }
        }
        if(commands < 50) ++errors;
        printf("Original script parsed: %d model-name stubs, %d items, %d commands (not MDX validation)\n",
               model.numAnimations, model.numScriptItems, commands);
    }
    line = end + 1;
    while(line && *line) {
        char *next = strchr(line, '\n'), *cursor = line;
        if(next) *next = 0;
        while(*cursor == ' ' || *cursor == '\t') ++cursor;
        if(!strncmp(cursor, "weapons ", 8)) {
            animScriptItem_t item;
            memset(&item, 0, sizeof(item));
            BG_ParseConditions(&cursor, &item);
            if(!item.numConditions) ++errors;
            ++count;
        }
        line = next ? next + 1 : NULL;
    }
    free(text);
    return errors + (count < 50);
}
static const char *fields[21] = {"ct", "11", "22", "33", "44", "55", "66", "77", "88", "99", "110", "121"};
static int argcValue = 11, prints;
static int bannerValue;
static int ncsTest, ncsAssets;
static int hitTest, hitValue, hitPlays, hitSound;
static int shoveTest, shoveValue, shovePlays, shoveEntity;
static int greetingTest, greetingValue, greetingLoads, greetingPlays, greetingHandle;
static int forceTest, forceSets, forceRegisters;
static char forceCurrent[256], forceLastName[256], forceLastValue[256];
static vmCvar_t *hitCvar;
static char *weaponCursor;
static int sourceLoads, sourceFrees, mediaSounds, sentCapabilities;
static int medicSounds, medicEntity, medicHandle;
static int landingTest, landingPlays, hurtPlays;
static int CheckOriginalLanding(void) {
    centity_t cent;
    int surface, bits, errors = 0;
    memset(&cent, 0, sizeof(cent));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.media.landHurt = 81;
    for(surface = 0; surface < FOOTSTEP_TOTAL; ++surface) cgs.media.landSound[surface] = 82;
    cent.currentState.number = 5;
    cent.currentState.clientNum = 5;
    cg.predictedPlayerState.clientNum = 5;
    cg.time = 12345;
    landingTest = 1;
    for(surface = -1; surface <= 255; ++surface) for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
        cent.currentState.event = 17 | bits;
        cent.currentState.eventParm = surface;
        cent.pe.painTime = 0; cg.landTime = 0; cg.landChange = 0;
        landingPlays = hurtPlays = 0;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(hurtPlays != 1 || cent.pe.painTime != cg.time || cg.landTime != cg.time || cg.landChange != -24 ||
           cent.currentState.event != (17 | bits) || cent.currentState.eventParm != surface) ++errors;
        if(surface && landingPlays != (surface > 0 && surface < FOOTSTEP_TOTAL)) ++errors;
    }
    landingTest = 0;
    return errors;
}
static int pmTest, pmValue, pmPlays, pmLoads;
static int CheckPrivateMessageSound(void) {
    centity_t cent;
    int value, target, bits, errors = 0;
    memset(&cent, 0, sizeof(cent));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cg.clientNum = 5;
    pmTest = 1; pmLoads = 0;
    NITMOD_ClearConfigStrings();
    for(value = -1; value <= 1; ++value) for(target = 4; target <= 5; ++target)
        for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
            pmValue = value; pmPlays = 0;
            cent.currentState.number = target;
            cent.currentState.event = 98 | bits;
            CG_EntityEvent(&cent, cent.lerpOrigin);
            if(pmPlays != (value != 0 && target == 5) || cent.currentState.event != (98 | bits)) ++errors;
        }
    if(pmLoads != 1) ++errors;
    NITMOD_ClearConfigStrings();
    CG_EntityEvent(&cent, cent.lerpOrigin);
    if(pmLoads != 2) ++errors;
    pmTest = 0;
    return errors;
}
static int CheckMedicEvents(void) {
    static gameState_t saved;
    centity_t cent;
    int mode, team, bits, errors = 0;
    const char *info[] = {"\\gamename\\etmain", "\\gamename\\nitmod", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    saved = cgs.gameState;
    cgs.media.sndMedicCall[0] = 71;
    cgs.media.sndMedicCall[1] = 72;
    for(mode = 0; mode < 3; ++mode) {
        memset(&cgs.gameState, 0, sizeof(cgs.gameState));
        cgs.gameState.dataCount = 1;
        /* Same synthetic serverinfo format as the TAGCONNECT fixture. */
        cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
        strcpy(cgs.gameState.stringData + 1, info[mode]);
        if(!!NITMOD_UsesOriginalProtocol() != (mode == 1)) ++errors;
        for(team = TEAM_FREE; team <= TEAM_SPECTATOR; ++team) {
            for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
                entityState_t before;
                memset(&cent, 0, sizeof(cent));
                cent.currentState.number = MAX_CLIENTS - 1;
                cent.currentState.event = (mode == 1 ? 93 : EV_MEDIC_CALL) | bits;
                cgs.clientinfo[MAX_CLIENTS - 1].team = team;
                before = cent.currentState;
                medicSounds = 0;
                CG_EntityEvent(&cent, cent.lerpOrigin);
                if(memcmp(&before, &cent.currentState, sizeof(before))) ++errors;
                if(medicSounds != (team == TEAM_AXIS || team == TEAM_ALLIES)) ++errors;
                if(medicSounds && (medicEntity != MAX_CLIENTS - 1 ||
                   medicHandle != (team == TEAM_AXIS ? 71 : 72))) ++errors;
            }
        }
        cent.currentState.number = MAX_CLIENTS;
        medicSounds = 0;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(medicSounds) ++errors;
        cent.currentState.number = -1;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(medicSounds) ++errors;
    }
    cgs.gameState = saved;
    return errors;
}
static int CheckSharedWeaponDefinitions(void) {
    struct { const char *text; int valid; } cases[] = {
        {"weaponDef { both { damage 18 } client { readySound test.wav } }", 1},
        {"weaponDef { both_altweap { damage 20 } client { readySound test.wav } }", 1},
        {"weaponDef { both { nested { value 1 } } both_altweap { } client { readySound test.wav } }", 1},
        {"weaponDef { client { readySound test.wav } }", 1},
        {"weaponDef { both damage 18 }", 0},
        {"weaponDef { both { damage 18", 0},
        {"weaponDef { both_altweap { damage 18", 0},
        {"weaponDef { unsupported { } }", 0}
    };
    int i, repeat, errors = 0;
    for(repeat = 0; repeat < 100; ++repeat) for(i = 0; i < sizeof(cases)/sizeof(cases[0]); ++i) {
        int oldPrints = prints;
        weaponCursor = (char *)cases[i].text;
        sourceLoads = sourceFrees = mediaSounds = 0;
        CG_RegisterWeapon(WP_MP40, qtrue);
        if(sourceLoads != 1 || sourceFrees != 1 || mediaSounds != cases[i].valid ||
           (cases[i].valid && prints != oldPrints) ||
           (!cases[i].valid && prints == oldPrints)) ++errors;
    }
    return errors;
}
static void SetTestConfig(int index, const char *value) {
    int length = (int)strlen(value) + 1;
    if(cgs.gameState.dataCount + length >= MAX_GAMESTATE_CHARS) exit(2);
    cgs.gameState.stringOffsets[index] = cgs.gameState.dataCount;
    memcpy(cgs.gameState.stringData + cgs.gameState.dataCount, value, length);
    cgs.gameState.dataCount += length;
}
static int CheckTagConnectLayouts(void) {
    static gameState_t saved;
    const char *info[] = {"\\gamename\\etmain", "\\gamename\\nitmod", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    int mode, errors = 0;
    saved = cgs.gameState;
    for(mode = 0; mode < 3; ++mode) {
        int base = mode == 1 ? 777 : CS_TAGCONNECTS;
        char number[16];
        memset(&cgs.gameState, 0, sizeof(cgs.gameState));
        cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, info[mode]);
        sentCapabilities = 0;
        cg.demoPlayback = qfalse;
        NITMOD_AdvertiseCapabilities();
        if(sentCapabilities != (mode == 2)) ++errors;
        cg.demoPlayback = qtrue;
        NITMOD_AdvertiseCapabilities();
        if(sentCapabilities != (mode == 2)) ++errors;
        cg.demoPlayback = qfalse;
        SetTestConfig(base, "1 3 tag_origin");
        SetTestConfig(base + 63, "2 4 tag_head");
        SetTestConfig(mode == 1 ? 841 : 777, "not a tag attachment");
        if(NITMOD_TagConnectBase() != base) ++errors;
        CG_ParseTagConnects();
        if(cg_entities[1].tagParent != 3 || strcmp(cg_entities[1].tagName, "tag_origin") ||
           cg_entities[2].tagParent != 4 || strcmp(cg_entities[2].tagName, "tag_head")) ++errors;
        SetTestConfig(base + 63, "2 9 tag_changed");
        fields[0] = "cs"; fields[1] = number; argcValue = 2;
        Com_sprintf(number, sizeof(number), "%d", base + 63);
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cg_entities[2].tagParent != 9 || strcmp(cg_entities[2].tagName, "tag_changed")) ++errors;
        if(mode == 1) {
            Com_sprintf(number, sizeof(number), "%d", 841);
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cg_entities[2].tagParent != 9) ++errors;
        }
    }
    cgs.gameState = saved;
    return errors;
}
static int QDECL Engine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(forceTest && command == CG_CVAR_VARIABLESTRINGBUFFER) {
        const char *name = va_arg(args, const char *);
        char *value = va_arg(args, char *);
        int size = va_arg(args, int);
        if(!*name) exit(2);
        Q_strncpyz(value, forceCurrent, size);
        va_end(args); return 0;
    }
    if(forceTest && command == CG_CVAR_REGISTER) {
        if(va_arg(args, vmCvar_t *) != NULL) exit(2);
        Q_strncpyz(forceLastName, va_arg(args, const char *), sizeof(forceLastName));
        Q_strncpyz(forceLastValue, va_arg(args, const char *), sizeof(forceLastValue));
        if(va_arg(args, int) != 0) exit(2);
        ++forceRegisters; va_end(args); return 0;
    }
    if(forceTest && command == CG_CVAR_SET) {
        if(strcmp(va_arg(args, const char *), forceLastName) ||
           strcmp(va_arg(args, const char *), forceLastValue)) exit(2);
        ++forceSets; va_end(args); return 0;
    }
    if(ncsTest && (command == CG_R_REGISTERMODEL || command == CG_R_REGISTERSKIN ||
       command == CG_R_REGISTERSHADER || command == CG_R_REGISTERSHADERNOMIP || command == CG_S_REGISTERSOUND)) {
        const char *path = va_arg(args, const char *);
        if(!*path) exit(2);
        ++ncsAssets; va_end(args); return 123;
    }
    if(command == CG_TRANSLATE_STRING) {
        const char *source = va_arg(args, const char *);
        char *target = va_arg(args, char *);
        Q_strncpyz(target, source, MAX_STRING_CHARS);
        va_end(args); return 0;
    }
    if(command == CG_S_STARTSOUND) {
        if(va_arg(args, const float *) != NULL) exit(2);
        if(greetingTest) {
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_VOICE ||
               va_arg(args, int) != 95) exit(2);
            ++greetingPlays; va_end(args); return 0;
        }
        if(shoveTest) {
            if(va_arg(args, int) != shoveEntity || va_arg(args, int) != CHAN_AUTO ||
               va_arg(args, int) != 94 || va_arg(args, int) != 255) exit(2);
            ++shovePlays; va_end(args); return 0;
        }
        if(hitTest) {
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_VOICE) exit(2);
            hitSound = va_arg(args, int); ++hitPlays;
            va_end(args); return 0;
        }
        if(landingTest) {
            int sound;
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_AUTO) exit(2);
            sound = va_arg(args, int);
            if(sound == 81) ++hurtPlays;
            else if(sound == 82) ++landingPlays;
            else exit(2);
            va_end(args); return 0;
        }
        if(pmTest) {
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_VOICE ||
               va_arg(args, int) != 73 || va_arg(args, int) != 255) exit(2);
            ++pmPlays; va_end(args); return 0;
        }
        medicEntity = va_arg(args, int);
        if(va_arg(args, int) != CHAN_AUTO) exit(2);
        medicHandle = va_arg(args, int);
        ++medicSounds; va_end(args); return 0;
    }
    if(command == CG_MILLISECONDS) { va_end(args); return 1000; }
    if(command == CG_SENDCLIENTCOMMAND) {
        const char *text = va_arg(args, const char *);
        if(strncmp(text, "nitcap ", 7)) exit(2);
        ++sentCapabilities; va_end(args); return 0;
    }
    if(command == CG_PC_LOAD_SOURCE) {
        if(strcmp(va_arg(args, const char *), "weapons/mp40.weap")) exit(2);
        ++sourceLoads; va_end(args); return 17;
    }
    if(command == CG_PC_READ_TOKEN) {
        pc_token_t *token;
        char *text;
        if(va_arg(args, int) != 17) exit(2);
        token = va_arg(args, pc_token_t *);
        text = COM_Parse(&weaponCursor);
        memset(token, 0, sizeof(*token));
        Q_strncpyz(token->string, text, sizeof(token->string));
        va_end(args); return !!*text;
    }
    if(command == CG_PC_FREE_SOURCE) {
        if(va_arg(args, int) != 17) exit(2);
        ++sourceFrees; va_end(args); return 0;
    }
    if(command == CG_PC_SOURCE_FILE_AND_LINE) {
        char *filename; int *line;
        if(va_arg(args, int) != 17) exit(2);
        filename = va_arg(args, char *); line = va_arg(args, int *);
        strcpy(filename, "weapons/mp40.weap"); *line = 4;
        va_end(args); return 1;
    }
    if(command == CG_S_REGISTERSOUND) {
        if(greetingTest) {
            if(strcmp(va_arg(args, const char *), "sound/test.wav") || va_arg(args, int) != qfalse) exit(2);
            ++greetingLoads; va_end(args); return greetingHandle;
        }
        if(hitTest) {
            const char *path = va_arg(args, const char *);
            int handle = !strcmp(path, "sound/nit/hs.wav") ? 91 : !strcmp(path, "sound/hitsounds/team.wav") ? 92 : 0;
            if(!handle) exit(2);
            va_end(args); return handle;
        }
        if(pmTest) {
            if(strcmp(va_arg(args, const char *), "sound/nit/pm.wav") || va_arg(args, int) != qfalse) exit(2);
            ++pmLoads; va_end(args); return 73;
        }
        if(strcmp(va_arg(args, const char *), "test.wav")) exit(2);
        ++mediaSounds; va_end(args); return 42;
    }
    if(command == CG_ARGC) { va_end(args); return argcValue; }
    if(command == CG_CVAR_REGISTER && hitTest) {
        hitCvar = va_arg(args, vmCvar_t *);
        if(strcmp(va_arg(args, const char *), "cg_hitSounds") || strcmp(va_arg(args, const char *), "1") ||
           va_arg(args, int) != CVAR_ARCHIVE) exit(2);
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE && greetingTest) {
        if(va_arg(args, vmCvar_t *) != &cg_noGreetingSounds) exit(2);
        cg_noGreetingSounds.integer = greetingValue;
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE && shoveTest) {
        if(va_arg(args, vmCvar_t *) != &cg_shoveSounds) exit(2);
        cg_shoveSounds.integer = shoveValue;
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE && hitTest) {
        if(va_arg(args, vmCvar_t *) != hitCvar) exit(2);
        hitCvar->integer = hitValue;
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE && pmTest) {
        if(va_arg(args, vmCvar_t *) != &cg_pmSounds) exit(2);
        cg_pmSounds.integer = pmValue;
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE) {
        if(va_arg(args, vmCvar_t *) != &cg_drawBanners) exit(2);
        cg_drawBanners.integer = bannerValue;
        va_end(args); return 0;
    }
    if(command == CG_GETSERVERCOMMAND) { va_end(args); return 1; }
    if(command == CG_GETGAMESTATE) {
        if(va_arg(args, gameState_t *) != &cgs.gameState) exit(2);
        /* Fixture already installed the exact updated engine gamestate. */
        va_end(args); return 0;
    }
    if(command == CG_ARGV) {
        int index = va_arg(args, int);
        char *buffer = va_arg(args, char *);
        int size = va_arg(args, int);
        if(index < 0 || index >= 21) exit(2);
        Q_strncpyz(buffer, fields[index], size);
        va_end(args); return 0;
    }
    if(command == CG_PRINT) { ++prints; va_end(args); return 0; }
    if(command == CG_ERROR) {
        fprintf(stderr, "Client parser error: %s\n", va_arg(args, const char *));
        va_end(args); exit(2);
    }
    fprintf(stderr, "Unexpected syscall %d\n", command); exit(2);
}
int main(int argc, char **argv) {
    int index, errors = 0;
    static cg_t before;
    dllEntry(Engine);
    errors += CheckDoubleJump();
    {
        int cls, maximum, i;
        char number[16];
        const char *savedFields[21];
        int savedArgc = argcValue;
        memcpy(savedFields, fields, sizeof(savedFields));
        NITMOD_ClearConfigStrings();
        if(NITMOD_ClassIsDisabled(TEAM_AXIS, PC_SOLDIER)) ++errors;
        if(NITMOD_ParseLatchedClass("\\lc\\4", 1) != 4 ||
           NITMOD_ParseLatchedClass("\\c\\2", 2) != 2 ||
           NITMOD_ParseLatchedClass("\\lc\\5", 2) != 2 ||
           NITMOD_ParseLatchedClass("\\lc\\bad", 2) != 2) ++errors;
        cg.clientNum = 0; cgs.maxclients = 5;
        for(i = 0; i < 5; ++i) {
            memset(&cgs.clientinfo[i], 0, sizeof(cgs.clientinfo[i]));
            cgs.clientinfo[i].infoValid = i != 4;
            cgs.clientinfo[i].team = i == 3 ? TEAM_ALLIES : TEAM_AXIS;
        }
        for(cls = 0; cls < 5; ++cls) for(maximum = -2; maximum <= 3; ++maximum) {
            for(i = 0; i < 5; ++i) {
                cgs.clientinfo[i].cls = cls; cgs.clientinfo[i].latchedClass = cls;
            }
            cgs.clientinfo[2].cls = (cls + 1) % 5;
            fields[0] = "#"; for(i = 1; i < 21; ++i) fields[i] = "0";
            for(i = 9; i <= 13; ++i) fields[i] = "-1";
            Com_sprintf(number, sizeof(number), "%d", maximum); fields[9 + cls] = number;
            argcValue = 21; NITMOD_GameStateCommand();
            if(NITMOD_ClassIsDisabled(TEAM_AXIS, cls) != (maximum != -1 && maximum <= 2)) ++errors;
            if(NITMOD_ClassIsDisabled(TEAM_SPECTATOR, cls)) ++errors;
        }
        NITMOD_ClearConfigStrings();
        if(NITMOD_ClassIsDisabled(TEAM_AXIS, PC_SOLDIER)) ++errors;
        memcpy(fields, savedFields, sizeof(savedFields)); argcValue = savedArgc;
        memset(cgs.clientinfo, 0, sizeof(cgs.clientinfo)); cgs.maxclients = 0;
    }
    NITMOD_ClearConfigStrings();
    CG_ExecuteNewServerCommands(1);
    if(cg.soldierChargeTime[0] != 11 || cg.soldierChargeTime[1] != 22 ||
       cg.medicChargeTime[0] != 33 || cg.medicChargeTime[1] != 44 ||
       cg.engineerChargeTime[0] != 55 || cg.engineerChargeTime[1] != 66 ||
       cg.ltChargeTime[0] != 77 || cg.ltChargeTime[1] != 88 ||
       cg.covertopsChargeTime[0] != 99 || cg.covertopsChargeTime[1] != 110 || prints) ++errors;
    before = cg;
    for(index = 1; index <= 10; ++index) {
        const char *saved = fields[index];
        fields[index] = "999999999999999999999";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(memcmp(&cg, &before, sizeof(cg))) ++errors;
        fields[index] = saved;
    }
    argcValue = 10;
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(memcmp(&cg, &before, sizeof(cg)) || prints != 1) ++errors;
    if(NITMOD_ServerSupports(NITMOD_FEATURE_CHARGE_TIMES) || NITMOD_ServerSupports(NITMOD_FEATURE_NCS)) ++errors;
    {
        nitmodGameState_t previous;
        const char *bad[] = {"", "1junk", "2147483648", "-2147483649"};
        int slot, badIndex;
        fields[0] = "tsc"; fields[1] = "-2147483648"; fields[2] = "2147483647";
        argcValue = 3;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(NITMOD_GameState()->teamScoreAxis != (-2147483647 - 1) ||
           NITMOD_GameState()->teamScoreAllies != 2147483647) ++errors;
        previous = *NITMOD_GameState();
        for(slot = 1; slot <= 2; ++slot) for(badIndex = 0; badIndex < 4; ++badIndex) {
            const char *saved = fields[slot];
            fields[slot] = bad[badIndex];
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(NITMOD_GameState(), &previous, sizeof(previous))) ++errors;
            fields[slot] = saved;
        }
        for(argcValue = 2; argcValue <= 4; argcValue += 2) {
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(NITMOD_GameState(), &previous, sizeof(previous))) ++errors;
        }
        argcValue = 3; fields[1] = "0"; fields[2] = "-7";
        previous.teamScoreAxis = 0; previous.teamScoreAllies = -7;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(memcmp(NITMOD_GameState(), &previous, sizeof(previous)) ||
           memcmp(&cg, &before, sizeof(cg)) || NITMOD_ServerSupports(NITMOD_FEATURE_TEAM_SCORES)) ++errors;
    }
    if(argc != 2) ++errors;
    else errors += CheckOriginalAnimationConditions(argv[1]);
    errors += CheckTagConnectLayouts();
    errors += CheckSharedWeaponDefinitions();
    errors += CheckMedicEvents();
    errors += CheckPrivateMessageSound();
    errors += CheckOriginalLanding();
    {
        const char *valid[] = {"scs", "2", "1", "0", "1", "1", "0", "7", "800", "1", "200", "300"};
        const char *bad[] = {"", "1junk", "2147483648", "-2147483649"};
        nitmodSimpleConfig_t expected = {2, 1, 0, 1, 1, 0, 7, 800, 1, 200, 300};
        int slot, test;
        NITMOD_ClearConfigStrings();
        for(slot = 0; slot < 12; ++slot) fields[slot] = valid[slot];
        argcValue = 12;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(memcmp(NITMOD_SimpleConfig(), &expected, sizeof(expected)) || !cg.filtercams) ++errors;
        for(slot = 1; slot < 12; ++slot) for(test = 0; test < 4; ++test) {
            fields[slot] = bad[test];
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(NITMOD_SimpleConfig(), &expected, sizeof(expected)) || !cg.filtercams) ++errors;
            fields[slot] = valid[slot];
        }
        for(argcValue = 11; argcValue <= 13; argcValue += 2) {
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(NITMOD_SimpleConfig(), &expected, sizeof(expected))) ++errors;
        }
        argcValue = 12; fields[1] = "0"; fields[5] = "0";
        expected.doubleJump = expected.filterCams = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(memcmp(NITMOD_SimpleConfig(), &expected, sizeof(expected)) || cg.filtercams ||
           NITMOD_ServerSupports(NITMOD_FEATURE_SIMPLE_CS)) ++errors;
    }
    {
        nitmodGameState_t beforeState;
        const char *bad[] = {"nan", "inf", "1.4oops", "1e99"};
        int j;
        fields[0] = "#";
        for(j = 1; j < 21; ++j) fields[j] = "0";
        fields[15] = "1.4"; argcValue = 21;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(fabs(NITMOD_GameState()->doubleJumpHeight - 1.4f) > 0.0001f) ++errors;
        beforeState = *NITMOD_GameState();
        for(j = 0; j < 4; ++j) {
            fields[15] = bad[j];
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(&beforeState, NITMOD_GameState(), sizeof(beforeState))) ++errors;
        }
        if(NITMOD_ServerSupports(NITMOD_FEATURE_SIMPLE_CS)) ++errors;
    }
    {
        int previousPrints = prints;
        cg.numScores = 3;
        cg.scores[0].client = 7; cg.scores[1].client = 2; cg.scores[2].client = 9;
        fields[0] = "kd0"; fields[1] = "2";
        fields[2] = "7"; fields[3] = "20"; fields[4] = "4";
        fields[5] = "2"; fields[6] = "30"; fields[7] = "5"; argcValue = 8;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[7].kills != 20 || cgs.clientinfo[7].deaths != 4 ||
           cgs.clientinfo[2].kills != 30 || cgs.clientinfo[2].deaths != 5 || cg.numScores != 3) ++errors;
        fields[0] = "kd1"; fields[1] = "1"; fields[2] = "9";
        fields[3] = "40"; fields[4] = "invalid"; argcValue = 5;
        cgs.clientinfo[9].kills = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[9].kills) ++errors;
        fields[4] = "6";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[9].kills != 40 || cgs.clientinfo[9].deaths != 6) ++errors;
        /* Reject an append past the existing scoreboard and malicious counts. */
        fields[3] = "99";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[9].kills != 40) ++errors;
        fields[0] = "kd0"; fields[1] = "2147483647";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[7].kills != 20 || prints != previousPrints) ++errors;
        fields[0] = "bp"; fields[1] = "1"; fields[2] = "Test banner"; argcValue = 3;
        bannerValue = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(prints != previousPrints) ++errors;
        bannerValue = 1;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(prints != previousPrints + 1) ++errors;
        fields[1] = "2";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(prints != previousPrints + 1) ++errors;
    }
    {
        int mode, j;
        const char *rows[] = {"7", "42", "50", "12", "0", "1", "-1"};
        for(mode = 0; mode < 2; ++mode) {
            score_t beforeScore;
            int offset = mode ? 2 : 4;
            memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
            SetTestConfig(CS_SERVERINFO, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
            fields[0] = "sc0"; fields[1] = "100"; fields[2] = "200";
            fields[offset - 1] = "1";
            for(j = 0; j < 7; ++j) fields[offset + j] = rows[j];
            argcValue = offset + 7;
            cg.teamScores[0] = 88; cg.teamScores[1] = 99;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cg.numScores != 1 || cg.scores[0].client != 7 || cg.scores[0].score != 42 ||
               cg.teamScores[0] != (mode ? 88 : 100) || cg.teamScores[1] != (mode ? 99 : 200)) ++errors;
            beforeScore = cg.scores[0];
            fields[offset - 1] = "2147483647";
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cg.numScores != 1 || memcmp(&beforeScore, &cg.scores[0], sizeof(beforeScore))) ++errors;
            fields[0] = "sc1"; fields[1] = "1";
            for(j = 0; j < 7; ++j) fields[2 + j] = rows[j];
            fields[2] = "9"; argcValue = 9;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cg.numScores != 2 || cg.scores[1].client != 9) ++errors;
        }
    }
    {
        int id;
        char number[16];
        fields[0] = "ncp"; fields[1] = number; argcValue = 2;
        for(id = 0; id < 58; ++id) {
            char rendered[1024];
            int k;
            Com_sprintf(number, sizeof(number), "%d", id);
            cg.centerPrintPriority = 0;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            Q_strncpyz(rendered, cg.centerPrint, sizeof(rendered));
            for(k = 0; rendered[k]; ++k) if(rendered[k] == '\n') rendered[k] = ' ';
            if(id != 7 && strcmp(rendered, NITMOD_ServerMessageText(id))) ++errors;
        }
        if(NITMOD_ServerMessageText(-1) || NITMOD_ServerMessageText(58)) ++errors;
    }
    {
        static snapshot_t snapshot;
        centity_t cent;
        int enabled, type, bits;
        memset(&cent, 0, sizeof(cent));
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
        NITMOD_ClearConfigStrings();
        cg.snap = &snapshot; snapshot.ps.clientNum = 5;
        hitTest = 1;
        for(enabled = 0; enabled < 2; ++enabled) for(type = 2; type <= 5; ++type)
            for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
                hitValue = enabled; hitPlays = 0;
                cent.currentState.event = 99 | bits; cent.currentState.eventParm = type;
                CG_EntityEvent(&cent, cent.lerpOrigin);
                if(hitPlays != (enabled && (type == 3 || type == 4))) ++errors;
                if(hitPlays && hitSound != (type == 3 ? 92 : 91)) ++errors;
            }
        hitTest = 0; cg.snap = NULL;
    }
    {
        centity_t cent;
        int enabled, bits, entity, sound;
        const int entities[] = {-1, 0, 5, MAX_GENTITIES - 1, MAX_GENTITIES};
        const int handles[] = {-1, 0, 94};
        memset(&cent, 0, sizeof(cent));
        shoveTest = 1;
        for(enabled = -1; enabled <= 1; ++enabled)
            for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1)
                for(entity = 0; entity < 5; ++entity) for(sound = 0; sound < 3; ++sound) {
                    shoveValue = enabled; shovePlays = 0; shoveEntity = entities[entity];
                    cgs.media.sfx_bullet_fleshhit[0] = handles[sound];
                    cent.currentState.number = shoveEntity;
                    cent.currentState.event = 96 | bits;
                    CG_EntityEvent(&cent, cent.lerpOrigin);
                    if(shovePlays != (enabled != 0 && shoveEntity >= 0 &&
                       shoveEntity < MAX_GENTITIES && handles[sound] > 0)) ++errors;
                    if(cent.currentState.event != (96 | bits)) ++errors;
                }
        shoveTest = 0;
    }
    {
        static snapshot_t snapshot;
        int disabled, valid, handle, malformed;
        char oversized[MAX_QPATH + 1];
        memset(oversized, 'a', sizeof(oversized) - 1); oversized[sizeof(oversized) - 1] = 0;
        greetingTest = 1; fields[0] = "gsnd";
        for(disabled = -1; disabled <= 1; ++disabled) for(valid = 0; valid < 4; ++valid)
            for(handle = 0; handle < 3; ++handle) for(malformed = 0; malformed < 4; ++malformed) {
                int expected;
                cg.snap = valid ? &snapshot : NULL;
                snapshot.ps.clientNum = valid == 1 ? -1 : valid == 2 ? MAX_CLIENTS : 5;
                greetingValue = disabled; greetingHandle = handle == 2 ? 95 : handle - 1;
                greetingPlays = greetingLoads = 0;
                fields[1] = malformed == 1 ? "" : malformed == 2 ? oversized : "sound/test.wav";
                argcValue = malformed == 3 ? 1 : 2;
                CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
                expected = disabled == 0 && valid == 3 && malformed == 0;
                if(greetingLoads != expected || greetingPlays != (expected && handle == 2)) ++errors;
            }
        greetingTest = 0; cg.snap = NULL;
    }
    {
        const char *blocked[] = {"cl_profile", "X", "NAME", "Sensitivity", "N_GUID", "", "bad;name", "bad name"};
        char name[32], oversized[257];
        int i;
        forceTest = 1; forceCurrent[0] = 0; forceSets = forceRegisters = 0;
        NITMOD_ClearConfigStrings(); fields[0] = "fc"; fields[2] = "1"; argcValue = 3;
        for(i = 0; i < sizeof(blocked)/sizeof(blocked[0]); ++i) {
            fields[1] = blocked[i]; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        }
        memset(oversized, 'a', sizeof(oversized) - 1); oversized[256] = 0;
        fields[1] = oversized; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        fields[1] = "r_test"; fields[2] = oversized; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        fields[2] = "1"; cg.demoPlayback = qtrue;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1); cg.demoPlayback = qfalse;
        argcValue = 2; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1); argcValue = 3;
        NITMOD_ApplyForcedCvars(); if(forceSets) ++errors;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(forceSets) ++errors; /* Reception is deferred. */
        NITMOD_ApplyForcedCvars(); if(forceSets != 1 || strcmp(forceLastValue, "1")) ++errors;
        fields[1] = "R_TEST"; fields[2] = "VALUE";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        strcpy(forceCurrent, "value"); NITMOD_ApplyForcedCvars(); if(forceSets != 1) ++errors;
        forceCurrent[0] = 0; NITMOD_ApplyForcedCvars(); if(forceSets != 2) ++errors;
        cg.demoPlayback = qtrue; NITMOD_ApplyForcedCvars(); cg.demoPlayback = qfalse;
        if(forceSets != 2) ++errors;
        NITMOD_ClearConfigStrings(); forceSets = forceRegisters = 0; fields[2] = "1";
        for(i = 0; i < 65; ++i) {
            Com_sprintf(name, sizeof(name), "test_%d", i); fields[1] = name;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        }
        fields[1] = "test_0"; fields[2] = "2";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        NITMOD_ApplyForcedCvars();
        if(forceSets != 64 || forceRegisters != 64 || strcmp(forceLastValue, "1")) ++errors;
        NITMOD_ClearConfigStrings(); NITMOD_ApplyForcedCvars(); if(forceSets != 64) ++errors;
        forceTest = 0;
    }
    {
        struct { int wire, native; const char *text; } assets[] = {
            {0, CS_MODELS, "models/test.md3"}, {255, CS_MODELS + 255, "models/last.md3"},
            {256, CS_SOUNDS, "sound/test.wav"}, {511, CS_SOUNDS + 255, "sound/last.wav"},
            {512, CS_SHADERS, "test/shader"}, {543, CS_SHADERS + 31, "*test/mip"},
            {545, CS_SKINS, "test.skin"}, {608, CS_SKINS + 63, "last.skin"}
        };
        char number[16];
        int i;
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
        NITMOD_ClearConfigStrings(); ncsTest = 1; ncsAssets = 0;
        fields[0] = "ncs"; fields[1] = number; argcValue = 3;
        for(i = 0; i < sizeof(assets)/sizeof(assets[0]); ++i) {
            Com_sprintf(number, sizeof(number), "%d", assets[i].wire); fields[2] = assets[i].text;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(strcmp(NITMOD_AssetConfigString(assets[i].native), assets[i].text)) ++errors;
        }
        if(ncsAssets != 8 || cgs.gameModels[255] != 123 || cgs.gameSounds[255] != 123 ||
           cgs.gameShaders[31] != 123 || cgs.gameModelSkins[63] != 123) ++errors;
        Com_sprintf(number, sizeof(number), "%d", NITMOD_NCS_OBJECTIVES);
        fields[2] = "\\s\\3\\b\\31\\r\\999999\\n\\Bridge\\x\\12\\y\\34\\z\\56";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(strcmp(cgs.oidInfo[0].name, "Bridge") || cgs.oidInfo[0].customimageallies != 123 ||
           cgs.oidInfo[0].customimageaxis || cgs.oidInfo[0].origin[2] != 56) ++errors;
        Com_sprintf(number, sizeof(number), "%d", NITMOD_NCS_FIRETEAMS);
        fields[2] = "\\n\\-1";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cg.fireTeams[0].inuse) ++errors;
        fields[2] = "\\n\\2\\l\\0\\c\\0000000000000001";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(!cg.fireTeams[0].inuse || cgs.clientinfo[0].fireteamData != &cg.fireTeams[0]) ++errors;
        SetTestConfig(CS_MULTI_INFO, "\\n\\1");
        Com_sprintf(number, sizeof(number), "%d", NITMOD_NCS_SPAWNS);
        fields[2] = "\\s\\AxisSpawn\\x\\12\\y\\34\\t\\1\\c\\2";
        cgs.ccLayers = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cg.spawnCount != 2 || strcmp(cg.spawnPoints[1], "AxisSpawn") ||
           cg.spawnCoordsUntransformed[1][0] != 12 || cg.spawnTeams[1] != 1 || cg.spawnPlayerCounts[1] != 2) ++errors;
        strcpy(number, "655"); fields[2] = "invalid";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(ncsAssets != 8 || NITMOD_ServerSupports(NITMOD_FEATURE_NCS)) ++errors;
        ncsTest = 0;
    }
    if(errors) fprintf(stderr, "%d original protocol/animation failures\n", errors);
    return errors != 0;
}
