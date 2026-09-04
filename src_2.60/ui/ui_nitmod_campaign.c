#include "ui_local.h"
#include <float.h>

/* Original UI_LoadCampaigns (ELF 0x11c10): semicolon-separated load names,
 * first arena match, unknown maps omitted, duplicates retained in order. */
static qboolean UI_CampaignMaps(campaignInfo_t *campaign, const char *text) {
    const char *start = text;
    campaign->mapCount = 0;
    memset(campaign->mapInfos, 0, sizeof(campaign->mapInfos));
    if(uiInfo.mapCount < 0 || uiInfo.mapCount > MAX_MAPS) return qfalse;
    while(*start) {
        const char *end = start;
        char name[128];
        int length, i;
        while(*end && *end != ';') ++end;
        length = (int)(end - start);
        if(length >= sizeof(name)) return qfalse;
        memcpy(name, start, length); name[length] = '\0';
        for(i = 0; i < uiInfo.mapCount; ++i) {
            if(uiInfo.mapList[i].mapLoadName && !Q_stricmp(uiInfo.mapList[i].mapLoadName, name)) {
                if(campaign->mapCount == MAX_MAPS_PER_CAMPAIGN) return qfalse;
                campaign->mapInfos[campaign->mapCount++] = &uiInfo.mapList[i];
                break;
            }
        }
        start = *end ? end + 1 : end;
    }
    return qtrue;
}

/* Commit only a closed record. A malformed file must not seed the next file's
 * partially initialized campaign. PC/String_Alloc retain normal UI ownership. */
void UI_LoadCampaignsFromFile(const char *filename) {
    campaignInfo_t next;
    pc_token_t token;
    int handle;
    if(!filename || uiInfo.campaignCount < 0 || uiInfo.campaignCount >= MAX_CAMPAIGNS) return;
    handle = trap_PC_LoadSource(filename);
    if(!handle) { trap_Print(va(S_COLOR_RED "file not found: %s\n", filename)); return; }
    while(uiInfo.campaignCount < MAX_CAMPAIGNS && trap_PC_ReadToken(handle, &token)) {
        if(strcmp(token.string, "{")) goto invalid;
        memset(&next, 0, sizeof(next));
        next.campaignCinematic = next.campaignShot = -1;
        while(trap_PC_ReadToken(handle, &token)) {
            const char **field = NULL;
            if(!strcmp(token.string, "}")) {
                /* Missing shortnames used to crash save/hash and next lookup. */
                if(!next.campaignShortName || !*next.campaignShortName) goto invalid;
                next.unlocked = next.initial && (next.typeBits & (1 << GT_SINGLE_PLAYER));
                uiInfo.campaignList[uiInfo.campaignCount++] = next;
                break;
            }
            if(!Q_stricmp(token.string, "shortname")) field = &next.campaignShortName;
            else if(!Q_stricmp(token.string, "name")) field = &next.campaignName;
            else if(!Q_stricmp(token.string, "description")) field = &next.campaignDescription;
            else if(!Q_stricmp(token.string, "image")) field = &next.campaignShotName;
            else if(!Q_stricmp(token.string, "next")) field = &next.nextCampaignShortName;
            if(field) {
                if(!PC_String_Parse(handle, field) || !*field) goto invalid;
            } else if(!Q_stricmp(token.string, "initial")) next.initial = qtrue;
            else if(!Q_stricmp(token.string, "type")) {
                if(!trap_PC_ReadToken(handle, &token)) goto invalid;
                if(strstr(token.string, "wolfsp")) next.typeBits |= 1 << GT_SINGLE_PLAYER;
                if(strstr(token.string, "wolfmp")) next.typeBits |= 1 << GT_WOLF;
                if(strstr(token.string, "wolfsw")) next.typeBits |= 1 << GT_WOLF_STOPWATCH;
                if(strstr(token.string, "wolflms")) next.typeBits |= 1 << GT_WOLF_LMS;
            } else if(!Q_stricmp(token.string, "maps")) {
                if(!trap_PC_ReadToken(handle, &token) || !UI_CampaignMaps(&next, token.string)) goto invalid;
            } else if(!Q_stricmp(token.string, "maptc")) {
                int axis;
                for(axis = 0; axis < 2; ++axis) {
                    if(!trap_PC_ReadToken(handle, &token) ||
                       !(token.floatvalue >= -FLT_MAX && token.floatvalue <= FLT_MAX)) goto invalid;
                    next.mapTC[0][axis] = token.floatvalue;
                    next.mapTC[1][axis] = token.floatvalue + 650.0f;
                }
            }
            /* Unknown keywords retain the original token-at-a-time handling. */
        }
        if(strcmp(token.string, "}")) goto invalid;
    }
    trap_PC_FreeSource(handle);
    return;
invalid:
    trap_Print(va(S_COLOR_RED "invalid or incomplete campaign inside: %s\n", filename));
    trap_PC_FreeSource(handle);
}

int UI_FindCampaignInCampaignList(const char *shortName) {
    int i;
    if(!shortName || !*shortName || uiInfo.campaignCount < 0 || uiInfo.campaignCount > MAX_CAMPAIGNS) return -1;
    for(i = 0; i < uiInfo.campaignCount; ++i) {
        const char *name = uiInfo.campaignList[i].campaignShortName;
        if(name && !Q_stricmp(name, shortName)) return i;
    }
    return -1;
}

void UI_OrderCampaigns(void) {
    qboolean visited[MAX_CAMPAIGNS];
    int i, order = 0;
    if(uiInfo.campaignCount < 0 || uiInfo.campaignCount > MAX_CAMPAIGNS) return;
    memset(visited, 0, sizeof(visited));
    for(i = 0; i < uiInfo.campaignCount; ++i)
        if(uiInfo.campaignList[i].initial && (uiInfo.campaignList[i].typeBits & (1 << GT_SINGLE_PLAYER))) break;
    while(i >= 0 && i < uiInfo.campaignCount && !visited[i]) {
        visited[i] = qtrue;
        uiInfo.campaignList[i].order = order++;
        i = UI_FindCampaignInCampaignList(uiInfo.campaignList[i].nextCampaignShortName);
    }
}

/* Serverinfo contains a BSP load name, not the localized/colorized menu title.
 * Reset the map cursor for every campaign (the original retained it by mistake). */
static campaignInfo_t *UI_CurrentCampaign(void) {
    char info[MAX_INFO_STRING];
    const char *name;
    int i, j;
    if(uiInfo.campaignCount < 0 || uiInfo.campaignCount > MAX_CAMPAIGNS) return NULL;
    trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
    name = Info_ValueForKey(info, "mapname");
    if(!*name) return NULL;
    for(i = 0; i < uiInfo.campaignCount; ++i) {
        campaignInfo_t *campaign = &uiInfo.campaignList[i];
        if(campaign->mapCount < 0 || campaign->mapCount > MAX_MAPS_PER_CAMPAIGN) continue;
        for(j = 0; j < campaign->mapCount; ++j) {
            mapInfo *map = campaign->mapInfos[j];
            if(map && map->mapLoadName && !Q_stricmp(name, map->mapLoadName)) return campaign;
        }
    }
    return NULL;
}

const char *UI_NameForCampaign(void) {
    campaignInfo_t *campaign = UI_CurrentCampaign();
    return campaign ? campaign->campaignName : NULL;
}

const char *UI_DescriptionForCampaign(void) {
    campaignInfo_t *campaign = UI_CurrentCampaign();
    return campaign ? campaign->campaignDescription : NULL;
}
