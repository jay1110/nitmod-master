#ifndef ET_UI_UI_MENU_H
#define ET_UI_UI_MENU_H

/* Menu definitions, menu item handling, menu events
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"

void UI_RunMenuScript(void) {;
void _UI_SetActiveMenu(uint32_t param_1) {;
bool MenuParse_background(int param_1,uint32_t param_2) {;
uint32_t MenuParse_backcolor(int param_1,uint32_t param_2) {;
uint32_t MenuParse_forecolor(int param_1,uint32_t param_2) {;
uint32_t MenuParse_bordercolor(int param_1,uint32_t param_2) {;
uint32_t MenuParse_focuscolor(int param_1,uint32_t param_2) {;
uint32_t MenuParse_disablecolor(int param_1,uint32_t param_2) {;
uint32_t MenuParse_visible(int param_1,uint32_t param_2) {;
bool MenuParse_name(int param_1,uint32_t param_2) {;
bool MenuParse_rect(int param_1,uint32_t param_2) {;
bool ItemParse_contextMenu(int param_1,uint32_t param_2) {;
void Script_CloseAllOtherMenus(int param_1) {;
void Script_FadeOutMenu(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_FadeInMenu(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
bool MenuParse_onTimeout(int param_1,uint32_t param_2) {;
bool MenuParse_execKey(int param_1,uint32_t param_2) {;
bool MenuParse_execKeyInt(int param_1,uint32_t param_2) {;
void Menu_UpdatePosition(float *param_1) {;
void Menu_PostParse(uint32_t *param_1) {;
int Menu_ClearFocus(int param_1) {;
void Script_SetMenuFocus(int param_1,uint32_t param_2,uint32_t param_3) {;
int Menu_ItemsMatchingGroup(int param_1,char *param_2) {;
uint32_t Menu_GetMatchingItemByNumber(int param_1,int param_2,char *param_3) {;
void Script_SetMenuItemColor(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
uint32_t Menu_FindItemByName(int param_1,int param_2) {;
void Menu_ShowItemByName(uint32_t param_1,uint32_t param_2,int param_3) {;
void Menu_FadeItemByName(uint32_t param_1,uint32_t param_2,int param_3) {;
uint32_t * Menus_FindByName(uint32_t param_1) {;
void Menus_CloseAll(void) {;
void Menu_FadeMenuByName(uint32_t param_1,uint32_t param_2,int param_3) {;
float * Menu_HitTest(int param_1,float param_2,float param_3) {;
void Menus_Activate(int param_1) {;
void Menus_ShowByName(uint32_t param_1) {;
int Display_VisibleMenuCount(void) {;
void Menu_Paint_part_20(uint32_t *param_1,int param_2) {;
void Menu_Init(uint32_t *param_1) {;
int Menu_GetFocusedItem(int param_1) {;
uint32_t * Menu_GetFocused(void) {;
void Menu_SetFeederSelection(uint32_t *param_1,int param_2,int param_3,int param_4) {;
uint32_t Menus_AnyFullScreenVisible(void) {;
uint32_t * Menus_ActivateByName(uint32_t param_1,int param_2) {;
void Menus_CloseByName(uint32_t param_1) {;
void Menu_ScrollFeeder(int param_1,int param_2,int param_3) {;
void Menu_HandleMouseMove(int param_1,float param_2,float param_3) {;
uint32_t Menu_SetPrevCursorItem(int param_1) {;
uint32_t Menu_SetNextCursorItem(int param_1) {;
void Menu_HandleKey(int param_1,int param_2,int param_3) {;
void Menus_HandleOOBClick(int param_1,uint32_t param_2,int param_3) {;
void Menu_Paint(int param_1,int param_2) {;
uint32_t MenuParse_itemDef(int param_1,uint32_t param_2) {;
void Menu_SetupKeywordHash(void) {;
int Menu_Parse(uint32_t param_1,uint32_t param_2) {;

#endif /* ET_UI_UI_MENU_H */
