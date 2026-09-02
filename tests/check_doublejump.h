/* Same production state transition exercised in full cgame and qagame links. */
static int CheckDoubleJump(void) {
    pmove_t move;
    playerState_t ps, before;
    pmoveExt_t ext;
    int mode, flags, rising, up, errors = 0, cases = 0;
    int guards[] = {0, PMF_RESPAWNED, PMF_NITMOD_DOUBLEJUMPED, PMF_JUMP_HELD};
    for(mode = 0; mode < 4; ++mode) for(flags = 0; flags < 4; ++flags)
        for(rising = -1; rising <= 1; ++rising) for(up = 9; up <= 10; ++up) {
            int expected = mode && !guards[flags] && (mode != 2 || rising > 0) && up >= 10;
            memset(&move, 0, sizeof(move)); memset(&ps, 0, sizeof(ps)); memset(&ext, 0, sizeof(ext));
            move.ps = &ps; move.pmext = &ext;
            move.nitmodDoubleJump = mode; move.nitmodDoubleJumpHeight = 1.4f;
            move.cmd.upmove = up; move.cmd.serverTime = 1000;
            ps.pm_flags = guards[flags]; ps.velocity[2] = (float)rising;
            ps.velocity[0] = 17; ps.velocity[1] = -19;
            ext.sprintTime = 3000; before = ps;
            if(!!BG_NITMOD_CheckAirJump(&move) != !!expected) ++errors;
            if(expected) {
                if(fabs(ps.velocity[2] - 378.0f) > 0.001f || ps.velocity[0] != 17 || ps.velocity[1] != -19 ||
                   ps.groundEntityNum != ENTITYNUM_NONE || ps.jumpTime != 1000 || ext.jumpTime != 1000 ||
                   ext.sprintTime != 500 || (ps.pm_flags & (PMF_JUMP_HELD | PMF_NITMOD_DOUBLEJUMPED)) !=
                    (PMF_JUMP_HELD | PMF_NITMOD_DOUBLEJUMPED)) ++errors;
                ps.pm_flags &= ~PMF_JUMP_HELD;
                if(BG_NITMOD_CheckAirJump(&move)) ++errors;
            } else if(memcmp(&ps, &before, sizeof(ps))) ++errors;
            ++cases;
        }
    move.nitmodDoubleJump = 1; move.cmd.upmove = 10;
    ps.pm_flags = 0; ps.eFlags = EF_PRONE;
    if(BG_NITMOD_CheckAirJump(&move)) ++errors;
    ps.eFlags = 0; move.nitmodDoubleJumpHeight = 0;
    if(BG_NITMOD_CheckAirJump(&move)) ++errors;
    move.nitmodDoubleJumpHeight = 1.4f; ext.jumpTime = 999; ext.sprintTime = 1000;
    if(!BG_NITMOD_CheckAirJump(&move) || ext.jumpTime != 999 || ext.sprintTime != 1000) ++errors;
    printf("Doublejump: %d mode/flag/velocity/input cases, plus prone/height/timing checks\n", cases);
    return errors;
}
