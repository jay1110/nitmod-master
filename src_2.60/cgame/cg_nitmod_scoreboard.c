#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_scoreboard.h"

static void NITMOD_ScoreText(nitmodScoreRow_t *row, int x, int y,
    qboolean compact, int limit, const char *text) {
    nitmodScoreText_t *entry = &row->text[row->textCount++];
    entry->x = x; entry->y = y;
    entry->width = compact ? 6 : 7; entry->height = compact ? 12 : 14;
    entry->maxChars = limit;
    Q_strncpyz(entry->text, text, sizeof(entry->text));
}

static void NITMOD_ScoreIcon(nitmodScoreRow_t *row, int *cursor, int y,
    qboolean compact, qhandle_t shader) {
    nitmodScoreIcon_t *icon = &row->icons[row->iconCount++];
    icon->x = *cursor; icon->y = y + (compact ? 0 : 2);
    icon->width = icon->height = 12; icon->shader = shader;
    *cursor += compact ? 14 : 12;
}

/* WM_DrawClientScore and WM_DrawClientScore_Small: original score status
 * bits are separate from the class in clientInfo. Powerup masks here are
 * original sc/configstring masks, not native playerState powerup indices. */
qboolean CG_NitmodScoreRow(int x, int y, const score_t *score,
    qboolean compact, qboolean lives, nitmodScoreRow_t *row) {
    const clientInfo_t *client;
    int cursor = x, limit = 18, icons, base, labelY, skill, viewerTeam;
    qboolean sameTeam, spectator;
    qhandle_t status = 0;
    if(!row) return qfalse;
    memset(row, 0, sizeof(*row));
    if(!score || !cg.snap || score->client < 0 || score->client >= MAX_CLIENTS ||
       cg.clientNum < 0 || cg.clientNum >= MAX_CLIENTS || y > (compact ? 455 : 453)) return qfalse;
    client = &cgs.clientinfo[score->client];
    spectator = client->team == TEAM_SPECTATOR;
    viewerTeam = cgs.clientinfo[cg.clientNum].team;
    sameTeam = viewerTeam != TEAM_SPECTATOR && viewerTeam == client->team;
    row->highlight = score->client == cg.snap->ps.clientNum;
    row->country = score->ping != -1 && score->ping != 999 && cg_countryflags.integer &&
        cgs.media.countryFlags && client->countryCode >= 0 && client->countryCode < 255;
    if(row->country) {
        row->countryCode = client->countryCode;
        row->countryX = x - (compact ? 12 : 11); row->countryY = y - (compact ? 9 : 7);
        cursor += 16; limit -= 2;
    }
    if(score->nitmodFlags & 4)
        NITMOD_ScoreIcon(row, &cursor, y, compact, cgs.media.friendShader);
    if(!spectator) {
        if(client->powerups & 0x60) status = cgs.media.objectiveShader;
        if(compact && status) {
            NITMOD_ScoreIcon(row, &cursor, y, compact, status); status = 0;
        }
        if((score->nitmodFlags & 3) && cgs.gamestate != GS_PLAYING) {
            if(compact) NITMOD_ScoreIcon(row, &cursor, y, compact, cgs.media.hudSprintIcon);
            else if(!status) status = cgs.media.hudSprintIcon;
        }
        if(compact || !status) {
            if(sameTeam && (client->powerups & 0x80)) {
                if(compact) NITMOD_ScoreIcon(row, &cursor, y, compact, cgs.media.axisUniformShader);
                else status = cgs.media.axisUniformShader;
            }
            if(compact || !status) {
                if(score->respawnsLeft == -2 || (sameTeam && client->health == -1))
                    status = cgs.media.scoreEliminatedShader;
                else if(sameTeam && client->health == 0) status = cgs.media.medicIcon;
            }
        }
        if(status) NITMOD_ScoreIcon(row, &cursor, y, compact, status);
    }
    icons = row->iconCount;
    limit -= icons * 2;
    labelY = y + (compact ? -1 : 1);
    if(!spectator && (cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR ||
       cg.snap->ps.persistant[PERS_TEAM] == client->team) &&
       client->cls >= PC_SOLDIER && client->cls < NUM_PLAYER_CLASSES) {
        nitmodScoreIcon_t *icon = &row->icons[row->iconCount++];
        skill = BG_ClassSkillForClass(client->cls);
        icon->x = cursor; icon->y = y + (compact ? 0 : 2);
        icon->width = icon->height = 13; icon->shader = cgs.media.skillPics[skill];
        NITMOD_ScoreText(row, cursor + 14, labelY, compact, limit, client->name);
    } else NITMOD_ScoreText(row, cursor, labelY, compact, limit, client->name);
    base = cursor - 14 + (icons ? (compact ? 120 : 122) : 134);
    if((compact && icons > 1) || (!compact && icons == 2)) base -= compact ? 14 : 12;
    if(spectator) {
        const char *label = CG_NitmodSpectatorLabel(client, score->ping);
        if(!row->country) base += 16;
        NITMOD_ScoreText(row, base + 147 - CG_DrawStrlen(label) * (compact ? 7 : 8),
            compact ? y - 1 : y, compact, 0, label);
        return qtrue;
    }
    NITMOD_ScoreText(row, x + (compact ? 130 : 132), labelY, compact, 0,
        va("^2%i^7/^1%i", score->kills, score->deaths));
    base += (lives ? 0 : 24) + 50 + (row->country ? 0 : 16);
    NITMOD_ScoreText(row, base - (compact ? 8 : 10), compact ? y - 1 : y,
        compact, 0, va("^7%3i", score->score));
    base += (cg_gameType.integer == GT_WOLF_LMS ? 56 : 36) + (lives ? 8 : 0);
    NITMOD_ScoreText(row, base, compact ? y - 1 : y, compact, 0,
        (score->nitmodFlags & 2) ? "^7 BOT" : CG_NitmodPingText(score->ping));
    if(lives && cg_gameType.integer != GT_WOLF_LMS)
        NITMOD_ScoreText(row, base + 32, compact ? y - 1 : y, compact, 0,
            score->respawnsLeft < 0 ? "^7 -" : va("^7%2i", score->respawnsLeft));
    return qtrue;
}

/* WM_DrawClientScoreDM: no class/status-health column in FFA. Account for
 * country/friend/ready markers without shifting K/D, XP or ping columns. */
qboolean CG_NitmodDMScoreRow(int x, int y, const score_t *score, nitmodScoreRow_t *row) {
    const clientInfo_t *client;
    int cursor = x, limit = 18;
    qboolean spectator;
    if(!row) return qfalse;
    memset(row, 0, sizeof(*row));
    if(!score || !cg.snap || score->client < 0 || score->client >= MAX_CLIENTS || y > 453) return qfalse;
    client = &cgs.clientinfo[score->client];
    spectator = client->team == TEAM_SPECTATOR;
    row->highlight = score->client == cg.snap->ps.clientNum;
    row->country = score->ping != -1 && score->ping != 999 && cg_countryflags.integer &&
        cgs.media.countryFlags && client->countryCode >= 0 && client->countryCode < 255;
    if(row->country) {
        row->countryCode = client->countryCode; row->countryX = x - 11; row->countryY = y - 7;
        cursor += 16; limit -= 2;
    }
    if(score->nitmodFlags & 4) {
        NITMOD_ScoreIcon(row, &cursor, y, qfalse, cgs.media.friendShader); limit -= 2;
    }
    /* Unlike team rows, BOT alone does not add the ready icon in DM. */
    if(!spectator && (score->nitmodFlags & 1) && cgs.gamestate != GS_PLAYING) {
        NITMOD_ScoreIcon(row, &cursor, y, qfalse, cgs.media.hudSprintIcon); limit -= 2;
    }
    NITMOD_ScoreText(row, cursor + (spectator ? 0 : 14), y + 1, qfalse, limit, client->name);
    if(spectator) {
        const char *label = CG_NitmodSpectatorLabel(client, score->ping);
        NITMOD_ScoreText(row, x + 597 + (row->country ? 0 : 16) - CG_DrawStrlen(label) * 8,
            y, qfalse, 0, label);
    } else {
        NITMOD_ScoreText(row, x + 196, y + 1, qfalse, 0, va("^2%i^7/^1%i", score->kills, score->deaths));
        NITMOD_ScoreText(row, x + 310, y, qfalse, 0, va("^7%3i", score->score));
        NITMOD_ScoreText(row, x + 572, y, qfalse, 0,
            (score->nitmodFlags & 2) ? "^7 BOT" : CG_NitmodPingText(score->ping));
    }
    return qtrue;
}

static void NITMOD_DrawPlannedScoreRow(int x, int y, const nitmodScoreRow_t *plan,
    float fade, int width, int height) {
    const nitmodScoreRow_t row = *plan;
    vec4_t color = {1, 1, 1, 1};
    int i;
    float s0, t0, s1, t1;
    if(row.highlight) {
        vec4_t highlight = {.5f, .5f, .2f, 0};
        highlight[3] = fade * .3f;
        CG_FillRect(x - 5, y, width, height, highlight);
    }
    if(row.country && CG_NitmodCountryFlagUV(row.countryCode, &s0, &t0, &s1, &t1))
        CG_DrawPicST(row.countryX, row.countryY, 32, 32, s0, t0, s1, t1, cgs.media.countryFlags);
    for(i = 0; i < row.iconCount; ++i) {
        const nitmodScoreIcon_t *icon = &row.icons[i];
        if(icon->shader) CG_DrawPic(icon->x, icon->y, icon->width, icon->height, icon->shader);
    }
    color[3] = fade;
    for(i = 0; i < row.textCount; ++i) {
        const nitmodScoreText_t *text = &row.text[i];
        CG_DrawStringExt(text->x, text->y, text->text, color, qfalse, qtrue,
            text->width, text->height, text->maxChars);
    }
}

void CG_NitmodDrawScoreRow(int x, int y, const score_t *score,
    float fade, qboolean compact, qboolean lives) {
    nitmodScoreRow_t row;
    if(CG_NitmodScoreRow(x, y, score, compact, lives, &row))
        NITMOD_DrawPlannedScoreRow(x, y, &row, fade, 285, compact ? 12 : 15);
}

void CG_NitmodDrawDMScoreRow(int x, int y, const score_t *score, float fade) {
    nitmodScoreRow_t row;
    if(CG_NitmodDMScoreRow(x, y, score, &row))
        NITMOD_DrawPlannedScoreRow(x, y, &row, fade, 610, 15);
}
