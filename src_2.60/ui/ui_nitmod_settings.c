#include "ui_local.h"
#include <limits.h>
#include <float.h>

/* UI_Update, original ELF 0x20cf0. Menu names are case-insensitive, but
 * presets and destination cvars are fixed, never executable user input. */
void UI_Update(const char *name) {
    static const char *presets[] = {
        "exec preset_high_ui.cfg\n", "exec preset_normal_ui.cfg\n",
        "exec preset_fast_ui.cfg\n", "exec preset_fastest_ui.cfg\n"
    };
    static const int subdivisions[] = {4, 12, 20};
    float value;
    int selected;
    char text[MAX_STRING_CHARS];
    if(!name || !*name) return;
    if(!Q_stricmp(name, "ui_SetName") || !Q_stricmp(name, "ui_GetName")) {
        qboolean set = !Q_stricmp(name, "ui_SetName");
        trap_Cvar_VariableStringBuffer(set ? "ui_Name" : "name", text, sizeof(text));
        trap_Cvar_Set(set ? "name" : "ui_Name", text);
        return;
    }
    if(!Q_stricmp(name, "ui_setRate")) {
        value = trap_Cvar_VariableValue("ui_rate");
        if(!(value >= -FLT_MAX && value <= FLT_MAX)) return;
        trap_Cvar_Set("ui_cl_maxpackets", value >= 5000 ? "100" : "15");
        trap_Cvar_Set("ui_cl_packetdup", value >= 4000 && value < 5000 ? "2" : "1");
        return;
    }
    if(Q_stricmp(name, "r_colorbits") && Q_stricmp(name, "ui_r_lodbias") &&
       Q_stricmp(name, "ui_glCustom") && Q_stricmp(name, "ui_mousePitch")) return;
    value = trap_Cvar_VariableValue(name);
    /* Avoid undefined float-to-int conversion for invalid engine/cvar input. */
    if(!((double)value >= INT_MIN && (double)value <= INT_MAX)) return;
    selected = (int)value;
    if(!Q_stricmp(name, "r_colorbits")) {
        if(selected == 0 || selected == 16 || selected == 32) {
            trap_Cvar_SetValue("r_depthbits", selected == 32 ? 24 : selected);
            if(selected != 32) trap_Cvar_SetValue("r_stencilbits", 0);
        }
    } else if(!Q_stricmp(name, "ui_r_lodbias")) {
        if(selected >= 0 && selected < 3) trap_Cvar_SetValue("ui_r_subdivisions", subdivisions[selected]);
    } else if(!Q_stricmp(name, "ui_glCustom")) {
        if(selected >= 0 && selected < 4) trap_Cmd_ExecuteText(EXEC_APPEND, presets[selected]);
    } else {
        trap_Cvar_SetValue("m_pitch", selected == 0 ? .022f : -.022f);
    }
}
