/* Embedded Lua VM and bindings — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_lua.h"

uint32_t G_LuaCall(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = lua_pcall(*(uint32_t *)(param_1 + 0x17c),param_3,param_4,0);
  if (tmp_i1 == 4) {
    LOG("Lua API: memory allocation error #2 ( %s )\n",param_1 + 4);
    *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + 1;
    return 0;
  }
  if (tmp_i1 != 5) {
    if (tmp_i1 != 2) {
      return 1;
    }
    tmp_u2 = lua_tolstring(*(uint32_t *)(param_1 + 0x17c),0xffffffff,0);
    LOG("Lua API: %s error running lua script: %s\n",param_2,tmp_u2);
    lua_settop(*(uint32_t *)(param_1 + 0x17c),0xfffffffe);
    *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + 1;
    return 0;
  }
  LOG("Lua API: traceback error ( %s )\n",param_1 + 4);
  *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + 1;
  return 0;
}

bool G_LuaGetNamedFunction(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  if (*(int *)(param_1 + 0x17c) != 0) {
    lua_getfield(*(int *)(param_1 + 0x17c),0xffffd8ee,param_2);
    tmp_i1 = lua_type(*(uint32_t *)(param_1 + 0x17c),0xffffffff);
    if (tmp_i1 != 6) {
      lua_settop(*(uint32_t *)(param_1 + 0x17c),0xfffffffe);
    }
    return tmp_i1 == 6;
  }
  return false;
}

uint32_t G_LuaStartVM(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t local_ec;
  uint32_t local_e8;
  uint8_t local_dc [64];
  uint8_t local_9c [64];
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0x118329;
  tmp_i1 = luaL_newstate();
  *(int *)(param_1 + 0x17c) = tmp_i1;
  if (tmp_i1 == 0) {
    LOG("Lua API: Lua failed to initialise.\n");
    return 0;
  }
  luaL_openlibs(tmp_i1);
  trap_Cvar_VariableStringBuffer("fs_basepath",local_dc,0x40);
  trap_Cvar_VariableStringBuffer("fs_homepath",local_9c,0x40);
  trap_Cvar_VariableStringBuffer("fs_game",local_5c,0x40);
  local_ec = va("%s%s%s%s?.lua;%s%s%s%slualibs%s?.lua",local_9c,&g_unk_0024ed91,local_5c,&g_unk_0024ed91
                ,local_9c,&g_unk_0024ed91,local_5c,&g_unk_0024ed91,&g_unk_0024ed91);
  local_e8 = va("%s%s%s%slualibs%s?.%s",local_9c,&g_unk_0024ed91,local_5c,&g_unk_0024ed91,&g_unk_0024ed91,
                &g_unk_002718fb);
  tmp_i1 = Q_stricmp(local_dc,local_9c);
  if (tmp_i1 != 0) {
    local_ec = va("%s%s%s%s?.lua;%s%s%s%slualibs%s?.lua;%s",local_dc,&g_unk_0024ed91,local_5c,
                  &g_unk_0024ed91,local_dc,&g_unk_0024ed91,local_5c,&g_unk_0024ed91,&g_unk_0024ed91,local_ec
                 );
    local_e8 = va("%s%s%s%slualibs%s?.%s;%s",local_dc,&g_unk_0024ed91,local_5c,&g_unk_0024ed91,
                  &g_unk_0024ed91,&g_unk_002718fb,local_e8);
  }
  lua_getfield(*(uint32_t *)(param_1 + 0x17c),0xffffd8ee,"package");
  tmp_i1 = lua_type(*(uint32_t *)(param_1 + 0x17c),0xffffffff);
  if (tmp_i1 == 5) {
    lua_pushstring(*(uint32_t *)(param_1 + 0x17c),local_ec);
    lua_setfield(*(uint32_t *)(param_1 + 0x17c),0xfffffffe,"path");
    lua_pushstring(*(uint32_t *)(param_1 + 0x17c),local_e8);
    lua_setfield(*(uint32_t *)(param_1 + 0x17c),0xfffffffe,"cpath");
  }
  lua_settop(*(uint32_t *)(param_1 + 0x17c),0xfffffffe);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),local_ec);
  lua_setfield(*(uint32_t *)(param_1 + 0x17c),0xffffd8ee,"LUA_PATH");
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),local_e8);
  lua_setfield(*(uint32_t *)(param_1 + 0x17c),0xffffd8ee,"LUA_CPATH");
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),&g_unk_0024ed91);
  lua_setfield(*(uint32_t *)(param_1 + 0x17c),0xffffd8ee,"LUA_DIRSEP");
  lua_createtable(*(uint32_t *)(param_1 + 0x17c),0,0);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"CS_PLAYERS");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),0x2b1);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"TEAM_AXIS");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),1);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"TEAM_ALLIES");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),2);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"TEAM_SPECTATOR");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),3);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"EXEC_NOW");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),0);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"EXEC_INSERT");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),1);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"EXEC_APPEND");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),2);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"FS_READ");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),0);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"FS_WRITE");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),1);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"FS_APPEND");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),2);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"FS_APPEND_SYNC");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),3);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"SAY_ALL");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),0);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"SAY_TEAM");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),1);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"SAY_BUDDY");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),2);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"SAY_TEAMNL");
  lua_pushinteger(*(uint32_t *)(param_1 + 0x17c),3);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),"HOSTARCH");
  lua_pushstring(*(uint32_t *)(param_1 + 0x17c),&g_unk_0025d1d5);
  lua_settable(*(uint32_t *)(param_1 + 0x17c),0xfffffffd);
  lua_setfield(*(uint32_t *)(param_1 + 0x17c),0xffffd8ee,"et");
  tmp_i1 = param_1 + 4;
  luaL_register(*(uint32_t *)(param_1 + 0x17c),"et",etlib);
  LOG("Lua API: Loading %s\n",tmp_i1);
  tmp_i2 = luaL_loadbuffer(*(uint32_t *)(param_1 + 0x17c),*(uint32_t *)(param_1 + 0x170),
                          *(uint32_t *)(param_1 + 0x174),tmp_i1);
  if (tmp_i2 == 3) {
    tmp_u3 = lua_tolstring(*(uint32_t *)(param_1 + 0x17c),0xffffffff,0);
    LOG("Lua API: syntax error during pre-compilation: %s\n",tmp_u3);
    lua_settop(*(uint32_t *)(param_1 + 0x17c),0xfffffffe);
    *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + 1;
    return 0;
  }
  if (tmp_i2 == 4) {
    LOG("Lua API: memory allocation error #1 ( %s )\n",tmp_i1);
    *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + 1;
    return 0;
  }
  tmp_i2 = lua_pcall(*(uint32_t *)(param_1 + 0x17c),0,0,0);
  if (tmp_i2 == 4) {
    LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_i1);
    *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + 1;
  }
  else if (tmp_i2 == 5) {
    LOG("Lua API: traceback error ( %s )\n",tmp_i1);
    *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + 1;
  }
  else {
    if (tmp_i2 != 2) {
      return 1;
    }
    tmp_u3 = lua_tolstring(*(uint32_t *)(param_1 + 0x17c),0xffffffff,0);
    LOG("Lua API: %s error running lua script: %s\n","G_LuaStartVM",tmp_u3);
    lua_settop(*(uint32_t *)(param_1 + 0x17c),0xfffffffe);
    *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + 1;
  }
  return 0;
}

void G_LuaStopVM(int *param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if (param_1 != (int *)0x0) {
    if ((void *)param_1[0x5c] != (void *)0x0) {
      free((void *)param_1[0x5c]);
      param_1[0x5c] = 0;
    }
    if (param_1[0x5f] != 0) {
      lua_getfield(param_1[0x5f],0xffffd8ee,"et_Quit");
      tmp_i1 = lua_type(param_1[0x5f],0xffffffff);
      if (tmp_i1 == 6) {
        tmp_i1 = lua_pcall(param_1[0x5f],0,0,0);
        if (tmp_i1 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",param_1 + 1);
          param_1[0x5e] = param_1[0x5e] + 1;
        }
        else if (tmp_i1 == 5) {
          LOG("Lua API: traceback error ( %s )\n",param_1 + 1);
          param_1[0x5e] = param_1[0x5e] + 1;
        }
        else if (tmp_i1 == 2) {
          tmp_u2 = lua_tolstring(param_1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_Quit",tmp_u2);
          lua_settop(param_1[0x5f],0xfffffffe);
          param_1[0x5e] = param_1[0x5e] + 1;
        }
      }
      else {
        lua_settop(param_1[0x5f],0xfffffffe);
      }
      lua_close(param_1[0x5f]);
      param_1[0x5f] = 0;
    }
    tmp_i1 = *param_1;
    if (-1 < tmp_i1) {
      if ((int *)(&lVM)[tmp_i1] == param_1) {
        (&lVM)[tmp_i1] = 0;
      }
      if (param_1[0x5e] == 0) {
        LOG("Lua API: Lua module [%s] [%s] unloaded.\n",param_1 + 1,param_1 + 0x51);
        free(param_1);
        return;
      }
    }
    free(param_1);
  }
  return;
}

uint32_t G_LuaInit(void)
{
  byte tmp_b1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  void *__ptr;
  int tmp_i5;
  char *tmp_pc6;
  int *tmp_pi7;
  uint *tmp_pu8;
  uint tmp_u9;
  uint *tmp_pu10;
  byte *tmp_pb11;
  int tmp_i12;
  char *__needle;
  uint *local_14c;
  int local_148;
  uint32_t local_120;
  uint local_11c [66];
  uint32_t uStack_14;
  
  uStack_14 = 0x118ef9;
  if (lua_modules[0x10] != '\0') {
    local_14c = local_11c;
    Q_strncpyz(local_14c,0x2e52c50,0x100);
    tmp_pu10 = local_14c;
    do {
      tmp_pu8 = tmp_pu10;
      tmp_u2 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu10 = tmp_pu8 + 1;
    } while (tmp_u3 == 0);
    tmp_u9 = tmp_u3 >> 0x10;
    tmp_pu10 = (uint *)((int)tmp_pu8 + 6);
    if ((tmp_u2 & 0x8080) != 0) {
      tmp_pu10 = tmp_pu8 + 1;
      tmp_u9 = tmp_u3;
    }
    tmp_u2 = 0;
    tmp_pb11 = (byte *)((int)tmp_pu10 +
                      ((-3 - (uint)CARRY1((byte)tmp_u9,(byte)tmp_u9)) - (int)local_14c));
    do {
      *(uint32_t *)((int)&lVM + tmp_u2) = 0;
      *(uint32_t *)((int)&g_unk_02e456e4 + tmp_u2) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0x40);
    if (-1 < (int)tmp_pb11) {
      tmp_i12 = 1;
      local_148 = 0;
      tmp_pu10 = local_11c;
      do {
        tmp_b1 = (byte)*tmp_pu10;
        if ((tmp_b1 == 0x3b || tmp_b1 == 0x2c) || ((tmp_b1 & 0xdf) == 0)) {
          *(byte *)tmp_pu10 = 0;
          __needle = (char *)0x0;
          tmp_i4 = trap_FS_FOpenFile(local_14c,&local_120,0);
          if (tmp_i4 < 0) {
            LOG("Lua API: can not open file %s\n",local_14c);
          }
          else if (tmp_i4 < 0x100001) {
            __ptr = malloc(tmp_i4 + 1);
            trap_FS_Read(__ptr,tmp_i4,local_120);
            *(uint8_t *)((int)__ptr + tmp_i4) = 0;
            trap_FS_FCloseFile(local_120);
            __needle = (char *)G_SHA1(__ptr);
            tmp_i5 = Q_stricmp(0x2e502b0,&g_unk_0026ea14);
            if ((tmp_i5 == 0) ||
               (tmp_pc6 = strstr(lua_allowedModules + 0x10,__needle), tmp_pc6 != (char *)0x0)) {
              tmp_pi7 = malloc(0x180);
              *tmp_pi7 = -1;
              Q_strncpyz(tmp_pi7 + 1,local_14c,0x40);
              Q_strncpyz(tmp_pi7 + 0x11,&g_unk_0026ea14,0x100);
              tmp_pc6 = (char *)0x29;
              Q_strncpyz(tmp_pi7 + 0x51,__needle,0x29);
              tmp_pi7[0x5c] = (int)__ptr;
              tmp_pi7[0x5d] = tmp_i4;
              tmp_pi7[0x5e] = 0;
              tmp_i4 = G_LuaStartVM(tmp_pi7);
              if (tmp_i4 == 0) {
                G_LuaStopVM(tmp_pi7);
                __needle = tmp_pc6;
              }
              else {
                *tmp_pi7 = local_148;
                (&lVM)[local_148] = tmp_pi7;
                local_148 = local_148 + 1;
                __needle = tmp_pc6;
              }
            }
            else {
              free(__ptr);
              LOG("Lua API: Lua module [%s] [%s] disallowed by ACL\n",local_14c,__needle);
            }
          }
          else {
            LOG("Lua API: ignoring file %s (too big)\n",local_14c);
            trap_FS_FCloseFile(local_120);
          }
          if ((int)tmp_pb11 <= tmp_i12) {
            if (local_148 < 0x10) {
              local_14c = (uint *)0x0;
              goto LAB_00118fbc;
            }
LAB_0011903c:
            LOG("Lua API: too many lua files specified, only the first %d have been loaded\n",0x10,
                __needle);
            return 1;
          }
          local_14c = (uint *)((int)tmp_pu10 + 1);
          if (0xf < local_148) goto LAB_0011903c;
        }
        else {
LAB_00118fbc:
          if ((int)tmp_pb11 < tmp_i12) {
            return 1;
          }
        }
        tmp_i12 = tmp_i12 + 1;
        tmp_pu10 = (uint *)((int)tmp_pu10 + 1);
      } while( true );
    }
  }
  return 1;
}

void G_LuaShutdown(void)
{
  int *__ptr;
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  
  tmp_pu3 = &lVM;
  do {
    __ptr = (int *)*tmp_pu3;
    if (__ptr != (int *)0x0) {
      if ((void *)__ptr[0x5c] != (void *)0x0) {
        free((void *)__ptr[0x5c]);
        __ptr[0x5c] = 0;
      }
      if (__ptr[0x5f] != 0) {
        lua_getfield(__ptr[0x5f],0xffffd8ee,"et_Quit");
        tmp_i1 = lua_type(__ptr[0x5f],0xffffffff);
        if (tmp_i1 == 6) {
          tmp_i1 = lua_pcall(__ptr[0x5f],0,0,0);
          if (tmp_i1 == 4) {
            LOG("Lua API: memory allocation error #2 ( %s )\n",__ptr + 1);
            __ptr[0x5e] = __ptr[0x5e] + 1;
          }
          else if (tmp_i1 == 5) {
            LOG("Lua API: traceback error ( %s )\n",__ptr + 1);
            __ptr[0x5e] = __ptr[0x5e] + 1;
          }
          else if (tmp_i1 == 2) {
            tmp_u2 = lua_tolstring(__ptr[0x5f],0xffffffff,0);
            LOG("Lua API: %s error running lua script: %s\n","et_Quit",tmp_u2);
            lua_settop(__ptr[0x5f],0xfffffffe);
            __ptr[0x5e] = __ptr[0x5e] + 1;
          }
        }
        else {
          lua_settop(__ptr[0x5f],0xfffffffe);
        }
        lua_close(__ptr[0x5f]);
        __ptr[0x5f] = 0;
      }
      tmp_i1 = *__ptr;
      if (-1 < tmp_i1) {
        if (__ptr == (int *)(&lVM)[tmp_i1]) {
          (&lVM)[tmp_i1] = 0;
        }
        if (__ptr[0x5e] == 0) {
          LOG("Lua API: Lua module [%s] [%s] unloaded.\n",__ptr + 1,__ptr + 0x51);
        }
      }
      free(__ptr);
    }
    tmp_pu3 = tmp_pu3 + 1;
  } while (tmp_pu3 != (uint32_t *)&CheckSums);
  return;
}

void G_LuaStatus(uint32_t param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  char *tmp_pc4;
  int *tmp_pi5;
  char *tmp_pc6;
  char *tmp_pc7;
  
  tmp_i2 = -(uint)(lVM == 0) + 1;
  if (g_unk_02e456e4 != 0) {
    tmp_i2 = -(uint)(lVM == 0) + 2;
  }
  if (g_unk_02e456e8 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e456ec != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e456f0 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e456f4 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e456f8 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e456fc != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e45700 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e45704 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e45708 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e4570c != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e45710 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e45714 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e45718 != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (g_unk_02e4571c != 0) {
    tmp_i2 = tmp_i2 + 1;
  }
  if (tmp_i2 != 0) {
    if (tmp_i2 == 1) {
      G_refPrintf(param_1,"Lua API: showing lua information ( 1 module loaded )");
    }
    else {
      G_refPrintf(param_1,"Lua API: showing lua information ( %d modules loaded )",tmp_i2);
    }
    tmp_pc7 = "Filename";
    tmp_pc6 = "Signature";
    tmp_pi5 = (int *)0x25d35d;
    tmp_pc4 = "VM";
    tmp_pu3 = &lVM;
    G_refPrintf(param_1,"%-2s %-24s %-40s %-24s","VM","Modname","Signature","Filename");
    G_refPrintf(param_1,
                "-- ------------------------ ---------------------------------------- ------------------------"
               );
    do {
      tmp_pi1 = (int *)*tmp_pu3;
      if (tmp_pi1 != (int *)0x0) {
        tmp_pc7 = (char *)(tmp_pi1 + 1);
        tmp_pc6 = (char *)(tmp_pi1 + 0x51);
        tmp_pi5 = tmp_pi1 + 0x11;
        tmp_pc4 = (char *)*tmp_pi1;
        G_refPrintf(param_1,"%2d %-24s %-40s %-24s",tmp_pc4,tmp_pi5,tmp_pc6,tmp_pc7);
      }
      tmp_pu3 = tmp_pu3 + 1;
    } while (tmp_pu3 != (uint32_t *)&CheckSums);
    G_refPrintf(param_1,
                "-- ------------------------ ---------------------------------------- ------------------------"
                ,tmp_pc4,tmp_pi5,tmp_pc6,tmp_pc7);
    return;
  }
  G_refPrintf(param_1,"Lua API: no scripts loaded.");
  return;
}

int G_LuaGetVM(int param_1)
{
  int tmp_i1;
  
  if (((((((lVM == 0) || (tmp_i1 = lVM, *(int *)(lVM + 0x17c) != param_1)) &&
         ((g_unk_02e456e4 == 0 || (tmp_i1 = g_unk_02e456e4, *(int *)(g_unk_02e456e4 + 0x17c) != param_1))))
        && ((g_unk_02e456e8 == 0 || (tmp_i1 = g_unk_02e456e8, *(int *)(g_unk_02e456e8 + 0x17c) != param_1))
           )) && ((g_unk_02e456ec == 0 ||
                  (tmp_i1 = g_unk_02e456ec, *(int *)(g_unk_02e456ec + 0x17c) != param_1)))) &&
      ((((g_unk_02e456f0 == 0 || (tmp_i1 = g_unk_02e456f0, *(int *)(g_unk_02e456f0 + 0x17c) != param_1)) &&
        ((g_unk_02e456f4 == 0 || (tmp_i1 = g_unk_02e456f4, *(int *)(g_unk_02e456f4 + 0x17c) != param_1))))
       && ((((g_unk_02e456f8 == 0 || (tmp_i1 = g_unk_02e456f8, *(int *)(g_unk_02e456f8 + 0x17c) != param_1)
             ) && ((g_unk_02e456fc == 0 ||
                   (tmp_i1 = g_unk_02e456fc, *(int *)(g_unk_02e456fc + 0x17c) != param_1)))) &&
           ((((g_unk_02e45700 == 0 ||
              (tmp_i1 = g_unk_02e45700, *(int *)(g_unk_02e45700 + 0x17c) != param_1)) &&
             ((g_unk_02e45704 == 0 ||
              (tmp_i1 = g_unk_02e45704, *(int *)(g_unk_02e45704 + 0x17c) != param_1)))) &&
            (((g_unk_02e45708 == 0 ||
              (tmp_i1 = g_unk_02e45708, *(int *)(g_unk_02e45708 + 0x17c) != param_1)) &&
             ((g_unk_02e4570c == 0 ||
              (tmp_i1 = g_unk_02e4570c, *(int *)(g_unk_02e4570c + 0x17c) != param_1)))))))))))) &&
     (((((g_unk_02e45710 == 0 || (tmp_i1 = g_unk_02e45710, *(int *)(g_unk_02e45710 + 0x17c) != param_1)) &&
        ((g_unk_02e45714 == 0 || (tmp_i1 = g_unk_02e45714, *(int *)(g_unk_02e45714 + 0x17c) != param_1))))
       && (((g_unk_02e45718 == 0 || (tmp_i1 = g_unk_02e45718, *(int *)(g_unk_02e45718 + 0x17c) != param_1))
           && (tmp_i1 = g_unk_02e4571c, g_unk_02e4571c != 0)))) &&
      (*(int *)(g_unk_02e4571c + 0x17c) != param_1)))) {
    tmp_i1 = 0;
  }
  return tmp_i1;
}

void G_LuaHook_InitGame(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
LAB_00119822:
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_InitGame");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        lua_pushinteger(tmp_pi1[0x5f],param_2);
        lua_pushinteger(tmp_pi1[0x5f],param_3);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],3,0,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_pi4 = tmp_pi4 + 1;
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_InitGame",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
          if (tmp_pi4 == (int *)&CheckSums) {
            return;
          }
          goto LAB_00119822;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return;
    }
  } while( true );
}

void G_LuaHook_ShutdownGame(uint32_t param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
LAB_001199f2:
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ShutdownGame");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],1,0,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_pi4 = tmp_pi4 + 1;
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ShutdownGame",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
          if (tmp_pi4 == (int *)&CheckSums) {
            return;
          }
          goto LAB_001199f2;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return;
    }
  } while( true );
}

void G_LuaHook_RunFrame(uint32_t param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
LAB_00119b92:
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_RunFrame");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],1,0,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_pi4 = tmp_pi4 + 1;
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_RunFrame",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
          if (tmp_pi4 == (int *)&CheckSums) {
            return;
          }
          goto LAB_00119b92;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return;
    }
  } while( true );
}

G_LuaHook_ClientConnect(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ClientConnect");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        lua_pushinteger(tmp_pi1[0x5f],param_2);
        lua_pushinteger(tmp_pi1[0x5f],param_3);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],3,1,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ClientConnect",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else {
          tmp_i2 = lua_isstring(tmp_pi1[0x5f],0xffffffff);
          if (tmp_i2 != 0) {
            tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
            Q_strncpyz(param_4,tmp_u3,0x400);
            return 1;
          }
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
  } while (tmp_pi4 != (int *)&CheckSums);
  return 0;
}

void G_LuaHook_ClientDisconnect(uint32_t param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
LAB_00119f62:
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ClientDisconnect");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],1,0,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_pi4 = tmp_pi4 + 1;
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ClientDisconnect",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
          if (tmp_pi4 == (int *)&CheckSums) {
            return;
          }
          goto LAB_00119f62;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return;
    }
  } while( true );
}

void G_LuaHook_ClientBegin(uint32_t param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
LAB_0011a102:
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ClientBegin");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],1,0,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_pi4 = tmp_pi4 + 1;
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ClientBegin",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
          if (tmp_pi4 == (int *)&CheckSums) {
            return;
          }
          goto LAB_0011a102;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return;
    }
  } while( true );
}

void G_LuaHook_ClientUserinfoChanged(uint32_t param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
LAB_0011a2a2:
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ClientUserinfoChanged");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],1,0,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_pi4 = tmp_pi4 + 1;
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ClientUserinfoChanged",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
          if (tmp_pi4 == (int *)&CheckSums) {
            return;
          }
          goto LAB_0011a2a2;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return;
    }
  } while( true );
}

void G_LuaHook_ClientSpawn
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ClientSpawn");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        lua_pushinteger(tmp_pi1[0x5f],param_2);
        lua_pushinteger(tmp_pi1[0x5f],param_3);
        lua_pushinteger(tmp_pi1[0x5f],param_4);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],4,0,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ClientSpawn",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
  } while (tmp_pi4 != (int *)&CheckSums);
  return;
}

uint32_t G_LuaHook_ClientCommand(uint32_t param_1,uint32_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ClientCommand");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        lua_pushstring(tmp_pi1[0x5f],param_2);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],2,1,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ClientCommand",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else {
          tmp_i2 = lua_isnumber(tmp_pi1[0x5f],0xffffffff);
          if ((tmp_i2 != 0) && (tmp_i2 = lua_tointeger(tmp_pi1[0x5f],0xffffffff), tmp_i2 == 1)) {
            return 1;
          }
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return 0;
    }
  } while( true );
}

uint32_t G_LuaHook_ConsoleCommand(uint32_t param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ConsoleCommand");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushstring(tmp_pi1[0x5f],param_1);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],1,1,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ConsoleCommand",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else {
          tmp_i2 = lua_isnumber(tmp_pi1[0x5f],0xffffffff);
          if ((tmp_i2 != 0) && (tmp_i2 = lua_tointeger(tmp_pi1[0x5f],0xffffffff), tmp_i2 == 1)) {
            return 1;
          }
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return 0;
    }
  } while( true );
}

uint32_t G_LuaHook_UpgradeSkill(uint32_t param_1,uint32_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_UpgradeSkill");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        lua_pushinteger(tmp_pi1[0x5f],param_2);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],2,1,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_UpgradeSkill",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else {
          tmp_i2 = lua_isnumber(tmp_pi1[0x5f],0xffffffff);
          if ((tmp_i2 != 0) && (tmp_i2 = lua_tointeger(tmp_pi1[0x5f],0xffffffff), tmp_i2 == -1)) {
            return 1;
          }
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return 0;
    }
  } while( true );
}

uint32_t G_LuaHook_SetPlayerSkill(uint32_t param_1,uint32_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_SetPlayerSkill");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        lua_pushinteger(tmp_pi1[0x5f],param_2);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],2,1,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_SetPlayerSkill",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else {
          tmp_i2 = lua_isnumber(tmp_pi1[0x5f],0xffffffff);
          if ((tmp_i2 != 0) && (tmp_i2 = lua_tointeger(tmp_pi1[0x5f],0xffffffff), tmp_i2 == -1)) {
            return 1;
          }
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return 0;
    }
  } while( true );
}

void G_LuaHook_Print(uint32_t param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
LAB_0011ae12:
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_Print");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushstring(tmp_pi1[0x5f],param_1);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],1,0,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_pi4 = tmp_pi4 + 1;
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_Print",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
          if (tmp_pi4 == (int *)&CheckSums) {
            return;
          }
          goto LAB_0011ae12;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return;
    }
  } while( true );
}

G_LuaHook_Obituary(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_Obituary");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        lua_pushinteger(tmp_pi1[0x5f],param_2);
        lua_pushinteger(tmp_pi1[0x5f],param_3);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],3,1,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_Obituary",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else {
          tmp_i2 = lua_isstring(tmp_pi1[0x5f],0xffffffff);
          if (tmp_i2 != 0) {
            tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
            Q_strncpyz(param_4,tmp_u3,0x400);
            return 1;
          }
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
  } while (tmp_pi4 != (int *)&CheckSums);
  return 0;
}

uint32_t G_LuaHook_ReceivedGlobalStats(uint32_t param_1,uint32_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  tmp_pi4 = &lVM;
LAB_0011b1e2:
  do {
    tmp_pi1 = (int *)*tmp_pi4;
    if (((tmp_pi1 != (int *)0x0) && (-1 < *tmp_pi1)) && (tmp_pi1[0x5f] != 0)) {
      lua_getfield(tmp_pi1[0x5f],0xffffd8ee,"et_ReceivedGlobalStats");
      tmp_i2 = lua_type(tmp_pi1[0x5f],0xffffffff);
      if (tmp_i2 == 6) {
        lua_pushinteger(tmp_pi1[0x5f],param_1);
        lua_pushstring(tmp_pi1[0x5f],param_2);
        tmp_i2 = lua_pcall(tmp_pi1[0x5f],2,1,0);
        if (tmp_i2 == 4) {
          LOG("Lua API: memory allocation error #2 ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 5) {
          LOG("Lua API: traceback error ( %s )\n",tmp_pi1 + 1);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
        }
        else if (tmp_i2 == 2) {
          tmp_pi4 = tmp_pi4 + 1;
          tmp_u3 = lua_tolstring(tmp_pi1[0x5f],0xffffffff,0);
          LOG("Lua API: %s error running lua script: %s\n","et_ReceivedGlobalStats",tmp_u3);
          lua_settop(tmp_pi1[0x5f],0xfffffffe);
          tmp_pi1[0x5e] = tmp_pi1[0x5e] + 1;
          if (tmp_pi4 == (int *)&CheckSums) {
            return 0;
          }
          goto LAB_0011b1e2;
        }
      }
      else {
        lua_settop(tmp_pi1[0x5f],0xfffffffe);
      }
    }
    tmp_pi4 = tmp_pi4 + 1;
    if (tmp_pi4 == (int *)&CheckSums) {
      return 0;
    }
  } while( true );
}

uint32_t luaM_toobig(uint32_t param_1)
{
  luaG_runerror(param_1,"memory allocation error: block too big");
  return 0;
}

void luaM_realloc_(int param_1,uint32_t param_2,int param_3,int param_4)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = *(int *)(param_1 + 0x10);
  tmp_i2 = (**(void **)(tmp_i1 + 0xc))(*(uint32_t *)(tmp_i1 + 0x10),param_2,param_3,param_4);
  if ((tmp_i2 == 0) && (param_4 != 0)) {
    luaD_throw(param_1,4);
  }
  *(int *)(tmp_i1 + 0x44) = *(int *)(tmp_i1 + 0x44) + (param_4 - param_3);
  return;
}

void luaA_pushobject(int param_1,uint32_t *param_2)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  
  tmp_u1 = param_2[1];
  tmp_pu2 = *(uint32_t **)(param_1 + 8);
  *tmp_pu2 = *param_2;
  tmp_pu2[1] = tmp_u1;
  tmp_pu2[2] = param_2[2];
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

uint32_t lua_checkstack(int param_1,int param_2)
{
  uint tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_u2 = 0;
  if ((param_2 < 0x1f41) &&
     (tmp_i3 = *(int *)(param_1 + 8),
     (tmp_i3 - *(int *)(param_1 + 0xc) >> 2) * -0x55555555 + param_2 < 0x1f41)) {
    if (0 < param_2) {
      if (*(int *)(param_1 + 0x1c) - tmp_i3 <= param_2 * 0xc) {
        luaD_growstack(param_1,param_2);
        tmp_i3 = *(int *)(param_1 + 8);
      }
      tmp_u1 = tmp_i3 + param_2 * 0xc;
      if (*(uint *)(*(int *)(param_1 + 0x14) + 8) < tmp_u1) {
        *(uint *)(*(int *)(param_1 + 0x14) + 8) = tmp_u1;
      }
    }
    tmp_u2 = 1;
  }
  return tmp_u2;
}

void lua_xmove(int param_1,int param_2,int param_3)
{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  
  if (param_1 != param_2) {
    tmp_i5 = *(int *)(param_1 + 8) + param_3 * -0xc;
    *(int *)(param_1 + 8) = tmp_i5;
    if (0 < param_3) {
      tmp_i4 = 0;
      while( true ) {
        tmp_pu1 = (uint32_t *)(tmp_i5 + tmp_i4 * 0xc);
        tmp_pu2 = *(uint32_t **)(param_2 + 8);
        *(uint32_t **)(param_2 + 8) = tmp_pu2 + 3;
        tmp_u3 = tmp_pu1[1];
        *tmp_pu2 = *tmp_pu1;
        tmp_pu2[1] = tmp_u3;
        tmp_pu2[2] = tmp_pu1[2];
        if (tmp_i4 + 1 == param_3) break;
        tmp_i5 = *(int *)(param_1 + 8);
        tmp_i4 = tmp_i4 + 1;
      }
    }
  }
  return;
}

void lua_setlevel(int param_1,int param_2)
{
  *(uint16_t *)(param_2 + 0x34) = *(uint16_t *)(param_1 + 0x34);
  return;
}

uint32_t lua_atpanic(int param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  tmp_u1 = *(uint32_t *)(*(int *)(param_1 + 0x10) + 0x58);
  *(uint32_t *)(*(int *)(param_1 + 0x10) + 0x58) = param_2;
  return tmp_u1;
}

void lua_newthread(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    luaC_step(param_1);
  }
  tmp_u2 = luaE_newthread(param_1);
  tmp_pu1 = *(uint32_t **)(param_1 + 8);
  tmp_pu1[2] = 8;
  *tmp_pu1 = tmp_u2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

int lua_gettop(int param_1)
{
  return (*(int *)(param_1 + 8) - *(int *)(param_1 + 0xc) >> 2) * -0x55555555;
}

void lua_settop(int param_1,int param_2)
{
  uint tmp_u1;
  uint tmp_u2;
  
  if (-1 < param_2) {
    tmp_u1 = *(uint *)(param_1 + 8);
    tmp_u2 = *(int *)(param_1 + 0xc) + param_2 * 0xc;
    if (tmp_u1 < tmp_u2) {
      do {
        *(uint *)(param_1 + 8) = tmp_u1 + 0xc;
        *(uint32_t *)(tmp_u1 + 8) = 0;
        tmp_u1 = *(uint *)(param_1 + 8);
        tmp_u2 = *(int *)(param_1 + 0xc) + param_2 * 0xc;
      } while (tmp_u1 < tmp_u2);
    }
    *(uint *)(param_1 + 8) = tmp_u2;
    return;
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + (param_2 * 3 + 3) * 4;
  return;
}

void lua_remove(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint32_t *tmp_pu5;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_pu5 = *(uint32_t **)(param_1 + 8);
        tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u2;
        tmp_pu3 = (uint32_t *)(param_1 + 0x54);
      }
      else if (param_2 == -10000) {
        tmp_pu5 = *(uint32_t **)(param_1 + 8);
        tmp_pu3 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_pu3 = (uint32_t *)(param_1 + 0x48);
        tmp_pu5 = *(uint32_t **)(param_1 + 8);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i1 + 7) < -0x2712 - param_2) {
          tmp_pu5 = *(uint32_t **)(param_1 + 8);
          tmp_pu3 = &luaO_nilobject_;
        }
        else {
          tmp_pu5 = *(uint32_t **)(param_1 + 8);
          tmp_pu3 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
        }
      }
    }
    else {
      tmp_pu5 = *(uint32_t **)(param_1 + 8);
      tmp_pu3 = tmp_pu5 + param_2 * 3;
    }
  }
  else {
    tmp_pu3 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pu5 = *(uint32_t **)(param_1 + 8);
    if (tmp_pu5 <= tmp_pu3) {
      tmp_pu3 = &luaO_nilobject_;
    }
  }
  tmp_pu4 = tmp_pu3 + 3;
  if (tmp_pu3 + 3 < tmp_pu5) {
    do {
      tmp_pu3 = tmp_pu4 + 3;
      tmp_pu4[-1] = tmp_pu4[2];
      tmp_pu4[-3] = *tmp_pu4;
      tmp_pu4[-2] = tmp_pu4[1];
      tmp_pu5 = *(uint32_t **)(param_1 + 8);
      tmp_pu4 = tmp_pu3;
    } while (tmp_pu3 < tmp_pu5);
  }
  *(uint32_t **)(param_1 + 8) = tmp_pu5 + -3;
  return;
}

void lua_insert(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint32_t *tmp_pu5;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_pu5 = (uint32_t *)(param_1 + 0x54);
        tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u1;
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else if (param_2 == -10000) {
        tmp_pu5 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else if (param_2 == -0x2712) {
        tmp_pu5 = (uint32_t *)(param_1 + 0x48);
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else {
        tmp_i2 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i2 + 7) < -0x2712 - param_2) {
          tmp_pu3 = *(uint32_t **)(param_1 + 8);
          tmp_pu5 = &luaO_nilobject_;
        }
        else {
          tmp_pu5 = (uint32_t *)(tmp_i2 + 0x14 + (-0x2713 - param_2) * 0xc);
          tmp_pu3 = *(uint32_t **)(param_1 + 8);
        }
      }
    }
    else {
      tmp_pu3 = *(uint32_t **)(param_1 + 8);
      tmp_pu5 = tmp_pu3 + param_2 * 3;
    }
LAB_002019d7:
    if (tmp_pu3 <= tmp_pu5) goto LAB_002019fc;
  }
  else {
    tmp_pu5 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pu3 = *(uint32_t **)(param_1 + 8);
    if (tmp_pu3 <= tmp_pu5) {
      tmp_pu5 = &luaO_nilobject_;
      goto LAB_002019d7;
    }
  }
  do {
    tmp_pu4 = tmp_pu3 + -3;
    *tmp_pu3 = tmp_pu3[-3];
    tmp_pu3[1] = tmp_pu3[-2];
    tmp_pu3[2] = tmp_pu3[-1];
    tmp_pu3 = tmp_pu4;
  } while (tmp_pu5 < tmp_pu4);
  tmp_pu3 = *(uint32_t **)(param_1 + 8);
LAB_002019fc:
  tmp_u1 = tmp_pu3[1];
  *tmp_pu5 = *tmp_pu3;
  tmp_pu5[1] = tmp_u1;
  tmp_pu5[2] = tmp_pu3[2];
  return;
}

void lua_replace(int param_1,int param_2)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  int tmp_i6;
  
  if (param_2 == -0x2711) {
    tmp_i3 = *(int *)(param_1 + 0x14);
    if (tmp_i3 == *(int *)(param_1 + 0x28)) {
      luaG_runerror(param_1,"no calling environment");
      tmp_i3 = *(int *)(param_1 + 0x14);
    }
LAB_00201b5c:
    tmp_u2 = *(uint32_t *)(**(int **)(tmp_i3 + 4) + 0xc);
    *(uint32_t *)(param_1 + 0x5c) = 5;
    *(uint32_t *)(param_1 + 0x54) = tmp_u2;
    tmp_i5 = **(int **)(tmp_i3 + 4);
    *(uint32_t *)(tmp_i5 + 0xc) = *(uint32_t *)(*(int *)(param_1 + 8) + -0xc);
    tmp_i3 = *(int *)(param_1 + 8);
    if ((*(int *)(tmp_i3 + -4) < 4) ||
       (tmp_i6 = *(int *)(tmp_i3 + -0xc), (*(byte *)(tmp_i6 + 5) & 3) == 0)) goto LAB_00201b20;
LAB_00201b8e:
    if ((*(byte *)(tmp_i5 + 5) & 4) == 0) goto LAB_00201b20;
    luaC_barrierf(param_1,tmp_i5,tmp_i6);
  }
  else if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_i3 = *(int *)(param_1 + 0x14);
        goto LAB_00201b5c;
      }
      if (param_2 == -10000) {
        tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else {
        if (param_2 != -0x2712) {
          tmp_i5 = **(int **)(*(int *)(param_1 + 0x14) + 4);
          if ((int)(uint)*(byte *)(tmp_i5 + 7) < -0x2712 - param_2) {
            tmp_i3 = *(int *)(param_1 + 8);
            tmp_pu4 = &luaO_nilobject_;
          }
          else {
            tmp_i3 = *(int *)(param_1 + 8);
            tmp_pu4 = (uint32_t *)(tmp_i5 + 0x14 + (-0x2713 - param_2) * 0xc);
          }
          goto LAB_00201c09;
        }
        tmp_pu4 = (uint32_t *)(param_1 + 0x48);
      }
      tmp_i3 = *(int *)(param_1 + 8);
    }
    else {
      tmp_i3 = *(int *)(param_1 + 8);
      tmp_pu4 = (uint32_t *)(tmp_i3 + param_2 * 0xc);
    }
LAB_00201c09:
    tmp_u2 = *(uint32_t *)(tmp_i3 + -8);
    *tmp_pu4 = *(uint32_t *)(tmp_i3 + -0xc);
    tmp_pu4[1] = tmp_u2;
    tmp_pu4[2] = *(uint32_t *)(tmp_i3 + -4);
    if (param_2 < -0x2712) {
      tmp_i3 = *(int *)(param_1 + 8);
      if ((*(int *)(tmp_i3 + -4) < 4) ||
         (tmp_i6 = *(int *)(tmp_i3 + -0xc), (*(byte *)(tmp_i6 + 5) & 3) == 0)) goto LAB_00201b20;
      tmp_i5 = **(int **)(*(int *)(param_1 + 0x14) + 4);
      goto LAB_00201b8e;
    }
  }
  else {
    tmp_pu1 = *(uint32_t **)(param_1 + 8);
    tmp_pu4 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pu1 <= tmp_pu4) {
      tmp_pu4 = &luaO_nilobject_;
    }
    tmp_u2 = tmp_pu1[-2];
    *tmp_pu4 = tmp_pu1[-3];
    tmp_pu4[1] = tmp_u2;
    tmp_pu4[2] = tmp_pu1[-1];
  }
  tmp_i3 = *(int *)(param_1 + 8);
LAB_00201b20:
  *(int *)(param_1 + 8) = tmp_i3 + -0xc;
  return;
}

void lua_pushvalue(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_pu4 = *(uint32_t **)(param_1 + 8);
        tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u1;
        tmp_pu3 = (uint32_t *)(param_1 + 0x54);
      }
      else if (param_2 == -10000) {
        tmp_pu4 = *(uint32_t **)(param_1 + 8);
        tmp_pu3 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_pu3 = (uint32_t *)(param_1 + 0x48);
        tmp_pu4 = *(uint32_t **)(param_1 + 8);
      }
      else {
        tmp_i2 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i2 + 7) < -0x2712 - param_2) {
          tmp_pu4 = *(uint32_t **)(param_1 + 8);
          tmp_pu3 = &luaO_nilobject_;
        }
        else {
          tmp_pu4 = *(uint32_t **)(param_1 + 8);
          tmp_pu3 = (uint32_t *)(tmp_i2 + 0x14 + (-0x2713 - param_2) * 0xc);
        }
      }
    }
    else {
      tmp_pu4 = *(uint32_t **)(param_1 + 8);
      tmp_pu3 = tmp_pu4 + param_2 * 3;
    }
  }
  else {
    tmp_pu3 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pu4 = *(uint32_t **)(param_1 + 8);
    if (tmp_pu4 <= tmp_pu3) {
      tmp_pu3 = &luaO_nilobject_;
    }
  }
  tmp_u1 = tmp_pu3[1];
  *tmp_pu4 = *tmp_pu3;
  tmp_pu4[1] = tmp_u1;
  tmp_pu4[2] = tmp_pu3[2];
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

uint32_t lua_type(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u2;
        tmp_pu3 = (uint32_t *)(param_1 + 0x54);
      }
      else if (param_2 == -10000) {
        tmp_pu3 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_pu3 = (uint32_t *)(param_1 + 0x48);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i1 + 7) < -0x2712 - param_2) {
          return 0xffffffff;
        }
        tmp_pu3 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
      }
    }
    else {
      tmp_pu3 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
    }
  }
  else {
    tmp_pu3 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (*(uint32_t **)(param_1 + 8) <= tmp_pu3) {
      return 0xffffffff;
    }
  }
  if (tmp_pu3 == &luaO_nilobject_) {
    return 0xffffffff;
  }
  return tmp_pu3[2];
}

char * lua_typename(uint32_t param_1,int param_2)
{
  if (param_2 != -1) {
    return *(char **)(luaT_typenames + param_2 * 4);
  }
  return "no value";
}

bool lua_iscfunction(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  int tmp_i3;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      tmp_i3 = tmp_pi2[2];
      goto joined_r0x00201f52;
    }
    if (param_2 == -0x2711) {
      tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u1;
      return false;
    }
    if (param_2 == -10000) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
      tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      goto joined_r0x00201f52;
    }
    if (param_2 == -0x2712) {
      tmp_pi2 = (int *)(param_1 + 0x48);
      tmp_i3 = *(int *)(param_1 + 0x50);
      goto joined_r0x00201f52;
    }
    tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i3 + 7)) {
      tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
      tmp_pi2 = (int *)(tmp_i3 + 4);
      tmp_i3 = *(int *)(tmp_i3 + 0xc);
      goto joined_r0x00201f52;
    }
  }
  else {
    tmp_pi2 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi2 < *(int **)(param_1 + 8)) {
      tmp_i3 = tmp_pi2[2];
      goto joined_r0x00201f52;
    }
  }
  tmp_pi2 = &luaO_nilobject_;
  tmp_i3 = g_unk_002701c8;
joined_r0x00201f52:
  if (tmp_i3 != 6) {
    return false;
  }
  return *(char *)(*tmp_pi2 + 6) != '\0';
}

bool lua_isnumber(int param_1,int param_2)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  uint8_t local_18 [16];
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_pu2 = (uint32_t *)(param_1 + 0x54);
        tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u1;
        goto LAB_00202076;
      }
      if (param_2 == -10000) {
        tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      }
      else if (param_2 == -0x2712) {
        tmp_pu2 = (uint32_t *)(param_1 + 0x48);
        tmp_i3 = *(int *)(param_1 + 0x50);
      }
      else {
        tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i3 + 7) < -0x2712 - param_2) goto LAB_00202060;
        tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
        tmp_pu2 = (uint32_t *)(tmp_i3 + 4);
        tmp_i3 = *(int *)(tmp_i3 + 0xc);
      }
    }
    else {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      tmp_i3 = tmp_pu2[2];
    }
  }
  else {
    tmp_pu2 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pu2 < *(uint32_t **)(param_1 + 8)) {
      tmp_i3 = tmp_pu2[2];
    }
    else {
LAB_00202060:
      tmp_pu2 = &luaO_nilobject_;
      tmp_i3 = g_unk_002701c8;
    }
  }
  if (tmp_i3 == 3) {
    return true;
  }
LAB_00202076:
  tmp_i3 = luaV_tonumber(tmp_pu2,local_18);
  return tmp_i3 != 0;
}

bool lua_isstring(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u2;
        tmp_pu3 = (uint32_t *)(param_1 + 0x54);
      }
      else if (param_2 == -10000) {
        tmp_pu3 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_pu3 = (uint32_t *)(param_1 + 0x48);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i1 + 7) < -0x2712 - param_2) {
          return false;
        }
        tmp_pu3 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
      }
    }
    else {
      tmp_pu3 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
    }
  }
  else {
    tmp_pu3 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (*(uint32_t **)(param_1 + 8) <= tmp_pu3) {
      return false;
    }
  }
  if (tmp_pu3 == &luaO_nilobject_) {
    return false;
  }
  return tmp_pu3[2] - 3 < 2;
}

bool lua_isuserdata(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  
  tmp_i4 = g_unk_002701c8;
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u2;
        return false;
      }
      if (param_2 == -10000) {
        tmp_i4 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      }
      else if (param_2 == -0x2712) {
        tmp_i4 = *(int *)(param_1 + 0x50);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i1 + 7)) {
          tmp_i4 = *(int *)(tmp_i1 + 0x1c + (-0x2713 - param_2) * 0xc);
        }
      }
      goto LAB_00202298;
    }
    tmp_u3 = *(int *)(param_1 + 8) + param_2 * 0xc;
  }
  else {
    tmp_u3 = param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc);
    if (*(uint *)(param_1 + 8) <= tmp_u3) goto LAB_00202298;
  }
  tmp_i4 = *(int *)(tmp_u3 + 8);
LAB_00202298:
  return tmp_i4 == 7 || tmp_i4 == 2;
}

uint32_t lua_rawequal(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  uint32_t *tmp_pu4;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto joined_r0x002023a7;
    }
    if (param_2 == -0x2711) {
      tmp_u3 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u3;
      tmp_pu2 = (uint32_t *)(param_1 + 0x54);
      goto joined_r0x002023a7;
    }
    if (param_2 == -10000) {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      goto joined_r0x002023a7;
    }
    if (param_2 == -0x2712) {
      tmp_pu2 = (uint32_t *)(param_1 + 0x48);
      goto joined_r0x002023a7;
    }
    tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i1 + 7)) {
      tmp_pu2 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
      goto joined_r0x002023a7;
    }
  }
  else {
    tmp_pu2 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pu2 < *(uint32_t **)(param_1 + 8)) goto joined_r0x002023a7;
  }
  tmp_pu2 = &luaO_nilobject_;
joined_r0x002023a7:
  if (param_3 < 1) {
    if (param_3 < -9999) {
      if (param_3 == -0x2711) {
        tmp_u3 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u3;
        tmp_pu4 = (uint32_t *)(param_1 + 0x54);
      }
      else if (param_3 == -10000) {
        tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_3 == -0x2712) {
        tmp_pu4 = (uint32_t *)(param_1 + 0x48);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i1 + 7) < -0x2712 - param_3) {
          return 0;
        }
        tmp_pu4 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_3) * 0xc);
      }
    }
    else {
      tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 8) + param_3 * 0xc);
    }
  }
  else {
    tmp_pu4 = (uint32_t *)(param_3 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (*(uint32_t **)(param_1 + 8) <= tmp_pu4) {
      return 0;
    }
  }
  if ((tmp_pu4 != &luaO_nilobject_) && (tmp_pu2 != &luaO_nilobject_)) {
    tmp_u3 = luaO_rawequalObj();
    return tmp_u3;
  }
  return 0;
}

bool lua_equal(int param_1,int param_2,int param_3)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto joined_r0x002025c8;
    }
    if (param_2 == -0x2711) {
      tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u1;
      tmp_pu2 = (uint32_t *)(param_1 + 0x54);
      goto joined_r0x002025c8;
    }
    if (param_2 == -10000) {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      goto joined_r0x002025c8;
    }
    if (param_2 == -0x2712) {
      tmp_pu2 = (uint32_t *)(param_1 + 0x48);
      goto joined_r0x002025c8;
    }
    tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i3 + 7)) {
      tmp_pu2 = (uint32_t *)(tmp_i3 + 0x14 + (-0x2713 - param_2) * 0xc);
      goto joined_r0x002025c8;
    }
  }
  else {
    tmp_pu2 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pu2 < *(uint32_t **)(param_1 + 8)) goto joined_r0x002025c8;
  }
  tmp_pu2 = &luaO_nilobject_;
joined_r0x002025c8:
  if (param_3 < 1) {
    if (param_3 < -9999) {
      if (param_3 == -0x2711) {
        tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u1;
        tmp_pu4 = (uint32_t *)(param_1 + 0x54);
      }
      else if (param_3 == -10000) {
        tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_3 == -0x2712) {
        tmp_pu4 = (uint32_t *)(param_1 + 0x48);
      }
      else {
        tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i3 + 7) < -0x2712 - param_3) {
          return false;
        }
        tmp_pu4 = (uint32_t *)(tmp_i3 + 0x14 + (-0x2713 - param_3) * 0xc);
      }
    }
    else {
      tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 8) + param_3 * 0xc);
    }
  }
  else {
    tmp_pu4 = (uint32_t *)(param_3 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (*(uint32_t **)(param_1 + 8) <= tmp_pu4) {
      return false;
    }
  }
  if (((tmp_pu4 != &luaO_nilobject_) && (tmp_pu2 != &luaO_nilobject_)) && (tmp_pu2[2] == tmp_pu4[2])) {
    tmp_i3 = luaV_equalval(param_1,tmp_pu2,tmp_pu4);
    return tmp_i3 != 0;
  }
  return false;
}

uint32_t lua_lessthan(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  uint32_t *tmp_pu4;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto joined_r0x002027e7;
    }
    if (param_2 == -0x2711) {
      tmp_u3 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u3;
      tmp_pu2 = (uint32_t *)(param_1 + 0x54);
      goto joined_r0x002027e7;
    }
    if (param_2 == -10000) {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      goto joined_r0x002027e7;
    }
    if (param_2 == -0x2712) {
      tmp_pu2 = (uint32_t *)(param_1 + 0x48);
      goto joined_r0x002027e7;
    }
    tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i1 + 7)) {
      tmp_pu2 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
      goto joined_r0x002027e7;
    }
  }
  else {
    tmp_pu2 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pu2 < *(uint32_t **)(param_1 + 8)) goto joined_r0x002027e7;
  }
  tmp_pu2 = &luaO_nilobject_;
joined_r0x002027e7:
  if (param_3 < 1) {
    if (param_3 < -9999) {
      if (param_3 == -0x2711) {
        tmp_u3 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u3;
        tmp_pu4 = (uint32_t *)(param_1 + 0x54);
      }
      else if (param_3 == -10000) {
        tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_3 == -0x2712) {
        tmp_pu4 = (uint32_t *)(param_1 + 0x48);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i1 + 7) < -0x2712 - param_3) {
          return 0;
        }
        tmp_pu4 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_3) * 0xc);
      }
    }
    else {
      tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 8) + param_3 * 0xc);
    }
  }
  else {
    tmp_pu4 = (uint32_t *)(param_3 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (*(uint32_t **)(param_1 + 8) <= tmp_pu4) {
      return 0;
    }
  }
  if ((tmp_pu4 != &luaO_nilobject_) && (tmp_pu2 != &luaO_nilobject_)) {
    tmp_u3 = luaV_lessthan();
    return tmp_u3;
  }
  return 0;
}

long double lua_tonumber(int param_1,int param_2)
{
  uint32_t tmp_u1;
  double *pdVar2;
  int tmp_i3;
  uint8_t local_18 [16];
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      pdVar2 = (double *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_002029f0;
    }
    if (param_2 != -0x2711) {
      if (param_2 == -10000) {
        pdVar2 = (double *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      }
      else if (param_2 == -0x2712) {
        pdVar2 = (double *)(param_1 + 0x48);
        tmp_i3 = *(int *)(param_1 + 0x50);
      }
      else {
        tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i3 + 7) < -0x2712 - param_2) goto LAB_00202a50;
        tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
        pdVar2 = (double *)(tmp_i3 + 4);
        tmp_i3 = *(int *)(tmp_i3 + 0xc);
      }
      goto LAB_002029f3;
    }
    tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
    *(uint32_t *)(param_1 + 0x5c) = 5;
    *(uint32_t *)(param_1 + 0x54) = tmp_u1;
    pdVar2 = (double *)(param_1 + 0x54);
  }
  else {
    pdVar2 = (double *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (pdVar2 < *(double **)(param_1 + 8)) {
LAB_002029f0:
      tmp_i3 = *(int *)(pdVar2 + 1);
    }
    else {
LAB_00202a50:
      pdVar2 = (double *)&luaO_nilobject_;
      tmp_i3 = g_unk_002701c8;
    }
LAB_002029f3:
    if (tmp_i3 == 3) goto LAB_00202a0c;
  }
  pdVar2 = (double *)luaV_tonumber(pdVar2,local_18);
  if (pdVar2 == (double *)0x0) {
    return (long double)0;
  }
LAB_00202a0c:
  return (long double)*pdVar2;
}

uint32_t lua_tointeger(int param_1,int param_2)
{
  uint32_t tmp_u1;
  double *pdVar2;
  int tmp_i3;
  uint32_t local_24;
  uint8_t local_18 [16];
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      pdVar2 = (double *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_00202b10;
    }
    if (param_2 != -0x2711) {
      if (param_2 == -10000) {
        pdVar2 = (double *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      }
      else if (param_2 == -0x2712) {
        pdVar2 = (double *)(param_1 + 0x48);
        tmp_i3 = *(int *)(param_1 + 0x50);
      }
      else {
        tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i3 + 7) < -0x2712 - param_2) goto LAB_00202b80;
        tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
        pdVar2 = (double *)(tmp_i3 + 4);
        tmp_i3 = *(int *)(tmp_i3 + 0xc);
      }
      goto LAB_00202b13;
    }
    tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
    *(uint32_t *)(param_1 + 0x5c) = 5;
    *(uint32_t *)(param_1 + 0x54) = tmp_u1;
    pdVar2 = (double *)(param_1 + 0x54);
  }
  else {
    pdVar2 = (double *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (pdVar2 < *(double **)(param_1 + 8)) {
LAB_00202b10:
      tmp_i3 = *(int *)(pdVar2 + 1);
    }
    else {
LAB_00202b80:
      pdVar2 = (double *)&luaO_nilobject_;
      tmp_i3 = g_unk_002701c8;
    }
LAB_00202b13:
    if (tmp_i3 == 3) goto LAB_00202b2c;
  }
  pdVar2 = (double *)luaV_tonumber(pdVar2,local_18);
  if (pdVar2 == (double *)0x0) {
    return 0;
  }
LAB_00202b2c:
  local_24 = SUB84((double)((float)*pdVar2 + 6.7553994e+15),0);
  return local_24;
}

bool lua_toboolean(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  int tmp_i3;
  bool tmp_b4;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      tmp_i3 = tmp_pi2[2];
      goto LAB_00202c51;
    }
    if (param_2 == -0x2711) {
      tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u1;
      return true;
    }
    if (param_2 == -10000) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
      tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      goto LAB_00202c51;
    }
    if (param_2 == -0x2712) {
      tmp_pi2 = (int *)(param_1 + 0x48);
      tmp_i3 = *(int *)(param_1 + 0x50);
      goto LAB_00202c51;
    }
    tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i3 + 7)) {
      tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
      tmp_pi2 = (int *)(tmp_i3 + 4);
      tmp_i3 = *(int *)(tmp_i3 + 0xc);
      goto LAB_00202c51;
    }
  }
  else {
    tmp_pi2 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi2 < *(int **)(param_1 + 8)) {
      tmp_i3 = tmp_pi2[2];
      goto LAB_00202c51;
    }
  }
  tmp_pi2 = &luaO_nilobject_;
  tmp_i3 = g_unk_002701c8;
LAB_00202c51:
  tmp_b4 = false;
  if ((tmp_i3 != 0) && (tmp_b4 = true, tmp_i3 == 1)) {
    tmp_b4 = *tmp_pi2 != 0;
  }
  return tmp_b4;
}

int lua_tolstring(int param_1,int param_2,uint32_t *param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int *tmp_pi3;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi3 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_00202d96;
    }
    if (param_2 != -0x2711) {
      if (param_2 == -10000) {
        tmp_pi3 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i2 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      }
      else if (param_2 == -0x2712) {
        tmp_pi3 = (int *)(param_1 + 0x48);
        tmp_i2 = *(int *)(param_1 + 0x50);
      }
      else {
        tmp_i2 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i2 + 7) < -0x2712 - param_2) goto LAB_00202e30;
        tmp_i2 = (-0x2713 - param_2) * 0xc + 0x10 + tmp_i2;
        tmp_pi3 = (int *)(tmp_i2 + 4);
        tmp_i2 = *(int *)(tmp_i2 + 0xc);
      }
      goto joined_r0x00202d9c;
    }
    tmp_pi3 = (int *)(param_1 + 0x54);
    tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
    *(uint32_t *)(param_1 + 0x5c) = 5;
    *(uint32_t *)(param_1 + 0x54) = tmp_u1;
LAB_00202da2:
    tmp_i2 = luaV_tostring(param_1,tmp_pi3);
    if (tmp_i2 == 0) {
      if (param_3 != (uint32_t *)0x0) {
        *param_3 = 0;
        return 0;
      }
      return 0;
    }
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      luaC_step(param_1);
    }
    if (param_2 < 1) {
      if (param_2 < -9999) {
        if (param_2 == -0x2711) {
          tmp_pi3 = (int *)(param_1 + 0x54);
          tmp_i2 = *(int *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
          *(uint32_t *)(param_1 + 0x5c) = 5;
          *(int *)(param_1 + 0x54) = tmp_i2;
          goto LAB_00202e47;
        }
        if (param_2 == -10000) {
          tmp_pi3 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
          tmp_i2 = *(int *)(*(int *)(param_1 + 0x10) + 0x5c);
          goto LAB_00202e47;
        }
        if (param_2 == -0x2712) {
          tmp_pi3 = (int *)(param_1 + 0x48);
          tmp_i2 = *(int *)(param_1 + 0x48);
          goto LAB_00202e47;
        }
        tmp_i2 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i2 + 7)) {
          tmp_i2 = (-0x2713 - param_2) * 0xc + 0x10 + tmp_i2;
          tmp_pi3 = (int *)(tmp_i2 + 4);
          tmp_i2 = *(int *)(tmp_i2 + 4);
          goto LAB_00202e47;
        }
        goto LAB_00202e83;
      }
      tmp_pi3 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
    }
    else {
      tmp_pi3 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
      if (*(int **)(param_1 + 8) <= tmp_pi3) {
LAB_00202e83:
        tmp_pi3 = &luaO_nilobject_;
        tmp_i2 = luaO_nilobject_;
        goto LAB_00202e47;
      }
    }
  }
  else {
    tmp_pi3 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi3 < *(int **)(param_1 + 8)) {
LAB_00202d96:
      tmp_i2 = tmp_pi3[2];
    }
    else {
LAB_00202e30:
      tmp_pi3 = &luaO_nilobject_;
      tmp_i2 = g_unk_002701c8;
    }
joined_r0x00202d9c:
    if (tmp_i2 != 4) goto LAB_00202da2;
  }
  tmp_i2 = *tmp_pi3;
LAB_00202e47:
  if (param_3 != (uint32_t *)0x0) {
    *param_3 = *(uint32_t *)(tmp_i2 + 0xc);
    tmp_i2 = *tmp_pi3;
  }
  return tmp_i2 + 0x10;
}

uint32_t lua_objlen(int param_1,int param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  uint32_t tmp_u4;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_u4 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u4;
        goto LAB_00203150;
      }
      if (param_2 == -10000) {
        tmp_pi2 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      }
      else if (param_2 == -0x2712) {
        tmp_pi2 = (int *)(param_1 + 0x48);
        tmp_i3 = *(int *)(param_1 + 0x50);
      }
      else {
        tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i3 + 7) < -0x2712 - param_2) goto LAB_0020302e;
        tmp_i3 = (-0x2713 - param_2) * 0xc + 0x10 + tmp_i3;
        tmp_pi2 = (int *)(tmp_i3 + 4);
        tmp_i3 = *(int *)(tmp_i3 + 0xc);
      }
    }
    else {
      tmp_pi2 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      tmp_i3 = tmp_pi2[2];
    }
LAB_0020303a:
    tmp_i1 = tmp_i3 + -4;
    if (tmp_i3 == 4) {
LAB_0020307a:
      return *(uint32_t *)(*tmp_pi2 + 0xc);
    }
  }
  else {
    tmp_pi2 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (*(int **)(param_1 + 8) <= tmp_pi2) {
LAB_0020302e:
      tmp_pi2 = &luaO_nilobject_;
      tmp_i3 = g_unk_002701c8;
      goto LAB_0020303a;
    }
    tmp_i3 = tmp_pi2[2];
    tmp_i1 = tmp_i3 + -4;
    if (tmp_i1 == 0) goto LAB_0020307a;
  }
  if (SBORROW4(tmp_i3,4) == tmp_i1 < 0) {
    if (tmp_i3 == 5) {
LAB_00203150:
      tmp_u4 = luaH_getn();
      return tmp_u4;
    }
    if (tmp_i3 != 7) {
      return 0;
    }
    tmp_u4 = *(uint32_t *)(*tmp_pi2 + 0x10);
  }
  else {
    if (tmp_i3 != 3) {
      return 0;
    }
    tmp_i3 = luaV_tostring(param_1,tmp_pi2);
    tmp_u4 = 0;
    if (tmp_i3 != 0) {
      return *(uint32_t *)(*tmp_pi2 + 0xc);
    }
  }
  return tmp_u4;
}

uint32_t lua_tocfunction(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  int tmp_i3;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_002031dd;
    }
    if (param_2 == -0x2711) {
      tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u1;
      return 0;
    }
    if (param_2 == -10000) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
      tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      goto joined_r0x0020323f;
    }
    if (param_2 == -0x2712) {
      tmp_pi2 = (int *)(param_1 + 0x48);
      tmp_i3 = *(int *)(param_1 + 0x50);
      goto joined_r0x0020323f;
    }
    tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i3 + 7)) {
      tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
      tmp_pi2 = (int *)(tmp_i3 + 4);
      tmp_i3 = *(int *)(tmp_i3 + 0xc);
      goto joined_r0x0020323f;
    }
  }
  else {
    tmp_pi2 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi2 < *(int **)(param_1 + 8)) {
LAB_002031dd:
      tmp_i3 = tmp_pi2[2];
      goto joined_r0x0020323f;
    }
  }
  tmp_pi2 = &luaO_nilobject_;
  tmp_i3 = g_unk_002701c8;
joined_r0x0020323f:
  if ((tmp_i3 == 6) && (*(char *)(*tmp_pi2 + 6) != '\0')) {
    return *(uint32_t *)(*tmp_pi2 + 0x10);
  }
  return 0;
}

int lua_touserdata(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  int tmp_i3;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_002032f5;
    }
    if (param_2 == -0x2711) {
      tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u1;
      return 0;
    }
    if (param_2 == -10000) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
      tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      goto joined_r0x0020336f;
    }
    if (param_2 == -0x2712) {
      tmp_pi2 = (int *)(param_1 + 0x48);
      tmp_i3 = *(int *)(param_1 + 0x50);
      goto joined_r0x0020336f;
    }
    tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i3 + 7)) {
      tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
      tmp_pi2 = (int *)(tmp_i3 + 4);
      tmp_i3 = *(int *)(tmp_i3 + 0xc);
      goto joined_r0x0020336f;
    }
  }
  else {
    tmp_pi2 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi2 < *(int **)(param_1 + 8)) {
LAB_002032f5:
      tmp_i3 = tmp_pi2[2];
      goto joined_r0x0020336f;
    }
  }
  tmp_pi2 = &luaO_nilobject_;
  tmp_i3 = g_unk_002701c8;
joined_r0x0020336f:
  if (tmp_i3 == 2) {
    return *tmp_pi2;
  }
  if (tmp_i3 == 7) {
    return *tmp_pi2 + 0x14;
  }
  return 0;
}

uint32_t lua_tothread(int param_1,int param_2)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_00203435;
    }
    if (param_2 == -0x2711) {
      tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u1;
      return 0;
    }
    if (param_2 == -10000) {
      tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      goto joined_r0x0020349f;
    }
    if (param_2 == -0x2712) {
      tmp_pu2 = (uint32_t *)(param_1 + 0x48);
      tmp_i3 = *(int *)(param_1 + 0x50);
      goto joined_r0x0020349f;
    }
    tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i3 + 7)) {
      tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
      tmp_pu2 = (uint32_t *)(tmp_i3 + 4);
      tmp_i3 = *(int *)(tmp_i3 + 0xc);
      goto joined_r0x0020349f;
    }
  }
  else {
    tmp_pu2 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pu2 < *(uint32_t **)(param_1 + 8)) {
LAB_00203435:
      tmp_i3 = tmp_pu2[2];
      goto joined_r0x0020349f;
    }
  }
  tmp_pu2 = &luaO_nilobject_;
  tmp_i3 = g_unk_002701c8;
joined_r0x0020349f:
  if (tmp_i3 == 8) {
    return *tmp_pu2;
  }
  return 0;
}

int lua_topointer(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int *tmp_pi3;
  int tmp_i4;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_i4 = *(int *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(int *)(param_1 + 0x54) = tmp_i4;
        return tmp_i4;
      }
      if (param_2 != -10000) {
        if (param_2 != -0x2712) {
          tmp_i4 = **(int **)(*(int *)(param_1 + 0x14) + 4);
          if ((int)(uint)*(byte *)(tmp_i4 + 7) < -0x2712 - param_2) {
            tmp_pi3 = &luaO_nilobject_;
          }
          else {
            tmp_pi3 = (int *)(tmp_i4 + 0x14 + (-0x2713 - param_2) * 0xc);
          }
          switch(tmp_pi3[2]) {
          default:
            return 0;
          case 2:
          case 7:
            goto _L594;
          case 5:
          case 6:
          case 8:
            return *tmp_pi3;
          }
        }
        tmp_pi3 = (int *)(param_1 + 0x48);
        tmp_i4 = *(int *)(param_1 + 0x50);
        switch(*(int *)(param_1 + 0x50)) {
        default:
          return 0;
        case 2:
        case 7:
          goto _L569;
        case 5:
        case 6:
        case 8:
          return *(int *)(param_1 + 0x48);
        }
      }
      tmp_i1 = *(int *)(param_1 + 0x10);
      tmp_pi3 = (int *)(tmp_i1 + 0x5c);
      tmp_i4 = *(int *)(tmp_i1 + 100);
      switch(*(int *)(tmp_i1 + 100)) {
      default:
        return 0;
      case 2:
      case 7:
        goto _L569;
      case 5:
      case 6:
      case 8:
        return *(int *)(tmp_i1 + 0x5c);
      }
    }
    tmp_pi3 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
    tmp_i4 = tmp_pi3[2];
    switch(tmp_pi3[2]) {
    default:
      return 0;
    case 2:
    case 7:
      goto _L569;
    case 5:
    case 6:
    case 8:
      goto _L604;
    }
  }
  tmp_pi3 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
  if (tmp_pi3 < *(int **)(param_1 + 8)) {
    if (8 < (uint)tmp_pi3[2]) {
      return 0;
    }
    tmp_i4 = tmp_pi3[2];
    switch(tmp_pi3[2]) {
    default:
      return 0;
    case 2:
    case 7:
      goto _L569;
    case 5:
    case 6:
    case 8:
_L604:
      return *tmp_pi3;
    }
  }
  switch(g_unk_002701c8) {
  default:
    return 0;
  case 2:
  case 7:
    goto _L631;
  case 5:
  case 6:
  case 8:
    tmp_pi3 = &luaO_nilobject_;
    goto _L604;
  }
_L594:
  if (param_2 == -0x2711) {
    tmp_u2 = *(uint32_t *)(tmp_i4 + 0xc);
    *(uint32_t *)(param_1 + 0x5c) = 5;
    *(uint32_t *)(param_1 + 0x54) = tmp_u2;
    return 0;
  }
  if (param_2 == -10000) {
    tmp_pi3 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
    tmp_i4 = *(int *)(*(int *)(param_1 + 0x10) + 100);
  }
  else if (param_2 == -0x2712) {
    tmp_i4 = *(int *)(param_1 + 0x50);
    tmp_pi3 = (int *)(param_1 + 0x48);
  }
  else if ((int)(uint)*(byte *)(tmp_i4 + 7) < -0x2712 - param_2) {
_L631:
    tmp_pi3 = &luaO_nilobject_;
    tmp_i4 = g_unk_002701c8;
  }
  else {
    tmp_i4 = tmp_i4 + (-0x2713 - param_2) * 0xc + 0x10;
    tmp_pi3 = (int *)(tmp_i4 + 4);
    tmp_i4 = *(int *)(tmp_i4 + 0xc);
  }
_L569:
  if (tmp_i4 != 2) {
    if (tmp_i4 != 7) {
      return 0;
    }
    return *tmp_pi3 + 0x14;
  }
  goto _L604;
}

void lua_pushnil(int param_1)
{
  *(uint32_t *)(*(int *)(param_1 + 8) + 8) = 0;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_pushnumber(int param_1,uint64_t param_2)
{
  uint64_t *tmp_pu1;
  
  tmp_pu1 = *(uint64_t **)(param_1 + 8);
  *tmp_pu1 = param_2;
  *(uint32_t *)(tmp_pu1 + 1) = 3;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_pushinteger(int param_1,int param_2)
{
  double *pdVar1;
  
  pdVar1 = *(double **)(param_1 + 8);
  *pdVar1 = (double)param_2;
  *(uint32_t *)(pdVar1 + 1) = 3;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_pushlstring(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    luaC_step(param_1);
  }
  tmp_pu1 = *(uint32_t **)(param_1 + 8);
  tmp_u2 = luaS_newlstr(param_1,param_2,param_3);
  tmp_pu1[2] = 4;
  *tmp_pu1 = tmp_u2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_pushstring(int param_1,char *param_2)
{
  uint32_t *tmp_pu1;
  size_t tmp_s2;
  uint32_t tmp_u3;
  
  if (param_2 == (char *)0x0) {
    *(uint32_t *)(*(int *)(param_1 + 8) + 8) = 0;
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  }
  else {
    tmp_s2 = strlen(param_2);
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      luaC_step(param_1);
    }
    tmp_pu1 = *(uint32_t **)(param_1 + 8);
    tmp_u3 = luaS_newlstr(param_1,param_2,tmp_s2);
    tmp_pu1[2] = 4;
    *tmp_pu1 = tmp_u3;
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  }
  return;
}

void lua_pushvfstring(int param_1)
{
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    luaC_step(param_1);
  }
  luaO_pushvfstring();
  return;
}

void lua_pushfstring(int param_1,uint32_t param_2)
{
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    luaC_step(param_1);
  }
  luaO_pushvfstring(param_1,param_2,&stack0x0000000c);
  return;
}

void lua_pushcclosure(int param_1,uint32_t param_2,int param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int *tmp_pi3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  int tmp_i6;
  
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x44) < *(uint *)(*(int *)(param_1 + 0x10) + 0x40)) {
    tmp_i6 = *(int *)(param_1 + 0x14);
    if (tmp_i6 == *(int *)(param_1 + 0x28)) {
LAB_00203a84:
      tmp_u1 = *(uint32_t *)(param_1 + 0x48);
      goto LAB_002039d1;
    }
  }
  else {
    luaC_step(param_1);
    tmp_i6 = *(int *)(param_1 + 0x14);
    if (tmp_i6 == *(int *)(param_1 + 0x28)) goto LAB_00203a84;
  }
  tmp_u1 = *(uint32_t *)(**(int **)(tmp_i6 + 4) + 0xc);
LAB_002039d1:
  tmp_i6 = param_3 + -1;
  tmp_i2 = luaF_newCclosure(param_1,param_3,tmp_u1);
  *(uint32_t *)(tmp_i2 + 0x10) = param_2;
  tmp_pi3 = (int *)(*(int *)(param_1 + 8) + param_3 * -0xc);
  *(int **)(param_1 + 8) = tmp_pi3;
  if (param_3 != 0) {
    tmp_i5 = param_3 * 0xc + tmp_i2;
    while( true ) {
      tmp_i6 = tmp_i6 + -1;
      tmp_pu4 = (uint32_t *)((int)tmp_pi3 + (-0xc - tmp_i2) + tmp_i5);
      tmp_u1 = tmp_pu4[1];
      *(uint32_t *)(tmp_i5 + 8) = *tmp_pu4;
      *(uint32_t *)(tmp_i5 + 0xc) = tmp_u1;
      *(uint32_t *)(tmp_i5 + 0x10) = tmp_pu4[2];
      if (tmp_i6 == -1) break;
      tmp_pi3 = *(int **)(param_1 + 8);
      tmp_i5 = tmp_i5 + -0xc;
    }
    tmp_pi3 = *(int **)(param_1 + 8);
  }
  tmp_pi3[2] = 6;
  *tmp_pi3 = tmp_i2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_pushboolean(int param_1,int param_2)
{
  uint *tmp_pu1;
  
  tmp_pu1 = *(uint **)(param_1 + 8);
  *tmp_pu1 = (uint)(param_2 != 0);
  tmp_pu1[2] = 1;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_pushlightuserdata(int param_1,uint32_t param_2)
{
  uint32_t *tmp_pu1;
  
  tmp_pu1 = *(uint32_t **)(param_1 + 8);
  *tmp_pu1 = param_2;
  tmp_pu1[2] = 2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

bool lua_pushthread(int param_1)
{
  int *tmp_pi1;
  
  tmp_pi1 = *(int **)(param_1 + 8);
  *tmp_pi1 = param_1;
  tmp_pi1[2] = 8;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return *(int *)(*(int *)(param_1 + 0x10) + 0x68) == param_1;
}

void lua_gettable(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_pu4 = (uint32_t *)(param_1 + 0x54);
        tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u2;
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else if (param_2 == -10000) {
        tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else if (param_2 == -0x2712) {
        tmp_pu4 = (uint32_t *)(param_1 + 0x48);
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i1 + 7) < -0x2712 - param_2) {
          tmp_pu3 = *(uint32_t **)(param_1 + 8);
          tmp_pu4 = &luaO_nilobject_;
        }
        else {
          tmp_pu4 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
          tmp_pu3 = *(uint32_t **)(param_1 + 8);
        }
      }
    }
    else {
      tmp_pu3 = *(uint32_t **)(param_1 + 8);
      tmp_pu4 = tmp_pu3 + param_2 * 3;
    }
  }
  else {
    tmp_pu4 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pu3 = *(uint32_t **)(param_1 + 8);
    if (tmp_pu3 <= tmp_pu4) {
      tmp_pu4 = &luaO_nilobject_;
    }
  }
  luaV_gettable(param_1,tmp_pu4,tmp_pu3 + -3,tmp_pu3 + -3);
  return;
}

void lua_getfield(int param_1,int param_2,char *param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  size_t tmp_s3;
  uint32_t *tmp_pu4;
  uint32_t local_28 [2];
  uint32_t local_20;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_00203c68;
    }
    if (param_2 == -0x2711) {
      tmp_pu4 = (uint32_t *)(param_1 + 0x54);
      tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u2;
      goto LAB_00203c68;
    }
    if (param_2 == -10000) {
      tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      goto LAB_00203c68;
    }
    if (param_2 == -0x2712) {
      tmp_pu4 = (uint32_t *)(param_1 + 0x48);
      goto LAB_00203c68;
    }
    tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i1 + 7)) {
      tmp_pu4 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
      goto LAB_00203c68;
    }
  }
  else {
    tmp_pu4 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pu4 < *(uint32_t **)(param_1 + 8)) goto LAB_00203c68;
  }
  tmp_pu4 = &luaO_nilobject_;
LAB_00203c68:
  tmp_s3 = strlen(param_3);
  local_28[0] = luaS_newlstr(param_1,param_3,tmp_s3);
  local_20 = 4;
  luaV_gettable(param_1,tmp_pu4,local_28,*(uint32_t *)(param_1 + 8));
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_rawget(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  
  tmp_u4 = luaO_nilobject_;
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_u4 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        tmp_pu2 = *(uint32_t **)(param_1 + 8);
        *(uint32_t *)(param_1 + 0x54) = tmp_u4;
      }
      else if (param_2 == -10000) {
        tmp_pu2 = *(uint32_t **)(param_1 + 8);
        tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_pu2 = *(uint32_t **)(param_1 + 8);
        tmp_u4 = *(uint32_t *)(param_1 + 0x48);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        tmp_pu2 = *(uint32_t **)(param_1 + 8);
        if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i1 + 7)) {
          tmp_u4 = *(uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
        }
      }
    }
    else {
      tmp_pu2 = *(uint32_t **)(param_1 + 8);
      tmp_u4 = tmp_pu2[param_2 * 3];
    }
  }
  else {
    tmp_pu3 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pu2 = *(uint32_t **)(param_1 + 8);
    if (tmp_pu3 < tmp_pu2) {
      tmp_u4 = *tmp_pu3;
    }
  }
  tmp_pu2 = (uint32_t *)luaH_get(tmp_u4,tmp_pu2 + -3);
  tmp_i1 = *(int *)(param_1 + 8);
  tmp_u4 = *tmp_pu2;
  *(uint32_t *)(tmp_i1 + -8) = tmp_pu2[1];
  *(uint32_t *)(tmp_i1 + -0xc) = tmp_u4;
  *(uint32_t *)(tmp_i1 + -4) = tmp_pu2[2];
  return;
}

void lua_rawgeti(int param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  uint32_t *tmp_pu4;
  
  tmp_u3 = luaO_nilobject_;
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_u3 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u3;
      }
      else if (param_2 == -10000) {
        tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_u3 = *(uint32_t *)(param_1 + 0x48);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i1 + 7)) {
          tmp_u3 = *(uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
        }
      }
      goto LAB_00203ec4;
    }
    tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
  }
  else {
    tmp_pu2 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (*(uint32_t **)(param_1 + 8) <= tmp_pu2) goto LAB_00203ec4;
  }
  tmp_u3 = *tmp_pu2;
LAB_00203ec4:
  tmp_pu4 = (uint32_t *)luaH_getnum(tmp_u3,param_3);
  tmp_pu2 = *(uint32_t **)(param_1 + 8);
  tmp_u3 = tmp_pu4[1];
  *tmp_pu2 = *tmp_pu4;
  tmp_pu2[1] = tmp_u3;
  tmp_pu2[2] = tmp_pu4[2];
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_createtable(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    luaC_step(param_1);
  }
  tmp_pu1 = *(uint32_t **)(param_1 + 8);
  tmp_u2 = luaH_new(param_1,param_2,param_3);
  tmp_pu1[2] = 5;
  *tmp_pu1 = tmp_u2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

uint32_t lua_getmetatable(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  int tmp_i3;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_0020404d;
    }
    if (param_2 != -0x2711) {
      if (param_2 == -10000) {
        tmp_pi2 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      }
      else if (param_2 == -0x2712) {
        tmp_pi2 = (int *)(param_1 + 0x48);
        tmp_i3 = *(int *)(param_1 + 0x50);
      }
      else {
        tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i3 + 7) < -0x2712 - param_2) goto LAB_002040f0;
        tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
        tmp_pi2 = (int *)(tmp_i3 + 4);
        tmp_i3 = *(int *)(tmp_i3 + 0xc);
      }
      goto joined_r0x00204053;
    }
    tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
    *(uint32_t *)(param_1 + 0x5c) = 5;
    *(uint32_t *)(param_1 + 0x54) = tmp_u1;
    tmp_pi2 = (int *)(param_1 + 0x54);
  }
  else {
    tmp_pi2 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi2 < *(int **)(param_1 + 8)) {
LAB_0020404d:
      tmp_i3 = tmp_pi2[2];
    }
    else {
LAB_002040f0:
      tmp_pi2 = &luaO_nilobject_;
      tmp_i3 = g_unk_002701c8;
    }
joined_r0x00204053:
    if ((tmp_i3 != 5) && (tmp_i3 != 7)) {
      tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 0x84 + tmp_i3 * 4);
      goto joined_r0x00204117;
    }
  }
  tmp_i3 = *(int *)(*tmp_pi2 + 8);
joined_r0x00204117:
  if (tmp_i3 == 0) {
    return 0;
  }
  tmp_pi2 = *(int **)(param_1 + 8);
  *tmp_pi2 = tmp_i3;
  tmp_pi2[2] = 5;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return 1;
}

void lua_getfenv(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int *tmp_pi3;
  int *tmp_pi4;
  int tmp_i5;
  
  tmp_i1 = g_unk_002701c8;
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi4 = *(int **)(param_1 + 8);
      tmp_pi3 = tmp_pi4 + param_2 * 3;
      goto LAB_002041db;
    }
    if (param_2 != -0x2711) {
      if (param_2 == -10000) {
        tmp_pi3 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i1 = *(int *)(*(int *)(param_1 + 0x10) + 100);
        tmp_pi4 = *(int **)(param_1 + 8);
      }
      else if (param_2 == -0x2712) {
        tmp_pi3 = (int *)(param_1 + 0x48);
        tmp_i1 = *(int *)(param_1 + 0x50);
        tmp_pi4 = *(int **)(param_1 + 8);
      }
      else {
        tmp_i5 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i5 + 7) < -0x2712 - param_2) {
          tmp_pi3 = &luaO_nilobject_;
          tmp_pi4 = *(int **)(param_1 + 8);
        }
        else {
          tmp_pi4 = *(int **)(param_1 + 8);
          tmp_i5 = tmp_i5 + (-0x2713 - param_2) * 0xc + 0x10;
          tmp_pi3 = (int *)(tmp_i5 + 4);
          tmp_i1 = *(int *)(tmp_i5 + 0xc);
        }
      }
      goto joined_r0x0020421f;
    }
    tmp_pi4 = *(int **)(param_1 + 8);
    tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
    *(uint32_t *)(param_1 + 0x5c) = 5;
    *(uint32_t *)(param_1 + 0x54) = tmp_u2;
LAB_002041f1:
    tmp_pi4[2] = 0;
  }
  else {
    tmp_pi3 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pi4 = *(int **)(param_1 + 8);
    if (tmp_pi3 < tmp_pi4) {
LAB_002041db:
      tmp_i1 = tmp_pi3[2];
    }
    else {
      tmp_pi3 = &luaO_nilobject_;
    }
joined_r0x0020421f:
    if (tmp_i1 != 7) {
      if (tmp_i1 == 8) {
        tmp_i1 = *tmp_pi3;
        tmp_i5 = *(int *)(tmp_i1 + 0x4c);
        *tmp_pi4 = *(int *)(tmp_i1 + 0x48);
        tmp_pi4[1] = tmp_i5;
        tmp_pi4[2] = *(int *)(tmp_i1 + 0x50);
        goto LAB_002041f8;
      }
      if (tmp_i1 != 6) goto LAB_002041f1;
    }
    tmp_i1 = *(int *)(*tmp_pi3 + 0xc);
    tmp_pi4[2] = 5;
    *tmp_pi4 = tmp_i1;
  }
LAB_002041f8:
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return;
}

void lua_settable(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_pu4 = (uint32_t *)(param_1 + 0x54);
        tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u2;
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else if (param_2 == -10000) {
        tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else if (param_2 == -0x2712) {
        tmp_pu4 = (uint32_t *)(param_1 + 0x48);
        tmp_pu3 = *(uint32_t **)(param_1 + 8);
      }
      else {
        tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i1 + 7) < -0x2712 - param_2) {
          tmp_pu3 = *(uint32_t **)(param_1 + 8);
          tmp_pu4 = &luaO_nilobject_;
        }
        else {
          tmp_pu4 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
          tmp_pu3 = *(uint32_t **)(param_1 + 8);
        }
      }
    }
    else {
      tmp_pu3 = *(uint32_t **)(param_1 + 8);
      tmp_pu4 = tmp_pu3 + param_2 * 3;
    }
  }
  else {
    tmp_pu4 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pu3 = *(uint32_t **)(param_1 + 8);
    if (tmp_pu3 <= tmp_pu4) {
      tmp_pu4 = &luaO_nilobject_;
    }
  }
  luaV_settable(param_1,tmp_pu4,tmp_pu3 + -6,tmp_pu3 + -3);
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x18;
  return;
}

void lua_setfield(int param_1,int param_2,char *param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  size_t tmp_s3;
  uint32_t *tmp_pu4;
  uint32_t local_28 [2];
  uint32_t local_20;
  
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_00204498;
    }
    if (param_2 == -0x2711) {
      tmp_pu4 = (uint32_t *)(param_1 + 0x54);
      tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u2;
      goto LAB_00204498;
    }
    if (param_2 == -10000) {
      tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      goto LAB_00204498;
    }
    if (param_2 == -0x2712) {
      tmp_pu4 = (uint32_t *)(param_1 + 0x48);
      goto LAB_00204498;
    }
    tmp_i1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i1 + 7)) {
      tmp_pu4 = (uint32_t *)(tmp_i1 + 0x14 + (-0x2713 - param_2) * 0xc);
      goto LAB_00204498;
    }
  }
  else {
    tmp_pu4 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pu4 < *(uint32_t **)(param_1 + 8)) goto LAB_00204498;
  }
  tmp_pu4 = &luaO_nilobject_;
LAB_00204498:
  tmp_s3 = strlen(param_3);
  local_28[0] = luaS_newlstr(param_1,param_3,tmp_s3);
  local_20 = 4;
  luaV_settable(param_1,tmp_pu4,local_28,*(int *)(param_1 + 8) + -0xc);
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0xc;
  return;
}

void lua_rawset(int param_1,int param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int *tmp_pi4;
  int *tmp_pi5;
  
  tmp_i1 = luaO_nilobject_;
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_pi5 = (int *)(param_1 + 0x54);
        tmp_pi4 = *(int **)(param_1 + 8);
        tmp_i1 = *(int *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(int *)(param_1 + 0x54) = tmp_i1;
      }
      else if (param_2 == -10000) {
        tmp_pi4 = *(int **)(param_1 + 8);
        tmp_pi5 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i1 = *(int *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_pi5 = (int *)(param_1 + 0x48);
        tmp_i1 = *(int *)(param_1 + 0x48);
        tmp_pi4 = *(int **)(param_1 + 8);
      }
      else {
        tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i3 + 7) < -0x2712 - param_2) {
          tmp_pi5 = &luaO_nilobject_;
          tmp_pi4 = *(int **)(param_1 + 8);
        }
        else {
          tmp_pi4 = *(int **)(param_1 + 8);
          tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
          tmp_pi5 = (int *)(tmp_i3 + 4);
          tmp_i1 = *(int *)(tmp_i3 + 4);
        }
      }
      goto LAB_002045e6;
    }
    tmp_pi4 = *(int **)(param_1 + 8);
    tmp_pi5 = tmp_pi4 + param_2 * 3;
  }
  else {
    tmp_pi4 = *(int **)(param_1 + 8);
    tmp_pi5 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi4 <= tmp_pi5) {
      tmp_pi5 = &luaO_nilobject_;
      goto LAB_002045e6;
    }
  }
  tmp_i1 = *tmp_pi5;
LAB_002045e6:
  tmp_pi2 = (int *)luaH_set(param_1,tmp_i1,tmp_pi4 + -6);
  tmp_i1 = tmp_pi4[-2];
  *tmp_pi2 = tmp_pi4[-3];
  tmp_pi2[1] = tmp_i1;
  tmp_pi2[2] = tmp_pi4[-1];
  tmp_i1 = *(int *)(param_1 + 8);
  if (((3 < *(int *)(tmp_i1 + -4)) && ((*(byte *)(*(int *)(tmp_i1 + -0xc) + 5) & 3) != 0)) &&
     ((*(byte *)(*tmp_pi5 + 5) & 4) != 0)) {
    luaC_barrierback(param_1,*tmp_pi5);
    tmp_i1 = *(int *)(param_1 + 8);
  }
  *(int *)(param_1 + 8) = tmp_i1 + -0x18;
  return;
}

void lua_rawseti(int param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int *tmp_pi4;
  int *tmp_pi5;
  
  tmp_i1 = luaO_nilobject_;
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_pi5 = (int *)(param_1 + 0x54);
        tmp_pi4 = *(int **)(param_1 + 8);
        tmp_i1 = *(int *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(int *)(param_1 + 0x54) = tmp_i1;
      }
      else if (param_2 == -10000) {
        tmp_pi4 = *(int **)(param_1 + 8);
        tmp_pi5 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i1 = *(int *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_pi5 = (int *)(param_1 + 0x48);
        tmp_i1 = *(int *)(param_1 + 0x48);
        tmp_pi4 = *(int **)(param_1 + 8);
      }
      else {
        tmp_i3 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i3 + 7) < -0x2712 - param_2) {
          tmp_pi5 = &luaO_nilobject_;
          tmp_pi4 = *(int **)(param_1 + 8);
        }
        else {
          tmp_pi4 = *(int **)(param_1 + 8);
          tmp_i3 = tmp_i3 + (-0x2713 - param_2) * 0xc + 0x10;
          tmp_pi5 = (int *)(tmp_i3 + 4);
          tmp_i1 = *(int *)(tmp_i3 + 4);
        }
      }
      goto LAB_00204796;
    }
    tmp_pi4 = *(int **)(param_1 + 8);
    tmp_pi5 = tmp_pi4 + param_2 * 3;
  }
  else {
    tmp_pi4 = *(int **)(param_1 + 8);
    tmp_pi5 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi4 <= tmp_pi5) {
      tmp_pi5 = &luaO_nilobject_;
      goto LAB_00204796;
    }
  }
  tmp_i1 = *tmp_pi5;
LAB_00204796:
  tmp_pi2 = (int *)luaH_setnum(param_1,tmp_i1,param_3);
  tmp_i1 = tmp_pi4[-2];
  *tmp_pi2 = tmp_pi4[-3];
  tmp_pi2[1] = tmp_i1;
  tmp_pi2[2] = tmp_pi4[-1];
  tmp_i1 = *(int *)(param_1 + 8);
  if (((3 < *(int *)(tmp_i1 + -4)) && ((*(byte *)(*(int *)(tmp_i1 + -0xc) + 5) & 3) != 0)) &&
     ((*(byte *)(*tmp_pi5 + 5) & 4) != 0)) {
    luaC_barrierback(param_1,*tmp_pi5);
    tmp_i1 = *(int *)(param_1 + 8);
  }
  *(int *)(param_1 + 8) = tmp_i1 + -0xc;
  return;
}

uint32_t lua_setmetatable(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  int tmp_i3;
  int *tmp_pi4;
  int tmp_i5;
  
  tmp_i3 = g_unk_002701c8;
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi4 = *(int **)(param_1 + 8);
      tmp_pi2 = tmp_pi4 + param_2 * 3;
      goto LAB_00204940;
    }
    if (param_2 != -0x2711) {
      if (param_2 == -10000) {
        tmp_pi2 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
        tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
        tmp_pi4 = *(int **)(param_1 + 8);
      }
      else if (param_2 == -0x2712) {
        tmp_pi2 = (int *)(param_1 + 0x48);
        tmp_i3 = *(int *)(param_1 + 0x50);
        tmp_pi4 = *(int **)(param_1 + 8);
      }
      else {
        tmp_i5 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i5 + 7) < -0x2712 - param_2) {
          tmp_pi2 = &luaO_nilobject_;
          tmp_pi4 = *(int **)(param_1 + 8);
        }
        else {
          tmp_pi4 = *(int **)(param_1 + 8);
          tmp_i5 = tmp_i5 + (-0x2713 - param_2) * 0xc + 0x10;
          tmp_pi2 = (int *)(tmp_i5 + 4);
          tmp_i3 = *(int *)(tmp_i5 + 0xc);
        }
      }
      goto LAB_00204943;
    }
    tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
    *(uint32_t *)(param_1 + 0x5c) = 5;
    *(uint32_t *)(param_1 + 0x54) = tmp_u1;
    tmp_pi2 = (int *)(param_1 + 0x54);
    if (*(int *)(*(int *)(param_1 + 8) + -4) == 0) goto LAB_002049ad;
    tmp_i5 = *(int *)(*(int *)(param_1 + 8) + -0xc);
LAB_00204a10:
    *(int *)(*tmp_pi2 + 8) = tmp_i5;
    if (((tmp_i5 != 0) && ((*(byte *)(tmp_i5 + 5) & 3) != 0)) && ((*(byte *)(*tmp_pi2 + 5) & 4) != 0))
    {
      luaC_barrierback(param_1,*tmp_pi2);
    }
  }
  else {
    tmp_pi4 = *(int **)(param_1 + 8);
    tmp_pi2 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi2 < tmp_pi4) {
LAB_00204940:
      tmp_i3 = tmp_pi2[2];
LAB_00204943:
      if (tmp_pi4[-1] != 0) goto LAB_0020494a;
LAB_002049a3:
      if ((tmp_i3 == 5) || (tmp_i3 == 7)) {
LAB_002049ad:
        *(uint32_t *)(*tmp_pi2 + 8) = 0;
        goto LAB_002049cc;
      }
      tmp_i5 = 0;
    }
    else {
      tmp_pi2 = &luaO_nilobject_;
      if (tmp_pi4[-1] == 0) goto LAB_002049a3;
LAB_0020494a:
      tmp_i5 = tmp_pi4[-3];
      if (tmp_i3 == 5) goto LAB_00204a10;
      if (tmp_i3 == 7) {
        *(int *)(*tmp_pi2 + 8) = tmp_i5;
        if (((tmp_i5 != 0) && ((*(byte *)(tmp_i5 + 5) & 3) != 0)) &&
           ((*(byte *)(*tmp_pi2 + 5) & 4) != 0)) {
          luaC_barrierf(param_1,*tmp_pi2,tmp_i5);
        }
        goto LAB_002049cc;
      }
    }
    *(int *)(*(int *)(param_1 + 0x10) + 0x84 + tmp_i3 * 4) = tmp_i5;
  }
LAB_002049cc:
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0xc;
  return 1;
}

uint32_t lua_setfenv(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  uint32_t local_10;
  
  tmp_i3 = g_unk_002701c8;
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi5 = *(int **)(param_1 + 8);
      tmp_pi2 = tmp_pi5 + param_2 * 3;
      goto LAB_00204b30;
    }
    if (param_2 == -0x2711) {
      tmp_pi5 = *(int **)(param_1 + 8);
      tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u1;
      local_10 = 0;
      goto LAB_00204b48;
    }
    if (param_2 == -10000) {
      tmp_pi2 = (int *)(*(int *)(param_1 + 0x10) + 0x5c);
      tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 100);
      tmp_pi5 = *(int **)(param_1 + 8);
    }
    else if (param_2 == -0x2712) {
      tmp_pi2 = (int *)(param_1 + 0x48);
      tmp_i3 = *(int *)(param_1 + 0x50);
      tmp_pi5 = *(int **)(param_1 + 8);
    }
    else {
      tmp_i4 = **(int **)(*(int *)(param_1 + 0x14) + 4);
      if ((int)(uint)*(byte *)(tmp_i4 + 7) < -0x2712 - param_2) {
        tmp_pi2 = &luaO_nilobject_;
        tmp_pi5 = *(int **)(param_1 + 8);
      }
      else {
        tmp_pi5 = *(int **)(param_1 + 8);
        tmp_i4 = tmp_i4 + (-0x2713 - param_2) * 0xc + 0x10;
        tmp_pi2 = (int *)(tmp_i4 + 4);
        tmp_i3 = *(int *)(tmp_i4 + 0xc);
      }
    }
LAB_00204b33:
    if (tmp_i3 == 7) goto LAB_00204b71;
LAB_00204b38:
    if (tmp_i3 != 8) {
      if (tmp_i3 != 6) {
        local_10 = 0;
        goto LAB_00204b48;
      }
      goto LAB_00204b71;
    }
    tmp_i3 = *tmp_pi2;
    tmp_i4 = tmp_pi5[-3];
    *(uint32_t *)(tmp_i3 + 0x50) = 5;
    *(int *)(tmp_i3 + 0x48) = tmp_i4;
  }
  else {
    tmp_pi2 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pi5 = *(int **)(param_1 + 8);
    if (tmp_pi2 < tmp_pi5) {
LAB_00204b30:
      tmp_i3 = tmp_pi2[2];
      goto LAB_00204b33;
    }
    tmp_pi2 = &luaO_nilobject_;
    if (g_unk_002701c8 != 7) goto LAB_00204b38;
LAB_00204b71:
    *(int *)(*tmp_pi2 + 0xc) = tmp_pi5[-3];
  }
  tmp_pi5 = *(int **)(param_1 + 8);
  if ((*(byte *)(tmp_pi5[-3] + 5) & 3) == 0) {
    local_10 = 1;
  }
  else {
    local_10 = 1;
    if ((*(byte *)(*tmp_pi2 + 5) & 4) != 0) {
      local_10 = 1;
      luaC_barrierf(param_1,*tmp_pi2,tmp_pi5[-3]);
      tmp_pi5 = *(int **)(param_1 + 8);
    }
  }
LAB_00204b48:
  *(int **)(param_1 + 8) = tmp_pi5 + -3;
  return local_10;
}

void lua_call(int param_1,int param_2,int param_3)
{
  luaD_call(param_1,param_2 * -0xc + -0xc + *(int *)(param_1 + 8),param_3);
  if (param_3 == -1) {
    if (*(uint *)(*(int *)(param_1 + 0x14) + 8) <= *(uint *)(param_1 + 8)) {
      *(uint *)(*(int *)(param_1 + 0x14) + 8) = *(uint *)(param_1 + 8);
      return;
    }
  }
  return;
}

void lua_pcall(int param_1,int param_2,int param_3,int param_4)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *local_24;
  int local_20;
  
  if (param_4 == 0) {
    tmp_i4 = *(int *)(param_1 + 0x20);
    local_24 = *(uint32_t **)(param_1 + 8);
    tmp_i3 = 0;
  }
  else {
    if (param_4 < 1) {
      if (param_4 < -9999) {
        if (param_4 == -0x2711) {
          local_24 = *(uint32_t **)(param_1 + 8);
          tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
          *(uint32_t *)(param_1 + 0x5c) = 5;
          *(uint32_t *)(param_1 + 0x54) = tmp_u1;
          tmp_pu2 = (uint32_t *)(param_1 + 0x54);
        }
        else if (param_4 == -10000) {
          tmp_pu2 = (uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
          local_24 = *(uint32_t **)(param_1 + 8);
        }
        else if (param_4 == -0x2712) {
          tmp_pu2 = (uint32_t *)(param_1 + 0x48);
          local_24 = *(uint32_t **)(param_1 + 8);
        }
        else {
          tmp_i4 = **(int **)(*(int *)(param_1 + 0x14) + 4);
          if ((int)(uint)*(byte *)(tmp_i4 + 7) < -0x2712 - param_4) {
            local_24 = *(uint32_t **)(param_1 + 8);
            tmp_pu2 = &luaO_nilobject_;
          }
          else {
            tmp_pu2 = (uint32_t *)(tmp_i4 + 0x14 + (-0x2713 - param_4) * 0xc);
            local_24 = *(uint32_t **)(param_1 + 8);
          }
        }
      }
      else {
        local_24 = *(uint32_t **)(param_1 + 8);
        tmp_pu2 = local_24 + param_4 * 3;
      }
    }
    else {
      tmp_pu2 = (uint32_t *)(param_4 * 0xc + -0xc + *(int *)(param_1 + 0xc));
      local_24 = *(uint32_t **)(param_1 + 8);
      if (local_24 <= tmp_pu2) {
        tmp_pu2 = &luaO_nilobject_;
      }
    }
    tmp_i4 = *(int *)(param_1 + 0x20);
    tmp_i3 = (int)tmp_pu2 - tmp_i4;
  }
  local_24 = local_24 + param_2 * -3 + -3;
  local_20 = param_3;
  luaD_pcall(param_1,f_call,&local_24,(int)local_24 - tmp_i4,tmp_i3);
  if (param_3 == -1) {
    if (*(uint *)(*(int *)(param_1 + 0x14) + 8) <= *(uint *)(param_1 + 8)) {
      *(uint *)(*(int *)(param_1 + 0x14) + 8) = *(uint *)(param_1 + 8);
    }
  }
  return;
}

void lua_cpcall(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t local_14;
  uint32_t local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  luaD_pcall(param_1,f_Ccall,&local_14,*(int *)(param_1 + 8) - *(int *)(param_1 + 0x20),0);
  return;
}

void lua_load(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint8_t *param_4)
{
  uint8_t local_30 [32];
  
  if (param_4 == (uint8_t *)0x0) {
    param_4 = &g_unk_0026f751;
  }
  luaZ_init(param_1,local_30,param_2,param_3);
  luaD_protectedparser(param_1,local_30,param_4);
  return;
}

void lua_dump(int param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  
  if ((*(int *)(*(int *)(param_1 + 8) + -4) == 6) &&
     (tmp_i1 = *(int *)(*(int *)(param_1 + 8) + -0xc), *(char *)(tmp_i1 + 6) == '\0')) {
    luaU_dump(param_1,*(uint32_t *)(tmp_i1 + 0x10),param_2,param_3,0);
    return;
  }
  return;
}

uint8_t lua_status(int param_1)
{
  return *(uint8_t *)(param_1 + 6);
}

uint lua_gc(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  
  tmp_i1 = *(int *)(param_1 + 0x10);
  switch(param_2) {
  case 0:
    *(uint32_t *)(tmp_i1 + 0x40) = 0xfffffffd;
    return 0;
  case 1:
    *(uint32_t *)(tmp_i1 + 0x40) = *(uint32_t *)(tmp_i1 + 0x44);
    return 0;
  case 2:
    luaC_fullgc(param_1);
    return 0;
  case 3:
    return *(uint *)(tmp_i1 + 0x44) >> 10;
  case 4:
    return *(uint *)(tmp_i1 + 0x44) & 0x3ff;
  case 5:
    tmp_u3 = *(uint *)(tmp_i1 + 0x44);
    tmp_u2 = tmp_u3 + param_3 * -0x400;
    if (tmp_u3 < (uint)(param_3 * 0x400)) {
      tmp_u2 = 0;
    }
    *(uint *)(tmp_i1 + 0x40) = tmp_u2;
    while (tmp_u2 <= tmp_u3) {
      luaC_step(param_1);
      if (*(char *)(tmp_i1 + 0x15) == '\0') {
        return 1;
      }
      tmp_u3 = *(uint *)(tmp_i1 + 0x44);
      tmp_u2 = *(uint *)(tmp_i1 + 0x40);
    }
    tmp_u3 = 0;
    break;
  case 6:
    tmp_u3 = *(uint *)(tmp_i1 + 0x50);
    *(int *)(tmp_i1 + 0x50) = param_3;
    break;
  case 7:
    tmp_u3 = *(uint *)(tmp_i1 + 0x54);
    *(int *)(tmp_i1 + 0x54) = param_3;
    return tmp_u3;
  default:
    tmp_u3 = 0xffffffff;
  }
  return tmp_u3;
}

uint32_t lua_error(uint32_t param_1)
{
  luaG_errormsg(param_1);
  return 0;
}

void lua_next(int param_1,int param_2)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  
  tmp_u4 = luaO_nilobject_;
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_u4 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        tmp_pu1 = *(uint32_t **)(param_1 + 8);
        *(uint32_t *)(param_1 + 0x54) = tmp_u4;
      }
      else if (param_2 == -10000) {
        tmp_pu1 = *(uint32_t **)(param_1 + 8);
        tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x10) + 0x5c);
      }
      else if (param_2 == -0x2712) {
        tmp_pu1 = *(uint32_t **)(param_1 + 8);
        tmp_u4 = *(uint32_t *)(param_1 + 0x48);
      }
      else {
        tmp_i2 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        tmp_pu1 = *(uint32_t **)(param_1 + 8);
        if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i2 + 7)) {
          tmp_u4 = *(uint32_t *)(tmp_i2 + 0x14 + (-0x2713 - param_2) * 0xc);
        }
      }
    }
    else {
      tmp_pu1 = *(uint32_t **)(param_1 + 8);
      tmp_u4 = tmp_pu1[param_2 * 3];
    }
  }
  else {
    tmp_pu3 = (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    tmp_pu1 = *(uint32_t **)(param_1 + 8);
    if (tmp_pu3 < tmp_pu1) {
      tmp_u4 = *tmp_pu3;
    }
  }
  tmp_i2 = luaH_next(param_1,tmp_u4,tmp_pu1 + -3);
  if (tmp_i2 == 0) {
    tmp_i2 = *(int *)(param_1 + 8) + -0xc;
  }
  else {
    tmp_i2 = *(int *)(param_1 + 8) + 0xc;
  }
  *(int *)(param_1 + 8) = tmp_i2;
  return;
}

void lua_concat(int param_1,int param_2)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  
  if (param_2 < 2) {
    if (param_2 == 0) {
      tmp_pu1 = *(uint32_t **)(param_1 + 8);
      tmp_u2 = luaS_newlstr(param_1,&g_unk_0026ea14,0);
      tmp_pu1[2] = 4;
      *tmp_pu1 = tmp_u2;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
      return;
    }
  }
  else {
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      luaC_step(param_1);
    }
    luaV_concat(param_1,param_2,
                (*(int *)(param_1 + 8) - *(int *)(param_1 + 0xc) >> 2) * -0x55555555 + -1);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + param_2 * -0xc + 0xc;
  }
  return;
}

uint32_t lua_getallocf(int param_1,uint32_t *param_2)
{
  if (param_2 != (uint32_t *)0x0) {
    *param_2 = *(uint32_t *)(*(int *)(param_1 + 0x10) + 0x10);
  }
  return *(uint32_t *)(*(int *)(param_1 + 0x10) + 0xc);
}

void lua_setallocf(int param_1,uint32_t param_2,uint32_t param_3)
{
  *(uint32_t *)(*(int *)(param_1 + 0x10) + 0x10) = param_3;
  *(uint32_t *)(*(int *)(param_1 + 0x10) + 0xc) = param_2;
  return;
}

int lua_newuserdata(int param_1,uint32_t param_2)
{
  int *tmp_pi1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x44) < *(uint *)(*(int *)(param_1 + 0x10) + 0x40)) {
    tmp_i3 = *(int *)(param_1 + 0x14);
    if (tmp_i3 == *(int *)(param_1 + 0x28)) {
LAB_00205460:
      tmp_u2 = *(uint32_t *)(param_1 + 0x48);
      goto LAB_00205423;
    }
  }
  else {
    luaC_step(param_1);
    tmp_i3 = *(int *)(param_1 + 0x14);
    if (tmp_i3 == *(int *)(param_1 + 0x28)) goto LAB_00205460;
  }
  tmp_u2 = *(uint32_t *)(**(int **)(tmp_i3 + 4) + 0xc);
LAB_00205423:
  tmp_i3 = luaS_newudata(param_1,param_2,tmp_u2);
  tmp_pi1 = *(int **)(param_1 + 8);
  tmp_pi1[2] = 7;
  *tmp_pi1 = tmp_i3;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
  return tmp_i3 + 0x14;
}

uint8_t * lua_getupvalue(int param_1,int param_2,int param_3)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  int *tmp_pi6;
  uint32_t *tmp_pu7;
  int tmp_i8;
  
  tmp_i3 = luaO_nilobject_;
  tmp_i4 = g_unk_002701c8;
  if (param_2 < 1) {
    if (-10000 < param_2) {
      tmp_pi6 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      goto LAB_002054b9;
    }
    if (param_2 == -0x2711) {
      tmp_u1 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
      *(uint32_t *)(param_1 + 0x5c) = 5;
      *(uint32_t *)(param_1 + 0x54) = tmp_u1;
      return (uint8_t *)0x0;
    }
    if (param_2 == -10000) {
      tmp_i3 = *(int *)(*(int *)(param_1 + 0x10) + 0x5c);
      tmp_i4 = *(int *)(*(int *)(param_1 + 0x10) + 100);
    }
    else if (param_2 == -0x2712) {
      tmp_i3 = *(int *)(param_1 + 0x48);
      tmp_i4 = *(int *)(param_1 + 0x50);
    }
    else {
      tmp_i8 = **(int **)(*(int *)(param_1 + 0x14) + 4);
      if (-0x2712 - param_2 <= (int)(uint)*(byte *)(tmp_i8 + 7)) {
        tmp_i8 = tmp_i8 + (-0x2713 - param_2) * 0xc + 0x10;
        tmp_i3 = *(int *)(tmp_i8 + 4);
        tmp_i4 = *(int *)(tmp_i8 + 0xc);
      }
    }
  }
  else {
    tmp_pi6 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (tmp_pi6 < *(int **)(param_1 + 8)) {
LAB_002054b9:
      tmp_i3 = *tmp_pi6;
      tmp_i4 = tmp_pi6[2];
    }
  }
  if (tmp_i4 == 6) {
    if (*(char *)(tmp_i3 + 6) == '\0') {
      if ((0 < param_3) && (param_3 <= *(int *)(*(int *)(tmp_i3 + 0x10) + 0x24))) {
        tmp_pu7 = *(uint32_t **)(*(int *)(tmp_i3 + 0x10 + param_3 * 4) + 8);
        tmp_pu5 = (uint8_t *)
                 (*(int *)(*(int *)(*(int *)(tmp_i3 + 0x10) + 0x1c) + (param_3 + 0x3fffffff) * 4) +
                 0x10);
        if (tmp_pu5 == (uint8_t *)0x0) {
          return (uint8_t *)0x0;
        }
        goto LAB_002054f3;
      }
    }
    else if ((0 < param_3) && (param_3 <= (int)(uint)*(byte *)(tmp_i3 + 7))) {
      tmp_pu7 = (uint32_t *)(tmp_i3 + 0x14 + (param_3 * 3 + -3) * 4);
      tmp_pu5 = &g_unk_0026ea14;
LAB_002054f3:
      tmp_u1 = tmp_pu7[1];
      tmp_pu2 = *(uint32_t **)(param_1 + 8);
      *tmp_pu2 = *tmp_pu7;
      tmp_pu2[1] = tmp_u1;
      tmp_pu2[2] = tmp_pu7[2];
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0xc;
      return tmp_pu5;
    }
  }
  return (uint8_t *)0x0;
}

uint8_t * lua_setupvalue(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int *local_20;
  
  tmp_i3 = luaO_nilobject_;
  tmp_i1 = g_unk_002701c8;
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2711) {
        tmp_u2 = *(uint32_t *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(uint32_t *)(param_1 + 0x5c) = 5;
        *(uint32_t *)(param_1 + 0x54) = tmp_u2;
        return (uint8_t *)0x0;
      }
      if (param_2 == -10000) {
        tmp_i1 = *(int *)(param_1 + 0x10);
        local_20 = (int *)(tmp_i1 + 0x5c);
        tmp_i3 = *(int *)(tmp_i1 + 0x5c);
        tmp_i1 = *(int *)(tmp_i1 + 100);
      }
      else if (param_2 == -0x2712) {
        local_20 = (int *)(param_1 + 0x48);
        tmp_i1 = *(int *)(param_1 + 0x50);
        tmp_i3 = *(int *)(param_1 + 0x48);
      }
      else {
        tmp_i6 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        if ((int)(uint)*(byte *)(tmp_i6 + 7) < -0x2712 - param_2) {
          local_20 = &luaO_nilobject_;
        }
        else {
          tmp_i6 = tmp_i6 + (-0x2713 - param_2) * 0xc + 0x10;
          local_20 = (int *)(tmp_i6 + 4);
          tmp_i3 = *(int *)(tmp_i6 + 4);
          tmp_i1 = *(int *)(tmp_i6 + 0xc);
        }
      }
    }
    else {
      local_20 = (int *)(*(int *)(param_1 + 8) + param_2 * 0xc);
      tmp_i3 = *local_20;
      tmp_i1 = local_20[2];
    }
  }
  else {
    local_20 = (int *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
    if (local_20 < *(int **)(param_1 + 8)) {
      tmp_i3 = *local_20;
      tmp_i1 = local_20[2];
    }
    else {
      local_20 = &luaO_nilobject_;
    }
  }
  if (tmp_i1 == 6) {
    if (*(char *)(tmp_i3 + 6) == '\0') {
      if ((0 < param_3) && (param_3 <= *(int *)(*(int *)(tmp_i3 + 0x10) + 0x24))) {
        tmp_pu5 = *(uint32_t **)(*(int *)(tmp_i3 + 0x10 + param_3 * 4) + 8);
        tmp_pu4 = (uint8_t *)
                 (*(int *)(*(int *)(*(int *)(tmp_i3 + 0x10) + 0x1c) + (param_3 + 0x3fffffff) * 4) +
                 0x10);
        if (tmp_pu4 == (uint8_t *)0x0) {
          return (uint8_t *)0x0;
        }
        goto LAB_002056b8;
      }
    }
    else if ((0 < param_3) && (param_3 <= (int)(uint)*(byte *)(tmp_i3 + 7))) {
      tmp_pu5 = (uint32_t *)(tmp_i3 + 0x14 + (param_3 * 3 + -3) * 4);
      tmp_pu4 = &g_unk_0026ea14;
LAB_002056b8:
      tmp_i1 = *(int *)(param_1 + 8);
      *(int *)(param_1 + 8) = tmp_i1 + -0xc;
      tmp_u2 = *(uint32_t *)(tmp_i1 + -8);
      *tmp_pu5 = *(uint32_t *)(tmp_i1 + -0xc);
      tmp_pu5[1] = tmp_u2;
      tmp_pu5[2] = *(uint32_t *)(tmp_i1 + -4);
      if ((*(int **)(param_1 + 8))[2] < 4) {
        return tmp_pu4;
      }
      tmp_i1 = **(int **)(param_1 + 8);
      if ((*(byte *)(tmp_i1 + 5) & 3) == 0) {
        return tmp_pu4;
      }
      if ((*(byte *)(*local_20 + 5) & 4) == 0) {
        return tmp_pu4;
      }
      luaC_barrierf(param_1,*local_20,tmp_i1);
      return tmp_pu4;
    }
  }
  return (uint8_t *)0x0;
}

void luaS_resize(int param_1,int param_2)
{
  int *tmp_pi1;
  int *tmp_pi2;
  uint32_t *tmp_pu3;
  int *tmp_pi4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  int tmp_i9;
  uint32_t *tmp_pu10;
  byte tmp_b11;
  
  tmp_b11 = 0;
  if (*(char *)(*(int *)(param_1 + 0x10) + 0x15) != '\x02') {
    if (param_2 + 1U < 0x40000000) {
      tmp_pu3 = (uint32_t *)luaM_realloc_(param_1,0,0,param_2 << 2);
    }
    else {
      tmp_pu3 = (uint32_t *)luaM_toobig(param_1);
    }
    tmp_pi1 = *(int **)(param_1 + 0x10);
    if (0 < param_2) {
      tmp_u8 = param_2 * 4;
      tmp_pu10 = tmp_pu3;
      if (7 < tmp_u8) {
        tmp_u6 = tmp_u8;
        if (((uint)tmp_pu3 & 1) != 0) {
          *(uint8_t *)tmp_pu3 = 0;
          tmp_pu10 = (uint32_t *)((int)tmp_pu3 + 1);
          tmp_u6 = tmp_u8 - 1;
        }
        if (((uint)tmp_pu10 & 2) != 0) {
          *(uint16_t *)tmp_pu10 = 0;
          tmp_u6 = tmp_u6 - 2;
          tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
        }
        if (((uint)tmp_pu10 & 4) != 0) {
          *tmp_pu10 = 0;
          tmp_u6 = tmp_u6 - 4;
          tmp_pu10 = tmp_pu10 + 1;
        }
        tmp_u8 = tmp_u6 & 3;
        for (tmp_u6 = tmp_u6 >> 2; tmp_u6 != 0; tmp_u6 = tmp_u6 - 1) {
          *tmp_pu10 = 0;
          tmp_pu10 = tmp_pu10 + (uint)tmp_b11 * -2 + 1;
        }
      }
      if ((tmp_u8 & 4) != 0) {
        *tmp_pu10 = 0;
        tmp_pu10 = tmp_pu10 + 1;
      }
      if ((tmp_u8 & 2) != 0) {
        *(uint16_t *)tmp_pu10 = 0;
        tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
      }
      if ((tmp_u8 & 1) != 0) {
        *(uint8_t *)tmp_pu10 = 0;
      }
    }
    tmp_i7 = tmp_pi1[2];
    if (tmp_i7 < 1) {
      tmp_i5 = *tmp_pi1;
    }
    else {
      tmp_i5 = *tmp_pi1;
      tmp_i9 = 0;
      do {
        tmp_pi4 = *(int **)(tmp_i5 + tmp_i9 * 4);
        if (tmp_pi4 != (int *)0x0) {
          do {
            tmp_pi2 = (int *)*tmp_pi4;
            *tmp_pi4 = tmp_pu3[tmp_pi4[2] & param_2 - 1U];
            tmp_pu3[tmp_pi4[2] & param_2 - 1U] = tmp_pi4;
            tmp_pi4 = tmp_pi2;
          } while (tmp_pi2 != (int *)0x0);
          tmp_i5 = *tmp_pi1;
          tmp_i7 = tmp_pi1[2];
        }
        tmp_i9 = tmp_i9 + 1;
      } while (tmp_i9 < tmp_i7);
    }
    luaM_realloc_(param_1,tmp_i5,tmp_i7 << 2,0);
    *tmp_pi1 = (int)tmp_pu3;
    tmp_pi1[2] = param_2;
  }
  return;
}

uint32_t * luaS_newlstr(int param_1,uint32_t *param_2,uint param_3)
{
  byte tmp_b1;
  uint8_t tmp_u2;
  uint16_t tmp_u3;
  int *tmp_pi4;
  uint32_t tmp_u5;
  bool tmp_b6;
  uint tmp_u7;
  int tmp_i8;
  uint32_t *tmp_pu9;
  uint tmp_u10;
  uint tmp_u11;
  uint tmp_u12;
  uint32_t *tmp_pu13;
  uint32_t *tmp_pu14;
  byte tmp_b15;
  
  tmp_b15 = 0;
  tmp_u7 = param_3 >> 5;
  tmp_u11 = tmp_u7 + 1;
  tmp_u12 = param_3;
  if (tmp_u11 <= param_3) {
    tmp_u10 = (param_3 - tmp_u7) - 1;
    do {
      tmp_u12 = tmp_u12 ^ (uint)*(byte *)((int)param_2 + tmp_u10 + tmp_u7) +
                        (tmp_u12 >> 2) + tmp_u12 * 0x20;
      tmp_b6 = tmp_u11 <= tmp_u10;
      tmp_u10 = tmp_u10 - tmp_u11;
    } while (tmp_b6);
  }
  tmp_pi4 = *(int **)(param_1 + 0x10);
  for (tmp_pu13 = *(uint32_t **)(*tmp_pi4 + (tmp_pi4[2] - 1U & tmp_u12) * 4);
      tmp_pu13 != (uint32_t *)0x0; tmp_pu13 = (uint32_t *)*tmp_pu13) {
    if ((tmp_pu13[3] == param_3) && (tmp_i8 = memcmp(param_2,tmp_pu13 + 4,param_3), tmp_i8 == 0)) {
      if ((*(byte *)((int)tmp_pu13 + 5) & 3 & (*(byte *)(tmp_pi4 + 5) ^ 3)) == 0) {
        return tmp_pu13;
      }
      *(byte *)((int)tmp_pu13 + 5) = *(byte *)((int)tmp_pu13 + 5) ^ 3;
      return tmp_pu13;
    }
  }
  if (0xffffffed < param_3 + 1) {
    luaM_toobig(param_1);
  }
  tmp_pu9 = (uint32_t *)luaM_realloc_(param_1,0,0,param_3 + 0x11);
  tmp_pu9[3] = param_3;
  tmp_pu13 = tmp_pu9 + 4;
  tmp_pu9[2] = tmp_u12;
  tmp_b1 = *(byte *)(*(int *)(param_1 + 0x10) + 0x14);
  *(uint8_t *)(tmp_pu9 + 1) = 4;
  *(uint8_t *)((int)tmp_pu9 + 6) = 0;
  *(byte *)((int)tmp_pu9 + 5) = tmp_b1 & 3;
  tmp_u11 = param_3;
  if (7 < param_3) {
    if (((uint)tmp_pu13 & 1) != 0) {
      tmp_u2 = *(uint8_t *)param_2;
      tmp_pu13 = (uint32_t *)((int)tmp_pu9 + 0x11);
      param_2 = (uint32_t *)((int)param_2 + 1);
      *(uint8_t *)(tmp_pu9 + 4) = tmp_u2;
      tmp_u11 = param_3 - 1;
    }
    tmp_pu14 = tmp_pu13;
    if (((uint)tmp_pu13 & 2) != 0) {
      tmp_u3 = *(uint16_t *)param_2;
      tmp_pu14 = (uint32_t *)((int)tmp_pu13 + 2);
      param_2 = (uint32_t *)((int)param_2 + 2);
      tmp_u11 = tmp_u11 - 2;
      *(uint16_t *)tmp_pu13 = tmp_u3;
    }
    tmp_pu13 = tmp_pu14;
    if (((uint)tmp_pu14 & 4) != 0) {
      tmp_u5 = *param_2;
      tmp_pu13 = tmp_pu14 + 1;
      param_2 = param_2 + 1;
      tmp_u11 = tmp_u11 - 4;
      *tmp_pu14 = tmp_u5;
    }
  }
  for (; tmp_u11 != 0; tmp_u11 = tmp_u11 - 1) {
    *(uint8_t *)tmp_pu13 = *(uint8_t *)param_2;
    param_2 = (uint32_t *)((int)param_2 + (uint)tmp_b15 * -2 + 1);
    tmp_pu13 = (uint32_t *)((int)tmp_pu13 + (uint)tmp_b15 * -2 + 1);
  }
  *(uint8_t *)((int)tmp_pu9 + param_3 + 0x10) = 0;
  tmp_pi4 = *(int **)(param_1 + 0x10);
  tmp_i8 = (tmp_u12 & tmp_pi4[2] - 1U) * 4;
  *tmp_pu9 = *(uint32_t *)(*tmp_pi4 + tmp_i8);
  *(uint32_t **)(*tmp_pi4 + tmp_i8) = tmp_pu9;
  tmp_i8 = tmp_pi4[1];
  tmp_pi4[1] = tmp_i8 + 1U;
  tmp_u11 = tmp_pi4[2];
  if ((tmp_u11 < tmp_i8 + 1U) && ((int)tmp_u11 < 0x3fffffff)) {
    luaS_resize(param_1,tmp_u11 * 2);
    return tmp_pu9;
  }
  return tmp_pu9;
}

void luaS_newudata(int param_1,uint param_2,uint32_t param_3)
{
  byte tmp_b1;
  uint32_t *tmp_pu2;
  
  if (0xffffffe9 < param_2) {
    luaM_toobig(param_1);
  }
  tmp_pu2 = (uint32_t *)luaM_realloc_(param_1,0,0,param_2 + 0x14);
  tmp_b1 = *(byte *)(*(int *)(param_1 + 0x10) + 0x14);
  *(uint8_t *)(tmp_pu2 + 1) = 7;
  tmp_pu2[4] = param_2;
  *(byte *)((int)tmp_pu2 + 5) = tmp_b1 & 3;
  tmp_pu2[2] = 0;
  tmp_pu2[3] = param_3;
  *tmp_pu2 = **(uint32_t **)(*(int *)(param_1 + 0x10) + 0x68);
  **(uint32_t **)(*(int *)(param_1 + 0x10) + 0x68) = tmp_pu2;
  return;
}

uint32_t luaopen_string(uint32_t param_1)
{
  luaL_register(param_1,"string",strlib);
  lua_getfield(param_1,0xffffffff,"gmatch");
  lua_setfield(param_1,0xfffffffe,"gfind");
  lua_createtable(param_1,0,1);
  lua_pushlstring(param_1,&g_unk_0026ea14,0);
  lua_pushvalue(param_1,0xfffffffe);
  lua_setmetatable(param_1,0xfffffffe);
  lua_settop(param_1,0xfffffffe);
  lua_pushvalue(param_1,0xfffffffe);
  lua_setfield(param_1,0xfffffffe,"__index");
  lua_settop(param_1,0xfffffffe);
  return 1;
}

void luaK_code(int *param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i1 = *param_1;
  patchlistaux(param_1[6],0xff,param_1[6]);
  tmp_i3 = param_1[6];
  param_1[8] = -1;
  if (tmp_i3 < *(int *)(tmp_i1 + 0x2c)) {
    tmp_i2 = *(int *)(tmp_i1 + 0xc);
  }
  else {
    tmp_i2 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i1 + 0xc),tmp_i1 + 0x2c,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i1 + 0xc) = tmp_i2;
    tmp_i3 = param_1[6];
  }
  *(uint32_t *)(tmp_i2 + tmp_i3 * 4) = param_2;
  tmp_i3 = param_1[6];
  if (tmp_i3 < *(int *)(tmp_i1 + 0x30)) {
    tmp_i2 = *(int *)(tmp_i1 + 0x14);
  }
  else {
    tmp_i2 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i1 + 0x14),tmp_i1 + 0x30,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i1 + 0x14) = tmp_i2;
    tmp_i3 = param_1[6];
  }
  *(uint32_t *)(tmp_i2 + tmp_i3 * 4) = param_3;
  param_1[6] = param_1[6] + 1;
  return;
}

void luaK_nil(int *param_1,int param_2,int param_3)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  uint *tmp_pu4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_i5 = param_1[6];
  if (param_1[7] < tmp_i5) {
    if (tmp_i5 != 0) {
      tmp_i6 = *param_1;
      tmp_pu4 = (uint *)(*(int *)(tmp_i6 + 0xc) + tmp_i5 * 4 + -4);
      tmp_u2 = *tmp_pu4;
      if ((((tmp_u2 & 0x3f) == 3) && ((int)(tmp_u2 >> 6 & 0xff) <= param_2)) &&
         (param_2 <= (int)((tmp_u2 >> 0x17) + 1))) {
        param_3 = param_2 + -1 + param_3;
        if (param_3 <= (int)(tmp_u2 >> 0x17)) {
          return;
        }
        *tmp_pu4 = tmp_u2 & 0x7fffff | param_3 * 0x800000;
        return;
      }
      goto LAB_00209780;
    }
    if ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2) {
      return;
    }
  }
  tmp_i6 = *param_1;
LAB_00209780:
  tmp_u1 = *(uint32_t *)(param_1[3] + 8);
  patchlistaux(tmp_i5,0xff,tmp_i5);
  tmp_i5 = param_1[6];
  param_1[8] = -1;
  if (tmp_i5 < *(int *)(tmp_i6 + 0x2c)) {
    tmp_i3 = *(int *)(tmp_i6 + 0xc);
  }
  else {
    tmp_i3 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i6 + 0xc),tmp_i6 + 0x2c,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i6 + 0xc) = tmp_i3;
    tmp_i5 = param_1[6];
  }
  *(uint *)(tmp_i3 + tmp_i5 * 4) = param_2 << 6 | 3U | (param_2 + -1 + param_3) * 0x800000;
  tmp_i5 = param_1[6];
  if (tmp_i5 < *(int *)(tmp_i6 + 0x30)) {
    tmp_i3 = *(int *)(tmp_i6 + 0x14);
  }
  else {
    tmp_i3 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i6 + 0x14),tmp_i6 + 0x30,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i6 + 0x14) = tmp_i3;
    tmp_i5 = param_1[6];
  }
  *(uint32_t *)(tmp_i3 + tmp_i5 * 4) = tmp_u1;
  param_1[6] = param_1[6] + 1;
  return;
}

uint luaK_jump(int *param_1)
{
  uint *tmp_pu1;
  uint tmp_u2;
  uint32_t tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  uint tmp_u8;
  uint tmp_u9;
  uint tmp_u10;
  
  tmp_u9 = param_1[8];
  param_1[8] = -1;
  tmp_i6 = *param_1;
  tmp_u3 = *(uint32_t *)(param_1[3] + 8);
  patchlistaux(param_1[6],0xff,param_1[6]);
  tmp_i7 = param_1[6];
  param_1[8] = -1;
  if (tmp_i7 < *(int *)(tmp_i6 + 0x2c)) {
    tmp_i5 = *(int *)(tmp_i6 + 0xc);
  }
  else {
    tmp_i5 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i6 + 0xc),tmp_i6 + 0x2c,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i6 + 0xc) = tmp_i5;
    tmp_i7 = param_1[6];
  }
  *(uint32_t *)(tmp_i5 + tmp_i7 * 4) = 0x7fff8016;
  tmp_i7 = param_1[6];
  if (tmp_i7 < *(int *)(tmp_i6 + 0x30)) {
    tmp_i5 = *(int *)(tmp_i6 + 0x14);
  }
  else {
    tmp_i5 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i6 + 0x14),tmp_i6 + 0x30,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i6 + 0x14) = tmp_i5;
    tmp_i7 = param_1[6];
  }
  *(uint32_t *)(tmp_i5 + tmp_i7 * 4) = tmp_u3;
  tmp_u4 = param_1[6];
  param_1[6] = tmp_u4 + 1;
  if (tmp_u9 != 0xffffffff) {
    if (tmp_u4 == 0xffffffff) {
      return tmp_u9;
    }
    tmp_u2 = tmp_u4;
    do {
      tmp_u8 = tmp_u2;
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u8 * 4);
      tmp_u10 = *tmp_pu1;
      tmp_i6 = (tmp_u10 >> 0xe) - 0x1ffff;
      if (tmp_i6 == -1) break;
      tmp_u2 = tmp_u8 + 1 + tmp_i6;
    } while (tmp_u2 != 0xffffffff);
    tmp_u9 = ~tmp_u8 + tmp_u9;
    if (0x1ffff < (int)(((int)tmp_u9 >> 0x1f ^ tmp_u9) - ((int)tmp_u9 >> 0x1f))) {
      luaX_syntaxerror(param_1[3],"control structure too long");
      tmp_u10 = *tmp_pu1;
    }
    *tmp_pu1 = tmp_u10 & 0x3fff | (tmp_u9 + 0x1ffff) * 0x4000;
  }
  return tmp_u4;
}

void luaK_ret(int *param_1,int param_2,int param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_u1 = *(uint32_t *)(param_1[3] + 8);
  tmp_i2 = *param_1;
  patchlistaux(param_1[6],0xff,param_1[6]);
  tmp_i4 = param_1[6];
  param_1[8] = -1;
  if (tmp_i4 < *(int *)(tmp_i2 + 0x2c)) {
    tmp_i3 = *(int *)(tmp_i2 + 0xc);
  }
  else {
    tmp_i3 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i2 + 0xc),tmp_i2 + 0x2c,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i2 + 0xc) = tmp_i3;
    tmp_i4 = param_1[6];
  }
  *(uint *)(tmp_i3 + tmp_i4 * 4) = param_2 << 6 | 0x1eU | (param_3 + 1) * 0x800000;
  tmp_i4 = param_1[6];
  if (tmp_i4 < *(int *)(tmp_i2 + 0x30)) {
    tmp_i3 = *(int *)(tmp_i2 + 0x14);
  }
  else {
    tmp_i3 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i2 + 0x14),tmp_i2 + 0x30,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i2 + 0x14) = tmp_i3;
    tmp_i4 = param_1[6];
  }
  *(uint32_t *)(tmp_i3 + tmp_i4 * 4) = tmp_u1;
  param_1[6] = param_1[6] + 1;
  return;
}

void luaK_getlabel(int param_1)
{
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x18);
  return;
}

void luaK_patchlist(int *param_1,int param_2,int param_3)
{
  uint *tmp_pu1;
  uint tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  
  if (param_1[6] != param_3) {
    patchlistaux();
    return;
  }
  param_1[7] = param_1[6];
  if (param_2 != -1) {
    if (param_1[8] == 0xffffffff) {
      param_1[8] = param_2;
    }
    else {
      tmp_u2 = param_1[8];
      do {
        tmp_u4 = tmp_u2;
        tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u4 * 4);
        tmp_u5 = *tmp_pu1;
        tmp_i3 = (tmp_u5 >> 0xe) - 0x1ffff;
        if (tmp_i3 == -1) break;
        tmp_u2 = tmp_u4 + 1 + tmp_i3;
      } while (tmp_u2 != 0xffffffff);
      tmp_u2 = param_2 + ~tmp_u4;
      if (0x1ffff < (int)(((int)tmp_u2 >> 0x1f ^ tmp_u2) - ((int)tmp_u2 >> 0x1f))) {
        luaX_syntaxerror(param_1[3],"control structure too long");
        tmp_u5 = *tmp_pu1;
      }
      *tmp_pu1 = tmp_u5 & 0x3fff | (tmp_u2 + 0x1ffff) * 0x4000;
    }
  }
  return;
}

void luaK_patchtohere(int *param_1,int param_2)
{
  uint *tmp_pu1;
  uint tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  
  param_1[7] = param_1[6];
  if (param_2 != -1) {
    if (param_1[8] == 0xffffffff) {
      param_1[8] = param_2;
      return;
    }
    tmp_u3 = param_1[8];
    do {
      tmp_u2 = tmp_u3;
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u2 * 4);
      tmp_u4 = *tmp_pu1;
      tmp_i5 = (tmp_u4 >> 0xe) - 0x1ffff;
      if (tmp_i5 == -1) break;
      tmp_u3 = tmp_u2 + 1 + tmp_i5;
    } while (tmp_u3 != 0xffffffff);
    tmp_u3 = ~tmp_u2 + param_2;
    if (0x1ffff < (int)(((int)tmp_u3 >> 0x1f ^ tmp_u3) - ((int)tmp_u3 >> 0x1f))) {
      luaX_syntaxerror(param_1[3],"control structure too long");
      tmp_u4 = *tmp_pu1;
    }
    *tmp_pu1 = tmp_u4 & 0x3fff | (tmp_u3 + 0x1ffff) * 0x4000;
  }
  return;
}

void luaK_concat(int *param_1,uint *param_2,uint param_3)
{
  uint *tmp_pu1;
  uint tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  
  if (param_3 != 0xffffffff) {
    if (*param_2 == 0xffffffff) {
      *param_2 = param_3;
      return;
    }
    tmp_u2 = *param_2;
    do {
      tmp_u3 = tmp_u2;
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u3 * 4);
      tmp_u4 = *tmp_pu1;
      tmp_i5 = (tmp_u4 >> 0xe) - 0x1ffff;
      if (tmp_i5 == -1) break;
      tmp_u2 = tmp_u3 + 1 + tmp_i5;
    } while (tmp_u2 != 0xffffffff);
    param_3 = param_3 + ~tmp_u3;
    if (0x1ffff < (int)(((int)param_3 >> 0x1f ^ param_3) - ((int)param_3 >> 0x1f))) {
      luaX_syntaxerror(param_1[3],"control structure too long");
      tmp_u4 = *tmp_pu1;
    }
    *tmp_pu1 = tmp_u4 & 0x3fff | (param_3 + 0x1ffff) * 0x4000;
  }
  return;
}

void luaK_checkstack(int *param_1,int param_2)
{
  int tmp_i1;
  
  param_2 = param_1[9] + param_2;
  tmp_i1 = *param_1;
  if ((int)(uint)*(byte *)(tmp_i1 + 0x4b) < param_2) {
    if (0xf9 < param_2) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i1 = *param_1;
    }
    *(char *)(tmp_i1 + 0x4b) = (char)param_2;
  }
  return;
}

void luaK_reserveregs(int *param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = *param_1;
  tmp_i1 = param_1[9] + param_2;
  if ((int)(uint)*(byte *)(tmp_i2 + 0x4b) < tmp_i1) {
    if (0xf9 < tmp_i1) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i2 = *param_1;
    }
    *(char *)(tmp_i2 + 0x4b) = (char)tmp_i1;
    tmp_i1 = param_1[9] + param_2;
  }
  param_1[9] = tmp_i1;
  return;
}

int luaK_stringK(int *param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  double *pdVar4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int local_28;
  int local_24;
  int local_20;
  
  local_20 = 4;
  local_28 = param_2;
  tmp_i2 = param_1[4];
  pdVar4 = (double *)luaH_set(tmp_i2,param_1[1],&local_28);
  tmp_i3 = *param_1;
  tmp_i7 = *(int *)(tmp_i3 + 0x28);
  if (*(int *)(pdVar4 + 1) == 3) {
    return (int)ROUND(*pdVar4);
  }
  tmp_i6 = param_1[10];
  *(uint32_t *)(pdVar4 + 1) = 3;
  *pdVar4 = (double)tmp_i6;
  tmp_i6 = *(int *)(tmp_i3 + 0x28);
  if (param_1[10] < tmp_i6) {
    tmp_i5 = *(int *)(tmp_i3 + 8);
  }
  else {
    tmp_i5 = luaM_growaux_(tmp_i2,*(uint32_t *)(tmp_i3 + 8),tmp_i3 + 0x28,0xc,0x3ffff,
                          "constant table overflow");
    tmp_i6 = *(int *)(tmp_i3 + 0x28);
    *(int *)(tmp_i3 + 8) = tmp_i5;
  }
  if (tmp_i7 < tmp_i6) {
    tmp_i6 = tmp_i7 * 0xc;
    do {
      *(uint32_t *)(tmp_i5 + 8 + tmp_i6) = 0;
      tmp_i7 = tmp_i7 + 1;
      tmp_i6 = tmp_i6 + 0xc;
      tmp_i5 = *(int *)(tmp_i3 + 8);
    } while (tmp_i7 < *(int *)(tmp_i3 + 0x28));
  }
  tmp_pi1 = (int *)(tmp_i5 + param_1[10] * 0xc);
  *tmp_pi1 = local_28;
  tmp_pi1[1] = local_24;
  tmp_pi1[2] = local_20;
  if (((3 < local_20) && ((*(byte *)(local_28 + 5) & 3) != 0)) && ((*(byte *)(tmp_i3 + 5) & 4) != 0))
  {
    luaC_barrierf(tmp_i2,tmp_i3,local_28);
  }
  tmp_i2 = param_1[10];
  param_1[10] = tmp_i2 + 1;
  return tmp_i2;
}

int luaK_numberK(int *param_1,uint64_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  double *pdVar4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  uint64_t local_28;
  int local_20;
  
  local_20 = 3;
  local_28 = param_2;
  tmp_i2 = param_1[4];
  pdVar4 = (double *)luaH_set(tmp_i2,param_1[1],&local_28);
  tmp_i3 = *param_1;
  tmp_i7 = *(int *)(tmp_i3 + 0x28);
  if (*(int *)(pdVar4 + 1) == 3) {
    return (int)ROUND(*pdVar4);
  }
  tmp_i6 = param_1[10];
  *(uint32_t *)(pdVar4 + 1) = 3;
  *pdVar4 = (double)tmp_i6;
  tmp_i6 = *(int *)(tmp_i3 + 0x28);
  if (param_1[10] < tmp_i6) {
    tmp_i5 = *(int *)(tmp_i3 + 8);
  }
  else {
    tmp_i5 = luaM_growaux_(tmp_i2,*(uint32_t *)(tmp_i3 + 8),tmp_i3 + 0x28,0xc,0x3ffff,
                          "constant table overflow");
    tmp_i6 = *(int *)(tmp_i3 + 0x28);
    *(int *)(tmp_i3 + 8) = tmp_i5;
  }
  if (tmp_i7 < tmp_i6) {
    tmp_i6 = tmp_i7 * 0xc;
    do {
      *(uint32_t *)(tmp_i5 + 8 + tmp_i6) = 0;
      tmp_i7 = tmp_i7 + 1;
      tmp_i6 = tmp_i6 + 0xc;
      tmp_i5 = *(int *)(tmp_i3 + 8);
    } while (tmp_i7 < *(int *)(tmp_i3 + 0x28));
  }
  tmp_pi1 = (int *)(tmp_i5 + param_1[10] * 0xc);
  *tmp_pi1 = (int)local_28;
  tmp_pi1[1] = GHIDRA_FIELD(local_28, 4, 4);
  tmp_pi1[2] = local_20;
  if (((3 < local_20) && ((*(byte *)((int)local_28 + 5) & 3) != 0)) &&
     ((*(byte *)(tmp_i3 + 5) & 4) != 0)) {
    luaC_barrierf(tmp_i2,tmp_i3,(int)local_28);
  }
  tmp_i2 = param_1[10];
  param_1[10] = tmp_i2 + 1;
  return tmp_i2;
}

void luaK_setreturns(int *param_1,int *param_2,int param_3)
{
  uint *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  
  if (*param_2 == 0xd) {
    tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
    *tmp_pu1 = (param_3 + 1U & 0x1ff) << 0xe | *tmp_pu1 & 0xff803fff;
    return;
  }
  if (*param_2 != 0xe) {
    return;
  }
  tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
  *tmp_pu1 = (param_3 + 1) * 0x800000 | *tmp_pu1 & 0x7fffff;
  tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
  *tmp_pu1 = (param_1[9] & 0xffU) << 6 | *tmp_pu1 & 0xffffc03f;
  tmp_i3 = *param_1;
  tmp_i2 = param_1[9] + 1;
  if ((int)(uint)*(byte *)(tmp_i3 + 0x4b) < tmp_i2) {
    if (0xf9 < tmp_i2) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i3 = *param_1;
    }
    *(char *)(tmp_i3 + 0x4b) = (char)tmp_i2;
    tmp_i2 = param_1[9] + 1;
  }
  param_1[9] = tmp_i2;
  return;
}

void luaK_setoneret(int *param_1,int *param_2)
{
  uint *tmp_pu1;
  
  if (*param_2 == 0xd) {
    *param_2 = 0xc;
    param_2[1] = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
    return;
  }
  if (*param_2 != 0xe) {
    return;
  }
  tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
  *tmp_pu1 = *tmp_pu1 & 0x7fffff | 0x1000000;
  *param_2 = 0xb;
  return;
}

void luaK_dischargevars(int *param_1,int *param_2)
{
  uint *tmp_pu1;
  int tmp_i2;
  
  switch(*param_2) {
  case 6:
    *param_2 = 0xc;
    return;
  case 7:
    break;
  case 8:
    break;
  case 9:
    if (((param_2[2] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[2])) {
      param_1[9] = param_1[9] + -1;
    }
    if (((param_2[1] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[1])) {
      param_1[9] = param_1[9] + -1;
    }
    break;
  default:
    return;
  case 0xd:
  case 0xe:
    if (*param_2 != 0xd) {
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
      *tmp_pu1 = *tmp_pu1 & 0x7fffff | 0x1000000;
      *param_2 = 0xb;
      return;
    }
    *param_2 = 0xc;
    param_2[1] = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
    return;
  }
  tmp_i2 = luaK_code(*(uint32_t *)(param_1[3] + 8));
  *param_2 = 0xb;
  param_2[1] = tmp_i2;
  return;
}

void luaK_exp2nextreg(int *param_1,int *param_2)
{
  uint *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i2 = *param_2;
  switch(tmp_i2) {
  case 6:
    *param_2 = 0xc;
    goto LAB_0020af96;
  case 7:
    break;
  case 8:
    break;
  case 9:
    if (((param_2[2] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[2])) {
      param_1[9] = param_1[9] + -1;
    }
    if (((param_2[1] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[1])) {
      param_1[9] = param_1[9] + -1;
    }
    break;
  default:
    if (tmp_i2 == 0xc) goto LAB_0020af96;
    goto LAB_0020af09;
  case 0xd:
  case 0xe:
    if (tmp_i2 != 0xd) {
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
      *tmp_pu1 = *tmp_pu1 & 0x7fffff | 0x1000000;
      *param_2 = 0xb;
      goto LAB_0020af09;
    }
    *param_2 = 0xc;
    param_2[1] = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
LAB_0020af96:
    if (((param_2[1] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[1])) {
      tmp_i2 = param_1[9] + -1;
      param_1[9] = tmp_i2;
      goto LAB_0020af0c;
    }
    goto LAB_0020af09;
  }
  tmp_i2 = luaK_code(*(uint32_t *)(param_1[3] + 8));
  *param_2 = 0xb;
  param_2[1] = tmp_i2;
LAB_0020af09:
  tmp_i2 = param_1[9];
LAB_0020af0c:
  tmp_i3 = *param_1;
  tmp_i2 = tmp_i2 + 1;
  if ((int)(uint)*(byte *)(tmp_i3 + 0x4b) < tmp_i2) {
    if (0xf9 < tmp_i2) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i3 = *param_1;
    }
    *(char *)(tmp_i3 + 0x4b) = (char)tmp_i2;
    tmp_i2 = param_1[9] + 1;
  }
  param_1[9] = tmp_i2;
  exp2reg();
  return;
}

uint luaK_exp2anyreg(int *param_1,int *param_2)
{
  uint *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  
  tmp_i2 = *param_2;
  switch(tmp_i2 + -6) {
  case 0:
    *param_2 = 0xc;
    tmp_u3 = param_2[1];
LAB_0020b1f3:
    if (param_2[3] == param_2[4]) {
      return tmp_u3;
    }
    if ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)tmp_u3) goto LAB_0020b160;
    goto LAB_0020b20b;
  case 1:
_L390:
    break;
  case 2:
_L391:
    break;
  case 3:
_L392:
    if (((param_2[2] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[2])) {
      param_1[9] = param_1[9] + -1;
    }
    if (((param_2[1] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[1])) {
      param_1[9] = param_1[9] + -1;
    }
    break;
  default:
    if (tmp_i2 == 0xc) {
      tmp_u3 = param_2[1];
      goto LAB_0020b1f3;
    }
    switch(tmp_i2 + -6) {
    case 0:
      *param_2 = 0xc;
      break;
    case 1:
      goto _L390;
    case 2:
      goto _L391;
    case 3:
      goto _L392;
    default:
      goto _L387;
    case 7:
    case 8:
      if (tmp_i2 != 0xd) goto LAB_0020b109;
      *param_2 = 0xc;
      param_2[1] = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
    }
LAB_0020b20b:
    if (((param_2[1] & 0x100U) != 0) || (param_2[1] < (int)(uint)*(byte *)((int)param_1 + 0x32)))
    goto _L387;
    tmp_u3 = param_1[9] - 1;
    param_1[9] = tmp_u3;
    goto LAB_0020b133;
  case 7:
  case 8:
    if (tmp_i2 == 0xd) {
      *param_2 = 0xc;
      tmp_u3 = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
      param_2[1] = tmp_u3;
      goto LAB_0020b1f3;
    }
LAB_0020b109:
    tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
    *tmp_pu1 = *tmp_pu1 & 0x7fffff | 0x1000000;
    *param_2 = 0xb;
    goto _L387;
  }
  tmp_i2 = luaK_code(*(uint32_t *)(param_1[3] + 8));
  *param_2 = 0xb;
  param_2[1] = tmp_i2;
_L387:
  tmp_u3 = param_1[9];
LAB_0020b133:
  tmp_i4 = *param_1;
  tmp_i2 = tmp_u3 + 1;
  if ((int)(uint)*(byte *)(tmp_i4 + 0x4b) < tmp_i2) {
    if (0xf9 < tmp_i2) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i4 = *param_1;
    }
    *(char *)(tmp_i4 + 0x4b) = (char)tmp_i2;
    tmp_u3 = param_1[9];
    tmp_i2 = tmp_u3 + 1;
  }
  param_1[9] = tmp_i2;
LAB_0020b160:
  exp2reg(tmp_u3);
  return param_2[1];
}

void luaK_exp2val(int *param_1,int *param_2)
{
  uint *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  
  if (param_2[3] == param_2[4]) {
    luaK_dischargevars();
    return;
  }
  tmp_i2 = *param_2;
  switch(tmp_i2 + -6) {
  case 0:
    tmp_u3 = param_2[1];
    *param_2 = 0xc;
LAB_0020b479:
    if ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)tmp_u3) goto LAB_0020b3df;
    goto LAB_0020b485;
  case 1:
_L441:
    break;
  case 2:
_L442:
    break;
  case 3:
_L443:
    if (((param_2[2] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[2])) {
      param_1[9] = param_1[9] + -1;
    }
    if (((param_2[1] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[1])) {
      param_1[9] = param_1[9] + -1;
    }
    break;
  default:
    if (tmp_i2 == 0xc) {
      tmp_u3 = param_2[1];
      goto LAB_0020b479;
    }
    switch(tmp_i2 + -6) {
    case 0:
      *param_2 = 0xc;
      break;
    case 1:
      goto _L441;
    case 2:
      goto _L442;
    case 3:
      goto _L443;
    default:
      goto _L438;
    case 7:
    case 8:
      if (tmp_i2 != 0xd) goto LAB_0020b449;
      *param_2 = 0xc;
      param_2[1] = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
    }
LAB_0020b485:
    if (((param_2[1] & 0x100U) != 0) || (param_2[1] < (int)(uint)*(byte *)((int)param_1 + 0x32)))
    goto _L438;
    tmp_i2 = param_1[9] + -1;
    param_1[9] = tmp_i2;
    goto LAB_0020b3b2;
  case 7:
  case 8:
    if (tmp_i2 == 0xd) {
      *param_2 = 0xc;
      tmp_u3 = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
      param_2[1] = tmp_u3;
      goto LAB_0020b479;
    }
LAB_0020b449:
    tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
    *tmp_pu1 = *tmp_pu1 & 0x7fffff | 0x1000000;
    *param_2 = 0xb;
    goto _L438;
  }
  tmp_i2 = luaK_code(*(uint32_t *)(param_1[3] + 8));
  *param_2 = 0xb;
  param_2[1] = tmp_i2;
_L438:
  tmp_i2 = param_1[9];
LAB_0020b3b2:
  tmp_i4 = *param_1;
  tmp_i2 = tmp_i2 + 1;
  if ((int)(uint)*(byte *)(tmp_i4 + 0x4b) < tmp_i2) {
    if (0xf9 < tmp_i2) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i4 = *param_1;
    }
    *(char *)(tmp_i4 + 0x4b) = (char)tmp_i2;
    tmp_i2 = param_1[9] + 1;
  }
  param_1[9] = tmp_i2;
LAB_0020b3df:
  exp2reg();
  return;
}

uint luaK_exp2RK(int *param_1,uint *param_2)
{
  uint *tmp_pu1;
  uint32_t *tmp_pu2;
  uint tmp_u3;
  double *pdVar4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int local_34 [2];
  uint32_t local_2c;
  uint64_t local_28;
  uint32_t local_20;
  
  if (param_2[3] == param_2[4]) {
    luaK_dischargevars(param_1,param_2);
    tmp_u3 = *param_2;
    if (tmp_u3 != 4) goto LAB_0020b5b9;
LAB_0020b720:
    if ((int)param_2[1] < 0x100) {
      return param_2[1] | 0x100;
    }
    goto _L492;
  }
  luaK_exp2anyreg();
  tmp_u3 = *param_2;
  if (tmp_u3 == 4) goto LAB_0020b720;
LAB_0020b5b9:
  if (tmp_u3 < 4) {
    if (tmp_u3 != 0) {
LAB_0020b5e5:
      if (param_1[10] < 0x100) {
        if (tmp_u3 == 1) {
          tmp_i6 = param_1[4];
          local_34[0] = param_1[1];
          local_2c = 5;
          pdVar4 = (double *)luaH_set(tmp_i6,local_34[0],local_34);
          tmp_i7 = *param_1;
          tmp_i8 = *(int *)(tmp_i7 + 0x28);
          if (*(int *)(pdVar4 + 1) == 3) {
            tmp_u3 = (uint)ROUND(*pdVar4);
          }
          else {
            tmp_i5 = param_1[10];
            *(uint32_t *)(pdVar4 + 1) = 3;
            *pdVar4 = (double)tmp_i5;
            tmp_i5 = *(int *)(tmp_i7 + 0x28);
            if (param_1[10] < tmp_i5) {
              tmp_i6 = *(int *)(tmp_i7 + 8);
            }
            else {
              tmp_i6 = luaM_growaux_(tmp_i6,*(uint32_t *)(tmp_i7 + 8),tmp_i7 + 0x28,0xc,0x3ffff,
                                    "constant table overflow");
              *(int *)(tmp_i7 + 8) = tmp_i6;
              tmp_i5 = *(int *)(tmp_i7 + 0x28);
            }
            if (tmp_i8 < tmp_i5) {
              tmp_i5 = tmp_i8 * 0xc;
              do {
                *(uint32_t *)(tmp_i6 + 8 + tmp_i5) = 0;
                tmp_i8 = tmp_i8 + 1;
                tmp_i5 = tmp_i5 + 0xc;
                tmp_i6 = *(int *)(tmp_i7 + 8);
              } while (tmp_i8 < *(int *)(tmp_i7 + 0x28));
            }
            tmp_pu2 = (uint32_t *)(tmp_i6 + param_1[10] * 0xc);
            tmp_pu2[1] = GHIDRA_FIELD(local_28, 4, 4);
            tmp_pu2[2] = 0;
            *tmp_pu2 = (uint32_t)local_28;
            tmp_u3 = param_1[10];
            param_1[10] = tmp_u3 + 1;
          }
        }
        else if (tmp_u3 == 5) {
          local_28 = *(uint64_t *)(param_2 + 1);
          local_20 = 3;
          tmp_u3 = addk(&local_28);
        }
        else {
          local_28 = CONCAT44(GHIDRA_FIELD(local_28, 4, 4),(uint)(tmp_u3 == 2));
          local_20 = 1;
          tmp_u3 = addk(&local_28);
        }
        param_2[1] = tmp_u3;
        *param_2 = 4;
        return tmp_u3 | 0x100;
      }
    }
  }
  else if (tmp_u3 == 5) goto LAB_0020b5e5;
  switch(tmp_u3 - 6) {
  case 0:
    *param_2 = 0xc;
    tmp_u3 = param_2[1];
    goto LAB_0020b73b;
  case 1:
_L510:
    break;
  case 2:
_L511:
    break;
  case 3:
_L512:
    if (((param_2[2] & 0x100) == 0) &&
       ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)param_2[2])) {
      param_1[9] = param_1[9] + -1;
    }
    if (((param_2[1] & 0x100) == 0) &&
       ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)param_2[1])) {
      param_1[9] = param_1[9] + -1;
    }
    break;
  default:
    if (tmp_u3 == 0xc) {
      tmp_u3 = param_2[1];
      goto LAB_0020b73b;
    }
    switch(tmp_u3 - 6) {
    case 0:
      *param_2 = 0xc;
      break;
    case 1:
      goto _L510;
    case 2:
      goto _L511;
    case 3:
      goto _L512;
    default:
      goto _L492;
    case 7:
    case 8:
      if (tmp_u3 != 0xd) goto LAB_0020b799;
      *param_2 = 0xc;
      param_2[1] = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
    }
    goto LAB_0020b753;
  case 7:
  case 8:
    if (tmp_u3 != 0xd) {
LAB_0020b799:
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
      *tmp_pu1 = *tmp_pu1 & 0x7fffff | 0x1000000;
      *param_2 = 0xb;
      goto _L492;
    }
    *param_2 = 0xc;
    tmp_u3 = *(uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4) >> 6 & 0xff;
    param_2[1] = tmp_u3;
LAB_0020b73b:
    if (param_2[3] == param_2[4]) {
      return tmp_u3;
    }
    if ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)tmp_u3) goto LAB_0020b6af;
LAB_0020b753:
    if (((param_2[1] & 0x100) != 0) || ((int)param_2[1] < (int)(uint)*(byte *)((int)param_1 + 0x32))
       ) goto _L492;
    tmp_u3 = param_1[9] - 1;
    param_1[9] = tmp_u3;
    goto LAB_0020b682;
  }
  tmp_u3 = luaK_code(*(uint32_t *)(param_1[3] + 8));
  *param_2 = 0xb;
  param_2[1] = tmp_u3;
_L492:
  tmp_u3 = param_1[9];
LAB_0020b682:
  tmp_i7 = *param_1;
  tmp_i6 = tmp_u3 + 1;
  if ((int)(uint)*(byte *)(tmp_i7 + 0x4b) < tmp_i6) {
    if (0xf9 < tmp_i6) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i7 = *param_1;
    }
    *(char *)(tmp_i7 + 0x4b) = (char)tmp_i6;
    tmp_u3 = param_1[9];
    tmp_i6 = tmp_u3 + 1;
  }
  param_1[9] = tmp_i6;
LAB_0020b6af:
  exp2reg(tmp_u3);
  return param_2[1];
}

void luaK_storevar(int param_1,uint *param_2,int *param_3)
{
  uint tmp_u1;
  
  tmp_u1 = *param_2;
  if (tmp_u1 == 7) {
    luaK_exp2anyreg(param_1,param_3);
  }
  else {
    if (tmp_u1 < 8) {
      if (tmp_u1 == 6) {
        if (((*param_3 == 0xc) && ((param_3[1] & 0x100U) == 0)) &&
           ((int)(uint)*(byte *)(param_1 + 0x32) <= param_3[1])) {
          *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + -1;
        }
        exp2reg();
        return;
      }
      goto LAB_0020c136;
    }
    if (tmp_u1 == 8) {
      luaK_exp2anyreg(param_1,param_3);
    }
    else {
      if (tmp_u1 != 9) goto LAB_0020c136;
      luaK_exp2RK(param_1,param_3);
    }
  }
  luaK_code(*(uint32_t *)(*(int *)(param_1 + 0xc) + 8));
LAB_0020c136:
  if (((*param_3 == 0xc) && ((param_3[1] & 0x100U) == 0)) &&
     ((int)(uint)*(byte *)(param_1 + 0x32) <= param_3[1])) {
    *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + -1;
  }
  return;
}

void luaK_self(int *param_1,int *param_2,int *param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  
  luaK_dischargevars(param_1,param_2);
  if (*param_2 == 0xc) {
    if (param_2[3] != param_2[4]) {
      tmp_i6 = param_2[1];
      if (tmp_i6 < (int)(uint)*(byte *)((int)param_1 + 0x32)) goto LAB_0020c230;
      goto LAB_0020c276;
    }
LAB_0020c4a8:
    if (((param_2[1] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[1])) {
      tmp_i6 = param_1[9] + -1;
      param_1[9] = tmp_i6;
      goto LAB_0020c295;
    }
  }
  else {
LAB_0020c230:
    luaK_dischargevars(param_1,param_2);
    if (((*param_2 == 0xc) && ((param_2[1] & 0x100U) == 0)) &&
       ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_2[1])) {
      tmp_i6 = param_1[9] + -1;
      param_1[9] = tmp_i6;
    }
    else {
      tmp_i6 = param_1[9];
    }
    tmp_i7 = *param_1;
    tmp_i2 = tmp_i6 + 1;
    if ((int)(uint)*(byte *)(tmp_i7 + 0x4b) < tmp_i2) {
      if (0xf9 < tmp_i2) {
        luaX_syntaxerror(param_1[3],"function or expression too complex");
        tmp_i7 = *param_1;
      }
      *(char *)(tmp_i7 + 0x4b) = (char)tmp_i2;
      tmp_i6 = param_1[9];
      tmp_i2 = tmp_i6 + 1;
    }
    param_1[9] = tmp_i2;
LAB_0020c276:
    exp2reg(tmp_i6);
    if (*param_2 == 0xc) goto LAB_0020c4a8;
  }
  tmp_i6 = param_1[9];
LAB_0020c295:
  tmp_i7 = *param_1;
  tmp_i2 = tmp_i6 + 2;
  if ((int)(uint)*(byte *)(tmp_i7 + 0x4b) < tmp_i2) {
    if (0xf9 < tmp_i2) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i7 = *param_1;
    }
    *(char *)(tmp_i7 + 0x4b) = (char)tmp_i2;
    tmp_i2 = param_1[9] + 2;
  }
  param_1[9] = tmp_i2;
  tmp_i3 = luaK_exp2RK(param_1,param_3);
  tmp_i2 = *param_1;
  tmp_u1 = *(uint32_t *)(param_1[3] + 8);
  tmp_i7 = param_2[1];
  patchlistaux(param_1[6],0xff,param_1[6]);
  tmp_i4 = param_1[6];
  param_1[8] = -1;
  if (tmp_i4 < *(int *)(tmp_i2 + 0x2c)) {
    tmp_i5 = *(int *)(tmp_i2 + 0xc);
  }
  else {
    tmp_i5 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i2 + 0xc),tmp_i2 + 0x2c,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i2 + 0xc) = tmp_i5;
    tmp_i4 = param_1[6];
  }
  *(uint *)(tmp_i5 + tmp_i4 * 4) = tmp_i7 << 0x17 | 0xbU | tmp_i6 << 6 | tmp_i3 << 0xe;
  tmp_i7 = param_1[6];
  if (tmp_i7 < *(int *)(tmp_i2 + 0x30)) {
    tmp_i4 = *(int *)(tmp_i2 + 0x14);
  }
  else {
    tmp_i4 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i2 + 0x14),tmp_i2 + 0x30,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i2 + 0x14) = tmp_i4;
    tmp_i7 = param_1[6];
  }
  *(uint32_t *)(tmp_i4 + tmp_i7 * 4) = tmp_u1;
  param_1[6] = param_1[6] + 1;
  if (((*param_3 == 0xc) && ((param_3[1] & 0x100U) == 0)) &&
     ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_3[1])) {
    param_1[9] = param_1[9] + -1;
  }
  *param_2 = 0xc;
  param_2[1] = tmp_i6;
  return;
}

void luaK_goiftrue(int *param_1,uint32_t *param_2)
{
  uint *tmp_pu1;
  uint tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  uint local_24;
  
  luaK_dischargevars(param_1,param_2);
  switch(*param_2) {
  default:
    tmp_u3 = jumponcond(0);
    break;
  case 2:
  case 4:
  case 5:
    goto _L681;
  case 3:
    local_24 = param_1[8];
    param_1[8] = -1;
    tmp_u3 = luaK_code(*(uint32_t *)(param_1[3] + 8));
    if (local_24 == 0xffffffff) break;
    if (tmp_u3 == 0xffffffff) goto LAB_0020c6d1;
    tmp_u4 = tmp_u3;
    do {
      tmp_u2 = tmp_u4;
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u2 * 4);
      tmp_u7 = *tmp_pu1;
      tmp_i6 = (tmp_u7 >> 0xe) - 0x1ffff;
      if (tmp_i6 == -1) break;
      tmp_u4 = tmp_u2 + 1 + tmp_i6;
    } while (tmp_u4 != 0xffffffff);
    local_24 = local_24 + ~tmp_u2;
    if (0x1ffff < (int)(((int)local_24 >> 0x1f ^ local_24) - ((int)local_24 >> 0x1f))) {
      luaX_syntaxerror(param_1[3],"control structure too long");
      tmp_u7 = *tmp_pu1;
    }
    *tmp_pu1 = tmp_u7 & 0x3fff | (local_24 + 0x1ffff) * 0x4000;
    tmp_u4 = param_2[4];
    local_24 = tmp_u3;
    goto joined_r0x0020c798;
  case 10:
    tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[1] * 4);
    if (((int)param_2[1] < 1) || (tmp_u3 = tmp_pu1[-1], -1 < (char)luaP_opmodes[tmp_u3 & 0x3f])) {
      tmp_u3 = *tmp_pu1;
    }
    else {
      tmp_pu1 = tmp_pu1 + -1;
    }
    *tmp_pu1 = -(uint)((tmp_u3 >> 6 & 0xff) == 0) & 0x40 | tmp_u3 & 0xffffc03f;
    tmp_u3 = param_2[1];
  }
  local_24 = tmp_u3;
  if (local_24 != 0xffffffff) {
LAB_0020c6d1:
    tmp_u4 = param_2[4];
joined_r0x0020c798:
    if (tmp_u4 == 0xffffffff) {
      param_2[4] = local_24;
    }
    else {
      do {
        tmp_u7 = tmp_u4;
        tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u7 * 4);
        tmp_u3 = *tmp_pu1;
        tmp_i6 = (tmp_u3 >> 0xe) - 0x1ffff;
        if (tmp_i6 == -1) break;
        tmp_u4 = tmp_u7 + 1 + tmp_i6;
      } while (tmp_u4 != 0xffffffff);
      local_24 = local_24 + ~tmp_u7;
      if (0x1ffff < (int)(((int)local_24 >> 0x1f ^ local_24) - ((int)local_24 >> 0x1f))) {
        luaX_syntaxerror(param_1[3],"control structure too long");
        tmp_u3 = *tmp_pu1;
      }
      *tmp_pu1 = tmp_u3 & 0x3fff | (local_24 + 0x1ffff) * 0x4000;
    }
  }
_L681:
  tmp_i6 = param_2[3];
  param_1[7] = param_1[6];
  if (tmp_i6 != -1) {
    if (param_1[8] == 0xffffffff) {
      param_1[8] = tmp_i6;
    }
    else {
      tmp_u3 = param_1[8];
      do {
        tmp_u7 = tmp_u3;
        tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u7 * 4);
        tmp_u4 = *tmp_pu1;
        tmp_i5 = (tmp_u4 >> 0xe) - 0x1ffff;
        if (tmp_i5 == -1) break;
        tmp_u3 = tmp_u7 + 1 + tmp_i5;
      } while (tmp_u3 != 0xffffffff);
      tmp_u3 = tmp_i6 + ~tmp_u7;
      if (0x1ffff < (int)(((int)tmp_u3 >> 0x1f ^ tmp_u3) - ((int)tmp_u3 >> 0x1f))) {
        luaX_syntaxerror(param_1[3],"control structure too long");
        tmp_u4 = *tmp_pu1;
      }
      *tmp_pu1 = tmp_u4 & 0x3fff | (tmp_u3 + 0x1ffff) * 0x4000;
    }
  }
  param_2[3] = 0xffffffff;
  return;
}

void luaK_indexed(int *param_1,uint32_t *param_2,uint *param_3)
{
  uint *tmp_pu1;
  uint32_t *tmp_pu2;
  uint tmp_u3;
  double *pdVar4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int local_34 [2];
  uint32_t local_2c;
  uint64_t local_28;
  uint32_t local_20;
  
  if (param_3[3] != param_3[4]) {
    luaK_exp2anyreg();
    tmp_u3 = *param_3;
    if (tmp_u3 != 4) goto LAB_0020c849;
LAB_0020c9d0:
    if ((int)param_3[1] < 0x100) {
      tmp_u3 = param_3[1] | 0x100;
      goto LAB_0020c953;
    }
    goto _L753;
  }
  luaK_dischargevars(param_1,param_3);
  tmp_u3 = *param_3;
  if (tmp_u3 == 4) goto LAB_0020c9d0;
LAB_0020c849:
  if (tmp_u3 < 4) {
    if (tmp_u3 != 0) {
LAB_0020c875:
      if (param_1[10] < 0x100) {
        if (tmp_u3 == 1) {
          tmp_i5 = param_1[4];
          local_34[0] = param_1[1];
          local_2c = 5;
          pdVar4 = (double *)luaH_set(tmp_i5,local_34[0],local_34);
          tmp_i6 = *param_1;
          tmp_i7 = *(int *)(tmp_i6 + 0x28);
          if (*(int *)(pdVar4 + 1) == 3) {
            tmp_u3 = (uint)ROUND(*pdVar4);
          }
          else {
            tmp_i8 = param_1[10];
            *(uint32_t *)(pdVar4 + 1) = 3;
            *pdVar4 = (double)tmp_i8;
            tmp_i8 = *(int *)(tmp_i6 + 0x28);
            if (param_1[10] < tmp_i8) {
              tmp_i5 = *(int *)(tmp_i6 + 8);
            }
            else {
              tmp_i5 = luaM_growaux_(tmp_i5,*(uint32_t *)(tmp_i6 + 8),tmp_i6 + 0x28,0xc,0x3ffff,
                                    "constant table overflow");
              tmp_i8 = *(int *)(tmp_i6 + 0x28);
              *(int *)(tmp_i6 + 8) = tmp_i5;
            }
            if (tmp_i7 < tmp_i8) {
              tmp_i8 = tmp_i7 * 0xc;
              do {
                *(uint32_t *)(tmp_i5 + 8 + tmp_i8) = 0;
                tmp_i7 = tmp_i7 + 1;
                tmp_i8 = tmp_i8 + 0xc;
                tmp_i5 = *(int *)(tmp_i6 + 8);
              } while (tmp_i7 < *(int *)(tmp_i6 + 0x28));
            }
            tmp_pu2 = (uint32_t *)(tmp_i5 + param_1[10] * 0xc);
            tmp_pu2[2] = 0;
            *tmp_pu2 = (uint32_t)local_28;
            tmp_pu2[1] = GHIDRA_FIELD(local_28, 4, 4);
            tmp_u3 = param_1[10];
            param_1[10] = tmp_u3 + 1;
          }
        }
        else if (tmp_u3 == 5) {
          local_28 = *(uint64_t *)(param_3 + 1);
          local_20 = 3;
          tmp_u3 = addk(&local_28);
        }
        else {
          local_28 = CONCAT44(GHIDRA_FIELD(local_28, 4, 4),(uint)(tmp_u3 == 2));
          local_20 = 1;
          tmp_u3 = addk(&local_28);
        }
        param_3[1] = tmp_u3;
        tmp_u3 = tmp_u3 | 0x100;
        *param_3 = 4;
        goto LAB_0020c953;
      }
    }
  }
  else if (tmp_u3 == 5) goto LAB_0020c875;
  switch(tmp_u3 - 6) {
  case 0:
    *param_3 = 0xc;
    tmp_u3 = param_3[1];
    goto LAB_0020c9f3;
  case 1:
_L771:
    break;
  case 2:
_L772:
    break;
  case 3:
_L773:
    if (((param_3[2] & 0x100) == 0) &&
       ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)param_3[2])) {
      param_1[9] = param_1[9] + -1;
    }
    if (((param_3[1] & 0x100) == 0) &&
       ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)param_3[1])) {
      param_1[9] = param_1[9] + -1;
    }
    break;
  default:
    if (tmp_u3 == 0xc) {
      tmp_u3 = param_3[1];
      goto LAB_0020c9f3;
    }
    switch(tmp_u3 - 6) {
    case 0:
      *param_3 = 0xc;
      break;
    case 1:
      goto _L771;
    case 2:
      goto _L772;
    case 3:
      goto _L773;
    default:
      goto _L753;
    case 7:
    case 8:
      if (tmp_u3 != 0xd) goto LAB_0020ca49;
      *param_3 = 0xc;
      param_3[1] = *(uint *)(*(int *)(*param_1 + 0xc) + param_3[1] * 4) >> 6 & 0xff;
    }
    goto LAB_0020ca0b;
  case 7:
  case 8:
    if (tmp_u3 != 0xd) {
LAB_0020ca49:
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_3[1] * 4);
      *tmp_pu1 = *tmp_pu1 & 0x7fffff | 0x1000000;
      *param_3 = 0xb;
      goto _L753;
    }
    *param_3 = 0xc;
    tmp_u3 = *(uint *)(*(int *)(*param_1 + 0xc) + param_3[1] * 4) >> 6 & 0xff;
    param_3[1] = tmp_u3;
LAB_0020c9f3:
    if (param_3[3] == param_3[4]) goto LAB_0020c953;
    if ((int)tmp_u3 < (int)(uint)*(byte *)((int)param_1 + 0x32)) {
LAB_0020ca0b:
      if (((param_3[1] & 0x100) != 0) ||
         ((int)param_3[1] < (int)(uint)*(byte *)((int)param_1 + 0x32))) goto _L753;
      tmp_u3 = param_1[9] - 1;
      param_1[9] = tmp_u3;
      goto LAB_0020c916;
    }
    goto LAB_0020c944;
  }
  tmp_u3 = luaK_code(*(uint32_t *)(param_1[3] + 8));
  *param_3 = 0xb;
  param_3[1] = tmp_u3;
_L753:
  tmp_u3 = param_1[9];
LAB_0020c916:
  tmp_i6 = *param_1;
  tmp_i5 = tmp_u3 + 1;
  if ((int)(uint)*(byte *)(tmp_i6 + 0x4b) < tmp_i5) {
    if (0xf9 < tmp_i5) {
      luaX_syntaxerror(param_1[3],"function or expression too complex");
      tmp_i6 = *param_1;
    }
    *(char *)(tmp_i6 + 0x4b) = (char)tmp_i5;
    tmp_u3 = param_1[9];
    tmp_i5 = tmp_u3 + 1;
  }
  param_1[9] = tmp_i5;
LAB_0020c944:
  exp2reg(tmp_u3);
  tmp_u3 = param_3[1];
LAB_0020c953:
  param_2[2] = tmp_u3;
  *param_2 = 9;
  return;
}

void luaK_prefix(int *param_1,int param_2,int *param_3)
{
  int tmp_i1;
  uint *tmp_pu2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  uint tmp_u6;
  uint *tmp_pu7;
  int local_40;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_20 = 0xffffffff;
  local_24 = 0xffffffff;
  local_30 = 5;
  local_2c = 0;
  local_28 = 0;
  if (param_2 != 1) {
    if (param_2 == 0) {
      if (((*param_3 != 5) || (param_3[3] != -1)) || (param_3[4] != -1)) {
        luaK_exp2anyreg(param_1,param_3);
      }
      codearith(param_3,&local_30);
      return;
    }
    if (param_2 != 2) {
      return;
    }
    luaK_exp2anyreg(param_1,param_3);
    codearith(param_3,&local_30);
    return;
  }
  luaK_dischargevars(param_1,param_3);
  switch(*param_3) {
  case 1:
  case 3:
    *param_3 = 2;
    break;
  case 2:
  case 4:
  case 5:
    *param_3 = 3;
    break;
  case 10:
    tmp_pu2 = (uint *)(*(int *)(*param_1 + 0xc) + param_3[1] * 4);
    if ((param_3[1] < 1) || (tmp_u6 = tmp_pu2[-1], -1 < (char)luaP_opmodes[tmp_u6 & 0x3f])) {
      tmp_u6 = *tmp_pu2;
    }
    else {
      tmp_pu2 = tmp_pu2 + -1;
    }
    *tmp_pu2 = -(uint)((tmp_u6 >> 6 & 0xff) == 0) & 0x40 | tmp_u6 & 0xffffc03f;
    break;
  case 0xb:
  case 0xc:
    if (*param_3 == 0xc) {
LAB_0020cfdf:
      if (((param_3[1] & 0x100U) == 0) && ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_3[1]))
      {
        param_1[9] = param_1[9] + -1;
      }
    }
    else {
      tmp_i5 = *param_1;
      tmp_i1 = param_1[9];
      tmp_i3 = tmp_i1 + 1;
      if ((int)(uint)*(byte *)(tmp_i5 + 0x4b) < tmp_i3) {
        if (0xf9 < tmp_i3) {
          luaX_syntaxerror(param_1[3],"function or expression too complex");
          tmp_i5 = *param_1;
        }
        *(char *)(tmp_i5 + 0x4b) = (char)tmp_i3;
        tmp_i1 = param_1[9];
        tmp_i3 = tmp_i1 + 1;
      }
      param_1[9] = tmp_i3;
      discharge2reg(tmp_i1);
      if (*param_3 == 0xc) goto LAB_0020cfdf;
    }
    tmp_i3 = luaK_code(*(uint32_t *)(param_1[3] + 8));
    *param_3 = 0xb;
    param_3[1] = tmp_i3;
  }
  tmp_i3 = param_3[3];
  tmp_i5 = param_3[4];
  param_3[4] = tmp_i3;
  param_3[3] = tmp_i5;
  if (tmp_i3 != -1) {
    local_40 = *(int *)(*param_1 + 0xc);
    do {
      tmp_pu2 = (uint *)(local_40 + tmp_i3 * 4);
      if (tmp_i3 < 1) {
LAB_0020ce37:
        tmp_u6 = *tmp_pu2;
        tmp_u4 = tmp_u6 & 0x3f;
        tmp_pu7 = tmp_pu2;
      }
      else {
        tmp_u6 = tmp_pu2[-1];
        tmp_u4 = tmp_u6 & 0x3f;
        if (-1 < (char)luaP_opmodes[tmp_u4]) goto LAB_0020ce37;
        tmp_pu7 = tmp_pu2 + -1;
      }
      if (tmp_u4 == 0x1b) {
        *tmp_pu7 = (tmp_u6 >> 0x17) << 6 | tmp_u6 & 0x7fc000 | 0x1a;
        local_40 = *(int *)(*param_1 + 0xc);
        tmp_pu2 = (uint *)(local_40 + tmp_i3 * 4);
      }
    } while ((*tmp_pu2 >> 0xe != 0x1fffe) &&
            (tmp_i3 = ((*tmp_pu2 >> 0xe) - 0x1fffe) + tmp_i3, tmp_i3 != -1));
    tmp_i5 = param_3[3];
  }
  if (tmp_i5 != -1) {
    local_40 = *(int *)(*param_1 + 0xc);
    do {
      tmp_pu2 = (uint *)(local_40 + tmp_i5 * 4);
      if (tmp_i5 < 1) {
LAB_0020cee3:
        tmp_u6 = *tmp_pu2;
        tmp_u4 = tmp_u6 & 0x3f;
        tmp_pu7 = tmp_pu2;
      }
      else {
        tmp_u6 = tmp_pu2[-1];
        tmp_u4 = tmp_u6 & 0x3f;
        if (-1 < (char)luaP_opmodes[tmp_u4]) goto LAB_0020cee3;
        tmp_pu7 = tmp_pu2 + -1;
      }
      if (tmp_u4 == 0x1b) {
        *tmp_pu7 = (tmp_u6 >> 0x17) << 6 | tmp_u6 & 0x7fc000 | 0x1a;
        local_40 = *(int *)(*param_1 + 0xc);
        tmp_pu2 = (uint *)(local_40 + tmp_i5 * 4);
      }
      tmp_i3 = (*tmp_pu2 >> 0xe) - 0x1ffff;
    } while ((tmp_i3 != -1) && (tmp_i5 = tmp_i5 + 1 + tmp_i3, tmp_i5 != -1));
  }
  return;
}

void luaK_infix(int *param_1,uint32_t param_2,uint *param_3)
{
  uint *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  uint tmp_u6;
  uint tmp_u7;
  uint local_24;
  
  switch(param_2) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    if (((*param_3 == 5) && (param_3[3] == 0xffffffff)) && (param_3[4] == 0xffffffff)) {
      return;
    }
  default:
    luaK_exp2RK();
    return;
  case 6:
    luaK_dischargevars(param_1,param_3);
    if (((*param_3 == 0xc) && ((param_3[1] & 0x100) == 0)) &&
       ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)param_3[1])) {
      tmp_i2 = param_1[9] + -1;
      param_1[9] = tmp_i2;
    }
    else {
      tmp_i2 = param_1[9];
    }
    tmp_i5 = *param_1;
    tmp_i2 = tmp_i2 + 1;
    if ((int)(uint)*(byte *)(tmp_i5 + 0x4b) < tmp_i2) {
      if (0xf9 < tmp_i2) {
        luaX_syntaxerror(param_1[3],"function or expression too complex");
        tmp_i5 = *param_1;
      }
      *(char *)(tmp_i5 + 0x4b) = (char)tmp_i2;
      tmp_i2 = param_1[9] + 1;
    }
    param_1[9] = tmp_i2;
    exp2reg();
    return;
  case 0xd:
    luaK_goiftrue();
    return;
  case 0xe:
    break;
  }
  luaK_dischargevars(param_1,param_3);
  tmp_u7 = *param_3;
  if (tmp_u7 == 2) {
    local_24 = param_1[8];
    param_1[8] = -1;
    tmp_u7 = luaK_code(*(uint32_t *)(param_1[3] + 8));
    if (local_24 == 0xffffffff) goto LAB_0020d0c1;
    if (tmp_u7 != 0xffffffff) {
      tmp_u6 = tmp_u7;
      do {
        tmp_u3 = tmp_u6;
        tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u3 * 4);
        tmp_u4 = *tmp_pu1;
        tmp_i2 = (tmp_u4 >> 0xe) - 0x1ffff;
        if (tmp_i2 == -1) break;
        tmp_u6 = tmp_u3 + 1 + tmp_i2;
      } while (tmp_u6 != 0xffffffff);
      local_24 = local_24 + ~tmp_u3;
      if (0x1ffff < (int)(((int)local_24 >> 0x1f ^ local_24) - ((int)local_24 >> 0x1f))) {
        luaX_syntaxerror(param_1[3],"control structure too long");
        tmp_u4 = *tmp_pu1;
      }
      *tmp_pu1 = (local_24 + 0x1ffff) * 0x4000 | tmp_u4 & 0x3fff;
      local_24 = tmp_u7;
    }
  }
  else {
    if (tmp_u7 < 3) {
      if (tmp_u7 == 1) goto LAB_0020d281;
    }
    else {
      if (tmp_u7 == 3) goto LAB_0020d281;
      if (tmp_u7 == 10) {
        tmp_u7 = param_3[1];
        goto LAB_0020d0c1;
      }
    }
    tmp_u7 = jumponcond(1);
LAB_0020d0c1:
    local_24 = tmp_u7;
    if (local_24 == 0xffffffff) goto LAB_0020d281;
  }
  if (param_3[3] == 0xffffffff) {
    param_3[3] = local_24;
  }
  else {
    tmp_u7 = param_3[3];
    do {
      tmp_u4 = tmp_u7;
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u4 * 4);
      tmp_u6 = *tmp_pu1;
      tmp_i2 = (tmp_u6 >> 0xe) - 0x1ffff;
      if (tmp_i2 == -1) break;
      tmp_u7 = tmp_u4 + 1 + tmp_i2;
    } while (tmp_u7 != 0xffffffff);
    local_24 = local_24 + ~tmp_u4;
    if (0x1ffff < (int)(((int)local_24 >> 0x1f ^ local_24) - ((int)local_24 >> 0x1f))) {
      luaX_syntaxerror(param_1[3],"control structure too long");
      tmp_u6 = *tmp_pu1;
    }
    *tmp_pu1 = tmp_u6 & 0x3fff | (local_24 + 0x1ffff) * 0x4000;
  }
LAB_0020d281:
  tmp_u7 = param_3[4];
  param_1[7] = param_1[6];
  if (tmp_u7 != 0xffffffff) {
    if (param_1[8] == 0xffffffff) {
      param_1[8] = tmp_u7;
    }
    else {
      tmp_u6 = param_1[8];
      do {
        tmp_u3 = tmp_u6;
        tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u3 * 4);
        tmp_u4 = *tmp_pu1;
        tmp_i2 = (tmp_u4 >> 0xe) - 0x1ffff;
        if (tmp_i2 == -1) break;
        tmp_u6 = tmp_u3 + 1 + tmp_i2;
      } while (tmp_u6 != 0xffffffff);
      tmp_u7 = tmp_u7 + ~tmp_u3;
      if (0x1ffff < (int)(((int)tmp_u7 >> 0x1f ^ tmp_u7) - ((int)tmp_u7 >> 0x1f))) {
        luaX_syntaxerror(param_1[3],"control structure too long");
        tmp_u4 = *tmp_pu1;
      }
      *tmp_pu1 = tmp_u4 & 0x3fff | (tmp_u7 + 0x1ffff) * 0x4000;
    }
  }
  param_3[4] = 0xffffffff;
  return;
}

void luaK_posfix(int *param_1,uint32_t param_2,int *param_3,int *param_4)
{
  uint *tmp_pu1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  int local_30;
  uint local_2c;
  uint local_28;
  
  switch(param_2) {
  case 0:
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    if (param_4[3] == param_4[4]) {
      luaK_dischargevars(param_1,param_4);
    }
    else {
      luaK_exp2anyreg();
    }
    if (*param_4 == 0xb) {
      tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_4[1] * 4);
      tmp_u3 = *tmp_pu1;
      if ((tmp_u3 & 0x3f) == 0x15) {
        local_2c = param_3[1];
        if (((*param_3 == 0xc) && ((local_2c & 0x100) == 0)) &&
           ((int)(uint)*(byte *)((int)param_1 + 0x32) <= (int)local_2c)) {
          param_1[9] = param_1[9] + -1;
          local_2c = param_3[1];
          tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + param_4[1] * 4);
          tmp_u3 = *tmp_pu1;
        }
        *tmp_pu1 = tmp_u3 & 0x7fffff | local_2c << 0x17;
        *param_3 = 0xb;
        param_3[1] = param_4[1];
        return;
      }
    }
    luaK_dischargevars(param_1,param_4);
    if (((*param_4 == 0xc) && ((param_4[1] & 0x100U) == 0)) &&
       ((int)(uint)*(byte *)((int)param_1 + 0x32) <= param_4[1])) {
      local_30 = param_1[9] + -1;
      param_1[9] = local_30;
    }
    else {
      local_30 = param_1[9];
    }
    tmp_i4 = *param_1;
    local_2c = local_30 + 1;
    if ((int)(uint)*(byte *)(tmp_i4 + 0x4b) < (int)local_2c) {
      if (0xf9 < (int)local_2c) {
        luaX_syntaxerror(param_1[3],"function or expression too complex");
        tmp_i4 = *param_1;
      }
      *(char *)(tmp_i4 + 0x4b) = (char)local_2c;
      local_30 = param_1[9];
      local_2c = local_30 + 1;
    }
    param_1[9] = local_2c;
    exp2reg(local_30);
    break;
  case 7:
    goto LAB_0020d720;
  case 8:
    goto LAB_0020d720;
  case 9:
    goto LAB_0020d720;
  case 10:
    goto LAB_0020d720;
  case 0xb:
    goto LAB_0020d720;
  case 0xc:
LAB_0020d720:
    codecomp();
    return;
  case 0xd:
    luaK_dischargevars(param_1,param_4);
    local_30 = param_3[4];
    if (local_30 != -1) {
      if (param_4[4] == 0xffffffff) {
        param_4[4] = local_30;
      }
      else {
        tmp_u3 = param_4[4];
        do {
          tmp_u2 = tmp_u3;
          tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u2 * 4);
          local_28 = *tmp_pu1;
          tmp_i4 = (local_28 >> 0xe) - 0x1ffff;
          if (tmp_i4 == -1) break;
          tmp_u3 = tmp_u2 + 1 + tmp_i4;
        } while (tmp_u3 != 0xffffffff);
LAB_0020d7d0:
        tmp_u3 = ~tmp_u2 + local_30;
        if (0x1ffff < (int)(((int)tmp_u3 >> 0x1f ^ tmp_u3) - ((int)tmp_u3 >> 0x1f))) {
          luaX_syntaxerror(param_1[3],"control structure too long");
          local_28 = *tmp_pu1;
        }
        *tmp_pu1 = (tmp_u3 + 0x1ffff) * 0x4000 | local_28 & 0x3fff;
      }
    }
    goto LAB_0020d811;
  case 0xe:
    luaK_dischargevars(param_1,param_4);
    local_30 = param_3[3];
    if (local_30 != -1) {
      if (param_4[3] != 0xffffffff) {
        tmp_u3 = param_4[3];
        do {
          tmp_u2 = tmp_u3;
          tmp_pu1 = (uint *)(*(int *)(*param_1 + 0xc) + tmp_u2 * 4);
          local_28 = *tmp_pu1;
          tmp_i4 = (local_28 >> 0xe) - 0x1ffff;
          if (tmp_i4 == -1) break;
          tmp_u3 = tmp_u2 + 1 + tmp_i4;
        } while (tmp_u3 != 0xffffffff);
        goto LAB_0020d7d0;
      }
      param_4[3] = local_30;
    }
LAB_0020d811:
    *param_3 = *param_4;
    param_3[1] = param_4[1];
    param_3[2] = param_4[2];
    param_3[3] = param_4[3];
    param_3[4] = param_4[4];
switchD_0020d4ac_default:
    return;
  default:
    goto switchD_0020d4ac_default;
  }
  codearith();
  return;
}

void luaK_fixline(int *param_1,uint32_t param_2)
{
  *(uint32_t *)(*(int *)(*param_1 + 0x14) + -4 + param_1[6] * 4) = param_2;
  return;
}

void luaK_codeABC(int *param_1,uint param_2,int param_3,int param_4,int param_5)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_u1 = *(uint32_t *)(param_1[3] + 8);
  tmp_i2 = *param_1;
  patchlistaux(param_1[6],0xff,param_1[6]);
  tmp_i4 = param_1[6];
  param_1[8] = -1;
  if (tmp_i4 < *(int *)(tmp_i2 + 0x2c)) {
    tmp_i3 = *(int *)(tmp_i2 + 0xc);
  }
  else {
    tmp_i3 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i2 + 0xc),tmp_i2 + 0x2c,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i2 + 0xc) = tmp_i3;
    tmp_i4 = param_1[6];
  }
  *(uint *)(tmp_i3 + tmp_i4 * 4) = param_5 << 0xe | param_2 | param_4 << 0x17 | param_3 << 6;
  tmp_i4 = param_1[6];
  if (tmp_i4 < *(int *)(tmp_i2 + 0x30)) {
    tmp_i3 = *(int *)(tmp_i2 + 0x14);
  }
  else {
    tmp_i3 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i2 + 0x14),tmp_i2 + 0x30,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i2 + 0x14) = tmp_i3;
    tmp_i4 = param_1[6];
  }
  *(uint32_t *)(tmp_i3 + tmp_i4 * 4) = tmp_u1;
  param_1[6] = param_1[6] + 1;
  return;
}

void luaK_codeABx(int *param_1,uint param_2,int param_3,int param_4)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_u1 = *(uint32_t *)(param_1[3] + 8);
  tmp_i2 = *param_1;
  patchlistaux(param_1[6],0xff,param_1[6]);
  tmp_i4 = param_1[6];
  param_1[8] = -1;
  if (tmp_i4 < *(int *)(tmp_i2 + 0x2c)) {
    tmp_i3 = *(int *)(tmp_i2 + 0xc);
  }
  else {
    tmp_i3 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i2 + 0xc),tmp_i2 + 0x2c,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i2 + 0xc) = tmp_i3;
    tmp_i4 = param_1[6];
  }
  *(uint *)(tmp_i3 + tmp_i4 * 4) = param_4 << 0xe | param_2 | param_3 << 6;
  tmp_i4 = param_1[6];
  if (tmp_i4 < *(int *)(tmp_i2 + 0x30)) {
    tmp_i3 = *(int *)(tmp_i2 + 0x14);
  }
  else {
    tmp_i3 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i2 + 0x14),tmp_i2 + 0x30,4,0x7ffffffd,
                          "code size overflow");
    *(int *)(tmp_i2 + 0x14) = tmp_i3;
    tmp_i4 = param_1[6];
  }
  *(uint32_t *)(tmp_i3 + tmp_i4 * 4) = tmp_u1;
  param_1[6] = param_1[6] + 1;
  return;
}

void luaK_setlist(int *param_1,int param_2,int param_3,int param_4)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_i6 = (param_3 + -1) / 0x32 + 1;
  tmp_u3 = 0;
  if (param_4 != -1) {
    tmp_u3 = param_4 << 0x17;
  }
  if (0x1ff < tmp_i6) {
    tmp_i1 = *param_1;
    tmp_u2 = *(uint32_t *)(param_1[3] + 8);
    patchlistaux(param_1[6],0xff,param_1[6]);
    tmp_i4 = param_1[6];
    param_1[8] = -1;
    if (tmp_i4 < *(int *)(tmp_i1 + 0x2c)) {
      tmp_i5 = *(int *)(tmp_i1 + 0xc);
    }
    else {
      tmp_i5 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i1 + 0xc),tmp_i1 + 0x2c,4,0x7ffffffd,
                            "code size overflow");
      *(int *)(tmp_i1 + 0xc) = tmp_i5;
      tmp_i4 = param_1[6];
    }
    *(uint *)(tmp_i5 + tmp_i4 * 4) = param_2 << 6 | 0x22U | tmp_u3;
    tmp_i4 = param_1[6];
    if (tmp_i4 < *(int *)(tmp_i1 + 0x30)) {
      tmp_i5 = *(int *)(tmp_i1 + 0x14);
    }
    else {
      tmp_i5 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i1 + 0x14),tmp_i1 + 0x30,4,0x7ffffffd,
                            "code size overflow");
      *(int *)(tmp_i1 + 0x14) = tmp_i5;
      tmp_i4 = param_1[6];
    }
    *(uint32_t *)(tmp_i5 + tmp_i4 * 4) = tmp_u2;
    tmp_i1 = *param_1;
    tmp_i4 = param_1[6] + 1;
    param_1[6] = tmp_i4;
    tmp_u2 = *(uint32_t *)(param_1[3] + 8);
    patchlistaux(tmp_i4,0xff,tmp_i4);
    tmp_i4 = param_1[6];
    param_1[8] = -1;
    if (tmp_i4 < *(int *)(tmp_i1 + 0x2c)) {
      tmp_i5 = *(int *)(tmp_i1 + 0xc);
    }
    else {
      tmp_i5 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i1 + 0xc),tmp_i1 + 0x2c,4,0x7ffffffd,
                            "code size overflow");
      *(int *)(tmp_i1 + 0xc) = tmp_i5;
      tmp_i4 = param_1[6];
    }
    *(int *)(tmp_i5 + tmp_i4 * 4) = tmp_i6;
    tmp_i6 = param_1[6];
    if (tmp_i6 < *(int *)(tmp_i1 + 0x30)) {
      tmp_i4 = *(int *)(tmp_i1 + 0x14);
    }
    else {
      tmp_i4 = luaM_growaux_(param_1[4],*(uint32_t *)(tmp_i1 + 0x14),tmp_i1 + 0x30,4,0x7ffffffd,
                            "code size overflow");
      *(int *)(tmp_i1 + 0x14) = tmp_i4;
      tmp_i6 = param_1[6];
    }
    *(uint32_t *)(tmp_i4 + tmp_i6 * 4) = tmp_u2;
    param_1[6] = param_1[6] + 1;
    param_1[9] = param_2 + 1;
    return;
  }
  luaK_code(*(uint32_t *)(param_1[3] + 8));
  param_1[9] = param_2 + 1;
  return;
}

int luaC_separateudata(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  byte tmp_b5;
  uint32_t *tmp_pu6;
  int local_14;
  
  local_14 = 0;
  tmp_i1 = *(int *)(param_1 + 0x10);
  tmp_pu6 = *(uint32_t **)(tmp_i1 + 0x68);
LAB_0020ebda:
  tmp_pu3 = (uint32_t *)*tmp_pu6;
  do {
    tmp_pu2 = tmp_pu3;
    if (tmp_pu2 == (uint32_t *)0x0) {
      return local_14;
    }
    tmp_b5 = *(byte *)((int)tmp_pu2 + 5);
    if (((tmp_b5 & 3) != 0 || param_2 != 0) && ((tmp_b5 & 8) == 0)) {
      tmp_i4 = tmp_pu2[2];
      if ((tmp_i4 != 0) && ((*(byte *)(tmp_i4 + 6) & 4) == 0)) {
        tmp_i4 = luaT_gettm(tmp_i4,2,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xb0));
        if (tmp_i4 != 0) break;
        tmp_b5 = *(byte *)((int)tmp_pu2 + 5);
      }
      *(byte *)((int)tmp_pu2 + 5) = tmp_b5 | 8;
    }
    tmp_pu3 = (uint32_t *)*tmp_pu2;
    tmp_pu6 = tmp_pu2;
  } while( true );
  *(byte *)((int)tmp_pu2 + 5) = *(byte *)((int)tmp_pu2 + 5) | 8;
  local_14 = local_14 + 0x14 + tmp_pu2[4];
  *tmp_pu6 = *tmp_pu2;
  if (*(uint32_t **)(tmp_i1 + 0x30) == (uint32_t *)0x0) {
    *tmp_pu2 = tmp_pu2;
    *(uint32_t **)(tmp_i1 + 0x30) = tmp_pu2;
  }
  else {
    *tmp_pu2 = **(uint32_t **)(tmp_i1 + 0x30);
    **(uint32_t **)(tmp_i1 + 0x30) = tmp_pu2;
    *(uint32_t **)(tmp_i1 + 0x30) = tmp_pu2;
  }
  goto LAB_0020ebda;
}

void luaC_callGCTM(int param_1)
{
  uint8_t tmp_u1;
  int tmp_i2;
  int *tmp_pi3;
  int *tmp_pi4;
  int tmp_i5;
  uint32_t tmp_u6;
  uint32_t tmp_u7;
  uint32_t *tmp_pu8;
  uint32_t *tmp_pu9;
  
  while( true ) {
    tmp_i2 = *(int *)(param_1 + 0x10);
    tmp_pi3 = *(int **)(tmp_i2 + 0x30);
    if (tmp_pi3 == (int *)0x0) break;
    tmp_pi4 = (int *)*tmp_pi3;
    if (tmp_pi3 == tmp_pi4) {
      *(uint32_t *)(tmp_i2 + 0x30) = 0;
    }
    else {
      *tmp_pi3 = *tmp_pi4;
    }
    *tmp_pi4 = **(uint32_t **)(tmp_i2 + 0x68);
    **(int **)(tmp_i2 + 0x68) = (int)tmp_pi4;
    *(byte *)((int)tmp_pi4 + 5) = *(byte *)((int)tmp_pi4 + 5) & 0xf8 | *(byte *)(tmp_i2 + 0x14) & 3;
    tmp_i5 = tmp_pi4[2];
    if ((tmp_i5 != 0) && ((*(byte *)(tmp_i5 + 6) & 4) == 0)) {
      tmp_pu9 = (uint32_t *)luaT_gettm(tmp_i5,2,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xb0));
      if (tmp_pu9 != (uint32_t *)0x0) {
        tmp_u1 = *(uint8_t *)(param_1 + 0x39);
        tmp_u6 = *(uint32_t *)(tmp_i2 + 0x40);
        *(uint8_t *)(param_1 + 0x39) = 0;
        *(int *)(tmp_i2 + 0x40) = *(int *)(tmp_i2 + 0x44) * 2;
        tmp_u7 = tmp_pu9[1];
        tmp_pu8 = *(uint32_t **)(param_1 + 8);
        *tmp_pu8 = *tmp_pu9;
        tmp_pu8[1] = tmp_u7;
        tmp_pu8[2] = tmp_pu9[2];
        tmp_i5 = *(int *)(param_1 + 8);
        *(int **)(tmp_i5 + 0xc) = tmp_pi4;
        *(uint32_t *)(tmp_i5 + 0x14) = 7;
        tmp_i5 = *(int *)(param_1 + 8);
        *(int *)(param_1 + 8) = tmp_i5 + 0x18;
        luaD_call(param_1,tmp_i5,0);
        *(uint8_t *)(param_1 + 0x39) = tmp_u1;
        *(uint32_t *)(tmp_i2 + 0x40) = tmp_u6;
      }
    }
  }
  return;
}

void luaC_freeall(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = 0;
  tmp_i1 = *(int *)(param_1 + 0x10);
  *(uint8_t *)(tmp_i1 + 0x14) = 0x43;
  sweeplist_constprop_3();
  if (0 < *(int *)(tmp_i1 + 8)) {
    do {
      tmp_i2 = tmp_i2 + 1;
      sweeplist_constprop_3();
    } while (tmp_i2 < *(int *)(tmp_i1 + 8));
  }
  return;
}

int luaC_step(int param_1)
{
  byte tmp_b1;
  uint8_t tmp_u2;
  int tmp_i3;
  int *tmp_pi4;
  uint32_t *tmp_pu5;
  uint32_t tmp_u6;
  uint tmp_u7;
  int *tmp_pi8;
  int tmp_i9;
  uint32_t *tmp_pu10;
  int tmp_i11;
  int tmp_i12;
  uint32_t tmp_u13;
  int tmp_i14;
  int *tmp_pi15;
  int tmp_i16;
  int local_38;
  int local_34;
  
  tmp_i3 = *(int *)(param_1 + 0x10);
  tmp_i9 = *(int *)(tmp_i3 + 0x54) * 10;
  local_34 = 0x7ffffffe;
  if (tmp_i9 != 0) {
    local_34 = tmp_i9;
  }
  *(int *)(tmp_i3 + 0x4c) =
       (*(int *)(tmp_i3 + 0x4c) + *(int *)(tmp_i3 + 0x44)) - *(int *)(tmp_i3 + 0x40);
  do {
    tmp_i9 = *(int *)(param_1 + 0x10);
    switch(*(uint8_t *)(tmp_i9 + 0x15)) {
    case 0:
      markroot_isra_2();
      tmp_i14 = 0;
      break;
    case 1:
      if (*(int *)(tmp_i9 + 0x24) == 0) {
        tmp_i14 = *(int *)(tmp_i9 + 0x7c);
        if (tmp_i9 + 0x6c != tmp_i14) {
          do {
            if ((((*(byte *)(tmp_i14 + 5) & 7) == 0) && (3 < (*(int **)(tmp_i14 + 8))[2])) &&
               ((*(byte *)(**(int **)(tmp_i14 + 8) + 5) & 3) != 0)) {
              reallymarkobject();
            }
            tmp_i14 = *(int *)(tmp_i14 + 0x10);
          } while (tmp_i9 + 0x6c != tmp_i14);
          tmp_i14 = *(int *)(tmp_i9 + 0x24);
          while (tmp_i14 != 0) {
            propagatemark();
            tmp_i14 = *(int *)(tmp_i9 + 0x24);
          }
        }
        tmp_u13 = *(uint32_t *)(tmp_i9 + 0x2c);
        *(uint32_t *)(tmp_i9 + 0x2c) = 0;
        *(uint32_t *)(tmp_i9 + 0x24) = tmp_u13;
        if ((*(byte *)(param_1 + 5) & 3) != 0) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0x84) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0x84) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0x88) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0x88) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0x8c) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0x8c) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0x90) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0x90) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0x94) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0x94) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0x98) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0x98) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0x9c) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0x9c) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0xa0) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0xa0) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i9 + 0xa4) != 0) && ((*(byte *)(*(int *)(tmp_i9 + 0xa4) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        tmp_i14 = *(int *)(tmp_i9 + 0x24);
        while (tmp_i14 != 0) {
          propagatemark();
          tmp_i14 = *(int *)(tmp_i9 + 0x24);
        }
        tmp_i14 = *(int *)(tmp_i9 + 0x28);
        *(uint32_t *)(tmp_i9 + 0x28) = 0;
        *(int *)(tmp_i9 + 0x24) = tmp_i14;
        while (tmp_i14 != 0) {
          propagatemark();
          tmp_i14 = *(int *)(tmp_i9 + 0x24);
        }
        tmp_i14 = luaC_separateudata(param_1,0);
        tmp_pi15 = *(int **)(tmp_i9 + 0x30);
        if (tmp_pi15 != (int *)0x0) {
          do {
            tmp_pi15 = (int *)*tmp_pi15;
            *(byte *)((int)tmp_pi15 + 5) =
                 *(byte *)((int)tmp_pi15 + 5) & 0xf8 | *(byte *)(tmp_i9 + 0x14) & 3;
            reallymarkobject();
          } while (tmp_pi15 != (int *)*(int *)(tmp_i9 + 0x30));
        }
        tmp_i16 = 0;
        if (*(int *)(tmp_i9 + 0x24) != 0) {
          tmp_i16 = 0;
          do {
            tmp_i11 = propagatemark();
            tmp_i16 = tmp_i16 + tmp_i11;
          } while (*(int *)(tmp_i9 + 0x24) != 0);
        }
        cleartable();
        *(int *)(tmp_i9 + 0x20) = tmp_i9 + 0x1c;
        *(byte *)(tmp_i9 + 0x14) = *(byte *)(tmp_i9 + 0x14) ^ 3;
        *(uint32_t *)(tmp_i9 + 0x18) = 0;
        *(int *)(tmp_i9 + 0x48) = (*(int *)(tmp_i9 + 0x44) - tmp_i14) - tmp_i16;
        tmp_i14 = 0;
        *(uint8_t *)(tmp_i9 + 0x15) = 2;
      }
      else {
        tmp_i14 = propagatemark();
      }
      break;
    case 2:
      tmp_i14 = *(int *)(tmp_i9 + 0x44);
      *(int *)(tmp_i9 + 0x18) = *(int *)(tmp_i9 + 0x18) + 1;
      sweeplist_constprop_3();
      if (*(int *)(tmp_i9 + 8) <= *(int *)(tmp_i9 + 0x18)) {
        *(uint8_t *)(tmp_i9 + 0x15) = 3;
      }
      *(int *)(tmp_i9 + 0x48) = (*(int *)(tmp_i9 + 0x48) + *(int *)(tmp_i9 + 0x44)) - tmp_i14;
      tmp_i14 = 10;
      break;
    case 3:
      tmp_i14 = *(int *)(tmp_i9 + 0x44);
      tmp_pi15 = *(int **)(tmp_i9 + 0x20);
      tmp_b1 = *(byte *)(tmp_i9 + 0x14);
      local_38 = 0x29;
switchD_0020f09b_default:
      tmp_pi4 = (int *)*tmp_pi15;
      while( true ) {
        tmp_pi8 = tmp_pi4;
        if ((tmp_pi8 == (int *)0x0) || (local_38 = local_38 + -1, local_38 == 0)) {
          *(int **)(tmp_i9 + 0x20) = tmp_pi15;
          if (*tmp_pi15 == 0) {
            tmp_i16 = *(int *)(param_1 + 0x10);
            tmp_i11 = *(int *)(tmp_i16 + 8);
            tmp_i12 = tmp_i11 + 3;
            if (-1 < tmp_i11) {
              tmp_i12 = tmp_i11;
            }
            if ((*(uint *)(tmp_i16 + 4) < (uint)(tmp_i12 >> 2)) && (0x40 < tmp_i11)) {
              luaS_resize(param_1,tmp_i11 >> 1);
            }
            tmp_u7 = *(uint *)(tmp_i16 + 0x3c);
            if (0x40 < tmp_u7) {
              tmp_u13 = luaM_realloc_(param_1,*(uint32_t *)(tmp_i16 + 0x34),tmp_u7,tmp_u7 >> 1);
              *(uint *)(tmp_i16 + 0x3c) = tmp_u7 >> 1;
              *(uint32_t *)(tmp_i16 + 0x34) = tmp_u13;
            }
            *(uint8_t *)(tmp_i9 + 0x15) = 4;
          }
          *(int *)(tmp_i9 + 0x48) = (*(int *)(tmp_i9 + 0x48) + *(int *)(tmp_i9 + 0x44)) - tmp_i14;
          tmp_i14 = 400;
          goto LAB_0020ef6e;
        }
        if ((char)tmp_pi8[1] == '\b') {
          sweeplist_constprop_3();
        }
        if ((byte)((tmp_b1 ^ 3) & (*(byte *)((int)tmp_pi8 + 5) ^ 3)) == 0) break;
        *(byte *)((int)tmp_pi8 + 5) = *(byte *)((int)tmp_pi8 + 5) & 0xf8 | *(byte *)(tmp_i9 + 0x14) & 3
        ;
        tmp_pi4 = (int *)*tmp_pi8;
        tmp_pi15 = tmp_pi8;
      }
      *tmp_pi15 = *tmp_pi8;
      if (tmp_pi8 == *(int **)(tmp_i9 + 0x1c)) {
        *(int *)(tmp_i9 + 0x1c) = *tmp_pi8;
      }
      switch((char)tmp_pi8[1]) {
      case '\x04':
        tmp_pi4 = (int *)(*(int *)(param_1 + 0x10) + 4);
        *tmp_pi4 = *tmp_pi4 + -1;
        tmp_i16 = tmp_pi8[3] + 0x11;
        break;
      case '\x05':
        luaH_free(param_1,tmp_pi8);
        goto switchD_0020f09b_default;
      case '\x06':
        luaF_freeclosure(param_1,tmp_pi8);
        goto switchD_0020f09b_default;
      case '\a':
        tmp_i16 = tmp_pi8[4] + 0x14;
        break;
      case '\b':
        luaE_freethread(param_1,tmp_pi8);
        goto switchD_0020f09b_default;
      case '\t':
        luaF_freeproto(param_1,tmp_pi8);
        goto switchD_0020f09b_default;
      case '\n':
        luaF_freeupval(param_1,tmp_pi8);
      default:
        goto switchD_0020f09b_default;
      }
      luaM_realloc_(param_1,tmp_pi8,tmp_i16,0);
      goto switchD_0020f09b_default;
    case 4:
      tmp_pi15 = *(int **)(tmp_i9 + 0x30);
      if (tmp_pi15 == (int *)0x0) {
        *(uint8_t *)(tmp_i9 + 0x15) = 0;
        *(uint32_t *)(tmp_i9 + 0x4c) = 0;
        tmp_i14 = 0;
      }
      else {
        tmp_pi4 = (int *)*tmp_pi15;
        if (tmp_pi15 == tmp_pi4) {
          *(uint32_t *)(tmp_i9 + 0x30) = 0;
        }
        else {
          *tmp_pi15 = *tmp_pi4;
        }
        *tmp_pi4 = **(uint32_t **)(tmp_i9 + 0x68);
        **(int **)(tmp_i9 + 0x68) = (int)tmp_pi4;
        *(byte *)((int)tmp_pi4 + 5) = *(byte *)((int)tmp_pi4 + 5) & 0xf8 | *(byte *)(tmp_i9 + 0x14) & 3
        ;
        tmp_i14 = tmp_pi4[2];
        if (((tmp_i14 != 0) && ((*(byte *)(tmp_i14 + 6) & 4) == 0)) &&
           (tmp_pu10 = (uint32_t *)
                      luaT_gettm(tmp_i14,2,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xb0)),
           tmp_pu10 != (uint32_t *)0x0)) {
          tmp_u2 = *(uint8_t *)(param_1 + 0x39);
          tmp_u13 = *(uint32_t *)(tmp_i9 + 0x40);
          *(uint8_t *)(param_1 + 0x39) = 0;
          *(int *)(tmp_i9 + 0x40) = *(int *)(tmp_i9 + 0x44) * 2;
          tmp_pu5 = *(uint32_t **)(param_1 + 8);
          tmp_u6 = tmp_pu10[1];
          *tmp_pu5 = *tmp_pu10;
          tmp_pu5[1] = tmp_u6;
          tmp_pu5[2] = tmp_pu10[2];
          tmp_i14 = *(int *)(param_1 + 8);
          *(int **)(tmp_i14 + 0xc) = tmp_pi4;
          *(uint32_t *)(tmp_i14 + 0x14) = 7;
          tmp_i14 = *(int *)(param_1 + 8);
          *(int *)(param_1 + 8) = tmp_i14 + 0x18;
          luaD_call(param_1,tmp_i14,0);
          *(uint8_t *)(param_1 + 0x39) = tmp_u2;
          *(uint32_t *)(tmp_i9 + 0x40) = tmp_u13;
        }
        tmp_i14 = 100;
        if (100 < *(uint *)(tmp_i9 + 0x48)) {
          *(uint *)(tmp_i9 + 0x48) = *(uint *)(tmp_i9 + 0x48) - 100;
        }
      }
      break;
    default:
      tmp_i14 = 0;
    }
LAB_0020ef6e:
    local_34 = local_34 - tmp_i14;
    if (*(char *)(tmp_i3 + 0x15) == '\0') {
      *(uint *)(tmp_i3 + 0x40) = (*(uint *)(tmp_i3 + 0x48) / 100) * *(int *)(tmp_i3 + 0x50);
      return *(uint *)(tmp_i3 + 0x48) * 0x51eb851f;
    }
    if (local_34 < 1) {
      if (0x3ff < *(uint *)(tmp_i3 + 0x4c)) {
        *(uint *)(tmp_i3 + 0x4c) = *(uint *)(tmp_i3 + 0x4c) - 0x400;
        *(int *)(tmp_i3 + 0x40) = *(int *)(tmp_i3 + 0x44);
        return *(int *)(tmp_i3 + 0x44);
      }
      tmp_i9 = *(int *)(tmp_i3 + 0x44) + 0x400;
      *(int *)(tmp_i3 + 0x40) = tmp_i9;
      return tmp_i9;
    }
  } while( true );
}

void luaC_fullgc(int param_1)
{
  uint8_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int *tmp_pi4;
  uint32_t *tmp_pu5;
  uint32_t tmp_u6;
  uint tmp_u7;
  int *tmp_pi8;
  byte tmp_b9;
  uint32_t *tmp_pu10;
  int tmp_i11;
  int tmp_i12;
  uint32_t tmp_u13;
  int tmp_i14;
  int *tmp_pi15;
  int tmp_i16;
  int local_34;
  
  tmp_i2 = *(int *)(param_1 + 0x10);
  tmp_b9 = *(byte *)(tmp_i2 + 0x15);
  if (tmp_b9 < 2) {
    *(int *)(tmp_i2 + 0x20) = tmp_i2 + 0x1c;
    tmp_b9 = 2;
    *(uint32_t *)(tmp_i2 + 0x18) = 0;
    *(uint32_t *)(tmp_i2 + 0x24) = 0;
    *(uint32_t *)(tmp_i2 + 0x28) = 0;
    *(uint32_t *)(tmp_i2 + 0x2c) = 0;
    *(uint8_t *)(tmp_i2 + 0x15) = 2;
  }
  do {
    if (tmp_b9 == 4) {
_L657:
      markroot_isra_2();
      do {
        if (*(char *)(tmp_i2 + 0x15) == '\0') {
LAB_0020f770:
          *(uint *)(tmp_i2 + 0x40) = (*(uint *)(tmp_i2 + 0x48) / 100) * *(int *)(tmp_i2 + 0x50);
          return;
        }
LAB_0020f6a7:
        tmp_i3 = *(int *)(param_1 + 0x10);
code_r0x0020f6b4:
        switch(*(uint8_t *)(tmp_i3 + 0x15)) {
        case 0:
          goto _L657;
        case 1:
          if (*(int *)(tmp_i3 + 0x24) == 0) {
            tmp_i11 = *(int *)(tmp_i3 + 0x7c);
            if (tmp_i11 != tmp_i3 + 0x6c) {
              do {
                if ((((*(byte *)(tmp_i11 + 5) & 7) == 0) && (3 < (*(int **)(tmp_i11 + 8))[2])) &&
                   ((*(byte *)(**(int **)(tmp_i11 + 8) + 5) & 3) != 0)) {
                  reallymarkobject();
                }
                tmp_i11 = *(int *)(tmp_i11 + 0x10);
              } while (tmp_i11 != tmp_i3 + 0x6c);
              tmp_i11 = *(int *)(tmp_i3 + 0x24);
              while (tmp_i11 != 0) {
                propagatemark();
                tmp_i11 = *(int *)(tmp_i3 + 0x24);
              }
            }
            tmp_u13 = *(uint32_t *)(tmp_i3 + 0x2c);
            *(uint32_t *)(tmp_i3 + 0x2c) = 0;
            *(uint32_t *)(tmp_i3 + 0x24) = tmp_u13;
            if ((*(byte *)(param_1 + 5) & 3) != 0) {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0x84) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x84) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0x88) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x88) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0x8c) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x8c) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0x90) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x90) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0x94) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x94) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0x98) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x98) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0x9c) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x9c) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0xa0) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0xa0) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            if ((*(int *)(tmp_i3 + 0xa4) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0xa4) + 5) & 3) != 0))
            {
              reallymarkobject();
            }
            tmp_i11 = *(int *)(tmp_i3 + 0x24);
            while (tmp_i11 != 0) {
              propagatemark();
              tmp_i11 = *(int *)(tmp_i3 + 0x24);
            }
            tmp_i11 = *(int *)(tmp_i3 + 0x28);
            *(uint32_t *)(tmp_i3 + 0x28) = 0;
            *(int *)(tmp_i3 + 0x24) = tmp_i11;
            while (tmp_i11 != 0) {
              propagatemark();
              tmp_i11 = *(int *)(tmp_i3 + 0x24);
            }
            tmp_i11 = luaC_separateudata(param_1,0);
            tmp_pi15 = *(int **)(tmp_i3 + 0x30);
            if (tmp_pi15 != (int *)0x0) {
              do {
                tmp_pi15 = (int *)*tmp_pi15;
                *(byte *)((int)tmp_pi15 + 5) =
                     *(byte *)((int)tmp_pi15 + 5) & 0xf8 | *(byte *)(tmp_i3 + 0x14) & 3;
                reallymarkobject();
              } while (tmp_pi15 != (int *)*(int *)(tmp_i3 + 0x30));
            }
            tmp_i16 = 0;
            if (*(int *)(tmp_i3 + 0x24) != 0) {
              tmp_i16 = 0;
              do {
                tmp_i12 = propagatemark();
                tmp_i16 = tmp_i16 + tmp_i12;
              } while (*(int *)(tmp_i3 + 0x24) != 0);
            }
            cleartable();
            *(int *)(tmp_i3 + 0x20) = tmp_i3 + 0x1c;
            *(byte *)(tmp_i3 + 0x14) = *(byte *)(tmp_i3 + 0x14) ^ 3;
            *(uint32_t *)(tmp_i3 + 0x18) = 0;
            *(uint8_t *)(tmp_i3 + 0x15) = 2;
            *(int *)(tmp_i3 + 0x48) = (*(int *)(tmp_i3 + 0x44) - tmp_i11) - tmp_i16;
          }
          else {
            propagatemark();
          }
          break;
        case 2:
          tmp_i11 = *(int *)(tmp_i3 + 0x44);
          *(int *)(tmp_i3 + 0x18) = *(int *)(tmp_i3 + 0x18) + 1;
          sweeplist_constprop_3();
          if (*(int *)(tmp_i3 + 8) <= *(int *)(tmp_i3 + 0x18)) {
            *(uint8_t *)(tmp_i3 + 0x15) = 3;
          }
          *(int *)(tmp_i3 + 0x48) = (*(int *)(tmp_i3 + 0x48) + *(int *)(tmp_i3 + 0x44)) - tmp_i11;
          break;
        case 3:
          tmp_i11 = *(int *)(tmp_i3 + 0x44);
          tmp_pi15 = *(int **)(tmp_i3 + 0x20);
          tmp_b9 = *(byte *)(tmp_i3 + 0x14);
          local_34 = 0x29;
switchD_0020fa3b_default:
          tmp_pi4 = (int *)*tmp_pi15;
          while( true ) {
            tmp_pi8 = tmp_pi4;
            if ((tmp_pi8 == (int *)0x0) || (local_34 = local_34 + -1, local_34 == 0)) {
              *(int **)(tmp_i3 + 0x20) = tmp_pi15;
              if (*tmp_pi15 == 0) {
                tmp_i16 = *(int *)(param_1 + 0x10);
                tmp_i12 = *(int *)(tmp_i16 + 8);
                tmp_i14 = tmp_i12 + 3;
                if (-1 < tmp_i12) {
                  tmp_i14 = tmp_i12;
                }
                if ((*(uint *)(tmp_i16 + 4) < (uint)(tmp_i14 >> 2)) && (0x40 < tmp_i12)) {
                  luaS_resize(param_1,tmp_i12 >> 1);
                }
                tmp_u7 = *(uint *)(tmp_i16 + 0x3c);
                if (0x40 < tmp_u7) {
                  tmp_u13 = luaM_realloc_(param_1,*(uint32_t *)(tmp_i16 + 0x34),tmp_u7,tmp_u7 >> 1);
                  *(uint *)(tmp_i16 + 0x3c) = tmp_u7 >> 1;
                  *(uint32_t *)(tmp_i16 + 0x34) = tmp_u13;
                }
                *(uint8_t *)(tmp_i3 + 0x15) = 4;
              }
              *(int *)(tmp_i3 + 0x48) = (*(int *)(tmp_i3 + 0x48) + *(int *)(tmp_i3 + 0x44)) - tmp_i11;
              if (*(char *)(tmp_i2 + 0x15) != '\0') goto LAB_0020f6a7;
              goto LAB_0020f770;
            }
            if ((char)tmp_pi8[1] == '\b') {
              sweeplist_constprop_3();
            }
            if ((byte)((tmp_b9 ^ 3) & (*(byte *)((int)tmp_pi8 + 5) ^ 3)) == 0) break;
            *(byte *)((int)tmp_pi8 + 5) =
                 *(byte *)((int)tmp_pi8 + 5) & 0xf8 | *(byte *)(tmp_i3 + 0x14) & 3;
            tmp_pi4 = (int *)*tmp_pi8;
            tmp_pi15 = tmp_pi8;
          }
          *tmp_pi15 = *tmp_pi8;
          if (tmp_pi8 == *(int **)(tmp_i3 + 0x1c)) {
            *(int *)(tmp_i3 + 0x1c) = *tmp_pi8;
          }
          switch((char)tmp_pi8[1]) {
          case '\x04':
            tmp_pi4 = (int *)(*(int *)(param_1 + 0x10) + 4);
            *tmp_pi4 = *tmp_pi4 + -1;
            tmp_i16 = tmp_pi8[3] + 0x11;
            break;
          case '\x05':
            luaH_free(param_1,tmp_pi8);
            goto switchD_0020fa3b_default;
          case '\x06':
            luaF_freeclosure(param_1,tmp_pi8);
            goto switchD_0020fa3b_default;
          case '\a':
            tmp_i16 = tmp_pi8[4] + 0x14;
            break;
          case '\b':
            luaE_freethread(param_1,tmp_pi8);
            goto switchD_0020fa3b_default;
          case '\t':
            luaF_freeproto(param_1,tmp_pi8);
            goto switchD_0020fa3b_default;
          case '\n':
            luaF_freeupval(param_1,tmp_pi8);
          default:
            goto switchD_0020fa3b_default;
          }
          luaM_realloc_(param_1,tmp_pi8,tmp_i16,0);
          goto switchD_0020fa3b_default;
        case 4:
          tmp_pi15 = *(int **)(tmp_i3 + 0x30);
          if (tmp_pi15 == (int *)0x0) {
            *(uint8_t *)(tmp_i3 + 0x15) = 0;
            *(uint32_t *)(tmp_i3 + 0x4c) = 0;
          }
          else {
            tmp_pi4 = (int *)*tmp_pi15;
            if (tmp_pi15 == tmp_pi4) {
              *(uint32_t *)(tmp_i3 + 0x30) = 0;
            }
            else {
              *tmp_pi15 = *tmp_pi4;
            }
            *tmp_pi4 = **(uint32_t **)(tmp_i3 + 0x68);
            **(int **)(tmp_i3 + 0x68) = (int)tmp_pi4;
            *(byte *)((int)tmp_pi4 + 5) =
                 *(byte *)((int)tmp_pi4 + 5) & 0xf8 | *(byte *)(tmp_i3 + 0x14) & 3;
            tmp_i11 = tmp_pi4[2];
            if (((tmp_i11 != 0) && ((*(byte *)(tmp_i11 + 6) & 4) == 0)) &&
               (tmp_pu10 = (uint32_t *)
                          luaT_gettm(tmp_i11,2,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xb0)),
               tmp_pu10 != (uint32_t *)0x0)) {
              tmp_u1 = *(uint8_t *)(param_1 + 0x39);
              tmp_u13 = *(uint32_t *)(tmp_i3 + 0x40);
              *(uint8_t *)(param_1 + 0x39) = 0;
              *(int *)(tmp_i3 + 0x40) = *(int *)(tmp_i3 + 0x44) * 2;
              tmp_pu5 = *(uint32_t **)(param_1 + 8);
              tmp_u6 = tmp_pu10[1];
              *tmp_pu5 = *tmp_pu10;
              tmp_pu5[1] = tmp_u6;
              tmp_pu5[2] = tmp_pu10[2];
              tmp_i11 = *(int *)(param_1 + 8);
              *(int **)(tmp_i11 + 0xc) = tmp_pi4;
              *(uint32_t *)(tmp_i11 + 0x14) = 7;
              tmp_i11 = *(int *)(param_1 + 8);
              *(int *)(param_1 + 8) = tmp_i11 + 0x18;
              luaD_call(param_1,tmp_i11,0);
              *(uint8_t *)(param_1 + 0x39) = tmp_u1;
              *(uint32_t *)(tmp_i3 + 0x40) = tmp_u13;
            }
            if (100 < *(uint *)(tmp_i3 + 0x48)) {
              *(uint *)(tmp_i3 + 0x48) = *(uint *)(tmp_i3 + 0x48) - 100;
            }
          }
          break;
        default:
          goto code_r0x0020f6b4;
        }
      } while( true );
    }
    tmp_i3 = *(int *)(param_1 + 0x10);
code_r0x0020f681:
    switch(*(uint8_t *)(tmp_i3 + 0x15)) {
    case 0:
      markroot_isra_2();
      break;
    case 1:
      if (*(int *)(tmp_i3 + 0x24) == 0) {
        tmp_i11 = *(int *)(tmp_i3 + 0x7c);
        if (tmp_i11 != tmp_i3 + 0x6c) {
          do {
            if ((((*(byte *)(tmp_i11 + 5) & 7) == 0) && (3 < (*(int **)(tmp_i11 + 8))[2])) &&
               ((*(byte *)(**(int **)(tmp_i11 + 8) + 5) & 3) != 0)) {
              reallymarkobject();
            }
            tmp_i11 = *(int *)(tmp_i11 + 0x10);
          } while (tmp_i11 != tmp_i3 + 0x6c);
          tmp_i11 = *(int *)(tmp_i3 + 0x24);
          while (tmp_i11 != 0) {
            propagatemark();
            tmp_i11 = *(int *)(tmp_i3 + 0x24);
          }
        }
        tmp_u13 = *(uint32_t *)(tmp_i3 + 0x2c);
        *(uint32_t *)(tmp_i3 + 0x2c) = 0;
        *(uint32_t *)(tmp_i3 + 0x24) = tmp_u13;
        if ((*(byte *)(param_1 + 5) & 3) != 0) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0x84) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x84) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0x88) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x88) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0x8c) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x8c) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0x90) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x90) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0x94) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x94) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0x98) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x98) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0x9c) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0x9c) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0xa0) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0xa0) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        if ((*(int *)(tmp_i3 + 0xa4) != 0) && ((*(byte *)(*(int *)(tmp_i3 + 0xa4) + 5) & 3) != 0)) {
          reallymarkobject();
        }
        tmp_i11 = *(int *)(tmp_i3 + 0x24);
        while (tmp_i11 != 0) {
          propagatemark();
          tmp_i11 = *(int *)(tmp_i3 + 0x24);
        }
        tmp_i11 = *(int *)(tmp_i3 + 0x28);
        *(uint32_t *)(tmp_i3 + 0x28) = 0;
        *(int *)(tmp_i3 + 0x24) = tmp_i11;
        while (tmp_i11 != 0) {
          propagatemark();
          tmp_i11 = *(int *)(tmp_i3 + 0x24);
        }
        tmp_i11 = luaC_separateudata(param_1,0);
        tmp_pi15 = *(int **)(tmp_i3 + 0x30);
        if (tmp_pi15 != (int *)0x0) {
          do {
            tmp_pi15 = (int *)*tmp_pi15;
            *(byte *)((int)tmp_pi15 + 5) =
                 *(byte *)((int)tmp_pi15 + 5) & 0xf8 | *(byte *)(tmp_i3 + 0x14) & 3;
            reallymarkobject();
          } while (tmp_pi15 != (int *)*(int *)(tmp_i3 + 0x30));
        }
        tmp_i16 = 0;
        if (*(int *)(tmp_i3 + 0x24) != 0) {
          tmp_i16 = 0;
          do {
            tmp_i12 = propagatemark();
            tmp_i16 = tmp_i16 + tmp_i12;
          } while (*(int *)(tmp_i3 + 0x24) != 0);
        }
        cleartable();
        *(int *)(tmp_i3 + 0x20) = tmp_i3 + 0x1c;
        *(byte *)(tmp_i3 + 0x14) = *(byte *)(tmp_i3 + 0x14) ^ 3;
        *(uint32_t *)(tmp_i3 + 0x18) = 0;
        *(uint8_t *)(tmp_i3 + 0x15) = 2;
        *(int *)(tmp_i3 + 0x48) = (*(int *)(tmp_i3 + 0x44) - tmp_i11) - tmp_i16;
      }
      else {
        propagatemark();
      }
      break;
    case 2:
      tmp_i11 = *(int *)(tmp_i3 + 0x44);
      *(int *)(tmp_i3 + 0x18) = *(int *)(tmp_i3 + 0x18) + 1;
      sweeplist_constprop_3();
      if (*(int *)(tmp_i3 + 8) <= *(int *)(tmp_i3 + 0x18)) {
        *(uint8_t *)(tmp_i3 + 0x15) = 3;
      }
      *(int *)(tmp_i3 + 0x48) = (*(int *)(tmp_i3 + 0x48) + *(int *)(tmp_i3 + 0x44)) - tmp_i11;
      break;
    case 3:
      tmp_i11 = *(int *)(tmp_i3 + 0x44);
      tmp_pi15 = *(int **)(tmp_i3 + 0x20);
      tmp_b9 = *(byte *)(tmp_i3 + 0x14);
      local_34 = 0x29;
switchD_0020fb23_default:
      tmp_pi4 = (int *)*tmp_pi15;
      while( true ) {
        tmp_pi8 = tmp_pi4;
        if ((tmp_pi8 == (int *)0x0) || (local_34 = local_34 + -1, local_34 == 0)) {
          *(int **)(tmp_i3 + 0x20) = tmp_pi15;
          if (*tmp_pi15 == 0) {
            tmp_i16 = *(int *)(param_1 + 0x10);
            tmp_i12 = *(int *)(tmp_i16 + 8);
            tmp_i14 = tmp_i12 + 3;
            if (-1 < tmp_i12) {
              tmp_i14 = tmp_i12;
            }
            if ((*(uint *)(tmp_i16 + 4) < (uint)(tmp_i14 >> 2)) && (0x40 < tmp_i12)) {
              luaS_resize(param_1,tmp_i12 >> 1);
            }
            tmp_u7 = *(uint *)(tmp_i16 + 0x3c);
            if (0x40 < tmp_u7) {
              tmp_u13 = luaM_realloc_(param_1,*(uint32_t *)(tmp_i16 + 0x34),tmp_u7,tmp_u7 >> 1);
              *(uint *)(tmp_i16 + 0x3c) = tmp_u7 >> 1;
              *(uint32_t *)(tmp_i16 + 0x34) = tmp_u13;
            }
            *(uint8_t *)(tmp_i3 + 0x15) = 4;
          }
          *(int *)(tmp_i3 + 0x48) = (*(int *)(tmp_i3 + 0x48) + *(int *)(tmp_i3 + 0x44)) - tmp_i11;
          goto LAB_0020f950;
        }
        if ((char)tmp_pi8[1] == '\b') {
          sweeplist_constprop_3();
        }
        if ((byte)((tmp_b9 ^ 3) & (*(byte *)((int)tmp_pi8 + 5) ^ 3)) == 0) break;
        *(byte *)((int)tmp_pi8 + 5) = *(byte *)((int)tmp_pi8 + 5) & 0xf8 | *(byte *)(tmp_i3 + 0x14) & 3
        ;
        tmp_pi4 = (int *)*tmp_pi8;
        tmp_pi15 = tmp_pi8;
      }
      *tmp_pi15 = *tmp_pi8;
      if (tmp_pi8 == *(int **)(tmp_i3 + 0x1c)) {
        *(int *)(tmp_i3 + 0x1c) = *tmp_pi8;
      }
      switch((char)tmp_pi8[1]) {
      case '\x04':
        tmp_pi4 = (int *)(*(int *)(param_1 + 0x10) + 4);
        *tmp_pi4 = *tmp_pi4 + -1;
        tmp_i16 = tmp_pi8[3] + 0x11;
        break;
      case '\x05':
        luaH_free(param_1,tmp_pi8);
        goto switchD_0020fb23_default;
      case '\x06':
        luaF_freeclosure(param_1,tmp_pi8);
        goto switchD_0020fb23_default;
      case '\a':
        tmp_i16 = tmp_pi8[4] + 0x14;
        break;
      case '\b':
        luaE_freethread(param_1,tmp_pi8);
        goto switchD_0020fb23_default;
      case '\t':
        luaF_freeproto(param_1,tmp_pi8);
        goto switchD_0020fb23_default;
      case '\n':
        luaF_freeupval(param_1,tmp_pi8);
      default:
        goto switchD_0020fb23_default;
      }
      luaM_realloc_(param_1,tmp_pi8,tmp_i16,0);
      goto switchD_0020fb23_default;
    case 4:
      tmp_pi15 = *(int **)(tmp_i3 + 0x30);
      if (tmp_pi15 == (int *)0x0) {
        *(uint8_t *)(tmp_i3 + 0x15) = 0;
        *(uint32_t *)(tmp_i3 + 0x4c) = 0;
      }
      else {
        tmp_pi4 = (int *)*tmp_pi15;
        if (tmp_pi15 == tmp_pi4) {
          *(uint32_t *)(tmp_i3 + 0x30) = 0;
        }
        else {
          *tmp_pi15 = *tmp_pi4;
        }
        *tmp_pi4 = **(uint32_t **)(tmp_i3 + 0x68);
        **(int **)(tmp_i3 + 0x68) = (int)tmp_pi4;
        *(byte *)((int)tmp_pi4 + 5) = *(byte *)((int)tmp_pi4 + 5) & 0xf8 | *(byte *)(tmp_i3 + 0x14) & 3
        ;
        tmp_i11 = tmp_pi4[2];
        if (((tmp_i11 != 0) && ((*(byte *)(tmp_i11 + 6) & 4) == 0)) &&
           (tmp_pu10 = (uint32_t *)
                      luaT_gettm(tmp_i11,2,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xb0)),
           tmp_pu10 != (uint32_t *)0x0)) {
          tmp_u1 = *(uint8_t *)(param_1 + 0x39);
          tmp_u13 = *(uint32_t *)(tmp_i3 + 0x40);
          *(uint8_t *)(param_1 + 0x39) = 0;
          *(int *)(tmp_i3 + 0x40) = *(int *)(tmp_i3 + 0x44) * 2;
          tmp_pu5 = *(uint32_t **)(param_1 + 8);
          tmp_u6 = tmp_pu10[1];
          *tmp_pu5 = *tmp_pu10;
          tmp_pu5[1] = tmp_u6;
          tmp_pu5[2] = tmp_pu10[2];
          tmp_i11 = *(int *)(param_1 + 8);
          *(int **)(tmp_i11 + 0xc) = tmp_pi4;
          *(uint32_t *)(tmp_i11 + 0x14) = 7;
          tmp_i11 = *(int *)(param_1 + 8);
          *(int *)(param_1 + 8) = tmp_i11 + 0x18;
          luaD_call(param_1,tmp_i11,0);
          *(uint8_t *)(param_1 + 0x39) = tmp_u1;
          *(uint32_t *)(tmp_i3 + 0x40) = tmp_u13;
        }
        if (100 < *(uint *)(tmp_i3 + 0x48)) {
          *(uint *)(tmp_i3 + 0x48) = *(uint *)(tmp_i3 + 0x48) - 100;
        }
      }
      break;
    default:
      goto code_r0x0020f681;
    }
LAB_0020f950:
    tmp_b9 = *(byte *)(tmp_i2 + 0x15);
  } while( true );
}

void luaC_barrierf(int param_1,int param_2)
{
  if (*(char *)(*(int *)(param_1 + 0x10) + 0x15) != '\x01') {
    *(byte *)(param_2 + 5) =
         *(byte *)(*(int *)(param_1 + 0x10) + 0x14) & 3 | *(byte *)(param_2 + 5) & 0xf8;
    return;
  }
  reallymarkobject();
  return;
}

void luaC_barrierback(int param_1,int param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x10);
  *(byte *)(param_2 + 5) = *(byte *)(param_2 + 5) & 0xfb;
  *(uint32_t *)(param_2 + 0x18) = *(uint32_t *)(tmp_i1 + 0x28);
  *(int *)(tmp_i1 + 0x28) = param_2;
  return;
}

void luaC_link(int param_1,uint32_t *param_2,uint8_t param_3)
{
  byte tmp_b1;
  int tmp_i2;
  
  tmp_i2 = *(int *)(param_1 + 0x10);
  *param_2 = *(uint32_t *)(tmp_i2 + 0x1c);
  *(uint32_t **)(tmp_i2 + 0x1c) = param_2;
  tmp_b1 = *(byte *)(tmp_i2 + 0x14);
  *(uint8_t *)(param_2 + 1) = param_3;
  *(byte *)((int)param_2 + 5) = tmp_b1 & 3;
  return;
}

void luaC_linkupval(int param_1,uint32_t *param_2)
{
  byte tmp_b1;
  int tmp_i2;
  
  tmp_i2 = *(int *)(param_1 + 0x10);
  *param_2 = *(uint32_t *)(tmp_i2 + 0x1c);
  *(uint32_t **)(tmp_i2 + 0x1c) = param_2;
  tmp_b1 = *(byte *)((int)param_2 + 5);
  if ((tmp_b1 & 7) == 0) {
    if (*(char *)(tmp_i2 + 0x15) == '\x01') {
      *(byte *)((int)param_2 + 5) = tmp_b1 | 4;
      if ((3 < ((int *)param_2[2])[2]) && ((*(byte *)(*(int *)param_2[2] + 5) & 3) != 0)) {
        if (*(char *)(*(int *)(param_1 + 0x10) + 0x15) == '\x01') {
          reallymarkobject();
          return;
        }
        *(byte *)((int)param_2 + 5) = tmp_b1 & 0xf8 | *(byte *)(*(int *)(param_1 + 0x10) + 0x14) & 3;
      }
    }
    else {
      *(byte *)((int)param_2 + 5) = tmp_b1 & 0xf8 | *(byte *)(tmp_i2 + 0x14) & 3;
    }
  }
  return;
}

uint32_t luaopen_package(uint32_t param_1)
{
  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  luaL_newmetatable(param_1,"_LOADLIB");
  tmp_i4 = 0;
  lua_pushcclosure(param_1,gctm,0);
  lua_setfield(param_1,0xfffffffe,&g_unk_0026ea07);
  luaL_register(param_1,"package",pk_funcs);
  lua_pushvalue(param_1,0xffffffff);
  lua_replace(param_1,0xffffd8ef);
  lua_createtable(param_1,0,4);
  tmp_pc1 = loader_preload;
  do {
    tmp_i4 = tmp_i4 + 1;
    lua_pushcclosure(param_1,tmp_pc1,0);
    lua_rawseti(param_1,0xfffffffe,tmp_i4);
    tmp_pc1 = *(void **)(loaders + tmp_i4 * 4);
  } while (tmp_pc1 != (void *)0x0);
  lua_setfield(param_1,0xfffffffe,"loaders");
  tmp_pc2 = getenv("LUA_PATH");
  if (tmp_pc2 == (char *)0x0) {
    lua_pushstring(param_1,
                   "./?.lua;/usr/local/share/lua/5.1/?.lua;/usr/local/share/lua/5.1/?/init.lua;/usr/local/lib/lua/5.1/?.lua;/usr/local/lib/lua/5.1/?/init.lua"
                  );
  }
  else {
    tmp_u3 = luaL_gsub(param_1,tmp_pc2,&g_unk_0026ea10,&g_unk_0026ea0c);
    luaL_gsub(param_1,tmp_u3,&g_unk_0026ea13,
              "./?.lua;/usr/local/share/lua/5.1/?.lua;/usr/local/share/lua/5.1/?/init.lua;/usr/local/lib/lua/5.1/?.lua;/usr/local/lib/lua/5.1/?/init.lua"
             );
    lua_remove(param_1,0xfffffffe);
  }
  lua_setfield(param_1,0xfffffffe,"path");
  tmp_pc2 = getenv("LUA_CPATH");
  if (tmp_pc2 == (char *)0x0) {
    lua_pushstring(param_1,
                   "./?.so;./lib?51.so;/usr/local/lib/lua/5.1/?.so;/usr/local/lib/lua/5.1/lib?51.so;/usr/local/lib/lua/5.1/loadall.so"
                  );
  }
  else {
    tmp_u3 = luaL_gsub(param_1,tmp_pc2,&g_unk_0026ea10,&g_unk_0026ea0c);
    luaL_gsub(param_1,tmp_u3,&g_unk_0026ea13,
              "./?.so;./lib?51.so;/usr/local/lib/lua/5.1/?.so;/usr/local/lib/lua/5.1/lib?51.so;/usr/local/lib/lua/5.1/loadall.so"
             );
    lua_remove(param_1,0xfffffffe);
  }
  lua_setfield(param_1,0xfffffffe,"cpath");
  lua_pushlstring(param_1,&g_unk_0026ea15,9);
  lua_setfield(param_1,0xfffffffe,"config");
  luaL_findtable(param_1,0xffffd8f0,"_LOADED",2);
  lua_setfield(param_1,0xfffffffe,"loaded");
  lua_createtable(param_1,0,0);
  lua_setfield(param_1,0xfffffffe,"preload");
  lua_pushvalue(param_1,0xffffd8ee);
  luaL_register(param_1,0,ll_funcs);
  lua_settop(param_1,0xfffffffe);
  return 1;
}

uint32_t lua_sethook(int param_1,int param_2,int param_3,uint32_t param_4)
{
  if ((param_2 == 0) || (param_3 == 0)) {
    GHIDRA_FIELD(param_3, 0, 1) = 0;
    param_2 = 0;
  }
  else {
  }
  *(int *)(param_1 + 0x44) = param_2;
  *(uint32_t *)(param_1 + 0x3c) = param_4;
  *(uint32_t *)(param_1 + 0x40) = param_4;
  *(uint8_t *)(param_1 + 0x38) = (uint8_t)param_3;
  return 1;
}

uint32_t lua_gethook(int param_1)
{
  return *(uint32_t *)(param_1 + 0x44);
}

uint8_t lua_gethookmask(int param_1)
{
  return *(uint8_t *)(param_1 + 0x38);
}

uint32_t lua_gethookcount(int param_1)
{
  return *(uint32_t *)(param_1 + 0x3c);
}

uint32_t lua_getstack(int param_1,int param_2,int param_3)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  
  tmp_u2 = *(uint *)(param_1 + 0x14);
  if (0 < param_2) {
    do {
      if (tmp_u2 <= *(uint *)(param_1 + 0x28)) {
        return 0;
      }
      param_2 = param_2 + -1;
      if (*(char *)(**(int **)(tmp_u2 + 4) + 6) == '\0') {
        param_2 = param_2 - *(int *)(tmp_u2 + 0x14);
      }
      tmp_u2 = tmp_u2 - 0x18;
    } while (0 < param_2);
  }
  if (param_2 == 0) {
    tmp_u1 = 0;
    if (*(uint *)(param_1 + 0x28) < tmp_u2) {
      *(int *)(param_3 + 0x60) = ((int)(tmp_u2 - *(uint *)(param_1 + 0x28)) >> 3) * -0x55555555;
      return 1;
    }
  }
  else {
    *(uint32_t *)(param_3 + 0x60) = 0;
    tmp_u1 = 1;
  }
  return tmp_u1;
}

char * lua_getlocal(int param_1,int param_2,int param_3)
{
  int *tmp_pi1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  int tmp_i6;
  
  tmp_pi1 = (int *)(*(int *)(param_1 + 0x28) + *(int *)(param_2 + 0x60) * 0x18);
  tmp_pi2 = (int *)tmp_pi1[1];
  if (((tmp_pi2[2] == 6) && (*(char *)(*tmp_pi2 + 6) == '\0')) &&
     (tmp_i3 = *(int *)(*tmp_pi2 + 0x10), tmp_i3 != 0)) {
    if (tmp_pi1 == *(int **)(param_1 + 0x14)) {
      tmp_i4 = *(int *)(param_1 + 0x18);
      tmp_pi1[3] = tmp_i4;
      tmp_i6 = *(int *)(*tmp_pi2 + 0x10);
    }
    else {
      tmp_i4 = tmp_pi1[3];
      tmp_i6 = tmp_i3;
    }
    tmp_pc5 = (char *)luaF_getlocalname(tmp_i3,param_3,(tmp_i4 - *(int *)(tmp_i6 + 0xc) >> 2) + -1);
    if (tmp_pc5 != (char *)0x0) {
      tmp_i4 = *tmp_pi1;
      goto LAB_0021245e;
    }
  }
  if (tmp_pi1 == *(int **)(param_1 + 0x14)) {
    tmp_i3 = *(int *)(param_1 + 8);
  }
  else {
    tmp_i3 = tmp_pi1[7];
  }
  tmp_i4 = *tmp_pi1;
  if (((tmp_i3 - tmp_i4 >> 2) * -0x55555555 < param_3) || (tmp_pc5 = "(*temporary)", param_3 < 1)) {
    return (char *)0x0;
  }
LAB_0021245e:
  luaA_pushobject(param_1,tmp_i4 + param_3 * 0xc + -0xc);
  return tmp_pc5;
}

char * lua_setlocal(int param_1,int param_2,int param_3)
{
  int *tmp_pi1;
  int *tmp_pi2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  char *tmp_pc6;
  int tmp_i7;
  uint32_t *tmp_pu8;
  
  tmp_pi1 = (int *)(*(int *)(param_1 + 0x28) + *(int *)(param_2 + 0x60) * 0x18);
  tmp_pi2 = (int *)tmp_pi1[1];
  if (((tmp_pi2[2] == 6) && (*(char *)(*tmp_pi2 + 6) == '\0')) &&
     (tmp_i7 = *(int *)(*tmp_pi2 + 0x10), tmp_i7 != 0)) {
    if (tmp_pi1 == *(int **)(param_1 + 0x14)) {
      tmp_i5 = *(int *)(param_1 + 0x18);
      tmp_pi1[3] = tmp_i5;
      tmp_i4 = *(int *)(*tmp_pi2 + 0x10);
    }
    else {
      tmp_i5 = tmp_pi1[3];
      tmp_i4 = tmp_i7;
    }
    tmp_pc6 = (char *)luaF_getlocalname(tmp_i7,param_3,(tmp_i5 - *(int *)(tmp_i4 + 0xc) >> 2) + -1);
    if (tmp_pc6 == (char *)0x0) goto LAB_0021253f;
    tmp_i7 = *tmp_pi1;
    tmp_i5 = *(int *)(param_1 + 8);
  }
  else {
LAB_0021253f:
    if (tmp_pi1 == *(int **)(param_1 + 0x14)) {
      tmp_i4 = *(int *)(param_1 + 8);
      tmp_i5 = tmp_i4;
    }
    else {
      tmp_i4 = tmp_pi1[7];
      tmp_i5 = *(int *)(param_1 + 8);
    }
    tmp_i7 = *tmp_pi1;
    if (((tmp_i4 - tmp_i7 >> 2) * -0x55555555 < param_3) || (tmp_pc6 = "(*temporary)", param_3 < 1)) {
      tmp_pc6 = (char *)0x0;
      goto LAB_00212592;
    }
  }
  tmp_pu8 = (uint32_t *)(tmp_i7 + param_3 * 0xc + -0xc);
  tmp_u3 = *(uint32_t *)(tmp_i5 + -0xc);
  tmp_pu8[1] = *(uint32_t *)(tmp_i5 + -8);
  *tmp_pu8 = tmp_u3;
  tmp_pu8[2] = *(uint32_t *)(tmp_i5 + -4);
  tmp_i5 = *(int *)(param_1 + 8);
LAB_00212592:
  *(int *)(param_1 + 8) = tmp_i5 + -0xc;
  return tmp_pc6;
}

uint32_t lua_getinfo(int param_1,char *param_2,int param_3)
{
  int *tmp_pi1;
  uint tmp_u2;
  char tmp_c3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  uint32_t tmp_u6;
  uint32_t *tmp_pu7;
  char *tmp_pc8;
  int tmp_i9;
  uint tmp_u10;
  char *tmp_pc11;
  int tmp_i12;
  int tmp_i13;
  uint32_t local_2c;
  int local_28;
  
  if (*param_2 == '>') {
    param_2 = param_2 + 1;
    local_28 = 0;
    tmp_i13 = *(int *)(*(int *)(param_1 + 8) + -0xc);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0xc;
LAB_00212664:
    if (tmp_i13 != 0) {
      local_2c = 1;
      tmp_c3 = *param_2;
      tmp_pc11 = param_2;
joined_r0x0021268c:
      if (tmp_c3 != '\0') {
        do {
          switch(tmp_c3) {
          case 'L':
          case 'f':
            goto _L278;
          default:
            tmp_pc11 = tmp_pc11 + 1;
            tmp_c3 = *tmp_pc11;
            local_2c = 0;
            if (tmp_c3 == '\0') goto LAB_00212726;
            break;
          case 'S':
            if (*(char *)(tmp_i13 + 6) == '\0') {
              tmp_pu4 = (uint8_t *)(*(int *)(*(int *)(tmp_i13 + 0x10) + 0x20) + 0x10);
              *(uint8_t **)(param_3 + 0x10) = tmp_pu4;
              tmp_i5 = *(int *)(*(int *)(tmp_i13 + 0x10) + 0x3c);
              *(int *)(param_3 + 0x1c) = tmp_i5;
              *(uint32_t *)(param_3 + 0x20) = *(uint32_t *)(*(int *)(tmp_i13 + 0x10) + 0x40);
              if (tmp_i5 == 0) {
                tmp_pc8 = "main";
              }
              else {
                tmp_pc8 = "Lua";
              }
              *(char **)(param_3 + 0xc) = tmp_pc8;
            }
            else {
              tmp_pu4 = &g_unk_0026ee02;
              *(uint8_t **)(param_3 + 0x10) = &g_unk_0026ee02;
              *(uint32_t *)(param_3 + 0x1c) = 0xffffffff;
              *(uint32_t *)(param_3 + 0x20) = 0xffffffff;
              *(uint8_t **)(param_3 + 0xc) = &g_unk_0024ae19;
            }
            luaO_chunkid(param_3 + 0x24,tmp_pu4,0x3c);
            tmp_c3 = tmp_pc11[1];
            goto joined_r0x00212914;
          case 'l':
            if (((local_28 == 0) || (tmp_pi1 = *(int **)(local_28 + 4), tmp_pi1[2] != 6)) ||
               (tmp_i5 = *tmp_pi1, *(char *)(tmp_i5 + 6) != '\0')) {
LAB_00212940:
              tmp_u6 = 0xffffffff;
            }
            else {
              if (local_28 == *(int *)(param_1 + 0x14)) {
                tmp_i12 = *(int *)(param_1 + 0x18);
                *(int *)(local_28 + 0xc) = tmp_i12;
                tmp_i5 = *tmp_pi1;
              }
              else {
                tmp_i12 = *(int *)(local_28 + 0xc);
              }
              tmp_i12 = (tmp_i12 - *(int *)(*(int *)(tmp_i5 + 0x10) + 0xc) >> 2) + -1;
              if (tmp_i12 < 0) goto LAB_00212940;
              tmp_i5 = *(int *)(*(int *)(tmp_i5 + 0x10) + 0x14);
              if (tmp_i5 == 0) {
                tmp_u6 = 0;
              }
              else {
                tmp_u6 = *(uint32_t *)(tmp_i5 + tmp_i12 * 4);
              }
            }
            *(uint32_t *)(param_3 + 0x14) = tmp_u6;
            goto _L278;
          case 'n':
            if (((local_28 != 0) &&
                ((((*(int **)(local_28 + 4))[2] != 6 ||
                  (*(char *)(**(int **)(local_28 + 4) + 6) != '\0')) ||
                 (*(int *)(local_28 + 0x14) < 1)))) &&
               ((tmp_pi1 = *(int **)(local_28 + -0x14), tmp_pi1[2] == 6 &&
                (*(char *)(*tmp_pi1 + 6) == '\0')))) {
              tmp_i5 = *(int *)(*(int *)(*tmp_pi1 + 0x10) + 0xc);
              if (local_28 + -0x18 == *(int *)(param_1 + 0x14)) {
                tmp_i12 = *(int *)(param_1 + 0x18);
                *(int *)(local_28 + -0xc) = tmp_i12;
                tmp_i9 = *(int *)(*(int *)(*tmp_pi1 + 0x10) + 0xc);
              }
              else {
                tmp_i12 = *(int *)(local_28 + -0xc);
                tmp_i9 = tmp_i5;
              }
              tmp_u2 = *(uint *)(tmp_i5 + ((tmp_i12 - tmp_i9 >> 2) + -1) * 4);
              tmp_u10 = tmp_u2 & 0x3f;
              if ((tmp_u10 - 0x1c < 2) || (tmp_u10 == 0x21)) {
                tmp_i5 = getobjname(tmp_u2 >> 6 & 0xff,param_3 + 4);
                *(int *)(param_3 + 8) = tmp_i5;
                if (tmp_i5 != 0) goto _L278;
              }
            }
            *(uint32_t *)(param_3 + 4) = 0;
            *(uint8_t **)(param_3 + 8) = &g_unk_0026ea14;
            tmp_c3 = tmp_pc11[1];
            goto joined_r0x00212914;
          case 'u':
            *(uint *)(param_3 + 0x18) = (uint)*(byte *)(tmp_i13 + 7);
            tmp_c3 = tmp_pc11[1];
            goto joined_r0x00212914;
          }
        } while( true );
      }
LAB_00212726:
      tmp_pc11 = strchr(param_2,0x66);
      if (tmp_pc11 != (char *)0x0) {
        tmp_pi1 = *(int **)(param_1 + 8);
        *tmp_pi1 = tmp_i13;
        tmp_pi1[2] = 6;
        goto LAB_0021274f;
      }
      tmp_pc11 = strchr(param_2,0x4c);
      if (tmp_pc11 == (char *)0x0) {
        return local_2c;
      }
      goto LAB_00212783;
    }
  }
  else if (*(int *)(param_3 + 0x60) != 0) {
    local_28 = *(int *)(param_1 + 0x28) + *(int *)(param_3 + 0x60) * 0x18;
    tmp_i13 = **(int **)(local_28 + 4);
    goto LAB_00212664;
  }
  *(uint8_t **)(param_3 + 8) = &g_unk_0026ea14;
  *(uint8_t **)(param_3 + 4) = &g_unk_0026ea14;
  *(char **)(param_3 + 0xc) = "tail";
  *(char **)(param_3 + 0x10) = "=(tail call)";
  *(uint32_t *)(param_3 + 0x14) = 0xffffffff;
  *(uint32_t *)(param_3 + 0x1c) = 0xffffffff;
  *(uint32_t *)(param_3 + 0x20) = 0xffffffff;
  luaO_chunkid(param_3 + 0x24,"=(tail call)",0x3c);
  *(uint32_t *)(param_3 + 0x18) = 0;
  tmp_pc11 = strchr(param_2,0x66);
  if (tmp_pc11 == (char *)0x0) {
    tmp_pc11 = strchr(param_2,0x4c);
    local_2c = 1;
    if (tmp_pc11 == (char *)0x0) {
      return 1;
    }
  }
  else {
    tmp_i13 = 0;
    *(uint32_t *)(*(int *)(param_1 + 8) + 8) = 0;
    local_2c = 1;
LAB_0021274f:
    tmp_i5 = *(int *)(param_1 + 8);
    if (*(int *)(param_1 + 0x1c) - tmp_i5 < 0xd) {
      luaD_growstack(param_1,1);
      tmp_i5 = *(int *)(param_1 + 8);
    }
    *(int *)(param_1 + 8) = tmp_i5 + 0xc;
    tmp_pc11 = strchr(param_2,0x4c);
    if (tmp_pc11 == (char *)0x0) {
      return local_2c;
    }
    if (tmp_i13 != 0) {
LAB_00212783:
      if (*(char *)(tmp_i13 + 6) == '\0') {
        tmp_u6 = luaH_new(param_1,0,0);
        tmp_i5 = *(int *)(*(int *)(tmp_i13 + 0x10) + 0x14);
        if (0 < *(int *)(*(int *)(tmp_i13 + 0x10) + 0x30)) {
          tmp_i12 = 0;
          do {
            tmp_i9 = tmp_i12 * 4;
            tmp_i12 = tmp_i12 + 1;
            tmp_pu7 = (uint32_t *)luaH_setnum(param_1,tmp_u6,*(uint32_t *)(tmp_i5 + tmp_i9));
            *tmp_pu7 = 1;
            tmp_pu7[2] = 1;
          } while (tmp_i12 < *(int *)(*(int *)(tmp_i13 + 0x10) + 0x30));
        }
        tmp_pu7 = *(uint32_t **)(param_1 + 8);
        tmp_pu7[2] = 5;
        *tmp_pu7 = tmp_u6;
        goto LAB_00212797;
      }
    }
  }
  *(uint32_t *)(*(int *)(param_1 + 8) + 8) = 0;
LAB_00212797:
  tmp_i13 = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 0x1c) - tmp_i13 < 0xd) {
    luaD_growstack(param_1,1);
    tmp_i13 = *(int *)(param_1 + 8);
  }
  *(int *)(param_1 + 8) = tmp_i13 + 0xc;
  return local_2c;
_L278:
  tmp_c3 = tmp_pc11[1];
joined_r0x00212914:
  tmp_pc11 = tmp_pc11 + 1;
  goto joined_r0x0021268c;
}

bool luaG_checkopenop(uint param_1)
{
  uint tmp_u1;
  
  tmp_u1 = (param_1 & 0x3f) - 0x1c;
  if ((tmp_u1 < 7) && ((1 << ((byte)tmp_u1 & 0x1f) & 0x47U) != 0)) {
    return param_1 >> 0x17 == 0;
  }
  return false;
}

uint64_t luaG_checkcode(void)
{
  int tmp_i1;
  
  tmp_i1 = symbexec();
  return CONCAT44(0xff,(uint)(tmp_i1 != 0));
}

void luaG_errormsg(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  
  if (*(int *)(param_1 + 0x6c) != 0) {
    tmp_pu4 = (uint32_t *)(*(int *)(param_1 + 0x6c) + *(int *)(param_1 + 0x20));
    if (tmp_pu4[2] != 6) {
      luaD_throw(param_1,5);
    }
    tmp_pu1 = *(uint32_t **)(param_1 + 8);
    *tmp_pu1 = tmp_pu1[-3];
    tmp_pu1[1] = tmp_pu1[-2];
    tmp_pu1[2] = tmp_pu1[-1];
    tmp_u2 = tmp_pu4[1];
    tmp_i3 = *(int *)(param_1 + 8);
    *(uint32_t *)(tmp_i3 + -0xc) = *tmp_pu4;
    *(uint32_t *)(tmp_i3 + -8) = tmp_u2;
    *(uint32_t *)(tmp_i3 + -4) = tmp_pu4[2];
    tmp_i3 = *(int *)(param_1 + 8);
    if (*(int *)(param_1 + 0x1c) - tmp_i3 < 0xd) {
      luaD_growstack(param_1,1);
      tmp_i3 = *(int *)(param_1 + 8);
    }
    *(int *)(param_1 + 8) = tmp_i3 + 0xc;
    luaD_call(param_1,tmp_i3 + -0xc,1);
  }
  luaD_throw(param_1,2);
}

void luaG_runerror(int param_1,uint32_t param_2)
{
  int *tmp_pi1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  void *tmp_pc4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint32_t *tmp_pu8;
  uint8_t local_58 [72];
  
  tmp_u5 = luaO_pushvfstring(param_1,param_2,&stack0x0000000c);
  tmp_pi1 = *(int **)(*(int *)(param_1 + 0x14) + 4);
  if ((tmp_pi1[2] == 6) && (*(char *)(*tmp_pi1 + 6) == '\0')) {
    tmp_i6 = *(int *)(param_1 + 0x18);
    *(int *)(*(int *)(param_1 + 0x14) + 0xc) = tmp_i6;
    tmp_i3 = *(int *)(*tmp_pi1 + 0x10);
    tmp_i6 = (tmp_i6 - *(int *)(tmp_i3 + 0xc) >> 2) + -1;
    if (tmp_i6 < 0) {
      tmp_u7 = 0xffffffff;
    }
    else if (*(int *)(tmp_i3 + 0x14) == 0) {
      tmp_u7 = 0;
    }
    else {
      tmp_u7 = *(uint32_t *)(*(int *)(tmp_i3 + 0x14) + tmp_i6 * 4);
    }
    if ((tmp_pi1[2] != 6) || (*(char *)(*tmp_pi1 + 6) != '\0')) {
      tmp_pc4 = (void *)invalidInstructionException();
      (*tmp_pc4)();
    }
    luaO_chunkid(local_58,*(int *)(tmp_i3 + 0x20) + 0x10,0x3c);
    luaO_pushfstring(param_1,"%s:%d: %s",local_58,tmp_u7,tmp_u5);
  }
  if (*(int *)(param_1 + 0x6c) != 0) {
    tmp_pu8 = (uint32_t *)(*(int *)(param_1 + 0x6c) + *(int *)(param_1 + 0x20));
    if (tmp_pu8[2] != 6) {
      luaD_throw(param_1,5);
    }
    tmp_pu2 = *(uint32_t **)(param_1 + 8);
    *tmp_pu2 = tmp_pu2[-3];
    tmp_pu2[1] = tmp_pu2[-2];
    tmp_pu2[2] = tmp_pu2[-1];
    tmp_u5 = tmp_pu8[1];
    tmp_i6 = *(int *)(param_1 + 8);
    *(uint32_t *)(tmp_i6 + -0xc) = *tmp_pu8;
    *(uint32_t *)(tmp_i6 + -8) = tmp_u5;
    *(uint32_t *)(tmp_i6 + -4) = tmp_pu8[2];
    tmp_i6 = *(int *)(param_1 + 8);
    if (*(int *)(param_1 + 0x1c) - tmp_i6 < 0xd) {
      luaD_growstack(param_1,1);
      tmp_i6 = *(int *)(param_1 + 8);
    }
    *(int *)(param_1 + 8) = tmp_i6 + 0xc;
    luaD_call(param_1,tmp_i6 + -0xc,1);
  }
  luaD_throw(param_1,2);
}

void luaG_typeerror(int param_1,uint param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t local_20 [4];
  
  local_20[0] = 0;
  tmp_u3 = **(uint **)(param_1 + 0x14);
  tmp_u1 = *(uint32_t *)(luaT_typenames + *(int *)(param_2 + 8) * 4);
  do {
    if ((*(uint **)(param_1 + 0x14))[2] <= tmp_u3) {
LAB_00212f48:
      luaG_runerror(param_1,"attempt to %s a %s value",param_3,tmp_u1);
      return;
    }
    if (param_2 == tmp_u3) {
      tmp_i2 = getobjname(((int)(param_2 - *(int *)(param_1 + 0xc)) >> 2) * -0x55555555,local_20);
      if (tmp_i2 != 0) {
        luaG_runerror(param_1,"attempt to %s %s \'%s\' (a %s value)",param_3,tmp_i2,local_20[0],tmp_u1
                     );
        return;
      }
      goto LAB_00212f48;
    }
    tmp_u3 = tmp_u3 + 0xc;
  } while( true );
}

uint32_t luaG_ordererror(uint32_t param_1,int param_2,int param_3)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(luaT_typenames + *(int *)(param_2 + 8) * 4);
  if (*(char *)(tmp_i1 + 2) != *(char *)(*(int *)(luaT_typenames + *(int *)(param_3 + 8) * 4) + 2)) {
    luaG_runerror(param_1,"attempt to compare %s with %s",tmp_i1,
                  *(int *)(luaT_typenames + *(int *)(param_3 + 8) * 4));
    return 0;
  }
  luaG_runerror(param_1,"attempt to compare two %s values",tmp_i1);
  return 0;
}

void luaG_concaterror(int param_1,uint param_2,uint param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t local_20 [4];
  
  tmp_i2 = *(int *)(param_2 + 8);
  if (tmp_i2 - 3U < 2) {
    tmp_i2 = *(int *)(param_3 + 8);
    param_2 = param_3;
  }
  tmp_u1 = *(uint32_t *)(luaT_typenames + tmp_i2 * 4);
  local_20[0] = 0;
  tmp_u3 = **(uint **)(param_1 + 0x14);
  do {
    if ((*(uint **)(param_1 + 0x14))[2] <= tmp_u3) {
LAB_002130b8:
      luaG_runerror(param_1,"attempt to %s a %s value","concatenate",tmp_u1);
      return;
    }
    if (param_2 == tmp_u3) {
      tmp_i2 = getobjname(((int)(param_2 - *(int *)(param_1 + 0xc)) >> 2) * -0x55555555,local_20);
      if (tmp_i2 != 0) {
        luaG_runerror(param_1,"attempt to %s %s \'%s\' (a %s value)","concatenate",tmp_i2,local_20[0]
                      ,tmp_u1);
        return;
      }
      goto LAB_002130b8;
    }
    tmp_u3 = tmp_u3 + 0xc;
  } while( true );
}

void luaG_aritherror(int param_1,uint param_2,uint param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t local_2c;
  uint8_t local_28 [24];
  
  tmp_i2 = luaV_tonumber(param_2,local_28);
  if (tmp_i2 == 0) {
    param_3 = param_2;
  }
  local_2c = 0;
  tmp_u1 = *(uint32_t *)(luaT_typenames + *(int *)(param_3 + 8) * 4);
  tmp_u3 = **(uint **)(param_1 + 0x14);
  do {
    if ((*(uint **)(param_1 + 0x14))[2] <= tmp_u3) {
LAB_002131a0:
      luaG_runerror(param_1,"attempt to %s a %s value","perform arithmetic on",tmp_u1);
      return;
    }
    if (param_3 == tmp_u3) {
      tmp_i2 = getobjname(((int)(param_3 - *(int *)(param_1 + 0xc)) >> 2) * -0x55555555,&local_2c);
      if (tmp_i2 != 0) {
        luaG_runerror(param_1,"attempt to %s %s \'%s\' (a %s value)","perform arithmetic on",tmp_i2,
                      local_2c,tmp_u1);
        return;
      }
      goto LAB_002131a0;
    }
    tmp_u3 = tmp_u3 + 0xc;
  } while( true );
}

void luaL_openlibs(uint32_t param_1)
{
  void *tmp_pc1;
  uint8_t **tmp_ppu2;
  
  tmp_pc1 = luaopen_base;
  tmp_ppu2 = &lualibs;
  do {
    lua_pushcclosure(param_1,tmp_pc1,0);
    lua_pushstring(param_1,*tmp_ppu2);
    lua_call(param_1,1,0);
    tmp_pc1 = (void *)tmp_ppu2[3];
    tmp_ppu2 = tmp_ppu2 + 2;
  } while (tmp_pc1 != (void *)0x0);
  return;
}

void luaF_newCclosure(uint32_t param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  
  tmp_i1 = luaM_realloc_(param_1,0,0,(param_2 * 3 + -3) * 4 + 0x20);
  luaC_link(param_1,tmp_i1,6);
  *(uint8_t *)(tmp_i1 + 6) = 1;
  *(uint32_t *)(tmp_i1 + 0xc) = param_3;
  *(char *)(tmp_i1 + 7) = (char)param_2;
  return;
}

int luaF_newLclosure(uint32_t param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint32_t *tmp_pu4;
  byte tmp_b5;
  
  tmp_b5 = 0;
  tmp_u3 = param_2 * 4;
  tmp_i1 = luaM_realloc_(param_1,0,0,tmp_u3 + 0x14);
  luaC_link(param_1,tmp_i1,6);
  *(uint8_t *)(tmp_i1 + 6) = 0;
  *(uint32_t *)(tmp_i1 + 0xc) = param_3;
  *(char *)(tmp_i1 + 7) = (char)param_2;
  if (param_2 != 0) {
    tmp_pu4 = (uint32_t *)(tmp_i1 + tmp_u3 + 0x14 + param_2 * -4);
    if (7 < tmp_u3) {
      tmp_u2 = tmp_u3;
      if (((uint)tmp_pu4 & 1) != 0) {
        *(uint8_t *)tmp_pu4 = 0;
        tmp_u2 = tmp_u3 - 1;
        tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 1);
      }
      if (((uint)tmp_pu4 & 2) != 0) {
        *(uint16_t *)tmp_pu4 = 0;
        tmp_u2 = tmp_u2 - 2;
        tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
      }
      if (((uint)tmp_pu4 & 4) != 0) {
        *tmp_pu4 = 0;
        tmp_u2 = tmp_u2 - 4;
        tmp_pu4 = tmp_pu4 + 1;
      }
      tmp_u3 = tmp_u2 & 3;
      for (tmp_u2 = tmp_u2 >> 2; tmp_u2 != 0; tmp_u2 = tmp_u2 - 1) {
        *tmp_pu4 = 0;
        tmp_pu4 = tmp_pu4 + (uint)tmp_b5 * -2 + 1;
      }
    }
    if ((tmp_u3 & 4) != 0) {
      *tmp_pu4 = 0;
      tmp_pu4 = tmp_pu4 + 1;
    }
    if ((tmp_u3 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    }
    if ((tmp_u3 & 1) != 0) {
      *(uint8_t *)tmp_pu4 = 0;
    }
  }
  return tmp_i1;
}

void luaF_newupval(uint32_t param_1)
{
  int tmp_i1;
  
  tmp_i1 = luaM_realloc_(param_1,0,0,0x18);
  luaC_link(param_1,tmp_i1,10);
  *(int *)(tmp_i1 + 8) = tmp_i1 + 0xc;
  *(uint32_t *)(tmp_i1 + 0x14) = 0;
  return;
}

int * luaF_findupval(int param_1,uint param_2)
{
  byte tmp_b1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int *tmp_pi5;
  int *tmp_pi6;
  int *tmp_pi7;
  
  tmp_pi6 = *(int **)(param_1 + 0x60);
  tmp_pi7 = (int *)(param_1 + 0x60);
  tmp_i2 = *(int *)(param_1 + 0x10);
  if (tmp_pi6 != (int *)0x0) {
    tmp_u3 = tmp_pi6[2];
    while (tmp_pi5 = tmp_pi6, param_2 <= tmp_u3) {
      if (tmp_u3 == param_2) {
        if ((*(byte *)((int)tmp_pi5 + 5) & 3 & (*(byte *)(tmp_i2 + 0x14) ^ 3)) != 0) {
          *(byte *)((int)tmp_pi5 + 5) = *(byte *)((int)tmp_pi5 + 5) ^ 3;
        }
        return tmp_pi5;
      }
      tmp_pi6 = (int *)*tmp_pi5;
      tmp_pi7 = tmp_pi5;
      if (tmp_pi6 == (int *)0x0) break;
      tmp_u3 = tmp_pi6[2];
    }
  }
  tmp_pi6 = (int *)luaM_realloc_(param_1,0,0,0x18);
  *(uint8_t *)(tmp_pi6 + 1) = 10;
  tmp_b1 = *(byte *)(tmp_i2 + 0x14);
  tmp_pi6[2] = param_2;
  *(byte *)((int)tmp_pi6 + 5) = tmp_b1 & 3;
  *tmp_pi6 = *tmp_pi7;
  *tmp_pi7 = (int)tmp_pi6;
  tmp_pi6[3] = tmp_i2 + 0x6c;
  tmp_i4 = *(int *)(tmp_i2 + 0x7c);
  tmp_pi6[4] = tmp_i4;
  *(int **)(tmp_i4 + 0xc) = tmp_pi6;
  *(int **)(tmp_i2 + 0x7c) = tmp_pi6;
  return tmp_pi6;
}

void luaF_freeupval(uint32_t param_1,int param_2)
{
  if (*(int *)(param_2 + 8) != param_2 + 0xc) {
    *(uint32_t *)(*(int *)(param_2 + 0x10) + 0xc) = *(uint32_t *)(param_2 + 0xc);
    *(uint32_t *)(*(int *)(param_2 + 0xc) + 0x10) = *(uint32_t *)(param_2 + 0x10);
  }
  luaM_realloc_(param_1,param_2,0x18,0);
  return;
}

void luaF_close(int param_1,uint param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  uint32_t *tmp_pu4;
  
  tmp_i1 = *(int *)(param_1 + 0x10);
  do {
    tmp_pu4 = *(uint32_t **)(param_1 + 0x60);
    if (tmp_pu4 == (uint32_t *)0x0) {
      return;
    }
    while( true ) {
      if ((uint)tmp_pu4[2] < param_2) {
        return;
      }
      *(uint32_t *)(param_1 + 0x60) = *tmp_pu4;
      if ((*(byte *)((int)tmp_pu4 + 5) & 3 & (*(byte *)(tmp_i1 + 0x14) ^ 3)) == 0) break;
      if ((uint32_t *)tmp_pu4[2] != tmp_pu4 + 3) {
        *(uint32_t *)(tmp_pu4[4] + 0xc) = tmp_pu4[3];
        *(uint32_t *)(tmp_pu4[3] + 0x10) = tmp_pu4[4];
      }
      luaM_realloc_(param_1,tmp_pu4,0x18,0);
      tmp_pu4 = *(uint32_t **)(param_1 + 0x60);
      if (tmp_pu4 == (uint32_t *)0x0) {
        return;
      }
    }
    *(uint32_t *)(tmp_pu4[4] + 0xc) = tmp_pu4[3];
    *(uint32_t *)(tmp_pu4[3] + 0x10) = tmp_pu4[4];
    tmp_pu2 = (uint32_t *)tmp_pu4[2];
    tmp_u3 = tmp_pu2[1];
    tmp_pu4[3] = *tmp_pu2;
    tmp_pu4[4] = tmp_u3;
    tmp_pu4[5] = tmp_pu2[2];
    tmp_pu4[2] = tmp_pu4 + 3;
    luaC_linkupval(param_1,tmp_pu4);
  } while( true );
}

void luaF_newproto(uint32_t param_1)
{
  int tmp_i1;
  
  tmp_i1 = luaM_realloc_(param_1,0,0,0x4c);
  luaC_link(param_1,tmp_i1,9);
  *(uint32_t *)(tmp_i1 + 8) = 0;
  *(uint32_t *)(tmp_i1 + 0x28) = 0;
  *(uint32_t *)(tmp_i1 + 0x10) = 0;
  *(uint32_t *)(tmp_i1 + 0x34) = 0;
  *(uint32_t *)(tmp_i1 + 0xc) = 0;
  *(uint32_t *)(tmp_i1 + 0x2c) = 0;
  *(uint32_t *)(tmp_i1 + 0x30) = 0;
  *(uint32_t *)(tmp_i1 + 0x24) = 0;
  *(uint8_t *)(tmp_i1 + 0x48) = 0;
  *(uint32_t *)(tmp_i1 + 0x1c) = 0;
  *(uint8_t *)(tmp_i1 + 0x49) = 0;
  *(uint8_t *)(tmp_i1 + 0x4a) = 0;
  *(uint8_t *)(tmp_i1 + 0x4b) = 0;
  *(uint32_t *)(tmp_i1 + 0x14) = 0;
  *(uint32_t *)(tmp_i1 + 0x38) = 0;
  *(uint32_t *)(tmp_i1 + 0x18) = 0;
  *(uint32_t *)(tmp_i1 + 0x3c) = 0;
  *(uint32_t *)(tmp_i1 + 0x40) = 0;
  *(uint32_t *)(tmp_i1 + 0x20) = 0;
  return;
}

void luaF_freeproto(uint32_t param_1,int param_2)
{
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 0xc),*(int *)(param_2 + 0x2c) << 2,0);
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 0x10),*(int *)(param_2 + 0x34) << 2,0);
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 8),*(int *)(param_2 + 0x28) * 0xc,0);
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 0x14),*(int *)(param_2 + 0x30) << 2,0);
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 0x18),*(int *)(param_2 + 0x38) * 0xc,0);
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 0x1c),*(int *)(param_2 + 0x24) << 2,0);
  luaM_realloc_(param_1,param_2,0x4c,0);
  return;
}

void luaF_freeclosure(uint32_t param_1,int param_2)
{
  int tmp_i1;
  
  if (*(char *)(param_2 + 6) == '\0') {
    tmp_i1 = (uint)*(byte *)(param_2 + 7) * 4 + 0x14;
  }
  else {
    tmp_i1 = ((uint)*(byte *)(param_2 + 7) * 3 + -3) * 4 + 0x20;
  }
  luaM_realloc_(param_1,param_2,tmp_i1,0);
  return;
}

int luaF_getlocalname(int param_1,int param_2,int param_3)
{
  int *tmp_pi1;
  int *tmp_pi2;
  int tmp_i3;
  
  if ((0 < *(int *)(param_1 + 0x38)) && ((*(int **)(param_1 + 0x18))[1] <= param_3)) {
    tmp_i3 = 0;
    tmp_pi2 = *(int **)(param_1 + 0x18);
    do {
      if ((param_3 < tmp_pi2[2]) && (param_2 = param_2 + -1, param_2 == 0)) {
        return *tmp_pi2 + 0x10;
      }
      tmp_i3 = tmp_i3 + 1;
    } while ((tmp_i3 != *(int *)(param_1 + 0x38)) &&
            (tmp_pi1 = tmp_pi2 + 4, tmp_pi2 = tmp_pi2 + 3, *tmp_pi1 <= param_3));
  }
  return 0;
}

uint32_t luaH_next(uint32_t param_1,int param_2,double *param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  int local_30;
  int local_24;
  
  if (*(int *)(param_3 + 1) == 0) {
    tmp_i3 = *(int *)(param_2 + 0x1c);
    local_24 = 0;
  }
  else if ((((*(int *)(param_3 + 1) != 3) ||
            (local_24 = SUB84(*param_3 + 6755399441055744.0,0), *param_3 != (double)local_24)) ||
           (local_24 < 1)) || (tmp_i3 = *(int *)(param_2 + 0x1c), tmp_i3 < local_24)) {
    tmp_i2 = mainposition();
    do {
      tmp_i3 = luaO_rawequalObj(tmp_i2 + 0xc,param_3);
      if ((tmp_i3 != 0) ||
         (((*(int *)(tmp_i2 + 0x14) == 0xb && (3 < *(int *)(param_3 + 1))) &&
          (*(int *)(tmp_i2 + 0xc) == *(int *)param_3)))) {
        tmp_i3 = *(int *)(param_2 + 0x1c);
        local_24 = tmp_i3 + 1 + (tmp_i2 - *(int *)(param_2 + 0x10) >> 2) * -0x49249249;
        goto LAB_00213a75;
      }
      tmp_i2 = *(int *)(tmp_i2 + 0x18);
    } while (tmp_i2 != 0);
    luaG_runerror(param_1,"invalid key to \'next\'");
    tmp_i3 = *(int *)(param_2 + 0x1c);
    local_24 = 1;
  }
LAB_00213a75:
  if (tmp_i3 <= local_24) {
LAB_00213ab5:
    local_24 = local_24 - tmp_i3;
    tmp_i3 = 1 << (*(byte *)(param_2 + 7) & 0x1f);
    if (local_24 < tmp_i3) {
      tmp_i2 = *(int *)(param_2 + 0x10);
      local_30 = local_24 * 0x1c;
      tmp_i4 = local_30 + tmp_i2;
      if (*(int *)(tmp_i4 + 8) != 0) {
LAB_00213c08:
        tmp_u1 = *(uint32_t *)(tmp_i4 + 0x10);
        *(uint32_t *)param_3 = *(uint32_t *)(tmp_i4 + 0xc);
        *(uint32_t *)((int)param_3 + 4) = tmp_u1;
        *(uint32_t *)(param_3 + 1) = *(uint32_t *)(tmp_i4 + 0x14);
        tmp_pu5 = (uint32_t *)(local_30 + *(int *)(param_2 + 0x10));
        goto LAB_00213b5b;
      }
      local_24 = local_24 + 1;
      tmp_i4 = local_24 * 0x1c + tmp_i2;
      for (; local_24 != tmp_i3; local_24 = local_24 + 1) {
        local_30 = tmp_i4 - tmp_i2;
        if (*(int *)(tmp_i4 + 8) != 0) goto LAB_00213c08;
        tmp_i4 = tmp_i4 + 0x1c;
      }
    }
    return 0;
  }
  tmp_i2 = local_24 * 0xc;
  if (*(int *)(*(int *)(param_2 + 0xc) + 8 + tmp_i2) == 0) {
    tmp_i4 = tmp_i2 + 0xc;
    do {
      tmp_i2 = tmp_i4;
      local_24 = local_24 + 1;
      if (local_24 == tmp_i3) goto LAB_00213ab5;
      tmp_i4 = tmp_i2 + 0xc;
    } while (*(int *)(*(int *)(param_2 + 0xc) + -4 + tmp_i2 + 0xc) == 0);
  }
  *(uint32_t *)(param_3 + 1) = 3;
  *param_3 = (double)(local_24 + 1);
  tmp_pu5 = (uint32_t *)(tmp_i2 + *(int *)(param_2 + 0xc));
LAB_00213b5b:
  tmp_u1 = tmp_pu5[1];
  *(uint32_t *)((int)param_3 + 0xc) = *tmp_pu5;
  *(uint32_t *)(param_3 + 2) = tmp_u1;
  *(uint32_t *)((int)param_3 + 0x14) = tmp_pu5[2];
  return 1;
}

int luaH_new(uint32_t param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  byte local_20;
  
  tmp_i1 = luaM_realloc_(param_1,0,0,0x20);
  tmp_pu3 = dummynode_;
  luaC_link(param_1,tmp_i1,5);
  *(uint32_t *)(tmp_i1 + 8) = 0;
  *(uint8_t *)(tmp_i1 + 6) = 0xff;
  *(uint32_t *)(tmp_i1 + 0xc) = 0;
  *(uint32_t *)(tmp_i1 + 0x1c) = 0;
  *(uint8_t *)(tmp_i1 + 7) = 0;
  *(uint8_t **)(tmp_i1 + 0x10) = dummynode_;
  if (param_2 + 1U < 0x15555556) {
    tmp_i2 = luaM_realloc_(param_1,0,0,param_2 * 0xc);
  }
  else {
    tmp_i2 = luaM_toobig(param_1);
  }
  tmp_i6 = *(int *)(tmp_i1 + 0x1c);
  *(int *)(tmp_i1 + 0xc) = tmp_i2;
  tmp_i4 = tmp_i6 * 0xc;
  if (tmp_i6 < param_2) {
    while( true ) {
      tmp_i6 = tmp_i6 + 1;
      *(uint32_t *)(tmp_i2 + 8 + tmp_i4) = 0;
      tmp_i4 = tmp_i4 + 0xc;
      if (tmp_i6 == param_2) break;
      tmp_i2 = *(int *)(tmp_i1 + 0xc);
    }
  }
  *(int *)(tmp_i1 + 0x1c) = param_2;
  if (param_3 == 0) {
    *(uint8_t **)(tmp_i1 + 0x10) = dummynode_;
    tmp_i6 = 0;
    local_20 = 0;
  }
  else {
    tmp_i2 = luaO_log2(param_3 + -1);
    if (0x1a < tmp_i2 + 1) {
      luaG_runerror(param_1,"table overflow");
    }
    local_20 = (byte)(tmp_i2 + 1);
    tmp_i2 = 1 << (local_20 & 0x1f);
    if (tmp_i2 + 1U < 0x924924a) {
      tmp_pu3 = (uint8_t *)luaM_realloc_(param_1,0,0,tmp_i2 * 0x1c);
    }
    else {
      tmp_pu3 = (uint8_t *)luaM_toobig(param_1);
    }
    tmp_i6 = tmp_i2 * 0x1c;
    *(uint8_t **)(tmp_i1 + 0x10) = tmp_pu3;
    if (0 < tmp_i2) {
      tmp_i5 = 0;
      tmp_i4 = 0;
      while( true ) {
        tmp_i5 = tmp_i5 + 1;
        *(uint32_t *)(tmp_pu3 + tmp_i4 + 0x18) = 0;
        *(uint32_t *)(tmp_pu3 + tmp_i4 + 0x14) = 0;
        *(uint32_t *)(tmp_pu3 + tmp_i4 + 8) = 0;
        if (tmp_i5 == tmp_i2) break;
        tmp_pu3 = *(uint8_t **)(tmp_i1 + 0x10);
        tmp_i4 = tmp_i4 + 0x1c;
      }
      tmp_pu3 = *(uint8_t **)(tmp_i1 + 0x10);
    }
  }
  *(byte *)(tmp_i1 + 7) = local_20;
  *(uint8_t **)(tmp_i1 + 0x14) = tmp_pu3 + tmp_i6;
  return tmp_i1;
}

void luaH_free(uint32_t param_1,int param_2)
{
  if (*(uint8_t **)(param_2 + 0x10) != dummynode_) {
    luaM_realloc_(param_1,*(uint8_t **)(param_2 + 0x10),0x1c << (*(byte *)(param_2 + 7) & 0x1f),0
                 );
  }
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 0xc),*(int *)(param_2 + 0x1c) * 0xc,0);
  luaM_realloc_(param_1,param_2,0x20,0);
  return;
}

uint32_t * luaH_getnum(int param_1,int param_2)
{
  double tmp_d1;
  uint32_t *tmp_pu2;
  int local_14;
  int iStack_10;
  
  if (param_2 - 1U < *(uint *)(param_1 + 0x1c)) {
    return (uint32_t *)(param_2 * 0xc + -0xc + *(int *)(param_1 + 0xc));
  }
  tmp_d1 = (double)param_2;
  if (tmp_d1 == 0.0) {
    tmp_pu2 = *(uint32_t **)(param_1 + 0x10);
  }
  else {
    iStack_10 = (int)((ulonglong)tmp_d1 >> 0x20);
    local_14 = SUB84(tmp_d1,0);
    tmp_pu2 = (uint32_t *)
             (*(int *)(param_1 + 0x10) +
             ((uint)(local_14 + iStack_10) % ((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U | 1)) *
             0x1c);
  }
  while ((tmp_pu2[5] != 3 || (tmp_d1 != *(double *)(tmp_pu2 + 3)))) {
    tmp_pu2 = (uint32_t *)tmp_pu2[6];
    if (tmp_pu2 == (uint32_t *)0x0) {
      return &luaO_nilobject_;
    }
  }
  return tmp_pu2;
}

uint32_t * luaH_getstr(int param_1,int param_2)
{
  uint32_t *tmp_pu1;
  
  tmp_pu1 = (uint32_t *)
           (((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U & *(uint *)(param_2 + 8)) * 0x1c +
           *(int *)(param_1 + 0x10));
  while ((tmp_pu1[5] != 4 || (tmp_pu1[3] != param_2))) {
    tmp_pu1 = (uint32_t *)tmp_pu1[6];
    if (tmp_pu1 == (uint32_t *)0x0) {
      return &luaO_nilobject_;
    }
  }
  return tmp_pu1;
}

uint32_t * luaH_get(int param_1,double *param_2)
{
  double tmp_d1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  int local_24;
  int iStack_20;
  int local_14;
  
  tmp_i3 = *(int *)(param_2 + 1);
  if (tmp_i3 == 3) {
    local_14 = SUB84(*param_2 + 6755399441055744.0,0);
    tmp_d1 = (double)local_14;
    if (*param_2 == tmp_d1) {
      if (local_14 - 1U < *(uint *)(param_1 + 0x1c)) {
        return (uint32_t *)(local_14 * 0xc + -0xc + *(int *)(param_1 + 0xc));
      }
      if (tmp_d1 == 0.0) {
        tmp_pu2 = *(uint32_t **)(param_1 + 0x10);
      }
      else {
        iStack_20 = (int)((ulonglong)tmp_d1 >> 0x20);
        local_24 = SUB84(tmp_d1,0);
        tmp_pu2 = (uint32_t *)
                 (((uint)(local_24 + iStack_20) % ((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U | 1))
                  * 0x1c + *(int *)(param_1 + 0x10));
      }
      do {
        if ((tmp_pu2[5] == 3) && (tmp_d1 == *(double *)(tmp_pu2 + 3))) {
          return tmp_pu2;
        }
        tmp_pu2 = (uint32_t *)tmp_pu2[6];
      } while (tmp_pu2 != (uint32_t *)0x0);
      goto LAB_00214098;
    }
  }
  else {
    if (tmp_i3 == 4) {
      tmp_pu2 = (uint32_t *)
               (((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U & *(uint *)(*(int *)param_2 + 8)) *
                0x1c + *(int *)(param_1 + 0x10));
      do {
        if ((tmp_pu2[5] == 4) && (*(int *)param_2 == tmp_pu2[3])) {
          return tmp_pu2;
        }
        tmp_pu2 = (uint32_t *)tmp_pu2[6];
      } while (tmp_pu2 != (uint32_t *)0x0);
      goto LAB_00214098;
    }
    if (tmp_i3 == 0) goto LAB_00214098;
  }
  tmp_pu2 = (uint32_t *)mainposition();
  do {
    tmp_i3 = luaO_rawequalObj(tmp_pu2 + 3,param_2);
    if (tmp_i3 != 0) {
      return tmp_pu2;
    }
    tmp_pu2 = (uint32_t *)tmp_pu2[6];
  } while (tmp_pu2 != (uint32_t *)0x0);
LAB_00214098:
  return &luaO_nilobject_;
}

void luaH_setnum(uint32_t param_1,int param_2,int param_3)
{
  double tmp_d1;
  uint32_t *tmp_pu2;
  int local_34;
  int iStack_30;
  double local_28;
  uint32_t local_20;
  
  if (param_3 - 1U < *(uint *)(param_2 + 0x1c)) {
    tmp_pu2 = (uint32_t *)(param_3 * 0xc + -0xc + *(int *)(param_2 + 0xc));
LAB_0021423e:
    if (tmp_pu2 != &luaO_nilobject_) {
      return;
    }
  }
  else {
    tmp_d1 = (double)param_3;
    if (tmp_d1 == 0.0) {
      tmp_pu2 = *(uint32_t **)(param_2 + 0x10);
    }
    else {
      iStack_30 = (int)((ulonglong)tmp_d1 >> 0x20);
      local_34 = SUB84(tmp_d1,0);
      tmp_pu2 = (uint32_t *)
               (*(int *)(param_2 + 0x10) +
               ((uint)(local_34 + iStack_30) % ((1 << (*(byte *)(param_2 + 7) & 0x1f)) - 1U | 1)) *
               0x1c);
    }
    do {
      if ((tmp_pu2[5] == 3) && (tmp_d1 == *(double *)(tmp_pu2 + 3))) goto LAB_0021423e;
      tmp_pu2 = (uint32_t *)tmp_pu2[6];
    } while (tmp_pu2 != (uint32_t *)0x0);
  }
  local_28 = (double)param_3;
  local_20 = 3;
  newkey(&local_28);
  return;
}

void luaH_resizearray(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  param_1 = param_3;
  resize();
  return;
}

void luaH_set(uint32_t param_1,int param_2,double *param_3)
{
  double tmp_d1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  int local_34;
  int iStack_30;
  int local_24;
  
  tmp_i3 = *(int *)(param_3 + 1);
  if (tmp_i3 == 3) {
    local_24 = SUB84(*param_3 + 6755399441055744.0,0);
    tmp_d1 = (double)local_24;
    if (*param_3 == tmp_d1) {
      if (local_24 - 1U < *(uint *)(param_2 + 0x1c)) {
        tmp_pu2 = (uint32_t *)(local_24 * 0xc + -0xc + *(int *)(param_2 + 0xc));
LAB_00214b1c:
        *(uint8_t *)(param_2 + 6) = 0;
        if (tmp_pu2 != &luaO_nilobject_) {
          return;
        }
        goto LAB_00214b3c;
      }
      if (tmp_d1 == 0.0) {
        tmp_pu2 = *(uint32_t **)(param_2 + 0x10);
      }
      else {
        iStack_30 = (int)((ulonglong)tmp_d1 >> 0x20);
        local_34 = SUB84(tmp_d1,0);
        tmp_pu2 = (uint32_t *)
                 (((uint)(local_34 + iStack_30) % ((1 << (*(byte *)(param_2 + 7) & 0x1f)) - 1U | 1))
                  * 0x1c + *(int *)(param_2 + 0x10));
      }
      do {
        if ((tmp_pu2[5] == 3) && (tmp_d1 == *(double *)(tmp_pu2 + 3))) goto LAB_00214b1c;
        tmp_pu2 = (uint32_t *)tmp_pu2[6];
      } while (tmp_pu2 != (uint32_t *)0x0);
    }
    else {
LAB_00214af3:
      tmp_pu2 = (uint32_t *)mainposition();
      do {
        tmp_i3 = luaO_rawequalObj(tmp_pu2 + 3,param_3);
        if (tmp_i3 != 0) goto LAB_00214b1c;
        tmp_pu2 = (uint32_t *)tmp_pu2[6];
      } while (tmp_pu2 != (uint32_t *)0x0);
    }
  }
  else if (tmp_i3 == 4) {
    tmp_pu2 = (uint32_t *)
             (((1 << (*(byte *)(param_2 + 7) & 0x1f)) - 1U & *(uint *)(*(int *)param_3 + 8)) * 0x1c
             + *(int *)(param_2 + 0x10));
    do {
      if ((tmp_pu2[5] == 4) && (*(int *)param_3 == tmp_pu2[3])) goto LAB_00214b1c;
      tmp_pu2 = (uint32_t *)tmp_pu2[6];
    } while (tmp_pu2 != (uint32_t *)0x0);
  }
  else if (tmp_i3 != 0) goto LAB_00214af3;
  *(uint8_t *)(param_2 + 6) = 0;
LAB_00214b3c:
  if (*(int *)(param_3 + 1) == 0) {
    luaG_runerror(param_1,"table index is nil");
  }
  else if ((*(int *)(param_3 + 1) == 3) && (NAN(*param_3))) {
    luaG_runerror(param_1,"table index is NaN");
  }
  newkey(param_3);
  return;
}

void luaH_setstr(uint32_t param_1,int param_2,int param_3)
{
  uint32_t *tmp_pu1;
  int local_18 [2];
  uint32_t local_10;
  
  tmp_pu1 = (uint32_t *)
           (((1 << (*(byte *)(param_2 + 7) & 0x1f)) - 1U & *(uint *)(param_3 + 8)) * 0x1c +
           *(int *)(param_2 + 0x10));
  while ((tmp_pu1[5] != 4 || (param_3 != tmp_pu1[3]))) {
    tmp_pu1 = (uint32_t *)tmp_pu1[6];
    if (tmp_pu1 == (uint32_t *)0x0) {
LAB_00214d38:
      local_10 = 4;
      local_18[0] = param_3;
      newkey(local_18);
      return;
    }
  }
  if (tmp_pu1 != &luaO_nilobject_) {
    return;
  }
  goto LAB_00214d38;
}

uint luaH_getn(int param_1)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  double tmp_d3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  uint tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  uint tmp_u9;
  int local_2c;
  int iStack_28;
  uint local_1c;
  
  tmp_u9 = *(uint *)(param_1 + 0x1c);
  if ((tmp_u9 != 0) && (*(int *)(*(int *)(param_1 + 0xc) + -4 + tmp_u9 * 0xc) == 0)) {
    tmp_u4 = 0;
    while (tmp_u8 = tmp_u4, 1 < tmp_u9 - tmp_u8) {
      tmp_u6 = tmp_u9 + tmp_u8 >> 1;
      tmp_u4 = tmp_u6;
      if (*(int *)(*(int *)(param_1 + 0xc) + -4 + tmp_u6 * 0xc) == 0) {
        tmp_u4 = tmp_u8;
        tmp_u9 = tmp_u6;
      }
    }
    return tmp_u8;
  }
  tmp_pu1 = *(uint32_t **)(param_1 + 0x10);
  if (tmp_pu1 == (uint32_t *)dummynode_) {
    return tmp_u9;
  }
  tmp_u4 = tmp_u9 + 1;
  local_1c = tmp_u9;
  do {
    tmp_d3 = (double)(int)tmp_u4;
    tmp_pu5 = tmp_pu1;
    if (tmp_d3 != 0.0) {
      iStack_28 = (int)((ulonglong)tmp_d3 >> 0x20);
      local_2c = SUB84(tmp_d3,0);
      tmp_pu5 = tmp_pu1 + ((uint)(local_2c + iStack_28) %
                        ((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U | 1)) * 7;
    }
    do {
      if ((tmp_pu5[5] == 3) && (tmp_d3 == *(double *)(tmp_pu5 + 3))) goto LAB_00214e19;
      tmp_pu5 = (uint32_t *)tmp_pu5[6];
    } while (tmp_pu5 != (uint32_t *)0x0);
    tmp_pu5 = &luaO_nilobject_;
LAB_00214e19:
    tmp_i7 = tmp_pu5[2];
    tmp_u8 = local_1c;
    while( true ) {
      local_1c = tmp_u4;
      if (tmp_i7 == 0) {
        tmp_u4 = local_1c - tmp_u8;
        goto joined_r0x00214e6c;
      }
      tmp_u4 = local_1c * 2;
      if (0x7ffffffd < tmp_u4) {
        tmp_u8 = 1;
        tmp_i7 = 0;
        tmp_u4 = 0;
        if (tmp_u9 != 0) goto LAB_00215061;
        tmp_u8 = 1;
        goto LAB_00215010;
      }
      if (tmp_u9 <= tmp_u4 - 1) break;
      tmp_i7 = *(int *)(local_1c * 0x18 + *(int *)(param_1 + 0xc) + -4);
      tmp_u8 = local_1c;
    }
  } while( true );
joined_r0x00214e6c:
  if (tmp_u4 < 2) {
    return tmp_u8;
  }
  tmp_u4 = local_1c + tmp_u8 >> 1;
  tmp_u6 = tmp_u4;
  if (tmp_u4 - 1 < tmp_u9) {
    if (*(int *)(tmp_u4 * 0xc + *(int *)(param_1 + 0xc) + -4) == 0) {
      tmp_u6 = tmp_u8;
      local_1c = tmp_u4;
    }
  }
  else {
    tmp_d3 = (double)tmp_u4;
    tmp_pu5 = tmp_pu1;
    if (tmp_d3 != 0.0) {
      iStack_28 = (int)((ulonglong)tmp_d3 >> 0x20);
      local_2c = SUB84(tmp_d3,0);
      tmp_pu5 = tmp_pu1 + ((uint)(local_2c + iStack_28) %
                        ((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U | 1)) * 7;
    }
    do {
      if ((tmp_pu5[5] == 3) && (tmp_d3 == *(double *)(tmp_pu5 + 3))) {
        if (tmp_pu5[2] == 0) {
          tmp_u6 = tmp_u8;
          local_1c = tmp_u4;
        }
        goto LAB_00214ee0;
      }
      tmp_pu5 = (uint32_t *)tmp_pu5[6];
    } while (tmp_pu5 != (uint32_t *)0x0);
    if (g_unk_002701c8 == 0) {
      tmp_u6 = tmp_u8;
      local_1c = tmp_u4;
    }
  }
LAB_00214ee0:
  tmp_u4 = local_1c - tmp_u6;
  tmp_u8 = tmp_u6;
  goto joined_r0x00214e6c;
LAB_00215010:
  tmp_d3 = (double)(int)tmp_u8;
  tmp_pu5 = tmp_pu1;
  if (tmp_d3 != 0.0) {
    iStack_28 = (int)((ulonglong)tmp_d3 >> 0x20);
    local_2c = SUB84(tmp_d3,0);
    tmp_pu5 = tmp_pu1 + ((uint)(local_2c + iStack_28) %
                      ((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U | 1)) * 7;
  }
  do {
    if ((tmp_pu5[5] == 3) && (tmp_d3 == *(double *)(tmp_pu5 + 3))) goto LAB_0021504d;
    tmp_pu5 = (uint32_t *)tmp_pu5[6];
  } while (tmp_pu5 != (uint32_t *)0x0);
  tmp_pu5 = &luaO_nilobject_;
LAB_0021504d:
  tmp_i2 = tmp_pu5[2];
  tmp_u6 = tmp_u4;
  while( true ) {
    tmp_u4 = tmp_u8;
    if (tmp_i2 == 0) {
      return tmp_u6;
    }
    tmp_i7 = tmp_i7 + 0xc;
    tmp_u8 = tmp_u4 + 1;
    if (tmp_u9 <= tmp_u4) break;
LAB_00215061:
    tmp_i2 = *(int *)(*(int *)(param_1 + 0xc) + tmp_i7 + 8);
    tmp_u6 = tmp_u4;
  }
  goto LAB_00215010;
}

void luaD_seterrorobj(int param_1,int param_2,uint32_t *param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  if (param_2 == 4) {
    tmp_u3 = 0x11;
    tmp_pc2 = "not enough memory";
  }
  else {
    if (param_2 < 5) {
      if (1 < param_2) {
        tmp_i1 = *(int *)(param_1 + 8);
        tmp_u3 = *(uint32_t *)(tmp_i1 + -8);
        *param_3 = *(uint32_t *)(tmp_i1 + -0xc);
        param_3[1] = tmp_u3;
        param_3[2] = *(uint32_t *)(tmp_i1 + -4);
      }
      goto LAB_00215149;
    }
    if (param_2 != 5) goto LAB_00215149;
    tmp_u3 = 0x17;
    tmp_pc2 = "error in error handling";
  }
  tmp_u3 = luaS_newlstr(param_1,tmp_pc2,tmp_u3);
  param_3[2] = 4;
  *param_3 = tmp_u3;
LAB_00215149:
  *(uint32_t **)(param_1 + 8) = param_3 + 3;
  return;
}

uint32_t luaD_rawrunprotected(int param_1,void *param_2,uint32_t param_3)
{
  int tmp_i1;
  uint32_t local_b0;
  __jmp_buf_tag local_ac;
  uint32_t local_10;
  
  local_10 = 0;
  local_b0 = *(uint32_t *)(param_1 + 0x68);
  *(uint32_t **)(param_1 + 0x68) = &local_b0;
  tmp_i1 = _setjmp(&local_ac);
  if (tmp_i1 == 0) {
    (*param_2)(param_1,param_3);
  }
  *(uint32_t *)(param_1 + 0x68) = local_b0;
  return local_10;
}

void luaD_reallocstack(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  int *tmp_pi4;
  int *tmp_pi5;
  
  tmp_i1 = *(int *)(param_1 + 0x20);
  if (param_2 + 7U < 0x15555556) {
    tmp_i3 = luaM_realloc_(param_1,tmp_i1,*(int *)(param_1 + 0x2c) * 0xc,(param_2 + 6) * 0xc);
  }
  else {
    tmp_i3 = luaM_toobig(param_1);
  }
  *(int *)(param_1 + 0x2c) = param_2 + 6;
  *(int *)(param_1 + 0x1c) = tmp_i3 + param_2 * 0xc;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + (tmp_i3 - tmp_i1);
  tmp_pu2 = *(uint32_t **)(param_1 + 0x60);
  *(int *)(param_1 + 0x20) = tmp_i3;
  for (; tmp_pu2 != (uint32_t *)0x0; tmp_pu2 = (uint32_t *)*tmp_pu2) {
    tmp_pu2[2] = tmp_pu2[2] + (tmp_i3 - tmp_i1);
    tmp_i3 = *(int *)(param_1 + 0x20);
  }
  tmp_pi4 = *(int **)(param_1 + 0x28);
  if (tmp_pi4 <= *(int **)(param_1 + 0x14)) {
    do {
      tmp_pi4[2] = tmp_pi4[2] + (tmp_i3 - tmp_i1);
      tmp_pi5 = tmp_pi4 + 6;
      *tmp_pi4 = (*tmp_pi4 - tmp_i1) + *(int *)(param_1 + 0x20);
      tmp_pi4[1] = (tmp_pi4[1] - tmp_i1) + *(int *)(param_1 + 0x20);
      tmp_i3 = *(int *)(param_1 + 0x20);
      tmp_pi4 = tmp_pi5;
    } while (tmp_pi5 <= *(int **)(param_1 + 0x14));
  }
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + (tmp_i3 - tmp_i1);
  return;
}

void luaD_reallocCI(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = *(int *)(param_1 + 0x28);
  if (param_2 + 1U < 0xaaaaaab) {
    tmp_i2 = luaM_realloc_(param_1,tmp_i1,*(int *)(param_1 + 0x30) * 0x18,param_2 * 0x18);
  }
  else {
    tmp_i2 = luaM_toobig(param_1);
  }
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + (tmp_i2 - tmp_i1);
  *(int *)(param_1 + 0x28) = tmp_i2;
  *(int *)(param_1 + 0x30) = param_2;
  *(int *)(param_1 + 0x24) = tmp_i2 + -0x18 + param_2 * 0x18;
  return;
}

void luaD_throw(int param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 0x68) != 0) {
    *(uint32_t *)(*(int *)(param_1 + 0x68) + 0xa0) = param_2;
    longjmp((__jmp_buf_tag *)(*(int *)(param_1 + 0x68) + 4),1);
  }
  *(char *)(param_1 + 6) = (char)param_2;
  if (*(int *)(*(int *)(param_1 + 0x10) + 0x58) != 0) {
    *(uint32_t **)(param_1 + 0x14) = *(uint32_t **)(param_1 + 0x28);
    tmp_u1 = **(uint32_t **)(param_1 + 0x28);
    *(uint32_t *)(param_1 + 0xc) = tmp_u1;
    luaF_close(param_1,tmp_u1);
    luaD_seterrorobj(param_1,param_2,*(uint32_t *)(param_1 + 0xc));
    *(uint8_t *)(param_1 + 0x39) = 1;
    *(uint16_t *)(param_1 + 0x34) = *(uint16_t *)(param_1 + 0x36);
    if ((20000 < *(int *)(param_1 + 0x30)) &&
       (*(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x28) < 0x752e8)) {
      luaD_reallocCI(param_1,20000);
    }
    *(uint32_t *)(param_1 + 0x6c) = 0;
    *(uint32_t *)(param_1 + 0x68) = 0;
    (**(void **)(*(int *)(param_1 + 0x10) + 0x58))(param_1);
  }
  exit(1);
}

void luaD_growstack(int param_1,int param_2)
{
  if (*(int *)(param_1 + 0x2c) < param_2) {
    luaD_reallocstack();
    return;
  }
  luaD_reallocstack();
  return;
}

void luaD_callhook(int param_1,int param_2,uint32_t param_3)
{
  void *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int local_70 [5];
  uint32_t local_5c;
  int local_10;
  
  tmp_pc1 = *(void **)(param_1 + 0x44);
  if ((tmp_pc1 != (void *)0x0) && (*(char *)(param_1 + 0x39) != '\0')) {
    tmp_i4 = *(int *)(param_1 + 8);
    tmp_i2 = *(int *)(param_1 + 0x20);
    tmp_i5 = *(int *)(param_1 + 0x14);
    tmp_i6 = tmp_i4 - tmp_i2;
    tmp_i3 = *(int *)(tmp_i5 + 8);
    local_70[0] = param_2;
    local_5c = param_3;
    if (param_2 == 4) {
      local_10 = 0;
    }
    else {
      local_10 = (tmp_i5 - *(int *)(param_1 + 0x28) >> 3) * -0x55555555;
    }
    if (*(int *)(param_1 + 0x1c) - tmp_i4 < 0xf1) {
      tmp_i4 = *(int *)(param_1 + 0x2c);
      if (tmp_i4 < 0x14) {
        tmp_i4 = tmp_i4 + 0x14;
      }
      else {
        tmp_i4 = tmp_i4 * 2;
      }
      luaD_reallocstack(param_1,tmp_i4);
      tmp_i5 = *(int *)(param_1 + 0x14);
      tmp_i4 = *(int *)(param_1 + 8);
    }
    *(int *)(tmp_i5 + 8) = tmp_i4 + 0xf0;
    *(uint8_t *)(param_1 + 0x39) = 0;
    (*tmp_pc1)(param_1,local_70);
    *(uint8_t *)(param_1 + 0x39) = 1;
    *(int *)(*(int *)(param_1 + 0x14) + 8) = (tmp_i3 - tmp_i2) + *(int *)(param_1 + 0x20);
    *(int *)(param_1 + 8) = tmp_i6 + *(int *)(param_1 + 0x20);
  }
  return;
}

int luaD_poscall(int param_1,uint32_t *param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  void *tmp_pc3;
  uint32_t *tmp_pu4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int tmp_i7;
  uint32_t *tmp_pu8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  int local_88;
  uint32_t local_70 [5];
  uint32_t local_5c;
  int local_10;
  
  if ((*(byte *)(param_1 + 0x38) & 2) == 0) {
    tmp_i6 = *(int *)(param_1 + 0x14);
  }
  else {
    tmp_i1 = *(int *)(param_1 + 0x20);
    tmp_pc3 = *(void **)(param_1 + 0x44);
    tmp_i11 = tmp_i1;
    if ((tmp_pc3 != (void *)0x0) && (*(char *)(param_1 + 0x39) != '\0')) {
      tmp_i11 = *(int *)(param_1 + 8);
      tmp_i6 = *(int *)(param_1 + 0x14);
      tmp_i9 = tmp_i11 - tmp_i1;
      tmp_i7 = *(int *)(tmp_i6 + 8);
      local_70[0] = 1;
      local_5c = 0xffffffff;
      local_10 = (tmp_i6 - *(int *)(param_1 + 0x28) >> 3) * -0x55555555;
      if (*(int *)(param_1 + 0x1c) - tmp_i11 < 0xf1) {
        tmp_i11 = *(int *)(param_1 + 0x2c);
        if (tmp_i11 < 0x14) {
          tmp_i11 = tmp_i11 + 0x14;
        }
        else {
          tmp_i11 = tmp_i11 * 2;
        }
        luaD_reallocstack(param_1,tmp_i11);
        tmp_i6 = *(int *)(param_1 + 0x14);
        tmp_i11 = *(int *)(param_1 + 8);
      }
      *(int *)(tmp_i6 + 8) = tmp_i11 + 0xf0;
      *(uint8_t *)(param_1 + 0x39) = 0;
      (*tmp_pc3)(param_1,local_70);
      *(uint8_t *)(param_1 + 0x39) = 1;
      *(int *)(*(int *)(param_1 + 0x14) + 8) = (tmp_i7 - tmp_i1) + *(int *)(param_1 + 0x20);
      tmp_i11 = *(int *)(param_1 + 0x20);
      *(int *)(param_1 + 8) = tmp_i9 + tmp_i11;
    }
    tmp_i6 = *(int *)(param_1 + 0x14);
    if (*(char *)(**(int **)(tmp_i6 + 4) + 6) == '\0') {
      while ((*(byte *)(param_1 + 0x38) & 2) != 0) {
        tmp_i11 = *(int *)(tmp_i6 + 0x14);
        *(int *)(tmp_i6 + 0x14) = tmp_i11 + -1;
        if (tmp_i11 == 0) {
          tmp_i6 = *(int *)(param_1 + 0x14);
          break;
        }
        tmp_pc3 = *(void **)(param_1 + 0x44);
        if ((tmp_pc3 != (void *)0x0) && (*(char *)(param_1 + 0x39) != '\0')) {
          tmp_i11 = *(int *)(param_1 + 8);
          tmp_i6 = *(int *)(param_1 + 0x20);
          tmp_i7 = *(int *)(param_1 + 0x14);
          tmp_i10 = tmp_i11 - tmp_i6;
          tmp_i9 = *(int *)(tmp_i7 + 8);
          local_70[0] = 4;
          local_5c = 0xffffffff;
          local_10 = 0;
          if (*(int *)(param_1 + 0x1c) - tmp_i11 < 0xf1) {
            tmp_i11 = *(int *)(param_1 + 0x2c);
            if (tmp_i11 < 0x14) {
              tmp_i11 = tmp_i11 + 0x14;
            }
            else {
              tmp_i11 = tmp_i11 * 2;
            }
            luaD_reallocstack(param_1,tmp_i11);
            tmp_i7 = *(int *)(param_1 + 0x14);
            tmp_i11 = *(int *)(param_1 + 8);
          }
          *(int *)(tmp_i7 + 8) = tmp_i11 + 0xf0;
          *(uint8_t *)(param_1 + 0x39) = 0;
          (*tmp_pc3)(param_1,local_70);
          *(uint8_t *)(param_1 + 0x39) = 1;
          *(int *)(*(int *)(param_1 + 0x14) + 8) = (tmp_i9 - tmp_i6) + *(int *)(param_1 + 0x20);
          *(int *)(param_1 + 8) = tmp_i10 + *(int *)(param_1 + 0x20);
        }
        tmp_i6 = *(int *)(param_1 + 0x14);
      }
      tmp_i11 = *(int *)(param_1 + 0x20);
    }
    param_2 = (uint32_t *)((int)param_2 + (tmp_i11 - tmp_i1));
  }
  *(int *)(param_1 + 0x14) = tmp_i6 + -0x18;
  tmp_i1 = *(int *)(tmp_i6 + 0x10);
  tmp_pu8 = *(uint32_t **)(tmp_i6 + 4);
  *(uint32_t *)(param_1 + 0xc) = *(uint32_t *)(tmp_i6 + -0x18);
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(tmp_i6 + -0xc);
  if (tmp_i1 != 0) {
    tmp_pu5 = tmp_pu8;
    local_88 = tmp_i1;
    if (param_2 < *(uint32_t **)(param_1 + 8)) {
      do {
        tmp_pu4 = param_2 + 3;
        tmp_pu8 = tmp_pu5 + 3;
        tmp_u2 = *param_2;
        local_88 = local_88 + -1;
        tmp_pu5[1] = param_2[1];
        *tmp_pu5 = tmp_u2;
        tmp_pu5[2] = param_2[2];
        if (local_88 == 0) goto LAB_00215753;
        param_2 = tmp_pu4;
        tmp_pu5 = tmp_pu8;
      } while (tmp_pu4 < *(uint32_t **)(param_1 + 8));
    }
    tmp_i11 = local_88 + -1;
    tmp_pu5 = tmp_pu8;
    if (0 < local_88) {
      do {
        tmp_i11 = tmp_i11 + -1;
        tmp_pu5[2] = 0;
        tmp_pu5 = tmp_pu5 + 3;
      } while (tmp_i11 != -1);
      *(uint32_t **)(param_1 + 8) = tmp_pu8 + local_88 * 3;
      return tmp_i1 + 1;
    }
  }
LAB_00215753:
  *(uint32_t **)(param_1 + 8) = tmp_pu8;
  return tmp_i1 + 1;
}

uint32_t luaD_precall(int param_1,int *param_2,int param_3)
{
  void *tmp_pc1;
  byte tmp_b2;
  int *tmp_pi3;
  uint32_t tmp_u4;
  double *pdVar5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  int tmp_i8;
  uint32_t *tmp_pu9;
  int tmp_i10;
  int *tmp_pi11;
  int *tmp_pi12;
  uint32_t *tmp_pu13;
  uint tmp_u14;
  int tmp_i15;
  uint tmp_u16;
  int tmp_i17;
  int local_b0;
  int local_ac;
  int local_a0;
  int local_98;
  uint local_90;
  uint32_t local_80 [5];
  uint32_t local_6c;
  int local_20;
  
  if (param_2[2] != 6) {
    tmp_pi3 = (int *)luaT_gettmbyobj(param_1,param_2,0x10);
    tmp_i7 = *(int *)(param_1 + 0x20);
    if (tmp_pi3[2] != 6) {
      luaG_typeerror(param_1,param_2,"call");
    }
    tmp_pi12 = *(int **)(param_1 + 8);
    if (param_2 < tmp_pi12) {
      do {
        tmp_pi11 = tmp_pi12 + -3;
        *tmp_pi12 = tmp_pi12[-3];
        tmp_pi12[1] = tmp_pi12[-2];
        tmp_pi12[2] = tmp_pi12[-1];
        tmp_pi12 = tmp_pi11;
      } while (param_2 < tmp_pi11);
      tmp_pi12 = *(int **)(param_1 + 8);
    }
    if (*(int *)(param_1 + 0x1c) - (int)tmp_pi12 < 0xd) {
      tmp_i10 = *(int *)(param_1 + 0x2c);
      if (tmp_i10 < 1) {
        tmp_i10 = tmp_i10 + 1;
      }
      else {
        tmp_i10 = tmp_i10 * 2;
      }
      luaD_reallocstack(param_1,tmp_i10);
      tmp_pi12 = *(int **)(param_1 + 8);
    }
    *(int **)(param_1 + 8) = tmp_pi12 + 3;
    param_2 = (int *)((int)param_2 + (*(int *)(param_1 + 0x20) - tmp_i7));
    tmp_i7 = *tmp_pi3;
    param_2[1] = tmp_pi3[1];
    *param_2 = tmp_i7;
    param_2[2] = tmp_pi3[2];
  }
  tmp_i7 = *(int *)(param_1 + 0x20);
  tmp_i10 = *param_2;
  *(uint32_t *)(*(int *)(param_1 + 0x14) + 0xc) = *(uint32_t *)(param_1 + 0x18);
  if (*(char *)(tmp_i10 + 6) != '\0') {
    if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0xf1) {
      tmp_i10 = *(int *)(param_1 + 0x2c);
      if (tmp_i10 < 0x14) {
        luaD_reallocstack(param_1,tmp_i10 + 0x14);
      }
      else {
        luaD_reallocstack(param_1,tmp_i10 * 2);
      }
    }
    if (*(int *)(param_1 + 0x14) != *(int *)(param_1 + 0x24)) {
      tmp_pi3 = (int *)(*(int *)(param_1 + 0x14) + 0x18);
      *(int **)(param_1 + 0x14) = tmp_pi3;
LAB_00215b55:
      tmp_i7 = (int)param_2 + (*(int *)(param_1 + 0x20) - tmp_i7);
      tmp_pi3[1] = tmp_i7;
      tmp_i7 = tmp_i7 + 0xc;
      *tmp_pi3 = tmp_i7;
      *(int *)(param_1 + 0xc) = tmp_i7;
      tmp_pi3[2] = *(int *)(param_1 + 8) + 0xf0;
      tmp_pi3[4] = param_3;
      if ((((*(byte *)(param_1 + 0x38) & 1) != 0) &&
          (tmp_pc1 = *(void **)(param_1 + 0x44), tmp_pc1 != (void *)0x0)) &&
         (*(char *)(param_1 + 0x39) != '\0')) {
        tmp_i7 = *(int *)(param_1 + 8);
        tmp_i10 = *(int *)(param_1 + 0x20);
        tmp_i15 = *(int *)(param_1 + 0x14);
        tmp_i8 = tmp_i7 - tmp_i10;
        tmp_i17 = *(int *)(tmp_i15 + 8);
        local_80[0] = 0;
        local_6c = 0xffffffff;
        local_20 = (tmp_i15 - *(int *)(param_1 + 0x28) >> 3) * -0x55555555;
        if (*(int *)(param_1 + 0x1c) - tmp_i7 < 0xf1) {
          tmp_i7 = *(int *)(param_1 + 0x2c);
          if (tmp_i7 < 0x14) {
            tmp_i7 = tmp_i7 + 0x14;
          }
          else {
            tmp_i7 = tmp_i7 * 2;
          }
          luaD_reallocstack(param_1,tmp_i7);
          tmp_i15 = *(int *)(param_1 + 0x14);
          tmp_i7 = *(int *)(param_1 + 8);
        }
        *(int *)(tmp_i15 + 8) = tmp_i7 + 0xf0;
        *(uint8_t *)(param_1 + 0x39) = 0;
        (*tmp_pc1)(param_1,local_80);
        *(uint8_t *)(param_1 + 0x39) = 1;
        *(int *)(*(int *)(param_1 + 0x14) + 8) = (tmp_i17 - tmp_i10) + *(int *)(param_1 + 0x20);
        *(int *)(param_1 + 8) = tmp_i8 + *(int *)(param_1 + 0x20);
      }
      tmp_i7 = (**(void **)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0x10))(param_1);
      if (tmp_i7 < 0) {
        return 2;
      }
      luaD_poscall(param_1,*(int *)(param_1 + 8) + tmp_i7 * -0xc);
      return 1;
    }
    tmp_i10 = *(int *)(param_1 + 0x30);
    if (tmp_i10 < 0x4e21) {
      tmp_i17 = tmp_i10 * 2;
      tmp_i15 = *(int *)(param_1 + 0x28);
      if (tmp_i17 + 1U < 0xaaaaaab) {
        tmp_i8 = luaM_realloc_(param_1,tmp_i15,tmp_i10 * 0x18,tmp_i10 * 0x30);
      }
      else {
        tmp_i8 = luaM_toobig(param_1);
      }
      *(int *)(param_1 + 0x28) = tmp_i8;
      *(int *)(param_1 + 0x30) = tmp_i17;
      *(int *)(param_1 + 0x24) = tmp_i8 + -0x18 + tmp_i10 * 0x30;
      tmp_i10 = *(int *)(param_1 + 0x14) + (tmp_i8 - tmp_i15);
      *(int *)(param_1 + 0x14) = tmp_i10;
      if (20000 < tmp_i17) {
        luaG_runerror(param_1,"stack overflow");
        tmp_i10 = *(int *)(param_1 + 0x14);
      }
      tmp_pi3 = (int *)(tmp_i10 + 0x18);
      *(int **)(param_1 + 0x14) = tmp_pi3;
      goto LAB_00215b55;
    }
    goto LAB_002161be;
  }
  tmp_i10 = *(int *)(tmp_i10 + 0x10);
  tmp_pu9 = *(uint32_t **)(param_1 + 8);
  tmp_u16 = (uint)*(byte *)(tmp_i10 + 0x4b);
  if (*(int *)(param_1 + 0x1c) - (int)tmp_pu9 <= (int)(tmp_u16 * 0xc)) {
    tmp_i15 = *(int *)(param_1 + 0x2c);
    if (tmp_i15 < (int)tmp_u16) {
      luaD_reallocstack(param_1,tmp_i15 + tmp_u16);
      tmp_pu9 = *(uint32_t **)(param_1 + 8);
    }
    else {
      luaD_reallocstack(param_1,tmp_i15 * 2);
      tmp_pu9 = *(uint32_t **)(param_1 + 8);
    }
  }
  tmp_i15 = (int)param_2 + (*(int *)(param_1 + 0x20) - tmp_i7);
  tmp_b2 = *(byte *)(tmp_i10 + 0x4a);
  if (tmp_b2 == 0) {
    tmp_pu13 = (uint32_t *)(tmp_i15 + 0xc);
    if (tmp_pu13 + (uint)*(byte *)(tmp_i10 + 0x49) * 3 < tmp_pu9) {
      *(uint32_t **)(param_1 + 8) = tmp_pu13 + (uint)*(byte *)(tmp_i10 + 0x49) * 3;
    }
  }
  else {
    tmp_u16 = (uint)*(byte *)(tmp_i10 + 0x49);
    local_90 = ((int)tmp_pu9 - tmp_i15 >> 2) * -0x55555555 - 1;
    if ((int)local_90 < (int)tmp_u16) {
      while( true ) {
        local_90 = local_90 + 1;
        *(uint32_t **)(param_1 + 8) = tmp_pu9 + 3;
        tmp_pu9[2] = 0;
        if (tmp_u16 == local_90) break;
        tmp_pu9 = *(uint32_t **)(param_1 + 8);
      }
      tmp_b2 = *(byte *)(tmp_i10 + 0x4a);
      local_90 = tmp_u16;
    }
    if ((tmp_b2 & 4) == 0) {
      tmp_pu13 = *(uint32_t **)(param_1 + 8);
      local_98 = 0;
      if (tmp_u16 != 0) goto LAB_00215d8d;
    }
    else {
      tmp_i15 = local_90 - tmp_u16;
      if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44))
      {
        luaC_step(param_1);
      }
      local_98 = luaH_new(param_1,tmp_i15,1);
      if (0 < tmp_i15) {
        local_b0 = 0;
        local_a0 = tmp_i15 * -0xc;
        do {
          local_b0 = local_b0 + 1;
          tmp_pu13 = (uint32_t *)(local_a0 + *(int *)(param_1 + 8));
          tmp_pu9 = (uint32_t *)luaH_setnum(param_1,local_98,local_b0);
          local_a0 = local_a0 + 0xc;
          tmp_u4 = tmp_pu13[1];
          *tmp_pu9 = *tmp_pu13;
          tmp_pu9[1] = tmp_u4;
          tmp_pu9[2] = tmp_pu13[2];
        } while (local_b0 != tmp_i15);
      }
      tmp_u4 = luaS_newlstr(param_1,&g_unk_0023bf57,1);
      pdVar5 = (double *)luaH_setstr(param_1,local_98,tmp_u4);
      *(uint32_t *)(pdVar5 + 1) = 3;
      *pdVar5 = (double)tmp_i15;
      tmp_pu13 = *(uint32_t **)(param_1 + 8);
      if (tmp_u16 != 0) {
LAB_00215d8d:
        tmp_i15 = 0;
        tmp_pu6 = tmp_pu13 + local_90 * -3 + 2;
        tmp_pu9 = tmp_pu13;
        while( true ) {
          tmp_i15 = tmp_i15 + 1;
          *(uint32_t **)(param_1 + 8) = tmp_pu9 + 3;
          tmp_u4 = tmp_pu6[-1];
          *tmp_pu9 = tmp_pu6[-2];
          tmp_pu9[1] = tmp_u4;
          tmp_pu9[2] = *tmp_pu6;
          *tmp_pu6 = 0;
          if ((int)tmp_u16 <= tmp_i15) break;
          tmp_pu9 = *(uint32_t **)(param_1 + 8);
          tmp_pu6 = tmp_pu6 + 3;
        }
      }
      if (local_98 != 0) {
        tmp_pi3 = *(int **)(param_1 + 8);
        *(int **)(param_1 + 8) = tmp_pi3 + 3;
        *tmp_pi3 = local_98;
        tmp_pi3[2] = 5;
      }
    }
    tmp_i15 = (int)param_2 + (*(int *)(param_1 + 0x20) - tmp_i7);
  }
  if (*(int *)(param_1 + 0x14) == *(int *)(param_1 + 0x24)) {
    local_ac = *(int *)(param_1 + 0x30);
    if (20000 < local_ac) {
LAB_002161be:
      luaD_throw(param_1,5);
    }
    tmp_i7 = *(int *)(param_1 + 0x28);
    tmp_i17 = local_ac * 2;
    if (tmp_i17 + 1U < 0xaaaaaab) {
      tmp_i8 = luaM_realloc_(param_1,tmp_i7,local_ac * 0x18,local_ac * 0x30);
    }
    else {
      tmp_i8 = luaM_toobig(param_1);
    }
    local_ac = local_ac * 0x30;
    *(int *)(param_1 + 0x28) = tmp_i8;
    local_b0 = (tmp_i8 - tmp_i7) + *(int *)(param_1 + 0x14);
    *(int *)(param_1 + 0x30) = tmp_i17;
    *(int *)(param_1 + 0x14) = local_b0;
    *(int *)(param_1 + 0x24) = tmp_i8 + -0x18 + local_ac;
    if (20000 < tmp_i17) {
      luaG_runerror(param_1,"stack overflow");
      local_b0 = *(int *)(param_1 + 0x14);
    }
    tmp_pu9 = (uint32_t *)(local_b0 + 0x18);
    *(uint32_t **)(param_1 + 0x14) = tmp_pu9;
  }
  else {
    tmp_pu9 = (uint32_t *)(*(int *)(param_1 + 0x14) + 0x18);
    *(uint32_t **)(param_1 + 0x14) = tmp_pu9;
  }
  *tmp_pu9 = tmp_pu13;
  tmp_pu9[1] = tmp_i15;
  *(uint32_t **)(param_1 + 0xc) = tmp_pu13;
  tmp_pu9[2] = tmp_pu13 + (uint)*(byte *)(tmp_i10 + 0x4b) * 3;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(tmp_i10 + 0xc);
  tmp_pu9[5] = 0;
  tmp_u14 = tmp_pu9[2];
  tmp_pu9[4] = param_3;
  tmp_u16 = *(uint *)(param_1 + 8);
  if (tmp_u16 < tmp_u14) {
    do {
      *(uint32_t *)(tmp_u16 + 8) = 0;
      tmp_u16 = tmp_u16 + 0xc;
      tmp_u14 = tmp_pu9[2];
    } while (tmp_u16 < tmp_u14);
  }
  *(uint *)(param_1 + 8) = tmp_u14;
  if ((*(byte *)(param_1 + 0x38) & 1) == 0) {
    return 0;
  }
  tmp_pc1 = *(void **)(param_1 + 0x44);
  tmp_i7 = *(int *)(param_1 + 0x18) + 4;
  *(int *)(param_1 + 0x18) = tmp_i7;
  if ((tmp_pc1 != (void *)0x0) && (*(char *)(param_1 + 0x39) != '\0')) {
    tmp_i7 = *(int *)(param_1 + 0x20);
    tmp_i10 = *(int *)(param_1 + 0x14);
    tmp_i17 = tmp_u14 - tmp_i7;
    tmp_i15 = *(int *)(tmp_i10 + 8);
    local_80[0] = 0;
    local_6c = 0xffffffff;
    local_20 = (tmp_i10 - *(int *)(param_1 + 0x28) >> 3) * -0x55555555;
    if ((int)(*(int *)(param_1 + 0x1c) - tmp_u14) < 0xf1) {
      tmp_i10 = *(int *)(param_1 + 0x2c);
      if (tmp_i10 < 0x14) {
        tmp_i10 = tmp_i10 + 0x14;
      }
      else {
        tmp_i10 = tmp_i10 * 2;
      }
      luaD_reallocstack(param_1,tmp_i10);
      tmp_i10 = *(int *)(param_1 + 0x14);
      tmp_u14 = *(uint *)(param_1 + 8);
    }
    *(uint *)(tmp_i10 + 8) = tmp_u14 + 0xf0;
    *(uint8_t *)(param_1 + 0x39) = 0;
    (*tmp_pc1)(param_1,local_80);
    *(uint8_t *)(param_1 + 0x39) = 1;
    *(int *)(*(int *)(param_1 + 0x14) + 8) = (tmp_i15 - tmp_i7) + *(int *)(param_1 + 0x20);
    *(int *)(param_1 + 8) = tmp_i17 + *(int *)(param_1 + 0x20);
    tmp_i7 = *(int *)(param_1 + 0x18);
  }
  *(int *)(param_1 + 0x18) = tmp_i7 + -4;
  return 0;
}

void luaD_call(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  
  tmp_u1 = *(int *)(param_1 + 0x34) + 1;
  tmp_u2 = tmp_u1 & 0xffff;
  *(short *)(param_1 + 0x34) = (short)tmp_u1;
  if (199 < tmp_u2) {
    if (tmp_u2 == 200) {
      luaG_runerror(param_1,"C stack overflow");
    }
    else if (0xe0 < tmp_u2) {
      luaD_throw(param_1,5);
    }
  }
  tmp_i3 = luaD_precall(param_1,param_2,param_3);
  if (tmp_i3 == 0) {
    luaV_execute(param_1,1);
  }
  *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x34) + -1;
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x44) < *(uint *)(*(int *)(param_1 + 0x10) + 0x40)) {
    return;
  }
  luaC_step();
  return;
}

uint lua_resume(int param_1,int param_2)
{
  short tmp_s1;
  int tmp_i2;
  uint tmp_u3;
  char *tmp_pc4;
  uint32_t *tmp_pu5;
  uint32_t tmp_u6;
  
  if ((*(char *)(param_1 + 6) != '\x01') &&
     ((*(char *)(param_1 + 6) != '\0' ||
      (*(uint32_t **)(param_1 + 0x14) != *(uint32_t **)(param_1 + 0x28))))) {
    tmp_pu5 = (uint32_t *)**(uint32_t **)(param_1 + 0x14);
    tmp_pc4 = "cannot resume non-suspended coroutine";
    *(uint32_t **)(param_1 + 8) = tmp_pu5;
    tmp_u6 = 0x25;
LAB_002163ae:
    tmp_u6 = luaS_newlstr(param_1,tmp_pc4,tmp_u6);
    tmp_pu5[2] = 4;
    *tmp_pu5 = tmp_u6;
    tmp_i2 = *(int *)(param_1 + 8);
    if (*(int *)(param_1 + 0x1c) - tmp_i2 < 0xd) {
      tmp_i2 = *(int *)(param_1 + 0x2c);
      if (tmp_i2 < 1) {
        luaD_reallocstack(param_1,tmp_i2 + 1);
        tmp_i2 = *(int *)(param_1 + 8);
      }
      else {
        luaD_reallocstack(param_1,tmp_i2 * 2);
        tmp_i2 = *(int *)(param_1 + 8);
      }
    }
    *(int *)(param_1 + 8) = tmp_i2 + 0xc;
    return 2;
  }
  if (199 < *(ushort *)(param_1 + 0x34)) {
    tmp_pu5 = (uint32_t *)**(uint32_t **)(param_1 + 0x14);
    tmp_pc4 = "C stack overflow";
    *(uint32_t **)(param_1 + 8) = tmp_pu5;
    tmp_u6 = 0x10;
    goto LAB_002163ae;
  }
  tmp_s1 = *(ushort *)(param_1 + 0x34) + 1;
  *(short *)(param_1 + 0x34) = tmp_s1;
  *(short *)(param_1 + 0x36) = tmp_s1;
  tmp_u3 = luaD_rawrunprotected(param_1,resume,*(int *)(param_1 + 8) + param_2 * -0xc);
  if (tmp_u3 == 0) {
    tmp_u3 = (uint)*(byte *)(param_1 + 6);
    goto LAB_0021645a;
  }
  tmp_pu5 = *(uint32_t **)(param_1 + 8);
  *(char *)(param_1 + 6) = (char)tmp_u3;
  if (tmp_u3 == 4) {
    tmp_u6 = 0x11;
    tmp_pc4 = "not enough memory";
LAB_002164a5:
    tmp_u6 = luaS_newlstr(param_1,tmp_pc4,tmp_u6);
    tmp_pu5[2] = 4;
    *tmp_pu5 = tmp_u6;
  }
  else if ((int)tmp_u3 < 5) {
    if (1 < (int)tmp_u3) {
      *tmp_pu5 = tmp_pu5[-3];
      tmp_pu5[1] = tmp_pu5[-2];
      tmp_pu5[2] = tmp_pu5[-1];
    }
  }
  else if (tmp_u3 == 5) {
    tmp_u6 = 0x17;
    tmp_pc4 = "error in error handling";
    goto LAB_002164a5;
  }
  *(uint32_t **)(param_1 + 8) = tmp_pu5 + 3;
  *(uint32_t **)(*(int *)(param_1 + 0x14) + 8) = tmp_pu5 + 3;
LAB_0021645a:
  *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x34) + -1;
  return tmp_u3;
}

uint32_t lua_yield(int param_1,int param_2)
{
  if (*(ushort *)(param_1 + 0x36) < (ushort)*(uint32_t *)(param_1 + 0x34)) {
    luaG_runerror(param_1,"attempt to yield across metamethod/C-call boundary");
  }
  *(uint8_t *)(param_1 + 6) = 1;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 8) + param_2 * -0xc;
  return 0xffffffff;
}

int luaD_pcall(int param_1,uint32_t param_2,uint32_t param_3,int param_4,uint32_t param_5)
{
  uint8_t tmp_u1;
  uint16_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  char *tmp_pc8;
  uint32_t *tmp_pu9;
  uint32_t tmp_u10;
  
  tmp_u2 = *(uint16_t *)(param_1 + 0x34);
  tmp_i7 = *(int *)(param_1 + 0x14);
  tmp_i3 = *(int *)(param_1 + 0x28);
  tmp_u1 = *(uint8_t *)(param_1 + 0x39);
  tmp_u4 = *(uint32_t *)(param_1 + 0x6c);
  *(uint32_t *)(param_1 + 0x6c) = param_5;
  tmp_i6 = luaD_rawrunprotected(param_1,param_2,param_3);
  if (tmp_i6 == 0) goto LAB_0021660c;
  tmp_pu9 = (uint32_t *)(param_4 + *(int *)(param_1 + 0x20));
  luaF_close(param_1,tmp_pu9);
  if (tmp_i6 == 4) {
    tmp_u10 = 0x11;
    tmp_pc8 = "not enough memory";
LAB_00216738:
    tmp_u10 = luaS_newlstr(param_1,tmp_pc8,tmp_u10);
    tmp_pu9[2] = 4;
    *tmp_pu9 = tmp_u10;
  }
  else if (tmp_i6 < 5) {
    if (1 < tmp_i6) {
      tmp_i5 = *(int *)(param_1 + 8);
      tmp_u10 = *(uint32_t *)(tmp_i5 + -8);
      *tmp_pu9 = *(uint32_t *)(tmp_i5 + -0xc);
      tmp_pu9[1] = tmp_u10;
      tmp_pu9[2] = *(uint32_t *)(tmp_i5 + -4);
    }
  }
  else if (tmp_i6 == 5) {
    tmp_pc8 = "error in error handling";
    tmp_u10 = 0x17;
    goto LAB_00216738;
  }
  tmp_i5 = *(int *)(param_1 + 0x28);
  *(uint32_t **)(param_1 + 8) = tmp_pu9 + 3;
  tmp_i7 = tmp_i7 - tmp_i3;
  tmp_pu9 = (uint32_t *)(tmp_i5 + tmp_i7);
  *(uint32_t **)(param_1 + 0x14) = tmp_pu9;
  *(uint16_t *)(param_1 + 0x34) = tmp_u2;
  *(uint32_t *)(param_1 + 0xc) = *tmp_pu9;
  *(uint32_t *)(param_1 + 0x18) = tmp_pu9[3];
  *(uint8_t *)(param_1 + 0x39) = tmp_u1;
  if ((20000 < *(int *)(param_1 + 0x30)) && (tmp_i7 < 0x752e8)) {
    tmp_i7 = luaM_realloc_(param_1,tmp_i5,*(int *)(param_1 + 0x30) * 0x18,480000);
    *(uint32_t *)(param_1 + 0x30) = 20000;
    *(int *)(param_1 + 0x28) = tmp_i7;
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + (tmp_i7 - tmp_i5);
    *(int *)(param_1 + 0x24) = tmp_i7 + 0x752e8;
  }
LAB_0021660c:
  *(uint32_t *)(param_1 + 0x6c) = tmp_u4;
  return tmp_i6;
}

int luaD_protectedparser(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint8_t tmp_u1;
  uint16_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  char *tmp_pc9;
  uint32_t *tmp_pu10;
  uint32_t tmp_u11;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_24;
  uint32_t local_20;
  
  local_30 = param_2;
  tmp_i3 = *(int *)(param_1 + 8);
  local_20 = param_3;
  local_2c = 0;
  local_24 = 0;
  tmp_u4 = *(uint32_t *)(param_1 + 0x6c);
  tmp_i8 = *(int *)(param_1 + 0x20);
  tmp_u2 = *(uint16_t *)(param_1 + 0x34);
  tmp_i7 = *(int *)(param_1 + 0x14);
  tmp_i5 = *(int *)(param_1 + 0x28);
  tmp_u1 = *(uint8_t *)(param_1 + 0x39);
  tmp_i6 = luaD_rawrunprotected(param_1,f_parser,&local_30);
  if (tmp_i6 == 0) goto LAB_00216815;
  tmp_pu10 = (uint32_t *)((tmp_i3 - tmp_i8) + *(int *)(param_1 + 0x20));
  luaF_close(param_1,tmp_pu10);
  if (tmp_i6 == 4) {
    tmp_u11 = 0x11;
    tmp_pc9 = "not enough memory";
LAB_0021694a:
    tmp_u11 = luaS_newlstr(param_1,tmp_pc9,tmp_u11);
    tmp_pu10[2] = 4;
    *tmp_pu10 = tmp_u11;
  }
  else if (tmp_i6 < 5) {
    if (1 < tmp_i6) {
      tmp_i3 = *(int *)(param_1 + 8);
      tmp_u11 = *(uint32_t *)(tmp_i3 + -8);
      *tmp_pu10 = *(uint32_t *)(tmp_i3 + -0xc);
      tmp_pu10[1] = tmp_u11;
      tmp_pu10[2] = *(uint32_t *)(tmp_i3 + -4);
    }
  }
  else if (tmp_i6 == 5) {
    tmp_u11 = 0x17;
    tmp_pc9 = "error in error handling";
    goto LAB_0021694a;
  }
  *(uint32_t **)(param_1 + 8) = tmp_pu10 + 3;
  tmp_i3 = *(int *)(param_1 + 0x28);
  tmp_i7 = tmp_i7 - tmp_i5;
  tmp_pu10 = (uint32_t *)(tmp_i3 + tmp_i7);
  *(uint16_t *)(param_1 + 0x34) = tmp_u2;
  *(uint32_t **)(param_1 + 0x14) = tmp_pu10;
  *(uint32_t *)(param_1 + 0xc) = *tmp_pu10;
  tmp_u11 = tmp_pu10[3];
  *(uint8_t *)(param_1 + 0x39) = tmp_u1;
  *(uint32_t *)(param_1 + 0x18) = tmp_u11;
  if ((20000 < *(int *)(param_1 + 0x30)) && (tmp_i7 < 0x752e8)) {
    tmp_i8 = luaM_realloc_(param_1,tmp_i3,*(int *)(param_1 + 0x30) * 0x18,480000);
    *(uint32_t *)(param_1 + 0x30) = 20000;
    *(int *)(param_1 + 0x28) = tmp_i8;
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + (tmp_i8 - tmp_i3);
    *(int *)(param_1 + 0x24) = tmp_i8 + 0x752e8;
  }
LAB_00216815:
  *(uint32_t *)(param_1 + 0x6c) = tmp_u4;
  luaM_realloc_(param_1,local_2c,local_24,0);
  return tmp_i6;
}

void luaT_init(int param_1)
{
  int tmp_i1;
  byte *tmp_pb2;
  char *__s;
  int tmp_i3;
  size_t tmp_s4;
  uint32_t tmp_u5;
  int tmp_i6;
  
  tmp_i6 = 0;
  do {
    __s = (&luaT_eventname_3653)[tmp_i6];
    tmp_i3 = *(int *)(param_1 + 0x10);
    tmp_s4 = strlen(__s);
    tmp_u5 = luaS_newlstr(param_1,__s,tmp_s4);
    tmp_i1 = tmp_i6 + 0x28;
    tmp_i6 = tmp_i6 + 1;
    *(uint32_t *)(tmp_i3 + 8 + tmp_i1 * 4) = tmp_u5;
    tmp_pb2 = (byte *)(*(int *)(*(int *)(param_1 + 0x10) + 8 + tmp_i1 * 4) + 5);
    *tmp_pb2 = *tmp_pb2 | 0x20;
  } while (tmp_i6 != 0x11);
  return;
}

int luaT_gettm(int param_1,byte param_2,uint32_t param_3)
{
  int tmp_i1;
  
  tmp_i1 = luaH_getstr(param_1,param_3);
  if (*(int *)(tmp_i1 + 8) != 0) {
    return tmp_i1;
  }
  *(byte *)(param_1 + 6) = *(byte *)(param_1 + 6) | (byte)(1 << (param_2 & 0x1f));
  return 0;
}

uint32_t * luaT_gettmbyobj(int param_1,int *param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  
  tmp_i1 = param_2[2];
  if ((tmp_i1 == 5) || (tmp_i1 == 7)) {
    tmp_i1 = *(int *)(*param_2 + 8);
  }
  else {
    tmp_i1 = *(int *)(*(int *)(param_1 + 0x10) + 0x84 + tmp_i1 * 4);
  }
  if (tmp_i1 != 0) {
    tmp_pu2 = (uint32_t *)luaH_getstr();
    return tmp_pu2;
  }
  return &luaO_nilobject_;
}

int * luaV_tonumber(int *param_1,int *param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  uint64_t local_14;
  
  if (param_1[2] != 3) {
    tmp_pi2 = (int *)0x0;
    if (param_1[2] == 4) {
      tmp_i1 = luaO_str2d(*param_1 + 0x10,&local_14);
      if (tmp_i1 != 0) {
        param_2[2] = 3;
        *(uint64_t *)param_2 = local_14;
        tmp_pi2 = param_2;
      }
    }
    return tmp_pi2;
  }
  return param_1;
}

uint32_t luaV_tostring(uint32_t param_1,uint64_t *param_2)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  uint tmp_u3;
  uint *tmp_pu4;
  uint *tmp_pu5;
  uint local_2c [8];
  
  tmp_u1 = 0;
  if (*(int *)(param_2 + 1) == 3) {
    sprintf((char *)local_2c,"%.14g",*param_2);
    tmp_pu5 = local_2c;
    do {
      tmp_pu4 = tmp_pu5;
      tmp_u2 = *tmp_pu4 + 0xfefefeff & ~*tmp_pu4;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu5 = tmp_pu4 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu5 = (uint *)((int)tmp_pu4 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    tmp_u1 = luaS_newlstr(param_1,local_2c,
                         (char *)((int)tmp_pu5 +
                                 ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_2c)));
    *(uint32_t *)(param_2 + 1) = 4;
    *(uint32_t *)param_2 = tmp_u1;
    tmp_u1 = 1;
  }
  return tmp_u1;
}

void luaV_gettable(int param_1,int *param_2,uint32_t *param_3,uint32_t *param_4)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int *tmp_pi5;
  int tmp_i6;
  int tmp_i7;
  
  tmp_i7 = 100;
  tmp_i6 = param_2[2];
  do {
    if (tmp_i6 == 5) {
      tmp_i6 = *param_2;
      tmp_pu4 = (uint32_t *)luaH_get(tmp_i6,param_3);
      if ((((tmp_pu4[2] != 0) || (tmp_i6 = *(int *)(tmp_i6 + 8), tmp_i6 == 0)) ||
          ((*(byte *)(tmp_i6 + 6) & 1) != 0)) ||
         (tmp_pi5 = (int *)luaT_gettm(tmp_i6,0,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xa8)),
         tmp_pi5 == (int *)0x0)) {
        tmp_u1 = tmp_pu4[1];
        *param_4 = *tmp_pu4;
        param_4[1] = tmp_u1;
        param_4[2] = tmp_pu4[2];
        return;
      }
LAB_00217144:
      tmp_i6 = tmp_pi5[2];
    }
    else {
      tmp_pi5 = (int *)luaT_gettmbyobj(param_1,param_2,0);
      tmp_i6 = tmp_pi5[2];
      if (tmp_i6 == 0) {
        luaG_typeerror(param_1,param_2,"index");
        goto LAB_00217144;
      }
    }
    if (tmp_i6 == 6) {
      tmp_i6 = *(int *)(param_1 + 0x20);
      tmp_pi2 = *(int **)(param_1 + 8);
      tmp_i7 = *tmp_pi5;
      tmp_pi2[1] = tmp_pi5[1];
      *tmp_pi2 = tmp_i7;
      tmp_pi2[2] = tmp_pi5[2];
      tmp_i7 = *(int *)(param_1 + 8);
      tmp_i3 = *param_2;
      *(int *)(tmp_i7 + 0x10) = param_2[1];
      *(int *)(tmp_i7 + 0xc) = tmp_i3;
      *(int *)(tmp_i7 + 0x14) = param_2[2];
      tmp_u1 = param_3[1];
      tmp_i7 = *(int *)(param_1 + 8);
      *(uint32_t *)(tmp_i7 + 0x18) = *param_3;
      *(uint32_t *)(tmp_i7 + 0x1c) = tmp_u1;
      *(uint32_t *)(tmp_i7 + 0x20) = param_3[2];
      tmp_i7 = *(int *)(param_1 + 8);
      if (*(int *)(param_1 + 0x1c) - tmp_i7 < 0x25) {
        luaD_growstack(param_1,3);
        tmp_i7 = *(int *)(param_1 + 8);
      }
      *(int *)(param_1 + 8) = tmp_i7 + 0x24;
      luaD_call(param_1,tmp_i7,1);
      tmp_i7 = *(int *)(param_1 + 8);
      *(int *)(param_1 + 8) = tmp_i7 + -0xc;
      param_4 = (uint32_t *)((int)param_4 + (*(int *)(param_1 + 0x20) - tmp_i6));
      tmp_u1 = *(uint32_t *)(tmp_i7 + -8);
      *param_4 = *(uint32_t *)(tmp_i7 + -0xc);
      param_4[1] = tmp_u1;
      param_4[2] = *(uint32_t *)(tmp_i7 + -4);
      return;
    }
    tmp_i7 = tmp_i7 + -1;
    param_2 = tmp_pi5;
    if (tmp_i7 == 0) {
      luaG_runerror();
      return;
    }
  } while( true );
}

void luaV_settable(int param_1,int *param_2,uint32_t *param_3,int *param_4)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int *tmp_pi3;
  int tmp_i4;
  int *tmp_pi5;
  int tmp_i6;
  
  tmp_i6 = 100;
  tmp_i4 = param_2[2];
  do {
    if (tmp_i4 == 5) {
      tmp_i4 = *param_2;
      tmp_pi3 = (int *)luaH_set(param_1,tmp_i4,param_3);
      if ((((tmp_pi3[2] != 0) || (tmp_i1 = *(int *)(tmp_i4 + 8), tmp_i1 == 0)) ||
          ((*(byte *)(tmp_i1 + 6) & 2) != 0)) ||
         (tmp_pi5 = (int *)luaT_gettm(tmp_i1,1,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xac)),
         tmp_pi5 == (int *)0x0)) {
        tmp_i6 = param_4[1];
        *tmp_pi3 = *param_4;
        tmp_pi3[1] = tmp_i6;
        tmp_pi3[2] = param_4[2];
        if (((3 < param_4[2]) && ((*(byte *)(*param_4 + 5) & 3) != 0)) &&
           ((*(byte *)(tmp_i4 + 5) & 4) != 0)) {
          luaC_barrierback();
          return;
        }
        return;
      }
LAB_0021737c:
      tmp_i4 = tmp_pi5[2];
    }
    else {
      tmp_pi5 = (int *)luaT_gettmbyobj(param_1,param_2,1);
      tmp_i4 = tmp_pi5[2];
      if (tmp_i4 == 0) {
        luaG_typeerror(param_1,param_2,"index");
        goto LAB_0021737c;
      }
    }
    if (tmp_i4 == 6) {
      tmp_pi3 = *(int **)(param_1 + 8);
      tmp_i4 = tmp_pi5[1];
      *tmp_pi3 = *tmp_pi5;
      tmp_pi3[1] = tmp_i4;
      tmp_pi3[2] = tmp_pi5[2];
      tmp_i4 = param_2[1];
      tmp_i6 = *(int *)(param_1 + 8);
      *(int *)(tmp_i6 + 0xc) = *param_2;
      *(int *)(tmp_i6 + 0x10) = tmp_i4;
      *(int *)(tmp_i6 + 0x14) = param_2[2];
      tmp_i4 = *(int *)(param_1 + 8);
      tmp_u2 = *param_3;
      *(uint32_t *)(tmp_i4 + 0x1c) = param_3[1];
      *(uint32_t *)(tmp_i4 + 0x18) = tmp_u2;
      *(uint32_t *)(tmp_i4 + 0x20) = param_3[2];
      tmp_i4 = *param_4;
      tmp_i6 = *(int *)(param_1 + 8);
      *(int *)(tmp_i6 + 0x28) = param_4[1];
      *(int *)(tmp_i6 + 0x24) = tmp_i4;
      *(int *)(tmp_i6 + 0x2c) = param_4[2];
      tmp_i4 = *(int *)(param_1 + 8);
      if (*(int *)(param_1 + 0x1c) - tmp_i4 < 0x31) {
        luaD_growstack(param_1,4);
        tmp_i4 = *(int *)(param_1 + 8);
      }
      *(int *)(param_1 + 8) = tmp_i4 + 0x30;
      luaD_call();
      return;
    }
    tmp_i6 = tmp_i6 + -1;
    param_2 = tmp_pi5;
    if (tmp_i6 == 0) {
      luaG_runerror();
      return;
    }
  } while( true );
}

uint luaV_lessthan(int param_1,double *param_2,double *param_3)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint tmp_u5;
  size_t tmp_s6;
  uint32_t *tmp_pu7;
  size_t tmp_s8;
  char *__s1;
  char *__s2;
  size_t local_2c;
  
  tmp_i3 = *(int *)(param_2 + 1);
  if (tmp_i3 != *(int *)(param_3 + 1)) {
LAB_00217650:
    tmp_u5 = luaG_ordererror();
    return tmp_u5;
  }
  if (tmp_i3 == 3) {
    tmp_u5 = (uint)(*param_2 < *param_3);
  }
  else {
    if (tmp_i3 != 4) {
      tmp_pu1 = (uint32_t *)luaT_gettmbyobj(param_1,param_2,0xd);
      if (tmp_pu1[2] != 0) {
        tmp_u2 = luaT_gettmbyobj(param_1,param_3,0xd);
        tmp_i3 = luaO_rawequalObj(tmp_pu1,tmp_u2);
        if (tmp_i3 != 0) {
          tmp_pu7 = *(uint32_t **)(param_1 + 8);
          tmp_i3 = *(int *)(param_1 + 0x20);
          tmp_u2 = *tmp_pu1;
          tmp_pu7[1] = tmp_pu1[1];
          *tmp_pu7 = tmp_u2;
          tmp_pu7[2] = tmp_pu1[2];
          tmp_i4 = *(int *)(param_1 + 8);
          tmp_u2 = *(uint32_t *)((int)param_2 + 4);
          *(uint32_t *)(tmp_i4 + 0xc) = *(uint32_t *)param_2;
          *(uint32_t *)(tmp_i4 + 0x10) = tmp_u2;
          *(uint32_t *)(tmp_i4 + 0x14) = *(uint32_t *)(param_2 + 1);
          tmp_i4 = *(int *)(param_1 + 8);
          tmp_u2 = *(uint32_t *)((int)param_3 + 4);
          *(uint32_t *)(tmp_i4 + 0x18) = *(uint32_t *)param_3;
          *(uint32_t *)(tmp_i4 + 0x1c) = tmp_u2;
          *(uint32_t *)(tmp_i4 + 0x20) = *(uint32_t *)(param_3 + 1);
          tmp_i4 = *(int *)(param_1 + 8);
          if (*(int *)(param_1 + 0x1c) - tmp_i4 < 0x25) {
            luaD_growstack(param_1,3);
            tmp_i4 = *(int *)(param_1 + 8);
          }
          *(int *)(param_1 + 8) = tmp_i4 + 0x24;
          luaD_call(param_1,tmp_i4,1);
          tmp_i4 = *(int *)(param_1 + 8);
          *(int *)(param_1 + 8) = tmp_i4 + -0xc;
          tmp_pu7 = (uint32_t *)((int)tmp_pu7 + (*(int *)(param_1 + 0x20) - tmp_i3));
          tmp_u2 = *(uint32_t *)(tmp_i4 + -8);
          *tmp_pu7 = *(uint32_t *)(tmp_i4 + -0xc);
          tmp_pu7[1] = tmp_u2;
          tmp_pu7[2] = *(uint32_t *)(tmp_i4 + -4);
          tmp_i3 = (*(int **)(param_1 + 8))[2];
          if (tmp_i3 != 0) {
            if (tmp_i3 != 1) {
              return 1;
            }
            return (uint)(**(int **)(param_1 + 8) != 0);
          }
          return 0;
        }
      }
      goto LAB_00217650;
    }
    local_2c = *(size_t *)(*(int *)param_2 + 0xc);
    __s1 = (char *)(*(int *)param_2 + 0x10);
    tmp_s8 = *(size_t *)(*(int *)param_3 + 0xc);
    __s2 = (char *)(*(int *)param_3 + 0x10);
    while (tmp_u5 = strcoll(__s1,__s2), tmp_u5 == 0) {
      tmp_s6 = strlen(__s1);
      if (tmp_s6 == tmp_s8) {
        return 0;
      }
      if (tmp_s6 == local_2c) {
        return 1;
      }
      tmp_i3 = tmp_s6 + 1;
      local_2c = local_2c - tmp_i3;
      __s1 = __s1 + tmp_i3;
      __s2 = __s2 + tmp_i3;
      tmp_s8 = tmp_s8 - tmp_i3;
    }
    tmp_u5 = tmp_u5 >> 0x1f;
  }
  return tmp_u5;
}

bool luaV_equalval(int param_1,double *param_2,double *param_3)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  bool tmp_b6;
  
  switch(*(uint32_t *)(param_2 + 1)) {
  default:
    tmp_b6 = *(int *)param_2 == *(int *)param_3;
    break;
  case 3:
    tmp_b6 = *param_3 == *param_2;
    break;
  case 5:
  case 7:
    if (*(int *)param_2 != *(int *)param_3) {
      tmp_i3 = *(int *)(*(int *)param_3 + 8);
      tmp_i4 = *(int *)(*(int *)param_2 + 8);
      if ((((tmp_i4 == 0) || ((*(byte *)(tmp_i4 + 6) & 0x10) != 0)) ||
          (tmp_pu2 = (uint32_t *)
                    luaT_gettm(tmp_i4,4,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xb8)),
          tmp_pu2 == (uint32_t *)0x0)) ||
         ((tmp_i3 != tmp_i4 &&
          (((tmp_i3 == 0 || ((*(byte *)(tmp_i3 + 6) & 0x10) != 0)) ||
           ((tmp_i3 = luaT_gettm(tmp_i3,4,*(uint32_t *)(*(int *)(param_1 + 0x10) + 0xb8)),
            tmp_i3 == 0 || (tmp_i3 = luaO_rawequalObj(tmp_pu2,tmp_i3), tmp_i3 == 0)))))))) {
        return false;
      }
      tmp_pu5 = *(uint32_t **)(param_1 + 8);
      tmp_i3 = *(int *)(param_1 + 0x20);
      tmp_u1 = tmp_pu2[1];
      *tmp_pu5 = *tmp_pu2;
      tmp_pu5[1] = tmp_u1;
      tmp_pu5[2] = tmp_pu2[2];
      tmp_i4 = *(int *)(param_1 + 8);
      tmp_u1 = *(uint32_t *)((int)param_2 + 4);
      *(uint32_t *)(tmp_i4 + 0xc) = *(uint32_t *)param_2;
      *(uint32_t *)(tmp_i4 + 0x10) = tmp_u1;
      *(uint32_t *)(tmp_i4 + 0x14) = *(uint32_t *)(param_2 + 1);
      tmp_i4 = *(int *)(param_1 + 8);
      tmp_u1 = *(uint32_t *)param_3;
      *(uint32_t *)(tmp_i4 + 0x1c) = *(uint32_t *)((int)param_3 + 4);
      *(uint32_t *)(tmp_i4 + 0x18) = tmp_u1;
      *(uint32_t *)(tmp_i4 + 0x20) = *(uint32_t *)(param_3 + 1);
      tmp_i4 = *(int *)(param_1 + 8);
      if (*(int *)(param_1 + 0x1c) - tmp_i4 < 0x25) {
        luaD_growstack(param_1,3);
        tmp_i4 = *(int *)(param_1 + 8);
      }
      *(int *)(param_1 + 8) = tmp_i4 + 0x24;
      luaD_call(param_1,tmp_i4,1);
      tmp_i4 = *(int *)(param_1 + 8);
      *(int *)(param_1 + 8) = tmp_i4 + -0xc;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + (*(int *)(param_1 + 0x20) - tmp_i3));
      tmp_u1 = *(uint32_t *)(tmp_i4 + -8);
      *tmp_pu5 = *(uint32_t *)(tmp_i4 + -0xc);
      tmp_pu5[1] = tmp_u1;
      tmp_pu5[2] = *(uint32_t *)(tmp_i4 + -4);
      tmp_i3 = (*(int **)(param_1 + 8))[2];
      if (tmp_i3 == 0) {
        return false;
      }
      if ((tmp_i3 == 1) && (**(int **)(param_1 + 8) == 0)) {
        return false;
      }
    }
  case 0:
    tmp_b6 = true;
  }
  return tmp_b6;
}

void luaV_concat(int param_1,int param_2,int param_3)
{
  int *tmp_pi1;
  uint16_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t *tmp_pu4;
  uint tmp_u5;
  uint tmp_u6;
  int tmp_i7;
  int tmp_i8;
  uint32_t tmp_u9;
  uint32_t *tmp_pu10;
  char *tmp_pc11;
  uint *tmp_pu12;
  uint *tmp_pu13;
  int *tmp_pi14;
  int *tmp_pi15;
  int tmp_i16;
  uint32_t *tmp_pu17;
  byte tmp_b18;
  uint64_t in_stack_ffffff9c;
  uint64_t tmp_u19;
  ulonglong tmp_u20;
  int local_50;
  int local_40;
  uint local_3c [10];
  uint32_t uStack_14;
  
  tmp_b18 = 0;
  uStack_14 = 0x217939;
  do {
    tmp_pi1 = (int *)(*(int *)(param_1 + 0xc) + (param_3 * 3 + 3) * 4);
    tmp_u20 = (ulonglong)(uint)tmp_pi1[-4];
    if (tmp_pi1[-4] - 3U < 2) {
      if (tmp_pi1[-1] != 4) {
        if (tmp_pi1[-1] != 3) goto LAB_00217a81;
        tmp_u19 = *(uint64_t *)(tmp_pi1 + -3);
        sprintf((char *)local_3c,"%.14g",tmp_u19,tmp_u19);
        tmp_pu13 = local_3c;
        do {
          tmp_pu12 = tmp_pu13;
          tmp_u5 = *tmp_pu12 + 0xfefefeff & ~*tmp_pu12;
          tmp_u6 = tmp_u5 & 0x80808080;
          tmp_pu13 = tmp_pu12 + 1;
        } while (tmp_u6 == 0);
        if ((tmp_u5 & 0x8080) == 0) {
          tmp_pu13 = (uint *)((int)tmp_pu12 + 6);
          tmp_u6 = tmp_u6 >> 0x10;
        }
        tmp_pc11 = (char *)((int)tmp_pu13 +
                          ((-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)local_3c));
        in_stack_ffffff9c = CONCAT44((int)((ulonglong)tmp_u19 >> 0x20),tmp_pc11);
        tmp_i7 = luaS_newlstr(param_1,local_3c,tmp_pc11);
        tmp_pi1[-1] = 4;
        tmp_pi1[-3] = tmp_i7;
      }
      tmp_u9 = (uint32_t)((ulonglong)in_stack_ffffff9c >> 0x20);
      tmp_i7 = *(int *)(tmp_pi1[-3] + 0xc);
      if (tmp_i7 == 0) {
        local_50 = -1;
        if (tmp_pi1[-4] == 3) {
          tmp_u19 = *(uint64_t *)(tmp_pi1 + -6);
          sprintf((char *)local_3c,"%.14g",tmp_u19,tmp_u19);
          tmp_pu13 = local_3c;
          do {
            tmp_pu12 = tmp_pu13;
            tmp_u5 = *tmp_pu12 + 0xfefefeff & ~*tmp_pu12;
            tmp_u6 = tmp_u5 & 0x80808080;
            tmp_pu13 = tmp_pu12 + 1;
          } while (tmp_u6 == 0);
          if ((tmp_u5 & 0x8080) == 0) {
            tmp_pu13 = (uint *)((int)tmp_pu12 + 6);
            tmp_u6 = tmp_u6 >> 0x10;
          }
          tmp_pc11 = (char *)((int)tmp_pu13 +
                            ((-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)local_3c));
          in_stack_ffffff9c = CONCAT44((int)((ulonglong)tmp_u19 >> 0x20),tmp_pc11);
          tmp_i7 = luaS_newlstr(param_1,local_3c,tmp_pc11);
          tmp_pi1[-4] = 4;
          tmp_pi1[-6] = tmp_i7;
          local_50 = -1;
        }
      }
      else {
        if (param_2 < 2) {
          local_50 = 0;
          tmp_i16 = 1;
          local_40 = -0xc;
        }
        else {
          tmp_i16 = 1;
          tmp_pi15 = tmp_pi1 + -6;
          do {
            while( true ) {
              tmp_u9 = (uint32_t)((ulonglong)in_stack_ffffff9c >> 0x20);
              if (tmp_pi15[2] != 4) {
                if (tmp_pi15[2] != 3) {
                  local_40 = tmp_i16 * -0xc;
                  local_50 = 1 - tmp_i16;
                  goto LAB_00217d61;
                }
                tmp_u19 = *(uint64_t *)tmp_pi15;
                sprintf((char *)local_3c,"%.14g",tmp_u19);
                tmp_pu13 = local_3c;
                do {
                  tmp_pu12 = tmp_pu13;
                  tmp_u5 = *tmp_pu12 + 0xfefefeff & ~*tmp_pu12;
                  tmp_u6 = tmp_u5 & 0x80808080;
                  tmp_pu13 = tmp_pu12 + 1;
                } while (tmp_u6 == 0);
                if ((tmp_u5 & 0x8080) == 0) {
                  tmp_pu13 = (uint *)((int)tmp_pu12 + 6);
                  tmp_u6 = tmp_u6 >> 0x10;
                }
                tmp_pc11 = (char *)((int)tmp_pu13 +
                                  ((-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)local_3c));
                in_stack_ffffff9c = CONCAT44((int)((ulonglong)tmp_u19 >> 0x20),tmp_pc11);
                tmp_i8 = luaS_newlstr(param_1,local_3c,tmp_pc11);
                tmp_pi15[2] = 4;
                *tmp_pi15 = tmp_i8;
              }
              tmp_u9 = (uint32_t)((ulonglong)in_stack_ffffff9c >> 0x20);
              tmp_u6 = *(uint *)(*tmp_pi15 + 0xc);
              if (tmp_u6 < -tmp_i7 - 3U) break;
              tmp_i16 = tmp_i16 + 1;
              tmp_pi15 = tmp_pi15 + -3;
              luaG_runerror(param_1,"string length overflow");
              tmp_u9 = (uint32_t)((ulonglong)in_stack_ffffff9c >> 0x20);
              tmp_i7 = tmp_i7 + tmp_u6;
              if (tmp_i16 == param_2) goto LAB_00217c82;
            }
            tmp_i16 = tmp_i16 + 1;
            tmp_pi15 = tmp_pi15 + -3;
            tmp_i7 = tmp_i7 + tmp_u6;
          } while (tmp_i16 != param_2);
LAB_00217c82:
          local_40 = param_2 * -0xc;
          local_50 = 1 - param_2;
          tmp_i16 = param_2;
        }
LAB_00217d61:
        tmp_i8 = luaZ_openspace(param_1,*(int *)(param_1 + 0x10) + 0x34,tmp_i7);
        tmp_pi15 = tmp_pi1 + tmp_i16 * -3;
        tmp_i7 = 0;
        do {
          while( true ) {
            tmp_i16 = tmp_i7;
            tmp_pi14 = tmp_pi15;
            tmp_i7 = *tmp_pi14;
            tmp_u5 = *(uint *)(tmp_i7 + 0xc);
            tmp_pu10 = (uint32_t *)(tmp_i8 + tmp_i16);
            tmp_pu4 = (uint32_t *)(tmp_i7 + 0x10);
            tmp_u6 = tmp_u5;
            if (7 < tmp_u5) break;
LAB_00217da0:
            for (; tmp_u6 != 0; tmp_u6 = tmp_u6 - 1) {
              *(uint8_t *)tmp_pu10 = *(uint8_t *)tmp_pu4;
              tmp_pu4 = (uint32_t *)((int)tmp_pu4 + (uint)tmp_b18 * -2 + 1);
              tmp_pu10 = (uint32_t *)((int)tmp_pu10 + (uint)tmp_b18 * -2 + 1);
            }
            tmp_pi15 = tmp_pi14 + 3;
            tmp_i7 = tmp_i16 + tmp_u5;
            if (tmp_pi14 + 3 == tmp_pi1) goto LAB_00217e10;
          }
          tmp_pu17 = tmp_pu10;
          if (((uint)tmp_pu10 & 1) != 0) {
            tmp_pu17 = (uint32_t *)((int)tmp_pu10 + 1);
            tmp_pu4 = (uint32_t *)(tmp_i7 + 0x11);
            *(uint8_t *)tmp_pu10 = *(uint8_t *)(tmp_i7 + 0x10);
            tmp_u6 = tmp_u5 - 1;
          }
          tmp_pu10 = tmp_pu17;
          if (((uint)tmp_pu17 & 2) != 0) {
            tmp_u2 = *(uint16_t *)tmp_pu4;
            tmp_pu10 = (uint32_t *)((int)tmp_pu17 + 2);
            tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
            tmp_u6 = tmp_u6 - 2;
            *(uint16_t *)tmp_pu17 = tmp_u2;
          }
          if (((uint)tmp_pu10 & 4) == 0) goto LAB_00217da0;
          *tmp_pu10 = *tmp_pu4;
          tmp_pu4 = tmp_pu4 + 1;
          tmp_pu10 = tmp_pu10 + 1;
          for (tmp_i7 = tmp_u6 - 4; tmp_i7 != 0; tmp_i7 = tmp_i7 + -1) {
            *(uint8_t *)tmp_pu10 = *(uint8_t *)tmp_pu4;
            tmp_pu4 = (uint32_t *)((int)tmp_pu4 + (uint)tmp_b18 * -2 + 1);
            tmp_pu10 = (uint32_t *)((int)tmp_pu10 + (uint)tmp_b18 * -2 + 1);
          }
          tmp_pi15 = tmp_pi14 + 3;
          tmp_i7 = tmp_i16 + tmp_u5;
        } while (tmp_pi14 + 3 != tmp_pi1);
LAB_00217e10:
        in_stack_ffffff9c = CONCAT44(tmp_u9,tmp_i16 + tmp_u5);
        tmp_pu4 = (uint32_t *)((int)tmp_pi14 + local_40 + 0xc);
        tmp_u9 = luaS_newlstr(param_1,tmp_i8,tmp_i16 + tmp_u5);
        tmp_pu4[2] = 4;
        *tmp_pu4 = tmp_u9;
      }
    }
    else {
LAB_00217a81:
      tmp_u9 = (uint32_t)((ulonglong)in_stack_ffffff9c >> 0x20);
      tmp_pi15 = tmp_pi1 + -6;
      tmp_pu4 = (uint32_t *)luaT_gettmbyobj(param_1,tmp_pi15,0xf);
      if (tmp_pu4[2] == 0) {
        tmp_pi14 = tmp_pi1 + -3;
        tmp_pu4 = (uint32_t *)luaT_gettmbyobj(param_1,tmp_pi14,0xf,tmp_u9,tmp_u20);
        if (tmp_pu4[2] == 0) {
          in_stack_ffffff9c = CONCAT44(tmp_u9,tmp_pi14);
          luaG_concaterror(param_1,tmp_pi15,tmp_pi14);
          local_50 = -1;
          goto LAB_00217a30;
        }
      }
      tmp_i7 = *(int *)(param_1 + 0x20);
      tmp_pu10 = *(uint32_t **)(param_1 + 8);
      tmp_u3 = tmp_pu4[1];
      *tmp_pu10 = *tmp_pu4;
      tmp_pu10[1] = tmp_u3;
      tmp_pu10[2] = tmp_pu4[2];
      tmp_i16 = *(int *)(param_1 + 8);
      tmp_i8 = tmp_pi1[-6];
      *(int *)(tmp_i16 + 0x10) = tmp_pi1[-5];
      *(int *)(tmp_i16 + 0xc) = tmp_i8;
      *(int *)(tmp_i16 + 0x14) = tmp_pi1[-4];
      tmp_i16 = *(int *)(param_1 + 8);
      tmp_i8 = tmp_pi1[-3];
      *(int *)(tmp_i16 + 0x1c) = tmp_pi1[-2];
      *(int *)(tmp_i16 + 0x18) = tmp_i8;
      *(int *)(tmp_i16 + 0x20) = tmp_pi1[-1];
      tmp_i16 = *(int *)(param_1 + 8);
      if (*(int *)(param_1 + 0x1c) - tmp_i16 < 0x25) {
        luaD_growstack(param_1,3);
        tmp_i16 = *(int *)(param_1 + 8);
      }
      *(int *)(param_1 + 8) = tmp_i16 + 0x24;
      in_stack_ffffff9c = CONCAT44(tmp_u9,1);
      luaD_call(param_1,tmp_i16,1);
      tmp_i16 = *(int *)(param_1 + 8);
      tmp_pu4 = (uint32_t *)((int)tmp_pi15 + (*(int *)(param_1 + 0x20) - tmp_i7));
      *(int *)(param_1 + 8) = tmp_i16 + -0xc;
      tmp_u9 = *(uint32_t *)(tmp_i16 + -8);
      *tmp_pu4 = *(uint32_t *)(tmp_i16 + -0xc);
      tmp_pu4[1] = tmp_u9;
      local_50 = -1;
      tmp_pu4[2] = *(uint32_t *)(tmp_i16 + -4);
    }
LAB_00217a30:
    param_2 = param_2 + local_50;
    param_3 = param_3 + local_50;
    if (param_2 < 2) {
      return;
    }
  } while( true );
}

void luaV_execute(int param_1,int param_2)
{
  double tmp_d1;
  byte tmp_b2;
  char tmp_c3;
  bool tmp_b4;
  void *tmp_pc5;
  int tmp_i6;
  uint32_t tmp_u7;
  double *pdVar8;
  int tmp_i10;
  int tmp_i11;
  uint tmp_u12;
  int tmp_i13;
  uint32_t tmp_u14;
  int *tmp_pi15;
  int tmp_i16;
  uint tmp_u17;
  size_t tmp_s18;
  uint *tmp_pu19;
  uint32_t *tmp_pu20;
  uint32_t *tmp_pu21;
  int tmp_i22;
  uint32_t *tmp_pu23;
  int *tmp_pi24;
  size_t tmp_s25;
  char *__s1;
  uint *tmp_pu26;
  uint tmp_u27;
  char *__s2;
  ushort inreg_FPUControlWord;
  double tmp_d28;
  uint64_t tmp_u29;
  uint64_t tmp_u30;
  uint local_74;
  uint *local_68;
  int local_64;
  double *local_60;
  ushort local_2c;
  uint16_t uStack_2a;
  uint32_t uStack_28;
  uint32_t local_24;
  double *pdVar9;
  
  tmp_i22 = *(int *)(param_1 + 0x14);
LAB_00217ec6:
  local_64 = *(int *)(param_1 + 0xc);
  tmp_i22 = **(int **)(tmp_i22 + 4);
  tmp_i16 = *(int *)(*(int *)(tmp_i22 + 0x10) + 8);
  local_68 = *(uint **)(param_1 + 0x18);
switchD_00217fed_default:
  tmp_pu19 = local_68;
  local_68 = tmp_pu19 + 1;
  tmp_u12 = *tmp_pu19;
  tmp_b2 = *(byte *)(param_1 + 0x38);
  if ((tmp_b2 & 0xc) != 0) {
    tmp_i11 = *(int *)(param_1 + 0x40) + -1;
    *(int *)(param_1 + 0x40) = tmp_i11;
    if (tmp_i11 == 0) {
      tmp_pu26 = *(uint **)(param_1 + 0x18);
      *(uint **)(param_1 + 0x18) = local_68;
      if ((tmp_b2 & 8) != 0) {
        *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x3c);
        luaD_callhook(param_1,3,0xffffffff);
      }
      if ((tmp_b2 & 4) != 0) goto LAB_00217f3e;
      tmp_c3 = *(char *)(param_1 + 6);
    }
    else {
      if ((tmp_b2 & 4) == 0) goto LAB_00217fb6;
      tmp_pu26 = *(uint **)(param_1 + 0x18);
      *(uint **)(param_1 + 0x18) = local_68;
LAB_00217f3e:
      tmp_i11 = *(int *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0x10);
      tmp_i13 = *(int *)(tmp_i11 + 0xc);
      tmp_i11 = *(int *)(tmp_i11 + 0x14);
      tmp_i6 = ((int)local_68 - tmp_i13 >> 2) + -1;
      if (tmp_i11 == 0) {
        if ((local_68 <= tmp_pu26) || (tmp_i6 == 0)) {
          local_64 = 0;
          goto LAB_00217f84;
        }
      }
      else {
        local_64 = *(int *)(tmp_i11 + tmp_i6 * 4);
        if (((local_68 <= tmp_pu26) || (tmp_i6 == 0)) ||
           (local_64 != *(int *)((int)tmp_pu26 + ((tmp_i11 + -4) - tmp_i13)))) {
LAB_00217f84:
          luaD_callhook(param_1,2,local_64);
        }
      }
      tmp_c3 = *(char *)(param_1 + 6);
    }
    if (tmp_c3 == '\x01') {
      *(uint **)(param_1 + 0x18) = tmp_pu19;
      return;
    }
    local_64 = *(int *)(param_1 + 0xc);
  }
LAB_00217fb6:
  tmp_u27 = tmp_u12 >> 6 & 0xff;
  tmp_i11 = tmp_u27 * 0xc;
  local_60 = (double *)(local_64 + tmp_i11);
  switch(tmp_u12 & 0x3f) {
  case 0:
    tmp_pu20 = (uint32_t *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
    goto LAB_00218762;
  case 1:
    tmp_pu20 = (uint32_t *)(tmp_i16 + (tmp_u12 >> 0xe) * 0xc);
    goto LAB_00218762;
  case 2:
    *(uint *)local_60 = tmp_u12 >> 0x17;
    *(uint32_t *)(local_60 + 1) = 1;
    if ((tmp_u12 & 0x7fc000) != 0) {
      local_68 = tmp_pu19 + 2;
    }
    goto switchD_00217fed_default;
  case 3:
    pdVar9 = (double *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
    do {
      pdVar8 = (double *)((int)pdVar9 + -0xc);
      *(uint32_t *)(pdVar9 + 1) = 0;
      pdVar9 = pdVar8;
    } while (local_60 <= pdVar8);
    goto switchD_00217fed_default;
  case 4:
    tmp_pu20 = *(uint32_t **)(*(int *)(tmp_i22 + 0x14 + (tmp_u12 >> 0x17) * 4) + 8);
LAB_00218762:
    tmp_u14 = tmp_pu20[1];
    *(uint32_t *)local_60 = *tmp_pu20;
    *(uint32_t *)((int)local_60 + 4) = tmp_u14;
    *(uint32_t *)(local_60 + 1) = tmp_pu20[2];
    goto switchD_00217fed_default;
  case 5:
    tmp_u14 = *(uint32_t *)(tmp_i22 + 0xc);
    *(uint **)(param_1 + 0x18) = local_68;
    local_2c = (ushort)tmp_u14;
    uStack_2a = (uint16_t)((uint)tmp_u14 >> 0x10);
    local_24 = 5;
    luaV_gettable(param_1,&local_2c,tmp_i16 + (tmp_u12 >> 0xe) * 0xc);
    local_64 = *(int *)(param_1 + 0xc);
    goto switchD_00217fed_default;
  case 6:
    *(uint **)(param_1 + 0x18) = local_68;
    goto LAB_002186e7;
  case 7:
    local_24 = 5;
    local_2c = (ushort)*(uint32_t *)(tmp_i22 + 0xc);
    uStack_2a = (uint16_t)((uint)*(uint32_t *)(tmp_i22 + 0xc) >> 0x10);
    *(uint **)(param_1 + 0x18) = local_68;
    luaV_settable(param_1,&local_2c,tmp_i16 + (tmp_u12 >> 0xe) * 0xc);
    local_64 = *(int *)(param_1 + 0xc);
    goto switchD_00217fed_default;
  case 8:
    tmp_i11 = *(int *)(tmp_i22 + 0x14 + (tmp_u12 >> 0x17) * 4);
    tmp_u14 = *(uint32_t *)local_60;
    tmp_pu20 = *(uint32_t **)(tmp_i11 + 8);
    tmp_pu20[1] = *(uint32_t *)((int)local_60 + 4);
    *tmp_pu20 = tmp_u14;
    tmp_pu20[2] = *(uint32_t *)(local_60 + 1);
    if (((3 < *(int *)(local_60 + 1)) && ((*(byte *)(*(int *)local_60 + 5) & 3) != 0)) &&
       ((*(byte *)(tmp_i11 + 5) & 4) != 0)) {
      luaC_barrierf(param_1,tmp_i11,*(int *)local_60);
    }
    goto switchD_00217fed_default;
  case 9:
    *(uint **)(param_1 + 0x18) = local_68;
    if ((tmp_u12 >> 0xe & 0x100) == 0) {
      if ((tmp_u12 >> 0x17 & 0x100) == 0) goto LAB_002191f8;
LAB_00218599:
      local_64 = tmp_i16 + (tmp_u12 >> 0x17 & 0xfffffeff) * 0xc;
    }
    else {
      if ((tmp_u12 >> 0x17 & 0x100) != 0) goto LAB_00218599;
LAB_002191f8:
      local_64 = local_64 + (tmp_u12 >> 0x17) * 0xc;
    }
    luaV_settable(param_1,local_60,local_64);
    local_64 = *(int *)(param_1 + 0xc);
    goto switchD_00217fed_default;
  case 10:
    tmp_u14 = luaO_fb2int(tmp_u12 >> 0xe & 0x1ff);
    tmp_u7 = luaO_fb2int(tmp_u12 >> 0x17);
    tmp_u14 = luaH_new(param_1,tmp_u7,tmp_u14);
    *(uint32_t *)(local_60 + 1) = 5;
    *(uint32_t *)local_60 = tmp_u14;
    *(uint **)(param_1 + 0x18) = local_68;
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      luaC_step();
    }
    break;
  case 0xb:
    tmp_pu20 = (uint32_t *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
    tmp_u14 = tmp_pu20[1];
    *(uint32_t *)((int)local_60 + 0xc) = *tmp_pu20;
    *(uint32_t *)(local_60 + 2) = tmp_u14;
    *(uint32_t *)((int)local_60 + 0x14) = tmp_pu20[2];
    *(uint **)(param_1 + 0x18) = local_68;
LAB_002186e7:
    luaV_gettable();
    break;
  case 0xc:
    tmp_u27 = tmp_u12 >> 0x17;
    if ((tmp_u27 & 0x100) == 0) {
      pdVar9 = (double *)(local_64 + tmp_u27 * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) == 0) goto LAB_002192bf;
LAB_00218442:
      pdVar8 = (double *)(tmp_i16 + (tmp_u12 >> 0xe & 0xff) * 0xc);
    }
    else {
      pdVar9 = (double *)(tmp_i16 + (tmp_u27 & 0xfffffeff) * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) != 0) goto LAB_00218442;
LAB_002192bf:
      pdVar8 = (double *)(local_64 + (tmp_u12 >> 0xe & 0x1ff) * 0xc);
    }
    if ((*(int *)(pdVar9 + 1) != 3) || (*(int *)(pdVar8 + 1) != 3)) {
      *(uint **)(param_1 + 0x18) = local_68;
      tmp_u29 = 5;
      goto LAB_0021846f;
    }
    tmp_d28 = *pdVar9;
    tmp_d1 = *pdVar8;
    *(uint32_t *)(local_60 + 1) = 3;
    *local_60 = tmp_d28 + tmp_d1;
    goto switchD_00217fed_default;
  case 0xd:
    tmp_u27 = tmp_u12 >> 0x17;
    if ((tmp_u27 & 0x100) == 0) {
      pdVar9 = (double *)(local_64 + tmp_u27 * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) == 0) goto LAB_002192f7;
LAB_002183e2:
      pdVar8 = (double *)(tmp_i16 + (tmp_u12 >> 0xe & 0xff) * 0xc);
    }
    else {
      pdVar9 = (double *)(tmp_i16 + (tmp_u27 & 0xfffffeff) * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) != 0) goto LAB_002183e2;
LAB_002192f7:
      pdVar8 = (double *)(local_64 + (tmp_u12 >> 0xe & 0x1ff) * 0xc);
    }
    if ((*(int *)(pdVar9 + 1) != 3) || (*(int *)(pdVar8 + 1) != 3)) {
      *(uint **)(param_1 + 0x18) = local_68;
      tmp_u29 = 6;
      goto LAB_0021846f;
    }
    tmp_d28 = *pdVar9;
    tmp_d1 = *pdVar8;
    *(uint32_t *)(local_60 + 1) = 3;
    *local_60 = tmp_d28 - tmp_d1;
    goto switchD_00217fed_default;
  case 0xe:
    tmp_u27 = tmp_u12 >> 0x17;
    if ((tmp_u27 & 0x100) == 0) {
      pdVar9 = (double *)(local_64 + tmp_u27 * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) == 0) goto LAB_0021932f;
LAB_00218382:
      pdVar8 = (double *)(tmp_i16 + (tmp_u12 >> 0xe & 0xff) * 0xc);
    }
    else {
      pdVar9 = (double *)(tmp_i16 + (tmp_u27 & 0xfffffeff) * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) != 0) goto LAB_00218382;
LAB_0021932f:
      pdVar8 = (double *)(local_64 + (tmp_u12 >> 0xe & 0x1ff) * 0xc);
    }
    if ((*(int *)(pdVar9 + 1) != 3) || (*(int *)(pdVar8 + 1) != 3)) {
      *(uint **)(param_1 + 0x18) = local_68;
      tmp_u30 = 7;
      goto LAB_002182e7;
    }
    tmp_d28 = *pdVar9;
    tmp_d1 = *pdVar8;
    *(uint32_t *)(local_60 + 1) = 3;
    *local_60 = tmp_d28 * tmp_d1;
    goto switchD_00217fed_default;
  case 0xf:
    tmp_u27 = tmp_u12 >> 0x17;
    if ((tmp_u27 & 0x100) == 0) {
      pdVar9 = (double *)(local_64 + tmp_u27 * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) == 0) goto LAB_00219367;
LAB_00218322:
      pdVar8 = (double *)(tmp_i16 + (tmp_u12 >> 0xe & 0xff) * 0xc);
    }
    else {
      pdVar9 = (double *)(tmp_i16 + (tmp_u27 & 0xfffffeff) * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) != 0) goto LAB_00218322;
LAB_00219367:
      pdVar8 = (double *)(local_64 + (tmp_u12 >> 0xe & 0x1ff) * 0xc);
    }
    if ((*(int *)(pdVar9 + 1) == 3) && (*(int *)(pdVar8 + 1) == 3)) {
      tmp_d28 = *pdVar9;
      tmp_d1 = *pdVar8;
      *(uint32_t *)(local_60 + 1) = 3;
      *local_60 = tmp_d28 / tmp_d1;
    }
    else {
      *(uint **)(param_1 + 0x18) = local_68;
      tmp_u29 = 8;
LAB_0021846f:
      Arith(pdVar9,pdVar8,tmp_u29);
      local_64 = *(int *)(param_1 + 0xc);
    }
    goto switchD_00217fed_default;
  case 0x10:
    tmp_u27 = tmp_u12 >> 0x17;
    if ((tmp_u27 & 0x100) == 0) {
      pdVar9 = (double *)(local_64 + tmp_u27 * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) == 0) goto LAB_0021922f;
LAB_002182ba:
      pdVar8 = (double *)(tmp_i16 + (tmp_u12 >> 0xe & 0xff) * 0xc);
    }
    else {
      pdVar9 = (double *)(tmp_i16 + (tmp_u27 & 0xfffffeff) * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) != 0) goto LAB_002182ba;
LAB_0021922f:
      pdVar8 = (double *)(local_64 + (tmp_u12 >> 0xe & 0x1ff) * 0xc);
    }
    if ((*(int *)(pdVar9 + 1) != 3) || (*(int *)(pdVar8 + 1) != 3)) {
      *(uint **)(param_1 + 0x18) = local_68;
      tmp_u30 = 9;
      goto LAB_002182e7;
    }
    tmp_d28 = *pdVar9;
    tmp_d1 = *pdVar8;
    local_2c = inreg_FPUControlWord & 0xf3ff | 0x400;
    *(uint32_t *)(local_60 + 1) = 3;
    *local_60 = tmp_d28 - ROUND(tmp_d28 / tmp_d1) * tmp_d1;
    goto switchD_00217fed_default;
  case 0x11:
    tmp_u27 = tmp_u12 >> 0x17;
    if ((tmp_u27 & 0x100) == 0) {
      pdVar9 = (double *)(local_64 + tmp_u27 * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) == 0) goto LAB_00219267;
LAB_0021825a:
      pdVar8 = (double *)(tmp_i16 + (tmp_u12 >> 0xe & 0xff) * 0xc);
    }
    else {
      pdVar9 = (double *)(tmp_i16 + (tmp_u27 & 0xfffffeff) * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) != 0) goto LAB_0021825a;
LAB_00219267:
      pdVar8 = (double *)(local_64 + (tmp_u12 >> 0xe & 0x1ff) * 0xc);
    }
    if ((*(int *)(pdVar9 + 1) == 3) && (*(int *)(pdVar8 + 1) == 3)) {
      tmp_d28 = pow(*pdVar9,*pdVar8);
      *(uint32_t *)(local_60 + 1) = 3;
      *local_60 = tmp_d28;
    }
    else {
      *(uint **)(param_1 + 0x18) = local_68;
      tmp_u30 = 10;
LAB_002182e7:
      tmp_u29 = CONCAT44(pdVar8,pdVar9);
LAB_00218210:
      Arith(tmp_u29,tmp_u30);
      local_64 = *(int *)(param_1 + 0xc);
    }
    goto switchD_00217fed_default;
  case 0x12:
    pdVar9 = (double *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
    if (*(int *)(pdVar9 + 1) != 3) {
      *(uint **)(param_1 + 0x18) = local_68;
      tmp_u30 = 0xb;
      tmp_u29 = CONCAT44(pdVar9,pdVar9);
      goto LAB_00218210;
    }
    *local_60 = -*pdVar9;
    *(uint32_t *)(local_60 + 1) = 3;
    goto switchD_00217fed_default;
  case 0x13:
    tmp_pi24 = (int *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
    tmp_u12 = 1;
    tmp_i11 = tmp_pi24[2];
    if ((tmp_i11 != 0) && (tmp_u12 = 0, tmp_i11 == 1)) {
      tmp_u12 = (uint)(*tmp_pi24 == 0);
    }
    *(uint *)local_60 = tmp_u12;
    *(uint32_t *)(local_60 + 1) = 1;
    goto switchD_00217fed_default;
  case 0x14:
    tmp_pi24 = (int *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
    if (tmp_pi24[2] == 4) {
      tmp_u12 = *(uint *)(*tmp_pi24 + 0xc);
      *(uint32_t *)(local_60 + 1) = 3;
      *local_60 = (double)tmp_u12;
      goto switchD_00217fed_default;
    }
    if (tmp_pi24[2] == 5) {
      tmp_i11 = luaH_getn();
      *(uint32_t *)(local_60 + 1) = 3;
      *local_60 = (double)tmp_i11;
      goto switchD_00217fed_default;
    }
    *(uint **)(param_1 + 0x18) = local_68;
    tmp_pu20 = (uint32_t *)luaT_gettmbyobj(param_1,tmp_pi24,0xc);
    if ((tmp_pu20[2] == 0) &&
       (tmp_pu20 = (uint32_t *)luaT_gettmbyobj(param_1,&luaO_nilobject_,0xc), tmp_pu20[2] == 0)) {
      luaG_typeerror(param_1,tmp_pi24,"get length of");
    }
    else {
      tmp_i11 = *(int *)(param_1 + 0x20);
      tmp_pu21 = *(uint32_t **)(param_1 + 8);
      tmp_u14 = tmp_pu20[1];
      *tmp_pu21 = *tmp_pu20;
      tmp_pu21[1] = tmp_u14;
      tmp_pu21[2] = tmp_pu20[2];
      tmp_i13 = *(int *)(param_1 + 8);
      tmp_i6 = tmp_pi24[1];
      *(int *)(tmp_i13 + 0xc) = *tmp_pi24;
      *(int *)(tmp_i13 + 0x10) = tmp_i6;
      *(int *)(tmp_i13 + 0x14) = tmp_pi24[2];
      tmp_u14 = g_unk_002701c4;
      tmp_i13 = *(int *)(param_1 + 8);
      *(uint32_t *)(tmp_i13 + 0x18) = luaO_nilobject_;
      tmp_u7 = g_unk_002701c8;
      *(uint32_t *)(tmp_i13 + 0x1c) = tmp_u14;
      *(uint32_t *)(tmp_i13 + 0x20) = tmp_u7;
      tmp_i13 = *(int *)(param_1 + 8);
      if (*(int *)(param_1 + 0x1c) - tmp_i13 < 0x25) {
        luaD_growstack(param_1);
        tmp_i13 = *(int *)(param_1 + 8);
      }
      *(int *)(param_1 + 8) = tmp_i13 + 0x24;
      luaD_call(param_1,tmp_i13,1);
      tmp_pu20 = (uint32_t *)((int)local_60 + (*(int *)(param_1 + 0x20) - tmp_i11));
      tmp_i11 = *(int *)(param_1 + 8);
      *(int *)(param_1 + 8) = tmp_i11 + -0xc;
      tmp_u14 = *(uint32_t *)(tmp_i11 + -8);
      *tmp_pu20 = *(uint32_t *)(tmp_i11 + -0xc);
      tmp_pu20[1] = tmp_u14;
      tmp_pu20[2] = *(uint32_t *)(tmp_i11 + -4);
    }
    break;
  case 0x15:
    tmp_u27 = tmp_u12 >> 0xe & 0x1ff;
    *(uint **)(param_1 + 0x18) = local_68;
    luaV_concat(param_1,(tmp_u27 - (tmp_u12 >> 0x17)) + 1,tmp_u27);
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      luaC_step();
    }
    local_64 = *(int *)(param_1 + 0xc);
    tmp_pu21 = (uint32_t *)(tmp_i11 + local_64);
    tmp_pu20 = (uint32_t *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
    tmp_u14 = tmp_pu20[1];
    *tmp_pu21 = *tmp_pu20;
    tmp_pu21[1] = tmp_u14;
    tmp_pu21[2] = tmp_pu20[2];
    goto switchD_00217fed_default;
  case 0x16:
    goto _L545;
  case 0x17:
    tmp_u17 = tmp_u12 >> 0x17;
    if ((tmp_u17 & 0x100) == 0) {
      local_60 = (double *)(local_64 + tmp_u17 * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) == 0) goto LAB_002190cb;
LAB_00218ebe:
      local_64 = tmp_i16 + (tmp_u12 >> 0xe & 0xff) * 0xc;
    }
    else {
      local_60 = (double *)(tmp_i16 + (tmp_u17 & 0xfffffeff) * 0xc);
      if ((tmp_u12 >> 0xe & 0x100) != 0) goto LAB_00218ebe;
LAB_002190cb:
      local_64 = local_64 + (tmp_u12 >> 0xe & 0x1ff) * 0xc;
    }
    *(uint **)(param_1 + 0x18) = local_68;
    local_74 = 0;
    if (*(int *)((int)local_60 + 8) == *(int *)(local_64 + 8)) {
      tmp_i11 = luaV_equalval(param_1,local_60,local_64);
      local_74 = (uint)(tmp_i11 != 0);
    }
    goto joined_r0x00218e03;
  case 0x18:
    *(uint **)(param_1 + 0x18) = local_68;
    tmp_u17 = tmp_u12 >> 0xe;
    if ((tmp_u17 & 0x100) == 0) {
      tmp_i11 = local_64 + (tmp_u17 & 0x1ff) * 0xc;
      if ((tmp_u12 >> 0x17 & 0x100) == 0) goto LAB_00219160;
LAB_00218e49:
      local_64 = tmp_i16 + (tmp_u12 >> 0x17 & 0xfffffeff) * 0xc;
    }
    else {
      tmp_i11 = tmp_i16 + (tmp_u17 & 0xff) * 0xc;
      if ((tmp_u12 >> 0x17 & 0x100) != 0) goto LAB_00218e49;
LAB_00219160:
      local_64 = local_64 + (tmp_u12 >> 0x17) * 0xc;
    }
    local_74 = luaV_lessthan(param_1,local_64,tmp_i11);
    goto joined_r0x00218e03;
  case 0x19:
    *(uint **)(param_1 + 0x18) = local_68;
    tmp_u17 = tmp_u12 >> 0xe;
    if ((tmp_u17 & 0x100) == 0) {
      local_60 = (double *)(local_64 + (tmp_u17 & 0x1ff) * 0xc);
      if ((tmp_u12 >> 0x17 & 0x100) == 0) goto LAB_00219104;
LAB_00218da5:
      pdVar9 = (double *)(tmp_i16 + (tmp_u12 >> 0x17 & 0xfffffeff) * 0xc);
      tmp_i11 = *(int *)(pdVar9 + 1);
      if (tmp_i11 == *(int *)(local_60 + 1)) goto LAB_00218dc5;
LAB_00219124:
      local_74 = luaG_ordererror(param_1,pdVar9,local_60);
    }
    else {
      local_60 = (double *)(tmp_i16 + (tmp_u17 & 0xff) * 0xc);
      if ((tmp_u12 >> 0x17 & 0x100) != 0) goto LAB_00218da5;
LAB_00219104:
      pdVar9 = (double *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
      tmp_i11 = *(int *)(pdVar9 + 1);
      if (tmp_i11 != *(int *)(local_60 + 1)) goto LAB_00219124;
LAB_00218dc5:
      if (tmp_i11 == 3) {
        local_74 = (uint)(*pdVar9 <= *local_60);
      }
      else if (tmp_i11 == 4) {
        __s1 = (char *)(*(int *)pdVar9 + 0x10);
        local_74 = *(size_t *)(*(int *)pdVar9 + 0xc);
        __s2 = (char *)(*(int *)local_60 + 0x10);
        tmp_s25 = *(size_t *)(*(int *)local_60 + 0xc);
        while (tmp_i11 = strcoll(__s1,__s2), tmp_i11 == 0) {
          tmp_s18 = strlen(__s1);
          if (tmp_s18 == tmp_s25) {
            local_74 = (uint)(local_74 == tmp_s25);
            goto joined_r0x00218e03;
          }
          if (tmp_s18 == local_74) {
            local_74 = 1;
            goto joined_r0x00218e03;
          }
          tmp_i11 = tmp_s18 + 1;
          local_74 = local_74 - tmp_i11;
          __s1 = __s1 + tmp_i11;
          __s2 = __s2 + tmp_i11;
          tmp_s25 = tmp_s25 - tmp_i11;
        }
        local_74 = (uint)(tmp_i11 < 1);
      }
      else {
        local_74 = call_orderTM();
        if (local_74 == 0xffffffff) {
          tmp_i11 = call_orderTM();
          if (tmp_i11 == -1) goto LAB_00219124;
          local_74 = (uint)(tmp_i11 == 0);
        }
      }
    }
joined_r0x00218e03:
    if (tmp_u27 == local_74) {
      local_68 = local_68 + ((tmp_pu19[1] >> 0xe) - 0x1ffff);
    }
    local_64 = *(int *)(param_1 + 0xc);
    local_68 = local_68 + 1;
    goto switchD_00217fed_default;
  case 0x1a:
    tmp_u27 = 1;
    if ((*(int *)(local_60 + 1) != 0) && (tmp_u27 = 0, *(int *)(local_60 + 1) == 1)) {
      tmp_u27 = (uint)(*(int *)local_60 == 0);
    }
    if (tmp_u27 != (tmp_u12 >> 0xe & 0x1ff)) {
LAB_00218d45:
      local_68 = local_68 + ((tmp_pu19[1] >> 0xe) - 0x1ffff);
    }
    goto LAB_00218d56;
  case 0x1b:
    tmp_u27 = 1;
    tmp_pi24 = (int *)(local_64 + (tmp_u12 >> 0x17) * 0xc);
    if ((tmp_pi24[2] != 0) && (tmp_u27 = 0, tmp_pi24[2] == 1)) {
      tmp_u27 = (uint)(*tmp_pi24 == 0);
    }
    if (tmp_u27 == (tmp_u12 >> 0xe & 0x1ff)) goto LAB_00218d56;
    tmp_i11 = tmp_pi24[1];
    *(int *)local_60 = *tmp_pi24;
    *(int *)((int)local_60 + 4) = tmp_i11;
    *(int *)(local_60 + 1) = tmp_pi24[2];
    local_68 = local_68 + ((tmp_pu19[1] >> 0xe) - 0x1fffe);
    goto switchD_00217fed_default;
  case 0x1c:
    tmp_i11 = (tmp_u12 >> 0xe & 0x1ff) - 1;
    if (tmp_u12 >> 0x17 != 0) {
      *(uint *)(param_1 + 8) = (int)local_60 + (tmp_u12 >> 0x17) * 0xc;
    }
    *(uint **)(param_1 + 0x18) = local_68;
    tmp_i13 = luaD_precall(param_1,local_60,tmp_i11);
    if (tmp_i13 == 0) {
      param_2 = param_2 + 1;
      tmp_i22 = *(int *)(param_1 + 0x14);
      goto LAB_00217ec6;
    }
    if (tmp_i13 != 1) {
      return;
    }
    if (tmp_i11 != -1) {
      *(uint32_t *)(param_1 + 8) = *(uint32_t *)(*(int *)(param_1 + 0x14) + 8);
    }
    break;
  case 0x1d:
    if (tmp_u12 >> 0x17 != 0) {
      *(uint *)(param_1 + 8) = (int)local_60 + (tmp_u12 >> 0x17) * 0xc;
    }
    *(uint **)(param_1 + 0x18) = local_68;
    tmp_i11 = luaD_precall(param_1,local_60,0xffffffff);
    if (tmp_i11 == 0) {
      tmp_pi24 = *(int **)(param_1 + 0x14);
      tmp_pu20 = (uint32_t *)tmp_pi24[-5];
      tmp_pu21 = (uint32_t *)tmp_pi24[1];
      tmp_pu23 = tmp_pu20;
      if (*(int *)(param_1 + 0x60) != 0) {
        luaF_close();
        tmp_pu23 = (uint32_t *)tmp_pi24[-5];
      }
      tmp_i22 = (int)tmp_pu23 + (*tmp_pi24 - (int)tmp_pu21);
      tmp_pi24[-6] = tmp_i22;
      *(int *)(param_1 + 0xc) = tmp_i22;
      if (tmp_pu21 < *(uint32_t **)(param_1 + 8)) {
        tmp_i16 = 0xc - (int)tmp_pu21;
        tmp_pu23 = tmp_pu20;
        do {
          tmp_u14 = *tmp_pu21;
          tmp_pu23[1] = tmp_pu21[1];
          *tmp_pu23 = tmp_u14;
          tmp_pu23[2] = tmp_pu21[2];
          tmp_i22 = (int)tmp_pu21 + tmp_i16;
          tmp_pu21 = tmp_pu21 + 3;
          tmp_pu23 = tmp_pu23 + 3;
        } while (tmp_pu21 < *(uint32_t **)(param_1 + 8));
      }
      else {
        tmp_i22 = 0;
      }
      *(int *)(param_1 + 8) = tmp_i22 + (int)tmp_pu20;
      tmp_pi24[-4] = tmp_i22 + (int)tmp_pu20;
      tmp_i22 = *(int *)(param_1 + 0x18);
      tmp_pi24[-1] = tmp_pi24[-1] + 1;
      tmp_pi24[-3] = tmp_i22;
      tmp_i22 = *(int *)(param_1 + 0x14) + -0x18;
      *(int *)(param_1 + 0x14) = tmp_i22;
      goto LAB_00217ec6;
    }
    if (tmp_i11 != 1) {
      return;
    }
    break;
  case 0x1e:
    goto _L315;
  case 0x1f:
    tmp_d28 = *local_60 + local_60[3];
    if (local_60[3] <= 0.0) {
      tmp_b4 = *(double *)((int)local_60 + 0xc) <= tmp_d28;
    }
    else {
      tmp_b4 = tmp_d28 <= *(double *)((int)local_60 + 0xc);
    }
    if (tmp_b4) {
      *local_60 = tmp_d28;
      *(uint32_t *)(local_60 + 1) = 3;
      *(double *)((int)local_60 + 0x24) = tmp_d28;
      *(uint32_t *)((int)local_60 + 0x2c) = 3;
      local_68 = local_68 + ((tmp_u12 >> 0xe) - 0x1ffff);
    }
    goto switchD_00217fed_default;
  case 0x20:
    *(uint **)(param_1 + 0x18) = local_68;
    if (*(int *)(local_60 + 1) == 3) {
LAB_0021940c:
      if (*(int *)((int)local_60 + 0x14) != 3) {
        if ((*(int *)((int)local_60 + 0x14) == 4) && (tmp_i11 = luaO_str2d(), tmp_i11 != 0)) {
          *(uint32_t *)((int)local_60 + 0x14) = 3;
          *(ulonglong *)((int)local_60 + 0xc) = CONCAT44(uStack_28,CONCAT22(uStack_2a,local_2c));
          if (local_60 != (double *)0xfffffff4) goto LAB_0021945b;
        }
        goto LAB_00218bf6;
      }
LAB_0021945b:
      if (*(int *)(local_60 + 4) == 3) {
        tmp_d28 = local_60[3];
      }
      else {
        if ((*(int *)(local_60 + 4) != 4) || (tmp_i11 = luaO_str2d(), tmp_i11 == 0)) {
LAB_00219474:
          luaG_runerror(param_1,"\'for\' step must be a number");
          tmp_pc5 = (void *)invalidInstructionException();
          (*tmp_pc5)();
        }
        tmp_d28 = (double)CONCAT44(uStack_28,CONCAT22(uStack_2a,local_2c));
        *(uint32_t *)(local_60 + 4) = 3;
        local_60[3] = tmp_d28;
        if (local_60 == (double *)0xffffffe8) goto LAB_00219474;
      }
    }
    else {
      if ((*(int *)(local_60 + 1) == 4) && (tmp_i11 = luaO_str2d(), tmp_i11 != 0)) {
        *(uint32_t *)(local_60 + 1) = 3;
        *local_60 = (double)CONCAT44(uStack_28,CONCAT22(uStack_2a,local_2c));
        goto LAB_0021940c;
      }
LAB_00218bf6:
      luaG_runerror();
      tmp_d28 = local_60[3];
    }
    *(uint32_t *)(local_60 + 1) = 3;
    *local_60 = *local_60 - tmp_d28;
_L545:
    local_68 = local_68 + ((tmp_u12 >> 0xe) - 0x1ffff);
    goto switchD_00217fed_default;
  case 0x21:
    *(uint32_t *)((int)local_60 + 0x3c) = *(uint32_t *)(local_60 + 3);
    *(uint32_t *)(local_60 + 8) = *(uint32_t *)((int)local_60 + 0x1c);
    *(uint32_t *)((int)local_60 + 0x44) = *(uint32_t *)(local_60 + 4);
    *(uint32_t *)((int)local_60 + 0x34) = *(uint32_t *)(local_60 + 2);
    *(uint32_t *)(local_60 + 6) = *(uint32_t *)((int)local_60 + 0xc);
    *(uint32_t *)(local_60 + 5) = *(uint32_t *)((int)local_60 + 4);
    *(uint32_t *)(local_60 + 7) = *(uint32_t *)((int)local_60 + 0x14);
    *(uint32_t *)((int)local_60 + 0x24) = *(uint32_t *)local_60;
    *(uint32_t *)((int)local_60 + 0x2c) = *(uint32_t *)(local_60 + 1);
    *(double **)(param_1 + 8) = local_60 + 9;
    *(uint **)(param_1 + 0x18) = local_68;
    luaD_call(param_1,(int)local_60 + 0x24,tmp_u12 >> 0xe & 0x1ff);
    local_64 = *(int *)(param_1 + 0xc);
    *(uint32_t *)(param_1 + 8) = *(uint32_t *)(*(int *)(param_1 + 0x14) + 8);
    tmp_pu20 = (uint32_t *)(local_64 + 0x24 + tmp_i11);
    if (tmp_pu20[2] != 0) {
      tmp_pu20[-1] = tmp_pu20[2];
      tmp_pu20[-3] = *tmp_pu20;
      tmp_pu20[-2] = tmp_pu20[1];
      goto LAB_00218d45;
    }
LAB_00218d56:
    local_68 = local_68 + 1;
    goto switchD_00217fed_default;
  case 0x22:
    tmp_u27 = tmp_u12 >> 0xe & 0x1ff;
    tmp_u12 = tmp_u12 >> 0x17;
    if (tmp_u12 == 0) {
      tmp_i11 = *(int *)(param_1 + 8);
      *(uint32_t *)(param_1 + 8) = *(uint32_t *)(*(int *)(param_1 + 0x14) + 8);
      tmp_u12 = (tmp_i11 - (int)local_60 >> 2) * -0x55555555 - 1;
    }
    if (tmp_u27 == 0) {
      tmp_u27 = tmp_pu19[1];
      local_68 = tmp_pu19 + 2;
    }
    if (*(int *)(local_60 + 1) == 5) {
      tmp_i13 = *(int *)local_60;
      tmp_i11 = tmp_u12 + (tmp_u27 * 5 + -5) * 10;
      if (*(int *)(tmp_i13 + 0x1c) < tmp_i11) {
        luaH_resizearray(param_1,tmp_i13,tmp_i11);
      }
      if (0 < (int)tmp_u12) {
        tmp_pi24 = (int *)((int)local_60 + tmp_u12 * 0xc);
        tmp_i6 = tmp_i11;
        do {
          tmp_i10 = tmp_i6 + -1;
          tmp_pi15 = (int *)luaH_setnum(param_1,tmp_i13,tmp_i6);
          tmp_i6 = *tmp_pi24;
          tmp_pi15[1] = tmp_pi24[1];
          *tmp_pi15 = tmp_i6;
          tmp_pi15[2] = tmp_pi24[2];
          if (((3 < tmp_pi24[2]) && ((*(byte *)(*tmp_pi24 + 5) & 3) != 0)) &&
             ((*(byte *)(tmp_i13 + 5) & 4) != 0)) {
            luaC_barrierback();
          }
          tmp_pi24 = tmp_pi24 + -3;
          tmp_i6 = tmp_i10;
        } while (tmp_i10 != tmp_i11 - tmp_u12);
      }
    }
    goto switchD_00217fed_default;
  case 0x23:
    luaF_close();
    goto switchD_00217fed_default;
  case 0x24:
    tmp_i11 = *(int *)(*(int *)(*(int *)(tmp_i22 + 0x10) + 0x10) + (tmp_u12 >> 0xe) * 4);
    tmp_u12 = (uint)*(byte *)(tmp_i11 + 0x48);
    tmp_i13 = luaF_newLclosure(param_1,tmp_u12,*(uint32_t *)(tmp_i22 + 0xc));
    *(int *)(tmp_i13 + 0x10) = tmp_i11;
    if (tmp_u12 != 0) {
      tmp_u27 = 0;
      do {
        while ((tmp_pu19[tmp_u27 + 1] & 0x3f) == 4) {
          *(uint32_t *)(tmp_i13 + 0x14 + tmp_u27 * 4) =
               *(uint32_t *)(tmp_i22 + 0x14 + (tmp_pu19[tmp_u27 + 1] >> 0x17) * 4);
          tmp_u27 = tmp_u27 + 1;
          if (tmp_u12 == tmp_u27) goto LAB_002189b3;
        }
        tmp_u14 = luaF_findupval();
        *(uint32_t *)(tmp_i13 + 0x14 + tmp_u27 * 4) = tmp_u14;
        tmp_u27 = tmp_u27 + 1;
      } while (tmp_u12 != tmp_u27);
LAB_002189b3:
      local_68 = local_68 + tmp_u12;
    }
    *(int *)local_60 = tmp_i13;
    *(uint32_t *)(local_60 + 1) = 6;
    *(uint **)(param_1 + 0x18) = local_68;
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      luaC_step();
    }
    local_64 = *(int *)(param_1 + 0xc);
    goto switchD_00217fed_default;
  case 0x25:
    tmp_pi24 = *(int **)(param_1 + 0x14);
    tmp_i6 = (tmp_u12 >> 0x17) - 1;
    tmp_i10 = (*tmp_pi24 - tmp_pi24[1] >> 2) * -0x55555555 -
             (uint)*(byte *)(*(int *)(tmp_i22 + 0x10) + 0x49);
    tmp_i13 = tmp_i10 + -1;
    if (tmp_i6 == -1) {
      *(uint **)(param_1 + 0x18) = local_68;
      if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) <= tmp_i13 * 0xc) {
        luaD_growstack();
      }
      local_64 = *(int *)(param_1 + 0xc);
      local_60 = (double *)(tmp_i11 + local_64);
      *(int *)(param_1 + 8) = (int)local_60 + tmp_i13 * 0xc;
      tmp_i6 = tmp_i13;
    }
    if (0 < tmp_i6) {
      tmp_i11 = 0;
      pdVar9 = local_60 + 1;
      do {
        while (tmp_i11 < tmp_i13) {
          tmp_i11 = tmp_i11 + 1;
          tmp_pu20 = (uint32_t *)((int)pdVar9 + *tmp_pi24 + (tmp_i10 * -0xc - (int)local_60) + 4);
          tmp_u14 = tmp_pu20[1];
          *(uint32_t *)(pdVar9 + -1) = *tmp_pu20;
          *(uint32_t *)((int)pdVar9 + -4) = tmp_u14;
          *(uint32_t *)pdVar9 = tmp_pu20[2];
          pdVar9 = (double *)((int)pdVar9 + 0xc);
          if (tmp_i11 == tmp_i6) goto switchD_00217fed_default;
        }
        tmp_i11 = tmp_i11 + 1;
        *(uint32_t *)pdVar9 = 0;
        pdVar9 = (double *)((int)pdVar9 + 0xc);
      } while (tmp_i11 != tmp_i6);
    }
  default:
    goto switchD_00217fed_default;
  }
  local_64 = *(int *)(param_1 + 0xc);
  goto switchD_00217fed_default;
_L315:
  if (tmp_u12 >> 0x17 != 0) {
    *(uint *)(param_1 + 8) = (tmp_u12 >> 0x17) * 0xc + -0xc + (int)local_60;
  }
  if (*(int *)(param_1 + 0x60) != 0) {
    luaF_close(param_1);
  }
  *(uint **)(param_1 + 0x18) = local_68;
  tmp_i16 = luaD_poscall();
  param_2 = param_2 + -1;
  if (param_2 == 0) {
    return;
  }
  tmp_i22 = *(int *)(param_1 + 0x14);
  if (tmp_i16 != 0) {
    *(uint32_t *)(param_1 + 8) = *(uint32_t *)(tmp_i22 + 8);
  }
  goto LAB_00217ec6;
}

void luaB_yield(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = lua_gettop(param_1);
  lua_yield(param_1,tmp_u1);
  return;
}

uint32_t luaB_corunning(uint32_t param_1)
{
  int tmp_i1;
  
  tmp_i1 = lua_pushthread(param_1);
  if (tmp_i1 != 0) {
    lua_pushnil(param_1);
  }
  return 1;
}

uint32_t luaB_cocreate(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = lua_newthread(param_1);
  tmp_i2 = lua_type(param_1,1);
  if ((tmp_i2 != 6) || (tmp_i2 = lua_iscfunction(param_1,1), tmp_i2 != 0)) {
    luaL_argerror(param_1,1,"Lua function expected");
  }
  lua_pushvalue(param_1,1);
  lua_xmove(param_1,tmp_u1,1);
  return 1;
}

uint32_t luaB_pairs(uint32_t param_1)
{
  luaL_checktype(param_1,1,5);
  lua_pushvalue(param_1,0xffffd8ed);
  lua_pushvalue(param_1,1);
  lua_pushnil(param_1);
  return 3;
}

uint32_t luaB_next(uint32_t param_1)
{
  int tmp_i1;
  
  luaL_checktype(param_1,1,5);
  lua_settop(param_1,2);
  tmp_i1 = lua_next(param_1,1);
  if (tmp_i1 != 0) {
    return 2;
  }
  lua_pushnil(param_1);
  return 1;
}

uint32_t luaB_ipairs(uint32_t param_1)
{
  luaL_checktype(param_1,1,5);
  lua_pushvalue(param_1,0xffffd8ed);
  lua_pushvalue(param_1,1);
  lua_pushinteger(param_1,0);
  return 3;
}

uint32_t luaB_rawset(uint32_t param_1)
{
  luaL_checktype(param_1,1,5);
  luaL_checkany(param_1,2);
  luaL_checkany(param_1,3);
  lua_settop(param_1,3);
  lua_rawset(param_1,1);
  return 1;
}

uint32_t luaB_rawget(uint32_t param_1)
{
  luaL_checktype(param_1,1,5);
  luaL_checkany(param_1,2);
  lua_settop(param_1,2);
  lua_rawget(param_1,1);
  return 1;
}

void luaB_pcall(uint32_t param_1)
{
  int tmp_i1;
  
  luaL_checkany(param_1,1);
  tmp_i1 = lua_gettop(param_1);
  tmp_i1 = lua_pcall(param_1,tmp_i1 + -1,0xffffffff,0);
  lua_pushboolean(param_1,tmp_i1 == 0);
  lua_insert(param_1,1);
  lua_gettop(param_1);
  return;
}

void luaB_xpcall(uint32_t param_1)
{
  int tmp_i1;
  
  luaL_checkany(param_1,2);
  lua_settop(param_1,2);
  lua_insert(param_1,1);
  tmp_i1 = lua_pcall(param_1,0,0xffffffff,1);
  lua_pushboolean(param_1,tmp_i1 == 0);
  lua_replace(param_1,1);
  lua_gettop(param_1);
  return;
}

void luaB_error(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = luaL_optinteger(param_1,2,1);
  lua_settop(param_1,1);
  tmp_i2 = lua_isstring(param_1,1);
  if ((tmp_i2 != 0) && (0 < tmp_i1)) {
    luaL_where(param_1,tmp_i1);
    lua_pushvalue(param_1,1);
    lua_concat(param_1,2);
  }
  lua_error(param_1);
  return;
}

int luaB_unpack(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  luaL_checktype(param_1,1,5);
  tmp_i1 = luaL_optinteger(param_1,2,1);
  tmp_i2 = lua_type(param_1,3);
  if (tmp_i2 < 1) {
    tmp_i2 = lua_objlen(param_1,1);
  }
  else {
    tmp_i2 = luaL_checkinteger(param_1,3);
  }
  tmp_i3 = 0;
  if (tmp_i1 <= tmp_i2) {
    tmp_i3 = (tmp_i2 - tmp_i1) + 1;
    if ((tmp_i3 < 1) || (tmp_i4 = lua_checkstack(param_1,tmp_i3), tmp_i4 == 0)) {
      tmp_i3 = luaL_error(param_1,"too many results to unpack");
    }
    else {
      lua_rawgeti(param_1,1,tmp_i1);
      if (tmp_i1 < tmp_i2) {
        tmp_i1 = tmp_i1 + 1;
        do {
          tmp_i4 = tmp_i1 + 1;
          lua_rawgeti(param_1,1,tmp_i1);
          tmp_i1 = tmp_i4;
        } while (tmp_i4 != tmp_i2 + 1);
      }
    }
  }
  return tmp_i3;
}

uint32_t luaB_type(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  luaL_checkany(param_1,1);
  tmp_u1 = lua_type(param_1,1);
  tmp_u1 = lua_typename(param_1,tmp_u1);
  lua_pushstring(param_1,tmp_u1);
  return 1;
}

int luaB_select(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  char *tmp_pc4;
  
  tmp_i1 = lua_gettop(param_1);
  tmp_i2 = lua_type(param_1,1);
  if ((tmp_i2 == 4) && (tmp_pc4 = (char *)lua_tolstring(param_1,1,0), *tmp_pc4 == '#')) {
    lua_pushinteger(param_1,tmp_i1 + -1);
    tmp_i1 = 1;
  }
  else {
    tmp_i3 = luaL_checkinteger(param_1,1);
    tmp_i2 = tmp_i1 + tmp_i3;
    if ((-1 < tmp_i3) && (tmp_i2 = tmp_i3, tmp_i1 < tmp_i3)) {
      tmp_i2 = tmp_i1;
    }
    if (tmp_i2 < 1) {
      luaL_argerror(param_1,1,"index out of range");
    }
    tmp_i1 = tmp_i1 - tmp_i2;
  }
  return tmp_i1;
}

uint32_t luaB_tonumber(uint32_t param_1)
{
  byte tmp_b1;
  int tmp_i2;
  byte *tmp_pb3;
  ulong tmp_u4;
  ushort **tmp_ppu5;
  byte *tmp_pb6;
  long double tmp_l7;
  byte *local_20 [4];
  
  tmp_i2 = luaL_optinteger(param_1,2);
  if (tmp_i2 == 10) {
    luaL_checkany(param_1,1);
    tmp_i2 = lua_isnumber(param_1,1);
    if (tmp_i2 != 0) {
      tmp_l7 = (long double)lua_tonumber(param_1,1);
      lua_pushnumber(param_1,(double)tmp_l7);
      return 1;
    }
  }
  else {
    tmp_pb3 = (byte *)luaL_checklstring(param_1,1);
    if (0x22 < tmp_i2 - 2U) {
      luaL_argerror(param_1,2);
    }
    tmp_u4 = strtoul((char *)tmp_pb3,(char **)local_20,tmp_i2);
    tmp_pb6 = local_20[0];
    if (tmp_pb3 != local_20[0]) {
      tmp_ppu5 = __ctype_b_loc();
      tmp_pb3 = local_20[0];
      do {
        local_20[0] = tmp_pb3;
        tmp_b1 = *tmp_pb6;
        tmp_pb6 = tmp_pb6 + 1;
        tmp_pb3 = tmp_pb6;
      } while ((*(byte *)((int)*tmp_ppu5 + (uint)tmp_b1 * 2 + 1) & 0x20) != 0);
      if (tmp_b1 == 0) {
        lua_pushnumber(param_1,(double)tmp_u4);
        return 1;
      }
    }
  }
  lua_pushnil(param_1);
  return 1;
}

uint32_t luaB_setmetatable(uint32_t param_1)
{
  int tmp_i1;
  
  tmp_i1 = lua_type(param_1,2);
  luaL_checktype(param_1,1,5);
  if ((tmp_i1 != 5) && (tmp_i1 != 0)) {
    luaL_argerror(param_1,2,"nil or table expected");
  }
  tmp_i1 = luaL_getmetafield(param_1,1,"__metatable");
  if (tmp_i1 != 0) {
    luaL_error(param_1,"cannot change a protected metatable");
  }
  lua_settop(param_1,2);
  lua_setmetatable(param_1,1);
  return 1;
}

uint32_t luaB_rawequal(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  luaL_checkany(param_1,1);
  luaL_checkany(param_1,2);
  tmp_u1 = lua_rawequal(param_1,1,2);
  lua_pushboolean(param_1,tmp_u1);
  return 1;
}

uint32_t luaB_print(uint32_t param_1)
{
  int tmp_i1;
  char *__s;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_i3 = 1;
  tmp_i1 = lua_gettop(param_1);
  lua_getfield(param_1,0xffffd8ee,"tostring");
  if (0 < tmp_i1) {
    do {
      lua_pushvalue(param_1,0xffffffff);
      lua_pushvalue(param_1,tmp_i3);
      lua_call(param_1,1,1);
      __s = (char *)lua_tolstring(param_1,0xffffffff,0);
      if (__s == (char *)0x0) {
        tmp_u2 = luaL_error(param_1,"\'tostring\' must return a string to \'print\'");
        return tmp_u2;
      }
      if (tmp_i3 != 1) {
        fputc(9,_stdout);
      }
      tmp_i3 = tmp_i3 + 1;
      fputs(__s,_stdout);
      lua_settop(param_1,0xfffffffe);
    } while (tmp_i3 <= tmp_i1);
  }
  fputc(10,_stdout);
  return 0;
}

int luaB_dofile(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_u1 = luaL_optlstring(param_1,1,0,0);
  tmp_i2 = lua_gettop(param_1);
  tmp_i3 = luaL_loadfile(param_1,tmp_u1);
  if (tmp_i3 != 0) {
    lua_error(param_1);
  }
  lua_call(param_1,0,0xffffffff);
  tmp_i3 = lua_gettop(param_1);
  return tmp_i3 - tmp_i2;
}

uint32_t luaB_gcinfo(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = lua_gc(param_1,3,0);
  lua_pushinteger(param_1,tmp_u1);
  return 1;
}

uint32_t luaB_collectgarbage(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_i1 = luaL_checkoption(param_1,1,"collect",opts_3381);
  tmp_u2 = luaL_optinteger(param_1,2,0);
  tmp_i1 = *(int *)(optsnum_3382 + tmp_i1 * 4);
  tmp_i3 = lua_gc(param_1,tmp_i1,tmp_u2);
  if (tmp_i1 == 3) {
    tmp_i1 = lua_gc(param_1,4,0);
    lua_pushnumber(param_1,(double)((float)tmp_i1 * 0.0009765625 + (float)tmp_i3));
  }
  else if (tmp_i1 == 5) {
    lua_pushboolean(param_1,tmp_i3);
  }
  else {
    lua_pushnumber(param_1,(double)tmp_i3);
  }
  return 1;
}

uint32_t luaB_load(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = luaL_optlstring(param_1,2,"=(load)",0);
  luaL_checktype(param_1,1,6);
  lua_settop(param_1,3);
  tmp_i2 = lua_load(param_1,generic_reader,0,tmp_u1);
  tmp_u1 = 1;
  if (tmp_i2 != 0) {
    lua_pushnil(param_1);
    lua_insert(param_1,0xfffffffe);
    tmp_u1 = 2;
  }
  return tmp_u1;
}

uint32_t luaB_newproxy(uint32_t param_1)
{
  int tmp_i1;
  
  lua_settop(param_1,1);
  lua_newuserdata(param_1,0);
  tmp_i1 = lua_toboolean(param_1,1);
  if (tmp_i1 == 0) {
    return 1;
  }
  tmp_i1 = lua_type(param_1,1);
  if (tmp_i1 == 1) {
    lua_createtable(param_1,0,0);
    lua_pushvalue(param_1,0xffffffff);
    lua_pushboolean(param_1,1);
    lua_rawset(param_1,0xffffd8ed);
    goto LAB_0021aa69;
  }
  tmp_i1 = lua_getmetatable(param_1,1);
  if (tmp_i1 == 0) {
LAB_0021aa3d:
    luaL_argerror(param_1,1,"boolean or proxy expected");
  }
  else {
    lua_rawget(param_1,0xffffd8ed);
    tmp_i1 = lua_toboolean(param_1,0xffffffff);
    lua_settop(param_1,0xfffffffe);
    if (tmp_i1 == 0) goto LAB_0021aa3d;
  }
  lua_getmetatable(param_1,1);
LAB_0021aa69:
  lua_setmetatable(param_1,2);
  return 1;
}

uint32_t luaB_tostring(uint32_t param_1)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  
  luaL_checkany(param_1,1);
  tmp_i1 = luaL_callmeta(param_1,1,"__tostring");
  if (tmp_i1 == 0) {
    tmp_i1 = lua_type(param_1,1);
    if (tmp_i1 == 1) {
      tmp_i1 = lua_toboolean(param_1,1);
      if (tmp_i1 == 0) {
        tmp_pc2 = "false";
      }
      else {
        tmp_pc2 = "true";
      }
      lua_pushstring(param_1,tmp_pc2);
    }
    else {
      if (tmp_i1 < 2) {
        if (tmp_i1 == 0) {
          lua_pushlstring(param_1,"nil",3);
          return 1;
        }
      }
      else {
        if (tmp_i1 == 3) {
          tmp_u3 = lua_tolstring(param_1,1,0);
          lua_pushstring(param_1,tmp_u3);
          return 1;
        }
        if (tmp_i1 == 4) {
          lua_pushvalue(param_1,1);
          return 1;
        }
      }
      tmp_u3 = lua_topointer(param_1,1);
      tmp_u4 = lua_type(param_1,1);
      tmp_u4 = lua_typename(param_1,tmp_u4);
      lua_pushfstring(param_1,"%s: %p",tmp_u4,tmp_u3);
    }
  }
  return 1;
}

uint32_t luaB_getmetatable(uint32_t param_1)
{
  int tmp_i1;
  
  luaL_checkany(param_1,1);
  tmp_i1 = lua_getmetatable(param_1,1);
  if (tmp_i1 == 0) {
    lua_pushnil(param_1);
  }
  else {
    luaL_getmetafield(param_1,1,"__metatable");
  }
  return 1;
}

void luaB_assert(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  luaL_checkany(param_1,1);
  tmp_i1 = lua_toboolean(param_1,1);
  if (tmp_i1 != 0) {
    lua_gettop(param_1);
    return;
  }
  tmp_u2 = luaL_optlstring(param_1,2,"assertion failed!",0);
  luaL_error(param_1,&g_unk_0024e6e9,tmp_u2);
  return;
}

uint32_t luaB_loadfile(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = luaL_optlstring(param_1,1,0,0);
  tmp_i2 = luaL_loadfile(param_1,tmp_u1);
  tmp_u1 = 1;
  if (tmp_i2 != 0) {
    lua_pushnil(param_1);
    lua_insert(param_1,0xfffffffe);
    tmp_u1 = 2;
  }
  return tmp_u1;
}

uint32_t luaB_loadstring(uint32_t param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t local_10;
  
  tmp_u1 = luaL_checklstring(param_1,1,&local_10);
  tmp_u2 = luaL_optlstring(param_1,2,tmp_u1,0);
  tmp_i3 = luaL_loadbuffer(param_1,tmp_u1,local_10,tmp_u2);
  tmp_u1 = 1;
  if (tmp_i3 != 0) {
    lua_pushnil(param_1);
    lua_insert(param_1,0xfffffffe);
    tmp_u1 = 2;
  }
  return tmp_u1;
}

uint32_t luaB_costatus(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint8_t local_70 [100];
  
  tmp_i1 = lua_tothread(param_1,1);
  if (tmp_i1 == 0) {
    luaL_argerror(param_1,1,"coroutine expected");
  }
  if (param_1 == tmp_i1) {
    tmp_i3 = 0;
  }
  else {
    tmp_i2 = lua_status(tmp_i1);
    if (tmp_i2 == 0) {
      tmp_i2 = lua_getstack(tmp_i1,0,local_70);
      tmp_i3 = 2;
      if (tmp_i2 < 1) {
        tmp_i1 = lua_gettop(tmp_i1);
        tmp_i3 = (-(uint)(tmp_i1 == 0) & 2) + 1;
      }
    }
    else {
      tmp_i3 = 1;
      if (tmp_i2 != 1) {
        tmp_i3 = 3;
      }
    }
  }
  lua_pushstring(param_1,(&statnames)[tmp_i3]);
  return 1;
}

int luaB_auxwrap(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  lua_tothread(param_1,0xffffd8ed);
  tmp_u1 = lua_gettop(param_1);
  tmp_i2 = auxresume(tmp_u1);
  if (tmp_i2 < 0) {
    tmp_i3 = lua_isstring(param_1,0xffffffff);
    if (tmp_i3 != 0) {
      luaL_where(param_1,1);
      lua_insert(param_1,0xfffffffe);
      lua_concat(param_1,2);
    }
    lua_error(param_1);
  }
  return tmp_i2;
}

int luaB_coresume(uint32_t param_1)
{
  int tmp_i1;
  uint tmp_u2;
  
  tmp_i1 = lua_tothread(param_1,1);
  if (tmp_i1 == 0) {
    luaL_argerror(param_1,1,"coroutine expected");
  }
  tmp_i1 = lua_gettop(param_1);
  tmp_u2 = auxresume(tmp_i1 + -1);
  if (-1 < (int)tmp_u2) {
    lua_pushboolean(param_1,1);
    lua_insert(param_1,~tmp_u2);
    return tmp_u2 + 1;
  }
  lua_pushboolean(param_1,0);
  lua_insert(param_1,0xfffffffe);
  return 2;
}

uint32_t luaB_cowrap(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = lua_newthread(param_1);
  tmp_i2 = lua_type(param_1,1);
  if ((tmp_i2 != 6) || (tmp_i2 = lua_iscfunction(param_1,1), tmp_i2 != 0)) {
    luaL_argerror(param_1,1,"Lua function expected");
  }
  lua_pushvalue(param_1,1);
  lua_xmove(param_1,tmp_u1,1);
  lua_pushcclosure(param_1,luaB_auxwrap,1);
  return 1;
}

uint32_t luaB_getfenv(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint8_t local_80 [112];
  
  tmp_i1 = lua_type(param_1,1);
  if (tmp_i1 == 6) {
    lua_pushvalue(param_1,1);
  }
  else {
    tmp_i1 = luaL_optinteger(param_1,1,1);
    if (tmp_i1 < 0) {
      luaL_argerror(param_1,1,"level must be non-negative");
    }
    tmp_i2 = lua_getstack(param_1,tmp_i1,local_80);
    if (tmp_i2 == 0) {
      luaL_argerror(param_1,1,"invalid level");
    }
    lua_getinfo(param_1,"f",local_80);
    tmp_i2 = lua_type(param_1,0xffffffff);
    if (tmp_i2 == 0) {
      luaL_error(param_1,"no function environment for tail call at level %d",tmp_i1);
    }
  }
  tmp_i1 = lua_iscfunction(param_1,0xffffffff);
  if (tmp_i1 == 0) {
    lua_getfenv(param_1,0xffffffff);
  }
  else {
    lua_pushvalue(param_1,0xffffd8ee);
  }
  return 1;
}

uint32_t luaB_setfenv(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  long double tmp_l3;
  uint8_t local_80 [112];
  
  luaL_checktype(param_1,2,5);
  tmp_i1 = lua_type(param_1,1);
  if (tmp_i1 == 6) {
    lua_pushvalue(param_1,1);
  }
  else {
    tmp_i1 = luaL_checkinteger();
    if (tmp_i1 < 0) {
      luaL_argerror(param_1,1,"level must be non-negative");
    }
    tmp_i2 = lua_getstack(param_1,tmp_i1,local_80);
    if (tmp_i2 == 0) {
      luaL_argerror(param_1,1,"invalid level");
    }
    lua_getinfo(param_1,"f",local_80);
    tmp_i2 = lua_type(param_1,0xffffffff);
    if (tmp_i2 == 0) {
      luaL_error(param_1,"no function environment for tail call at level %d",tmp_i1);
    }
  }
  lua_pushvalue(param_1,2);
  tmp_i1 = lua_isnumber(param_1,1);
  if ((tmp_i1 != 0) && (tmp_l3 = (long double)lua_tonumber(param_1,1), tmp_l3 == (long double)0)) {
    lua_pushthread(param_1);
    lua_insert(param_1,0xfffffffe);
    lua_setfenv(param_1,0xfffffffe);
    return 0;
  }
  tmp_i1 = lua_iscfunction(param_1,0xfffffffe);
  if ((tmp_i1 == 0) && (tmp_i1 = lua_setfenv(param_1,0xfffffffe), tmp_i1 != 0)) {
    return 1;
  }
  luaL_error(param_1,"\'setfenv\' cannot change environment of given object");
  return 1;
}

uint32_t luaopen_base(uint32_t param_1)
{
  lua_pushvalue(param_1,0xffffd8ee);
  lua_setfield(param_1,0xffffd8ee,&g_unk_0026f319);
  luaL_register(param_1,&g_unk_0026f319,base_funcs);
  lua_pushlstring(param_1,"Lua 5.1",7);
  lua_setfield(param_1,0xffffd8ee,"_VERSION");
  lua_pushcclosure(param_1,ipairsaux,0);
  lua_pushcclosure(param_1,luaB_ipairs,1);
  lua_setfield(param_1,0xfffffffe,"ipairs");
  lua_pushcclosure(param_1,luaB_next,0);
  lua_pushcclosure(param_1,luaB_pairs,1);
  lua_setfield(param_1,0xfffffffe,"pairs");
  lua_createtable(param_1,0,1);
  lua_pushvalue(param_1,0xffffffff);
  lua_setmetatable(param_1,0xfffffffe);
  lua_pushlstring(param_1,&g_unk_0026f32b,2);
  lua_setfield(param_1,0xfffffffe,"__mode");
  lua_pushcclosure(param_1,luaB_newproxy,1);
  lua_setfield(param_1,0xffffd8ee,"newproxy");
  luaL_register(param_1,"coroutine",co_funcs);
  return 2;
}

void luaX_init(uint32_t param_1)
{
  char *__s;
  size_t tmp_s1;
  int tmp_i2;
  char tmp_c3;
  uint8_t **tmp_ppu4;
  
  tmp_c3 = '\x01';
  tmp_ppu4 = &luaX_tokens;
  do {
    __s = *tmp_ppu4;
    tmp_ppu4 = tmp_ppu4 + 1;
    tmp_s1 = strlen(__s);
    tmp_i2 = luaS_newlstr(param_1,__s,tmp_s1);
    *(char *)(tmp_i2 + 6) = tmp_c3;
    tmp_c3 = tmp_c3 + '\x01';
    *(byte *)(tmp_i2 + 5) = *(byte *)(tmp_i2 + 5) | 0x20;
  } while (tmp_c3 != '\x16');
  return;
}

uint32_t luaX_token2str(int param_1,int param_2)
{
  ushort **tmp_ppu1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  if (param_2 < 0x101) {
    tmp_ppu1 = __ctype_b_loc();
    if (((*tmp_ppu1)[param_2] & 2) == 0) {
      tmp_pc2 = "%c";
    }
    else {
      tmp_pc2 = "char(%d)";
    }
    tmp_u3 = luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),tmp_pc2,param_2);
    return tmp_u3;
  }
  return *(uint32_t *)(nolockIoMethods + param_2 * 4 + 0x3c);
}

void luaX_lexerror(int param_1,uint32_t param_2,int param_3)
{
  uint32_t tmp_u1;
  ushort **tmp_ppu2;
  uint32_t tmp_u3;
  uint8_t local_6c [92];
  
  luaO_chunkid(local_6c,*(int *)(param_1 + 0x34) + 0x10,0x50);
  tmp_u3 = *(uint32_t *)(param_1 + 4);
  tmp_u1 = luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),"%s:%d: %s",local_6c,tmp_u3,param_2);
  if (param_3 != 0) {
    if (param_3 - 0x11cU < 3) {
      save();
      tmp_u3 = **(uint32_t **)(param_1 + 0x30);
    }
    else if (param_3 < 0x101) {
      tmp_ppu2 = __ctype_b_loc();
      if (((*tmp_ppu2)[param_3] & 2) == 0) {
        tmp_u3 = luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),"%c",param_3,tmp_u3,param_2);
      }
      else {
        tmp_u3 = luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),"char(%d)",param_3,tmp_u3,param_2);
      }
    }
    else {
      tmp_u3 = *(uint32_t *)(nolockIoMethods + param_3 * 4 + 0x3c);
    }
    luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),"%s near \'%s\'",tmp_u1,tmp_u3,param_2);
  }
  luaD_throw(*(uint32_t *)(param_1 + 0x28),3);
}

void luaX_syntaxerror(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  ushort **tmp_ppu3;
  uint32_t tmp_u4;
  uint8_t local_6c [92];
  
  tmp_i1 = *(int *)(param_1 + 0xc);
  luaO_chunkid(local_6c,*(int *)(param_1 + 0x34) + 0x10,0x50);
  tmp_u4 = *(uint32_t *)(param_1 + 4);
  tmp_u2 = luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),"%s:%d: %s",local_6c,tmp_u4,param_2);
  if (tmp_i1 != 0) {
    if (tmp_i1 - 0x11cU < 3) {
      save();
      tmp_u4 = **(uint32_t **)(param_1 + 0x30);
    }
    else if (tmp_i1 < 0x101) {
      tmp_ppu3 = __ctype_b_loc();
      if (((*tmp_ppu3)[tmp_i1] & 2) == 0) {
        tmp_u4 = luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),"%c",tmp_i1,tmp_u4,param_2);
      }
      else {
        tmp_u4 = luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),"char(%d)",tmp_i1,tmp_u4,param_2);
      }
    }
    else {
      tmp_u4 = *(uint32_t *)(nolockIoMethods + tmp_i1 * 4 + 0x3c);
    }
    luaO_pushfstring(*(uint32_t *)(param_1 + 0x28),"%s near \'%s\'",tmp_u2,tmp_u4,param_2);
  }
  luaD_throw(*(uint32_t *)(param_1 + 0x28),3);
}

uint32_t luaX_newstring(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  
  tmp_u1 = *(uint32_t *)(param_1 + 0x28);
  tmp_u2 = luaS_newlstr(tmp_u1,param_2,param_3);
  tmp_pu3 = (uint32_t *)luaH_setstr(tmp_u1,*(uint32_t *)(*(int *)(param_1 + 0x24) + 4),tmp_u2);
  if (tmp_pu3[2] == 0) {
    *tmp_pu3 = 1;
    tmp_pu3[2] = 1;
  }
  return tmp_u2;
}

void luaX_setinput(uint param_1,uint *param_2,uint param_3,uint param_4)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  byte *tmp_pb3;
  uint32_t tmp_u4;
  uint tmp_u5;
  
  tmp_pu1 = (uint32_t *)param_2[0xc];
  param_2[0xb] = param_3;
  *(uint8_t *)(param_2 + 0xe) = 0x2e;
  param_2[10] = param_1;
  param_2[6] = 0x11f;
  param_2[0xd] = param_4;
  param_2[9] = 0;
  param_2[1] = 1;
  param_2[2] = 1;
  tmp_u4 = luaM_realloc_(param_1,*tmp_pu1,tmp_pu1[2],0x20);
  *tmp_pu1 = tmp_u4;
  *(uint32_t *)(param_2[0xc] + 8) = 0x20;
  tmp_i2 = *(int *)param_2[0xb];
  *(int *)param_2[0xb] = tmp_i2 + -1;
  if (tmp_i2 != 0) {
    tmp_pb3 = *(byte **)(param_2[0xb] + 4);
    *(byte **)(param_2[0xb] + 4) = tmp_pb3 + 1;
    *param_2 = (uint)*tmp_pb3;
    return;
  }
  tmp_u5 = luaZ_fill(param_2[0xb]);
  *param_2 = tmp_u5;
  return;
}

void luaX_next(int param_1)
{
  uint32_t tmp_u1;
  
  *(uint32_t *)(param_1 + 8) = *(uint32_t *)(param_1 + 4);
  if (*(int *)(param_1 + 0x18) != 0x11f) {
    tmp_u1 = *(uint32_t *)(param_1 + 0x18);
    *(uint32_t *)(param_1 + 0x18) = 0x11f;
    *(uint32_t *)(param_1 + 0xc) = tmp_u1;
    *(uint32_t *)(param_1 + 0x10) = *(uint32_t *)(param_1 + 0x1c);
    *(uint32_t *)(param_1 + 0x14) = *(uint32_t *)(param_1 + 0x20);
    return;
  }
  tmp_u1 = llex();
  *(uint32_t *)(param_1 + 0xc) = tmp_u1;
  return;
}

void luaX_lookahead(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = llex();
  *(uint32_t *)(param_1 + 0x18) = tmp_u1;
  return;
}

uint32_t luaopen_debug(uint32_t param_1)
{
  luaL_register(param_1,"debug",dblib);
  return 1;
}

int luaY_parser(uint32_t param_1,uint32_t param_2,uint32_t param_3,char *param_4)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  size_t tmp_s3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint8_t local_294 [12];
  int local_288;
  int *local_270;
  int local_26c;
  uint32_t local_264;
  uint32_t local_260;
  int local_258;
  uint32_t local_254;
  uint32_t local_250;
  uint8_t *local_24c;
  int local_248;
  uint32_t local_244;
  uint32_t local_240;
  uint32_t local_23c;
  uint32_t local_238;
  uint32_t local_234;
  uint32_t local_230;
  uint32_t local_22c;
  uint16_t local_228;
  uint8_t local_226;
  
  local_264 = param_3;
  tmp_s3 = strlen(param_4);
  tmp_u4 = luaS_newlstr(param_1,param_4,tmp_s3);
  luaX_setinput(param_1,local_294,param_2,tmp_u4);
  tmp_i2 = local_26c;
  tmp_i5 = luaF_newproto(local_26c);
  local_228 = 0;
  local_226 = 0;
  local_248 = tmp_i2;
  *(uint8_t *)(tmp_i5 + 0x4b) = 2;
  local_250 = local_270;
  local_270 = &local_258;
  local_240 = 0;
  local_23c = 0xffffffff;
  local_238 = 0xffffffff;
  local_234 = 0;
  local_230 = 0;
  local_22c = 0;
  local_244 = 0;
  *(uint32_t *)(tmp_i5 + 0x20) = local_260;
  local_258 = tmp_i5;
  local_24c = local_294;
  local_254 = luaH_new(tmp_i2,0,0);
  tmp_pu1 = *(uint32_t **)(tmp_i2 + 8);
  tmp_pu1[2] = 5;
  *tmp_pu1 = local_254;
  tmp_i6 = *(int *)(tmp_i2 + 8);
  if (*(int *)(tmp_i2 + 0x1c) - tmp_i6 < 0xd) {
    luaD_growstack(tmp_i2,1);
    tmp_i6 = *(int *)(tmp_i2 + 8);
  }
  *(int *)(tmp_i2 + 8) = tmp_i6 + 0xc;
  *(int *)(tmp_i6 + 0xc) = tmp_i5;
  *(uint32_t *)(tmp_i6 + 0x14) = 9;
  tmp_i6 = *(int *)(tmp_i2 + 8);
  if (*(int *)(tmp_i2 + 0x1c) - tmp_i6 < 0xd) {
    luaD_growstack(tmp_i2,1);
    tmp_i6 = *(int *)(tmp_i2 + 8);
  }
  *(int *)(tmp_i2 + 8) = tmp_i6 + 0xc;
  *(uint8_t *)(local_258 + 0x4a) = 2;
  luaX_next(local_294);
  chunk();
  if (local_288 != 0x11f) {
    tmp_u4 = luaX_token2str(local_294,0x11f);
    tmp_u4 = luaO_pushfstring(local_26c,"\'%s\' expected",tmp_u4);
    luaX_syntaxerror(local_294,tmp_u4);
  }
  close_func();
  return local_258;
}

uint32_t luaopen_table(uint32_t param_1)
{
  luaL_register(param_1,"table",tab_funcs);
  return 1;
}

void luaL_where(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  uint8_t local_70 [20];
  int local_5c;
  uint8_t local_4c [64];
  
  tmp_i1 = lua_getstack(param_1,param_2,local_70);
  if ((tmp_i1 != 0) && (lua_getinfo(param_1,&g_unk_0026fb46,local_70), 0 < local_5c)) {
    lua_pushfstring(param_1,"%s:%d: ",local_4c,local_5c);
    return;
  }
  lua_pushlstring(param_1,&g_unk_0026ea14,0);
  return;
}

void luaL_error(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  uint8_t local_80 [20];
  int local_6c;
  uint8_t local_5c [76];
  
  tmp_i1 = lua_getstack(param_1,1,local_80);
  if (tmp_i1 != 0) {
    lua_getinfo(param_1,&g_unk_0026fb46,local_80);
    if (0 < local_6c) {
      lua_pushfstring(param_1,"%s:%d: ",local_5c,local_6c);
      goto LAB_00224ede;
    }
  }
  lua_pushlstring(param_1,&g_unk_0026ea14,0);
LAB_00224ede:
  lua_pushvfstring(param_1,param_2,&stack0x0000000c);
  lua_concat(param_1,2);
  lua_error(param_1);
  return;
}

void luaL_argerror(uint32_t param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  uint8_t tmp_u3;
  byte tmp_b4;
  uint8_t local_80 [4];
  uint8_t *local_7c;
  char *local_78;
  
  tmp_b4 = 0;
  tmp_i1 = lua_getstack(param_1,0,local_80);
  tmp_u3 = tmp_i1 == 0;
  if ((bool)tmp_u3) {
    luaL_error(param_1,"bad argument #%d (%s)",param_2,param_3);
  }
  else {
    lua_getinfo(param_1,&g_unk_0023bf57,local_80);
    tmp_i1 = 7;
    tmp_pc2 = "method";
    do {
      if (tmp_i1 == 0) break;
      tmp_i1 = tmp_i1 + -1;
      tmp_u3 = *local_78 == *tmp_pc2;
      local_78 = local_78 + (uint)tmp_b4 * -2 + 1;
      tmp_pc2 = tmp_pc2 + (uint)tmp_b4 * -2 + 1;
    } while ((bool)tmp_u3);
    if (((bool)tmp_u3) && (param_2 = param_2 + -1, param_2 == 0)) {
      luaL_error(param_1,"calling \'%s\' on bad self (%s)",local_7c,param_3);
      return;
    }
    if (local_7c == (uint8_t *)0x0) {
      local_7c = &g_unk_0026f751;
    }
    luaL_error(param_1,"bad argument #%d to \'%s\' (%s)",param_2,local_7c,param_3);
  }
  return;
}

void luaL_typerror(uint32_t param_1,int param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  uint8_t tmp_u4;
  byte tmp_b5;
  uint8_t local_80 [4];
  uint8_t *local_7c;
  char *local_78;
  
  tmp_b5 = 0;
  tmp_u1 = lua_type(param_1,param_2);
  tmp_u1 = lua_typename(param_1,tmp_u1);
  tmp_u1 = lua_pushfstring(param_1,"%s expected, got %s",param_3,tmp_u1);
  tmp_i2 = lua_getstack(param_1,0,local_80);
  tmp_u4 = tmp_i2 == 0;
  if ((bool)tmp_u4) {
    luaL_error(param_1,"bad argument #%d (%s)",param_2,tmp_u1);
  }
  else {
    lua_getinfo(param_1,&g_unk_0023bf57,local_80);
    tmp_i2 = 7;
    tmp_pc3 = "method";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u4 = *local_78 == *tmp_pc3;
      local_78 = local_78 + (uint)tmp_b5 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b5 * -2 + 1;
    } while ((bool)tmp_u4);
    if (((bool)tmp_u4) && (param_2 = param_2 + -1, param_2 == 0)) {
      luaL_error(param_1,"calling \'%s\' on bad self (%s)",local_7c,tmp_u1);
      return;
    }
    if (local_7c == (uint8_t *)0x0) {
      local_7c = &g_unk_0026f751;
    }
    luaL_error(param_1,"bad argument #%d to \'%s\' (%s)",param_2,local_7c,tmp_u1);
  }
  return;
}

int luaL_checkoption(uint32_t param_1,uint32_t param_2,char *param_3,int *param_4)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  char *__s1;
  
  if (param_3 == (char *)0x0) {
    param_3 = (char *)lua_tolstring(param_1,param_2,0);
    if (param_3 == (char *)0x0) {
      tmp_u4 = lua_typename(param_1,4);
      tmp_u3 = lua_type(param_1,param_2);
      tmp_u3 = lua_typename(param_1,tmp_u3);
      tmp_u4 = lua_pushfstring(param_1,"%s expected, got %s",tmp_u4,tmp_u3);
      luaL_argerror(param_1,param_2,tmp_u4);
    }
  }
  else {
    tmp_i1 = lua_type(param_1,param_2);
    if (0 < tmp_i1) {
      param_3 = (char *)lua_tolstring(param_1,param_2,0);
      if (param_3 == (char *)0x0) {
        tmp_u4 = lua_typename(param_1,4);
        luaL_typerror(param_1,param_2,tmp_u4);
      }
    }
  }
  __s1 = (char *)*param_4;
  if (__s1 != (char *)0x0) {
    tmp_i1 = 0;
    do {
      tmp_i2 = strcmp(__s1,param_3);
      if (tmp_i2 == 0) {
        return tmp_i1;
      }
      tmp_i1 = tmp_i1 + 1;
      __s1 = (char *)param_4[tmp_i1];
    } while (__s1 != (char *)0x0);
  }
  lua_pushfstring(param_1,"invalid option \'%s\'",param_3);
  tmp_i1 = luaL_argerror();
  return tmp_i1;
}

bool luaL_newmetatable(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  
  lua_getfield(param_1,0xffffd8f0,param_2);
  tmp_i1 = lua_type(param_1,0xffffffff);
  if (tmp_i1 == 0) {
    lua_settop(param_1,0xfffffffe);
    lua_createtable(param_1,0,0);
    lua_pushvalue(param_1,0xffffffff);
    lua_setfield(param_1,0xffffd8f0,param_2);
  }
  return tmp_i1 == 0;
}

int luaL_checkudata(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  tmp_i1 = lua_touserdata(param_1,param_2);
  if ((tmp_i1 != 0) && (tmp_i2 = lua_getmetatable(param_1,param_2), tmp_i2 != 0)) {
    lua_getfield(param_1,0xffffd8f0,param_3);
    tmp_i2 = lua_rawequal(param_1,0xffffffff,0xfffffffe);
    if (tmp_i2 != 0) {
      lua_settop(param_1,0xfffffffd);
      return tmp_i1;
    }
  }
  tmp_u3 = lua_type(param_1,param_2);
  tmp_u3 = lua_typename(param_1,tmp_u3);
  tmp_u3 = lua_pushfstring(param_1,"%s expected, got %s",param_3,tmp_u3);
  luaL_argerror(param_1,param_2,tmp_u3);
  return 0;
}

void luaL_checkstack(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = lua_checkstack(param_1,param_2);
  if (tmp_i1 != 0) {
    return;
  }
  luaL_error();
  return;
}

void luaL_checktype(uint32_t param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint8_t tmp_u5;
  byte tmp_b6;
  uint8_t local_80 [4];
  uint8_t *local_7c;
  char *local_78;
  
  tmp_b6 = 0;
  tmp_i1 = lua_type(param_1,param_2);
  if (tmp_i1 != param_3) {
    tmp_u2 = lua_typename(param_1,param_3);
    tmp_u3 = lua_type(param_1,param_2);
    tmp_u3 = lua_typename(param_1,tmp_u3);
    tmp_u2 = lua_pushfstring(param_1,"%s expected, got %s",tmp_u2,tmp_u3);
    tmp_i1 = lua_getstack(param_1,0,local_80);
    tmp_u5 = tmp_i1 == 0;
    if ((bool)tmp_u5) {
      luaL_error(param_1,"bad argument #%d (%s)",param_2,tmp_u2);
    }
    else {
      lua_getinfo(param_1,&g_unk_0023bf57,local_80);
      tmp_i1 = 7;
      tmp_pc4 = "method";
      do {
        if (tmp_i1 == 0) break;
        tmp_i1 = tmp_i1 + -1;
        tmp_u5 = *local_78 == *tmp_pc4;
        local_78 = local_78 + (uint)tmp_b6 * -2 + 1;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
      } while ((bool)tmp_u5);
      if (((bool)tmp_u5) && (param_2 = param_2 + -1, param_2 == 0)) {
        luaL_error(param_1,"calling \'%s\' on bad self (%s)",local_7c,tmp_u2);
        return;
      }
      if (local_7c == (uint8_t *)0x0) {
        local_7c = &g_unk_0026f751;
      }
      luaL_error(param_1,"bad argument #%d to \'%s\' (%s)",param_2,local_7c,tmp_u2);
    }
  }
  return;
}

void luaL_checkany(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = lua_type(param_1,param_2);
  if (tmp_i1 != -1) {
    return;
  }
  luaL_argerror(param_1,param_2,"value expected");
  return;
}

int luaL_checklstring(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  
  tmp_i1 = lua_tolstring(param_1,param_2,param_3);
  if (tmp_i1 == 0) {
    tmp_u2 = lua_typename(param_1,4);
    tmp_u3 = lua_type(param_1,param_2);
    tmp_u3 = lua_typename(param_1,tmp_u3);
    tmp_u2 = lua_pushfstring(param_1,"%s expected, got %s",tmp_u2,tmp_u3);
    luaL_argerror(param_1,param_2,tmp_u2);
  }
  return tmp_i1;
}

char * luaL_optlstring(uint32_t param_1,uint32_t param_2,char *param_3,size_t *param_4)
{
  int tmp_i1;
  size_t tmp_s2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  
  tmp_i1 = lua_type(param_1,param_2);
  if (tmp_i1 < 1) {
    if (param_4 != (size_t *)0x0) {
      if (param_3 == (char *)0x0) {
        tmp_s2 = 0;
      }
      else {
        tmp_s2 = strlen(param_3);
      }
      *param_4 = tmp_s2;
    }
  }
  else {
    param_3 = (char *)lua_tolstring(param_1,param_2,param_4);
    if (param_3 == (char *)0x0) {
      tmp_u3 = lua_typename(param_1,4);
      tmp_u4 = lua_type(param_1,param_2);
      tmp_u4 = lua_typename(param_1,tmp_u4);
      tmp_u3 = lua_pushfstring(param_1,"%s expected, got %s",tmp_u3,tmp_u4);
      luaL_argerror(param_1,param_2,tmp_u3);
    }
  }
  return param_3;
}

long double luaL_checknumber(uint32_t param_1,uint32_t param_2)
{
  double tmp_d1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  long double tmp_l5;
  
  tmp_l5 = (long double)lua_tonumber(param_1,param_2);
  if (tmp_l5 == (long double)0) {
    tmp_d1 = (double)tmp_l5;
    tmp_i2 = lua_isnumber(param_1,param_2);
    tmp_l5 = (long double)tmp_d1;
    if (tmp_i2 == 0) {
      tmp_u3 = lua_typename(param_1,3);
      tmp_u4 = lua_type(param_1,param_2);
      tmp_u4 = lua_typename(param_1,tmp_u4);
      tmp_u3 = lua_pushfstring(param_1,"%s expected, got %s",tmp_u3,tmp_u4);
      luaL_argerror(param_1,param_2,tmp_u3);
      tmp_l5 = (long double)tmp_d1;
    }
  }
  return tmp_l5;
}

long double luaL_optnumber(uint32_t param_1,uint32_t param_2,double param_3)
{
  double tmp_d1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  long double tmp_l5;
  
  tmp_i2 = lua_type(param_1,param_2);
  if (tmp_i2 < 1) {
    tmp_l5 = (long double)param_3;
  }
  else {
    tmp_l5 = (long double)lua_tonumber(param_1,param_2);
    if (tmp_l5 == (long double)0) {
      tmp_d1 = (double)tmp_l5;
      tmp_i2 = lua_isnumber(param_1,param_2);
      tmp_l5 = (long double)tmp_d1;
      if (tmp_i2 == 0) {
        tmp_u3 = lua_typename(param_1,3);
        tmp_u4 = lua_type(param_1,param_2);
        tmp_u4 = lua_typename(param_1,tmp_u4);
        tmp_u3 = lua_pushfstring(param_1,"%s expected, got %s",tmp_u3,tmp_u4);
        luaL_argerror(param_1,param_2,tmp_u3);
        tmp_l5 = (long double)tmp_d1;
      }
    }
  }
  return tmp_l5;
}

int luaL_checkinteger(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  
  tmp_i1 = lua_tointeger(param_1,param_2);
  if (tmp_i1 == 0) {
    tmp_i2 = lua_isnumber(param_1,param_2);
    if (tmp_i2 == 0) {
      tmp_u3 = lua_typename(param_1,3);
      tmp_u4 = lua_type(param_1,param_2);
      tmp_u4 = lua_typename(param_1,tmp_u4);
      tmp_u3 = lua_pushfstring(param_1,"%s expected, got %s",tmp_u3,tmp_u4);
      luaL_argerror(param_1,param_2,tmp_u3);
    }
  }
  return tmp_i1;
}

int luaL_optinteger(uint32_t param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  
  tmp_i1 = lua_type(param_1,param_2);
  if ((0 < tmp_i1) && (param_3 = lua_tointeger(param_1,param_2), param_3 == 0)) {
    tmp_i1 = lua_isnumber(param_1,param_2);
    if (tmp_i1 == 0) {
      tmp_u2 = lua_typename(param_1,3);
      tmp_u3 = lua_type(param_1,param_2);
      tmp_u3 = lua_typename(param_1,tmp_u3);
      tmp_u2 = lua_pushfstring(param_1,"%s expected, got %s",tmp_u2,tmp_u3);
      luaL_argerror(param_1,param_2,tmp_u2);
      param_3 = 0;
    }
    else {
      param_3 = 0;
    }
  }
  return param_3;
}

uint32_t luaL_getmetafield(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  
  tmp_i1 = lua_getmetatable(param_1,param_2);
  if (tmp_i1 == 0) {
    return 0;
  }
  lua_pushstring(param_1,param_3);
  lua_rawget(param_1,0xfffffffe);
  tmp_i1 = lua_type(param_1,0xffffffff);
  if (tmp_i1 != 0) {
    lua_remove(param_1,0xfffffffe);
    return 1;
  }
  lua_settop(param_1,0xfffffffd);
  return 0;
}

uint32_t luaL_callmeta(uint32_t param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  
  if (param_2 + 9999U < 10000) {
    tmp_i1 = lua_gettop(param_1);
    param_2 = tmp_i1 + 1 + param_2;
  }
  tmp_i1 = lua_getmetatable(param_1,param_2);
  if (tmp_i1 != 0) {
    lua_pushstring(param_1,param_3);
    lua_rawget(param_1,0xfffffffe);
    tmp_i1 = lua_type(param_1,0xffffffff);
    if (tmp_i1 != 0) {
      lua_remove(param_1,0xfffffffe);
      lua_pushvalue(param_1,param_2);
      lua_call(param_1,1,1);
      return 1;
    }
    lua_settop(param_1,0xfffffffd);
  }
  return 0;
}

char * luaL_findtable(uint32_t param_1,uint32_t param_2,char *param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  int tmp_i3;
  size_t tmp_s4;
  
  lua_pushvalue(param_1,param_2);
  do {
    tmp_pc2 = strchr(param_3,0x2e);
    if (tmp_pc2 == (char *)0x0) {
      tmp_s4 = strlen(param_3);
      tmp_pc2 = param_3 + tmp_s4;
    }
    lua_pushlstring(param_1,param_3,(int)tmp_pc2 - (int)param_3);
    lua_rawget(param_1,0xfffffffe);
    tmp_i3 = lua_type(param_1,0xffffffff);
    if (tmp_i3 == 0) {
      lua_settop(param_1,0xfffffffe);
      tmp_u1 = 1;
      if (*tmp_pc2 != '.') {
        tmp_u1 = param_4;
      }
      lua_createtable(param_1,0,tmp_u1);
      lua_pushlstring(param_1,param_3,(int)tmp_pc2 - (int)param_3);
      lua_pushvalue(param_1,0xfffffffe);
      lua_settable(param_1,0xfffffffc);
    }
    else {
      tmp_i3 = lua_type(param_1,0xffffffff);
      if (tmp_i3 != 5) {
        lua_settop(param_1,0xfffffffd);
        return param_3;
      }
    }
    param_3 = tmp_pc2 + 1;
    lua_remove(param_1,0xfffffffe);
  } while (*tmp_pc2 == '.');
  return (char *)0x0;
}

void luaL_openlib(uint32_t param_1,int param_2,int *param_3,uint param_4)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  uint local_20;
  
  if (param_2 != 0) {
    tmp_i2 = 0;
    tmp_i1 = *param_3;
    while (tmp_i1 != 0) {
      tmp_i2 = tmp_i2 + 1;
      tmp_i1 = param_3[tmp_i2 * 2];
    }
    luaL_findtable(param_1,0xffffd8f0,"_LOADED",1);
    lua_getfield(param_1,0xffffffff,param_2);
    tmp_i1 = lua_type(param_1,0xffffffff);
    if (tmp_i1 != 5) {
      lua_settop(param_1,0xfffffffe);
      tmp_i1 = luaL_findtable(param_1,0xffffd8ee,param_2,tmp_i2);
      if (tmp_i1 != 0) {
        luaL_error(param_1,"name conflict for module \'%s\'",param_2);
      }
      lua_pushvalue(param_1,0xffffffff);
      lua_setfield(param_1,0xfffffffd,param_2);
    }
    lua_remove(param_1,0xfffffffe);
    lua_insert(param_1,~param_4);
  }
  local_20 = ~param_4;
  if (*param_3 != 0) {
    do {
      if (0 < (int)param_4) {
        tmp_u3 = 0;
        do {
          tmp_u3 = tmp_u3 + 1;
          lua_pushvalue(param_1,-param_4);
        } while (tmp_u3 != param_4);
      }
      lua_pushcclosure(param_1,param_3[1],param_4);
      lua_setfield(param_1,-2 - param_4,*param_3);
      param_3 = param_3 + 2;
    } while (*param_3 != 0);
  }
  lua_settop(param_1,local_20);
  return;
}

void luaL_register(uint32_t param_1,int param_2,int *param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  
  if (param_2 == 0) goto LAB_00226420;
  tmp_i3 = 0;
  tmp_i2 = *param_3;
  while (tmp_i2 != 0) {
    tmp_i3 = tmp_i3 + 1;
    tmp_i2 = param_3[tmp_i3 * 2];
  }
  luaL_findtable(param_1,0xffffd8f0,"_LOADED",1);
  lua_getfield(param_1,0xffffffff,param_2);
  tmp_i2 = lua_type(param_1,0xffffffff);
  if (tmp_i2 != 5) {
    lua_settop(param_1,0xfffffffe);
    tmp_i2 = luaL_findtable(param_1,0xffffd8ee,param_2,tmp_i3);
    if (tmp_i2 != 0) {
      luaL_error(param_1,"name conflict for module \'%s\'",param_2);
    }
    lua_pushvalue(param_1,0xffffffff);
    lua_setfield(param_1,0xfffffffd,param_2);
  }
  lua_remove(param_1,0xfffffffe);
  lua_insert(param_1,0xffffffff);
  tmp_i2 = *param_3;
  tmp_pi1 = param_3;
  while (tmp_i2 != 0) {
    param_3 = tmp_pi1 + 2;
    lua_pushcclosure(param_1,tmp_pi1[1],0);
    lua_setfield(param_1,0xfffffffe,*tmp_pi1);
LAB_00226420:
    tmp_pi1 = param_3;
    tmp_i2 = *param_3;
  }
  lua_settop(param_1,0xffffffff);
  return;
}

int * luaL_prepbuffer(int *param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  
  tmp_pi1 = param_1 + 3;
  if (*param_1 - (int)tmp_pi1 != 0) {
    lua_pushlstring(param_1[2],tmp_pi1,*param_1 - (int)tmp_pi1);
    tmp_i2 = param_1[1];
    *param_1 = (int)tmp_pi1;
    param_1[1] = tmp_i2 + 1;
    if (1 < tmp_i2 + 1) {
      tmp_i2 = param_1[2];
      tmp_u5 = 1;
      tmp_u3 = lua_objlen(tmp_i2,0xffffffff);
      do {
        tmp_u4 = lua_objlen(tmp_i2,~tmp_u5);
        if (((int)(param_1[1] - tmp_u5) < 9) && (tmp_u3 <= tmp_u4)) break;
        tmp_u5 = tmp_u5 + 1;
        tmp_u3 = tmp_u3 + tmp_u4;
      } while ((int)tmp_u5 < param_1[1]);
      lua_concat(tmp_i2,tmp_u5);
      param_1[1] = (param_1[1] - tmp_u5) + 1;
      return tmp_pi1;
    }
  }
  return tmp_pi1;
}

void luaL_addlstring(int *param_1,uint8_t *param_2,int param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  int *tmp_pi3;
  uint tmp_u4;
  uint tmp_u5;
  uint tmp_u6;
  
  tmp_pi1 = param_1 + 3;
  do {
    if (param_3 == 0) {
      return;
    }
    tmp_pi3 = (int *)*param_1;
    if ((param_1 + 0x803 <= tmp_pi3) && ((int)tmp_pi3 - (int)tmp_pi1 != 0)) {
      lua_pushlstring(param_1[2],tmp_pi1,(int)tmp_pi3 - (int)tmp_pi1);
      tmp_i2 = param_1[1];
      *param_1 = (int)tmp_pi1;
      param_1[1] = tmp_i2 + 1;
      tmp_pi3 = tmp_pi1;
      if (1 < tmp_i2 + 1) {
        tmp_i2 = param_1[2];
        tmp_u6 = 1;
        tmp_u4 = lua_objlen(tmp_i2,0xffffffff);
        do {
          tmp_u5 = lua_objlen(tmp_i2,~tmp_u6);
          if (((int)(param_1[1] - tmp_u6) < 9) && (tmp_u4 <= tmp_u5)) break;
          tmp_u6 = tmp_u6 + 1;
          tmp_u4 = tmp_u4 + tmp_u5;
        } while ((int)tmp_u6 < param_1[1]);
        lua_concat(tmp_i2,tmp_u6);
        param_1[1] = (param_1[1] - tmp_u6) + 1;
        tmp_pi3 = (int *)*param_1;
      }
    }
    *param_1 = (int)tmp_pi3 + 1;
    param_3 = param_3 + -1;
    *(uint8_t *)tmp_pi3 = *param_2;
    param_2 = param_2 + 1;
  } while( true );
}

void luaL_gsub(uint32_t param_1,char *param_2,char *param_3,char *param_4)
{
  uint32_t tmp_u1;
  size_t tmp_s2;
  char *tmp_pc3;
  int tmp_i4;
  size_t tmp_s5;
  uint tmp_u6;
  uint tmp_u7;
  char *tmp_pc8;
  int tmp_i9;
  char *tmp_pc10;
  uint tmp_u11;
  char *local_2028;
  int local_2024;
  uint32_t local_2020;
  char local_201c;
  char local_201b [8191];
  char local_1c [12];
  
  tmp_s2 = strlen(param_3);
  local_2024 = 0;
  local_2020 = param_1;
  local_2028 = &local_201c;
  do {
    tmp_pc3 = strstr(param_2,param_3);
    if (tmp_pc3 == (char *)0x0) {
      tmp_s2 = strlen(param_2);
      luaL_addlstring(&local_2028,param_2,tmp_s2);
      tmp_i4 = (int)local_2028 - (int)&local_201c;
      if (tmp_i4 != 0) {
        lua_pushlstring(local_2020,&local_201c,tmp_i4);
        local_2024 = local_2024 + 1;
        local_2028 = &local_201c;
      }
      lua_concat(local_2020,local_2024);
      local_2024 = 1;
      lua_tolstring(param_1,0xffffffff,0);
      return;
    }
    tmp_i4 = (int)tmp_pc3 - (int)param_2;
    for (; tmp_i4 != 0; tmp_i4 = tmp_i4 + -1) {
      if ((local_2028 < local_1c) || (tmp_i9 = (int)local_2028 - (int)&local_201c, tmp_i9 == 0)) {
LAB_002266c0:
        tmp_pc8 = local_2028 + 1;
      }
      else {
        lua_pushlstring(local_2020,&local_201c,tmp_i9);
        tmp_u1 = local_2020;
        local_2024 = local_2024 + 1;
        if (1 < local_2024) {
          tmp_u11 = 1;
          local_2028 = &local_201c;
          tmp_u6 = lua_objlen(local_2020,0xffffffff);
          do {
            tmp_u7 = lua_objlen(tmp_u1,~tmp_u11);
            if (((int)(local_2024 - tmp_u11) < 9) && (tmp_u6 <= tmp_u7)) break;
            tmp_u11 = tmp_u11 + 1;
            tmp_u6 = tmp_u6 + tmp_u7;
          } while ((int)tmp_u11 < local_2024);
          lua_concat(tmp_u1,tmp_u11);
          local_2024 = (local_2024 - tmp_u11) + 1;
          goto LAB_002266c0;
        }
        tmp_pc8 = local_201b;
        local_2028 = &local_201c;
      }
      *local_2028 = *param_2;
      param_2 = param_2 + 1;
      local_2028 = tmp_pc8;
    }
    tmp_s5 = strlen(param_4);
    tmp_pc8 = param_4;
    for (; tmp_s5 != 0; tmp_s5 = tmp_s5 - 1) {
      if ((local_2028 < local_1c) || (tmp_i4 = (int)local_2028 - (int)&local_201c, tmp_i4 == 0)) {
LAB_002267d0:
        tmp_pc10 = local_2028 + 1;
      }
      else {
        lua_pushlstring(local_2020,&local_201c,tmp_i4);
        tmp_u1 = local_2020;
        local_2024 = local_2024 + 1;
        if (1 < local_2024) {
          tmp_u11 = 1;
          local_2028 = &local_201c;
          tmp_u6 = lua_objlen(local_2020,0xffffffff);
          do {
            tmp_u7 = lua_objlen(tmp_u1,~tmp_u11);
            if (((int)(local_2024 - tmp_u11) < 9) && (tmp_u6 <= tmp_u7)) break;
            tmp_u11 = tmp_u11 + 1;
            tmp_u6 = tmp_u6 + tmp_u7;
          } while ((int)tmp_u11 < local_2024);
          lua_concat(tmp_u1,tmp_u11);
          local_2024 = (local_2024 - tmp_u11) + 1;
          goto LAB_002267d0;
        }
        tmp_pc10 = local_201b;
        local_2028 = &local_201c;
      }
      *local_2028 = *tmp_pc8;
      local_2028 = tmp_pc10;
      tmp_pc8 = tmp_pc8 + 1;
    }
    param_2 = tmp_pc3 + tmp_s2;
  } while( true );
}

void luaL_addstring(int *param_1,char *param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  size_t tmp_s3;
  int *tmp_pi4;
  uint tmp_u5;
  uint tmp_u6;
  uint tmp_u7;
  
  tmp_s3 = strlen(param_2);
  tmp_pi1 = param_1 + 3;
  do {
    if (tmp_s3 == 0) {
      return;
    }
    tmp_pi4 = (int *)*param_1;
    if ((param_1 + 0x803 <= tmp_pi4) && ((int)tmp_pi4 - (int)tmp_pi1 != 0)) {
      lua_pushlstring(param_1[2],tmp_pi1,(int)tmp_pi4 - (int)tmp_pi1);
      tmp_i2 = param_1[1];
      *param_1 = (int)tmp_pi1;
      param_1[1] = tmp_i2 + 1;
      tmp_pi4 = tmp_pi1;
      if (1 < tmp_i2 + 1) {
        tmp_i2 = param_1[2];
        tmp_u7 = 1;
        tmp_u5 = lua_objlen(tmp_i2,0xffffffff);
        do {
          tmp_u6 = lua_objlen(tmp_i2,~tmp_u7);
          if (((int)(param_1[1] - tmp_u7) < 9) && (tmp_u5 <= tmp_u6)) break;
          tmp_u7 = tmp_u7 + 1;
          tmp_u5 = tmp_u5 + tmp_u6;
        } while ((int)tmp_u7 < param_1[1]);
        lua_concat(tmp_i2,tmp_u7);
        param_1[1] = (param_1[1] - tmp_u7) + 1;
        tmp_pi4 = (int *)*param_1;
      }
    }
    *param_1 = (int)tmp_pi4 + 1;
    tmp_s3 = tmp_s3 - 1;
    *(char *)tmp_pi4 = *param_2;
    param_2 = param_2 + 1;
  } while( true );
}

void luaL_pushresult(int *param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  
  tmp_pi1 = param_1 + 3;
  if (*param_1 - (int)tmp_pi1 == 0) {
    tmp_i2 = param_1[1];
  }
  else {
    lua_pushlstring(param_1[2],tmp_pi1,*param_1 - (int)tmp_pi1);
    *param_1 = (int)tmp_pi1;
    tmp_i2 = param_1[1] + 1;
    param_1[1] = tmp_i2;
  }
  lua_concat(param_1[2],tmp_i2);
  param_1[1] = 1;
  return;
}

void luaL_addvalue(int *param_1)
{
  int *tmp_pi1;
  uint8_t tmp_u2;
  uint16_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  uint tmp_u7;
  uint tmp_u8;
  uint tmp_u9;
  uint32_t *tmp_pu10;
  uint32_t *tmp_pu11;
  uint32_t *tmp_pu12;
  byte tmp_b13;
  uint local_20 [4];
  
  tmp_b13 = 0;
  tmp_i6 = param_1[2];
  tmp_pi1 = param_1 + 3;
  tmp_pu5 = (uint32_t *)lua_tolstring(tmp_i6,0xffffffff,local_20);
  tmp_pu10 = (uint32_t *)*param_1;
  if (local_20[0] <= (uint)((int)tmp_pi1 + (0x2000 - (int)tmp_pu10))) {
    tmp_u7 = local_20[0];
    if (7 < local_20[0]) {
      tmp_pu12 = tmp_pu10;
      if (((uint)tmp_pu10 & 1) != 0) {
        tmp_u2 = *(uint8_t *)tmp_pu5;
        tmp_pu12 = (uint32_t *)((int)tmp_pu10 + 1);
        tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 1);
        tmp_u7 = local_20[0] - 1;
        *(uint8_t *)tmp_pu10 = tmp_u2;
      }
      tmp_pu11 = tmp_pu12;
      if (((uint)tmp_pu12 & 2) != 0) {
        tmp_u3 = *(uint16_t *)tmp_pu5;
        tmp_pu11 = (uint32_t *)((int)tmp_pu12 + 2);
        tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
        tmp_u7 = tmp_u7 - 2;
        *(uint16_t *)tmp_pu12 = tmp_u3;
      }
      tmp_pu10 = tmp_pu11;
      if (((uint)tmp_pu11 & 4) != 0) {
        tmp_u4 = *tmp_pu5;
        tmp_pu10 = tmp_pu11 + 1;
        tmp_pu5 = tmp_pu5 + 1;
        tmp_u7 = tmp_u7 - 4;
        *tmp_pu11 = tmp_u4;
      }
    }
    for (; tmp_u7 != 0; tmp_u7 = tmp_u7 - 1) {
      *(uint8_t *)tmp_pu10 = *(uint8_t *)tmp_pu5;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + (uint)tmp_b13 * -2 + 1);
      tmp_pu10 = (uint32_t *)((int)tmp_pu10 + (uint)tmp_b13 * -2 + 1);
    }
    *param_1 = *param_1 + local_20[0];
    lua_settop(tmp_i6,0xfffffffe);
    return;
  }
  if ((int)tmp_pu10 - (int)tmp_pi1 == 0) {
    tmp_i6 = param_1[1] + 1;
    param_1[1] = tmp_i6;
  }
  else {
    lua_pushlstring(param_1[2],tmp_pi1,(int)tmp_pu10 - (int)tmp_pi1);
    param_1[1] = param_1[1] + 1;
    *param_1 = (int)tmp_pi1;
    lua_insert(tmp_i6,0xfffffffe);
    tmp_i6 = param_1[1] + 1;
    param_1[1] = tmp_i6;
  }
  if (1 < tmp_i6) {
    tmp_i6 = param_1[2];
    tmp_u9 = 1;
    tmp_u7 = lua_objlen(tmp_i6,0xffffffff);
    do {
      tmp_u8 = lua_objlen(tmp_i6,~tmp_u9);
      if (((int)(param_1[1] - tmp_u9) < 9) && (tmp_u7 <= tmp_u8)) break;
      tmp_u9 = tmp_u9 + 1;
      tmp_u7 = tmp_u7 + tmp_u8;
    } while ((int)tmp_u9 < param_1[1]);
    lua_concat(tmp_i6,tmp_u9);
    param_1[1] = (param_1[1] - tmp_u9) + 1;
  }
  return;
}

void luaL_buffinit(int param_1,int *param_2)
{
  param_2[1] = 0;
  param_2[2] = param_1;
  *param_2 = (int)(param_2 + 3);
  return;
}

int luaL_ref(uint32_t param_1,int param_2)
{
  int tmp_i1;
  
  if (param_2 + 9999U < 10000) {
    tmp_i1 = lua_gettop(param_1);
    param_2 = tmp_i1 + 1 + param_2;
  }
  tmp_i1 = lua_type(param_1,0xffffffff);
  if (tmp_i1 == 0) {
    lua_settop(param_1,0xfffffffe);
    tmp_i1 = -1;
  }
  else {
    lua_rawgeti(param_1,param_2,0);
    tmp_i1 = lua_tointeger(param_1,0xffffffff);
    lua_settop(param_1,0xfffffffe);
    if (tmp_i1 == 0) {
      tmp_i1 = lua_objlen(param_1,param_2);
      tmp_i1 = tmp_i1 + 1;
    }
    else {
      lua_rawgeti(param_1,param_2,tmp_i1);
      lua_rawseti(param_1,param_2,0);
    }
    lua_rawseti(param_1,param_2,tmp_i1);
  }
  return tmp_i1;
}

void luaL_unref(uint32_t param_1,int param_2,int param_3)
{
  int tmp_i1;
  
  if (-1 < param_3) {
    if (param_2 + 9999U < 10000) {
      tmp_i1 = lua_gettop(param_1);
      param_2 = tmp_i1 + 1 + param_2;
    }
    lua_rawgeti(param_1,param_2,0);
    lua_rawseti(param_1,param_2,param_3);
    lua_pushinteger(param_1,param_3);
    lua_rawseti(param_1,param_2,0);
  }
  return;
}

uint32_t luaL_loadfile(uint32_t param_1,char *param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  int *tmp_pi5;
  char *tmp_pc6;
  uint32_t local_2034;
  uint32_t local_2024;
  _IO_FILE *local_2020;
  
  tmp_i1 = lua_gettop(param_1);
  tmp_i1 = tmp_i1 + 1;
  local_2024 = 0;
  if (param_2 == (char *)0x0) {
    lua_pushlstring(param_1,&g_unk_0026fbee,6);
    local_2020 = _stdin;
  }
  else {
    lua_pushfstring(param_1,&g_unk_0026fbf5,param_2);
    local_2020 = fopen(param_2,"r");
    if (local_2020 == (FILE *)0x0) {
      tmp_pi5 = __errno_location();
      tmp_pc6 = strerror(*tmp_pi5);
      tmp_i2 = lua_tolstring(param_1,tmp_i1,0);
      tmp_i2 = tmp_i2 + 1;
      tmp_pc4 = "open";
      goto LAB_002270c7;
    }
  }
  tmp_i2 = _IO_getc(local_2020);
  if (tmp_i2 == 0x23) {
    local_2024 = 1;
    do {
      tmp_i2 = _IO_getc(local_2020);
      if (tmp_i2 == -1) goto LAB_00226ffa;
    } while (tmp_i2 != 10);
    tmp_i2 = _IO_getc(local_2020);
  }
  if (tmp_i2 == 0x1b) {
    if (param_2 == (char *)0x0) {
      ungetc(0x1b,local_2020);
      tmp_u3 = lua_tolstring(param_1,0xffffffff,0);
      local_2034 = lua_load(param_1,getF,&local_2024,tmp_u3);
      tmp_i2 = ferror(local_2020);
    }
    else {
      local_2020 = freopen(param_2,"rb",local_2020);
      if (local_2020 == (FILE *)0x0) {
        tmp_pi5 = __errno_location();
        tmp_pc6 = strerror(*tmp_pi5);
        tmp_i2 = lua_tolstring(param_1,tmp_i1,0);
        tmp_i2 = tmp_i2 + 1;
        tmp_pc4 = "reopen";
        goto LAB_002270c7;
      }
      do {
        tmp_i2 = _IO_getc(local_2020);
        if (tmp_i2 == -1) break;
      } while (tmp_i2 != 0x1b);
      local_2024 = 0;
      ungetc(tmp_i2,local_2020);
      tmp_u3 = lua_tolstring(param_1,0xffffffff,0);
      local_2034 = lua_load(param_1,getF,&local_2024,tmp_u3);
      tmp_i2 = ferror(local_2020);
LAB_00227055:
      fclose(local_2020);
    }
  }
  else {
LAB_00226ffa:
    ungetc(tmp_i2,local_2020);
    tmp_u3 = lua_tolstring(param_1,0xffffffff,0);
    local_2034 = lua_load(param_1,getF,&local_2024,tmp_u3);
    tmp_i2 = ferror(local_2020);
    if (param_2 != (char *)0x0) goto LAB_00227055;
  }
  if (tmp_i2 == 0) {
    lua_remove();
    return local_2034;
  }
  lua_settop(param_1,tmp_i1);
  tmp_pi5 = __errno_location();
  tmp_pc6 = strerror(*tmp_pi5);
  tmp_i2 = lua_tolstring(param_1,tmp_i1,0);
  tmp_i2 = tmp_i2 + 1;
  tmp_pc4 = "read";
LAB_002270c7:
  lua_pushfstring(param_1,"cannot %s %s: %s",tmp_pc4,tmp_i2,tmp_pc6);
  lua_remove(param_1,tmp_i1);
  return 6;
}

void luaL_loadbuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  uint32_t local_14;
  uint32_t local_10;
  
  local_14 = param_2;
  local_10 = param_3;
  lua_load(param_1,getS,&local_14,param_4);
  return;
}

void luaL_loadstring(uint32_t param_1,char *param_2)
{
  char *local_14;
  size_t local_10;
  
  local_10 = strlen(param_2);
  local_14 = param_2;
  lua_load(param_1,getS,&local_14,param_2);
  return;
}

int luaL_newstate(void)
{
  int tmp_i1;
  
  tmp_i1 = lua_newstate(l_alloc,0);
  if (tmp_i1 != 0) {
    lua_atpanic(tmp_i1,panic);
  }
  return tmp_i1;
}

uint luaZ_fill(int *param_1)
{
  byte *tmp_pb1;
  uint tmp_u2;
  int local_10 [3];
  
  tmp_pb1 = (byte *)(*(void *)param_1[2])(param_1[4],param_1[3],local_10);
  if ((tmp_pb1 == (byte *)0x0) || (local_10[0] == 0)) {
    tmp_u2 = 0xffffffff;
  }
  else {
    *param_1 = local_10[0] + -1;
    param_1[1] = (int)(tmp_pb1 + 1);
    tmp_u2 = (uint)*tmp_pb1;
  }
  return tmp_u2;
}

uint luaZ_lookahead(int *param_1)
{
  byte *tmp_pb1;
  int local_10 [3];
  
  if (*param_1 == 0) {
    tmp_pb1 = (byte *)(*(void *)param_1[2])(param_1[4],param_1[3],local_10);
    if ((tmp_pb1 == (byte *)0x0) || (local_10[0] == 0)) {
      return 0xffffffff;
    }
    *param_1 = local_10[0];
    param_1[1] = (int)tmp_pb1;
  }
  else {
    tmp_pb1 = (byte *)param_1[1];
  }
  return (uint)*tmp_pb1;
}

void luaZ_init(uint32_t param_1,uint32_t *param_2,uint32_t param_3,uint32_t param_4)
{
  *param_2 = 0;
  param_2[4] = param_1;
  param_2[1] = 0;
  param_2[2] = param_3;
  param_2[3] = param_4;
  return;
}

uint luaZ_read(uint *param_1,uint32_t *param_2,uint param_3)
{
  uint8_t tmp_u1;
  uint16_t tmp_u2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  uint32_t *tmp_pu6;
  uint32_t *tmp_pu7;
  uint32_t *tmp_pu8;
  byte tmp_b9;
  uint local_24;
  uint local_10;
  
  tmp_b9 = 0;
  if (param_3 != 0) {
    tmp_u5 = *param_1;
    do {
      if (tmp_u5 == 0) {
        tmp_pu6 = (uint32_t *)(*(void *)param_1[2])(param_1[4],param_1[3],&local_10);
        if ((tmp_pu6 == (uint32_t *)0x0) || (local_10 == 0)) {
          return param_3;
        }
        *param_1 = local_10;
        param_1[1] = (uint)tmp_pu6;
        tmp_u5 = local_10;
      }
      else {
        tmp_pu6 = (uint32_t *)param_1[1];
      }
      tmp_u4 = tmp_u5;
      if (param_3 < tmp_u5) {
        tmp_u4 = param_3;
      }
      local_24 = tmp_u4;
      tmp_pu8 = param_2;
      if (7 < tmp_u4) {
        if (((uint)param_2 & 1) != 0) {
          tmp_u1 = *(uint8_t *)tmp_pu6;
          tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 1);
          *(uint8_t *)param_2 = tmp_u1;
          local_24 = tmp_u4 - 1;
          tmp_pu8 = (uint32_t *)((int)param_2 + 1);
        }
        tmp_pu7 = tmp_pu8;
        if (((uint)tmp_pu8 & 2) != 0) {
          tmp_u2 = *(uint16_t *)tmp_pu6;
          tmp_pu7 = (uint32_t *)((int)tmp_pu8 + 2);
          tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
          *(uint16_t *)tmp_pu8 = tmp_u2;
          local_24 = local_24 - 2;
        }
        tmp_pu8 = tmp_pu7;
        if (((uint)tmp_pu7 & 4) != 0) {
          tmp_u3 = *tmp_pu6;
          tmp_pu8 = tmp_pu7 + 1;
          tmp_pu6 = tmp_pu6 + 1;
          *tmp_pu7 = tmp_u3;
          local_24 = local_24 - 4;
        }
      }
      for (; local_24 != 0; local_24 = local_24 - 1) {
        *(uint8_t *)tmp_pu8 = *(uint8_t *)tmp_pu6;
        tmp_pu6 = (uint32_t *)((int)tmp_pu6 + (uint)tmp_b9 * -2 + 1);
        tmp_pu8 = (uint32_t *)((int)tmp_pu8 + (uint)tmp_b9 * -2 + 1);
      }
      param_1[1] = param_1[1] + tmp_u4;
      param_2 = (uint32_t *)((int)param_2 + tmp_u4);
      tmp_u5 = *param_1 - tmp_u4;
      param_3 = param_3 - tmp_u4;
      *param_1 = tmp_u5;
    } while (param_3 != 0);
  }
  return 0;
}

uint32_t luaZ_openspace(uint32_t param_1,uint32_t *param_2,uint param_3)
{
  uint32_t tmp_u1;
  
  if (param_3 <= (uint)param_2[2]) {
    return *param_2;
  }
  if (param_3 < 0x20) {
    param_3 = 0x20;
  }
  else if (0xfffffffd < param_3 + 1) {
    tmp_u1 = luaM_toobig(param_1);
    goto LAB_00227573;
  }
  tmp_u1 = luaM_realloc_(param_1,*param_2,param_2[2],param_3);
LAB_00227573:
  *param_2 = tmp_u1;
  param_2[2] = param_3;
  return tmp_u1;
}

uint32_t luaopen_math(uint32_t param_1)
{
  luaL_register(param_1,&g_unk_0026eebd,mathlib);
  lua_pushnumber(param_1,0x54442d18,0x400921fb);
  lua_setfield(param_1,0xfffffffe,&g_unk_0026fc40);
  lua_pushnumber(param_1,0x7ff0000000000000);
  lua_setfield(param_1,0xfffffffe,&g_unk_0026fc43);
  lua_getfield(param_1,0xffffffff,&g_unk_0026fc48);
  lua_setfield(param_1,0xfffffffe,"mod");
  return 1;
}

uint32_t luaopen_os(uint32_t param_1)
{
  luaL_register(param_1,&g_unk_0026174c,syslib);
  return 1;
}

void luaU_print(int param_1,int param_2)
{
  int *tmp_pi1;
  char tmp_c2;
  byte tmp_b3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  byte tmp_b8;
  uint tmp_u9;
  char *tmp_pc10;
  uint8_t *tmp_pu11;
  uint tmp_u12;
  uint tmp_u13;
  uint tmp_u14;
  uint8_t *tmp_pu15;
  int tmp_i16;
  uint8_t *tmp_pu17;
  int tmp_i18;
  uint8_t *tmp_pu19;
  uint tmp_u20;
  int tmp_i21;
  int tmp_i22;
  uint8_t *tmp_pu23;
  uint8_t *tmp_pu24;
  int tmp_i25;
  int tmp_i26;
  int tmp_i27;
  char *local_54;
  
  tmp_i4 = *(int *)(param_1 + 0x34);
  tmp_c2 = *(char *)(*(int *)(param_1 + 0x20) + 0x10);
  if ((tmp_c2 == '=') || (tmp_c2 == '@')) {
    local_54 = (char *)(*(int *)(param_1 + 0x20) + 0x11);
  }
  else {
    if (tmp_c2 != '\x1b') {
      local_54 = "(string)";
      tmp_i21 = *(int *)(param_1 + 0x2c);
      goto joined_r0x002291a4;
    }
    local_54 = "(bstring)";
  }
  tmp_i21 = *(int *)(param_1 + 0x2c);
joined_r0x002291a4:
  if (tmp_i21 == 1) {
    tmp_i16 = *(int *)(param_1 + 0x3c);
    tmp_pu23 = &g_unk_0026ea14;
    tmp_u5 = *(uint32_t *)(param_1 + 0x40);
  }
  else {
    tmp_i16 = *(int *)(param_1 + 0x3c);
    tmp_pu23 = &g_unk_0024e6ea;
    tmp_u5 = *(uint32_t *)(param_1 + 0x40);
  }
  if (tmp_i16 == 0) {
    tmp_pc10 = "main";
  }
  else {
    tmp_pc10 = "function";
  }
  tmp_i18 = param_1;
  printf("\n%s <%s:%d,%d> (%d instruction%s, %d bytes at %p)\n",tmp_pc10,local_54,tmp_i16,tmp_u5,tmp_i21
         ,tmp_pu23,tmp_i21 * 4,param_1);
  if (*(byte *)(param_1 + 0x48) == 1) {
    tmp_pu23 = &g_unk_0026ea14;
  }
  else {
    tmp_pu23 = &g_unk_0024e6ea;
  }
  if (*(byte *)(param_1 + 0x4b) == 1) {
    tmp_pu24 = &g_unk_0026ea14;
    tmp_b3 = *(byte *)(param_1 + 0x49);
  }
  else {
    tmp_pu24 = &g_unk_0024e6ea;
    tmp_b3 = *(byte *)(param_1 + 0x49);
  }
  if (tmp_b3 == 1) {
    local_54 = &g_unk_0026ea14;
  }
  else {
    local_54 = &g_unk_0024e6ea;
  }
  if (*(char *)(param_1 + 0x4a) == '\0') {
    tmp_pu11 = &g_unk_0026ea14;
  }
  else {
    tmp_pu11 = &g_unk_0026fdaf;
  }
  printf("%d%s param%s, %d slot%s, %d upvalue%s, ",(uint)tmp_b3,tmp_pu11,local_54,
         (uint)*(byte *)(param_1 + 0x4b),tmp_pu24,(uint)*(byte *)(param_1 + 0x48),tmp_pu23,tmp_i18);
  tmp_i21 = *(int *)(param_1 + 0x34);
  if (tmp_i21 == 1) {
    tmp_pu24 = &g_unk_0026ea14;
  }
  else {
    tmp_pu24 = &g_unk_0024e6ea;
  }
  tmp_i16 = *(int *)(param_1 + 0x28);
  if (tmp_i16 == 1) {
    tmp_pu15 = &g_unk_0026ea14;
    tmp_i22 = *(int *)(param_1 + 0x38);
  }
  else {
    tmp_pu15 = &g_unk_0024e6ea;
    tmp_i22 = *(int *)(param_1 + 0x38);
  }
  if (tmp_i22 == 1) {
    tmp_pu19 = &g_unk_0026ea14;
  }
  else {
    tmp_pu19 = &g_unk_0024e6ea;
  }
  printf("%d local%s, %d constant%s, %d function%s\n",tmp_i22,tmp_pu19,tmp_i16,tmp_pu15,tmp_i21,tmp_pu24,
         tmp_pu23,tmp_i18);
  tmp_i22 = *(int *)(param_1 + 0xc);
  tmp_i27 = *(int *)(param_1 + 0x2c);
  if (0 < tmp_i27) {
    tmp_i25 = 0;
    do {
      tmp_u14 = *(uint *)(tmp_i22 + tmp_i25 * 4);
      tmp_u20 = tmp_u14 & 0x3f;
      tmp_u12 = tmp_u14 >> 6 & 0xff;
      tmp_u13 = tmp_u14 >> 0x17;
      tmp_pu17 = (uint8_t *)(tmp_u14 >> 0xe);
      tmp_u14 = (uint)tmp_pu17 & 0x1ff;
      if (*(int *)(param_1 + 0x14) == 0) {
        tmp_i26 = tmp_i25 + 1;
        printf("\t%d\t",tmp_i26,tmp_pu19,tmp_i16,tmp_pu15,tmp_i21,tmp_pu24,tmp_pu23,tmp_i18);
LAB_00229687:
        printf("[-]\t",tmp_i26,tmp_pu19,tmp_i16,tmp_pu15,tmp_i21,tmp_pu24);
      }
      else {
        tmp_i6 = *(int *)(*(int *)(param_1 + 0x14) + tmp_i25 * 4);
        tmp_i26 = tmp_i25 + 1;
        printf("\t%d\t",tmp_i26,tmp_pu19,tmp_i16,tmp_pu15,tmp_i21,tmp_pu24,tmp_pu23,tmp_i18);
        if (tmp_i6 < 1) goto LAB_00229687;
        printf("[%d]\t",tmp_i6,tmp_pu19,tmp_i16,tmp_pu15,tmp_i21,tmp_pu24,tmp_pu23);
      }
      local_54 = (char *)(tmp_i25 + 1);
      tmp_u9 = *(uint *)(luaP_opnames + tmp_u20 * 4);
      printf("%-9s\t",tmp_u9);
      tmp_b3 = luaP_opmodes[tmp_u20];
      tmp_b8 = tmp_b3 & 3;
      if (tmp_b8 != 1) {
        if (tmp_b8 == 0) {
          printf("%d",tmp_u12);
          tmp_u9 = tmp_u12;
          if ((tmp_b3 >> 4 & 3) != 0) {
            tmp_u9 = tmp_u13;
            if ((tmp_u13 & 0x100) != 0) {
              tmp_u9 = ~(tmp_u13 & 0xfffffeff);
            }
            printf(" %d",tmp_u9);
          }
          if ((tmp_b3 >> 2 & 3) != 0) {
            tmp_u9 = tmp_u14;
            if (((uint)tmp_pu17 & 0x100) != 0) {
              tmp_u9 = ~((uint)tmp_pu17 & 0xff);
            }
            printf(" %d",tmp_u9);
          }
          goto LAB_0022941d;
        }
        if (tmp_b8 != 2) goto LAB_0022941d;
        tmp_pu7 = tmp_pu17 + -0x1ffff;
        if (tmp_u20 != 0x16) goto LAB_00229407;
        printf("%d",tmp_pu17 + -0x1ffff);
_L61:
        printf("\t; to %d",tmp_pu17 + tmp_i25 + -0x1fffd,tmp_pu19);
        goto LAB_00229460;
      }
      tmp_pu7 = tmp_pu17;
      if ((tmp_b3 >> 4 & 3) == 3) {
        tmp_pu7 = (uint8_t *)~(uint)tmp_pu17;
      }
LAB_00229407:
      tmp_pu19 = tmp_pu7;
      printf("%d %d",tmp_u12,tmp_pu19);
      tmp_u9 = tmp_u12;
LAB_0022941d:
      switch(tmp_u20) {
      default:
_L99:
        break;
      case 1:
        printf("\t; ",tmp_u9,tmp_pu19);
        PrintConstant_isra_0();
        break;
      case 4:
      case 8:
        if (*(int *)(param_1 + 0x24) < 1) {
          tmp_pu17 = &g_unk_0026ea1d;
        }
        else {
          tmp_pu17 = (uint8_t *)(*(int *)(*(int *)(param_1 + 0x1c) + tmp_u13 * 4) + 0x10);
        }
        goto LAB_00229518;
      case 5:
      case 7:
        tmp_pu17 = (uint8_t *)(*(int *)((int)tmp_pu17 * 0xc + *(int *)(param_1 + 8)) + 0x10);
LAB_00229518:
        printf("\t; %s",tmp_pu17,tmp_pu19);
        break;
      case 6:
      case 0xb:
        if (((uint)tmp_pu17 & 0x100) != 0) {
          printf("\t; ",tmp_u9,tmp_pu19);
          PrintConstant_isra_0();
        }
        break;
      case 9:
      case 0xc:
      case 0xd:
      case 0xe:
      case 0xf:
      case 0x11:
      case 0x17:
      case 0x18:
      case 0x19:
        if ((tmp_u13 & 0x100) == 0) {
          if (((uint)tmp_pu17 & 0x100) == 0) goto _L99;
          printf("\t; ",tmp_u9,tmp_pu19);
          putchar(0x2d);
          putchar(0x20);
LAB_00229578:
          PrintConstant_isra_0();
        }
        else {
          printf("\t; ",tmp_u9,tmp_pu19);
          PrintConstant_isra_0();
          putchar(0x20);
          if (((uint)tmp_pu17 & 0x100) != 0) goto LAB_00229578;
          putchar(0x2d);
        }
        break;
      case 0x16:
      case 0x1f:
      case 0x20:
        goto _L61;
      case 0x22:
        if (tmp_u14 == 0) {
          tmp_i26 = (int)local_54 * 4;
          local_54 = (char *)(tmp_i25 + 2);
          printf("\t; %d",*(uint32_t *)(tmp_i22 + tmp_i26),tmp_pu19);
        }
        else {
          printf("\t; %d",tmp_u14,tmp_pu19);
        }
        break;
      case 0x24:
        printf("\t; %p",*(uint32_t *)(*(int *)(param_1 + 0x10) + (int)tmp_pu17 * 4),tmp_pu19);
      }
LAB_00229460:
      putchar(10);
      tmp_i25 = (int)local_54;
    } while ((int)local_54 < tmp_i27);
  }
  if (param_2 != 0) {
    tmp_i22 = *(int *)(param_1 + 0x28);
    tmp_i27 = param_1;
    printf("constants (%d) for %p:\n",tmp_i22,param_1,tmp_i16,tmp_pu15,tmp_i21,tmp_pu24,tmp_pu23,tmp_i18);
    if (0 < tmp_i22) {
      tmp_i18 = 0;
      do {
        tmp_i18 = tmp_i18 + 1;
        printf("\t%d\t",tmp_i18,tmp_i27,tmp_i16,tmp_pu15,tmp_i21,tmp_pu24);
        PrintConstant_isra_0();
        putchar(10);
      } while (tmp_i18 != tmp_i22);
    }
    tmp_i18 = *(int *)(param_1 + 0x38);
    printf("locals (%d) for %p:\n",tmp_i18,param_1,tmp_i16,tmp_pu15,tmp_i21,tmp_pu24);
    if (0 < tmp_i18) {
      tmp_i21 = 0;
      do {
        tmp_pi1 = (int *)(*(int *)(param_1 + 0x18) + tmp_i21 * 0xc);
        tmp_pu15 = (uint8_t *)(tmp_pi1[2] + 1);
        tmp_i16 = tmp_pi1[1] + 1;
        tmp_i22 = tmp_i21 + 1;
        printf("\t%d\t%s\t%d\t%d\n",tmp_i21,*tmp_pi1 + 0x10,tmp_i16,tmp_pu15);
        tmp_i21 = tmp_i22;
      } while (tmp_i22 != tmp_i18);
    }
    tmp_i21 = *(int *)(param_1 + 0x24);
    printf("upvalues (%d) for %p:\n",tmp_i21,param_1,tmp_i16,tmp_pu15);
    tmp_i18 = *(int *)(param_1 + 0x1c);
    if ((tmp_i18 != 0) && (0 < tmp_i21)) {
      tmp_i22 = 0;
      while( true ) {
        printf("\t%d\t%s\n",tmp_i22,*(int *)(tmp_i18 + tmp_i22 * 4) + 0x10,tmp_i16,tmp_pu15);
        if (tmp_i22 + 1 == tmp_i21) break;
        tmp_i18 = *(int *)(param_1 + 0x1c);
        tmp_i22 = tmp_i22 + 1;
      }
    }
  }
  tmp_i21 = 0;
  if (0 < tmp_i4) {
    do {
      tmp_i16 = tmp_i21 * 4;
      tmp_i21 = tmp_i21 + 1;
      luaU_print(*(uint32_t *)(*(int *)(param_1 + 0x10) + tmp_i16),param_2);
    } while (tmp_i21 != tmp_i4);
  }
  return;
}

uint luaO_int2fb(uint param_1)
{
  int tmp_i1;
  
  tmp_i1 = 0;
  for (; 0xf < param_1; param_1 = param_1 + 1 >> 1) {
    tmp_i1 = tmp_i1 + 1;
  }
  if (7 < param_1) {
    param_1 = param_1 - 8 | tmp_i1 * 8 + 8U;
  }
  return param_1;
}

uint luaO_fb2int(uint param_1)
{
  uint tmp_u1;
  
  tmp_u1 = (int)param_1 >> 3 & 0x1f;
  if (tmp_u1 != 0) {
    param_1 = (param_1 & 7) + 8 << ((char)tmp_u1 - 1U & 0x1f);
  }
  return param_1;
}

int luaO_log2(uint param_1)
{
  int tmp_i1;
  
  tmp_i1 = -1;
  for (; 0xff < param_1; param_1 = param_1 >> 8) {
    tmp_i1 = tmp_i1 + 8;
  }
  return tmp_i1 + (uint)(byte)log_2_4786[param_1];
}

bool luaO_rawequalObj(double *param_1,double *param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 1);
  if (tmp_i1 != *(int *)(param_2 + 1)) {
    return false;
  }
  if (tmp_i1 != 1) {
    if (tmp_i1 < 2) {
      if (tmp_i1 == 0) {
        return true;
      }
    }
    else if ((tmp_i1 != 2) && (tmp_i1 == 3)) {
      return *param_2 == *param_1;
    }
  }
  return *(int *)param_1 == *(int *)param_2;
}

bool luaO_str2d(byte *param_1,double *param_2)
{
  ushort **tmp_ppu1;
  ulong tmp_u2;
  byte tmp_b3;
  bool tmp_b4;
  double tmp_d5;
  byte *local_20 [4];
  
  tmp_d5 = strtod((char *)param_1,(char **)local_20);
  *param_2 = tmp_d5;
  if (local_20[0] != param_1) {
    tmp_b3 = *local_20[0];
    if ((tmp_b3 & 0xdf) == 0x58) {
      tmp_u2 = strtoul((char *)param_1,(char **)local_20,0x10);
      *param_2 = (double)tmp_u2;
      tmp_b3 = *local_20[0];
    }
    tmp_b4 = true;
    if (tmp_b3 != 0) {
      tmp_ppu1 = __ctype_b_loc();
      while (local_20[0] = local_20[0] + 1,
            (*(byte *)((int)*tmp_ppu1 + (uint)tmp_b3 * 2 + 1) & 0x20) != 0) {
        tmp_b3 = *local_20[0];
      }
      tmp_b4 = tmp_b3 == 0;
    }
    return tmp_b4;
  }
  return false;
}

int luaO_pushvfstring(int param_1,char *param_2,int *param_3)
{
  int tmp_i1;
  uint64_t tmp_u2;
  char tmp_c3;
  char tmp_c4;
  uint32_t tmp_u5;
  char *tmp_pc6;
  uint tmp_u7;
  uint tmp_u8;
  size_t tmp_s9;
  uint *tmp_pu10;
  uint *tmp_pu11;
  uint8_t *tmp_pu12;
  uint *tmp_pu13;
  char *tmp_pc14;
  char *__s;
  uint32_t *tmp_pu15;
  int tmp_i16;
  int *local_4c;
  int local_48;
  uint32_t local_34;
  uint32_t uStack_14;
  
  uStack_14 = 0x229b9b;
  tmp_pu15 = *(uint32_t **)(param_1 + 8);
  tmp_u5 = luaS_newlstr(param_1,&g_unk_0026ea14,0);
  tmp_pu15[2] = 4;
  *tmp_pu15 = tmp_u5;
  tmp_i16 = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 0x1c) - tmp_i16 < 0xd) {
    luaD_growstack(param_1,1);
    tmp_i16 = *(int *)(param_1 + 8);
  }
  tmp_pu15 = (uint32_t *)(tmp_i16 + 0xc);
  local_48 = 1;
  *(uint32_t **)(param_1 + 8) = tmp_pu15;
  do {
    tmp_pc6 = strchr(param_2,0x25);
    if (tmp_pc6 == (char *)0x0) {
      tmp_s9 = strlen(param_2);
      tmp_u5 = luaS_newlstr(param_1,param_2,tmp_s9);
      tmp_pu15[2] = 4;
      *tmp_pu15 = tmp_u5;
      tmp_i16 = *(int *)(param_1 + 8);
      if (*(int *)(param_1 + 0x1c) - tmp_i16 < 0xd) {
        luaD_growstack(param_1,1);
        tmp_i16 = *(int *)(param_1 + 8);
      }
      *(int *)(param_1 + 8) = tmp_i16 + 0xc;
      luaV_concat(param_1,local_48 + 1,
                  ((tmp_i16 + 0xc) - *(int *)(param_1 + 0xc) >> 2) * -0x55555555 + -1);
      tmp_i16 = *(int *)(param_1 + 8) + local_48 * -0xc;
      *(int *)(param_1 + 8) = tmp_i16;
      return *(int *)(tmp_i16 + -0xc) + 0x10;
    }
    tmp_u5 = luaS_newlstr(param_1,param_2,(int)tmp_pc6 - (int)param_2);
    tmp_pu15[2] = 4;
    *tmp_pu15 = tmp_u5;
    tmp_i16 = *(int *)(param_1 + 8);
    if (*(int *)(param_1 + 0x1c) - tmp_i16 < 0xd) {
      luaD_growstack(param_1,1);
      tmp_i16 = *(int *)(param_1 + 8);
      *(int *)(param_1 + 8) = tmp_i16 + 0xc;
      tmp_c4 = tmp_pc6[1];
      tmp_c3 = tmp_c4 + -100;
      if (tmp_c3 == '\0') goto LAB_00229e1e;
LAB_00229d2f:
      if (SBORROW1(tmp_c4,'d') == tmp_c3 < '\0') {
        if (tmp_c4 != 'p') {
          if (tmp_c4 == 's') {
            __s = (char *)*param_3;
            if ((uint *)__s == (uint *)0x0) {
              tmp_pc14 = (char *)0x6;
              __s = "(null)";
            }
            else {
              tmp_pc14 = (char *)strlen(__s);
            }
            goto LAB_00229da6;
          }
          if (tmp_c4 != 'f') goto LAB_00229c30;
          tmp_u2 = *(uint64_t *)param_3;
          param_3 = param_3 + 2;
          *(uint64_t *)(tmp_i16 + 0xc) = tmp_u2;
          goto LAB_00229f28;
        }
        sprintf((char *)&local_34,"%p",*param_3);
        tmp_pu15 = *(uint32_t **)(param_1 + 8);
        tmp_pu13 = &local_34;
        do {
          tmp_pu11 = tmp_pu13;
          tmp_u7 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
          tmp_u8 = tmp_u7 & 0x80808080;
          tmp_pu13 = tmp_pu11 + 1;
        } while (tmp_u8 == 0);
        if ((tmp_u7 & 0x8080) == 0) {
          tmp_pu13 = (uint *)((int)tmp_pu11 + 6);
          tmp_u8 = tmp_u8 >> 0x10;
        }
        tmp_u5 = luaS_newlstr(param_1,&local_34,
                             (char *)((int)tmp_pu13 +
                                     ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)&local_34)
                                     ));
        tmp_pu15[2] = 4;
        *tmp_pu15 = tmp_u5;
LAB_00229dc0:
        local_4c = param_3 + 1;
        tmp_i16 = *(int *)(param_1 + 8);
        if (*(int *)(param_1 + 0x1c) - tmp_i16 < 0xd) {
          luaD_growstack(param_1,1);
          tmp_i16 = *(int *)(param_1 + 8);
        }
        param_3 = local_4c;
        tmp_pu15 = (uint32_t *)(tmp_i16 + 0xc);
        *(uint32_t **)(param_1 + 8) = tmp_pu15;
      }
      else {
        if (tmp_c4 == '%') {
          tmp_pu12 = (uint8_t *)0x1;
          tmp_pu13 = (uint *)&g_unk_002603d7;
        }
        else {
          if (tmp_c4 == 'c') {
            __s = (char *)&local_34;
            GHIDRA_FIELD(local_34, 1, 1) = '\0';
            GHIDRA_FIELD(local_34, 0, 1) = (char)*param_3;
            tmp_pu13 = (uint *)__s;
            do {
              tmp_pu11 = tmp_pu13;
              tmp_u7 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
              tmp_u8 = tmp_u7 & 0x80808080;
              tmp_pu13 = tmp_pu11 + 1;
            } while (tmp_u8 == 0);
            if ((tmp_u7 & 0x8080) == 0) {
              tmp_pu13 = (uint *)((int)tmp_pu11 + 6);
              tmp_u8 = tmp_u8 >> 0x10;
            }
            tmp_pc14 = (char *)((int)tmp_pu13 +
                              ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)__s));
LAB_00229da6:
            tmp_u5 = luaS_newlstr(param_1,__s,tmp_pc14);
            *(uint32_t *)(tmp_i16 + 0x14) = 4;
            *(uint32_t *)(tmp_i16 + 0xc) = tmp_u5;
            goto LAB_00229dc0;
          }
LAB_00229c30:
          tmp_pu13 = &local_34;
          GHIDRA_FIELD(local_34, 0, 1) = 0x25;
          GHIDRA_FIELD(local_34, 1, 1) = tmp_c4;
          GHIDRA_FIELD(local_34, 2, 1) = 0;
          tmp_pu11 = tmp_pu13;
          do {
            tmp_pu10 = tmp_pu11;
            tmp_u7 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
            tmp_u8 = tmp_u7 & 0x80808080;
            tmp_pu11 = tmp_pu10 + 1;
          } while (tmp_u8 == 0);
          if ((tmp_u7 & 0x8080) == 0) {
            tmp_pu11 = (uint *)((int)tmp_pu10 + 6);
            tmp_u8 = tmp_u8 >> 0x10;
          }
          tmp_pu12 = (uint8_t *)
                    ((int)tmp_pu11 + ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)tmp_pu13));
        }
        tmp_u5 = luaS_newlstr(param_1,tmp_pu13,tmp_pu12);
        *(uint32_t *)(tmp_i16 + 0x14) = 4;
        *(uint32_t *)(tmp_i16 + 0xc) = tmp_u5;
        tmp_i16 = *(int *)(param_1 + 8);
        if (*(int *)(param_1 + 0x1c) - tmp_i16 < 0xd) {
          luaD_growstack(param_1,1);
          tmp_i16 = *(int *)(param_1 + 8);
        }
        tmp_pu15 = (uint32_t *)(tmp_i16 + 0xc);
        *(uint32_t **)(param_1 + 8) = tmp_pu15;
      }
    }
    else {
      *(int *)(param_1 + 8) = tmp_i16 + 0xc;
      tmp_c4 = tmp_pc6[1];
      tmp_c3 = tmp_c4 + -100;
      if (tmp_c4 != 'd') goto LAB_00229d2f;
LAB_00229e1e:
      tmp_i1 = *param_3;
      param_3 = param_3 + 1;
      *(double *)(tmp_i16 + 0xc) = (double)tmp_i1;
LAB_00229f28:
      *(uint32_t *)(tmp_i16 + 0x14) = 3;
      tmp_i16 = *(int *)(param_1 + 8);
      if (*(int *)(param_1 + 0x1c) - tmp_i16 < 0xd) {
        luaD_growstack(param_1,1);
        tmp_i16 = *(int *)(param_1 + 8);
      }
      tmp_pu15 = (uint32_t *)(tmp_i16 + 0xc);
      *(uint32_t **)(param_1 + 8) = tmp_pu15;
    }
    local_48 = local_48 + 2;
    param_2 = tmp_pc6 + 2;
  } while( true );
}

void luaO_pushfstring(uint32_t param_1,uint32_t param_2)
{
  luaO_pushvfstring(param_1,param_2,&stack0x0000000c);
  return;
}

void luaO_chunkid(char *param_1,char *param_2,size_t param_3)
{
  char tmp_c1;
  size_t tmp_s2;
  uint __n;
  
  tmp_c1 = *param_2;
  if (tmp_c1 == '=') {
    strncpy(param_1,param_2 + 1,param_3);
    param_1[param_3 - 1] = '\0';
  }
  else {
    if (tmp_c1 == '@') {
      param_2 = param_2 + 1;
      tmp_s2 = strlen(param_2);
      *param_1 = '\0';
      if (param_3 - 8 < tmp_s2) {
        param_2 = param_2 + (tmp_s2 - (param_3 - 8));
        *(uint8_t **)param_1 = &g_unk_002e2e2e;
      }
      strcat(param_1,param_2);
      return;
    }
    __n = 0;
    if (((tmp_c1 != '\0') && (tmp_c1 != '\n')) && (tmp_c1 != '\r')) {
      do {
        __n = __n + 1;
        tmp_c1 = param_2[__n];
        if ((tmp_c1 == '\0') || (tmp_c1 == '\n')) break;
      } while (tmp_c1 != '\r');
      if (param_3 - 0x11 < __n) {
        __n = param_3 - 0x11;
      }
    }
    builtin_strncpy(param_1,"[string \"",10);
    if (param_2[__n] == '\0') {
      strcpy(param_1 + 9,param_2);
    }
    else {
      strncat(param_1,param_2,__n);
      tmp_s2 = strlen(param_1);
      *(uint8_t **)(param_1 + tmp_s2) = &g_unk_002e2e2e;
    }
    tmp_s2 = strlen(param_1);
    param_1 = param_1 + tmp_s2;
    param_1[0] = '\"';
    param_1[1] = ']';
    param_1[2] = '\0';
  }
  return;
}

int luaE_newthread(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i3 = luaM_realloc_(param_1,0,0,0x70);
  luaC_link(param_1,tmp_i3,8);
  tmp_u1 = *(uint32_t *)(param_1 + 0x10);
  *(uint32_t *)(tmp_i3 + 0x20) = 0;
  *(uint32_t *)(tmp_i3 + 0x2c) = 0;
  *(uint32_t *)(tmp_i3 + 0x68) = 0;
  *(uint32_t *)(tmp_i3 + 0x10) = tmp_u1;
  *(uint32_t *)(tmp_i3 + 0x44) = 0;
  *(uint8_t *)(tmp_i3 + 0x38) = 0;
  *(uint32_t *)(tmp_i3 + 0x3c) = 0;
  *(uint8_t *)(tmp_i3 + 0x39) = 1;
  *(uint32_t *)(tmp_i3 + 0x40) = 0;
  *(uint32_t *)(tmp_i3 + 0x60) = 0;
  *(uint32_t *)(tmp_i3 + 0x30) = 0;
  *(uint16_t *)(tmp_i3 + 0x36) = 0;
  *(uint16_t *)(tmp_i3 + 0x34) = 0;
  *(uint8_t *)(tmp_i3 + 6) = 0;
  *(uint32_t *)(tmp_i3 + 0x14) = 0;
  *(uint32_t *)(tmp_i3 + 0x28) = 0;
  *(uint32_t *)(tmp_i3 + 0x18) = 0;
  *(uint32_t *)(tmp_i3 + 0x6c) = 0;
  *(uint32_t *)(tmp_i3 + 0x50) = 0;
  tmp_i4 = luaM_realloc_(param_1,0,0,0xc0);
  *(uint32_t *)(tmp_i3 + 0x30) = 8;
  *(int *)(tmp_i3 + 0x28) = tmp_i4;
  *(int *)(tmp_i3 + 0x14) = tmp_i4;
  *(int *)(tmp_i3 + 0x24) = tmp_i4 + 0xa8;
  tmp_i4 = luaM_realloc_(param_1,0,0,0x21c);
  *(uint32_t *)(tmp_i3 + 0x2c) = 0x2d;
  *(int *)(tmp_i3 + 0x1c) = tmp_i4 + 0x1d4;
  *(int *)(tmp_i3 + 8) = tmp_i4;
  *(int *)(tmp_i3 + 0x20) = tmp_i4;
  *(int *)(*(int *)(tmp_i3 + 0x14) + 4) = tmp_i4;
  tmp_i4 = *(int *)(tmp_i3 + 8);
  *(int *)(tmp_i3 + 8) = tmp_i4 + 0xc;
  *(uint32_t *)(tmp_i4 + 8) = 0;
  tmp_u1 = *(uint32_t *)(tmp_i3 + 8);
  **(uint32_t **)(tmp_i3 + 0x14) = tmp_u1;
  *(uint32_t *)(tmp_i3 + 0xc) = tmp_u1;
  *(int *)(*(int *)(tmp_i3 + 0x14) + 8) = *(int *)(tmp_i3 + 8) + 0xf0;
  tmp_u1 = *(uint32_t *)(param_1 + 0x4c);
  *(uint32_t *)(tmp_i3 + 0x48) = *(uint32_t *)(param_1 + 0x48);
  *(uint32_t *)(tmp_i3 + 0x4c) = tmp_u1;
  *(uint32_t *)(tmp_i3 + 0x50) = *(uint32_t *)(param_1 + 0x50);
  *(uint8_t *)(tmp_i3 + 0x38) = *(uint8_t *)(param_1 + 0x38);
  tmp_u1 = *(uint32_t *)(param_1 + 0x3c);
  *(uint32_t *)(tmp_i3 + 0x3c) = tmp_u1;
  tmp_u2 = *(uint32_t *)(param_1 + 0x44);
  *(uint32_t *)(tmp_i3 + 0x40) = tmp_u1;
  *(uint32_t *)(tmp_i3 + 0x44) = tmp_u2;
  return tmp_i3;
}

void luaE_freethread(uint32_t param_1,int param_2)
{
  luaF_close(param_2,*(uint32_t *)(param_2 + 0x20));
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 0x28),*(int *)(param_2 + 0x30) * 0x18,0);
  luaM_realloc_(param_1,*(uint32_t *)(param_2 + 0x20),*(int *)(param_2 + 0x2c) * 0xc,0);
  luaM_realloc_(param_1,param_2,0x70,0);
  return;
}

uint32_t * lua_newstate(void *param_1,uint32_t param_2)
{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  bool tmp_b6;
  
  tmp_pu1 = (uint32_t *)(*param_1)(param_2,0,0,0x15c);
  if (tmp_pu1 == (uint32_t *)0x0) {
    tmp_pu1 = (uint32_t *)0x0;
  }
  else {
    *tmp_pu1 = 0;
    *(uint8_t *)(tmp_pu1 + 1) = 8;
    *(uint8_t *)(tmp_pu1 + 0x21) = 0x21;
    *(uint8_t *)((int)tmp_pu1 + 5) = 0x61;
    tmp_pu1[4] = tmp_pu1 + 0x1c;
    tmp_pu1[0x3a] = tmp_pu1 + 0x37;
    tmp_pu1[0x3b] = tmp_pu1 + 0x37;
    tmp_pu1[0x2c] = 0;
    tmp_pu1[0x35] = 0;
    tmp_pu1[0x1f] = param_1;
    tmp_pu1[0x20] = param_2;
    tmp_pu1[8] = 0;
    tmp_pu1[0xb] = 0;
    tmp_pu1[0x1a] = 0;
    tmp_pu1[0x11] = 0;
    *(uint8_t *)(tmp_pu1 + 0xe) = 0;
    tmp_pu1[0xf] = 0;
    *(uint8_t *)((int)tmp_pu1 + 0x39) = 1;
    tmp_pu1[0x10] = 0;
    tmp_pu1[0x18] = 0;
    tmp_pu1[0xc] = 0;
    *(uint16_t *)((int)tmp_pu1 + 0x36) = 0;
    *(uint16_t *)(tmp_pu1 + 0xd) = 0;
    *(uint8_t *)((int)tmp_pu1 + 6) = 0;
    tmp_pu1[5] = 0;
    tmp_pu1[10] = 0;
    tmp_pu1[6] = 0;
    tmp_pu1[0x1b] = 0;
    tmp_pu1[0x14] = 0;
    tmp_pu1[0x36] = tmp_pu1;
    tmp_pu1[0x1e] = 0;
    tmp_pu1[0x1d] = 0;
    tmp_pu1[0x1c] = 0;
    tmp_pu1[0x29] = 0;
    tmp_pu1[0x2b] = 0;
    tmp_pu1[0x32] = 0;
    tmp_pu1[0x22] = 0;
    tmp_pu1[0x24] = tmp_pu1 + 0x23;
    tmp_pu1[0x2d] = 0x15c;
    tmp_pu1[0x30] = 200;
    tmp_pu1[0x31] = 200;
    tmp_pu1[0x2f] = 0;
    tmp_pu2 = tmp_pu1 + 0x3d;
    tmp_b6 = ((uint)tmp_pu2 & 1) != 0;
    tmp_pu1[0x26] = 0;
    tmp_u4 = 0x24;
    *(uint8_t *)((int)tmp_pu1 + 0x85) = 0;
    tmp_pu1[0x23] = tmp_pu1;
    tmp_pu1[0x25] = 0;
    tmp_pu1[0x27] = 0;
    tmp_pu1[0x28] = 0;
    if (tmp_b6) {
      *(uint8_t *)(tmp_pu1 + 0x3d) = 0;
      tmp_pu2 = (uint32_t *)((int)tmp_pu1 + 0xf5);
      tmp_u4 = 0x23;
    }
    if (((uint)tmp_pu2 & 2) != 0) {
      *(uint16_t *)tmp_pu2 = 0;
      tmp_u4 = tmp_u4 - 2;
      tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
    }
    tmp_u5 = 0;
    do {
      *(uint32_t *)((int)tmp_pu2 + tmp_u5) = 0;
      *(uint32_t *)((int)tmp_pu2 + tmp_u5 + 4) = 0;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < (tmp_u4 & 0xfffffff8));
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + tmp_u5);
    if ((tmp_u4 & 4) != 0) {
      *tmp_pu2 = 0;
      tmp_pu2 = tmp_pu2 + 1;
    }
    if ((tmp_u4 & 2) != 0) {
      *(uint16_t *)tmp_pu2 = 0;
      tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
    }
    if (tmp_b6) {
      *(uint8_t *)tmp_pu2 = 0;
    }
    tmp_i3 = luaD_rawrunprotected(tmp_pu1,f_luaopen,0);
    if (tmp_i3 != 0) {
      close_state();
      return (uint32_t *)0x0;
    }
  }
  return tmp_pu1;
}

void lua_close(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_i1 = *(int *)(*(int *)(param_1 + 0x10) + 0x68);
  luaF_close(tmp_i1,*(uint32_t *)(tmp_i1 + 0x20));
  luaC_separateudata(tmp_i1,1);
  *(uint32_t *)(tmp_i1 + 0x6c) = 0;
  do {
    *(uint32_t **)(tmp_i1 + 0x14) = *(uint32_t **)(tmp_i1 + 0x28);
    tmp_u2 = **(uint32_t **)(tmp_i1 + 0x28);
    *(uint16_t *)(tmp_i1 + 0x36) = 0;
    *(uint16_t *)(tmp_i1 + 0x34) = 0;
    *(uint32_t *)(tmp_i1 + 8) = tmp_u2;
    *(uint32_t *)(tmp_i1 + 0xc) = tmp_u2;
    tmp_i3 = luaD_rawrunprotected(tmp_i1,callallgcTM,0);
  } while (tmp_i3 != 0);
  close_state();
  return;
}

uint32_t luaopen_io(uint32_t param_1)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  
  luaL_newmetatable(param_1,"FILE*");
  lua_pushvalue(param_1,0xffffffff);
  lua_setfield(param_1,0xfffffffe,"__index");
  luaL_register(param_1,0,flib);
  lua_createtable(param_1,0,1);
  lua_pushcclosure(param_1,io_fclose,0);
  lua_setfield(param_1,0xfffffffe,"__close");
  lua_replace(param_1,0xffffd8ef);
  luaL_register(param_1,"io",iolib);
  lua_createtable(param_1,0,1);
  lua_pushcclosure(param_1,io_noclose,0);
  lua_setfield(param_1,0xfffffffe,"__close");
  tmp_u1 = _stdin;
  tmp_pu2 = (uint32_t *)lua_newuserdata(param_1,4);
  *tmp_pu2 = 0;
  lua_getfield(param_1,0xffffd8f0,"FILE*");
  lua_setmetatable(param_1,0xfffffffe);
  *tmp_pu2 = tmp_u1;
  lua_pushvalue(param_1,0xffffffff);
  lua_rawseti(param_1,0xffffd8ef,1);
  lua_pushvalue(param_1,0xfffffffe);
  lua_setfenv(param_1,0xfffffffe);
  lua_setfield(param_1,0xfffffffd,"stdin");
  tmp_u1 = _stdout;
  tmp_pu2 = (uint32_t *)lua_newuserdata(param_1,4);
  *tmp_pu2 = 0;
  lua_getfield(param_1,0xffffd8f0,"FILE*");
  lua_setmetatable(param_1,0xfffffffe);
  *tmp_pu2 = tmp_u1;
  lua_pushvalue(param_1,0xffffffff);
  lua_rawseti(param_1,0xffffd8ef,2);
  lua_pushvalue(param_1,0xfffffffe);
  lua_setfenv(param_1,0xfffffffe);
  lua_setfield(param_1,0xfffffffd,"stdout");
  tmp_u1 = _stderr;
  tmp_pu2 = (uint32_t *)lua_newuserdata(param_1,4);
  *tmp_pu2 = 0;
  lua_getfield(param_1,0xffffd8f0,"FILE*");
  lua_setmetatable(param_1,0xfffffffe);
  *tmp_pu2 = tmp_u1;
  lua_pushvalue(param_1,0xfffffffe);
  lua_setfenv(param_1,0xfffffffe);
  lua_setfield(param_1,0xfffffffd,"stderr");
  lua_settop(param_1,0xfffffffe);
  lua_getfield(param_1,0xffffffff,"popen");
  lua_createtable(param_1,0,1);
  lua_pushcclosure(param_1,io_pclose,0);
  lua_setfield(param_1,0xfffffffe,"__close");
  lua_setfenv(param_1,0xfffffffe);
  lua_settop(param_1,0xfffffffe);
  return 1;
}

void luaU_undump(uint32_t param_1,uint32_t param_2,uint32_t param_3,char *param_4)
{
  char tmp_c1;
  int tmp_i2;
  uint32_t local_34;
  uint8_t local_30;
  uint8_t local_2f;
  uint8_t local_2e;
  uint8_t local_2d;
  uint8_t local_2c;
  uint8_t local_2b;
  uint8_t local_2a;
  uint8_t local_29;
  uint8_t local_28 [12];
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  char *local_10;
  
  tmp_c1 = *param_4;
  if ((tmp_c1 == '=') || (tmp_c1 == '@')) {
    local_10 = param_4 + 1;
  }
  else if (tmp_c1 == '\x1b') {
    local_10 = "binary string";
  }
  else {
    local_10 = param_4;
  }
  local_1c = param_1;
  local_14 = param_3;
  local_34 = 0x61754c1b;
  local_18 = param_2;
  local_30 = 0x51;
  local_2f = 0;
  local_2e = 1;
  local_2d = 4;
  local_2c = 4;
  local_2b = 4;
  local_2a = 8;
  local_29 = 0;
  tmp_i2 = luaZ_read(param_2,local_28,0xc);
  if (tmp_i2 != 0) {
    luaO_pushfstring(local_1c,"%s: %s in precompiled chunk",local_10,"unexpected end");
    luaD_throw(local_1c,3);
  }
  tmp_i2 = memcmp(&local_34,local_28,0xc);
  if (tmp_i2 != 0) {
    luaO_pushfstring(local_1c,"%s: %s in precompiled chunk",local_10,"bad header");
    luaD_throw(local_1c,3);
  }
  luaS_newlstr(param_1,&g_unk_0025fdd8,2);
  LoadFunction();
  return;
}

void luaU_header(uint32_t *param_1)
{
  *param_1 = 0x61754c1b;
  *(uint8_t *)(param_1 + 1) = 0x51;
  *(uint8_t *)((int)param_1 + 5) = 0;
  *(uint8_t *)((int)param_1 + 6) = 1;
  *(uint8_t *)((int)param_1 + 7) = 4;
  *(uint8_t *)(param_1 + 2) = 4;
  *(uint8_t *)((int)param_1 + 9) = 4;
  *(uint8_t *)((int)param_1 + 10) = 8;
  *(uint8_t *)((int)param_1 + 0xb) = 0;
  return;
}

