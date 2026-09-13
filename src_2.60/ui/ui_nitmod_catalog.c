#include "ui_local.h"

/* Original UI_RunMenuScript LoadMods, ELF 0x221fb..0x22862.
 * The directory remains the sort/start key; this is presentation only. */
void UI_SetModDisplayName(modInfo_t *mod) {
    static const struct { const char *directory, *display; } names[] = {
        {"nitmod", "^7N^1!^7tmod"},
        {"jaymod", "^8Jay^4mod"},
        {"nq", "^?No Quarter"},
        {"legacy", "^1ET^7:Legacy"},
        {"etpro", "^7ETPro"},
        {"comp", "^7Comp^1ET"},
        {"silent", "^7silEnT"},
        {"etpub", "^7ETPub"}
    };
    int i;
    mod->modDisplayName[0] = '\0';
    if(!mod->modName) return;
    for(i = 0; i < (int)(sizeof(names) / sizeof(names[0])); ++i) {
        if(!Q_stricmp(mod->modName, names[i].directory)) {
            Q_strncpyz(mod->modDisplayName, names[i].display, sizeof(mod->modDisplayName));
            return;
        }
    }
}

/* Read one engine FS_GetFileList string without scanning outside its buffer.
 * Empty strings are valid descriptions in the paired $modlist format. */
const char *UI_CatalogNextString(const char *buffer, int capacity, int *offset) {
    int start;
    if(!buffer || !offset || *offset < 0 || *offset >= capacity) return NULL;
    start = *offset;
    while(*offset < capacity && buffer[*offset]) ++*offset;
    if(*offset == capacity) return NULL;
    ++*offset;
    return buffer + start;
}

qboolean UI_CatalogScriptPath(const char *name, char *path, int capacity) {
    int i;
    if(!name || !*name || !path || capacity < 10) return qfalse;
    for(i = 0; name[i]; ++i) {
        unsigned char c = (unsigned char)name[i];
        if(i >= capacity - 9 || c < 32 || c == '/' || c == '\\' || c == ':' ||
           c == '"' || c == ';') return qfalse;
    }
    if(!strcmp(name, ".") || !strcmp(name, "..")) return qfalse;
    Com_sprintf(path, capacity, "scripts/%s", name);
    return qtrue;
}

/* Original comparators use strcmp, not case folding, after Q_CleanStr.
 * Keep the stored colored titles and the complete metadata records intact. */
static int UI_CatalogTitleCompare(const char *a, const char *b) {
    char left[1024], right[1024];
    Q_strncpyz(left, a ? a : "", sizeof(left));
    Q_strncpyz(right, b ? b : "", sizeof(right));
    Q_CleanStr(left); Q_CleanStr(right);
    return strcmp(left, right);
}

static int QDECL UI_SortArenas(const void *a, const void *b) {
    return UI_CatalogTitleCompare(((const mapInfo *)a)->mapName, ((const mapInfo *)b)->mapName);
}
static int QDECL UI_SortCampaigns(const void *a, const void *b) {
    return UI_CatalogTitleCompare(((const campaignInfo_t *)a)->campaignName, ((const campaignInfo_t *)b)->campaignName);
}
static int QDECL UI_SortMods(const void *a, const void *b) {
    const char *left = ((const modInfo_t *)a)->modName, *right = ((const modInfo_t *)b)->modName;
    return strcmp(left ? left : "", right ? right : "");
}

void UI_SortCatalog(uiCatalog_t catalog) {
    switch(catalog) {
    case UI_CATALOG_MAPS:
        if(uiInfo.mapCount > 1 && uiInfo.mapCount <= MAX_MAPS)
            qsort(uiInfo.mapList, uiInfo.mapCount, sizeof(uiInfo.mapList[0]), UI_SortArenas);
        break;
    case UI_CATALOG_CAMPAIGNS:
        if(uiInfo.campaignCount > 1 && uiInfo.campaignCount <= MAX_CAMPAIGNS)
            qsort(uiInfo.campaignList, uiInfo.campaignCount, sizeof(uiInfo.campaignList[0]), UI_SortCampaigns);
        break;
    case UI_CATALOG_MODS:
        if(uiInfo.modCount > 1 && uiInfo.modCount <= MAX_MODS)
            qsort(uiInfo.modList, uiInfo.modCount, sizeof(uiInfo.modList[0]), UI_SortMods);
        break;
    }
}
