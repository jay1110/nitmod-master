#ifndef G_NITMOD_ANTIWARP_H
#define G_NITMOD_ANTIWARP_H
qboolean G_NITMOD_DoAntiwarp(gentity_t *ent);
void G_NITMOD_QueueUsercmd(gentity_t *ent, const usercmd_t *cmd);
void G_NITMOD_RunUsercmds(gentity_t *ent);
void G_NITMOD_PrepareUsercmd(gentity_t *ent);
void G_NITMOD_SkipCorrection(gentity_t *ent);
void G_NITMOD_PredictPmove(gentity_t *ent, float seconds);
#endif
