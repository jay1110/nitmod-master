/* Actual throw -> sink -> free callback; scheduler/free are engine doubles. */
#define main pack_team_fixture_main
#include "test_nitmod_pack_team_wasm.c"
#undef main
void Com_Error(int code,const char *format,...) { abort(); }
int main(void) {
    static gclient_t client;
    static gentity_t owner, expected;
    const int delays[]={4999,5000,30000,60000,60001};
    const int times[]={0,100000,100000000};
    const float origins[][3]={{0,0,0},{13.25f,-37.5f,101.75f},{-1000.5f,2000.25f,-40.0f}};
    int health,team,d,t,o,mask,count=0;
    owner.client=&client; owner.s.number=7;
    for(health=0;health<2;++health) for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(d=0;d<5;++d) for(t=0;t<3;++t) for(o=0;o<3;++o) for(mask=0;mask<4;++mask) {
        vec3_t position;
        int step, sinkTime, freeTime;
        memset(&client,0,sizeof(client)); client.sess.sessionTeam=team;
        client.sess.nitmodSkillMasks[SK_SIGNALS]=(mask&1 ? 2u : 0) | (mask&2 ? 32u : 0);
        level.time=times[t];
        n_medPackSinkDelay.integer=n_ammoPackSinkDelay.integer=delays[d];
        if(health) Weapon_Medic(&owner); else Weapon_MagicAmmo(&owner);
        sinkTime=times[t]+((delays[d]>=5000 && delays[d]<=60000) ? delays[d] : 30000);
        assert(pack.nextthink==sinkTime && pack.think==MagicSink);
        /* Engine would move/link the pack before this scheduled callback. */
        VectorCopy(origins[o],pack.r.currentOrigin);
        pack.clipmask=MASK_SOLID; pack.r.contents=CONTENTS_TRIGGER;
        pack.s.pos.trType=TR_GRAVITY; pack.s.pos.trDuration=731;
        VectorSet(pack.s.pos.trDelta,13,27,39);
        pack.damage=127; pack.health=61;
        expected=pack;
        expected.clipmask=expected.r.contents=0;
        expected.nextthink=sinkTime+4000; expected.think=G_FreeEntity;
        expected.s.pos.trType=TR_LINEAR; expected.s.pos.trTime=sinkTime;
        VectorCopy(origins[o],expected.s.pos.trBase);
        VectorSet(expected.s.pos.trDelta,0,0,-5);
        level.time=sinkTime; packFrees=0;
        pack.think(&pack);
        assert(packFrees==0 && !memcmp(&pack,&expected,sizeof(pack)));
        freeTime=pack.nextthink;
        for(step=0;step<=4;++step) {
            BG_EvaluateTrajectory(&pack.s.pos,sinkTime+step*1000,position,qfalse,0);
            assert(position[0]==origins[o][0] && position[1]==origins[o][1]);
            assert(position[2]==origins[o][2]-5*step);
            assert(packFrees==0);
        }
        level.time=freeTime; pack.think(&pack);
        assert(packFrees==1);
        ++count;
    }
    printf("Pack sink: %d actual throw/sink/trajectory/free-callback cases passed\n",count);
    return 0;
}
