#ifndef G_NITMOD_INTEGRITY_H
#define G_NITMOD_INTEGRITY_H
int G_NITMOD_LoadChecksums(void);
void G_NITMOD_ClearChecksums(void);
int G_NITMOD_VerifyChecksum(const char *checksum);
int G_NITMOD_ChecksumCommand(int clientNum, const char *command);
#endif
