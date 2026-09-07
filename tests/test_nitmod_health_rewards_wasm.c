/* Tests actual production health functions with independent level/mask. */
#include "../src_2.60/game/g_client.c"
#include <assert.h>
#include <stdio.h>
int main(void) {
    static gclient_t client;
    static gentity_t ent;
    int cls, mask, level, medics, war, dm, custom, count = 0;
    for(cls = 0; cls < 5; ++cls)
    for(mask = 0; mask < 64; ++mask)
    for(level = 0; level < 2; ++level)
    for(medics = 0; medics < 5; ++medics)
    for(war = 0; war < 2; ++war)
    for(dm = 0; dm < 2; ++dm)
    for(custom = 0; custom < 2; ++custom) {
        int base = war || dm ? 100 : 100 + (medics < 3 ? medics * 10 : 25);
        int bonus = !war && !dm && (mask & 8) ? 15 : 0;
        int expected = custom ? 180 : base + bonus;
        memset(&client, 0, sizeof(client));
        client.sess.playerType = cls;
        client.sess.skill[SK_BATTLE_SENSE] = level ? 5 : 0;
        client.sess.nitmodSkillMasks[SK_BATTLE_SENSE] = mask;
        G_NITMOD_SetHealthLimits(&client, medics, war, dm ? 8 : 2, custom ? 180 : 0);
        assert(client.pers.maxHealth == expected);
        assert(client.ps.stats[STAT_MAX_HEALTH] == expected);
        assert(client.ps.stats[STAT_NITMOD_MAX_HEALTH] ==
            (cls == PC_MEDIC && !custom && !(war && dm) ? (int)(expected * 1.12) : expected));
        assert(G_NITMOD_SpawnHealth(&client,war,dm ? 8 : 2,custom ? 180 : 0) == (custom ? 180 : base));
        ent.client=&client; ent.health=37; client.ps.stats[STAT_HEALTH]=0;
        ApplySpawnHealth(&ent,qfalse,war,dm ? 8 : 2,custom ? 180 : 0);
        assert(ent.health==37 && client.ps.stats[STAT_HEALTH]==37);
        ApplySpawnHealth(&ent,qtrue,war,dm ? 8 : 2,custom ? 180 : 0);
        assert(ent.health==(custom ? 180 : base) && client.ps.stats[STAT_HEALTH]==ent.health);
        ++count;
    }
    printf("Health reward adapter: %d combinations passed\n", count);
    return 0;
}
