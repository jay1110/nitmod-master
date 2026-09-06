/* Production UI settings action with cvar IO sinks, not an engine replay. */
#include "ui_local.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
static const char *names[] = {
    "r_mode", "r_gamma", "rate", "cl_maxpackets", "cl_packetdup", "sensitivity",
    "r_colorbits", "r_fullscreen", "r_lodbias", "r_subdivisions", "r_picmip",
    "r_texturebits", "r_depthbits", "r_ext_compressed_textures", "r_finish",
    "r_dynamiclight", "r_allowextensions", "m_filter", "s_khz", "r_detailtextures", "r_texturemode"
};
static int action, reads, writes, bad, zeroRate;
static void checkRead(const char *name, int i) {
    char expected[64];
    assert(i < 21);
    sprintf(expected, "%s%s", action == 1 ? "ui_" : "", names[i]);
    assert(!strcmp(name, expected));
}
float trap_Cvar_VariableValue(const char *name) {
    int i = reads++;
    checkRead(name, i);
    assert(i < 20);
    return i == bad ? NAN : zeroRate && i == 2 ? 0 : i + .75f;
}
void trap_Cvar_VariableStringBuffer(const char *name, char *out, int size) {
    checkRead(name, reads++);
    assert(reads == 21);
    Q_strncpyz(out, "GL_LINEAR_MIPMAP_LINEAR", size);
}
void trap_Cvar_Set(const char *name, const char *text) {
    char expected[64], value[64];
    int reset = action == 2 || writes >= 21, i = writes++ % 21;
    assert(reads == (action == 2 ? 0 : 21));
    sprintf(expected, "%s%s", reset || action == 0 ? "ui_" : "", names[i]);
    if(reset) value[0] = 0;
    else if(i == 20) strcpy(value, "GL_LINEAR_MIPMAP_LINEAR");
    else if(action == 1 && zeroRate && i >= 2 && i <= 4)
        strcpy(value, i == 2 ? "5000" : i == 3 ? "30" : "1");
    else if(i == 1 || i == 5) sprintf(value, "%f", i + .75);
    else sprintf(value, "%d", zeroRate && i == 2 ? 0 : i);
    assert(!strcmp(name, expected) && !strcmp(text, value));
}
void QDECL Com_Error(int level, const char *format, ...) { abort(); }
void QDECL Com_Printf(const char *format, ...) { abort(); }
#undef vsnprintf
int Q_vsnprintf(char *out, int size, const char *format, va_list args) {
    return vsnprintf(out, size, format, args);
}
int main(void) {
    static const char *commands[] = {"systemCvarsGet", "systemCvarsApply", "systemCvarsReset"};
    int cases = 0;
    for(action = 0; action < 3; ++action)
    for(zeroRate = 0; zeroRate < 2; ++zeroRate)
    for(bad = -1; bad < 20; ++bad) {
        reads = writes = 0;
        assert(UI_NitmodSystemSettings(commands[action]));
        assert(writes == (action == 2 ? 21 : bad >= 0 ? 0 : action == 1 ? 42 : 21));
        ++cases;
    }
    assert(!UI_NitmodSystemSettings(NULL));
    assert(!UI_NitmodSystemSettings("unknown"));
    printf("WASM UI system settings: %d get/apply/reset cases passed\n", cases);
    return 0;
}
