#include "g_local.h"
#include <assert.h>
static unsigned char bytes[256];
static int flags=1,size=7,opens,closes;
void G_LogPrintf(const char *fmt,...) {}
int trap_Cvar_VariableIntegerValue(const char *name) { assert(!strcmp(name,"g_countryflags")); return flags; }
void trap_Cvar_VariableStringBuffer(const char *name,char *out,int capacity) {
    assert(!strcmp(name,"net_ip")); strcpy(out,"200.1.2.3");
}
int trap_FS_FOpenFile(const char *name,fileHandle_t *file,fsMode_t mode) {
    assert(!strcmp(name,"GeoIP.dat") && mode==FS_READ); ++opens; *file=size<0 ? 0 : 7; return size;
}
void trap_FS_FCloseFile(fileHandle_t file) { assert(file==7); ++closes; }
void trap_FS_Read(void *out,int length,fileHandle_t file) { assert(length<=sizeof(bytes) && file==7); memcpy(out,bytes,length); }
static void child(int offset,unsigned int node) { bytes[offset]=node;bytes[offset+1]=node>>8;bytes[offset+2]=node>>16; }
int main(void) {
    int n; const char *privateIPs[]={"localhost","10.1.2.3:27960","172.16.0.1","172.31.255.255","192.168.1.2","127.0.0.1"};
    assert(G_NITMOD_GeoIPCountry("localhost",0)==255);
    flags=0;G_NITMOD_GeoIPLoad();assert(!opens);
    flags=1;size=-1;G_NITMOD_GeoIPLoad();assert(G_NITMOD_GeoIPCountry("8.8.8.8",0)==255 && !closes);
    size=0;G_NITMOD_GeoIPLoad();assert(closes==1);
    size=7;child(0,0xffff05);child(3,0xffff09);G_NITMOD_GeoIPLoad();
    assert(G_NITMOD_GeoIPCountry("8.8.8.8:27960",0)==5);
    assert(G_NITMOD_GeoIPCountry("200.1.2.3",0)==9);
    for(n=0;n<sizeof(privateIPs)/sizeof(privateIPs[0]);++n) assert(G_NITMOD_GeoIPCountry(privateIPs[n],0)==0);
    assert(G_NITMOD_GeoIPCountry("172.15.0.1",0)==9 && G_NITMOD_GeoIPCountry("172.32.0.1",0)==9);
    assert(G_NITMOD_GeoIPCountry("8.8.8.8",1)==5);flags=3;assert(G_NITMOD_GeoIPCountry("8.8.8.8",1)==9);
    child(0,0xffff00);G_NITMOD_GeoIPLoad();assert(G_NITMOD_GeoIPCountry("8.8.8.8",0)==246);
    child(0,0xfffffe);G_NITMOD_GeoIPLoad();assert(G_NITMOD_GeoIPCountry("8.8.8.8",0)==254);
    child(0,99999);G_NITMOD_GeoIPLoad();assert(G_NITMOD_GeoIPCountry("8.8.8.8",0)==255);
    child(0,0);G_NITMOD_GeoIPLoad();assert(G_NITMOD_GeoIPCountry("0.0.0.0",0)==255); /* cyclic trie terminates */
    size=6;child(0,0xffff05);G_NITMOD_GeoIPLoad();assert(G_NITMOD_GeoIPCountry("8.8.8.8",0)==255);
    size=13;child(0,1);child(6,0xffff2a);child(9,0xffff2b);G_NITMOD_GeoIPLoad();
    assert(G_NITMOD_GeoIPCountry("8.8.8.8",0)==42 && G_NITMOD_GeoIPCountry("80.1.1.1",0)==43);
    G_NITMOD_GeoIPClose();G_NITMOD_GeoIPClose();assert(G_NITMOD_GeoIPCountry("8.8.8.8",0)==255);
    puts("GeoIP engine-FS, trie, private ranges, bot option, missing/corrupt DB and reload: PASS");return 0;
}
