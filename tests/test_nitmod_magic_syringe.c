#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_ammo_rewards.h"
#include <assert.h>
#include <stdio.h>
vmCvar_t ui_gameType;
static void ResetOtherAmmo(playerState_t *ps) {
    memset(ps, 0, sizeof(*ps));
    ps->ammoclip[BG_FindClipForWeapon(WP_KNIFE)] = 8;
}
/* No firearm is owned in this fixture; entering that branch is a failure. */
qboolean BG_IsAkimboWeapon(int weapon) { (void)weapon; assert(0); return qfalse; }
void Com_Printf(const char *format, ...) { (void)format; }
void Com_Error(int code, const char *format, ...) { (void)code; (void)format; assert(0); }
int main(void) {
    assert(GetAmmoTableData(WP_KNIFE)->maxammo == 8);
    assert(GetAmmoTableData(WP_KNIFE)->maxclip == 8);
    assert(GetAmmoTableData(WP_KNIFE)->defaultStartingAmmo == 0);
    assert(GetAmmoTableData(WP_KNIFE)->defaultStartingClip == 4);
    static playerState_t ps;
    int skills[SK_NUM_SKILLS] = {0};
    int base, level, amount, tests = 0;
    int clip = BG_FindClipForWeapon(WP_MEDIC_SYRINGE);
    for(base = 2; base <= 20; base += 3)
    for(level = 0; level < 6; ++level)
    for(amount = 0; amount <= 3; ++amount) {
        int limit = base + (level >= 2 ? 2 : 0);
        ResetOtherAmmo(&ps);
        skills[SK_FIRST_AID] = level;
        GetAmmoTableData(WP_MEDIC_SYRINGE)->maxammo = base;
        COM_BitSet(ps.weapons, WP_MEDIC_SYRINGE);
        /* Fill grenades so a probe reaches the syringe branch. */
        ps.ammoclip[BG_FindClipForWeapon(WP_GRENADE_LAUNCHER)] = 100;
        ps.ammoclip[clip] = limit - 1;
        assert(BG_AddMagicAmmo(&ps, skills, TEAM_AXIS, amount));
        assert(ps.ammoclip[clip] == (amount ? limit : limit - 1));
        ps.ammoclip[clip] = limit;
        assert(!BG_AddMagicAmmo(&ps, skills, TEAM_AXIS, amount));
        assert(ps.ammoclip[clip] == limit);
        ps.eFlags = EF_HEADSHOT | EF_CROUCHING;
        assert(BG_AddMagicAmmo(&ps, skills, TEAM_AXIS, amount));
        assert(ps.eFlags == EF_CROUCHING);
        assert(ps.ammoclip[clip] == limit);
        assert(!BG_AddMagicAmmo(&ps, skills, TEAM_AXIS, amount));
        ++tests;
    }
    printf("Magic syringe: %d limit/probe cases passed\n", tests);
    {
        const int scoped[] = { WP_GARAND_SCOPE, WP_K43_SCOPE, WP_FG42SCOPE };
        const int grenades[] = { WP_GRENADE_LAUNCHER, WP_GRENADE_PINEAPPLE };
        int a, b, w, checked = 0;
        for(a = 0; a < 6; ++a)
        for(b = 0; b < 6; ++b) {
            memset(skills, 0, sizeof(skills));
            skills[SK_LIGHT_WEAPONS] = a;
            skills[SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS] = b;
            for(w = 0; w < 3; ++w) {
                ammotable_t *table = GetAmmoTableData(scoped[w]);
                assert(BG_MaxAmmoForWeapon(scoped[w], skills) == table->maxammo + ((a || b) ? table->maxclip : 0));
                ++checked;
            }
            skills[SK_EXPLOSIVES_AND_CONSTRUCTION] = a;
            skills[SK_FIRST_AID] = b;
            for(w = 0; w < 2; ++w) {
                assert(BG_MaxAmmoForWeapon(grenades[w], skills) == GetAmmoTableData(grenades[w])->maxammo + ((!a && b) ? 1 : 0));
                ++checked;
            }
            assert(BG_MaxAmmoForWeapon(WP_MEDIC_ADRENALINE, skills) == GetAmmoTableData(WP_MEDIC_ADRENALINE)->maxammo + (b >= 2 ? 2 : 0));
            ++checked;
        }
        printf("Max ammo: %d reward-adapter cases passed\n", checked);
    }
    {
        const int weapons[] = { WP_FLAMETHROWER, WP_MOBILE_MG42, WP_MOBILE_MG42_SET, WP_MORTAR, WP_MORTAR_SET, WP_PANZERFAUST };
        int w, level, variant, checked = 0;
        for(w = 0; w < 6; ++w)
        for(variant = 0; variant < 3; ++variant) {
            ammotable_t *table = GetAmmoTableData(weapons[w]);
            int savedAmmo = table->maxammo, savedClip = table->maxclip;
            table->maxammo = 20 + variant * 10;
            table->maxclip = 5 + variant;
            for(level = 0; level < 6; ++level) {
                int bonus = w == 0 ? 50 : w < 3 ? table->maxclip : w < 5 ? 2 : 0;
                memset(skills, 0, sizeof(skills));
                skills[SK_HEAVY_WEAPONS] = level;
                assert(BG_MaxAmmoForWeapon(weapons[w], skills) == table->maxammo + (level == 5 ? bonus : 0));
                ++checked;
            }
            {
                unsigned int mask;
                for(mask = 0; mask < 64; ++mask) {
                    int bonus = w == 0 ? 50 : w < 3 ? table->maxclip : 2;
                    int expected = w == 5 ? -1 : table->maxammo + ((mask & 32) ? bonus : 0);
                    assert(NITMOD_HeavyAmmoCapacity(weapons[w], mask, table->maxammo, table->maxclip) == expected);
                }
            }
            table->maxammo = savedAmmo; table->maxclip = savedClip;
        }
        printf("Heavy ammo: %d custom-table/level cases passed\n", checked);
    }
    {
        unsigned int rewards[SK_NUM_SKILLS] = {0};
        int mask, level, probe, checked = 0;
        for(mask = 0; mask < 64; ++mask)
        for(level = 0; level < 6; ++level)
        for(probe = 0; probe < 2; ++probe) {
            int limit;
            ResetOtherAmmo(&ps);
            memset(skills, 0, sizeof(skills));
            skills[SK_HEAVY_WEAPONS] = skills[SK_FIRST_AID] = level;
            rewards[SK_HEAVY_WEAPONS] = rewards[SK_FIRST_AID] = mask;
            ps.ammoclip[BG_FindClipForWeapon(WP_GRENADE_LAUNCHER)] = 100;
            COM_BitSet(ps.weapons, WP_FLAMETHROWER);
            limit = GetAmmoTableData(WP_FLAMETHROWER)->maxammo + ((mask & 32) ? 50 : 0);
            ps.ammoclip[BG_FindAmmoForWeapon(WP_FLAMETHROWER)] = limit - 1;
            assert(BG_AddMagicAmmoRewards(&ps, skills, TEAM_AXIS, probe ? 0 : 1, rewards));
            assert(ps.ammoclip[BG_FindAmmoForWeapon(WP_FLAMETHROWER)] == (probe ? limit - 1 : limit));
            COM_BitClear(ps.weapons, WP_FLAMETHROWER);
            COM_BitSet(ps.weapons, WP_MEDIC_SYRINGE);
            limit = GetAmmoTableData(WP_MEDIC_SYRINGE)->maxammo + ((mask & 4) ? 2 : 0);
            ps.ammoclip[clip] = limit - 1;
            assert(BG_AddMagicAmmoRewards(&ps, skills, TEAM_AXIS, probe ? 0 : 1, rewards));
            assert(ps.ammoclip[clip] == (probe ? limit - 1 : limit));
            checked += 2;
        }
        printf("Explicit reward pickup: %d independent level/mask cases passed\n", checked);
    }
    {
        unsigned int r[SK_NUM_SKILLS] = {0};
        int a, b, checked = 0;
        for(a = 0; a < 64; ++a)
        for(b = 0; b < 64; ++b) {
            r[SK_LIGHT_WEAPONS] = a;
            r[SK_FIRST_AID] = b;
            r[SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS] = b;
            r[SK_EXPLOSIVES_AND_CONSTRUCTION] = a;
            assert(NITMOD_AmmoRewardCapacity(WP_LUGER, r, 40, 8) == 40 + ((a & 2) ? 8 : 0));
            assert(NITMOD_AmmoRewardCapacity(WP_MP40, r, 40, 8) == 40 + (((a | b) & 2) ? 8 : 0));
            assert(NITMOD_AmmoRewardCapacity(WP_K43_SCOPE, r, 40, 8) == 40 + (((a | b) & 2) ? 8 : 0));
            assert(NITMOD_AmmoRewardCapacity(WP_MEDIC_ADRENALINE, r, 40, 8) == 40 + ((b & 4) ? 2 : 0));
            assert(NITMOD_AmmoRewardCapacity(WP_M7, r, 40, 8) == 40 + ((a & 2) ? 4 : 0));
            assert(NITMOD_AmmoRewardCapacity(WP_GRENADE_PINEAPPLE, r, 40, 8) == 40 + (!(a & 2) && (b & 2) ? 1 : 0));
            assert(NITMOD_AmmoRewardCapacity(WP_PANZERFAUST, r, 40, 8) == 40);
            checked += 7;
        }
        printf("Ammo rewards: %d independent mask combinations passed\n", checked);
    }
    {
        entityState_t item = {0};
        unsigned int rewards[SK_NUM_SKILLS] = {0};
        int level, mask, checked = 0;
        item.modelindex = BG_FindItem("Huge Ammo Pack") - bg_itemlist;
        for(level = 0; level < 6; ++level)
        for(mask = 0; mask < 64; ++mask) {
            int limit = GetAmmoTableData(WP_FLAMETHROWER)->maxammo + ((mask & 32) ? 50 : 0);
            ResetOtherAmmo(&ps);
            memset(skills, 0, sizeof(skills));
            skills[SK_HEAVY_WEAPONS] = level;
            rewards[SK_HEAVY_WEAPONS] = mask;
            COM_BitSet(ps.weapons, WP_FLAMETHROWER);
            ps.ammoclip[BG_FindClipForWeapon(WP_GRENADE_LAUNCHER)] = 100;
            ps.ammoclip[BG_FindAmmoForWeapon(WP_FLAMETHROWER)] = limit - 1;
            assert(BG_CanItemBeGrabbedRewards(&item, &ps, skills, TEAM_AXIS, rewards));
            assert(ps.ammoclip[BG_FindAmmoForWeapon(WP_FLAMETHROWER)] == limit - 1);
            assert(BG_AddMagicAmmoRewards(&ps, skills, TEAM_AXIS, 1, rewards));
            assert(!BG_CanItemBeGrabbedRewards(&item, &ps, skills, TEAM_AXIS, rewards));
            ++checked;
        }
        printf("Pickup eligibility: %d mask/level sequences passed\n", checked);
    }
    {
        int base, count, owned, current, checked = 0;
        int poisonClip = BG_FindClipForWeapon(WP_POISON_SYRINGE);
        int saved = GetAmmoTableData(WP_POISON_SYRINGE)->maxammo;
        for(base = 1; base <= 12; ++base)
        for(count = 0; count <= 3; ++count)
        for(owned = 0; owned < 2; ++owned)
        for(current = 0; current <= base + 1; ++current) {
            int expected = current;
            ResetOtherAmmo(&ps);
            ps.ammoclip[BG_FindClipForWeapon(WP_GRENADE_LAUNCHER)] = 100;
            if(owned) COM_BitSet(ps.weapons, WP_POISON_SYRINGE);
            GetAmmoTableData(WP_POISON_SYRINGE)->maxammo = base;
            ps.ammoclip[poisonClip] = current;
            ps.ammo[BG_FindAmmoForWeapon(WP_POISON_SYRINGE)] = 3;
            assert(!!BG_AddMagicAmmo(&ps, skills, TEAM_AXIS, count) == (owned && current < base));
            if(owned && current < base && count) expected = current + count > base ? base : current + count;
            assert(ps.ammoclip[poisonClip] == expected);
            assert(ps.ammo[BG_FindAmmoForWeapon(WP_POISON_SYRINGE)] == 3);
            ++checked;
        }
        GetAmmoTableData(WP_POISON_SYRINGE)->maxammo = saved;
        printf("Poison syringe: %d pickup cases passed\n", checked);
    }
    {
        unsigned int rewards[SK_NUM_SKILLS] = {0};
        entityState_t item = {0};
        int options, mask, owned, count, checked = 0;
        int adclip = BG_FindClipForWeapon(WP_MEDIC_ADRENALINE);
        item.modelindex = BG_FindItem("Ammo Pack") - bg_itemlist;
        for(options = 0; options < 16; ++options)
        for(mask = 0; mask < 64; ++mask)
        for(owned = 0; owned < 2; ++owned)
        for(count = 0; count < 4; ++count) {
            int limit = (options & 4) ? 1 : GetAmmoTableData(WP_MEDIC_ADRENALINE)->maxammo + ((mask & 4) ? 2 : 0);
            int eligible = owned && !(options & 2);
            ResetOtherAmmo(&ps);
            ps.ammoclip[BG_FindClipForWeapon(WP_GRENADE_LAUNCHER)] = 100;
            if(owned) COM_BitSet(ps.weapons, WP_MEDIC_ADRENALINE);
            rewards[SK_FIRST_AID] = mask;
            assert(!!BG_CanItemBeGrabbedOptions(&item, &ps, skills, TEAM_AXIS, rewards, options) == eligible);
            assert(ps.ammoclip[adclip] == 0);
            assert(!!BG_AddMagicAmmoOptions(&ps, skills, TEAM_AXIS, count, rewards, options) == eligible);
            assert(ps.ammoclip[adclip] == (eligible ? (count < limit ? count : limit) : 0));
            ++checked;
        }
        printf("Adrenaline: %d option/mask/ownership/count cases passed\n", checked);
    }
    {
        unsigned int rewards[SK_NUM_SKILLS] = {0};
        int mask, count, current, checked = 0;
        int knifeClip = BG_FindClipForWeapon(WP_KNIFE);
        for(mask = 0; mask < 64; ++mask)
        for(count = 0; count < 4; ++count)
        for(current = 0; current <= 9; ++current) {
            int limit = (mask & 32) ? 8 : 1;
            int expected = current;
            ResetOtherAmmo(&ps);
            memset(skills, 0, sizeof(skills));
            rewards[SK_LIGHT_WEAPONS] = mask;
            ps.ammoclip[BG_FindClipForWeapon(WP_GRENADE_LAUNCHER)] = 100;
            ps.ammoclip[knifeClip] = current;
            ps.ammo[BG_FindAmmoForWeapon(WP_KNIFE)] = 3;
            assert(!!BG_AddMagicAmmoRewards(&ps, skills, TEAM_AXIS, count, rewards) == (current < limit));
            if(current < limit && count) expected = current + count > limit ? limit : current + count;
            assert(ps.ammoclip[knifeClip] == expected);
            assert(ps.ammo[BG_FindAmmoForWeapon(WP_KNIFE)] == 3);
            assert(!!COM_BitCheck(ps.weapons, WP_KNIFE) == (current < limit && count > 0));
            ++checked;
        }
        printf("Knife refill: %d mask/count/clip cases passed\n", checked);
    }
    {
        unsigned int rewards[SK_NUM_SKILLS] = {0};
        int cls, mask, war, team, current, checked = 0;
        entityState_t item = {0};
        item.modelindex = BG_FindItem("Ammo Pack") - bg_itemlist;
        for(cls = 0; cls < 5; ++cls)
        for(mask = 0; mask < 64; ++mask)
        for(war = 0; war < 2; ++war)
        for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
        for(current = 0; current <= 9; ++current) {
            int s, limit, grenade, grenadeClip;
            for(s = 0; s < SK_NUM_SKILLS; ++s) rewards[s] = mask;
            ResetOtherAmmo(&ps);
            ps.stats[STAT_PLAYER_CLASS] = cls;
            grenade = team == TEAM_AXIS ? WP_GRENADE_LAUNCHER : WP_GRENADE_PINEAPPLE;
            grenadeClip = BG_FindClipForWeapon(grenade);
            ps.ammoclip[grenadeClip] = current;
            limit = BG_NitmodGrenadesForClass(cls, rewards, war);
            assert(!!BG_CanItemBeGrabbedWar(&item, &ps, skills, team, rewards, 2u, war) == (current < limit));
            assert(!!BG_AddMagicAmmoWar(&ps, skills, team, 0, rewards, 2u, war) == (current < limit));
            assert(ps.ammoclip[grenadeClip] == current);
            assert(!!BG_AddMagicAmmoWar(&ps, skills, team, 3, rewards, 2u, war) == (current < limit));
            assert(ps.ammoclip[grenadeClip] == (current < limit ? (current + 3 < limit ? current + 3 : limit) : current));
            assert(!!COM_BitCheck(ps.weapons, grenade) == (current < limit));
            ++checked;
        }
        printf("Grenade refill: %d class/mask/war/team/clip cases passed\n", checked);
    }
    return 0;
}
