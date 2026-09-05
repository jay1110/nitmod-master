#include "g_local.h"
#include "g_nitmod_weapon_definition.h"
#include "nitmod_weapon_definition.h"
#include "nitmod_weapon_recoil.h"
static const char *tokens[] = { "weaponDef", "{", "client", "{", "}", "}", "both", "{", "classes", "7", "}", "}", "}" };
static int opens, frees, reads, failOpens, count = 12, quoted = 4, badHandle;
static char opened[2][MAX_QPATH];
int trap_PC_LoadSource( const char *filename ) {
    if( opens < 2 ) {
        strncpy(opened[opens], filename, MAX_QPATH - 1);
        opened[opens][MAX_QPATH - 1] = 0;
    }
    opens++;
    if( opens <= failOpens ) return 0;
    return 23;
}
int trap_PC_FreeSource( int handle ) { frees++; if( handle != 23 ) badHandle = 1; return 1; }
int trap_PC_ReadToken( int handle, pc_token_t *token ) {
    if( handle != 23 ) badHandle = 1;
    if( reads >= count ) return 0;
    token->type = reads == 4 || reads == quoted ? TT_STRING : TT_NAME;
    strcpy(token->string, tokens[reads++]);
    return 1;
}
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
static void Reset( void ) { opens = frees = reads = 0; memset(opened, 0, sizeof(opened)); }
int main( void ) {
    unsigned int mask = 99;
    ammotable_t ammo, baseline = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    char directory[MAX_QPATH + 1];
    size_t limit;
    CHECK( G_NITMOD_LoadWeaponClassMask("custom/x.weap", "weapons/x.weap", 0, &mask) );
    CHECK( mask == 7 && opens == 1 && frees == 1 && !badHandle );
    Reset(); failOpens = 1;
    CHECK( G_NITMOD_LoadWeaponClassMask("custom/x.weap", "weapons/x.weap", 1, &mask) );
    CHECK( !mask && opens == 2 && frees == 1 );
    Reset(); failOpens = 2; mask = 99;
    CHECK( !G_NITMOD_LoadWeaponClassMask("custom/x.weap", "weapons/x.weap", 0, &mask) );
    CHECK( mask == 99 && opens == 2 && !frees );
    Reset(); failOpens = 0; count = 11;
    CHECK( !G_NITMOD_LoadWeaponClassMask("custom/x.weap", "weapons/x.weap", 0, &mask) );
    CHECK( mask == 99 && opens == 1 && frees == 1 ); /* no fallback on parse failure */
    Reset(); count = 12; quoted = 9;
    CHECK( !G_NITMOD_LoadWeaponClassMask("custom/x.weap", NULL, 0, &mask) );
    CHECK( mask == 99 && frees == 1 );
    Reset();
    CHECK( !G_NITMOD_LoadWeaponClassMask(NULL, "weapons/x.weap", 0, &mask) );
    CHECK( !G_NITMOD_LoadWeaponClassMask("x.weap", NULL, 0, NULL) );
    CHECK( !opens && !frees && !badHandle );
    /* Runtime cache: distinct alternate identities, failed-load caching and
     * map-reset retry. A failed lookup never overwrites caller metadata. */
    Reset(); count = 12; quoted = 4; failOpens = 0;
    tokens[6] = "both"; tokens[8] = "classes"; tokens[9] = "7";
    G_NITMOD_ResetPickupDefinitions();
    CHECK(G_NITMOD_PickupClassMask(WP_K43, &mask) && mask == 7);
    CHECK(opens == 1 && frees == 1);
    CHECK(G_NITMOD_PickupClassMask(WP_K43, &mask) && opens == 1);
    Reset();
    CHECK(G_NITMOD_PickupClassMask(WP_K43_SCOPE, &mask) && mask == 0);
    CHECK(opens == 1 && frees == 1);
    Reset(); count = 11; mask = 99;
    CHECK(!G_NITMOD_PickupClassMask(WP_MP40, &mask) && mask == 99);
    CHECK(opens == 1 && frees == 1);
    count = 12;
    CHECK(!G_NITMOD_PickupClassMask(WP_MP40, &mask) && opens == 1);
    G_NITMOD_ResetPickupDefinitions(); Reset();
    CHECK(G_NITMOD_PickupClassMask(WP_MP40, &mask) && mask == 7);
    CHECK(!G_NITMOD_PickupClassMask(-1, &mask));
    CHECK(!G_NITMOD_PickupClassMask(WP_NUM_WEAPONS, &mask));
    CHECK(!G_NITMOD_PickupClassMask(WP_K43, NULL));
    G_NITMOD_ResetPickupDefinitions(); Reset(); mask = 99;
    Reset(); failOpens = 0; count = 13; quoted = 4;
    tokens[6] = "both_altweap"; tokens[8] = "maxclip";
    tokens[9] = "-"; tokens[10] = "2147483648";
    ammo = baseline; mask = 99;
    CHECK( G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( ammo.maxclip == (-2147483647 - 1) && !mask && frees == 1 );
    Reset(); tokens[10] = "-0"; ammo = baseline; mask = 99;
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 99 && frees == 1 );
    /* Restore fixtures for the remaining loader cases. */
    count = 12; tokens[6] = "both"; tokens[8] = "classes"; tokens[9] = "7"; tokens[10] = "}";
    Reset(); quoted = 4; mask = 99;
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_K43, "custom", &mask) );
    CHECK( mask == 7 && opens == 1 && frees == 1 );
    CHECK( !strcmp(opened[0], "custom/k43.weap") );
    Reset(); failOpens = 1;
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_K43_SCOPE, "custom", &mask) );
    CHECK( mask == 0 && opens == 2 && frees == 1 );
    CHECK( !strcmp(opened[0], "custom/k43.weap") && !strcmp(opened[1], "weapons/k43.weap") );
    Reset(); failOpens = 0; tokens[6] = "both_altweap";
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_MOBILE_MG42_SET, "custom", &mask) );
    CHECK( mask == 7 && !strcmp(opened[0], "custom/mg42.weap") );
    Reset();
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_MORTAR_SET, "custom", &mask) );
    CHECK( mask == 0 && !strcmp(opened[0], "custom/mortar_set.weap") );
    Reset(); failOpens = 1; mask = 99;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, "weapons", &mask) );
    CHECK( mask == 99 && opens == 1 && !frees ); /* same path is not reopened */
    Reset(); failOpens = 0;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_ARTY, "custom", &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(-1, "custom", &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, NULL, &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, "", &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, "custom", NULL) );
    memset(directory, 'x', sizeof(directory)); directory[MAX_QPATH] = 0;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, directory, &mask) );
    CHECK( mask == 99 && !opens && !frees );
    limit = MAX_QPATH - strlen("k43.weap") - 2;
    directory[limit + 1] = 0;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, directory, &mask) );
    CHECK( mask == 99 && !opens );
    directory[limit] = 0;
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_K43, directory, &mask) );
    CHECK( strlen(opened[0]) == MAX_QPATH - 1 && frees == 1 );
    Reset(); count = 11; mask = 99;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43_SCOPE, "custom", &mask) );
    CHECK( mask == 99 && opens == 1 && frees == 1 && !badHandle );
    Reset(); count = 12; tokens[8] = "maxclip"; tokens[9] = "37";
    ammo = baseline; failOpens = 1;
    CHECK( G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( ammo.maxclip == 37 && ammo.uses == 2 && ammo.mod == 11 && !mask );
    CHECK( opens == 2 && frees == 1 && !strcmp(opened[1], "weapons/k43.weap") );
    Reset(); failOpens = 0; ammo = baseline; mask = 99;
    CHECK( G_NITMOD_LoadNativeWeaponAmmo(WP_K43, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && !mask ); /* unselected block */
    Reset(); count = 11; mask = 99;
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 99 );
    CHECK( opens == 1 && frees == 1 ); /* rollback after a parsed ammo assignment */
    Reset(); count = 12; quoted = 9;
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 99 && frees == 1 );
    Reset(); quoted = 4; failOpens = 2;
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 99 && opens == 2 && !frees );
    Reset();
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", NULL, &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, NULL) );
    CHECK( !opens && !frees && !badHandle );
    {
        nitmodWeaponOptions_t metadata;
        nitmodWeaponRecoil_t recoil;
        Reset(); count = 12; failOpens = 0; quoted = 9;
        tokens[6] = "both"; tokens[8] = "name"; tokens[9] = "Poison Bomb";
        ammo = baseline;
        CHECK(G_NITMOD_LoadNativeWeaponOptions(WP_POISON_BOMB, "weapons", &ammo, &mask, &recoil, &metadata));
        CHECK(!strcmp(metadata.name, "Poison Bomb") && mask == 0 && opens == 1 && frees == 1);
        Reset(); quoted = 9; tokens[8] = "HeadshotWeapon"; tokens[9] = "yes";
        CHECK(G_NITMOD_LoadNativeWeaponOptions(WP_MP40, "weapons", &ammo, &mask, &recoil, &metadata));
        CHECK(metadata.headshotWeapon == 1 && !metadata.name[0]);
        Reset(); quoted = 9; tokens[8] = "damage"; tokens[9] = "18";
        CHECK(!G_NITMOD_LoadNativeWeaponOptions(WP_MP40, "weapons", &ammo, &mask, &recoil, &metadata));
        CHECK(metadata.headshotWeapon == 1 && frees == 1);
    }
    {
        const char *values[]={"0","123","-7","2147483647"};
        int i;
        for(i=0;i<4;++i) {
            float spread=400;
            G_NITMOD_ResetPickupDefinitions(); Reset(); count=12; quoted=4; failOpens=0;
            tokens[6]="both"; tokens[8]="spread"; tokens[9]=values[i]; tokens[10]="}";
            CHECK(G_NITMOD_PickupClassMask(WP_MP40,&mask));
            CHECK(G_NITMOD_WeaponSpreadOverride(WP_MP40,&spread)==(i!=0));
            CHECK(spread==(i==0 ? 400.f : i==1 ? 123.f : i==2 ? -7.f : (float)2147483647));
            CHECK(opens==1 && frees==1);
            CHECK(!G_NITMOD_WeaponSpreadOverride(WP_MP40,NULL));
            CHECK(!G_NITMOD_WeaponSpreadOverride(-1,&spread));
            CHECK(!G_NITMOD_WeaponSpreadOverride(WP_NUM_WEAPONS,&spread));
            G_NITMOD_ResetPickupDefinitions(); spread=400;
            CHECK(!G_NITMOD_WeaponSpreadOverride(WP_MP40,&spread) && spread==400);
        }
    }
    {
        const char *values[]={"yes","no","invalid"};
        int i, fallback;
        for(i=0;i<3;++i) {
            G_NITMOD_ResetPickupDefinitions(); Reset(); count=12; quoted=4; failOpens=0;
            tokens[6]="both"; tokens[8]="DistanceFalloff"; tokens[9]=values[i]; tokens[10]="}";
            CHECK(G_NITMOD_PickupClassMask(WP_MP40,&mask));
            for(fallback=0;fallback<2;++fallback) {
                CHECK(G_NITMOD_WeaponFalloffMode(WP_MP40,fallback)==(i<2 ? i+1 : fallback));
                CHECK(G_NITMOD_WeaponFalloffMode(-1,fallback)==fallback);
                CHECK(G_NITMOD_WeaponFalloffMode(WP_NUM_WEAPONS,fallback)==fallback);
            }
            Reset(); CHECK(G_NITMOD_PickupClassMask(WP_MOBILE_MG42,&mask));
            CHECK(G_NITMOD_WeaponFalloffMode(WP_MOBILE_MG42,0)==0);
            G_NITMOD_ResetPickupDefinitions();
            CHECK(G_NITMOD_WeaponFalloffMode(WP_MP40,1)==1);
        }
    }
    {
        const char *keys[]={"HeadshotWeapon","HeadshotRatio","minHeadshotDamage"};
        const char *values[][3]={{"yes","no","invalid"},{"0","1.5","3"},{"0","70","-5"}};
        int field,value;
        for(field=0;field<3;++field) for(value=0;value<3;++value) {
            G_NITMOD_ResetPickupDefinitions(); Reset(); count=12; quoted=4; failOpens=0;
            tokens[6]="both"; tokens[8]=keys[field]; tokens[9]=values[field][value]; tokens[10]="}";
            CHECK(G_NITMOD_PickupClassMask(WP_MP40,&mask));
            CHECK(G_NITMOD_WeaponHeadshotAllowed(WP_MP40,-1)==(field==0 && value<2 ? !value : -1));
            CHECK(G_NITMOD_HeadshotDamage(WP_MP40,40)==(field==1 && value ? (value==1 ? 60 : 120) : 80));
            CHECK(G_NITMOD_HeadshotDamage(WP_MP40,10)==(field==2 && value ? (value==1 ? 70 : 20) : 50));
            CHECK(opens==1 && frees==1);
        }
        G_NITMOD_ResetPickupDefinitions();
        CHECK(G_NITMOD_WeaponHeadshotAllowed(WP_MP40,-1)==-1);
        CHECK(G_NITMOD_HeadshotDamage(WP_MP40,40)==80);
        CHECK(G_NITMOD_HeadshotDamage(-1,10)==50);
        CHECK(G_NITMOD_HeadshotDamage(WP_NUM_WEAPONS,2147483647)==2147483647);
        CHECK(G_NITMOD_HeadshotDamage(WP_NONE,-2147483647)==50);
    }
    {
        const char *values[]={"yes","no","invalid"};
        int i,fallback;
        for(i=0;i<3;++i) {
            G_NITMOD_ResetPickupDefinitions(); Reset(); count=12; quoted=4; failOpens=0;
            tokens[6]="both"; tokens[8]="GibbingWeapon"; tokens[9]=values[i]; tokens[10]="}";
            CHECK(G_NITMOD_PickupClassMask(WP_MP40,&mask));
            for(fallback=0;fallback<2;++fallback) {
                CHECK(G_NITMOD_WeaponGibAllowed(WP_MP40,fallback)==(i<2 ? !i : fallback));
                CHECK(G_NITMOD_WeaponGibAllowed(-1,fallback)==fallback);
                CHECK(G_NITMOD_WeaponGibAllowed(WP_NUM_WEAPONS,fallback)==fallback);
            }
            CHECK(opens==1 && frees==1);
            G_NITMOD_ResetPickupDefinitions();
            CHECK(G_NITMOD_WeaponGibAllowed(WP_MP40,1)==1);
            CHECK(G_NITMOD_WeaponGibAllowed(WP_MP40,0)==0);
        }
    }
    /* Live map-owned cache: original nonzero override semantics, independent
     * fields, failure isolation, reset, and no I/O from damage callbacks. */
    {
        const char *keys[]={"damage","splashdamage","splashdamage_radius"};
        const char *values[]={"0","27","-3"};
        int field,value;
        for(field=0;field<3;++field) for(value=0;value<3;++value) {
            int d=100,s=200,r=300,expected=value==1 ? 27 : -3;
            G_NITMOD_ResetPickupDefinitions(); Reset();
            count=12; failOpens=0; quoted=4;
            tokens[6]="both"; tokens[8]=keys[field]; tokens[9]=values[value]; tokens[10]="}";
            CHECK(G_NITMOD_PickupClassMask(WP_GRENADE_LAUNCHER,&mask));
            G_NITMOD_WeaponDamageOverrides(WP_GRENADE_LAUNCHER,&d,&s,&r);
            CHECK(d==(field==0 && value ? expected : 100));
            CHECK(s==(field==1 && value ? expected : 200));
            CHECK(r==(field==2 && value ? expected : 300));
            CHECK(opens==1 && frees==1);
            G_NITMOD_WeaponDamageOverrides(-1,&d,&s,&r);
            G_NITMOD_WeaponDamageOverrides(WP_NUM_WEAPONS,NULL,NULL,NULL);
            G_NITMOD_ResetPickupDefinitions();
            d=100;s=200;r=300;
            G_NITMOD_WeaponDamageOverrides(WP_GRENADE_LAUNCHER,&d,&s,&r);
            CHECK(d==100 && s==200 && r==300 && opens==1);
        }
        G_NITMOD_ResetPickupDefinitions(); Reset(); failOpens=10000;
        G_NITMOD_LoadMapWeaponDefinitions();
        { int oldOpens=opens,d=1,s=2,r=3;
          CHECK(oldOpens>0);
          G_NITMOD_LoadMapWeaponDefinitions();
          G_NITMOD_WeaponDamageOverrides(WP_GRENADE_LAUNCHER,&d,&s,&r);
          CHECK(opens==oldOpens && d==1 && s==2 && r==3); }
    }
    return 0;
}
