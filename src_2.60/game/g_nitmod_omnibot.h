#ifndef G_NITMOD_OMNIBOT_H
#define G_NITMOD_OMNIBOT_H

const char *G_NITMOD_OmniBotModuleName(void);
void G_NITMOD_OmniBotExpectedPath(char *buffer, int bufferSize);
int G_NITMOD_OmniBotProbe(void);
void G_NITMOD_OmniBotConsoleCommand(void);
void G_NITMOD_OmniBotReportStatus(void);
void G_NITMOD_OmniBotStartup(void);

#endif
