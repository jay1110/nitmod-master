/* Reuse established full-product tests with explicit per-group results.
 * The native variadic engine doubles are a fixture boundary, not browser ABI. */
#define main existing_full_ui_matrix
#include "test_nitmod_ui_bitflag.c"
#undef main
int main(void) {
    displayContextDef_t dc;
    int errors=0, result;
    memset(&dc,0,sizeof(dc));
    dc.getCVarString=GetString; dc.getCVarValue=GetValue;
    dc.setCVar=SetValue; dc.drawHandlePic=Draw; dc.stopCinematic=StopCinematic;
    Init_Display(&dc); String_Init();
#ifdef NITMOD_ACCEPT_BROWSER
    result=CheckBrowser(); printf("UI browser group: %s\n",result ? "FAIL" : "PASS");
    return result != 0;
#endif
#ifdef NITMOD_ACCEPT_SEARCH
    result=CheckPlayerSearch(); printf("UI player-search group: %s\n",result ? "FAIL" : "PASS");
    return result != 0;
#endif
    {
        itemDef_t item, target;
        menuDef_t menu;
        int initial, mask, bitErrors=0, visibilityErrors=0;
        memset(&item,0,sizeof(item)); memset(&target,0,sizeof(target)); memset(&menu,0,sizeof(menu));
        item.parent=&menu; item.cvar="flags"; item.type=ITEM_TYPE_CHECKBOX;
        item.window.flags=WINDOW_HASFOCUS; item.window.rect.w=item.window.rect.h=10;
        dc.cursorx=dc.cursory=5; dc.Assets.checkboxCheck=1; dc.Assets.checkboxCheckNot=2;
        for(initial=0;initial<32;++initial) for(mask=1;mask<=16;mask<<=1) {
            char command[64], *args=command; qboolean abort=qfalse;
            value=initial; writes=0; item.bitflag=mask;
            Item_CheckBox_Paint(&item);
            if(drawn!=((initial&mask)?1:2)) ++bitErrors;
            if(!Item_CheckBox_HandleKey(&item,K_MOUSE1)||writes||value!=initial) ++bitErrors;
            Com_sprintf(command,sizeof(command),"flags %d",mask);
            Script_ToggleCvarBit(&item,&abort,&args);
            if(value!=(initial^mask)||writes!=1||abort) ++bitErrors;
        }
        item.bitflag=0; value=3; writes=0;
        if(!Item_CheckBox_HandleKey(&item,K_MOUSE1)||value||writes!=1) ++bitErrors;
        menu.itemCount=1; menu.items[0]=&target; target.parent=&menu;
        target.window.name="filtericonNxAC"; target.window.group="nxac";
        target.window.cinematic=-1;
        for(value=-1;value<=1;++value) {
            Item_RunScript(&item,NULL,"condhideshow filtericonNxAC ;");
            if(!!(target.window.flags&WINDOW_VISIBLE)!=!!value) ++visibilityErrors;
        }
        value=0; stopped=0; target.window.cinematic=42;
        Item_RunScript(&item,NULL,"condhideshow nxac ;");
        if(stopped!=1||target.window.cinematic!=-1||(target.window.flags&WINDOW_VISIBLE)) ++visibilityErrors;
        printf("UI bitflag group: %s\n",bitErrors?"FAIL":"PASS");
        printf("UI conditional visibility group: %s\n",visibilityErrors?"FAIL":"PASS");
        errors+=bitErrors+visibilityErrors;
    }
    result=CheckServerStatus(); printf("UI server-status group: %s\n",result ? "FAIL" : "PASS"); errors+=result;
    result=CheckSystemSettings(); printf("UI system-settings group: %s\n",result ? "FAIL" : "PASS"); errors+=result;
    result=CheckProfileSettings(); printf("UI profile-settings group: %s\n",result ? "FAIL" : "PASS"); errors+=result;
    return errors != 0;
}
