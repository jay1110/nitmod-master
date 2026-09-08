#ifndef G_NITMOD_NXAC_H
#define G_NITMOD_NXAC_H
void G_NITMOD_NxACReset(void);
void G_NITMOD_NxACResetClient(int clientNum);
void G_NITMOD_NxACUsercmd(int clientNum,const usercmd_t *cmd);
void G_NITMOD_NxACRunFrame(void);
void G_NITMOD_NxACScreenshotStored(int clientNum);
unsigned int G_NITMOD_NxACScreenshotFlags(int clientNum);
#endif
