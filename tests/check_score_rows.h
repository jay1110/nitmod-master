#include "../src_2.60/cgame/cg_nitmod_scoreboard.h"

static int scoreRowGlyphs, scoreRowDrawCount;
static nitmodScoreIcon_t scoreRowDraws[512];
static int QDECL ScoreRowEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_R_DRAWSTRETCHPIC) {
        float coords[8];
        int i, shader;
        for(i = 0; i < 8; ++i) {
            union { int bits; float value; } number;
            number.bits = va_arg(args, int); coords[i] = number.value;
        }
        shader = va_arg(args, int);
        if(shader == 300) ++scoreRowGlyphs;
        else {
            nitmodScoreIcon_t *draw;
            if(scoreRowDrawCount == 512) exit(2);
            draw = &scoreRowDraws[scoreRowDrawCount++];
            draw->x = coords[0]; draw->y = coords[1];
            draw->width = coords[2]; draw->height = coords[3]; draw->shader = shader;
        }
    } else if(command != CG_R_SETCOLOR) exit(2);
    va_end(args); return 0;
}

static int CheckNitmodScoreRows(void) {
    snapshot_t snapshot, *savedSnapshot = cg.snap;
    clientInfo_t savedClients[2];
    static cgMedia_t savedMedia;
    score_t score;
    nitmodScoreRow_t row;
    int savedClient = cg.clientNum, savedGame = cg_gameType.integer;
    int savedState = cgs.gamestate, savedCountry = cg_countryflags.integer;
    int compact, flags, powerups, team, health, life, ping, state, i, errors = 0;
    static const int pings[] = {-1, 999, 50};
    savedClients[0] = cgs.clientinfo[0]; savedClients[1] = cgs.clientinfo[1];
    savedMedia = cgs.media;
    memset(&snapshot, 0, sizeof(snapshot)); memset(&score, 0, sizeof(score));
    memset(&cgs.clientinfo[0], 0, sizeof(clientInfo_t));
    memset(&cgs.clientinfo[1], 0, sizeof(clientInfo_t));
    cg.snap = &snapshot; cg.clientNum = 0;
    snapshot.ps.clientNum = 1; snapshot.ps.persistant[PERS_TEAM] = TEAM_AXIS;
    cgs.clientinfo[0].team = TEAM_AXIS;
    cgs.clientinfo[1].cls = PC_MEDIC; cgs.clientinfo[1].countryCode = 34;
    Q_strncpyz(cgs.clientinfo[1].name, "^1Example", sizeof(cgs.clientinfo[1].name));
    cgs.media.friendShader = 101; cgs.media.objectiveShader = 102;
    cgs.media.hudSprintIcon = 103; cgs.media.axisUniformShader = 104;
    cgs.media.scoreEliminatedShader = 105; cgs.media.medicIcon = 106;
    cgs.media.countryFlags = 107;
    for(i = 0; i < SK_NUM_SKILLS; ++i) cgs.media.skillPics[i] = 200 + i;
    cg_countryflags.integer = 1; cg_gameType.integer = GT_WOLF;
    cgs.gamestate = GS_WARMUP;
    score.client = 1; score.kills = 12; score.deaths = 3; score.score = 42;
    for(state = 0; state < 2; ++state)
    for(compact = 0; compact < 2; ++compact) for(flags = 0; flags < 8; ++flags)
    for(powerups = 0; powerups < 4; ++powerups) for(team = TEAM_AXIS; team <= TEAM_SPECTATOR; ++team)
    for(health = -1; health <= 1; ++health) for(life = 0; life < 2; ++life)
    for(ping = 0; ping < 3; ++ping) {
        int spectator = team == TEAM_SPECTATOR;
        cgs.gamestate = state ? GS_WARMUP : GS_PLAYING;
        score.nitmodFlags = flags; score.ping = pings[ping]; score.respawnsLeft = life ? -2 : 5;
        cgs.clientinfo[1].team = team; cgs.clientinfo[1].health = health;
        cgs.clientinfo[1].powerups = (powerups & 1 ? 0x20 : 0) | (powerups & 2 ? 0x80 : 0);
        if(!CG_NitmodScoreRow(20, 100, &score, compact, life, &row)) { ++errors; continue; }
        if(!row.highlight || row.country != (ping == 2) || row.textCount != (spectator ? 2 : 4 + life) ||
           row.iconCount > 6 || row.text[0].maxChars < 1 || strcmp(row.text[0].text, "^1Example")) ++errors;
        if(row.country && (row.countryX != (compact ? 8 : 9) || row.countryY != (compact ? 91 : 93))) ++errors;
        for(i = 0; i < row.textCount; ++i)
            if(row.text[i].width != (compact ? 6 : 7) || row.text[i].height != (compact ? 12 : 14)) ++errors;
        if(flags & 4) {
            if(!row.iconCount || row.icons[0].shader != 101) ++errors;
        }
        if(!spectator) {
            if(row.text[1].x != (compact ? 150 : 152) || strcmp(row.text[1].text, "^2\x31\x32^7/^1\x33")) ++errors;
            if(flags & 2) { if(strcmp(row.text[3].text, "^7 BOT")) ++errors; }
            else if(score.ping == -1 && strcmp(row.text[3].text, "^2CONN.^7")) ++errors;
            if(team == TEAM_AXIS) {
                if(!row.iconCount || row.icons[row.iconCount - 1].shader != 200 + BG_ClassSkillForClass(PC_MEDIC)) ++errors;
            } else for(i = 0; i < row.iconCount; ++i) if(row.icons[i].shader >= 200) ++errors;
        } else {
            if(row.iconCount != ((flags & 4) != 0)) ++errors;
            if(score.ping == -1 && strcmp(row.text[1].text, "^3CONNECTING")) ++errors;
        }
        /* DM has fixed columns, no class/health/objective icons and a distinct
         * ready-bit rule: BOT alone must not acquire the stamina marker. */
        if(!CG_NitmodDMScoreRow(20, 100, &score, &row)) { ++errors; continue; }
        {
            int expectedIcons = !!(flags & 4) + (!spectator && (flags & 1) && state);
            int country = ping == 2;
            if(row.textCount != (spectator ? 2 : 4) || row.iconCount != expectedIcons ||
               row.country != country || !row.highlight ||
               row.text[0].x != 20 + country * 16 + expectedIcons * 12 + (spectator ? 0 : 14) ||
               row.text[0].maxChars != 18 - country * 2 - expectedIcons * 2) ++errors;
            for(i = 0; i < row.textCount; ++i)
                if(row.text[i].width != 7 || row.text[i].height != 14) ++errors;
            if(!spectator) {
                if(row.text[1].x != 216 || row.text[1].y != 101 || row.text[2].x != 330 ||
                   row.text[2].y != 100 || row.text[3].x != 592 || row.text[3].y != 100) ++errors;
                if(flags & 2) { if(strcmp(row.text[3].text, "^7 BOT")) ++errors; }
                else if(!strcmp(row.text[3].text, "^7 BOT")) ++errors;
            } else {
                if(row.text[1].x != 617 + (country ? 0 : 16) - CG_DrawStrlen(row.text[1].text) * 8) ++errors;
            }
        }
    }
    score.nitmodFlags = 0; score.ping = 50; score.respawnsLeft = 5;
    cgs.clientinfo[1].team = TEAM_AXIS; cgs.clientinfo[1].health = 100;
    cgs.clientinfo[1].powerups = 0; cg_countryflags.integer = 0;
    for(compact = 0; compact < 2; ++compact) for(life = 0; life < 2; ++life) {
        CG_NitmodScoreRow(20, 100, &score, compact, life, &row);
        if(row.text[0].x != 34 || row.text[0].maxChars != 18 ||
           row.text[2].x != 20 + (life ? 176 : 200) + (compact ? 2 : 0) ||
           row.text[3].x != 20 + (life ? 230 : 246)) ++errors;
        cg_gameType.integer = GT_WOLF_LMS;
        CG_NitmodScoreRow(20, 100, &score, compact, life, &row);
        if(row.textCount != 4 || row.text[3].x != 40 + (life ? 230 : 246)) ++errors;
        cg_gameType.integer = GT_WOLF;
        if(CG_NitmodScoreRow(20, compact ? 456 : 454, &score, compact, life, &row)) ++errors;
    }
    {
        float savedX = cgs.screenXScale, savedY = cgs.screenYScale;
        nitmodHudAnchor_t savedAnchor = CG_NitmodHudAnchor(NITMOD_HUD_STRETCH);
        cgs.screenXScale = cgs.screenYScale = 1;
        cgs.media.charsetShader = 300; cgs.media.whiteShader = 301;
        cg_countryflags.integer = 1; cgs.gamestate = GS_WARMUP;
        cgs.clientinfo[1].powerups = 0xa0; cgs.clientinfo[1].health = 0;
        score.nitmodFlags = 7;
        dllEntry(ScoreRowEngine);
        for(compact = 0; compact < 2; ++compact) {
            CG_NitmodScoreRow(20, 100, &score, compact, 1, &row);
            scoreRowDrawCount = scoreRowGlyphs = 0;
            CG_NitmodDrawScoreRow(20, 100, &score, .75f, compact, 1);
            if(!scoreRowGlyphs || scoreRowDrawCount != row.iconCount + 2 ||
               row.iconCount != (compact ? 6 : 3)) ++errors;
            if(scoreRowDraws[0].shader != 301 || scoreRowDraws[0].x != 15 ||
               scoreRowDraws[0].width != 285 || scoreRowDraws[0].height != (compact ? 12 : 15)) ++errors;
            if(scoreRowDraws[1].shader != 107 || scoreRowDraws[1].x != row.countryX ||
               scoreRowDraws[1].y != row.countryY) ++errors;
            for(i = 0; i < row.iconCount; ++i)
                if(memcmp(&scoreRowDraws[i + 2], &row.icons[i], sizeof(row.icons[i]))) ++errors;
        }
        for(life = 0; life < 2; ++life) {
            score.ping = life ? 999 : 50;
            CG_NitmodDMScoreRow(20, 100, &score, &row);
            scoreRowDrawCount = scoreRowGlyphs = 0;
            CG_NitmodDrawDMScoreRow(20, 100, &score, .75f);
            if(!scoreRowGlyphs || scoreRowDrawCount != 3 + !life || row.iconCount != 2 ||
               scoreRowDraws[0].shader != 301 || scoreRowDraws[0].width != 610 ||
               scoreRowDraws[0].height != 15) ++errors;
            for(i = 0; i < row.iconCount; ++i)
                if(memcmp(&scoreRowDraws[i + 1 + !life], &row.icons[i], sizeof(row.icons[i]))) ++errors;
        }
        scoreRowDrawCount = scoreRowGlyphs = 0;
        CG_NitmodDrawDMScoreRow(20, 454, &score, 1);
        if(scoreRowDrawCount || scoreRowGlyphs) ++errors;
        {
            score_t savedScores[MAX_CLIENTS];
            int savedCount = cg.numScores, bands, selected, n;
            memcpy(savedScores, cg.scores, sizeof(savedScores));
            cgs.media.limboFont1.glyphScale = 1;
            for(i = 0; i < GLYPHS_PER_FONT; ++i) {
                glyphInfo_t *glyph = &cgs.media.limboFont1.glyphs[i];
                memset(glyph, 0, sizeof(*glyph));
                glyph->glyph = 300; glyph->xSkip = 7;
                glyph->imageWidth = 7; glyph->imageHeight = 14;
            }
            cg.numScores = 3;
            cg.scores[0] = cg.scores[1] = cg.scores[2] = score;
            cg.scores[1].client = MAX_CLIENTS;
            for(n = 0; n <= 3; ++n) {
                scoreRowDrawCount = scoreRowGlyphs = 0;
                if(CG_NitmodDMScoreboard(20, 100, .75f, n, qfalse) != 169) ++errors;
                bands = selected = 0;
                for(i = 0; i < scoreRowDrawCount; ++i) {
                    if(scoreRowDraws[i].width == 610 && scoreRowDraws[i].y >= 137) {
                        if(scoreRowDraws[i].height == 16) ++bands;
                        if(scoreRowDraws[i].height == 15) ++selected;
                    }
                }
                if(bands != n || selected != 2 || !scoreRowGlyphs) ++errors;
            }
            for(i = 0; i < MAX_CLIENTS; ++i) cg.scores[i] = score;
            cg.numScores = INT_MAX;
            scoreRowDrawCount = scoreRowGlyphs = 0;
            if(CG_NitmodDMScoreboard(20, 100, 1, INT_MAX, qfalse) != 457) ++errors;
            memcpy(cg.scores, savedScores, sizeof(savedScores)); cg.numScores = savedCount;
        }
        dllEntry(Engine);
        cgs.screenXScale = savedX; cgs.screenYScale = savedY;
        CG_NitmodHudAnchor(savedAnchor);
    }
    score.client = MAX_CLIENTS;
    if(CG_NitmodScoreRow(20, 100, &score, 0, 0, &row) || row.textCount || row.iconCount) ++errors;
    if(CG_NitmodDMScoreRow(20, 100, &score, &row) || row.textCount || row.iconCount) ++errors;
    if(CG_NitmodDMScoreRow(20, 100, NULL, &row) || CG_NitmodDMScoreRow(20, 100, &score, NULL)) ++errors;
    if(CG_NitmodScoreRow(20, 100, NULL, 0, 0, &row) || CG_NitmodScoreRow(20, 100, &score, 0, 0, NULL)) ++errors;
    cg.snap = savedSnapshot; cg.clientNum = savedClient; cg_gameType.integer = savedGame;
    cgs.gamestate = savedState; cg_countryflags.integer = savedCountry;
    cgs.clientinfo[0] = savedClients[0]; cgs.clientinfo[1] = savedClients[1]; cgs.media = savedMedia;
    return errors;
}
