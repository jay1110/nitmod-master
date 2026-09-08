#ifndef CG_NITMOD_NXAC_TRANSFER_H
#define CG_NITMOD_NXAC_TRANSFER_H
void CG_NITMOD_NxACTransferReset(void);
void CG_NITMOD_NxACTransferFrame(void);
qboolean CG_NITMOD_NxACTransferCommand(const char *command);
#endif
