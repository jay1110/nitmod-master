/* db_* persistence helpers — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_database.h"

uint32_t db_setmetatable(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = lua_type(param_1,2);
  if ((tmp_i1 != 5) && (tmp_i1 != 0)) {
    luaL_argerror(param_1,2,"nil or table expected");
  }
  lua_settop(param_1,2);
  tmp_u2 = lua_setmetatable(param_1,1);
  lua_pushboolean(param_1,tmp_u2);
  return 1;
}

uint32_t db_getregistry(uint32_t param_1)
{
  lua_pushvalue(param_1,0xffffd8f0);
  return 1;
}

uint32_t db_setfenv(uint32_t param_1)
{
  int tmp_i1;
  
  luaL_checktype(param_1,2,5);
  lua_settop(param_1,2);
  tmp_i1 = lua_setfenv(param_1,1);
  if (tmp_i1 == 0) {
    luaL_error(param_1,"\'setfenv\' cannot change environment of given object");
  }
  return 1;
}

uint32_t db_getmetatable(uint32_t param_1)
{
  int tmp_i1;
  
  luaL_checkany(param_1,1);
  tmp_i1 = lua_getmetatable(param_1,1);
  if (tmp_i1 == 0) {
    lua_pushnil(param_1);
  }
  return 1;
}

uint32_t db_getfenv(uint32_t param_1)
{
  lua_getfenv(param_1,1);
  return 1;
}

uint32_t db_debug(uint32_t param_1)
{
  FILE *__stream;
  size_t tmp_s1;
  char *tmp_pc2;
  int tmp_i3;
  char *tmp_pc4;
  bool tmp_b5;
  byte tmp_b6;
  char local_116 [258];
  uint32_t uStack_14;
  
  tmp_b6 = 0;
  uStack_14 = 0x21de69;
  do {
    fwrite("lua_debug> ",1,0xb,_stderr);
    tmp_pc2 = fgets(local_116,0xfa,_stdin);
    if (tmp_pc2 == (char *)0x0) {
      return 0;
    }
    tmp_i3 = 6;
    tmp_b5 = false;
    tmp_pc2 = local_116;
    tmp_pc4 = "cont\n";
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b5 = *tmp_pc2 == *tmp_pc4;
      tmp_pc2 = tmp_pc2 + (uint)tmp_b6 * -2 + 1;
      tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
    } while (tmp_b5);
    if (tmp_b5) {
      return 0;
    }
    tmp_s1 = strlen(local_116);
    tmp_i3 = luaL_loadbuffer(param_1,local_116,tmp_s1,"=(debug command)");
    if ((tmp_i3 != 0) || (tmp_i3 = lua_pcall(param_1,0,0,0), tmp_i3 != 0)) {
      __stream = _stderr;
      tmp_pc2 = (char *)lua_tolstring(param_1,0xffffffff,0);
      fputs(tmp_pc2,__stream);
      fputc(10,_stderr);
    }
    lua_settop(param_1,0);
  } while( true );
}

uint32_t db_getupvalue(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = luaL_checkinteger(param_1,2);
  luaL_checktype(param_1,1,6);
  tmp_i2 = lua_iscfunction(param_1,1);
  if (tmp_i2 == 0) {
    tmp_i2 = lua_getupvalue(param_1,1,tmp_u1);
    if (tmp_i2 != 0) {
      lua_pushstring(param_1,tmp_i2);
      lua_insert(param_1,0xfffffffe);
      return 2;
    }
  }
  return 0;
}

uint32_t db_setupvalue(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  luaL_checkany(param_1,3);
  tmp_u1 = luaL_checkinteger(param_1,2);
  luaL_checktype(param_1,1,6);
  tmp_i2 = lua_iscfunction(param_1,1);
  if (tmp_i2 == 0) {
    tmp_i2 = lua_setupvalue(param_1,1,tmp_u1);
    if (tmp_i2 != 0) {
      lua_pushstring(param_1,tmp_i2);
      lua_insert(param_1,0xffffffff);
      return 1;
    }
  }
  return 0;
}

uint32_t db_getlocal(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t local_90;
  uint8_t local_80 [112];
  
  tmp_i1 = lua_type(param_1,1);
  if (tmp_i1 == 8) {
    tmp_u3 = lua_tothread(param_1,1);
    tmp_u4 = 2;
    local_90 = 3;
  }
  else {
    local_90 = 2;
    tmp_u4 = 1;
    tmp_u3 = param_1;
  }
  tmp_u2 = luaL_checkinteger(param_1,tmp_u4);
  tmp_i1 = lua_getstack(tmp_u3,tmp_u2,local_80);
  if (tmp_i1 == 0) {
    tmp_u3 = luaL_argerror(param_1,tmp_u4,"level out of range");
  }
  else {
    tmp_u4 = luaL_checkinteger(param_1,local_90);
    tmp_i1 = lua_getlocal(tmp_u3,local_80,tmp_u4);
    if (tmp_i1 == 0) {
      lua_pushnil(param_1);
      tmp_u3 = 1;
    }
    else {
      lua_xmove(tmp_u3,param_1,1);
      lua_pushstring(param_1,tmp_i1);
      lua_pushvalue(param_1,0xfffffffe);
      tmp_u3 = 2;
    }
  }
  return tmp_u3;
}

uint32_t db_setlocal(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t local_98;
  uint32_t local_90;
  uint8_t local_80 [112];
  
  tmp_i1 = lua_type(param_1,1);
  if (tmp_i1 == 8) {
    tmp_u3 = lua_tothread(param_1,1);
    tmp_u4 = 2;
    local_90 = 3;
    local_98 = 4;
  }
  else {
    local_90 = 2;
    tmp_u4 = 1;
    local_98 = 3;
    tmp_u3 = param_1;
  }
  tmp_u2 = luaL_checkinteger(param_1,tmp_u4);
  tmp_i1 = lua_getstack(tmp_u3,tmp_u2,local_80);
  if (tmp_i1 == 0) {
    tmp_u3 = luaL_argerror(param_1,tmp_u4,"level out of range");
  }
  else {
    luaL_checkany(param_1,local_98);
    lua_settop(param_1,local_98);
    lua_xmove(param_1,tmp_u3,1);
    tmp_u4 = luaL_checkinteger(param_1,local_90);
    tmp_u3 = lua_setlocal(tmp_u3,local_80,tmp_u4);
    lua_pushstring(param_1,tmp_u3);
    tmp_u3 = 1;
  }
  return tmp_u3;
}

uint32_t db_getinfo(int param_1)
{
  int tmp_i1;
  char *tmp_pc2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int local_94;
  uint32_t local_90;
  uint8_t local_80 [4];
  uint32_t local_7c;
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint8_t local_5c [76];
  
  tmp_i1 = lua_type(param_1,1);
  if (tmp_i1 == 8) {
    tmp_u4 = 2;
    local_94 = lua_tothread(param_1,1);
    local_90 = 3;
  }
  else {
    tmp_u4 = 1;
    local_94 = param_1;
    local_90 = 2;
  }
  tmp_pc2 = (char *)luaL_optlstring(param_1,local_90,"flnSu",0);
  tmp_i1 = lua_isnumber(param_1,tmp_u4);
  if (tmp_i1 == 0) {
    tmp_i1 = lua_type(param_1,tmp_u4);
    if (tmp_i1 != 6) {
      tmp_u4 = luaL_argerror(param_1,tmp_u4,"function or level expected");
      return tmp_u4;
    }
    lua_pushfstring(param_1,&g_unk_0026f685,tmp_pc2);
    tmp_pc2 = (char *)lua_tolstring(param_1,0xffffffff,0);
    lua_pushvalue(param_1,tmp_u4);
    lua_xmove(param_1,local_94,1);
  }
  else {
    tmp_u4 = lua_tointeger();
    tmp_i1 = lua_getstack(local_94,tmp_u4,local_80);
    if (tmp_i1 == 0) {
      lua_pushnil(param_1);
      return 1;
    }
  }
  tmp_i1 = lua_getinfo(local_94,tmp_pc2,local_80);
  if (tmp_i1 == 0) {
    tmp_u4 = luaL_argerror(param_1,local_90,"invalid option");
    return tmp_u4;
  }
  lua_createtable(param_1,0,2);
  tmp_pc3 = strchr(tmp_pc2,0x53);
  if (tmp_pc3 != (char *)0x0) {
    lua_pushstring(param_1,local_70);
    lua_setfield(param_1,0xfffffffe,"source");
    lua_pushstring(param_1,local_5c);
    lua_setfield(param_1,0xfffffffe,"short_src");
    lua_pushinteger(param_1,local_64);
    lua_setfield(param_1,0xfffffffe,"linedefined");
    lua_pushinteger(param_1,local_60);
    lua_setfield(param_1,0xfffffffe,"lastlinedefined");
    lua_pushstring(param_1,local_74);
    lua_setfield(param_1,0xfffffffe,"what");
  }
  tmp_pc3 = strchr(tmp_pc2,0x6c);
  if (tmp_pc3 != (char *)0x0) {
    lua_pushinteger(param_1,local_6c);
    lua_setfield(param_1,0xfffffffe,"currentline");
  }
  tmp_pc3 = strchr(tmp_pc2,0x75);
  if (tmp_pc3 != (char *)0x0) {
    lua_pushinteger(param_1,local_68);
    lua_setfield(param_1,0xfffffffe,&g_unk_0026f6e0);
  }
  tmp_pc3 = strchr(tmp_pc2,0x6e);
  if (tmp_pc3 != (char *)0x0) {
    lua_pushstring(param_1,local_7c);
    lua_setfield(param_1,0xfffffffe,"name");
    lua_pushstring(param_1,local_78);
    lua_setfield(param_1,0xfffffffe,"namewhat");
  }
  tmp_pc3 = strchr(tmp_pc2,0x4c);
  if (tmp_pc3 != (char *)0x0) {
    if (param_1 == local_94) {
      lua_pushvalue(param_1,0xfffffffe);
      lua_remove(param_1,0xfffffffd);
    }
    else {
      lua_xmove(local_94,param_1,1);
    }
    lua_setfield(param_1,0xfffffffe,"activelines");
  }
  tmp_pc2 = strchr(tmp_pc2,0x66);
  if (tmp_pc2 != (char *)0x0) {
    if (param_1 == local_94) {
      lua_pushvalue(param_1,0xfffffffe);
      lua_remove(param_1,0xfffffffd);
    }
    else {
      lua_xmove(local_94,param_1,1);
    }
    lua_setfield(param_1,0xfffffffe,&g_unk_0026f6fa);
  }
  return 1;
}

uint32_t db_sethook(uint32_t param_1)
{
  int tmp_i1;
  char *tmp_pc2;
  char *tmp_pc3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  byte tmp_b6;
  uint32_t tmp_u7;
  uint32_t local_2c;
  int local_28;
  void *local_24;
  uint32_t local_20;
  
  tmp_i1 = lua_type(param_1,1);
  if (tmp_i1 == 8) {
    tmp_u5 = 3;
    tmp_u7 = 4;
    local_20 = lua_tothread(param_1,1);
    local_2c = 2;
  }
  else {
    tmp_u7 = 3;
    local_20 = param_1;
    tmp_u5 = 2;
    local_2c = 1;
  }
  tmp_i1 = lua_type(param_1,local_2c);
  if (tmp_i1 < 1) {
    tmp_b6 = 0;
    lua_settop(param_1,local_2c);
    local_24 = (void *)0x0;
    local_28 = 0;
  }
  else {
    tmp_pc2 = (char *)luaL_checklstring(param_1,tmp_u5,0);
    luaL_checktype(param_1,local_2c,6);
    local_28 = luaL_optinteger(param_1,tmp_u7,0);
    tmp_pc3 = strchr(tmp_pc2,99);
    tmp_pc4 = strchr(tmp_pc2,0x72);
    tmp_b6 = tmp_pc3 != (char *)0x0;
    if (tmp_pc4 != (char *)0x0) {
      tmp_b6 = tmp_pc3 != (char *)0x0 | 2;
    }
    tmp_pc2 = strchr(tmp_pc2,0x6c);
    if (tmp_pc2 != (char *)0x0) {
      tmp_b6 = tmp_b6 | 4;
    }
    if (local_28 < 1) {
      local_24 = hookf;
    }
    else {
      local_24 = hookf;
      tmp_b6 = tmp_b6 | 8;
    }
  }
  lua_pushlightuserdata(param_1,"hupvalues");
  lua_rawget(param_1,0xffffd8f0);
  tmp_i1 = lua_type(param_1,0xffffffff);
  if (tmp_i1 != 5) {
    lua_settop(param_1,0xfffffffe);
    lua_createtable(param_1,0,1);
    lua_pushlightuserdata(param_1,"hupvalues");
    lua_pushvalue(param_1,0xfffffffe);
    lua_rawset(param_1,0xffffd8f0);
  }
  lua_pushlightuserdata(param_1,local_20);
  lua_pushvalue(param_1,local_2c);
  lua_rawset(param_1,0xfffffffd);
  lua_settop(param_1,0xfffffffe);
  lua_sethook(local_20,local_24,tmp_b6,local_28);
  return 0;
}

uint32_t db_gethook(uint32_t param_1)
{
  int tmp_i1;
  uint tmp_u2;
  void *tmp_pc3;
  uint8_t *tmp_pu4;
  uint32_t tmp_u5;
  uint tmp_u6;
  bool tmp_b7;
  uint local_34;
  int local_30;
  uint8_t local_21 [17];
  
  tmp_i1 = lua_type(param_1,1);
  tmp_u5 = param_1;
  if (tmp_i1 == 8) {
    tmp_u5 = lua_tothread(param_1,1);
  }
  tmp_u2 = lua_gethookmask(tmp_u5);
  tmp_pc3 = (void *)lua_gethook(tmp_u5);
  if ((tmp_pc3 == (void *)0x0) || (tmp_pc3 == hookf)) {
    lua_pushlightuserdata(param_1,"hupvalues");
    lua_rawget(param_1,0xffffd8f0);
    tmp_i1 = lua_type(param_1,0xffffffff);
    if (tmp_i1 != 5) {
      lua_settop(param_1,0xfffffffe);
      lua_createtable(param_1,0,1);
      lua_pushlightuserdata(param_1,"hupvalues");
      lua_pushvalue(param_1,0xfffffffe);
      lua_rawset(param_1,0xffffd8f0);
    }
    lua_pushlightuserdata(param_1,tmp_u5);
    lua_rawget(param_1,0xfffffffe);
    lua_remove(param_1,0xfffffffe);
  }
  else {
    lua_pushlstring(param_1,"external hook",0xd);
  }
  tmp_b7 = (tmp_u2 & 1) == 0;
  if (tmp_b7) {
    local_34 = 1;
    tmp_pu4 = local_21;
    local_30 = 1;
  }
  else {
    local_30 = 2;
    local_34 = 2;
    tmp_pu4 = local_21 + 1;
    local_21[0] = 99;
  }
  tmp_u6 = (uint)!tmp_b7;
  if ((tmp_u2 & 2) != 0) {
    *tmp_pu4 = 0x72;
    tmp_pu4 = local_21 + local_30;
    tmp_u6 = local_34;
  }
  if ((tmp_u2 & 4) != 0) {
    *tmp_pu4 = 0x6c;
    tmp_pu4 = local_21 + tmp_u6 + 1;
  }
  *tmp_pu4 = 0;
  lua_pushstring(param_1,local_21);
  tmp_u5 = lua_gethookcount(tmp_u5);
  lua_pushinteger(param_1,tmp_u5);
  return 3;
}

uint32_t db_errorfb(int param_1)
{
  char tmp_c1;
  bool tmp_b2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  uint32_t tmp_u6;
  uint tmp_u7;
  uint8_t *tmp_pu8;
  uint local_a0;
  uint local_94;
  uint8_t local_80 [4];
  uint32_t local_7c;
  char *local_78;
  char *local_74;
  uint8_t *local_6c;
  uint32_t local_64;
  uint8_t local_5c [76];
  
  tmp_i3 = lua_type(param_1,1);
  if (tmp_i3 == 8) {
    tmp_u6 = 3;
    tmp_i5 = lua_tothread(param_1,1);
  }
  else {
    tmp_u6 = 2;
    tmp_i5 = param_1;
  }
  local_94 = (uint)(tmp_i3 == 8);
  tmp_i3 = lua_isnumber(param_1,tmp_u6);
  if (tmp_i3 == 0) {
    tmp_u7 = (uint)(param_1 == tmp_i5);
    tmp_u4 = lua_gettop(param_1);
  }
  else {
    tmp_u7 = lua_tointeger(param_1,tmp_u6);
    lua_settop(param_1,0xfffffffe);
    tmp_u4 = lua_gettop(param_1);
  }
  if (tmp_u4 == local_94) {
    lua_pushlstring(param_1,&g_unk_0026ea14,0);
  }
  else {
    tmp_i3 = lua_isstring(param_1,local_94 + 1);
    if (tmp_i3 == 0) {
      return 1;
    }
    lua_pushlstring(param_1,"\n",1);
  }
  lua_pushlstring(param_1,"stack traceback:",0x10);
  tmp_b2 = true;
  local_a0 = tmp_u7 + 1;
  while (tmp_i3 = lua_getstack(tmp_i5,tmp_u7,local_80), tmp_i3 != 0) {
    if (((int)local_a0 < 0xd) || (!tmp_b2)) {
      lua_pushlstring(param_1,&g_unk_0026f724,2);
      lua_getinfo(tmp_i5,&g_unk_0026f727,local_80);
      tmp_pu8 = local_5c;
      lua_pushfstring(param_1,&g_unk_00249b56,local_5c);
      if (0 < (int)local_6c) {
        tmp_pu8 = local_6c;
        lua_pushfstring(param_1,&g_unk_0026f72b,local_6c);
      }
      if (*local_78 == '\0') {
        tmp_c1 = *local_74;
        if (tmp_c1 == 'm') {
          lua_pushfstring(param_1," in main chunk",tmp_pu8);
        }
        else if ((tmp_c1 == 't') || (tmp_c1 == 'C')) {
          lua_pushlstring(param_1,&g_unk_0026f750,2);
        }
        else {
          lua_pushfstring(param_1," in function <%s:%d>",local_5c,local_64);
        }
      }
      else {
        lua_pushfstring(param_1," in function \'%s\'",local_7c);
      }
      tmp_i3 = lua_gettop(param_1);
      lua_concat(param_1,tmp_i3 - local_94);
      tmp_u7 = local_a0;
      local_a0 = local_a0 + 1;
    }
    else {
      tmp_i3 = lua_getstack(tmp_i5,tmp_u7 + 0xb,local_80);
      tmp_b2 = false;
      if (tmp_i3 != 0) {
        lua_pushlstring(param_1,&g_unk_0026f71e,5);
        while (tmp_i3 = lua_getstack(tmp_i5,local_a0 + 10,local_80), tmp_i3 != 0) {
          local_a0 = local_a0 + 1;
        }
        tmp_b2 = false;
        tmp_u7 = local_a0;
        local_a0 = local_a0 + 1;
      }
    }
  }
  tmp_i3 = lua_gettop(param_1);
  lua_concat(param_1,tmp_i3 - local_94);
  return 1;
}

