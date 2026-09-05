extern void Item_SetScreenCoords(itemDef_t *, float, float);
static int CheckTooltipLayout(displayContextDef_t *dc) {
    const int sizes[][2]={{640,480},{1920,1080},{3440,1440}};
    const float origins[][2]={{0,0},{600,450},{-200,-100},{100,100}};
    glconfig_t old=dc->glconfig;
    itemDef_t item,tip;
    int size,origin,repeat,errors=0;
    memset(&item,0,sizeof(item)); memset(&tip,0,sizeof(tip));
    item.toolTipData=&tip;
    tip.window.rectClient.x=30; tip.window.rectClient.y=20;
    tip.window.rectClient.w=120; tip.window.rectClient.h=40;
    Init_Display(dc);
    for(size=0;size<3;++size) {
        float right;
        dc->glconfig.vidWidth=sizes[size][0]; dc->glconfig.vidHeight=sizes[size][1];
        right=UI_NitmodWideWidth(dc)-5;
        for(repeat=0;repeat<10;++repeat) for(origin=0;origin<4;++origin) {
            float x=origins[origin][0]+30, y=origins[origin][1]+20;
            if(x+120>right) x=right-120;
            if(x<5) x=5;
            if(y+40>475) y=435;
            if(y<5) y=5;
            Item_SetScreenCoords(&item,origins[origin][0],origins[origin][1]);
            if(fabs(tip.window.rect.x-x)>.001 || fabs(tip.window.rect.y-y)>.001 ||
               tip.window.rectClient.x!=30 || tip.window.rectClient.y!=20 ||
               tip.window.rect.w!=120 || tip.window.rect.h!=40) ++errors;
        }
    }
    dc->glconfig=old;
    if(errors) fprintf(stderr,"tooltip layout: %d errors\n",errors);
    return errors;
}
