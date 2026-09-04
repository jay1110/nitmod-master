#include "ui_local.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
extern float Item_Slider_ThumbPosition(itemDef_t *);
extern int Item_Slider_OverSlider(itemDef_t *, float, float);
extern qboolean Item_Slider_HandleKey(itemDef_t *, int, qboolean);
extern qboolean Item_HandleKey(itemDef_t *, int, qboolean);
extern void Item_StartCapture(itemDef_t *, int);
extern void Item_Slider_Paint(itemDef_t *);
extern int menuCount;
static float sliderValue, sliderWritten;
extern void UI_RunMenuScript(char **args);
extern void dllEntry(int (QDECL *)(int, ...));
#include "check_ui_widescreen.h"
#include "check_ui_map_preview.h"
static int catalogListMode;
static char *campaignInput;
static int campaignBudget, campaignReads, campaignOpens, campaignCloses;
static const char *campaignMap;
static unsigned char campaignSaveBytes[13 + MAX_CAMPAIGNS * (8 + 4 * MAX_MAPS_PER_CAMPAIGN)];
static int campaignSaveSize, campaignSavePosition, campaignSaveClosed;
static int QDECL CampaignSaveSyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_FS_FOPENFILE) {
        fileHandle_t *file;
        if(strcmp(va_arg(args, const char *), "profiles/test/campaign.dat")) exit(2);
        file = va_arg(args, fileHandle_t *);
        if(va_arg(args, int) != FS_READ) exit(2);
        *file = 72; campaignSavePosition = 0; campaignSaveClosed = 0;
        result = campaignSaveSize;
    } else if(command == UI_FS_READ) {
        void *buffer = va_arg(args, void *);
        int length = va_arg(args, int);
        if(va_arg(args, int) != 72 || length < 0 || length > campaignSaveSize - campaignSavePosition) exit(2);
        memcpy(buffer, campaignSaveBytes + campaignSavePosition, length); campaignSavePosition += length;
    } else if(command == UI_FS_FCLOSEFILE) {
        if(va_arg(args, int) != 72) exit(2);
        ++campaignSaveClosed;
    } else if(command == UI_PRINT) { (void)va_arg(args, const char *); }
    else { fprintf(stderr, "Unexpected campaign save syscall %d\n", command); exit(2); }
    va_end(args); return result;
}
static void CampaignSaveInt(int offset, unsigned int value) {
    int i;
    for(i = 0; i < 4; ++i) campaignSaveBytes[offset + i] = (unsigned char)(value >> (i*8));
}
static int CheckCampaignSave(void) {
    static cpsFile_t output, empty;
    unsigned int hash = 't'*119u + 'e'*120u + 's'*121u + 't'*122u;
    int progress, prefix, size, i, errors = 0;
    dllEntry(CampaignSaveSyscall);
    memset(campaignSaveBytes, 0, sizeof(campaignSaveBytes));
    CampaignSaveInt(0, CPS_IDENT); campaignSaveBytes[4] = CPS_VERSION;
    CampaignSaveInt(5, 1); CampaignSaveInt(9, hash); CampaignSaveInt(13, 12345);
    for(progress = 0; progress <= MAX_MAPS_PER_CAMPAIGN; ++progress) {
        CampaignSaveInt(17, progress);
        for(i = 0; i < progress; ++i) CampaignSaveInt(21 + 4*i, 0x80000000u + i);
        size = 21 + progress * 4;
        for(prefix = 0; prefix <= size; ++prefix) {
            qboolean result;
            campaignSaveSize = prefix; memset(&output, 0x5a, sizeof(output));
            result = BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "TeSt");
            if(result != (prefix == size) || campaignSaveClosed != 1) ++errors;
            if(!result && memcmp(&output, &empty, sizeof(output))) ++errors;
            if(result) {
                if(output.header.numCampaigns != 1 || output.campaigns[0].progress != progress ||
                   output.campaigns[0].shortnameHash != 12345) ++errors;
                for(i = 0; i < progress; ++i)
                    if((unsigned int)output.campaigns[0].maps[i].mapnameHash != 0x80000000u + i) ++errors;
            }
        }
    }
    campaignSaveSize = sizeof(campaignSaveBytes);
    CampaignSaveInt(17, MAX_MAPS_PER_CAMPAIGN + 1);
    if(BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "test")) ++errors;
    CampaignSaveInt(17, ~0u);
    if(BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "test")) ++errors;
    CampaignSaveInt(5, MAX_CAMPAIGNS + 1);
    if(BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "test")) ++errors;
    CampaignSaveInt(5, ~0u);
    if(BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "test")) ++errors;
    CampaignSaveInt(5, 0); campaignSaveSize = 13;
    if(!BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "test")) ++errors;
    if(BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "other")) ++errors;
    campaignSaveBytes[4] = CPS_VERSION + 1;
    if(BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "test")) ++errors;
    campaignSaveBytes[4] = CPS_VERSION;
    /* Full-capacity file with ten completed maps in every record. */
    CampaignSaveInt(5, MAX_CAMPAIGNS);
    for(i = 0; i < MAX_CAMPAIGNS; ++i) {
        int offset = 13 + i * (8 + 4 * MAX_MAPS_PER_CAMPAIGN);
        CampaignSaveInt(offset, i); CampaignSaveInt(offset + 4, MAX_MAPS_PER_CAMPAIGN);
    }
    campaignSaveSize = sizeof(campaignSaveBytes);
    if(!BG_LoadCampaignSave("profiles/test/campaign.dat", &output, "test") ||
       output.campaigns[MAX_CAMPAIGNS - 1].shortnameHash != MAX_CAMPAIGNS - 1) ++errors;
    if(errors) fprintf(stderr, "%d campaign save failures\n", errors);
    return errors;
}
static int QDECL CampaignParserSyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_PC_LOAD_SOURCE) { ++campaignOpens; result = 71; }
    else if(command == UI_FS_GETFILELIST) {
        char *buffer; int capacity;
        if(strcmp(va_arg(args, const char *), "scripts") || strcmp(va_arg(args, const char *), ".campaign")) exit(2);
        buffer = va_arg(args, char *); capacity = va_arg(args, int);
        Q_strncpyz(buffer, "test.campaign", capacity); result = 1;
    } else if(command == UI_FS_FOPENFILE) {
        fileHandle_t *file;
        (void)va_arg(args, const char *); file = va_arg(args, fileHandle_t *);
        if(va_arg(args, int) != FS_READ) exit(2);
        *file = 0; result = -1;
    }
    else if(command == UI_PC_FREE_SOURCE) {
        if(va_arg(args, int) != 71) exit(2);
        ++campaignCloses;
    } else if(command == UI_PC_READ_TOKEN) {
        pc_token_t *token;
        if(va_arg(args, int) != 71) exit(2);
        token = va_arg(args, pc_token_t *);
        if(campaignReads++ < campaignBudget) {
            char *word = COM_ParseExt(&campaignInput, qtrue);
            if(*word || campaignInput) {
                memset(token, 0, sizeof(*token));
                Q_strncpyz(token->string, word, sizeof(token->string));
                token->floatvalue = (float)atof(word);
                result = 1;
            }
        }
    } else if(command == UI_GETCONFIGSTRING) {
        char *buffer; int size;
        if(va_arg(args, int) != CS_SERVERINFO) exit(2);
        buffer = va_arg(args, char *); size = va_arg(args, int);
        Com_sprintf(buffer, size, "\\mapname\\%s", campaignMap);
        result = 1;
    } else if(command == UI_PRINT) { (void)va_arg(args, const char *); }
    else { fprintf(stderr, "Unexpected campaign parser syscall %d\n", command); exit(2); }
    va_end(args); return result;
}
static void LoadCampaignFixture(char *input, int budget) {
    campaignInput = input; campaignBudget = budget; campaignReads = 0;
    UI_LoadCampaignsFromFile("scripts/test.campaign");
}
static int CheckCampaignCatalog(void) {
    static uiInfo_t saved;
    char complete[] = "{ shortname first name First description Desc image shot next second initial type \"wolfsp wolfmp wolfsw wolflms\" maps \"oasis;missing;GOLDRUSH;oasis;\" maptc 10 20 }";
    char second[] = "{ shortname second name Second maps goldrush }";
    char bad[] = "{ shortname broken initial maps oasis name";
    char list[1024];
    int errors = 0, limit, tokens, count, length, i, j;
    saved = uiInfo; dllEntry(CampaignParserSyscall);
    uiInfo.mapCount = 2;
    memset(uiInfo.mapList, 0, sizeof(uiInfo.mapList));
    uiInfo.mapList[0].mapLoadName = "oasis"; uiInfo.mapList[0].mapName = "^2Siwa Oasis";
    uiInfo.mapList[1].mapLoadName = "goldrush"; uiInfo.mapList[1].mapName = "^3Gold Rush";
    campaignOpens = campaignCloses = 0;
    uiInfo.campaignCount = 0; LoadCampaignFixture(complete, 1000);
    tokens = campaignReads - 1;
    if(uiInfo.campaignCount != 1 || uiInfo.campaignList[0].mapCount != 3 ||
       uiInfo.campaignList[0].mapInfos[1] != &uiInfo.mapList[1] ||
       uiInfo.campaignList[0].mapInfos[2] != &uiInfo.mapList[0] ||
       !uiInfo.campaignList[0].unlocked || uiInfo.campaignList[0].campaignCinematic != -1 ||
       uiInfo.campaignList[0].campaignShot != -1 || uiInfo.campaignList[0].mapTC[1][0] != 660 ||
       uiInfo.campaignList[0].mapTC[1][1] != 670 || uiInfo.campaignList[0].typeBits != 45) ++errors;
    for(limit = 0; limit <= tokens; ++limit) {
        uiInfo.campaignCount = 0;
        LoadCampaignFixture(complete, limit);
        if(uiInfo.campaignCount != (limit == tokens)) ++errors;
    }
    uiInfo.campaignCount = 0; LoadCampaignFixture(bad, 1000); LoadCampaignFixture(second, 1000);
    if(uiInfo.campaignCount != 1 || strcmp(uiInfo.campaignList[0].campaignShortName, "second") ||
       uiInfo.campaignList[0].initial || uiInfo.campaignList[0].unlocked) ++errors;
    /* Capacity at every boundary, including repeated map names. */
    for(count = 0; count <= MAX_MAPS_PER_CAMPAIGN + 2; ++count) {
        strcpy(list, "{ shortname list maps \"");
        for(i = 0; i < count; ++i) strcat(list, "oasis;");
        strcat(list, "\" }");
        uiInfo.campaignCount = 0; LoadCampaignFixture(list, 1000);
        if(uiInfo.campaignCount != (count <= MAX_MAPS_PER_CAMPAIGN) ||
           (uiInfo.campaignCount && uiInfo.campaignList[0].mapCount != count)) ++errors;
    }
    for(length = 126; length <= 130; ++length) {
        strcpy(list, "{ shortname list maps \""); i = (int)strlen(list);
        memset(list + i, 'x', length); strcpy(list + i + length, ";oasis\" }");
        uiInfo.campaignCount = 0; LoadCampaignFixture(list, 1000);
        if(uiInfo.campaignCount != (length < 128)) ++errors;
    }
    for(count = MAX_CAMPAIGNS - 1; count <= MAX_CAMPAIGNS + 1; ++count) {
        uiInfo.campaignCount = count; LoadCampaignFixture(second, 1000);
        if(uiInfo.campaignCount != (count < MAX_CAMPAIGNS ? count + 1 : count)) ++errors;
    }
    if(campaignOpens != campaignCloses) ++errors;
    /* Exhaust all 3-node next-link graphs: terminators, missing links and cycles. */
    for(count = 0; count < 64; ++count) {
        const char *names[] = {"a", "b", "c", "missing"};
        int links[3], node = 0, order = 0, seen[3] = {0,0,0}, expected[3] = {-7,-7,-7};
        uiInfo.campaignCount = 3;
        memset(uiInfo.campaignList, 0, sizeof(uiInfo.campaignList));
        for(i = 0; i < 3; ++i) {
            links[i] = (count >> (2*i)) & 3;
            uiInfo.campaignList[i].campaignShortName = names[i];
            uiInfo.campaignList[i].nextCampaignShortName = names[links[i]];
            uiInfo.campaignList[i].order = -7;
        }
        uiInfo.campaignList[0].initial = qtrue; uiInfo.campaignList[0].typeBits = 1 << GT_SINGLE_PLAYER;
        while(node < 3 && !seen[node]) { seen[node] = 1; expected[node] = order++; node = links[node]; }
        UI_OrderCampaigns();
        for(i = 0; i < 3; ++i) if(uiInfo.campaignList[i].order != expected[i]) ++errors;
    }
    /* Match the first map of every campaign, not just the first campaign. */
    for(i = 0; i < 3; ++i) for(j = 0; j < MAX_MAPS_PER_CAMPAIGN; ++j) {
        uiInfo.campaignCount = 3; memset(uiInfo.campaignList, 0, sizeof(uiInfo.campaignList));
        for(count = 0; count < 3; ++count) {
            uiInfo.campaignList[count].mapCount = MAX_MAPS_PER_CAMPAIGN;
            for(length = 0; length < MAX_MAPS_PER_CAMPAIGN; ++length)
                uiInfo.campaignList[count].mapInfos[length] = &uiInfo.mapList[0];
        }
        uiInfo.campaignList[i].mapInfos[j] = &uiInfo.mapList[1];
        uiInfo.campaignList[i].campaignName = "matched"; uiInfo.campaignList[i].campaignDescription = "description";
        campaignMap = "GOLDRUSH";
        if(!UI_NameForCampaign() || strcmp(UI_NameForCampaign(), "matched") ||
           !UI_DescriptionForCampaign() || strcmp(UI_DescriptionForCampaign(), "description")) ++errors;
    }
    campaignMap = "missing"; if(UI_NameForCampaign() || UI_DescriptionForCampaign()) ++errors;
    {
        char pipeline[] = "{ shortname first name Zulu initial type wolfsp next second maps oasis } { shortname second name Alpha maps goldrush }";
        campaignInput = pipeline; campaignBudget = 1000; campaignReads = 0;
        UI_LoadCampaigns();
        if(uiInfo.campaignCount != 2 || strcmp(uiInfo.campaignList[0].campaignShortName, "second") ||
           uiInfo.campaignList[0].order != 1 || uiInfo.campaignList[0].unlocked ||
           uiInfo.campaignList[0].mapInfos[0] != &uiInfo.mapList[1] ||
           !uiInfo.campaignList[1].unlocked || uiInfo.campaignList[1].order != 0) ++errors;
        campaignMap = "goldrush";
        if(!UI_NameForCampaign() || strcmp(UI_NameForCampaign(), "Alpha")) ++errors;
        campaignInput = bad; campaignReads = 0; UI_LoadCampaigns();
        if(uiInfo.campaignCount || UI_NameForCampaign()) ++errors;
    }
    uiInfo = saved;
    if(errors) fprintf(stderr, "%d campaign catalog failures\n", errors);
    return errors;
}
static float settingsValue, settingsWritten[2];
static int settingsWrites, settingsCommands;
static char settingsNames[2][64], settingsText[2][1024], settingsCommand[128];
static int QDECL SettingsSyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_CVAR_VARIABLEVALUE) {
        (void)va_arg(args, const char *);
        memcpy(&result, &settingsValue, sizeof(result));
    } else if(command == UI_CVAR_VARIABLESTRINGBUFFER) {
        const char *name = va_arg(args, const char *);
        char *text = va_arg(args, char *);
        int size = va_arg(args, int);
        Q_strncpyz(text, !Q_stricmp(name, "ui_Name") ? "^2New Name" : "^1Old Name", size);
    } else if(command == UI_CVAR_SET || command == UI_CVAR_SETVALUE) {
        int index = settingsWrites++;
        if(index >= 2) exit(2);
        Q_strncpyz(settingsNames[index], va_arg(args, const char *), sizeof(settingsNames[index]));
        if(command == UI_CVAR_SET) Q_strncpyz(settingsText[index], va_arg(args, const char *), sizeof(settingsText[index]));
        else { int bits = va_arg(args, int); memcpy(&settingsWritten[index], &bits, sizeof(bits)); }
    } else if(command == UI_CMD_EXECUTETEXT) {
        if(va_arg(args, int) != EXEC_APPEND) exit(2);
        Q_strncpyz(settingsCommand, va_arg(args, const char *), sizeof(settingsCommand)); ++settingsCommands;
    } else { fprintf(stderr, "Unexpected settings syscall %d\n", command); exit(2); }
    va_end(args); return result;
}
static int CheckSettings(void) {
    const char *actions[] = {"r_colorbits", "ui_r_lodbias", "ui_glCustom", "ui_mousePitch"};
    const char *presets[] = {"exec preset_high_ui.cfg\n", "exec preset_normal_ui.cfg\n", "exec preset_fast_ui.cfg\n", "exec preset_fastest_ui.cfg\n"};
    const int subdivisions[] = {4,12,20};
    int action, step, errors = 0;
    dllEntry(SettingsSyscall);
    for(action = 0; action < 4; ++action) for(step = -4; step <= 68; ++step) {
        char script[80], *cursor = script;
        int selected, writes = 0, commands = 0;
        settingsValue = step * .5f; selected = (int)settingsValue;
        settingsWrites = settingsCommands = 0;
        Com_sprintf(script, sizeof(script), "update %s", actions[action]);
        UI_RunMenuScript(&cursor);
        if(action == 0 && (selected == 0 || selected == 16 || selected == 32)) {
            writes = selected == 32 ? 1 : 2;
            if(strcmp(settingsNames[0], "r_depthbits") || settingsWritten[0] != (selected == 32 ? 24 : selected)) ++errors;
            if(writes == 2 && (strcmp(settingsNames[1], "r_stencilbits") || settingsWritten[1] != 0)) ++errors;
        } else if(action == 1 && selected >= 0 && selected < 3) {
            writes = 1;
            if(strcmp(settingsNames[0], "ui_r_subdivisions") || settingsWritten[0] != subdivisions[selected]) ++errors;
        } else if(action == 2 && selected >= 0 && selected < 4) {
            commands = 1; if(strcmp(settingsCommand, presets[selected])) ++errors;
        } else if(action == 3) {
            writes = 1;
            if(strcmp(settingsNames[0], "m_pitch") || settingsWritten[0] != (selected ? -.022f : .022f)) ++errors;
        }
        if(settingsWrites != writes || settingsCommands != commands) ++errors;
    }
    for(step = 3998; step <= 5002; ++step) {
        settingsValue = step; settingsWrites = settingsCommands = 0;
        UI_Update("UI_SETRATE");
        if(settingsWrites != 2 || settingsCommands || strcmp(settingsNames[0], "ui_cl_maxpackets") ||
           strcmp(settingsText[0], step >= 5000 ? "100" : "15") || strcmp(settingsNames[1], "ui_cl_packetdup") ||
           strcmp(settingsText[1], step >= 4000 && step < 5000 ? "2" : "1")) ++errors;
    }
    settingsWrites = 0; UI_Update("ui_SetName"); UI_Update("ui_GetName");
    if(settingsWrites != 2 || strcmp(settingsNames[0], "name") || strcmp(settingsText[0], "^2New Name") ||
       strcmp(settingsNames[1], "ui_Name") || strcmp(settingsText[1], "^1Old Name")) ++errors;
    for(action = 0; action < 4; ++action) {
        settingsValue = FLT_MAX; settingsWrites = settingsCommands = 0;
        UI_Update(actions[action]);
        if(settingsWrites || settingsCommands) ++errors;
    }
    settingsWrites = settingsCommands = 0; UI_Update(NULL); UI_Update(""); UI_Update("unknown");
    if(settingsWrites || settingsCommands) ++errors;
    if(errors) fprintf(stderr, "%d settings failures\n", errors);
    return errors;
}
static int QDECL CatalogSyscall(int command, ...) {
    const char *directory, *extension;
    char *buffer;
    int capacity;
    va_list args;
    if(command != UI_FS_GETFILELIST) { fprintf(stderr, "Unexpected catalog syscall %d\n", command); exit(2); }
    va_start(args, command);
    directory = va_arg(args, const char *); extension = va_arg(args, const char *);
    buffer = va_arg(args, char *); capacity = va_arg(args, int);
    if(strcmp(directory, "$modlist") || strcmp(extension, "") || capacity != 2048) exit(2);
    if(catalogListMode == 0) {
        static const char list[] = "zmod\0Zulu\0amod\0\0nitmod\0N!tmod\0";
        memcpy(buffer, list, sizeof(list));
    } else if(catalogListMode == 1) memset(buffer, 'x', capacity);
    else {
        memset(buffer, 'x', capacity);
        memcpy(buffer, "good\0Good mod\0", 14);
    }
    va_end(args); return 3;
}
static int CheckCatalog(void) {
    static uiInfo_t saved;
    const char *titles[] = {"^1Zulu", "^2Alpha", "alpha", "^3Bravo", "Omega"};
    const int expected[] = {1, 3, 4, 0, 2};
    int a, b, c, d, e, i, errors = 0;
    char path[128], longname[130];
    const char stream[] = "nitmod\0N!tmod\0etmain\0\0";
    saved = uiInfo;
    for(a = 0; a < 5; ++a) for(b = 0; b < 5; ++b) for(c = 0; c < 5; ++c)
    for(d = 0; d < 5; ++d) for(e = 0; e < 5; ++e) {
        int order[5] = {a,b,c,d,e}, mask = 0;
        for(i = 0; i < 5; ++i) mask |= 1 << order[i];
        if(mask != 31) continue;
        uiInfo.mapCount = uiInfo.campaignCount = uiInfo.modCount = 5;
        for(i = 0; i < 5; ++i) {
            memset(&uiInfo.mapList[i], 0, sizeof(uiInfo.mapList[i]));
            memset(&uiInfo.campaignList[i], 0, sizeof(uiInfo.campaignList[i]));
            uiInfo.mapList[i].mapName = titles[order[i]];
            uiInfo.mapList[i].mapLoadName = titles[order[i]];
            uiInfo.mapList[i].levelShot = order[i] + 100;
            uiInfo.campaignList[i].campaignName = titles[order[i]];
            uiInfo.campaignList[i].campaignShortName = titles[order[i]];
            uiInfo.campaignList[i].progress = order[i];
            uiInfo.campaignList[i].mapInfos[0] = &uiInfo.mapList[0];
            uiInfo.modList[i].modName = titles[order[i]];
            uiInfo.modList[i].modDescr = titles[order[i]];
        }
        UI_SortCatalog(UI_CATALOG_MAPS); UI_SortCatalog(UI_CATALOG_CAMPAIGNS); UI_SortCatalog(UI_CATALOG_MODS);
        for(i = 0; i < 5; ++i) {
            if(strcmp(uiInfo.mapList[i].mapName, titles[expected[i]]) || uiInfo.mapList[i].levelShot != expected[i] + 100 ||
               strcmp(uiInfo.mapList[i].mapLoadName, titles[expected[i]]) ||
               uiInfo.campaignList[i].progress != expected[i] ||
               strcmp(uiInfo.campaignList[i].campaignName, titles[expected[i]]) ||
               uiInfo.campaignList[i].mapInfos[0] != &uiInfo.mapList[0] ||
               uiInfo.modList[i].modName != uiInfo.modList[i].modDescr) ++errors;
            if(i && strcmp(uiInfo.modList[i-1].modName, uiInfo.modList[i].modName) > 0) ++errors;
        }
    }
    for(i = 0; i <= sizeof(stream); ++i) {
        int offset = 0, n = 0;
        const char *value;
        while((value = UI_CatalogNextString(stream, i, &offset)) != NULL) {
            if(value < stream || value >= stream + i || offset > i) ++errors;
            ++n;
        }
        if(n != (i >= 7) + (i >= 14) + (i >= 21) + (i >= 22) + (i >= 23)) ++errors;
    }
    {
        const char *bad[] = {"", ".", "..", "../a.arena", "x/a", "x\\a", "C:a", "a\n", "a;cfg", "a\"cfg"};
        for(i = 0; i < sizeof(bad)/sizeof(bad[0]); ++i) if(UI_CatalogScriptPath(bad[i], path, sizeof(path))) ++errors;
    }
    memset(longname, 'a', sizeof(longname)); longname[119] = 0;
    if(!UI_CatalogScriptPath(longname, path, sizeof(path)) || strlen(path) != 127) ++errors;
    longname[119] = 'a'; longname[120] = 0;
    if(UI_CatalogScriptPath(longname, path, sizeof(path))) ++errors;
    if(!UI_CatalogScriptPath("goldrush.arena", path, sizeof(path)) || strcmp(path, "scripts/goldrush.arena")) ++errors;
    dllEntry(CatalogSyscall);
    for(catalogListMode = 0; catalogListMode < 3; ++catalogListMode) {
        char script[] = "LoadMods", *cursor = script;
        UI_RunMenuScript(&cursor);
        if(uiInfo.modCount != (catalogListMode == 0 ? 3 : catalogListMode == 1 ? 0 : 1)) ++errors;
        if(catalogListMode == 0 && (strcmp(uiInfo.modList[0].modName, "amod") ||
           *uiInfo.modList[0].modDescr || strcmp(uiInfo.modList[1].modName, "nitmod") ||
           strcmp(uiInfo.modList[2].modDescr, "Zulu"))) ++errors;
    }
    uiInfo = saved;
    if(errors) fprintf(stderr, "%d catalog failures\n", errors);
    return errors;
}
static int sliderReads, sliderWrites, sliderPics;
static float sliderRects[2][4];
static float SliderRead(const char *name) {
    if(!name || strcmp(name, "test_slider")) exit(2);
    ++sliderReads; return sliderValue;
}
static void SliderWrite(const char *name, const char *value) {
    if(!name || strcmp(name, "test_slider")) exit(2);
    ++sliderWrites; sliderWritten = (float)atof(value);
}
static void SliderColor(const float *color) { (void)color; }
static void SliderPic(float x, float y, float w, float h, qhandle_t shader) {
    if(sliderPics >= 2) exit(2);
    sliderRects[sliderPics][0] = x; sliderRects[sliderPics][1] = y;
    sliderRects[sliderPics][2] = w; sliderRects[sliderPics++][3] = h;
    (void)shader;
}
static int CheckSliders(displayContextDef_t *dc) {
    displayContextDef_t saved = *dc;
    itemDef_t item;
    editFieldDef_t edit;
    const int positions[] = {-7,-6,-5,0,24,48,72,95,96,97};
    const int keys[] = {K_MOUSE1,K_MOUSE2,K_MOUSE3,K_ENTER,K_LEFTARROW};
    int p,k,down,label,errors=0,savedMenus=menuCount;
    memset(&item,0,sizeof(item)); memset(&edit,0,sizeof(edit));
    item.type = ITEM_TYPE_SLIDER; item.typeData = &edit; item.cvar = "test_slider";
    item.window.flags = WINDOW_HASFOCUS | WINDOW_FOCUSPULSE;
    item.window.rect.x=10; item.window.rect.y=20; item.window.rect.w=220; item.window.rect.h=20;
    item.textRect.x=20; item.textRect.w=30;
    edit.minVal=-5; edit.maxVal=5;
    dc->getCVarValue=SliderRead; dc->setCVar=SliderWrite;
    dc->setColor=SliderColor; dc->drawHandlePic=SliderPic;
    dc->cursory=25;
    for(label=0;label<2;++label) for(p=0;p<10;++p) for(k=0;k<5;++k) for(down=0;down<2;++down) {
        float x=label?58:10;
        int valid=down && k<4 && positions[p]>-6 && positions[p]<96 && x+positions[p]>10;
        float expected=positions[p]<0?-5:-5+10*positions[p]/96.f;
        item.text=label?"Label":NULL; dc->cursorx=(int)x+positions[p]; sliderWrites=0;
        if(Item_Slider_HandleKey(&item,keys[k],down)!=valid || sliderWrites!=valid ||
           (valid && fabs(sliderWritten-expected)>.00001)) ++errors;
    }
    item.text=NULL; sliderValue=0; sliderReads=0;
    if(Item_Slider_ThumbPosition(&item)!=58 || sliderReads!=1 ||
       !Item_Slider_OverSlider(&item,58,25) || Item_Slider_OverSlider(&item,52,25)) ++errors;
    sliderPics=0; sliderReads=0; Item_Slider_Paint(&item);
    if(sliderPics!=2 || sliderReads!=1 || sliderRects[0][0]!=10 || sliderRects[0][1]!=21 ||
       sliderRects[0][2]!=96 || sliderRects[1][0]!=52 || sliderRects[1][2]!=12) ++errors;
    /* Exercise the real frame callback and release path, including data loss during drag. */
    menuCount=0; dc->cursorx=58; Item_StartCapture(&item,K_MOUSE1);
    for(p=0;p<10;++p) {
        float expected=positions[p]<0?-5:positions[p]>96?5:-5+10*positions[p]/96.f;
        dc->cursorx=10+positions[p]; sliderWrites=0; Menu_PaintAll();
        if(sliderWrites!=1 || fabs(sliderWritten-expected)>.00001) ++errors;
    }
    item.typeData=NULL; sliderWrites=0; Menu_PaintAll();
    if(sliderWrites || Item_Slider_OverSlider(&item,58,25)) ++errors;
    Item_HandleKey(&item,K_MOUSE1,qfalse); item.typeData=&edit; menuCount=savedMenus;
    for(p=0;p<5;++p) {
        edit.minVal=p==4?-FLT_MAX:-5;
        edit.maxVal=p==0?-5:p==1?-6:p==2?(float)strtod("nan",NULL):p==3?HUGE_VAL:FLT_MAX;
        sliderWrites=sliderReads=sliderPics=0; dc->cursorx=58;
        if(p<4) {
            if(Item_Slider_HandleKey(&item,K_MOUSE1,qtrue) || Item_Slider_OverSlider(&item,58,25)) ++errors;
            Item_Slider_Paint(&item); Item_Slider_ThumbPosition(&item);
            if(sliderWrites || sliderReads || sliderPics) ++errors;
        } else {
            sliderValue=0;
            if(Item_Slider_ThumbPosition(&item)!=58 || !Item_Slider_HandleKey(&item,K_MOUSE1,qtrue) || sliderWritten!=0) ++errors;
        }
    }
    edit.minVal=-5; edit.maxVal=5; sliderValue=(float)strtod("nan",NULL);
    if(Item_Slider_ThumbPosition(&item)!=10) ++errors;
    sliderValue=HUGE_VAL; if(Item_Slider_ThumbPosition(&item)!=106) ++errors;
    item.cvar=NULL; if(Item_Slider_HandleKey(&item,K_MOUSE1,qtrue)) ++errors;
    *dc=saved;
    if(errors) fprintf(stderr,"slider regression: %d failures\n",errors);
    return errors;
}
#ifndef FEEDER_SAVEGAMES
#define FEEDER_SAVEGAMES 0x10 /* Compiled legacy UI handler, not a PK3 identifier. */
#endif
extern void dllEntry(int (QDECL *)(int, ...));
extern qboolean Item_Parse(int, itemDef_t *);
extern void Script_ToggleCvarBit(itemDef_t *, qboolean *, char **);
extern qboolean Item_CheckBox_HandleKey(itemDef_t *, int);
extern void Item_CheckBox_Paint(itemDef_t *);
extern void Item_RunScript(itemDef_t *, qboolean *, const char *);
extern int Item_Multi_CountSettings(itemDef_t *);
extern int Item_Multi_FindCvarByValue(itemDef_t *);
extern const char *Item_Multi_Setting(itemDef_t *);
extern qboolean Item_Multi_HandleKey(itemDef_t *, int);
extern void Item_TextField_Paint(itemDef_t *);
extern void UI_RunMenuScript(char **);
static int actionWrites, actionReads;
static char actionCommand[512];
static const char *actionValue = "Question?";
static int QDECL ActionSyscall(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == UI_CMD_EXECUTETEXT) {
        if(va_arg(args, int) != EXEC_APPEND) exit(2);
        Q_strncpyz(actionCommand, va_arg(args, const char *), sizeof(actionCommand));
        ++actionWrites;
    } else if(command == UI_CVAR_VARIABLESTRINGBUFFER) {
        const char *name = va_arg(args, const char *);
        char *buffer = va_arg(args, char *);
        int size = va_arg(args, int);
        if(strcmp(name, "ui_poll") && strcmp(name, "ui_warnreason") && strcmp(name, "ui_warmup")) exit(2);
        Q_strncpyz(buffer, actionValue, size); ++actionReads;
    } else exit(2);
    va_end(args); return 0;
}
static char rosterPlayers[MAX_CLIENTS][128], rosterCommand[256];
static int rosterLocal, rosterCount, rosterReads, rosterWrites;
static int QDECL RosterSyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_GETCLIENTSTATE) {
        uiClientState_t *state = va_arg(args, uiClientState_t *);
        memset(state, 0, sizeof(*state)); state->clientNum = rosterLocal;
    } else if(command == UI_GETCONFIGSTRING) {
        int index = va_arg(args, int);
        char *out = va_arg(args, char *);
        int size = va_arg(args, int);
        if(index == CS_SERVERINFO) Com_sprintf(out, size, "\\sv_maxclients\\%d", rosterCount);
        else {
            index -= CS_PLAYERS;
            if(index < 0 || index >= MAX_CLIENTS) exit(2);
            Q_strncpyz(out, rosterPlayers[index], size); ++rosterReads;
        }
        result = 1;
    } else if(command == UI_CVAR_SET) {
        const char *name = va_arg(args, const char *);
        const char *value = va_arg(args, const char *);
        if(strcmp(name, "cg_selectedPlayer") && strcmp(name, "cg_selectedPlayerName")) exit(2);
        (void)value;
    } else if(command == UI_CVAR_VARIABLEVALUE) {
        if(strcmp(va_arg(args, const char *), "cg_selectedPlayer")) exit(2);
    } else if(command == UI_CMD_EXECUTETEXT) {
        if(va_arg(args, int) != EXEC_APPEND) exit(2);
        Q_strncpyz(rosterCommand, va_arg(args, const char *), sizeof(rosterCommand)); ++rosterWrites;
    } else { fprintf(stderr, "unexpected roster syscall %d\n", command); exit(2); }
    va_end(args); return result;
}
static int CheckRoster(void) {
    extern menuDef_t Menus[MAX_MENUS];
    static uiInfo_t saved;
    static menuDef_t savedMenu;
    itemDef_t items[2]; listBoxDef_t lists[2];
    int savedMenuCount = menuCount;
    int selected, scenario, slot, errors = 0;
    saved = uiInfo; savedMenu = Menus[0]; dllEntry(RosterSyscall);
    memset(&Menus[0], 0, sizeof(Menus[0])); memset(items, 0, sizeof(items)); memset(lists, 0, sizeof(lists));
    menuCount = 1; Menus[0].itemCount = 2;
    for(slot = 0; slot < 2; ++slot) {
        Menus[0].items[slot] = &items[slot]; items[slot].type = ITEM_TYPE_LISTBOX;
        items[slot].typeData = &lists[slot]; items[slot].special = slot ? FEEDER_TEAM_LIST : FEEDER_PLAYER_LIST;
    }
    rosterLocal = 0; rosterCount = MAX_CLIENTS;
    for(selected = 0; selected < MAX_CLIENTS; ++selected) for(scenario = 0; scenario < 6; ++scenario) {
        int expected, teamExpected;
        char command[256];
        memset(&uiInfo, 0, sizeof(uiInfo));
        for(slot = 0; slot < MAX_CLIENTS; ++slot)
            Com_sprintf(rosterPlayers[slot], sizeof(rosterPlayers[slot]), "\\n\\P%d\\t\\1\\mu\\%d\\ref\\%d", slot, slot & 1, slot % 3);
        UI_NitmodRefreshPlayers();
        uiInfo.playerIndex = uiInfo.teamIndex = selected;
        expected = teamExpected = selected;
        if(scenario == 0 && selected > 0) { rosterPlayers[0][0] = 0; --expected; teamExpected = -1; }
        if(scenario == 1) { rosterPlayers[selected][0] = 0; expected = teamExpected = -1; }
        if(scenario == 2) {
            Com_sprintf(rosterPlayers[selected], sizeof(rosterPlayers[selected]), "\\n\\Replacement\\t\\1");
            expected = teamExpected = -1;
        }
        if(scenario == 3) {
            Com_sprintf(rosterPlayers[selected], sizeof(rosterPlayers[selected]), "\\n\\P%d\\t\\2", selected);
            teamExpected = selected == 0 ? 0 : -1;
        }
        if(scenario == 4 && selected > 0) {
            Com_sprintf(rosterPlayers[0], sizeof(rosterPlayers[0]), "\\n\\P%d\\t\\1", selected);
        }
        UI_NitmodRefreshPlayers();
        if(uiInfo.playerIndex != expected || uiInfo.teamIndex != teamExpected) ++errors;
        if(items[0].cursorPos != expected || lists[0].cursorPos != expected ||
           items[1].cursorPos != teamExpected || lists[1].cursorPos != teamExpected) ++errors;
        if(expected >= 0 && uiInfo.playerClientNums[expected] != selected) ++errors;
        if(scenario == 5 && (uiInfo.playerMuted[selected] != (selected & 1) ||
            uiInfo.playerRefereeStatus[selected] != selected % 3)) ++errors;
        rosterWrites = 0; UI_NitmodMenuAction("voteKick");
        Com_sprintf(command, sizeof(command), "callvote kick \"P%d\"\n", selected);
        if(rosterWrites != (expected >= 0) || (expected >= 0 && strcmp(rosterCommand, command))) ++errors;
    }
    rosterCount = -1; rosterLocal = -1; rosterReads = 0;
    UI_NitmodRefreshPlayers();
    if(rosterReads || uiInfo.playerCount || uiInfo.myTeamCount || uiInfo.playerIndex != -1 || uiInfo.teamIndex != -1) ++errors;
    rosterCount = MAX_CLIENTS + 100; rosterLocal = MAX_CLIENTS; rosterReads = 0;
    UI_NitmodRefreshPlayers();
    if(rosterReads != MAX_CLIENTS || uiInfo.playerCount != MAX_CLIENTS || uiInfo.myTeamCount) ++errors;
    uiInfo = saved; Menus[0] = savedMenu; menuCount = savedMenuCount;
    if(errors) fprintf(stderr, "%d roster failures\n", errors);
    return errors;
}
static int CheckPlayerActions(void) {
    const struct { const char *script, *command; } actions[] = {
        {"voteKick", "callvote kick"},
        {"voteMute", "callvote mute"},
        {"voteUnMute", "callvote unmute"},
        {"voteReferee", "callvote referee"},
        {"voteUnReferee", "callvote unreferee"},
        {"rconKick", "rcon kick"},
        {"refKick", "ref kick"},
        {"rconBan", "rcon ban"},
        {"refMute", "ref mute"},
        {"refUnMute", "ref unmute"},
        {"refMakeAxis", "ref putaxis"},
        {"refMakeAllied", "ref putallies"},
        {"refMakeSpec", "ref remove"},
        {"refUnReferee", "ref unreferee"},
        {"refMakeReferee", "ref referee"},
        {"rconMakeReferee", "rcon makeReferee"},
        {"rconRemoveReferee", "rcon removeReferee"},
        {"rconMute", "rcon mute"},
        {"rconUnMute", "rcon unmute"},
        {"ignorePlayer", "ignore"},
        {"unIgnorePlayer", "unignore"},
    };
    const int counts[] = {-1, 0, 1, MAX_CLIENTS, MAX_CLIENTS + 1};
    const int rows[] = {-1, 0, MAX_CLIENTS - 1, MAX_CLIENTS};
    const char *names[] = {"^1Player Name", "", "bad\"name", "bad;quit", "bad\nname", "bad\\name"};
    int a, c, r, n, errors = 0;
    char script[64], expected[512], *args;
    dllEntry(ActionSyscall);
    for(a = 0; a < sizeof(actions)/sizeof(actions[0]); ++a)
    for(c = 0; c < 5; ++c) for(r = 0; r < 4; ++r) for(n = 0; n < 6; ++n) {
        int valid = counts[c] > 0 && counts[c] <= MAX_CLIENTS && rows[r] >= 0 && rows[r] < counts[c] && n == 0;
        uiInfo.playerCount = counts[c]; uiInfo.playerIndex = rows[r];
        if(rows[r] >= 0 && rows[r] < MAX_CLIENTS)
            Q_strncpyz(uiInfo.playerNames[rows[r]], names[n], sizeof(uiInfo.playerNames[0]));
        Q_strncpyz(script, actions[a].script, sizeof(script)); args = script;
        actionWrites = actionReads = 0;
        UI_RunMenuScript(&args);
        Com_sprintf(expected, sizeof(expected), "%s \"%s\"\n", actions[a].command, names[n]);
        if(actionWrites != valid || actionReads || (valid && strcmp(actionCommand, expected))) ++errors;
    }
    uiInfo.playerCount = 1; uiInfo.playerIndex = 0;
    strcpy(uiInfo.playerNames[0], "^1Player Name");
    for(a = 0; a < 3; ++a) for(n = 0; n < 6; ++n) {
        const char *commands[] = {"votePoll", "refWarning", "refWarmup"};
        actionValue = names[n]; actionReads = actionWrites = 0;
        Q_strncpyz(script, commands[a], sizeof(script)); args = script;
        UI_RunMenuScript(&args);
        if(actionReads != 1 || actionWrites != (n == 0)) ++errors;
        if(n == 0) {
            if(a == 0) Com_sprintf(expected, sizeof(expected), "callvote poll \"%s\"\n", actionValue);
            else if(a == 1) Com_sprintf(expected, sizeof(expected), "ref warn \"^1Player Name\" \"%s\"\n", actionValue);
            else Com_sprintf(expected, sizeof(expected), "ref warmup \"%s\"\n", actionValue);
            if(strcmp(actionCommand, expected)) ++errors;
        }
    }
    uiInfo.playerIndex = -1; actionReads = actionWrites = 0;
    if(!UI_NitmodMenuAction("VoTePoLl") || actionReads || actionWrites) ++errors;
    if(UI_NitmodMenuAction("unknown-action") || UI_NitmodMenuAction(NULL)) ++errors;
    uiInfo.playerCount = uiInfo.playerIndex = 0;
    return errors;
}

static int fileLength, fileHandle, fileOpens, fileReads, fileCloses, fileDeletes, fileCvars;
static int demoListCase, demoLists;
static int QDECL FileSyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_FS_FOPENFILE) {
        fileHandle_t *handle;
        if(strcmp(va_arg(args, const char *), "text.txt")) exit(2);
        handle = va_arg(args, fileHandle_t *);
        if(va_arg(args, int) != FS_READ) exit(2);
        *handle = fileHandle; ++fileOpens; result = fileLength;
    } else if(command == UI_FS_READ) {
        char *buffer = va_arg(args, char *);
        if(va_arg(args, int) != fileLength || va_arg(args, int) != 42 ||
           fileLength < 1 || fileLength >= MAX_MENUDEFFILE) exit(2);
        memset(buffer, 'x', fileLength); ++fileReads;
    } else if(command == UI_FS_FCLOSEFILE) {
        if(va_arg(args, int) != 42) exit(2);
        ++fileCloses;
    } else if(command == UI_CVAR_VARIABLEVALUE) {
        float protocol = 84.0f;
        if(strcmp(va_arg(args, const char *), "protocol")) exit(2);
        memcpy(&result, &protocol, sizeof(result)); ++fileCvars;
    } else if(command == UI_FS_GETFILELIST) {
        char *buffer;
        int size;
        if(strcmp(va_arg(args, const char *), "demos") || strcmp(va_arg(args, const char *), "dm_84")) exit(2);
        buffer = va_arg(args, char *); size = va_arg(args, int);
        if(size != 30000) exit(2);
        ++demoLists;
        if(demoListCase == 0) {
            static const char entries[] = "sample.dm_84\0x\0SECOND.DM_84\0";
            memcpy(buffer, entries, sizeof(entries)); result = 3;
        } else if(demoListCase == 1) result = -1;
        else if(demoListCase == 2) { memset(buffer, 'x', size); result = 1; }
        else if(demoListCase == 3) { strcpy(buffer, "sample.dm_84"); result = 0x7fffffff; }
        else result = 0;
    } else if(command == UI_FS_DELETEFILE) {
        if(strcmp(va_arg(args, const char *), "demos/sample.dm_84")) exit(2);
        ++fileDeletes;
    } else exit(2);
    va_end(args); return result;
}
static int CheckFileActions(void) {
    const int lengths[] = {-1, 0, 1, MAX_MENUDEFFILE - 1, MAX_MENUDEFFILE, 0x7fffffff};
    const int indices[] = {-1, 0, 1, 0x7fffffff};
    const char *names[] = {"sample", NULL, "", "../outside", "..\\outside", "C:outside", ".", ".."};
    int i, j, state, errors = 0;
    char longName[MAX_QPATH + 1];
    dllEntry(FileSyscall);
    fileOpens = fileReads = fileCloses = 0;
    if(UI_FileText(NULL) || UI_FileText("") || fileOpens) ++errors;
    for(j = 0; j < 2; ++j) for(i = 0; i < 6; ++i) {
        const char *text;
        int valid;
        fileLength = lengths[i]; fileHandle = j ? 42 : 0;
        fileOpens = fileReads = fileCloses = 0;
        valid = j && fileLength >= 0 && fileLength < MAX_MENUDEFFILE;
        text = UI_FileText("text.txt");
        if((text != NULL) != valid || fileOpens != 1 || fileCloses != j ||
           fileReads != (valid && fileLength > 0)) ++errors;
        if(text && ((int)strlen(text) != fileLength || (fileLength && text[fileLength-1] != 'x'))) ++errors;
    }
    memset(longName, 'x', MAX_QPATH); longName[MAX_QPATH] = 0;
    for(state = 0; state < 4; ++state) for(i = 0; i < 4; ++i) for(j = 0; j < 9; ++j) {
        char script[] = "deleteDemo", *args = script;
        int valid = state == 0 && indices[i] == 0 && j == 0;
        uiInfo.demoCount = state == 0 ? 1 : state == 1 ? 0 : state == 2 ? -1 : MAX_DEMOS + 1;
        uiInfo.demoIndex = indices[i]; uiInfo.demoList[0] = j == 8 ? longName : names[j];
        fileDeletes = fileCvars = 0;
        UI_RunMenuScript(&args);
        if(fileDeletes != valid || fileCvars != valid) ++errors;
    }
    for(demoListCase = 0; demoListCase < 5; ++demoListCase) {
        char script[] = "LoadDemos", *args = script;
        demoLists = fileCvars = 0;
        UI_RunMenuScript(&args);
        if(demoLists != 1 || fileCvars != 2 ||
           uiInfo.demoCount != (demoListCase == 0 ? 3 : demoListCase == 3 ? 1 : 0)) ++errors;
        if(demoListCase == 0 && (strcmp(uiInfo.demoList[0], "sample") ||
           strcmp(uiInfo.demoList[1], "x") || strcmp(uiInfo.demoList[2], "SECOND"))) ++errors;
    }
    uiInfo.demoCount = uiInfo.demoIndex = 0; uiInfo.demoList[0] = NULL;
    return errors;
}
static int launchCommands, launchCvars, launchStops, launchKind;
static int QDECL LaunchSyscall(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == UI_CMD_EXECUTETEXT) {
        const char *expected = launchKind == 0 ? "cinematic intro.roq 2\n" :
            launchKind == 1 ? "vid_restart;" : "demo \"sample\"\n";
        if(va_arg(args, int) != EXEC_APPEND || strcmp(va_arg(args, const char *), expected)) exit(2);
        ++launchCommands;
    } else if(command == UI_CVAR_SET) {
        if(launchKind != 1 || strcmp(va_arg(args, const char *), "fs_game") ||
           strcmp(va_arg(args, const char *), "nitmod")) exit(2);
        ++launchCvars;
    } else if(command == UI_CIN_STOPCINEMATIC) {
        if(launchKind != 0 || va_arg(args, int) != 42) exit(2);
        ++launchStops;
    } else exit(2);
    va_end(args); return 0;
}
static int CheckLaunchActions(void) {
    const int indices[] = {-1, 0, 1, 0x7fffffff};
    int i, state, errors = 0;
    dllEntry(LaunchSyscall);
    for(launchKind = 0; launchKind < 3; ++launchKind)
    for(state = 0; state < 6; ++state) for(i = 0; i < 4; ++i) {
        char script[32], *args = script;
        int valid = state == 0 && indices[i] == 0;
        int count = state == 1 ? 0 : state == 2 ? -1 : state == 3 ? 0x7fffffff : 1;
        uiInfo.movieCount = uiInfo.modCount = uiInfo.demoCount = count;
        uiInfo.movieIndex = uiInfo.modIndex = uiInfo.demoIndex = indices[i];
        uiInfo.movieList[0] = state == 4 ? NULL : state == 5 ? "" : "intro";
        uiInfo.modList[0].modName = state == 4 ? NULL : state == 5 ? "" : "nitmod";
        uiInfo.demoList[0] = state == 4 ? NULL : state == 5 ? "" : "sample";
        uiInfo.previewMovie = 42;
        launchCommands = launchCvars = launchStops = 0;
        strcpy(script, launchKind == 0 ? "playMovie" : launchKind == 1 ? "RunMod" : "RunDemo");
        UI_RunMenuScript(&args);
        if(launchCommands != valid || launchCvars != (valid && launchKind == 1) ||
           launchStops != (valid && launchKind == 0) ||
           uiInfo.previewMovie != (valid && launchKind == 0 ? -1 : 42)) ++errors;
    }
    uiInfo.movieCount = uiInfo.modCount = uiInfo.demoCount = 0;
    uiInfo.movieIndex = uiInfo.modIndex = uiInfo.demoIndex = 0;
    uiInfo.movieList[0] = uiInfo.modList[0].modName = uiInfo.demoList[0] = NULL;
    uiInfo.previewMovie = -1;
    return errors;
}
static int value, writes, drawn;
static int QDECL NoSelectionSyscall(int command, ...) { (void)command; exit(2); return 0; }
static int campaignWrites, campaignStops, campaignCompleted;
static int QDECL CampaignSyscall(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == UI_CIN_STOPCINEMATIC) {
        if(va_arg(args, int) != 42) exit(2);
        ++campaignStops;
    } else if(command == UI_CVAR_SET) {
        const char *name = va_arg(args, const char *), *text = va_arg(args, const char *);
        if(!strcmp(name, "ui_campaignIndex")) { if(strcmp(text, "0")) exit(2); }
        else if(!strcmp(name, "ui_currentCampaign")) { if(strcmp(text, "1")) exit(2); }
        else if(!strcmp(name, "ui_currentCampaignCompleted")) campaignCompleted = atoi(text);
        else exit(2);
        ++campaignWrites;
    } else exit(2);
    va_end(args); return 0;
}
static int CheckCampaignRows(void) {
    int i, handles, errors = 0;
    int oldCurrent = ui_currentCampaign.integer;
    int oldIndex = ui_campaignIndex.integer, oldComplete = ui_currentCampaignCompleted.integer;
    dllEntry(NoSelectionSyscall);
    uiInfo.campaignCount = 0;
    UI_FeederSelection(FEEDER_CAMPAIGNS, 0);
    if(*UI_FeederItemText(FEEDER_CAMPAIGNS, 0, 0, NULL, &handles)) ++errors;
    uiInfo.campaignCount = MAX_CAMPAIGNS + 1;
    if(UI_FeederCount(FEEDER_CAMPAIGNS) || *UI_FeederItemText(FEEDER_CAMPAIGNS, 0, 0, NULL, &handles)) ++errors;
    UI_FeederSelection(FEEDER_CAMPAIGNS, 0);
    uiInfo.campaignCount = 3;
    for(i = 0; i < 3; ++i) {
        memset(&uiInfo.campaignList[i], 0, sizeof(uiInfo.campaignList[i]));
        uiInfo.campaignList[i].order = i == 1 ? 0 : i == 2 ? 1 : 2;
        uiInfo.campaignList[i].unlocked = i != 2;
        uiInfo.campaignList[i].typeBits = 1 << GT_SINGLE_PLAYER;
        uiInfo.campaignList[i].campaignCinematic = -1;
    }
    uiInfo.campaignList[1].campaignName = "selected";
    uiInfo.campaignList[1].mapCount = 5;
    uiInfo.campaignList[1].progress = 5;
    if(strcmp(UI_FeederItemText(FEEDER_CAMPAIGNS, 0, 0, NULL, &handles), "selected")) ++errors;
    /* Locked order 1 must not fall back to physical entry 0. */
    UI_FeederSelection(FEEDER_CAMPAIGNS, 1);
    UI_FeederSelection(FEEDER_CAMPAIGNS, -1);
    UI_FeederSelection(FEEDER_CAMPAIGNS, 3);
    /* With all entries unlocked, count-1 points at a different campaign. */
    uiInfo.campaignList[2].unlocked = qtrue;
    uiInfo.campaignList[2].mapCount = 9;
    dllEntry(CampaignSyscall);
    campaignWrites = campaignStops = 0; campaignCompleted = -1;
    ui_currentCampaign.integer = 0x7fffffff;
    UI_FeederSelection(FEEDER_CAMPAIGNS, 0);
    if(campaignWrites != 3 || campaignStops || campaignCompleted != 1) ++errors;
    uiInfo.campaignList[1].campaignCinematic = 42;
    uiInfo.campaignList[1].progress = 4;
    campaignWrites = 0;
    UI_FeederSelection(FEEDER_CAMPAIGNS, 0);
    if(campaignWrites != 3 || campaignStops != 1 || campaignCompleted != 0 ||
       uiInfo.campaignList[1].campaignCinematic != -1) ++errors;
    for(i = 0; i < 3; ++i) memset(&uiInfo.campaignList[i], 0, sizeof(uiInfo.campaignList[i]));
    uiInfo.campaignCount = 0;
    ui_currentCampaign.integer = oldCurrent; ui_campaignIndex.integer = oldIndex;
    ui_currentCampaignCompleted.integer = oldComplete;
    return errors;
}
static int CheckMapRows(void) {
    int errors = 0, handles, i;
    int oldGame = ui_netGameType.integer, oldSingle = ui_gameType.integer;
    const char *text;
    dllEntry(NoSelectionSyscall);
    uiInfo.mapCount = 0; uiInfo.campaignCount = 3;
    ui_netGameType.integer = GT_WOLF_CAMPAIGN;
    for(i = 0; i < 3; ++i) {
        uiInfo.campaignList[i].typeBits = i == 1 ? 0 : 1 << GT_WOLF;
        uiInfo.campaignList[i].campaignName = i == 0 ? "first" : "last";
    }
    text = UI_FeederItemText(FEEDER_ALLMAPS, 0, 0, NULL, &handles);
    if(strcmp(text, "first")) ++errors;
    text = UI_FeederItemText(FEEDER_ALLMAPS, 1, 0, NULL, &handles);
    if(strcmp(text, "last")) ++errors;
    /* Invalid rows must not silently select row zero or write cvars. */
    for(i = -1; i <= 4; ++i) if(i < 0 || i >= 2) {
        if(*UI_FeederItemText(FEEDER_ALLMAPS, i, 0, NULL, &handles)) ++errors;
        UI_FeederSelection(FEEDER_ALLMAPS, i);
    }
    uiInfo.mapCount = MAX_MAPS; uiInfo.campaignCount = 0;
    if(*UI_FeederItemText(FEEDER_ALLMAPS, 0, 0, NULL, &handles)) ++errors;
    UI_FeederSelection(FEEDER_ALLMAPS, 0);
    uiInfo.campaignCount = MAX_CAMPAIGNS + 1;
    if(*UI_FeederItemText(FEEDER_ALLMAPS, 0, 0, NULL, &handles)) ++errors;
    ui_netGameType.integer = GT_WOLF; uiInfo.mapCount = 3;
    for(i = 0; i < 3; ++i) {
        uiInfo.mapList[i].active = i != 1;
        uiInfo.mapList[i].mapName = i == 0 ? "first map" : "last map";
    }
    if(strcmp(UI_FeederItemText(FEEDER_ALLMAPS, 1, 0, NULL, &handles), "last map")) ++errors;
    UI_FeederSelection(FEEDER_ALLMAPS, 2);
    ui_gameType.integer = -1;
    if(*UI_FeederItemText(FEEDER_MAPS, 0, 0, NULL, &handles)) ++errors;
    UI_FeederSelection(FEEDER_MAPS, 0);
    ui_gameType.integer = 0x7fffffff;
    if(*UI_FeederItemText(FEEDER_MAPS, 0, 0, NULL, &handles)) ++errors;
    UI_FeederSelection(FEEDER_MAPS, 0);
    uiInfo.mapCount = uiInfo.campaignCount = 0;
    for(i = 0; i < 3; ++i) {
        memset(&uiInfo.mapList[i], 0, sizeof(uiInfo.mapList[i]));
        memset(&uiInfo.campaignList[i], 0, sizeof(uiInfo.campaignList[i]));
    }
    ui_netGameType.integer = oldGame; ui_gameType.integer = oldSingle;
    return errors;
}
static int CheckMapFilters(void) {
    static uiInfo_t saved;
    int oldGame = ui_netGameType.integer, oldSingle = ui_gameType.integer;
    int game, local, i, handles, errors = 0;
    const int invalid[] = {-1, 32, 0x7fffffff};
    saved = uiInfo;
    dllEntry(NoSelectionSyscall);
    uiInfo.numGameTypes = 1; ui_gameType.integer = 0;
    uiInfo.mapCount = 3; uiInfo.campaignCount = 2;
    uiInfo.campaignList[0].typeBits = 1 << GT_WOLF;
    uiInfo.campaignList[1].typeBits = 0;
    uiInfo.campaignList[0].campaignName = "campaign";
    for(local = 0; local < 2; ++local) for(game = 0; game < 32; ++game) {
        int feeder = local ? FEEDER_MAPS : FEEDER_ALLMAPS;
        int expected = game == GT_WOLF_CAMPAIGN ? 1 : 2;
        ui_netGameType.integer = game;
        /* Opposite local category: row mapping must follow the network
         * filter, not silently switch arrays when local settings differ. */
        uiInfo.gameTypes[0].gtEnum = game == GT_WOLF_CAMPAIGN ? GT_WOLF : GT_WOLF_CAMPAIGN;
        for(i = 0; i < MAX_MAPS; ++i) uiInfo.mapList[i].active = qtrue;
        for(i = 0; i < 3; ++i) {
            uiInfo.mapList[i].typeBits = i == 1 ? 0 : (int)(1u << game);
            uiInfo.mapList[i].mapName = i == 0 ? "first" : "last";
        }
        if(UI_FeederCount((float)feeder) != expected) ++errors;
        for(i = 0; i < MAX_MAPS; ++i) {
            int active = game != GT_WOLF_CAMPAIGN && (i == 0 || i == 2);
            if(!!uiInfo.mapList[i].active != active) ++errors;
        }
        if(expected && strcmp(UI_FeederItemText((float)feeder, expected - 1, 0, NULL, &handles),
            game == GT_WOLF_CAMPAIGN ? "campaign" : "last")) ++errors;
        if(*UI_FeederItemText((float)feeder, expected, 0, NULL, &handles)) ++errors;
    }
    for(i = 0; i < 3; ++i) {
        ui_netGameType.integer = uiInfo.gameTypes[0].gtEnum = invalid[i];
        uiInfo.mapList[MAX_MAPS - 1].active = qtrue;
        if(UI_FeederCount(FEEDER_ALLMAPS) || UI_FeederCount(FEEDER_MAPS) ||
           uiInfo.mapList[MAX_MAPS - 1].active) ++errors;
    }
    ui_netGameType.integer = uiInfo.gameTypes[0].gtEnum = GT_WOLF;
    uiInfo.mapCount = MAX_MAPS + 1;
    if(UI_FeederCount(FEEDER_ALLMAPS)) ++errors;
    uiInfo.mapCount = -1;
    if(UI_FeederCount(FEEDER_ALLMAPS)) ++errors;
    ui_netGameType.integer = GT_WOLF_CAMPAIGN;
    uiInfo.campaignCount = MAX_CAMPAIGNS + 1;
    if(UI_FeederCount(FEEDER_ALLMAPS)) ++errors;
    uiInfo.campaignCount = -1;
    if(UI_FeederCount(FEEDER_ALLMAPS)) ++errors;
    ui_netGameType.integer = GT_WOLF;
    uiInfo.mapCount = 1; uiInfo.mapList[0].typeBits = 1 << GT_WOLF;
    uiInfo.numGameTypes = MAX_GAMETYPES + 1;
    if(UI_FeederCount(FEEDER_MAPS) != 1) ++errors;
    uiInfo.numGameTypes = 1; ui_gameType.integer = -1;
    if(UI_FeederCount(FEEDER_MAPS) != 1) ++errors;
    ui_gameType.integer = 1;
    if(UI_FeederCount(FEEDER_MAPS) != 1) ++errors;
    uiInfo = saved;
    ui_netGameType.integer = oldGame; ui_gameType.integer = oldSingle;
    return errors;
}
static int CheckListText(void) {
    const int feeders[] = {FEEDER_MODS, FEEDER_CINEMATICS, FEEDER_DEMOS, FEEDER_PROFILES, FEEDER_SAVEGAMES};
    const int capacities[] = {MAX_MODS, MAX_MOVIES, MAX_DEMOS, MAX_PROFILES, MAX_SAVEGAMES};
    int *counts[] = {&uiInfo.modCount, &uiInfo.movieCount, &uiInfo.demoCount, &uiInfo.profileCount, &uiInfo.savegameCount};
    int f, c, i, errors = 0;
    for(f = 0; f < 5; ++f) {
        int values[] = {-1, 0, 1, capacities[f], capacities[f] + 1, 0x7fffffff};
        for(c = 0; c < 6; ++c) {
            int expected = values[c] >= 0 && values[c] <= capacities[f] ? values[c] : 0;
            int indices[] = {-1, expected, capacities[f], 0x7fffffff};
            *counts[f] = values[c];
            if(UI_FeederCount((float)feeders[f]) != expected) ++errors;
            for(i = 0; i < 4; ++i) {
                int handles = 99;
                const char *text = UI_FeederItemText((float)feeders[f], indices[i], 0, NULL, &handles);
                if(!text || *text || handles) ++errors;
            }
        }
        *counts[f] = 1;
    }
    uiInfo.modList[0].modName = "nitmod"; uiInfo.modList[0].modDescr = "Nitmod";
    uiInfo.movieList[0] = "intro"; uiInfo.demoList[0] = "sample";
    uiInfo.profileList[0].name = "tester";
    for(f = 0; f < 4; ++f) {
        const char *expected[] = {"Nitmod", "intro", "sample", "tester"};
        int handles = 99;
        const char *text = UI_FeederItemText((float)feeders[f], 0, 0, NULL, &handles);
        if(!text || !strstr(text, expected[f]) || handles) ++errors;
    }
    uiInfo.modList[0].modDescr = "";
    { int handles; if(strcmp(UI_FeederItemText(FEEDER_MODS, 0, 0, NULL, &handles), "nitmod")) ++errors; }
    uiInfo.modList[0].modName = uiInfo.modList[0].modDescr = NULL;
    uiInfo.movieList[0] = uiInfo.demoList[0] = uiInfo.profileList[0].name = NULL;
    for(f = 0; f < 4; ++f) {
        int handles;
        const char *text = UI_FeederItemText((float)feeders[f], 0, 0, NULL, &handles);
        if(!text || *text) ++errors;
    }
    for(f = 0; f < 5; ++f) *counts[f] = 0;
    return errors;
}
static int previewStarts, previewStops, previewRuns, previewDraws, previewExtents, previewFailure, profileWrites;
static int QDECL PreviewSyscall(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == UI_CIN_PLAYCINEMATIC) {
        int i;
        if(strcmp(va_arg(args, const char *), "intro.roq")) exit(2);
        for(i = 0; i < 4; ++i) if(va_arg(args, int)) exit(2);
        if(va_arg(args, int) != (CIN_loop | CIN_silent)) exit(2);
        ++previewStarts;
        va_end(args); return previewFailure ? -1 : 42;
    }
    if(command == UI_CVAR_SET) {
        if(strcmp(va_arg(args, const char *), "ui_profile") || strcmp(va_arg(args, const char *), "tester")) exit(2);
        ++profileWrites;
    } else {
        if(va_arg(args, int) != 42) exit(2);
        if(command == UI_CIN_STOPCINEMATIC) ++previewStops;
        else if(command == UI_CIN_RUNCINEMATIC) ++previewRuns;
        else if(command == UI_CIN_DRAWCINEMATIC) ++previewDraws;
        else if(command == UI_CIN_SETEXTENTS) {
            if(va_arg(args, int) != 10 || va_arg(args, int) != 20 ||
               va_arg(args, int) != 100 || va_arg(args, int) != 60) exit(2);
            ++previewExtents;
        } else exit(2);
    }
    va_end(args); return 0;
}
static int CheckPreviewLifecycle(void) {
    rectDef_t rect = {10, 20, 100, 60};
    vec4_t color = {1,1,1,1};
    const int invalid[] = {-1, 1, 0x7fffffff};
    const int feeders[] = {FEEDER_MODS, FEEDER_CINEMATICS, FEEDER_DEMOS, FEEDER_PROFILES};
    int i, j, errors = 0;
    dllEntry(PreviewSyscall);
    uiInfo.movieCount = uiInfo.modCount = uiInfo.demoCount = uiInfo.profileCount = 1;
    uiInfo.movieIndex = uiInfo.modIndex = uiInfo.demoIndex = uiInfo.profileIndex = 0;
    uiInfo.movieList[0] = "intro"; uiInfo.profileList[0].name = "tester";
    uiInfo.previewMovie = -1;
    previewStarts = previewStops = previewRuns = previewDraws = previewExtents = previewFailure = profileWrites = 0;
    for(i = 0; i < 10; ++i) UI_DrawPreviewCinematic(&rect, 1, color);
    if(previewStarts != 1 || previewRuns != 10 || previewDraws != 10 || previewExtents != 10) ++errors;
    for(i = 0; i < 4; ++i) for(j = 0; j < 3; ++j) UI_FeederSelection(feeders[i], invalid[j]);
    if(previewStops || profileWrites || uiInfo.movieIndex || uiInfo.modIndex || uiInfo.demoIndex || uiInfo.profileIndex) ++errors;
    UI_FeederSelection(FEEDER_PROFILES, 0); if(profileWrites != 1) ++errors;
    UI_FeederSelection(FEEDER_CINEMATICS, 0);
    if(previewStops != 1 || uiInfo.previewMovie != -1) ++errors;
    previewFailure = 1;
    for(i = 0; i < 10; ++i) UI_DrawPreviewCinematic(&rect, 1, color);
    if(previewStarts != 2 || previewRuns != 10 || uiInfo.previewMovie != -2) ++errors;
    previewFailure = 0; UI_FeederSelection(FEEDER_CINEMATICS, 0);
    UI_DrawPreviewCinematic(&rect, 1, color);
    if(previewStarts != 3 || previewRuns != 11) ++errors;
    uiInfo.movieCount = 0;
    for(i = 0; i < 10; ++i) UI_DrawPreviewCinematic(&rect, 1, color);
    if(previewStarts != 3 || previewStops != 2 || uiInfo.previewMovie != -1) ++errors;
    uiInfo.movieCount = MAX_MOVIES + 1;
    UI_DrawPreviewCinematic(&rect, 1, color);
    uiInfo.movieCount = 1; uiInfo.movieList[0] = NULL;
    UI_DrawPreviewCinematic(&rect, 1, color);
    if(previewStarts != 3 || previewRuns != 11) ++errors;
    uiInfo.movieCount = uiInfo.modCount = uiInfo.demoCount = uiInfo.profileCount = 0;
    uiInfo.profileList[0].name = NULL;
    return errors;
}
static int parsePosition, parseMask;
static int stopped;
static int browserCount = 1, browserVisible, browserQueries, browserReady, browserReleased;
static const char *browserGame;
static int browserNxac;
static int browserAll, browserClients=3, browserCompare=1, browserPing=50;
static int browserHumanMode,browserStatusIndex;
static int QDECL BrowserSyscall(int command, ...) {
    va_list args;
    int result = 0, index, size;
    char *out;
    const char *name;
    va_start(args, command);
    switch(command) {
    case UI_CVAR_UPDATE: (void)va_arg(args, vmCvar_t *); break;
    case UI_CVAR_VARIABLESTRINGBUFFER:
        name = va_arg(args, const char *);
        if(strcmp(name, "cl_motdString")) exit(2);
        out = va_arg(args, char *); size = va_arg(args, int);
        Q_strncpyz(out, "test", size); break;
    case UI_LAN_GETSERVERCOUNT: (void)va_arg(args, int); result = browserCount; break;
    case UI_LAN_MARKSERVERVISIBLE:
        (void)va_arg(args, int); index = va_arg(args, int);
        result = va_arg(args, int);
        if(index == -1 || index == browserCount - 1) browserVisible = result;
        result = 0; break;
    case UI_LAN_SERVERISVISIBLE:
        (void)va_arg(args, int); index = va_arg(args, int);
        if(index < 0 || index >= MAX_GLOBAL_SERVERS) exit(2);
        result = browserAll || (index == browserCount - 1 && browserVisible); break;
    case UI_LAN_GETSERVERPING:
        (void)va_arg(args, int); (void)va_arg(args, int); result = browserPing; break;
    case UI_LAN_GETSERVERINFO:
        (void)va_arg(args, int); (void)va_arg(args, int);
        out = va_arg(args, char *); size = va_arg(args, int);
        Com_sprintf(out, size, "\\game\\%s\\clients\\%d\\gametype\\2", browserGame, browserClients); break;
    case UI_LAN_GETSERVERADDRESSSTRING:
        (void)va_arg(args, int); browserStatusIndex=va_arg(args, int);
        out = va_arg(args, char *); size = va_arg(args, int);
        Q_strncpyz(out, "127.0.0.1:27960", size); break;
    case UI_LAN_SERVERSTATUS:
        name = va_arg(args, const char *);
        if(strcmp(name, "127.0.0.1:27960")) exit(2);
        out = va_arg(args, char *); size = va_arg(args, int);
        if(!out) { if(size) exit(2); ++browserReleased; break; }
        ++browserQueries; result = browserReady;
        if(result) {
            if(browserHumanMode) Com_sprintf(out,size,"\\sv_NxAC\\%d\\humans\\%d",browserNxac,8-browserStatusIndex);
            else Com_sprintf(out, size, "\\sv_NxAC\\%d", browserNxac);
        }
        break;
    case UI_R_REGISTERSHADERNOMIP: (void)va_arg(args, const char *); result = 1; break;
    case UI_LAN_COMPARESERVERS:
        (void)va_arg(args, int); (void)va_arg(args, int); (void)va_arg(args, int);
        index = va_arg(args, int); result = va_arg(args, int);
        result = (index < result ? -1 : index > result ? 1 : 0) * browserCompare; break;
    default: fprintf(stderr, "Unexpected browser syscall %d\n", command); exit(2);
    }
    va_end(args);
    return result;
}

static int CheckBrowser(void) {
    static const char *games[] = {"nitmod", "NITMOD", "etmain", ""};
    int mod, nx, game, status, errors = 0, i;
    dllEntry(BrowserSyscall);
    ui_netSource.integer = AS_GLOBAL; ui_joinGameType.integer = -1;
    for(mod = 0; mod <= 3; ++mod) for(nx = 0; nx <= 3; ++nx)
    for(game = 0; game < 4; ++game) for(status = 0; status <= 1; ++status) {
        int matches = mod == 1 ? game < 2 : mod == 2 ? game >= 2 : 1;
        int query = matches && mod == 1 && (nx == 1 || nx == 2);
        int expected = matches && (!query || (nx == 1 ? status != 0 : status == 0));
        ui_browserNitmodonly.integer = mod; ui_browserNxAConly.integer = nx;
        browserGame = games[game]; browserNxac = status; browserReady = 1; browserQueries = browserReleased = 0;
        UI_BuildServerDisplayList(qtrue);
        if(uiInfo.serverStatus.numDisplayServers != expected || browserQueries != query ||
           browserReleased != query || browserVisible) ++errors;
    }
    /* Pending replies must not inflate player totals or prematurely hide a server. */
    ui_browserNitmodonly.integer = ui_browserNxAConly.integer = 1;
    browserGame = "nitmod"; browserNxac = 1; browserReady = 0; browserQueries = browserReleased = 0;
    UI_BuildServerDisplayList(qtrue);
    UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers || uiInfo.serverStatus.numPlayersOnServers ||
       browserQueries != 2 || browserReleased || !browserVisible) ++errors;
    browserReady = 1;
    UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers != 1 || uiInfo.serverStatus.numPlayersOnServers != 3 ||
       browserReleased != 1 || browserVisible) ++errors;
    /* Appending the last permitted slot must not overwrite the adjacent UI state. */
    ui_browserNitmodonly.integer = ui_browserNxAConly.integer = 0;
    browserCount = MAX_DISPLAY_SERVERS; browserVisible = 1;
    uiInfo.serverStatus.numDisplayServers = MAX_DISPLAY_SERVERS - 1;
    for(i = 0; i < MAX_DISPLAY_SERVERS - 1; ++i) uiInfo.serverStatus.displayServers[i] = i;
    uiInfo.serverStatus.numPlayersOnServers = 100;
    UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers != MAX_DISPLAY_SERVERS ||
       uiInfo.serverStatus.displayServers[MAX_DISPLAY_SERVERS - 1] != MAX_DISPLAY_SERVERS - 1 ||
       uiInfo.serverStatus.numPlayersOnServers != 103) ++errors;
    browserCount++; browserVisible = 1;
    UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers != MAX_DISPLAY_SERVERS ||
       uiInfo.serverStatus.displayServers[MAX_DISPLAY_SERVERS - 1] != MAX_DISPLAY_SERVERS - 1) ++errors;
    /* Refresh every favorite repeatedly: sorting accepts comparator signs,
     * player counts are replaced, and a server appears exactly once. */
    browserAll=1; browserPing=0; browserGame="nitmod";
    ui_netSource.integer=AS_FAVORITES;
    for(mod=0;mod<2;++mod) for(nx=1;nx<=128;nx*=2) {
        browserCompare=mod ? -7 : 19; browserCount=nx; browserClients=3;
        UI_BuildServerDisplayList(qtrue);
        for(game=0;game<8;++game) {
            int expectedClients;
            browserClients=game==6 ? -10 : game==7 ? 999 : game+1;
            expectedClients=game==6 ? 0 : game==7 ? MAX_CLIENTS : game+1;
            UI_BuildServerDisplayList(2);
            if(uiInfo.serverStatus.numDisplayServers!=nx ||
               uiInfo.serverStatus.numPlayersOnServers!=nx*expectedClients) ++errors;
            for(i=0;i<nx;++i)
                if(uiInfo.serverStatus.displayServers[i]!=(mod ? nx-1-i : i)) ++errors;
        }
    }
    /* A source change without force must discard the previous source's list. */
    ui_netSource.integer=AS_GLOBAL; browserCount=1; browserClients=3; browserPing=50;
    UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers!=1 || uiInfo.serverStatus.numPlayersOnServers!=3) ++errors;
    browserCount=-2; uiInfo.uiDC.realTime=2147483647;
    UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers || uiInfo.serverStatus.numPlayersOnServers ||
       uiInfo.serverStatus.nextDisplayRefresh!=2147483647) ++errors;
    browserCount=1;
    UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers!=1 || uiInfo.serverStatus.numPlayersOnServers!=3) ++errors;
    browserAll=0; browserCount=1; browserClients=3; browserCompare=1; browserPing=50;
    uiInfo.uiDC.realTime=0; uiInfo.serverStatus.nextDisplayRefresh=0;
    /* Original human-count column uses status, not the master client count. */
    if(UI_ServerHumanCount("\\humans\\2\\\\0 30 Alice\\0 40 Bob\\0 0 Bot","")!=2 ||
       UI_ServerHumanCount("\\sv_hostname\\test\\\\0 30 Alice\\0 0 Bot\\0 -1 Connecting","")!=1 ||
       UI_ServerHumanCount("\\sv_hostname\\test","\\version\\ET Legacy\\humans\\4")!=4 ||
       UI_ServerHumanCount("\\humans\\999","")!=MAX_CLIENTS ||
       UI_ServerHumanCount("\\humans\\-1","")!=0) ++errors;
    browserAll=browserHumanMode=1; browserCount=8; browserClients=10; browserReady=1;
    uiInfo.serverStatus.sortKey=SORT_CLIENTS; uiInfo.serverStatus.sortDir=0;
    UI_BuildServerDisplayList(qtrue);
    if(uiInfo.serverStatus.numDisplayServers!=8) ++errors;
    for(i=0;i<8;++i) if(uiInfo.serverStatus.displayServers[i]!=7-i) ++errors;
    uiInfo.serverStatus.sortDir=1; UI_ServersSort(SORT_CLIENTS,qtrue);
    for(i=0;i<8;++i) if(uiInfo.serverStatus.displayServers[i]!=i) ++errors;
    /* Pending then success, and separately timeout: no duplicated totals. */
    browserCount=1; browserReady=0; uiInfo.uiDC.realTime=100;
    UI_BuildServerDisplayList(qtrue);
    if(uiInfo.serverStatus.numDisplayServers || uiInfo.serverStatus.numPlayersOnServers) ++errors;
    browserReady=1; UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers!=1 || uiInfo.serverStatus.numPlayersOnServers!=10) ++errors;
    browserReady=0; UI_BuildServerDisplayList(qtrue);
    uiInfo.uiDC.realTime=5100; UI_BuildServerDisplayList(2);
    if(uiInfo.serverStatus.numDisplayServers!=1 || uiInfo.serverStatus.numPlayersOnServers!=10) ++errors;
    browserAll=browserHumanMode=0; browserClients=3; browserReady=1;
    uiInfo.serverStatus.sortKey=uiInfo.serverStatus.sortDir=0;
    uiInfo.uiDC.realTime=uiInfo.serverStatus.nextDisplayRefresh=0;
    return errors;
}
static void StopCinematic(int handle) {
    if(handle != 42) exit(2);
    ++stopped;
}
static int QDECL ParserSyscall(int command, ...) {
    va_list args;
    pc_token_t *token;
    static const char *tokens[] = {"{", "bitflag", "0", "}"};
    if(command != UI_PC_READ_TOKEN) exit(2);
    va_start(args, command);
    if(va_arg(args, int) != 1) exit(2);
    token = va_arg(args, pc_token_t *);
    va_end(args);
    if(parsePosition >= 4) return 0;
    memset(token, 0, sizeof(*token));
    Q_strncpyz(token->string, tokens[parsePosition], sizeof(token->string));
    if(parsePosition == 2) {
        token->type = TT_NUMBER; token->intvalue = parseMask;
        token->floatvalue = (float)parseMask;
        Com_sprintf(token->string, sizeof(token->string), "%d", parseMask);
    }
    ++parsePosition;
    return 1;
}
static void GetString(const char *name, char *out, int size) {
    if(strcmp(name, "flags")) exit(2);
    Com_sprintf(out, size, "%d", value);
}
static float GetValue(const char *name) {
    if(strcmp(name, "flags")) exit(2);
    return (float)value;
}
static void SetValue(const char *name, const char *text) {
    if(strcmp(name, "flags")) exit(2);
    value = atoi(text); ++writes;
}
static void Draw(float x, float y, float w, float h, qhandle_t shader) {
    (void)x; (void)y; (void)w; (void)h; drawn = shader;
}
static const char *editInput;
static int editWidthCalls, editDraws, editOverstrike;
static char editDrawn[512];
static qboolean EditOverstrike(void) { return editOverstrike; }
static int EditWidth(const char *text, float scale, int limit, fontInfo_t *font) {
    (void)scale; (void)limit; (void)font;
    if(++editWidthCalls > 300) exit(2);
    return (int)strlen(text);
}
static void EditDraw(float x, float y, float sx, float sy, vec4_t color, const char *text,
                     float adjust, int limit, int style, fontInfo_t *font) {
    (void)x; (void)y; (void)sx; (void)sy; (void)color; (void)adjust; (void)limit; (void)style; (void)font;
    ++editDraws; Q_strncpyz(editDrawn, text, sizeof(editDrawn));
}
static int QDECL EditSyscall(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == UI_CVAR_VARIABLESTRINGBUFFER) {
        char *out; int size;
        if(strcmp(va_arg(args, const char *), "edit_test")) exit(2);
        out = va_arg(args, char *); size = va_arg(args, int);
        Q_strncpyz(out, editInput, size);
    } else if(command != UI_KEY_GETOVERSTRIKEMODE) exit(2);
    va_end(args); return command == UI_KEY_GETOVERSTRIKEMODE ? editOverstrike : 0;
}
static int CheckPanelEdit(displayContextDef_t *dc) {
    panel_button_t button;
    panel_button_text_t font;
    const char *inputs[] = {"", "abcdef", "^1colored"};
    char source[512], expected[512];
    int mode, focused, blink, overstrike, width, input, errors = 0;
    memset(&button, 0, sizeof(button)); memset(&font, 0, sizeof(font));
    button.font = &font;
    dc->textWidthExt = EditWidth; dc->drawTextExt = EditDraw; dc->getOverstrikeMode = EditOverstrike;
    dllEntry(EditSyscall);
    for(mode = 0; mode <= 1; ++mode) for(focused = 0; focused <= 1; ++focused)
    for(blink = 0; blink <= 1; ++blink) for(overstrike = 0; overstrike <= 1; ++overstrike)
    for(width = -1; width <= 14; ++width) for(input = 0; input < 3; ++input) {
        int length, offset;
        editInput = inputs[input]; editOverstrike = overstrike;
        button.data[0] = mode ? 256 : 0;
        button.text = mode ? editInput : "edit_test";
        button.rect.w = (float)width; dc->realTime = blink * 1000;
        BG_PanelButtons_SetFocusButton(focused ? &button : NULL);
        Com_sprintf(source, sizeof(source), "%s%s%s", mode ? "^7" : "", editInput,
            focused && blink ? (overstrike ? "^0|" : "^0_") : " ");
        length = (int)strlen(source);
        offset = width < 0 ? length : length > width ? length - width : 0;
        Com_sprintf(expected, sizeof(expected), "%s%s", mode ? "" : "^7", source + offset);
        editWidthCalls = editDraws = 0;
        BG_PanelButton_RenderEdit(&button);
        if(editDraws != 1 || strcmp(editDrawn, expected) || editWidthCalls > length) ++errors;
    }
    BG_PanelButtons_SetFocusButton(NULL);
    return errors;
}
static void EditGetString(const char *name, char *out, int size) {
    if(strcmp(name, "edit_test")) exit(2);
    Q_strncpyz(out, editInput, size);
}
static int FieldWidth(const char *text, float scale, int limit) {
    return EditWidth(text, scale, limit, NULL);
}
static void FieldDraw(float x, float y, float scale, vec4_t color, const char *text,
                      float adjust, int limit, int style) {
    EditDraw(x, y, scale, scale, color, text, adjust, limit, style, NULL);
}
static int CheckTextField(displayContextDef_t *dc) {
    itemDef_t item;
    editFieldDef_t edit;
    const int offsets[] = {-1, 0, 3, 6, 7, 1024};
    int i, width, errors = 0;
    memset(&item, 0, sizeof(item)); memset(&edit, 0, sizeof(edit));
    item.typeData = &edit; item.text = ""; item.cvar = "edit_test";
    item.textRect.w = 1;
    dc->getCVarString = EditGetString; dc->textWidth = FieldWidth; dc->drawText = FieldDraw;
    editInput = "abcdef";
    for(i = 0; i < sizeof(offsets)/sizeof(offsets[0]); ++i) for(width = -1; width < 15; ++width) {
        int start = offsets[i] < 0 || offsets[i] > 6 ? 0 : offsets[i];
        int available = width - 1;
        int skip = available < 0 ? 6 - start : 6 - start > available ? 6 - start - available : 0;
        edit.paintOffset = offsets[i]; item.window.rect.w = (float)width;
        editDraws = editWidthCalls = 0;
        Item_TextField_Paint(&item);
        if(edit.paintOffset != start || editDraws != 1 || strcmp(editDrawn, editInput + start + skip) ||
           editWidthCalls > 6 - start) ++errors;
    }
    dc->getCVarString = GetString;
    return errors;
}
static int CheckMultiOptions(void) {
    itemDef_t item;
    multiDef_t multi;
    int count, mode, direction, current, errors = 0;
    const char *labels[] = {"zero", "one", "two"};
    const char *values[] = {"0", "1", "2"};
    memset(&item, 0, sizeof(item)); memset(&multi, 0, sizeof(multi));
    item.cvar = "flags"; item.type = ITEM_TYPE_MULTI;
    item.window.flags = WINDOW_HASFOCUS;
    item.window.rect.w = item.window.rect.h = 10;
    writes = 0;
    if(strcmp(Item_Multi_Setting(&item), "None Defined") || Item_Multi_HandleKey(&item, K_MOUSE1) ||
       Item_Multi_HandleKey(NULL, K_MOUSE2) || Item_Multi_CountSettings(NULL)) ++errors;
    item.typeData = &multi;
    for(count = -1; count <= MAX_MULTI_CVARS + 1; ++count) {
        if(count > 0 && count <= MAX_MULTI_CVARS) continue;
        multi.count = count;
        if(Item_Multi_CountSettings(&item) || Item_Multi_FindCvarByValue(&item) ||
           strcmp(Item_Multi_Setting(&item), "None Defined") ||
           Item_Multi_HandleKey(&item, K_MOUSE1) || Item_Multi_HandleKey(&item, K_MOUSE2)) ++errors;
    }
    if(writes) ++errors;
    multi.count = 3;
    for(current = 0; current < 3; ++current) {
        multi.cvarList[current] = labels[current]; multi.cvarStr[current] = values[current];
        multi.cvarValue[current] = current;
    }
    for(mode = 0; mode <= 1; ++mode) for(direction = 0; direction <= 1; ++direction)
    for(current = 0; current < 3; ++current) {
        int expected = (current + (direction ? 2 : 1)) % 3;
        multi.strDef = mode; value = current; writes = 0;
        if(Item_Multi_FindCvarByValue(&item) != current || strcmp(Item_Multi_Setting(&item), labels[current]) ||
           !Item_Multi_HandleKey(&item, direction ? K_MOUSE2 : K_MOUSE1) || value != expected || writes != 1) ++errors;
    }
    value = 99;
    if(strcmp(Item_Multi_Setting(&item), "Custom")) ++errors;
    multi.undefinedStr = "server value";
    if(strcmp(Item_Multi_Setting(&item), "server value")) ++errors;
    item.cvar = NULL; writes = 0;
    if(Item_Multi_HandleKey(&item, K_ENTER) || Item_Multi_FindCvarByValue(&item) || writes ||
       strcmp(Item_Multi_Setting(&item), "server value")) ++errors;
    return errors;
}
#include "check_ui_status.h"
#include "check_ui_search.h"
#include "check_ui_descriptions.h"
#include "check_ui_bindings.h"
extern int Menu_ItemsMatchingGroup(menuDef_t *, const char *);
extern itemDef_t *Menu_GetMatchingItemByNumber(menuDef_t *, int, const char *);
static int CheckMenuGroups(void) {
    menuDef_t menu;
    itemDef_t first, second;
    int errors = 0;
    memset(&menu, 0, sizeof(menu)); memset(&first, 0, sizeof(first)); memset(&second, 0, sizeof(second));
    menu.itemCount = 3; menu.items[0] = &first; menu.items[2] = &second;
    first.window.name = "panel_one"; first.window.group = "panel";
    second.window.group = "panel_two";
    if(Menu_ItemsMatchingGroup(&menu, "panel*") != 2 ||
       Menu_GetMatchingItemByNumber(&menu, 1, "panel*") != &second ||
       Menu_ItemsMatchingGroup(&menu, "PANEL_ONE") != 1 ||
       Menu_ItemsMatchingGroup(&menu, "PANEL*") != 0 ||
       Menu_GetMatchingItemByNumber(&menu, 2, "panel*")) ++errors;
    if(Menu_ItemsMatchingGroup(NULL, "*") || Menu_ItemsMatchingGroup(&menu, NULL) ||
       Menu_GetMatchingItemByNumber(&menu, -1, "*") || Menu_GetMatchingItemByNumber(NULL, 0, "*")) ++errors;
    menu.itemCount = MAX_MENUITEMS + 1;
    if(Menu_ItemsMatchingGroup(&menu, "*") || Menu_GetMatchingItemByNumber(&menu, 0, "*")) ++errors;
    return errors;
}
int main(void) {
    displayContextDef_t dc;
    itemDef_t item;
    menuDef_t menu;
    int initial, mask, errors = 0;
    memset(&dc, 0, sizeof(dc)); memset(&item, 0, sizeof(item));
    memset(&menu, 0, sizeof(menu));
    dc.getCVarString = GetString; dc.getCVarValue = GetValue;
    dc.setCVar = SetValue; dc.drawHandlePic = Draw;
    dc.stopCinematic = StopCinematic;
    dc.Assets.checkboxCheck = 1; dc.Assets.checkboxCheckNot = 2;
    dc.cursorx = dc.cursory = 5;
    Init_Display(&dc); String_Init();
    errors += CheckMenuGroups();
    errors += CheckWideUI();
    errors += CheckBindings(&dc);
    dllEntry(ParserSyscall);
    for(mask = 1; mask <= 16; mask <<= 1) {
        parsePosition = 0; parseMask = mask;
        if(!Item_Parse(1, &item) || parsePosition != 4 || item.bitflag != mask) ++errors;
    }
    item.parent = &menu; item.cvar = "flags";
    item.type = ITEM_TYPE_CHECKBOX; item.window.flags = WINDOW_HASFOCUS;
    item.window.rect.w = item.window.rect.h = 10;
    for(initial = 0; initial < 32; ++initial) for(mask = 1; mask <= 16; mask <<= 1) {
        char command[64], *args = command;
        qboolean abort = qfalse;
        value = initial; writes = 0; item.bitflag = mask;
        Item_CheckBox_Paint(&item);
        if(drawn != ((initial & mask) ? 1 : 2)) ++errors;
        if(!Item_CheckBox_HandleKey(&item, K_MOUSE1) || writes || value != initial) ++errors;
        Com_sprintf(command, sizeof(command), "flags %d", mask);
        Script_ToggleCvarBit(&item, &abort, &args);
        if(value != (initial ^ mask) || writes != 1 || abort) ++errors;
        Item_CheckBox_Paint(&item);
        if(drawn != ((value & mask) ? 1 : 2)) ++errors;
    }
    item.bitflag = 0; value = 3; writes = 0;
    if(!Item_CheckBox_HandleKey(&item, K_MOUSE1) || value || writes != 1) ++errors;
    {
        itemDef_t targets[3];
        int i;
        memset(targets, 0, sizeof(targets));
        menu.itemCount = 3;
        for(i = 0; i < 3; ++i) {
            menu.items[i] = &targets[i]; targets[i].parent = &menu;
            targets[i].window.cinematic = -1;
            targets[i].window.flags = WINDOW_DECORATION;
        }
        targets[0].window.name = "filtericonNxAC";
        targets[1].window.name = "tricheckactionmultiui_browserNxAConly";
        targets[2].window.name = "unrelated";
        targets[0].window.group = targets[1].window.group = "nxac";
        for(value = -1; value <= 1; ++value) {
            Item_RunScript(&item, NULL, "condhideshow filtericonNxAC ; condhideshow tricheckactionmultiui_browserNxAConly ;");
            for(i = 0; i < 2; ++i)
                if(targets[i].window.flags != (WINDOW_DECORATION | (value ? WINDOW_VISIBLE : 0))) ++errors;
            if(targets[2].window.flags != WINDOW_DECORATION) ++errors;
        }
        value = 0; stopped = 0; targets[0].window.cinematic = 42;
        Item_RunScript(&item, NULL, "condhideshow nxac ;");
        if(stopped != 1 || targets[0].window.cinematic != -1) ++errors;
        for(i = 0; i < 3; ++i) if(targets[i].window.flags != WINDOW_DECORATION) ++errors;
        value = 1;
        Item_RunScript(&item, NULL, "condhideshow missing ; condhideshow nxac ;");
        for(i = 0; i < 2; ++i) if(!(targets[i].window.flags & WINDOW_VISIBLE)) ++errors;
        item.cvar = NULL; value = 0;
        Item_RunScript(&item, NULL, "condhideshow nxac ;");
        for(i = 0; i < 2; ++i) if(!(targets[i].window.flags & WINDOW_VISIBLE)) ++errors;
        item.cvar = "flags";
        Item_RunScript(&item, NULL, "condhideshow");
        for(i = 0; i < 2; ++i) if(!(targets[i].window.flags & WINDOW_VISIBLE)) ++errors;
    }
    errors += CheckMultiOptions();
    errors += CheckSliders(&dc);
    errors += CheckPanelEdit(&dc);
    errors += CheckTextField(&dc);
    errors += CheckBrowser();
    errors += CheckLaunchActions();
    errors += CheckPreviewLifecycle();
    errors += CheckMapPreview();
    errors += CheckListText();
    errors += CheckMapRows();
    errors += CheckMapFilters();
    errors += CheckCampaignRows();
    errors += CheckFileActions();
    errors += CheckPlayerActions();
    errors += CheckRoster();
    errors += CheckCatalog();
    errors += CheckCampaignCatalog();
    errors += CheckCampaignSave();
    errors += CheckSettings();
    errors += CheckServerStatus();
    errors += CheckPlayerSearch();
    errors += CheckDescriptions();
    {
        const int counts[] = {-1, 0, 1, MAX_CLIENTS, MAX_CLIENTS + 1};
        const int indexes[] = {-1, 0, MAX_CLIENTS - 1, MAX_CLIENTS};
        const int rules[] = {UI_SHOW_PLAYERMUTED, UI_SHOW_PLAYERNOTMUTED,
            UI_SHOW_PLAYERNOREFEREE, UI_SHOW_PLAYERREFEREE};
        int c, p, muted, ref, r;
        for(c = 0; c < 5; ++c) for(p = 0; p < 4; ++p)
        for(muted = 0; muted < 2; ++muted) for(ref = RL_NONE; ref <= RL_RCON; ++ref) {
            int valid = counts[c] > 0 && counts[c] <= MAX_CLIENTS &&
                indexes[p] >= 0 && indexes[p] < counts[c];
            uiInfo.playerCount = counts[c]; uiInfo.playerIndex = indexes[p];
            if(indexes[p] >= 0 && indexes[p] < MAX_CLIENTS) {
                uiInfo.playerMuted[indexes[p]] = muted;
                uiInfo.playerRefereeStatus[indexes[p]] = ref;
            }
            if(UI_NitmodPlayerSelectionValid() != valid) ++errors;
            for(r = 0; r < 4; ++r) {
                int expected = valid && (r == 0 ? muted : r == 1 ? !muted :
                    r == 2 ? ref == RL_NONE : ref == RL_REFEREE);
                if(UI_OwnerDrawVisible(rules[r]) != expected) ++errors;
            }
            if(UI_OwnerDrawVisible(UI_SHOW_PLAYERMUTED | UI_SHOW_PLAYERNOTMUTED)) ++errors;
        }
    }
    if(errors) fprintf(stderr, "%d UI regression failures\n", errors);
    return errors != 0;
}
