#include "g_local.h"
#include <limits.h>
#include <stdio.h>
gentity_t g_entities[MAX_GENTITIES];
level_locals_t level;
static gclient_t client;
static int events, errors;
void G_ExplodeMissile(gentity_t *entity) { (void)entity; ++errors; }
void G_AddEvent(gentity_t *entity, int event, int parm) {
    if(entity != &g_entities[1] || event != EV_NOAMMO || parm ||
       client.ps.ammoclip[WP_SATCHEL] != 1 || client.ps.ammo[WP_SATCHEL_DET] ||
       client.ps.ammoclip[WP_SATCHEL_DET]) ++errors;
    ++events;
}
int main(void) {
    static const int times[] = {0, 100, -1, INT_MAX};
    gentity_t self;
    int t, weapon, type, present, flags, cases = 0;
    for(flags = 0; flags < 256; ++flags) {
        memset(&self, 0, sizeof(self)); self.health = 5;
        G_NITMOD_ConfigureSatchelDamage(&self, flags);
        if(self.health != ((flags & 2) ? 40 : 5) ||
           self.takedamage != ((flags & 2) ? qtrue : qfalse) ||
           self.die != ((flags & 2) ? G_NITMOD_SatchelDie : NULL)) ++errors;
    }
    G_NITMOD_ConfigureSatchelDamage(NULL, 2);
    G_NITMOD_SatchelDie(NULL, NULL, NULL, 0, 0);
    for(t = 0; t < 4; ++t) for(weapon = 0; weapon < 2; ++weapon)
    for(type = 0; type < 2; ++type) for(present = 0; present < 2; ++present) {
        memset(&self, 0, sizeof(self)); memset(&client, 0, sizeof(client));
        level.time = times[t]; events = 0;
        self.s.eType = type ? ET_MISSILE : ET_GENERAL;
        self.s.clientNum = 1; self.free = G_ExplodeMissile;
        self.r.contents = 123; self.nextthink = 77;
        g_entities[1].client = present ? &client : NULL;
        client.ps.weapon = weapon ? WP_SATCHEL_DET : WP_KNIFE;
        client.ps.ammoclip[WP_SATCHEL] = 7;
        if(type) {
            G_NITMOD_ConfigureSatchelDamage(&self, 2);
            self.die(&self, &self, NULL, 5, 0);
        } else G_NITMOD_SatchelDie(&self, &self, NULL, 5, 0);
        if(type) {
            if(self.free || self.r.contents != CONTENTS_CORPSE || self.think != G_ExplodeMissile ||
               self.nextthink != (times[t] == INT_MAX ? INT_MIN : times[t] + 1)) ++errors;
        } else if(self.free != G_ExplodeMissile || self.r.contents != 123 || self.nextthink != 77 || self.think) ++errors;
        if(client.ps.ammoclip[WP_SATCHEL] != (type && present ? 1 : 7) ||
           events != (type && present && weapon ? 1 : 0)) ++errors;
        ++cases;
    }
    printf("Satchel death: %d cases plus 256 spawn masks, %d errors\n", cases, errors);
    return errors != 0;
}
