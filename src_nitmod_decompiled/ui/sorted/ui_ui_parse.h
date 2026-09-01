#ifndef ET_UI_UI_PARSE_H
#define ET_UI_UI_PARSE_H

/**
 * @file ui_ui_parse.h
 * @brief ui_parse
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 * Original decompilation: Ghidra
 */

#include "ui_types.h"
#include "ui_globals.h"

void COM_BackupParseSession(uint32_t *param_1);
void COM_BeginParseSession(uint32_t param_1);
uint32_t COM_GetCurrentParseLine(void);
void COM_Parse(void);
void COM_ParseError(char *param_1);
uint8_t * COM_ParseExt(int *param_1,int param_2);
uint64_t COM_ParseExt_constprop_2(int *param_1);
uint64_t COM_ParseExt_nico(uint32_t *param_1,int param_2);
void COM_RestoreParseSession(uint32_t *param_1);
uint32_t Float_Parse(uint32_t param_1,float *param_2);
uint32_t Int_Parse(uint32_t param_1,long *param_2);
bool ItemParse_accept(int param_1,uint32_t param_2);
bool ItemParse_action(int param_1,uint32_t param_2);
bool ItemParse_align(int param_1,uint32_t param_2);
uint32_t ItemParse_asset_model(int param_1,uint32_t param_2);
bool ItemParse_asset_shader(int param_1,uint32_t param_2);
uint32_t ItemParse_autowrapped(int param_1);
bool ItemParse_background(int param_1,uint32_t param_2);
bool ItemParse_bitflag(int param_1,uint32_t param_2);
bool ItemParse_border(int param_1,uint32_t param_2);
bool ItemParse_bordersize(int param_1,uint32_t param_2);
bool ItemParse_cinematic(int param_1,uint32_t param_2);
uint32_t ItemParse_columns(int param_1,uint32_t param_2);
bool ItemParse_contextMenu(int param_1,uint32_t param_2);
uint32_t ItemParse_cvar(int param_1,uint32_t param_2);
bool ItemParse_cvarFloat(int param_1,uint32_t param_2);
uint32_t ItemParse_cvarFloatList(int param_1,uint32_t param_2);
uint32_t ItemParse_cvarListUndefined(int param_1,uint32_t param_2);
uint32_t ItemParse_cvarStrList(int param_1,uint32_t param_2);
bool ItemParse_cvarTest(int param_1,uint32_t param_2);
uint32_t ItemParse_decoration(int param_1);
bool ItemParse_disableCvar(int param_1,uint32_t param_2);
bool ItemParse_doubleClick(int param_1,uint32_t param_2);
bool ItemParse_elementheight(int param_1,uint32_t param_2);
bool ItemParse_elementtype(int param_1,uint32_t param_2);
bool ItemParse_elementwidth(int param_1,uint32_t param_2);
bool ItemParse_enableCvar(int param_1,uint32_t param_2);
bool ItemParse_execKey(int param_1,uint32_t param_2);
bool ItemParse_feeder(int param_1,uint32_t param_2);
bool ItemParse_focusSound(int param_1,uint32_t param_2);
bool ItemParse_group(int param_1,uint32_t param_2);
bool ItemParse_hideCvar(int param_1,uint32_t param_2);
uint32_t ItemParse_horizontalscroll(int param_1);
bool ItemParse_leaveFocus(int param_1,uint32_t param_2);
uint32_t ItemParse_maxChars(int param_1,uint32_t param_2);
bool ItemParse_model_angle(int param_1,uint32_t param_2);
uint32_t ItemParse_model_animplay(int param_1,uint32_t param_2);
bool ItemParse_model_fovx(int param_1,uint32_t param_2);
bool ItemParse_model_fovy(int param_1,uint32_t param_2);
bool ItemParse_model_origin(int param_1,uint32_t param_2);
bool ItemParse_model_rotation(int param_1,uint32_t param_2);
bool ItemParse_mouseEnter(int param_1,uint32_t param_2);
bool ItemParse_mouseEnterText(int param_1,uint32_t param_2);
bool ItemParse_mouseExit(int param_1,uint32_t param_2);
bool ItemParse_mouseExitText(int param_1,uint32_t param_2);
bool ItemParse_name(int param_1,uint32_t param_2);
uint32_t ItemParse_noToggle(int param_1);
uint32_t ItemParse_notselectable(int param_1);
bool ItemParse_onEnter(int param_1,uint32_t param_2);
bool ItemParse_onEsc(int param_1,uint32_t param_2);
bool ItemParse_onFocus(int param_1,uint32_t param_2);
uint32_t ItemParse_origin(int param_1,uint32_t param_2);
bool ItemParse_rect(int param_1,uint32_t param_2);
void ItemParse_settingDisabled(int param_1,uint32_t param_2);
void ItemParse_settingEnabled(int param_1,uint32_t param_2);
bool ItemParse_showCvar(int param_1,uint32_t param_2);
bool ItemParse_special(int param_1,uint32_t param_2);
bool ItemParse_style(int param_1,uint32_t param_2);
bool ItemParse_text(int param_1,uint32_t param_2);
bool ItemParse_textalign(int param_1,uint32_t param_2);
bool ItemParse_textalignx(int param_1,uint32_t param_2);
bool ItemParse_textaligny(int param_1,uint32_t param_2);
uint32_t ItemParse_textasfloat(int param_1);
uint32_t ItemParse_textasint(int param_1);
bool ItemParse_textfile(int param_1,uint32_t param_2);
bool ItemParse_textfont(int param_1,uint32_t param_2);
bool ItemParse_textscale(int param_1,uint32_t param_2);
bool ItemParse_textstyle(int param_1,uint32_t param_2);
bool ItemParse_tooltip(int param_1,uint32_t param_2);
bool ItemParse_tooltipalignx(int param_1,uint32_t param_2);
bool ItemParse_tooltipaligny(int param_1,uint32_t param_2);
uint32_t ItemParse_type(int param_1,uint32_t param_2);
uint32_t ItemParse_visible(int param_1,uint32_t param_2);
void ItemParse_voteFlag(int param_1,uint32_t param_2);
uint32_t ItemParse_wrapped(int param_1);
bool MenuParse_background(int param_1,uint32_t param_2);
bool MenuParse_border(int param_1,uint32_t param_2);
bool MenuParse_borderSize(int param_1,uint32_t param_2);
bool MenuParse_cinematic(int param_1,uint32_t param_2);
bool MenuParse_execKey(int param_1,uint32_t param_2);
bool MenuParse_execKeyInt(int param_1,uint32_t param_2);
bool MenuParse_fadeAmount(int param_1,uint32_t param_2);
bool MenuParse_fadeClamp(int param_1,uint32_t param_2);
bool MenuParse_fadeCycle(int param_1,uint32_t param_2);
bool MenuParse_fullscreen(int param_1,uint32_t param_2);
uint32_t MenuParse_itemDef(int param_1,uint32_t param_2);
bool MenuParse_itemHotkeyMode(int param_1,uint32_t param_2);
uint32_t MenuParse_modal(int param_1);
bool MenuParse_name(int param_1,uint32_t param_2);
bool MenuParse_onClose(int param_1,uint32_t param_2);
bool MenuParse_onESC(int param_1,uint32_t param_2);
bool MenuParse_onEnter(int param_1,uint32_t param_2);
bool MenuParse_onOpen(int param_1,uint32_t param_2);
bool MenuParse_onTimeout(int param_1,uint32_t param_2);
uint32_t MenuParse_outOfBounds(int param_1);
uint32_t MenuParse_popup(int param_1);
bool MenuParse_rect(int param_1,uint32_t param_2);
bool MenuParse_soundLoop(int param_1,uint32_t param_2);
bool MenuParse_style(int param_1,uint32_t param_2);
uint32_t MenuParse_visible(int param_1,uint32_t param_2);
bool PC_Char_Parse(uint32_t param_1,uint8_t *param_2);
uint32_t PC_Color_Parse(uint32_t param_1,int param_2);
uint32_t PC_Float_Parse(uint32_t param_1,float *param_2);
uint32_t PC_Int_Parse(uint32_t param_1,int *param_2);
uint32_t PC_Script_Parse(uint32_t param_1,uint32_t *param_2);
void PC_SourceError(uint32_t param_1,char *param_2);
void PC_SourceWarning(uint32_t param_1,char *param_2);
bool PC_String_Parse(uint32_t param_1,uint32_t *param_2);
bool PC_String_ParseNoAlloc(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void PC_String_tolower(char *param_1);
uint32_t PC_Vec_Parse(uint32_t param_1,int param_2);
void Parse1DMatrix(uint32_t param_1,uint param_2,int param_3);
void Parse2DMatrix(uint32_t param_1,int param_2,int param_3,int param_4);
void Parse3DMatrix(uint32_t param_1,int param_2,int param_3,int param_4,int param_5);
bool Rect_Parse(uint32_t param_1,float *param_2);
uint32_t String_Parse(uint32_t param_1,uint32_t *param_2);
void UI_ReadableSize(char *param_1,int param_2,uint param_3);

#endif /* ET_UI_UI_PARSE_H */
