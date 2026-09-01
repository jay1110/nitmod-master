#ifndef NITMOD_DATABASE_H
#define NITMOD_DATABASE_H

/* db_* persistence helpers */

#include "nitmod_types.h"
#include "nitmod_globals.h"

uint32_t db_setmetatable(uint32_t param_1);
uint32_t db_getregistry(uint32_t param_1);
uint32_t db_setfenv(uint32_t param_1);
uint32_t db_getmetatable(uint32_t param_1);
uint32_t db_getfenv(uint32_t param_1);
uint32_t db_debug(uint32_t param_1);
uint32_t db_getupvalue(uint32_t param_1);
uint32_t db_setupvalue(uint32_t param_1);
uint32_t db_getlocal(uint32_t param_1);
uint32_t db_setlocal(uint32_t param_1);
uint32_t db_getinfo(int param_1);
uint32_t db_sethook(uint32_t param_1);
uint32_t db_gethook(uint32_t param_1);
uint32_t db_errorfb(int param_1);

#endif

