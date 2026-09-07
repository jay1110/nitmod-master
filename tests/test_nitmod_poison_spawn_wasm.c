/* Actual spawn entrypoint; engine/bot/config boundaries are stubbed. */
#include "../src_2.60/game/g_client.c"
#include <assert.h>
#include <stdio.h>
vmCvar_t ui_gameType, g_knifeonly, g_dualSMG, g_poison;
vmCvar_t g_gametype, g_DMOptions;
gentity_t g_entities[MAX_GENTITIES];
level_locals_t level;
static int war, poisonEvents, satchelPresent, weaponOptions, deniedWeapon, medicOptions;
static int satchelLookups;
int G_NITMOD_ConfiguredWarMode(void) { return war; }
int G_NITMOD_LegacyCvarInteger(const char *name, int fallback) {
    return !strcmp(name, "g_weapons") ? weaponOptions : fallback;
}
int G_NITMOD_ReadMedicOptions(unsigned int *options) { *options = medicOptions; return 1; }
int Bot_WeaponGameToBot(int weapon) { return weapon; }
void Bot_Event_AddWeapon(int client, int weapon) {
    assert(client == 0);
    if(weapon == WP_POISON_SYRINGE) ++poisonEvents;
}
void Bot_Event_ResetWeapons(int client) { assert(client == 0); }
void BotSetPOW(int client, qboolean pow) { (void)client; (void)pow; }
qboolean G_IsWeaponDisabled(gentity_t *ent, weapon_t weapon) { return weapon == deniedWeapon; }
gentity_t *G_FindSatchel(gentity_t *ent) { ++satchelLookups; return satchelPresent ? &g_entities[1] : NULL; }

int main(void) {
    static gclient_t client, withoutPoison;
    int team, cls, light, aid, numeric, enabled, knife, defaults, count = 0;
    ammotable_t saved = *GetAmmoTableData(WP_POISON_SYRINGE);
    for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
    for(cls = PC_SOLDIER; cls <= PC_COVERTOPS; ++cls)
    for(light = 0; light < 2; ++light)
    for(aid = 0; aid < 2; ++aid)
    for(numeric = 0; numeric < 2; ++numeric)
    for(enabled = 0; enabled < 2; ++enabled)
    for(knife = 0; knife < 2; ++knife)
    for(defaults = 0; defaults < 2; ++defaults)
    for(war = 0; war <= 5; ++war) {
        int shouldGrant = light && enabled && !knife && (war == 0 || war == 5);
        int reserve = defaults ? 7 : saved.defaultStartingAmmo;
        int clip = defaults ? 9 : saved.defaultStartingClip;
        memset(&client, 0, sizeof(client));
        client.sess.sessionTeam = team;
        client.sess.playerType = cls;
        client.sess.skill[SK_LIGHT_WEAPONS] = numeric ? 5 : 0;
        client.sess.skill[SK_FIRST_AID] = numeric ? 5 : 0;
        client.sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] = light ? 16u : 0;
        client.sess.nitmodSkillMasks[SK_FIRST_AID] = aid ? 16u : 0;
        g_knifeonly.integer = knife;
        GetAmmoTableData(WP_POISON_SYRINGE)->defaultStartingAmmo = reserve;
        GetAmmoTableData(WP_POISON_SYRINGE)->defaultStartingClip = clip;
        withoutPoison = client;
        g_poison.integer = 0;
        SetWolfSpawnWeapons(&withoutPoison);
        g_poison.integer = enabled;
        poisonEvents = 0;
        SetWolfSpawnWeapons(&client);
        assert(!!COM_BitCheck(client.ps.weapons, WP_POISON_SYRINGE) == shouldGrant);
        assert(poisonEvents == shouldGrant);
        if(shouldGrant) {
            COM_BitSet(withoutPoison.ps.weapons, WP_POISON_SYRINGE);
            withoutPoison.ps.ammo[BG_FindAmmoForWeapon(WP_POISON_SYRINGE)] = reserve;
            withoutPoison.ps.ammoclip[BG_FindClipForWeapon(WP_POISON_SYRINGE)] = clip;
        }
        assert(!memcmp(&client, &withoutPoison, sizeof(client)));
        ++count;
    }
    *GetAmmoTableData(WP_POISON_SYRINGE) = saved;
    printf("Poison actual spawn: %d cases passed\n", count);
    return 0;
}
