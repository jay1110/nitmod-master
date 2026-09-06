#include "ui_local.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static float input;
static int writes;
static char keys[2][64], values[2][128];
float trap_Cvar_VariableValue(const char *name) { return input; }
void trap_Cvar_Set(const char *name, const char *value) {
    assert(writes < 2);
    strcpy(keys[writes], name); strcpy(values[writes++], value);
}
void trap_Cvar_SetValue(const char *name, float value) {
    char text[64]; sprintf(text, "%g", value); trap_Cvar_Set(name, text);
}
void trap_Cvar_VariableStringBuffer(const char *name, char *out, int size) {
    Q_strncpyz(out, "Player Name", size);
}
void trap_Cmd_ExecuteText(int when, const char *text) {
    assert(when == EXEC_APPEND); trap_Cvar_Set("exec", text);
}
void QDECL Com_Error(int level, const char *format, ...) { abort(); }

int main(void) {
    static const float rates[] = {3999, 4000, 4999, 5000, 25000};
    int i;
    for(i = 0; i < 5; ++i) {
        input = rates[i]; writes = 0; UI_Update("ui_setRate");
        assert(writes == 2 && !strcmp(keys[0], "ui_cl_maxpackets"));
        assert(!strcmp(values[0], i >= 3 ? "100" : "15"));
        assert(!strcmp(values[1], i == 1 || i == 2 ? "2" : "1"));
    }
    input = 32; writes = 0; UI_Update("r_colorbits");
    assert(writes == 1 && !strcmp(keys[0], "r_depthbits") && !strcmp(values[0], "24"));
    input = 16; writes = 0; UI_Update("r_colorbits");
    assert(writes == 2 && !strcmp(values[0], "16") && !strcmp(keys[1], "r_stencilbits"));
    input = 2; writes = 0; UI_Update("ui_r_lodbias");
    assert(writes == 1 && !strcmp(values[0], "20"));
    input = 3; writes = 0; UI_Update("ui_glCustom");
    assert(writes == 1 && !strcmp(values[0], "exec preset_fastest_ui.cfg\n"));
    input = 4; writes = 0; UI_Update("ui_glCustom"); assert(writes == 0);
    writes = 0; UI_Update("ui_SetName");
    assert(writes == 1 && !strcmp(keys[0], "name") && !strcmp(values[0], "Player Name"));
    puts("WASM UI_Update: rate boundaries, graphics and name actions passed");
    return 0;
}
