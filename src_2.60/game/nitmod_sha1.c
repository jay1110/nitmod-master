#include "nitmod_sha1.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
static uint32_t Rotate(uint32_t x,int n) { return (x<<n)|(x>>(32-n)); }
void NITMOD_SHA1Text(const char *text,char result[41]) {
    uint32_t h[5]={0x67452301,0xefcdab89,0x98badcfe,0x10325476,0xc3d2e1f0};
    size_t length=strlen(text),blocks=(length+9+63)/64,block;
    uint64_t bits=(uint64_t)length*8;
    for(block=0;block<blocks;++block) {
        uint32_t w[80],a,b,c,d,e,f,k,t; int i,j;
        for(i=0;i<16;++i) {
            w[i]=0;
            for(j=0;j<4;++j) {
                size_t at=block*64+i*4+j; unsigned int byte;
                if(at<length) byte=(unsigned char)text[at];
                else if(at==length) byte=128;
                else if(at>=blocks*64-8) byte=(unsigned int)(bits>>((blocks*64-1-at)*8))&255;
                else byte=0;
                w[i]=(w[i]<<8)|byte;
            }
        }
        for(i=16;i<80;++i) w[i]=Rotate(w[i-3]^w[i-8]^w[i-14]^w[i-16],1);
        a=h[0];b=h[1];c=h[2];d=h[3];e=h[4];
        for(i=0;i<80;++i) {
            if(i<20) { f=(b&c)|(~b&d);k=0x5a827999; }
            else if(i<40) { f=b^c^d;k=0x6ed9eba1; }
            else if(i<60) { f=(b&c)|(b&d)|(c&d);k=0x8f1bbcdc; }
            else { f=b^c^d;k=0xca62c1d6; }
            t=Rotate(a,5)+f+e+k+w[i];e=d;d=c;c=Rotate(b,30);b=a;a=t;
        }
        h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;h[4]+=e;
    }
    sprintf(result,"%08X%08X%08X%08X%08X",(unsigned)h[0],(unsigned)h[1],(unsigned)h[2],(unsigned)h[3],(unsigned)h[4]);
}
