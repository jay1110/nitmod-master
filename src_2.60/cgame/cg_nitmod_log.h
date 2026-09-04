#ifndef CG_NITMOD_LOG_H
#define CG_NITMOD_LOG_H

void CG_NitmodLogInit(void);
void CG_NitmodLogShutdown(void);
void CG_NitmodLogText(const char *text);
void CG_NitmodLogLine(char *out, int size, const qtime_t *now, const char *text);

#endif
