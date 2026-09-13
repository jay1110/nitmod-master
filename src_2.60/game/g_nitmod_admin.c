#include "g_local.h"
#include "g_nitmod_restrictions.h"
#include "../../pak/ui/menudef.h"
#include "g_nitmod_admin.h"
#include "g_nitmod_accounts.h"
#include "g_nitmod_database.h"
#include "g_nitmod_config.h"
#include "g_nitmod_records.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_admin_commands.h"
#include "nitmod_support_time.h"
#include "nitmod_lua_events.h"
#include "../sqlite/sqlite3.h"
#include <time.h>
typedef struct { int number; char name[36],flags[1024],gtext[1024],gsound[1024]; } adminLevel_t;
static adminLevel_t levels[64];
static int levelCount,levelsReady,levelSavePending;
static int LevelGeneration(char *path,int *next) {
    static char list[65536]; char *p=list,*end=list+sizeof(list); int i,count,max=0,committed=0;
    memset(list,0,sizeof(list)); count=trap_FS_GetFileList("levels.db.d","",list,sizeof(list));
    strcpy(path,"levels.db");
    for(i=0;i<count;++i) {
        int j,n=0; size_t length;
        if(p>=end || !memchr(p,0,end-p)) return 0;
        length=strlen(p);
        if(length==12 || length==16) {
            for(j=0;j<8 && p[j]>='0' && p[j]<='9';++j) n=n*10+p[j]-'0';
            if(j==8 && (!strcmp(p+8,".cfg") || !strcmp(p+8,".pending"))) {
                if(n>max) max=n;
                if(!strcmp(p+8,".cfg") && n>committed) { committed=n; Com_sprintf(path,MAX_QPATH,"levels.db.d/%s",p); }
            }
        }
        p+=length+1;
    }
    if(end-p<MAX_QPATH || max>=99999999) return 0;
    *next=max+1; return 1;
}
static int LevelFileMatches(const char *path,const char *text,int length) {
    fileHandle_t f=0; char *readback=NULL; int size=trap_FS_FOpenFile(path,&f,FS_READ),ok=0;
    if(f && size==length && (readback=malloc(length))) { trap_FS_Read(readback,length,f); ok=!memcmp(readback,text,length); }
    if(f) trap_FS_FCloseFile(f); free(readback); return ok;
}
static int SaveLevels(void) {
    char latest[MAX_QPATH],pending[MAX_QPATH],destination[MAX_QPATH],line[4096];
    char *text; fileHandle_t f=0; int next,i,size,length=0,ok=0;
    if(!LevelGeneration(latest,&next)) return 0;
    text=malloc(262144); if(!text) return 0; text[0]=0;
    for(i=0;i<levelCount;++i) {
        adminLevel_t *a=&levels[i];
        /* Quoted values preserve spaces and comment-like greeting text. */
        const char *values[]={a->name,a->flags,a->gtext,a->gsound}; int j;
        for(j=0;j<4;++j) if(strpbrk(values[j],"\"\r\n")) goto done;
        Com_sprintf(line,sizeof(line),"**********\nlevel = %d\nname = \"%s\"\nflags = \"%s\"\ngtext = \"%s\"\ngsound = \"%s\"\n",a->number,a->name,a->flags,a->gtext,a->gsound);
        size=strlen(line); if(length+size>=262144) goto done; memcpy(text+length,line,size+1); length+=size;
    }
    if(LevelFileMatches(latest,text,length)) { ok=1; goto done; }
    Com_sprintf(pending,sizeof(pending),"levels.db.d/%08d.pending",next);
    Com_sprintf(destination,sizeof(destination),"levels.db.d/%08d.cfg",next);
    size=trap_FS_FOpenFile(pending,&f,FS_READ); if(f) trap_FS_FCloseFile(f); if(f || size>=0) goto done;
    f=0; size=trap_FS_FOpenFile(destination,&f,FS_READ); if(f) trap_FS_FCloseFile(f); if(f || size>=0) goto done;
    f=0; trap_FS_FOpenFile(pending,&f,FS_WRITE); if(!f) goto done;
    size=trap_FS_Write(text,length,f); trap_FS_FCloseFile(f);
    if(size!=length || !LevelFileMatches(pending,text,length)) goto done;
    trap_FS_Rename(pending,destination); ok=LevelFileMatches(destination,text,length);
done:
    free(text); return ok;
}
static const char defaults[]=
    "**********\nlevel = 0\nname = Guest\nflags = time listplayers records help gibme admintest news uptime about\ngtext = Welcome to the guest [n]\xA0!\ngsound =\n"
    "**********\nlevel = 1\nname = Server Moderator\nflags = time listplayers records help gibme admintest spec999 news pip pop pants uptime about stats put ban banguid\ngtext = Welcome to the administrator [n] !\ngsound =\n"
    "**********\nlevel = 2\nname = Server Master\nflags = all\ngtext =  Welcome to the master\xA0: [n] !\ngsound =\n";
static int Number(const char *s,int *out) {
    int n=0; if(!*s) return 0;
    for(;*s;++s) { if(*s<'0' || *s>'9' || n>(2147483647-(*s-'0'))/10) return 0; n=n*10+*s-'0'; }
    *out=n; return 1;
}
static adminLevel_t *Level(int number) {
    int i; adminLevel_t *fallback=0;
    for(i=0;i<levelCount;++i) { if(levels[i].number==number) return &levels[i]; if(!levels[i].number) fallback=&levels[i]; }
    return fallback;
}
int G_NITMOD_AdminLevel(int n) {
    nitmodDatabaseAccount_t account;adminLevel_t *entry;
    if(!levelsReady && !G_NITMOD_LoadAdminLevels()) return 0;
    entry=Level(n>=0 && G_NITMOD_ClientAccount(n,&account)?account.user.level:0);
    return entry?entry->number:0;
}
const char *G_NITMOD_AdminLevelName(int n) {
    nitmodDatabaseAccount_t account; adminLevel_t *entry;
    if(!levelsReady && !G_NITMOD_LoadAdminLevels()) return "";
    entry=Level(n>=0 && G_NITMOD_ClientAccount(n,&account)?account.user.level:0);
    return entry?entry->name:"";
}
static int EffectiveLevel(int number) { adminLevel_t *entry=Level(number); return entry?entry->number:0; }
int G_NITMOD_LoadAdminLevels(void) {
    fileHandle_t file=0; int length,i,used=0; char *buffer,*cursor,*token;
    char path[MAX_QPATH]; int nextGeneration;
    adminLevel_t *next; adminLevel_t *current=0;
    if(levelSavePending) return levelsReady;
    levelsReady=0; levelCount=0;
    if(!LevelGeneration(path,&nextGeneration)) return 0;
    length=trap_FS_FOpenFile(path,&file,FS_READ);
    if(length<0 && !file) {
        length=(int)strlen(defaults); trap_FS_FOpenFile("levels.db",&file,FS_WRITE);
        if(!file) return 0;
        i=trap_FS_Write(defaults,length,file); trap_FS_FCloseFile(file); file=0;
        if(i!=length) return 0;
        buffer=malloc(length+1); if(!buffer) return 0; memcpy(buffer,defaults,length+1);
    } else {
        if(!file || length<0 || length>1048576) { if(file) trap_FS_FCloseFile(file); return 0; }
        buffer=malloc(length+1); if(!buffer) { trap_FS_FCloseFile(file); return 0; }
        trap_FS_Read(buffer,length,file); trap_FS_FCloseFile(file); buffer[length]=0;
    }
    next=calloc(64,sizeof(*next)); if(!next) { free(buffer); return 0; }
    cursor=buffer;
    while(*(token=COM_Parse(&cursor))) {
        char key[32],value[1024];
        if(!strcmp(token,"**********")) { if(used==64) goto invalid; current=&next[used++]; continue; }
        if(!current) goto invalid;
        Q_strncpyz(key,token,sizeof(key)); token=COM_ParseExt(&cursor,qfalse); if(strcmp(token,"=")) goto invalid;
        value[0]=0;
        while(*(token=COM_ParseExt(&cursor,qfalse))) {
            if(strlen(value)+strlen(token)+2>=sizeof(value)) goto invalid;
            if(*value) Q_strcat(value,sizeof(value)," "); Q_strcat(value,sizeof(value),token);
        }
        if(!strcmp(key,"level")) { if(!Number(value,&current->number)) goto invalid; }
        else if(!strcmp(key,"name")) Q_strncpyz(current->name,value,sizeof(current->name));
        else if(!strcmp(key,"flags")) Q_strncpyz(current->flags,value,sizeof(current->flags));
        else if(!strcmp(key,"gtext")) Q_strncpyz(current->gtext,value,sizeof(current->gtext));
        else if(!Q_stricmp(key,"gsound")) Q_strncpyz(current->gsound,value,sizeof(current->gsound));
        else goto invalid;
    }
    for(i=0;i<used;++i) { int j; for(j=0;j<i;++j) if(next[i].number==next[j].number) goto invalid; }
    memcpy(levels,next,sizeof(levels)); levelCount=used;
    if(!Level(0)) {
        if(levelCount==64) goto invalid;
        current=&levels[levelCount++]; memset(current,0,sizeof(*current));
        strcpy(current->flags,"help listplayers admintest time records gibme about stats spec");
    }
    levelsReady=1; free(next); free(buffer); return 1;
invalid:
    free(next); free(buffer); levelCount=0; G_LogPrintf("[Admin] Invalid levels.db; admin commands disabled\n"); return 0;
}
static int FlagsMatch(const char *flags,const char *command,int all) {
    char copy[1024],*cursor,*token; Q_strncpyz(copy,flags,sizeof(copy)); cursor=copy;
    while(*(token=COM_ParseExt(&cursor,qfalse))) if((all && !Q_stricmp(token,"all")) || !Q_stricmp(token,command)) return 1;
    return 0;
}
int G_NITMOD_AdminAllowed(int n,const char *command) {
    nitmodDatabaseAccount_t account; adminLevel_t *level;
    if(NITMOD_DBUserCount()<0 || !levelsReady) return 0;
    if(n<0) return 1;
    if(!G_NITMOD_ClientAccount(n,&account)) return 0;
    level=Level(account.user.level);
    return FlagsMatch(account.user.flags,command,1) || (level && FlagsMatch(level->flags,command,1));
}
int G_NITMOD_AdminPrivilege(int n,const char *privilege) {
    nitmodDatabaseAccount_t account; adminLevel_t *entry; int all;
    if(NITMOD_DBUserCount()<0 || !levelsReady) return 0;
    if(n<0) return 1;
    if(!G_NITMOD_ClientAccount(n,&account)) return 0;
    entry=Level(account.user.level);
    all=Q_stricmp(privilege,"immunity") && Q_stricmp(privilege,"incognito") && Q_stricmp(privilege,"novote") && Q_stricmp(privilege,"nopm");
    return FlagsMatch(account.user.flags,privilege,all) || (entry && FlagsMatch(entry->flags,privilege,all));
}
void G_NITMOD_AdminGreeting(int n) {
    nitmodDatabaseAccount_t account; adminLevel_t *entry; const char *text,*sound,*p,*prefix;
    char message[900]; int used=0,pos;
    if(!levelsReady || !G_NITMOD_ClientAccount(n,&account)) return;
    entry=Level(G_NITMOD_AdminPrivilege(n,"incognito")?0:account.user.level); if(!entry) return;
    text=*account.gtext?account.gtext:entry->gtext; sound=*account.gsound?account.gsound:entry->gsound;
    if(G_NITMOD_AdminPrivilege(n,"incognito")) { text=entry->gtext; sound=entry->gsound; }
    if(*sound && !strpbrk(sound,"\"\r\n; ")) trap_SendServerCommand(-1,va("gsnd %s",sound));
    if(!*text) return;
    for(p=text;*p && used<(int)sizeof(message)-1;) {
        if(!strncmp(p,"[n]",3)) {
            const char *name=g_entities[n].client->pers.netname;
            for(;*name && used<(int)sizeof(message)-1;++name) message[used++]=(*name=='"' || *name=='\\' || *name=='\n' || *name=='\r')?' ':*name;
            p+=3;
        } else { message[used++]=(*p=='"' || *p=='\\' || *p=='\n' || *p=='\r')?' ':*p; ++p; }
    }
    message[used]=0; pos=G_NITMOD_LegacyCvarInteger("n_greetingPos",0);
    prefix=pos==1?"cp":pos==2?"cpm":pos==3?"bp":pos==4?"print":"chat";
    trap_SendServerCommand(-1,va("%s \"%s\" -2",prefix,message));
}
static void Print(int n,const char *text) { if(n<0) G_Printf("%s",text); else NITMOD_SendChunkedPrint(n,text); }
static const char *Duration(unsigned int seconds) {
    static const unsigned int divisors[]={1,60,3600,86400,604800,2592000,31536000};
    static const char *units[]={"secs","mins","hours","days","weeks","months","years"}; int unit=0;
    if(seconds>=0x5dfc0f01U) return "PERMANENT";
    while(unit<6 && seconds>=divisors[unit+1]) ++unit;
    return va("%u %s",seconds/divisors[unit],units[unit]);
}
static int Targets(const char *text,int *matches) {
    int n,i,count=0; char needle[MAX_NAME_LENGTH],name[MAX_NAME_LENGTH];
    if(Number(text,&n)) {
        if(n<MAX_CLIENTS && g_entities[n].client && g_entities[n].client->pers.connected!=CON_DISCONNECTED) { matches[0]=n;return 1; }
        return 0;
    }
    Q_strncpyz(needle,text,sizeof(needle)); Q_CleanStr(needle); Q_strlwr(needle);
    if(!*needle) return 0;
    for(i=0;i<MAX_CLIENTS;++i) if(g_entities[i].client && g_entities[i].client->pers.connected!=CON_DISCONNECTED) {
        Q_strncpyz(name,g_entities[i].client->pers.netname,sizeof(name)); Q_CleanStr(name); Q_strlwr(name);
        if(strstr(name,needle)) matches[count++]=i;
    }
    return count;
}
static int Target(const char *text) {
    int matches[MAX_CLIENTS];return Targets(text,matches)==1?matches[0]:-1;
}
static int FlingClient(gentity_t *ent,int mode) {
    vec3_t direction;
    if(!ent || !ent->client || ent->health<=0) return 0;
    if(mode==0) {
        direction[0]=(((rand()&32767)/32767.0f)-0.5f)*100.0f;
        direction[1]=(((rand()&32767)/32767.0f)-0.5f)*100.0f;
        direction[2]=10.0f;
    } else if(mode==1) {
        AngleVectors(ent->client->ps.viewangles,direction,NULL,NULL);direction[2]=0.25f;
    } else VectorSet(direction,0,0,10);
    VectorNormalize(direction);
    VectorMA(ent->s.pos.trDelta,1500,direction,ent->s.pos.trDelta);
    VectorMA(ent->client->ps.velocity,1500,direction,ent->client->ps.velocity);
    return 1;
}
/* Database completions own text/identity snapshots, never entity pointers or
 * va() buffers. Account connection generations reject reused client slots. */
typedef struct {
    int actor,target,action,dropTime;
    unsigned int actorGeneration,targetGeneration,targets[MAX_CLIENTS];
    unsigned char selected[MAX_CLIENTS];
    char success[1200],failure[256],drop[1200];
} adminDbCompletion_t;
static int AdminDbClient(int n,unsigned int generation) {
    return n>=0 && n<MAX_CLIENTS && g_entities[n].client &&
        g_entities[n].client->pers.connected!=CON_DISCONNECTED &&
        G_NITMOD_AccountConnectionGeneration(n)==generation;
}
static void AdminDbContext(adminDbCompletion_t *ctx,int actor,const char *command) {
    memset(ctx,0,sizeof(*ctx));ctx->actor=actor;ctx->target=-1;
    ctx->actorGeneration=G_NITMOD_AccountConnectionGeneration(actor);
    Com_sprintf(ctx->failure,sizeof(ctx->failure),"^1%s error: ^9Database write failed\n",command);
}
static void AdminDbTarget(adminDbCompletion_t *ctx,int target,int action) {
    ctx->target=target;ctx->action=action;
    ctx->targetGeneration=G_NITMOD_AccountConnectionGeneration(target);
}
static void AdminDbDone(int ok,const void *opaque) {
    const adminDbCompletion_t *ctx=opaque;int i;
    if(ok && AdminDbClient(ctx->target,ctx->targetGeneration)) {
        gclient_t *client=g_entities[ctx->target].client;
        if(ctx->action==1) { client->sess.muted=qfalse;client->sess.nitmodCensorMuteTime=-1;client->nitmodMuteUntil=0;ClientUserinfoChanged(ctx->target); }
        /* Original !mute keeps the censor timestamp: its dynamic language
         * timer and the persisted mute are checked independently. */
        else if(ctx->action==2) ClientUserinfoChanged(ctx->target);
        else if(ctx->action==3) trap_DropClient(ctx->target,ctx->drop,ctx->dropTime);
    }
    /* Original kick policy still kicks if optional temporary-ban storage
     * fails, but only after that storage operation has a final outcome. */
    if(ctx->action==4 && AdminDbClient(ctx->target,ctx->targetGeneration))
        trap_DropClient(ctx->target,ctx->drop,ctx->dropTime);
    if(ok) for(i=0;i<MAX_CLIENTS;++i)
        if(ctx->selected[i] && AdminDbClient(i,ctx->targets[i])) trap_DropClient(i,ctx->drop,0);
    if(ctx->actor<0 || AdminDbClient(ctx->actor,ctx->actorGeneration)) {
        const char *text=ok?ctx->success:ctx->failure;if(*text)Print(ctx->actor,text);
    } else if(!ok) G_LogPrintf("[Admin] Deferred database operation failed after actor disconnect\n");
}
static void PenaltyStore(const nitmodDatabasePenalty_t *penalty,int mute,int add,const adminDbCompletion_t *ctx) {
    int length;void *before=NITMOD_DBExport(&length);
    if(!before){AdminDbDone(0,ctx);return;}
    if(!NITMOD_DBPenaltySave(mute,penalty,add)) {
        NITMOD_DBInstallWorking(before,length);NITMOD_DBFreeExport(before);AdminDbDone(0,ctx);return;
    }
    G_NITMOD_DatabaseCommit(before,length,AdminDbDone,ctx,sizeof(*ctx));
}
static int PenaltyCommand(int n,const char *command,int argc,char args[][1024]) {
    nitmodDatabasePenalty_t penalty,existing; nitmodDatabaseAccount_t account,actor;
    int target=-1,mute=!strcmp(command,"mute") || !strcmp(command,"unmute"),i,seconds=0,start=3,expired;
    qtime_t now; int time=trap_RealTime(&now)-946490400;
    if(!strcmp(command,"showbans")) {
        static int lastStart[MAX_CLIENTS+1];
        int slot=n>=0 && n<MAX_CLIENTS?n:MAX_CLIENTS,first=0,count=0,rc=0,filter=0,position=1;
        int indices[1024]; char needle[1024],candidate[1024]; const char *startArg=NULL;
        needle[0]=0;
        if(argc>1) {
            filter=!Q_stricmp(args[1],"find")?1:!Q_stricmp(args[1],"banner")?2:!Q_stricmp(args[1],"reason")?3:0;
            if(filter) {
                if(argc<3) { Print(n,"^9usage: ^g!showbans [start|find <match>|banner <match>|reason <match>] [start]\n"); return 1; }
                Q_strncpyz(needle,args[2],sizeof(needle)); Q_strlwr(needle);
                if(argc>3) startArg=args[3];
            } else startArg=args[1];
        }
        for(i=0;i<1024 && (rc=NITMOD_DBPenaltyAt(0,i,&penalty))==1;++i) {
            if(penalty.expires && penalty.expires<=time) continue;
            if(filter) {
                Q_strncpyz(candidate,filter==1?penalty.name:filter==2?penalty.actor:penalty.reason,sizeof(candidate));
                Q_strlwr(candidate); if(!strstr(candidate,needle)) continue;
            }
            indices[count++]=i;
        }
        if(rc<0) { Print(n,"^1showbans error: ^9Database query failed\n"); return 1; }
        if(startArg) {
            if(!Q_stricmp(startArg,"next")) first=lastStart[slot]+30;
            else if(!Q_stricmp(startArg,"prev")) first=lastStart[slot]-30;
            else {
                char *end; long value=strtol(startArg,&end,10);
                if(!*startArg || *end || value < -1024 || value>1024 || !value) {
                    Print(n,"^1showbans error: ^9Invalid start\n"); return 1;
                }
                first=value<0?count+(int)value:(int)value-1;
            }
        }
        if(first<0) first=0;
        if(first>=count && first) { Print(n,va("^xshowbans: ^9there are only ^g%d ^9active bans!\n",count)); return 1; }
        lastStart[slot]=first;
        for(position=first;position<count && position<first+30;++position) {
            if(NITMOD_DBPenaltyAt(0,indices[position],&penalty)!=1) { Print(n,"^1showbans error: ^9Database query failed\n"); return 1; }
            Print(n,va("^g%d ^9| ^7%s ^9| ^g%s ^9| ^g%s ^9| ^7%s ^9| ^g%s ^9| ^g%s\n",
                indices[position]+1,penalty.name,strlen(penalty.guid)==32?penalty.guid+24:penalty.guid,
                penalty.made,penalty.actor,penalty.expires?Duration((unsigned int)(penalty.expires-time)):"PERMANENT",penalty.reason));
        }
        Print(n,va("^xshowbans: ^9showing bans ^g%d ^9- ^g%d ^9of ^g%d ^9(Page ^g%i ^9of ^g%i^9)\n",
            count?first+1:0,position,count,first/30+1,count?(count+29)/30:1));
        return 1;
    }
    if(argc<2) { Print(n,va("^9usage: ^g!%s [target]\n",command)); return 1; }
    if(!strcmp(command,"unban")) {
        if(!Number(args[1],&i) || i<1 || NITMOD_DBPenaltyAt(0,i-1,&penalty)!=1) { Print(n,"^1unban error: ^9invalid ban #\n"); return 1; }
        { adminDbCompletion_t ctx;AdminDbContext(&ctx,n,"unban");
          Com_sprintf(ctx.success,sizeof(ctx.success),"^xunban: ^9ban ^g#%d ^9removed\n",i);
          PenaltyStore(&penalty,0,0,&ctx); } return 1;
    }
    if(!strcmp(command,"banguid")) {
        if(NITMOD_DBAccountByID(args[1],&account)!=1) { Print(n,"^1banguid error: ^9Player not found.\n"); return 1; }
    } else {
        target=Target(args[1]);
        if(target<0 || !G_NITMOD_ClientAccount(target,&account)) { Print(n,"^1Admin error: ^9No unique player with valid NGUID\n"); return 1; }
    }
    if(strcmp(command,"unmute") && n>=0 && (!G_NITMOD_ClientAccount(n,&actor) || EffectiveLevel(actor.user.level)<EffectiveLevel(account.user.level))) {
        Print(n,"^1Admin error: ^9Specified player has a higher admin level than you do.\n"); return 1;
    }
    memset(&penalty,0,sizeof(penalty)); Q_strncpyz(penalty.guid,account.user.guid,sizeof(penalty.guid));
    if(!strcmp(command,"unmute")) {
        if(!g_entities[target].client->sess.muted) {
            int matches[64],count=0,rc=0,selection=1,numeric; char needle[64],name[64];
            Q_strncpyz(needle,Number(args[1],&numeric)?g_entities[target].client->pers.netname:args[1],sizeof(needle));
            Q_CleanStr(needle); Q_strlwr(needle);
            for(i=0;i<1024 && count<64 && (rc=NITMOD_DBPenaltyAt(1,i,&existing))==1;++i) {
                if(existing.expires && existing.expires<=time) continue;
                Q_strncpyz(name,existing.name,sizeof(name)); Q_CleanStr(name); Q_strlwr(name);
                if(*needle && strstr(name,needle)) matches[count++]=i;
            }
            if(rc<0) { Print(n,"^1unmute error: ^9Database query failed\n"); return 1; }
            if(!count) { Print(n,"^1unmute ^9no player by that name or slot # is muted\n"); return 1; }
            if(count>1 && argc<3) {
                Print(n,"^1unmute ^9more than one player name matches. Select a result with !unmute [name] [number]:\n");
                for(i=0;i<count;++i) if(NITMOD_DBPenaltyAt(1,matches[i],&existing)==1)
                    Print(n,va("^9%d ^7- %s ^9for %s\n",i+1,existing.name,existing.reason));
                return 1;
            }
            if(argc>2 && (!Number(args[2],&selection) || selection<1 || selection>count)) { Print(n,"^9invalid number\n"); return 1; }
            if(NITMOD_DBPenaltyAt(1,matches[selection-1],&penalty)!=1) { Print(n,"^1unmute error: ^9Database query failed\n"); return 1; }
        }
        { adminDbCompletion_t ctx;AdminDbContext(&ctx,n,"unmute");AdminDbTarget(&ctx,target,1);
          Q_strncpyz(ctx.success,"^xunmute: ^9Player has been unmuted\n",sizeof(ctx.success));
          PenaltyStore(&penalty,1,0,&ctx); }
        return 1;
    }
    if(argc>2) {
        char duration[7],*end; long number; int multiplier=1; size_t length;
        Q_strncpyz(duration,args[2],sizeof(duration)); length=strlen(duration);
        if(length && (duration[length-1]<'0' || duration[length-1]>'9')) {
            switch(duration[length-1]) { case 'w':multiplier=604800;break;case 'd':multiplier=86400;break;case 'h':multiplier=3600;break;case 'm':multiplier=60;break; }
            duration[length-1]=0;
        }
        number=strtol(duration,&end,10);
        if(number>0) { if(number>(2147483647-time)/multiplier) { Print(n,"^1Admin error: ^9Duration too large\n"); return 1; } seconds=(int)number*multiplier; }
    }
    if(!seconds) {
        start=2;
        if(mute) { seconds=G_NITMOD_LegacyCvarInteger("g_defaultMute",3600); if(seconds<10) seconds=10; }
        else if(!G_NITMOD_AdminAllowed(n,"permban")) { Print(n,"^1ban error: ^9seconds must be a positive integer\n"); return 1; }
    }
    if(!G_NITMOD_AdminAllowed(n,"noreason") && argc<=start) { Print(n,"^1Admin error: ^9A reason is required\n"); return 1; }
    if(seconds>2147483647-time) { Print(n,"^1Admin error: ^9Duration too large\n"); return 1; }
    if(!strcmp(account.ip,"localhost") || !strcmp(account.ip,"127.0.0.1") || (target>=0 && g_entities[target].client->pers.localClient)) {
        Print(n,"^1Admin error: ^9Cannot ban or mute server host.\n"); return 1;
    }
    i=NITMOD_DBPenaltyPeek(mute,"",account.user.guid,account.mac,time,&existing,&expired);
    if(i!=0) { Print(n,i>0?"^1Admin error: ^9Player already banned/muted\n":"^1Admin error: ^9Database query failed\n"); return 1; }
    Q_strncpyz(penalty.name,account.user.name,sizeof(penalty.name)); Q_strncpyz(penalty.ip,account.ip,sizeof(penalty.ip));
    Q_strncpyz(penalty.mac,account.mac,sizeof(penalty.mac)); Q_strncpyz(penalty.actor,n<0?"console":g_entities[n].client->pers.netname,sizeof(penalty.actor));
    Com_sprintf(penalty.made,sizeof(penalty.made),"%02d/%02d/%02d %02d:%02d:%02d",now.tm_mon+1,now.tm_mday,(now.tm_year+1900)%100,now.tm_hour,now.tm_min,now.tm_sec);
    penalty.expires=seconds?time+seconds:0;
    for(i=start;i<argc;++i) { if(i>start) Q_strcat(penalty.reason,sizeof(penalty.reason)," "); Q_strcat(penalty.reason,sizeof(penalty.reason),args[i]); }
    if(!*penalty.reason) Q_strncpyz(penalty.reason,mute?"muted by admin":"banned by admin",sizeof(penalty.reason));
    { adminDbCompletion_t ctx;AdminDbContext(&ctx,n,command);AdminDbTarget(&ctx,target,mute?2:3);
      Q_strncpyz(ctx.failure,"^1Admin error: ^9Database write failed\n",sizeof(ctx.failure));
      Com_sprintf(ctx.drop,sizeof(ctx.drop),"You have been banned %s, Reason: %s",seconds?va("for %i seconds",seconds):"^1PERMANENTLY",penalty.reason);
      if(!strcmp(command,"banguid")) for(i=0;i<MAX_CLIENTS;++i)
          if(G_NITMOD_ClientAccount(i,&actor) && !Q_stricmp(actor.user.guid,account.user.guid)) {
              ctx.selected[i]=1;ctx.targets[i]=G_NITMOD_AccountConnectionGeneration(i);
          }
      Com_sprintf(ctx.success,sizeof(ctx.success),"^x%s: ^7%s ^9has been %s\n",command,penalty.name,mute?"muted":"banned");
      PenaltyStore(&penalty,mute,1,&ctx);
    } return 1;
}
static int KnownPrivilege(const char *name) {
    static const char names[]="readconfig time setlevel kick ban unban put pause unpause listplayers records mute unmute showbans help gibme admintest cancelvote passvote spec999 shuffle rename splat splata slap burn warn news lock unlock nade pip pop restart reset fling throw launch disorient orient resetxp resetmyxp nextmap swap swap_restart revive panzerwar sniperwar disguise poison ammopack medpack pants give finger uptime glow freeze unfreeze blind unblind about stats levedit levinfo levlist spec banguid userlist useredit userinfo seen delrecords dbsave userdelete levdelete levadd crazygravity immunity nocensorflood silentcmds specchat balanceimmunity noreason novotelimit permban teamcmds inactivity incognito novote pmspec adminchat nopm all";
    char copy[sizeof(names)],*cursor,*token;
    strcpy(copy,names); cursor=copy;
    while(*(token=COM_ParseExt(&cursor,qfalse))) if(!Q_stricmp(token,name)) return 1;
    return 0;
}
static int EditFlags(char *flags,const char *flag,int grant) {
    char old[1024],*cursor,*token; int found=0;
    if(!KnownPrivilege(flag)) return 0;
    Q_strncpyz(old,flags,sizeof(old)); cursor=old; flags[0]=0;
    while(*(token=COM_ParseExt(&cursor,qfalse))) {
        if(!Q_stricmp(token,flag)) { found=1; if(!grant) continue; }
        if(*flags) Q_strcat(flags,1024," "); Q_strcat(flags,1024,token);
    }
    if(grant && !found) {
        if(strlen(flags)+strlen(flag)+2>=1024) { strcpy(flags,old); return 0; }
        if(*flags) Q_strcat(flags,1024," "); Q_strcat(flags,1024,flag);
    }
    return 1;
}
typedef struct {
    adminDbCompletion_t notice;
    adminLevel_t *oldLevels,*newLevels;
    int oldCount,newCount,beforeLength,afterLength;
    void *dbBefore,*dbAfter;
} levelDbCompletion_t;
static void LevelDbFree(levelDbCompletion_t *ctx) {
    NITMOD_DBFreeExport(ctx->dbBefore);NITMOD_DBFreeExport(ctx->dbAfter);
    free(ctx->oldLevels);free(ctx->newLevels);free(ctx);levelSavePending=0;
}
static void LevelDbUndoDone(int ok,const void *opaque) {
    levelDbCompletion_t *ctx=*(levelDbCompletion_t *const *)opaque;
    if(!ok)G_LogPrintf("[Admin] Failed to persist targeted level migration rollback\n");
    AdminDbDone(0,&ctx->notice);LevelDbFree(ctx);
}
static void LevelDbDone(int ok,const void *opaque) {
    levelDbCompletion_t *ctx=*(levelDbCompletion_t *const *)opaque;
    if(!ok){AdminDbDone(0,&ctx->notice);LevelDbFree(ctx);return;}
    memcpy(levels,ctx->newLevels,sizeof(levels));levelCount=ctx->newCount;
    if(SaveLevels()){AdminDbDone(1,&ctx->notice);LevelDbFree(ctx);return;}
    memcpy(levels,ctx->oldLevels,sizeof(levels));levelCount=ctx->oldCount;
    /* Undo only this migration's changed fields against the latest DB image.
     * A stale whole-image restore would erase other committed XP/accounts. */
    { void *base=ctx->dbAfter,*changed=ctx->dbBefore;int baseLength=ctx->afterLength,changedLength=ctx->beforeLength;
      ctx->dbAfter=ctx->dbBefore=NULL;
      G_NITMOD_DatabaseSubmitImages(base,baseLength,changed,changedLength,LevelDbUndoDone,&ctx,sizeof(ctx));
    }
}
static int LevelCommand(int n,const char *command,int argc,char args[][1024]) {
    adminLevel_t *entry,*before; int i,number,oldCount=levelCount,to=0,length=0,ok,migrate=0; void *databaseBefore=NULL;
    if(!strcmp(command,"levlist")) {
        for(i=0;i<levelCount;++i) Print(n,va("^x%3d ^7%s\n",levels[i].number,levels[i].name)); return 1;
    }
    if(strcmp(command,"levinfo") && !G_NITMOD_SecureShrubAllowed(n)) {
        Print(n,va("^1%s error: ^9Secure Shrubbot Login is enabled on this server. \n ^9Log in using ^g/sslogin ^9and try again.^7\n",command)); return 1;
    }
    if(argc<2 || !Number(args[1],&number)) { Print(n,va("^9usage: ^g!%s [level#]\n",command)); return 1; }
    entry=Level(number); if(entry && entry->number!=number) entry=NULL;
    if(!strcmp(command,"levinfo")) {
        if(!entry) Print(n,"^1levinfo error: ^9Unknown level\n");
        else Print(n,va("^9Level: ^g%d\n^9Name: ^g%s\n^9Flags: ^g%s\n^9GText: ^g%s\n^9GSound: ^g%s\n",entry->number,entry->name,entry->flags,entry->gtext,entry->gsound));
        return 1;
    }
    if(!strcmp(command,"levadd")) {
        if(entry || levelCount==64) { Print(n,"^1levadd error: ^9Level exists or level limit reached\n"); return 1; }
    } else if(!entry) { Print(n,va("^1%s error: ^9Unknown level\n",command)); return 1; }
    before=malloc(sizeof(levels)); if(!before) return 1; memcpy(before,levels,sizeof(levels));
    if(!strcmp(command,"levadd")) { entry=&levels[levelCount++]; memset(entry,0,sizeof(*entry)); entry->number=number; }
    else if(!strcmp(command,"levdelete")) {
        if(!number) { Print(n,"^1levdelete error: ^9Level ^70 ^gcan not be deleted!^7\n"); goto abortEdit; }
        if(argc>2 && (!Number(args[2],&to) || !Level(to) || Level(to)->number!=to || to==number)) {
            Print(n,"^1levdelete error: ^9Invalid migration level\n"); goto abortEdit;
        }
        databaseBefore=NITMOD_DBExport(&length); if(!databaseBefore) goto abortEdit;
        migrate=1;
        if(!NITMOD_DBMigrateUserLevel(number,to)) goto failed;
        i=(int)(entry-levels); memmove(&levels[i],&levels[i+1],(levelCount-i-1)*sizeof(*entry)); --levelCount;
    } else {
        if(argc<3) { Print(n,"^9usage: ^g!levedit [level] [grant|revoke|name|gtext|gsound] [args]^7\n"); goto abortEdit; }
        if(!Q_stricmp(args[2],"grant") || !Q_stricmp(args[2],"revoke")) {
            if(argc<4 || !EditFlags(entry->flags,args[3],!Q_stricmp(args[2],"grant"))) { Print(n,"^1levedit error: ^9Unknown command/privilege\n"); goto abortEdit; }
        } else {
            char *value; int capacity;
            if(!Q_stricmp(args[2],"name")) { value=entry->name; capacity=sizeof(entry->name); }
            else if(!Q_stricmp(args[2],"gtext")) { value=entry->gtext; capacity=sizeof(entry->gtext); }
            else if(!Q_stricmp(args[2],"gsound")) { value=entry->gsound; capacity=sizeof(entry->gsound); }
            else { Print(n,"^1levedit error: ^9Unknown action\n"); goto abortEdit; }
            value[0]=0; for(i=3;i<argc;++i) { if(i>3) Q_strcat(value,capacity," "); Q_strcat(value,capacity,args[i]); if(value==entry->gsound) break; }
        }
    }
    if(migrate) {
        levelDbCompletion_t *ctx=calloc(1,sizeof(*ctx));
        if(!ctx)goto failed;
        ctx->dbBefore=sqlite3_malloc(length);ctx->newLevels=malloc(sizeof(levels));
        ctx->dbAfter=NITMOD_DBExport(&ctx->afterLength);
        if(!ctx->dbBefore || !ctx->newLevels || !ctx->dbAfter) {
            NITMOD_DBFreeExport(ctx->dbBefore);NITMOD_DBFreeExport(ctx->dbAfter);free(ctx->newLevels);free(ctx);goto failed;
        }
        memcpy(ctx->dbBefore,databaseBefore,length);ctx->beforeLength=length;
        memcpy(ctx->newLevels,levels,sizeof(levels));ctx->newCount=levelCount;
        ctx->oldLevels=before;ctx->oldCount=oldCount;
        AdminDbContext(&ctx->notice,n,command);
        Com_sprintf(ctx->notice.success,sizeof(ctx->notice.success),"^x%s: ^9level ^7%d successfully deleted^7\n",command,number);
        Com_sprintf(ctx->notice.failure,sizeof(ctx->notice.failure),"^1%s error: ^9Persistence failed\n",command);
        memcpy(levels,before,sizeof(levels));levelCount=oldCount;levelSavePending=1;
        G_NITMOD_DatabaseCommit(databaseBefore,length,LevelDbDone,&ctx,sizeof(ctx));return 1;
    }
    ok=SaveLevels(); if(!ok) goto failed;
    Print(n,va("^x%s: ^9level ^7%d successfully %s^7\n",command,number,!strcmp(command,"levadd")?"added":!strcmp(command,"levdelete")?"deleted":"updated"));
    NITMOD_DBFreeExport(databaseBefore); free(before); return 1;
failed:
    if(migrate && databaseBefore) {
        if(!NITMOD_DBInstallWorking(databaseBefore,length)) G_LogPrintf("[Admin] Failed to restore uncommitted level migration\n");
    }
    Print(n,va("^1%s error: ^9Persistence failed\n",command));
abortEdit:
    memcpy(levels,before,sizeof(levels)); levelCount=oldCount; NITMOD_DBFreeExport(databaseBefore); free(before); return 1;
}
static int UserCommand(int n,const char *command,int argc,char args[][1024]) {
    nitmodDatabaseAccount_t account; char id[9]; int i,rc,number;
    if(!strcmp(command,"seen")) {
        char needle[36],name[64]; int matches=0,j,online; qtime_t now; unsigned int time=(unsigned int)trap_RealTime(&now);
        if(argc<2) { Print(n,"^9usage: ^g!seen [name]^7\n"); return 1; }
        Q_strncpyz(needle,args[1],sizeof(needle)); Q_CleanStr(needle); Q_strlwr(needle);
        for(i=0;(rc=NITMOD_DBAccountAt(i,&account))==1;++i) {
            Q_strncpyz(name,account.user.name,sizeof(name)); Q_CleanStr(name); Q_strlwr(name);
            if(!strstr(name,needle)) continue;
            if(++matches>15) continue;
            online=0;
            for(j=0;j<MAX_CLIENTS;++j) { nitmodDatabaseAccount_t connected;
                if(g_entities[j].client && g_entities[j].client->pers.connected!=CON_DISCONNECTED &&
                   G_NITMOD_ClientAccount(j,&connected) && !strcmp(connected.user.guid,account.user.guid)) { online=1; break; }
            }
            Print(n,va("^xSeen: ^w%s ^g(%s) %s\n",account.user.name,strlen(account.user.guid)==32?account.user.guid+24:"????????",
                online?"is online.":account.timestamp?va("%s ago.",Duration(time-(unsigned int)account.timestamp)):"???"));
        }
        if(rc<0) Print(n,"^1seen error: ^9Database query failed\n");
        else Print(n,va("^xSeen: ^g%d player(s) found.\n",matches>15?15:matches));
        if(matches>15) Print(n,va("^xSeen: ^gToo many matches (%d). Please be more specific.\n",matches)); return 1;
    }
    if(!strcmp(command,"userlist")) {
        int page=1,matches=0; char needle[64],candidate[64];
        if(argc==2 && !Number(args[1],&page)) page=0;
        if(argc>3 && !Number(args[3],&page)) page=0;
        if(page<1) { Print(n,"^1userlist error: ^9Invalid page\n"); return 1; }
        Q_strncpyz(needle,argc>2?args[2]:"",sizeof(needle)); Q_CleanStr(needle); Q_strlwr(needle);
        for(i=0;(rc=NITMOD_DBAccountAt(i,&account))==1;++i) {
            if(argc>2) {
                if(!Q_stricmp(args[1],"level")) { if(!Number(args[2],&number) || EffectiveLevel(account.user.level)!=number) continue; }
                else {
                    const char *value=!Q_stricmp(args[1],"name")?account.user.name:!Q_stricmp(args[1],"ip")?account.ip:!Q_stricmp(args[1],"mac")?account.mac:NULL;
                    if(!value) { Print(n,"^9usage: ^g!userlist [name|level|ip|mac] [value] [page]\n"); return 1; }
                    Q_strncpyz(candidate,value,sizeof(candidate)); Q_CleanStr(candidate); Q_strlwr(candidate);
                    if(!strstr(candidate,needle)) continue;
                }
            }
            if(matches/20+1==page) Print(n,va("^g%s ^x%3i ^7%s\n",strlen(account.user.guid)==32?account.user.guid+24:"????????",EffectiveLevel(account.user.level),account.user.name));
            ++matches;
        }
        if(rc<0) Print(n,"^1userlist error: ^9Database query failed\n");
        else Print(n,va("^xpage %d/%d (%d matches)\n",page,(matches+19)/20,matches));
        return 1;
    }
    if((!strcmp(command,"useredit") || !strcmp(command,"userdelete")) && !G_NITMOD_SecureShrubAllowed(n)) {
        Print(n,va("^1%s error: ^9Secure Shrubbot Login is enabled on this server. \n ^9Log in using ^g/sslogin ^9and try again.^7\n",command)); return 1;
    }
    if(argc<2) { Print(n,va("^9usage: ^g!%s [UserID]\n",command)); return 1; }
    Q_strncpyz(id,args[1],sizeof(id));
    rc=NITMOD_DBAccountByID(id,&account);
    if(rc!=1) { Print(n,va("^1%s error: ^9%s UserID : ^g%s^7\n",command,rc<0?"Invalid or ambiguous":"Unknown",id)); return 1; }
    if(!strcmp(command,"userinfo")) {
        Print(n,va("^9Name:   ^g%s\n^9Level:  ^g%d\n^9NGUID:  ^g%s\n^9UserID: ^g%s\n^9IP:     ^g%s\n^9MAC:    ^g%s\n",account.user.name,EffectiveLevel(account.user.level),account.user.guid,id,account.ip,account.mac));
        if(*account.gtext) Print(n,va("^9GText:  ^g%s\n",account.gtext));
        if(*account.gsound) Print(n,va("^9GSound: ^g%s\n",account.gsound));
        if(*account.user.flags) Print(n,va("^9Flags:  ^g%s\n",account.user.flags));
        if(account.timestamp) { qtime_t now; Print(n,va("^xSeen:   ^g%s ago.\n",Duration((unsigned int)trap_RealTime(&now)-(unsigned int)account.timestamp))); }
        return 1;
    }
    if(!strcmp(command,"userdelete")) {
        { adminDbCompletion_t ctx;AdminDbContext(&ctx,n,"userdelete");
          Com_sprintf(ctx.success,sizeof(ctx.success),"^xuserdelete: ^9User ^7%s ^9(UserID ^g%s^9) successfully deleted from database^7\n",account.user.name,id);
          G_NITMOD_StoreAccountAsync(&account,0,AdminDbDone,&ctx,sizeof(ctx)); }
        return 1;
    }
    if(argc<3) { Print(n,"^9usage: ^g!useredit [UserID] [grant|revoke|level|gtext|gsound] [args]^7\n"); return 1; }
    if(!Q_stricmp(args[2],"level")) {
        if(argc<4 || !Number(args[3],&number) || !Level(number) || Level(number)->number!=number) { Print(n,"^1useredit error: ^9unknown level\n"); return 1; }
        account.user.level=number;
    } else if(!Q_stricmp(args[2],"gtext") || !Q_stricmp(args[2],"gsound")) {
        char *value=!Q_stricmp(args[2],"gtext")?account.gtext:account.gsound;
        value[0]=0;
        for(i=3;i<argc;++i) { if(i>3) Q_strcat(value,1024," "); Q_strcat(value,1024,args[i]); if(value==account.gsound) break; }
    } else if(!Q_stricmp(args[2],"grant") || !Q_stricmp(args[2],"revoke")) {
        char previous[1024],*cursor,*token; int found=0,grant=!Q_stricmp(args[2],"grant");
        if(argc<4 || !KnownPrivilege(args[3])) { Print(n,"^1useredit error: ^9Unknown command/privilege\n"); return 1; }
        Q_strncpyz(previous,account.user.flags,sizeof(previous)); cursor=previous; account.user.flags[0]=0;
        while(*(token=COM_ParseExt(&cursor,qfalse))) {
            if(!Q_stricmp(token,args[3])) { found=1; if(!grant) continue; }
            if(*account.user.flags) Q_strcat(account.user.flags,sizeof(account.user.flags)," ");
            Q_strcat(account.user.flags,sizeof(account.user.flags),token);
        }
        if(grant && !found) {
            if(strlen(account.user.flags)+strlen(args[3])+2>=sizeof(account.user.flags)) { Print(n,"^1useredit error: ^9Too many privileges\n"); return 1; }
            if(*account.user.flags) Q_strcat(account.user.flags,sizeof(account.user.flags)," ");
            Q_strcat(account.user.flags,sizeof(account.user.flags),args[3]);
        }
    } else { Print(n,"^1useredit error: ^9Unknown action^7\n"); return 1; }
    { adminDbCompletion_t ctx;AdminDbContext(&ctx,n,"useredit");
      Com_sprintf(ctx.success,sizeof(ctx.success),"^xuseredit: ^7%s ^9updated\n",account.user.name);
      G_NITMOD_StoreAccountAsync(&account,2,AdminDbDone,&ctx,sizeof(ctx)); }
    return 1;
}

typedef struct { char name[64],exec[1024],description[1024]; int levels[64],levelCount; } customCommand_t;
static customCommand_t customCommands[128];
static int customCommandCount;
int G_NITMOD_LoadAdminCommands(void) {
    static const char initial[]="**********\nname = minbots\nexec = bot minbots [1]\ndesc = Sets the minimum number of bots on the server\nlevels = 1 2\n**********\nname = maxbots\nexec = bot maxbots [1]\ndesc = Sets the maximum number of bots on the server\nlevels = 1 2\n";
    fileHandle_t f=0; int length,i,count=0,ok=0; char *buffer=NULL,*cursor,*token;
    customCommand_t *next=NULL,*current=NULL;
    const char *filename="commands.db";
    customCommandCount=0;
    length=trap_FS_FOpenFile(filename,&f,FS_READ);
    if(length<0 && !f) {
        trap_FS_FOpenFile("commands.db",&f,FS_WRITE);
        if(!f) return 0;
        i=trap_FS_Write(initial,sizeof(initial)-1,f);trap_FS_FCloseFile(f);f=0;
        if(i!=sizeof(initial)-1 || !LevelFileMatches("commands.db",initial,sizeof(initial)-1)) return 0;
        length=trap_FS_FOpenFile("commands.db",&f,FS_READ);
    }
    if(!f || length<0 || length>1048576) { if(f) trap_FS_FCloseFile(f);return 0; }
    buffer=malloc(length+1);next=calloc(128,sizeof(*next));
    if(!buffer || !next) goto done;
    trap_FS_Read(buffer,length,f);buffer[length]=0;cursor=buffer;
    if(length>=3 && (unsigned char)buffer[0]==0xef && (unsigned char)buffer[1]==0xbb && (unsigned char)buffer[2]==0xbf) cursor+=3;
    while(*cursor) {
        char *line=cursor,*end,*equal,*key,*value;
        while(*cursor && *cursor!='\n') ++cursor;
        if(*cursor) *cursor++=0;
        while(*line==' ' || *line=='\t' || *line=='\r') ++line;
        end=line+strlen(line);
        while(end>line && (end[-1]==' ' || end[-1]=='\t' || end[-1]=='\r')) *--end=0;
        if(!*line || *line=='#' || !strncmp(line,"//",2)) continue;
        if(!strcmp(line,"**********") || !strcmp(line,"---")) { current=NULL;continue; }
        equal=strchr(line,'=');if(!equal) goto done;
        *equal=0;key=line;end=equal;
        while(end>key && (end[-1]==' ' || end[-1]=='\t')) *--end=0;
        value=equal+1;while(*value==' ' || *value=='\t') ++value;
        if(strlen(value)>=1024) goto done;
        if(strcmp(key,"exec") && value[0]=='"' && strlen(value)>1 && value[strlen(value)-1]=='"') { value[strlen(value)-1]=0;++value; }
        if(!strcmp(key,"name") && (!current || *current->name)) {
            if(count==128) goto done;current=&next[count++];
        }
        if(!current) goto done;
        if(!strcmp(key,"name")) {
            if(strlen(value)>=sizeof(current->name) || strpbrk(value," \t\r\n;\"")) goto done;
            Q_strncpyz(current->name,value,sizeof(current->name));Q_strlwr(current->name);
        } else if(!strcmp(key,"exec")) Q_strncpyz(current->exec,value,sizeof(current->exec));
        else if(!strcmp(key,"desc")) Q_strncpyz(current->description,value,sizeof(current->description));
        else if(!strcmp(key,"levels")) {
            char *v=value,*separator;current->levelCount=0;
            for(separator=value;*separator;++separator) if(*separator==',') *separator=' ';
            while(*(token=COM_Parse(&v))) {
                int number;if(current->levelCount==64 || !Number(token,&number)) goto done;
                current->levels[current->levelCount++]=number;
            }
        } else goto done;
    }
    for(i=0;i<count;++i) { int j;if(!*next[i].name || !*next[i].exec) goto done;for(j=0;j<i;++j) if(!strcmp(next[i].name,next[j].name)) goto done; }
    memcpy(customCommands,next,sizeof(customCommands));customCommandCount=count;ok=1;
done:
    trap_FS_FCloseFile(f);free(buffer);free(next);
    if(!ok) G_Printf("[Admin] Invalid %s; custom commands disabled\n",filename);
    else G_Printf("[Admin] Loaded %d custom commands from %s\n",count,filename);
    return ok;
}
static int CustomAllowed(int n,int index) {
    int i,number;
    if(NITMOD_DBUserCount()<0 || !levelsReady) return 0;
    number=G_NITMOD_AdminLevel(n);
    if(n<0) return 1;
    for(i=0;i<customCommands[index].levelCount;++i) if(customCommands[index].levels[i]==number) return 1;
    return 0;
}
/* Exact custom names take priority, then exact builtins; abbreviations must
 * be unique across the entire original table, even for unported handlers. */
static const char *ResolveAdminCommand(const char *name,int *custom) {
    int i,matches=0;const char *found=NULL;size_t length=strlen(name);*custom=-1;
    if(!length) return NULL;
    for(i=0;i<customCommandCount;++i) if(!Q_stricmp(name,customCommands[i].name)) { *custom=i;return customCommands[i].name; }
    for(i=0;i<78;++i) if(!Q_stricmp(name,nitmodAdminCommands[i].name)) return nitmodAdminCommands[i].name;
    for(i=0;i<78;++i) if(!Q_stricmpn(name,nitmodAdminCommands[i].name,length)) { ++matches;found=nitmodAdminCommands[i].name; }
    for(i=0;i<customCommandCount;++i) if(!Q_stricmpn(name,customCommands[i].name,length)) { ++matches;found=customCommands[i].name;*custom=i; }
    return matches==1?found:NULL;
}
static int ExecuteCustom(int n,int index,int argc,char args[][1024]) {
    static char expanded[16384],output[16384];const char *p;int used=0;
    if(!CustomAllowed(n,index)) { Print(n,va("^x%s: ^1Permission denied\n",customCommands[index].name));return 1; }
    G_NITMOD_ExpandCommandShortcuts(n>=0?&g_entities[n]:NULL,customCommands[index].exec,expanded,sizeof(expanded));
    for(p=expanded;*p;) {
        char value[36];const char *v=NULL;
        if(p[0]=='[' && p[1]>='1' && p[1]<='9' && p[2]==']') {
            int arg=p[1]-'0';Q_strncpyz(value,arg<argc?args[arg]:"",sizeof(value));v=value;p+=3;
        } else if(n>=0 && !strncmp(p,"[i]",3)) { Com_sprintf(value,sizeof(value),"%d",n);v=value;p+=3; }
        if(v) {
            for(;*v;++v) {
                /* Argument substitutions are data, never extra console commands. */
                if(*v==';' || *v=='\n' || *v=='\r' || *v=='"' || *v=='\\') continue;
                if(used>=sizeof(output)-2) goto overflow;output[used++]=*v;
            }
        } else { if(used>=sizeof(output)-2) goto overflow;output[used++]=*p++; }
    }
    output[used++]='\n';output[used]=0;trap_SendConsoleCommand(EXEC_APPEND,output);return 1;
overflow:
    Print(n,"^1Custom command expansion is too long\n");return 1;
}
static int SupportedAdminCommand(const char *cursor) { if(!Q_stricmp(cursor,"glow") || !Q_stricmp(cursor,"give") || !Q_stricmp(cursor,"pants") || !Q_stricmp(cursor,"listplayers") || !Q_stricmp(cursor,"blind") || !Q_stricmp(cursor,"unblind") || !Q_stricmp(cursor,"stats") || !Q_stricmp(cursor,"nade") || !Q_stricmp(cursor,"pip") || !Q_stricmp(cursor,"pop") || !Q_stricmp(cursor,"disguise") || !Q_stricmp(cursor,"medpack") || !Q_stricmp(cursor,"ammopack") || !Q_stricmp(cursor,"warn") || !Q_stricmp(cursor,"finger") || !Q_stricmp(cursor,"about") || !Q_stricmp(cursor,"slap") || !Q_stricmp(cursor,"burn") || !Q_stricmp(cursor,"poison") || !Q_stricmp(cursor,"fling") || !Q_stricmp(cursor,"throw") || !Q_stricmp(cursor,"launch") || !Q_stricmp(cursor,"revive") || !Q_stricmp(cursor,"disorient") || !Q_stricmp(cursor,"orient") || !Q_stricmp(cursor,"kick") || !Q_stricmp(cursor,"news") || !Q_stricmp(cursor,"gibme") || !Q_stricmp(cursor,"splat") || !Q_stricmp(cursor,"splata") || !Q_stricmp(cursor,"lock") || !Q_stricmp(cursor,"unlock") || !Q_stricmp(cursor,"rename") || !Q_stricmp(cursor,"freeze") || !Q_stricmp(cursor,"unfreeze")) return 1; return !(Q_stricmp(cursor,"time") && Q_stricmp(cursor,"uptime") && Q_stricmp(cursor,"cancelvote") && Q_stricmp(cursor,"passvote") && Q_stricmp(cursor,"nextmap") && Q_stricmp(cursor,"panzerwar") && Q_stricmp(cursor,"sniperwar") && Q_stricmp(cursor,"crazygravity") && Q_stricmp(cursor,"help") && Q_stricmp(cursor,"pause") && Q_stricmp(cursor,"unpause") && Q_stricmp(cursor,"shuffle") && Q_stricmp(cursor,"swap") && Q_stricmp(cursor,"swap_restart") && Q_stricmp(cursor,"restart") && Q_stricmp(cursor,"reset") && Q_stricmp(cursor,"put") && Q_stricmp(cursor,"spec") && Q_stricmp(cursor,"spec999") && Q_stricmp(cursor,"setlevel") && Q_stricmp(cursor,"admintest") && Q_stricmp(cursor,"records") &&
       Q_stricmp(cursor,"readconfig") && Q_stricmp(cursor,"dbsave") && Q_stricmp(cursor,"ban") && Q_stricmp(cursor,"banguid") &&
       Q_stricmp(cursor,"mute") && Q_stricmp(cursor,"unmute") && Q_stricmp(cursor,"unban") && Q_stricmp(cursor,"showbans") &&
       Q_stricmp(cursor,"userlist") && Q_stricmp(cursor,"userinfo") && Q_stricmp(cursor,"useredit") && Q_stricmp(cursor,"userdelete") && Q_stricmp(cursor,"seen") &&
       Q_stricmp(cursor,"levadd") && Q_stricmp(cursor,"levdelete") && Q_stricmp(cursor,"levlist") && Q_stricmp(cursor,"levinfo") && Q_stricmp(cursor,"levedit") && Q_stricmp(cursor,"delrecords") && Q_stricmp(cursor,"resetxp") && Q_stricmp(cursor,"resetmyxp")); }
typedef struct {
    int enabled, attempted;
    char command[64], invoked[64], arguments[1024];
} adminLogRequest_t;

/* Original _shrubbot_log: one append per dispatched or denied command. */
static void AdminCommandLog(int clientNum, const adminLogRequest_t *request) {
    char path[MAX_QPATH], name[MAX_NETNAME], guid[33], info[MAX_INFO_STRING];
    char timestamp[20], line[1024];
    fileHandle_t file = 0;
    qtime_t now;
    if (!request->enabled) return;
    G_NITMOD_LegacyCvarString("g_logAdmin", path, sizeof(path), "");
    if (!path[0]) return;
    if (trap_FS_FOpenFile(path, &file, FS_APPEND) < 0 || !file) {
        G_Printf("_shrubbot_log: error could not open %s\n", path);
        return;
    }
    if (trap_RealTime(&now) == -1) Q_strncpyz(timestamp, "Time error!", sizeof(timestamp));
    else Com_sprintf(timestamp, sizeof(timestamp), "%04d-%02d-%02d %02d:%02d:%02d",
        now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
    Q_strncpyz(name, "console", sizeof(name));
    Q_strncpyz(guid, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", sizeof(guid));
    if (clientNum >= 0 && clientNum < level.maxclients && g_entities[clientNum].client) {
        Q_strncpyz(name, g_entities[clientNum].client->pers.netname, sizeof(name));
        Q_CleanStr(name);
        if (!name[0]) Q_strncpyz(name, "console", sizeof(name));
        trap_GetUserinfo(clientNum, info, sizeof(info));
        Q_strncpyz(guid, Info_ValueForKey(info, "n_guid"), sizeof(guid));
    }
    if (request->attempted)
        Com_sprintf(line, sizeof(line), "%s [%2i] [%s '%s']: attempted \"%s%s%s\"\n",
            timestamp, clientNum, guid, name, request->invoked,
            request->arguments[0] ? " " : "", request->arguments);
    else
        Com_sprintf(line, sizeof(line), "%s [%2i] [%s '%s']: %s %s\n",
            timestamp, clientNum, guid, name, request->command, request->arguments);
    trap_FS_Write(line, strlen(line), file);
    trap_FS_FCloseFile(file);
}

static int DispatchAdminCommand(int n,const char *command,adminLogRequest_t *log) {

    static char args[16][1024]; /* engine command dispatch is single threaded */
    char *cursor,*token; int argc=0,i,target,number,custom; const char *resolved; nitmodDatabaseAccount_t account,actor;
    if(!Q_stricmp(command,"say") || ((!Q_stricmp(command,"say_team") || !Q_stricmp(command,"say_buddy")) && G_NITMOD_AdminPrivilege(n,"teamcmds"))) {
        char text[MAX_STRING_CHARS],part[MAX_STRING_CHARS]; text[0]=0;
        for(i=1;i<trap_Argc();++i) { trap_Argv(i,part,sizeof(part)); if(i>1) Q_strcat(text,sizeof(text)," "); Q_strcat(text,sizeof(text),part); }
        if(text[0]!='!') return 0;
        cursor=text; while(argc<16 && *(token=COM_Parse(&cursor))) Q_strncpyz(args[argc++],token,sizeof(args[0]));
    } else {
        if(n>=0 && *command!='!') return 0;
        argc=trap_Argc(); if(argc>16) argc=16;
        for(i=0;i<argc;++i) trap_Argv(i,args[i],sizeof(args[i]));
    }
    if(!argc) return 0;
    Q_strncpyz(log->invoked,args[0],sizeof(log->invoked));
    cursor=args[0]; if(*cursor=='!') ++cursor; Q_strlwr(cursor);
    resolved=ResolveAdminCommand(cursor,&custom);if(!resolved) return 0;
    if(!G_NITMOD_DatabaseReady() || levelSavePending) {
        Print(n,"^9Database operation pending; retry this command after completion.\n");return 1;
    }
    Q_strncpyz(log->command,cursor,sizeof(log->command));
    for(i=1;i<argc;++i) { if(i>1) Q_strcat(log->arguments,sizeof(log->arguments)," ");Q_strcat(log->arguments,sizeof(log->arguments),args[i]); }
    if(custom>=0) { log->enabled=1;log->attempted=!CustomAllowed(n,custom);return ExecuteCustom(n,custom,argc,args); }
    cursor=(char *)resolved;
    if(!SupportedAdminCommand(cursor)) return 0;
    log->enabled=1;
    if(!G_NITMOD_AdminAllowed(n,cursor)) { log->attempted=1;Print(n,va("^x%s: ^1Permission denied\n",cursor)); return 1; }

    if(!strcmp(cursor,"glow")) {
        int all,j,count,changed=0;
        if(argc<2) { Print(n,"^9usage: ^g!glow [name|slot#|-1]^7\n");return 1; }
        all=!strcmp(args[1],"-1");target=all?-1:Target(args[1]);
        if(!all && target<0) { Print(n,"^1glow: ^9No unique player\n");return 1; }
        count=all?level.numNonSpectatorClients:1;if(count>MAX_CLIENTS) count=MAX_CLIENTS;
        for(j=0;j<count;++j) {
            gclient_t *client;if(all) target=level.sortedClients[j];
            if(target<0 || target>=MAX_CLIENTS || !g_entities[target].client) continue;
            client=g_entities[target].client;
            if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { if(!all) Print(n,"^1glow error: ^9Specified player has a higher admin level than you do.^7\n");continue; }
            if(!all && client->sess.sessionTeam!=TEAM_AXIS && client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,"^1glow error: ^9player must be on a team^7\n");return 1; }
            if(all && client->nitmodGlowing) continue;
            client->nitmodGlowing=all?qtrue:!client->nitmodGlowing;G_NITMOD_UpdateAdminGlow(&g_entities[target]);++changed;
            if(!all) trap_SendServerCommand(-1,va("cpm \"^xglow: ^7%s ^9%s^7\"",client->pers.netname,client->nitmodGlowing?"is now glowing":"stopped glowing"));
        }
        if(all) trap_SendServerCommand(-1,va("cpm \"^xglow: %d ^9players are now glowing^7\"",changed));
        return 1;
    }

    if(!strcmp(cursor,"give")) {
        char name[1024],arg[1024],extra[1024];int war=G_NITMOD_ConfiguredWarMode();
        if(argc<2) { Print(n,"^9usage: ^g!give [name|slot#] [item] [args]^7\n");return 1; }
        if(war>=1 && war<=4) { Print(n,"^1give error: ^9Not allowed during panzerwar/sniperwar !^7\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1give: ^9No unique player\n");return 1; }
        name[0]=arg[0]=extra[0]=0;
        for(i=2;i<argc;++i) { if(i>2) Q_strcat(name,sizeof(name)," ");Q_strcat(name,sizeof(name),args[i]); }
        for(i=3;i<argc;++i) { if(i>3) Q_strcat(arg,sizeof(arg)," ");Q_strcat(arg,sizeof(arg),args[i]); }
        for(i=4;i<argc;++i) { if(i>4) Q_strcat(extra,sizeof(extra)," ");Q_strcat(extra,sizeof(extra),args[i]); }
        G_NITMOD_ExecGive(&g_entities[target],name,arg,extra);return 1;
    }

    if(!strcmp(cursor,"pants")) {
        int all,j,count,changed=0;
        if(argc<2) { Print(n,"^9usage: ^g!pants [name|slot#|-1]^7\n");return 1; }
        all=!strcmp(args[1],"-1");target=all?-1:Target(args[1]);
        if(!all && target<0) { Print(n,"^1pants: ^9No unique player\n");return 1; }
        count=all?level.numNonSpectatorClients:1;if(count>MAX_CLIENTS) count=MAX_CLIENTS;
        for(j=0;j<count;++j) {
            gclient_t *client;if(all) target=level.sortedClients[j];
            if(target<0 || target>=MAX_CLIENTS || !g_entities[target].client) continue;
            client=g_entities[target].client;
            if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { if(!all) Print(n,"^1pants error: ^9Specified player has a higher admin level than you do.^7\n");continue; }
            if(client->ps.eFlags & NITMOD_EF_STRIPPED) { if(!all) Print(n,"^1pants error: ^9Player is already stripped^7\n");continue; }
            if(!all && client->sess.sessionTeam!=TEAM_AXIS && client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,"^1pants error: ^9Player must be on a team^7\n");return 1; }
            if(all?g_entities[target].health<=0:g_entities[target].health==0) { if(!all) Print(n,"^1pants error: ^9Player must be alive^7\n");continue; }
            client->ps.eFlags|=NITMOD_EF_STRIPPED;++changed;
            if(!all) trap_SendServerCommand(-1,va("cpm \"^xpants: ^7%s ^9was stripped^7\"",client->pers.netname));
        }
        if(all) trap_SendServerCommand(-1,va("cpm \"^xpants: %d ^9players stripped^7\"",changed));
        return 1;
    }

    if(!strcmp(cursor,"listplayers")) {
        int team,j,count=level.numConnectedClients;
        static const char *headings[]={"", "^9----------------------^_AXIS^9-----------------------\n", "^9---------------------^4ALLIES^9----------------------\n", "^9-------------------^xSPECTATORS^9--------------------\n"};
        if(count<1) { Print(n,"^9No players connected\n");return 1; }
        if(count>MAX_CLIENTS) count=MAX_CLIENTS;
        Print(n,"^9  # | L  | NAME                                  \n");
        for(team=TEAM_AXIS;team<=TEAM_SPECTATOR;++team) {
            int heading=0;
            for(j=0;j<count;++j) {
                gclient_t *client;int displayLevel,muted;
                target=level.sortedClients[j];if(target<0 || target>=MAX_CLIENTS || !g_entities[target].client) continue;
                client=g_entities[target].client;if(client->sess.sessionTeam!=team) continue;
                if(!heading) { Print(n,headings[team]);heading=1; }
                displayLevel=G_NITMOD_AdminPrivilege(target,"incognito")?0:G_NITMOD_AdminLevel(target);
                muted=client->sess.muted || G_NITMOD_AccountMuted(target);
                Print(n,va(" ^%s%2i ^9| ^g%-2i ^9| ^7%s\n",muted?"1":"g",target,displayLevel,client->pers.netname));
            }
        }
        Print(n,"^9-------------------------------------------------\n");
        Print(n,"^9Info : ^gred slot# = player muted\n");
        Print(n,va("^x%d ^9players connected\n",level.numConnectedClients));
        return 1;
    }

    if(!strcmp(cursor,"blind") || !strcmp(cursor,"unblind")) {
        int all,j,count,changed=0,blind=!strcmp(cursor,"blind");
        if(argc<2) { Print(n,va("^9usage: ^g!%s [name|slot#|-1]^7\n",cursor));return 1; }
        all=!strcmp(args[1],"-1");
        target=all?-1:Target(args[1]);
        if(!all && target<0) { Print(n,va("^1%s: ^9No unique player\n",cursor));return 1; }
        count=all?level.numNonSpectatorClients:1;if(count>MAX_CLIENTS) count=MAX_CLIENTS;
        for(j=0;j<count;++j) {
            gclient_t *client;
            if(all) target=level.sortedClients[j];
            if(target<0 || target>=MAX_CLIENTS || !g_entities[target].client) continue;
            client=g_entities[target].client;
            if((blind || all) && n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) {
                if(!all) Print(n,va("^1%s error: ^9Specified player has a higher admin level than you.^7\n",cursor));continue;
            }
            if(!all && blind && client->sess.sessionTeam==TEAM_SPECTATOR) { Print(n,"^1blind error: ^9Can't blind spectators\n");return 1; }
            if(!all && client->nitmodBlinded==blind) { Print(n,va("^1%s error: ^7%s ^9is %sblind^7\n",cursor,client->pers.netname,blind?"already ":"not "));return 1; }
            client->nitmodBlinded=blind;
            if(blind) client->ps.powerups[PW_BLACKOUT]|=NITMOD_BLACKOUT_ADMIN;
            else client->ps.powerups[PW_BLACKOUT]&=~NITMOD_BLACKOUT_ADMIN;
            ++changed;
            if(!all) trap_SendServerCommand(-1,va("cpm \"^x%s: ^7%s ^9%s\"",cursor,client->pers.netname,blind?"is now blind":"can see again"));
        }
        if(all) trap_SendServerCommand(-1,va("cpm \"^x%s: ^7%d ^9players %s^7\"",cursor,changed,blind?"are now blind":"can see again"));
        return 1;
    }

    if(!strcmp(cursor,"stats")) {
        int width=4,j;char clean[MAX_NAME_LENGTH];
        Print(n,"^xstats: ^9Showing ^gThompson^9 and ^gMP40 ^9stats of all connected players\n");
        for(j=0;j<level.maxclients && j<MAX_CLIENTS;++j) if(g_entities[j].client && g_entities[j].client->pers.connected==CON_CONNECTED) {
            Q_strncpyz(clean,g_entities[j].client->pers.netname,sizeof(clean));Q_CleanStr(clean);
            if((int)strlen(clean)>width) width=strlen(clean);
        }
        Print(n,va("^x%*s SHOTS  HITS   ACC  HEAD    HR\n",width,"^gNAME"));
        for(j=0;j<level.maxclients && j<MAX_CLIENTS;++j) if(g_entities[j].client && g_entities[j].client->pers.connected==CON_CONNECTED) {
            gclient_t *client=g_entities[j].client;
            int shots=(int)(client->sess.aWeaponStats[WS_MP40].atts+client->sess.aWeaponStats[WS_THOMPSON].atts);
            int hits=(int)(client->sess.aWeaponStats[WS_MP40].hits+client->sess.aWeaponStats[WS_THOMPSON].hits);
            int heads=(int)(client->sess.aWeaponStats[WS_MP40].headshots+client->sess.aWeaponStats[WS_THOMPSON].headshots);
            float acc=shots>0 && hits>=0?(float)hits*100.0f/shots:0;
            float hr=hits>0 && heads>=0?(float)heads*100.0f/hits:0;
            int padded;
            if(acc>999.9f) acc=999.9f;if(hr>999.9f) hr=999.9f;
            Q_strncpyz(clean,client->pers.netname,sizeof(clean));Q_CleanStr(clean);
            padded=width+(int)strlen(client->pers.netname)-(int)strlen(clean);
            Print(n,va("^7%*s ^2%5i %5i ^%c%5.1f ^2%5i ^%c%5.1f\n",padded,client->pers.netname,shots,hits,acc>=40?'1':acc>=30?'3':'2',(double)acc,heads,hr>=12.5f?'1':hr>=7.5f?'3':'2',(double)hr));
        }
        return 1;
    }

    if(!strcmp(cursor,"nade")) {
        static int lastNade;
        int matches[MAX_CLIENTS],count,j,amount=0,all,available,changed=0;
        char amountText[4];
        if((long long)level.time-lastNade<600) { Print(n,"^1nade error: ^9denied by entities overflow protection.^7\n");return 1; }
        lastNade=level.time;
        if(argc>2) { Q_strncpyz(amountText,args[2],sizeof(amountText));amount=atoi(amountText);if(amount<1) amount=1;else if(amount>16) amount=16; }
        if(argc<2) { Print(n,"^9usage: ^g!nade [name|slot#|-1] [nades]^7\n");return 1; }
        all=!strcmp(args[1],"-1");
        if(all) { count=level.numNonSpectatorClients;if(count>MAX_CLIENTS) count=MAX_CLIENTS;for(j=0;j<count;++j) matches[j]=level.sortedClients[j]; }
        else count=Targets(args[1],matches);
        if(!all && !count) { Print(n,"^1nade: ^9No matching player\n");return 1; }
        available=MAX_GENTITIES-level.num_entities;
        for(j=MAX_CLIENTS;j<level.num_entities && j<MAX_GENTITIES;++j) if(!g_entities[j].inuse) ++available;
        if((all || count>1) && available-amount*(all?level.numConnectedClients*2:count*3)<=63) {
            Print(n,"^1nade error: ^9too many entities, use fewer nades or nade fewer players.^7\n");return 1;
        }
        for(j=0;j<count;++j) {
            target=matches[j];if(target<0 || target>=MAX_CLIENTS || !g_entities[target].client) continue;
            if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { if(!all) Print(n,"^1nade error: ^9Specified player has a higher admin level than you do.^7\n");continue; }
            if(!all && (g_entities[target].client->sess.sessionTeam==TEAM_SPECTATOR || (count>1 && g_entities[target].client->sess.sessionTeam!=TEAM_AXIS && g_entities[target].client->sess.sessionTeam!=TEAM_ALLIES))) {
                Print(n,"^1nade error: ^9Player must be on a team to be naded^7\n");continue;
            }
            G_NITMOD_CreateClusterNade(&g_entities[target],all || !amount?1:amount,qtrue);++changed;
            if(!all) trap_SendServerCommand(-1,va("cpm \"^xnade: ^7%s ^9was naded^7\"",g_entities[target].client->pers.netname));
        }
        if(all) trap_SendServerCommand(-1,va("cpm \"^xnade: ^7%d players naded^7\"",changed));
        return 1;
    }

    if(!strcmp(cursor,"pop") || !strcmp(cursor,"pip")) {
        int pip=!strcmp(cursor,"pip");
        int matches[MAX_CLIENTS],count,j,changed=0,all=argc>1 && !strcmp(args[1],"-1");
        vec3_t direction={5,5,5};
        if(all) {
            count=level.numNonSpectatorClients;if(count>MAX_CLIENTS) count=MAX_CLIENTS;
            for(j=0;j<count;++j) matches[j]=level.sortedClients[j];
        } else count=Targets(argc>1?args[1]:"",matches);
        if(!count && !all) { Print(n,va("^1%s: ^9No matching player\n",cursor));return 1; }
        for(j=0;j<count;++j) {
            target=matches[j];if(target<0 || target>=MAX_CLIENTS || !g_entities[target].client) continue;
            if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) {
                if(!all) Print(n,va("^1%s error: ^9Specified player has a higher admin level than you do.^7\n",cursor));continue;
            }
            if(all && !pip) {
                if(g_entities[target].client->ps.eFlags & EF_HEADSHOT) continue;
                g_entities[target].client->ps.eFlags|=EF_HEADSHOT;
            } else if(!all && g_entities[target].client->sess.sessionTeam!=TEAM_AXIS && g_entities[target].client->sess.sessionTeam!=TEAM_ALLIES) {
                Print(n,va("^1%s error: ^9Player must be on a team^7\n",cursor));continue;
            }
            if(pip) {
                gentity_t *event=G_NITMOD_TempEventOriginal(g_entities[target].r.currentOrigin,61);
                VectorCopy(g_entities[target].r.currentOrigin,event->s.origin);event->s.origin[2]-=6;
                VectorCopy(g_entities[target].r.currentAngles,event->s.angles);
                event->s.density=5000;event->s.frame=6000;
                VectorSet(event->s.angles2,18,18,0.5f);
            } else G_AddEvent(&g_entities[target],EV_LOSE_HAT,DirToByte(direction));
            ++changed;
            if(!all) trap_SendServerCommand(-1,va("cpm \"^x%s: ^7%s ^9was %s'd^7\"",cursor,g_entities[target].client->pers.netname,cursor));
        }
        if(all) trap_SendServerCommand(-1,va("cpm \"^x%s: %d ^9players %s'd\"",cursor,changed,cursor));
        return 1;
    }

    if(!strcmp(cursor,"disguise")) {
        gclient_t *client;long disguise;
        if(argc<3) { Print(n,"^9usage: ^g!disguise [name|slot#] [class]^7\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1disguise: ^9No unique player\n");return 1; }
        client=g_entities[target].client;
        if(client->sess.sessionTeam!=TEAM_AXIS && client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,"^1disguise error: ^9Player must be on a team.^7\n");return 1; }
        disguise=strtol(args[2],NULL,10);if(disguise < -1) disguise=-1;else if(disguise>4) disguise=4;
        if(!Q_stricmpn(args[2],"m",1)) disguise=PC_MEDIC;
        else if(!Q_stricmpn(args[2],"e",1)) disguise=PC_ENGINEER;
        else if(!Q_stricmpn(args[2],"f",1)) disguise=PC_FIELDOPS;
        else if(!Q_stricmpn(args[2],"c",1)) disguise=PC_COVERTOPS;
        else if(!Q_stricmpn(args[2],"s",1)) disguise=PC_SOLDIER;
        else if(args[2][0]=='-') disguise=-1;
        if(disguise==-1) { client->ps.powerups[PW_OPS_DISGUISED]=0;Print(target,"^9givedisguise : ^7Removing disguise\n");return 1; }
        client->ps.powerups[PW_OPS_DISGUISED]=1;
        client->ps.powerups[PW_OPS_CLASS_1]=disguise & 1;
        client->ps.powerups[PW_OPS_CLASS_2]=disguise & 2;
        client->ps.powerups[PW_OPS_CLASS_3]=disguise & 4;
        Q_strncpyz(client->disguiseNetname,client->pers.netname,sizeof(client->disguiseNetname));
        client->disguiseRank=client->sess.rank;
        Print(target,va("^9givedisguise : ^7%s\n",BG_ClassnameForNumber(disguise)));
        ClientUserinfoChanged(target);return 1;
    }

    if(!strcmp(cursor,"medpack") || !strcmp(cursor,"ammopack")) {
        vec3_t velocity;
        if(n<0) return 0;
        velocity[0]=(float)(((double)(rand() & 32767)/32767.0-0.5)*2.0)*100.0f;
        velocity[1]=(float)(((double)(rand() & 32767)/32767.0-0.5)*2.0)*100.0f;
        velocity[2]=G_NITMOD_LegacyCvarInteger("g_throwDistance",75);
        if(!strcmp(cursor,"medpack")) Weapon_MedicAdmin(&g_entities[n],g_entities[n].r.currentOrigin,velocity);
        else Weapon_MagicAmmoAdmin(&g_entities[n],g_entities[n].r.currentOrigin,velocity);
        return 1;
    }

    if(!strcmp(cursor,"warn")) {
        char reason[1024];
        if(argc<3) { Print(n,"^9usage: ^g!warn [name|slot#] [reason]^7\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1warn: ^9No unique player\n");return 1; }
        if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,"^1warn error: ^9Specified player has a higher admin level than you do.^7\n");return 1; }
        reason[0]=0;for(i=2;i<argc;++i) { if(i>2) Q_strcat(reason,sizeof(reason)," ");Q_strcat(reason,sizeof(reason),args[i]); }
        nitmod_Sound_Global(12);
        trap_SendServerCommand(-1,va("cpm \"^xwarn: ^7%s ^9was warned^7\"",g_entities[target].client->pers.netname));
        trap_SendServerCommand(target,va("cp \"^7%s ^xwarned ^9you because:\n^x%s\"",n<0?"^3SERVER CONSOLE":g_entities[n].client->pers.netname,reason));return 1;
    }

    if(!strcmp(cursor,"finger")) {
        char info[MAX_INFO_STRING],value[256];int hasAccount;gclient_t *client;
        if(argc!=2) { Print(n,"^9usage: ^g!finger [name|slot#]\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1finger: ^9No unique player\n");return 1; }
        client=g_entities[target].client;hasAccount=G_NITMOD_ClientAccount(target,&account);
        trap_GetUserinfo(target,info,sizeof(info));
        Print(n,va("^9Information about ^7%s\n",client->pers.netname));
        Print(n,va("^9Slot:   ^g%i\n",target));
        if(client->sess.sessionTeam==TEAM_SPECTATOR) Print(n,va("^9Team:   ^7%s\n",TeamName(TEAM_SPECTATOR)));
        else Print(n,va("^9Team:   ^7%s ^9(^7%s^9)\n",TeamName(client->sess.sessionTeam),BG_ClassnameForNumber(client->sess.playerType)));
        Q_strncpyz(value,hasAccount?account.user.guid:Info_ValueForKey(info,"n_guid"),sizeof(value));
        Print(n,strlen(value)==32?va("^9NGUID:  ^g%s\n",value):"^9NGUID:  ^1INVALID\n");
        Print(n,va("^9IP:     ^g%s\n",hasAccount?account.ip:Info_ValueForKey(info,"ip")));
        Print(n,va("^9MAC:    ^g%s\n",hasAccount?account.mac:G_NITMOD_AccountMAC(target)));
        Q_strncpyz(value,Info_ValueForKey(info,"etVersion"),sizeof(value));if(value[0]) Print(n,va("^9Client: ^g%s\n",value));
        Q_strncpyz(value,Info_ValueForKey(info,"build"),sizeof(value));if(value[0]) Print(n,va("^9Mod build: ^g%s\n",value));
        if(hasAccount) {
            Print(n,va("^9Level:  ^g%i^7\n",G_NITMOD_AdminLevel(target)));
            Print(n,va("^9GText:  ^g%s\n",account.gtext));Print(n,va("^9GAudio: ^g%s\n",account.gsound));
            if(account.login[0]) Print(n,va("^2Registered user\n^9Username: ^g%s\n",account.login));
        } else Print(n,"Admin information temporarly unavailable.\n");
        return 1;
    }

    if(!strcmp(cursor,"about")) {
        const char *platform;
#ifdef __EMSCRIPTEN__
        platform="wasm32";
#elif defined(CPUSTRING)
        platform=CPUSTRING;
#else
        platform="unknown";
#endif
        Print(n,"^9-- Mod informations\n");
        Print(n," ^9Version : ^7N^1!^7tmod ^g2.3.5\n");
        Print(n," ^9Website : ^getmods.net \n");
        Print(n,va(" ^9Build : ^g%s %s\n",platform,__DATE__));
        Print(n,va(" ^9SQLite version : ^g%s\n",sqlite3_libversion()));
        Print(n,"^9-- Dev. Team\n");
        Print(n," ^7N^1!^7trox^0*^9: ^gProject lead, programmer\n");
        Print(n," ^hN^7ico^h$^9: ^gProgrammer\n");
        Print(n," ^77Killer^9: ^gProgrammer\n");return 1;
    }

    if(!strcmp(cursor,"slap")) {
        char amount[4];int damage;gentity_t *victim,*event;
        if(argc<2) { Print(n,"^9usage: ^g!slap [name|slot#] (damage)^7\n");return 1; }
        Q_strncpyz(amount,argc>2?args[2]:"",sizeof(amount));damage=(int)strtol(amount,NULL,10);if(damage<1) damage=20;
        target=Target(args[1]);if(target<0) { Print(n,"^1slap: ^9No unique player\n");return 1; }
        if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,"^1slap error: ^9Specified player has a higher admin level than you do.^7\n");return 1; }
        victim=&g_entities[target];
        if(victim->client->sess.sessionTeam!=TEAM_AXIS && victim->client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,"^1slap error: ^9Player must be on a team.^7\n");return 1; }
        if(victim->health<=0 || (victim->client->ps.pm_flags&PMF_LIMBO)) { Print(n,va("^1slap error: ^7%s ^9is dead.^7\n",victim->client->pers.netname));return 1; }
        victim->health=victim->health>damage?victim->health-damage:1;
        event=G_NITMOD_TempEventOriginal(victim->client->ps.origin,102);
        event->s.onFireStart=2;event->r.svFlags=SVF_BROADCAST|SVF_SINGLECLIENT;event->r.singleClient=target;
        trap_SendServerCommand(-1,va("cpm \"^xslap: ^7%s ^9was slapped^7\"",victim->client->pers.netname));return 1;
    }

    if(!strcmp(cursor,"burn")) {
        if(argc<2 || !strcmp(args[1],"-1")) {
            int affected=0;
            for(i=0;i<level.numNonSpectatorClients && i<MAX_CLIENTS;++i) {
                target=level.sortedClients[i];if(target<0 || target>=MAX_CLIENTS || !g_entities[target].client) continue;
                if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) continue;
                G_BurnMeGood(&g_entities[target],&g_entities[target]);++affected;
            }
            trap_SendServerCommand(-1,va("cpm \"^xburn: %d ^9players burned^7\"",affected));return 1;
        }
        target=Target(args[1]);if(target<0) { Print(n,"^1burn: ^9No unique player\n");return 1; }
        if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,"^1burn error: ^9Specified player has a higher admin level than you do.^7\n");return 1; }
        if(g_entities[target].client->sess.sessionTeam!=TEAM_AXIS && g_entities[target].client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,"^1burn error: ^9player must be on a team^7\n");return 1; }
        G_BurnMeGood(&g_entities[target],&g_entities[target]);
        trap_SendServerCommand(-1,va("cpm \"^xburn: ^7%s ^9was set ablaze^7\"",g_entities[target].client->pers.netname));return 1;
    }

    if(!strcmp(cursor,"poison")) {
        gclient_t *client;
        if(argc<2) { Print(n,"^9usage: ^g!poison [name|slot#]^7\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1poison: ^9No unique player\n");return 1; }
        if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,"^1poison error: ^9Specified player has a higher admin level than you do.^7\n");return 1; }
        client=g_entities[target].client;
        if(client->sess.sessionTeam!=TEAM_AXIS && client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,"^1poison error: ^9Player must be on a team.^7\n");return 1; }
        client->ps.eFlags|=NITMOD_EF_POISONED;
        client->nitmodPoisonAttacker=g_entities[target].s.number;
        client->nitmodPoisonStacks=1;client->nitmodPoisonNextTick=level.time;
        trap_SendServerCommand(-1,va("cpm \"^xpoison: ^7%s ^9was poisoned^7\"",client->pers.netname));return 1;
    }

    if(!strcmp(cursor,"fling") || !strcmp(cursor,"throw") || !strcmp(cursor,"launch")) {
        int mode=!strcmp(cursor,"throw")?1:!strcmp(cursor,"launch")?2:0;
        int matches[MAX_CLIENTS],count=0,affected=0;const char *verb=mode==1?"thrown":mode==2?"launched":"flung";
        if(argc>1) {
            count=Targets(args[1],matches);
            if(!count) { Print(n,va("^1%s: ^9No matching player\n",cursor));return 1; }
        } else for(i=0;i<level.numNonSpectatorClients && i<MAX_CLIENTS;++i) matches[count++]=level.sortedClients[i];
        for(i=0;i<count;++i) {
            target=matches[i];if(target<0 || target>=MAX_CLIENTS || !g_entities[target].client) continue;
            if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) {
                if(argc>1 && count==1) Print(n,va("^1%s error: ^7%s ^9has a higher admin level than you.^7\n",cursor,g_entities[target].client->pers.netname));
                continue;
            }
            if(FlingClient(&g_entities[target],mode)) {
                ++affected;
                if(argc>1 && count==1) trap_SendServerCommand(-1,va("cpm \"^x%s: ^7%s ^9was %s^7\"",cursor,g_entities[target].client->pers.netname,verb));
            }
        }
        if(argc<2 || count>1) trap_SendServerCommand(-1,va("cpm \"^x%s: %d ^9players %s^7\"",cursor,affected,verb));
        return 1;
    }

    if(!strcmp(cursor,"revive")) {
        target=argc>1?Target(args[1]):-1;
        if(target<0) { Print(n,"^1revive: ^9No unique player\n");return 1; }
        if(g_entities[target].client->sess.sessionTeam!=TEAM_AXIS && g_entities[target].client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,va("^1revive error: ^7%s ^9is not in a team.^7\n",g_entities[target].client->pers.netname));return 1; }
        if(g_entities[target].health>0) { Print(n,va("^1revive error: ^7%s ^9is alive.^7\n\n",g_entities[target].client->pers.netname));return 1; }
        ReviveEntity(NULL,&g_entities[target]);return 1;
    }

    if(!strcmp(cursor,"disorient") || !strcmp(cursor,"orient")) {
        int disorient=!strcmp(cursor,"disorient");gclient_t *client;
        if(argc<2) { Print(n,va("^9usage: ^g!%s [name|slot#]\n",cursor));return 1; }
        target=Target(args[1]);if(target<0) { Print(n,va("^1%s: ^9No unique player\n",cursor));return 1; }
        client=g_entities[target].client;
        if(disorient) {
            if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,"^1disorient error: ^9Specified player has a higher admin level than you do.\n");return 1; }
            if(client->sess.sessionTeam!=TEAM_AXIS && client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,"^1disorient error: ^9Player must be on a team\n");return 1; }
            if(client->nitmodDisoriented) { Print(n,va("^1disorient error: ^7%s ^9is already disoriented\n",client->pers.netname));return 1; }
        } else {
            if(!client->nitmodDisoriented) { Print(n,va("^1orient error: ^7%s ^9is not disoriented\n",client->pers.netname));return 1; }
            if(client->ps.eFlags&NITMOD_EF_POISONED) { Print(n,"^1orient error: ^9Can't orient poisoned players\n");return 1; }
        }
        client->nitmodDisoriented=disorient;
        trap_SendServerCommand(-1,va(disorient?"cpm \"^xdisorient: ^7%s ^9is disoriented\" -1":"cpm \"^xorient: ^7%s ^9is no longer disoriented\"",client->pers.netname));return 1;
    }

    if(!strcmp(cursor,"kick")) {
        char reason[1024];int duration;
        if(argc<(G_NITMOD_AdminAllowed(n,"noreason")?2:3)) { Print(n,"^9usage: ^g!kick [name] [reason]^7\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1kick: ^9No unique player\n");return 1; }
        if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,va("^1kick error: ^7%s ^9is a higher level admin than you are.\n",g_entities[target].client->pers.netname));return 1; }
        if(g_entities[target].client->pers.localClient && (g_entities[target].r.svFlags&SVF_BOT)) { Print(n,"^1kick error: ^9Can't kick server host.\n");return 1; }
        reason[0]=0;for(i=2;i<argc;++i) { if(i>2) Q_strcat(reason,sizeof(reason)," ");Q_strcat(reason,sizeof(reason),args[i]); }
        if(!reason[0]) Q_strncpyz(reason,"^7kicked by admin^7",sizeof(reason));
        duration=G_NITMOD_LegacyCvarInteger("g_autoTempBanTime",1800);
        if(G_NITMOD_LegacyCvarInteger("g_autoTempBan",0) && duration) {
            nitmodDatabasePenalty_t penalty;qtime_t now;int unixTime=trap_RealTime(&now);
            /* Original G_shrubbot_tempban (ELF 0xbda4a): wrapping 32-bit add/sub. */
            int expires=NITMOD_SupportSignedTime((uint32_t)unixTime+(uint32_t)duration-UINT32_C(946490400));
            if(!G_NITMOD_ClientAccount(target,&account)) {
                char userinfo[MAX_INFO_STRING];memset(&account,0,sizeof(account));trap_GetUserinfo(target,userinfo,sizeof(userinfo));
                Q_strncpyz(account.user.guid,Info_ValueForKey(userinfo,"n_guid"),sizeof(account.user.guid));
                Q_strncpyz(account.ip,Info_ValueForKey(userinfo,"ip"),sizeof(account.ip));
                Q_strncpyz(account.mac,G_NITMOD_AccountMAC(target),sizeof(account.mac));
            }
            if(!unixTime || strlen(account.user.guid)!=32) {
                Print(n,"^1kick error: ^9Cannot create temporary ban\n");
            } else {
            memset(&penalty,0,sizeof(penalty));
            Q_strncpyz(penalty.name,g_entities[target].client->pers.netname,36);
            Q_strncpyz(penalty.guid,account.user.guid,sizeof(penalty.guid));
            { char info[MAX_INFO_STRING],ip[64],*port;
              trap_GetUserinfo(target,info,sizeof(info));
              Q_strncpyz(ip,Info_ValueForKey(info,"ip"),sizeof(ip));
              port=strchr(ip,':');if(port)*port=0;
              Q_strncpyz(penalty.ip,ip,sizeof(penalty.ip)); }
            /* G_shrubbot_tempban copies the live client MAC, not the user row. */
            Q_strncpyz(penalty.mac,G_NITMOD_AccountMAC(target),sizeof(penalty.mac));
            Q_strncpyz(penalty.actor,"Temp Ban System",sizeof(penalty.actor));
            Com_sprintf(penalty.reason,sizeof(penalty.reason),"^7You have been kicked, Reason: %s^7",reason);
            Com_sprintf(penalty.made,sizeof(penalty.made),"%02d/%02d/%02d %02d:%02d:%02d",now.tm_mon+1,now.tm_mday,(now.tm_year+1900)%100,now.tm_hour,now.tm_min,now.tm_sec);
            penalty.expires=(int)expires;
            { adminDbCompletion_t ctx;AdminDbContext(&ctx,n,"kick");AdminDbTarget(&ctx,target,4);ctx.dropTime=120;
              Com_sprintf(ctx.drop,sizeof(ctx.drop),"^7You have been kicked, Reason: %s^7",reason);
              PenaltyStore(&penalty,0,1,&ctx);return 1; }
            }
        }
        trap_DropClient(target,va("^7You have been kicked, Reason: %s^7",reason),120);return 1;
    }

    if(!strcmp(cursor,"news")) {
        const char *map=argc>1?args[1]:level.rawmapname;
        G_globalSound(va("sound/vo/%s/news_%s.wav",map,map));return 1;
    }

    if(!strcmp(cursor,"gibme")) {
        gentity_t *ent;
        if(n<0) { Print(n,"^1gibme error: ^9You are on the server console, you can't gib yourself^7\n");return 1; }
        ent=&g_entities[n];
        if((ent->client->ps.pm_flags&PMF_LIMBO) || ent->health<=0) { Print(n,"^1gibme error: ^9You must be alive to use this command^7\n");return 1; }
        if(level.match_pause!=PAUSE_NONE) return 1;
        if(ent->client->sess.sessionTeam==TEAM_SPECTATOR) { Print(n,"^1gibme error: ^9You must be on a team to use ^g!gibme^7\n");return 1; }
        G_Damage(ent,ent,ent,NULL,NULL,0,DAMAGE_NO_PROTECTION|DAMAGE_NO_KNOCKBACK,MOD_GIBME);return 1;
    }

    if(!strcmp(cursor,"splata")) {
        int affected=0;
        for(i=0;i<level.numNonSpectatorClients && i<MAX_CLIENTS;++i) {
            target=level.sortedClients[i];
            if(target<0 || target>=level.maxclients || !g_entities[target].client) continue;
            if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) continue;
            G_Damage(&g_entities[target],NULL,NULL,NULL,NULL,0,DAMAGE_NO_PROTECTION|DAMAGE_NO_KNOCKBACK,MOD_UNKNOWN);++affected;
        }
        trap_SendServerCommand(-1,va("cpm \"^xsplata: ^7%d ^9players splattered^7\"",affected));return 1;
    }
    if(!strcmp(cursor,"splat")) {
        if(argc<2) { Print(n,"^9usage: ^g!splat ^7[name|slot#]^7\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1splat: ^9No unique player\n");return 1; }
        if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,"^1splat error: ^9Specified player has a higher level admin than you.^7\n");return 1; }
        if(g_entities[target].client->sess.sessionTeam!=TEAM_AXIS && g_entities[target].client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,"^1splat error: ^9player isn't on a team^7\n");return 1; }
        G_Damage(&g_entities[target],NULL,NULL,NULL,NULL,0,DAMAGE_NO_PROTECTION|DAMAGE_NO_KNOCKBACK,MOD_UNKNOWN);
        /* Original sends the feedback only to the invoking player. */
        if(n>=0) trap_SendServerCommand(n,va("cpm \"^xsplat: ^7%s ^9went splat^7\"",g_entities[target].client->pers.netname));
        return 1;
    }

    if(!strcmp(cursor,"lock") || !strcmp(cursor,"unlock")) {
        int lock=!strcmp(cursor,"lock"),all;char team[4];const char *label;
        if(argc<2) { Print(n,va("^9usage: ^g!%s [r|b|s|all]^7\n",cursor));return 1; }
        Q_strncpyz(team,args[1],sizeof(team));all=!Q_stricmp(team,"all");
        if(!all && Q_stricmp(team,"r") && Q_stricmp(team,"b") && Q_stricmp(team,"s")) {
            Print(n,va("^9usage: ^g!%s ^7r|b|s|all^7\n",cursor));return 1;
        }
        if(all || !Q_stricmp(team,"r")) teamInfo[TEAM_AXIS].team_lock=lock && TeamCount(-1,TEAM_AXIS)!=0;
        if(all || !Q_stricmp(team,"b")) teamInfo[TEAM_ALLIES].team_lock=lock && TeamCount(-1,TEAM_ALLIES)!=0;
        if(all || !Q_stricmp(team,"s")) {
            G_updateSpecLock(TEAM_AXIS,lock && TeamCount(-1,TEAM_AXIS)!=0);
            G_updateSpecLock(TEAM_ALLIES,lock && TeamCount(-1,TEAM_ALLIES)!=0);
            if(lock) level.server_settings|=CV_SVS_LOCKSPECS;else level.server_settings&=~CV_SVS_LOCKSPECS;
        }
        /* Original updates the teams toggle even for a spectators-only command. */
        if(lock) level.server_settings|=CV_SVS_LOCKTEAMS;else level.server_settings&=~CV_SVS_LOCKTEAMS;
        label=all?"All teams":!Q_stricmp(team,"r")?"Axis team":!Q_stricmp(team,"b")?"Allied team":"Spectators";
        trap_SendServerCommand(-1,va("cpm \"^x%s: ^9%s %sed^7\" -1",cursor,label,cursor));
        trap_SetConfigstring(CS_SERVERTOGGLES,va("%d",level.server_settings));return 1;
    }

    if(!strcmp(cursor,"freeze") || !strcmp(cursor,"unfreeze")) {
        int freeze=!strcmp(cursor,"freeze"),changed=0;
        if(argc<2) { Print(n,va("^9usage: ^g!%s [name|slot#|-1]^7\n",cursor));return 1; }
        if(!strcmp(args[1],"-1")) {
            for(i=0;i<level.numNonSpectatorClients && i<MAX_CLIENTS;++i) {
                target=level.sortedClients[i];
                if(target<0 || target>=level.maxclients || !g_entities[target].client) continue;
                if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) continue;
                if(!!g_entities[target].client->nitmodFrozen==freeze) continue;
                g_entities[target].client->nitmodFrozen=freeze;++changed;
            }
            trap_SendServerCommand(-1,va(freeze?"cpm \"^xfreeze: %d ^9players frozen^7\"":"cpm \"^xunfreeze: %d players unfrozen^7\"",changed));return 1;
        }
        target=Target(args[1]);if(target<0) { Print(n,va("^1%s: ^9No unique player\n",cursor));return 1; }
        if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,va("^1%s error: ^9Specified player has a higher admin level than you do.^7\n",cursor));return 1; }
        if(g_entities[target].client->sess.sessionTeam!=TEAM_AXIS && g_entities[target].client->sess.sessionTeam!=TEAM_ALLIES) { Print(n,va("^1%s error: ^9Player must be on a team^7\n",cursor));return 1; }
        if(!!g_entities[target].client->nitmodFrozen==freeze) { Print(n,freeze?"^1freeze error: ^9Player is already freezed^7\n":"^1unfreeze error: ^9Player is not freezed^7\n");return 1; }
        g_entities[target].client->nitmodFrozen=freeze;
        trap_SendServerCommand(-1,va(freeze?"cpm \"^xfreeze: ^7%s ^9was frozen^7\"":"cpm \"^xunfreeze: ^7%s ^9was unfroze^7\"",g_entities[target].client->pers.netname));return 1;
    }

    if(!strcmp(cursor,"rename")) {
        char userinfo[MAX_INFO_STRING],name[MAX_STRING_CHARS];
        if(argc<3) { Print(n,"^9usage: ^g!rename [name] [newname]^7\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1rename: ^9No unique player\n");return 1; }
        if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) {
            Print(n,va("^1rename error: ^7%s ^9is a higher level admin than you are.^7\n",g_entities[target].client->pers.netname));return 1;
        }
        name[0]=0;
        for(i=2;i<argc;++i) { if(i>2) Q_strcat(name,sizeof(name)," ");Q_strcat(name,sizeof(name),args[i]); }
        trap_GetUserinfo(target,userinfo,sizeof(userinfo));
        trap_SendServerCommand(-1,va("cpm \"^xrename: ^7%s ^9renamed to ^7%s\"",Info_ValueForKey(userinfo,"name"),name));
        Info_SetValueForKey(userinfo,"name",name);
        trap_SetUserinfo(target,userinfo);
        ClientCleanName(name,g_entities[target].client->pers.netname,sizeof(g_entities[target].client->pers.netname));
        ClientUserinfoChanged(target);return 1;
    }



    if(!strcmp(cursor,"time")) {
        time_t now=time(NULL);struct tm *local=localtime(&now);char text[50];
        if(now && local && strftime(text,sizeof(text),"%I:%M%p %Z",local)) trap_SendServerCommand(-1,va("chat \"^xtime:^g %s\" -2",text));
        return 1;
    }
    if(!strcmp(cursor,"uptime")) {
        int seconds=level.time/1000;
        const char *text=va("^xuptime: ^g%i days, %i hours, %i minutes.",seconds/86400,(seconds%86400)/3600,(seconds%3600)/60);
        if(n<0) Print(n,va("%s\n",text));else trap_SendServerCommand(n,va("chat \"%s\" -2",text));return 1;
    }
    if(!strcmp(cursor,"cancelvote") || !strcmp(cursor,"passvote")) {
        if(!strcmp(cursor,"passvote")) { level.voteInfo.voteYes=level.numConnectedClients;level.voteInfo.voteNo=0; }
        else level.voteInfo.voteNo=level.numConnectedClients;
        CheckVote();Print(n,!strcmp(cursor,"passvote")?"^xpassvote: ^9Current vote has been forced to pass\n":"^xcancelvote: ^9Current vote has been canceled\n");return 1;
    }
    if(!strcmp(cursor,"nextmap")) {
        if(g_gametype.integer==GT_WOLF_CAMPAIGN) {
            g_campaignInfo_t *campaign=&g_campaigns[level.currentCampaign];
            if(campaign->current+1<campaign->mapCount) {
                trap_Cvar_Set("g_currentCampaignMap",va("%d",campaign->current+1));
                trap_SendConsoleCommand(EXEC_APPEND,va("map %s\n",campaign->mapnames[campaign->current+1]));
            } else trap_SendConsoleCommand(EXEC_APPEND,"vstr nextcampaign\n");
        } else if(g_gametype.integer==GT_WOLF_MAPVOTE && (g_mapVoteFlags.integer&16)) {
            LogExit("Nextmap forced by admin");trap_SendServerCommand(-1,"chat \"^3*** Nextmap forced by admin! Choose a new map! ***\" -2");
        } else trap_SendConsoleCommand(EXEC_APPEND,"vstr nextmap\n");
        return 1;
    }
    if(!strcmp(cursor,"crazygravity")) {
        if(argc<2 || (args[1][0]!='0' && args[1][0]!='1')) { Print(n,"^9usage : ^g!crazygravity [0|1]^7\n");return 1; }
        trap_Cvar_Set("n_crazyGravity",args[1][0]=='1'?"1":"0");trap_SendServerCommand(-1,args[1][0]=='1'?"cpm \"^xcrazygravity: ^2Enabled !\"":"cpm \"^xcrazygravity: ^1Disabled!\"");return 1;
    }
    if(!strcmp(cursor,"panzerwar") || !strcmp(cursor,"sniperwar")) {
        int mode=!strcmp(cursor,"panzerwar")?1:2,enable,current;
        const char *display=mode==1?"Panzerwar":"Sniperwar";
        if(argc<2) { Print(n,va("^9usage : ^g!%s [1|on|0|off]^7\n",cursor));return 1; }
        if(!Q_stricmp(args[1],"on") || !strcmp(args[1],"1")) enable=1;
        else if(!Q_stricmp(args[1],"off") || !strcmp(args[1],"0")) enable=0;
        else return 1;
        current=G_NITMOD_ConfiguredWarMode();
        if((enable && current==mode) || (!enable && current!=mode)) { Print(n,va("^1%s error: ^9%s is already %s.^7\n",cursor,display,enable?"enabled":"disabled"));return 1; }
        trap_Cvar_Set("g_war",enable?va("%d",mode):"0");G_NITMOD_WarModeTouchClients();
        trap_SendServerCommand(-1,va("cpm \"^x%s: %s !\"",cursor,enable?"^2Enabled":"^1Disabled"));return 1;
    }
    if(!strcmp(cursor,"help")) {
        if(argc>1) {
            int c;const char *name=ResolveAdminCommand(args[1],&c);
            if(!name) { Print(n,"^1help: ^9Unknown or ambiguous command\n");return 1; }
            if(c>=0) {
                if(!CustomAllowed(n,c)) { Print(n,"^1help: ^9Permission denied\n");return 1; }
                Print(n,va("^x%s: ^9%s\n",name,customCommands[c].description));return 1;
            }
            if(!SupportedAdminCommand(name) || !G_NITMOD_AdminAllowed(n,name)) { Print(n,"^1help: ^9Command unavailable\n");return 1; }
            for(i=0;i<78;++i) if(!strcmp(name,nitmodAdminCommands[i].name)) {
                Print(n,va("^x%s: ^9%s\n^9usage: ^g!%s %s\n",name,nitmodAdminCommands[i].description,name,nitmodAdminCommands[i].usage));break;
            }
        } else {
            char listing[512] = "^9";
            int available=0;
            for(i=0;i<78;++i) if(SupportedAdminCommand(nitmodAdminCommands[i].name) && G_NITMOD_AdminAllowed(n,nitmodAdminCommands[i].name)) {
                Q_strcat(listing,sizeof(listing),va("%-12s",nitmodAdminCommands[i].name));
                if(++available%6==0) { Q_strcat(listing,sizeof(listing),"\n"); Print(n,listing); Q_strncpyz(listing,"^9",sizeof(listing)); }
            }
            for(i=0;i<customCommandCount;++i) if(CustomAllowed(n,i)) {
                Q_strcat(listing,sizeof(listing),va("%-12s",customCommands[i].name));
                if(++available%6==0) { Q_strcat(listing,sizeof(listing),"\n"); Print(n,listing); Q_strncpyz(listing,"^9",sizeof(listing)); }
            }
            if(available%6) { Q_strcat(listing,sizeof(listing),"\n"); Print(n,listing); }
            Print(n,va("^g%i ^9Commands available\n",available));
            Print(n,"^9Type !help [command] for help with a specific command.^7\n");
        }
        return 1;
    }
    if(!strcmp(cursor,"pause") || !strcmp(cursor,"unpause")) { G_refPause_cmd(n>=0?&g_entities[n]:NULL,!strcmp(cursor,"pause"));return 1; }
    if(!strcmp(cursor,"shuffle")) { G_shuffleTeams();return 1; }
    if(!strcmp(cursor,"swap")) { G_swapTeams();trap_SendServerCommand(-1,"chat \"^xswap: ^9Teams swapped^7\" -2");return 1; }
    if(!strcmp(cursor,"swap_restart")) { Svcmd_SwapTeams_f();trap_SendServerCommand(-1,"chat \"^xswap_restart: ^9Teams swapped, match restarting^7\" -2");return 1; }
    if(!strcmp(cursor,"restart") || !strcmp(cursor,"reset")) { Svcmd_ResetMatch_f(Q_stricmp(args[0],"reset")!=0,qtrue);return 1; }
    if(!strcmp(cursor,"spec999")) {
        for(i=0;i<level.maxclients;++i) {
            gentity_t *e=&g_entities[i];
            if(e->client && e->client->pers.connected==CON_CONNECTED && e->client->sess.sessionTeam!=TEAM_SPECTATOR && e->client->ps.ping==999) {
                SetTeam(e,"s",qtrue,-1,-1,qfalse);
                trap_SendServerCommand(-1,va("cpm \"^xspec999: ^7%s ^9moved to spectators^7\" -1",e->client->pers.netname));
            }
        }
        return 1;
    }
    if(!strcmp(cursor,"put") || !strcmp(cursor,"spec")) {
        int follow=!strcmp(cursor,"spec");
        if(follow && n<0) return 1;
        if(argc<(follow?2:3)) { Print(n,follow?"^9usage: ^g!spec ^7[name|slot#]^7\n":"^9usage: ^g!putteam ^7[name] [r|b|s]\n");return 1; }
        target=Target(args[1]);if(target<0) { Print(n,"^1No unique player\n");return 1; }
        if(follow) {
            if(target==n) return 1;
            if(g_entities[target].client->sess.sessionTeam==TEAM_SPECTATOR) { Print(n,va("^1spec error: ^7%s ^9isn't on a team^7\n",g_entities[target].client->pers.netname));return 1; }
            if(g_entities[n].client->sess.sessionTeam!=TEAM_SPECTATOR) SetTeam(&g_entities[n],"s",qtrue,-1,-1,qfalse);
            g_entities[n].client->sess.spectatorState=SPECTATOR_FOLLOW;g_entities[n].client->sess.spectatorClient=target;
            Print(n,va("^xspec: ^9Now following %s^7\n",g_entities[target].client->pers.netname));
        } else {
            if(n>=0 && G_NITMOD_AdminLevel(n)<G_NITMOD_AdminLevel(target)) { Print(n,va("^1putteam error: ^7%s ^9is a higher level admin than you are.\n",g_entities[target].client->pers.netname));return 1; }
            if(!SetTeam(&g_entities[target],args[2],qtrue,-1,-1,qfalse)) Print(n,"^1putteam error: ^9Put team failed^7\n");
        }
        return 1;
    }
    if(!strcmp(cursor,"resetxp") || !strcmp(cursor,"resetmyxp")) {
        target=!strcmp(cursor,"resetmyxp")?n:argc>1?Target(args[1]):-1;
        if(target<0 || !G_NITMOD_ClientAccount(target,&account)) { Print(n,"^1resetxp error: ^9No unique player\n"); return 1; }
        if(n>=0 && (!G_NITMOD_ClientAccount(n,&actor) || EffectiveLevel(actor.user.level)<EffectiveLevel(account.user.level))) {
            Print(n,"^1resetxp error: ^9Specified player has a higher ^7 admin level than you.\n"); return 1;
        }
        { adminDbCompletion_t ctx;AdminDbContext(&ctx,n,"resetxp");
          Com_sprintf(ctx.success,sizeof(ctx.success),"^x%s: ^9XP has been reset for player ^7%s\n",cursor,account.user.name);
          G_NITMOD_AccountResetXPAsync(target,AdminDbDone,&ctx,sizeof(ctx)); }
        return 1;
    }
    if(!strcmp(cursor,"levadd") || !strcmp(cursor,"levdelete") || !strcmp(cursor,"levlist") || !strcmp(cursor,"levinfo") || !strcmp(cursor,"levedit")) return LevelCommand(n,cursor,argc,args);
    if(!strcmp(cursor,"delrecords")) {
        int length; void *before; const char *map; nitmodDatabaseRecords_t record;adminDbCompletion_t ctx;
        if(!G_NITMOD_LegacyCvarInteger("n_mapRecords",0)) { Print(n,"^xdelrecords: ^gSorry, map records are not enabled.\n"); return 1; }
        if(argc<2) { Print(n,"^9usage: ^g!delrecord [map_name|DELETEALL]^7\n"); return 1; }
        map=!strcmp(args[1],"DELETEALL")?NULL:args[1];
        if(map && NITMOD_DBRecords(map,&record)!=1) { Print(n,va("^9delrecords : ^9map records not found for '^g%s^9'\n",map)); return 1; }
        before=NITMOD_DBExport(&length); if(!before) return 1;
        AdminDbContext(&ctx,n,"delrecords");
        Q_strncpyz(ctx.success,map?va("^xdelrecords: ^9Map records for ^g%s^9 successfully deleted from database^7\n",map):"^xdelrecords: ^9Sucessfully deleted all map records^7\n",sizeof(ctx.success));
        if(!NITMOD_DBClearRecords(map)) {
            NITMOD_DBInstallWorking(before,length);NITMOD_DBFreeExport(before);AdminDbDone(0,&ctx);
        } else G_NITMOD_DatabaseCommit(before,length,AdminDbDone,&ctx,sizeof(ctx));
        return 1;
    }
    if(!strcmp(cursor,"userlist") || !strcmp(cursor,"userinfo") || !strcmp(cursor,"useredit") || !strcmp(cursor,"userdelete") || !strcmp(cursor,"seen")) return UserCommand(n,cursor,argc,args);
    if(!strcmp(cursor,"readconfig")) { G_NITMOD_LoadAdminLevels(); G_NITMOD_LoadAdminCommands(); return 1; }
    if(!strcmp(cursor,"dbsave")) {
        adminDbCompletion_t ctx;int length;void *before=NITMOD_DBExport(&length);AdminDbContext(&ctx,n,"dbsave");
        Q_strncpyz(ctx.failure,"^1Database save failed\n",sizeof(ctx.failure));
        if(!before)AdminDbDone(NITMOD_DBUserCount()<0,&ctx);else G_NITMOD_DatabaseCommit(before,length,AdminDbDone,&ctx,sizeof(ctx));return 1;
    }
    if(!strcmp(cursor,"ban") || !strcmp(cursor,"banguid") || !strcmp(cursor,"mute") || !strcmp(cursor,"unmute") ||
       !strcmp(cursor,"unban") || !strcmp(cursor,"showbans")) return PenaltyCommand(n,cursor,argc,args);
    if(!strcmp(cursor,"admintest")) {
        adminLevel_t *entry;
        if(n<0 || !G_NITMOD_ClientAccount(n,&account)) return 1;
        entry=Level(account.user.level);
        Print(n,va("^xadmintest: ^7%s ^9is a level ^x%d ^9user %s\n",account.user.name,entry?entry->number:0,entry?entry->name:"")); return 1;
    }
    if(!strcmp(cursor,"records")) {
        nitmodDatabaseRecords_t record;
        if(!G_NITMOD_LegacyCvarInteger("n_mapRecords",0)) { Print(n,"^xrecords: ^gSorry, map records are not enabled.\n"); return 1; }
        if(NITMOD_DBRecords(level.rawmapname,&record)==1) G_NITMOD_PrintMapRecords(&record,7);
        return 1;
    }
    if(argc<3 || !Number(args[2],&number)) { Print(n,"^9usage: ^g!setlevel [name|slot#] [level]\n"); return 1; }
    if(!Level(number) || Level(number)->number!=number) { Print(n,"^1setlevel error: ^9unknown level\n"); return 1; }
    target=Target(args[1]);
    if(target<0 || !G_NITMOD_ClientAccount(target,&account)) { Print(n,"^1setlevel error: ^9No unique player with valid NGUID\n"); return 1; }
    if(n>=0 && (!G_NITMOD_ClientAccount(n,&actor) || number>EffectiveLevel(actor.user.level) || EffectiveLevel(account.user.level)>EffectiveLevel(actor.user.level))) {
        Print(n,"^1setlevel error: ^9you can't setlevel higher than your level\n"); return 1;
    }
    account.user.level=number;
    { adminDbCompletion_t ctx;AdminDbContext(&ctx,n,"setlevel");
      Com_sprintf(ctx.success,sizeof(ctx.success),"^xsetlevel: ^7%s^9's level set to ^x%d\n",account.user.name,number);
      G_NITMOD_StoreAccountAsync(&account,2,AdminDbDone,&ctx,sizeof(ctx)); }
    return 1;
}

void G_NITMOD_UpdateAdminGlow(gentity_t *ent) {
    if(!ent || !ent->client) return;
    if(ent->client->nitmodGlowing) ent->s.time2|=NITMOD_ES_GLOW;
    else ent->s.time2&=~NITMOD_ES_GLOW;
}

int G_NITMOD_AdminCommand(int clientNum, const char *command) {
    adminLogRequest_t log;
    int handled;
    memset(&log,0,sizeof(log));
    handled=DispatchAdminCommand(clientNum,command,&log);
    AdminCommandLog(clientNum,&log);
    return handled;
}
