static float voteUIFlags, voteUIDisabled;
static int voteUIWrites;
static int QDECL VoteUISyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_CVAR_VARIABLEVALUE) {
        if(strcmp(va_arg(args, const char *), "cg_ui_voteFlags")) exit(2);
        memcpy(&result, &voteUIFlags, sizeof(result));
    } else if(command == UI_CVAR_SETVALUE) {
        int bits;
        if(strcmp(va_arg(args, const char *), "cg_ui_novote")) exit(2);
        bits = va_arg(args, int); memcpy(&voteUIDisabled, &bits, sizeof(bits)); ++voteUIWrites;
    } else exit(2);
    va_end(args); return result;
}
static int CheckVoteUIFlags(void) {
    int i, errors = 0;
    dllEntry(VoteUISyscall);
    for(i = -2; i < 24; ++i) {
        char script[] = "clientCheckVote", *cursor = script;
        voteUIFlags = (float)(i == -2 ? ET_VOTING_DISABLED :
            i == -1 ? VOTING_DISABLED : VOTING_DISABLED ^ (1 << i));
        voteUIWrites = 0; UI_RunMenuScript(&cursor);
        if(voteUIWrites != 1 || voteUIDisabled != (i < 0 ? 1.f : 0.f)) ++errors;
    }
    return errors;
}
