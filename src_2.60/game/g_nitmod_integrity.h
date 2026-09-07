#ifndef G_NITMOD_INTEGRITY_H
#define G_NITMOD_INTEGRITY_H
int G_NITMOD_LoadChecksums(void);
void G_NITMOD_ClearChecksums(void);
int G_NITMOD_VerifyChecksum(const char *checksum);
int G_NITMOD_ChecksumCommand(int clientNum, const char *command);
int G_NITMOD_LoadCvarList(void);
void G_NITMOD_ClearCvarList(void);
void G_NITMOD_CvarScanResetClient(int clientNum);
void G_NITMOD_CvarScanStart(int clientNum);
void G_NITMOD_CvarScanRequest(int clientNum);
void G_NITMOD_CvarScanThink(int clientNum);
int G_NITMOD_CvarScanCommand(int clientNum,const char *command);
#endif
