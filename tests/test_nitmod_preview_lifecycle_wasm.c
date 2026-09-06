#include "ui_local.h"
#include <assert.h>
#include <stdio.h>
extern void UI_DrawPreviewCinematic(rectDef_t *, float, vec4_t);
static int starts, runs, draws, stops, nextHandle;
void Com_Error(int code, const char *format, ...) { (void)code; (void)format; assert(0); }
int trap_CIN_PlayCinematic(const char *name, int x, int y, int w, int h, int flags) {
    assert(!strcmp(name, "intro.roq"));
    assert(flags == (CIN_loop | CIN_silent));
    ++starts; return nextHandle;
}
e_status trap_CIN_RunCinematic(int handle) { assert(handle == 7); ++runs; return FMV_PLAY; }
e_status trap_CIN_StopCinematic(int handle) { assert(handle == 7); ++stops; return FMV_EOF; }
void trap_CIN_SetExtents(int handle,int x,int y,int w,int h) { assert(handle == 7 && x == 10 && y == 20 && w == 160 && h == 90); }
void trap_CIN_DrawCinematic(int handle) { assert(handle == 7); ++draws; }
int main(void) {
    rectDef_t rect = {10,20,160,90};
    vec4_t color = {1,1,1,1};
    uiInfo.movieCount = 1; uiInfo.movieIndex = 0;
    uiInfo.movieList[0] = "intro"; uiInfo.previewMovie = -1;
    nextHandle = 7;
    UI_DrawPreviewCinematic(&rect,1,color);
    UI_DrawPreviewCinematic(&rect,1,color);
    assert(starts == 1 && runs == 2 && draws == 2 && !stops);
    uiInfo.movieIndex = 1;
    UI_DrawPreviewCinematic(&rect,1,color);
    assert(stops == 1 && uiInfo.previewMovie == -1);
    uiInfo.movieIndex = 0; nextHandle = -1;
    UI_DrawPreviewCinematic(&rect,1,color);
    UI_DrawPreviewCinematic(&rect,1,color);
    assert(starts == 2 && runs == 2 && draws == 2 && uiInfo.previewMovie == -2);
    uiInfo.movieCount = 0;
    UI_DrawPreviewCinematic(&rect,1,color);
    assert(stops == 1 && uiInfo.previewMovie == -1);
    puts("Preview lifecycle: start, reuse, invalid selection, failure latch and empty list passed");
    return 0;
}
