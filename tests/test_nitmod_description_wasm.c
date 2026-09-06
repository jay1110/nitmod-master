/* Execute actual text layout with deterministic glyph metrics, not GL. */
#include "ui_local.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

displayContextDef_t *DC;
static displayContextDef_t context;
static char lines[16][1024];
static float xs[16], ys[16];
static int count;
static int Width(const char *s,float scale,int limit) { return (int)strlen(s); }
static int Height(const char *s,float scale,int limit) { return 10; }
static void Draw(float x,float y,float scale,vec4_t color,const char *s,float adjust,int limit,int style) {
    assert(count<16 && strlen(s)<1024);
    strcpy(lines[count],s); xs[count]=x; ys[count]=y; ++count;
}
static void Render(const char *s,int align,int stars,float width) {
    rectDef_t rect={100,200,width,100};
    vec4_t color={1,1,1,1};
    count=0;
    UI_DrawDescriptionText(&rect,1,color,20,7,0,align,s,stars);
}
int main(void) {
    char longword[2501];
    int align;
    DC=&context; context.textWidth=Width; context.textHeight=Height; context.drawText=Draw;
    for(align=0;align<3;++align) {
        Render("abc\ndef",align,0,100);
        assert(count==2 && !strcmp(lines[0],"abc") && !strcmp(lines[1],"def"));
        assert(ys[0]==207 && ys[1]==222);
        assert(xs[0]==(align==ITEM_ALIGN_RIGHT?117:align==ITEM_ALIGN_CENTER?118.5f:120));
    }
    Render("a\n\nb",0,0,100); assert(count==2 && ys[1]==237);
    Render("a*b",0,0,100); assert(count==1 && !strcmp(lines[0],"a*b"));
    Render("a*b",0,1,100); assert(count==2 && !strcmp(lines[1],"b"));
    Render("a*b**c",0,2,100); assert(count==2 && !strcmp(lines[0],"a*b") && !strcmp(lines[1],"c"));
    Render("a\rb",0,0,100); assert(count==1 && !strcmp(lines[0],"a b"));
    Render("",0,0,100); assert(count==0);
    Render("abc",0,0,0); assert(count==0);
    memset(longword,'x',2500); longword[2500]=0;
    Render(longword,0,0,100);
    assert(count==3 && strlen(lines[0])==1023 && strlen(lines[1])==1023 && strlen(lines[2])==454);
    puts("Description WASM: alignment, offsets, breaks, stars, CR, empty/invalid width and long-word cases passed");
    return 0;
}
