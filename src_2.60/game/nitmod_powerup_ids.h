#ifndef NITMOD_POWERUP_IDS_H
#define NITMOD_POWERUP_IDS_H
/* Original CG_DrawFlashFade (ELF 0x3da5d/0x3db8f) reads snapshot
 * 0x1b4: ps + 0x188, powerups[14]. Slot 2 is the flak indicator
 * (CG_DrawActivePowerups), never a spectator lock. Use the unused native
 * FIRE slot for flak; retain reserved wire slots 12/13 without colliding
 * with BLACKOUT/MVCLIENTLIST. All sixteen slots must survive translation. */
#define NITMOD_PW_FLAK PW_FIRE
#define NITMOD_POWERUP_COUNT 16
static const int nitmodPowerupIds[NITMOD_POWERUP_COUNT]={PW_NONE,PW_INVULNERABLE,NITMOD_PW_FLAK,
    PW_BREATHER,PW_NOFATIGUE,PW_REDFLAG,PW_BLUEFLAG,PW_OPS_DISGUISED,
    PW_OPS_CLASS_1,PW_OPS_CLASS_2,PW_OPS_CLASS_3,PW_ADRENALINE,
    13,PW_ELECTRIC,PW_BLACKOUT,PW_MVCLIENTLIST};
static unsigned int NITMOD_NativePowerupBits(unsigned int original) {
    unsigned int native=0;int i;
    for(i=0;i<NITMOD_POWERUP_COUNT;++i) if(original&(1u<<i)) native|=1u<<nitmodPowerupIds[i];
    return native;
}
static unsigned int NITMOD_OriginalPowerupBits(unsigned int native) {
    unsigned int original=0;int i;
    for(i=0;i<NITMOD_POWERUP_COUNT;++i) if(native&(1u<<nitmodPowerupIds[i])) original|=1u<<i;
    return original;
}
#endif
