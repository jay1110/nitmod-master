#ifndef G_NITMOD_NXAC_TRANSFER_H
#define G_NITMOD_NXAC_TRANSFER_H
void G_NITMOD_NxACTransferInit(void);
void G_NITMOD_NxACTransferShutdown(void);
void G_NITMOD_NxACTransferResetClient(int clientNum);
void G_NITMOD_NxACTransferRunFrame(void);
qboolean G_NITMOD_NxACTransferRequest(int clientNum);
qboolean G_NITMOD_NxACTransferConsoleCommand(const char *command);
#endif
