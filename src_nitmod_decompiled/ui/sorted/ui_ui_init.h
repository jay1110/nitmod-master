#ifndef ET_UI_UI_INIT_H
#define ET_UI_UI_INIT_H

/**
 * @file ui_ui_init.h
 * @brief ui_init
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 * Original decompilation: Ghidra
 */

#include "ui_types.h"
#include "ui_globals.h"

void Init_Display(uint32_t param_1);
void String_Init(void);
void Tooltip_Initialize(int param_1);
void UI_InitMemory(void);
void UI_RegisterCvars(void);
void Window_Init(uint16_t *param_1);
void _UI_Init(void);
void deregister_tm_clones(void);
void register_tm_clones(void);

#endif /* ET_UI_UI_INIT_H */
