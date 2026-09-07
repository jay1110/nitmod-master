#include "g_local.h"
#include "g_nitmod_lua.h"
#include "nitmod_sha1.h"
#include <assert.h>
static const char *fixtureArgument="argument",*fixtureStatsURL="";
int trap_Argc(void) { return 2; }
void trap_Argv(int n,char *out,int size) { Q_strncpyz(out,n==0?"fixture":fixtureArgument,size); }
void Com_Printf(const char *fmt,...) {}

#undef vsnprintf
int Q_vsnprintf(char *out,int size,const char *fmt,va_list args) { return vsnprintf(out,size,fmt,args); }
void Com_Error(int code,const char *fmt,...) { abort(); }
static const char *modules="test.lua",*acl="",*source;
static int frames,inits,quits,closed,errors;
static char lifecycleOrder[128];
void G_Printf(const char *fmt,...) { G_NITMOD_LuaPrint("nested print"); }
static char statusText[10000];
void NITMOD_SendChunkedPrint(int client,const char *text) { assert(client==3 && strstr(text,"modules loaded")); Q_strncpyz(statusText,text,sizeof(statusText)); }
static char fixtureLastLog[2048];
void G_LogPrintf(const char *fmt,...) { va_list args;va_start(args,fmt);vsnprintf(fixtureLastLog,sizeof(fixtureLastLog),fmt,args);va_end(args);++errors; }
void G_NITMOD_LegacyCvarString(const char *name,char *out,int size,const char *fallback) { Q_strncpyz(out,!strcmp(name,"lua_modules")?modules:acl,size); }
void trap_Cvar_VariableStringBuffer(const char *name,char *out,int size) { Q_strncpyz(out,!strcmp(name,"n_globalStatsBridge")?fixtureStatsURL:"value",size); }
void trap_Cvar_Set(const char *name,const char *value) { if(!strcmp(name,"lifecycle_order")) Q_strcat(lifecycleOrder,sizeof(lifecycleOrder),value); if(!strcmp(name,"frame")) ++frames; if(!strcmp(name,"init")) ++inits; if(!strcmp(name,"quit")) ++quits; }
static const char *childSource="return 42, 'child'";
static char fileBytes[4096]; static int fileLength,renamed;
int trap_FS_Write(const void *data,int length,fileHandle_t file) { assert(file==9 && length<=sizeof(fileBytes)); memcpy(fileBytes,data,length); fileLength=length; return length; }
int trap_FS_Rename(const char *from,const char *to) { assert(!strcmp(from,"fixture.dat") && !strcmp(to,"renamed.dat")); ++renamed; return 0; }
int trap_FS_FOpenFile(const char *path,fileHandle_t *file,fsMode_t mode) { if(!strcmp(path,"child.lua") || !strcmp(path,"./child.lua")) { *file=8; return strlen(childSource); } if(!strcmp(path,"missing.lua")) { *file=0; return -1; } if(!strcmp(path,"fixture.dat")) { *file=9; return fileLength; } assert(mode==FS_READ); *file=1; return strlen(source); }
void trap_FS_Read(void *out,int size,fileHandle_t file) { if(file==8) { assert(size==strlen(childSource)); memcpy(out,childSource,size); return; } if(file==9) { assert(size<=fileLength); memcpy(out,fileBytes,size); return; } memcpy(out,source,size); }
void trap_FS_FCloseFile(fileHandle_t file) { ++closed; }
static char userinfo[1024],configstring[1024]; static int changed,sent,consoleSent,dropped;
void trap_GetUserinfo(int n,char *out,int size) { assert(n==3); Q_strncpyz(out,userinfo,size); }
void trap_SetUserinfo(int n,const char *value) { assert(n==3); Q_strncpyz(userinfo,value,sizeof(userinfo)); }
void ClientUserinfoChanged(int n) { assert(n==3); ++changed; }
void trap_GetConfigstring(int n,char *out,int size) { assert(n==42); Q_strncpyz(out,configstring,size); }
void trap_SetConfigstring(int n,const char *value) { assert(n==42); Q_strncpyz(configstring,value,sizeof(configstring)); }
static char statsReply[512];
void trap_SendServerCommand(int n,const char *value) { if(n==3 && !strncmp(value,"glstats ",8)) { Q_strncpyz(statsReply,value,sizeof(statsReply));return; } assert(n==-1 && (!strcmp(value,"fixture") || !strcmp(value,"cpm \"Custom obituary\n\""))); ++sent; }
void trap_SendConsoleCommand(int when,const char *value) { assert(when==EXEC_APPEND && !strcmp(value,"fixture")); ++consoleSent; }
void trap_DropClient(int n,const char *reason,int ban) { assert(n==3 && !strcmp(reason,"fixture") && ban==45); ++dropped; }
int trap_Cvar_VariableIntegerValue(const char *name) { assert(!strcmp(name,"g_defaultBanTime")); return 45; }
int trap_Milliseconds(void) { return 12345; }
gentity_t g_entities[MAX_GENTITIES]; static int events,linked,freed,sounds; static int expectedLuaEvent=EV_NITMOD_LUA_FIRST+40,expectedLuaParm=3; static float skillPoints;
void G_AddEvent(gentity_t *ent,int event,int parm) { assert(ent==g_entities+100 && event==expectedLuaEvent && parm==expectedLuaParm); ++events; }
void trap_LinkEntity(gentity_t *ent) { assert(ent==g_entities+100); ++linked; }
void trap_UnlinkEntity(gentity_t *ent) { assert(ent==g_entities+100); --linked; }
void G_FreeEntity(gentity_t *ent) { assert(ent==g_entities+100); ++freed; }
gentity_t *G_Spawn(void) { return g_entities+100; }
void G_AddSkillPoints(gentity_t *ent,skillType_t skill,float points) { assert(ent==g_entities+3 && skill==2); skillPoints+=points; }
void G_LoseSkillPoints(gentity_t *ent,skillType_t skill,float points) { assert(ent==g_entities+3 && skill==2); skillPoints-=points; }
int G_ModelIndex(char *name) { assert(!strcmp(name,"model")); return 12; }
int G_SoundIndex(const char *name) { assert(!strcmp(name,"sound")); return 13; }
void G_Sound(gentity_t *ent,int sound) { assert(ent==g_entities+100 && sound==13); ++sounds; }
char *G_NewString(const char *s) { char *copy=malloc(strlen(s)+1); strcpy(copy,s); return copy; }
level_locals_t level;
static int damageCalls,globalSounds,expectedDamageMod=MOD_MACHINEGUN;
void G_Damage(gentity_t *t,gentity_t *i,gentity_t *a,vec3_t dir,vec3_t point,int damage,int flags,int mod) { assert(t==g_entities+3 && i==g_entities+100 && a==g_entities+3 && !dir && !point && damage==10 && flags==0 && mod==expectedDamageMod); ++damageCalls; }
gentity_t *G_TempEntity(vec3_t origin,int event) { assert((origin[0]==1 && origin[1]==2 && origin[2]==3 && event==EV_NITMOD_LUA_FIRST) || (origin[0]==0 && event==EV_GLOBAL_CLIENT_SOUND)); g_entities[101].s.eType=ET_EVENTS+event; return g_entities+101; }
void G_globalSound(char *sound) { assert(!strcmp(sound,"fixture.wav")); ++globalSounds; }
static int said;
qboolean G_NITMOD_ClientIsFlooding(gentity_t *ent) { assert(ent==g_entities+3);return qtrue; }
void G_Say(gentity_t *ent,gentity_t *target,int mode,const char *text) { assert(ent==g_entities+3 && !target && mode==0 && !strcmp(text,"hello")); ++said; }
qboolean G_EntitiesFree(void) { return qtrue; }
const char *G_NITMOD_AdminLevelName(int n) { return n==3?"Moderator":"Guest"; }
static int rankUpdates,stateUpdates;
void G_CalcRank(gclient_t *client) { ++rankUpdates; }
void BG_PlayerStateToEntityState(playerState_t *ps,entityState_t *s,qboolean snap) { ++stateUpdates; }
int G_NITMOD_CurrentKillSpree(int client) { assert(client==3);return 7; }
int G_NITMOD_AdminLevel(int n) { return n==3?2:0; }
int G_NITMOD_AdminAllowed(int n,const char *cmd) { return n<0 || !strcmp(cmd,"help"); }
int main(void) {
 char hash[41];
 source="assert(et.FindSelf()==0); et.RegisterModname('fixture'); local name,sha=et.FindMod(0); assert(name=='fixture' and #sha==40); local absent,signature=et.FindMod(-1); assert(absent==nil and signature==nil); assert(et.trap_Cvar_Get('x')=='value'); function et_InitGame(t,s,r) assert(t==10 and s==20 and r==0); et.trap_Cvar_Set('init','1') end; function et_RunFrame(t) assert(t==30); et.trap_Cvar_Set('frame','1') end; function et_Quit() et.trap_Cvar_Set('quit','1') end";
 G_NITMOD_LuaInit(10,20,0); assert(G_NITMOD_LuaCount()==1 && inits==1 && closed==1);
 G_NITMOD_LuaFrame(30); assert(frames==1); G_NITMOD_LuaShutdown(0); assert(quits==1 && G_NITMOD_LuaCount()==0);
 acl="DENIED"; G_NITMOD_LuaInit(10,20,0); assert(!G_NITMOD_LuaCount());
 NITMOD_SHA1Text(source,hash); acl=hash; G_NITMOD_LuaInit(10,20,0); assert(G_NITMOD_LuaCount()==1); G_NITMOD_LuaShutdown(0);
 acl=""; source="function et_RunFrame() error('fixture failure') end"; G_NITMOD_LuaInit(0,0,0); { int before=errors,i; for(i=0;i<100;++i) G_NITMOD_LuaFrame(i); assert(errors==before+100); } G_NITMOD_LuaShutdown(0);
 source="invalid lua !"; G_NITMOD_LuaInit(0,0,0); assert(!G_NITMOD_LuaCount());
 source="error('startup')"; G_NITMOD_LuaInit(0,0,0); assert(!G_NITMOD_LuaCount());
 source="function et_ClientConnect(c,f,b) assert(c==3 and f==1 and b==0); return 'denied by fixture' end; function et_ClientCommand(c,cmd) assert(c==3); assert(et.trap_Argc()==2 and et.trap_Argv(1)=='argument'); if cmd=='handled' then return 1 elseif cmd=='boolean' then return true else error('command error') end end; function et_ConsoleCommand(cmd) return cmd=='handled' and 1 or 0 end; function et_ClientBegin(c) assert(c==3); et.trap_Cvar_Set('init','1') end";
 G_NITMOD_LuaInit(0,0,0);
 assert(!strcmp(G_NITMOD_LuaConnect(3,1,0),"denied by fixture"));
 assert(G_NITMOD_LuaCommand(3,"handled") && !G_NITMOD_LuaCommand(3,"boolean"));
 assert(!G_NITMOD_LuaCommand(3,"error") && G_NITMOD_LuaCommand(3,"handled"));
 assert(G_NITMOD_LuaCommand(-1,"handled") && !G_NITMOD_LuaCommand(-1,"other"));
 { int before=inits; G_NITMOD_LuaClientEvent("et_ClientBegin",3); assert(inits==before+1); }
 G_NITMOD_LuaShutdown(0); assert(!G_NITMOD_LuaConnect(3,1,0) && !G_NITMOD_LuaCommand(3,"handled"));
 { static gclient_t client; g_entities[3].client=&client;
 client.ps.powerups[PW_FIRE]=901;client.ps.powerups[PW_ELECTRIC]=902;
 source="for i=0,15 do et.gentity_set(3,'ps.powerups',i,100+i) end; for i=0,15 do assert(et.gentity_get(3,'ps.powerups',i)==100+i) end";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
 assert(client.ps.powerups[PW_BLACKOUT]==102 && client.ps.powerups[PW_ADRENALINE]==111);
 assert(client.ps.powerups[PW_MVCLIENTLIST]==112 && client.ps.powerups[PW_OPS_DISGUISED]==107);
 assert(client.ps.powerups[PW_FIRE]==901 && client.ps.powerups[PW_ELECTRIC]==902);
 G_NITMOD_LuaShutdown(0); }
 g_entities[100].s.powerups=(1<<PW_FIRE)|(1<<PW_ELECTRIC)|(1<<PW_ADRENALINE)|(1<<PW_OPS_DISGUISED);
 source="assert(et.gentity_get(100,'s.powerups')==2176); assert(not pcall(et.gentity_set,100,'s.powerups',0))";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 modules="first.lua;second.lua";
 source="local self=et.FindSelf(); function et_IPCReceive(sender,msg) if msg=='bad' then error('ipc failure') end; if msg=='ping' then assert(sender==0 and self==1); assert(et.IPCSend(0,'pong')==1) elseif msg=='pong' then assert(sender==1 and self==0); et.trap_Cvar_Set('frame','1') elseif msg=='self' then assert(sender==self) end end; function et_ClientCommand(c,cmd) if self==0 then assert(et.IPCSend(-1,'x')==0 and et.IPCSend(16,'x')==0); assert(et.IPCSend(0,'self')==1); assert(et.IPCSend(1,'ping')==1); assert(et.IPCSend(1,'bad')==0); assert(et.IPCSend(1,'ping')==0); return 1 end end";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==2);
 { int before=frames; assert(G_NITMOD_LuaCommand(3,"ipc")); assert(frames==before+1); }
 G_NITMOD_LuaShutdown(0); modules="test.lua";
 modules="first.lua;second.lua";
 source="function et_RunFrame() if et.FindSelf()==1 then error({}) end end; function et_ClientCommand() if et.FindSelf()==0 then assert(et.IPCSend(1,'blocked')==0); return 1 end end; function et_IPCReceive() error('must not run') end";
 G_NITMOD_LuaInit(0,0,0); G_NITMOD_LuaFrame(1); assert(G_NITMOD_LuaCommand(0,"verify")); G_NITMOD_LuaShutdown(0);
 modules="test.lua";
 source="et.trap_SetUserinfo(3,'userinfo'); assert(et.trap_GetUserinfo(3)=='userinfo'); et.ClientUserinfoChanged(3); et.trap_SetConfigstring(42,'config'); assert(et.trap_GetConfigstring(42)=='config'); et.trap_SendServerCommand(-1,'fixture'); et.trap_SendConsoleCommand(et.EXEC_APPEND,'fixture'); et.trap_DropClient(3,'fixture'); et.trap_DropClient(3,'fixture',45); assert(et.trap_Milliseconds()==12345); assert(not pcall(et.trap_GetUserinfo,-1)); assert(not pcall(et.trap_SetConfigstring,999999,'x')); assert(not pcall(et.trap_SendConsoleCommand,9,'x'))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1 && changed==1 && sent==1 && consoleSent==1 && dropped==2); G_NITMOD_LuaShutdown(0);
 source="local f,n=et.trap_FS_FOpenFile('fixture.dat',et.FS_WRITE); assert(f==9 and n==0); assert(et.trap_FS_Write('abc',3,f)==3); assert(not pcall(et.trap_FS_Write,'a',2,f)); et.trap_FS_FCloseFile(f); f,n=et.trap_FS_FOpenFile('fixture.dat',et.FS_READ); assert(n==3 and et.trap_FS_Read(f,3)=='abc'); assert(not pcall(et.trap_FS_Read,f,-1)); et.trap_FS_FCloseFile(f); et.trap_FS_Rename('fixture.dat','renamed.dat'); assert(et.Q_CleanStr('^1hello')=='hello'); local info=et.Info_SetValueForKey('','name','fixture'); assert(et.Info_ValueForKey(info,'name')=='fixture'); assert(et.Info_ValueForKey(et.Info_RemoveKey(info,'name'),'name')==''); assert(et.ConcatArgs(0)=='fixture argument')";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1 && renamed==1 && fileLength==3); G_NITMOD_LuaShutdown(0);
 source="function et_SetPlayerSkill(c,s) assert(c==3 and s==2); return -1 end; function et_UpgradeSkill(c,s) return 1 end";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaSkill("et_SetPlayerSkill",3,2) && !G_NITMOD_LuaSkill("et_UpgradeSkill",3,2)); G_NITMOD_LuaShutdown(0);
 source="local f=assert(loadfile('child.lua')); assert(f()==42); local a,b=dofile('child.lua'); assert(a==42 and b=='child'); package.path='./?.lua'; assert(require('child')==42); local no,err=loadfile('missing.lua'); assert(no==nil and type(err)=='string'); assert(not pcall(dofile,'missing.lua'))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1); G_NITMOD_LuaShutdown(0);
 source="local e=et.G_Spawn(); assert(e==100); et.trap_LinkEntity(e); et.G_AddEvent(e,40,3); assert(et.G_ModelIndex('model')==12); et.G_Sound(e,et.G_SoundIndex('sound')); et.trap_UnlinkEntity(e); et.G_FreeEntity(e); et.G_AddSkillPoints(3,2,2.5); et.G_LoseSkillPoints(3,2,1.25); assert(not pcall(et.G_FreeEntity,-1)); assert(not pcall(et.G_AddSkillPoints,3,999,1))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1 && events==1 && linked==0 && freed==1 && sounds==1 && skillPoints==1.25f); G_NITMOD_LuaShutdown(0);
 {
 int original;char sourceText[768];
 for(original=0;original<=106;++original) {
    expectedLuaEvent=original?EV_NITMOD_LUA_FIRST+original:0;expectedLuaParm=-2147483647;
    snprintf(sourceText,sizeof(sourceText),"et.G_AddEvent(100,%d,-2147483647); local e=et.G_TempEntity({1,2,3},%d); assert(et.gentity_get(e,'s.eType')==%d); et.gentity_set(100,'s.eType',%d); assert(et.gentity_get(100,'s.eType')==%d)",original,original,59+original,59+original,59+original);
    source=sourceText;G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
    assert(g_entities[101].s.eType<256 && g_entities[101].s.event<256);
    G_NITMOD_LuaShutdown(0);
 }
 source="for i=0,55 do et.gentity_set(100,'s.eType',i); assert(et.gentity_get(100,'s.eType')==i) end; assert(not pcall(et.G_AddEvent,100,107,0)); assert(not pcall(et.G_AddEvent,100,-1,0)); assert(not pcall(et.G_TempEntity,{1,2,3},107)); assert(not pcall(et.gentity_set,100,'s.eType',58)); assert(et.gentity_get(100,'s.eType')==55)";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 expectedLuaEvent=EV_NITMOD_LUA_FIRST+40;expectedLuaParm=3;
 }
 source="for _,f in ipairs({'methodOfDeath','splashMethodOfDeath','deathType'}) do for m=0,68 do et.gentity_set(100,f,m); assert(et.gentity_get(100,f)==m) end; assert(not pcall(et.gentity_set,100,f,69)); assert(not pcall(et.gentity_set,100,f,-1)); assert(et.gentity_get(100,f)==68) end; et.gentity_set(100,'methodOfDeath',62); et.gentity_set(100,'splashMethodOfDeath',63); et.gentity_set(100,'deathType',60)";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1);
 assert(g_entities[100].methodOfDeath==MOD_SHOVE && g_entities[100].splashMethodOfDeath==MOD_THROWKNIFE && g_entities[100].deathType==MOD_FEAR);
 G_NITMOD_LuaShutdown(0);
 { static gclient_t client; int row; g_entities[3].client=&client;
 for(row=0;row<=WS_MAX;++row) { client.sess.aWeaponStats[row].atts=100+row;client.sess.aWeaponStats[row].deaths=200+row;client.sess.aWeaponStats[row].headshots=300+row;client.sess.aWeaponStats[row].hits=400+row;client.sess.aWeaponStats[row].kills=500+row; }
 source="for i=0,26 do local n=i<15 and i or i+1; local t=et.gentity_get(3,'sess.aWeaponStats',i); for j=1,5 do assert(t[j]==100*j+n) end end; assert(not pcall(et.gentity_get,3,'sess.aWeaponStats',27)); assert(not pcall(et.gentity_set,3,'sess.aWeaponStats',21,0))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0); }
 { static gclient_t client; int i; g_entities[3].client=&client;
 for(i=0;i<MAX_PERSISTANT;++i) client.ps.persistant[i]=100+i;
 source="for i=0,15 do et.gentity_set(3,'ps.persistant',i,2000+i) end; for i=0,15 do assert(et.gentity_get(3,'PS.PERSISTANT',i)==2000+i) end; assert(not pcall(et.gentity_set,3,'ps.persistant',16,9)); assert(not pcall(et.gentity_get,3,'ps.persistant',-1))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1);
 assert(client.ps.persistant[PERS_TEAM]==2007 && client.ps.persistant[PERS_RESPAWNS_LEFT]==2009);
 assert(client.ps.persistant[PERS_KILLED]==2004 && client.ps.persistant[PERS_REVIVE_COUNT]==2011);
 assert(client.ps.persistant[PERS_HITS]==101 && client.ps.persistant[PERS_RANK]==102 && client.ps.persistant[PERS_ATTACKER]==105);
 assert(client.nitmodLuaPersistant[1]==2001 && client.nitmodLuaPersistant[2]==2002 && client.nitmodLuaPersistant[6]==2006);
 G_NITMOD_LuaShutdown(0); }
 { static gclient_t client; g_entities[3].client=&client;
 g_entities[100].s.weapon=WP_POISON_MINE;
 source="assert(et.gentity_get(100,'s.weapon')==51); assert(not pcall(et.gentity_set,100,'s.weapon',1)); et.gentity_set(3,'sess.playerWeapon',31); et.gentity_set(3,'sess.playerWeapon2',43); et.gentity_set(3,'sess.latchPlayerWeapon',48); et.gentity_set(3,'sess.latchPlayerWeapon2',51); assert(et.gentity_get(3,'SESS.PLAYERWEAPON')==31); assert(et.gentity_get(3,'sess.playerWeapon2')==43); assert(et.gentity_get(3,'sess.latchPlayerWeapon')==48); assert(et.gentity_get(3,'sess.latchPlayerWeapon2')==51); assert(not pcall(et.gentity_set,3,'sess.playerWeapon',52)); assert(not pcall(et.gentity_set,3,'sess.playerWeapon',-1)); assert(et.gentity_get(3,'sess.playerWeapon')==31)";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1);
 assert(client.sess.playerWeapon==WP_FG42 && client.sess.playerWeapon2==WP_MEDIC_ADRENALINE);
 assert(client.sess.latchPlayerWeapon==WP_BOMB && client.sess.latchPlayerWeapon2==WP_POISON_MINE);
 G_NITMOD_LuaShutdown(0);
 client.ps.ammo[WP_MAPMORTAR]=777; client.ps.ammoclip[WP_LOCKPICK]=888;
 source="for i=0,63 do et.gentity_set(3,'ps.ammo',i,1000+i); et.gentity_set(3,'ps.ammoclip',i,2000+i) end; for i=0,63 do assert(et.gentity_get(3,'PS.AMMO',i)==1000+i); assert(et.gentity_get(3,'ps.ammoclip',i)==2000+i) end; assert(not pcall(et.gentity_set,3,'ps.ammo',64,9)); assert(not pcall(et.gentity_set,3,'ps.ammoclip',-1,9))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1);
 assert(client.ps.ammo[WP_MEDIC_ADRENALINE]==1043 && client.ps.ammo[WP_MEDIC_SYRINGE]==1011);
 assert(client.ps.ammo[WP_POISON_MINE]==1051 && client.ps.ammo[WP_POISON_BOMB]==1050);
 assert(client.ps.ammoclip[WP_FG42]==2031 && client.ps.ammoclip[WP_TRIPMINE]==2049);
 assert(client.ps.ammo[WP_MAPMORTAR]==777 && client.ps.ammoclip[WP_LOCKPICK]==888);
 assert(client.nitmodLuaUnusedAmmo[0][0]==1052 && client.nitmodLuaUnusedAmmo[1][11]==2063);
 G_NITMOD_LuaShutdown(0); }
 { static gclient_t client; g_entities[3].client=&client;
 client.sess.nitmodKillingSpree=23; client.nitmodLuaPersistant[15]=9;
 source="assert(et.gentity_get(3,'sess.killingSpree')==23); assert(not pcall(et.gentity_set,3,'sess.killingSpree',9)); et.gentity_set(3,'health',75); assert(et.gentity_get(3,'HEALTH')==75); et.gentity_set(3,'pers.netname','LuaName'); assert(et.gentity_get(3,'pers.netname')=='LuaName'); et.gentity_set(3,'ps.ammo',2,30); assert(et.gentity_get(3,'ps.ammo',2)==30); et.gentity_set(3,'origin',{1,2,3}); assert(et.gentity_get(3,'ps.origin')[3]==3); et.gentity_set(100,'origin',{4,5,6}); assert(et.gentity_get(100,'r.currentOrigin')[1]==4); et.gentity_set(100,'s.pos',{trType=1,trTime=2,trDuration=3,trBase={4,5,6},trDelta={7,8,9}}); assert(et.gentity_get(100,'s.pos').trDelta[3]==9); assert(not pcall(et.gentity_set,3,'sess.skillpoints',0,99)); assert(not pcall(et.gentity_set,3,'ps.ammo',999,30)); assert(not pcall(et.gentity_set,100,'s.pos',{})); assert(et.gentity_get(100,'s.pos').trTime==2); et.gentity_set(100,'enemy',3); assert(et.gentity_get(100,'enemy')==3); et.gentity_set(100,'enemy',-1); assert(et.gentity_get(100,'enemy')==-1); assert(type(et.gentity_get(3,'sess.aWeaponStats',0))=='table'); assert(not pcall(et.gentity_get,3,'sess.aWeaponStats',999)); assert(not pcall(et.gentity_get,3,'missing_field'))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1 && g_entities[3].health==75 && client.ps.ammo[2]==30); G_NITMOD_LuaShutdown(0); }
 { static gclient_t client; level.maxclients=4; g_entities[3].inuse=qtrue; g_entities[3].client=&client; client.pers.connected=CON_CONNECTED; client.sess.sessionTeam=TEAM_AXIS;
 source="et.G_Damage(3,100,3,10,0,1); assert(et.G_TempEntity({1,2,3},40)==101); et.G_globalSound('fixture.wav'); assert(et.G_PlayerCount(0)==1 and et.G_PlayerCount(et.TEAM_AXIS)==1 and et.G_PlayerCount()==0); assert(not pcall(et.G_PlayerCount,99))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1 && damageCalls==1 && globalSounds==1); G_NITMOD_LuaShutdown(0); }
 strcpy(g_entities[3].client->pers.netname,"^1FixturePlayer");
 source="assert(et.ClientNumberFromString('fixture')==3 and et.ClientNumberFromString('3')==3 and et.ClientNumberFromString('999')==-1); assert(et.ClientIsFlooding(3)==1); et.G_Say(3,0,'hello'); assert(et.G_AdminLevelName(3)=='Moderator'); assert(et.G_AdminLevelName()=='Guest'); assert(select('#',et.G_EntitiesFree())==0)";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1 && said==1);G_NITMOD_LuaShutdown(0);
 g_entities[3].client->sess.skillpoints[2]=10; g_entities[3].client->sess.startxptotal=50;
 source="assert(et.G_XP_Set(3,20,2,false)==false); assert(et.G_XP_Set(3,5,2,1)==1); assert(not pcall(et.G_XP_Set,3,-1,2,false)); assert(not pcall(et.G_XP_Set,3,1,99,false))";
 G_NITMOD_LuaInit(0,0,0); assert(G_NITMOD_LuaCount()==1 && g_entities[3].client->sess.skillpoints[2]==25 && g_entities[3].client->sess.startxptotal==65 && rankUpdates==2 && stateUpdates==2);G_NITMOD_LuaShutdown(0);
 g_entities[100].inuse=qtrue;
 source="assert(et.G_SetSpawnVar(100,'speed',2.5)==2.5); assert(et.G_GetSpawnVar(100,'speed')==2.5); et.G_SetSpawnVar(100,'baseOrigin',{4,5,6}); assert(et.G_GetSpawnVar(100,'baseOrigin')[2]==5); assert(et.G_GetSpawnVar(102,'health')==nil); assert(not pcall(et.G_GetSpawnVar,100,'invalid')); et.G_ClientSound(3,27)";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1 && g_entities[101].r.singleClient==3 && g_entities[101].s.eventParm==27 && g_entities[101].r.svFlags==SVF_SINGLECLIENT);G_NITMOD_LuaShutdown(0);
 source="function et_Obituary(v,k,m) assert(v==3 and k==2 and m==1); return 'Custom obituary' end";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1 && G_NITMOD_LuaObituary(3,2,1));G_NITMOD_LuaShutdown(0);assert(!G_NITMOD_LuaObituary(3,2,1));
 {
  const int native[]={MOD_FALLING,MOD_GOOMBA,MOD_SHOVE,MOD_TRIPMINE,MOD_POISON_GAS,MOD_SWITCHTEAM,MOD_FG42SCOPE,MOD_FEAR,MOD_CENSORED,MOD_THROWKNIFE,MOD_GIBME};
  const int original[]={31,58,62,66,67,57,14,60,61,63,64};int n;
  for(n=0;n<11;++n) {
   char script[300];int before;
   snprintf(script,sizeof(script),"et.G_Damage(3,100,3,10,0,%d); function et_Obituary(v,k,m) assert(v==3 and k==2 and m==%d); et.trap_Cvar_Set('frame','1') end",original[n],original[n]);
   expectedDamageMod=native[n];source=script;before=damageCalls;
   G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1 && damageCalls==before+1);
   before=frames;assert(!G_NITMOD_LuaObituary(3,2,native[n]) && frames==before+1);
   G_NITMOD_LuaShutdown(0);
  }
  expectedDamageMod=MOD_MACHINEGUN;
 }
 source="function et_ClientSpawn(c,r,t,h) assert(c==3 and r==1 and t==0 and h==1); et.trap_Cvar_Set('frame','1') end";
 G_NITMOD_LuaInit(0,0,0); { int before=frames; G_NITMOD_LuaSpawn(3,1,0,1); assert(frames==before+1); } G_NITMOD_LuaStatus(3);G_NITMOD_LuaShutdown(0);
 source="function et_Print(text) assert(text=='outer print'); et.G_Print('nested print'); et.trap_Cvar_Set('frame','1') end";
 G_NITMOD_LuaInit(0,0,0); { int before=frames; G_NITMOD_LuaPrint("outer print");assert(frames==before+1); } G_NITMOD_LuaShutdown(0);
 g_entities[3].client->pers.nitmodLastReviverClient=4;g_entities[3].client->pers.nitmodLastKillerClient=5;g_entities[3].client->pers.nitmodLastAmmoClient=6;g_entities[3].client->pers.nitmodLastHealthClient=7;g_entities[3].client->pers.nitmodLastKilledClient=8;g_entities[3].client->lastkilled_client=99;
 source="assert(et.gentity_get(3,'pers.lastrevive_client')==4);assert(et.gentity_get(3,'pers.lastkiller_client')==5);assert(et.gentity_get(3,'pers.lastammo_client')==6);assert(et.gentity_get(3,'pers.lasthealth_client')==7);assert(et.gentity_get(3,'pers.lastkilled_client')==8);assert(not pcall(et.gentity_set,3,'pers.lasthealth_client',99))";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 source="assert(et.G_shrubbot_level(3)==2);assert(et.G_shrubbot_permission(3,'help')==1);assert(et.G_shrubbot_permission(3,'ban')==0);assert(et.SAY_TEAMNL==3 and et.HOSTARCH=='wasm32');assert(LUA_DIRSEP=='/' and package.path=='?.lua;lualibs/?.lua')";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 g_entities[3].client->sess.nitmodNewton=7;
 g_entities[3].client->sess.uci=42;
 source="assert(et.gentity_get(3,'sess.uci')==42); assert(not pcall(et.gentity_set,3,'sess.uci',1))";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1 && g_entities[3].client->sess.uci==42);G_NITMOD_LuaShutdown(0);
 source="et.gentity_set(3,'sess.shoutcaster',1); assert(et.gentity_get(3,'sess.shoutcaster')==1); et.gentity_set(3,'sess.shoutcaster',0); assert(et.gentity_get(3,'sess.shoutcaster')==0)";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1 && !g_entities[3].client->sess.shoutcaster);G_NITMOD_LuaShutdown(0);
 source="assert(et.G_GetSpawnVar(100,'light')==nil); assert(et.G_SetSpawnVar(100,'light',5)==nil); function et_ClientSpawn(c,r,t,h) assert(c==3 and r==0 and t==1 and h==0) end";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1); { int before=errors; G_NITMOD_LuaSpawn(3,0,1,0); assert(errors==before); } G_NITMOD_LuaShutdown(0);
 source="assert(et.G_SetSpawnVar(100,'_etxmap_autogeneratedName',1)==1); assert(et.G_GetSpawnVar(100,'_etxmap_autogeneratedName')==1); et.G_SetSpawnVar(100,'_etxmap_fixedDuplicatedName',2); assert(et.G_GetSpawnVar(100,'_etxmap_fixedDuplicatedName')==2)";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1 && g_entities[100].etxmapAutogeneratedName==1 && g_entities[100].etxmapFixedDuplicatedName==2);G_NITMOD_LuaShutdown(0);
 source="assert(et.gentity_get(3,'sess.newton')==7); assert(not pcall(et.gentity_set,3,'sess.newton',99)); assert(et.G_SetSpawnVar(100,'numPlayers',3)==3); assert(et.G_GetSpawnVar(100,'numPlayers')==3)";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1 && g_entities[100].numPlayers==3 && g_entities[3].client->sess.nitmodNewton==7);G_NITMOD_LuaShutdown(0);
 modules="a;b;c;d;e;f;g;h;i;j;k;l;m;n;o;p";
 modules="a;b";
 source="local id=et.FindSelf(); function et_ReceivedGlobalStats(c,s) assert(c==3 and s=='payload'); if id==0 then error('fixture') end; et.trap_Cvar_Set('frame','1') end";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==2);
 { int before=frames,previous=errors;G_NITMOD_LuaReceivedGlobalStats(3,"payload");G_NITMOD_LuaReceivedGlobalStats(3,"payload");assert(frames==before+2 && errors==previous+2); }
 G_NITMOD_LuaShutdown(0);
 modules="a;b;c;d;e;f;g;h;i;j;k;l;m;n;o;p";
 source="et.RegisterModname(string.rep('x',250)..et.FindSelf())";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==16);G_NITMOD_LuaStatus(3);
 assert(strlen(statusText)>4096 && strstr(statusText,"xxxxxxxx15 "));
 G_NITMOD_LuaShutdown(0);assert(G_NITMOD_LuaCount()==0);
 modules="test.lua";
 source="assert(_VERSION=='Lua 5.1'); local f=assert(io.tmpfile()); assert(f:write('first\\nsecond\\0tail')); assert(f:flush()); assert(f:seek('set',0)==0); assert(f:read('*l')=='first'); assert(f:read('*a')=='second\\0tail'); assert(f:close()); assert(io.type(f)=='closed file'); local name=os.tmpname(); f=assert(io.open(name,'wb')); assert(f:write('a\\nb\\n')); assert(f:close()); local count=0; for line in io.lines(name) do count=count+1 end; assert(count==2); assert(os.rename(name,name..'.moved')); assert(os.remove(name..'.moved')); local ok,err=pcall(io.popen,'echo unused'); assert(not ok and string.find(err,'not supported',1,true)); local fn,msg,kind=package.loadlib('unavailable.so','luaopen_unavailable'); assert(fn==nil and kind=='absent' and string.find(msg,'dynamic libraries not enabled',1,true)); assert(os.execute()==1); et.trap_Cvar_Set('frame','1')";
 { int before=frames;G_NITMOD_LuaInit(0,0,0);if(G_NITMOD_LuaCount()!=1 || frames!=before+1) fprintf(stderr,"Standard library test: %s\n",fixtureLastLog);assert(G_NITMOD_LuaCount()==1 && frames==before+1);G_NITMOD_LuaShutdown(0); }
 modules="first.lua;second.lua";
 source="local id=et.FindSelf(); function et_ShutdownGame(r) assert(r==1); et.trap_Cvar_Set('lifecycle_order','S'..id) end; function et_Quit() et.trap_Cvar_Set('lifecycle_order','Q'..id) end";
 lifecycleOrder[0]=0;G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==2);
 G_NITMOD_LuaShutdown(1);assert(!strcmp(lifecycleOrder,"S0S1Q0Q1"));
 lifecycleOrder[0]=0;G_NITMOD_LuaInit(0,0,0);G_NITMOD_LuaUnload();
 assert(!strcmp(lifecycleOrder,"Q0Q1") && G_NITMOD_LuaCount()==0);
 G_NITMOD_LuaUnload();assert(!strcmp(lifecycleOrder,"Q0Q1"));
 modules="test.lua";source="function et_ConsoleCommand() et.G_LogPrint('literal %s %n 100%');return 1 end";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);
 assert(G_NITMOD_LuaCommand(-1,"log"));
 assert(!strcmp(fixtureLastLog,"literal %s %n 100%"));G_NITMOD_LuaShutdown(0);
 childSource="#!/usr/bin/lua\nreturn 42,'child'";
 source="local f=assert(loadfile('child.lua'));assert(debug.getinfo(f).source=='@child.lua');assert(f()==42);assert(dofile('child.lua')==42);assert(require('child')==42)";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 childSource="#!/usr/bin/lua\nerror('line-two')";
 source="local f=assert(loadfile('child.lua'));local ok,err=pcall(f);assert(not ok and string.find(err,'child.lua:2:',1,true));local ok,err=pcall(dofile,'child.lua');assert(not ok and string.find(err,'child.lua:2:',1,true))";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 childSource="#!/usr/bin/lua\n\ninvalid !";
 source="local f,err=loadfile('child.lua');assert(f==nil and string.find(err,'child.lua:3:',1,true));local ok,err=pcall(require,'child');assert(not ok and string.find(err,'child.lua:3:',1,true))";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 childSource="#!/usr/bin/lua";
 source="assert(assert(loadfile('child.lua'))()==nil)";
 G_NITMOD_LuaInit(0,0,0);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 source="for _,prefix in ipairs({'','#!/usr/bin/lua\\n'}) do local data=prefix..string.dump(function() return 42 end);local f=et.trap_FS_FOpenFile('fixture.dat',et.FS_WRITE);et.trap_FS_Write(data,#data,f);et.trap_FS_FCloseFile(f);assert(assert(loadfile('fixture.dat'))()==42) end";
 G_NITMOD_LuaInit(0,0,0);if(G_NITMOD_LuaCount()!=1) fprintf(stderr,"%s\n",fixtureLastLog);assert(G_NITMOD_LuaCount()==1);G_NITMOD_LuaShutdown(0);
 puts("Lua real VM: startup FindSelf, lifecycle, cvars, ACL, syntax/runtime failures and repeated hook error recovery: PASS"); return 0;
}
