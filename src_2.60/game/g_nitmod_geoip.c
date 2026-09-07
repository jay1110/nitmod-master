#include "g_local.h"
#include "g_nitmod_geoip.h"
static unsigned char *database;
static unsigned int databaseSize;
void G_NITMOD_GeoIPClose(void) { free(database); database=NULL; databaseSize=0; }
void G_NITMOD_GeoIPLoad(void) {
    fileHandle_t file=0; int size;
    G_NITMOD_GeoIPClose();
    if(!trap_Cvar_VariableIntegerValue("g_countryflags")) return;
    size=trap_FS_FOpenFile("GeoIP.dat",&file,FS_READ);
    if(size<=0 || !file || size>64*1024*1024) {
        if(file) trap_FS_FCloseFile(file);
        G_LogPrintf("GeoIP: unavailable or invalid database file\n"); return;
    }
    database=calloc((size_t)size+1,1);
    if(database) { trap_FS_Read(database,size,file); databaseSize=size; }
    else G_LogPrintf("GeoIP: Memory allocation error for GeoIP cache\n");
    trap_FS_FCloseFile(file);
}
static unsigned int Address(const char *text) {
    unsigned int ip=0; int octet;
    for(octet=0;octet<4;++octet) {
        unsigned int value=0; int digits=0;
        while(*text>='0' && *text<='9') {
            if(++digits>3) return 0;
            value=value*10+(*text++-'0');
        }
        if(!digits || value>255) return 0;
        ip=(ip<<8)|value;
        if(octet<3) { if(*text++!='.') return 0; }
        else if(*text && *text!=':') return 0;
    }
    return ip;
}
static int Seek(unsigned int ip) {
    unsigned int node=0; int bit;
    for(bit=31;bit>=0;--bit) {
        unsigned int offset=node*6,child;
        /* Match the original strict bound, including an exact-size last node. */
        if(node>databaseSize/6 || offset+6>=databaseSize) break;
        offset+=((ip>>bit)&1)*3;
        child=database[offset]|((unsigned int)database[offset+1]<<8)|((unsigned int)database[offset+2]<<16);
        if(child>=0xffff00) return child-0xffff00;
        node=child;
    }
    G_LogPrintf("GeoIP: Error Traversing Database for ipnum = %u - Perhaps database is corrupt?\n",ip);
    return 255;
}
int G_NITMOD_GeoIPCountry(const char *address,int bot) {
    unsigned int ip; int country; char server[256];
    if(!database) return 255;
    if(bot && (trap_Cvar_VariableIntegerValue("g_countryflags")&2)) {
        trap_Cvar_VariableStringBuffer("net_ip",server,sizeof(server)); address=server;
    }
    if(!address) address="";
    if(!strcmp(address,"localhost")) return 0;
    ip=Address(address);
    if((ip&0xff000000)==0x0a000000 || (ip&0xfff00000)==0xac100000 ||
       (ip&0xffff0000)==0xc0a80000 || ip==0x7f000001) return 0;
    country=Seek(ip);
    return country ? country : 246;
}
