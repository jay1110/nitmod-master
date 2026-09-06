"""Source checks for shared campaign preview selection, not renderer replay."""
from pathlib import Path
source=(Path(__file__).resolve().parents[1]/'src_2.60/ui/ui_main.c').read_text()
helper=source.split('static int UI_CampaignPreviewIndex(',1)[1].split('static void UI_DrawCampaignPreview',1)[0]
assert 'uiInfo.campaignCount <= 0' in helper
assert 'uiInfo.campaignCount > MAX_CAMPAIGNS' in helper
assert 'selection->integer >= uiInfo.campaignCount' in helper
assert 'selection->integer = 0;' in helper
for name in ('Preview','Cinematic','Name','MapPreview'):
    body=source.split('static void UI_DrawCampaign'+name+'(',1)[1].split('\nstatic ',1)[0]
    assert 'int campaign = UI_CampaignPreviewIndex(net);' in body
    assert body.index('if(campaign < 0) return;') < body.index('uiInfo.campaignList[campaign]')
    assert 'campaign > uiInfo.campaignCount' not in body
print('All four campaign preview selection routes verified')
body=source.split('static void UI_DrawCampaignMapPreview(',1)[1].split('static void UI_DrawMissionBriefingMap',1)[0]
assert 'map >= uiInfo.campaignList[campaign].mapCount) return;' not in body
assert 'uiInfo.campaignList[campaign].mapInfos[map] : NULL;' in body
assert 'trap_R_RegisterShaderNoMip("levelshots/unknownmap")' in body
assert body.count('progress < map') == 1
assert body.index('UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, shot)') < body.index('progress < map')
print('Empty-slot image and shared progress overlay source checks passed')
