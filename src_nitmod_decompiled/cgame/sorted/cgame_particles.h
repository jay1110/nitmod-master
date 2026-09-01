#ifndef CGAME_PARTICLES_H
#define CGAME_PARTICLES_H

/* Particle systems */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void CG_ParticleSnowFlurry(int param_1,int param_2);
uint32_t CG_ParticleBubble(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4);
void CG_ParticleSmoke(int param_1,int param_2);
void CG_ParticleBulletDebris(uint32_t *param_1,uint32_t *param_2,int param_3);
void CG_ParticleDirtBulletDebris(uint32_t *param_1,uint32_t *param_2,int param_3);
void CG_ParticleImpactSmokePuff(int param_1,uint32_t *param_2);
void CG_Particle_Bleed(int param_1,uint32_t *param_2,uint32_t param_3,int param_4,int param_5);
void CG_Particle_OilSlick(int param_1,int param_2);
void CG_ParticleBloodCloud(int param_1,uint32_t *param_2,uint32_t param_3);
void CG_ParticleBloodCloudZombie(int param_1,uint32_t *param_2,uint32_t param_3);
void CG_ParticleDust(int param_1,float *param_2,float *param_3);
void CG_ParticleMisc(int param_1,uint32_t *param_2,int param_3,int param_4);

#endif

