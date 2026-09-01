#ifndef ET_UI_UI_DRAW_H
#define ET_UI_UI_DRAW_H

/**
 * @file ui_ui_draw.h
 * @brief ui_draw
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 * Original decompilation: Ghidra
 */

#include "ui_types.h"
#include "ui_globals.h"

void GradientBar_Paint(uint32_t *param_1,uint32_t param_2);
uint32_t ItemParse_maxPaintChars(int param_1,uint32_t param_2);
bool ItemParse_ownerdraw(int param_1,uint32_t param_2);
bool ItemParse_ownerdrawFlag(int param_1,uint32_t param_2);
uint32_t MenuParse_drawAlwaysOnTop(int param_1);
bool MenuParse_ownerdraw(int param_1,uint32_t param_2);
bool MenuParse_ownerdrawFlag(int param_1,uint32_t param_2);
void Text_PaintCenter(float param_1,uint32_t param_2,float param_3,uint32_t param_4, byte *param_5);
void UI_DrawCampaignDescription (float *param_1,float param_2,uint32_t param_3,float param_4,uint32_t param_5, uint32_t param_6,int param_7,int param_8);
void UI_DrawConnectScreen(int param_1);
void UI_DrawGametypeDescription (float *param_1,float param_2,uint32_t param_3,float param_4,uint32_t param_5, uint32_t param_6,int param_7);
void UI_DrawHandlePic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5);
void UI_DrawMapCinematic(float *param_1,uint32_t param_2,uint32_t param_3,int param_4);
void UI_DrawMapPreview(float *param_1,float param_2,uint32_t param_3,int param_4);
void UI_DrawNamedPic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5);
void UI_DrawNetMapPreview(uint32_t *param_1);
void UI_DrawRect(float param_1,float param_2,float param_3,float param_4,uint32_t param_5);
void UI_DrawRotatedPic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5, uint32_t param_6);
void UI_DrawSides(float param_1,float param_2,float param_3,float param_4);
void UI_DrawTextBox(int param_1,int param_2,int param_3,int param_4);
void UI_DrawTopBottom(float param_1,float param_2,float param_3,float param_4);
void UI_OwnerDraw(float param_1,float param_2,float param_3,float param_4,float param_5, float param_6,int param_7,uint32_t param_8,uint32_t param_9,uint32_t param_10 ,float param_11,float *param_12,uint32_t param_13,uint32_t param_14);
void Window_Paint(float *param_1,float param_2,float param_3,float param_4);

#endif /* ET_UI_UI_DRAW_H */
