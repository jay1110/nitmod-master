#ifndef G_NITMOD_LUA_H
#define G_NITMOD_LUA_H
void G_NITMOD_LuaInit(int time,int seed,int restart);
void G_NITMOD_LuaFrame(int time);
void G_NITMOD_LuaShutdown(int restart);
void G_NITMOD_LuaUnload(void);
int G_NITMOD_LuaCount(void);
void G_NITMOD_LuaClientEvent(const char *hook,int client);
char *G_NITMOD_LuaConnect(int client,int first,int bot);
int G_NITMOD_LuaCommand(int client,const char *command);
int G_NITMOD_LuaSkill(const char *hook,int client,int skill);
int G_NITMOD_LuaObituary(int victim,int killer,int mod);
void G_NITMOD_LuaSpawn(int client,int revived,int teamChange,int restoreHealth);
void G_NITMOD_LuaStatus(int client);
void G_NITMOD_LuaPrint(const char *text);
void G_NITMOD_LuaReceivedGlobalStats(int client,const char *text);
#endif
