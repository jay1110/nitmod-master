#include "../src_2.60/cgame/cg_nitmod_mapvote.h"
static int mapVoteSends, mapVoteLoads, mapVotePreviews, mapVoteErrors;
static char mapVoteCommand[128];
static int QDECL MapVoteEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_SENDCLIENTCOMMAND) {
        Q_strncpyz(mapVoteCommand, va_arg(args, const char *), sizeof(mapVoteCommand)); ++mapVoteSends;
    } else if(command == CG_R_REGISTERSHADERNOMIP) {
        const char *name = va_arg(args, const char *);
        int result = strstr(name, "_cc.tga") ? 502 : 501;
        if(strcmp(name, "levelshots/oasis.tga") && strcmp(name, "levelshots/oasis_cc.tga")) ++mapVoteErrors;
        ++mapVoteLoads; va_end(args); return result;
    } else if(command == CG_R_DRAWSTRETCHPIC) {
        int bits[8], shader, i;
        float rect[4];
        for(i = 0; i < 8; ++i) bits[i] = va_arg(args, int);
        memcpy(rect, bits, sizeof(rect)); shader = va_arg(args, int);
        if(shader == 501 || shader == 502) {
            ++mapVotePreviews;
            if(rect[0] != (shader == 501 ? 524 : 428) || rect[1] != (shader == 501 ? 50 : 154) ||
                rect[2] != (shader == 501 ? 96 : 192) || rect[3] != (shader == 501 ? 72 : 192)) ++mapVoteErrors;
        }
    } else if(command != CG_R_SETCOLOR && command != CG_PRINT &&
        command != CG_MILLISECONDS && command != CG_PUMPEVENTLOOP) {
        fprintf(stderr, "Unexpected mapvote syscall %d\n", command); exit(2);
    }
    va_end(args); return 0;
}
static int CheckMapVotePresentation(void) {
    static cgs_t saved;
    static displayContextDef_t context;
    displayContextDef_t *savedContext = Display_GetContext();
    snapshot_t snap, *savedSnap = cg.snap;
    nitmodMapVoteButton_t button;
    int mode, row, voted, i, count, offset, errors = 0;
    saved = cgs; memset(&snap, 0, sizeof(snap)); cg.snap = &snap;
    memset(&context, 0, sizeof(context)); Init_Display(&context);
    CG_NitmodMapVoteReset(); cgs.nitmodMapVoteCount = 24; cgs.nitmodMapVoteListReceived = qtrue;
    for(i = 0; i < 24; ++i) {
        cgs.nitmodMapVoteIds[i] = 100 + i;
        Q_strncpyz(cgs.nitmodMapVoteNames[i], "oasis", MAX_QPATH);
        Com_sprintf(cgs.nitmodMapVoteDisplayNames[i], 128, "Map %d", i);
    }
    for(mode = 0; mode < 2; ++mode) for(row = -1; row < 4; ++row) for(voted = 0; voted < 2; ++voted) {
        cgs.nitmodMapVoteMulti = mode; snap.ps.eFlags = voted ? EF_VOTED : 0;
        for(i = 0; i < 3; ++i) cgs.nitmodMapVoteSelections[i] = voted ? i : -1;
        if(CG_NitmodMapVoteButton(row, &button) != (row >= 0 && row < (mode ? 3 : 1))) ++errors;
        if(row < 0 || row >= (mode ? 3 : 1)) continue;
        if(button.slot != (mode ? 3 - row : 1) || button.rect.x != 15 || button.rect.y != 296 + row * 20 ||
            button.rect.w != 64 || button.rect.h != 16 || (strstr(button.label, "RE-VOTE") != NULL) != voted ||
            (button.mapName[0] != 0) != voted) ++errors;
    }
    dllEntry(MapVoteEngine); mapVoteSends = mapVoteLoads = mapVoteErrors = mapVotePreviews = 0;
    cgs.nitmodMapVoteMulti = qtrue;
    for(i = 0; i < 3; ++i) cgs.nitmodMapVoteSelections[i] = -1;
    for(row = 0; row < 3; ++row) {
        char expected[128];
        cgs.nitmodMapVoteSelected = row; cgs.cursorX = 20; cgs.cursorY = 300 + row * 20;
        if(!CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue)) ++errors;
        Com_sprintf(expected, sizeof(expected), "mapvote %d %d", 100 + row, 3 - row);
        if(strcmp(mapVoteCommand, expected) || mapVoteSends != row + 1) ++errors;
    }
    cgs.nitmodMapVoteSelected = 0; cgs.cursorY = 320;
    if(CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue) || mapVoteSends != 3) ++errors;
    cgs.cursorY = 313; if(CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue)) ++errors;
    cgs.cursorX = 15; cgs.cursorY = 55;
    if(CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue)) ++errors;
    cgs.cursorY = 80;
    if(!CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue) || cgs.nitmodMapVoteSelected != 2 || mapVoteLoads != 2) ++errors;
    CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue); if(mapVoteLoads != 2) ++errors;
    for(i = 0; i < 30; ++i) CG_NitmodMapVoteKeyEvent(K_MWHEELDOWN, qtrue);
    if(cgs.nitmodMapVoteOffset != 5) ++errors;
    cgs.glconfig.vidWidth = 640; cgs.glconfig.vidHeight = 480;
    cgs.screenXScale = cgs.screenYScale = 1;
    memset(&cgs.media.limboFont2, 0, sizeof(cgs.media.limboFont2));
    CG_NitmodMapVoteDraw();
    if(mapVotePreviews != 2 || mapVoteErrors) ++errors;
    for(count = 0; count <= NITMOD_MAX_MAPVOTE_MAPS; ++count) {
        int maximum = count > 19 ? count - 19 : 0;
        cgs.nitmodMapVoteCount = count;
        for(offset = -1; offset <= maximum + 1; ++offset) {
            rectDef_t thumb;
            int bounded = offset < 0 ? 0 : offset > maximum ? maximum : offset;
            float height = count > 19 ? 240.f * 19 / count : 240;
            float top = maximum ? 56 + bounded / (float)maximum * (240 - height) : 56;
            cgs.nitmodMapVoteOffset = offset; CG_NitmodMapVoteScrollRect(&thumb);
            if(cgs.nitmodMapVoteOffset != bounded || thumb.x != 265 || thumb.w != 16 ||
                fabs(thumb.y - top) > .001 || fabs(thumb.h - height) > .001) ++errors;
        }
    }
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.dbMode = 0; cgs.gametype = 6;
    cgs.nitmodMapVoteCount = 64; cgs.nitmodMapVoteOffset = 0;
    cgs.cursorX = 270; cgs.cursorY = 60;
    context.cursorx = cgs.cursorX; context.cursory = cgs.cursorY;
    if(!CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue) || !BG_PanelButtons_GetFocusButton()) ++errors;
    CG_Debriefing_MouseEvent(0, 30);
    if(cgs.nitmodMapVoteOffset != 3) ++errors; // 64 is clamped to the 32-slot typed list
    if(!CG_NitmodMapVoteKeyEvent(K_MOUSE1, qfalse) || BG_PanelButtons_GetFocusButton()) ++errors;
    {
        rectDef_t thumb;
        CG_NitmodMapVoteScrollRect(&thumb); cgs.cursorY = (int)thumb.y + 4;
        context.cursory = cgs.cursorY;
        CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue);
        CG_Debriefing_MouseEvent(0, 2147483647);
        if(cgs.nitmodMapVoteOffset != 13) ++errors;
        CG_Debriefing_MouseEvent(0, -2147483647);
        CG_Debriefing_MouseEvent(0, -2147483647);
        if(cgs.nitmodMapVoteOffset != 0) ++errors;
        CG_NitmodMapVoteKeyEvent(K_MOUSE1, qfalse);
        cgs.cursorY = context.cursory = 60; CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue);
        cgs.dbMode = 1; CG_Debriefing_MouseEvent(0, 0);
        if(BG_PanelButtons_GetFocusButton()) ++errors;
        cgs.dbMode = 0; cgs.cursorY = context.cursory = 60;
        CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue);
        cgs.dbMode = 1; CG_Debriefing_KeyEvent(K_MOUSE1, qfalse);
        if(BG_PanelButtons_GetFocusButton()) ++errors;
        cgs.dbMode = 0;
        CG_NitmodMapVoteKeyEvent(K_MOUSE1, qtrue); CG_NitmodMapVoteReset();
        if(BG_PanelButtons_GetFocusButton()) ++errors;
    }
    {
        panel_button_t scroll;
        const int counts[4] = {MAX_CLIENTS, WS_MAX, 10, NITMOD_MAX_MAPVOTE_MAPS};
        const int visible[4] = {24, 7, 7, 19};
        int type, step, actual;
        memset(&scroll, 0, sizeof(scroll)); scroll.rect.h = 240;
        for(i = 0; i < MAX_CLIENTS; ++i) { cgs.dbSortedClients[i] = i; cgs.clientinfo[i].infoValid = qtrue; }
        for(i = 0; i < WS_MAX; ++i) cgs.dbWeaponStats[i].numShots = 1;
        cgs.dbWeaponStatsRecieved = qtrue; cgs.campaignInfoLoaded = qtrue;
        cgs.campaignData.mapCount = 10; cgs.nitmodMapVoteCount = NITMOD_MAX_MAPVOTE_MAPS;
        cgs.dbPlayerListOffset = cgs.dbWeaponListOffset = cgs.tdbMapListOffset = cgs.nitmodMapVoteOffset = 0;
        for(type = 0; type < 4; ++type) {
            scroll.data[0] = type;
            for(step = 0; step < 100; ++step) CG_Debriefing_Scrollbar_KeyDown(&scroll, K_MWHEELDOWN);
            actual = type == 0 ? cgs.dbPlayerListOffset : type == 1 ? cgs.dbWeaponListOffset :
                type == 2 ? cgs.tdbMapListOffset : cgs.nitmodMapVoteOffset;
            if(actual != counts[type] - visible[type]) ++errors;
            for(step = 0; step < 100; ++step) CG_Debriefing_Scrollbar_KeyDown(&scroll, K_MWHEELUP);
            actual = type == 0 ? cgs.dbPlayerListOffset : type == 1 ? cgs.dbWeaponListOffset :
                type == 2 ? cgs.tdbMapListOffset : cgs.nitmodMapVoteOffset;
            if(actual != 0) ++errors;
        }
    }
    cg.snap = NULL; if(CG_NitmodMapVoteButton(0, &button)) ++errors;
    CG_NitmodMapVoteReset(); cgs = saved; cg.snap = savedSnap; dllEntry(Engine); Init_Display(savedContext);
    return errors;
}
