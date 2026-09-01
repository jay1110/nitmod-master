#ifndef CGAME_CONSOLECMDS_H
#define CGAME_CONSOLECMDS_H

/* Client console commands */

#include "nitmod_types.h"
#include "nitmod_globals.h"

uint32_t CG_ConsoleCommand(void);
void CG_InitConsoleCommands(void);
uint8_t * CG_Argv(uint32_t param_1);

#endif

