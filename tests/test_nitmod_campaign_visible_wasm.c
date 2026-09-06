#include "ui_local.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
uiInfo_t uiInfo;
vmCvar_t ui_currentCampaign;
static float selected;
float trap_Cvar_VariableValue(const char *name) { assert(!strcmp(name, "ui_campaignmap")); return selected; }
int main(void) {
    static const int exists[] = {UI_SHOW_CAMPAIGNMAP1EXISTS, UI_SHOW_CAMPAIGNMAP2EXISTS,
        UI_SHOW_CAMPAIGNMAP3EXISTS, UI_SHOW_CAMPAIGNMAP4EXISTS,
        UI_SHOW_CAMPAIGNMAP5EXISTS, UI_SHOW_CAMPAIGNMAP6EXISTS};
    int count, map, progress, i, cases = 0;
    uiInfo.campaignCount = 1;
    for(count = 0; count <= 6; ++count) {
        uiInfo.campaignList[0].mapCount = count;
        for(i = 0; i < 6; ++i) assert(!!UI_NitmodCampaignVisible(exists[i]) == (count > i));
        for(progress = 0; progress <= 6; ++progress) {
            uiInfo.campaignList[0].progress = progress;
            for(map = -1; map <= 6; ++map) {
                selected = map;
                assert(!!UI_NitmodCampaignVisible(UI_SHOW_SELECTEDCAMPAIGNMAPPLAYABLE) ==
                    (map >= 0 && map < count && map <= progress));
                assert(!!UI_NitmodCampaignVisible(UI_SHOW_SELECTEDCAMPAIGNMAPNOTPLAYABLE) ==
                    (map >= 0 && map < count && map > progress));
                ++cases;
            }
        }
    }
    selected = NAN;
    assert(!UI_NitmodCampaignVisible(UI_SHOW_SELECTEDCAMPAIGNMAPPLAYABLE));
    ui_currentCampaign.integer = -1;
    assert(!UI_NitmodCampaignVisible(exists[0]));
    ui_currentCampaign.integer = 1;
    assert(!UI_NitmodCampaignVisible(exists[0]));
    ui_currentCampaign.integer = 0;
    uiInfo.campaignCount = MAX_CAMPAIGNS + 1;
    assert(!UI_NitmodCampaignVisible(exists[0]));
    printf("WASM campaign visibility: %d selection/progress cases, six map flags and invalid states passed\n", cases);
    return 0;
}
