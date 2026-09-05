/* Negotiated server snapshot production for the reconstructed layout. */
#include "g_nitmod_config.h"
static int spectatorPackets, spectatorSetting;
static int QDECL SpectatorConfigEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == G_CVAR_VARIABLE_STRING_BUFFER) {
        char *out;
        (void)va_arg(args, const char *); out = va_arg(args, char *);
        if(va_arg(args, int) < 1) exit(2);
        out[0] = 0; /* Unrelated weapon policy unavailable in this fixture. */
    } else if(command == G_SEND_SERVER_COMMAND) {
        const char *text;
        int a,b,c,d,e;
        if(va_arg(args, int) != 3) exit(2);
        text = va_arg(args, const char *);
        if(!strncmp(text, "scs ", 4)) {
            if(sscanf(text, "scs %d %d %d %d %d %d", &a,&b,&c,&d,&e,&spectatorSetting) != 6) exit(2);
            ++spectatorPackets;
        }
    } else exit(2);
    va_end(args); return 0;
}
static int CheckSpectatorConfiguration(void) {
    vmCvar_t saved = g_spectatorNames;
    int errors = 0;
    dllEntry(SpectatorConfigEngine);
    G_NITMOD_ClearConfigStrings();
    G_NITMOD_ClientCapabilities(3, NITMOD_PROTOCOL_VERSION, NITMOD_FEATURE_SIMPLE_CS);
    spectatorPackets = 0;
    g_spectatorNames.integer = 1; nitmod_RefreshBaseSettings();
    if(spectatorPackets != 1 || spectatorSetting != 1) ++errors;
    nitmod_RefreshBaseSettings();
    if(spectatorPackets != 1) ++errors;
    g_spectatorNames.integer = 0; nitmod_RefreshBaseSettings();
    if(spectatorPackets != 2 || spectatorSetting != 0) ++errors;
    G_NITMOD_ResetClient(3);
    g_spectatorNames.integer = 1; nitmod_RefreshBaseSettings();
    if(spectatorPackets != 2) ++errors;
    G_NITMOD_ClearConfigStrings();
    g_spectatorNames = saved;
    dllEntry(EngineCallback);
    return errors;
}
