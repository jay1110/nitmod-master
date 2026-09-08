#ifndef G_NITMOD_SERVER_CVARS_H
#define G_NITMOD_SERVER_CVARS_H

void G_NITMOD_ResetServerCvars(void);
qboolean G_NITMOD_ServerCvarCommand(const char *command);
void G_NITMOD_SendForcedCvars(int clientNum);

#endif
