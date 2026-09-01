#ifndef CGAME_MAIN_H
#define CGAME_MAIN_H

/* Client-game VM lifecycle and frame orchestration */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void CG_InitStatsDebug(void);
void CG_InitFlameChunks(void);
void CG_InitLocalEntities(void);
void CG_Shutdown(void);
void CG_InitMarkPolys(void);
void CG_InitPMGraphics(void);
void CG_InitPM(void);

#endif

