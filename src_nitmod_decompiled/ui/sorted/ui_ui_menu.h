#ifndef ET_UI_UI_MENU_H
#define ET_UI_UI_MENU_H

/**
 * @file ui_ui_menu.h
 * @brief ui_menu
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 * Original decompilation: Ghidra
 */

#include "ui_types.h"
#include "ui_globals.h"

int Menu_ClearFocus(int param_1);
void Menu_FadeItemByName(uint32_t param_1,uint32_t param_2,int param_3);
void Menu_FadeMenuByName(uint32_t param_1,uint32_t param_2,int param_3);
uint32_t Menu_FindItemByName(int param_1,int param_2);
uint32_t * Menu_GetFocused(void);
int Menu_GetFocusedItem(int param_1);
uint32_t Menu_GetMatchingItemByNumber(int param_1,int param_2,char *param_3);
void Menu_HandleKey(int param_1,int param_2,int param_3);
void Menu_HandleMouseMove(int param_1,float param_2,float param_3);
float * Menu_HitTest(int param_1,float param_2,float param_3);
void Menu_Init(uint32_t *param_1);
int Menu_ItemsMatchingGroup(int param_1,char *param_2);
void Menu_OrbitItemByName (uint32_t param_1,uint32_t param_2,float param_3,float param_4,float param_5, float param_6,float param_7);
void Menu_Paint(int param_1,int param_2);
void Menu_Paint_part_20(uint32_t *param_1,int param_2);
int Menu_Parse(uint32_t param_1,uint32_t param_2);
void Menu_PostParse(uint32_t *param_1);
void Menu_RunCloseScript_part_10(int param_1);
void Menu_ScrollFeeder(int param_1,int param_2,int param_3);
void Menu_SetFeederSelection(uint32_t *param_1,int param_2,int param_3,int param_4);
uint32_t Menu_SetNextCursorItem(int param_1);
uint32_t Menu_SetPrevCursorItem(int param_1);
void Menu_SetupKeywordHash(void);
void Menu_ShowItemByName(uint32_t param_1,uint32_t param_2,int param_3);
void Menu_TransitionItemByName (uint32_t param_1,uint32_t param_2,float param_3,float param_4,float param_5, float param_6,float param_7,float param_8,float param_9,float param_10, uint32_t param_11,float param_12);
void Menu_UpdatePosition(float *param_1);

#endif /* ET_UI_UI_MENU_H */
