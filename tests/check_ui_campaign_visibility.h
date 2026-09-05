static float visibilityMap;
static int QDECL CampaignVisibilitySyscall(int command, ...) {
    va_list args;
    union { float f; int i; } result;
    va_start(args, command);
    if(command != UI_CVAR_VARIABLEVALUE || strcmp(va_arg(args, const char *), "ui_campaignmap")) exit(2);
    va_end(args);
    result.f = visibilityMap;
    return result.i;
}
static int CheckCampaignVisibility(void) {
    const int rules[] = { UI_SHOW_CAMPAIGNMAP1EXISTS, UI_SHOW_CAMPAIGNMAP2EXISTS,
        UI_SHOW_CAMPAIGNMAP3EXISTS, UI_SHOW_CAMPAIGNMAP4EXISTS,
        UI_SHOW_CAMPAIGNMAP5EXISTS, UI_SHOW_CAMPAIGNMAP6EXISTS,
        UI_SHOW_SELECTEDCAMPAIGNMAPPLAYABLE, UI_SHOW_SELECTEDCAMPAIGNMAPNOTPLAYABLE };
    const int counts[] = {-1, 0, 1, MAX_CAMPAIGNS, MAX_CAMPAIGNS + 1};
    const int indexes[] = {-1, 0, MAX_CAMPAIGNS - 1, MAX_CAMPAIGNS, 0x7fffffff};
    int oldCount = uiInfo.campaignCount, oldIndex = ui_currentCampaign.integer;
    campaignInfo_t first = uiInfo.campaignList[0], last = uiInfo.campaignList[MAX_CAMPAIGNS - 1];
    int count, index, maps, progress, map, rule, errors = 0;
    dllEntry(CampaignVisibilitySyscall);
    for(count = 0; count < 5; ++count) for(index = 0; index < 5; ++index)
    for(maps = -1; maps <= MAX_MAPS_PER_CAMPAIGN + 1; ++maps)
    for(progress = -1; progress <= MAX_MAPS_PER_CAMPAIGN + 1; ++progress)
    for(map = -1; map <= MAX_MAPS_PER_CAMPAIGN; ++map) {
        int valid = counts[count] > 0 && counts[count] <= MAX_CAMPAIGNS &&
            indexes[index] >= 0 && indexes[index] < counts[count] &&
            maps >= 0 && maps <= MAX_MAPS_PER_CAMPAIGN;
        uiInfo.campaignCount = counts[count]; ui_currentCampaign.integer = indexes[index];
        uiInfo.campaignList[0].mapCount = uiInfo.campaignList[MAX_CAMPAIGNS - 1].mapCount = maps;
        uiInfo.campaignList[0].progress = uiInfo.campaignList[MAX_CAMPAIGNS - 1].progress = progress;
        visibilityMap = (float)map;
        for(rule = 0; rule < 8; ++rule) {
            int expected = valid && (rule < 6 ? maps >= rule + 1 :
                map >= 0 && map < maps && progress >= 0 && progress <= MAX_MAPS_PER_CAMPAIGN &&
                (rule == 6 ? map <= progress : map > progress));
            if(UI_OwnerDrawVisible(rules[rule]) != expected) ++errors;
            if(UI_OwnerDrawVisible(rules[rule] | UI_SHOW_NOTFFA)) ++errors;
        }
        if(UI_OwnerDrawVisible(rules[6] | rules[7])) ++errors;
    }
    uiInfo.campaignCount = 1; ui_currentCampaign.integer = 0;
    uiInfo.campaignList[0].mapCount = 3; uiInfo.campaignList[0].progress = 1;
    visibilityMap = 1.75f;
    if(!UI_OwnerDrawVisible(rules[6]) || UI_OwnerDrawVisible(rules[7])) ++errors;
    visibilityMap = (float)sqrt(-1.0);
    if(UI_OwnerDrawVisible(rules[6]) || UI_OwnerDrawVisible(rules[7])) ++errors;
    visibilityMap = FLT_MAX;
    if(UI_OwnerDrawVisible(rules[6]) || UI_OwnerDrawVisible(rules[7])) ++errors;
    uiInfo.campaignCount = oldCount; ui_currentCampaign.integer = oldIndex;
    uiInfo.campaignList[0] = first; uiInfo.campaignList[MAX_CAMPAIGNS - 1] = last;
    if(errors) fprintf(stderr, "%d campaign visibility failures\n", errors);
    return errors;
}
