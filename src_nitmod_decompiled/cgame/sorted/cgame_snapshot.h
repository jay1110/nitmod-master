#ifndef CGAME_SNAPSHOT_H
#define CGAME_SNAPSHOT_H

/* Snapshot processing and interpolation */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void CG_ExecuteNewServerCommands(int param_1);
void CG_SetInitialSnapshot(int param_1);
void CG_ProcessSnapshots(void);

#endif

