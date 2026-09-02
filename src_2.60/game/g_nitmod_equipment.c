#include "g_local.h"
#include "g_nitmod_equipment.h"

void G_NITMOD_ReadEquipment( gclient_t *client, int clientNum ) {
    char name[40], value[MAX_CVAR_VALUE_STRING];
    if( !client ) return;
    client->sess.rifleGrenadeStatus = 0;
    if( clientNum < 0 || clientNum >= MAX_CLIENTS ) return;
    sprintf(name, "nitmod_equipment%i", clientNum);
    trap_Cvar_VariableStringBuffer(name, value, sizeof(value));
    /* Version 1 stores a canonical flag. Legacy/malformed/unknown versions
     * remain neutral rather than reading an unrelated ET session integer. */
    if( !strcmp(value, "1 1") ) client->sess.rifleGrenadeStatus = 1;
}

void G_NITMOD_WriteEquipment( const gclient_t *client, int clientNum ) {
    char name[40];
    if( !client || clientNum < 0 || clientNum >= MAX_CLIENTS ) return;
    sprintf(name, "nitmod_equipment%i", clientNum);
    trap_Cvar_Set(name, client->sess.rifleGrenadeStatus ? "1 1" : "1 0");
}
