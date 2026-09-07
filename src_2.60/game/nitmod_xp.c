#include "nitmod_xp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
static const char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int NITMOD_XPEncode(const float skills[7],char encoded[1024]) {
    char text[256],result[1024]; int i,n=0,out=0;
    for(i=0;i<7;++i) {
        if(!isfinite(skills[i]) || (double)skills[i]<INT_MIN || (double)skills[i]>INT_MAX) return 0;
        n+=snprintf(text+n,sizeof(text)-n,"S%d\\%d\\",i,(int)skills[i]);
    }
    for(i=0;i<n;i+=3) {
        unsigned int word=(unsigned char)text[i]<<16;
        if(i+1<n) word|=(unsigned char)text[i+1]<<8;
        if(i+2<n) word|=(unsigned char)text[i+2];
        result[out++]=alphabet[word>>18]; result[out++]=alphabet[(word>>12)&63];
        result[out++]=i+1<n?alphabet[(word>>6)&63]:'='; result[out++]=i+2<n?alphabet[word&63]:'=';
    }
    result[out]=0; strcpy(encoded,result); return 1;
}
int NITMOD_XPDecode(const char *encoded,float skills[7]) {
    char text[768],*p,*key,*value,*end; float result[7]={0};
    size_t length; int i,n=0;
    if(!encoded || !skills || !(length=strlen(encoded)) || length>1020 || length%4) return 0;
    for(i=0;i<(int)length;i+=4) {
        unsigned int word=0; int j,padding=0;
        for(j=0;j<4;++j) {
            const char *digit;
            if(encoded[i+j]=='=') { if(j<2 || i+4!=(int)length) return 0; ++padding; word<<=6; }
            else { if(padding || !(digit=strchr(alphabet,encoded[i+j]))) return 0; word=(word<<6)|(unsigned int)(digit-alphabet); }
        }
        if((padding==1 && (word&255)) || (padding==2 && (word&65535))) return 0;
        text[n++]=(char)(word>>16); if(padding<2) text[n++]=(char)(word>>8); if(!padding) text[n++]=(char)word;
    }
    text[n]=0; if((int)strlen(text)!=n) return 0;
    p=text; if(*p=='\\') ++p;
    while(*p) {
        double number;
        key=p; p=strchr(p,'\\'); if(!p) return 0; *p++=0;
        value=p; p=strchr(p,'\\'); if(p) *p++=0;
        if(key[0]=='S' && key[1]>='0' && key[1]<='6' && !key[2]) {
            number=strtod(value,&end);
            if(end==value || *end || !isfinite(number) || number<INT_MIN || number>INT_MAX) return 0;
            result[key[1]-'0']=(float)(int)number;
        }
        if(!p) break;
    }
    memcpy(skills,result,sizeof(result)); return 1;
}
