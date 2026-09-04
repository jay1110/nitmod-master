#include "ui_local.h"
extern displayContextDef_t *DC;

/* Shared original description layout: explicit breaks, last-word wrapping,
 * alignment and five-pixel leading. Bound long words before writing, and
 * always consume input even when a word cannot fit the requested width. */
void UI_DrawDescriptionText(const rectDef_t *rect, float scale, vec4_t color,
    float textX, float textY, int style, int align, const char *text, int stars) {
    const char *p, *restart;
    char line[1024];
    int length, split, skip, width, splitWidth, height, end;
    float x, y;
    if(!rect || !text || !DC || !DC->textWidth || !DC->textHeight || !DC->drawText ||
       !(rect->w > 0) || !(scale > 0)) return;
    height=DC->textHeight(text,scale,0); y=textY; p=text;
    while(*p) {
        length=split=splitWidth=0; restart=NULL; line[0]=0;
        for(;;) {
            width=DC->textWidth(line,scale,0);
            skip=*p=='\n' ? 1 : stars==1 && *p=='*' ? 1 :
                stars==2 && *p=='*' && p[1]=='*' ? 2 : 0;
            end=*p==0;
            if(*p==' ' || *p=='\t' || skip || end) {
                split=length; splitWidth=width; restart=p+(end ? 0 : skip ? skip : 1);
            }
            if((split && width>rect->w) || skip || end || length==(int)sizeof(line)-1) {
                if(!split && length && !skip && !end) {
                    split=length; splitWidth=width; restart=p;
                }
                if(length) {
                    line[split]=0;
                    x=textX;
                    if(align==ITEM_ALIGN_RIGHT) x-=splitWidth;
                    else if(align==ITEM_ALIGN_CENTER) x-=splitWidth*.5f;
                    DC->drawText(rect->x+x,rect->y+y,scale,color,line,0,0,style);
                }
                if(end) return;
                p=restart; y+=height+5;
                break;
            }
            line[length++]=*p=='\r' ? ' ' : *p;
            ++p; line[length]=0;
        }
    }
}

void UI_DrawCampaignDescription(rectDef_t *rect, float scale, vec4_t color,
    float textX, float textY, int style, int align, qboolean net) {
    const char *text=NULL;
    int index=net ? ui_currentNetMap.integer : ui_currentMap.integer;
    if(ui_netGameType.integer==GT_WOLF_CAMPAIGN) {
        if(uiInfo.campaignCount>=0 && uiInfo.campaignCount<=MAX_CAMPAIGNS &&
           index>=0 && index<uiInfo.campaignCount) text=uiInfo.campaignList[index].campaignDescription;
    } else if(uiInfo.mapCount>=0 && uiInfo.mapCount<=MAX_MAPS && index>=0 && index<uiInfo.mapCount) {
        text=ui_netGameType.integer==GT_WOLF_LMS ? uiInfo.mapList[index].lmsbriefing : uiInfo.mapList[index].briefing;
    }
    if(!text || !*text) text="^1No text supplied";
    /* Original campaign and gametype panels start at rect.y, ignoring textY. */
    UI_DrawDescriptionText(rect,scale,color,textX,0,style,align,text,1);
}

void UI_DrawGametypeDescription(rectDef_t *rect, float scale, vec4_t color,
    float textX, float textY, int style, int align, qboolean net) {
    int i;
    const char *text="Unknown";
    if(uiInfo.numGameTypes>=0 && uiInfo.numGameTypes<=MAX_GAMETYPES)
        for(i=0;i<uiInfo.numGameTypes;++i) if(uiInfo.gameTypes[i].gtEnum==ui_netGameType.integer) {
            text=uiInfo.gameTypes[i].gameTypeDescription; break;
        }
    UI_DrawDescriptionText(rect,scale,color,textX,0,style,align,text,2);
}

void UI_DrawCampaignMapDescription(rectDef_t *rect, float scale, vec4_t color,
    float textX, float textY, int style, int align, qboolean net, int number) {
    const char *text="No information is available for this region.";
    int index=net ? ui_currentNetCampaign.integer : ui_currentCampaign.integer;
    if(uiInfo.campaignCount>=0 && uiInfo.campaignCount<=MAX_CAMPAIGNS &&
       index>=0 && index<uiInfo.campaignCount && number>=0 && number<MAX_MAPS_PER_CAMPAIGN) {
        const campaignInfo_t *campaign=&uiInfo.campaignList[index];
        if(campaign->unlocked && campaign->progress>=number && number<campaign->mapCount && campaign->mapInfos[number]) {
            text=campaign->mapInfos[number]->briefing;
            if(!text || !*text) text="^1No text supplied";
        }
    }
    UI_DrawDescriptionText(rect,scale,color,textX,textY,style,align,text,0);
}
