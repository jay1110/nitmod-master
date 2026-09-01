#ifndef ET_UI_UI_PARSE_H
#define ET_UI_UI_PARSE_H

/* Configuration parsing, script loading
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"

void PC_SourceWarning(uint32_t param_1,char *param_2) {;
void PC_SourceError(uint32_t param_1,char *param_2) {;
uint32_t PC_Float_Parse(uint32_t param_1,float *param_2) {;
uint32_t PC_Color_Parse(uint32_t param_1,int param_2) {;
uint32_t PC_Vec_Parse(uint32_t param_1,int param_2) {;
uint32_t PC_Int_Parse(uint32_t param_1,int *param_2) {;
bool PC_String_Parse(uint32_t param_1,uint32_t *param_2) {;
bool PC_String_ParseNoAlloc(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
uint64_t COM_ParseExt_constprop_2(int *param_1) {;
void COM_FixPath(char *param_1) {;
char * COM_SkipPath(char *param_1) {;
void COM_StripExtension(char *param_1,char *param_2) {;
void COM_StripFilename(char *param_1,char *param_2) {;
uint COM_BitCheck(int param_1,uint param_2) {;
void COM_BitSet(int param_1,uint param_2) {;
void COM_BitClear(int param_1,uint param_2) {;
void COM_ParseError(char *param_1) {;
int COM_Compress(char *param_1) {;
uint8_t * COM_ParseExt(int *param_1,int param_2) {;
void COM_MatchToken(uint32_t param_1,char *param_2) {;
void Parse1DMatrix(uint32_t param_1,uint param_2,int param_3) {;
void Parse2DMatrix(uint32_t param_1,int param_2,int param_3,int param_4) {;
void Parse3DMatrix(uint32_t param_1,int param_2,int param_3,int param_4,int param_5) {;
void Com_sprintf(char *param_1,size_t param_2,char *param_3) {;
uint32_t Info_NextPair(uint32_t *param_1,char *param_2,char *param_3) {;
bool Info_Validate(char *param_1) {;
uint64_t COM_ParseExt_nico(uint32_t *param_1,int param_2) {;
void Com_Error(uint32_t param_1,char *param_2) {;
void Com_Printf(char *param_1) {;
void Com_DPrintf(char *param_1) {;
uint32_t Float_Parse(uint32_t param_1,float *param_2) {;
uint32_t Color_Parse(uint32_t param_1,int param_2) {;
uint32_t Int_Parse(uint32_t param_1,long *param_2) {;
bool Rect_Parse(uint32_t param_1,float *param_2) {;
uint32_t String_Parse(uint32_t param_1,uint32_t *param_2) {;
uint32_t PC_Script_Parse(uint32_t param_1,uint32_t *param_2) {;
uint32_t ParseColorRange(int param_1,uint32_t param_2,int param_3) {;

#endif /* ET_UI_UI_PARSE_H */
