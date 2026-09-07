#define main class_lists_fixture_main
#include "test_nitmod_client_class_lists_wasm.c"
#undef main
int main(void) {
    pmove_t move;
    char caps[32]; int i;
    const char *bad[]={"", "1 2", "1 2 3 4 5 6 7 8", "1 2 3 4 5 6 -1", "1 2 3 4 5 6 4294967296"};
    serverInfo="\\gamename\\nitmod\\nitmod_csLayout\\et260";
    playerInfo="\\xp\\1 2 4 8 16 32 4294967295";
    memset(&move,0,sizeof(move));
    NITMOD_PackPredictionInputs(&move,0); assert(!move.nitmodPackChargeEnabled);
    args[0]=NITMOD_CAPABILITIES_ACK_COMMAND; args[1]="1";
    sprintf(caps,"%u",NITMOD_FEATURE_PACK_CHARGE); args[2]=caps;
    assert(NITMOD_ProtocolCommand(args[0]));
    NITMOD_PackPredictionInputs(&move,0); assert(!move.nitmodPackChargeEnabled);
    argumentCount=2; args[1]="0"; assert(NITMOD_ProtocolCommand("npcc"));
    argumentCount=3; args[1]="1";
    NITMOD_PackPredictionInputs(&move,0); assert(move.nitmodPackChargeEnabled);
    for(i=0;i<6;++i) assert(move.nitmodPackSkillMasks[i]==(1u<<i));
    assert(move.nitmodPackSkillMasks[6]==0xffffffffu);
    argumentCount=2; args[1]="1"; NITMOD_ProtocolCommand("npcc");
    NITMOD_PackPredictionInputs(&move,0); assert(move.nitmodPackChargeBypass);
    args[1]="2"; NITMOD_ProtocolCommand("npcc");
    NITMOD_PackPredictionInputs(&move,0); assert(move.nitmodPackChargeBypass);
    args[1]="0"; NITMOD_ProtocolCommand("npcc");
    NITMOD_PackPredictionInputs(&move,0); assert(!move.nitmodPackChargeBypass);
    argumentCount=3; args[1]="1";
    for(i=0;i<5;++i) {
        char info[128]; sprintf(info,"\\xp\\%s",bad[i]); playerInfo=info;
        NITMOD_PackPredictionInputs(&move,0); assert(!move.nitmodPackChargeEnabled);
        assert(move.nitmodPackSkillMasks[0]==0);
    }
    playerInfo="\\xp\\2 2 2 2 2 2 2";
    NITMOD_PackPredictionInputs(&move,0); assert(move.nitmodPackChargeEnabled);
    args[1]="99"; NITMOD_ProtocolCommand(args[0]);
    NITMOD_PackPredictionInputs(&move,0); assert(!move.nitmodPackChargeEnabled);
    args[1]="1"; NITMOD_ProtocolCommand(args[0]); NITMOD_ClearConfigStrings();
    NITMOD_PackPredictionInputs(&move,0); assert(!move.nitmodPackChargeEnabled);
    serverInfo="\\gamename\\nitmod"; cgs.clientinfo[0].nitmodSkillMasks[2]=32;
    NITMOD_PackPredictionInputs(&move,0); assert(move.nitmodPackChargeEnabled && move.nitmodPackSkillMasks[2]==32);
    NITMOD_PackPredictionInputs(&move,MAX_CLIENTS); assert(!move.nitmodPackChargeEnabled);
    puts("Pack mask negotiation: actual ACK/parser/reset/original fallback checks passed");
    return 0;
}
