#ifndef G_NITMOD_LEGACY_CVARS_H
#define G_NITMOD_LEGACY_CVARS_H
void G_NITMOD_RegisterLegacyGameplayCvars(void);
qboolean G_NITMOD_UpdateLegacyGameplayCvars(void);
int G_NITMOD_LegacyCvarInteger(const char *name, int fallback);
float G_NITMOD_LegacyCvarValue(const char *name, float fallback);
void G_NITMOD_LegacyCvarString(const char *name, char *buffer, int bufferSize,
	const char *fallback);
qboolean G_NITMOD_CensorText(const char *cvarName, char *text, int textSize);
#endif
