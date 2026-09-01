#ifndef ET_UI_UI_ITEM_H
#define ET_UI_UI_ITEM_H

/* Item definitions, item parsing, item configuration
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"

int * BG_FindItemForWeapon(int param_1) {;
int * BG_FindItem(uint32_t param_1) {;
int * BG_FindItemForClassName(uint32_t param_1) {;
bool BG_PlayerTouchesItem(int param_1,int param_2,int param_3) {;
uint BG_CanItemBeGrabbed(int param_1,int param_2,uint32_t param_3) {;
void WM_setItemPic(uint32_t param_1,uint32_t param_2) {;
bool ItemParse_focusSound(int param_1,uint32_t param_2) {;
bool ItemParse_asset_shader(int param_1,uint32_t param_2) {;
bool ItemParse_background(int param_1,uint32_t param_2) {;
uint32_t ItemParse_backcolor(int param_1,uint32_t param_2) {;
uint32_t ItemParse_forecolor(int param_1,uint32_t param_2) {;
uint32_t ItemParse_bordercolor(int param_1,uint32_t param_2) {;
uint32_t ItemParse_origin(int param_1,uint32_t param_2) {;
uint32_t ItemParse_visible(int param_1,uint32_t param_2) {;
uint32_t * Item_CorrectedTextRect(int param_1) {;
uint Item_SettingShow_constprop_35(int param_1) {;
bool Item_SettingShow_constprop_36(int param_1) {;
bool ItemParse_rect(int param_1,uint32_t param_2) {;
uint32_t Item_ValidateTooltipData_part_24(int param_1) {;
bool ItemParse_tooltip(int param_1,uint32_t param_2) {;
bool ItemParse_tooltipalignx(int param_1,uint32_t param_2) {;
bool ItemParse_tooltipaligny(int param_1,uint32_t param_2) {;
uint32_t ItemParse_addColorRangeRel(int param_1,uint32_t param_2) {;
uint32_t ItemParse_addColorRange(int param_1,uint32_t param_2) {;
void Item_ValidateTypeData_part_21(int param_1) {;
uint32_t ItemParse_asset_model(int param_1,uint32_t param_2) {;
bool ItemParse_model_origin(int param_1,uint32_t param_2) {;
bool ItemParse_model_fovx(int param_1,uint32_t param_2) {;
bool ItemParse_model_fovy(int param_1,uint32_t param_2) {;
bool ItemParse_model_rotation(int param_1,uint32_t param_2) {;
bool ItemParse_model_angle(int param_1,uint32_t param_2) {;
uint32_t ItemParse_model_animplay(int param_1,uint32_t param_2) {;
uint32_t ItemParse_notselectable(int param_1) {;
uint32_t ItemParse_type(int param_1,uint32_t param_2) {;
bool ItemParse_elementwidth(int param_1,uint32_t param_2) {;
bool ItemParse_elementheight(int param_1,uint32_t param_2) {;
bool ItemParse_elementtype(int param_1,uint32_t param_2) {;
uint32_t ItemParse_columns(int param_1,uint32_t param_2) {;
uint32_t ItemParse_cvar(int param_1,uint32_t param_2) {;
uint32_t ItemParse_maxChars(int param_1,uint32_t param_2) {;
uint32_t ItemParse_maxPaintChars(int param_1,uint32_t param_2) {;
bool ItemParse_cvarFloat(int param_1,uint32_t param_2) {;
bool ItemParse_textfile(int param_1,uint32_t param_2) {;
uint32_t ItemParse_cvarStrList(int param_1,uint32_t param_2) {;
uint32_t ItemParse_cvarFloatList(int param_1,uint32_t param_2) {;
uint32_t ItemParse_cvarListUndefined(int param_1,uint32_t param_2) {;
void Item_RunScript_constprop_37(int param_1,char *param_2) {;
bool ItemParse_execKey(int param_1,uint32_t param_2) {;
bool ItemParse_doubleClick(int param_1,uint32_t param_2) {;
void Item_SetScreenCoords(float *param_1,float param_2,float param_3) {;
void Item_UpdatePosition(float *param_1) {;
void Script_SetItemColor(int param_1,uint32_t param_2,uint32_t param_3) {;
void Item_RunScript(int param_1,int *param_2,char *param_3) {;
bool Item_EnableShowViaCvar(int param_1,uint param_2) {;
uint Item_SettingShow(int param_1,int param_2) {;
uint32_t Item_SetFocus(int param_1,float param_2,float param_3) {;
int Item_ListBox_MaxScroll(int param_1) {;
int Item_ListBox_ThumbPosition(float *param_1) {;
int Item_ListBox_ThumbDrawPosition(float *param_1) {;
long double Item_Slider_ThumbPosition(float *param_1) {;
uint32_t Item_Slider_OverSlider(float *param_1,float param_2,float param_3) {;
uint32_t Item_ListBox_OverLB(float *param_1,float param_2,float param_3) {;
void Item_ListBox_MouseEnter(float *param_1,float param_2,float param_3,int param_4) {;
void Item_MouseEnter(int param_1,float param_2,float param_3) {;
void Item_MouseLeave(int param_1) {;
uint32_t Item_CheckBox_HandleKey(float *param_1,int param_2) {;
uint32_t Item_YesNo_HandleKey(float *param_1,int param_2) {;
int Item_Multi_FindCvarByValue(int param_1) {;
char * Item_Multi_Setting(int param_1) {;
uint32_t Item_Multi_HandleKey(float *param_1,int param_2) {;
void Item_StartCapture(float *param_1,uint32_t param_2) {;
uint32_t Item_Slider_HandleKey(float *param_1,int param_2) {;
void Item_SetTextExtents(float *param_1,int *param_2,int *param_3,float param_4) {;
void Item_TextColor(int param_1,float *param_2) {;
void Item_Text_AutoWrapped_Paint(float *param_1) {;
void Item_Text_Wrapped_Paint(int param_1) {;
void Item_Text_Paint(float *param_1) {;
void Item_TextField_Paint(float *param_1) {;
void Item_CheckBox_Paint(float *param_1) {;
void Item_YesNo_Paint(int param_1) {;
void Item_Multi_Paint(int param_1) {;
void Item_Slider_Paint(float *param_1) {;
void Item_Bind_Paint(int param_1) {;
uint32_t Item_Bind_HandleKey(float *param_1,uint param_2,int param_3) {;
void Item_Model_Paint(float *param_1) {;
void Item_ListBox_Paint(float *param_1) {;
void Item_OwnerDraw_Paint(uint32_t *param_1) {;
void Item_Paint(float *param_1) {;
uint32_t Item_ListBox_HandleKey(float *param_1,uint param_2,uint32_t param_3,int param_4) {;
uint32_t Item_HandleKey(float *param_1,uint param_2,int param_3) {;
void Item_Init(uint16_t *param_1) {;
bool Item_TextField_HandleKey(int param_1,uint param_2) {;
void Item_SetupKeywordHash(void) {;
int Item_Parse(uint32_t param_1,uint32_t param_2) {;
void Item_InitControls(int param_1) {;

#endif /* ET_UI_UI_ITEM_H */
