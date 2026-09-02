#include "g_local.h"
#include "g_nitmod_equipment.h"
static gclient_t client, expected;
static char saved[128], lastName[40];
static int reads, writes;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
void trap_Cvar_Set( const char *name, const char *value ) {
    strcpy(lastName, name); strcpy(saved, value); writes++;
}
void trap_Cvar_VariableStringBuffer( const char *name, char *buffer, int size ) {
    strcpy(lastName, name);
    strncpy(buffer, saved, size - 1); buffer[size - 1] = 0; reads++;
}
int main( void ) {
    static const char *bad[] = { "", "0 1", "2 1", "1", "1 -1", "1 2", "1 1 extra", "1 1 ", "garbage" };
    int i;
    client.sess.playerWeapon = WP_KAR98;
    client.sess.rifleGrenadeStatus = 1;
    G_NITMOD_WriteEquipment(&client, 3);
    CHECK( !strcmp(saved, "1 1") && !strcmp(lastName, "nitmod_equipment3") );
    client.sess.rifleGrenadeStatus = 0;
    expected = client; expected.sess.rifleGrenadeStatus = 1;
    G_NITMOD_ReadEquipment(&client, 3);
    CHECK( !memcmp(&client, &expected, sizeof(client)) );
    client.sess.rifleGrenadeStatus = 0;
    G_NITMOD_WriteEquipment(&client, MAX_CLIENTS - 1);
    CHECK( !strcmp(saved, "1 0") );
    for( i = 0; i < sizeof(bad) / sizeof(bad[0]); i++ ) {
        strcpy(saved, bad[i]); client.sess.rifleGrenadeStatus = 1;
        expected = client; expected.sess.rifleGrenadeStatus = 0;
        G_NITMOD_ReadEquipment(&client, 3);
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
    }
    i = reads;
    G_NITMOD_ReadEquipment(&client, -1);
    G_NITMOD_ReadEquipment(NULL, 0);
    CHECK( reads == i );
    i = writes;
    G_NITMOD_WriteEquipment(&client, MAX_CLIENTS);
    G_NITMOD_WriteEquipment(NULL, 0);
    CHECK( writes == i );
    return 0;
}
