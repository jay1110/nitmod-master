#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_animation.h"
#include <limits.h>

static int CorpseTime(double time) {
    if(time >= INT_MAX) return INT_MAX;
    if(time <= INT_MIN) return INT_MIN;
    return (int)time;
}

/* Original CG_SetLerpFrameAnimationRateCorpse / CG_RunLerpFrameRateCorpse.
 * effect1Time is the death-animation end time, not the corpse lifetime. */
qboolean CG_NitmodCorpseAnimation(centity_t *cent, lerpFrame_t *lf, int number) {
    bg_character_t *character;
    animModelInfo_t *model;
    animation_t *anim;
    int index = number & ~ANIM_TOGGLEBIT, offset;
    double remaining, elapsed;
    if(!cent || !lf || cent->currentState.eType != ET_CORPSE || !NITMOD_UsesOriginalProtocol()) return qfalse;
    character = CG_CharacterForClientinfo(NULL, cent);
    model = character ? character->animModelInfo : NULL;
    if(!model || model->numAnimations < 1 || model->numAnimations > MAX_MODEL_ANIMATIONS ||
       index < 0 || index >= model->numAnimations || !(anim = model->animations[index]) ||
       anim->numFrames <= 0 || anim->firstFrame < 0 || anim->firstFrame > INT_MAX - anim->numFrames ||
       anim->frameLerp <= 0 || anim->duration < 0 || anim->loopFrames < 0 || anim->loopFrames > anim->numFrames) {
        lf->animation = NULL;
        lf->oldFrame = lf->frame = lf->oldFrameModel = lf->frameModel = 0;
        lf->backlerp = 0;
        return qtrue;
    }
    if(lf->animationNumber != number || lf->animation != anim) {
        lf->animationNumber = number; lf->animation = anim;
        remaining = (double)cent->currentState.effect1Time - cg.time;
        if(remaining < 0) remaining = 0;
        if(remaining > anim->duration) remaining = anim->duration;
        offset = (int)((anim->duration - remaining) / anim->frameLerp);
        /* Do not expose an out-of-range oldframe when joining late. */
        if(offset >= anim->numFrames) offset = anim->numFrames - 1;
        lf->frame = anim->firstFrame + offset;
        lf->frameTime = CorpseTime((double)cg.time - 1);
        lf->animationTime = CorpseTime((double)cg.time + remaining - anim->duration);
        lf->frameModel = anim->mdxFile;
        if(cg_debugAnim.integer) CG_Printf("Anim: %i, %.*s\n", index, MAX_QPATH, anim->name);
    }
    if(cent->currentState.effect1Time < cg.time) {
        lf->oldFrame = lf->frame = anim->firstFrame + anim->numFrames - 1;
        lf->oldFrameModel = lf->frameModel = anim->mdxFile;
        lf->backlerp = 0;
        return qtrue;
    }
    if(cg.time >= lf->frameTime) {
        lf->oldFrame = lf->frame; lf->oldFrameTime = lf->frameTime;
        lf->oldFrameModel = lf->frameModel;
        if(cg.time < lf->animationTime) {
            lf->frameTime = lf->animationTime; offset = 0;
        } else {
            lf->frameTime = CorpseTime((double)lf->frameTime + anim->frameLerp);
            elapsed = (double)lf->frameTime - lf->animationTime;
            offset = CorpseTime(elapsed / anim->frameLerp);
        }
        if(offset >= anim->numFrames) {
            if(anim->loopFrames) offset = anim->numFrames - anim->loopFrames + (offset - anim->numFrames) % anim->loopFrames;
            else { offset = anim->numFrames - 1; lf->frameTime = cg.time; }
        }
        if(offset < 0) offset = 0;
        lf->frame = anim->firstFrame + offset; lf->frameModel = anim->mdxFile;
        if(lf->frameTime < cg.time) lf->frameTime = cg.time;
    }
    if((double)lf->frameTime > (double)cg.time + 200) lf->frameTime = cg.time;
    if(lf->oldFrameTime > cg.time) lf->oldFrameTime = cg.time;
    if(lf->frameTime == lf->oldFrameTime) lf->backlerp = 0;
    else lf->backlerp = 1.0f - (float)(((double)cg.time - lf->oldFrameTime) /
        ((double)lf->frameTime - lf->oldFrameTime));
    return qtrue;
}
