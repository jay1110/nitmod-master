#include "g_local.h"
#include <stdio.h>

gentity_t g_entities[MAX_GENTITIES];
static gclient_t client, expected;
static void DummyFree(gentity_t *entity) { (void)entity; }
int main(void) {
    static const int owners[] = {-1, 0, MAX_CLIENTS - 1, MAX_GENTITIES - 1, MAX_GENTITIES};
    gentity_t satchel;
    int o, type, connected, playerClass, weapon, present, cases = 0, errors = 0;
    G_FreeSatchel(NULL);
    for(o = 0; o < 5; ++o) for(type = 0; type < 2; ++type)
    for(connected = 0; connected < 3; ++connected) for(playerClass = 0; playerClass < 5; ++playerClass)
    for(weapon = 0; weapon < 2; ++weapon) for(present = 0; present < 2; ++present) {
        memset(&client, 0, sizeof(client));
        memset(&satchel, 0, sizeof(satchel));
        client.pers.connected = connected;
        client.sess.playerType = playerClass;
        client.ps.weapon = weapon ? WP_SATCHEL_DET : WP_KNIFE;
        client.ps.ammo[WP_SATCHEL_DET] = 9;
        client.ps.ammoclip[WP_SATCHEL_DET] = 8;
        client.ps.ammoclip[WP_SATCHEL] = 7;
        client.ps.eventSequence = 21;
        expected = client;
        satchel.free = DummyFree;
        satchel.s.eType = type ? ET_MISSILE : ET_GENERAL;
        satchel.s.clientNum = owners[o];
        if(owners[o] >= 0 && owners[o] < MAX_GENTITIES) {
            g_entities[owners[o]].client = present ? &client : NULL;
            if(type && present && connected == CON_CONNECTED && playerClass == PC_COVERTOPS) {
                expected.ps.ammo[WP_SATCHEL_DET] = 0;
                expected.ps.ammoclip[WP_SATCHEL_DET] = 0;
                expected.ps.ammoclip[WP_SATCHEL] = 1;
            }
        }
        G_FreeSatchel(&satchel);
        if(satchel.free || memcmp(&client, &expected, sizeof(client))) ++errors;
        ++cases;
    }
    printf("Satchel free: %d cases, %d errors\n", cases, errors);
    return errors != 0;
}
