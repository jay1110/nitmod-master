extern displayContextDef_t *DC;
static char descriptionLines[16][1024];
static float descriptionX[16],descriptionY[16];
static int descriptionCount;
static int DescriptionWidth(const char *text,float scale,int limit) { return (int)strlen(text)*8; }
static int DescriptionHeight(const char *text,float scale,int limit) { return 12; }
static void DescriptionPaint(float x,float y,float scale,vec4_t color,const char *text,float adjust,int limit,int style) {
    if(descriptionCount>=16 || strlen(text)>=1024) exit(2);
    Q_strncpyz(descriptionLines[descriptionCount],text,1024);
    descriptionX[descriptionCount]=x; descriptionY[descriptionCount]=y; ++descriptionCount;
}
static int CheckDescriptions(void) {
    static uiInfo_t saved;
    displayContextDef_t context, *old=DC;
    rectDef_t rect={10,20,100,200}; vec4_t color={1,1,1,1};
    vmCvar_t oldGame=ui_netGameType,oldMap=ui_currentMap,oldNet=ui_currentNetMap;
    vmCvar_t oldCampaign=ui_currentCampaign,oldNetCampaign=ui_currentNetCampaign;
    char longWord[4097]; int errors=0,align,mode,i;
    saved=uiInfo; memset(&context,0,sizeof(context));
    context.textWidth=DescriptionWidth; context.textHeight=DescriptionHeight; context.drawText=DescriptionPaint; DC=&context;
    for(align=ITEM_ALIGN_LEFT;align<=ITEM_ALIGN_RIGHT;++align) for(mode=0;mode<3;++mode) {
        const char *text=mode==0 ? "alpha\nbeta" : mode==1 ? "alpha*beta" : "alpha**beta";
        descriptionCount=0;
        UI_DrawDescriptionText(&rect,1,color,40,3,0,align,text,mode);
        if(descriptionCount!=2 || strcmp(descriptionLines[0],"alpha") || strcmp(descriptionLines[1],"beta") ||
           descriptionY[0]!=23 || descriptionY[1]!=40 ||
           descriptionX[0]!=(align==ITEM_ALIGN_RIGHT ? 10 : align==ITEM_ALIGN_CENTER ? 30 : 50)) ++errors;
    }
    descriptionCount=0;
    UI_DrawDescriptionText(&rect,1,color,0,0,0,0,"one two three four",0);
    if(descriptionCount!=2 || strcmp(descriptionLines[0],"one two three") || strcmp(descriptionLines[1],"four")) ++errors;
    memset(longWord,'x',sizeof(longWord)-1); longWord[sizeof(longWord)-1]=0;
    descriptionCount=0;
    UI_DrawDescriptionText(&rect,1,color,0,0,0,0,longWord,0);
    if(descriptionCount!=5) ++errors;
    for(i=0;i<descriptionCount;++i) if(strlen(descriptionLines[i])!=(i<4 ? 1023 : 4)) ++errors;
    memset(&uiInfo,0,sizeof(uiInfo)); rect.w=1000;
    ui_netGameType.integer=GT_WOLF; ui_currentMap.integer=ui_currentNetMap.integer=0;
    uiInfo.mapCount=1; uiInfo.mapList[0].briefing="Map"; uiInfo.mapList[0].lmsbriefing="LMS";
    uiInfo.campaignCount=1; uiInfo.campaignList[0].campaignDescription="Campaign";
    for(mode=0;mode<3;++mode) {
        ui_netGameType.integer=mode==0 ? GT_WOLF : mode==1 ? GT_WOLF_LMS : GT_WOLF_CAMPAIGN;
        descriptionCount=0; UI_DrawCampaignDescription(&rect,1,color,0,99,0,0,qtrue);
        if(descriptionCount!=1 || strcmp(descriptionLines[0],mode==0 ? "Map" : mode==1 ? "LMS" : "Campaign") || descriptionY[0]!=20) ++errors;
    }
    ui_currentNetMap.integer=1; descriptionCount=0;
    UI_DrawCampaignDescription(&rect,1,color,0,0,0,0,qtrue);
    if(descriptionCount!=1 || strcmp(descriptionLines[0],"^1No text supplied")) ++errors;
    uiInfo.numGameTypes=1; uiInfo.gameTypes[0].gtEnum=ui_netGameType.integer;
    uiInfo.gameTypes[0].gameTypeDescription="Type**Details"; descriptionCount=0;
    UI_DrawGametypeDescription(&rect,1,color,0,99,0,0,qtrue);
    if(descriptionCount!=2 || strcmp(descriptionLines[0],"Type") || strcmp(descriptionLines[1],"Details")) ++errors;
    ui_currentCampaign.integer=ui_currentNetCampaign.integer=0;
    uiInfo.campaignList[0].unlocked=qtrue; uiInfo.campaignList[0].progress=0;
    uiInfo.campaignList[0].mapCount=1; uiInfo.campaignList[0].mapInfos[0]=&uiInfo.mapList[0];
    for(i=-1;i<=MAX_MAPS_PER_CAMPAIGN;++i) {
        descriptionCount=0; UI_DrawCampaignMapDescription(&rect,1,color,0,7,0,0,qfalse,i);
        if(descriptionCount!=1 || strcmp(descriptionLines[0],i==0 ? "Map" : "No information is available for this region.") || descriptionY[0]!=27) ++errors;
    }
    uiInfo=saved; DC=old; ui_netGameType=oldGame; ui_currentMap=oldMap; ui_currentNetMap=oldNet;
    ui_currentCampaign=oldCampaign; ui_currentNetCampaign=oldNetCampaign;
    return errors;
}
