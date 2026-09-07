#ifndef NITMOD_POWERUP_IDS_H
#define NITMOD_POWERUP_IDS_H
/* Original ps.powerups starts at 0x150; used slots end with MVCLIENTLIST (12).
 * ET's FIRE/ELECTRIC slots are absent and BLACKOUT is original slot 2. */
static const int nitmodPowerupIds[13]={PW_NONE,PW_INVULNERABLE,PW_BLACKOUT,
    PW_BREATHER,PW_NOFATIGUE,PW_REDFLAG,PW_BLUEFLAG,PW_OPS_DISGUISED,
    PW_OPS_CLASS_1,PW_OPS_CLASS_2,PW_OPS_CLASS_3,PW_ADRENALINE,PW_MVCLIENTLIST};
static unsigned int NITMOD_NativePowerupBits(unsigned int original) {
    unsigned int native=0;int i;
    for(i=0;i<13;++i) if(original&(1u<<i)) native|=1u<<nitmodPowerupIds[i];
    return native;
}
static unsigned int NITMOD_OriginalPowerupBits(unsigned int native) {
    unsigned int original=0;int i;
    for(i=0;i<13;++i) if(native&(1u<<nitmodPowerupIds[i])) original|=1u<<i;
    return original;
}
#endif
