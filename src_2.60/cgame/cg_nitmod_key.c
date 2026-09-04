#include "cg_local.h"
#include "cg_nitmod_config.h"

/* The original hashes exactly 14 timestamp bytes. A single SHA-1 block is
 * sufficient; this deliberately is not a general-purpose crypto API. */
static unsigned int KeyRotate(unsigned int n, int bits) {
    return (n << bits) | (n >> (32 - bits));
}
static void KeyTimestampHash(const char stamp[15], char hex[41]) {
    unsigned int words[80] = {0};
    unsigned int h[5] = {0x67452301u,0xefcdab89u,0x98badcfeu,0x10325476u,0xc3d2e1f0u};
    unsigned int a, b, c, d, e, f, k, next;
    static const char digits[] = "0123456789ABCDEF";
    int i, j;
    for(i = 0; i < 14; ++i) words[i / 4] |= (unsigned int)(unsigned char)stamp[i] << (24 - 8 * (i % 4));
    words[3] |= 0x8000; words[15] = 112;
    for(i = 16; i < 80; ++i) words[i] = KeyRotate(words[i-3] ^ words[i-8] ^ words[i-14] ^ words[i-16], 1);
    a=h[0]; b=h[1]; c=h[2]; d=h[3]; e=h[4];
    for(i = 0; i < 80; ++i) {
        if(i < 20) { f=(b&c)|(~b&d); k=0x5a827999u; }
        else if(i < 40) { f=b^c^d; k=0x6ed9eba1u; }
        else if(i < 60) { f=(b&c)|(b&d)|(c&d); k=0x8f1bbcdcu; }
        else { f=b^c^d; k=0xca62c1d6u; }
        next=KeyRotate(a,5)+f+e+k+words[i]; e=d; d=c; c=KeyRotate(b,30); b=a; a=next;
    }
    h[0]+=a; h[1]+=b; h[2]+=c; h[3]+=d; h[4]+=e;
    for(i = 0; i < 5; ++i) for(j = 0; j < 8; ++j) hex[i*8+j]=digits[(h[i] >> (28-4*j)) & 15];
    hex[40]=0;
}

qboolean NITMOD_CreateNKey(const qtime_t *time, const unsigned int choices[4], char encoded[45]) {
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char stamp[15], hash[41], key[32];
    int sum = 260, i, step, pos = 0, week;
    if(!time || !choices || !encoded || time->tm_sec < 0 || time->tm_sec > 60 ||
       time->tm_min < 0 || time->tm_min > 59 || time->tm_hour < 0 || time->tm_hour > 23 ||
       time->tm_mday < 1 || time->tm_mday > 31 || time->tm_yday < 0 || time->tm_yday > 365 ||
       time->tm_wday < 0 || time->tm_wday > 6) return qfalse;
    week = (time->tm_yday + 7 - time->tm_wday) / 7;
    /* strftime("%S%j%M%d%w%U%H") without platform-dependent libc time. */
    Com_sprintf(stamp,sizeof(stamp),"%02d%03d%02d%02d%d%02d%02d",time->tm_sec,
        time->tm_yday+1,time->tm_min,time->tm_mday,time->tm_wday,week,time->tm_hour);
    KeyTimestampHash(stamp,hash);
    memcpy(key+2,hash,28);
    for(i = 0; i < 28; ++i) sum += (unsigned char)hash[i];
    sum %= 100;
    /* Equivalent acceptance intervals to the original rejection loop.
     * Bounded selection avoids hanging on a degenerate RNG stream. */
    for(step = 0; step < 4; ++step) {
        int low = (step+1)*25-sum, high = 100-sum, offset;
        if(low < 0) low=0;
        if(high > 25) high=25;
        offset=low+(int)(choices[step] % (unsigned int)(high-low+1));
        key[(step+30)&31]=(char)('A'+offset); sum+=offset;
    }
    for(i = 0; i < 32; i += 3) {
        unsigned int value=(unsigned int)(unsigned char)key[i] << 16;
        if(i+1 < 32) value |= (unsigned int)(unsigned char)key[i+1] << 8;
        if(i+2 < 32) value |= (unsigned char)key[i+2];
        encoded[pos++]=alphabet[value >> 18]; encoded[pos++]=alphabet[(value >> 12)&63];
        encoded[pos++]=i+1 < 32 ? alphabet[(value >> 6)&63] : '=';
        encoded[pos++]=i+2 < 32 ? alphabet[value&63] : '=';
    }
    encoded[pos]=0;
    return qtrue;
}

qboolean NITMOD_GenerateMissingNKey(char guid[33]) {
    qtime_t time;
    unsigned int choices[4];
    char encoded[45], stored[44], decoded[33];
    fileHandle_t file=0;
    int i, length;
    if(!guid) return qfalse;
    memset(&time,0,sizeof(time));
    if(trap_RealTime(&time) <= 0) return qfalse;
    for(i=0;i<4;++i) choices[i]=(unsigned int)rand();
    if(!NITMOD_CreateNKey(&time,choices,encoded)) return qfalse;
    /* Never replace a pre-existing identity, even if it is damaged. */
    length=trap_FS_FOpenFile("nkey.dat",&file,FS_READ);
    if(file) { trap_FS_FCloseFile(file); return qfalse; }
    if(length >= 0) return qfalse;
    trap_FS_FOpenFile("nkey.dat",&file,FS_WRITE);
    if(!file) return qfalse;
    trap_FS_Write(encoded,44,file); trap_FS_FCloseFile(file);
    file=0;
    length=trap_FS_FOpenFile("nkey.dat",&file,FS_READ);
    if(!file) return qfalse;
    if(length != 44) { trap_FS_FCloseFile(file); return qfalse; }
    trap_FS_Read(stored,44,file); trap_FS_FCloseFile(file);
    if(memcmp(encoded,stored,44) || !NITMOD_DecodeNKey(stored,44,decoded)) return qfalse;
    memcpy(guid,decoded,33);
    return qtrue;
}
