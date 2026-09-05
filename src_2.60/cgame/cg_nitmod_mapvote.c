#include "cg_local.h"
#include "cg_nitmod_mapvote.h"
#include "cg_nitmod_config.h"

qboolean CG_NitmodMapVoteEnabled(void) {
    const nitmodGameState_t *state = NITMOD_GameState();
    return NITMOD_UsesOriginalProtocol() && ((int)cgs.gametype == 6 ||
        ((int)cgs.gametype == 7 && (state->tdmOptions & 8)) ||
        ((int)cgs.gametype == 8 && (state->dmOptions & 0x4000)));
}

/* Original Nitmod page IDs: 0 map vote, 1 scoreboard, 2 team/campaign,
 * 3 player statistics.  Without map voting the cycle starts at 1. */
int CG_NitmodNextDebriefPage(int page) {
    if(CG_NitmodMapVoteEnabled()) {
        return page >= 0 && page < 3 ? page + 1 : 0;
    }
    return page >= 1 && page < 3 ? page + 1 : 1;
}

/* Original # arguments 19/20: zero-based map index and XP-reset cycle size. */
qboolean CG_NitmodMapCycleText(const nitmodGameState_t *state, qboolean uppercase, char *text, int size) {
    if(!text || size <= 0) return qfalse;
    text[0] = 0;
    if(!state || state->mapCount < 0 || state->resetXPMapCount <= 0) return qfalse;
    Com_sprintf(text, size, uppercase ? "MAP %u of %d" : "Map %u of %d",
        (unsigned int)state->mapCount + 1U, state->resetXPMapCount);
    return qtrue;
}

qboolean CG_NitmodMapCycleReset(const nitmodGameState_t *state) {
    return state && state->mapCount >= 0 && state->resetXPMapCount > 0 &&
        state->mapCount >= state->resetXPMapCount - 1;
}

qboolean CG_NitmodScoreboardCycleText(const nitmodGameState_t *state, int gametype, char *text, int size) {
    if(!text || size <= 0) return qfalse;
    text[0] = 0;
    if(!state || !(gametype == 6 || (gametype == 7 && (state->tdmOptions & 8)) ||
        (gametype == 8 && (state->dmOptions & 0x4000)))) return qfalse;
    return CG_NitmodMapCycleText(state, qtrue, text, size);
}

#define NITMOD_MAPVOTE_VISIBLE 19
#define NITMOD_MAPVOTE_LIST_X 15.f
#define NITMOD_MAPVOTE_LIST_Y 56.f
#define NITMOD_MAPVOTE_ROW_H 12.f

static qhandle_t mapVoteCommandMap;
static panel_button_t mapVoteScrollbar = {
    NULL, NULL, {265, 56, 16, 240}, {3, 0, 0, 0, 0, 0, 0, 0}, NULL,
    CG_Debriefing_Scrollbar_KeyDown, CG_Debriefing_Scrollbar_KeyUp,
    CG_Debriefing_Scrollbar_Draw, NULL
};

static qboolean CG_NitmodMapVoteNameSafe( const char *name ) {
	int i;
	if( !name || !*name ) return qfalse;
	for( i = 0; name[i]; ++i ) {
		unsigned char c = (unsigned char)name[i];
		if( i >= MAX_QPATH - 1 || !( Q_isalphanumeric(c) || c == '_' || c == '-' || c == '.' ) )
			return qfalse;
	}
	return qtrue;
}

void CG_NitmodMapVoteScrollRect(rectDef_t *rect) {
    if(!rect) return;
    CG_Debriefing_ScrollCheckOffset(&mapVoteScrollbar);
    CG_Debriefing_ScrollGetBarRect(&mapVoteScrollbar, rect);
}

static void CG_NitmodMapVoteSelect( int mapIndex ) {
    if(mapIndex < 0 || mapIndex >= cgs.nitmodMapVoteCount || mapIndex >= NITMOD_MAX_MAPVOTE_MAPS) return;
    cgs.nitmodMapVoteSelected = mapIndex;
    cgs.nitmodMapVoteSelectedTime = cg.time;
    cgs.nitmodMapVoteLevelshot = trap_R_RegisterShaderNoMip(
        va("levelshots/%s.tga", cgs.nitmodMapVoteNames[mapIndex]));
    if(!cgs.nitmodMapVoteLevelshot)
        cgs.nitmodMapVoteLevelshot = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
    mapVoteCommandMap = trap_R_RegisterShaderNoMip(
        va("levelshots/%s_cc.tga", cgs.nitmodMapVoteNames[mapIndex]));
}

static qboolean CG_NitmodMapVoteCast( int slot ) {
	int selected = cgs.nitmodMapVoteSelected;
	int i;

	if( !cg.snap || selected < 0 || selected >= cgs.nitmodMapVoteCount || selected >= NITMOD_MAX_MAPVOTE_MAPS ) {
		return qfalse;
	}
	if( !cgs.nitmodMapVoteMulti ) slot = 1;
	if( slot < 1 || slot > NITMOD_MAX_MAPVOTE_CHOICES ) return qfalse;
	for( i = 0; i < NITMOD_MAX_MAPVOTE_CHOICES; ++i ) {
		if( i != slot - 1 && cgs.nitmodMapVoteSelections[i] == selected ) {
			CG_Printf( "^3Can't vote for the same map twice.\n" );
			return qfalse;
		}
	}
	if( cgs.nitmodMapVoteMulti ) {
		trap_SendClientCommand( va( "mapvote %d %d",
			cgs.nitmodMapVoteIds[selected], slot ) );
	} else {
		trap_SendClientCommand( va( "mapvote %d",
			cgs.nitmodMapVoteIds[selected] ) );
	}
	cgs.nitmodMapVoteSelections[slot - 1] = selected;
	return qtrue;
}

void CG_NitmodMapVoteReset( void ) {
	int i;
	if(BG_PanelButtons_GetFocusButton() == &mapVoteScrollbar) BG_PanelButtons_SetFocusButton(NULL);
	mapVoteScrollbar.data[1] = mapVoteScrollbar.data[2] = 0;
	cgs.nitmodMapVoteListReceived = qfalse;
	cgs.nitmodMapVoteCount = 0;
	cgs.nitmodMapVoteOffset = 0;
	cgs.nitmodMapVoteSelected = -1;
	cgs.nitmodMapVoteRequestTime = 0;
	cgs.nitmodMapVoteTallyTime = 0;
	cgs.nitmodMapVoteLevelshot = 0;
	mapVoteCommandMap = 0;
	for( i = 0; i < NITMOD_MAX_MAPVOTE_CHOICES; ++i )
		cgs.nitmodMapVoteSelections[i] = -1;
}

void CG_NitmodMapVoteRequest( void ) {
	if( !cgs.nitmodMapVoteListReceived ) {
		if( !cgs.nitmodMapVoteRequestTime ||
			cg.time < cgs.nitmodMapVoteRequestTime ||
			(double)cg.time - cgs.nitmodMapVoteRequestTime >= 1000 ) {
			cgs.nitmodMapVoteRequestTime = cg.time;
			trap_SendClientCommand( "immaplist" );
		}
		return;
	}
	if( !cgs.nitmodMapVoteTallyTime ||
		cg.time < cgs.nitmodMapVoteTallyTime ||
		(double)cg.time - cgs.nitmodMapVoteTallyTime >= 1000 ) {
		cgs.nitmodMapVoteTallyTime = cg.time;
		trap_SendClientCommand( "imvotetally" );
	}
}

/* Original CG_parseMapVoteListInfo 0x45230.  The original wire record is:
 * map name, numeric map id, maps since last played, total times played. */
void CG_NitmodParseMapVoteList( void ) {
	int argc = trap_Argc();
	int records;
	int multi;
	int i;

	cgs.nitmodMapVoteCount = 0;
	cgs.nitmodMapVoteListReceived = qfalse;
	cgs.nitmodMapVoteMulti = qfalse;
	memset( cgs.nitmodMapVoteNames, 0, sizeof(cgs.nitmodMapVoteNames) );
	memset( cgs.nitmodMapVoteDisplayNames, 0,
		sizeof(cgs.nitmodMapVoteDisplayNames) );
	memset( cgs.nitmodMapVoteIds, 0, sizeof(cgs.nitmodMapVoteIds) );
	memset( cgs.nitmodMapVoteVotes, 0, sizeof(cgs.nitmodMapVoteVotes) );
	memset( cgs.nitmodMapVoteLastPlayed, 0,
		sizeof(cgs.nitmodMapVoteLastPlayed) );
	memset( cgs.nitmodMapVoteTimesPlayed, 0,
		sizeof(cgs.nitmodMapVoteTimesPlayed) );
	for( i = 0; i < NITMOD_MAX_MAPVOTE_CHOICES; ++i ) {
		cgs.nitmodMapVoteSelections[i] = -1;
	}

	if( argc < 2 || ( ( argc - 2 ) % 4 ) != 0 ) {
		CG_Printf( "^3Nitmod: malformed immaplist (%d arguments)\n", argc );
		return;
	}
	records = ( argc - 2 ) / 4;
	if( records > NITMOD_MAX_MAPVOTE_MAPS ) {
		CG_Printf( "^3Nitmod: immaplist truncated from %d to %d maps\n",
			records, NITMOD_MAX_MAPVOTE_MAPS );
		records = NITMOD_MAX_MAPVOTE_MAPS;
	}
	if( !NITMOD_ParseProtocolInteger(CG_Argv(1), &multi) || multi > 1 ) {
		CG_Printf( "^3Nitmod: malformed immaplist mode\n" );
		return;
	}
	cgs.nitmodMapVoteMulti = multi != 0;
	for( i = 0; i < records; ++i ) {
		arenaInfo_t arena;
		int arg = 2 + i * 4;
		int id, lastPlayed, timesPlayed;

		memset( &arena, 0, sizeof(arena) );
		if( !CG_NitmodMapVoteNameSafe(CG_Argv(arg)) ||
			!NITMOD_ParseProtocolInteger(CG_Argv(arg + 1), &id) ||
			!NITMOD_ParseProtocolSigned(CG_Argv(arg + 2), &lastPlayed) || lastPlayed < -1 ||
			!NITMOD_ParseProtocolInteger(CG_Argv(arg + 3), &timesPlayed) ) {
			CG_Printf( "^3Nitmod: malformed immaplist record %d\n", i + 1 );
			CG_NitmodMapVoteReset();
			return;
		}
		Q_strncpyz( cgs.nitmodMapVoteNames[i], CG_Argv(arg),
			sizeof(cgs.nitmodMapVoteNames[i]) );
		cgs.nitmodMapVoteIds[i] = id;
		cgs.nitmodMapVoteLastPlayed[i] = lastPlayed;
		cgs.nitmodMapVoteTimesPlayed[i] = timesPlayed;
		if( CG_FindArenaInfo( va( "scripts/%s.arena",
			cgs.nitmodMapVoteNames[i] ), cgs.nitmodMapVoteNames[i], &arena ) &&
			arena.longname[0] ) {
			Q_strncpyz( cgs.nitmodMapVoteDisplayNames[i], arena.longname,
				sizeof(cgs.nitmodMapVoteDisplayNames[i]) );
		} else {
			Q_strncpyz( cgs.nitmodMapVoteDisplayNames[i],
				cgs.nitmodMapVoteNames[i],
				sizeof(cgs.nitmodMapVoteDisplayNames[i]) );
		}
	}
	cgs.nitmodMapVoteCount = records;
	cgs.nitmodMapVoteListReceived = qtrue;
	if( records > 0 ) CG_NitmodMapVoteSelect( 0 );
	CG_LocateArena();
}

/* Original CG_parseMapVoteTally 0x454e0: one vote total per listed map. */
void CG_NitmodParseMapVoteTally( void ) {
	int count = trap_Argc() - 1;
	int votes[NITMOD_MAX_MAPVOTE_MAPS];
	int i;

	if( count < 0 ) count = 0;
	if( count > cgs.nitmodMapVoteCount ) count = cgs.nitmodMapVoteCount;
	if( count > NITMOD_MAX_MAPVOTE_MAPS ) count = NITMOD_MAX_MAPVOTE_MAPS;
	for( i = 0; i < count; ++i ) {
		if( !NITMOD_ParseProtocolInteger(CG_Argv(i + 1), &votes[i]) ) {
			CG_Printf( "^3Nitmod: malformed imvotetally record %d\n", i + 1 );
			return;
		}
	}
	for( i = 0; i < count; ++i ) cgs.nitmodMapVoteVotes[i] = votes[i];
}

void CG_NitmodMapVoteList_f( void ) {
	int i;

	if( !cgs.nitmodMapVoteListReceived ) {
		CG_Printf( "^3Map vote list has not been received yet.\n" );
		return;
	}
	CG_Printf( "^7Nitmod map vote%s:\n",
		cgs.nitmodMapVoteMulti ? " (three choices)" : "" );
	for( i = 0; i < cgs.nitmodMapVoteCount; ++i ) {
		CG_Printf( "^3%2d^7  %-28s votes ^2%3d^7  last %d  played %d\n",
			i + 1, cgs.nitmodMapVoteDisplayNames[i],
			cgs.nitmodMapVoteVotes[i], cgs.nitmodMapVoteLastPlayed[i],
			cgs.nitmodMapVoteTimesPlayed[i] );
	}
}

void CG_NitmodMapVote_f( void ) {
	int mapIndex;
	int slot = 1;
	int i;

	if( !cgs.nitmodMapVoteListReceived || trap_Argc() < 2 ) {
		CG_Printf( "usage: nitmapvote <list number> [choice 1-3]\n" );
		return;
	}
	mapIndex = atoi( CG_Argv(1) ) - 1;
	if( mapIndex < 0 || mapIndex >= cgs.nitmodMapVoteCount ) {
		CG_Printf( "^3Invalid map vote number. Use /nitmaplist.\n" );
		return;
	}
	if( cgs.nitmodMapVoteMulti ) {
		if( trap_Argc() >= 3 ) slot = atoi( CG_Argv(2) );
		if( slot < 1 || slot > NITMOD_MAX_MAPVOTE_CHOICES ) {
			CG_Printf( "^3Multi-vote choice must be 1, 2 or 3.\n" );
			return;
		}
		for( i = 0; i < NITMOD_MAX_MAPVOTE_CHOICES; ++i ) {
			if( i != slot - 1 && cgs.nitmodMapVoteSelections[i] == mapIndex ) {
				CG_Printf( "^3Can't vote for the same map twice.\n" );
				return;
			}
		}
		trap_SendClientCommand( va( "mapvote %d %d",
			cgs.nitmodMapVoteIds[mapIndex], slot ) );
		cgs.nitmodMapVoteSelections[slot - 1] = mapIndex;
	} else {
		trap_SendClientCommand( va( "mapvote %d",
			cgs.nitmodMapVoteIds[mapIndex] ) );
		cgs.nitmodMapVoteSelections[0] = mapIndex;
	}
}


/* Original button records: 0x131240, 0x1311e0, 0x131180, 0x131120.
 * Visual rank 1/2/3 sends protocol slot 3/2/1 (weighted choices). */
qboolean CG_NitmodMapVoteButton(int row, nitmodMapVoteButton_t *button) {
    int selected;
    qboolean revote;
    if(!button) return qfalse;
    memset(button, 0, sizeof(*button));
    if(!cg.snap || row < 0 || row >= (cgs.nitmodMapVoteMulti ? 3 : 1)) return qfalse;
    button->rect.x = 15; button->rect.y = 296 + row * 20;
    button->rect.w = 64; button->rect.h = 16;
    button->slot = cgs.nitmodMapVoteMulti ? 3 - row : 1;
    selected = cgs.nitmodMapVoteSelections[button->slot - 1];
    revote = cgs.nitmodMapVoteMulti ? selected != -1 : (cg.snap->ps.eFlags & EF_VOTED) != 0;
    if(revote && selected >= 0 && selected < cgs.nitmodMapVoteCount && selected < NITMOD_MAX_MAPVOTE_MAPS)
        Q_strncpyz(button->mapName, cgs.nitmodMapVoteDisplayNames[selected], sizeof(button->mapName));
    if(cgs.nitmodMapVoteMulti)
        Com_sprintf(button->label, sizeof(button->label), "^3%d: %s", row + 1, revote ? "^1RE-VOTE" : "^3VOTE");
    else Q_strncpyz(button->label, revote ? "^1RE-VOTE" : "^3VOTE", sizeof(button->label));
    return qtrue;
}

static qboolean CG_MapVoteInside(float x, float y, const rectDef_t *rect) {
    return x >= rect->x && y >= rect->y && x < rect->x + rect->w && y < rect->y + rect->h;
}

void CG_NitmodMapVoteDraw( void ) {
    static const vec4_t panel = {0, 0, 0, .8f}, selectedColor = {1, 1, 1, .3f};
    static vec4_t textColor = {.6f, .6f, .6f, 1};
    static const vec4_t normal = {.3f, .3f, .3f, .4f}, hover = {.5f, .5f, .5f, .4f};
    static const vec4_t border = {.1f, .1f, .1f, .5f};
    static vec4_t bright = {.9f, .9f, .9f, 1};
    int count = cgs.nitmodMapVoteCount, first = cgs.nitmodMapVoteOffset, end, i;
    float y, infoY = 81;
    char cycle[64];
    if(count < 0) count = 0;
    if(count > NITMOD_MAX_MAPVOTE_MAPS) count = NITMOD_MAX_MAPVOTE_MAPS;
    if(first < 0) first = 0;
    if(first > count) first = count;
    end = first + NITMOD_MAPVOTE_VISIBLE;
    if(end > count) end = count;
    CG_FillRect(10, 30, 620, 326, panel);
    CG_DrawRect_FixedBorder(10, 30, 620, 326, 1, colorMdGrey);
    CG_Text_Paint_Ext(24, 48, .25f, .25f, colorWhite, "MAP VOTE", 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2);
    if(!cgs.nitmodMapVoteListReceived) {
        CG_Text_Paint_Ext(24, 72, .2f, .2f, colorWhite, "Waiting for map list...", 0, 0, 0, &cgs.media.limboFont2);
        return;
    }
    CG_Text_Paint_Ext(15, 56, .2f, .2f, textColor, "Name", 0, 0, 0, &cgs.media.limboFont2);
    CG_Text_Paint_Ext(215, 56, .2f, .2f, textColor, "Score", 0, 0, 0, &cgs.media.limboFont2);
    if(CG_NitmodMapCycleText(NITMOD_GameState(), qfalse, cycle, sizeof(cycle)))
        CG_Text_Paint_Ext(290, 66, .2f, .2f, textColor, cycle, 0, 0, 0, &cgs.media.limboFont2);
    if(CG_NitmodMapCycleReset(NITMOD_GameState())) {
        CG_Text_Paint_Ext(290, 81, .2f, .2f, textColor, "^1XP Resetting!", 0, 0, 0, &cgs.media.limboFont2);
        infoY += 15;
    }
    CG_Debriefing_Scrollbar_Draw(&mapVoteScrollbar);
    y = NITMOD_MAPVOTE_LIST_Y + NITMOD_MAPVOTE_ROW_H;
    for(i = first; i < end; ++i, y += NITMOD_MAPVOTE_ROW_H) {
        if(i == cgs.nitmodMapVoteSelected) CG_FillRect(15, y - 10, 250, 12, selectedColor);
        CG_Text_Paint_Ext(15, y, .2f, .2f, textColor, cgs.nitmodMapVoteDisplayNames[i],
            0, 30, 0, &cgs.media.limboFont2);
        CG_Text_Paint_Ext(225, y, .2f, .2f, textColor,
            va("%s%d", cgs.nitmodMapVoteVotes[i] ? "^7" : "", cgs.nitmodMapVoteVotes[i]),
            0, 0, 0, &cgs.media.limboFont2);
    }
    i = cgs.nitmodMapVoteSelected;
    if(i >= 0 && i < count) {
        if(cgs.nitmodMapVoteLevelshot) CG_DrawPic(524, 50, 96, 72, cgs.nitmodMapVoteLevelshot);
        if(mapVoteCommandMap) CG_DrawPic(428, 154, 192, 192, mapVoteCommandMap);
        CG_Text_Paint_Ext(290, infoY, .2f, .2f, textColor,
            va("Last Played            : %s", cgs.nitmodMapVoteLastPlayed[i] == -1 ? "^1Never" :
                va("^3%d ^7maps ago", cgs.nitmodMapVoteLastPlayed[i])), 0, 0, 0, &cgs.media.limboFont2);
        CG_Text_Paint_Ext(290, infoY + 15, .2f, .2f, textColor,
            va("Total Accumulated Votes: ^3%d", cgs.nitmodMapVoteTimesPlayed[i]), 0, 0, 0, &cgs.media.limboFont2);
    }
    for(i = 0; i < 3; ++i) {
        nitmodMapVoteButton_t button;
        qboolean over;
        float width;
        if(!CG_NitmodMapVoteButton(i, &button)) continue;
        over = CG_MapVoteInside(cgs.cursorX, cgs.cursorY, &button.rect);
        CG_FillRect(button.rect.x, button.rect.y, button.rect.w, button.rect.h, over ? hover : normal);
        CG_DrawRect_FixedBorder(button.rect.x, button.rect.y, button.rect.w, button.rect.h, 1, border);
        width = CG_Text_Width_Ext(button.label, .2f, 0, &cgs.media.limboFont2);
        CG_Text_Paint_Ext(button.rect.x + (button.rect.w + 2 - width) * .5f, button.rect.y + 11,
            .19f, .19f, over ? bright : textColor, button.label, 0, 0, 0, &cgs.media.limboFont2);
        if(button.mapName[0]) CG_Text_Paint_Ext(89, button.rect.y + 12, .2f, .2f, textColor,
            button.mapName, 0, 30, 0, &cgs.media.limboFont2);
    }
}

qboolean CG_NitmodMapVoteKeyEvent( int key, qboolean down ) {
    int count = cgs.nitmodMapVoteCount, maxOffset, row;
    rectDef_t list = {15, 56, 250, NITMOD_MAPVOTE_VISIBLE * 12};
    if(!down) {
        if(key == K_MOUSE1 && BG_PanelButtons_GetFocusButton() == &mapVoteScrollbar) {
            CG_Debriefing_Scrollbar_KeyUp(&mapVoteScrollbar, key);
            return qtrue;
        }
        return qfalse;
    }
    if(count < 0) count = 0;
    if(count > NITMOD_MAX_MAPVOTE_MAPS) count = NITMOD_MAX_MAPVOTE_MAPS;
    maxOffset = count > NITMOD_MAPVOTE_VISIBLE ? count - NITMOD_MAPVOTE_VISIBLE : 0;
    if(cgs.nitmodMapVoteOffset < 0) cgs.nitmodMapVoteOffset = 0;
    if(cgs.nitmodMapVoteOffset > maxOffset) cgs.nitmodMapVoteOffset = maxOffset;
    if(key == K_MWHEELUP || key == K_UPARROW) {
        if(cgs.nitmodMapVoteOffset > 0) --cgs.nitmodMapVoteOffset;
        return qtrue;
    }
    if(key == K_MWHEELDOWN || key == K_DOWNARROW) {
        if(cgs.nitmodMapVoteOffset < maxOffset) ++cgs.nitmodMapVoteOffset;
        return qtrue;
    }
    if(key == K_ENTER) return CG_NitmodMapVoteCast(cgs.nitmodMapVoteMulti ? 3 : 1);
    if(key != K_MOUSE1) return qfalse;
    if(CG_MapVoteInside(cgs.cursorX, cgs.cursorY, &mapVoteScrollbar.rect)) {
        CG_Debriefing_ScrollCheckOffset(&mapVoteScrollbar);
        CG_Debriefing_Scrollbar_KeyDown(&mapVoteScrollbar, key);
        return qtrue;
    }
    if(CG_MapVoteInside(cgs.cursorX, cgs.cursorY, &list)) {
        row = (cgs.cursorY - 56) / 12 + cgs.nitmodMapVoteOffset;
        if(row >= count) return qfalse;
        if(row != cgs.nitmodMapVoteSelected) CG_NitmodMapVoteSelect(row);
        return qtrue;
    }
    for(row = 0; row < 3; ++row) {
        nitmodMapVoteButton_t button;
        if(CG_NitmodMapVoteButton(row, &button) && CG_MapVoteInside(cgs.cursorX, cgs.cursorY, &button.rect))
            return CG_NitmodMapVoteCast(button.slot);
    }
    return qfalse;
}
