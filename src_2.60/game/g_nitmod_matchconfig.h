#ifndef G_NITMOD_MATCHCONFIG_H
#define G_NITMOD_MATCHCONFIG_H
void G_NITMOD_InitMatchConfig(void);
void G_NITMOD_EnforceMatchConfig(void);
qboolean G_NITMOD_LoadMatchConfig(const char *filename, qboolean reload);
qboolean G_NITMOD_MatchConfigCommand(const char *command);
#endif
