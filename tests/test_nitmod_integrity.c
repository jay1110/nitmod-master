#include "g_local.h"
#include "g_nitmod_integrity.h"
#include <assert.h>
static const char *contents;
static const char *argument;
static int opened,closed,reads,drops,enabled;
int trap_FS_FOpenFile(const char *name,fileHandle_t *handle,fsMode_t mode) {
    assert(!strcmp(name,"NxAC/checksums.cfg") && mode==FS_READ); ++opened;
    *handle=contents ? 7 : 0; return contents ? (int)strlen(contents) : -1;
}
void trap_FS_Read(void *out,int len,fileHandle_t handle) { assert(handle==7); ++reads; memcpy(out,contents,len); }
void trap_FS_FCloseFile(fileHandle_t handle) { assert(handle==7); ++closed; }
void G_LogPrintf(const char *format,...) { }
void Com_Printf(const char *format,...) { }
void Com_Error(int code,const char *format,...) { abort(); }
int G_NITMOD_LegacyCvarInteger(const char *name,int fallback) {
    assert(!strcmp(name,"n_NxAC_CheckClientBinary")); return enabled;
}
void trap_Argv(int number,char *out,int size) { assert(number==1); Q_strncpyz(out,argument,size); }
void trap_DropClient(int client,const char *reason,int ban) {
    assert(client==3 && !ban && !strcmp(reason,"^9Nx^7AC ^5VIOLATION: ^5[UNKNOWN_CLIENT_BINARY]")); ++drops;
}
int main(void) {
    const char *hash="0123456789abcdef0123456789abcdef01234567";
    char list[8192],entry[64],longHash[70]; int i;
    contents=NULL; assert(G_NITMOD_LoadChecksums()==0 && !closed);
    contents="// comment\n\"0123456789abcdef0123456789abcdef01234567\"\n0123456789ABCDEF0123456789ABCDEF01234567\n";
    assert(G_NITMOD_LoadChecksums()==1 && closed==1 && reads==1);
    assert(G_NITMOD_VerifyChecksum(hash));
    assert(G_NITMOD_VerifyChecksum("0123456789ABCDEF0123456789ABCDEF01234567"));
    assert(!G_NITMOD_VerifyChecksum(NULL) && !G_NITMOD_VerifyChecksum("short"));
    argument="MDEyMzQ1Njc4OWFiY2RlZjAxMjM0NTY3ODlhYmNkZWYwMTIzNDU2Nw==";
    enabled=1; assert(G_NITMOD_ChecksumCommand(3,"csm") && !drops);
    assert(!G_NITMOD_ChecksumCommand(3,"other"));
    argument="bad!"; assert(G_NITMOD_ChecksumCommand(3,"csm") && drops==1);
    enabled=0; assert(G_NITMOD_ChecksumCommand(3,"csm") && drops==1);
    G_NITMOD_ClearChecksums(); assert(!G_NITMOD_VerifyChecksum(hash));
    list[0]=0;
    for(i=0;i<65;++i) { sprintf(entry,"%040d\n",i); strcat(list,entry); }
    contents=list; assert(G_NITMOD_LoadChecksums()==64 && closed==2);
    sprintf(entry,"%040d",63); assert(G_NITMOD_VerifyChecksum(entry));
    sprintf(entry,"%040d",64); assert(!G_NITMOD_VerifyChecksum(entry));
    memset(longHash,'Z',60); longHash[60]=0; contents=longHash;
    assert(G_NITMOD_LoadChecksums()==1); longHash[40]=0;
    assert(G_NITMOD_VerifyChecksum(longHash)); /* original truncation, not hex validation */
    contents=""; assert(!G_NITMOD_LoadChecksums() && closed==4);
    puts("NxAC checksum loader, membership and actual csm dispatch: PASS");
    return 0;
}
