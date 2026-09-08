#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_debug.h"
#include "cg_nitmod_nxac.h"

/* Original cgs+0x204195c/60 and +0x2041984/88. These checks observe real
 * render submissions; they do not infer cheating from a cvar or checksum. */
static unsigned int nxacFlags;
static int nxacRenderCalls;
static int nxacNextReport;
static qboolean nxacDetected;
void CG_NITMOD_NxACReset(void) {
    nxacFlags=0; nxacRenderCalls=0; nxacNextReport=0; nxacDetected=qfalse;
}
static void NxACGamehack(void) { nxacFlags|=0x20; nxacDetected=qtrue; }
void CG_NITMOD_NxACAfterRender(const refEntity_t *entity,int before) {
    if(!entity || nxacDetected || !NITMOD_UsesNitmodHud()) return;
    /* trap_R_AddRefEntityToScene ELF0xb61d0: the first 501 submissions
     * advance the counter without checking mutations. */
    if(nxacRenderCalls>500 && entity->renderfx!=before) NxACGamehack();
    else if(nxacRenderCalls<2147483647) ++nxacRenderCalls;
}
void CG_NITMOD_NxACAfterPlayerRender(const refEntity_t *entity,int before) {
    if(!entity || nxacDetected || !NITMOD_UsesNitmodHud() || cg.demoPlayback || demo_wallHack.integer) return;
    /* CG_Player 0x96680..0x96738 / 0x97963: head renderfx before/after
     * CG_AddRefEntityWithPowerups, including an already-set DEPTHHACK. */
    if(entity->renderfx!=before || (before&RF_DEPTHHACK)) NxACGamehack();
}
int CG_NITMOD_NxACUsercmdFlags(int menuFlags) {
    if(NITMOD_UsesNitmodHud() && (nxacNextReport==-1 || nxacNextReport<cg.time)) {
        nxacNextReport=(int)((unsigned int)cg.time+10000U);
        return menuFlags|(int)nxacFlags;
    }
    return menuFlags;
}

void CG_NITMOD_NxACTransferFailure(int mask) { nxacFlags|=(unsigned int)mask&0xc0U; }
