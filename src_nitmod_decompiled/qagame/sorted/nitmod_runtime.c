/* ELF/C++ runtime leftovers from the .so — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_runtime.h"

int _init(EVP_PKEY_CTX *ctx)
{
  int tmp_i1;
  
  tmp_i1 = __gmon_start__();
  return tmp_i1;
}

void std_ostream_operator(ostream *this,int param_1)
{
  operator<<(this,param_1);
  return;
}

void std_ios_base_dtor_ios_base(ios_base *this)
{
  ~ios_base(this);
  return;
}

void std_iostream_dtor_iostream(iostream *this)
{
  ~iostream(this);
  return;
}

void std::stringstream::dtor_stringstream(stringstream *this)
{
  dtor_stringstream(this);
  return;
}

void std_locale_dtor_locale(locale *this)
{
  ~locale(this);
  return;
}

ostream * std_ostream_insert(ostream *param_1,char *param_2,int param_3)
{
  ostream *poVar1;
  
  poVar1 = __ostream_insert<>(param_1,param_2,param_3);
  return poVar1;
}

uint32_t std_string_Rep_M_dispose(allocator *param_1)
{
  allocator *paVar1;
  int tmp_i2;
  uint32_t saved_ESI;
  
  LOCK();
  paVar1 = param_1 + 8;
  tmp_i2 = *(int *)paVar1;
  *(int *)paVar1 = *(int *)paVar1 + -1;
  UNLOCK();
  if (tmp_i2 < 1) {
    std::string::_Rep::_M_destroy(param_1);
  }
  return saved_ESI;
}

void _GLOBAL__sub_I_vectors_cpp(void)
{
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::dtor_Init,&std::__ioinit,&__dso_handle);
  return;
}

void _GLOBAL__sub_I_HitDetect_cpp(void)
{
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::dtor_Init,&std::__ioinit,&__dso_handle);
  return;
}

void _GLOBAL__sub_I_g_etbot_interface_cpp(void)
{
  KeyVals *this;
  KeyVals *pKVar1;
  
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::dtor_Init,&std::__ioinit,&__dso_handle);
  this = (KeyVals *)g_DeferredGoals;
  do {
    KeyVals::KeyVals(this);
    pKVar1 = this + 0xe00;
    KeyVals::Reset(this);
    this = pKVar1;
  } while (pKVar1 != (KeyVals *)&m_EntityHandles);
  return;
}

void _GLOBAL__sub_I_BotLoadLibrary_cpp(void)
{
  g_OmnibotLibPath = memchr;
  __cxa_atexit(std::string::dtor_string,&g_OmnibotLibPath,&__dso_handle);
  return;
}

void deregister_tm_clones(void)
{
  return;
}

void register_tm_clones(void)
{
  return;
}

void __do_global_dtors_aux(void)
{
  if (completed_6288 == '\0') {
    __cxa_finalize(__dso_handle);
    deregister_tm_clones();
    completed_6288 = '\x01';
  }
  return;
}

void frame_dummy(void)
{
  if (__JCR_END__ != 0) {
    _Jv_RegisterClasses(&__JCR_END__);
  }
  register_tm_clones();
  return;
}

void Vector_Vector(Vector *this,Point *param_1)
{
  *(uint32_t *)this = *(uint32_t *)param_1;
  *(uint32_t *)(this + 4) = *(uint32_t *)(param_1 + 4);
  *(uint32_t *)(this + 8) = *(uint32_t *)(param_1 + 8);
  return;
}

// Vector::TEMPNAMEPLACEHOLDERVALUE(Vector const&) const

void Vector::operator+(Vector *this,Vector *param_1)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float *in_stack_0000000c;
  
  tmp_f1 = *(float *)(param_1 + 8);
  tmp_f2 = in_stack_0000000c[2];
  tmp_f3 = *(float *)(param_1 + 4);
  tmp_f4 = in_stack_0000000c[1];
  *(float *)this = *(float *)param_1 + *in_stack_0000000c;
  *(float *)(this + 4) = tmp_f3 + tmp_f4;
  *(float *)(this + 8) = tmp_f1 + tmp_f2;
  return;
}

// Vector::TEMPNAMEPLACEHOLDERVALUE(Vector const&) const

void Vector::operator-(Vector *this,Vector *param_1)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float *in_stack_0000000c;
  
  tmp_f1 = *(float *)(param_1 + 8);
  tmp_f2 = in_stack_0000000c[2];
  tmp_f3 = *(float *)(param_1 + 4);
  tmp_f4 = in_stack_0000000c[1];
  *(float *)this = *(float *)param_1 - *in_stack_0000000c;
  *(float *)(this + 4) = tmp_f3 - tmp_f4;
  *(float *)(this + 8) = tmp_f1 - tmp_f2;
  return;
}

// Vector::TEMPNAMEPLACEHOLDERVALUE(float) const

void Vector::operator*(Vector *this,float param_1)

{
  float tmp_f1;
  float tmp_f2;
  float in_stack_0000000c;
  
  tmp_f1 = *(float *)((int)param_1 + 8);
  tmp_f2 = *(float *)((int)param_1 + 4);
  *(float *)this = in_stack_0000000c * *(float *)param_1;
  *(float *)(this + 4) = tmp_f2 * in_stack_0000000c;
  *(float *)(this + 8) = tmp_f1 * in_stack_0000000c;
  return;
}

long double Vector_Length(Vector *this)
{
  long double tmp_l1;
  long double tmp_l2;
  float tmp_f3;
  
  tmp_l2 = (long double)*(float *)(this + 8) * (long double)*(float *)(this + 8) +
          (long double)*(float *)(this + 4) * (long double)*(float *)(this + 4) +
          (long double)*(float *)this * (long double)*(float *)this;
  tmp_l1 = SQRT(tmp_l2);
  if (NAN(tmp_l1)) {
    tmp_f3 = sqrtf((float)tmp_l2);
    tmp_l1 = (long double)tmp_f3;
  }
  return tmp_l1;
}

// ClipLine(int, Vector const&, Vector const&, Vector const&, Vector const&, float&, float&)

bool ClipLine(int param_1,Vector *param_2,Vector *param_3,Vector *param_4,Vector *param_5,
             float *param_6,float *param_7)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  bool tmp_b4;
  
  tmp_f1 = *(float *)(param_4 + param_1 * 4);
  tmp_f3 = (*(float *)(param_2 + param_1 * 4) - tmp_f1) / (*(float *)(param_5 + param_1 * 4) - tmp_f1);
  tmp_f1 = (*(float *)(param_3 + param_1 * 4) - tmp_f1) / (*(float *)(param_5 + param_1 * 4) - tmp_f1);
  tmp_f2 = tmp_f1;
  if (tmp_f3 <= tmp_f1) {
    tmp_f2 = tmp_f3;
    tmp_f3 = tmp_f1;
  }
  tmp_f1 = *param_6;
  tmp_b4 = false;
  if ((tmp_f1 <= tmp_f3) && (tmp_f2 <= *param_7)) {
    if (tmp_f1 <= tmp_f2) {
      tmp_f1 = tmp_f2;
    }
    *param_6 = tmp_f1;
    if (*param_7 < tmp_f3) {
      tmp_f3 = *param_7;
    }
    *param_7 = tmp_f3;
    tmp_b4 = *param_6 <= tmp_f3;
  }
  return tmp_b4;
}

uint32_t
LineAABBIntersection
          (uint32_t *param_1,uint32_t *param_2,uint32_t *param_3,uint32_t *param_4,
          uint32_t *param_5,uint32_t *param_6,float *param_7,float *param_8)

{
  char tmp_c1;
  long double tmp_l2;
  uint32_t local_9c;
  uint32_t uStack_98;
  uint32_t uStack_94;
  float fStack_84;
  float fStack_80;
  uint32_t local_7c;
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  Vector local_58 [12];
  Vector aVStack_4c [12];
  Vector local_40 [12];
  uint32_t uStack_34;
  uint32_t uStack_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_7c = *param_1;
  local_78 = param_1[1];
  local_74 = param_1[2];
  local_70 = *param_4;
  local_6c = param_4[1];
  local_68 = param_4[2];
  local_64 = *param_5;
  local_60 = param_5[1];
  local_5c = param_5[2];
  local_28 = *param_2;
  local_24 = param_2[1];
  local_20 = param_2[2];
  Vector::operator+(local_58,(Vector *)&local_7c);
  local_28 = *param_3;
  local_24 = param_3[1];
  local_20 = param_3[2];
  Vector::operator+(aVStack_4c,(Vector *)&local_7c);
  fStack_84 = 0.0;
  fStack_80 = 1.0;
  tmp_c1 = ClipLine(0,local_58,aVStack_4c,(Vector *)&local_70,(Vector *)&local_64,&fStack_84,
                   &fStack_80);
  if (((tmp_c1 != '\0') &&
      (tmp_c1 = ClipLine(1,local_58,aVStack_4c,(Vector *)&local_70,(Vector *)&local_64,&fStack_84,
                        &fStack_80), tmp_c1 != '\0')) &&
     (tmp_c1 = ClipLine(2,local_58,aVStack_4c,(Vector *)&local_70,(Vector *)&local_64,&fStack_84,
                       &fStack_80), tmp_c1 != '\0')) {
    Vector::operator-(local_40,(Vector *)&local_64);
    Vector::operator*((Vector *)&local_28,(float)local_40);
    Vector::operator+((Vector *)&local_9c,(Vector *)&local_70);
    uStack_34 = local_9c;
    uStack_30 = uStack_98;
    local_2c = uStack_94;
    *param_6 = local_9c;
    param_6[1] = uStack_98;
    param_6[2] = uStack_94;
    Vector::operator-((Vector *)&local_28,(Vector *)&uStack_34);
    tmp_l2 = (long double)Vector::Length((Vector *)&local_28);
    *param_7 = (float)tmp_l2;
    *param_8 = fStack_84;
    return 1;
  }
  return 0;
}

void TracePlayers(uint *param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                 float *param_5,int *param_6,uint32_t *param_7)

{
  int tmp_i1;
  uint *tmp_pu2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  float *pfVar8;
  float local_50;
  float local_4c [3];
  uint8_t local_40 [12];
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x200ffe;
  local_4c[0] = 2.0;
  local_4c[1] = 0.0;
  tmp_pu6 = &level;
  if (g_unk_00abe938 < 1) {
    local_4c[0] = 2.0;
  }
  else {
    local_50 = 2.0;
    tmp_i7 = 0;
    tmp_i5 = g_unk_00abe938;
    do {
      while( true ) {
        local_4c[2] = -NAN;
        tmp_i1 = tmp_pu6[tmp_i7 + 0x29] * 0x600;
        tmp_pu2 = (uint *)(g_entities + tmp_i1);
        if ((((*(int *)(g_entities + tmp_i1 + 0x194) != 0) &&
             (tmp_i3 = *(int *)(g_entities + tmp_i1 + 400), tmp_pu2 != param_1)) &&
            (*(int *)(tmp_i3 + 3000) != 3)) &&
           (((*(int *)(g_entities + tmp_i1 + 0x120) != 0 && ((*(byte *)(tmp_i3 + 0xd) & 0x40) == 0))
            && ((*(int *)(tmp_i3 + 4) == 3 || (*(int *)(tmp_i3 + 4) == 0)))))) break;
        tmp_i7 = tmp_i7 + 1;
        if (tmp_i5 <= tmp_i7) goto LAB_002011f4;
      }
      if ((*(uint *)(tmp_i3 + 0x68) & 0x880001) == 0) {
        if ((*(uint *)(tmp_i3 + 0x68) & 0x10) == 0) {
          if (((g_hitboxes[0xc] & 0x10) == 0) || (*(int *)(tmp_i3 + 0x154) == 0)) {
            local_34 = StandBBoxMins;
            local_30 = g_unk_002bd47c;
            local_2c = g_unk_002bd480;
            local_28 = StandBBoxMaxs;
            local_24 = g_unk_002bd470;
            local_20 = g_unk_002bd474;
          }
          else {
            local_34 = *(uint32_t *)(g_entities + tmp_i1 + 0x134);
            local_30 = *(uint32_t *)(g_entities + tmp_i1 + 0x138);
            local_2c = *(uint32_t *)(g_entities + tmp_i1 + 0x13c);
            local_28 = *(uint32_t *)(g_entities + tmp_i1 + 0x140);
            local_24 = *(uint32_t *)(g_entities + tmp_i1 + 0x144);
            local_20 = *(uint32_t *)(g_entities + tmp_i1 + 0x148);
          }
        }
        else {
          local_34 = CrouchBBoxMins;
          local_30 = g_unk_002bd464;
          local_2c = g_unk_002bd468;
          local_28 = CrouchBBoxMaxs;
          local_24 = g_unk_002bd458;
          local_20 = g_unk_002bd45c;
        }
      }
      else {
        local_34 = ProneBBoxMins;
        local_30 = g_unk_002bd44c;
        local_2c = g_unk_002bd450;
        local_28 = ProneBBoxMaxs;
        local_24 = g_unk_002bd440;
        local_20 = g_unk_002bd444;
      }
      tmp_i5 = tmp_i1 + 0x93e608;
      pfVar8 = local_4c;
      tmp_i3 = LineAABBIntersection
                        (tmp_i5,&local_34,&local_28,param_2,param_3,local_40,local_4c + 1,pfVar8,
                         tmp_pu6,tmp_i5,pfVar8);
      if ((g_antilag[0xc] & 2) != 0) {
        tmp_i4 = *(int *)(*(int *)(g_entities + tmp_i1 + 400) + 0xa0);
        if ((0x1f < tmp_i4) && (tmp_i4 = tmp_i4 >> 1, tmp_i4 == 0x20)) {
          tmp_i4 = 0x1f;
        }
        G_RailBox(tmp_i5,tmp_i1 + 0x93e5d4,tmp_i1 + 0x93e5e0,g_color_table + tmp_i4 * 0x10,
                  *tmp_pu2 | 0x1000);
      }
      if (((tmp_i3 != 0) &&
          (tmp_i5 = Trace_HitsPlayer(param_1,tmp_pu2,param_2,param_3,pfVar8,local_4c + 2), tmp_i5 != -1
          )) && (local_4c[0] < local_50)) {
        *param_6 = (tmp_i1 >> 9) * -0x55555555;
        *param_7 = local_4c[2];
        local_50 = local_4c[0];
      }
      tmp_i5 = tmp_pu6[0x26];
      tmp_i7 = tmp_i7 + 1;
    } while (tmp_i7 < tmp_i5);
  }
LAB_002011f4:
  *param_5 = local_4c[0];
  return;
}

int luaM_growaux_(int param_1,uint32_t param_2,int *param_3,uint param_4,int param_5,
                 uint32_t param_6)

{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i3 = *param_3;
  if (tmp_i3 < param_5 / 2) {
    param_5 = tmp_i3 * 2;
    if (3 < param_5) goto LAB_002013d5;
    param_5 = 4;
    if ((uint)(0xfffffffd / (ulonglong)param_4) < 5) goto LAB_00201497;
  }
  else {
    if (param_5 <= tmp_i3) {
      luaG_runerror(param_1,param_6);
    }
LAB_002013d5:
    if ((uint)(0xfffffffd / (ulonglong)param_4) < param_5 + 1U) {
LAB_00201497:
      luaG_runerror(param_1,"memory allocation error: block too big");
      tmp_i3 = 0;
      goto LAB_00201459;
    }
  }
  tmp_i1 = *param_3;
  tmp_i4 = param_5 * param_4;
  tmp_i2 = *(int *)(param_1 + 0x10);
  tmp_i3 = (**(void **)(tmp_i2 + 0xc))(*(uint32_t *)(tmp_i2 + 0x10),param_2,param_4 * tmp_i1,tmp_i4);
  if ((tmp_i3 == 0) && (tmp_i4 != 0)) {
    luaD_throw(param_1,4);
  }
  *(int *)(tmp_i2 + 0x44) = *(int *)(tmp_i2 + 0x44) + (tmp_i4 - param_4 * tmp_i1);
LAB_00201459:
  *param_3 = param_5;
  return tmp_i3;
}

char std_ctype_char_do_widen(ctype<char> *this,char param_1)
{
  return param_1;
}

uint32_t IEngineInterface_DebugLine(float *param_1,float *param_2,obColor *param_3,float param_4)
{
  return 0;
}

uint32_t IEngineInterface_DebugBox(float *param_1,float *param_2,obColor *param_3,float param_4)
{
  return 0;
}

// IEngineInterface::DebugArrow(float const*, float const*, obColor const&, float)

void IEngineInterface::DebugArrow
          (IEngineInterface *this,float *param_1,float *param_2,obColor *param_3,float param_4)

{
  (**(void **)(*(int *)this + 0x84))(this,param_1,param_2,param_3,param_4);
  return;
}

IEngineInterface_DebugRadius(float *param_1,float param_2,obColor *param_3,float param_4)
{
  return 0;
}

// IEngineInterface::DebugPolygon(obVec3 const*, int, obColor const&, float, int)

uint32_t
IEngineInterface::DebugPolygon
          (obVec3 *param_1,int param_2,obColor *param_3,float param_4,int param_5)

{
  return 0;
}

IEngineInterface_PrintScreenText(float *param_1,float param_2,obColor *param_3,char *param_4)
{
  return 0;
}

uint32_t ETInterface_DebugLine(float *param_1,float *param_2,obColor *param_3,float param_4)
{
  return CONCAT31(SUB43(GHIDRA_FIELD(g_dedicated, 12, 4),1),GHIDRA_FIELD(g_dedicated, 12, 4) != 0);
}

uint32_t ETInterface_DebugRadius(float *param_1,float param_2,obColor *param_3,float param_4)
{
  return CONCAT31(SUB43(GHIDRA_FIELD(g_dedicated, 12, 4),1),GHIDRA_FIELD(g_dedicated, 12, 4) != 0);
}

uint32_t ETInterface_GetEntityPowerups(void)
{
  return 0;
}

uint32_t ETInterface_GetGameTime(void)
{
  return g_unk_00abe908;
}

uint8_t * ETInterface_GetMapName(void)
{
  return &g_unk_00abe8c0;
}

char * ETInterface_GetGameName(void)
{
  return "Enemy Territory";
}

char * ETInterface_GetModName(void)
{
  return "nitmod";
}

uint8_t * ETInterface_GetModVers(void)
{
  return &g_unk_00249e9e;
}

void ETInterface_dtor_ETInterface(ETInterface *this)
{
  return;
}

void ETInterface_PrintMessage(ETInterface *this,char *param_1)
{
  char tmp_c1;
  uint tmp_u2;
  char *tmp_pc3;
  char local_40c [4];
  uint32_t local_408 [255];
  
  if (param_1 != (char *)0x0) {
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)local_408 + (tmp_u2 - 4)) = 0;
      *(uint32_t *)((int)local_408 + tmp_u2) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0x400);
    tmp_c1 = *param_1;
    if (tmp_c1 != '\0') {
      tmp_pc3 = local_40c;
      do {
        if (tmp_c1 == '\t') {
          *tmp_pc3 = ' ';
          tmp_c1 = param_1[1];
          tmp_pc3[1] = ' ';
          tmp_pc3[2] = ' ';
          tmp_pc3[3] = ' ';
          tmp_pc3 = tmp_pc3 + 4;
        }
        else {
          *tmp_pc3 = tmp_c1;
          tmp_c1 = param_1[1];
          tmp_pc3 = tmp_pc3 + 1;
        }
        param_1 = param_1 + 1;
      } while (tmp_c1 != '\0');
    }
    G_Printf("%s%s\n",&g_unk_00270b9f,local_40c);
  }
  return;
}

void ETInterface_PrintError(ETInterface *this,char *param_1)
{
  if (param_1 != (char *)0x0) {
    G_Printf("%s%s\n",&g_unk_00248060,param_1);
  }
  return;
}

void ETInterface_dtor_ETInterface(ETInterface *this)
{
  operator_delete(this);
  return;
}

void ETInterface_GetLogPath(void)
{
  trap_Cvar_VariableStringBuffer("fs_homepath",GetLogPath()::logpath,0x200);
  Omnibot_FixPath(GetLogPath()::logpath);
  return;
}

void ETInterface_GetBotPath(void)
{
  Omnibot_GetLibraryPath();
  return;
}

int ETInterface_GetAutoNavFeatures(AutoNavFeature_t *param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int *tmp_pi4;
  int *tmp_pi5;
  int tmp_i6;
  int local_34;
  int local_24;
  
  if (g_unk_00abe8a8 < 0x41) {
    local_24 = 0;
  }
  else {
    local_34 = 0x40;
    tmp_i6 = 0x9564a0;
    local_24 = 0;
    tmp_i3 = g_unk_00abe8a8;
    do {
      if (*(int *)(tmp_i6 + 0x194) != 0) {
        tmp_pi1 = (int *)(param_2 + local_24 * 100);
        *tmp_pi1 = 0;
        tmp_pi1[0x11] = 0;
        *(uint8_t *)(tmp_pi1 + 0x18) = 0;
        tmp_i3 = tmp_i6;
        tmp_pi4 = tmp_pi1 + 2;
        do {
          tmp_pi5 = tmp_pi4 + 1;
          *tmp_pi4 = *(int *)(tmp_i3 + 0x168);
          tmp_pi4[6] = *(int *)(tmp_i3 + 0x168);
          tmp_pi1[0x12] = 0;
          tmp_pi1[0x15] = 0;
          AngleVectors(tmp_i6 + 0x74,tmp_pi1 + 5,0,0);
          tmp_i3 = tmp_i3 + 4;
          tmp_pi4 = tmp_pi5;
        } while (tmp_pi5 != tmp_pi1 + 5);
        tmp_pi1[0x12] = *(int *)(tmp_i6 + 0x150);
        tmp_pi1[0x13] = *(int *)(tmp_i6 + 0x154);
        tmp_pi1[0x14] = *(int *)(tmp_i6 + 0x158);
        tmp_pi1[0x15] = *(int *)(tmp_i6 + 0x15c);
        tmp_pi1[0x16] = *(int *)(tmp_i6 + 0x160);
        tmp_pi1[0x17] = *(int *)(tmp_i6 + 0x164);
        if (*(int *)(tmp_i6 + 0x1a4) == 0) {
LAB_00232500:
          tmp_i2 = *tmp_pi1;
          tmp_i3 = g_unk_00abe8a8;
joined_r0x002325bb:
          g_unk_00abe8a8 = tmp_i3;
          if (tmp_i2 == 0) goto LAB_00232510;
        }
        else {
          tmp_i3 = *(int *)(tmp_i6 + 0x5c0);
          if (tmp_i3 == 0x37c98) {
            *tmp_pi1 = 0x2713;
          }
          else if (tmp_i3 == 0x3b699) {
            *tmp_pi1 = 0x2714;
          }
          else if ((tmp_i3 == 0x49240) ||
                  (tmp_i3 = Q_stricmp(*(int *)(tmp_i6 + 0x1a4),"info_player_spawn"), tmp_i3 == 0)) {
            *tmp_pi1 = 0x2712;
          }
          else {
            tmp_i3 = Q_stricmp(*(uint32_t *)(tmp_i6 + 0x1a4),"target_teleporter");
            if (tmp_i3 == 0) {
              *tmp_pi1 = 0x271e;
              tmp_i3 = G_PickTarget(*(uint32_t *)(tmp_i6 + 0x254));
              if (tmp_i3 == 0) goto LAB_00232500;
              tmp_pi1[8] = *(int *)(tmp_i3 + 0x168);
              tmp_pi1[9] = *(int *)(tmp_i3 + 0x16c);
              tmp_i2 = *tmp_pi1;
              tmp_pi1[10] = *(int *)(tmp_i3 + 0x170);
              tmp_i3 = g_unk_00abe8a8;
              goto joined_r0x002325bb;
            }
            tmp_i3 = *(int *)(tmp_i6 + 0x5c0);
            if ((tmp_i3 == 0x3317f) || (tmp_i3 == 0x36af1)) {
              *tmp_pi1 = 0x271c;
            }
            else if ((tmp_i3 == 0x1908e) ||
                    (tmp_i3 = Q_stricmp(*(uint32_t *)(tmp_i6 + 0x1a4),"misc_mg42base"), tmp_i3 == 0))
            {
              *tmp_pi1 = 7;
              *(uint8_t *)(tmp_pi1 + 0x18) = 1;
            }
            else if (*(int *)(tmp_i6 + 0x5c0) == 0x3db3a) {
              *tmp_pi1 = 0x1b;
              *(uint8_t *)(tmp_pi1 + 0x18) = 1;
            }
            else {
              if (*(int *)(tmp_i6 + 0x5c0) != 0x3f805) goto LAB_00232500;
              *tmp_pi1 = 0x1c;
              *(uint8_t *)(tmp_pi1 + 0x18) = 1;
            }
          }
        }
        local_24 = local_24 + 1;
        tmp_i3 = g_unk_00abe8a8;
      }
LAB_00232510:
      local_34 = local_34 + 1;
      tmp_i6 = tmp_i6 + 0x600;
    } while (local_34 < tmp_i3);
  }
  return local_24;
}

void ETInterface_BotCommand(ETInterface *this,int param_1,char *param_2)
{
  trap_EA_Command(param_1,param_2);
  return;
}

bool ETInterface_IsInPVS(ETInterface *this,float *param_1,float *param_2)
{
  int tmp_i1;
  
  tmp_i1 = trap_InPVS(param_1,param_2);
  return tmp_i1 != 0;
}

void ETInterface_UpdateBotInput(ETInterface *this,int param_1,ClientInput *param_2)
{
  int *tmp_pi1;
  uint tmp_u2;
  uint8_t tmp_u3;
  int tmp_i4;
  uint tmp_u5;
  uint8_t tmp_u6;
  int tmp_i7;
  int local_64;
  float local_58;
  uint8_t local_4c [4];
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x232679;
  *(uint *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0xc) =
       *(uint *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0xc) & 0xfffffdff;
  tmp_u2 = 0;
  do {
    tmp_u5 = tmp_u2;
    *(uint32_t *)((int)&UpdateBotInput(int,ClientInput_const&)::cmd + tmp_u5) = 0;
    *(uint32_t *)(&g_unk_00880f90 + tmp_u5) = 0;
    tmp_u2 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x18);
  *(uint32_t *)((int)&g_unk_00880f94 + tmp_u5) = 0;
  g_unk_00880fa4 = (uint8_t)param_1;
  UpdateBotInput(int,ClientInput_const&)::cmd = g_unk_00abe908;
  g_unk_00880f92 = _weaponBotToGame(*(int *)(param_2 + 0x20));
  if (g_unk_00880f92 == '(') {
    g_unk_00880f92 = '\x1e';
LAB_00232774:
    tmp_i7 = *(int *)(g_entities + param_1 * 0x600 + 400);
LAB_00232787:
    local_64 = *(int *)(tmp_i7 + 0xa8);
  }
  else {
    if (g_unk_00880f92 == ')') {
      g_unk_00880f92 = '\x1f';
      goto LAB_00232774;
    }
    if (g_unk_00880f92 == '\'') {
      g_unk_00880f92 = '\x18';
      goto LAB_00232774;
    }
    if (g_unk_00880f92 == '\x13') {
      g_unk_00880f91 = 2;
      goto LAB_00232774;
    }
    if (g_unk_00880f92 == '$') {
      tmp_i7 = *(int *)(g_entities + param_1 * 0x600 + 400);
      if (*(int *)(tmp_i7 + 0xa4) == 0x24) {
        tmp_i4 = BG_FindClipForWeapon(0x24);
        tmp_pi1 = (int *)(tmp_i7 + (tmp_i4 + 0xa4) * 4);
        tmp_i7 = *(int *)(g_entities + param_1 * 0x600 + 400);
        local_64 = *(int *)(tmp_i7 + 0xa8);
        if ((*tmp_pi1 == 0) && (local_64 == 0)) {
          g_unk_00880f92 = '\x16';
        }
        goto LAB_00232791;
      }
      goto LAB_00232787;
    }
    if (g_unk_00880f92 != '%') goto LAB_00232774;
    tmp_i7 = *(int *)(g_entities + param_1 * 0x600 + 400);
    if (*(int *)(tmp_i7 + 0xa4) != 0x25) goto LAB_00232787;
    tmp_i4 = BG_FindClipForWeapon(0x25);
    tmp_pi1 = (int *)(tmp_i7 + (tmp_i4 + 0xa4) * 4);
    tmp_i7 = *(int *)(g_entities + param_1 * 0x600 + 400);
    local_64 = *(int *)(tmp_i7 + 0xa8);
    if ((*tmp_pi1 == 0) && (local_64 == 0)) {
      g_unk_00880f92 = '\x17';
    }
  }
LAB_00232791:
  tmp_u2 = *(uint *)(param_2 + 0x18);
  if ((tmp_u2 & 0x80000) != 0) {
    g_unk_00880f90 = g_unk_00880f90 | 0x40;
  }
  if ((tmp_u2 & 1) != 0) {
    g_unk_00880f90 = g_unk_00880f90 | 1;
  }
  if ((tmp_u2 & 0x20) == 0) {
    if ((tmp_u2 & 0x4000) != 0) {
      g_unk_00880f90 = g_unk_00880f90 | 0x20;
    }
  }
  else {
    g_unk_00880f90 = g_unk_00880f90 | 0x10;
  }
  if ((tmp_u2 & 0x40) != 0) {
    g_unk_00880f90 = g_unk_00880f90 | 0x40;
  }
  if ((tmp_u2 & 2) != 0) {
    g_unk_00880f91 = g_unk_00880f91 | 1;
  }
  if ((tmp_u2 & 0x8000) != 0) {
    g_unk_00880f91 = g_unk_00880f91 | 0x40;
  }
  if ((tmp_u2 & 0x10) == 0) {
    if ((*(byte *)(tmp_i7 + 0x6a) & 8) != 0) goto LAB_002327e1;
  }
  else if ((*(byte *)(tmp_i7 + 0x6a) & 8) == 0) {
LAB_002327e1:
    g_unk_00880f91 = g_unk_00880f91 | 0x80;
  }
  if ((tmp_u2 & 0x40000) == 0) goto LAB_00232834;
  tmp_u5 = *(int *)(tmp_i7 + 0xa4) - 0x18;
  if (tmp_u5 < 0x12) {
    tmp_u5 = 1 << ((byte)tmp_u5 & 0x1f);
    if ((tmp_u5 & 0x10040) != 0) {
      g_unk_00880f92 = '(';
      goto LAB_00232834;
    }
    if ((tmp_u5 & 0x20080) != 0) {
      g_unk_00880f92 = ')';
      goto LAB_00232834;
    }
    if ((tmp_u5 & 0x8001) != 0) {
      g_unk_00880f92 = '\'';
      goto LAB_00232834;
    }
  }
  g_unk_00880f91 = g_unk_00880f91 | 2;
LAB_00232834:
  if ((tmp_u2 & 0x10000) == 0) {
    if ((tmp_u2 & 0x20000) != 0) {
      g_unk_00880f91 = g_unk_00880f91 | 0x20;
    }
  }
  else {
    g_unk_00880f91 = g_unk_00880f91 | 0x10;
  }
  if (((local_64 - 2U & 0xfffffffd) == 0) || (local_64 == 7)) {
    g_unk_00880f92 = (char)*(uint32_t *)(tmp_i7 + 0xa4);
  }
  else if ((tmp_u2 & 0x2000) != 0) {
    g_unk_00880f91 = g_unk_00880f91 | 8;
  }
  if ((*(int *)(tmp_i7 + 4) < 3) && ((*(uint *)(tmp_i7 + 0xc) & 0xc000) == 0)) {
    vectoangles(param_2,local_4c);
    SetClientViewAngle(g_entities + param_1 * 0x600,local_4c);
    if ((g_unk_00880f90 & 0x10) == 0) {
      local_58 = 127.0;
      tmp_u3 = 0x81;
      tmp_u6 = 0x7f;
    }
    else {
      local_58 = 64.0;
      tmp_u3 = 0xc0;
      tmp_u6 = 0x40;
    }
    local_3c = local_48;
    local_38 = local_44;
    local_40 = 0;
    AngleVectors(&local_40,&local_34,&local_28,0);
    tmp_u2 = *(uint *)(param_2 + 0x18);
    g_unk_00880fa0 = (char)(short)ROUND((local_2c * *(float *)(param_2 + 0x14) +
                                      local_30 * *(float *)(param_2 + 0x10) +
                                      local_34 * *(float *)(param_2 + 0xc)) * local_58);
    if ((tmp_u2 & 0x880) != 0) {
      g_unk_00880fa0 = tmp_u6;
    }
    if ((tmp_u2 & 0x1100) != 0) {
      g_unk_00880fa0 = tmp_u3;
    }
    g_unk_00880fa1 = (char)(short)ROUND((local_20 * *(float *)(param_2 + 0x14) +
                                      local_24 * *(float *)(param_2 + 0x10) +
                                      local_28 * *(float *)(param_2 + 0xc)) * local_58);
    if ((tmp_u2 & 0x200) != 0) {
      g_unk_00880fa1 = tmp_u6;
    }
    if ((tmp_u2 & 0x400) != 0) {
      g_unk_00880fa1 = tmp_u3;
    }
    if ((tmp_u2 & 4) != 0) {
      g_unk_00880fa2 = tmp_u6;
    }
    if ((tmp_u2 & 8) != 0) {
      g_unk_00880fa2 = tmp_u3;
    }
  }
  else {
    g_unk_00880f90 = g_unk_00880f90 & 0xfe;
    g_unk_00880f91 = g_unk_00880f91 & 0xfe;
  }
  trap_BotUserCommand(param_1,&UpdateBotInput(int,ClientInput_const&)::cmd);
  return;
}

void ETInterface_GetMapExtents(ETInterface *this,AABB_t *param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float tmp_f3;
  AABB_t *pAVar4;
  uint tmp_u5;
  uint tmp_u6;
  bool tmp_b7;
  
  tmp_f1 = g_unk_02a99b94;
  if (g_unk_02a99b8c == 0) {
    tmp_b7 = ((uint)param_1 & 1) != 0;
    tmp_u5 = 0x18;
    if (tmp_b7) {
      *param_1 = (AABB_t)0x0;
      tmp_u5 = 0x17;
      param_1 = param_1 + 1;
    }
    if (((uint)param_1 & 2) != 0) {
      *(uint16_t *)param_1 = 0;
      tmp_u5 = tmp_u5 - 2;
      param_1 = param_1 + 2;
    }
    tmp_u6 = 0;
    do {
      *(uint32_t *)(param_1 + tmp_u6) = 0;
      *(uint32_t *)(param_1 + tmp_u6 + 4) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < (tmp_u5 & 0xfffffff8));
    pAVar4 = param_1 + tmp_u6;
    if ((tmp_u5 & 4) != 0) {
      *(uint32_t *)pAVar4 = 0;
      pAVar4 = pAVar4 + 4;
    }
    if ((tmp_u5 & 2) != 0) {
      *(uint16_t *)pAVar4 = 0;
      pAVar4 = pAVar4 + 2;
    }
    if (tmp_b7) {
      *pAVar4 = (AABB_t)0x0;
    }
  }
  else {
    *(float *)param_1 = g_unk_02a99b94;
    tmp_u2 = g_unk_02a99b98;
    *(uint32_t *)(param_1 + 8) = 0xc77fff00;
    *(uint32_t *)(param_1 + 4) = tmp_u2;
    tmp_f3 = g_unk_02a99b9c;
    *(float *)(param_1 + 0xc) = g_unk_02a99b9c;
    tmp_u2 = g_unk_02a99ba0;
    *(uint32_t *)(param_1 + 0x14) = 0x477fff00;
    *(uint32_t *)(param_1 + 0x10) = tmp_u2;
    if (tmp_f3 < tmp_f1) {
      *(float *)param_1 = tmp_f3;
      *(float *)(param_1 + 0xc) = tmp_f1;
    }
    tmp_f1 = *(float *)(param_1 + 4);
    if (*(float *)(param_1 + 0x10) < tmp_f1) {
      *(float *)(param_1 + 4) = *(float *)(param_1 + 0x10);
      *(float *)(param_1 + 0x10) = tmp_f1;
    }
    tmp_f1 = *(float *)(param_1 + 8);
    if (*(float *)(param_1 + 0x14) < tmp_f1) {
      *(float *)(param_1 + 8) = *(float *)(param_1 + 0x14);
      *(float *)(param_1 + 0x14) = tmp_f1;
    }
  }
  return;
}

int ETInterface_AddBot(ETInterface *this,MessageHelper *param_1)
{
  code tmp_c1;
  uint16_t tmp_u2;
  void *tmp_pc3;
  int *tmp_pi4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  uint8_t *tmp_pu9;
  char *tmp_pc10;
  uint tmp_u11;
  streambuf *psVar12;
  ostream *poVar13;
  uint32_t tmp_u14;
  uint *tmp_pu15;
  int tmp_i16;
  int tmp_i17;
  void *tmp_pc18;
  void *extraout_ECX;
  void *tmp_pc19;
  int tmp_i20;
  void *tmp_pc21;
  void *tmp_pc22;
  void *tmp_pc23;
  byte tmp_b24;
  uint local_4f4;
  allocator local_4e1;
  void *local_4e0;
  void *local_4dc;
  void *local_4d8 [2];
  void *local_4d0;
  void *local_4cc;
  uint *local_4c8 [2];
  void *local_4c0;
  void *local_4bc;
  void *local_4b8;
  uint32_t local_4b4;
  locale local_4b0 [4];
  uint32_t local_4ac;
  void *local_4a8;
  void *local_4a4 [18];
  char acStack_45c [8];
  int aiStack_454 [8];
  uint32_t local_434;
  uint8_t local_430;
  uint8_t local_42f;
  uint32_t local_42c;
  uint32_t local_428;
  uint32_t local_424;
  uint32_t local_420;
  uint32_t local_41c [258];
  uint32_t uStack_14;
  
  tmp_b24 = 0;
  uStack_14 = 0x232c89;
  if ((GHIDRA_FIELD(g_dedicated, 12, 4) == 0) || (9999 < g_unk_00abe908 - g_unk_00abe918)) {
    tmp_i17 = *(int *)(param_1 + 4);
    if (1 < g_unk_00abe900) {
      tmp_pu9 = g_entities;
      tmp_i20 = 1;
      do {
        if ((*(int *)(tmp_pu9 + 0x794) == 0) &&
           ((*(int *)(tmp_pu9 + 0x790) == 0 || (1 < *(int *)(*(int *)(tmp_pu9 + 0x790) + 0x5ac) - 1U))
           )) {
          if (tmp_i20 != 0) {
            tmp_i20 = trap_BotAllocateClient(tmp_i20);
            if (-1 < tmp_i20) {
              tmp_u11 = 0;
              do {
                *(uint32_t *)((int)local_41c + tmp_u11) = 0;
                *(uint32_t *)((int)local_41c + tmp_u11 + 4) = 0;
                tmp_u11 = tmp_u11 + 8;
              } while (tmp_u11 < 0x400);
              std::ios_base::ios_base((ios_base *)local_4a4);
              tmp_u14 = ___xstat64;
              tmp_pc18 = ___isoc99_sscanf;
              local_420 = 0;
              local_4a4[0] = __isoc99_fscanf;
              local_434 = 0;
              local_430 = 0;
              local_42f = 0;
              local_42c = 0;
              local_428 = 0;
              local_424 = 0;
              local_4d8[0] = tmp_pc18;
              *(uint32_t *)((int)local_4d8 + *(int *)(___isoc99_sscanf + -0xc)) = ___xstat64;
              local_4d8[1] = (void *)0x0;
              std::ios::init((streambuf *)
                             ((stringstream *)local_4d8 + *(int *)(___isoc99_sscanf + -0xc)));
              tmp_u7 = __M_widen_init;
              tmp_pc3 = _localtime;
              psVar12 = (streambuf *)((ostream *)&local_4d0 + *(int *)(_localtime + -0xc));
              local_4d0 = tmp_pc3;
              *(uint32_t *)psVar12 = __M_widen_init;
              std::ios::init(psVar12);
              tmp_u8 = _strtod;
              tmp_i6 = _operator_delete;
              *(uint32_t *)((int)local_4d8 + *(int *)(_operator_delete + -0xc)) = _strtod;
              local_4b4 = 0;
              local_4d8[0] = localeconv;
              local_4a4[0] = (void *)&std::stringbuf::vtable;
              local_4d0 = __cxa_atexit;
              local_4cc = setsockopt;
              local_4c8[0] = (uint *)0x0;
              local_4c8[1] = (uint *)0x0;
              local_4c0 = (void *)0x0;
              local_4bc = (void *)0x0;
              local_4b8 = (void *)0x0;
              std::locale::locale(local_4b0);
              local_4ac = 0x18;
              local_4cc = asin;
              local_4a8 = memchr;
              std::ios::init((streambuf *)local_4a4);
              tmp_i16 = *(int *)(local_4d0 + -0xc);
              if (acStack_45c[tmp_i16 + 1] == '\0') {
                tmp_pi4 = *(int **)((int)aiStack_454 + tmp_i16);
                if (tmp_pi4 == (int *)0x0) {
                  tmp_u14 = std::__throw_bad_cast();
                  local_4cc = asin;
                  if ((allocator *)(local_4a8 + -0xc) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    tmp_pc18 = local_4a8 + -4;
                    LOCK();
                    tmp_i17 = *(int *)tmp_pc18;
                    *(int *)tmp_pc18 = *(int *)tmp_pc18 + -1;
                    UNLOCK();
                    if (tmp_i17 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_4a8 + -0xc));
                    }
                  }
                  local_4cc = setsockopt;
                  std::locale::~locale(local_4b0);
                  tmp_i16 = (int)&local_4cc + tmp_i16;
                  std::iostream::~iostream((iostream *)local_4d8);
                  local_4a4[0] = __isoc99_fscanf;
                  std::ios_base::~ios_base((ios_base *)local_4a4);
                  _Unwind_Resume(tmp_u14,tmp_i16);
                }
                if ((char)tmp_pi4[7] == '\0') {
                  std::ctype<char>::_M_widen_init();
                  if (*(void **)(*tmp_pi4 + 0x18) != std::ctype<char>::do_widen) {
                    (**(void **)(*tmp_pi4 + 0x18))(tmp_pi4,0x20);
                  }
                }
                acStack_45c[tmp_i16 + 1] = '\x01';
              }
              acStack_45c[tmp_i16] = '0';
              *(uint32_t *)((int)local_4c8 + *(int *)(local_4d0 + -0xc)) = 0x1b;
              std::__ostream_insert<>((ostream *)&local_4d0,"BOT",3);
              *(uint32_t *)((int)local_4c8 + *(int *)(local_4d0 + -0xc)) = 5;
              poVar13 = (ostream *)std::ostream::operator<<((ostream *)&local_4d0,tmp_i20);
              std::__ostream_insert<>(poVar13,"",0);
              Info_SetValueForKey(local_41c,"name",tmp_i17 + 8);
              Info_SetValueForKey(local_41c,"rate",&g_unk_00270bcb);
              Info_SetValueForKey(local_41c,"snaps",&g_unk_0024a16e);
              Info_SetValueForKey(local_41c,"ip","localhost");
              tmp_pc21 = local_4bc;
              tmp_pc19 = memchr;
              local_4e0 = tmp_pc19;
              if (local_4b8 == (void *)0x0) {
                std::string::assign((string *)&local_4e0);
              }
              else {
                if (local_4c0 < local_4b8) {
                  if (local_4b8 != local_4bc) {
                    if (local_4bc == (void *)0x0) {
                      tmp_u14 = std::__throw_logic_error("basic_string::_S_construct null not valid")
                      ;
                      if ((allocator *)(local_4e0 + -0xc) !=
                          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                        std::string::_Rep::_M_dispose((allocator *)(local_4e0 + -0xc));
                      }
                      std::stringstream::dtor_stringstream((stringstream *)local_4d8);
                      _Unwind_Resume(tmp_u14);
                    }
                    tmp_u11 = (int)local_4b8 - (int)local_4bc;
                    tmp_pu15 = (uint *)std::string::_Rep::_S_create(tmp_u11,0,&local_4e1);
                    tmp_pc19 = (void *)(tmp_pu15 + 3);
                    if (tmp_u11 == 1) {
                      *(void *)(tmp_pu15 + 3) = *tmp_pc21;
                    }
                    else {
                      local_4f4 = tmp_u11;
                      tmp_pc22 = tmp_pc19;
                      if (7 < tmp_u11) {
                        if (((uint)tmp_pc19 & 1) != 0) {
                          tmp_c1 = *tmp_pc21;
                          tmp_pc22 = (void *)((int)tmp_pu15 + 0xd);
                          tmp_pc21 = tmp_pc21 + 1;
                          *(void *)(tmp_pu15 + 3) = tmp_c1;
                          local_4f4 = tmp_u11 - 1;
                        }
                        tmp_pc23 = tmp_pc22;
                        if (((uint)tmp_pc22 & 2) != 0) {
                          tmp_u2 = *(uint16_t *)tmp_pc21;
                          tmp_pc23 = tmp_pc22 + 2;
                          tmp_pc21 = tmp_pc21 + 2;
                          *(uint16_t *)tmp_pc22 = tmp_u2;
                          local_4f4 = local_4f4 - 2;
                        }
                        tmp_pc22 = tmp_pc23;
                        if (((uint)tmp_pc23 & 4) != 0) {
                          tmp_u5 = *(uint32_t *)tmp_pc21;
                          tmp_pc22 = tmp_pc23 + 4;
                          tmp_pc21 = tmp_pc21 + 4;
                          *(uint32_t *)tmp_pc23 = tmp_u5;
                          local_4f4 = local_4f4 - 4;
                        }
                      }
                      for (; local_4f4 != 0; local_4f4 = local_4f4 - 1) {
                        *tmp_pc22 = *tmp_pc21;
                        tmp_pc21 = tmp_pc21 + (uint)tmp_b24 * -2 + 1;
                        tmp_pc22 = tmp_pc22 + (uint)tmp_b24 * -2 + 1;
                      }
                    }
                    if (tmp_pu15 != &std::string::_Rep::_S_empty_rep_storage) {
                      tmp_pu15[2] = 0;
                      *tmp_pu15 = tmp_u11;
                      *(uint8_t *)((int)tmp_pu15 + tmp_u11 + 0xc) = 0;
                    }
                  }
                  local_4dc = tmp_pc19;
                  std::string::assign((string *)&local_4e0);
                }
                else {
                  if (local_4c0 != local_4bc) {
                    tmp_pc19 = local_4c0;
                    if ((local_4bc == (void *)0x0) && (local_4c0 != (void *)0x0)) {
                      std::__throw_logic_error("basic_string::_S_construct null not valid");
                      tmp_pc19 = extraout_ECX;
                    }
                    tmp_u11 = (int)tmp_pc19 - (int)tmp_pc21;
                    tmp_pu15 = (uint *)std::string::_Rep::_S_create(tmp_u11,0,&local_4e1);
                    tmp_pc19 = (void *)(tmp_pu15 + 3);
                    if (tmp_u11 == 1) {
                      *(void *)(tmp_pu15 + 3) = *tmp_pc21;
                    }
                    else {
                      local_4f4 = tmp_u11;
                      tmp_pc22 = tmp_pc19;
                      if (7 < tmp_u11) {
                        if (((uint)tmp_pc19 & 1) != 0) {
                          tmp_c1 = *tmp_pc21;
                          tmp_pc22 = (void *)((int)tmp_pu15 + 0xd);
                          tmp_pc21 = tmp_pc21 + 1;
                          *(void *)(tmp_pu15 + 3) = tmp_c1;
                          local_4f4 = tmp_u11 - 1;
                        }
                        tmp_pc23 = tmp_pc22;
                        if (((uint)tmp_pc22 & 2) != 0) {
                          tmp_u2 = *(uint16_t *)tmp_pc21;
                          tmp_pc23 = tmp_pc22 + 2;
                          tmp_pc21 = tmp_pc21 + 2;
                          *(uint16_t *)tmp_pc22 = tmp_u2;
                          local_4f4 = local_4f4 - 2;
                        }
                        tmp_pc22 = tmp_pc23;
                        if (((uint)tmp_pc23 & 4) != 0) {
                          tmp_u5 = *(uint32_t *)tmp_pc21;
                          tmp_pc22 = tmp_pc23 + 4;
                          tmp_pc21 = tmp_pc21 + 4;
                          *(uint32_t *)tmp_pc23 = tmp_u5;
                          local_4f4 = local_4f4 - 4;
                        }
                      }
                      for (; local_4f4 != 0; local_4f4 = local_4f4 - 1) {
                        *tmp_pc22 = *tmp_pc21;
                        tmp_pc21 = tmp_pc21 + (uint)tmp_b24 * -2 + 1;
                        tmp_pc22 = tmp_pc22 + (uint)tmp_b24 * -2 + 1;
                      }
                    }
                    if (tmp_pu15 != &std::string::_Rep::_S_empty_rep_storage) {
                      tmp_pu15[2] = 0;
                      *tmp_pu15 = tmp_u11;
                      *(uint8_t *)((int)tmp_pu15 + tmp_u11 + 0xc) = 0;
                    }
                  }
                  local_4dc = tmp_pc19;
                  std::string::assign((string *)&local_4e0);
                }
                if ((allocator *)(local_4dc + -0xc) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  tmp_pc19 = local_4dc + -4;
                  tmp_i17 = *(int *)tmp_pc19;
                  *(int *)tmp_pc19 = *(int *)tmp_pc19 + -1;
                  UNLOCK();
                  if (tmp_i17 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_4dc + -0xc));
                  }
                }
              }
              Info_SetValueForKey(local_41c,"n_guid",local_4e0);
              if ((allocator *)(local_4e0 + -0xc) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                tmp_pc19 = local_4e0 + -4;
                tmp_i17 = *(int *)tmp_pc19;
                *(int *)tmp_pc19 = *(int *)tmp_pc19 + -1;
                UNLOCK();
                if (tmp_i17 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_4e0 + -0xc));
                }
              }
              Info_SetValueForKey(local_41c,&g_unk_0026019a,"00-00-00-00-00-00");
              Info_SetValueForKey(local_41c,"cl_punkbuster",&g_unk_0024bfa6);
              Info_SetValueForKey(local_41c,"cl_anonymous",&g_unk_0024bfa6);
              trap_SetUserinfo(tmp_i20,local_41c);
              tmp_i16 = ClientConnect(tmp_i20,1,1);
              tmp_i17 = tmp_i20;
              if (tmp_i16 != 0) {
                tmp_pc19 = *(void **)(*(int *)this + 0x9c);
                tmp_i17 = va("Could not connect bot: %s",tmp_i16);
                if (tmp_pc19 == PrintError) {
                  if (tmp_i17 != 0) {
                    G_Printf("%s%s\n",&g_unk_00248060,tmp_i17);
                  }
                }
                else {
                  (*tmp_pc19)(this,tmp_i17);
                }
                tmp_i17 = -1;
              }
              if (*(int *)(g_entities + tmp_i20 * 0x600 + 0x194) == 0) {
                tmp_i17 = -1;
              }
              local_4d8[0] = localeconv;
              local_4a4[0] = (void *)&std::stringbuf::vtable;
              local_4d0 = __cxa_atexit;
              local_4cc = asin;
              if ((allocator *)(local_4a8 + -0xc) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                tmp_pc19 = local_4a8 + -4;
                tmp_i20 = *(int *)tmp_pc19;
                *(int *)tmp_pc19 = *(int *)tmp_pc19 + -1;
                UNLOCK();
                if (tmp_i20 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_4a8 + -0xc));
                }
              }
              local_4cc = setsockopt;
              std::locale::~locale(local_4b0);
              *(uint32_t *)((int)local_4d8 + *(int *)(tmp_i6 + -0xc)) = tmp_u8;
              local_4d0 = tmp_pc3;
              *(uint32_t *)((int)&local_4d0 + *(int *)(tmp_pc3 + -0xc)) = tmp_u7;
              local_4d8[0] = tmp_pc18;
              *(uint32_t *)((int)local_4d8 + *(int *)(tmp_pc18 + -0xc)) = tmp_u14;
              local_4a4[0] = __isoc99_fscanf;
              std::ios_base::~ios_base((ios_base *)local_4a4);
              return tmp_i17;
            }
            tmp_pc18 = *(void **)(*(int *)this + 0x9c);
            if (tmp_pc18 == PrintError) {
              tmp_pc10 = "Could not add bot!";
              goto LAB_00232d2b;
            }
            tmp_pc10 = "Could not add bot!";
            goto LAB_0023358d;
          }
          break;
        }
        tmp_i20 = tmp_i20 + 1;
        tmp_pu9 = tmp_pu9 + 0x600;
      } while (tmp_i20 != g_unk_00abe900);
    }
    tmp_pc18 = *(void **)(*(int *)this + 0x9c);
    if (tmp_pc18 == PrintError) {
      tmp_pc10 = "Could not add bot!, no free slots!";
LAB_00232d2b:
      G_Printf("%s%s\n",&g_unk_00248060,tmp_pc10);
    }
    else {
      tmp_pc10 = "Could not add bot!, no free slots!";
LAB_0023358d:
      (*tmp_pc18)(this,tmp_pc10);
    }
  }
  return -1;
}

void ETInterface_RemoveBot(ETInterface *this,MessageHelper *param_1)
{
  uint tmp_u1;
  char tmp_c2;
  int tmp_i3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  int tmp_i6;
  uint8_t local_64 [36];
  uint8_t local_40 [48];
  
  tmp_i3 = *(int *)(param_1 + 4);
  tmp_u1 = *(uint *)(tmp_i3 + 0x40);
  if (tmp_u1 == 0xffffffff) {
    Q_strncpyz(local_40,tmp_i3,0x24);
    Q_CleanStr(local_40);
    if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
      tmp_pu5 = g_entities;
      tmp_i6 = 0;
      tmp_i3 = GHIDRA_FIELD(g_maxclients, 12, 4);
      do {
        if ((*(int *)(tmp_pu5 + 0x194) != 0) &&
           (tmp_c2 = IsBot((gentity_s *)tmp_pu5), tmp_i3 = GHIDRA_FIELD(g_maxclients, 12, 4), tmp_c2 != '\0')) {
          Q_strncpyz(local_64,*(int *)(tmp_pu5 + 400) + 0x5f8,0x24);
          Q_CleanStr(local_64);
          tmp_i4 = Q_stricmp(local_64,local_40);
          tmp_i3 = GHIDRA_FIELD(g_maxclients, 12, 4);
          if (tmp_i4 == 0) {
            trap_DropClient(tmp_i6,"disconnected",0);
            tmp_i3 = GHIDRA_FIELD(g_maxclients, 12, 4);
          }
        }
        tmp_i6 = tmp_i6 + 1;
        tmp_pu5 = tmp_pu5 + 0x600;
      } while (tmp_i6 < tmp_i3);
    }
  }
  else if ((tmp_u1 < 0x40) &&
          (tmp_c2 = IsBot((gentity_s *)(g_entities + tmp_u1 * 0x600)), tmp_c2 != '\0')) {
    trap_DropClient(*(uint32_t *)(tmp_i3 + 0x40),"disconnected",0);
  }
  return;
}

bool ETInterface_DoesEntityStillExist(ETInterface *this,GameEntity *param_1)
{
  int tmp_i1;
  
  if ((param_1[1] & 0x80) == 0) {
    tmp_i1 = EntityFromHandle(*(uint32_t *)param_1);
    return tmp_i1 != 0;
  }
  return false;
}

int ETInterface_IDFromEntity(uint32_t this,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = EntityFromHandle(param_2);
  if (tmp_i1 == 0) {
    tmp_i1 = -1;
  }
  else {
    tmp_i1 = (tmp_i1 + -0x93e4a0 >> 9) * -0x55555555;
    if (0x3ff < tmp_i1) {
      tmp_i1 = -1;
    }
  }
  return tmp_i1;
}

// ETInterface::GetCurrentAmmo(GameEntity, int, eFireMode, int&, int&)

uint32_t ETInterface::GetCurrentAmmo
          (uint32_t this,uint32_t param_2,int param_3,uint32_t param_4,int *param_5,
          int *param_6)

{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_i1 = EntityFromHandle(param_2);
  tmp_u2 = 3;
  if (((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x194) != 0)) && (*(int *)(tmp_i1 + 400) != 0)) {
    tmp_u2 = _weaponBotToGame(param_3);
    tmp_i3 = BG_FindAmmoForWeapon(tmp_u2);
    tmp_i5 = *(int *)(tmp_i1 + 400);
    tmp_i4 = BG_FindClipForWeapon(tmp_u2);
    tmp_i1 = *(int *)(tmp_i1 + 400);
    *param_5 = *(int *)(tmp_i1 + (tmp_i3 + 100) * 4) + *(int *)(tmp_i5 + (tmp_i4 + 0xa4) * 4);
    switch(tmp_u2) {
    default:
      tmp_i5 = *(int *)(ammoTableMP + tmp_i3 * 0x48 + 8);
      break;
    case 1:
    case 4:
    case 5:
    case 6:
    case 9:
    case 0xb:
    case 0xc:
    case 0xf:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x21:
    case 0x2a:
    case 0x2b:
    case 0x2f:
    case 0x33:
      tmp_i5 = 0;
    }
    tmp_i1 = BG_MaxAmmoForWeapon(tmp_u2,tmp_i1 + 0xc30);
    *param_6 = tmp_i5 + tmp_i1;
    tmp_u2 = 0;
  }
  return tmp_u2;
}

// ETInterface::GetCurrentWeaponClip(GameEntity, eFireMode, int&, int&)

uint32_t ETInterface::GetCurrentWeaponClip
          (uint32_t this,uint32_t param_2,uint32_t param_3,uint32_t *param_4,
          uint32_t *param_5)

{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  tmp_i2 = EntityFromHandle(param_2);
  tmp_u3 = 3;
  if (((tmp_i2 != 0) && (*(int *)(tmp_i2 + 0x194) != 0)) &&
     (tmp_i2 = *(int *)(tmp_i2 + 400), tmp_i2 != 0)) {
    tmp_i1 = *(int *)(tmp_i2 + 0xa4);
    tmp_i4 = BG_FindClipForWeapon(tmp_i1);
    *param_4 = *(uint32_t *)(tmp_i2 + (tmp_i4 + 0xa4) * 4);
    switch(tmp_i1) {
    default:
      *param_5 = *(uint32_t *)(ammoTableMP + tmp_i1 * 0x48 + 8);
      tmp_u3 = 0;
      break;
    case 1:
    case 4:
    case 5:
    case 6:
    case 9:
    case 0xb:
    case 0xc:
    case 0xf:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x21:
    case 0x2a:
    case 0x2b:
    case 0x2f:
    case 0x33:
      *param_5 = 0;
      tmp_u3 = 0;
    }
  }
  return tmp_u3;
}

// ETInterface::GetEntityWorldOBB(GameEntity, float*, float*, float*, float*, float*)

uint32_t ETInterface::GetEntityWorldOBB
          (uint32_t this,uint32_t param_2,float *param_3,float *param_4,float *param_5,
          float *param_6,float *param_7)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  uint32_t tmp_u7;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i6 = EntityFromHandle(param_2);
  tmp_u7 = 3;
  if (tmp_i6 != 0) {
    AnglesToAxis(tmp_i6 + 0x174,&local_40);
    tmp_f3 = (*(float *)(tmp_i6 + 0x140) + *(float *)(tmp_i6 + 0x134)) * 0.5;
    tmp_f5 = (*(float *)(tmp_i6 + 0x144) + *(float *)(tmp_i6 + 0x138)) * 0.5;
    tmp_f4 = (*(float *)(tmp_i6 + 0x148) + *(float *)(tmp_i6 + 0x13c)) * 0.5;
    tmp_f1 = *(float *)(tmp_i6 + 0x16c);
    tmp_f2 = *(float *)(tmp_i6 + 0x170);
    *param_3 = tmp_f4 * local_28 + local_34 * tmp_f5 + local_40 * tmp_f3 + *(float *)(tmp_i6 + 0x168);
    param_3[1] = local_24 * tmp_f4 + local_30 * tmp_f5 + local_3c * tmp_f3 + tmp_f1;
    param_3[2] = local_20 * tmp_f4 + tmp_f5 * local_2c + tmp_f3 * local_38 + tmp_f2;
    *param_4 = local_40;
    param_4[1] = local_3c;
    param_4[2] = local_38;
    *param_5 = local_34;
    param_5[1] = local_30;
    param_5[2] = local_2c;
    *param_6 = local_28;
    param_6[1] = local_24;
    param_6[2] = local_20;
    *param_7 = (*(float *)(tmp_i6 + 0x140) - *(float *)(tmp_i6 + 0x134)) * 0.5;
    param_7[1] = (*(float *)(tmp_i6 + 0x144) - *(float *)(tmp_i6 + 0x138)) * 0.5;
    param_7[2] = (*(float *)(tmp_i6 + 0x148) - *(float *)(tmp_i6 + 0x13c)) * 0.5;
    tmp_u7 = 0;
  }
  return tmp_u7;
}

ETInterface_GetEntityLocalAABB(uint32_t this,uint32_t param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  uint32_t tmp_u7;
  int tmp_i8;
  int tmp_i9;
  
  tmp_i6 = EntityFromHandle(param_2);
  tmp_u7 = 3;
  if ((tmp_i6 != 0) && (*(int *)(tmp_i6 + 0x194) != 0)) {
    tmp_i8 = tmp_i6;
    if (*(int *)(tmp_i6 + 4) == 0x20) {
      tmp_i8 = *(int *)(tmp_i6 + 0x218);
      if (*(int *)(tmp_i6 + 0x218) == 0) {
        tmp_i8 = tmp_i6;
      }
      tmp_i8 = G_ConstructionForTeam(tmp_i8,1);
      tmp_i9 = *(int *)(tmp_i6 + 0x218);
      if (*(int *)(tmp_i6 + 0x218) == 0) {
        tmp_i9 = tmp_i6;
      }
      tmp_i9 = G_ConstructionForTeam(tmp_i9,2);
      if ((tmp_i8 == 0) && (tmp_i8 = tmp_i6, tmp_i9 != 0)) {
        tmp_i8 = tmp_i9;
      }
    }
    tmp_f1 = *(float *)(tmp_i8 + 0x134);
    tmp_u7 = 0;
    tmp_i6 = *(int *)(tmp_i8 + 0x5c0);
    *param_3 = tmp_f1;
    tmp_f2 = *(float *)(tmp_i8 + 0x138);
    param_3[1] = tmp_f2;
    tmp_f3 = *(float *)(tmp_i8 + 0x13c);
    param_3[2] = tmp_f3;
    tmp_f4 = *(float *)(tmp_i8 + 0x140);
    param_3[3] = tmp_f4;
    tmp_f5 = *(float *)(tmp_i8 + 0x144);
    param_3[4] = tmp_f5;
    param_3[5] = *(float *)(tmp_i8 + 0x148);
    if (tmp_i6 == 0x1908e) {
      if ((((tmp_f1 == 0.0) && (tmp_f4 == 0.0)) && (tmp_f2 == 0.0)) &&
         (((tmp_f5 == 0.0 && (tmp_f3 == 0.0)) && (param_3[5] == 0.0)))) {
        tmp_u7 = 0;
        *param_3 = -8.0;
        param_3[3] = 8.0;
        param_3[1] = -8.0;
        param_3[4] = 8.0;
        param_3[2] = -8.0;
        param_3[5] = 48.0;
      }
      else {
        tmp_u7 = 0;
      }
    }
  }
  return tmp_u7;
}

ETInterface_GetEntityPosition(uint32_t this,uint32_t param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  uint32_t tmp_u7;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_i6 = EntityFromHandle(param_2);
  tmp_u7 = 3;
  if ((tmp_i6 != 0) && (*(int *)(tmp_i6 + 0x194) != 0)) {
    if (*(int *)(tmp_i6 + 400) != 0) {
      *param_3 = *(float *)(tmp_i6 + 0x168);
      param_3[1] = *(float *)(tmp_i6 + 0x16c);
      param_3[2] = *(float *)(tmp_i6 + 0x170);
      return 0;
    }
    AnglesToAxis(tmp_i6 + 0x174,&local_30);
    tmp_f3 = (*(float *)(tmp_i6 + 0x140) + *(float *)(tmp_i6 + 0x134)) * 0.5;
    tmp_f5 = (*(float *)(tmp_i6 + 0x144) + *(float *)(tmp_i6 + 0x138)) * 0.5;
    tmp_f4 = (*(float *)(tmp_i6 + 0x148) + *(float *)(tmp_i6 + 0x13c)) * 0.5;
    tmp_f1 = *(float *)(tmp_i6 + 0x16c);
    tmp_f2 = *(float *)(tmp_i6 + 0x170);
    *param_3 = tmp_f4 * local_18 + local_24 * tmp_f5 + local_30 * tmp_f3 + *(float *)(tmp_i6 + 0x168);
    param_3[1] = local_14 * tmp_f4 + local_20 * tmp_f5 + local_2c * tmp_f3 + tmp_f1;
    param_3[2] = local_10 * tmp_f4 + tmp_f5 * local_1c + tmp_f3 * local_28 + tmp_f2;
    tmp_u7 = 0;
  }
  return tmp_u7;
}

ETInterface_GetEntityVelocity(uint32_t this,uint32_t param_2,float *param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = EntityFromHandle(param_2);
  tmp_u2 = 3;
  if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x194) != 0)) {
    if (((*(int *)(tmp_i1 + 400) != 0) && (tmp_i1 + -0x93e4a0 < 0x18000)) ||
       (*(int *)(tmp_i1 + 4) != 4)) {
      *param_3 = *(float *)(tmp_i1 + 0x24);
      param_3[1] = *(float *)(tmp_i1 + 0x28);
      param_3[2] = *(float *)(tmp_i1 + 0x2c);
      return 0;
    }
    *param_3 = (*(float *)(tmp_i1 + 0x168) - *(float *)(tmp_i1 + 0x4d8)) * 50.0;
    param_3[1] = (*(float *)(tmp_i1 + 0x16c) - *(float *)(tmp_i1 + 0x4dc)) * 50.0;
    param_3[2] = (*(float *)(tmp_i1 + 0x170) - *(float *)(tmp_i1 + 0x4e0)) * 50.0;
    tmp_u2 = 0;
  }
  return tmp_u2;
}

// ETInterface::GetEntityOrientation(GameEntity, float*, float*, float*)

uint32_t ETInterface::GetEntityOrientation
          (uint32_t this,uint32_t param_2,uint32_t param_3,uint32_t param_4,
          uint32_t param_5)

{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = EntityFromHandle(param_2);
  tmp_u2 = 3;
  if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x194) != 0)) {
    if (*(int *)(tmp_i1 + 400) != 0) {
      AngleVectors(*(int *)(tmp_i1 + 400) + 0xb0,param_3,param_4,param_5);
      return 0;
    }
    AngleVectors(tmp_i1 + 0x174,param_3,param_4,param_5);
    tmp_u2 = 0;
  }
  return tmp_u2;
}

ETInterface_GetEntityCategory(uint32_t this,uint32_t param_2,uint *param_3)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  
  tmp_i1 = EntityFromHandle(param_2);
  if (tmp_i1 == 0) {
    return 3;
  }
  tmp_i2 = *(int *)(tmp_i1 + 400);
  if (tmp_i2 == 0) {
    switch(*(uint32_t *)(tmp_i1 + 4)) {
    case 0:
      goto _L723;
    default:
      goto LAB_002341f5;
    case 2:
_L732:
      if ((*(byte *)(tmp_i1 + 0x14d) & 1) == 0) {
        return 3;
      }
      tmp_i2 = Q_strncmp(*(uint32_t *)(tmp_i1 + 0x1a4),"item_health",0xb);
      if (tmp_i2 == 0) {
        *param_3 = *param_3 | 0x90;
        return 0;
      }
      tmp_i2 = Q_strncmp(*(uint32_t *)(tmp_i1 + 0x1a4),"weapon_magicammo",0x10);
      if (tmp_i2 == 0) {
        *param_3 = *param_3 | 0x30;
        return 0;
      }
      tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"item_treasure");
      if (tmp_i2 != 0) {
        if (*(int *)(tmp_i1 + 0x33c) == 0) {
          return 3;
        }
        if (*(int *)(*(int *)(tmp_i1 + 0x33c) + 0x24) != 1) {
          return 3;
        }
        *param_3 = *param_3 | 0x50;
        return 0;
      }
      *param_3 = *param_3 | 0x10;
      return 0;
    case 3:
_L737:
      switch(*(uint32_t *)(tmp_i1 + 0xe8)) {
      case 4:
      case 5:
      case 9:
      case 0xd:
      case 0xf:
      case 0x15:
      case 0x1a:
      case 0x24:
      case 0x25:
      case 0x2a:
        break;
      default:
        tmp_i1 = Q_strncmp(*(uint32_t *)(tmp_i1 + 0x1a4),"air strike",0xb);
        if (tmp_i1 != 0) {
          return 3;
        }
        break;
      case 0x19:
      case 0x33:
        *param_3 = *param_3 | 0x141000;
        return 0;
      case 0x1c:
        *param_3 = *param_3 | 4;
        return 0;
      }
      goto _L743;
    case 4:
_L744:
      if (*(int *)(tmp_i1 + 0x5c0) == 0x27cac) {
        tmp_i2 = *(int *)(tmp_i1 + 0x2c8);
        tmp_u3 = *param_3 | 0x40800;
        if (*(int *)(tmp_i1 + 0x1b8) != 0) {
          tmp_u3 = *param_3 | 0x40002;
        }
        *param_3 = tmp_u3 | 0x8000;
        if (tmp_i2 < 1) {
          return 0;
        }
        *param_3 = tmp_u3 | 0x8008;
        return 0;
      }
      tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair_hiback");
      if (((tmp_i2 != 0) &&
          (tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair"), tmp_i2 != 0)) &&
         (tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair_side"), tmp_i2 != 0)) {
        return 3;
      }
      if (*(int *)(tmp_i1 + 0x2c8) < 1) {
        return 0;
      }
      if (*(int *)(tmp_i1 + 0x2cc) != 1) {
        return 0;
      }
      *param_3 = *param_3 | 8;
      return 0;
    case 0xe:
_L751:
      if ((*(byte *)(tmp_i1 + 0x1a8) & 0x20) != 0) {
        return 3;
      }
      if (*(int *)(tmp_i1 + 0x4f4) - 1U < 2) {
        return 3;
      }
      *param_3 = *param_3 | 0x40008;
      return 0;
    case 0x19:
      goto _L743;
    case 0x26:
      goto _L736;
    case 0x29:
_L750:
      if (*(int *)(tmp_i1 + 0x2c8) < 1) {
        return 3;
      }
      if (*(int *)(tmp_i1 + 0x458) - 1U < 2) {
        return 3;
      }
      goto LAB_0023436e;
    case 0x31:
    case 0x32:
_L753:
      *param_3 = *param_3 | 0x40010;
      return 0;
    }
  }
  if (tmp_i1 + -0x93e4a0 < 0x18000) {
_L721:
    if (((*(int *)(tmp_i1 + 0x458) != 1) && (*(int *)(tmp_i2 + 4) != 2)) &&
       (*(int *)(tmp_i2 + 3000) - 1U < 2)) {
      if (-0xaf < *(int *)(tmp_i1 + 0x2c8)) {
        if (*(int *)(tmp_i2 + 0x154) == 0) {
          *param_3 = *param_3 | 8;
        }
        *param_3 = *param_3 | 1;
        return 0;
      }
_L736:
      *param_3 = *param_3 | 0x4000;
      return 0;
    }
LAB_002341f5:
    return 3;
  }
  switch(*(uint32_t *)(tmp_i1 + 4)) {
  case 0:
    goto _L723;
  case 1:
    goto _L721;
  case 2:
    goto _L732;
  case 3:
    goto _L737;
  case 4:
    goto _L744;
  default:
    goto LAB_002341f5;
  case 0xe:
    goto _L751;
  case 0x19:
    break;
  case 0x26:
    goto _L736;
  case 0x29:
    goto _L750;
  case 0x31:
  case 0x32:
    goto _L753;
  }
_L743:
  *param_3 = *param_3 | 0x1004;
  return 0;
_L723:
  if (*(int *)(tmp_i1 + 0x5c0) == 0x3f73d) {
    if (*(int *)(tmp_i1 + 0xf8) == 0x10) goto LAB_0023447d;
  }
  else {
    tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"func_button");
    if (tmp_i2 == 0) {
LAB_0023447d:
      *param_3 = *param_3 | 0x8400;
      return 0;
    }
    if (*(int *)(tmp_i1 + 0x5c0) != 0x1908e) {
      return 3;
    }
    if (0 < *(int *)(tmp_i1 + 0x2c8)) {
      if (*(int *)(tmp_i1 + 0x458) - 1U < 2) {
        return 0;
      }
LAB_0023436e:
      *param_3 = *param_3 | 0x2008;
      return 0;
    }
  }
  return 0;
}

// ETInterface::GetEntityBonePosition(GameEntity, int, float*)

uint32_t ETInterface::GetEntityBonePosition
          (ETInterface *this,uint32_t param_2,uint32_t param_3,float *param_4)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  uint32_t tmp_u7;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  if (*(void **)(*(int *)this + 0x4c) != GetEntityPosition) {
    tmp_u7 = (**(void **)(*(int *)this + 0x4c))(this,param_2,param_4);
    return tmp_u7;
  }
  tmp_i6 = EntityFromHandle(param_2);
  tmp_u7 = 3;
  if ((tmp_i6 != 0) && (*(int *)(tmp_i6 + 0x194) != 0)) {
    if (*(int *)(tmp_i6 + 400) != 0) {
      *param_4 = *(float *)(tmp_i6 + 0x168);
      param_4[1] = *(float *)(tmp_i6 + 0x16c);
      param_4[2] = *(float *)(tmp_i6 + 0x170);
      return 0;
    }
    AnglesToAxis(tmp_i6 + 0x174,&local_30);
    tmp_f3 = (*(float *)(tmp_i6 + 0x140) + *(float *)(tmp_i6 + 0x134)) * 0.5;
    tmp_f5 = (*(float *)(tmp_i6 + 0x144) + *(float *)(tmp_i6 + 0x138)) * 0.5;
    tmp_f4 = (*(float *)(tmp_i6 + 0x148) + *(float *)(tmp_i6 + 0x13c)) * 0.5;
    tmp_f1 = *(float *)(tmp_i6 + 0x16c);
    tmp_f2 = *(float *)(tmp_i6 + 0x170);
    *param_4 = tmp_f4 * local_18 + local_24 * tmp_f5 + local_30 * tmp_f3 + *(float *)(tmp_i6 + 0x168);
    param_4[1] = local_14 * tmp_f4 + local_20 * tmp_f5 + local_2c * tmp_f3 + tmp_f1;
    param_4[2] = local_10 * tmp_f4 + tmp_f5 * local_1c + tmp_f3 * local_28 + tmp_f2;
    tmp_u7 = 0;
  }
  return tmp_u7;
}

ETInterface_GetEntityEyePosition(ETInterface *this,uint32_t param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  if (*(void **)(*(int *)this + 0x4c) == GetEntityPosition) {
    tmp_i6 = EntityFromHandle(param_2);
    if ((tmp_i6 != 0) && (*(int *)(tmp_i6 + 0x194) != 0)) {
      if (*(int *)(tmp_i6 + 400) == 0) {
        AnglesToAxis(tmp_i6 + 0x174,&local_30);
        tmp_f3 = (*(float *)(tmp_i6 + 0x140) + *(float *)(tmp_i6 + 0x134)) * 0.5;
        tmp_f5 = (*(float *)(tmp_i6 + 0x144) + *(float *)(tmp_i6 + 0x138)) * 0.5;
        tmp_f4 = (*(float *)(tmp_i6 + 0x148) + *(float *)(tmp_i6 + 0x13c)) * 0.5;
        tmp_f1 = *(float *)(tmp_i6 + 0x16c);
        tmp_f2 = *(float *)(tmp_i6 + 0x170);
        *param_3 = tmp_f4 * local_18 +
                   local_24 * tmp_f5 + local_30 * tmp_f3 + *(float *)(tmp_i6 + 0x168);
        param_3[1] = local_14 * tmp_f4 + local_20 * tmp_f5 + local_2c * tmp_f3 + tmp_f1;
        param_3[2] = local_10 * tmp_f4 + tmp_f5 * local_1c + tmp_f3 * local_28 + tmp_f2;
      }
      else {
        *param_3 = *(float *)(tmp_i6 + 0x168);
        param_3[1] = *(float *)(tmp_i6 + 0x16c);
        param_3[2] = *(float *)(tmp_i6 + 0x170);
      }
LAB_002347ec:
      tmp_i6 = EntityFromHandle(param_2);
      if ((tmp_i6 != 0) && (*(int *)(tmp_i6 + 400) != 0)) {
        param_3[2] = (float)*(int *)(*(int *)(tmp_i6 + 400) + 0xbc) + param_3[2];
        return 0;
      }
      return 0;
    }
  }
  else {
    tmp_i6 = (**(void **)(*(int *)this + 0x4c))(this,param_2,param_3);
    if (tmp_i6 == 0) goto LAB_002347ec;
  }
  return 3;
}

ETInterface_GetEntityWorldAABB(ETInterface *this,uint32_t param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i4 = EntityFromHandle(param_2);
  tmp_u5 = 3;
  if ((tmp_i4 != 0) && (*(int *)(tmp_i4 + 0x194) != 0)) {
    tmp_i6 = tmp_i4;
    if (*(int *)(tmp_i4 + 4) == 0x20) {
      tmp_i6 = *(int *)(tmp_i4 + 0x218);
      if (*(int *)(tmp_i4 + 0x218) == 0) {
        tmp_i6 = tmp_i4;
      }
      tmp_i6 = G_ConstructionForTeam(tmp_i6,1);
      tmp_i7 = *(int *)(tmp_i4 + 0x218);
      if (*(int *)(tmp_i4 + 0x218) == 0) {
        tmp_i7 = tmp_i4;
      }
      tmp_i7 = G_ConstructionForTeam(tmp_i7,2);
      if ((tmp_i6 == 0) && (tmp_i6 = tmp_i4, tmp_i7 != 0)) {
        tmp_i6 = tmp_i7;
      }
    }
    tmp_i4 = *(int *)(tmp_i6 + 400);
    *param_3 = *(float *)(tmp_i6 + 0x150);
    param_3[1] = *(float *)(tmp_i6 + 0x154);
    tmp_f1 = *(float *)(tmp_i6 + 0x158);
    param_3[2] = tmp_f1;
    param_3[3] = *(float *)(tmp_i6 + 0x15c);
    param_3[4] = *(float *)(tmp_i6 + 0x160);
    tmp_f2 = *(float *)(tmp_i6 + 0x164);
    param_3[5] = tmp_f2;
    if (tmp_i4 != 0) {
      param_3[2] = tmp_f1 + 2.0;
      param_3[5] = tmp_f2 + 2.0;
    }
    tmp_u5 = 0;
    if (*(int *)(tmp_i6 + 0x5c0) == 0x1908e) {
      if ((((((*param_3 == 0.0) && (param_3[3] == 0.0)) && (param_3[1] == 0.0)) &&
           (((param_3[4] == 0.0 && (param_3[2] == 0.0)) && (param_3[5] == 0.0)))) ||
          ((param_3[3] < *(float *)(tmp_i6 + 0x168) || (*(float *)(tmp_i6 + 0x168) < *param_3)))) ||
         ((param_3[4] < *(float *)(tmp_i6 + 0x16c) ||
          (((*(float *)(tmp_i6 + 0x16c) < param_3[1] || (param_3[5] < *(float *)(tmp_i6 + 0x170))) ||
           (*(float *)(tmp_i6 + 0x170) < param_3[2])))))) {
        local_70 = 0.0;
        local_6c = 0.0;
        local_68 = 0.0;
        local_64 = -8.0;
        local_60 = -8.0;
        local_5c = -8.0;
        local_58 = 8.0;
        local_54 = 8.0;
        local_50 = 48.0;
        if (*(void **)(*(int *)this + 0x4c) == GetEntityPosition) {
          tmp_i4 = EntityFromHandle(param_2);
          if ((tmp_i4 != 0) && (*(int *)(tmp_i4 + 0x194) != 0)) {
            if (*(int *)(tmp_i4 + 400) == 0) {
              AnglesToAxis(tmp_i4 + 0x174,&local_40);
              tmp_f1 = (*(float *)(tmp_i4 + 0x140) + *(float *)(tmp_i4 + 0x134)) * 0.5;
              tmp_f3 = (*(float *)(tmp_i4 + 0x144) + *(float *)(tmp_i4 + 0x138)) * 0.5;
              tmp_f2 = (*(float *)(tmp_i4 + 0x148) + *(float *)(tmp_i4 + 0x13c)) * 0.5;
              local_6c = local_24 * tmp_f2 +
                         local_30 * tmp_f3 + *(float *)(tmp_i4 + 0x16c) + local_3c * tmp_f1;
              local_68 = local_20 * tmp_f2 +
                         tmp_f3 * local_2c + tmp_f1 * local_38 + *(float *)(tmp_i4 + 0x170);
              local_70 = tmp_f2 * local_28 +
                         local_34 * tmp_f3 + local_40 * tmp_f1 + *(float *)(tmp_i4 + 0x168);
            }
            else {
              local_70 = *(float *)(tmp_i4 + 0x168);
              local_6c = *(float *)(tmp_i4 + 0x16c);
              local_68 = *(float *)(tmp_i4 + 0x170);
            }
          }
        }
        else {
          (**(void **)(*(int *)this + 0x4c))(this,param_2,&local_70);
        }
        tmp_f1 = local_58;
        if (local_64 < local_58) {
          tmp_f1 = local_64;
        }
        if (local_64 <= local_58) {
          local_64 = local_58;
        }
        tmp_f2 = local_54;
        if (local_60 < local_54) {
          tmp_f2 = local_60;
        }
        if (local_60 <= local_54) {
          local_60 = local_54;
        }
        tmp_f3 = local_50;
        if (local_5c < local_50) {
          tmp_f3 = local_5c;
        }
        if (local_5c <= local_50) {
          local_5c = local_50;
        }
        tmp_u5 = 0;
        *param_3 = tmp_f1 + local_70;
        param_3[3] = local_64 + local_70;
        param_3[1] = tmp_f2 + local_6c;
        param_3[4] = local_60 + local_6c;
        param_3[2] = tmp_f3 + local_68;
        param_3[5] = local_5c + local_68;
      }
      else {
        tmp_u5 = 0;
      }
    }
  }
  return tmp_u5;
}

char * ETInterface_EntityByName(char *param_1)
{
  BG_StringHashValue();
  G_FindByTargetnameFast(0);
  HandleFromEntity((gentity_s *)param_1);
  return param_1;
}

int ETInterface_EntityFromID(int param_1)
{
  int tmp_i1;
  int in_stack_0000000c;
  
  tmp_i1 = INDEXENT(in_stack_0000000c);
  if (tmp_i1 != 0) {
    HandleFromEntity((gentity_s *)param_1);
    return param_1;
  }
  *(uint16_t *)param_1 = 0xffff;
  *(uint16_t *)(param_1 + 2) = 0;
  return param_1;
}

gentity_s * ETInterface_GetEntityOwner(gentity_s *param_1,uint32_t param_2,uint32_t param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  
  *(uint16_t *)param_1 = 0xffff;
  *(uint16_t *)(param_1 + 2) = 0;
  tmp_pi1 = (int *)EntityFromHandle(param_3);
  if (tmp_pi1 == (int *)0x0) {
    return param_1;
  }
  if (tmp_pi1[0x65] == 0) {
    return param_1;
  }
  tmp_i2 = tmp_pi1[1];
  if ((tmp_pi1[100] == 0) || (0x17fff < (int)(tmp_pi1 + -0x24f928))) {
    if (tmp_i2 == 2) {
      if ((tmp_pi1[0x170] != 0x36af1) && (tmp_pi1[0x170] != 0x3317f)) {
        return param_1;
      }
      tmp_pu3 = g_entities;
      if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) < 1) {
        return param_1;
      }
      tmp_i4 = 0;
      tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
      do {
        while ((*(int *)(tmp_pu3 + 400) == 0 ||
               (*(int *)(*(int *)(tmp_pu3 + 400) + 0x5294) !=
                ((int)(tmp_pi1 + -0x24f928) >> 9) * -0x55555555))) {
          tmp_i4 = tmp_i4 + 1;
          tmp_pu3 = tmp_pu3 + 0x600;
          if (tmp_i2 <= tmp_i4) {
            return param_1;
          }
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_pu3 = tmp_pu3 + 0x600;
        HandleFromEntity(param_1);
        tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
      } while (tmp_i4 < (int)GHIDRA_FIELD(g_maxclients, 12, 4));
      return param_1;
    }
    if ((tmp_i2 == 0x29) || (tmp_i2 == 0)) {
      if (tmp_pi1[0x170] != 0x1908e) {
        return param_1;
      }
      if (tmp_pi1[0x60] == *tmp_pi1) {
        return param_1;
      }
      tmp_i2 = tmp_pi1[0x60] * 0x600;
      if (*(int *)(g_entities + tmp_i2 + 0x368) == 0) {
        return param_1;
      }
      if (*(int *)(g_entities + tmp_i2 + 400) == 0) {
        return param_1;
      }
      if ((g_entities[tmp_i2 + 8] & 0x20) == 0) {
        return param_1;
      }
      goto LAB_00235036;
    }
  }
  if (0x3ff < tmp_pi1[0x60]) {
    return param_1;
  }
LAB_00235036:
  HandleFromEntity(param_1);
  return param_1;
}

ETInterface_GetEntityGroundEntity(uint32_t this,uint32_t param_2,uint32_t *param_3)
{
  int tmp_i1;
  uint32_t local_10 [3];
  
  tmp_i1 = EntityFromHandle(param_2);
  if (tmp_i1 == 0) {
    return 3;
  }
  if (0x3fc < *(int *)(tmp_i1 + 0x94) - 1U) {
    return 0;
  }
  HandleFromEntity((gentity_s *)local_10);
  *param_3 = local_10[0];
  return 0;
}

// ETInterface::FindEntityInSphere(float const*, float, GameEntity, int)

gentity_s *
ETInterface::FindEntityInSphere
          (gentity_s *param_1,uint32_t param_2,float *param_3,float param_4,uint param_5,
          int param_6)

{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  long double tmp_l4;
  uint local_40;
  int local_34;
  char *local_30;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i2 = 0;
  if ((param_5 & 0x8000) == 0) {
    tmp_i2 = EntityFromHandle(param_5);
  }
  switch(param_6) {
  default:
    *(uint16_t *)param_1 = 0xffff;
    *(uint16_t *)(param_1 + 2) = 0;
    return param_1;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    if (param_6 == 6) {
      local_34 = 0;
      local_40 = 0;
      tmp_i3 = 0;
      local_30 = "player";
    }
    else {
      local_34 = param_6;
      tmp_i3 = 0;
      local_40 = 0;
      local_30 = "player";
    }
    break;
  case 7:
    tmp_i3 = 0x1908e;
    local_40 = 0;
    local_34 = 0;
    local_30 = "misc_mg42";
    break;
  case 8:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "dynamite";
    break;
  case 9:
    local_40 = 0;
    tmp_i3 = 0;
    local_34 = 0;
    local_30 = "landmine";
    break;
  case 10:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "satchel_charge";
    break;
  case 0xb:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "smoke_bomb";
    break;
  case 0xc:
  case 0x16:
  case 0x17:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "air strike";
    break;
  case 0xd:
  case 0xe:
    if (param_6 == 0xe) {
      tmp_i3 = 0x27cac;
      local_40 = 4;
      local_34 = 0;
      local_30 = "script_mover";
    }
    else {
      local_34 = 0;
      tmp_i3 = 0x27cac;
      local_40 = 0;
      local_30 = "script_mover";
    }
    break;
  case 0x11:
    local_40 = 0;
    tmp_i3 = 0;
    local_34 = 0;
    local_30 = "corpse";
    break;
  case 0x13:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "grenade";
    break;
  case 0x14:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "rocket";
    break;
  case 0x15:
    local_34 = 0;
    local_40 = 0;
    tmp_i3 = 0;
    local_30 = "mortar_grenade";
    break;
  case 0x18:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "flamechunk";
    break;
  case 0x19:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "m7_grenade";
    break;
  case 0x1a:
    tmp_i3 = 0;
    local_40 = 0;
    local_34 = 0;
    local_30 = "gpg40_grenade";
    break;
  case 0x1b:
    local_30 = "misc_cabinet_health";
    local_34 = 0;
    tmp_i3 = 0x3db3a;
    local_40 = 0;
    break;
  case 0x1c:
    local_40 = 0;
    local_30 = "misc_cabinet_supply";
    tmp_i3 = 0x3f805;
    local_34 = 0;
  }
  param_4 = param_4 * param_4;
  if (tmp_i3 == 0) {
    if (local_34 == 0) {
      if (local_40 == 0) {
        if (param_6 == 0x11) {
          do {
            do {
              tmp_u1 = BG_StringHashValue(local_30);
              tmp_i2 = nitrox_FindByClassNameHash(tmp_i2,tmp_u1);
              if (tmp_i2 == 0) goto LAB_002351e0;
            } while ((*(int *)(tmp_i2 + 0x1cc) == 0) ||
                    ((*(int *)(tmp_i2 + 0x2f0) != 0 &&
                     (*(int *)(*(int *)(*(int *)(tmp_i2 + 0x2f0) + 400) + 0x16c) != 0))));
            local_28 = *param_3 - *(float *)(tmp_i2 + 0x168);
            local_24 = param_3[1] - *(float *)(tmp_i2 + 0x16c);
            local_20 = param_3[2] - *(float *)(tmp_i2 + 0x170);
            tmp_l4 = (long double)VectorLengthSquared(&local_28);
          } while ((long double)param_4 <= tmp_l4);
        }
        else {
          do {
            tmp_u1 = BG_StringHashValue(local_30);
            tmp_i2 = nitrox_FindByClassNameHash(tmp_i2,tmp_u1);
            if (tmp_i2 == 0) break;
            local_28 = *param_3 - *(float *)(tmp_i2 + 0x168);
            local_24 = param_3[1] - *(float *)(tmp_i2 + 0x16c);
            local_20 = param_3[2] - *(float *)(tmp_i2 + 0x170);
            tmp_l4 = (long double)VectorLengthSquared(&local_28);
          } while ((long double)param_4 <= tmp_l4);
        }
      }
      else {
        do {
          do {
            tmp_u1 = BG_StringHashValue(local_30);
            tmp_i2 = nitrox_FindByClassNameHash(tmp_i2,tmp_u1);
            if (tmp_i2 == 0) goto LAB_002351e0;
          } while (((*(uint *)(tmp_i2 + 0x1a8) & local_40) == 0) ||
                  ((param_6 == 0x11 &&
                   ((*(int *)(tmp_i2 + 0x1cc) == 0 ||
                    ((*(int *)(tmp_i2 + 0x2f0) != 0 &&
                     (*(int *)(*(int *)(*(int *)(tmp_i2 + 0x2f0) + 400) + 0x16c) != 0))))))));
          local_28 = *param_3 - *(float *)(tmp_i2 + 0x168);
          local_24 = param_3[1] - *(float *)(tmp_i2 + 0x16c);
          local_20 = param_3[2] - *(float *)(tmp_i2 + 0x170);
          tmp_l4 = (long double)VectorLengthSquared(&local_28);
        } while ((long double)param_4 <= tmp_l4);
      }
    }
    else {
      do {
        do {
          tmp_u1 = BG_StringHashValue(local_30);
          tmp_i2 = nitrox_FindByClassNameHash(tmp_i2,tmp_u1);
          if (tmp_i2 == 0) goto LAB_002351e0;
        } while ((((*(int *)(tmp_i2 + 400) != 0) &&
                  (*(int *)(*(int *)(tmp_i2 + 400) + 3000) != local_34)) ||
                 ((local_40 != 0 && ((*(uint *)(tmp_i2 + 0x1a8) & local_40) == 0)))) ||
                ((param_6 == 0x11 &&
                 ((*(int *)(tmp_i2 + 0x1cc) == 0 ||
                  ((*(int *)(tmp_i2 + 0x2f0) != 0 &&
                   (*(int *)(*(int *)(*(int *)(tmp_i2 + 0x2f0) + 400) + 0x16c) != 0))))))));
        local_28 = *param_3 - *(float *)(tmp_i2 + 0x168);
        local_24 = param_3[1] - *(float *)(tmp_i2 + 0x16c);
        local_20 = param_3[2] - *(float *)(tmp_i2 + 0x170);
        tmp_l4 = (long double)VectorLengthSquared(&local_28);
      } while ((long double)param_4 <= tmp_l4);
    }
  }
  else if (local_34 == 0) {
    if (local_40 == 0) {
      if (param_6 == 0x11) {
        do {
          do {
            tmp_i2 = nitrox_FindByClassNameHash(tmp_i2,tmp_i3);
            if (tmp_i2 == 0) goto LAB_002351e0;
          } while ((*(int *)(tmp_i2 + 0x1cc) == 0) ||
                  ((*(int *)(tmp_i2 + 0x2f0) != 0 &&
                   (*(int *)(*(int *)(*(int *)(tmp_i2 + 0x2f0) + 400) + 0x16c) != 0))));
          local_28 = *param_3 - *(float *)(tmp_i2 + 0x168);
          local_24 = param_3[1] - *(float *)(tmp_i2 + 0x16c);
          local_20 = param_3[2] - *(float *)(tmp_i2 + 0x170);
          tmp_l4 = (long double)VectorLengthSquared(&local_28);
        } while ((long double)param_4 <= tmp_l4);
      }
      else {
        do {
          tmp_i2 = nitrox_FindByClassNameHash(tmp_i2,tmp_i3);
          if (tmp_i2 == 0) break;
          local_28 = *param_3 - *(float *)(tmp_i2 + 0x168);
          local_24 = param_3[1] - *(float *)(tmp_i2 + 0x16c);
          local_20 = param_3[2] - *(float *)(tmp_i2 + 0x170);
          tmp_l4 = (long double)VectorLengthSquared(&local_28);
        } while ((long double)param_4 <= tmp_l4);
      }
    }
    else {
      do {
        do {
          tmp_i2 = nitrox_FindByClassNameHash(tmp_i2,tmp_i3);
          if (tmp_i2 == 0) goto LAB_002351e0;
        } while (((*(uint *)(tmp_i2 + 0x1a8) & local_40) == 0) ||
                ((param_6 == 0x11 &&
                 ((*(int *)(tmp_i2 + 0x1cc) == 0 ||
                  ((*(int *)(tmp_i2 + 0x2f0) != 0 &&
                   (*(int *)(*(int *)(*(int *)(tmp_i2 + 0x2f0) + 400) + 0x16c) != 0))))))));
        local_28 = *param_3 - *(float *)(tmp_i2 + 0x168);
        local_24 = param_3[1] - *(float *)(tmp_i2 + 0x16c);
        local_20 = param_3[2] - *(float *)(tmp_i2 + 0x170);
        tmp_l4 = (long double)VectorLengthSquared(&local_28);
      } while ((long double)param_4 <= tmp_l4);
    }
  }
  else {
    do {
      do {
        tmp_i2 = nitrox_FindByClassNameHash(tmp_i2,tmp_i3);
        if (tmp_i2 == 0) goto LAB_002351e0;
      } while ((((*(int *)(tmp_i2 + 400) != 0) &&
                (*(int *)(*(int *)(tmp_i2 + 400) + 3000) != local_34)) ||
               ((local_40 != 0 && ((*(uint *)(tmp_i2 + 0x1a8) & local_40) == 0)))) ||
              ((param_6 == 0x11 &&
               ((*(int *)(tmp_i2 + 0x1cc) == 0 ||
                ((*(int *)(tmp_i2 + 0x2f0) != 0 &&
                 (*(int *)(*(int *)(*(int *)(tmp_i2 + 0x2f0) + 400) + 0x16c) != 0))))))));
      local_28 = *param_3 - *(float *)(tmp_i2 + 0x168);
      local_24 = param_3[1] - *(float *)(tmp_i2 + 0x16c);
      local_20 = param_3[2] - *(float *)(tmp_i2 + 0x170);
      tmp_l4 = (long double)VectorLengthSquared(&local_28);
    } while ((long double)param_4 <= tmp_l4);
  }
LAB_002351e0:
  HandleFromEntity(param_1);
  return param_1;
}

gentity_s * ETInterface_GetLocalGameEntity(void)
{
  int tmp_i1;
  gentity_s *in_stack_00000004;
  int *in_stack_00000008;
  
  if (*(void **)(*in_stack_00000008 + 0xac) != EntityFromID) {
    (**(void **)(*in_stack_00000008 + 0xac))();
    return in_stack_00000004;
  }
  tmp_i1 = INDEXENT(0);
  if (tmp_i1 != 0) {
    HandleFromEntity(in_stack_00000004);
    return in_stack_00000004;
  }
  *(uint16_t *)in_stack_00000004 = 0xffff;
  *(uint16_t *)(in_stack_00000004 + 2) = 0;
  return in_stack_00000004;
}

uint32_t ETInterface_GetEntityTeam(uint32_t this,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  tmp_i2 = EntityFromHandle(param_2);
  if (tmp_i2 == 0) {
    return 0;
  }
  if (*(int *)(tmp_i2 + 0x194) == 0) {
    return 0;
  }
  if ((*(int *)(tmp_i2 + 400) != 0) && (tmp_i2 + -0x93e4a0 < 0x18000)) {
LAB_00235a20:
    tmp_u3 = Bot_TeamGameToBot(*(uint32_t *)(*(int *)(tmp_i2 + 400) + 3000));
    return tmp_u3;
  }
  tmp_i1 = *(int *)(tmp_i2 + 4);
  if (tmp_i1 == 3) {
    tmp_i1 = *(int *)(tmp_i2 + 0xe8);
    if ((tmp_i1 != 0x33 && tmp_i1 != 0x19) && (tmp_i1 != 0xf)) goto LAB_002359eb;
    tmp_u3 = G_LandmineTeam(tmp_i2);
    tmp_u3 = Bot_TeamGameToBot(tmp_u3);
  }
  else {
    if (tmp_i1 != 0x26) {
      if (tmp_i1 == 1) goto LAB_00235a20;
LAB_002359eb:
      tmp_u3 = Bot_TeamGameToBot(*(uint32_t *)(tmp_i2 + 0x108));
      return tmp_u3;
    }
    tmp_u3 = Bot_TeamGameToBot(*(uint32_t *)(tmp_i2 + 0xa4));
  }
  return tmp_u3;
}

ETInterface_ChangeTeam(ETInterface *this,int param_1,int param_2,MessageHelper *param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  gentity_s *pgVar8;
  char *local_20;
  
  tmp_i2 = param_1 * 0x600;
  pgVar8 = (gentity_s *)(g_entities + tmp_i2);
  if (param_2 - 1U < 2) {
LAB_00235d2c:
    if (param_2 == 1) goto LAB_00235afa;
LAB_00235d09:
    local_20 = "putallies";
  }
  else {
    if ((param_2 != -1) && (*(int *)(*(int *)(g_entities + tmp_i2 + 400) + 3000) - 1U < 2)) {
      param_2 = Bot_TeamGameToBot(*(int *)(*(int *)(g_entities + tmp_i2 + 400) + 3000));
      goto LAB_00235d2c;
    }
    tmp_i3 = TeamCount(param_1,2);
    tmp_i4 = TeamCount(param_1,1);
    if (tmp_i3 <= tmp_i4) {
      param_2 = 2;
      goto LAB_00235d09;
    }
LAB_00235afa:
    param_2 = 1;
    local_20 = "putaxis";
  }
  local_20 = local_20 + 3;
  if ((param_3 != (MessageHelper *)0x0) && (tmp_pi1 = *(int **)(param_3 + 4), tmp_pi1 != (int *)0x0))
  {
    if (*tmp_pi1 != 0) {
      tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
      tmp_u5 = _weaponBotToGame(*tmp_pi1);
      *(uint32_t *)(tmp_i3 + 0xbdc) = tmp_u5;
    }
    if (tmp_pi1[1] != 0) {
      tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
      tmp_u5 = _weaponBotToGame(tmp_pi1[1]);
      *(uint32_t *)(tmp_i3 + 0xbe0) = tmp_u5;
    }
    tmp_i3 = G_IsWeaponDisabled(pgVar8,*(uint32_t *)
                                       (*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbdc),1,0);
    if (tmp_i3 != 0) {
      *(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbdc) = 0;
    }
    tmp_i3 = G_IsWeaponDisabled(pgVar8,*(uint32_t *)
                                       (*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbe0),1,0);
    if (tmp_i3 != 0) {
      *(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbe0) = 0;
    }
  }
  tmp_pi1 = (int *)(g_entities + param_1 * 0x600 + 400);
  tmp_i4 = Bot_TeamGameToBot(*(uint32_t *)(*tmp_pi1 + 3000));
  tmp_i6 = Bot_PlayerClassGameToBot(*(uint32_t *)(*tmp_pi1 + 0xbd8));
  tmp_i3 = *tmp_pi1;
  if ((tmp_i4 != param_2) || (*(int *)(tmp_i3 + 0xbdc) == 0)) {
    tmp_i7 = _choosePriWeap(pgVar8,tmp_i6,param_2);
    tmp_u5 = _weaponBotToGame(tmp_i7);
    *(uint32_t *)(tmp_i3 + 0xbdc) = tmp_u5;
    tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
    if (tmp_i4 == param_2) goto LAB_00235c87;
  }
  else {
LAB_00235c87:
    if (*(int *)(tmp_i3 + 0xbe0) != 0) goto LAB_00235cb3;
  }
  tmp_i2 = _chooseSecWeap((gentity_s *)(g_entities + tmp_i2 + 400),tmp_i6,param_2);
  tmp_u5 = _weaponBotToGame(tmp_i2);
  *(uint32_t *)(tmp_i3 + 0xbe0) = tmp_u5;
LAB_00235cb3:
  SetTeam(pgVar8,local_20,1,0xffffffff,0xffffffff,0);
  G_TeamCountPlayers();
  return 0;
}

void ETInterface_GetPlayerInfo(ETInterface *this,obPlayerInfo *param_1)
{
  byte tmp_b1;
  gentity_s *pgVar2;
  gentity_s *pgVar3;
  uint32_t tmp_u4;
  int tmp_i5;
  obPlayerInfo *poVar6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  gentity_s *pgVar9;
  gentity_s *local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x235d49;
  *(uint *)(param_1 + 0x304) = *(uint *)(param_1 + 0x304) | 6;
  *(uint32_t *)(param_1 + 0x300) = g_unk_00abe900;
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    tmp_pu7 = g_entities;
    poVar6 = param_1 + 4;
    tmp_i8 = 0;
    tmp_i5 = GHIDRA_FIELD(g_maxclients, 12, 4);
    do {
      if (((*(int *)(tmp_pu7 + 0x194) != 0) && (*(int *)(tmp_pu7 + 400) != 0)) &&
         (*(int *)(*(int *)(tmp_pu7 + 400) + 0x5ac) == 2)) {
        pgVar9 = (gentity_s *)tmp_pu7;
        HandleFromEntity((gentity_s *)local_20);
        pgVar3 = local_20[0];
        if (*(void **)(*(int *)this + 100) == GetEntityTeam) {
          pgVar2 = (gentity_s *)EntityFromHandle(local_20[0],pgVar9);
          tmp_u4 = 0;
          if ((pgVar2 != (gentity_s *)0x0) && (*(int *)(pgVar2 + 0x194) != 0)) {
            tmp_u4 = _GetEntityTeam(pgVar2);
          }
        }
        else {
          pgVar9 = local_20[0];
          tmp_u4 = (**(void **)(*(int *)this + 100))(this,local_20[0]);
        }
        *(uint32_t *)(poVar6 + -4) = tmp_u4;
        if (*(void **)(*(int *)this + 0x2c) == GetEntityClass) {
          pgVar3 = (gentity_s *)EntityFromHandle(pgVar3,pgVar9);
          tmp_u4 = 0;
          if ((pgVar3 != (gentity_s *)0x0) && (*(int *)(pgVar3 + 0x194) != 0)) {
            tmp_u4 = _GetEntityClass(pgVar3);
          }
        }
        else {
          tmp_u4 = (**(void **)(*(int *)this + 0x2c))(this,pgVar3);
        }
        *(uint32_t *)poVar6 = tmp_u4;
        tmp_b1 = IsBot((gentity_s *)tmp_pu7);
        *(uint *)(poVar6 + 4) = (uint)(tmp_b1 ^ 1);
        tmp_i5 = GHIDRA_FIELD(g_maxclients, 12, 4);
      }
      tmp_i8 = tmp_i8 + 1;
      tmp_pu7 = tmp_pu7 + 0x600;
      poVar6 = poVar6 + 0xc;
    } while (tmp_i8 < tmp_i5);
  }
  return;
}

int ETInterface_GetEntityClass(uint32_t this,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = EntityFromHandle(param_2);
  if (tmp_i1 == 0) {
    return 0;
  }
  if (*(int *)(tmp_i1 + 0x194) == 0) {
    return 0;
  }
  tmp_i2 = *(int *)(tmp_i1 + 400);
  if (tmp_i2 != 0) {
    if (tmp_i1 + -0x93e4a0 < 0x18000) {
_L1306:
      if (*(int *)(tmp_i1 + 0x458) == 1) {
        return 0x2711;
      }
      if (*(int *)(tmp_i2 + 3000) - 1U < 2) {
        tmp_i1 = Bot_PlayerClassGameToBot(*(uint32_t *)(tmp_i2 + 0xbd8));
        return tmp_i1;
      }
      return 0x2711;
    }
    switch(*(uint32_t *)(tmp_i1 + 4)) {
    case 0:
      goto _L1309;
    case 1:
      goto _L1306;
    case 2:
      goto _L1312;
    case 3:
      goto _L1313;
    case 4:
      goto _L1314;
    default:
      goto LAB_00235ee4;
    case 10:
      goto LAB_00235ee4;
    case 0xc:
      goto LAB_00235ee4;
    case 0xe:
      goto _L1317;
    case 0x19:
      goto LAB_00235ee4;
    case 0x26:
      goto LAB_00235ee4;
    case 0x29:
      goto LAB_00235ee4;
    case 0x31:
      goto LAB_00235ee4;
    case 0x32:
      goto LAB_00235ee4;
    }
  }
  switch(*(uint32_t *)(tmp_i1 + 4)) {
  case 0:
_L1309:
    if ((*(int *)(tmp_i1 + 0x5c0) == 0x3f73d) ||
       (tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"func_button"), tmp_i2 == 0)) {
      return 0x2717;
    }
    if (*(int *)(tmp_i1 + 0x5c0) == 0x1908e) {
      return 7;
    }
    tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair_hiback");
    if (((tmp_i2 != 0) &&
        (tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair"), tmp_i2 != 0)) &&
       (tmp_i1 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair_side"), tmp_i1 != 0)) {
      return 0;
    }
    return 0x1d;
  case 1:
LAB_00235ee4:
    return 0x2711;
  case 2:
_L1312:
    tmp_i2 = Q_strncmp(*(uint32_t *)(tmp_i1 + 0x1a4),"item_health",0xb);
    if (tmp_i2 == 0) {
      return 0x2718;
    }
    tmp_i2 = Q_strncmp(*(uint32_t *)(tmp_i1 + 0x1a4),"weapon_magicammo",0x10);
    if (tmp_i2 == 0) {
      return 0x2719;
    }
    tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"item_treasure");
    if (tmp_i2 == 0) {
      return 0x12;
    }
    tmp_i1 = *(int *)(tmp_i1 + 0x33c);
    if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x24) == 1)) {
      tmp_i1 = Bot_WeaponGameToBot(*(uint32_t *)(tmp_i1 + 0x28));
      return tmp_i1 + 0x1e;
    }
    break;
  case 3:
_L1313:
    switch(*(uint32_t *)(tmp_i1 + 0xe8)) {
    case 4:
    case 9:
      return 0x13;
    case 5:
      return 0x14;
    case 0xd:
      return 0x16;
    case 0xf:
      return 8;
    case 0x15:
      return 0xc;
    case 0x19:
    case 0x33:
      return 9;
    case 0x1a:
      return 10;
    case 0x1c:
      return 0xb;
    case 0x24:
      return 0x1a;
    case 0x25:
      return 0x19;
    case 0x2a:
      return 0x15;
    }
    tmp_i1 = Q_strncmp(*(uint32_t *)(tmp_i1 + 0x1a4),"air strike",0xb);
    if (tmp_i1 == 0) {
      return 0x17;
    }
    break;
  case 4:
_L1314:
    if (*(int *)(tmp_i1 + 0x5c0) == 0x27cac) {
      if (0 < *(int *)(tmp_i1 + 0x2e4)) {
        return 0xe - (uint)((*(uint *)(tmp_i1 + 0x1a8) & 4) == 0);
      }
      return 0xf;
    }
    tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair_hiback");
    if (((tmp_i2 != 0) &&
        (tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair"), tmp_i2 != 0)) &&
       (tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i1 + 0x1a4),"props_chair_side"), tmp_i2 != 0)) {
      return 0;
    }
    if (*(int *)(tmp_i1 + 0x2c8) < 1) {
      return 0;
    }
    if (*(int *)(tmp_i1 + 0x2cc) != 1) {
      return 0;
    }
    return 0x10;
  default:
    break;
  case 0xc:
LAB_00235ee4:
    return 0x2723;
  case 0xe:
_L1317:
    if ((*(byte *)(tmp_i1 + 0x1a8) & 0x20) != 0) {
      return 0;
    }
    if (*(int *)(tmp_i1 + 0x4f4) - 1U < 2) {
      return 0;
    }
    return 0x10;
  case 0x19:
LAB_00235ee4:
    return 0x18;
  case 0x26:
LAB_00235ee4:
    return 0x11;
  case 0x29:
LAB_00235ee4:
    return 7;
  case 0x31:
LAB_00235ee4:
    return 0x1b;
  case 0x32:
LAB_00235ee4:
    return 0x1c;
  }
LAB_00235ee4:
  return 0;
}

ETInterface_InterfaceSendMessage(ETInterface *this,int *param_1,uint32_t param_3)
{
  float tmp_f1;
  int *tmp_pi2;
  uint *tmp_pu3;
  byte *tmp_pb4;
  char *tmp_pc5;
  uint32_t *tmp_pu6;
  gentity_s *pgVar7;
  int tmp_i8;
  gentity_s *pgVar9;
  uint32_t tmp_u10;
  uint tmp_u11;
  int tmp_i12;
  byte *tmp_pb13;
  byte *tmp_pb14;
  int tmp_i15;
  bool tmp_b16;
  bool tmp_b17;
  bool tmp_b18;
  byte tmp_b19;
  ushort local_434;
  uint local_430 [2];
  uint32_t local_428;
  uint32_t local_424;
  float local_420;
  uint32_t *local_41c [2];
  float local_414;
  uint local_3f0;
  
  tmp_b19 = 0;
  pgVar7 = (gentity_s *)EntityFromHandle(param_3);
  tmp_u10 = GHIDRA_FIELD(g_gamestate, 12, 4);
  tmp_i8 = *param_1;
  switch(tmp_i8) {
  case 3:
    if (((pgVar7 != (gentity_s *)0x0) && ((uint32_t *)param_1[1] != (uint32_t *)0x0)) &&
       ((*(int *)(pgVar7 + 0x194) != 0 &&
        (((*(int *)(pgVar7 + 400) != 0 && (0 < *(int *)(pgVar7 + 0x2c8))) &&
         (*(int *)(*(int *)(pgVar7 + 400) + 4) == 0)))))) {
      *(uint32_t *)param_1[1] = 1;
      return 0;
    }
    break;
  case 4:
    if ((((pgVar7 != (gentity_s *)0x0) && ((uint32_t *)param_1[1] != (uint32_t *)0x0)) &&
        (*(int *)(pgVar7 + 0x194) != 0)) &&
       ((*(int *)(pgVar7 + 400) != 0 && (*(int *)(*(int *)(pgVar7 + 400) + 0xa8) - 1U < 7)))) {
      *(uint32_t *)param_1[1] = 1;
      return 0;
    }
    break;
  case 5:
    if (((pgVar7 != (gentity_s *)0x0) && ((uint32_t *)param_1[1] != (uint32_t *)0x0)) &&
       (((*(int *)(pgVar7 + 0x194) != 0 && (*(int *)(pgVar7 + 400) != 0)) &&
        ((tmp_i8 = *(int *)(*(int *)(pgVar7 + 400) + 0xa8), tmp_i8 == 5 || (tmp_i8 == 0)))))) {
      *(uint32_t *)param_1[1] = 1;
      return 0;
    }
    break;
  case 6:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (((tmp_pu6 != (uint32_t *)0x0) &&
        (pgVar9 = (gentity_s *)EntityFromHandle(*tmp_pu6), pgVar9 != (gentity_s *)0x0)) &&
       (pgVar7 != (gentity_s *)0x0)) {
      tmp_i8 = ENTINDEX(pgVar9);
      if (tmp_i8 == 0x3fe) {
        tmp_pu6[1] = 1;
        return 0;
      }
      if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
        tmp_pu6[1] = 0;
        return 0;
      }
      tmp_i8 = _GetEntityTeam(pgVar7);
      tmp_i15 = _GetEntityTeam(pgVar9);
      tmp_pu6[1] = (uint)(tmp_i8 == tmp_i15);
      return 0;
    }
    break;
  case 7:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      local_428 = *tmp_pu6;
      local_424 = tmp_pu6[1];
      local_420 = (float)tmp_pu6[2] + 4096.0;
      trap_Trace(local_41c,tmp_pu6,0,0,&local_428,0xffffffff,1);
      tmp_u11 = 1;
      if (local_414 < 1.0) {
        tmp_u11 = local_3f0 >> 4 & 1;
      }
      tmp_pu6[3] = tmp_u11;
      return 0;
    }
    break;
  case 8:
    tmp_i8 = param_1[1];
    if (((pgVar7 != (gentity_s *)0x0) && (tmp_i8 != 0)) && (*(int *)(pgVar7 + 400) != 0)) {
      tmp_i15 = ((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555;
      trap_GetUserinfo(tmp_i15,local_41c,0x400);
      Info_SetValueForKey(local_41c,"name",tmp_i8);
      trap_SetUserinfo(tmp_i15,local_41c);
      ClientUserinfoChanged(tmp_i15);
      return 0;
    }
    break;
  case 9:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      if (((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 0x194) != 0)) &&
         (*(int *)(pgVar7 + 400) != 0)) {
        tmp_u10 = Bot_WeaponGameToBot(*(uint32_t *)(*(int *)(pgVar7 + 400) + 0xa4));
        *tmp_pu6 = tmp_u10;
        return 0;
      }
      *tmp_pu6 = 0;
      return 0;
    }
    break;
  case 10:
    if (((pgVar7 != (gentity_s *)0x0) && ((uint *)param_1[1] != (uint *)0x0)) &&
       ((*(int *)(pgVar7 + 0x194) != 0 && (*(int *)(pgVar7 + 400) != 0)))) {
      *(uint *)param_1[1] = ~-(uint)((*(uint *)(pgVar7 + 8) & 0x8020) == 0) & 0x2b;
      return 0;
    }
    break;
  case 0xb:
    tmp_i8 = param_1[1];
    if (tmp_i8 != 0) {
      if (((pgVar7 == (gentity_s *)0x0) || (*(int *)(pgVar7 + 0x194) == 0)) ||
         (tmp_i15 = *(int *)(pgVar7 + 400), tmp_i15 == 0)) {
        *(uint32_t *)(tmp_i8 + 0x20) = 0;
        return 0;
      }
      tmp_i12 = *(int *)(tmp_i8 + 0x1c);
      if (tmp_i12 == 0x2b) {
        if ((*(uint *)(tmp_i15 + 0x68) & 0x8020) == 0) {
          return 0;
        }
        *(uint32_t *)(tmp_i8 + 0x20) = 1;
        AngleVectors(tmp_i15 + 0x52c0,tmp_i8,0,0);
        tmp_i15 = *(int *)(pgVar7 + 400);
        if ((*(byte *)(tmp_i15 + 0x69) & 0x80) == 0) {
          tmp_f1 = *(float *)(tmp_i15 + 0x52bc);
          tmp_i12 = *(int *)(tmp_i8 + 0x1c);
          *(float *)(tmp_i8 + 0xc) = -tmp_f1;
          *(float *)(tmp_i8 + 0x10) = tmp_f1;
          tmp_f1 = *(float *)(tmp_i15 + 0x52b8);
          *(float *)(tmp_i8 + 0x14) = -tmp_f1;
          *(float *)(tmp_i8 + 0x18) = tmp_f1;
        }
        else {
          *(uint32_t *)(tmp_i8 + 0xc) = 0xc3b40000;
          tmp_i12 = *(int *)(tmp_i8 + 0x1c);
          *(uint32_t *)(tmp_i8 + 0x10) = 0xc3b40000;
          *(uint32_t *)(tmp_i8 + 0x14) = 0x41600000;
          *(uint32_t *)(tmp_i8 + 0x18) = 0x42480000;
        }
      }
      if (tmp_i12 - 0xfU < 2) {
        AngleVectors(tmp_i15 + 0x52dc,tmp_i8,0,0);
        *(uint32_t *)(tmp_i8 + 0x20) = 1;
        *(uint32_t *)(tmp_i8 + 0xc) = 0xc1a00000;
        *(uint32_t *)(tmp_i8 + 0x10) = 0x41a00000;
        *(uint32_t *)(tmp_i8 + 0x14) = 0xc1a00000;
        *(uint32_t *)(tmp_i8 + 0x18) = 0x41a00000;
        return 0;
      }
    }
    break;
  case 0xc:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      tmp_pu6[3] = 0;
      tmp_pu6[2] = 0;
      if (pgVar7 != (gentity_s *)0x0) {
        tmp_i8 = *(int *)(pgVar7 + 4);
        if (tmp_i8 == 4) {
LAB_00237b64:
          tmp_u10 = 0;
          if ((*(int *)(pgVar7 + 0x2cc) != 0) && (-1 < *(int *)(pgVar7 + 0x2c8))) {
            tmp_u10 = *(uint32_t *)(pgVar7 + 0x2c8);
          }
          *tmp_pu6 = tmp_u10;
          tmp_pu6[1] = *(uint32_t *)(pgVar7 + 0x2e4);
          return 0;
        }
        if (tmp_i8 < 5) {
          if (tmp_i8 != 0) {
LAB_00237b3e:
            tmp_i8 = *(int *)(pgVar7 + 400);
            if (tmp_i8 == 0) {
              tmp_u10 = 0;
              if (*(int *)(pgVar7 + 0x2cc) != 0) {
                tmp_u10 = *(uint32_t *)(pgVar7 + 0x2c8);
              }
              *tmp_pu6 = tmp_u10;
              tmp_pu6[1] = 0;
              return 0;
            }
            tmp_u10 = *(uint32_t *)(tmp_i8 + 0xe0);
            *tmp_pu6 = *(uint32_t *)(tmp_i8 + 0xd0);
            tmp_pu6[1] = tmp_u10;
            return 0;
          }
        }
        else {
          if (tmp_i8 == 0x20) goto LAB_00237b64;
          if (tmp_i8 != 0x29) goto LAB_00237b3e;
        }
        if (*(int *)(pgVar7 + 0x5c0) == 0x1908e) {
          tmp_i8 = Simple_EmplacedGunIsRepairable(pgVar7);
          if (tmp_i8 != 0) {
            *tmp_pu6 = 0;
            tmp_pu6[1] = 0x15e;
            return 0;
          }
          if (*(int *)(pgVar7 + 0x388) < 1) {
            tmp_u10 = *(uint32_t *)(pgVar7 + 0x2c8);
            tmp_pu6[1] = 0x15e;
            *tmp_pu6 = tmp_u10;
            return 0;
          }
          tmp_u10 = *(uint32_t *)(g_entities + *(int *)(pgVar7 + 0x388) * 0x600 + 0x2c8);
          tmp_pu6[1] = 0x15e;
          *tmp_pu6 = tmp_u10;
          return 0;
        }
      }
    }
    break;
  case 0xd:
    if ((pgVar7 != (gentity_s *)0x0) && ((float *)param_1[1] != (float *)0x0)) {
      *(float *)param_1[1] = (float)(int)GHIDRA_FIELD(g_movespeed, 12, 4);
      return 0;
    }
    break;
  case 0xe:
  case 0x12:
  case 0x1c:
    return 0;
  case 0xf:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (((pgVar7 != (gentity_s *)0x0) && (tmp_pu6 != (uint32_t *)0x0)) &&
       (*(int *)(pgVar7 + 4) == 0x11)) {
      tmp_u10 = Bot_TeamGameToBot(*(uint32_t *)(pgVar7 + 0x2e4));
      *tmp_pu6 = tmp_u10;
      return 0;
    }
    break;
  case 0x10:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      if (g_unk_00abe904 < 6) {
        *tmp_pu6 = 0;
        return 0;
      }
      tmp_pu6[1] = (float)(((int)ROUND((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0) - g_unk_02a99b84) +
                         g_unk_00abe918) / 1000.0;
      if ((uint)tmp_u10 < 5) {
        tmp_u10 = (*(void *)((int)&_GLOBAL_OFFSET_TABLE_ +
                           *(int *)(&g_unk_00271628 + GHIDRA_FIELD(g_gamestate, 12, 4) * 4)))();
        return tmp_u10;
      }
      *tmp_pu6 = 0;
      return 0;
    }
    break;
  case 0x11:
    tmp_pb4 = (byte *)param_1[1];
    if ((pgVar7 != (gentity_s *)0x0) && (tmp_pb4 != (byte *)0x0)) {
      tmp_i8 = *(int *)(pgVar7 + 400);
      tmp_b16 = false;
      tmp_b18 = tmp_i8 == 0;
      if (!tmp_b18) {
        tmp_i15 = 6;
        tmp_pb13 = tmp_pb4;
        tmp_pb14 = (byte *)0x25dcc9;
        do {
          if (tmp_i15 == 0) break;
          tmp_i15 = tmp_i15 + -1;
          tmp_b16 = *tmp_pb13 < *tmp_pb14;
          tmp_b18 = *tmp_pb13 == *tmp_pb14;
          tmp_pb13 = tmp_pb13 + (uint)tmp_b19 * -2 + 1;
          tmp_pb14 = tmp_pb14 + (uint)tmp_b19 * -2 + 1;
        } while (tmp_b18);
        tmp_b17 = (!tmp_b16 && !tmp_b18) < tmp_b16;
        if ((!tmp_b16 && !tmp_b18) == tmp_b16) {
          tmp_u10 = *(uint32_t *)(tmp_i8 + 0xc7c);
          tmp_pb4[0x40] = 3;
          tmp_pb4[0x41] = 0;
          tmp_pb4[0x42] = 0;
          tmp_pb4[0x43] = 0;
          *(uint32_t *)(tmp_pb4 + 0x44) = tmp_u10;
          return 0;
        }
        tmp_i15 = 7;
        tmp_b16 = false;
        tmp_pb13 = tmp_pb4;
        tmp_pb14 = (byte *)0x25dcac;
        do {
          if (tmp_i15 == 0) break;
          tmp_i15 = tmp_i15 + -1;
          tmp_b17 = *tmp_pb13 < *tmp_pb14;
          tmp_b16 = *tmp_pb13 == *tmp_pb14;
          tmp_pb13 = tmp_pb13 + (uint)tmp_b19 * -2 + 1;
          tmp_pb14 = tmp_pb14 + (uint)tmp_b19 * -2 + 1;
        } while (tmp_b16);
        tmp_b18 = (!tmp_b17 && !tmp_b16) < tmp_b17;
        if ((!tmp_b17 && !tmp_b16) == tmp_b17) {
          tmp_u10 = *(uint32_t *)(tmp_i8 + 0xc74);
          tmp_pb4[0x40] = 3;
          tmp_pb4[0x41] = 0;
          tmp_pb4[0x42] = 0;
          tmp_pb4[0x43] = 0;
          *(uint32_t *)(tmp_pb4 + 0x44) = tmp_u10;
          return 0;
        }
        tmp_i15 = 3;
        tmp_b16 = false;
        tmp_pb13 = tmp_pb4;
        tmp_pb14 = &g_unk_0026fc7f;
        do {
          if (tmp_i15 == 0) break;
          tmp_i15 = tmp_i15 + -1;
          tmp_b18 = *tmp_pb13 < *tmp_pb14;
          tmp_b16 = *tmp_pb13 == *tmp_pb14;
          tmp_pb13 = tmp_pb13 + (uint)tmp_b19 * -2 + 1;
          tmp_pb14 = tmp_pb14 + (uint)tmp_b19 * -2 + 1;
        } while (tmp_b16);
        if ((!tmp_b18 && !tmp_b16) == tmp_b18) {
          tmp_u10 = *(uint32_t *)(tmp_i8 + 0xf0);
          tmp_pb4[0x40] = 3;
          tmp_pb4[0x41] = 0;
          tmp_pb4[0x42] = 0;
          tmp_pb4[0x43] = 0;
          *(uint32_t *)(tmp_pb4 + 0x44) = tmp_u10;
          return 0;
        }
      }
    }
    break;
  case 0x13:
    tmp_pi2 = (int *)param_1[1];
    if (pgVar7 == (gentity_s *)0x0) {
      return 0;
    }
    if (tmp_pi2 == (int *)0x0) {
      return 0;
    }
    if (*(int *)(pgVar7 + 0x194) == 0) {
      return 0;
    }
    tmp_i8 = *(int *)(pgVar7 + 400);
    if (tmp_i8 == 0) {
      return 0;
    }
    tmp_u10 = _weaponBotToGame(*tmp_pi2);
    tmp_i15 = *(int *)(tmp_i8 + 3000);
    switch(tmp_u10) {
    case 5:
      tmp_u11 = 0;
      if ((*(byte *)(tmp_i8 + 0x6a) & 8) == 0) {
        if (*(int *)(tmp_i8 + 0xc44) < 1) {
          tmp_u11 = (uint)(*(int *)(&g_unk_02a983e0 + tmp_i15 * 4) <=
                         g_unk_00abe908 - *(int *)(tmp_i8 + 0x478));
        }
        else {
          tmp_u11 = (uint)((float)*(int *)(&g_unk_02a983e0 + tmp_i15 * 4) * 0.66 <=
                         (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
        }
      }
      break;
    default:
      tmp_u11 = 1;
      break;
    case 0xc:
      if (*(int *)(tmp_i8 + 0xc3c) < 1) {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a983f8)[tmp_i15] * 0.25 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      else {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a983f8)[tmp_i15] * 0.15 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      break;
    case 0xf:
      if (*(int *)(tmp_i8 + 0xc34) < 3) {
        tmp_u11 = (uint)((int)(&g_unk_02a983f0)[tmp_i15] <= g_unk_00abe908 - *(int *)(tmp_i8 + 0x478));
      }
      else {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a983f0)[tmp_i15] * 0.66 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      break;
    case 0x12:
      if (*(int *)(tmp_i8 + 0xc38) < 2) {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a983e8)[tmp_i15] * 0.25 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      else {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a983e8)[tmp_i15] * 0.15 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      break;
    case 0x13:
      tmp_u11 = 0;
      if (*(int *)(tmp_i8 + 0xe4) == 3) {
        if (*(int *)(tmp_i8 + 0xc3c) < 2) {
          tmp_u11 = (uint)((int)(&g_unk_02a983f8)[tmp_i15] < g_unk_00abe908 - *(int *)(tmp_i8 + 0x478));
        }
        else {
          tmp_u11 = (uint)((float)(int)(&g_unk_02a983f8)[tmp_i15] * 0.66 <
                         (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
        }
      }
      break;
    case 0x15:
      if (*(int *)(tmp_i8 + 0xc3c) < 2) {
        tmp_u11 = (uint)((int)(&g_unk_02a983f8)[tmp_i15] <= g_unk_00abe908 - *(int *)(tmp_i8 + 0x478));
      }
      else {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a983f8)[tmp_i15] * 0.66 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      break;
    case 0x19:
    case 0x33:
      if (1 < *(int *)(tmp_i8 + 0xc34)) {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a983f0)[tmp_i15] * 0.33 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
        break;
      }
      goto LAB_00237856;
    case 0x1a:
    case 0x1c:
      if (*(int *)(tmp_i8 + 0xc48) < 2) {
        tmp_u11 = (uint)((int)(&g_unk_02a98400)[tmp_i15] <= g_unk_00abe908 - *(int *)(tmp_i8 + 0x478));
      }
      else {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a98400)[tmp_i15] * 0.66 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      break;
    case 0x21:
    case 0x2a:
      if (*(int *)(tmp_i8 + 0xc44) < 1) {
        tmp_u11 = (uint)((float)*(int *)(&g_unk_02a983e0 + tmp_i15 * 4) * 0.5 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      else {
        tmp_u11 = (uint)((float)*(int *)(&g_unk_02a983e0 + tmp_i15 * 4) * 0.33 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      }
      break;
    case 0x24:
    case 0x25:
      if (*(int *)(tmp_i8 + 0xc34) == 5) {
        tmp_u11 = (uint)((float)(int)(&g_unk_02a983f0)[tmp_i15] * 0.4 <=
                       (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
        break;
      }
LAB_00237856:
      tmp_u11 = (uint)((float)(int)(&g_unk_02a983f0)[tmp_i15] * 0.5 <=
                     (float)(g_unk_00abe908 - *(int *)(tmp_i8 + 0x478)));
      break;
    case 0x2b:
      tmp_u11 = (uint)((int)(&g_unk_02a983e8)[tmp_i15] <= g_unk_00abe908 - *(int *)(tmp_i8 + 0x478));
    }
    tmp_pi2[2] = tmp_u11;
    return 0;
  case 0x14:
    tmp_i8 = param_1[1];
    if (((pgVar7 != (gentity_s *)0x0) && (tmp_i8 != 0)) &&
       ((*(int *)(pgVar7 + 0x194) != 0 && (*(int *)(pgVar7 + 400) != 0)))) {
      tmp_i15 = *(int *)(*(int *)(pgVar7 + 400) + 0x51c);
      *(uint32_t *)(tmp_i8 + 8) = 0x44bb8000;
      *(float *)(tmp_i8 + 4) = (float)tmp_i15;
      return 0;
    }
    break;
  case 0x15:
    tmp_pu6 = (uint32_t *)param_1[1];
    if ((((tmp_pu6 != (uint32_t *)0x0) && ((*(byte *)((int)tmp_pu6 + 1) & 0x80) == 0)) &&
        (GHIDRA_FIELD(g_cheats, 12, 4) != 0)) && (tmp_i8 = EntityFromHandle(*tmp_pu6), tmp_i8 != 0)) {
      G_Damage(tmp_i8,0,0,0,0,100000,8,0x1e);
      return 0;
    }
    break;
  case 0x16:
    tmp_pc5 = (char *)param_1[1];
    if ((tmp_pc5 != (char *)0x0) && (*tmp_pc5 != '\0')) {
      trap_SendConsoleCommand(0,tmp_pc5);
      return 0;
    }
    break;
  default:
    return 5;
  case 0x1a:
    tmp_i8 = param_1[1];
    if ((tmp_i8 != 0) && (GHIDRA_FIELD(g_cheats, 12, 4) != 0)) {
      tmp_u10 = va("setviewpos %f %f %f %f",(double)*(float *)(tmp_i8 + 0x40),
                  (double)*(float *)(tmp_i8 + 0x44),(double)*(float *)(tmp_i8 + 0x48),0,0);
      trap_SendConsoleCommand(0,tmp_u10);
      return 0;
    }
    break;
  case 0x1f:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      if (((((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 0x194) != 0)) &&
           (tmp_i8 = *(int *)(pgVar7 + 400), tmp_i8 != 0)) &&
          ((-0xaf < *(int *)(pgVar7 + 0x2c8) && (*(int *)(tmp_i8 + 4) == 3)))) &&
         ((*(byte *)(tmp_i8 + 0xd) & 0x40) == 0)) {
        limbo(pgVar7,1);
        *tmp_pu6 = 1;
        return 0;
      }
      *tmp_pu6 = 0;
      return 0;
    }
    break;
  case 0x20:
    tmp_pu3 = (uint *)param_1[1];
    if (tmp_pu3 != (uint *)0x0) {
      if (((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 0x194) != 0)) &&
         ((tmp_i8 = *(int *)(pgVar7 + 400), tmp_i8 != 0 &&
          ((*(int *)(tmp_i8 + 4) == 3 && ((*(byte *)(tmp_i8 + 0xd) & 0x40) == 0)))))) {
        *tmp_pu3 = (uint)(*(int *)(tmp_i8 + 0x410) == 7);
        return 0;
      }
      *tmp_pu3 = 0xffffffff;
      return 0;
    }
    break;
  case 0x21:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      if (((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 0x194) != 0)) &&
         (tmp_i8 = *(int *)(pgVar7 + 400), tmp_i8 != 0)) {
        if (((*(int *)(pgVar7 + 0x2c8) < 0x3d) || (*(int *)(tmp_i8 + 4) == 3)) &&
           ((*(byte *)(tmp_i8 + 0xd) & 0x40) == 0)) {
          *tmp_pu6 = 1;
          return 0;
        }
        if (*(int *)(tmp_i8 + 4) == 0) {
          *tmp_pu6 = 0;
          return 0;
        }
      }
      *tmp_pu6 = 0xffffffff;
      return 0;
    }
    break;
  case 0x22:
    tmp_pi2 = (int *)param_1[1];
    if (((pgVar7 != (gentity_s *)0x0) && (tmp_pi2 != (int *)0x0)) &&
       ((*(int *)(pgVar7 + 0x194) != 0 && (*(int *)(pgVar7 + 400) != 0)))) {
      tmp_i8 = *(int *)(*(int *)(pgVar7 + 400) + 3000);
      if (tmp_i8 == 1) {
        *tmp_pi2 = GHIDRA_FIELD(g_redlimbotime, 12, 4) -
                  ((g_unk_02a99b84 + g_unk_02a99a6c) - g_unk_00abe918) % (int)GHIDRA_FIELD(g_redlimbotime, 12, 4);
        return 0;
      }
      if (tmp_i8 == 2) {
        *tmp_pi2 = GHIDRA_FIELD(g_bluelimbotime, 12, 4) -
                  ((g_unk_02a99b84 + g_unk_02a99a68) - g_unk_00abe918) % (int)GHIDRA_FIELD(g_bluelimbotime, 12, 4);
        return 0;
      }
    }
    break;
  case 0x23:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      tmp_i8 = EntityFromHandle(*tmp_pu6);
      if ((((tmp_i8 != 0) && (*(int *)(tmp_i8 + 0x194) != 0)) && (*(int *)(tmp_i8 + 0x120) != 0)) &&
         (*(int *)(tmp_i8 + 0x458) == 0)) {
        if (*(int *)(tmp_i8 + 0x388) == -1) {
          tmp_pu6[1] = *(uint32_t *)(tmp_i8 + 0x2c8);
          return 0;
        }
        tmp_pu6[1] = *(uint32_t *)(g_entities + *(int *)(tmp_i8 + 0x388) * 0x600 + 0x2c8);
        return 0;
      }
      tmp_pu6[1] = 0xffffffff;
      return 0;
    }
    break;
  case 0x24:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      tmp_i8 = EntityFromHandle(*tmp_pu6);
      if (((pgVar7 != (gentity_s *)0x0) && (tmp_i8 != 0)) && (*(int *)(pgVar7 + 400) != 0)) {
        tmp_u10 = *(uint32_t *)(*(int *)(pgVar7 + 400) + 0x51c);
        tmp_pu6[2] = 0x5dc;
        tmp_pu6[1] = tmp_u10;
        return 0;
      }
      tmp_pu6[1] = 0xffffffff;
      tmp_pu6[2] = 0xffffffff;
      return 0;
    }
    break;
  case 0x25:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      tmp_i8 = EntityFromHandle(*tmp_pu6);
      if (((tmp_i8 != 0) && (*(int *)(tmp_i8 + 0x194) != 0)) &&
         (*(int *)(tmp_i8 + 0x180) < g_unk_00abe900)) {
        HandleFromEntity((gentity_s *)local_430);
        tmp_pu6[1] = local_430[0];
        return 0;
      }
      *(uint16_t *)(tmp_pu6 + 1) = 0xffff;
      *(uint16_t *)((int)tmp_pu6 + 6) = 0;
      return 0;
    }
    break;
  case 0x26:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      tmp_i8 = EntityFromHandle(*tmp_pu6);
      if (((tmp_i8 != 0) && (pgVar7 != (gentity_s *)0x0)) && (*(int *)(tmp_i8 + 0x194) != 0)) {
        tmp_i8 = G_EmplacedGunIsRepairable(tmp_i8,pgVar7);
        tmp_pu6[1] = (uint)(tmp_i8 == 1);
        return 0;
      }
      tmp_pu6[1] = 0;
      return 0;
    }
    break;
  case 0x27:
    tmp_i8 = param_1[1];
    if (((pgVar7 != (gentity_s *)0x0) && (tmp_i8 != 0)) &&
       ((*(int *)(pgVar7 + 0x194) != 0 &&
        ((tmp_i15 = *(int *)(pgVar7 + 400), tmp_i15 != 0 && ((*(uint *)(tmp_i15 + 0x68) & 0x8020) != 0)
         ))))) {
      AngleVectors(tmp_i15 + 0x52c0,tmp_i8,0,0);
      tmp_i15 = *(int *)(pgVar7 + 400);
      if ((*(byte *)(tmp_i15 + 0x69) & 0x80) == 0) {
        tmp_f1 = *(float *)(tmp_i15 + 0x52bc);
        *(float *)(tmp_i8 + 0xc) = -tmp_f1;
        *(float *)(tmp_i8 + 0x10) = tmp_f1;
        tmp_f1 = *(float *)(tmp_i15 + 0x52b8);
        *(float *)(tmp_i8 + 0x14) = -tmp_f1;
        *(float *)(tmp_i8 + 0x18) = tmp_f1;
        return 0;
      }
      *(uint32_t *)(tmp_i8 + 0xc) = 0xc3b40000;
      *(uint32_t *)(tmp_i8 + 0x10) = 0xc3b40000;
      *(uint32_t *)(tmp_i8 + 0x14) = 0x41600000;
      *(uint32_t *)(tmp_i8 + 0x18) = 0x42480000;
      return 0;
    }
    break;
  case 0x28:
    tmp_pi2 = (int *)param_1[1];
    if ((((pgVar7 != (gentity_s *)0x0) && (tmp_pi2 != (int *)0x0)) && (*(int *)(pgVar7 + 0x194) != 0)
        ) && (tmp_i8 = *(int *)(pgVar7 + 400), tmp_i8 != 0)) {
      if (*tmp_pi2 == 0x2b) {
        tmp_pi2[1] = (uint)((*(uint *)(pgVar7 + 8) & 0x2800) != 0);
        return 0;
      }
      tmp_i15 = _weaponBotToGame(*tmp_pi2);
      tmp_pi2[1] = (uint)(*(int *)(ammoTableMP + tmp_i15 * 0x48 + 0x20) != 0 &&
                        *(int *)(ammoTableMP + tmp_i15 * 0x48 + 0x20) <=
                        *(int *)(tmp_i8 + 0x49c + tmp_i15 * 4));
      return 0;
    }
    break;
  case 0x29:
  case 0x2a:
    tmp_pi2 = (int *)param_1[1];
    if (tmp_pi2 != (int *)0x0) {
      if (((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 0x194) != 0)) &&
         (tmp_i15 = *(int *)(pgVar7 + 400), tmp_i15 != 0)) {
        tmp_i12 = *tmp_pi2;
        if (tmp_i12 == 0x28) {
          *tmp_pi2 = 0x27;
          tmp_i12 = 0x27;
        }
        else if (tmp_i12 == 0x2a) {
          *tmp_pi2 = 0x29;
          tmp_i12 = 0x29;
        }
        if (tmp_i8 == 0x2a) {
          tmp_u10 = _weaponBotToGame(tmp_i12);
          *(uint32_t *)(tmp_i15 + 0xbd0) = tmp_u10;
          tmp_u10 = _weaponBotToGame(tmp_i12);
          *(uint32_t *)(tmp_i15 + 0xbe0) = tmp_u10;
        }
        else {
          if (((*(byte *)(tmp_i15 + 0xd) & 0x40) == 0) &&
             (tmp_i8 = _weaponBotToGame(tmp_i12), *(int *)(tmp_i15 + 0xbcc) != tmp_i8)) {
            *(uint32_t *)(tmp_i15 + 0xf24) = 1;
          }
          tmp_u10 = _weaponBotToGame(tmp_i12);
          *(uint32_t *)(tmp_i15 + 0xbcc) = tmp_u10;
          tmp_u10 = _weaponBotToGame(tmp_i12);
          *(uint32_t *)(tmp_i15 + 0xbdc) = tmp_u10;
        }
        tmp_pi2[1] = 1;
        return 0;
      }
      tmp_pi2[1] = 0;
      return 0;
    }
    break;
  case 0x2b:
    tmp_pi2 = (int *)param_1[1];
    if (((pgVar7 != (gentity_s *)0x0) && (tmp_pi2 != (int *)0x0)) &&
       (tmp_i8 = *(int *)(pgVar7 + 400), tmp_i8 != 0)) {
      tmp_i15 = 0;
      if (*(int *)(tmp_i8 + 0x428) - 2U < 0x24) {
        tmp_i15 = (int)(char)(&UNK_00270b5e)[*(int *)(tmp_i8 + 0x428)];
      }
      tmp_i8 = *(int *)(tmp_i8 + 0x42c);
      *tmp_pi2 = tmp_i15;
      tmp_pi2[1] = tmp_i8;
      return 0;
    }
    break;
  case 0x2c:
    if (((pgVar7 != (gentity_s *)0x0) && ((uint32_t *)param_1[1] != (uint32_t *)0x0)) &&
       (*(int *)(pgVar7 + 400) != 0)) {
      SetPlayerSpawn(pgVar7,*(uint32_t *)param_1[1],1);
      return 0;
    }
    break;
  case 0x2d:
    if ((((pgVar7 != (gentity_s *)0x0) && ((uint32_t *)param_1[1] != (uint32_t *)0x0)) &&
        (*(int *)(pgVar7 + 0x194) != 0)) &&
       (((tmp_i8 = *(int *)(pgVar7 + 400), tmp_i8 != 0 && (-1 < *(int *)(pgVar7 + 0x2c8))) &&
        ((*(int *)(tmp_i8 + 0x164) != 0 || (*(int *)(tmp_i8 + 0x168) != 0)))))) {
      *(uint32_t *)param_1[1] = 1;
      return 0;
    }
    break;
  case 0x2e:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      tmp_i8 = EntityFromHandle(*tmp_pu6);
      if (((pgVar7 == (gentity_s *)0x0) || (tmp_i8 == 0)) ||
         ((*(int *)(pgVar7 + 0x194) == 0 || (*(int *)(tmp_i8 + 0x194) == 0)))) {
        tmp_pu6[1] = 0xffffffff;
        return 0;
      }
      tmp_i15 = G_IsConstructible(*(uint32_t *)(*(int *)(pgVar7 + 400) + 3000),tmp_i8);
      if (tmp_i15 != 0) {
        tmp_pu6[1] = 1;
        return 0;
      }
      tmp_i8 = G_ConstructionForTeam(tmp_i8,*(uint32_t *)(*(int *)(pgVar7 + 400) + 3000));
      if ((tmp_i8 != 0) && (tmp_i8 = G_ConstructionIsFullyBuilt(tmp_i8), tmp_i8 != 0)) {
        tmp_pu6[1] = 0;
        return 0;
      }
      tmp_pu6[1] = 0xffffffff;
      return 0;
    }
    break;
  case 0x2f:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (((tmp_pu6 != (uint32_t *)0x0) &&
        (tmp_i8 = EntityFromHandle(*tmp_pu6), pgVar7 != (gentity_s *)0x0)) &&
       ((tmp_i8 != 0 && ((*(int *)(pgVar7 + 0x194) != 0 && (*(int *)(tmp_i8 + 0x194) != 0)))))) {
      tmp_i15 = *(int *)(tmp_i8 + 4);
      if (tmp_i15 == 0xc) {
        tmp_i8 = *(int *)(tmp_i8 + 0x264);
        if (tmp_i8 == 0) {
          tmp_pu6[1] = 0;
          return 0;
        }
        tmp_i15 = *(int *)(tmp_i8 + 4);
      }
      if (tmp_i15 == 0x20) {
        if ((*(byte *)(tmp_i8 + 0x1a8) & 2) != 0) {
          tmp_pu6[1] = 0xffffffff;
          return 0;
        }
        tmp_i15 = G_ConstructionIsPartlyBuilt(tmp_i8);
        if ((tmp_i15 != 0) && (*(int *)(tmp_i8 + 0x108) != *(int *)(*(int *)(pgVar7 + 400) + 3000))) {
          tmp_pu6[1] = 1;
          return 0;
        }
        tmp_i15 = *(int *)(tmp_i8 + 0x218);
        if ((tmp_i15 == 0) || (*(int *)(tmp_i15 + 4) != 0xc)) {
          tmp_pu6[1] = 0;
          return 0;
        }
        tmp_i15 = *(int *)(tmp_i15 + 0x2e8);
        do {
          if (tmp_i15 == 0) {
            return 0;
          }
          tmp_i12 = G_ConstructionIsPartlyBuilt(tmp_i15);
          if ((tmp_i12 != 0) && (*(int *)(tmp_i15 + 0x108) != *(int *)(*(int *)(pgVar7 + 400) + 3000))
             ) {
            tmp_pu6[1] = 1;
            return 0;
          }
          tmp_i15 = *(int *)(tmp_i15 + 0x2e8);
        } while (*(int *)(*(int *)(tmp_i8 + 0x218) + 0x2e8) != tmp_i15);
      }
      else if ((((tmp_i15 == 0xe) && (tmp_i15 = *(int *)(tmp_i8 + 0x218), tmp_i15 != 0)) &&
               (*(int *)(tmp_i15 + 4) == 0xc)) &&
              ((((*(uint *)(tmp_i15 + 0x1a8) & 2) != 0 &&
                (*(int *)(*(int *)(pgVar7 + 400) + 3000) == 1)) ||
               (((*(uint *)(tmp_i15 + 0x1a8) & 1) != 0 &&
                (*(int *)(*(int *)(pgVar7 + 400) + 3000) == 2)))))) {
        if (*(int *)(tmp_i8 + 0x2c8) < 1) {
          tmp_pu6[1] = 0;
          return 0;
        }
        tmp_pu6[1] = 1;
        return 0;
      }
    }
    break;
  case 0x31:
    tmp_pu6 = (uint32_t *)param_1[1];
    if ((((tmp_pu6 != (uint32_t *)0x0) && (tmp_i8 = EntityFromHandle(*tmp_pu6), tmp_i8 != 0)) &&
        (*(int *)(tmp_i8 + 0x194) != 0)) && (*(int *)(tmp_i8 + 4) == 3)) {
      tmp_i15 = *(int *)(tmp_i8 + 0xe8);
      if (tmp_i15 != 0x19) {
        if (tmp_i15 < 0x1a) {
          if (tmp_i15 != 0xf) {
            return 0;
          }
        }
        else {
          if (tmp_i15 == 0x1a) {
            tmp_pu6[1] = (uint)(0xf9 < *(int *)(tmp_i8 + 0x2c8));
            return 0;
          }
          if (tmp_i15 != 0x33) {
            return 0;
          }
        }
      }
      tmp_pu6[1] = (uint)(3 < *(int *)(tmp_i8 + 0x108));
      return 0;
    }
    break;
  case 0x32:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (((tmp_pu6 != (uint32_t *)0x0) &&
        (tmp_i8 = EntityFromHandle(*tmp_pu6), pgVar7 != (gentity_s *)0x0)) &&
       ((tmp_i15 = *(int *)(pgVar7 + 400), tmp_i8 != 0 && (tmp_i15 != 0)))) {
      if ((*(int *)(tmp_i8 + 0xa4) < 1) || (bg_numItems <= *(int *)(tmp_i8 + 0xa4))) {
        tmp_pu6[1] = 0xffffffff;
        return 0;
      }
      tmp_i15 = BG_CanItemBeGrabbed(tmp_i8,tmp_i15,tmp_i15 + 0xc30,*(uint32_t *)(tmp_i15 + 3000));
      if (tmp_i15 == 0) {
        tmp_pu6[1] = 0;
        return 0;
      }
      tmp_b19 = *(byte *)(tmp_i8 + 0x1b1);
      tmp_pu6[1] = 1;
      if ((tmp_b19 & 0x10) == 0) {
        if (*(int *)(*(int *)(pgVar7 + 400) + 3000) == 1) {
          if (*(int *)(tmp_i8 + 0x5c0) == 0x3317f) {
            (**(void **)(*(int *)this + 0x60))(local_430,this,*tmp_pu6);
            if ((local_434 & 0x8000) != 0) {
              tmp_pu6[1] = 0;
            }
            return 0;
          }
        }
        else if ((*(int *)(*(int *)(pgVar7 + 400) + 3000) == 2) &&
                (*(int *)(tmp_i8 + 0x5c0) == 0x36af1)) {
          (**(void **)(*(int *)this + 0x60))(local_430,this,*tmp_pu6);
          if ((local_434 & 0x8000) != 0) {
            tmp_pu6[1] = 0;
            return 0;
          }
          return 0;
        }
      }
    }
    break;
  case 0x33:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (((pgVar7 != (gentity_s *)0x0) && (tmp_pu6 != (uint32_t *)0x0)) &&
       (*(int *)(pgVar7 + 400) != 0)) {
      tmp_u10 = G_CountTeamLandmines(*(uint32_t *)(*(int *)(pgVar7 + 400) + 3000));
      *tmp_pu6 = tmp_u10;
      tmp_pu6[1] = GHIDRA_FIELD(team_maxLandmines, 12, 4);
      return 0;
    }
    break;
  case 0x34:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      if (pgVar7 == (gentity_s *)0x0) {
        return 3;
      }
      if (*(int *)(pgVar7 + 4) - 0x31U < 2) {
        tmp_pu6[2] = *(uint32_t *)(pgVar7 + 0x2d0);
        *tmp_pu6 = *(uint32_t *)(pgVar7 + 0x2c8);
        tmp_pu6[1] = *(uint32_t *)(pgVar7 + 0x2e4);
        return 0;
      }
      return 3;
    }
    break;
  case 0x35:
    if (pgVar7 == (gentity_s *)0x0) {
      return 3;
    }
    tmp_i8 = *(int *)(pgVar7 + 400);
    if (tmp_i8 == 0) {
      return 3;
    }
    tmp_pu6 = (uint32_t *)param_1[1];
    *tmp_pu6 = *(uint32_t *)(tmp_i8 + 0xc30);
    tmp_pu6[1] = *(uint32_t *)(tmp_i8 + 0xc34);
    tmp_pu6[2] = *(uint32_t *)(tmp_i8 + 0xc38);
    tmp_pu6[3] = *(uint32_t *)(tmp_i8 + 0xc3c);
    tmp_pu6[4] = *(uint32_t *)(tmp_i8 + 0xc40);
    tmp_u10 = *(uint32_t *)(tmp_i8 + 0xc48);
    tmp_pu6[5] = *(uint32_t *)(tmp_i8 + 0xc44);
    tmp_pu6[6] = tmp_u10;
    return 0;
  case 0x36:
    if ((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) {
      trap_EA_Command(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,"fireteam create");
      return 0;
    }
    break;
  case 0x37:
    if ((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) {
      trap_EA_Command(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,"fireteam disband");
      return 0;
    }
    break;
  case 0x38:
    if ((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) {
      trap_EA_Command(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,"fireteam leave");
      return 0;
    }
    break;
  case 0x39:
    if ((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) {
      tmp_u10 = va("fireteam apply %i",*(uint32_t *)param_1[1]);
      trap_EA_Command(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,tmp_u10);
      return 0;
    }
    break;
  case 0x3a:
    if (((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) &&
       (tmp_i8 = EntityFromHandle(*(uint32_t *)param_1[1]), tmp_i8 != 0)) {
      tmp_u10 = va("fireteam invite %i",(tmp_i8 + -0x93e4a0 >> 9) * -0x55555555 + 1);
      trap_EA_Command(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,tmp_u10);
      return 0;
    }
    break;
  case 0x3b:
    if (((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) &&
       (tmp_i8 = EntityFromHandle(*(uint32_t *)param_1[1]), tmp_i8 != 0)) {
      tmp_u10 = va("fireteam warn %i",(tmp_i8 + -0x93e4a0 >> 9) * -0x55555555 + 1);
      trap_EA_Command(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,tmp_u10);
      return 0;
    }
    break;
  case 0x3c:
    if (((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) &&
       (tmp_i8 = EntityFromHandle(*(uint32_t *)param_1[1]), tmp_i8 != 0)) {
      tmp_u10 = va("fireteam kick %i",(tmp_i8 + -0x93e4a0 >> 9) * -0x55555555 + 1);
      trap_EA_Command(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,tmp_u10);
      return 0;
    }
    break;
  case 0x3d:
    if (((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) &&
       (tmp_i8 = EntityFromHandle(*(uint32_t *)param_1[1]), tmp_i8 != 0)) {
      tmp_u10 = va("fireteam propose %i",(tmp_i8 + -0x93e4a0 >> 9) * -0x55555555 + 1);
      trap_EA_Command(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,tmp_u10);
      return 0;
    }
    break;
  case 0x3e:
    if ((pgVar7 != (gentity_s *)0x0) && (*(int *)(pgVar7 + 400) != 0)) {
      tmp_pu6 = (uint32_t *)param_1[1];
      local_41c[0] = (uint32_t *)0x0;
      tmp_i8 = G_IsOnFireteam(((int)(pgVar7 + -0x93e4a0) >> 9) * -0x55555555,local_41c);
      if (tmp_i8 != 0) {
        tmp_pu6[0x42] = *local_41c[0];
        HandleFromEntity((gentity_s *)local_430);
        tmp_u10 = GHIDRA_FIELD(g_maxclients, 12, 4);
        *tmp_pu6 = 1;
        tmp_pu6[1] = local_430[0];
        if (0 < (int)tmp_u10) {
          tmp_i15 = 0;
          tmp_i8 = 0;
          do {
            *(uint16_t *)(tmp_pu6 + tmp_i15 + 2) = 0xffff;
            *(uint16_t *)((int)tmp_pu6 + tmp_i15 * 4 + 10) = 0;
            if ((*(char *)((int)local_41c[0] + tmp_i8 + 4) != -1) &&
               (HandleFromEntity((gentity_s *)local_430), (local_430[0] & 0x8000) == 0)) {
              tmp_pu6[tmp_i15 + 2] = local_430[0];
              tmp_i15 = tmp_i15 + 1;
            }
            tmp_i8 = tmp_i8 + 1;
          } while (tmp_i8 < (int)GHIDRA_FIELD(g_maxclients, 12, 4));
          return 0;
        }
      }
      return 0;
    }
    break;
  case 0x3f:
    if ((uint32_t *)param_1[1] != (uint32_t *)0x0) {
      *(uint32_t *)param_1[1] = GHIDRA_FIELD(g_gametype, 12, 4);
      return 0;
    }
    break;
  case 0x40:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      trap_Cvar_Set(*tmp_pu6,tmp_pu6[1]);
      return 0;
    }
    break;
  case 0x41:
    tmp_pu6 = (uint32_t *)param_1[1];
    if (tmp_pu6 != (uint32_t *)0x0) {
      tmp_u10 = trap_Cvar_VariableIntegerValue(*tmp_pu6);
      tmp_pu6[1] = tmp_u10;
      return 0;
    }
    break;
  case 0x42:
    if (((pgVar7 != (gentity_s *)0x0) && ((int *)param_1[1] != (int *)0x0)) &&
       (tmp_i8 = *(int *)(pgVar7 + 400), tmp_i8 != 0)) {
      if (*(int *)param_1[1] < 1) {
        *(uint32_t *)(tmp_i8 + 0xf28) = 1;
        return 0;
      }
      *(uint32_t *)(tmp_i8 + 0xf28) = 0;
      return 0;
    }
  }
  return 0;
}

uint32_t ETInterface_GetEntityFlags(uint32_t this,uint32_t param_2,uint *param_3)
{
  gentity_s gVar1;
  int tmp_i2;
  char tmp_c3;
  gentity_s *pgVar4;
  int tmp_i5;
  uint tmp_u6;
  uint tmp_u7;
  
  pgVar4 = (gentity_s *)EntityFromHandle(param_2);
  if (pgVar4 == (gentity_s *)0x0) {
    return 0;
  }
  if (*(int *)(pgVar4 + 0x194) == 0) {
    return 0;
  }
  if (*(int *)(pgVar4 + 0x2c8) < 1) {
    tmp_i5 = *(int *)(pgVar4 + 400);
    *param_3 = *param_3 | 0x200;
    param_3[1] = param_3[1];
  }
  else {
    tmp_i5 = *(int *)(pgVar4 + 400);
  }
  if ((tmp_i5 != 0) && (tmp_c3 = IsBot(pgVar4), tmp_c3 == '\0')) {
    *param_3 = *param_3 | 0x20000;
    param_3[1] = param_3[1];
  }
  if (*(int *)(pgVar4 + 0x304) < 3) {
    if (0 < *(int *)(pgVar4 + 0x304)) {
      *param_3 = *param_3 | 0x400;
      param_3[1] = param_3[1];
    }
  }
  else {
    *param_3 = *param_3 | 0x800;
    param_3[1] = param_3[1];
  }
  tmp_u7 = *(uint *)(pgVar4 + 8);
  if ((tmp_u7 & 0x40000) != 0) {
    *param_3 = *param_3 | 0x401000;
    param_3[1] = param_3[1];
  }
  if ((tmp_u7 & 0x20) != 0) {
    *param_3 = *param_3;
    param_3[1] = param_3[1] | 6;
  }
  if ((tmp_u7 & 0x8000) != 0) {
    *param_3 = *param_3;
    param_3[1] = param_3[1] | 10;
  }
  tmp_i5 = *(int *)(pgVar4 + 4);
  if (tmp_i5 - 0x31U < 2) {
    if (*(int *)(pgVar4 + 0x458) == 1) {
      *param_3 = *param_3 | 0x20;
      param_3[1] = param_3[1];
    }
  }
  else {
    if (tmp_i5 == 4) {
      *param_3 = *param_3 | 0x10;
      param_3[1] = param_3[1];
      tmp_i5 = _TankIsMountable(pgVar4);
      if (tmp_i5 != 0) {
        *param_3 = *param_3;
        param_3[1] = param_3[1] | 0x80;
      }
      tmp_i5 = G_TankIsOccupied(pgVar4);
      if (tmp_i5 != 0) {
        *param_3 = *param_3;
        param_3[1] = param_3[1] | 2;
      }
      tmp_i5 = *(int *)(pgVar4 + 4);
    }
    if (tmp_i5 == 0x20) {
      tmp_i5 = G_ConstructionIsFullyBuilt(pgVar4);
      if (tmp_i5 == 0) {
        *param_3 = *param_3 | 0x200;
        param_3[1] = param_3[1];
        tmp_i5 = *(int *)(pgVar4 + 4);
      }
      else {
        tmp_i5 = G_ConstructionIsFullyBuilt(pgVar4);
        if (tmp_i5 != 0) {
          *param_3 = *param_3 & 0xfffffdff;
          param_3[1] = param_3[1];
        }
        tmp_i5 = *(int *)(pgVar4 + 4);
      }
    }
  }
  if ((tmp_i5 == 0x29) || ((tmp_i5 == 0 && (*(int *)(pgVar4 + 0x5c0) == 0x1908e)))) {
    tmp_i5 = Simple_EmplacedGunIsRepairable(pgVar4);
    if (tmp_i5 == 0) {
      tmp_u7 = param_3[1];
      tmp_u6 = *param_3 & 0xfffffdff;
    }
    else {
      tmp_u6 = *param_3 | 0x200;
      tmp_u7 = param_3[1];
    }
    *param_3 = tmp_u6 | 0x10;
    param_3[1] = tmp_u7;
    tmp_i5 = _EmplacedGunIsMountable(pgVar4);
    if (tmp_i5 != 0) {
      *param_3 = *param_3;
      param_3[1] = param_3[1] | 0x80;
    }
    if ((((*(int *)(pgVar4 + 0x180) != *(int *)pgVar4) &&
         (tmp_i5 = *(int *)(pgVar4 + 0x180) * 0x600, *(int *)(g_entities + tmp_i5 + 0x368) != 0)) &&
        (*(int *)(g_entities + tmp_i5 + 400) != 0)) && ((g_entities[tmp_i5 + 8] & 0x20) != 0)) {
      *param_3 = *param_3;
      param_3[1] = param_3[1] | 2;
    }
    tmp_i5 = *(int *)(pgVar4 + 4);
  }
  tmp_i2 = *(int *)(pgVar4 + 400);
  if (tmp_i2 == 0) {
LAB_002384a0:
    switch(tmp_i5) {
    case 0:
    case 0x29:
      if ((*(int *)(pgVar4 + 0x5c0) == 0x1908e) &&
         ((*(int *)(pgVar4 + 0x2c8) < 0 || (*(int *)(pgVar4 + 0x458) == 1)))) {
        *param_3 = *param_3 | 0x200;
        param_3[1] = param_3[1];
      }
      break;
    case 1:
      goto _L2112;
    case 2:
      tmp_u7 = *param_3;
      gVar1 = pgVar4[0x14d];
      *param_3 = tmp_u7 | 0x10;
      if (((byte)gVar1 & 1) == 0) {
        *param_3 = tmp_u7 | 0x30;
      }
      break;
    case 3:
    case 0xe:
      *param_3 = *param_3 | 0x10;
      param_3[1] = param_3[1];
      return 0;
    case 0x26:
      tmp_u7 = *param_3;
      tmp_u6 = param_3[1];
      *param_3 = tmp_u7 | 0x10;
      if (((*(int *)(pgVar4 + 0x120) != 0) && (*(int *)(pgVar4 + 0xa4) < 4)) &&
         ((*(int *)(pgVar4 + 0x300) < 0xfa && (-0xb0 < *(int *)(pgVar4 + 0x2c8))))) {
        return 0;
      }
      goto LAB_002385d0;
    }
  }
  else {
    tmp_u7 = *(uint *)(tmp_i2 + 0x68);
    if ((tmp_u7 & 0x200000) != 0) {
      *param_3 = *param_3;
      param_3[1] = param_3[1] | 0x100;
    }
    tmp_u6 = *(uint *)(tmp_i2 + 0xc);
    if ((tmp_u6 & 4) != 0) {
      *param_3 = *param_3 | 0x2000;
      param_3[1] = param_3[1];
    }
    if ((tmp_u7 & 0x80000) != 0) {
      *param_3 = *param_3 | 0x40;
      param_3[1] = param_3[1];
    }
    if ((tmp_u6 & 1) != 0) {
      *param_3 = *param_3 | 0x80;
      param_3[1] = param_3[1];
    }
    if (*(int *)(tmp_i2 + 0x50) != 0x3ff) {
      *param_3 = *param_3 | 0x4000;
      param_3[1] = param_3[1];
    }
    if (*(int *)(tmp_i2 + 0xa8) == 7) {
      *param_3 = *param_3 | 0x8000;
      param_3[1] = param_3[1];
    }
    if (*(int *)(tmp_i2 + 0x16c) != 0) {
      *param_3 = *param_3;
      param_3[1] = param_3[1] | 1;
    }
    if ((*(int *)(tmp_i2 + 0x164) != 0) || (*(int *)(tmp_i2 + 0x168) != 0)) {
      *param_3 = *param_3;
      param_3[1] = param_3[1] | 0x20;
    }
    if ((tmp_u6 & 0x4000) != 0) {
      *param_3 = *param_3;
      param_3[1] = param_3[1] | 0x40;
    }
    if (*(int *)(tmp_i2 + 0xa4) - 0x27U < 3) {
      *param_3 = *param_3 | 0x1000;
      param_3[1] = param_3[1];
    }
    if (((byte)pgVar4[10] & 4) != 0) {
      *param_3 = *param_3 | 0x1000;
      param_3[1] = param_3[1];
    }
    if (0x17fff < (int)(pgVar4 + -0x93e4a0)) goto LAB_002384a0;
_L2112:
    tmp_u7 = *param_3;
    tmp_u6 = param_3[1];
    *param_3 = tmp_u7 | 0x10;
    if (0 < *(int *)(pgVar4 + 0x2c8)) {
      return 0;
    }
    if ((((*(int *)(pgVar4 + 0x120) != 0) && (*(int *)(pgVar4 + 0xa4) < 4)) &&
        (*(int *)(pgVar4 + 0x300) < 0xfa)) && (-0xb0 < *(int *)(pgVar4 + 0x2c8))) {
      if ((g_OmniBotFlags[0xc] & 0x10) == 0) {
        return 0;
      }
      *param_3 = tmp_u7 & 0xfffffdff | 0x50;
      param_3[1] = tmp_u6;
      return 0;
    }
LAB_002385d0:
    *param_3 = tmp_u7 | 0x30;
    param_3[1] = tmp_u6;
  }
  return 0;
}

void ETInterface_GetPointContents(ETInterface *this,float *param_1)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  
  local_18 = *param_1;
  local_14 = param_1[1];
  local_10 = param_1[2];
  tmp_i1 = trap_PointContents(&local_18,0xffffffff);
  obUtilBotContentsFromGameContents(tmp_i1);
  return;
}

// ETInterface::TraceLine(obTraceResult&, float const*, float const*, AABB_t const*, int, int,
// eobBool)

uint32_t ETInterface::TraceLine
          (uint32_t this,uint32_t *param_1,float *param_2,float *param_3,int param_4,
          uint param_5,uint32_t param_6,int param_8)

{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  uint32_t local_60 [3];
  uint8_t local_54 [4];
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t uStack_34;
  int local_28;
  int iStack_24;
  int local_20;
  
  if ((param_8 != 0) && (tmp_i1 = trap_InPVS(param_2,param_3), tmp_i1 == 0)) {
    *param_1 = 0;
    *(uint16_t *)(param_1 + 7) = 0xffff;
    *(uint16_t *)((int)param_1 + 0x1e) = 0;
    return 1;
  }
  if ((param_5 & 1) == 0) {
    tmp_pu4 = &g_unk_02010001;
    if ((param_5 & 4) == 0) {
      tmp_pu4 = (uint8_t *)(param_5 >> 1 & 1);
    }
    if ((param_5 & 8) != 0) {
      tmp_pu4 = (uint8_t *)((uint)tmp_pu4 | 0x6000001);
    }
    if ((param_5 & 0x10) != 0) {
      tmp_pu4 = (uint8_t *)((uint)tmp_pu4 | 9);
    }
    if ((param_5 & 0x20) != 0) {
      tmp_pu4 = (uint8_t *)((uint)tmp_pu4 | 0x38);
    }
    if ((param_5 & 0x100) != 0) {
      tmp_pu4 = (uint8_t *)((uint)tmp_pu4 | 0x10000);
    }
    if ((param_5 & 0xc00) != 0) {
      tmp_pu4 = (uint8_t *)((uint)tmp_pu4 | 0x10001);
    }
    if (((param_5 & 0x200) != 0) &&
       (tmp_i1 = Bot_EntInvisibleBySmokeBomb(param_2,param_3), tmp_i1 != 0)) {
      *param_1 = 0;
      HandleFromEntity((gentity_s *)local_60);
      param_1[7] = local_60[0];
      return 0;
    }
  }
  else {
    tmp_pu4 = (uint8_t *)0xffffffff;
  }
  tmp_i1 = param_4 + 0xc;
  if ((param_5 & 0x400) == 0) {
    tmp_i3 = 0;
    if (param_4 != 0) {
      tmp_i3 = tmp_i1;
    }
    trap_Trace(local_54,param_2,param_4,tmp_i3,param_3,param_6,tmp_pu4);
  }
  else {
    if (param_4 == 0) {
      tmp_i1 = 0;
    }
    trap_TraceNoEnts(local_54,param_2,param_4,tmp_i1,param_3,param_6,tmp_pu4);
  }
  if (local_20 - 0x3feU < 2) {
    *(uint16_t *)(param_1 + 7) = 0xffff;
    *(uint16_t *)((int)param_1 + 0x1e) = 0;
  }
  else {
    HandleFromEntity((gentity_s *)local_60);
    param_1[7] = local_60[0];
  }
  *param_1 = local_4c;
  param_1[4] = local_48;
  param_1[8] = local_50;
  param_1[5] = local_44;
  param_1[6] = local_40;
  param_1[1] = local_3c;
  param_1[2] = local_38;
  param_1[3] = uStack_34;
  tmp_u2 = obUtilBotContentsFromGameContents(iStack_24);
  param_1[9] = tmp_u2;
  tmp_u2 = obUtilBotSurfaceFromGameSurface(local_28);
  param_1[10] = tmp_u2;
  return 0;
}

void ETInterface_GetGoals(void)
{
  bool tmp_b1;
  bool tmp_b2;
  bool tmp_b3;
  char *tmp_pc4;
  char *tmp_pc5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint tmp_u8;
  int tmp_i9;
  int tmp_i10;
  gentity_s *pgVar11;
  int tmp_i12;
  gentity_s *pgVar13;
  uint8_t tmp_u14;
  byte tmp_b15;
  char *tmp_pc16;
  obUserData_t *poVar17;
  char *local_138;
  char *local_134;
  uint32_t local_11c;
  uint local_118;
  uint32_t uStack_14;
  
  tmp_b15 = 0;
  uStack_14 = 0x238a89;
  g_GoalSubmitReady = 1;
  SendDeferredGoals();
  GetMG42s();
  if (g_unk_00abe8a8 < 0x41) {
LAB_00238c00:
    if (0 < numofmg42s) {
      tmp_i12 = 0;
      tmp_pc4 = &g_unk_0083d430;
      do {
        if (tmp_pc4[0x40] == '\0') {
          strcpy((char *)&local_11c,tmp_pc4 + -0x40);
        }
        else {
          strcpy((char *)&local_11c,tmp_pc4);
        }
        tmp_i12 = tmp_i12 + 1;
        Bot_Util_AddGoal("mountmg42",*(gentity_s **)(tmp_pc4 + -0x50),6,(char *)&local_11c,
                         (char *)0x0,(obUserData_t *)0x0);
        Bot_Util_AddGoal("repairmg42",*(gentity_s **)(tmp_pc4 + -0x50),6,(char *)&local_11c,
                         (char *)0x0,(obUserData_t *)0x0);
        tmp_pc4 = tmp_pc4 + 0x94;
      } while (tmp_i12 < numofmg42s);
    }
    return;
  }
  pgVar11 = (gentity_s *)(g_entities + 0x18000);
  tmp_i10 = 0x40;
  tmp_i12 = g_unk_00abe8a8;
LAB_00238adf:
  if (*(int *)(pgVar11 + 0x194) == 0) goto LAB_00238ad0;
  tmp_pc4 = (char *)_GetEntityName(pgVar11);
  switch(*(uint32_t *)(pgVar11 + 4)) {
  case 2:
    if (*(int *)(pgVar11 + 0x5c0) == 0x3317f) {
      tmp_pc5 = "flag";
      poVar17 = (obUserData_t *)0x0;
      tmp_pc16 = (char *)0x0;
      tmp_i12 = 4;
    }
    else {
      if (*(int *)(pgVar11 + 0x5c0) != 0x36af1) break;
      tmp_pc5 = "flag";
      poVar17 = (obUserData_t *)0x0;
      tmp_pc16 = (char *)0x0;
      tmp_i12 = 2;
    }
    goto LAB_00238d53;
  case 4:
    tmp_i12 = 4;
    if ((*(uint *)(pgVar11 + 0x1a8) & 0x20) == 0) {
      tmp_i12 = (-(uint)((*(uint *)(pgVar11 + 0x1a8) & 0x40) == 0) & 4) + 2;
    }
    tmp_pc4 = (char *)_GetEntityName(pgVar11);
    if (((tmp_pc4 != (char *)0x0) && (*(int *)(pgVar11 + 0x5c0) == 0x27cac)) &&
       (*(void **)(pgVar11 + 0x2a4) != G_FreeEntity)) {
      tmp_pc5 = "mover";
      poVar17 = (obUserData_t *)0x0;
      tmp_pc16 = (char *)0x0;
      goto LAB_00238d53;
    }
    break;
  case 0xc:
    tmp_i12 = G_ConstructionForTeam(pgVar11,1);
    tmp_i6 = G_ConstructionForTeam(pgVar11,2);
    if (tmp_i12 == 0) {
      local_138 = (char *)0x0;
      if (tmp_i6 != 0) goto LAB_00238f21;
LAB_00239071:
      tmp_b1 = false;
      if (tmp_i12 == 0) {
        tmp_b3 = false;
        tmp_b2 = false;
        local_134 = (char *)0x0;
      }
      else {
        local_134 = (char *)0x0;
        tmp_b2 = false;
LAB_0023908d:
        if (*(char **)(pgVar11 + 0x254) == (char *)0x0) {
          local_118 = 0;
        }
        else {
          tmp_pc4 = strstr(*(char **)(pgVar11 + 0x254),"_construct");
          local_118 = (uint)(tmp_pc4 != (char *)0x0);
        }
        local_11c = 3;
        Bot_Util_AddGoal("build",pgVar11,2,local_138,"Mobile",(obUserData_t *)&local_11c);
        if (tmp_b2) {
LAB_0023911a:
          if (*(char **)(pgVar11 + 0x254) == (char *)0x0) {
            local_118 = 0;
          }
          else {
            tmp_pc4 = strstr(*(char **)(pgVar11 + 0x254),"_construct");
            local_118 = (uint)(tmp_pc4 != (char *)0x0);
          }
          local_11c = 3;
          Bot_Util_AddGoal("build",pgVar11,4,local_134,"Mobile",(obUserData_t *)&local_11c);
          tmp_b3 = true;
        }
        else {
          tmp_b3 = false;
          tmp_b2 = true;
        }
      }
LAB_00239191:
      if (*(int *)(pgVar11 + 0x264) != 0) {
        tmp_i12 = _GetEntityName(pgVar11);
        if (tmp_i12 != 0) {
          local_138 = (char *)_GetEntityName(pgVar11);
        }
        tmp_i12 = _GetEntityName(pgVar11);
        if (tmp_i12 != 0) {
          local_134 = (char *)_GetEntityName(pgVar11);
        }
        pgVar13 = *(gentity_s **)(pgVar11 + 0x264);
        tmp_pc4 = *(char **)(pgVar13 + 600);
        if ((tmp_pc4 != (char *)0x0) &&
           (tmp_pc16 = strstr(tmp_pc4,"_construct"), tmp_pc16 != (char *)0x0)) {
          Q_strncpyz(&local_11c,tmp_pc4,0x100);
          tmp_pc16[(int)&local_11c - *(int *)(*(int *)(pgVar11 + 0x264) + 600)] = '\0';
          tmp_u7 = BG_StringHashValue(&local_11c);
          tmp_i12 = G_FindByTargetnameFast(0,&local_11c,tmp_u7);
          if ((tmp_i12 != 0) &&
             ((*(int *)(tmp_i12 + 4) == 4 && (*(int *)(tmp_i12 + 0x5c0) == 0x27cac)))) break;
          pgVar13 = *(gentity_s **)(pgVar11 + 0x264);
        }
        if (*(int *)(pgVar13 + 4) == 0x20) {
          local_11c = 3;
          local_118 = 0;
          tmp_i12 = *(int *)(pgVar13 + 0x4f4);
          if (tmp_i12 == 1) {
LAB_0023963a:
            local_118 = 3;
          }
          else if (tmp_i12 == 2) {
            local_118 = 1;
          }
          else {
            if (tmp_i12 == -1) goto LAB_0023963a;
            if (-1 < tmp_i12) {
              if (tmp_b2) {
                Bot_Util_AddGoal("explode",pgVar13,4,local_138,"ExplosiveType",
                                 (obUserData_t *)&local_11c);
              }
              if (tmp_b3) {
                Bot_Util_AddGoal("explode",*(gentity_s **)(pgVar11 + 0x264),2,local_134,
                                 "ExplosiveType",(obUserData_t *)&local_11c);
              }
              break;
            }
            local_118 = 2;
          }
          if ((tmp_b1) && (tmp_i12 = Q_stricmp(local_138,local_134), tmp_i12 == 0)) {
            Bot_Util_AddGoal("plant",*(gentity_s **)(pgVar11 + 0x264),6,local_138,"ExplosiveType",
                             (obUserData_t *)&local_11c);
            CheckForMG42(*(gentity_s **)(pgVar11 + 0x264),local_138);
          }
          else {
            if (tmp_b2) {
              Bot_Util_AddGoal("plant",*(gentity_s **)(pgVar11 + 0x264),4,local_138,"ExplosiveType",
                               (obUserData_t *)&local_11c);
              CheckForMG42(*(gentity_s **)(pgVar11 + 0x264),local_138);
            }
            if (tmp_b3) {
              Bot_Util_AddGoal("plant",*(gentity_s **)(pgVar11 + 0x264),2,local_134,"ExplosiveType",
                               (obUserData_t *)&local_11c);
              CheckForMG42(*(gentity_s **)(pgVar11 + 0x264),local_134);
            }
          }
        }
        else if (*(int *)(pgVar13 + 4) == 0xe) {
          local_11c = 0;
          if (*(int *)(pgVar13 + 0x4f4) == 1) {
            local_118 = local_118 | 2;
          }
          else if (*(int *)(pgVar13 + 0x4f4) != 2) break;
          local_118 = local_118 | 1;
          tmp_u8 = *(uint *)(pgVar11 + 0x1a8);
          if ((tmp_u8 & 2) != 0) {
            Bot_Util_AddGoal("plant",pgVar13,2,local_138,"ExplosiveType",(obUserData_t *)&local_11c)
            ;
            tmp_u8 = *(uint *)(pgVar11 + 0x1a8);
          }
          if ((tmp_u8 & 1) != 0) {
            Bot_Util_AddGoal("plant",*(gentity_s **)(pgVar11 + 0x264),4,local_134,"ExplosiveType",
                             (obUserData_t *)&local_11c);
          }
        }
      }
    }
    else {
      local_138 = (char *)_GetEntityName(pgVar11);
      tmp_u14 = 0;
      if (local_138 == (char *)0x0) {
        tmp_u14 = *(int *)(pgVar11 + 0x218) == 0;
        if (!(bool)tmp_u14) {
          local_138 = (char *)_GetEntityName(*(int *)(pgVar11 + 0x218));
        }
      }
      tmp_i9 = 7;
      tmp_pc4 = *(char **)(tmp_i12 + 600);
      tmp_pc16 = "fakeobj";
      do {
        if (tmp_i9 == 0) break;
        tmp_i9 = tmp_i9 + -1;
        tmp_u14 = *tmp_pc4 == *tmp_pc16;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b15 * -2 + 1;
        tmp_pc16 = tmp_pc16 + (uint)tmp_b15 * -2 + 1;
      } while ((bool)tmp_u14);
      if (!(bool)tmp_u14) {
        if (tmp_i6 == 0) goto LAB_00239071;
LAB_00238f21:
        local_134 = (char *)_GetEntityName(pgVar11);
        tmp_u14 = 0;
        if (local_134 == (char *)0x0) {
          tmp_u14 = *(int *)(pgVar11 + 0x218) == 0;
          if (!(bool)tmp_u14) {
            local_134 = (char *)_GetEntityName(*(int *)(pgVar11 + 0x218));
          }
        }
        tmp_i9 = 7;
        tmp_pc4 = *(char **)(tmp_i6 + 600);
        tmp_pc16 = "fakeobj";
        do {
          if (tmp_i9 == 0) break;
          tmp_i9 = tmp_i9 + -1;
          tmp_u14 = *tmp_pc4 == *tmp_pc16;
          tmp_pc4 = tmp_pc4 + (uint)tmp_b15 * -2 + 1;
          tmp_pc16 = tmp_pc16 + (uint)tmp_b15 * -2 + 1;
        } while ((bool)tmp_u14);
        if (!(bool)tmp_u14) {
          if (tmp_i12 == 0) {
            tmp_b1 = false;
            tmp_b2 = false;
            goto LAB_0023911a;
          }
          tmp_i12 = Q_stricmp(local_138,local_134);
          if (tmp_i12 != 0) {
            tmp_b1 = true;
            tmp_b2 = true;
            goto LAB_0023908d;
          }
          tmp_u8 = 0;
          if (*(char **)(pgVar11 + 0x254) != (char *)0x0) {
            tmp_pc4 = strstr(*(char **)(pgVar11 + 0x254),"_construct");
            tmp_u8 = (uint)(tmp_pc4 != (char *)0x0);
          }
          local_11c = 3;
          local_118 = tmp_u8;
          Bot_Util_AddGoal("build",pgVar11,6,local_138,"Mobile",(obUserData_t *)&local_11c);
          tmp_b1 = true;
          tmp_b3 = true;
          tmp_b2 = true;
          goto LAB_00239191;
        }
      }
    }
    break;
  case 0xe:
    if ((*(int *)(pgVar11 + 0x5c0) == 0x2e686) && (*(float *)(pgVar11 + 0x4e8) == 5.0)) {
      tmp_pc4 = (char *)_GetEntityName(pgVar11);
      poVar17 = (obUserData_t *)0x0;
      tmp_pc16 = (char *)0x0;
      tmp_i12 = 0;
      tmp_pc5 = "explosive";
      goto LAB_00238d53;
    }
    break;
  case 0x11:
    if (*(uint8_t **)(pgVar11 + 0x5c0) == &g_unk_00042729) {
      tmp_pc5 = "checkpoint";
      poVar17 = (obUserData_t *)0x0;
      tmp_pc16 = (char *)0x0;
      tmp_i12 = 0;
      goto LAB_00238d53;
    }
    break;
  case 0x29:
    UpdateMG42(pgVar11);
    tmp_i12 = g_unk_00abe8a8;
    goto LAB_00238ad0;
  case 0x31:
    local_118 = *(uint *)(pgVar11 + 0x2d0);
    local_11c = 3;
    tmp_i12 = _GetEntityName(*(uint32_t *)(pgVar11 + 0x264));
    if (tmp_i12 == 0) {
      tmp_pc4 = (char *)_GetEntityName(pgVar11);
    }
    else {
      tmp_pc4 = (char *)_GetEntityName(*(uint32_t *)(pgVar11 + 0x264));
    }
    poVar17 = (obUserData_t *)&local_11c;
    tmp_i12 = 6;
    tmp_pc5 = "healthcab";
    tmp_pc16 = "HealRate";
    goto LAB_00238d53;
  case 0x32:
    local_118 = *(uint *)(pgVar11 + 0x2d0);
    local_11c = 3;
    tmp_i12 = _GetEntityName(*(uint32_t *)(pgVar11 + 0x264));
    if (tmp_i12 == 0) {
      tmp_pc4 = (char *)_GetEntityName(pgVar11);
    }
    else {
      tmp_pc4 = (char *)_GetEntityName(*(uint32_t *)(pgVar11 + 0x264));
    }
    poVar17 = (obUserData_t *)&local_11c;
    tmp_pc16 = "AmmoRate";
    tmp_pc5 = "ammocab";
    tmp_i12 = 6;
LAB_00238d53:
    Bot_Util_AddGoal(tmp_pc5,pgVar11,tmp_i12,tmp_pc4,tmp_pc16,poVar17);
    tmp_i12 = g_unk_00abe8a8;
LAB_00238ad0:
    tmp_i10 = tmp_i10 + 1;
    pgVar11 = pgVar11 + 0x600;
    if (tmp_i12 <= tmp_i10) goto LAB_00238c00;
    goto LAB_00238adf;
  }
  tmp_i10 = tmp_i10 + 1;
  pgVar11 = pgVar11 + 0x600;
  tmp_i12 = g_unk_00abe8a8;
  if (g_unk_00abe8a8 <= tmp_i10) goto LAB_00238c00;
  goto LAB_00238adf;
}

uint32_t ETInterface_GetEntityName(uint32_t this,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = EntityFromHandle(param_2);
  if (tmp_i1 == 0) {
    tmp_u2 = 0;
  }
  else {
    tmp_u2 = _GetEntityName(tmp_i1);
  }
  return tmp_u2;
}

ETInterface_ChangeClass(ETInterface *this,int param_1,int param_2,MessageHelper *param_3)
{
  int *tmp_pi1;
  gentity_s *pgVar2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint32_t tmp_u7;
  int tmp_i8;
  uint tmp_u9;
  int local_38;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  
  tmp_i8 = param_1 * 0x600;
  pgVar2 = (gentity_s *)(g_entities + tmp_i8);
  G_TeamCountPlayers();
  tmp_u9 = param_2 - 1;
  if (tmp_u9 < 5) {
    tmp_i4 = Bot_TeamGameToBot(*(uint32_t *)(*(int *)(g_entities + tmp_i8 + 400) + 3000));
    tmp_i3 = *(int *)(g_entities + tmp_i8 + 400);
LAB_002399a3:
    tmp_u7 = (&CSWTCH_439)[tmp_u9];
  }
  else {
    if ((param_2 == -1) ||
       (tmp_u9 = *(uint *)(*(int *)(g_entities + tmp_i8 + 400) + 0xbd8), 4 < tmp_u9)) {
      tmp_i3 = *(int *)(*(int *)(g_entities + tmp_i8 + 400) + 3000);
      if (1 < tmp_i3 - 1U) {
        tmp_i3 = TeamCount(param_1,2);
        tmp_i4 = TeamCount(param_1,1);
        tmp_i3 = (tmp_i3 <= tmp_i4) + 1;
      }
      if (g_unk_00abe93c < 1) {
LAB_00239bc0:
        tmp_u9 = 2;
      }
      else {
        tmp_i4 = 0;
        local_30 = 0;
        do {
          while ((param_1 == tmp_i4 ||
                 (tmp_i6 = (&g_unk_00abe944)[tmp_i4] * 0x54dc + level, tmp_i3 != *(int *)(tmp_i6 + 3000)))
                ) {
            tmp_i4 = tmp_i4 + 1;
            if (tmp_i4 == g_unk_00abe93c) goto LAB_002397c6;
          }
          tmp_i4 = tmp_i4 + 1;
          local_30 = local_30 + (uint)(*(int *)(tmp_i6 + 0xbd8) == 2);
        } while (tmp_i4 != g_unk_00abe93c);
LAB_002397c6:
        tmp_i4 = 0;
        local_2c = 0;
        do {
          while ((param_1 == tmp_i4 ||
                 (tmp_i6 = (&g_unk_00abe944)[tmp_i4] * 0x54dc + level, tmp_i3 != *(int *)(tmp_i6 + 3000)))
                ) {
            tmp_i4 = tmp_i4 + 1;
            if (tmp_i4 == g_unk_00abe93c) goto LAB_00239806;
          }
          tmp_i4 = tmp_i4 + 1;
          local_2c = local_2c + (uint)(*(int *)(tmp_i6 + 0xbd8) == 1);
        } while (tmp_i4 != g_unk_00abe93c);
LAB_00239806:
        tmp_i4 = 0;
        local_28 = 0;
        do {
          while ((param_1 == tmp_i4 ||
                 (tmp_i6 = (&g_unk_00abe944)[tmp_i4] * 0x54dc + level, tmp_i3 != *(int *)(tmp_i6 + 3000)))
                ) {
            tmp_i4 = tmp_i4 + 1;
            if (g_unk_00abe93c <= tmp_i4) goto LAB_00239856;
          }
          tmp_i4 = tmp_i4 + 1;
          local_28 = local_28 + (uint)(*(int *)(tmp_i6 + 0xbd8) == 3);
        } while (tmp_i4 < g_unk_00abe93c);
LAB_00239856:
        local_24 = 0;
        tmp_i4 = 0;
        do {
          while ((param_1 == tmp_i4 ||
                 (tmp_i6 = (&g_unk_00abe944)[tmp_i4] * 0x54dc + level, tmp_i3 != *(int *)(tmp_i6 + 3000)))
                ) {
            tmp_i4 = tmp_i4 + 1;
            if (g_unk_00abe93c <= tmp_i4) goto LAB_00239891;
          }
          local_24 = local_24 + (uint)(*(int *)(tmp_i6 + 0xbd8) == 0);
          tmp_i4 = tmp_i4 + 1;
        } while (tmp_i4 < g_unk_00abe93c);
LAB_00239891:
        tmp_i4 = 0;
        local_20 = 0;
        do {
          while ((param_1 == tmp_i4 ||
                 (tmp_i6 = (&g_unk_00abe944)[tmp_i4] * 0x54dc + level, tmp_i3 != *(int *)(tmp_i6 + 3000)))
                ) {
            tmp_i4 = tmp_i4 + 1;
            if (g_unk_00abe93c <= tmp_i4) goto LAB_002398de;
          }
          tmp_i4 = tmp_i4 + 1;
          local_20 = local_20 + (uint)(*(int *)(tmp_i6 + 0xbd8) == 4);
        } while (tmp_i4 < g_unk_00abe93c);
LAB_002398de:
        if (local_30 == 0) goto LAB_00239bc0;
        if (local_2c == 0) {
LAB_00239c00:
          tmp_u9 = 1;
        }
        else if (local_28 == 0) {
LAB_00239d00:
          tmp_u9 = 3;
        }
        else {
          if (local_24 != 0) {
            if (local_20 == 0) {
              tmp_u9 = 4;
              goto LAB_00239bc5;
            }
            if (local_30 == 1) goto LAB_00239bc0;
            if (local_2c == 1) goto LAB_00239c00;
            if (local_28 == 1) goto LAB_00239d00;
            if (local_24 != 1) {
              tmp_i3 = rand();
              local_38 = Bot_PlayerClassGameToBot(tmp_i3 % 5);
              goto LAB_00239cbc;
            }
          }
          tmp_u9 = 0;
        }
      }
LAB_00239bc5:
      tmp_i4 = Bot_TeamGameToBot(*(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 3000)
                               );
      tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
      goto LAB_002399a3;
    }
    local_38 = Bot_PlayerClassGameToBot(tmp_u9);
LAB_00239cbc:
    tmp_i4 = Bot_TeamGameToBot(*(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 3000));
    tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
    tmp_u9 = local_38 - 1;
    if (tmp_u9 < 5) goto LAB_002399a3;
    tmp_u7 = 0xffffffff;
  }
  *(uint32_t *)(tmp_i3 + 0xbd8) = tmp_u7;
  if ((param_3 != (MessageHelper *)0x0) && (tmp_pi1 = *(int **)(param_3 + 4), tmp_pi1 != (int *)0x0))
  {
    if (*tmp_pi1 != 0) {
      tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
      tmp_u7 = _weaponBotToGame(*tmp_pi1);
      *(uint32_t *)(tmp_i3 + 0xbdc) = tmp_u7;
    }
    if (tmp_pi1[1] != 0) {
      tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
      tmp_u7 = _weaponBotToGame(tmp_pi1[1]);
      *(uint32_t *)(tmp_i3 + 0xbe0) = tmp_u7;
    }
    tmp_i3 = G_IsWeaponDisabled(pgVar2,*(uint32_t *)
                                       (*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbdc),1,0);
    if (tmp_i3 != 0) {
      *(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbdc) = 0;
    }
    tmp_i3 = G_IsWeaponDisabled(pgVar2,*(uint32_t *)
                                       (*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbe0),1,0);
    if (tmp_i3 != 0) {
      *(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbe0) = 0;
    }
  }
  tmp_i6 = Bot_PlayerClassGameToBot
                    (*(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0xbd8));
  tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
  if ((*(int *)(tmp_i3 + 0xbdc) == 0) || (*(int *)(tmp_i3 + 0xbd8) != *(int *)(tmp_i3 + 0xbc8))) {
    tmp_i5 = _choosePriWeap(pgVar2,tmp_i6,tmp_i4);
    tmp_u7 = _weaponBotToGame(tmp_i5);
    *(uint32_t *)(tmp_i3 + 0xbdc) = tmp_u7;
    tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
    if ((*(int *)(tmp_i3 + 0xbe0) != 0) && (*(int *)(tmp_i3 + 0xbd8) == *(int *)(tmp_i3 + 0xbc8)))
    goto LAB_00239c1e;
  }
  else if (*(int *)(tmp_i3 + 0xbe0) != 0) goto LAB_00239c1e;
  tmp_i4 = _chooseSecWeap((gentity_s *)(g_entities + tmp_i8 + 400),tmp_i6,tmp_i4);
  tmp_u7 = _weaponBotToGame(tmp_i4);
  *(uint32_t *)(tmp_i3 + 0xbe0) = tmp_u7;
  tmp_i3 = *(int *)(g_entities + param_1 * 0x600 + 400);
  if (*(int *)(tmp_i3 + 0xbd8) != *(int *)(tmp_i3 + 0xbc8)) {
    if ((*(uint *)(tmp_i3 + 0xc) & 0x8000) != 0) {
      Cmd_Kill_f(pgVar2);
      return 0;
    }
    if ((*(uint *)(tmp_i3 + 0xc) & 0x4000) != 0) {
      return 0;
    }
    *(uint32_t *)(tmp_i3 + 0xf24) = 1;
    return 0;
  }
LAB_00239c1e:
  tmp_i3 = 1;
  tmp_i8 = (tmp_i8 >> 9) * -0x55555555;
  Bot_Event_ResetWeapons(tmp_i8);
  do {
    tmp_i4 = COM_BitCheck(*(int *)(g_entities + param_1 * 0x600 + 400) + 0x3d4,tmp_i3);
    if (tmp_i4 != 0) {
      tmp_u7 = Bot_WeaponGameToBot(tmp_i3);
      Bot_Event_AddWeapon(tmp_i8,tmp_u7);
    }
    tmp_i3 = tmp_i3 + 1;
  } while (tmp_i3 != 0x34);
  return 0;
}

void KeyVals_Reset(KeyVals *this)
{
  uint tmp_u1;
  KeyVals *pKVar2;
  uint tmp_u3;
  bool tmp_b4;
  
  tmp_u3 = 0x400;
  tmp_b4 = false;
  if (((uint)this & 1) == 0) {
    pKVar2 = this;
    if (((uint)this & 2) == 0) goto LAB_0023a377;
  }
  else {
    pKVar2 = this + 1;
    tmp_u3 = 0x3ff;
    tmp_b4 = true;
    *this = (KeyVals)0x0;
    if (((uint)pKVar2 & 2) == 0) goto LAB_0023a377;
    tmp_u3 = 0x3ff;
    tmp_b4 = true;
  }
  *(uint16_t *)pKVar2 = 0;
  tmp_u3 = tmp_u3 - 2;
  pKVar2 = pKVar2 + 2;
LAB_0023a377:
  tmp_u1 = 0;
  do {
    *(uint32_t *)(pKVar2 + tmp_u1) = 0;
    *(uint32_t *)(pKVar2 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < (tmp_u3 & 0xfffffff8));
  pKVar2 = pKVar2 + tmp_u1;
  if ((tmp_u3 & 4) != 0) {
    *(uint32_t *)pKVar2 = 0;
    pKVar2 = pKVar2 + 4;
  }
  if ((tmp_u3 & 2) != 0) {
    *(uint16_t *)pKVar2 = 0;
    pKVar2 = pKVar2 + 2;
  }
  if (tmp_b4) {
    *pKVar2 = (KeyVals)0x0;
  }
  pKVar2 = this + 0x400;
  tmp_u3 = 0x800;
  tmp_b4 = ((uint)pKVar2 & 1) != 0;
  if (tmp_b4) {
    this[0x400] = (KeyVals)0x0;
    pKVar2 = this + 0x401;
    tmp_u3 = 0x7ff;
  }
  if (((uint)pKVar2 & 2) != 0) {
    *(uint16_t *)pKVar2 = 0;
    tmp_u3 = tmp_u3 - 2;
    pKVar2 = pKVar2 + 2;
  }
  if (((uint)pKVar2 & 4) != 0) {
    *(uint32_t *)pKVar2 = 0;
    tmp_u3 = tmp_u3 - 4;
    pKVar2 = pKVar2 + 4;
  }
  for (tmp_u1 = tmp_u3 >> 2; tmp_u1 != 0; tmp_u1 = tmp_u1 - 1) {
    *(uint32_t *)pKVar2 = 0;
    pKVar2 = pKVar2 + 4;
  }
  if ((tmp_u3 & 2) != 0) {
    *(uint16_t *)pKVar2 = 0;
    pKVar2 = pKVar2 + 2;
  }
  if (tmp_b4) {
    *pKVar2 = (KeyVals)0x0;
  }
  pKVar2 = this + 0xc00;
  tmp_u3 = 0x200;
  tmp_b4 = ((uint)pKVar2 & 1) != 0;
  if (tmp_b4) {
    this[0xc00] = (KeyVals)0x0;
    pKVar2 = this + 0xc01;
    tmp_u3 = 0x1ff;
  }
  if (((uint)pKVar2 & 2) != 0) {
    *(uint16_t *)pKVar2 = 0;
    tmp_u3 = tmp_u3 - 2;
    pKVar2 = pKVar2 + 2;
  }
  tmp_u1 = 0;
  do {
    *(uint32_t *)(pKVar2 + tmp_u1) = 0;
    *(uint32_t *)(pKVar2 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < (tmp_u3 & 0xfffffff8));
  pKVar2 = pKVar2 + tmp_u1;
  if ((tmp_u3 & 4) != 0) {
    *(uint32_t *)pKVar2 = 0;
    pKVar2 = pKVar2 + 4;
  }
  if ((tmp_u3 & 2) != 0) {
    *(uint16_t *)pKVar2 = 0;
    pKVar2 = pKVar2 + 2;
  }
  if (tmp_b4) {
    *pKVar2 = (KeyVals)0x0;
  }
  return;
}

void KeyVals_KeyVals(KeyVals *this)
{
  KeyVals *pKVar1;
  
  pKVar1 = this + 0xc00;
  do {
    *(uint32_t *)pKVar1 = 0;
    pKVar1 = pKVar1 + 0x10;
  } while (pKVar1 != this + 0xe00);
  Reset(this);
  return;
}

uint32_t KeyVals_SetKeyVal(KeyVals *this,char *param_1,obUserData_t *param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  KeyVals *pKVar5;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  tmp_i3 = 0;
  tmp_i4 = -1;
  pKVar5 = this;
  do {
    if ((tmp_i4 == -1) && (*pKVar5 == (KeyVals)0x0)) {
      tmp_i4 = tmp_i3;
    }
    tmp_i1 = strcasecmp((char *)pKVar5,param_1);
    if (tmp_i1 == 0) goto LAB_0023a5ab;
    tmp_i3 = tmp_i3 + 1;
    pKVar5 = pKVar5 + 0x20;
  } while (tmp_i3 != 0x20);
  tmp_u2 = 0;
  if (tmp_i4 != -1) {
    Omnibot_strncpy((char *)(this + tmp_i4 * 0x20),param_1,0x1f);
    tmp_i3 = tmp_i4;
LAB_0023a5ab:
    pKVar5 = this + (tmp_i3 + 0xc0) * 0x10;
    *(uint32_t *)pKVar5 = *(uint32_t *)param_2;
    *(uint32_t *)(pKVar5 + 4) = *(uint32_t *)(param_2 + 4);
    *(uint32_t *)(pKVar5 + 8) = *(uint32_t *)(param_2 + 8);
    *(uint32_t *)(pKVar5 + 0xc) = *(uint32_t *)(param_2 + 0xc);
    tmp_u2 = CONCAT31((int3)((uint)pKVar5 >> 8),1);
  }
  return tmp_u2;
}

void KeyVals_SetInt(KeyVals *this,char *param_1,int param_2)
{
  uint32_t local_1c;
  int local_18;
  
  local_1c = 3;
  local_18 = param_2;
  SetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  return;
}

void KeyVals_SetFloat(KeyVals *this,char *param_1,float param_2)
{
  uint32_t local_1c;
  float local_18;
  
  local_1c = 4;
  local_18 = param_2;
  SetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  return;
}

void KeyVals_SetEntity(KeyVals *this,char *param_1,uint32_t param_3)
{
  uint32_t local_1c;
  uint32_t local_18;
  
  local_1c = 5;
  local_18 = param_3;
  SetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  return;
}

KeyVals_SetVector(KeyVals *this,char *param_1,float param_2,float param_3,float param_4)
{
  uint32_t local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_1c = 1;
  local_18 = param_2;
  local_14 = param_3;
  local_10 = param_4;
  SetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  return;
}

void KeyVals_SetVector(KeyVals *this,char *param_1,float *param_2)
{
  uint32_t local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_10 = param_2[2];
  local_14 = param_2[1];
  local_18 = *param_2;
  local_1c = 1;
  SetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  return;
}

uint32_t KeyVals_SetString(KeyVals *this,char *param_1,char *param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  KeyVals *pKVar3;
  uint32_t local_1c;
  KeyVals *local_18;
  uint32_t uStack_10;
  
  uStack_10 = 0x23a7d8;
  if (param_2 == (char *)0x0) {
    param_2 = "";
  }
  tmp_i1 = 0;
  pKVar3 = this + 0x400;
  do {
    if (*pKVar3 == (KeyVals)0x0) {
      Omnibot_strncpy((char *)(this + (tmp_i1 + 0x10) * 0x40),param_2,0x3f);
      local_1c = 2;
      local_18 = this + (tmp_i1 + 0x10) * 0x40;
      tmp_u2 = SetKeyVal(this,param_1,(obUserData_t *)&local_1c);
      return tmp_u2;
    }
    tmp_i1 = tmp_i1 + 1;
    pKVar3 = pKVar3 + 0x40;
  } while (tmp_i1 != 0x20);
  return 0;
}

void KeyVals_Set(KeyVals *this,char *param_1,obUserData_t *param_2)
{
  SetKeyVal(this,param_1,param_2);
  return;
}

uint32_t KeyVals_GetKeyVal(KeyVals *this,char *param_1,obUserData_t *param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  KeyVals *pKVar3;
  int tmp_i4;
  
  tmp_i4 = 0;
  pKVar3 = this;
  do {
    tmp_i2 = strcasecmp((char *)pKVar3,param_1);
    if (tmp_i2 == 0) {
      pKVar3 = this + (tmp_i4 + 0xc0) * 0x10;
      *(uint32_t *)param_2 = *(uint32_t *)pKVar3;
      *(uint32_t *)(param_2 + 4) = *(uint32_t *)(pKVar3 + 4);
      *(uint32_t *)(param_2 + 8) = *(uint32_t *)(pKVar3 + 8);
      tmp_u1 = *(uint32_t *)(pKVar3 + 0xc);
      *(uint32_t *)(param_2 + 0xc) = tmp_u1;
      return CONCAT31((int3)((uint)tmp_u1 >> 8),1);
    }
    tmp_i4 = tmp_i4 + 1;
    pKVar3 = pKVar3 + 0x20;
  } while (tmp_i4 != 0x20);
  return 0;
}

void KeyVals_GetInt(KeyVals *this,char *param_1,int *param_2)
{
  char tmp_c1;
  uint32_t local_1c;
  int local_18;
  
  local_1c = 0;
  tmp_c1 = GetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  if (tmp_c1 != '\0') {
    *param_2 = local_18;
  }
  return;
}

void KeyVals_GetFloat(KeyVals *this,char *param_1,float *param_2)
{
  char tmp_c1;
  uint32_t local_1c;
  float local_18;
  
  local_1c = 0;
  tmp_c1 = GetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  if (tmp_c1 != '\0') {
    *param_2 = local_18;
  }
  return;
}

void KeyVals_GetEntity(KeyVals *this,char *param_1,GameEntity *param_2)
{
  char tmp_c1;
  uint32_t local_1c;
  uint32_t local_18;
  
  local_1c = 0;
  tmp_c1 = GetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  if (tmp_c1 != '\0') {
    *(uint32_t *)param_2 = local_18;
  }
  return;
}

KeyVals_GetVector(KeyVals *this,char *param_1,float *param_2,float *param_3,float *param_4)
{
  char tmp_c1;
  uint32_t local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_1c = 0;
  tmp_c1 = GetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  if (tmp_c1 != '\0') {
    *param_2 = local_18;
    *param_3 = local_14;
    *param_4 = local_10;
  }
  return;
}

void KeyVals_GetVector(KeyVals *this,char *param_1,float *param_2)
{
  char tmp_c1;
  uint32_t local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_1c = 0;
  tmp_c1 = GetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  if (tmp_c1 != '\0') {
    *param_2 = local_18;
    param_2[1] = local_14;
    param_2[2] = local_10;
  }
  return;
}

void KeyVals_GetString(KeyVals *this,char *param_1,char **param_2)
{
  char tmp_c1;
  uint32_t local_1c;
  char *local_18;
  
  local_1c = 0;
  tmp_c1 = GetKeyVal(this,param_1,(obUserData_t *)&local_1c);
  if (tmp_c1 != '\0') {
    *param_2 = local_18;
  }
  return;
}

void KeyVals_GetKV(KeyVals *this,int param_1,char **param_2,obUserData_t *param_3)
{
  KeyVals *pKVar1;
  
  *param_2 = (char *)(this + param_1 * 0x20);
  pKVar1 = this + (param_1 + 0xc0) * 0x10;
  *(uint32_t *)param_3 = *(uint32_t *)pKVar1;
  *(uint32_t *)(param_3 + 4) = *(uint32_t *)(pKVar1 + 4);
  *(uint32_t *)(param_3 + 8) = *(uint32_t *)(pKVar1 + 8);
  *(uint32_t *)(param_3 + 0xc) = *(uint32_t *)(pKVar1 + 0xc);
  return;
}

void _fini(void)
{
  return;
}

