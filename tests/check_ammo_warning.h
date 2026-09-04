#include "cg_nitmod_ammo.h"
static int ammoWarningSounds;
static int QDECL AmmoWarningSyscall(int command, ...) {
    va_list args;
    va_start(args,command);
    if(command!=CG_S_STARTLOCALSOUND || va_arg(args,int)!=731 || va_arg(args,int)!=CHAN_LOCAL_SOUND) exit(2);
    va_end(args); ++ammoWarningSounds; return 0;
}
static int CheckAmmoWarning(void) {
    static snapshot_t snapshot;
    snapshot_t *oldSnapshot=cg.snap;
    int oldWarning=cg.lowAmmoWarning,oldSound=cgs.media.noAmmoSound;
    int weapon,reserve,previous,errors=0;
    dllEntry(AmmoWarningSyscall); cg.snap=&snapshot; cgs.media.noAmmoSound=731;
    for(weapon=1;weapon<WP_NUM_WEAPONS;++weapon) for(reserve=-1;reserve<=6;++reserve)
    for(previous=0;previous<3;++previous) {
        memset(&snapshot,0,sizeof(snapshot));
        snapshot.ps.weapons[weapon/32]=(int)(1u<<(weapon%32));
        snapshot.ps.ammo[BG_FindAmmoForWeapon(weapon)]=reserve;
        cg.lowAmmoWarning=previous; ammoWarningSounds=0;
        CG_CheckAmmo();
        if(cg.lowAmmoWarning!=(reserve>=5 ? 0 : reserve>0 ? 1 : 2) ||
           ammoWarningSounds!=(reserve<5 && previous==0)) ++errors;
        /* The second observation cannot replay a warning while still low. */
        CG_CheckAmmo();
        if(ammoWarningSounds!=(reserve<5 && previous==0)) ++errors;
    }
    memset(&snapshot,0,sizeof(snapshot)); cg.lowAmmoWarning=1; ammoWarningSounds=0;
    CG_CheckAmmo();
    if(cg.lowAmmoWarning!=1 || ammoWarningSounds) ++errors;
    snapshot.ps.weapons[WP_MP40/32]=(int)(1u<<(WP_MP40%32));
    snapshot.ps.ammo[WP_MP40]=2147483647; CG_CheckAmmo();
    if(cg.lowAmmoWarning || ammoWarningSounds) ++errors;
    snapshot.ps.ammo[WP_MP40]=0; cgs.media.noAmmoSound=-1; CG_CheckAmmo();
    if(cg.lowAmmoWarning!=2 || ammoWarningSounds) ++errors;
    cg.snap=NULL; CG_CheckAmmo();
    if(cg.lowAmmoWarning!=2) ++errors;
    cg.snap=oldSnapshot; cg.lowAmmoWarning=oldWarning; cgs.media.noAmmoSound=oldSound;
    return errors;
}
