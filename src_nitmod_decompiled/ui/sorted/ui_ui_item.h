#ifndef ET_UI_UI_ITEM_H
#define ET_UI_UI_ITEM_H

/**
 * @file ui_ui_item.h
 * @brief ui_item
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 * Original decompilation: Ghidra
 */

#include "ui_types.h"
#include "ui_globals.h"

void Item_Action(int param_1);
uint32_t Item_Bind_HandleKey(float *param_1,uint param_2,int param_3);
void Item_Bind_Paint(int param_1);
uint32_t Item_CheckBox_HandleKey(float *param_1,int param_2);
void Item_CheckBox_Paint(float *param_1);
uint32_t * Item_CorrectedTextRect(int param_1);
bool Item_EnableShowViaCvar(int param_1,uint param_2);
uint32_t Item_HandleKey(float *param_1,uint param_2,int param_3);
void Item_Image_Paint(float *param_1);
void Item_Init(uint16_t *param_1);
void Item_InitControls(int param_1);
uint32_t Item_ListBox_HandleKey(float *param_1,uint param_2,uint32_t param_3,int param_4);
int Item_ListBox_MaxScroll(int param_1);
void Item_ListBox_MouseEnter(float *param_1,float param_2,float param_3,int param_4);
uint32_t Item_ListBox_OverLB(float *param_1,float param_2,float param_3);
void Item_ListBox_Paint(float *param_1);
int Item_ListBox_ThumbDrawPosition(float *param_1);
int Item_ListBox_ThumbPosition(float *param_1);
void Item_Model_Paint(float *param_1);
void Item_MouseEnter(int param_1,float param_2,float param_3);
void Item_MouseLeave(int param_1);
uint32_t Item_Multi_CountSettings(int param_1);
int Item_Multi_FindCvarByValue(int param_1);
uint32_t Item_Multi_HandleKey(float *param_1,int param_2);
void Item_Multi_Paint(int param_1);
char * Item_Multi_Setting(int param_1);
uint32_t Item_OwnerDraw_HandleKey(int param_1,uint32_t param_2);
void Item_OwnerDraw_Paint(uint32_t *param_1);
void Item_Paint(float *param_1);
int Item_Parse(uint32_t param_1,uint32_t param_2);
void Item_RunScript(int param_1,int *param_2,char *param_3);
void Item_RunScript_constprop_37(int param_1,char *param_2);
uint32_t Item_SetFocus(int param_1,float param_2,float param_3);
void Item_SetMouseOver(int param_1,int param_2);
void Item_SetScreenCoords(float *param_1,float param_2,float param_3);
void Item_SetTextExtents(float *param_1,int *param_2,int *param_3,float param_4);
uint Item_SettingShow(int param_1,int param_2);
uint Item_SettingShow_constprop_35(int param_1);
bool Item_SettingShow_constprop_36(int param_1);
void Item_SetupKeywordHash(void);
uint32_t Item_Slider_HandleKey(float *param_1,int param_2);
uint32_t Item_Slider_OverSlider(float *param_1,float param_2,float param_3);
void Item_Slider_Paint(float *param_1);
long double Item_Slider_ThumbPosition(float *param_1);
void Item_StartCapture(float *param_1,uint32_t param_2);
void Item_StopCapture(void);
void Item_TextColor(int param_1,float *param_2);
bool Item_TextField_HandleKey(int param_1,uint param_2);
void Item_TextField_Paint(float *param_1);
void Item_Text_AutoWrapped_Paint(float *param_1);
void Item_Text_Paint(float *param_1);
void Item_Text_Wrapped_Paint(int param_1);
void Item_UpdatePosition(float *param_1);
uint32_t Item_ValidateTooltipData(int param_1);
uint32_t Item_ValidateTooltipData_part_24(int param_1);
void Item_ValidateTypeData(int param_1);
void Item_ValidateTypeData_part_21(int param_1);
uint32_t Item_YesNo_HandleKey(float *param_1,int param_2);
void Item_YesNo_Paint(int param_1);

#endif /* ET_UI_UI_ITEM_H */
