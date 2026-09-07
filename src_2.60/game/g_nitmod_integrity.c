#include "g_local.h"
#include "g_nitmod_integrity.h"
#include "g_nitmod_legacy_cvars.h"

/* Original NxAC records: 64 entries, 40 characters plus terminator.
 * No invented hexadecimal requirement: original verification checks length
 * and case-insensitive list membership only. */
static char checksums[64][41];
static int checksumCount;

void G_NITMOD_ClearChecksums(void) {
    memset(checksums,0,sizeof(checksums)); checksumCount=0;
}

int G_NITMOD_VerifyChecksum(const char *checksum) {
    int i;
    if(!checksum || strlen(checksum)!=40) return 0;
    for(i=0;i<checksumCount;++i) if(!Q_stricmp(checksums[i],checksum)) return 1;
    return 0;
}

int G_NITMOD_LoadChecksums(void) {
    fileHandle_t file=0;
    char *buffer,*cursor,*token;
    int length,i,duplicate;
    G_NITMOD_ClearChecksums();
    length=trap_FS_FOpenFile("NxAC/checksums.cfg",&file,FS_READ);
    if(length<0 || !file) {
        G_LogPrintf("[NxAC] Could not open NxAC/checksums.cfg\n"); return 0;
    }
    /* Bound untrusted file sizes; close on every path, unlike the original
     * allocation leak at the 64-entry boundary. */
    if(length>1048576) { trap_FS_FCloseFile(file); G_LogPrintf("[NxAC] Checksum file exceeds 1 MiB\n"); return 0; }
    buffer=(char *)malloc((size_t)length+1);
    if(!buffer) { trap_FS_FCloseFile(file); return 0; }
    trap_FS_Read(buffer,length,file); trap_FS_FCloseFile(file); buffer[length]=0;
    cursor=buffer;
    while(checksumCount<64 && *(token=COM_Parse(&cursor))) {
        duplicate=0;
        for(i=0;i<checksumCount;++i) if(!Q_stricmp(checksums[i],token)) duplicate=1;
        if(duplicate) { G_LogPrintf("[NxAC] Duplicate checksum: %s\n",token); continue; }
        Q_strncpyz(checksums[checksumCount++],token,41);
    }
    free(buffer);
    G_LogPrintf("[NxAC] Loaded %d allowed client SHA1 checksums\n",checksumCount);
    return checksumCount;
}

/* Valid original csm payloads are ordinary base64. Reject malformed payloads
 * deterministically rather than reproducing decode64's stale-byte behavior. */
static int DecodeChecksum(const char *input,char output[41]) {
    unsigned int bits=0;
    int available=0,count=0,value;
    const unsigned char *p=(const unsigned char *)input;
    for(;*p && *p!='=';++p) {
        if(*p>='A' && *p<='Z') value=*p-'A';
        else if(*p>='a' && *p<='z') value=*p-'a'+26;
        else if(*p>='0' && *p<='9') value=*p-'0'+52;
        else if(*p=='+') value=62;
        else if(*p=='/') value=63;
        else return 0;
        bits=(bits<<6)|(unsigned int)value; available+=6;
        if(available>=8) {
            available-=8;
            if(count>=40) return 0;
            output[count]=(char)((bits>>available)&255);
            if(!output[count++]) return 0;
        }
    }
    if(count!=40 || available!=4 || (bits&15)) return 0;
    if(*p && strcmp((const char *)p,"==")) return 0;
    output[40]=0; return 1;
}

int G_NITMOD_ChecksumCommand(int clientNum,const char *command) {
    char encoded[256],decoded[41];
    if(!command || strcmp(command,"csm")) return 0;
    if(clientNum<0 || clientNum>=MAX_CLIENTS) return 1;
    if(!G_NITMOD_LegacyCvarInteger("n_NxAC_CheckClientBinary",0)) return 1;
    trap_Argv(1,encoded,sizeof(encoded));
    if(DecodeChecksum(encoded,decoded) && G_NITMOD_VerifyChecksum(decoded)) return 1;
    G_LogPrintf("[NxAC] client %d UNKNOWN_CLIENT_BINARY\n",clientNum);
    trap_DropClient(clientNum,"^9Nx^7AC ^5VIOLATION: ^5[UNKNOWN_CLIENT_BINARY]",0);
    return 1;
}
