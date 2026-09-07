#include "nitmod_xp_snapshot.h"
#include "g_nitmod_admin.h"
#include "g_local.h"
#include "nitmod_lua_mod.h"
#include "nitmod_lua_events.h"
#include "nitmod_entity_ids.h"
#include "nitmod_weapon_ids.h"
#include "nitmod_powerup_ids.h"
#include "g_nitmod_config.h"
#include "g_nitmod_lua.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_sha1.h"
#include "../lua51/lua.h"
#include "../lua51/lauxlib.h"
#include "../lua51/lualib.h"
static lua_State *states[16];
static int count;
static unsigned int vmErrors[16];
static char modnames[16][256],signatures[16][41],filenames[16][MAX_QPATH];
static void HookError(lua_State *L,const char *hook) {
    int i; const char *error=lua_tostring(L,-1);
    for(i=0;i<count;++i) if(states[i]==L) { ++vmErrors[i]; break; }
    G_LogPrintf("Lua API: %s: %s\n",hook,error?error:"non-string error");
}
int G_NITMOD_LuaCount(void) { return count; }
static int Print(lua_State *L) { G_Printf("%s",luaL_checkstring(L,1)); return 0; }
static int CvarGet(lua_State *L) {
    char value[MAX_CVAR_VALUE_STRING];
    trap_Cvar_VariableStringBuffer(luaL_checkstring(L,1),value,sizeof(value)); lua_pushstring(L,value); return 1;
}
static int CvarSet(lua_State *L) { trap_Cvar_Set(luaL_checkstring(L,1),luaL_checkstring(L,2));return 0; }
static int FindSelf(lua_State *L) {
    int i; for(i=0;i<count;++i) if(states[i]==L) { lua_pushinteger(L,i);return 1; }
    lua_pushnil(L);return 1;
}
static int Argc(lua_State *L) { lua_pushinteger(L,trap_Argc()); return 1; }
static int Argv(lua_State *L) { char value[MAX_STRING_CHARS]; trap_Argv(luaL_checkinteger(L,1),value,sizeof(value)); lua_pushstring(L,value); return 1; }
static int RegisterName(lua_State *L) {
    const char *name=luaL_checkstring(L,1); int i;
    for(i=0;i<count;++i) if(states[i]==L) { Q_strncpyz(modnames[i],name,sizeof(modnames[i])); break; }
    return 0;
}
static int FindMod(lua_State *L) {
    int id=luaL_checkinteger(L,1);
    if(id<0 || id>=count || !states[id]) { lua_pushnil(L); lua_pushnil(L); }
    else { lua_pushstring(L,modnames[id]); lua_pushstring(L,signatures[id]); }
    return 2;
}
static int IPCSend(lua_State *L) {
    int destination=luaL_checkinteger(L,1),sender,top,ok=0;
    const char *message=luaL_checkstring(L,2); lua_State *target;
    if(destination<0 || destination>=count || !(target=states[destination]) || vmErrors[destination]) {
        lua_pushinteger(L,0); return 1;
    }
    for(sender=0;sender<count && states[sender]!=L;++sender) {}
    top=lua_gettop(target); lua_getglobal(target,"et_IPCReceive");
    if(lua_isfunction(target,-1)) {
        if(sender<count) lua_pushinteger(target,sender); else lua_pushnil(target);
        lua_pushstring(target,message);
        if(lua_pcall(target,2,0,0)) {
            HookError(target,"et.IPCSend");
        } else ok=1;
    }
    lua_settop(target,top); lua_pushinteger(L,ok); return 1;
}
static int ClientIndex(lua_State *L,int argument,int broadcast) {
    int n=luaL_checkinteger(L,argument);
    luaL_argcheck(L,n>=(broadcast?-1:0) && n<MAX_CLIENTS,argument,"invalid client index"); return n;
}
static int ConfigIndex(lua_State *L) {
    int n=luaL_checkinteger(L,1); luaL_argcheck(L,n>=0 && n<MAX_CONFIGSTRINGS,1,"invalid configstring index"); return n;
}
static int GetUserinfo(lua_State *L) { char value[MAX_INFO_STRING]; trap_GetUserinfo(ClientIndex(L,1,0),value,sizeof(value)); lua_pushstring(L,value); return 1; }
static int SetUserinfo(lua_State *L) { int n=ClientIndex(L,1,0); trap_SetUserinfo(n,luaL_checkstring(L,2)); return 0; }
static int UserinfoChanged(lua_State *L) { ClientUserinfoChanged(ClientIndex(L,1,0)); return 0; }
static int GetConfigstring(lua_State *L) { char value[MAX_STRING_CHARS]; trap_GetConfigstring(ConfigIndex(L),value,sizeof(value)); lua_pushstring(L,value); return 1; }
static int SetConfigstring(lua_State *L) { int n=ConfigIndex(L); trap_SetConfigstring(n,luaL_checkstring(L,2)); return 0; }
static int SendServer(lua_State *L) { int n=ClientIndex(L,1,1); trap_SendServerCommand(n,luaL_checkstring(L,2)); return 0; }
static int SendConsole(lua_State *L) { int when=luaL_checkinteger(L,1); luaL_argcheck(L,when>=EXEC_NOW && when<=EXEC_APPEND,1,"invalid execution mode"); trap_SendConsoleCommand(when,luaL_checkstring(L,2)); return 0; }
static int DropClient(lua_State *L) { int n=ClientIndex(L,1,0); const char *reason=luaL_checkstring(L,2); int ban=luaL_optinteger(L,3,trap_Cvar_VariableIntegerValue("g_defaultBanTime")); trap_DropClient(n,reason,ban); return 0; }
static int Milliseconds(lua_State *L) { lua_pushinteger(L,trap_Milliseconds()); return 1; }
static int LogPrint(lua_State *L) { G_LogPrintf("%s",luaL_checkstring(L,1)); return 0; }
static int CleanStr(lua_State *L) { char value[1024]; Q_strncpyz(value,luaL_checkstring(L,1),sizeof(value)); Q_CleanStr(value); lua_pushstring(L,value); return 1; }
static int InfoValue(lua_State *L) { const char *info=luaL_checkstring(L,1),*key=luaL_checkstring(L,2); lua_pushstring(L,Info_ValueForKey(info,key)); return 1; }
static int InfoSet(lua_State *L) { char info[1024]; const char *key=luaL_checkstring(L,2),*value=luaL_checkstring(L,3); Q_strncpyz(info,luaL_checkstring(L,1),sizeof(info)); Info_SetValueForKey(info,key,value); lua_pushstring(L,info); return 1; }
static int InfoRemove(lua_State *L) { char info[1024]; const char *key=luaL_checkstring(L,2); Q_strncpyz(info,luaL_checkstring(L,1),sizeof(info)); Info_RemoveKey(info,key); lua_pushstring(L,info); return 1; }
static int Concat(lua_State *L) { char value[MAX_STRING_CHARS],arg[MAX_STRING_CHARS]; int i=luaL_checkinteger(L,1); luaL_argcheck(L,i>=0,1,"invalid argument index"); value[0]=0; for(;i<trap_Argc();++i) { trap_Argv(i,arg,sizeof(arg)); if(*value) Q_strcat(value,sizeof(value)," "); Q_strcat(value,sizeof(value),arg); } lua_pushstring(L,value); return 1; }
static int FileOpen(lua_State *L) { fileHandle_t file=0; const char *path=luaL_checkstring(L,1); int mode=luaL_checkinteger(L,2),length; luaL_argcheck(L,mode>=FS_READ && mode<=FS_APPEND_SYNC,2,"invalid file mode"); length=trap_FS_FOpenFile(path,&file,mode); lua_pushinteger(L,file); lua_pushinteger(L,length); return 2; }
static int FileClose(lua_State *L) { int file=luaL_checkinteger(L,1); luaL_argcheck(L,file>0,1,"invalid file handle"); trap_FS_FCloseFile(file); return 0; }
static int FileRead(lua_State *L) { int file=luaL_checkinteger(L,1),length=luaL_checkinteger(L,2); char *bytes; luaL_argcheck(L,file>0,1,"invalid file handle"); luaL_argcheck(L,length>=0 && length<=1048576,2,"invalid read length"); bytes=lua_newuserdata(L,(size_t)length+1); memset(bytes,0,(size_t)length+1); trap_FS_Read(bytes,length,file); lua_pushstring(L,bytes); return 1; }
static int FileWrite(lua_State *L) { size_t available; const char *bytes=luaL_checklstring(L,1,&available); int length=luaL_checkinteger(L,2),file=luaL_checkinteger(L,3); luaL_argcheck(L,length>=0 && (size_t)length<=available,2,"write exceeds string length"); luaL_argcheck(L,file>0,3,"invalid file handle"); lua_pushinteger(L,trap_FS_Write(bytes,length,file)); return 1; }
static int FileRename(lua_State *L) { const char *from=luaL_checkstring(L,1),*to=luaL_checkstring(L,2); trap_FS_Rename(from,to); return 0; }
/* Compile through the engine VFS; successful calls leave the chunk on stack. */
static int LoadEngineFile(lua_State *L,const char *path) {
    fileHandle_t file=0; int length=trap_FS_FOpenFile(path,&file,FS_READ),result,offset=0; char *source;
    if(!file || length<0 || length>1048576) { if(file) trap_FS_FCloseFile(file); lua_pushfstring(L,"cannot read %s through engine VFS",path); return LUA_ERRFILE; }
    source=malloc((size_t)length+1);
    if(!source) { trap_FS_FCloseFile(file); lua_pushliteral(L,"out of memory loading engine file"); return LUA_ERRMEM; }
    trap_FS_Read(source,length,file); trap_FS_FCloseFile(file); source[length]=0;
    /* Match Lua 5.1 luaL_loadfile: ignore an interpreter line, retaining its
     * newline for text line numbers, but never prepend it to binary chunks. */
    if(length && source[0]=='#') {
        while(offset<length && source[offset]!='\n') ++offset;
        if(offset==length) { source[0]='\n';offset=0;length=1; }
        else if(offset+1<length && source[offset+1]==LUA_SIGNATURE[0]) ++offset;
    }
    lua_pushfstring(L,"@%s",path);
    result=luaL_loadbuffer(L,source+offset,length-offset,lua_tostring(L,-1));
    lua_remove(L,-2);free(source);return result;
}
static int LoadFile(lua_State *L) {
    const char *path=luaL_checkstring(L,1);
    if(LoadEngineFile(L,path)) { lua_pushnil(L); lua_insert(L,-2); return 2; }
    return 1;
}
static int DoFile(lua_State *L) {
    const char *path=luaL_checkstring(L,1); int top=lua_gettop(L);
    if(LoadEngineFile(L,path)) return lua_error(L);
    lua_call(L,0,LUA_MULTRET); return lua_gettop(L)-top;
}
static int ModuleLoader(lua_State *L) {
    char module[MAX_QPATH],path[MAX_QPATH]; const char *name=luaL_checkstring(L,1),*pattern,*end; int i;
    if(strlen(name)>=sizeof(module)) return luaL_error(L,"module name too long");
    Q_strncpyz(module,name,sizeof(module)); for(i=0;module[i];++i) if(module[i]=='.') module[i]='/';
    lua_getglobal(L,"package"); lua_getfield(L,-1,"path"); pattern=lua_tostring(L,-1);
    if(!pattern) return luaL_error(L,"package.path must be a string");
    while(*pattern) {
        size_t used=0; end=strchr(pattern,';'); if(!end) end=pattern+strlen(pattern);
        while(pattern<end) {
            const char *part=*pattern=='?'?module:NULL; size_t size=part?strlen(part):1;
            if(used+size>=sizeof(path)) return luaL_error(L,"module path too long");
            if(part) memcpy(path+used,part,size); else path[used]=*pattern;
            used+=size; ++pattern;
        }
        path[used]=0;
        if(used) {
            int rc=LoadEngineFile(L,path);
            if(!rc) return 1;
            if(rc!=LUA_ERRFILE) return lua_error(L);
            lua_pop(L,1);
        }
        if(*pattern==';') ++pattern;
    }
    lua_pushfstring(L,"\n\tno engine VFS module '%s'",name); return 1;
}
static void InstallEngineLoader(lua_State *L) {
    lua_pushcfunction(L,LoadFile); lua_setglobal(L,"loadfile");
    lua_pushcfunction(L,DoFile); lua_setglobal(L,"dofile");
    lua_pushliteral(L,"/");lua_setglobal(L,"LUA_DIRSEP");
    lua_pushliteral(L,"?.lua;lualibs/?.lua");lua_setglobal(L,"LUA_PATH");
    lua_getglobal(L,"package");lua_pushliteral(L,"?.lua;lualibs/?.lua");lua_setfield(L,-2,"path"); lua_getfield(L,-1,"loaders");
    lua_pushcfunction(L,ModuleLoader); lua_rawseti(L,-2,2);
    lua_pop(L,2);
}
static gentity_t *Entity(lua_State *L,int arg) { int n=luaL_checkinteger(L,arg); luaL_argcheck(L,n>=0 && n<MAX_GENTITIES,arg,"invalid entity index"); return &g_entities[n]; }
static int AddEvent(lua_State *L) { gentity_t *ent=Entity(L,1); int event=luaL_checkinteger(L,2),parameter=luaL_checkinteger(L,3); event=NITMOD_LuaEventEncode(event); luaL_argcheck(L,event>=0,2,"unsupported original event"); G_AddEvent(ent,event,parameter); return 0; }
static int LinkEntity(lua_State *L) { trap_LinkEntity(Entity(L,1)); return 0; }
static int UnlinkEntity(lua_State *L) { trap_UnlinkEntity(Entity(L,1)); return 0; }
static int FreeEntity(lua_State *L) { G_FreeEntity(Entity(L,1)); return 0; }
static int SpawnEntity(lua_State *L) { gentity_t *ent=G_Spawn(); lua_pushinteger(L,ent-g_entities); return 1; }
static int AddSkill(lua_State *L) { gentity_t *ent=Entity(L,1); int skill=luaL_checkinteger(L,2); float value=luaL_checknumber(L,3); luaL_argcheck(L,skill>=0 && skill<SK_NUM_SKILLS,2,"invalid skill"); G_AddSkillPoints(ent,skill,value); return 0; }
static int LoseSkill(lua_State *L) { gentity_t *ent=Entity(L,1); int skill=luaL_checkinteger(L,2); float value=luaL_checknumber(L,3); luaL_argcheck(L,skill>=0 && skill<SK_NUM_SKILLS,2,"invalid skill"); G_LoseSkillPoints(ent,skill,value); return 0; }
static int ModelIndex(lua_State *L) { lua_pushinteger(L,G_ModelIndex((char *)luaL_checkstring(L,1))); return 1; }
static int SoundIndex(lua_State *L) { lua_pushinteger(L,G_SoundIndex(luaL_checkstring(L,1))); return 1; }
static int Sound(lua_State *L) { gentity_t *ent=Entity(L,1); int sound=luaL_checkinteger(L,2); G_Sound(ent,sound); return 0; }
typedef struct { const char *name; int type,flags; size_t offset,size; } luaField_t;
static const luaField_t luaFields[]={
#include "nitmod_lua_fields.h"
};
static const luaField_t *Field(lua_State *L,gentity_t *ent) {
    const char *name=luaL_checkstring(L,2); int i,pass;
    for(pass=0;pass<2;++pass) for(i=0;i<(int)(sizeof(luaFields)/sizeof(luaFields[0]));++i) {
        const luaField_t *f=&luaFields[i];
        if((pass==0 && (!(f->flags&2) || !ent->client)) || (pass==1 && !(f->flags&1))) continue;
        if(!Q_stricmp(name,f->name)) return f;
    }
    luaL_error(L,"invalid or unavailable gentity field '%s'",name); return NULL;
}
static void PushVector(lua_State *L,const float *v) { int i; lua_createtable(L,3,0); for(i=0;i<3;++i) { lua_pushnumber(L,v[i]); lua_rawseti(L,-2,i+1); } }
static void ReadVector(lua_State *L,int index,float *out) { float values[3]; int i; luaL_checktype(L,index,LUA_TTABLE); for(i=0;i<3;++i) { lua_rawgeti(L,index,i+1); values[i]=luaL_checknumber(L,-1); lua_pop(L,1); } memcpy(out,values,sizeof(values)); }
static int IsWeaponField(const luaField_t *f) {
    return !strcmp(f->name,"s.weapon") || !strcmp(f->name,"sess.playerWeapon") ||
        !strcmp(f->name,"sess.playerWeapon2") || !strcmp(f->name,"sess.latchPlayerWeapon") ||
        !strcmp(f->name,"sess.latchPlayerWeapon2");
}
static int IsDamageField(const luaField_t *f) {
    return !strcmp(f->name,"methodOfDeath") || !strcmp(f->name,"splashMethodOfDeath") ||
        !strcmp(f->name,"deathType");
}
static int LuaEntityType(const gentity_t *ent) {
    int i,event,native=ent->s.eType;
    if(native==ET_EVENTS+EV_NITMOD_LUA_FIRST) {
        event=ent->s.event & ~EV_EVENT_BITS;
        i=NITMOD_LuaEventDecode(event);
        return event==0?59:i>=0?59+i:-1;
    }
    if(native<ET_EVENTS) return NITMOD_OriginalEntityType(native);
    event=native-ET_EVENTS;
    i=NITMOD_LuaEventDecode(event);
    if(i>=0) return 59+i;
    if(event==0) return 59;
    /* Existing native entities can be inspected by original Lua scripts. */
    for(i=1;i<=106;++i) if(NITMOD_LuaEventServerDispatch(NITMOD_LuaEventEncode(i))==event) return 59+i;
    return -1;
}
static int NativeLuaEntityType(gentity_t *ent,int original) {
    if(original>=59 && original<=165) {
        ent->s.event=NITMOD_LuaEventEncode(original-59);
        return ET_EVENTS+EV_NITMOD_LUA_FIRST;
    }
    {
        int native=NITMOD_NativeEntityType(original);
        if(native>=0 && ent->s.eType==ET_EVENTS+EV_NITMOD_LUA_FIRST) ent->s.event=0;
        return native;
    }
}
static int *PersistantFieldSlot(gentity_t *ent,const luaField_t *f,int index) {
    static const int native[16]={PERS_SCORE,-1,-1,-1,PERS_KILLED,-1,-1,PERS_TEAM,
        PERS_SPAWN_COUNT,PERS_RESPAWNS_LEFT,PERS_RESPAWNS_PENALTY,PERS_REVIVE_COUNT,
        PERS_HWEAPON_USE,-1,-1,-1};
    if(strcmp(f->name,"ps.persistant")) return NULL;
    return native[index]<0?&ent->client->nitmodLuaPersistant[index]:&ent->client->ps.persistant[native[index]];
}
static int *PowerupFieldSlot(gentity_t *ent,const luaField_t *f,int index) {
    if(strcmp(f->name,"ps.powerups")) return NULL;
    return &ent->client->ps.powerups[nitmodPowerupIds[index]];
}
static int *AmmoFieldSlot(gentity_t *ent,const luaField_t *f,int index) {
    int clip=!strcmp(f->name,"ps.ammoclip");
    if(!clip && strcmp(f->name,"ps.ammo")) return NULL;
    if(index>=52) return &ent->client->nitmodLuaUnusedAmmo[clip][index-52];
    return &(clip?ent->client->ps.ammoclip:ent->client->ps.ammo)[NITMOD_NativeWeaponId(index)];
}
static int FieldGet(lua_State *L) {
    gentity_t *ent=Entity(L,1); const luaField_t *f;
    f=Field(L,ent);
    char *p=(char *)((f->flags&1)?(void *)ent:(void *)ent->client)+f->offset; int i,index;
    switch(f->type) {
    case 0: lua_pushinteger(L,!strcmp(f->name,"s.powerups")?(int)(NITMOD_OriginalPowerupBits((unsigned int)ent->s.powerups)):!strcmp(f->name,"s.eType")?LuaEntityType(ent):IsWeaponField(f)?NITMOD_OriginalWeaponId(*(int *)p):
            IsDamageField(f)?NITMOD_LuaMeansOfDeath(*(int *)p):*(int *)p); break;
    case 1:
        if(!strcmp(f->name,"item")) lua_pushstring(L,ent->item?ent->item->classname:NULL);
        else lua_pushstring(L,(f->flags&4) || f->size>sizeof(char *)?p:*(char **)p); break;
    case 2: lua_pushnumber(L,*(float *)p); break;
    case 3: lua_pushinteger(L,*(gentity_t **)p?*(gentity_t **)p-g_entities:-1); break;
    case 4: PushVector(L,(float *)p); break;
    case 5: case 7:
        index=luaL_optinteger(L,3,0); luaL_argcheck(L,index>=0 && index<(int)(f->size/4),3,"array index out of range");
        if(f->type==5) {
            int *ammo=AmmoFieldSlot(ent,f,index);
            if(!ammo) ammo=PersistantFieldSlot(ent,f,index);
            if(!ammo) ammo=PowerupFieldSlot(ent,f,index);
            lua_pushinteger(L,ammo?*ammo:((int *)p)[index]);
        } else lua_pushnumber(L,((float *)p)[index]); break;
    case 6: {
        trajectory_t *t=(trajectory_t *)p; lua_newtable(L);
        lua_pushinteger(L,t->trType);lua_setfield(L,-2,"trType");lua_pushinteger(L,t->trTime);lua_setfield(L,-2,"trTime");lua_pushinteger(L,t->trDuration);lua_setfield(L,-2,"trDuration");
        PushVector(L,t->trBase);lua_setfield(L,-2,"trBase");PushVector(L,t->trDelta);lua_setfield(L,-2,"trDelta");break;
    }
    case 8:
        /* Original omits ET's smoke-screen row. Original 26 is the sentinel. */
        index=luaL_optinteger(L,3,0); luaL_argcheck(L,index>=0 && index<=26,3,"weapon index out of range");
        if(index>=15) ++index;
        lua_createtable(L,5,0); for(i=0;i<5;++i) { lua_pushinteger(L,((unsigned int *)(p+index*sizeof(weapon_stat_t)))[i]);lua_rawseti(L,-2,i+1); } break;
    default:return luaL_error(L,"unsupported field type");
    } return 1;
}
static int FieldSet(lua_State *L) {
    gentity_t *ent=Entity(L,1); const luaField_t *f=Field(L,ent); char *p; int index;
    if(f->flags&8) return luaL_error(L,"field '%s' is read only",f->name);
    p=(char *)((f->flags&1)?(void *)ent:(void *)ent->client)+f->offset;
    switch(f->type) {
    case 0:
        index=luaL_checkinteger(L,3);
        if(IsWeaponField(f)) {
            index=NITMOD_NativeWeaponId(index);
            luaL_argcheck(L,index>=0,3,"unsupported original weapon");
        }
        if(!strcmp(f->name,"s.eType")) {
            index=NativeLuaEntityType(ent,index);
            luaL_argcheck(L,index>=0,3,"unsupported original entity type");
        }
        if(IsDamageField(f)) {
            index=NITMOD_NativeMeansOfDeath(index);
            luaL_argcheck(L,index>=0,3,"unsupported original means of death");
        }
        *(int *)p=index;break;
    case 1: {
        const char *value=luaL_checkstring(L,3);
        if(!strcmp(f->name,"item")) return luaL_error(L,"item pointer is not a writable string");
        if((f->flags&4) || f->size>sizeof(char *)) Q_strncpyz(p,value,f->size);
        else *(char **)p=G_NewString(value); break;
    }
    case 2: *(float *)p=luaL_checknumber(L,3);break;
    case 3: index=luaL_checkinteger(L,3); luaL_argcheck(L,index>=-1 && index<MAX_GENTITIES,3,"invalid entity index"); *(gentity_t **)p=index<0?NULL:g_entities+index;break;
    case 4: ReadVector(L,3,(float *)p);break;
    case 5: case 7:
        index=luaL_checkinteger(L,3);luaL_argcheck(L,index>=0 && index<(int)(f->size/4),3,"array index out of range");
        if(f->type==5) {
            int *ammo=AmmoFieldSlot(ent,f,index);
            if(!ammo) ammo=PersistantFieldSlot(ent,f,index);
            if(!ammo) ammo=PowerupFieldSlot(ent,f,index);
            *(ammo?ammo:&((int *)p)[index])=luaL_checkinteger(L,4);
        } else ((float *)p)[index]=luaL_checknumber(L,4);break;
    case 6: {
        trajectory_t t; luaL_checktype(L,3,LUA_TTABLE);
        lua_getfield(L,3,"trType");t.trType=luaL_checkinteger(L,-1);lua_pop(L,1);
        lua_getfield(L,3,"trTime");t.trTime=luaL_checkinteger(L,-1);lua_pop(L,1);
        lua_getfield(L,3,"trDuration");t.trDuration=luaL_checkinteger(L,-1);lua_pop(L,1);
        lua_getfield(L,3,"trBase");ReadVector(L,lua_gettop(L),t.trBase);lua_pop(L,1);
        lua_getfield(L,3,"trDelta");ReadVector(L,lua_gettop(L),t.trDelta);lua_pop(L,1);
        memcpy(p,&t,sizeof(t));break;
    }
    default:return luaL_error(L,"unsupported writable field type");
    } return 0;
}
static int Damage(lua_State *L) {
    gentity_t *target=Entity(L,1),*inflictor=Entity(L,2),*attacker=Entity(L,3);
    int amount=luaL_checkinteger(L,4),flags=luaL_checkinteger(L,5),mod=luaL_checkinteger(L,6);
    mod=NITMOD_NativeMeansOfDeath(mod);
    luaL_argcheck(L,mod>=0,6,"unsupported original means of death");
    G_Damage(target,inflictor,attacker,NULL,NULL,amount,flags,mod); return 0;
}
static int TempEntity(lua_State *L) { vec3_t origin; int event; gentity_t *ent; ReadVector(L,1,origin); event=NITMOD_LuaEventEncode(luaL_checkinteger(L,2)); luaL_argcheck(L,event>=0,2,"unsupported original event"); ent=G_TempEntity(origin,EV_NITMOD_LUA_FIRST); ent->s.event=event; lua_pushinteger(L,ent-g_entities); return 1; }
static int GlobalSound(lua_State *L) { G_globalSound((char *)luaL_checkstring(L,1)); return 0; }
static int PlayerCount(lua_State *L) {
    int team=luaL_optinteger(L,1,-1),i,total=0; luaL_argcheck(L,team<=TEAM_SPECTATOR,1,"invalid team index");
    for(i=0;i<level.maxclients && i<MAX_CLIENTS;++i) if(g_entities[i].inuse && g_entities[i].client) {
        gclient_t *client=g_entities[i].client;
        if(team==0?client->pers.connected==CON_CONNECTED:(int)client->sess.sessionTeam==team) ++total;
    }
    lua_pushinteger(L,total); return 1;
}
extern qboolean G_NITMOD_ClientIsFlooding(gentity_t *ent);
extern void G_Say(gentity_t *ent,gentity_t *target,int mode,const char *text);
extern qboolean G_EntitiesFree(void);
static int Flooding(lua_State *L) { lua_pushinteger(L,G_NITMOD_ClientIsFlooding(&g_entities[ClientIndex(L,1,0)]));return 1; }
static int Say(lua_State *L) { int n=ClientIndex(L,1,0),mode=luaL_checkinteger(L,2); const char *text=luaL_checkstring(L,3); if(!g_entities[n].client) return luaL_error(L,"entity is not a client"); G_Say(&g_entities[n],NULL,mode,text);return 0; }
static int EntitiesFree(lua_State *L) { G_EntitiesFree(); return 0; }
static int AdminLevelName(lua_State *L) { int n=luaL_optinteger(L,1,-1); luaL_argcheck(L,n<MAX_CLIENTS,1,"invalid client index"); lua_pushstring(L,G_NITMOD_AdminLevelName(n)); return 1; }
static int ClientNumber(lua_State *L) {
    const char *input=luaL_checkstring(L,1); char *end,name[64],needle[64]; long number=strtol(input,&end,10); int i,found=-1;
    if(*input && !*end) { if(number>=0 && number<MAX_CLIENTS && g_entities[number].client && g_entities[number].client->pers.connected!=CON_DISCONNECTED) found=number; }
    else {
        Q_strncpyz(needle,input,sizeof(needle));Q_CleanStr(needle);Q_strlwr(needle);
        for(i=0;*needle && i<MAX_CLIENTS;++i) if(g_entities[i].client && g_entities[i].client->pers.connected!=CON_DISCONNECTED) {
            Q_strncpyz(name,g_entities[i].client->pers.netname,sizeof(name));Q_CleanStr(name);Q_strlwr(name);
            if(strstr(name,needle)) { if(found!=-1) { found=-1;break; } found=i; }
        }
    }
    lua_pushinteger(L,found);return 1;
}
static int XPSet(lua_State *L) {
    int n=ClientIndex(L,1,0),xp=luaL_checkinteger(L,2),skill=luaL_checkinteger(L,3);
    int add=lua_isboolean(L,4)?lua_toboolean(L,4):luaL_checkinteger(L,4); gentity_t *ent=&g_entities[n]; gclient_t *client=ent->client;
    luaL_argcheck(L,ent->inuse && client,1,"entity is not an active client");
    luaL_argcheck(L,xp>=0,2,"negative XP is not allowed");luaL_argcheck(L,skill>=0 && skill<SK_NUM_SKILLS,3,"invalid skill");
    if(add) { client->sess.skillpoints[skill]+=xp; client->sess.startxptotal+=xp; }
    else { client->sess.startxptotal+=xp-client->sess.skillpoints[skill]; client->sess.skillpoints[skill]=xp; }
    NITMOD_SetSnapshotXP(&client->ps,NITMOD_XPInteger(client->sess.startxptotal));
    G_CalcRank(client); BG_PlayerStateToEntityState(&client->ps,&ent->s,qtrue);
    /* The original binding returns its fourth argument without pushing a value. */
    lua_pushvalue(L,4); return 1;
}
typedef struct { const char *name; int type; size_t offset; } luaSpawnField_t;
static const luaSpawnField_t spawnFields[]={
#include "nitmod_lua_spawn_fields.h"
};
static const luaSpawnField_t *SpawnField(lua_State *L) {
    const char *name=luaL_checkstring(L,2); int i;
    for(i=0;i<(int)(sizeof(spawnFields)/sizeof(spawnFields[0]));++i) if(!Q_stricmp(name,spawnFields[i].name)) return &spawnFields[i];
    luaL_error(L,"invalid or unavailable spawn field '%s'",name); return NULL;
}
static int SpawnGet(lua_State *L) {
    gentity_t *ent=Entity(L,1);const luaSpawnField_t *f=SpawnField(L);char *p=(char *)ent+f->offset;
    if(!ent->inuse) { lua_pushnil(L);return 1; }
    switch(f->type) {
    case 0:lua_pushinteger(L,*(int *)p);break;
    case 1:lua_pushnumber(L,*(float *)p);break;
    case 2:case 3:lua_pushstring(L,*(char **)p);break;
    case 4:case 5:PushVector(L,(float *)p);break;
    default:lua_pushnil(L);break;
    } return 1;
}
static int SpawnSet(lua_State *L) {
    gentity_t *ent=Entity(L,1);const luaSpawnField_t *f=SpawnField(L);char *p=(char *)ent+f->offset;
    if(!ent->inuse) { lua_pushnil(L);return 1; }
    switch(f->type) {
    case 0:*(int *)p=luaL_checkinteger(L,3);break;
    case 1:*(float *)p=luaL_checknumber(L,3);break;
    case 2:case 3:*(char **)p=G_NewString(luaL_checkstring(L,3));break;
    case 4:case 5:ReadVector(L,3,(float *)p);break;
    case 6:*(gentity_t **)p=Entity(L,3);break;
    default:lua_pushnil(L);return 1;
    } lua_pushvalue(L,3);return 1;
}
static int ClientSound(lua_State *L) {
    int n=ClientIndex(L,1,0),sound=luaL_checkinteger(L,2);gentity_t *event;vec3_t origin={0,0,0};
    if(!g_entities[n].client) return 0;
    event=G_TempEntity(origin,EV_GLOBAL_CLIENT_SOUND);event->r.svFlags=SVF_SINGLECLIENT;
    event->s.teamNum=n;event->s.eventParm=sound;event->r.singleClient=n;return 0;
}
static int ShrubLevel(lua_State *L) { int n=luaL_optinteger(L,1,-1); luaL_argcheck(L,n<MAX_CLIENTS,1,"invalid client index");lua_pushinteger(L,G_NITMOD_AdminLevel(n));return 1; }
static int ShrubPermission(lua_State *L) { int n=luaL_optinteger(L,1,-1);const char *permission=luaL_checkstring(L,2);luaL_argcheck(L,n<MAX_CLIENTS,1,"invalid client index");lua_pushinteger(L,G_NITMOD_AdminAllowed(n,permission));return 1; }
static const luaL_Reg bindings[]={{"G_Print",Print},{"trap_Cvar_Get",CvarGet},{"trap_Cvar_Set",CvarSet},
    {"trap_Argc",Argc},{"trap_Argv",Argv},{"FindSelf",FindSelf},{"RegisterModname",RegisterName},{"FindMod",FindMod},{"IPCSend",IPCSend},{"trap_GetUserinfo",GetUserinfo},{"trap_SetUserinfo",SetUserinfo},{"ClientUserinfoChanged",UserinfoChanged},{"trap_GetConfigstring",GetConfigstring},{"trap_SetConfigstring",SetConfigstring},{"trap_SendServerCommand",SendServer},{"trap_SendConsoleCommand",SendConsole},{"trap_DropClient",DropClient},{"trap_Milliseconds",Milliseconds},{"G_LogPrint",LogPrint},{"Q_CleanStr",CleanStr},{"Info_ValueForKey",InfoValue},{"Info_SetValueForKey",InfoSet},{"Info_RemoveKey",InfoRemove},{"ConcatArgs",Concat},{"trap_FS_FOpenFile",FileOpen},{"trap_FS_FCloseFile",FileClose},{"trap_FS_Read",FileRead},{"trap_FS_Write",FileWrite},{"trap_FS_Rename",FileRename},{"G_AddEvent",AddEvent},{"trap_LinkEntity",LinkEntity},{"trap_UnlinkEntity",UnlinkEntity},{"G_FreeEntity",FreeEntity},{"G_Spawn",SpawnEntity},{"G_AddSkillPoints",AddSkill},{"G_LoseSkillPoints",LoseSkill},{"G_ModelIndex",ModelIndex},{"G_SoundIndex",SoundIndex},{"G_Sound",Sound},{"gentity_get",FieldGet},{"gentity_set",FieldSet},{"G_Damage",Damage},{"G_TempEntity",TempEntity},{"G_globalSound",GlobalSound},{"G_PlayerCount",PlayerCount},{"ClientIsFlooding",Flooding},{"G_Say",Say},{"G_EntitiesFree",EntitiesFree},{"G_AdminLevelName",AdminLevelName},{"ClientNumberFromString",ClientNumber},{"G_XP_Set",XPSet},{"G_GetSpawnVar",SpawnGet},{"G_SetSpawnVar",SpawnSet},{"G_ClientSound",ClientSound},{"G_shrubbot_level",ShrubLevel},{"G_shrubbot_permission",ShrubPermission},{NULL,NULL}};
static void Call(lua_State *L,const char *hook,int n,const int *args) {
    int top=lua_gettop(L),i;
    lua_getglobal(L,hook);
    if(lua_isfunction(L,-1)) {
        for(i=0;i<n;++i) lua_pushinteger(L,args[i]);
        if(lua_pcall(L,n,0,0)) HookError(L,hook);
    }
    lua_settop(L,top);
}
int G_NITMOD_LuaSkill(const char *hook,int client,int skill) {
    int i;
    for(i=0;i<count;++i) {
        lua_State *L=states[i]; int top=lua_gettop(L),handled=0;
        lua_getglobal(L,hook);
        if(lua_isfunction(L,-1)) {
            lua_pushinteger(L,client); lua_pushinteger(L,skill);
            if(lua_pcall(L,2,1,0)) HookError(L,hook);
            else handled=lua_isnumber(L,-1) && lua_tointeger(L,-1)==-1;
        }
        lua_settop(L,top); if(handled) return 1;
    }
    return 0;
}
int G_NITMOD_LuaObituary(int victim,int killer,int mod) {
    int i;
    for(i=0;i<count;++i) {
        lua_State *L=states[i];int top=lua_gettop(L),handled=0;char text[1024];
        lua_getglobal(L,"et_Obituary");
        if(lua_isfunction(L,-1)) {
            lua_pushinteger(L,victim);lua_pushinteger(L,killer);lua_pushinteger(L,NITMOD_LuaMeansOfDeath(mod));
            if(lua_pcall(L,3,1,0)) HookError(L,"et_Obituary");
            else if(lua_isstring(L,-1)) { char *p; Q_strncpyz(text,lua_tostring(L,-1),sizeof(text)); for(p=text;*p;++p) if(*p=='"' || *p=='\\' || *p=='\n' || *p=='\r') *p=' '; handled=1; }
        }
        lua_settop(L,top);
        if(handled) { trap_SendServerCommand(-1,va("cpm \"%s\n\"",text));return 1; }
    }
    return 0;
}
void G_NITMOD_LuaSpawn(int client,int revived,int teamChange,int restoreHealth) {
    int args[4],i;args[0]=client;args[1]=revived;args[2]=teamChange;args[3]=restoreHealth;
    for(i=0;i<count;++i) Call(states[i],"et_ClientSpawn",4,args);
}
void G_NITMOD_LuaStatus(int client) {
    /* Original G_LuaStatus (ELF 0x109460): four fixed-width columns. Hook
     * errors remain in the server log; they are not part of this listing. */
    static const char separator[] = "-- ------------------------ ---------------------------------------- ------------------------\n";
    char text[sizeof(modnames)+sizeof(signatures)+sizeof(filenames)+16*96+512];
    int i;
    if(!count) Q_strncpyz(text,"Lua API: no scripts loaded.\n",sizeof(text));
    else {
        Com_sprintf(text,sizeof(text),"Lua API: showing lua information ( %d %s loaded )\n",count,count==1?"module":"modules");
        Q_strcat(text,sizeof(text),va("%-2s %-24s %-40s %-24s\n","VM","Modname","Signature","Filename"));
        Q_strcat(text,sizeof(text),separator);
        for(i=0;i<count;++i)
            Q_strcat(text,sizeof(text),va("%2d %-24s %-40s %-24s\n",i,modnames[i],signatures[i],filenames[i]));
        Q_strcat(text,sizeof(text),separator);
    }
    if(client<0) G_Printf("%s",text);else NITMOD_SendChunkedPrint(client,text);
}

void G_NITMOD_LuaPrint(const char *text) {
    static int printing; int i;
    if(printing) return; printing=1;
    for(i=0;i<count;++i) {
        lua_State *L=states[i]; int top;
        if(!L) continue; top=lua_gettop(L);lua_getglobal(L,"et_Print");
        if(lua_isfunction(L,-1)) { lua_pushstring(L,text);if(lua_pcall(L,1,0,0)) HookError(L,"et_Print"); }
        lua_settop(L,top);
    }
    printing=0;
}
void G_NITMOD_LuaClientEvent(const char *hook,int client) {
    int i; for(i=0;i<count;++i) Call(states[i],hook,1,&client);
}
char *G_NITMOD_LuaConnect(int client,int first,int bot) {
    static char reason[1024]; int i;
    for(i=0;i<count;++i) {
        lua_State *L=states[i]; int top=lua_gettop(L),deny=0;
        lua_getglobal(L,"et_ClientConnect");
        if(lua_isfunction(L,-1)) {
            lua_pushinteger(L,client); lua_pushinteger(L,first); lua_pushinteger(L,bot);
            if(lua_pcall(L,3,1,0)) HookError(L,"et_ClientConnect");
            else if(lua_isstring(L,-1)) { Q_strncpyz(reason,lua_tostring(L,-1),sizeof(reason)); deny=1; }
        }
        lua_settop(L,top); if(deny) return reason;
    }
    return NULL;
}
int G_NITMOD_LuaCommand(int client,const char *command) {
    int i; const char *hook=client<0?"et_ConsoleCommand":"et_ClientCommand";
    for(i=0;i<count;++i) {
        lua_State *L=states[i]; int top=lua_gettop(L),handled=0;
        lua_getglobal(L,hook);
        if(lua_isfunction(L,-1)) {
            if(client>=0) lua_pushinteger(L,client);
            lua_pushstring(L,command);
            if(lua_pcall(L,client<0?1:2,1,0)) HookError(L,hook);
            else handled=lua_isnumber(L,-1) && lua_tointeger(L,-1)==1;
        }
        lua_settop(L,top); if(handled) return 1;
    }
    return 0;
}
void G_NITMOD_LuaUnload(void) {
    int i;
    for(i=0;i<count;++i) {
        Call(states[i],"et_Quit",0,NULL);
        lua_close(states[i]);states[i]=NULL;
    }
    count=0;
}
void G_NITMOD_LuaShutdown(int restart) {
    int i;
    for(i=0;i<count;++i) Call(states[i],"et_ShutdownGame",1,&restart);
    G_NITMOD_LuaUnload();
}
void G_NITMOD_LuaReceivedGlobalStats(int client,const char *text) {
    int i;
    for(i=0;i<count;++i) {
        lua_State *L=states[i];int top=lua_gettop(L);
        lua_getglobal(L,"et_ReceivedGlobalStats");
        if(lua_isfunction(L,-1)) {
            lua_pushinteger(L,client);lua_pushstring(L,text);
            if(lua_pcall(L,2,0,0)) HookError(L,"et_ReceivedGlobalStats");
        }
        lua_settop(L,top);
    }
}
void G_NITMOD_LuaFrame(int time) { int i;for(i=0;i<count;++i) Call(states[i],"et_RunFrame",1,&time); }
void G_NITMOD_LuaInit(int time,int seed,int restart) {
    char modules[256],allowed[MAX_CVAR_VALUE_STRING],*p,*start;
    int args[3],i;
    if(count) G_NITMOD_LuaShutdown(restart);
    G_NITMOD_LegacyCvarString("lua_modules",modules,sizeof(modules),"");
    G_NITMOD_LegacyCvarString("lua_allowedModules",allowed,sizeof(allowed),"");
    start=modules;
    for(p=modules;;++p) {
        int last=*p==0;
        if(last || *p==' ' || *p==';' || *p==',') {
            fileHandle_t file=0; int length; char *source,hash[41];lua_State *L;
            *p=0;
            if(*start && count<16) {
                length=trap_FS_FOpenFile(start,&file,FS_READ);
                if(length>=0 && length<=1048576 && file) {
                    source=(char *)malloc((size_t)length+1);
                    if(source) {
                        trap_FS_Read(source,length,file);source[length]=0;
                        NITMOD_SHA1Text(source,hash); /* original hashes strlen, including binary-chunk quirk */
                        if(!*allowed || strstr(allowed,hash)) {
                            L=luaL_newstate();
                            if(L) {
                                Q_strncpyz(filenames[count],start,sizeof(filenames[count])); vmErrors[count]=0; modnames[count][0]=0; Q_strncpyz(signatures[count],hash,sizeof(signatures[count]));
                                states[count++]=L;
                                luaL_openlibs(L);InstallEngineLoader(L);luaL_register(L,"et",bindings);
                                lua_pushinteger(L,CS_PLAYERS);lua_setfield(L,-2,"CS_PLAYERS");
                                lua_pushinteger(L,0);lua_setfield(L,-2,"SAY_ALL");
                                lua_pushinteger(L,1);lua_setfield(L,-2,"SAY_TEAM");
                                lua_pushinteger(L,2);lua_setfield(L,-2,"SAY_BUDDY");
                                lua_pushinteger(L,3);lua_setfield(L,-2,"SAY_TEAMNL");
                                lua_pushliteral(L,"wasm32");lua_setfield(L,-2,"HOSTARCH");
                                lua_pushinteger(L,TEAM_AXIS);lua_setfield(L,-2,"TEAM_AXIS");
                                lua_pushinteger(L,TEAM_ALLIES);lua_setfield(L,-2,"TEAM_ALLIES");
                                lua_pushinteger(L,TEAM_SPECTATOR);lua_setfield(L,-2,"TEAM_SPECTATOR");
                                lua_pushinteger(L,FS_READ);lua_setfield(L,-2,"FS_READ");
                                lua_pushinteger(L,FS_WRITE);lua_setfield(L,-2,"FS_WRITE");
                                lua_pushinteger(L,FS_APPEND);lua_setfield(L,-2,"FS_APPEND");
                                lua_pushinteger(L,FS_APPEND_SYNC);lua_setfield(L,-2,"FS_APPEND_SYNC");
                                lua_pushinteger(L,EXEC_NOW);lua_setfield(L,-2,"EXEC_NOW");
                                lua_pushinteger(L,EXEC_INSERT);lua_setfield(L,-2,"EXEC_INSERT");
                                lua_pushinteger(L,EXEC_APPEND);lua_setfield(L,-2,"EXEC_APPEND");
                                lua_pushinteger(L,TEAM_FREE);lua_setfield(L,-2,"TEAM_FREE");
                                lua_pushinteger(L,MAX_CLIENTS);lua_setfield(L,-2,"MAX_CLIENTS");
                                lua_settop(L,0);
                                if(luaL_loadbuffer(L,source,length,start) || lua_pcall(L,0,0,0)) {
                                    G_LogPrintf("Lua API: %s: %s\n",start,lua_tostring(L,-1));
                                    Call(L,"et_Quit",0,NULL);states[--count]=NULL;lua_close(L);
                                } else { G_LogPrintf("Lua API: loaded %s [%s]\n",start,hash); }
                            }
                        } else G_LogPrintf("Lua API: %s [%s] disallowed by ACL\n",start,hash);
                        free(source);
                    }
                } else G_LogPrintf("Lua API: cannot load %s\n",start);
                if(file) trap_FS_FCloseFile(file);
            }
            if(last || count==16) break;
            start=p+1;
        }
    }
    args[0]=time;args[1]=seed;args[2]=restart;
    for(i=0;i<count;++i) Call(states[i],"et_InitGame",3,args);
}
