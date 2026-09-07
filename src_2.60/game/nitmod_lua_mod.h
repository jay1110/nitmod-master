#ifndef NITMOD_LUA_MOD_H
#define NITMOD_LUA_MOD_H
/* Original qagame modNames at ELF VA 0x2a7bc0. Native ET enum values are
 * deliberately retained internally and translated at the Lua boundary. */
static int NITMOD_LuaMeansOfDeath(int cause) {
    switch(cause) {
    case MOD_UNKNOWN: return 0;
    case MOD_MACHINEGUN: return 1;
    case MOD_BROWNING: return 2;
    case MOD_MG42: return 3;
    case MOD_GRENADE: return 4;
    case MOD_KNIFE: return 5;
    case MOD_LUGER: return 6;
    case MOD_COLT: return 7;
    case MOD_MP40: return 8;
    case MOD_THOMPSON: return 9;
    case MOD_STEN: return 10;
    case MOD_GARAND: return 11;
    case MOD_SILENCER: return 12;
    case MOD_FG42: return 13;
    case MOD_FG42SCOPE: return 14;
    case MOD_PANZERFAUST: return 15;
    case MOD_GRENADE_LAUNCHER: return 16;
    case MOD_FLAMETHROWER: return 17;
    case MOD_GRENADE_PINEAPPLE: return 18;
    case MOD_MAPMORTAR: return 19;
    case MOD_MAPMORTAR_SPLASH: return 20;
    case MOD_DYNAMITE: return 21;
    case MOD_AIRSTRIKE: return 22;
    case MOD_SYRINGE: return 23;
    case MOD_AMMO: return 24;
    case MOD_ARTY: return 25;
    case MOD_WATER: return 26;
    case MOD_SLIME: return 27;
    case MOD_LAVA: return 28;
    case MOD_CRUSH: return 29;
    case MOD_TELEFRAG: return 30;
    case MOD_FALLING: return 31;
    case MOD_SUICIDE: return 32;
    case MOD_TARGET_LASER: return 33;
    case MOD_TRIGGER_HURT: return 34;
    case MOD_EXPLOSIVE: return 35;
    case MOD_CARBINE: return 36;
    case MOD_KAR98: return 37;
    case MOD_GPG40: return 38;
    case MOD_M7: return 39;
    case MOD_LANDMINE: return 40;
    case MOD_SATCHEL: return 41;
    case MOD_SMOKEBOMB: return 42;
    case MOD_MOBILE_MG42: return 43;
    case MOD_SILENCED_COLT: return 44;
    case MOD_GARAND_SCOPE: return 45;
    case MOD_CRUSH_CONSTRUCTION: return 46;
    case MOD_CRUSH_CONSTRUCTIONDEATH: return 47;
    case MOD_CRUSH_CONSTRUCTIONDEATH_NOATTACKER: return 48;
    case MOD_K43: return 49;
    case MOD_K43_SCOPE: return 50;
    case MOD_MORTAR: return 51;
    case MOD_AKIMBO_COLT: return 52;
    case MOD_AKIMBO_LUGER: return 53;
    case MOD_AKIMBO_SILENCEDCOLT: return 54;
    case MOD_AKIMBO_SILENCEDLUGER: return 55;
    case MOD_SMOKEGRENADE: return 56;
    case MOD_SWITCHTEAM: return 57;
    case MOD_GOOMBA: return 58;
    case MOD_POISON: return 59;
    case MOD_FEAR: return 60;
    case MOD_CENSORED: return 61;
    case MOD_SHOVE: return 62;
    case MOD_THROWKNIFE: return 63;
    case MOD_GIBME: return 64;
    case MOD_BOMB: return 65;
    case MOD_TRIPMINE: return 66;
    case MOD_POISON_GAS: return 67;
    case MOD_POISON_GAS_MINE: return 68;
    default: return 0; /* ET-only and invalid causes have no Nitmod meaning. */
    }
}
static int NITMOD_NativeMeansOfDeath(int cause) {
    int native;
    if(cause==0) return MOD_UNKNOWN;
    for(native=0;native<MOD_NUM_MODS;++native)
        if(NITMOD_LuaMeansOfDeath(native)==cause) return native;
    return -1;
}
#endif
