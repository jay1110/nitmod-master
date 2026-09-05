extern void Menu_UpdatePosition(menuDef_t *);
extern void Item_UpdatePosition(itemDef_t *);
extern void _UI_MouseEvent(int, int);
extern qboolean Rect_ContainsPoint(rectDef_t *, float, float);
extern panel_button_t *loadpanelButtons[];
extern qboolean bg_loadscreeninited;
static float wideDraw[4], widePanelOffset;
static int widePanelDraws, widePanelErrors;
static float widePanelX[16];
static int QDECL WideSyscall(int command, ...) {
    va_list args;
    int i;
    va_start(args, command);
    if(command == UI_R_DRAWSTRETCHPIC) {
        for(i = 0; i < 4; ++i) { union { int bits; float value; } f; f.bits = va_arg(args, int); wideDraw[i] = f.value; }
    } else if(command != UI_R_SETCOLOR && command != UI_CVAR_VARIABLEVALUE) {
        fprintf(stderr, "Unexpected wide UI syscall %d\n", command); exit(2);
    }
    va_end(args); return 0;
}
static void WidePanelDraw(panel_button_t *button) {
    int i;
    for(i = 0; loadpanelButtons[i] != button && loadpanelButtons[i]; ++i) {}
    if(i >= 16 || !loadpanelButtons[i] || fabs(button->rect.x - widePanelX[i] - widePanelOffset) > .001f)
        ++widePanelErrors;
    ++widePanelDraws;
}
static float wideMode;
static float WideCvar(const char *name) { return !strcmp(name, "r_mode") ? wideMode : 0; }
static int CheckWideUI(void) {
    static const int dimensions[][2] = {{640,480},{1280,1024},{1280,720},{1920,1080},{3440,1440},{3840,2160},{0,0}};
    displayContextDef_t *previous = Display_GetContext(), saved = uiInfo.uiDC, dc;
    menuDef_t menu;
    itemDef_t item, background, clouds;
    rectDef_t original;
    float width, offset, sx, x, y, w, h;
    int d, frame, i, oldCount = menuCount, errors = 0;
    qboolean savedInited = bg_loadscreeninited;
    void (*savedDraw[16])(panel_button_t *);
    dllEntry(WideSyscall);
    for(i = 0; loadpanelButtons[i]; ++i) {
        if(i >= 16) exit(2);
        savedDraw[i] = loadpanelButtons[i]->onDraw;
        widePanelX[i] = loadpanelButtons[i]->rect.x;
        loadpanelButtons[i]->onDraw = WidePanelDraw;
    }
    bg_loadscreeninited = qtrue;
    for(d = 0; d < 7; ++d) {
        memset(&dc, 0, sizeof(dc));
        dc.glconfig.vidWidth = dimensions[d][0]; dc.glconfig.vidHeight = dimensions[d][1];
        dc.xscale = dimensions[d][0] ? dimensions[d][0] / 640.f : 1;
        dc.yscale = dimensions[d][1] ? dimensions[d][1] / 480.f : 1;
        dc.getCVarValue = WideCvar; wideMode = 0;
        Init_Display(&dc); uiInfo.uiDC = dc;
        width = dimensions[d][1] ? dimensions[d][0] * 480.f / dimensions[d][1] : 640;
        if(width < 640) width = 640;
        offset = (width - 640) * .5f; sx = dc.xscale * 640 / width;
        if(fabs(UI_NitmodWideWidth(&dc) - width) > .001f) ++errors;
        if(fabs(UI_NitmodWideX(&dc, 320.f) - width * .5f) > .001f ||
           fabs(UI_NitmodWideXOffset(&dc) - offset) > .001f) ++errors;
		{
			rectDef_t transformed = {20, 30, 100, 60};
			UI_NitmodWideRect(&dc, &transformed);
			if(fabs(transformed.x - 20*sx) > .001f ||
			   fabs(transformed.w - 100*sx) > .001f ||
			   fabs(transformed.y - 30*dc.yscale) > .001f ||
			   fabs(transformed.h - 60*dc.yscale) > .001f) ++errors;
		}
        x = 20; y = 30; w = 100; h = 60;
        UI_AdjustFrom640(&x, &y, &w, &h);
        if(fabs(x - 20*sx) > .001f || fabs(w - 100*sx) > .001f ||
           fabs(y - 30*dc.yscale) > .001f || fabs(h - 60*dc.yscale) > .001f) ++errors;
        UI_DrawHandlePic(20, 30, 100, 60, 42);
        if(fabs(wideDraw[0] - x) > .001f || fabs(wideDraw[1] - y) > .001f ||
           fabs(wideDraw[2] - w) > .001f || fabs(wideDraw[3] - h) > .001f) ++errors;
        widePanelOffset = offset; widePanelDraws = widePanelErrors = 0;
        for(frame = 0; frame < 3; ++frame) {
            UI_DrawLoadPanel(qfalse, qfalse, qtrue);
            for(i = 0; loadpanelButtons[i]; ++i)
                if(loadpanelButtons[i]->rect.x != widePanelX[i]) ++errors;
            if(wideDraw[2] != dimensions[d][0] || wideDraw[3] != dimensions[d][1]) ++errors;
        }
        if(widePanelErrors || widePanelDraws != i * 3) ++errors;
        memset(&menu, 0, sizeof(menu)); memset(&item, 0, sizeof(item));
        memset(&background, 0, sizeof(background)); memset(&clouds, 0, sizeof(clouds));
        menu.fullScreen = qtrue; menu.itemCount = 3;
        menu.items[0] = &item; menu.items[1] = &background; menu.items[2] = &clouds;
        item.parent = background.parent = clouds.parent = &menu;
        item.window.rectClient.x = 20; item.window.rectClient.y = 30;
        item.window.rectClient.w = 100; item.window.rectClient.h = 60;
        original = item.window.rectClient;
        background.window.rectClient.w = clouds.window.rectClient.w = 640;
        background.window.rectClient.h = clouds.window.rectClient.h = 480;
        clouds.window.name = "clouds";
        for(frame = 0; frame < 10; ++frame) {
            Menu_PostParse(&menu); Item_UpdatePosition(&item);
            if(fabs(item.window.rect.x - (20+offset)) > .001f || item.window.rect.y != 30 ||
               memcmp(&original, &item.window.rectClient, sizeof(original)) ||
               fabs(clouds.window.rect.w - width) > .001f || clouds.window.rect.x != 0 ||
               fabs(background.window.rect.w - 640*sx) > .001f ||
               background.window.rectClient.w != 640 || clouds.window.rectClient.w != 640) ++errors;
            if(!Rect_ContainsPoint(&item.window.rect, 21+offset, 31) ||
               Rect_ContainsPoint(&item.window.rect, 19+offset, 31) ||
               Rect_ContainsPoint(&item.window.rect, 121+offset, 31)) ++errors;
        }
        wideMode = 11; Menu_UpdatePosition(&menu);
        if(fabs(background.window.rect.w - 640*dc.xscale) > .001f) ++errors;
        menu.fullScreen = qfalse; menu.window.rect.x = 16; menu.window.rect.w = 608;
        for(frame = 0; frame < 10; ++frame) {
            Menu_UpdatePosition(&menu); Item_UpdatePosition(&item);
            if(fabs(menu.window.rect.x - (16+offset)) > .001f ||
               fabs(item.window.rect.x - (36+offset)) > .001f) ++errors;
        }
        menuCount = 0;
        uiInfo.uiDC.cursorx = uiInfo.uiDC.cursory = 0;
        _UI_MouseEvent(2147483647, 2147483647);
        if(uiInfo.uiDC.cursorx != (int)width || uiInfo.uiDC.cursory != 480) ++errors;
        _UI_MouseEvent(2147483647, 2147483647);
        if(uiInfo.uiDC.cursorx != (int)width || uiInfo.uiDC.cursory != 480) ++errors;
        _UI_MouseEvent(-2147483647, -2147483647);
        if(uiInfo.uiDC.cursorx || uiInfo.uiDC.cursory) ++errors;
    }
    for(i = 0; loadpanelButtons[i]; ++i) loadpanelButtons[i]->onDraw = savedDraw[i];
    bg_loadscreeninited = savedInited;
    uiInfo.uiDC = saved; menuCount = oldCount; Init_Display(previous);
    if(errors) fprintf(stderr, "wide UI errors: %d\n", errors);
    return errors;
}
