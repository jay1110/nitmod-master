#ifndef G_NITMOD_ACCOUNTS_H
#define G_NITMOD_ACCOUNTS_H
#include "nitmod_database.h"
int G_NITMOD_AccountUserinfo(int clientNum,const char *userinfo);
void G_NITMOD_AccountReset(int clientNum);
void G_NITMOD_AccountBegin(int clientNum);
int G_NITMOD_AccountCommand(int clientNum,const char *command);
void G_NITMOD_AccountSaveXP(int clientNum);
void G_NITMOD_AccountsSaveAllXP(void);
void G_NITMOD_AccountsMapStart(void);
const char *G_NITMOD_DatabaseBanReason(const char *userinfo);
int G_NITMOD_AccountMuted(int clientNum);
int G_NITMOD_ClientAccount(int clientNum,nitmodDatabaseAccount_t *account);
int G_NITMOD_StoreAccount(const nitmodDatabaseAccount_t *account,int mode);
int G_NITMOD_SecureShrubAllowed(int clientNum);
int G_NITMOD_AccountResetXP(int clientNum);
#endif
