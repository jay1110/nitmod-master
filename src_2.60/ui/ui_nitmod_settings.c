#include "ui_local.h"
#include <limits.h>
#include <float.h>

/* System menu staging contract: read everything before changing anything. */
qboolean UI_NitmodSystemSettings(const char *name) {
    static const char *keys[] = {
        "r_mode", "r_gamma", "rate", "cl_maxpackets", "cl_packetdup", "sensitivity",
        "r_colorbits", "r_fullscreen", "r_lodbias", "r_subdivisions", "r_picmip",
        "r_texturebits", "r_depthbits", "r_ext_compressed_textures", "r_finish",
        "r_dynamiclight", "r_allowextensions", "m_filter", "s_khz", "r_detailtextures", "r_texturemode"
    };
    char values[21][MAX_CVAR_VALUE_STRING], staged[64];
    int i, action;
    if(!name) return qfalse;
    if(!Q_stricmp(name, "systemCvarsGet")) action = 0;
    else if(!Q_stricmp(name, "systemCvarsApply")) action = 1;
    else if(!Q_stricmp(name, "systemCvarsReset")) action = 2;
    else return qfalse;
    if(action != 2) {
        for(i = 0; i < 21; ++i) {
            float value;
            Com_sprintf(staged, sizeof(staged), "ui_%s", keys[i]);
            if(i == 20) {
                trap_Cvar_VariableStringBuffer(action ? staged : keys[i], values[i], sizeof(values[i]));
                continue;
            }
            value = trap_Cvar_VariableValue(action ? staged : keys[i]);
            if(i == 1 || i == 5) {
                if(!(value >= -FLT_MAX && value <= FLT_MAX)) return qtrue;
                Com_sprintf(values[i], sizeof(values[i]), "%f", value);
            } else {
                if(!((double)value >= INT_MIN && (double)value <= INT_MAX)) return qtrue;
                Com_sprintf(values[i], sizeof(values[i]), "%i", (int)value);
            }
        }
        /* Preserve the established zero-rate recovery settings. */
        if(action == 1 && !strcmp(values[2], "0")) {
            strcpy(values[2], "5000"); strcpy(values[3], "30"); strcpy(values[4], "1");
        }
        for(i = 0; i < 21; ++i) {
            Com_sprintf(staged, sizeof(staged), "ui_%s", keys[i]);
            trap_Cvar_Set(action ? keys[i] : staged, values[i]);
        }
    }
    if(action != 0) for(i = 0; i < 21; ++i) {
        Com_sprintf(staged, sizeof(staged), "ui_%s", keys[i]);
        trap_Cvar_Set(staged, "");
    }
    return qtrue;
}

/* UI_Update, original ELF 0x20cf0. Menu names are case-insensitive, but
 * presets and destination cvars are fixed, never executable user input. */
static qboolean UI_ProfileSelector(const char *name, int *out) {
    float value = trap_Cvar_VariableValue(name);
    if(!((double)value >= INT_MIN && (double)value <= INT_MAX)) return qfalse;
    *out = (int)value;
    return qtrue;
}

qboolean UI_NitmodProfileSettings(const char *name) {
    int pitch, handedness;
    qboolean apply;
    if(!name) return qfalse;
    if(!Q_stricmp(name, "profileCvarsGet")) {
        if(UI_ProfileSelector("ui_mousePitch", &pitch))
            trap_Cvar_Set("ui_profile_mousePitch", va("%i", pitch));
        return qtrue;
    }
    if(!Q_stricmp(name, "profileCvarsReset")) {
        trap_Cvar_Set("ui_handedness", "");
        trap_Cvar_Set("ui_profile_mousePitch", "");
        return qtrue;
    }
    apply = !Q_stricmp(name, "profileCvarsApply");
    if(!apply && Q_stricmp(name, "defaultControls")) return qfalse;
    if(!UI_ProfileSelector("ui_handedness", &handedness)) return qtrue;
    if(apply) {
        if(!UI_ProfileSelector("ui_profile_mousePitch", &pitch)) return qtrue;
        trap_Cvar_Set("ui_mousePitch", va("%i", pitch));
        trap_Cvar_SetValue("m_pitch", pitch == 0 ? .022f : -.022f);
    }
    trap_Cmd_ExecuteText(EXEC_APPEND, handedness == 0 ? "exec default.cfg\n" : "exec default_left.cfg\n");
    Controls_SetDefaults(handedness != 0);
    if(apply) {
        trap_Cvar_Set("ui_handedness", "");
        trap_Cvar_Set("ui_profile_mousePitch", "");
    }
    return qtrue;
}

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
