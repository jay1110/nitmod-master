#ifndef ET_UI_UI_COLOR_H
#define ET_UI_UI_COLOR_H

/**
 * @file ui_ui_color.h
 * @brief ui_color
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 * Original decompilation: Ghidra
 */

#include "ui_types.h"
#include "ui_globals.h"

uint32_t ColorBytes3(float param_1,float param_2,float param_3);
uint32_t ColorBytes4(float param_1,float param_2,float param_3,float param_4);
uint32_t Color_Parse(uint32_t param_1,int param_2);
uint32_t ItemParse_addColorRange(int param_1,uint32_t param_2);
uint32_t ItemParse_addColorRangeRel(int param_1,uint32_t param_2);
uint32_t ItemParse_backcolor(int param_1,uint32_t param_2);
uint32_t ItemParse_bordercolor(int param_1,uint32_t param_2);
uint32_t ItemParse_forecolor(int param_1,uint32_t param_2);
bool ItemParse_outlinecolor(int param_1,uint32_t param_2);
void LerpColor(float *param_1,float *param_2,float *param_3,float param_4);
uint32_t MenuParse_backcolor(int param_1,uint32_t param_2);
uint32_t MenuParse_bordercolor(int param_1,uint32_t param_2);
uint32_t MenuParse_disablecolor(int param_1,uint32_t param_2);
uint32_t MenuParse_focuscolor(int param_1,uint32_t param_2);
uint32_t MenuParse_forecolor(int param_1,uint32_t param_2);
bool MenuParse_outlinecolor(int param_1,uint32_t param_2);
void NormalizeColor(float *param_1,float *param_2);
uint32_t ParseColorRange(int param_1,uint32_t param_2,int param_3);
void Script_SetColor(int param_1,uint32_t param_2,uint32_t param_3);
void Script_SetItemColor(int param_1,uint32_t param_2,uint32_t param_3);
void Script_SetMenuItemColor(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void Script_SetTeamColor(int param_1);
void UI_SetColor(uint32_t param_1);

#endif /* ET_UI_UI_COLOR_H */
