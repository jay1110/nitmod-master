#ifndef CGAME_SOUND_H
#define CGAME_SOUND_H

/* Sound registration and playback */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void CG_PlayCinematic(uint32_t param_1,float param_2,float param_3,float param_4,float param_5);
void CG_PlayPMItemSound(int param_1);
void CG_PlayVoiceChat(int *param_1);
void CG_PlayBufferedVoiceChats(void);
void CG_SoundLoadSoundFiles(void);
int CG_SoundScriptPrecache(char *param_1);
uint32_t CG_SoundPickOldestRandomSound(int param_1,uint32_t param_2,uint32_t param_3);
uint32_t CG_SoundPlaySoundScript(char *param_1,uint32_t param_2,uint32_t param_3,int param_4);
void CG_SoundPlayIndexedScript(int param_1);
void CG_SoundInit(void);
void CG_PlaySwitchSound(int param_1,int param_2);

#endif

