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

/* Altered 2026: Nitmod server integration. MDX math derives from the licensed
 * ETPro implementation; Nitmod-specific angles, state and hit testing are
 * recovered against qagame.mp.i386.so. This is not the original ETPro source. */
#include "q_shared.h"
#include "g_local.h"

#include "g_nitmod_mdx.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_restrictions.h"
#include "nitmod_lua_events.h"
#include "g_nitmod_hitboxdebug.h"
#include "g_nitmod_mdx_lut.h"

typedef struct {
 qhandle_t oldFrameModel, frameModel;
 int oldFrame, oldFrameTime, oldFrameSnapshotTime;
 vec3_t oldFramePos;
 int frame, frameTime;
 float yawAngle; qboolean yawing;
 float pitchAngle; qboolean pitching;
 int moveSpeed, animationNumber, oldAnimationNumber;
 animation_t *animation;
 int animationTime; float animSpeedScale;
} nitmodMdxLerpFrame_t;
typedef struct {
 nitmodMdxLerpFrame_t legsFrame, torsoFrame;
 int lerpTime, turnAfter, updateTime;
 qboolean ready;
} nitmodMdxState_t;
static nitmodMdxState_t mdx_entityStates[MAX_GENTITIES];
static struct { bg_character_t *character; qhandle_t model; } mdx_characters[MAX_CHARACTERS + 16];
static int mdx_characterCount;
static int mdx_debugCounter;
static void MDXResetHistory(void);
static nitmodMdxState_t *MDXState(gentity_t *ent) { return &mdx_entityStates[ent - g_entities]; }
static qhandle_t MDXCharacterModel(bg_character_t *character) {
 int i; for(i=0;i<mdx_characterCount;i++) if(mdx_characters[i].character==character) return mdx_characters[i].model;
 return 0;
}
static void mdx_PlayerAngles(gentity_t *,vec3_t,vec3_t,vec3_t,qboolean);

/* ******************* MDM/MDX file format, etc */
/* from http://games.theteamkillers.net/rtcw/mdx/ */
struct mdm_hdr {
	char ident[4];		/* "MDMW" */
	byte version[4];	/* uint32 */
	char filename[64];
	byte lod_bias[4];	/* vec_t */
	byte lod_scale[4];	/* vec_t */
	byte surface_count[4];	/* uint32 */
	byte surface_offset[4];	/* uint32 */
	byte tag_count[4];	/* uint32 */
	byte tag_offset[4];	/* uint32 */
	byte eof_offset[4];	/* uint32 */
};

struct mdm_tag {
	char name[64];
	byte axis[3][3][4];	/* vec_t[3][3] */
	byte attach_bone[4];	/* uint32 */
	byte offset[3][4];	/* vec_t[3] */
	byte bone_count[4];	/* uint32 */
	byte bone_offset[4];	/* uint32 */
	byte tag_size[4];	/* uint32 */
	/* bone indexes (uint32) follow */
};

struct mdx_hdr {
	char ident[4];	/* "MDXW" */
	byte version[4];	/* uint32 */
	char filename[64];
	byte frame_count[4];	/* uint32 */
	byte bone_count[4];	/* uint32 */
	byte frame_offset[4];	/* uint32 */
	byte bone_offset[4];	/* uint32 */
	byte torso_parent[4];	/* uint32 */
	byte eof_offset[4];	/* uint32 */
};

struct mdx_frame_bone {
	byte angles[3][2];	/* int16[3] */
	byte unused[2];		/* int16 */
	byte offset_angles[2][2];	/* int16[2] */
};

struct mdx_frame {
	byte mins[3][4];	/* vec_t[3] */
	byte maxs[3][4];	/* vec_t[3] */
	byte origin[3][4];	/* vec_t[3] */
	byte radius[4];		/* vec_t */
	byte parent_offset[3][4];	/* vec_t[3] */
	/* mdx_frame_bones follow */
};

struct mdx_bone {
	char name[64];
	byte parent_index[4];	/* int32 */
	byte torso_weight[4];	/* vec_t */
	byte parent_dist[4];	/* vec_t */
	byte is_tag[4];		/* uint32 */
};

struct mdx {
	struct mdx_hdr *hdr;
	void *frame; /* struct mdx_frame; struct mdx_frame_bone*bone_count; ... */
	struct mdx_bone *bone;
	int frames, bones;
};

/* ******************* Internal */

struct bone {
	char name[64];
	int parent_index;
	vec_t parent_dist;
	vec_t torso_weight;
};

struct frame_bone {
	short angles[3];	/* Orientation angle */
	short offset_angles[2];	/* Offset angle */
};

struct frame {
	vec_t radius;
	vec3_t parent_offset;
	struct frame_bone *bones;
};


struct tag {
	char name[64];
	vec3_t axis[3];
	vec3_t offset;
	int attach_bone;
};

/**************************************************************/

#define TAG_INTERNAL		(1<<30)
#define TAG_INTERNAL_MASK	(~TAG_INTERNAL)

#define INTERNTAG_TAG		(1<<29)	/* based off tag, not bone */
#define INTERNTAG_TAG_MASK	(~INTERNTAG_TAG)

typedef struct interntag_s interntag_t;
typedef struct mdm_s mdm_t;
typedef struct mdx_s mdx_t;
typedef struct hit_s hit_t;

struct interntag_s {
	struct tag tag;
	qboolean merged;	/* merge with cachetag */
	float weight;		/* weight for merge (1.0 = only first) */
	qboolean ishead;	/* use head angles (for offset) */
};

struct mdm_s {
	char path[MAX_QPATH];

	int tag_count;
	struct tag *tags;

	/* quick lookup */
	int tag_head, tag_footleft, tag_footright;
};

struct mdx_s {
	char path[MAX_QPATH];

	int bone_count;
	struct bone *bones;

	int frame_count;
	struct frame *frames;

	int torso_parent;
};


static int mdm_model_count = 0;
static mdm_t *mdm_models = NULL;

static int mdx_model_count = 0;
static mdx_t *mdx_models = NULL;



/* Space for calculated bone origins -- new calculations overwrite the previous */
static int mdx_bones_max = 0;
static vec3_t *mdx_bones = NULL;

#define INDEXTOQHANDLE(idx)		(qhandle_t)((idx)+1)
// Index may be NULL sometimes, so just default to the first model (FIXME: This is a HACK.)
#define QHANDLETOINDEX(qh)		((qh>=1)?((int)(qh) - 1):0)
#define QHANDLETOINDEX_SAFE(qh,old)	((qh>=1)?(int)(qh) - 1:QHANDLETOINDEX(old))

/**************************************************************/
/* free allocated memory */
void G_NITMOD_MDXShutdown(void)
{
	int i;

	memset(mdx_entityStates,0,sizeof(mdx_entityStates));MDXResetHistory();mdx_debugCounter=0;
	memset(mdx_characters,0,sizeof(mdx_characters));mdx_characterCount=0;
	mdx_bones_max = 0;
	free(mdx_bones);
	mdx_bones = NULL;


	for (i = 0; i < mdm_model_count; i++) {
		free(mdm_models[i].tags);
	}
	mdm_model_count = 0;
	free(mdm_models);
	mdm_models = NULL;

	for (i = 0; i < mdx_model_count; i++) {
		free(mdx_models[i].bones);
		free(mdx_models[i].frames);
	}
	mdx_model_count = 0;
	free(mdx_models);
	mdx_models = NULL;

}

/**************************************************************/
/* Utility functions */

/* VectorRotate uses the transpose; I have no idea what use it is. */
static void PointRotate(const vec3_t in, vec3_t axis[3], vec3_t out)
{
	out[0] = in[0]*axis[0][0] + in[1]*axis[1][0] + in[2]*axis[2][0];
	out[1] = in[0]*axis[0][1] + in[1]*axis[1][1] + in[2]*axis[2][1];
	out[2] = in[0]*axis[0][2] + in[1]*axis[1][2] + in[2]*axis[2][2];
}

static void MatrixTranspose(/*const*/ vec3_t in[3], vec3_t out[3])
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			out[i][j] = in[j][i];
		}
	}
}

static void MatrixWeight(/*const*/ vec3_t m[3], float weight, vec3_t mout[3])
{
	float one = 1.0 - weight;

	mout[0][0] = m[0][0]*weight + one;
	mout[0][1] = m[0][1]*weight;
	mout[0][2] = m[0][2]*weight;

	mout[1][0] = m[1][0]*weight;
	mout[1][1] = m[1][1]*weight + one;
	mout[1][2] = m[1][2]*weight;

	mout[2][0] = m[2][0]*weight;
	mout[2][1] = m[2][1]*weight;
	mout[2][2] = m[2][2]*weight + one;
}

/* The engine transforms short angles to an axis somewhat brokenly -
   it uses a LUT and has truely perplexing values */
static void AnglesToAxisBroken(const short angles[2], vec3_t matrix[3])
{
	int idx;
	float sp, sy, cp, cy;

	idx = angles[0]>>4;
	if (idx < 0) idx += 4096;
	sp = sintable[idx];
	cp = sintable[(idx + 1024) % 4096];

	idx = angles[1]>>4;
	if (idx < 0) idx += 4096;
	sy = sintable[idx];
	cy = sintable[(idx + 1024) % 4096];

	matrix[0][0] = cp*cy;
	matrix[0][1] = cp*sy;
	matrix[0][2] = -sp;
	
	matrix[1][0] = -sy;
	matrix[1][1] = cy;
	matrix[1][2] = 0;
	
	matrix[2][0] = sp*cy;
	matrix[2][1] = sp*sy;
	matrix[2][2] = cp;
}


void G_NITMOD_MDXRefEntity(gentity_t *ent, grefEntity_t *refent, int lerpTime)
{
	bg_character_t *character;
	vec3_t legsAngles, torsoAngles, headAngles;

	memset(refent, 0, sizeof(*refent));

	if (ent->s.eType == ET_PLAYER) {
		character = BG_GetCharacterForPlayerstate(&ent->client->ps);
	} else {
		character = BG_GetCharacter(BODY_TEAM(ent), BODY_CLASS(ent));
	}

	refent->hModel = MDXCharacterModel(character);
	VectorCopy(ent->r.currentOrigin, refent->origin);

	refent->frame = MDXState(ent)->legsFrame.frame;
	refent->frameModel = MDXState(ent)->legsFrame.frameModel;

	refent->oldframe = MDXState(ent)->legsFrame.oldFrame;
	refent->oldframeModel = MDXState(ent)->legsFrame.oldFrameModel;
	if (MDXState(ent)->legsFrame.frameTime == MDXState(ent)->legsFrame.oldFrameTime)
		refent->backlerp = 0.0;
	else
		refent->backlerp = 1.0 - (float)( lerpTime - MDXState(ent)->legsFrame.oldFrameTime ) / ( MDXState(ent)->legsFrame.frameTime - MDXState(ent)->legsFrame.oldFrameTime );

	refent->torsoFrame = MDXState(ent)->torsoFrame.frame;
	refent->torsoFrameModel = MDXState(ent)->torsoFrame.frameModel;

	refent->oldTorsoFrame = MDXState(ent)->torsoFrame.oldFrame;
	refent->oldTorsoFrameModel = MDXState(ent)->torsoFrame.oldFrameModel;
	if (MDXState(ent)->torsoFrame.frameTime == MDXState(ent)->torsoFrame.oldFrameTime)
		refent->torsoBacklerp = 0.0;
	else
		refent->torsoBacklerp = 1.0 - (float)( lerpTime - MDXState(ent)->torsoFrame.oldFrameTime ) / ( MDXState(ent)->torsoFrame.frameTime - MDXState(ent)->torsoFrame.oldFrameTime );

	mdx_PlayerAngles(ent, legsAngles, torsoAngles, headAngles, qfalse);
	AnglesToAxis(legsAngles, refent->axis);
	AnglesToAxis(torsoAngles, refent->torsoAxis);
	AnglesToAxis(headAngles, refent->headAxis);
}

/**************************************************************/
/* tag management */

/**************************************************************/
/* File I/O */
static int mdx_read_int(const byte *data)
{
	return (data[0]<<0) | (data[1]<<8) | (data[2]<<16) | (data[3]<<24);
}

static short mdx_read_short(const byte *data)
{
	return (data[0]<<0) | (data[1]<<8);
}

static vec_t mdx_read_vec(const byte *data)
{
	/* FIXME: depends on size of int */
	int int_val = (data[0]<<0) | (data[1]<<8) | (data[2]<<16) | (data[3]<<24);
	{ float value;memcpy(&value,&int_val,sizeof(value));return value; }
}


static int mdm_tag_lookup(const mdm_t *model, const char tagName[64])
{
	int i;
	for (i = 0; i < model->tag_count; i++) {
		if (!Q_stricmp(model->tags[i].name, tagName))
			return i;
	}
	return -1;
}

static void mdx_load(mdx_t *mdxModel, char *mem)
{
	char *ptr;
	int frame_count, bone_count;
	int frame_offset, bone_offset;
	struct mdx_hdr *hdr;
	struct mdx_bone *bones;
	char *frames;
	int i, j;

	hdr = (void*)mem;

	frame_offset = mdx_read_int(hdr->frame_offset);
	frames = (void*)(mem + frame_offset);
	frame_count = mdx_read_int(hdr->frame_count);

	bone_offset = mdx_read_int(hdr->bone_offset);
	bones = (void*)(mem + bone_offset);
	bone_count = mdx_read_int(hdr->bone_count);

	mdxModel->torso_parent = mdx_read_int(hdr->torso_parent);

	if (bone_count > mdx_bones_max) {
		free(mdx_bones);
		mdx_bones_max = bone_count;
		mdx_bones = malloc(mdx_bones_max * sizeof(*mdx_bones));
	}

	/* Load bones */
	mdxModel->bone_count = bone_count;

	free(mdxModel->bones);
	mdxModel->bones = malloc(mdxModel->bone_count * sizeof(struct bone));

	for (i = 0; i < mdxModel->bone_count; i++) {
		struct bone *bone = &mdxModel->bones[i];

		bone->parent_index = mdx_read_int(bones[i].parent_index);
		if (bone->parent_index >= i)
			G_Error(GAME_VERSION " MDX: parent_index >= index\n");

		memcpy(bone->name,bones[i].name,63);bone->name[63]=0;

		bone->parent_dist = mdx_read_vec(bones[i].parent_dist);
		bone->torso_weight = mdx_read_vec(bones[i].torso_weight);
	}

	/* Load frames */
	mdxModel->frame_count = frame_count;

	free(mdxModel->frames);
	ptr = malloc(mdxModel->frame_count * (sizeof(struct frame) + mdxModel->bone_count*sizeof(struct frame_bone)));
	mdxModel->frames = (void*)ptr;
	ptr += mdxModel->frame_count * sizeof(struct frame);

	for (i = 0; i < mdxModel->frame_count; i++) {
		struct mdx_frame *frame = (void*)(frames + i*(sizeof(struct mdx_frame) + sizeof(struct mdx_frame_bone)*bone_count));
		struct mdx_frame_bone *frame_bone = (void*)&frame[1];
		struct frame_bone *bones;

		bones = mdxModel->frames[i].bones = (void*)ptr;
		ptr += mdxModel->bone_count * sizeof(struct frame_bone);

		mdxModel->frames[i].radius = mdx_read_vec(frame->radius);
		mdxModel->frames[i].parent_offset[0] = mdx_read_vec(frame->parent_offset[0]);
		mdxModel->frames[i].parent_offset[1] = mdx_read_vec(frame->parent_offset[1]);
		mdxModel->frames[i].parent_offset[2] = mdx_read_vec(frame->parent_offset[2]);
		for (j = 0; j < mdxModel->bone_count; j++) {
			bones[j].angles[0] = mdx_read_short(frame_bone[j].angles[0]);
			bones[j].angles[1] = mdx_read_short(frame_bone[j].angles[1]);
			bones[j].angles[2] = mdx_read_short(frame_bone[j].angles[2]);
			bones[j].offset_angles[0] = mdx_read_short(frame_bone[j].offset_angles[0]);
			bones[j].offset_angles[1] = mdx_read_short(frame_bone[j].offset_angles[1]);
		}
	}
}

static void mdm_load(mdm_t *mdmModel, char *mem)
{
	struct mdm_hdr *hdr;
	struct mdm_tag *tag;
	int i, tags;

	hdr = (void*)mem;

	tags = mdx_read_int(hdr->tag_count);
	tag = (void*)(mem + mdx_read_int(hdr->tag_offset));

	free(mdmModel->tags);
	mdmModel->tag_count = tags;
	mdmModel->tags = malloc(mdmModel->tag_count * sizeof(struct tag));

	mdmModel->tag_head = mdmModel->tag_footleft = mdmModel->tag_footright = -1;


	for (i = 0; i < tags; i++) {
		int n, p;

		memcpy(mdmModel->tags[i].name,tag->name,63);mdmModel->tags[i].name[63]=0;

		// lookup
		if (!Q_stricmp(mdmModel->tags[i].name, "tag_head"))
			mdmModel->tag_head = i;
		else if (!Q_stricmp(mdmModel->tags[i].name, "tag_footleft"))
			mdmModel->tag_footleft = i;
		else if (!Q_stricmp(mdmModel->tags[i].name, "tag_footright"))
			mdmModel->tag_footright = i;

		for (n = 0; n < 3; n++)
			for (p = 0; p < 3; p++)
				mdmModel->tags[i].axis[n][p] = mdx_read_vec(tag->axis[n][p]);

		for (p = 0; p < 3; p++)
			mdmModel->tags[i].offset[p] = mdx_read_vec(tag->offset[p]);

		mdmModel->tags[i].attach_bone = mdx_read_int(tag->attach_bone);

		tag = (void*)(((char*)tag) + mdx_read_int(tag->tag_size));
	}

}


/* Validate PK3 offsets before decoding. Valid models keep the original math. */
static qboolean MDXSpan(int offset,int count,size_t stride,size_t length) {
 return offset>=0 && count>=0 && (size_t)offset<=length && (size_t)count<=(length-(size_t)offset)/stride;
}
static qboolean MDXValidate(const char *mem,int len) {
 int i,n,bones,off,size,parent;
 if(len<(int)sizeof(struct mdx_hdr)) return qfalse;
 if(!memcmp(mem,"MDXW",4)) {
  const struct mdx_hdr *h=(const void*)mem;
  bones=mdx_read_int(h->bone_count);n=mdx_read_int(h->frame_count);
  if(bones<1 || bones>128 || n<1 || mdx_read_int(h->torso_parent)<0 || mdx_read_int(h->torso_parent)>=bones) return qfalse;
  off=mdx_read_int(h->bone_offset);
  if(!MDXSpan(off,bones,sizeof(struct mdx_bone),len) || !MDXSpan(mdx_read_int(h->frame_offset),n,sizeof(struct mdx_frame)+sizeof(struct mdx_frame_bone)*bones,len)) return qfalse;
  for(i=0;i<bones;i++) {
   const struct mdx_bone *b=(const void*)(mem+off+i*sizeof(*b));parent=mdx_read_int(b->parent_index);
   if((i==0 && parent!=-1) || (i>0 && (parent<0 || parent>=i))) return qfalse;
  }
  return qtrue;
 }
 if(!memcmp(mem,"MDMW",4)) {
  const struct mdm_hdr *h=(const void*)mem;if(len<(int)sizeof(*h)) return qfalse;
  n=mdx_read_int(h->tag_count);off=mdx_read_int(h->tag_offset);if(n<1 || n>4096) return qfalse;
  for(i=0;i<n;i++) {
   const struct mdm_tag *tag;if(!MDXSpan(off,1,sizeof(*tag),len)) return qfalse;
   tag=(const void*)(mem+off);size=mdx_read_int(tag->tag_size);
   if(size<(int)sizeof(*tag) || !MDXSpan(off,1,size,len) || mdx_read_int(tag->attach_bone)<0) return qfalse;off+=size;
  }
  return qtrue;
 }
 return qfalse;
}

qhandle_t G_NITMOD_MDXRegisterModel(const char *filename)
{
	fileHandle_t fh;
	char *mem;
	int ret;
	int i;
	int len;

	for (i = 0; i < mdm_model_count; i++) {
		if (!strcmp(mdm_models[i].path, filename))
			return INDEXTOQHANDLE(i);
	}

	for (i = 0; i < mdx_model_count; i++) {
		if (!strcmp(mdx_models[i].path, filename))
			return INDEXTOQHANDLE(i);
	}

	len = trap_FS_FOpenFile(filename, &fh, FS_READ);
	if (len <= 0) {if(fh) trap_FS_FCloseFile(fh);G_Error(GAME_VERSION " MDX: File not found: %s\n", filename);return 0;}
	mem = malloc(len);
 if(!mem) {trap_FS_FCloseFile(fh);G_Error("MDX: out of memory\n");return 0;}
	trap_FS_Read(mem, len, fh);
	trap_FS_FCloseFile(fh);

	if(!MDXValidate(mem,len)) {free(mem);G_Error("MDX: invalid model %s\n",filename);return 0;}
	if (!memcmp(mem, "MDXW", 4)) {
		ret = mdx_model_count++;
		mdx_models = realloc(mdx_models, mdx_model_count * sizeof(*mdx_models));
		memset(&mdx_models[ret], 0, sizeof(mdx_models[ret]));
		Q_strncpyz(mdx_models[ret].path, filename, sizeof(mdx_models[ret].path));
		mdx_load(&mdx_models[ret], mem);
	} else if (!memcmp(mem, "MDMW", 4)) {
		ret = mdm_model_count++;
		mdm_models = realloc(mdm_models, mdm_model_count * sizeof(*mdm_models));
		memset(&mdm_models[ret], 0, sizeof(mdm_models[ret]));
		Q_strncpyz(mdm_models[ret].path, filename, sizeof(mdm_models[ret].path));
		mdm_load(&mdm_models[ret], mem);
	} else {
		ret = -1;
		G_Error(GAME_VERSION " MDX: Not a model: %s\n", filename);
	}

	free(mem);
	return INDEXTOQHANDLE(ret);
}


/**************************************************************/
/* Bone Calculations */

static void mdx_calculate_bone(
	vec3_t dest,
	const struct bone *bone,
	const struct frame_bone *frameBone
) {
	vec3_t tmp;
	vec3_t axis[3];

	tmp[1] = tmp[2] = 0;
	tmp[0] = bone->parent_dist;

	/* frame bone rotation */
	AnglesToAxisBroken(frameBone->offset_angles, axis);
	PointRotate(tmp, axis, dest);
}

static void mdx_calculate_bone_lerp(
	/*const*/ grefEntity_t *refent,
	mdx_t *frameModel,
	mdx_t *oldFrameModel,
	mdx_t *torsoFrameModel,
	mdx_t *oldTorsoFrameModel,
	int i,
	qboolean recursive
)
{
	mdx_t *oldBoneFrameModel, *boneFrameModel;
	int oldFrame, frame;
	float backlerp;

	struct bone *oldBone, *bone;
	struct frame_bone *oldFrameBone, *frameBone;

	vec3_t point, oldpoint;

	if ( frameModel->bones[i].torso_weight ) {
		boneFrameModel = torsoFrameModel;
		oldBoneFrameModel = oldTorsoFrameModel;

		frame = refent->torsoFrame;
		oldFrame = refent->oldTorsoFrame;

		backlerp = refent->torsoBacklerp;
	} else {
		boneFrameModel = frameModel;
		oldBoneFrameModel = oldFrameModel;

		frame = refent->frame;
		oldFrame = refent->oldframe;

		backlerp = refent->backlerp;
	}

	bone = &boneFrameModel->bones[i];
	oldBone = &oldBoneFrameModel->bones[i];

	if ( i == 0 ) {
		VectorMA( vec3_origin, 1.0 - backlerp, boneFrameModel->frames[frame].parent_offset, mdx_bones[i] );
		VectorMA( mdx_bones[i], backlerp, oldBoneFrameModel->frames[oldFrame].parent_offset, mdx_bones[i] );
		return; // It's offset funny if we do the calculations for the top-most bone
	} else {
		if (recursive) {
			mdx_calculate_bone_lerp(
				refent,
				frameModel, oldFrameModel,
				torsoFrameModel, oldTorsoFrameModel,
				bone->parent_index,
				qtrue
			);
		}
	}

	frameBone = &boneFrameModel->frames[frame].bones[i];
	oldFrameBone = &oldBoneFrameModel->frames[oldFrame].bones[i];

	mdx_calculate_bone(oldpoint, oldBone, oldFrameBone);
	mdx_calculate_bone(point, bone, frameBone);

	/* This frame's position */
	VectorAdd(mdx_bones[bone->parent_index], point, mdx_bones[i]);

	/* Lerp in old frame */
	VectorSubtract(oldpoint, point, oldpoint);
	VectorMA(mdx_bones[i], backlerp, oldpoint, mdx_bones[i]);
}


void mdx_calculate_bones_single(/*const*/ grefEntity_t *refent, int i)
{
	mdx_t *frameModel = &mdx_models[QHANDLETOINDEX(refent->frameModel)];
	mdx_t *oldFrameModel = &mdx_models[QHANDLETOINDEX_SAFE(refent->oldframeModel, refent->frameModel)];

	mdx_t *torsoFrameModel = &mdx_models[QHANDLETOINDEX(refent->torsoFrameModel)];
	mdx_t *oldTorsoFrameModel = &mdx_models[QHANDLETOINDEX_SAFE(refent->oldTorsoFrameModel, refent->torsoFrameModel)];

#ifdef DEBUG
	if (frameModel->bone_count != torsoFrameModel->bone_count
	 || frameModel->bone_count != oldFrameModel->bone_count
	 || frameModel->bone_count != oldTorsoFrameModel->bone_count) {
		G_Error(GAME_VERSION " MDX: Frame count mismatch\n");
	}
#endif

	mdx_calculate_bone_lerp(
		refent,
		frameModel, oldFrameModel,
		torsoFrameModel, oldTorsoFrameModel,
		i,
		qtrue
	);
}

static void mdx_bone_orientation(/*const*/ grefEntity_t *refent, int idx, vec3_t origin, vec3_t axis[3])
{
	mdx_t *frameModel = &mdx_models[QHANDLETOINDEX(refent->frameModel)];
	mdx_t *oldFrameModel = &mdx_models[QHANDLETOINDEX_SAFE(refent->oldframeModel, refent->frameModel)];

	mdx_t *torsoFrameModel = &mdx_models[QHANDLETOINDEX(refent->torsoFrameModel)];
	mdx_t *oldTorsoFrameModel = &mdx_models[QHANDLETOINDEX_SAFE(refent->oldTorsoFrameModel, refent->torsoFrameModel)];

	mdx_t *oldBoneFrameModel, *boneFrameModel;

	struct bone *oldBone, *bone;
	struct frame_bone *oldFrameBone, *frameBone;

	int oldFrame, frame;
	float backlerp;

	vec3_t realangles, angles;
	vec3_t axis1[3], tmpaxis[3];

	if ( frameModel->bones[idx].torso_weight ) {
		boneFrameModel = torsoFrameModel;
		oldBoneFrameModel = oldTorsoFrameModel;

		frame = refent->torsoFrame;
		oldFrame = refent->oldTorsoFrame;

		backlerp = refent->torsoBacklerp;
	} else {
		boneFrameModel = frameModel;
		oldBoneFrameModel = oldFrameModel;

		frame = refent->frame;
		oldFrame = refent->oldframe;

		backlerp = refent->backlerp;
	}

	bone = &boneFrameModel->bones[idx];
	oldBone = &oldBoneFrameModel->bones[idx];

	frameBone = &boneFrameModel->frames[frame].bones[idx];
	oldFrameBone = &oldBoneFrameModel->frames[oldFrame].bones[idx];

	/* Calculate origin */
	VectorCopy( mdx_bones[idx], origin );

	/* Apply torso rotation to origin */
	// FIXME: This probably isn't entirely correct; my test models fail,
	// in any case.  It seems to produce the proper results with a real
	// player model, though.
	if (bone->torso_weight) {
		vec3_t tmp, torso_origin;

		/* Rotate around torso_parent */
		VectorSubtract(origin, mdx_bones[boneFrameModel->torso_parent], tmp);
		PointRotate(tmp, refent->torsoAxis, torso_origin);
		VectorAdd(torso_origin, mdx_bones[boneFrameModel->torso_parent], torso_origin);

		/* Lerp torso-rotated point with non-rotated */
		VectorSubtract(torso_origin, origin, torso_origin);
		VectorMA(origin, bone->torso_weight, torso_origin, origin);
	}

	/* Calculate angles */
	/* bone angles */
	realangles[0] = SHORT2ANGLE(oldFrameBone->angles[0]);
	realangles[1] = SHORT2ANGLE(oldFrameBone->angles[1]);
	realangles[2] = SHORT2ANGLE(oldFrameBone->angles[2]);
	VectorScale(realangles, backlerp, angles);
	realangles[0] = SHORT2ANGLE(frameBone->angles[0]);
	realangles[1] = SHORT2ANGLE(frameBone->angles[1]);
	realangles[2] = SHORT2ANGLE(frameBone->angles[2]);
	VectorMA(angles, (1.0 - backlerp), realangles, angles);
	AnglesToAxis(angles, tmpaxis);

	// FIXME: Why is this transpose needed?
	MatrixTranspose(tmpaxis, axis1);

	/* torso angles */
	// FIXME: This probably isn't how the engine decides.
	MatrixWeight(refent->torsoAxis, bone->torso_weight, tmpaxis);
	MatrixMultiply(axis1, tmpaxis, axis);
}


/* */
static qboolean MDXValidRef(const grefEntity_t *refent);

int G_NITMOD_MDXLerpTagNumber( orientation_t *tag, /*const*/ grefEntity_t *refent, int tagNum )
{
	mdm_t *model;
	vec3_t axis[3];
	vec3_t offset;
	mdx_t *mdx;
	int bone;

	if(!MDXValidRef(refent)) return -1;
	model = &mdm_models[QHANDLETOINDEX(refent->hModel)];
	mdx = &mdx_models[QHANDLETOINDEX(refent->frameModel)];

	if (tagNum < 0 || tagNum >= model->tag_count)
		return -1;

	bone = model->tags[tagNum].attach_bone;
 if(bone<0 || bone>=mdx->bone_count) return -1;

	mdx_calculate_bones_single(refent, bone);
	mdx_bone_orientation(refent, bone, tag->origin, axis);

	PointRotate(model->tags[tagNum].offset, axis, offset);
	VectorAdd(tag->origin, offset, tag->origin);

	MatrixMultiply(model->tags[tagNum].axis, axis, tag->axis);

	return 0;
}

int G_NITMOD_MDXLookupTag(/*const*/ grefEntity_t *refent, const char *tagName)
{
	mdm_t *model;
	model = &mdm_models[QHANDLETOINDEX(refent->hModel)];
	return mdm_tag_lookup(model, tagName);
}

int G_NITMOD_MDXLerpTag( orientation_t *tag, /*const*/ grefEntity_t *refent, const char *tagName, int startIndex )
{
	int tagNum;

	if (startIndex) {
		G_Error(GAME_VERSION " MDX: Huh?  What to do, what to do... (non-zero startIndex)\n");
	}

	tagNum = G_NITMOD_MDXLookupTag(refent, tagName);

	return G_NITMOD_MDXLerpTagNumber(tag, refent, tagNum);
}

/**************************************************************/
/* Animations/Player stuff */

#define SWING_RIGHT	1
#define SWING_LEFT	2

/*
==================
mdx_SwingAngles, adapted from CG_SwingAngles
==================
*/
#define SERVER_FRAMETIME	(1000/20)
static void mdx_SwingAngles( float destination, float swingTolerance, float clampTolerance,
					float speed, float *angle, qboolean *swinging ) {
	float	swing;
	float	move;
	float	scale;

	if ( !*swinging ) {
		// see if a swing should be started
		float centerAngle;

		// zinx - use predictable center so server can match cgame easier
		centerAngle = rint(*angle / swingTolerance) * swingTolerance;

		swing = AngleSubtract( destination, *angle );
		if ( swing >= swingTolerance || swing < -swingTolerance ) {
			*swinging = qtrue;
		}
	}

	if ( !*swinging ) {
		return;
	}

	// modify the speed depending on the delta
	// so it doesn't seem so linear
	swing = AngleSubtract( destination, *angle );
	scale = fabs( swing );
	scale *= 0.05;
	if (scale < 0.5)
		scale = 0.5;

	// swing towards the destination angle
	if ( swing >= 0 ) {
		move = SERVER_FRAMETIME * scale * speed;
		if ( move >= swing ) {
			move = swing;
			*swinging = qfalse;
		} else {
			*swinging = SWING_LEFT;		// left
		}
		*angle = AngleMod( *angle + move );
	} else if ( swing < 0 ) {
		move = SERVER_FRAMETIME * scale * -speed;
		if ( move <= swing ) {
			move = swing;
			*swinging = qfalse;
		} else {
			*swinging = SWING_RIGHT;	// right
		}
		*angle = AngleMod( *angle + move );
	}

	// clamp to no more than tolerance
	swing = AngleSubtract( destination, *angle );
	if ( swing > clampTolerance ) {
		*angle = AngleMod( destination - (clampTolerance - 1) );
	} else if ( swing < -clampTolerance ) {
		*angle = AngleMod( destination + (clampTolerance - 1) );
	}
}

/*
===============
mdx_PlayerAngles, adapted from CG_PlayerAngles
===============
*/
#define SWINGSPEED	0.1	/* Cheat protected, so we don't care if it matches. */

static void mdx_PlayerAngles( gentity_t *ent, vec3_t legsAngles, vec3_t torsoAngles, vec3_t headAngles, qboolean doswing )
{
	float			dest;
	vec3_t			velocity;
	float			speed;
	float			clampTolerance;
	float			movementDir;
	bg_character_t		*character;
	int			legsSet;
	gclient_t		*client = ent->client;

	if(ent->s.eType==ET_CORPSE) {
  VectorClear(legsAngles);VectorClear(torsoAngles);VectorClear(headAngles);
  legsAngles[YAW]=torsoAngles[YAW]=headAngles[YAW]=ent->s.angles[YAW];return;
 }
 if(!client) return;
 character = BG_GetCharacterForPlayerstate( &client->ps );
	if ( !character )
		return;

	legsSet = client->ps.legsAnim & ~ANIM_TOGGLEBIT;

	if (client->ps.movementDir > 128)
		movementDir = (float)client->ps.movementDir - 256;
	else
		movementDir = client->ps.movementDir;

	VectorCopy(client->ps.viewangles, headAngles);

	headAngles[YAW] = AngleMod( headAngles[YAW] );
	VectorClear( legsAngles );
	VectorClear( torsoAngles );

	// --------- yaw -------------

	// allow yaw to drift a bit, unless these conditions don't allow them
	// rain - use clientNum instead of number, we get called for corpses.
	if( !(BG_GetConditionBitFlag( ent->s.clientNum, ANIM_COND_MOVETYPE, ANIM_MT_IDLE ) ||
		  BG_GetConditionBitFlag( ent->s.clientNum, ANIM_COND_MOVETYPE, ANIM_MT_IDLECR ) )/*
		||	 (BG_GetConditionValue( cent->currentState.clientNum, ANIM_COND_MOVETYPE, qfalse ) & ((1<<ANIM_MT_STRAFELEFT) | (1<<ANIM_MT_STRAFERIGHT)) )*/) {

		// always point all in the same direction
		MDXState(ent)->torsoFrame.yawing = qtrue;	// always center
		MDXState(ent)->torsoFrame.pitching = qtrue;	// always center
		MDXState(ent)->legsFrame.yawing = qtrue;	// always center

	// if firing, make sure torso and head are always aligned
	// rain - clientNum instead of number
	} else if( BG_GetConditionValue( ent->s.clientNum, ANIM_COND_FIRING, qtrue ) ) {
		MDXState(ent)->torsoFrame.yawing = qtrue;	// always center
		MDXState(ent)->torsoFrame.pitching = qtrue;	// always center
	}

	// adjust legs for movement dir
	if( client->ps.eFlags & EF_DEAD || client->ps.eFlags & EF_MOUNTEDTANK ) {
		// don't let dead bodies twitch
		legsAngles[YAW] = headAngles[YAW];
		torsoAngles[YAW] = headAngles[YAW];
	} else {
		legsAngles[YAW] = headAngles[YAW] + movementDir;

		if( !(client->ps.eFlags & EF_FIRING) ) {
			torsoAngles[YAW] = headAngles[YAW] + 0.35 * movementDir;
			clampTolerance = 90;
		} else {	// must be firing
			torsoAngles[YAW] = headAngles[YAW];	// always face firing direction
			//if (fabs(ent->s.angles2[YAW]) > 30)
			//	legsAngles[YAW] = headAngles[YAW];
			clampTolerance = 60;
		}

		// torso
		if (doswing) mdx_SwingAngles( torsoAngles[YAW], 25, clampTolerance, SWINGSPEED, &MDXState(ent)->torsoFrame.yawAngle, &MDXState(ent)->torsoFrame.yawing );

		// if the legs are yawing (facing heading direction), allow them to rotate a bit, so we don't keep calling
		// the legs_turn animation while an AI is firing, and therefore his angles will be randomizing according to their accuracy

		clampTolerance = 150;

		if( BG_GetConditionBitFlag( ent->s.clientNum, ANIM_COND_MOVETYPE, ANIM_MT_IDLE) ) {
			if (doswing) {
				MDXState(ent)->legsFrame.yawing = qfalse; // set it if they really need to swing
				mdx_SwingAngles( legsAngles[YAW], 20, clampTolerance, 0.5*SWINGSPEED, &MDXState(ent)->legsFrame.yawAngle, &MDXState(ent)->legsFrame.yawing );
			}
		} else if( strstr( BG_GetAnimString( character->animModelInfo, legsSet ), "strafe" ) ) {
			// FIXME: what is this strstr hack??
			// if	( BG_GetConditionValue( ci->clientNum, ANIM_COND_MOVETYPE, qfalse ) & ((1<<ANIM_MT_STRAFERIGHT)|(1<<ANIM_MT_STRAFELEFT)) ) {
			// rain - this nasty strstr hack is to apply this only to
			// strafe animations, because strafing with some weapons uses
			// a non-strafe animation (!@#%), e.g. strafing with the 
			// mobile mg42
			
			if (doswing) {
				MDXState(ent)->legsFrame.yawing = qfalse; // set it if they really need to swing
				legsAngles[YAW] = headAngles[YAW];
				mdx_SwingAngles( legsAngles[YAW], 0, clampTolerance, SWINGSPEED, &MDXState(ent)->legsFrame.yawAngle, &MDXState(ent)->legsFrame.yawing );
			}
		} else if(MDXState(ent)->legsFrame.yawing) {
			if (doswing) mdx_SwingAngles( legsAngles[YAW], 0, clampTolerance, SWINGSPEED, &MDXState(ent)->legsFrame.yawAngle, &MDXState(ent)->legsFrame.yawing );
		} else {
			if (doswing) mdx_SwingAngles( legsAngles[YAW], 40, clampTolerance, SWINGSPEED, &MDXState(ent)->legsFrame.yawAngle, &MDXState(ent)->legsFrame.yawing );
		}

		torsoAngles[YAW] = MDXState(ent)->torsoFrame.yawAngle;
		legsAngles[YAW] = MDXState(ent)->legsFrame.yawAngle;
	}

	// --------- pitch -------------

	// only show a fraction of the pitch angle in the torso
	if( headAngles[PITCH] > 180 ) {
		dest = (-360 + headAngles[PITCH]) * 0.75;
	} else {
		dest = headAngles[PITCH] * 0.75;
	}

	// rain - zero out the head pitch when dead
	if (client->ps.eFlags & EF_DEAD) {
		headAngles[PITCH] = 0;
	}
	//if (doswing) mdx_SwingAngles( dest, 15, 30, 0.1, &MDXState(ent)->torsoFrame.pitchAngle, &MDXState(ent)->torsoFrame.pitching );
	//torsoAngles[PITCH] = MDXState(ent)->torsoFrame.pitchAngle;

	if( client->ps.eFlags & EF_PRONE ) {
		torsoAngles[PITCH] = legsAngles[PITCH] - 3;
	} else if (client->ps.eFlags & EF_DEAD) {
		// rain - zero out the torso pitch when dead
		torsoAngles[PITCH] = 0;
	} else {
		if (doswing) mdx_SwingAngles( dest, 15, 30, 0.1, &MDXState(ent)->torsoFrame.pitchAngle, &MDXState(ent)->torsoFrame.pitching );
		torsoAngles[PITCH] = MDXState(ent)->torsoFrame.pitchAngle;
	}

	// --------- roll -------------

	// lean towards the direction of travel
	VectorCopy( client->ps.velocity, velocity );
	speed = VectorNormalize( velocity );
	if( speed ) {
		vec3_t	axis[3];
		float	side;

		speed *= 0.05;

		AnglesToAxis( legsAngles, axis );
		side = speed * DotProduct( velocity, axis[1] );
		legsAngles[ROLL] -= side;

		side = speed * DotProduct( velocity, axis[0] );
		legsAngles[PITCH] += side;
	}

	/* Nitmod mdx_PlayerAngles 0x39950: alternative lean scale, weapons wins. */
 if(G_NITMOD_ConfiguredWeaponFlags()&0x100) {
  torsoAngles[ROLL]+=client->ps.leanf*2.2f;headAngles[ROLL]+=client->ps.leanf;
 } else if(G_NITMOD_LegacyCvarInteger("g_misc",0)&0x20) {
  torsoAngles[ROLL]+=client->ps.leanf*1.25f;headAngles[ROLL]+=client->ps.leanf;
 }
	// FIXME: Do pain twitch?

	// pull the angles back out of the hierarchial chain
	AnglesSubtract( headAngles, torsoAngles, headAngles );
	AnglesSubtract( torsoAngles, legsAngles, torsoAngles );
}

/* Adapted from CG_RunLerpFrameRate */
/* I'd rather not duplicate this much code.... */
#define CROUCHING(anim)	( (anim) && ((anim)->movetype & ((1<<ANIM_MT_IDLECR)|(1<<ANIM_MT_WALKCR)|(1<<ANIM_MT_WALKCRBK))) )

static void mdx_SetLerpFrame(gentity_t *ent, nitmodMdxLerpFrame_t *lf, int newAnimation, bg_character_t *character)
{
	animation_t *oldAnim;
	animation_t *anim;
	int transitionMin = -1;
	qboolean firstAnim = qfalse;

	if ( !lf->animation ) {
		firstAnim = qtrue;
	}

	oldAnim = lf->animation;

	lf->animationNumber = newAnimation;
	anim = BG_GetAnimationForIndex(character->animModelInfo, lf->animationNumber & ~ANIM_TOGGLEBIT);

	lf->animation = anim;
	lf->animationTime = lf->frameTime + anim->initialLerp;

	if ( !(anim->flags & ANIMFL_FIRINGANIM) || (lf != &MDXState(ent)->torsoFrame) ) {
		if ( (lf == &MDXState(ent)->legsFrame) && (CROUCHING(oldAnim) != CROUCHING(anim)) ) {
			if ( anim->moveSpeed || ( anim->movetype & ((1<<ANIM_MT_TURNLEFT)|(1<<ANIM_MT_TURNRIGHT)) ) ) // if unknown movetype, go there faster
				transitionMin = lf->frameTime + 200;	// slowly raise/drop
			else
				transitionMin = lf->frameTime + 350;	// slowly raise/drop
		} else if ( anim->moveSpeed ) {
			transitionMin = lf->frameTime + 120;	// always do some lerping (?)
		} else	// not moving, so take your time
			transitionMin = lf->frameTime + 170;	// always do some lerping (?)

		if ( oldAnim && oldAnim->animBlend ) { //transitionMin < lf->frameTime + oldanim->animBlend) {
			transitionMin = lf->frameTime + oldAnim->animBlend;
			lf->animationTime = transitionMin;
		} else {
			// slow down transitions according to speed
			if( anim->moveSpeed && lf->animSpeedScale < 1.0 )
				lf->animationTime += anim->initialLerp;
			if( lf->animationTime < transitionMin )
				lf->animationTime = transitionMin;
		}
	}

	// if first anim, go immediately
	if ( firstAnim ) {
		lf->frameTime = level.time - 1;
		lf->animationTime = level.time - 1;
		lf->frame = anim->firstFrame;
		lf->frameModel = G_NITMOD_MDXRegisterModel(anim->mdxFileName);
		VectorCopy( ent->s.pos.trBase, lf->oldFramePos );
	}
//G_Printf("[fT%6d->%-6d] NA %d%s sT %d\n", lf->oldFrameTime, lf->frameTime, lf->animationNumber, firstAnim?" (FIRST)":"", level.time);
}

static void mdx_RunLerpFrame(gentity_t *ent, nitmodMdxLerpFrame_t *lf, int newAnimation, bg_character_t *character, int recursion)
{
	int			f;
	animation_t	*anim, *oldAnim;
	animation_t *otherAnim = NULL;
	qboolean	isLadderAnim;

	qboolean	done = qfalse;	// break out if we would loop forever

#define	ANIM_SCALEMAX_LOW	1.1
#define	ANIM_SCALEMAX_HIGH	1.6

#define	ANIM_SPEEDMAX_LOW	100
#define	ANIM_SPEEDMAX_HIGH	20

	isLadderAnim = lf->animation && (lf->animation->flags & ANIMFL_LADDERANIM);

	oldAnim = lf->animation;

	if ( newAnimation != lf->animationNumber || !lf->animation ) {
		mdx_SetLerpFrame(ent, lf, newAnimation, character);
	}

	anim = lf->animation;

	// check for forcing last frame
	if ( (ent->s.eFlags & EF_FORCE_END_FRAME) || ent->s.eType == ET_CORPSE ) {
		lf->oldFrame = lf->frame = anim->firstFrame + anim->numFrames - 1;
		lf->oldFrameModel = lf->frameModel = G_NITMOD_MDXRegisterModel(anim->mdxFileName);
		return;
	}

	// if we have passed the current frame, move it to
	// oldFrame and calculate a new frame
	while( level.time > lf->frameTime && !done ) {
		// Calculate move speed
		if (lf->oldFrameSnapshotTime < ent->s.pos.trTime) {
			// We have a new snapshot, and thus a new speed
			float	serverDelta;
		
			// calculate the speed at which we moved over the last frame
			// zinx - changed to use server position instead of lerp'd position
			if( isLadderAnim ) { // only use Z axis for speed
				lf->oldFramePos[0] = ent->s.pos.trBase[0];
				lf->oldFramePos[1] = ent->s.pos.trBase[1];
			}
			serverDelta = (float)(ent->s.pos.trTime - lf->oldFrameSnapshotTime) / 1000.0;
			lf->moveSpeed = Distance( ent->s.pos.trBase, lf->oldFramePos ) / serverDelta;

			VectorCopy( ent->s.pos.trBase, lf->oldFramePos );
			lf->oldFrameSnapshotTime = ent->s.pos.trTime;
		}
	
		// calculate speed for new frame
		if (anim->moveSpeed) {
			// convert moveSpeed to a factor of this animation's movespeed
			lf->animSpeedScale = lf->moveSpeed / (float)anim->moveSpeed;
		} else {
			// move at normal speed
			lf->animSpeedScale = 1.0;
		}

		// restrict the speed range
		if( lf->animSpeedScale < 0.25 ) {	// if it's too slow, then a really slow spped, combined with a sudden take-off, can leave them playing a really slow frame while they a moving really fast
			if (lf->animSpeedScale < 0.01 && isLadderAnim)
				lf->animSpeedScale = 0.0;
			else
				lf->animSpeedScale = 0.25;
		} else if( lf->animSpeedScale > ANIM_SCALEMAX_LOW ) {

			if( !(anim->flags & ANIMFL_LADDERANIM) ) {
				// allow slower anims to speed up more than faster anims
				if( anim->moveSpeed > ANIM_SPEEDMAX_LOW ) {
					lf->animSpeedScale = ANIM_SCALEMAX_LOW;
				} else if( anim->moveSpeed < ANIM_SPEEDMAX_HIGH ) {
					if( lf->animSpeedScale > ANIM_SCALEMAX_HIGH )
						lf->animSpeedScale = ANIM_SCALEMAX_HIGH;
				} else {
					lf->animSpeedScale = ANIM_SCALEMAX_HIGH - (ANIM_SCALEMAX_HIGH - ANIM_SCALEMAX_LOW) * (float)(anim->moveSpeed - ANIM_SPEEDMAX_HIGH) / (float)(ANIM_SPEEDMAX_LOW - ANIM_SPEEDMAX_HIGH);
				}
			} else if( lf->animSpeedScale > 4.0 ) {
				lf->animSpeedScale = 4.0;
			}

		}

		// move to new frame
		lf->oldFrame = lf->frame;
		lf->oldFrameTime = lf->frameTime;
		lf->oldFrameModel = lf->frameModel;

		if ( lf == &MDXState(ent)->legsFrame ) {
			otherAnim = MDXState(ent)->torsoFrame.animation;
		} else if ( lf == &MDXState(ent)->torsoFrame ) {
			otherAnim = MDXState(ent)->legsFrame.animation;
		}

		// get the next frame based on the animation
		if( !lf->animSpeedScale ) {
			// stopped on the ladder, so stay on the same frame
			f = lf->frame - anim->firstFrame;
			lf->frameTime += anim->frameLerp;		// don't wait too long before starting to move again
		} else if ( lf->oldAnimationNumber != lf->animationNumber &&
				  (!anim->moveSpeed || lf->oldFrame < anim->firstFrame || lf->oldFrame >= anim->firstFrame + anim->numFrames) ) {	// Ridah, added this so walking frames don't always get reset to 0, which can happen in the middle of a walking anim, which looks wierd
			lf->frameTime = lf->animationTime;		// initial lerp
			if (oldAnim && anim->moveSpeed) {	// keep locomotions going continuously
				f = (lf->frame - oldAnim->firstFrame) + 1;
				while (f < 0) {
					f += anim->numFrames;
				}
			} else {
				f = 0;
			}
		} else if ( (lf == &MDXState(ent)->legsFrame) && otherAnim && !(anim->flags & ANIMFL_FIRINGANIM) && ((lf->animationNumber & ~ANIM_TOGGLEBIT) == (MDXState(ent)->torsoFrame.animationNumber & ~ANIM_TOGGLEBIT)) && (!anim->moveSpeed) ) {
			// legs should synch with torso
			f = MDXState(ent)->torsoFrame.frame - otherAnim->firstFrame;
			if (f >= anim->numFrames || f < 0) {
				f = 0;	// wait at the start for the legs to catch up (assuming they are still in an old anim)
			}
			lf->frameTime = MDXState(ent)->torsoFrame.frameTime;
			done = qtrue;
		} else if ( (lf == &MDXState(ent)->torsoFrame) && otherAnim && !(anim->flags & ANIMFL_FIRINGANIM) && ((lf->animationNumber & ~ANIM_TOGGLEBIT) == (MDXState(ent)->legsFrame.animationNumber & ~ANIM_TOGGLEBIT)) && (otherAnim->moveSpeed) ) {
			// torso needs to sync with legs
			f = MDXState(ent)->legsFrame.frame - otherAnim->firstFrame;
			if (f >= anim->numFrames || f < 0) {
				f = 0;	// wait at the start for the legs to catch up (assuming they are still in an old anim)
			}
			lf->frameTime = MDXState(ent)->legsFrame.frameTime;
			done = qtrue;
		} else {
			lf->frameTime = lf->oldFrameTime + (int)((float)anim->frameLerp * (1.0 / lf->animSpeedScale));
			if( anim->flags & ANIMFL_REVERSED ) {
				f = (anim->numFrames - 1) - ( (lf->frame - anim->firstFrame) - 1 );
			} else {
				f = (lf->frame - anim->firstFrame) + 1;
			}
		}
		//f = ( lf->frameTime - lf->animationTime ) / anim->frameLerp;
		if ( f >= anim->numFrames ) {
			f -= anim->numFrames;
			if ( anim->loopFrames ) {
				f %= anim->loopFrames;
				f += anim->numFrames - anim->loopFrames;
			} else {
				f = anim->numFrames - 1;
				// the animation is stuck at the end, so it
				// can immediately transition to another sequence
				lf->frameTime = level.time;
				done = qtrue;
			}
		}
		if( anim->flags & ANIMFL_REVERSED ) {
			lf->frame = anim->firstFrame + anim->numFrames - 1 - f;
			lf->frameModel = G_NITMOD_MDXRegisterModel(anim->mdxFileName);
		} else {
			lf->frame = anim->firstFrame + f;
			lf->frameModel = G_NITMOD_MDXRegisterModel(anim->mdxFileName);
		}

		lf->oldAnimationNumber = lf->animationNumber;
		oldAnim = anim;
//G_Printf("[fT%6d->%-6d] NF %4d->%-4d s %1.4f sT %d\n", lf->oldFrameTime, lf->frameTime, lf->oldFrame, lf->frame, lf->animSpeedScale, level.time);
	}

	// Gordon: BIG hack, occaisionaly (VERY occaisionally), the frametime gets totally wacked
	if( lf->frameTime > level.time + 5000 ) {
		lf->frameTime = level.time;
	}
}

void G_NITMOD_MDXUpdate(gentity_t *ent)
{
	bg_character_t *character;
	vec3_t legsAngles, torsoAngles, headAngles;
	int animIndex, tempIndex;

	if (ent->s.eType == ET_PLAYER) {
		character = BG_GetCharacter(ent->client->sess.sessionTeam, ent->client->sess.playerType);
	} else {
		character = BG_GetCharacter(BODY_TEAM(ent), BODY_CLASS(ent));
	}

	if(!character || !character->animModelInfo || !MDXCharacterModel(character)) return;
 if(MDXState(ent)->ready && MDXState(ent)->updateTime==level.time) return;
 MDXState(ent)->updateTime=level.time;
 MDXState(ent)->ready=qtrue;
	animIndex = ent->s.legsAnim;

	// do the shuffle turn frames locally
	if(ent->s.eFlags & EF_SPARE0) MDXState(ent)->turnAfter=level.time+1750;
 if(MDXState(ent)->turnAfter < level.time && !(ent->s.eFlags & (EF_DEAD|EF_MOUNTEDTANK|EF_SPARE0)) && MDXState(ent)->legsFrame.yawing ) {
		tempIndex = BG_GetAnimScriptAnimation( ent->s.number, character->animModelInfo, ent->s.aiState, (MDXState(ent)->legsFrame.yawing == SWING_RIGHT ? ANIM_MT_TURNRIGHT : ANIM_MT_TURNLEFT) );
		if (tempIndex > -1) {
			animIndex = tempIndex;
		}
	}
	mdx_RunLerpFrame(ent, &MDXState(ent)->legsFrame, animIndex, character, 0);
	mdx_RunLerpFrame(ent, &MDXState(ent)->torsoFrame, ent->s.torsoAnim, character, 0);

	// swing angles
	mdx_PlayerAngles(ent, legsAngles, torsoAngles, headAngles, qtrue);
}

/**************************************************************/
/* Hit testing */


/* For new old-style hit tests; returns -center- positions, to have -centered- bbox applied. */

/* Init_Hit_ETKill 0x36d20: exact 17 records, including inactive TORSO2/BACKPACK. */
typedef struct {
 int hitType,flags,unused,tag1,tag2;
 vec3_t mins,maxs,scale,secondOffset;
 int reserved; vec3_t offset,axis[3];char name[32];
} nitmodMdxHitBox_t;
static const nitmodMdxHitBox_t mdx_hitboxes[17] = {
 {7,0,11,0,-1,{-5.0f,-4.25f,-5.0f},{5.0f,4.25f,5.0f},{10.0f,8.5f,10.0f},{1.0f,1.0f,1.0f},0,{0.5f,-0.5f,5.5f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"HEAD"},
 {7,1,11,0,4,{-3.0f,-3.0f,-3.0f},{4.0f,4.0f,3.0f},{7.0f,7.0f,6.0f},{0.0f,0.0f,15.0f},0,{0.0f,0.0f,0.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"NECK"},
 {2,0,11,2,-1,{-6.0f,-8.5f,-4.0f},{6.0f,8.5f,4.0f},{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,6.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"TORSO"},
 {2,0,11,-1,-1,{-3.75f,-7.5f,-7.0f},{3.75f,7.5f,7.0f},{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,-1.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"BACKPACK"},
 {2,0,11,4,-1,{-6.0f,-8.5f,-4.5999999f},{6.0f,8.5f,4.5999999f},{12.0f,17.0f,9.19999981f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,6.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"CHEST"},
 {6,0,11,5,13,{-5.0f,-5.0f,-9.0f},{5.0f,5.0f,9.0f},{10.0f,10.0f,18.0f},{1.0f,1.0f,1.0f},0,{0.0f,-1.0f,2.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"RIGHT THIGH"},
 {4,0,11,6,4,{-4.0f,-3.0f,-7.5f},{4.0f,3.0f,7.5f},{8.0f,6.0f,15.0f},{0.0f,-9.0f,8.0f},0,{0.0f,0.0f,0.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"RIGHTARM"},
 {4,0,11,7,6,{-3.0f,-3.0f,-8.5f},{3.0f,3.0f,8.5f},{6.0f,6.0f,17.0f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,0.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"RIGHT FOREARM"},
 {5,0,11,8,15,{-5.0f,-5.0f,-9.0f},{5.0f,5.0f,9.0f},{10.0f,10.0f,18.0f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,2.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"LEFT THIGH"},
 {3,0,11,9,4,{-4.0f,-3.0f,-7.5f},{4.0f,3.0f,7.5f},{8.0f,6.0f,15.0f},{0.0f,9.0f,8.0f},0,{0.0f,0.0f,0.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"LEFTARM"},
 {3,0,11,10,9,{-3.0f,-3.0f,-8.5f},{3.0f,3.0f,8.5f},{6.0f,6.0f,17.0f},{1.0f,1.0f,1.0f},0,{0.0f,2.0f,0.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"LEFT FOREARM"},
 {2,0,11,-1,-1,{-4.0f,-4.0f,-4.0f},{4.0f,4.0f,4.0f},{8.0f,8.0f,8.0f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,0.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"TORSO2"},
 {2,0,11,12,-1,{-7.0f,-8.5f,-6.0f},{7.0f,8.5f,6.0f},{14.0f,17.0f,12.0f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,-2.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"HIPS"},
 {6,0,11,13,14,{-5.5f,-5.0f,-8.0f},{5.5f,5.0f,8.0f},{11.0f,10.0f,16.0f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,0.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"RIGHT LEG"},
 {6,0,11,14,-1,{-7.5f,-2.5f,-3.0f},{7.5f,2.5f,3.0f},{15.0f,5.0f,6.0f},{1.0f,1.0f,1.0f},0,{0.0f,1.29999995f,-2.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"RIGHT FOOT"},
 {5,0,11,15,16,{-5.5f,-5.0f,-8.0f},{5.5f,5.0f,8.0f},{11.0f,10.0f,16.0f},{1.0f,1.0f,1.0f},0,{0.0f,0.0f,0.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"LEFT LEG"},
 {5,0,11,16,-1,{-7.5f,-2.5f,-3.0f},{7.5f,2.5f,3.0f},{15.0f,5.0f,6.0f},{1.0f,1.0f,1.0f},0,{0.0f,1.29999995f,-2.0f},{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},"LEFT FOOT"},
};
static const int mdx_hitOrder[17]={7,10,9,6,5,8,15,13,14,16,11,12,4,2,0,1,3};
static const char *mdx_tagNames[17]={"tag_head","tag_mouth","tag_torso","tag_back","tag_chest","tag_bright","tag_armright","tag_weapon","tag_bleft","tag_armleft","tag_weapon2","tag_lbelt","tag_ubelt","tag_legright","tag_footright","tag_legleft","tag_footleft"};

static qboolean MDXValidRef(const grefEntity_t *r) {
 int handles[4],frames[4],i,n;
 if(!r || r->hModel<1 || r->hModel>mdm_model_count || r->frameModel<1 || r->torsoFrameModel<1) return qfalse;
 handles[0]=r->frameModel;handles[1]=r->oldframeModel>0?r->oldframeModel:r->frameModel;
 handles[2]=r->torsoFrameModel;handles[3]=r->oldTorsoFrameModel>0?r->oldTorsoFrameModel:r->torsoFrameModel;
 frames[0]=r->frame;frames[1]=r->oldframe;frames[2]=r->torsoFrame;frames[3]=r->oldTorsoFrame;
 n=0;
 for(i=0;i<4;i++) {
  mdx_t *m;
  if(handles[i]<1 || handles[i]>mdx_model_count) return qfalse;
  m=&mdx_models[handles[i]-1];
  if(frames[i]<0 || frames[i]>=m->frame_count || (i && m->bone_count!=n)) return qfalse;
  n=m->bone_count;
 }
 return qtrue;
}
qboolean G_NITMOD_MDXRegisterCharacter(bg_character_t *character,const char *mesh) {
 qhandle_t model;int i;
 if(!character || !character->animModelInfo || !mesh || !mesh[0]) return qfalse;
 model=G_NITMOD_MDXRegisterModel(mesh);if(!model) return qfalse;
 for(i=0;i<mdx_characterCount;i++) if(mdx_characters[i].character==character) break;
 if(i==mdx_characterCount) {
  if(i>=(int)(sizeof(mdx_characters)/sizeof(mdx_characters[0]))) {G_Error("MDX: too many characters\n");return qfalse;}
  mdx_characterCount++;
 }
 mdx_characters[i].character=character;mdx_characters[i].model=model;
 for(i=0;i<character->animModelInfo->numAnimations;i++) {
  animation_t *anim=character->animModelInfo->animations[i];
  if(anim && anim->mdxFileName[0]) G_NITMOD_MDXRegisterModel(anim->mdxFileName);
 }
 return qtrue;
}
static qboolean MDXEntityRef(gentity_t *ent,grefEntity_t *ref) {
 if(!ent || ent<g_entities || ent>=g_entities+MAX_GENTITIES ||
  (ent->s.eType!=ET_PLAYER && ent->s.eType!=ET_CORPSE) || (ent->s.eType==ET_PLAYER && !ent->client)) return qfalse;
 if(!MDXState(ent)->ready) G_NITMOD_MDXUpdate(ent);
 if(!MDXState(ent)->ready) return qfalse;
 G_NITMOD_MDXRefEntity(ent,ref,MDXState(ent)->lerpTime?MDXState(ent)->lerpTime:level.time);
 return MDXValidRef(ref);
}
qboolean G_NITMOD_MDXHeadPosition(gentity_t *ent,vec3_t origin) {
 grefEntity_t ref;orientation_t tag;vec3_t temp[3],axis[3];int i;
 if(!MDXEntityRef(ent,&ref) || G_NITMOD_MDXLerpTag(&tag,&ref,"tag_head",0)<0) return qfalse;
 VectorCopy(ref.origin,origin);
 for(i=0;i<3;i++) VectorMA(origin,tag.origin[i],ref.axis[i],origin);
 MatrixMultiply(ref.headAxis,tag.axis,temp);MatrixMultiply(temp,ref.axis,axis);
 for(i=0;i<3;i++) origin[i]+=axis[0][i]*.5f+axis[2][i]*6.5f;
 return qtrue;
}
qboolean G_NITMOD_MDXLegsPosition(gentity_t *ent,vec3_t origin) {
 grefEntity_t ref;orientation_t left,right;vec3_t point;int i;
 if(!MDXEntityRef(ent,&ref) || G_NITMOD_MDXLerpTag(&left,&ref,"tag_footleft",0)<0 ||
  G_NITMOD_MDXLerpTag(&right,&ref,"tag_footright",0)<0) return qfalse;
 VectorAdd(left.origin,right.origin,point);VectorScale(point,.5f,point);VectorCopy(ref.origin,origin);
 for(i=0;i<3;i++) VectorMA(origin,point[i],ref.axis[i],origin);
 return qtrue;
}
static gentity_t *MDXDebugEvent(const vec3_t origin,int event) {
 vec3_t position;gentity_t *e;VectorCopy(origin,position);e=G_NITMOD_TempEventOriginal(position,event);return e;
}
static void MDXDebugAxes(const vec3_t origin,vec3_t axis[3],const vec3_t size,int color) {
 gentity_t *e=MDXDebugEvent(origin,size?106:105);
 VectorCopy(axis[0],e->s.origin2);VectorCopy(axis[1],e->s.angles);VectorCopy(axis[2],e->s.angles2);
 if(size) {e->s.effect1Time=(int)size[0];e->s.effect2Time=(int)size[1];e->s.effect3Time=(int)size[2];e->s.otherEntityNum=color;}
}
/* Original mdx_shot_test 0x3b6a0. Closest point in normalized oriented-box
 * space is intentional. It is not a conventional slab intersection. */
qboolean G_NITMOD_MDXShotTest(const vec3_t start,const vec3_t end,grefEntity_t *ref,int *hitType,float *fraction) {
 int order,mode=G_NITMOD_LegacyCvarInteger("g_hitboxes",0),debug=g_debugBullets.integer;
 int result=0;float best=2.f,limit=(mode&2)?.7f:(mode&32)?.5f:1.f;
 if(hitType) *hitType=0;if(fraction) *fraction=1.f;
 if(!MDXValidRef(ref)) return qfalse;
 for(order=0;order<17;order++) {
  int index=(mode&8)?mdx_hitOrder[order]:order,i;
  const nitmodMdxHitBox_t *box=&mdx_hitboxes[index];orientation_t tag;
  vec3_t origin,other,axis[3],tmp[3],point,unstart,unend,delta;float t;
  if(box->tag1<0 || G_NITMOD_MDXLerpTag(&tag,ref,mdx_tagNames[box->tag1],0)<0) continue;
  MatrixMultiply(tag.axis,ref->axis,axis);VectorCopy(ref->origin,origin);
  for(i=0;i<3;i++) VectorMA(origin,tag.origin[i],ref->axis[i],origin);
  if(box->tag2>=0) {
   if(G_NITMOD_MDXLerpTag(&tag,ref,mdx_tagNames[box->tag2],0)<0) continue;
   MatrixMultiply(tag.axis,ref->axis,tmp);VectorCopy(ref->origin,other);
   for(i=0;i<3;i++) VectorMA(other,tag.origin[i],ref->axis[i],other);
   for(i=0;i<3;i++) VectorMA(other,box->secondOffset[i],tmp[i],other);
   if(debug&0x100) MDXDebugAxes(other,tmp,NULL,0);
   VectorSubtract(other,origin,axis[2]);VectorNormalize(axis[2]);
   CrossProduct(axis[2],axis[0],axis[1]);VectorNormalize(axis[1]);CrossProduct(axis[2],axis[1],axis[0]);
   VectorAdd(origin,other,origin);VectorScale(origin,.5f,origin);
  }
  if(box->hitType==7) {MatrixMultiply(ref->headAxis,axis,tmp);AxisCopy(tmp,axis);}
  for(i=0;i<3;i++) VectorMA(origin,box->offset[i],axis[i],origin);
  {vec3_t localAxis[3];memcpy(localAxis,box->axis,sizeof(localAxis));MatrixMultiply(localAxis,axis,tmp);AxisCopy(tmp,axis);}
  if(debug&0x200) MDXDebugAxes(origin,axis,box->scale,order<14?order+1:order-14);
  VectorSubtract(start,origin,point);
  for(i=0;i<3;i++) unstart[i]=DotProduct(point,axis[i])/box->scale[i];
  VectorSubtract(end,origin,point);
  for(i=0;i<3;i++) unend[i]=DotProduct(point,axis[i])/box->scale[i];
  VectorSubtract(unend,unstart,delta);
  t=((-unstart[1]*delta[1]-unstart[0]*delta[0])-unstart[2]*delta[2]) /
    (delta[2]*delta[2]+delta[1]*delta[1]+delta[0]*delta[0]);
  if(!(t>=0.f)) continue; /* Includes original unordered/NaN behavior. */
  if(t<1.f) VectorMA(unstart,t,delta,point);else {t=1.f;VectorCopy(unend,point);}
  if(debug&0x80) {
   gentity_t *e=MDXDebugEvent(origin,104);VectorCopy(origin,e->s.origin2);VectorSet(e->s.angles2,1,1,1);
   VectorSubtract(end,start,other);VectorMA(start,t,other,e->s.pos.trBase);
  }
  if(Q_fabs(point[0])<=limit && Q_fabs(point[1])<=limit && Q_fabs(point[2])<=limit) {
   if(debug&0x400) MDXDebugAxes(origin,axis,box->scale,15);
   if(t<best) {best=t;result=box->hitType;}
  }
 }
 if(hitType) *hitType=result;if(fraction) *fraction=best>1.f?1.f:best;
 return result!=0;
}
int G_NITMOD_MDXHitPlayer(gentity_t *target,const vec3_t start,const vec3_t end,int *region,float *fraction) {
 grefEntity_t ref;int type;
 if(!target || !target->client) return -1;
 /* Trace_HitsPlayer 0x44000: original ps+0x154 = PW_INVULNERABLE. */
 if((G_NITMOD_LegacyCvarInteger("g_hitboxes",0)&16) && target->client->ps.powerups[PW_INVULNERABLE]) {
  if(region) *region=HR_BODY;return target-g_entities;
 }
 if(!MDXEntityRef(target,&ref) || !G_NITMOD_MDXShotTest(start,end,&ref,&type,fraction)) return -1;
 if(region) *region=type==7?HR_HEAD:(type==3 || type==4)?HR_ARMS:(type==5 || type==6)?HR_LEGS:HR_BODY;
 return target-g_entities;
}
/* Historical frames follow the nearest snapshot; viewangles interpolate.
 * G_AdjustSingleClientPosition copies both lerp records and ps flags/height. */
typedef struct {
 nitmodMdxState_t state;vec3_t viewangles;int eFlags,pmFlags,viewheight,time; qboolean valid;
} nitmodMdxMarker_t;
static nitmodMdxMarker_t mdx_markers[MAX_CLIENTS][MAX_CLIENT_MARKERS],mdx_backups[MAX_CLIENTS];
static void MDXCapture(gentity_t *ent,nitmodMdxMarker_t *m) {
 m->state=*MDXState(ent);VectorCopy(ent->client->ps.viewangles,m->viewangles);
 m->eFlags=ent->client->ps.eFlags;m->pmFlags=ent->client->ps.pm_flags;m->viewheight=ent->client->ps.viewheight;
 m->time=level.time;m->valid=qtrue;
}
void G_NITMOD_MDXReset(gentity_t *ent) {
 int n;if(!ent || ent<g_entities || ent>=g_entities+MAX_GENTITIES) return;n=ent-g_entities;
 memset(&mdx_entityStates[n],0,sizeof(mdx_entityStates[n]));
 if(n<MAX_CLIENTS) {memset(mdx_markers[n],0,sizeof(mdx_markers[n]));memset(&mdx_backups[n],0,sizeof(mdx_backups[n]));}
}
void G_NITMOD_MDXCopy(gentity_t *dst,gentity_t *src) {
 if(!dst || !src) return;*MDXState(dst)=*MDXState(src);MDXState(dst)->updateTime=-1;MDXState(dst)->lerpTime=0;
}
void G_NITMOD_MDXStoreMarker(gentity_t *ent,int marker) {
 nitmodMdxMarker_t *m;if(!ent || !ent->client || ent-g_entities>=MAX_CLIENTS || marker<0 || marker>=MAX_CLIENT_MARKERS) return;
 m=&mdx_markers[ent-g_entities][marker];MDXCapture(ent,m);m->time=ent->client->clientMarkers[marker].time;
}
/* Original G_ResetMarkers 0x45768 clears only the saved mount flag. */
void G_NITMOD_MDXInitializeMarker(gentity_t *ent,int marker) {
 if(!ent || !ent->client || ent<g_entities || ent>=g_entities+MAX_CLIENTS || marker<0 || marker>=MAX_CLIENT_MARKERS) return;
 G_NITMOD_MDXStoreMarker(ent,marker);
 mdx_markers[ent-g_entities][marker].eFlags &= ~EF_MOUNTEDTANK;
}
/* Original G_ResetMarkers ends with entity+0x5a8 = 0 (0x45a43). */
void G_NITMOD_MDXFinishMarkerReset(gentity_t *ent) {
 if(!ent || ent<g_entities || ent>=g_entities+MAX_CLIENTS || !ent->client) return;
 MDXState(ent)->lerpTime=0;
}
void G_NITMOD_MDXRewind(gentity_t *ent,int older,int newer,int time) {
 int n=ent-g_entities,i;nitmodMdxMarker_t *a,*b,*chosen;float frac;
 if(n<0 || n>=MAX_CLIENTS || !ent->client || older<0 || newer<0 || older>=MAX_CLIENT_MARKERS || newer>=MAX_CLIENT_MARKERS) return;
 a=&mdx_markers[n][older];b=&mdx_markers[n][newer];if(!a->valid || !b->valid) return;
 if(!mdx_backups[n].valid || mdx_backups[n].time!=level.time) MDXCapture(ent,&mdx_backups[n]);
 frac=a->time==b->time?0.f:(float)(time-a->time)/(b->time-a->time);
 chosen=(b->time-time < time-a->time)?b:a;
 *MDXState(ent)=chosen->state;MDXState(ent)->lerpTime=chosen->time;
 for(i=0;i<3;i++) ent->client->ps.viewangles[i]=LerpAngle(a->viewangles[i],b->viewangles[i],frac);
 ent->client->ps.eFlags=chosen->eFlags;ent->client->ps.pm_flags=chosen->pmFlags;ent->client->ps.viewheight=chosen->viewheight;
}
/* Original G_Damage 0x6a0e9 and ReviveEntity 0xf280e also latch
 * helmet loss in the antilag backup, so restoring a trace cannot undo it. */
void G_NITMOD_MDXLoseHelmet(gentity_t *ent) {
 int n=ent-g_entities;
 if(n<0 || n>=MAX_CLIENTS || !ent->client) return;
 mdx_backups[n].eFlags |= EF_HEADSHOT;
}
void G_NITMOD_MDXRestore(gentity_t *ent) {
 int n=ent-g_entities;nitmodMdxMarker_t *m;
 if(n<0 || n>=MAX_CLIENTS || !ent->client) return;m=&mdx_backups[n];
 if(!m->valid || m->time!=level.time) return;
 *MDXState(ent)=m->state;MDXState(ent)->lerpTime=0;VectorCopy(m->viewangles,ent->client->ps.viewangles);
 ent->client->ps.eFlags=m->eFlags;ent->client->ps.pm_flags=m->pmFlags;ent->client->ps.viewheight=m->viewheight;m->valid=qfalse;
}
void G_NITMOD_MDXDrawPlayer(gentity_t *ent) {
 grefEntity_t ref;int hit;
 if(mdx_debugCounter!=5) {mdx_debugCounter++;return;}mdx_debugCounter=0;
 if(MDXEntityRef(ent,&ref)) G_NITMOD_MDXShotTest(vec3_origin,vec3_origin,&ref,&hit,NULL);
}

static void MDXResetHistory(void) {
 memset(mdx_markers,0,sizeof(mdx_markers));memset(mdx_backups,0,sizeof(mdx_backups));
}
/* Original ClipLine/LineAABBIntersection keeps IEEE divide-by-zero and
 * unordered comparisons at an exactly parallel face. This only rejects
 * broad-phase candidates; the actual hit is always the MDX tag test. */
static qboolean MDXLineBox(const vec3_t origin,const vec3_t mins,const vec3_t maxs,
 const vec3_t start,const vec3_t end,float *fraction) {
 float enter=0.f,leave=1.f;int i;
 for(i=0;i<3;i++) {
  float a=(origin[i]+mins[i]-start[i])/(end[i]-start[i]);
  float b=(origin[i]+maxs[i]-start[i])/(end[i]-start[i]);
  float low=b,high=a;
  if(a<=b) {low=a;high=b;}
  if(!(enter<=high && low<=leave)) return qfalse;
  if(enter<=low) enter=low;
  if(leave<high) high=leave;
  leave=high;if(!(enter<=leave)) return qfalse;
 }
 *fraction=enter;return qtrue;
}
/* G_TraceNew 0x46250 and TracePlayers 0x1f0ff0. World collision bounds
 * the MDX segment; original retains the world trace fraction/endpos and
 * only changes entityNum plus the one-unit endpos adjustment. */
int G_NITMOD_MDXTraceBullets(gentity_t *source,trace_t *trace,trace_t *water,
 const vec3_t start,const vec3_t end) {
 int i,winner=-1,region=-2,mode=G_NITMOD_LegacyCvarInteger("g_hitboxes",0);float best=2.f;
 trap_EngineerTrace(trace,start,NULL,NULL,end,ENTITYNUM_NONE,MASK_SHOT);
 trap_EngineerTrace(water,start,NULL,NULL,end,ENTITYNUM_NONE,MASK_SHOT|MASK_WATER);
 for(i=0;i<level.numConnectedClients;i++) {
  int id=level.sortedClients[i],part=-1,flags;gentity_t *target;vec3_t mins,maxs;float fraction=2.f;
  if(id<0 || id>=MAX_CLIENTS) continue;target=&g_entities[id];
  if(!target->inuse || !target->client || target==source || target->client->sess.sessionTeam==TEAM_SPECTATOR ||
   !target->r.linked || (target->client->ps.pm_flags&PMF_LIMBO) ||
   (target->client->ps.pm_type!=PM_NORMAL && target->client->ps.pm_type!=PM_DEAD)) continue;
  flags=target->client->ps.eFlags;
  if(flags&(EF_DEAD|EF_PRONE|EF_SPARE0)) {VectorSet(mins,-36,-36,-24);VectorSet(maxs,36,36,10);}
  else if(flags&EF_CROUCHING) {VectorSet(mins,-26,-26,-24);VectorSet(maxs,26,26,48);}
  else if((mode&16) && target->client->ps.powerups[PW_INVULNERABLE]) {VectorCopy(target->r.mins,mins);VectorCopy(target->r.maxs,maxs);}
  else {VectorSet(mins,-28,-28,-24);VectorSet(maxs,28,28,48);}
  if(g_antilag.integer&2) G_NITMOD_DrawHistoricalHitbox(target);
  if(MDXLineBox(target->r.currentOrigin,mins,maxs,start,trace->endpos,&fraction) &&
   G_NITMOD_MDXHitPlayer(target,start,trace->endpos,&part,&fraction)>=0 && fraction<best) {
   best=fraction;winner=id;region=part;
  }
 }
 if(winner>=0 && winner!=trace->entityNum) {
  vec3_t direction;VectorSubtract(end,start,direction);VectorNormalizeFast(direction);
  VectorMA(trace->endpos,-1,direction,trace->endpos);trace->entityNum=winner;
 }
 source->nitmodLastTraceRegion=region;
 return region;
}
/* Scoped damage context avoids stale hit regions leaking to explosions or
 * a later shot. G_Damage receives the same four regions as original +0x5ec. */
static struct {gentity_t *attacker,*target;int region;} mdx_damage;
void G_NITMOD_MDXBeginDamage(gentity_t *attacker,gentity_t *target,int region) {
 mdx_damage.attacker=attacker;mdx_damage.target=target;mdx_damage.region=region;
}
void G_NITMOD_MDXEndDamage(void) {memset(&mdx_damage,0,sizeof(mdx_damage));}
int G_NITMOD_MDXDamageRegion(gentity_t *attacker,gentity_t *target) {
 int region;
 if(mdx_damage.attacker!=attacker || mdx_damage.target!=target) return -1;
 region=mdx_damage.region;G_NITMOD_MDXEndDamage();return region;
}
