/* Text rendering, font management
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_text.h"

void PC_String_tolower(char *param_1)

{
{  char tmp_c1;
  __int32_t **pp_Var2;
  
  tmp_c1 = *param_1;
  if (tmp_c1 != '\0') {
    pp_Var2 = __ctype_tolower_loc();
    do {
      *param_1 = (char)(*pp_Var2)[tmp_c1];
      tmp_c1 = param_1[1];
      param_1 = param_1 + 1;
    } while (tmp_c1 != '\0');
  }
  return;
}

uint8_t * BG_GetLocationString(float *param_1)

{
{  int tmp_i1;
  int tmp_i2;
  
  coord_7557 = 0;
  tmp_i1 = (int)ROUND((*param_1 - locInfo) / g_dat_0006c108);
  tmp_i2 = (int)ROUND((g_dat_0006c104 - param_1[1]) / g_dat_0006c10c);
  if (tmp_i2 < 0) {
    tmp_i2 = 0;
  }
  if (tmp_i1 < 0) {
    tmp_i1 = 0;
  }
  Com_sprintf(&coord_7557,6,"%c,%i",tmp_i1 + 0x41,tmp_i2);
  return &coord_7557;
}

uint32_t Nit_RemoveWordInString(char *param_1,char *param_2)

{
{  size_t tmp_s1;
  int tmp_i2;
  size_t tmp_s3;
  char tmp_c4;
  char *__src;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  tmp_s1 = strlen(param_2);
  tmp_c4 = *param_1;
  if (tmp_c4 != '\0') {
    tmp_s3 = 0;
    tmp_i2 = 0;
    __src = param_1 + 1;
    do {
      while (tmp_c4 == param_2[tmp_i2]) {
        tmp_s3 = tmp_s3 + 1;
        tmp_i2 = tmp_i2 + 1;
        if (tmp_s3 == tmp_s1) goto LAB_0001a3e8;
LAB_0001a3d4:
        tmp_c4 = *__src;
        __src = __src + 1;
        if (tmp_c4 == '\0') {
          return 1;
        }
      }
      if (tmp_s3 != tmp_s1) goto LAB_0001a3d4;
LAB_0001a3e8:
      strcpy(__src + -tmp_s3,__src);
      tmp_c4 = *__src;
      tmp_s3 = 0;
      tmp_i2 = 0;
      __src = __src + 1;
    } while (tmp_c4 != '\0');
  }
  return 1;
}

byte * escape_string(byte *param_1)

{
{  size_t tmp_s1;
  byte *tmp_pb2;
  byte tmp_b3;
  byte *__ptr;
  byte local_2d [25];
  uint32_t uStack_14;
  
  __ptr = buf_5546;
  uStack_14 = 0x2023d;
  local_2d[8] = 0x38;
  local_2d[9] = 0x39;
  local_2d[10] = 0x41;
  local_2d[0xb] = 0x42;
  local_2d[0] = 0x30;
  local_2d[1] = 0x31;
  local_2d[2] = 0x32;
  local_2d[3] = 0x33;
  local_2d[4] = 0x34;
  local_2d[5] = 0x35;
  local_2d[6] = 0x36;
  local_2d[7] = 0x37;
  local_2d[0xc] = 0x43;
  local_2d[0xd] = 0x44;
  local_2d[0xe] = 0x45;
  local_2d[0xf] = 0x46;
  local_2d[0x10] = 0;
  if ((buf_5546 == (byte *)0x0) || (tmp_s1 = strlen((char *)param_1), bufsize_5547 < tmp_s1 * 3)) {
    free(__ptr);
    tmp_s1 = strlen((char *)param_1);
    bufsize_5547 = tmp_s1 * 3 + 1;
    __ptr = calloc(bufsize_5547,1);
    buf_5546 = __ptr;
  }
  tmp_b3 = *param_1;
  tmp_pb2 = __ptr;
  while (tmp_b3 != 0) {
    while ((tmp_b3 != 0x25 && tmp_b3 != 0x3d && (tmp_b3 < 0x7f))) {
      *__ptr = tmp_b3;
      param_1 = param_1 + 1;
      __ptr = __ptr + 1;
      tmp_b3 = *param_1;
      tmp_pb2 = buf_5546;
      if (tmp_b3 == 0) goto LAB_000202e5;
    }
    *__ptr = 0x3d;
    __ptr[1] = local_2d[*param_1 >> 4];
    __ptr[2] = local_2d[*param_1 & 0xf];
    tmp_b3 = param_1[1];
    __ptr = __ptr + 3;
    tmp_pb2 = buf_5546;
    param_1 = param_1 + 1;
  }
LAB_000202e5:
  *__ptr = 0;
  return tmp_pb2;
}

void unescape_string(char *param_1)

{
{  char tmp_c1;
  char tmp_c2;
  size_t tmp_s3;
  char *tmp_pc4;
  char *tmp_pc5;
  long tmp_l6;
  char tmp_c7;
  char *tmp_pc8;
  
  tmp_s3 = strlen(param_1);
  if ((2 < (int)tmp_s3) && (tmp_pc4 = strchr(param_1,0x3d), tmp_pc4 != (char *)0x0)) {
    tmp_c7 = *param_1;
    tmp_pc4 = param_1;
    if (tmp_c7 != '\0') {
      tmp_pc5 = param_1 + 1;
      tmp_pc8 = param_1;
      do {
        while (tmp_pc4 = tmp_pc5, tmp_c7 != '=') {
LAB_00020390:
          tmp_pc4[-1] = tmp_c7;
          param_1 = tmp_pc8 + 1;
          tmp_c7 = tmp_pc8[1];
          tmp_pc5 = tmp_pc4 + 1;
          tmp_pc8 = param_1;
          if (tmp_c7 == '\0') goto LAB_00020450;
        }
        tmp_c1 = tmp_pc8[1];
        tmp_pc5 = strchr("23456789ABCDEF",(int)tmp_c1);
        if (tmp_pc5 == (char *)0x0) goto LAB_00020390;
        tmp_c2 = tmp_pc8[2];
        tmp_pc5 = strchr("0123456789ABCDEF",(int)tmp_c2);
        if (tmp_pc5 == (char *)0x0) goto LAB_00020390;
        code_5557 = tmp_c1;
        g_dat_00067a85 = tmp_c2;
        tmp_l6 = strtol(&code_5557,(char **)0x0,0x10);
        param_1 = tmp_pc8 + 3;
        tmp_pc4[-1] = (char)tmp_l6;
        tmp_c7 = tmp_pc8[3];
        tmp_pc5 = tmp_pc4 + 1;
        tmp_pc8 = param_1;
      } while (tmp_c7 != '\0');
    }
LAB_00020450:
    do {
      *tmp_pc4 = *param_1;
      tmp_c7 = *param_1;
      param_1 = param_1 + 1;
      tmp_pc4 = tmp_pc4 + 1;
    } while (tmp_c7 != '\0');
  }
  return;
}

void Text_PaintCenter(float param_1,uint32_t param_2,float param_3,uint32_t param_4,
                     byte *param_5)

{
{  byte tmp_b1;
  float tmp_f2;
  int tmp_i3;
  size_t tmp_s4;
  byte *tmp_pb5;
  int tmp_i6;
  int tmp_i7;
  
  tmp_i3 = g_dat_003e7e2c;
  tmp_i6 = g_dat_003e7e2c * 0x5044;
  if (param_5 == (byte *)0x0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_i7 = 0;
    tmp_s4 = strlen((char *)param_5);
    tmp_f2 = 0.0;
    tmp_pb5 = param_5;
    do {
      while( true ) {
        tmp_b1 = *tmp_pb5;
        if ((tmp_b1 == 0) || ((int)tmp_s4 <= tmp_i7)) goto LAB_00038780;
        if ((tmp_b1 != 0x5e) || ((tmp_pb5[1] == 0 || (tmp_pb5[1] == 0x5e)))) break;
        tmp_pb5 = tmp_pb5 + 2;
        if (tmp_pb5 == (byte *)0x0) goto LAB_00038780;
      }
      tmp_pb5 = tmp_pb5 + 1;
      tmp_i7 = tmp_i7 + 1;
      tmp_f2 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b1 * 0x50 + tmp_i6) + tmp_f2;
    } while (tmp_pb5 != (byte *)0x0);
  }
LAB_00038780:
  Text_Paint_Ext(param_1 - (float)(int)ROUND(param_3 * tmp_f2 *
                                             *(float *)(&g_dat_0039cffc + tmp_i3 * 0x5044)) * 0.5,
                 param_2,param_3,param_3,param_4,param_5,0,0,6,&g_dat_00397ffc + tmp_i6);
  return;
}

char * String_Alloc(char *param_1)

{
{  char tmp_c1;
  uint16_t tmp_u2;
  uint32_t *tmp_pu3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  void *tmp_pc6;
  __int32_t **pp_Var7;
  int tmp_i8;
  size_t tmp_s9;
  uint tmp_u10;
  uint tmp_u11;
  uint tmp_u12;
  uint32_t *tmp_pu13;
  char *tmp_pc14;
  char *tmp_pc15;
  byte tmp_b16;
  
  tmp_b16 = 0;
  if (param_1 != (char *)0x0) {
    tmp_c1 = *param_1;
    if (tmp_c1 == '\0') {
      return "";
    }
    pp_Var7 = __ctype_tolower_loc();
    tmp_u10 = 0;
    tmp_i8 = 0x77;
    do {
      tmp_u10 = tmp_u10 + (char)(*pp_Var7)[tmp_c1] * tmp_i8;
      tmp_c1 = param_1[tmp_i8 + -0x76];
      tmp_i8 = tmp_i8 + 1;
    } while (tmp_c1 != '\0');
    tmp_pu3 = (uint32_t *)(&strHandle)[tmp_u10 & 0x7ff];
    tmp_pu13 = tmp_pu3;
    if (tmp_pu3 == (uint32_t *)0x0) {
      tmp_s9 = strlen(param_1);
      if ((int)(strPoolIndex + tmp_s9) < 0x5ffff) {
        tmp_pc4 = strPool + strPoolIndex;
        tmp_u11 = tmp_s9 + 1;
        tmp_u12 = tmp_u11;
        tmp_pc15 = tmp_pc4;
        if (7 < tmp_u11) {
          if (((uint)tmp_pc4 & 1) != 0) {
            tmp_c1 = *param_1;
            tmp_pc15 = strPool + strPoolIndex + 1;
            param_1 = param_1 + 1;
            *tmp_pc4 = tmp_c1;
            tmp_u12 = tmp_s9;
          }
          tmp_pc14 = tmp_pc15;
          if (((uint)tmp_pc15 & 2) != 0) {
            tmp_u2 = *(uint16_t *)param_1;
            tmp_pc14 = tmp_pc15 + 2;
            param_1 = param_1 + 2;
            tmp_u12 = tmp_u12 - 2;
            *(uint16_t *)tmp_pc15 = tmp_u2;
          }
          tmp_pc15 = tmp_pc14;
          if (((uint)tmp_pc14 & 4) != 0) {
            tmp_u5 = *(uint32_t *)param_1;
            tmp_pc15 = tmp_pc14 + 4;
            param_1 = param_1 + 4;
            tmp_u12 = tmp_u12 - 4;
            *(uint32_t *)tmp_pc14 = tmp_u5;
          }
        }
        for (; tmp_i8 = allocPoint, tmp_u12 != 0; tmp_u12 = tmp_u12 - 1) {
          *tmp_pc15 = *param_1;
          param_1 = param_1 + (uint)tmp_b16 * -2 + 1;
          tmp_pc15 = tmp_pc15 + (uint)tmp_b16 * -2 + 1;
        }
        strPoolIndex = strPoolIndex + tmp_u11;
        if (allocPoint < 0x1ffff9) {
          tmp_pu3 = (uint32_t *)(memoryPool + allocPoint);
          allocPoint = allocPoint + 0x10;
          (&strHandle)[tmp_u10 & 0x7ff] = tmp_pu3;
          *tmp_pu3 = 0;
          *(char **)(memoryPool + tmp_i8 + 4) = tmp_pc4;
          return tmp_pc4;
        }
        goto LAB_0003c1b0;
      }
    }
    else {
      do {
        tmp_pc4 = (char *)tmp_pu13[1];
        tmp_i8 = strcmp(param_1,tmp_pc4);
        if (tmp_i8 == 0) {
          return tmp_pc4;
        }
        tmp_pu13 = (uint32_t *)*tmp_pu13;
      } while (tmp_pu13 != (uint32_t *)0x0);
      tmp_s9 = strlen(param_1);
      if ((int)(tmp_s9 + strPoolIndex) < 0x5ffff) {
        tmp_u10 = tmp_s9 + 1;
        tmp_pc4 = strPool + strPoolIndex;
        tmp_u11 = tmp_u10;
        tmp_pc15 = tmp_pc4;
        if (7 < tmp_u10) {
          if (((uint)tmp_pc4 & 1) != 0) {
            tmp_c1 = *param_1;
            tmp_pc15 = strPool + strPoolIndex + 1;
            param_1 = param_1 + 1;
            *tmp_pc4 = tmp_c1;
            tmp_u11 = tmp_s9;
          }
          tmp_pc14 = tmp_pc15;
          if (((uint)tmp_pc15 & 2) != 0) {
            tmp_u2 = *(uint16_t *)param_1;
            tmp_pc14 = tmp_pc15 + 2;
            param_1 = param_1 + 2;
            tmp_u11 = tmp_u11 - 2;
            *(uint16_t *)tmp_pc15 = tmp_u2;
          }
          tmp_pc15 = tmp_pc14;
          if (((uint)tmp_pc14 & 4) != 0) {
            tmp_u5 = *(uint32_t *)param_1;
            tmp_pc15 = tmp_pc14 + 4;
            param_1 = param_1 + 4;
            tmp_u11 = tmp_u11 - 4;
            *(uint32_t *)tmp_pc14 = tmp_u5;
          }
        }
        for (; tmp_i8 = allocPoint, tmp_u11 != 0; tmp_u11 = tmp_u11 - 1) {
          *tmp_pc15 = *param_1;
          param_1 = param_1 + (uint)tmp_b16 * -2 + 1;
          tmp_pc15 = tmp_pc15 + (uint)tmp_b16 * -2 + 1;
        }
        strPoolIndex = strPoolIndex + tmp_u10;
        for (tmp_pu13 = (uint32_t *)*tmp_pu3; tmp_pu13 != (uint32_t *)0x0;
            tmp_pu13 = (uint32_t *)*tmp_pu13) {
          tmp_pu3 = tmp_pu13;
        }
        if (allocPoint < 0x1ffff9) {
          tmp_pu13 = (uint32_t *)(memoryPool + allocPoint);
          allocPoint = allocPoint + 0x10;
          *tmp_pu13 = 0;
          *(char **)(memoryPool + tmp_i8 + 4) = tmp_pc4;
          *tmp_pu3 = tmp_pu13;
          return tmp_pc4;
        }
LAB_0003c1b0:
        outOfMemory = 1;
        if (*(void **)(DC + 0xd0) != (void *)0x0) {
          (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
        }
        _DAT_00000000 = 0;
        tmp_pc6 = (void *)invalidInstructionException();
        (*tmp_pc6)();
      }
    }
  }
  return (char *)0x0;
}

void String_Report(void)

{
{  Com_Printf("Memory/String Pool Info\n");
  Com_Printf("----------------\n");
  Com_Printf("String Pool is %.1f%% full, %i bytes out of %i used.\n",
             (double)(((float)strPoolIndex / 393216.0) * 100.0),strPoolIndex,0x60000);
  Com_Printf("Memory Pool is %.1f%% full, %i bytes out of %i used.\n",
             (double)((float)allocPoint * 4.7683716e-07 * 100.0),allocPoint,0x200000);
  return;
}

void String_Init(void)

{
{  uint8_t *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  char tmp_c6;
  uint8_t **tmp_ppu7;
  uint8_t **tmp_ppu8;
  char *tmp_pc9;
  uint8_t **local_24;
  uint32_t *local_20;
  
  tmp_pu4 = &strHandle;
  for (tmp_i5 = 0x800; tmp_i5 != 0; tmp_i5 = tmp_i5 + -1) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  menuCount = 0;
  modalMenuCount = 0;
  allocPoint = 0;
  outOfMemory = 0;
  strHandleCount = 0;
  strPoolIndex = 0;
  local_20 = &itemParseKeywordHash;
  tmp_pu4 = &itemParseKeywordHash;
  for (tmp_i5 = 0x200; tmp_i5 != 0; tmp_i5 = tmp_i5 + -1) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  if (itemParseKeywords != (uint8_t *)0x0) {
    tmp_pc9 = itemParseKeywords;
    local_24 = &itemParseKeywords;
    do {
      tmp_c6 = *tmp_pc9;
      tmp_pu4 = local_20;
      if (tmp_c6 != '\0') {
        tmp_u3 = 0;
        tmp_i5 = 0x77;
        do {
          tmp_i2 = (int)tmp_c6;
          if ((byte)(tmp_c6 + 0xbfU) < 0x1a) {
            tmp_i2 = tmp_c6 + 0x20;
          }
          tmp_u3 = tmp_i2 * tmp_i5 + tmp_u3;
          tmp_c6 = tmp_pc9[tmp_i5 + -0x76];
          tmp_i5 = tmp_i5 + 1;
        } while (tmp_c6 != '\0');
        tmp_pu4 = &itemParseKeywordHash + ((tmp_u3 ^ (int)tmp_u3 >> 0x14 ^ (int)tmp_u3 >> 10) & 0x1ff);
      }
      tmp_pu1 = (uint8_t *)*tmp_pu4;
      *tmp_pu4 = local_24;
      local_24[2] = tmp_pu1;
      tmp_pc9 = local_24[3];
      local_24 = local_24 + 3;
    } while (tmp_pc9 != (char *)0x0);
  }
  local_20 = &menuParseKeywordHash;
  tmp_pu4 = &menuParseKeywordHash;
  for (tmp_i5 = 0x200; tmp_i5 != 0; tmp_i5 = tmp_i5 + -1) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  tmp_ppu7 = &menuParseKeywords;
  tmp_pc9 = menuParseKeywords;
  while (tmp_pc9 != (char *)0x0) {
    tmp_c6 = *tmp_pc9;
    tmp_pu4 = local_20;
    if (tmp_c6 != '\0') {
      tmp_u3 = 0;
      tmp_i5 = 0x77;
      do {
        tmp_i2 = (int)tmp_c6;
        if ((byte)(tmp_c6 + 0xbfU) < 0x1a) {
          tmp_i2 = tmp_c6 + 0x20;
        }
        tmp_u3 = tmp_i2 * tmp_i5 + tmp_u3;
        tmp_c6 = tmp_pc9[tmp_i5 + -0x76];
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_c6 != '\0');
      tmp_pu4 = &menuParseKeywordHash + ((tmp_u3 ^ (int)tmp_u3 >> 10 ^ (int)tmp_u3 >> 0x14) & 0x1ff);
    }
    tmp_pu1 = (uint8_t *)*tmp_pu4;
    *tmp_pu4 = tmp_ppu7;
    tmp_ppu7[2] = tmp_pu1;
    tmp_pc9 = tmp_ppu7[3];
    tmp_ppu7 = tmp_ppu7 + 3;
  }
  if ((DC != 0) && (*(int *)(DC + 0xb8) != 0)) {
    tmp_ppu7 = (uint8_t **)&g_dat_000693f8;
    do {
      tmp_ppu8 = tmp_ppu7 + 8;
      (**(void **)(DC + 0xbc))(tmp_ppu7[-6],tmp_ppu7,tmp_ppu7 + 1);
      tmp_ppu7 = tmp_ppu8;
    } while (tmp_ppu8 != &g_ptr_DAT_00069b98);
  }
  return;
}
