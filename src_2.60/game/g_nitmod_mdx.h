/* 

	Copyright (C) 2003-2005 Christopher Lais (aka "Zinx Verituse")
	and is covered by the following license:

	***
	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. Modified source for this software, as used in any binaries you have
	distributed, must be provided on request, free of charge and/or penalty.

	4. This notice may not be removed or altered from any source distribution.
	***

*/

/* Altered Nitmod server adaptation; see g_nitmod_mdx.c. */
#ifndef G_NITMOD_MDX_H
#define G_NITMOD_MDX_H
/* Server-only render entity: original 32-bit layout is 176 bytes. */
typedef struct {
 qhandle_t hModel;
 vec3_t headAxis[3],axis[3],torsoAxis[3],origin;
 int frame; qhandle_t frameModel;
 int torsoFrame; qhandle_t torsoFrameModel;
 vec3_t oldorigin; int oldframe; qhandle_t oldframeModel;
 int oldTorsoFrame; qhandle_t oldTorsoFrameModel;
 float backlerp,torsoBacklerp;
} grefEntity_t;
qhandle_t G_NITMOD_MDXRegisterModel(const char *filename);
qboolean G_NITMOD_MDXRegisterCharacter(bg_character_t *character,const char *mesh);
void G_NITMOD_MDXShutdown(void);
void G_NITMOD_MDXReset(gentity_t *ent);
void G_NITMOD_MDXUpdate(gentity_t *ent);
void G_NITMOD_MDXCopy(gentity_t *destination,gentity_t *source);
void G_NITMOD_MDXRefEntity(gentity_t *ent,grefEntity_t *refent,int lerpTime);
int G_NITMOD_MDXLerpTagNumber(orientation_t *tag,grefEntity_t *refent,int tagNum);
int G_NITMOD_MDXLookupTag(grefEntity_t *refent,const char *tagName);
int G_NITMOD_MDXLerpTag(orientation_t *tag,grefEntity_t *refent,const char *tagName,int startIndex);
qboolean G_NITMOD_MDXHeadPosition(gentity_t *ent,vec3_t origin);
qboolean G_NITMOD_MDXLegsPosition(gentity_t *ent,vec3_t origin);
qboolean G_NITMOD_MDXShotTest(const vec3_t start,const vec3_t end,grefEntity_t *refent,int *hitType,float *fraction);
int G_NITMOD_MDXHitPlayer(gentity_t *target,const vec3_t start,const vec3_t end,int *region,float *fraction);
void G_NITMOD_MDXFinishMarkerReset(gentity_t *ent);
void G_NITMOD_MDXInitializeMarker(gentity_t *ent,int marker);
void G_NITMOD_MDXStoreMarker(gentity_t *ent,int marker);
void G_NITMOD_MDXRewind(gentity_t *ent,int older,int newer,int time);
void G_NITMOD_MDXRestore(gentity_t *ent);
void G_NITMOD_MDXLoseHelmet(gentity_t *ent);
void G_NITMOD_MDXDrawPlayer(gentity_t *ent);
int G_NITMOD_MDXTraceBullets(gentity_t *source,trace_t *trace,trace_t *water,const vec3_t start,const vec3_t end);
void G_NITMOD_MDXBeginDamage(gentity_t *attacker,gentity_t *target,int region);
void G_NITMOD_MDXEndDamage(void);
int G_NITMOD_MDXDamageRegion(gentity_t *attacker,gentity_t *target);
#endif
