#include "g_local.h"
#include "g_nitmod_admin.h"
#include "g_nitmod_accounts.h"
#include "g_nitmod_database.h"
#include "g_nitmod_config.h"
#include "g_nitmod_records.h"
#include "g_nitmod_legacy_cvars.h"
typedef struct { int number; char name[36],flags[1024],gtext[1024],gsound[1024]; } adminLevel_t;
static adminLevel_t levels[64];
static int levelCount,levelsReady;
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
static int Target(const char *text) {
    int n,i,found=-1; char needle[MAX_NAME_LENGTH],name[MAX_NAME_LENGTH];
    if(Number(text,&n)) return n<MAX_CLIENTS && g_entities[n].client && g_entities[n].client->pers.connected!=CON_DISCONNECTED?n:-1;
    Q_strncpyz(needle,text,sizeof(needle)); Q_CleanStr(needle); Q_strlwr(needle);
    if(!*needle) return -1;
    for(i=0;i<MAX_CLIENTS;++i) if(g_entities[i].client && g_entities[i].client->pers.connected!=CON_DISCONNECTED) {
        Q_strncpyz(name,g_entities[i].client->pers.netname,sizeof(name)); Q_CleanStr(name); Q_strlwr(name);
        if(strstr(name,needle)) { if(found>=0) return -1; found=i; }
    }
    return found;
}
static int PenaltyStore(const nitmodDatabasePenalty_t *penalty,int mute,int add) {
    int length,ok; void *before=NITMOD_DBExport(&length); if(!before) return 0;
    ok=NITMOD_DBPenaltySave(mute,penalty,add) && G_NITMOD_DatabaseFlush();
    if(!ok) NITMOD_DBOpenWorking(before,length);
    NITMOD_DBFreeExport(before); return ok;
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
        if(!PenaltyStore(&penalty,0,0)) Print(n,"^1unban error: ^9Database write failed\n");
        else Print(n,va("^xunban: ^9ban ^g#%d ^9removed\n",i)); return 1;
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
        if(!PenaltyStore(&penalty,1,0)) Print(n,"^1unmute error: ^9Database write failed\n");
        else { g_entities[target].client->sess.muted=qfalse; g_entities[target].client->nitmodMuteUntil=0;
               ClientUserinfoChanged(target); Print(n,"^xunmute: ^9Player has been unmuted\n"); }
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
    i=NITMOD_DBPenaltyCheck(mute,"",account.user.guid,account.mac,time,&existing,&expired);
    if(i!=0) { Print(n,i>0?"^1Admin error: ^9Player already banned/muted\n":"^1Admin error: ^9Database query failed\n"); return 1; }
    Q_strncpyz(penalty.name,account.user.name,sizeof(penalty.name)); Q_strncpyz(penalty.ip,account.ip,sizeof(penalty.ip));
    Q_strncpyz(penalty.mac,account.mac,sizeof(penalty.mac)); Q_strncpyz(penalty.actor,n<0?"console":g_entities[n].client->pers.netname,sizeof(penalty.actor));
    Com_sprintf(penalty.made,sizeof(penalty.made),"%02d/%02d/%02d %02d:%02d:%02d",now.tm_mon+1,now.tm_mday,(now.tm_year+1900)%100,now.tm_hour,now.tm_min,now.tm_sec);
    penalty.expires=seconds?time+seconds:0;
    for(i=start;i<argc;++i) { if(i>start) Q_strcat(penalty.reason,sizeof(penalty.reason)," "); Q_strcat(penalty.reason,sizeof(penalty.reason),args[i]); }
    if(!*penalty.reason) Q_strncpyz(penalty.reason,mute?"muted by admin":"banned by admin",sizeof(penalty.reason));
    if(!PenaltyStore(&penalty,mute,1)) { Print(n,"^1Admin error: ^9Database write failed\n"); return 1; }
    if(target>=0) {
        if(mute) ClientUserinfoChanged(target);
        else trap_DropClient(target,va("You have been banned %s, Reason: %s",seconds?va("for %i seconds",seconds):"^1PERMANENTLY",penalty.reason),0);
    }
    if(!strcmp(command,"banguid")) for(i=0;i<MAX_CLIENTS;++i) {
        if(G_NITMOD_ClientAccount(i,&actor) && !Q_stricmp(actor.user.guid,account.user.guid))
            trap_DropClient(i,va("You have been banned %s, Reason: %s",seconds?va("for %i seconds",seconds):"^1PERMANENTLY",penalty.reason),0);
    }
    Print(n,va("^x%s: ^7%s ^9has been %s\n",command,penalty.name,mute?"muted":"banned")); return 1;
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
        if(!NITMOD_DBMigrateUserLevel(number,to) || !G_NITMOD_DatabaseFlush()) goto failed;
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
    ok=SaveLevels(); if(!ok) goto failed;
    Print(n,va("^x%s: ^9level ^7%d successfully %s^7\n",command,number,!strcmp(command,"levadd")?"added":!strcmp(command,"levdelete")?"deleted":"updated"));
    NITMOD_DBFreeExport(databaseBefore); free(before); return 1;
failed:
    if(migrate && databaseBefore) {
        if(!NITMOD_DBOpenWorking(databaseBefore,length) || !G_NITMOD_DatabaseFlush()) G_LogPrintf("[Admin] Failed to persist level migration rollback\n");
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
        if(!G_NITMOD_StoreAccount(&account,0)) Print(n,"^1userdelete error: ^9Database write failed\n");
        else Print(n,va("^xuserdelete: ^9User ^7%s ^9(UserID ^g%s^9) successfully deleted from database^7\n",account.user.name,id));
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
    if(!G_NITMOD_StoreAccount(&account,2)) Print(n,"^1useredit error: ^9Database write failed\n");
    else Print(n,va("^xuseredit: ^7%s ^9updated\n",account.user.name));
    return 1;
}
static int SupportedAdminCommand(const char *cursor) { return !(Q_stricmp(cursor,"setlevel") && Q_stricmp(cursor,"admintest") && Q_stricmp(cursor,"records") &&
       Q_stricmp(cursor,"readconfig") && Q_stricmp(cursor,"dbsave") && Q_stricmp(cursor,"ban") && Q_stricmp(cursor,"banguid") &&
       Q_stricmp(cursor,"mute") && Q_stricmp(cursor,"unmute") && Q_stricmp(cursor,"unban") && Q_stricmp(cursor,"showbans") &&
       Q_stricmp(cursor,"userlist") && Q_stricmp(cursor,"userinfo") && Q_stricmp(cursor,"useredit") && Q_stricmp(cursor,"userdelete") && Q_stricmp(cursor,"seen") &&
       Q_stricmp(cursor,"levadd") && Q_stricmp(cursor,"levdelete") && Q_stricmp(cursor,"levlist") && Q_stricmp(cursor,"levinfo") && Q_stricmp(cursor,"levedit") && Q_stricmp(cursor,"delrecords") && Q_stricmp(cursor,"resetxp") && Q_stricmp(cursor,"resetmyxp")); }
int G_NITMOD_AdminCommand(int n,const char *command) {
    static char args[16][1024]; /* engine command dispatch is single threaded */
    char *cursor,*token; int argc=0,i,target,number; nitmodDatabaseAccount_t account,actor;
    if(n<0 && !SupportedAdminCommand(*command=='!'?command+1:command)) return 0;
    if(!Q_stricmp(command,"say")) {
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
    cursor=args[0]; if(*cursor=='!') ++cursor; Q_strlwr(cursor);
    if(!SupportedAdminCommand(cursor)) return 0;
    if(!G_NITMOD_AdminAllowed(n,cursor)) { Print(n,va("^x%s: ^1Permission denied\n",cursor)); return 1; }
    if(!strcmp(cursor,"resetxp") || !strcmp(cursor,"resetmyxp")) {
        target=!strcmp(cursor,"resetmyxp")?n:argc>1?Target(args[1]):-1;
        if(target<0 || !G_NITMOD_ClientAccount(target,&account)) { Print(n,"^1resetxp error: ^9No unique player\n"); return 1; }
        if(n>=0 && (!G_NITMOD_ClientAccount(n,&actor) || EffectiveLevel(actor.user.level)<EffectiveLevel(account.user.level))) {
            Print(n,"^1resetxp error: ^9Specified player has a higher ^7 admin level than you.\n"); return 1;
        }
        if(!G_NITMOD_AccountResetXP(target)) Print(n,"^1resetxp error: ^9Database write failed\n");
        else Print(n,va("^x%s: ^9XP has been reset for player ^7%s\n",cursor,account.user.name));
        return 1;
    }
    if(!strcmp(cursor,"levadd") || !strcmp(cursor,"levdelete") || !strcmp(cursor,"levlist") || !strcmp(cursor,"levinfo") || !strcmp(cursor,"levedit")) return LevelCommand(n,cursor,argc,args);
    if(!strcmp(cursor,"delrecords")) {
        int length,ok; void *before; const char *map; nitmodDatabaseRecords_t record;
        if(!G_NITMOD_LegacyCvarInteger("n_mapRecords",0)) { Print(n,"^xdelrecords: ^gSorry, map records are not enabled.\n"); return 1; }
        if(argc<2) { Print(n,"^9usage: ^g!delrecord [map_name|DELETEALL]^7\n"); return 1; }
        map=!strcmp(args[1],"DELETEALL")?NULL:args[1];
        if(map && NITMOD_DBRecords(map,&record)!=1) { Print(n,va("^9delrecords : ^9map records not found for '^g%s^9'\n",map)); return 1; }
        before=NITMOD_DBExport(&length); if(!before) return 1;
        ok=NITMOD_DBClearRecords(map) && G_NITMOD_DatabaseFlush();
        if(!ok) { NITMOD_DBOpenWorking(before,length); Print(n,"^1delrecords error: ^9Database write failed\n"); }
        else Print(n,map?va("^xdelrecords: ^9Map records for ^g%s^9 successfully deleted from database^7\n",map):"^xdelrecords: ^9Sucessfully deleted all map records^7\n");
        NITMOD_DBFreeExport(before); return 1;
    }
    if(!strcmp(cursor,"userlist") || !strcmp(cursor,"userinfo") || !strcmp(cursor,"useredit") || !strcmp(cursor,"userdelete") || !strcmp(cursor,"seen")) return UserCommand(n,cursor,argc,args);
    if(!strcmp(cursor,"readconfig")) { G_NITMOD_LoadAdminLevels(); return 1; }
    if(!strcmp(cursor,"dbsave")) { if(!G_NITMOD_DatabaseFlush()) Print(n,"^1Database save failed\n"); return 1; }
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
    if(!G_NITMOD_StoreAccount(&account,2)) Print(n,"^1setlevel error: ^9Database write failed\n");
    else Print(n,va("^xsetlevel: ^7%s^9's level set to ^x%d\n",account.user.name,number));
    return 1;
}
