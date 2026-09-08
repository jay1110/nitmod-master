#ifndef CG_NITMOD_NXAC_H
#define CG_NITMOD_NXAC_H
void CG_NITMOD_NxACReset(void);
void CG_NITMOD_NxACAfterRender(const refEntity_t *entity,int before);
void CG_NITMOD_NxACAfterPlayerRender(const refEntity_t *entity,int before);
int CG_NITMOD_NxACUsercmdFlags(int menuFlags);
void CG_NITMOD_NxACTransferFailure(int mask);
#endif
