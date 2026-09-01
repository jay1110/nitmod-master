#ifndef NITMOD_RUNTIME_H
#define NITMOD_RUNTIME_H

/* ELF/C++ runtime leftovers from the .so */

#include "nitmod_types.h"
#include "nitmod_globals.h"

int _init(EVP_PKEY_CTX *ctx);
void std_ostream_operator(ostream *this,int param_1);
void std_ios_base_dtor_ios_base(ios_base *this);
void std_iostream_dtor_iostream(iostream *this);
void std::stringstream::dtor_stringstream(stringstream *this);
void std_locale_dtor_locale(locale *this);
ostream * std_ostream_insert(ostream *param_1,char *param_2,int param_3);
uint32_t std_string_Rep_M_dispose(allocator *param_1);
void _GLOBAL__sub_I_vectors_cpp(void);
void _GLOBAL__sub_I_HitDetect_cpp(void);
void _GLOBAL__sub_I_g_etbot_interface_cpp(void);
void _GLOBAL__sub_I_BotLoadLibrary_cpp(void);
void deregister_tm_clones(void);
void register_tm_clones(void);
void __do_global_dtors_aux(void);
void frame_dummy(void);
void Vector_Vector(Vector *this,Point *param_1);
long double Vector_Length(Vector *this);
char std_ctype_char_do_widen(ctype<char> *this,char param_1);
uint32_t IEngineInterface_DebugLine(float *param_1,float *param_2,obColor *param_3,float param_4);
uint32_t IEngineInterface_DebugBox(float *param_1,float *param_2,obColor *param_3,float param_4);
IEngineInterface_DebugRadius(float *param_1,float param_2,obColor *param_3,float param_4);
IEngineInterface_PrintScreenText(float *param_1,float param_2,obColor *param_3,char *param_4);
uint32_t ETInterface_DebugLine(float *param_1,float *param_2,obColor *param_3,float param_4);
uint32_t ETInterface_DebugRadius(float *param_1,float param_2,obColor *param_3,float param_4);
uint32_t ETInterface_GetEntityPowerups(void);
uint32_t ETInterface_GetGameTime(void);
uint8_t * ETInterface_GetMapName(void);
char * ETInterface_GetGameName(void);
char * ETInterface_GetModName(void);
uint8_t * ETInterface_GetModVers(void);
void ETInterface_dtor_ETInterface(ETInterface *this);
void ETInterface_PrintMessage(ETInterface *this,char *param_1);
void ETInterface_PrintError(ETInterface *this,char *param_1);
void ETInterface_dtor_ETInterface(ETInterface *this);
void ETInterface_GetLogPath(void);
void ETInterface_GetBotPath(void);
int ETInterface_GetAutoNavFeatures(AutoNavFeature_t *param_1,int param_2);
void ETInterface_BotCommand(ETInterface *this,int param_1,char *param_2);
bool ETInterface_IsInPVS(ETInterface *this,float *param_1,float *param_2);
void ETInterface_UpdateBotInput(ETInterface *this,int param_1,ClientInput *param_2);
void ETInterface_GetMapExtents(ETInterface *this,AABB_t *param_1);
int ETInterface_AddBot(ETInterface *this,MessageHelper *param_1);
void ETInterface_RemoveBot(ETInterface *this,MessageHelper *param_1);
bool ETInterface_DoesEntityStillExist(ETInterface *this,GameEntity *param_1);
int ETInterface_IDFromEntity(uint32_t this,uint32_t param_2);
ETInterface_GetEntityLocalAABB(uint32_t this,uint32_t param_2,float *param_3);
ETInterface_GetEntityPosition(uint32_t this,uint32_t param_2,float *param_3);
ETInterface_GetEntityVelocity(uint32_t this,uint32_t param_2,float *param_3);
ETInterface_GetEntityCategory(uint32_t this,uint32_t param_2,uint *param_3);
ETInterface_GetEntityEyePosition(ETInterface *this,uint32_t param_2,float *param_3);
ETInterface_GetEntityWorldAABB(ETInterface *this,uint32_t param_2,float *param_3);
char * ETInterface_EntityByName(char *param_1);
int ETInterface_EntityFromID(int param_1);
gentity_s * ETInterface_GetEntityOwner(gentity_s *param_1,uint32_t param_2,uint32_t param_3);
ETInterface_GetEntityGroundEntity(uint32_t this,uint32_t param_2,uint32_t *param_3);
gentity_s * ETInterface_GetLocalGameEntity(void);
uint32_t ETInterface_GetEntityTeam(uint32_t this,uint32_t param_2);
ETInterface_ChangeTeam(ETInterface *this,int param_1,int param_2,MessageHelper *param_3);
void ETInterface_GetPlayerInfo(ETInterface *this,obPlayerInfo *param_1);
int ETInterface_GetEntityClass(uint32_t this,uint32_t param_2);
ETInterface_InterfaceSendMessage(ETInterface *this,int *param_1,uint32_t param_3);
uint32_t ETInterface_GetEntityFlags(uint32_t this,uint32_t param_2,uint *param_3);
void ETInterface_GetPointContents(ETInterface *this,float *param_1);
void ETInterface_GetGoals(void);
uint32_t ETInterface_GetEntityName(uint32_t this,uint32_t param_2);
ETInterface_ChangeClass(ETInterface *this,int param_1,int param_2,MessageHelper *param_3);
void KeyVals_Reset(KeyVals *this);
void KeyVals_KeyVals(KeyVals *this);
uint32_t KeyVals_SetKeyVal(KeyVals *this,char *param_1,obUserData_t *param_2);
void KeyVals_SetInt(KeyVals *this,char *param_1,int param_2);
void KeyVals_SetFloat(KeyVals *this,char *param_1,float param_2);
void KeyVals_SetEntity(KeyVals *this,char *param_1,uint32_t param_3);
KeyVals_SetVector(KeyVals *this,char *param_1,float param_2,float param_3,float param_4);
void KeyVals_SetVector(KeyVals *this,char *param_1,float *param_2);
uint32_t KeyVals_SetString(KeyVals *this,char *param_1,char *param_2);
void KeyVals_Set(KeyVals *this,char *param_1,obUserData_t *param_2);
uint32_t KeyVals_GetKeyVal(KeyVals *this,char *param_1,obUserData_t *param_2);
void KeyVals_GetInt(KeyVals *this,char *param_1,int *param_2);
void KeyVals_GetFloat(KeyVals *this,char *param_1,float *param_2);
void KeyVals_GetEntity(KeyVals *this,char *param_1,GameEntity *param_2);
KeyVals_GetVector(KeyVals *this,char *param_1,float *param_2,float *param_3,float *param_4);
void KeyVals_GetVector(KeyVals *this,char *param_1,float *param_2);
void KeyVals_GetString(KeyVals *this,char *param_1,char **param_2);
void KeyVals_GetKV(KeyVals *this,int param_1,char **param_2,obUserData_t *param_3);
void _fini(void);

#endif

