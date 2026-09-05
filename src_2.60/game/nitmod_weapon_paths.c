#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_weapon_paths.h"

/* BG_RegisterWeapon, original qagame ELF 0x363c0. Original numeric weapon
 * IDs are NOT the ET 2.60 enum. Keep only named, representable identities. */
typedef struct {
    weapon_t weapon;
    nitmodWeaponPath_t path;
} weaponPathEntry_t;
static const weaponPathEntry_t weaponPaths[] = {
    { WP_KNIFE, { "knife.weap", 0 } },
    { WP_LUGER, { "luger.weap", 0 } },
    { WP_MP40, { "mp40.weap", 0 } },
    { WP_GRENADE_LAUNCHER, { "grenade.weap", 0 } },
    { WP_PANZERFAUST, { "panzerfaust.weap", 0 } },
    { WP_FLAMETHROWER, { "flamethrower.weap", 0 } },
    { WP_COLT, { "colt.weap", 0 } },
    { WP_THOMPSON, { "thompson.weap", 0 } },
    { WP_GRENADE_PINEAPPLE, { "pineapple.weap", 0 } },
    { WP_STEN, { "sten.weap", 0 } },
    { WP_MEDIC_SYRINGE, { "syringe.weap", 0 } },
    { WP_AMMO, { "ammopack.weap", 0 } },
    { WP_SILENCER, { "silenced_luger.weap", 0 } },
    { WP_DYNAMITE, { "dynamite.weap", 0 } },
    { WP_SMOKETRAIL, { "smoketrail.weap", 0 } },
    { WP_MEDKIT, { "medpack.weap", 0 } },
    { WP_BINOCULARS, { "binocs.weap", 0 } },
    { WP_PLIERS, { "pliers.weap", 0 } },
    { WP_SMOKE_MARKER, { "smokemarker.weap", 0 } },
    { WP_KAR98, { "kar98.weap", 0 } },
    { WP_CARBINE, { "m1_garand.weap", 0 } },
    { WP_GARAND, { "m1_garand_s.weap", 0 } },
    { WP_LANDMINE, { "landmine.weap", 0 } },
    { WP_SATCHEL, { "satchel.weap", 0 } },
    { WP_SATCHEL_DET, { "satchel_det.weap", 0 } },
    { WP_SMOKE_BOMB, { "smokegrenade.weap", 0 } },
    { WP_MOBILE_MG42, { "mg42.weap", 0 } },
    { WP_K43, { "k43.weap", 0 } },
    { WP_FG42, { "fg42.weap", 0 } },
    { WP_MORTAR, { "mortar.weap", 0 } },
    { WP_AKIMBO_COLT, { "akimbo_colt.weap", 0 } },
    { WP_AKIMBO_LUGER, { "akimbo_luger.weap", 0 } },
    { WP_GPG40, { "gpg40.weap", 0 } },
    { WP_M7, { "m7.weap", 0 } },
    { WP_SILENCED_COLT, { "silenced_colt.weap", 0 } },
    { WP_GARAND_SCOPE, { "m1_garand_s.weap", 1 } },
    { WP_K43_SCOPE, { "k43.weap", 1 } },
    { WP_FG42SCOPE, { "fg42.weap", 1 } },
    { WP_MORTAR_SET, { "mortar_set.weap", 0 } },
    { WP_MEDIC_ADRENALINE, { "adrenaline.weap", 0 } },
    { WP_AKIMBO_SILENCEDCOLT, { "akimbo_silenced_colt.weap", 0 } },
    { WP_AKIMBO_SILENCEDLUGER, { "akimbo_silenced_luger.weap", 0 } },
    { WP_MOBILE_MG42_SET, { "mg42.weap", 1 } },
    { WP_TRIPMINE, { "tripmine.weap", 0 } },
    { WP_BOMB, { "bomb.weap", 0 } },
    { WP_POISON_SYRINGE, { "poison.weap", 0 } },
    { WP_POISON_BOMB, { "poisongas.weap", 0 } },
    { WP_POISON_MINE, { "landmine_pgas.weap", 0 } },
};

const nitmodWeaponPath_t *NITMOD_WeaponPath( int weapon ) {
    unsigned int i;
    if( weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ) return NULL;
    for( i = 0; i < sizeof(weaponPaths) / sizeof(weaponPaths[0]); ++i )
        if( weapon == weaponPaths[i].weapon ) return &weaponPaths[i].path;
    return NULL;
}
