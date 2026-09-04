static int CheckMapCycle(void) {
    nitmodGameState_t state;
    const int totals[] = {-1, 0, 1, 2, 10, 2147483647};
    const int positions[] = {-1, 0, 1, 8, 9, 10, 2147483647};
    char text[64], expected[64], small[4];
    int t, p, upper, game, tdm, dm, errors = 0;
    memset(&state, 0, sizeof(state));
    for(t = 0; t < 6; ++t) for(p = 0; p < 7; ++p) for(upper = 0; upper < 2; ++upper) {
        int valid = totals[t] > 0 && positions[p] >= 0;
        state.resetXPMapCount = totals[t]; state.mapCount = positions[p];
        if(CG_NitmodMapCycleText(&state, upper, text, sizeof(text)) != valid) ++errors;
        if(valid) {
            Com_sprintf(expected, sizeof(expected), upper ? "MAP %.0f of %d" : "Map %.0f of %d",
                (double)positions[p] + 1, totals[t]);
            if(strcmp(text, expected)) ++errors;
        } else if(text[0]) ++errors;
        if(CG_NitmodMapCycleReset(&state) != (valid && (double)positions[p] + 1 >= totals[t])) ++errors;
        memset(small, 42, sizeof(small)); CG_NitmodMapCycleText(&state, upper, small, 3);
        if(small[3] != 42 || !memchr(small, 0, 3)) ++errors;
    }
    state.mapCount = 2; state.resetXPMapCount = 5;
    for(game = -1; game < 10; ++game) for(tdm = 0; tdm < 16; ++tdm) for(dm = 0; dm < 4; ++dm) {
        int valid = game == 6 || (game == 7 && (tdm & 8)) || (game == 8 && (dm & 1));
        state.tdmOptions = tdm; state.dmOptions = (dm & 1 ? 0x4000 : 0) | (dm & 2 ? 0x8000 : 0);
        if(CG_NitmodScoreboardCycleText(&state, game, text, sizeof(text)) != valid ||
            (valid ? strcmp(text, "MAP 3 of 5") != 0 : text[0] != 0)) ++errors;
    }
    if(CG_NitmodMapCycleText(NULL, qfalse, text, sizeof(text)) || text[0] ||
        CG_NitmodMapCycleReset(NULL) || CG_NitmodMapCycleText(&state, qfalse, NULL, 1) ||
        CG_NitmodScoreboardCycleText(&state, 6, text, 0)) ++errors;
    return errors;
}
