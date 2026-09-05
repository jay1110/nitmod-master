extern localEntity_t cg_activeLocalEntities;
extern void CG_LaunchGib(centity_t *, vec3_t, vec3_t, vec3_t, qhandle_t, float, int);
extern void CG_BloodTrail(localEntity_t *);
static int CheckGibOptions(void) {
    static snapshot_t snapshot;
    centity_t cent;
    vec3_t origin={1,2,3}, angles={0,90,0}, velocity={4,5,6};
    vmCvar_t savedGibs=cg_gibs, savedBlood=cg_blood;
    snapshot_t *savedSnap=cg.snap;
    int savedTime=cg.time, option, blood, errors=0;
    memset(&cent,0,sizeof(cent)); cent.currentState.number=7;
    cg.time=1000; memset(&snapshot,0,sizeof(snapshot)); cg.snap=&snapshot;
    for(option=-1;option<=1;++option) for(blood=0;blood<2;++blood) {
        localEntity_t *le;
        CG_InitLocalEntities(); cg_gibs.integer=option; cg_blood.integer=blood;
        CG_LaunchGib(&cent,origin,angles,velocity,123,1,2);
        le=cg_activeLocalEntities.next;
        if(!option) {
            if(le!=&cg_activeLocalEntities) ++errors;
        } else {
            if(le==&cg_activeLocalEntities) { ++errors; continue; }
            if(le->leType!=LE_FRAGMENT || le->refEntity.hModel!=123 || le->ownerNum!=7 ||
               le->endTime<36000 || le->endTime>46000 || le->breakCount!=2 ||
               le->pos.trType!=TR_GRAVITY || !VectorCompare(le->pos.trDelta,velocity)) ++errors;
        }
    }
    /* Disabled effects must not touch tags, trails or allocate fragments. */
    CG_InitLocalEntities(); cg_gibs.integer=0; cg_blood.integer=1;
    cent.currentState.eFlags=EF_HEADSHOT; /* Hat removal is independent. */
    CG_Bleed(origin,7);
    CG_GibPlayer(&cent,origin,velocity);
    {
        localEntity_t trail;
        memset(&trail,0,sizeof(trail)); trail.ownerNum=7;
        VectorCopy(velocity,trail.pos.trDelta);
        CG_BloodTrail(&trail);
        if(trail.headJuncIndex) ++errors;
    }
    cg_gibs.integer=1; cg.snap=NULL;
    CG_Bleed(origin,7);
    CG_Bleed(origin,-1);
    CG_LaunchGib(NULL,origin,angles,velocity,123,1,0);
    if(cg_activeLocalEntities.next!=&cg_activeLocalEntities) ++errors;
    CG_InitLocalEntities(); cg_gibs=savedGibs; cg_blood=savedBlood;
    cg.time=savedTime; cg.snap=savedSnap;
    if(errors) fprintf(stderr,"gib options: %d failures\n",errors);
    return errors;
}
