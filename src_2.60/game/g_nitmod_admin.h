#ifndef G_NITMOD_ADMIN_H
#define G_NITMOD_ADMIN_H
int G_NITMOD_LoadAdminLevels(void);
int G_NITMOD_LoadAdminCommands(void);
int G_NITMOD_AdminAllowed(int clientNum,const char *command);
int G_NITMOD_AdminCommand(int clientNum,const char *command);
int G_NITMOD_AdminPrivilege(int clientNum,const char *privilege);
void G_NITMOD_AdminGreeting(int clientNum);
const char *G_NITMOD_AdminLevelName(int clientNum);
int G_NITMOD_AdminLevel(int clientNum);
#endif
