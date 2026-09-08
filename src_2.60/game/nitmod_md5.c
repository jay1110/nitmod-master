#include "nitmod_md5.h"
#include <stdint.h>
#include <string.h>
static const uint32_t constants[64]={0xd76aa478U,0xe8c7b756U,0x242070dbU,0xc1bdceeeU,0xf57c0fafU,0x4787c62aU,0xa8304613U,0xfd469501U,0x698098d8U,0x8b44f7afU,0xffff5bb1U,0x895cd7beU,0x6b901122U,0xfd987193U,0xa679438eU,0x49b40821U,0xf61e2562U,0xc040b340U,0x265e5a51U,0xe9b6c7aaU,0xd62f105dU,0x02441453U,0xd8a1e681U,0xe7d3fbc8U,0x21e1cde6U,0xc33707d6U,0xf4d50d87U,0x455a14edU,0xa9e3e905U,0xfcefa3f8U,0x676f02d9U,0x8d2a4c8aU,0xfffa3942U,0x8771f681U,0x6d9d6122U,0xfde5380cU,0xa4beea44U,0x4bdecfa9U,0xf6bb4b60U,0xbebfbc70U,0x289b7ec6U,0xeaa127faU,0xd4ef3085U,0x04881d05U,0xd9d4d039U,0xe6db99e5U,0x1fa27cf8U,0xc4ac5665U,0xf4292244U,0x432aff97U,0xab9423a7U,0xfc93a039U,0x655b59c3U,0x8f0ccc92U,0xffeff47dU,0x85845dd1U,0x6fa87e4fU,0xfe2ce6e0U,0xa3014314U,0x4e0811a1U,0xf7537e82U,0xbd3af235U,0x2ad7d2bbU,0xeb86d391U};
static const unsigned char shifts[64]={7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21};
static void Block(uint32_t h[4],const unsigned char *p) {
    uint32_t w[16],a=h[0],b=h[1],c=h[2],d=h[3],f,t; unsigned int i,g;
    for(i=0;i<16;++i) w[i]=(uint32_t)p[i*4]|((uint32_t)p[i*4+1]<<8)|((uint32_t)p[i*4+2]<<16)|((uint32_t)p[i*4+3]<<24);
    for(i=0;i<64;++i) {
        if(i<16){f=(b&c)|(~b&d);g=i;}else if(i<32){f=(d&b)|(~d&c);g=(5*i+1)%16;}
        else if(i<48){f=b^c^d;g=(3*i+5)%16;}else{f=c^(b|~d);g=(7*i)%16;}
        f+=a+constants[i]+w[g];t=d;d=c;c=b;b+=(f<<shifts[i])|(f>>(32-shifts[i]));a=t;
    }
    h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;
}
void NITMOD_MD5Hex(const void *bytes,size_t length,char hex[33]) {
    const unsigned char *p=(const unsigned char *)bytes; unsigned char tail[128];
    uint32_t h[4]={0x67452301U,0xefcdab89U,0x98badcfeU,0x10325476U};
    uint64_t bits=(uint64_t)length*8U; size_t remaining=length,n; unsigned int i,b;
    while(remaining>=64){Block(h,p);p+=64;remaining-=64;}
    memset(tail,0,sizeof(tail));if(remaining)memcpy(tail,p,remaining);tail[remaining]=0x80;
    n=remaining<56?64:128;for(i=0;i<8;++i)tail[n-8+i]=(unsigned char)(bits>>(i*8));
    Block(h,tail);if(n==128)Block(h,tail+64);
    for(i=0;i<16;++i){b=(h[i/4]>>((i%4)*8))&255U;hex[i*2]="0123456789abcdef"[b>>4];hex[i*2+1]="0123456789abcdef"[b&15];}hex[32]=0;
}
