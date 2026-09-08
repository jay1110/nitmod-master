#include "g_local.h"
#include "g_nitmod_integrity.h"
#include "g_nitmod_legacy_cvars.h"
#include <limits.h>

/* Original NxAC_LoadCvarList 0x1117a0 / NxAC_ScanClientCvars 0x111d10.
 * Scan state belongs to the connection, never to persistent user accounts. */
#define NITMOD_MAX_CVAR_RULES 512
typedef struct { char name[64], first[32], second[32]; int rule; } nitmodCvarRule_t;
typedef struct {
    int next, waiting, warnings;
    int scanAt, nextAt;
    qboolean started;
} nitmodCvarScan_t;
static nitmodCvarRule_t cvarRules[NITMOD_MAX_CVAR_RULES];
static nitmodCvarScan_t cvarScans[MAX_CLIENTS];
static int cvarRuleCount;
static const char *cvarRuleNames[10] = {"NULL","EQ","IN","OUT","G","GE","L","LE","INC","EXC"};

static qboolean CvarScanClient(int clientNum) {
    return clientNum >= 0 && clientNum < MAX_CLIENTS && g_entities[clientNum].client &&
        g_entities[clientNum].client->pers.connected == CON_CONNECTED &&
        !(g_entities[clientNum].r.svFlags & SVF_BOT) &&
        !g_entities[clientNum].client->pers.nitmodDemoClient;
}
static qboolean CvarScanEnabled(void) {
    return cvarRuleCount && G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScan",0);
}
static void ClearScan(nitmodCvarScan_t *scan) {
    int warnings=scan->warnings;
    memset(scan,0,sizeof(*scan)); scan->waiting=-1; scan->warnings=warnings;
}
void G_NITMOD_CvarScanResetClient(int clientNum) {
    if(clientNum<0 || clientNum>=MAX_CLIENTS) return;
    memset(&cvarScans[clientNum],0,sizeof(cvarScans[clientNum]));
    cvarScans[clientNum].waiting=-1;
}
void G_NITMOD_ClearCvarList(void) {
    int i;
    memset(cvarRules,0,sizeof(cvarRules)); cvarRuleCount=0;
    for(i=0;i<MAX_CLIENTS;++i) G_NITMOD_CvarScanResetClient(i);
}
static qboolean SafeCvarName(const char *name) {
    int i;
    if(!name || !*name || strlen(name)>=64) return qfalse;
    for(i=0;name[i];++i) {
        unsigned char c=name[i];
        if(!((c>='a' && c<='z') || (c>='A' && c<='Z') ||
             (c>='0' && c<='9') || c=='_')) return qfalse;
    }
    return qtrue;
}
int G_NITMOD_LoadCvarList(void) {
    fileHandle_t file=0;
    char *buffer,*cursor,*token;
    int length,i,rule;
    nitmodCvarRule_t entry;
    G_NITMOD_ClearCvarList();
    length=trap_FS_FOpenFile("NxAC/cvarlist.cfg",&file,FS_READ);
    if(length<0 || !file) {
        G_LogPrintf("[NxAC] Could not open NxAC/cvarlist.cfg\n"); return 0;
    }
    if(length>1048576) {
        trap_FS_FCloseFile(file); G_LogPrintf("[NxAC] Cvar list exceeds 1 MiB\n"); return 0;
    }
    buffer=(char *)malloc((size_t)length+1);
    if(!buffer) { trap_FS_FCloseFile(file); return 0; }
    trap_FS_Read(buffer,length,file); trap_FS_FCloseFile(file); buffer[length]=0;
    cursor=buffer;
    while(*(token=COM_Parse(&cursor))) {
        if(cvarRuleCount==NITMOD_MAX_CVAR_RULES) {
            G_LogPrintf("[NxAC] NXAC_MAX_CVARCHECKS EXCEEDED\n");
            free(buffer); return 0; /* Original retains its first 512 rules. */
        }
        if(!SafeCvarName(token)) { SkipRestOfLine(&cursor); continue; }
        for(i=0;i<cvarRuleCount && Q_stricmp(cvarRules[i].name,token);++i) {}
        if(i<cvarRuleCount) {
            G_LogPrintf("[NxAC] restriction already loaded for cvar %s\n",token);
            SkipRestOfLine(&cursor); continue;
        }
        memset(&entry,0,sizeof(entry)); Q_strncpyz(entry.name,token,sizeof(entry.name));
        token=COM_ParseExt(&cursor,qfalse);
        for(rule=0;rule<10 && Q_stricmp(cvarRuleNames[rule],token);++rule) {}
        if(rule==10) {
            G_LogPrintf("[NxAC] Invalid cvar rule (%s) for cvar %s\n",token,entry.name);
            /* COM_ParseExt already crossed the newline when it returned empty. */
            if(*token) SkipRestOfLine(&cursor);
            continue;
        }
        entry.rule=rule;
        if(rule) Q_strncpyz(entry.first,COM_ParseExt(&cursor,qfalse),sizeof(entry.first));
        if(rule==2 || rule==3) Q_strncpyz(entry.second,COM_ParseExt(&cursor,qfalse),sizeof(entry.second));
        cvarRules[cvarRuleCount++]=entry;
    }
    free(buffer);
    G_LogPrintf("| [NxAC::LoadCvarList] Loaded %d cvar restriction%s\n",cvarRuleCount,cvarRuleCount==1?"":"s");
    return cvarRuleCount;
}
void G_NITMOD_CvarScanStart(int clientNum) {
    nitmodCvarScan_t *scan;
    if(!CvarScanClient(clientNum)) return;
    scan=&cvarScans[clientNum];
    if(scan->started || !G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScan",0)) return;
    scan->started=qtrue; scan->next=0; scan->waiting=-1; scan->nextAt=0;
    scan->scanAt=(int)((unsigned int)level.time+(unsigned int)G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScanWait",10000));
}
void G_NITMOD_CvarScanThink(int clientNum) {
    nitmodCvarScan_t *scan;
    if(!CvarScanClient(clientNum)) return;
    scan=&cvarScans[clientNum];
    if(level.intermissiontime) return;
    /* Original ClientThink_real 0x40469 gates only the whole-scan timer.
     * A disabled pending single-step timer still reaches ScanClientCvars,
     * which clears the transient scan state while retaining warnings. */
    if(G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScan",0) &&
       scan->scanAt>0 && scan->scanAt<level.time) {
        scan->scanAt=0; scan->nextAt=0; scan->next=0; scan->waiting=-1;
    } else if(scan->nextAt>0 && scan->nextAt<level.time) {
        scan->nextAt=0;
    } else return;
    if(!CvarScanEnabled()) { ClearScan(scan); return; }
    if(scan->next<0 || scan->next>=cvarRuleCount) return;
    scan->waiting=scan->next;
    trap_SendServerCommand(clientNum,va("cvs %i %s\n",scan->next,cvarRules[scan->next].name));
}
/* Original ClientCommand explicitly rounds all three strtod results to float.
 * Its unordered x87 compares accept NaN; keep that behavior in these rules. */
static qboolean CvarRulePasses(const nitmodCvarRule_t *rule,const char *value) {
    volatile float v=(float)strtod(value,NULL);
    volatile float a=(float)strtod(rule->first,NULL);
    volatile float b=(float)strtod(rule->second,NULL);
    qboolean vaUnordered=(v!=v || a!=a), vbUnordered=(v!=v || b!=b);
    switch(rule->rule) {
    case 0: return !*value;
    case 1: return !Q_stricmp(value,rule->first);
    case 2: return (vbUnordered || v<=b) && (vaUnordered || v>=a);
    case 3: return !((v>=a && v<b) || (v>a && v<=b));
    case 4: return vaUnordered || v>a;
    case 5: return vaUnordered || v>=a;
    case 6: return vaUnordered || v<a;
    case 7: return vaUnordered || v<=a;
    case 8: return strstr(value,rule->first)!=NULL;
    case 9: return strstr(value,rule->first)==NULL;
    default: return qtrue;
    }
}
static qboolean CvarViolation(int clientNum,const nitmodCvarRule_t *rule,const char *value) {
    nitmodCvarScan_t *scan=&cvarScans[clientNum];
    char message[768],drop[900];
    int maximum=G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScanMaxWarnings",1);
    qboolean kick=rule->rule==0 || maximum<1 || scan->warnings>=maximum;
    const char *firstQuote=*rule->first?"'":"", *secondQuote=*rule->second?"'":"";
    Com_sprintf(message,sizeof(message),"'%s' IS '%s' SHOULD BE %s %s%s%s%s%s%s",
        rule->name,value,cvarRuleNames[rule->rule],firstQuote,rule->first,firstQuote,
        secondQuote,rule->second,secondQuote);
    G_LogPrintf("[NxAC] client %d CVARSCAN]^5 %s\n",clientNum,message);
    if(kick) {
        Com_sprintf(drop,sizeof(drop),"\n^7^9Nx^7AC: CVAR_VIOLATION\n'%s' IS '%s' SHOULD BE %s %s%s%s%s%s%s\n\"",
            rule->name,value,cvarRuleNames[rule->rule],firstQuote,rule->first,firstQuote,
            *rule->second?" '":"",rule->second,secondQuote);
        ClearScan(scan);
        trap_DropClient(clientNum,drop,0);
        return qtrue;
    }
    trap_SendServerCommand(clientNum,va("cpm \"^9Nx^7AC: ^1CVAR_VIOLATION ^7%s\n\"",message));
    ++scan->warnings;
    return qfalse;
}
int G_NITMOD_CvarScanCommand(int clientNum,const char *command) {
    /* Original argv3 trap buffer is 32 bytes, including the terminator. */
    char indexText[64],name[64],value[32],*end;
    long index;
    size_t length;
    nitmodCvarScan_t *scan;
    const nitmodCvarRule_t *rule;
    if(!command || strcmp(command,"cvs")) return 0;
    /* Disabled original servers leave cvs to the normal command fallback. */
    if(!G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScan",0)) return 0;
    if(!CvarScanClient(clientNum) || !cvarRuleCount) return 1;
    scan=&cvarScans[clientNum];
    if(trap_Argc()!=4 || scan->waiting<0) return 1;
    trap_Argv(1,indexText,sizeof(indexText)); trap_Argv(2,name,sizeof(name));
    trap_Argv(3,value,sizeof(value));
    index=strtol(indexText,&end,10);
    /* Unlike the original unchecked array index, malformed/stale responses
     * cannot read outside the rules or advance a different active scan. */
    if(!*indexText || *end || index<0 || index>=cvarRuleCount || index!=scan->waiting) return 1;
    rule=&cvarRules[index];
    if(Q_stricmp(name,rule->name)) {
        G_LogPrintf("[NxAC] client %d UNEXPECTED CVAR SCAN DATA]\n",clientNum);
        ClearScan(scan);
        trap_DropClient(clientNum,"^9Nx^7AC ^5VIOLATION: ^5[UNEXPECTED CVAR SCAN DATA]\n",0);
        return 1;
    }
    /* These bytes cannot occur in the client's quoted cvs response. */
    if(strpbrk(value,"\"\\\r\n")) return 1;
    length=strlen(value); if(length && value[length-1]==' ') value[length-1]=0;
    scan->waiting=-1;
    if(!CvarRulePasses(rule,value) && CvarViolation(clientNum,rule,value)) return 1;
    ++scan->next;
    if(scan->next<cvarRuleCount)
        scan->nextAt=(int)((unsigned int)level.time+(unsigned int)G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScanDelay",750));
    else scan->scanAt=(int)((unsigned int)level.time+(unsigned int)G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScanInterval",300000));
    return 1;
}

/* Original getdata sets only the next full-scan time (client+0xb24).
 * Preserve outstanding response state and the connection warning count. */
void G_NITMOD_CvarScanRequest(int clientNum) {
    nitmodCvarScan_t *scan;
    if(!CvarScanClient(clientNum) || !G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScan",0)) return;
    scan=&cvarScans[clientNum];
    scan->started=qtrue;
    scan->scanAt=(int)((unsigned int)level.time+(unsigned int)G_NITMOD_LegacyCvarInteger("n_NxAC_CvarScanWait",10000));
}
