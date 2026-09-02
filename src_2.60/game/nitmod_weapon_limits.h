#ifndef NITMOD_WEAPON_LIMITS_H
#define NITMOD_WEAPON_LIMITS_H
typedef enum {
    NITMOD_LIMIT_INVALID = -1,
    NITMOD_LIMIT_NONE = 0, /* no numeric limit hit; other policies still apply */
    NITMOD_LIMIT_HEAVY,
    NITMOD_LIMIT_PANZER_TEAM,
    NITMOD_LIMIT_FIXED
} nitmodWeaponLimit_t;
typedef struct {
    int teamSize;
    int weaponCount;
    int heavyPercent;
    int maxClients;
    int panzerPercent;
    int fixedCap; /* -1 alone means unlimited */
    int isHeavy;
    int isPanzer;
} nitmodWeaponLimitInput_t;
nitmodWeaponLimit_t NITMOD_EvaluateWeaponLimits( const nitmodWeaponLimitInput_t *input );
#endif
