static int CheckScopeView(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    static snapshot_t snap;
    vmCvar_t savedLetterbox = cg_letterbox;
    const int sizes[][2] = {{640,480},{1280,720},{1919,1079},{3440,1440}};
    const int flags[] = {0, EF_MG42_ACTIVE, EF_AAGUN_ACTIVE, EF_MOUNTEDTANK};
    const int spreads[] = {0,1,64,128,255};
    const float percentages[] = {20,85,100};
    const char *protocols[] = {"\\gamename\\nitmod", "\\gamename\\etmain", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    int errors=0, protocol, weapon, flag, zoom, spread, tick, size, percent, center, letter;
    savedCg=cg; savedCgs=cgs; memset(&snap,0,sizeof(snap)); cg.snap=&snap;
    for(protocol=0;protocol<3;++protocol) {
        memset(&cgs.gameState,0,sizeof(cgs.gameState)); cgs.gameState.dataCount=1;
        SetTestConfig(CS_SERVERINFO,protocols[protocol]);
        for(weapon=0;weapon<2;++weapon) for(flag=0;flag<4;++flag)
        for(zoom=0;zoom<3;++zoom) for(spread=0;spread<5;++spread) for(tick=0;tick<41;++tick) {
            float pitch=3, yaw=17;
            int allowed = zoom && !(flags[flag] & (protocol ? EF_MG42_ACTIVE|EF_AAGUN_ACTIVE : EF_MG42_ACTIVE));
            cg.time=tick*125; cg.zoomval=zoom*10.f;
            snap.ps.weapon=weapon ? WP_FG42SCOPE : WP_GARAND_SCOPE;
            snap.ps.eFlags=flags[flag]; snap.ps.aimSpreadScale=spreads[spread];
            VectorSet(cg.refdefViewAngles,3,17,-2);
            if(allowed) {
                float s=spreads[spread]/255.f;
                pitch += (float)(sin(cg.time/1000.0*.24*M_PI*2)*.13*(s+(!protocol && weapon ? .4 : .1)));
                yaw += (float)(sin(cg.time/1000.0*.12*M_PI*2)*.7*(s+(!protocol && weapon ? .8 : .2)));
            }
            CG_ZoomSway();
            if(fabs(cg.refdefViewAngles[0]-pitch)>.0001 || fabs(cg.refdefViewAngles[1]-yaw)>.0001 || cg.refdefViewAngles[2]!=-2) ++errors;
        }
        for(size=0;size<4;++size) for(percent=0;percent<3;++percent)
        for(center=0;center<2;++center) for(letter=0;letter<2;++letter) {
            float scale=percentages[percent], yscale=scale;
            int x=13,y=27,w,h;
            cgs.glconfig.vidWidth=sizes[size][0]; cgs.glconfig.vidHeight=sizes[size][1];
            cg_letterbox.integer=letter; cg.refdef.x=x; cg.refdef.y=y;
            if(protocol && letter) {
                float lb=yscale*.85f;
                if(!center) y += (int)(sizes[size][1]*(.5f*(yscale-lb))/100)&~1;
                yscale=lb;
            }
            w=(int)(sizes[size][0]*scale/100)&~1; h=(int)(sizes[size][1]*yscale/100)&~1;
            if(center) { x=(sizes[size][0]-w)/2; y=(sizes[size][1]-h)/2; }
            CG_Letterbox(scale,scale,center);
            if(cg.refdef.width!=w || cg.refdef.height!=h || cg.refdef.x!=x || cg.refdef.y!=y) ++errors;
        }
    }
    {
        refdef_t view, before;
        memset(&view,0,sizeof(view)); view.x=19; view.width=91; before=view;
        CG_NitmodLetterbox(&view,-1,720,100,100,qtrue);
        if(memcmp(&view,&before,sizeof(view))) ++errors;
        CG_NitmodLetterbox(&view,1280,720,HUGE_VAL,100,qtrue);
        if(memcmp(&view,&before,sizeof(view))) ++errors;
        CG_NitmodLetterbox(&view,1280,720,-1,100,qtrue);
        if(memcmp(&view,&before,sizeof(view))) ++errors;
    }
    cg=savedCg; cgs=savedCgs; cg_letterbox=savedLetterbox;
    if(errors) fprintf(stderr,"%d scope/view rectangle failures\n",errors);
    return errors;
}
