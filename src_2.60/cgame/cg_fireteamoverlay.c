/******************************************************************************
***** teh firetams! (sic)
****/

#include "cg_local.h"
#include "cg_nitmod_locations.h"
#include "cg_nitmod_hud.h"
#include "cg_nitmod_config.h"
#include "../game/nitmod_protocol.h"

/******************************************************************************
***** Defines, constants, etc 
****/

static int sortedFireTeamClients[MAX_CLIENTS];

fireteamData_t *CG_IsOnFireteam(int clientNum) {
    if(clientNum < 0 || clientNum >= MAX_CLIENTS) return NULL;
    if(NITMOD_UsesOriginalProtocol() &&
       (cgs.gametype == 8 || cgs.clientinfo[clientNum].team == TEAM_SPECTATOR)) return NULL;
    return cgs.clientinfo[clientNum].fireteamData;
}

/* Decode into a temporary: malformed masks must never publish half a roster. */
qboolean CG_DecodeFireteam(const char *text, qboolean original, fireteamData_t *out) {
    fireteamData_t decoded;
    const char *mask;
    int i, bit, value;
    if(!out || !text || !*text) return qfalse;
    memset(&decoded, 0, sizeof(decoded));
    if(!NITMOD_ParseProtocolInteger(Info_ValueForKey(text, original ? "n" : "id"), &decoded.ident) ||
       decoded.ident < 0 || decoded.ident >= MAX_FIRETEAMS / 2 ||
       !NITMOD_ParseProtocolInteger(Info_ValueForKey(text, "l"), &decoded.leader) ||
       decoded.leader < 0 || decoded.leader >= MAX_CLIENTS) return qfalse;
    mask = Info_ValueForKey(text, "c");
    if(strlen(mask) != 16) return qfalse;
    for(i = 0; i < 16; ++i) {
        if(mask[i] >= '0' && mask[i] <= '9') value = mask[i] - '0';
        else if(mask[i] >= 'a' && mask[i] <= 'f') value = mask[i] - 'a' + 10;
        else if(mask[i] >= 'A' && mask[i] <= 'F') value = mask[i] - 'A' + 10;
        else return qfalse;
        for(bit = 0; bit < 4; ++bit) decoded.joinOrder[(15 - i) * 4 + bit] = !!(value & (1 << bit));
    }
    if(!decoded.joinOrder[decoded.leader]) return qfalse;
    decoded.inuse = qtrue;
    *out = decoded;
    return qtrue;
}

/* Original CG_DrawActiveFrame reselects the six displayed members each
 * frame. Disabled mode leaves manual selections alone; it does not clear. */
int CG_NitmodAutoSelectFireteam(void) {
    int i;
    if(!NITMOD_UsesOriginalProtocol() || !cg_FTAutoSelect.integer || cg.clientNum < 0 ||
       cg.clientNum >= MAX_CLIENTS || !CG_IsOnFireteam(cg.clientNum)) return 0;
    for(i = 0; i < 6; ++i) {
        clientInfo_t *ci = CG_SortedFireTeamPlayerForPosition(i, 6);
        if(!ci) break;
        ci->selected = qtrue;
    }
    return i;
}

/******************************************************************************
***** Support Routines
****/

int QDECL CG_SortFireTeam( const void *a, const void *b ) {
	clientInfo_t	*ca, *cb;
	int				cna, cnb;

	cna = *(int*)a;
	cnb = *(int*)b;

	if(cna == cnb) return 0;
	{
		qboolean aMember = CG_IsOnSameFireteam(cna, cg.clientNum) != NULL;
		qboolean bMember = CG_IsOnSameFireteam(cnb, cg.clientNum) != NULL;
		if(aMember != bMember) return aMember ? -1 : 1;
		if(!aMember) return cna < cnb ? -1 : 1;
	}

	ca = &cgs.clientinfo[cna];
	cb = &cgs.clientinfo[cnb];

	// Not on our team, so shove back
	if ( !CG_IsOnSameFireteam( cnb, cg.clientNum ) ) {
		return -1;
	}
	if ( !CG_IsOnSameFireteam( cna, cg.clientNum ) ) {
		return 1;
	}

	// Leader comes first
	if ( CG_IsFireTeamLeader( cna ) ) {
		return -1;
	}
	if ( CG_IsFireTeamLeader( cnb ) ) {
		return 1;
	}

	// Then higher ranks
	if ( ca->rank > cb->rank ) {
		return -1;
	}
	if ( cb->rank > ca->rank ) {
		return 1;
	}

	// Then score
/*	if ( ca->score > cb->score ) {
		return -1;
	}
	if ( cb->score > ca->score ) {
		return 1;
	}*/ // not atm

	return 0;
}

// Sorts client's fireteam by leader then rank
void CG_SortClientFireteam() {
	int i;

	for(i = 0; i < MAX_CLIENTS; i++) {
		sortedFireTeamClients[i] = i;
	}

	qsort( sortedFireTeamClients, MAX_CLIENTS, sizeof(sortedFireTeamClients[0]), CG_SortFireTeam );

/*	for(i = 0; i < MAX_CLIENTS; i++) {
		CG_Printf( "%i ", sortedFireTeamClients[i] );
	}

	CG_Printf( "\n" );*/
}

// Parses fireteam servercommand
void CG_ParseFireteams(void) {
    int i, j;
    for(i = 0; i < MAX_CLIENTS; ++i) cgs.clientinfo[i].fireteamData = NULL;
    memset(cg.fireTeams, 0, sizeof(cg.fireTeams));
    for(i = 0; i < MAX_FIRETEAMS; ++i) {
        if(!CG_DecodeFireteam(NITMOD_AssetConfigString(CS_FIRETEAMS + i),
            NITMOD_UsesOriginalProtocol(), &cg.fireTeams[i])) continue;
        for(j = 0; j < MAX_CLIENTS; ++j) {
            if(cg.fireTeams[i].joinOrder[j]) cgs.clientinfo[j].fireteamData = &cg.fireTeams[i];
        }
    }
    CG_SortClientFireteam();
}

// Fireteam that both specified clients are on, if they both are on the same team
fireteamData_t* CG_IsOnSameFireteam( int clientNum, int clientNum2 ) {
	if(CG_IsOnFireteam(clientNum) == CG_IsOnFireteam(clientNum2)) {
		return CG_IsOnFireteam(clientNum);
	}

	return NULL;
}

// Fireteam that specified client is leader of, or NULL if none
fireteamData_t* CG_IsFireTeamLeader( int clientNum ) {
	fireteamData_t* f;

	if(!(f = CG_IsOnFireteam(clientNum))) {
		return NULL;
	}

	if(f->leader != clientNum) {
		return NULL;
	}

	return f ;
}

// Client, not on a fireteam, not sorted, but on your team
clientInfo_t* CG_ClientInfoForPosition(int pos, int max) {
	int i, cnt = 0;
	if(pos < 0 || pos >= max || cg.clientNum < 0 || cg.clientNum >= MAX_CLIENTS) return NULL;

	for(i = 0; i < MAX_CLIENTS && cnt < max; i++) {
		if(cg.clientNum != i && cgs.clientinfo[i].infoValid && !CG_IsOnFireteam( i ) && cgs.clientinfo[cg.clientNum].team == cgs.clientinfo[i].team ) {
			if(cnt == pos) {
				return &cgs.clientinfo[i];
			}
			cnt++;
		}
	}

	return NULL;
}

// Fireteam, that's on your same team
fireteamData_t* CG_FireTeamForPosition( int pos, int max ) {
	int i, cnt = 0;
	if(pos < 0 || pos >= max || cg.clientNum < 0 || cg.clientNum >= MAX_CLIENTS) return NULL;

	for(i = 0; i < MAX_FIRETEAMS && cnt < max; i++) {
		if(cg.fireTeams[i].inuse && cg.fireTeams[i].leader >= 0 && cg.fireTeams[i].leader < MAX_CLIENTS && cgs.clientinfo[cg.fireTeams[i].leader].team == cgs.clientinfo[cg.clientNum].team) {
			if(cnt == pos) {				
				return &cg.fireTeams[i];
			}
			cnt++;
		}
	}

	return NULL;
}

// Client, not sorted by rank, on CLIENT'S fireteam
clientInfo_t* CG_FireTeamPlayerForPosition(int pos, int max) {
	int i, cnt = 0;
	fireteamData_t* f = CG_IsOnFireteam(cg.clientNum);

	if(!f || pos < 0 || pos >= max) {
		return NULL;
	}

	for(i = 0; i < MAX_CLIENTS && cnt < max; i++) {
		if(cgs.clientinfo[i].infoValid && cgs.clientinfo[cg.clientNum].team == cgs.clientinfo[i].team ) {
			if(!(f == CG_IsOnFireteam(i))) {
				continue;
			}

			if(cnt == pos) {
				return &cgs.clientinfo[i];
			}
			cnt++;
		}
	}

	return NULL;
}

// Client, sorted by rank, on CLIENT'S fireteam
clientInfo_t* CG_SortedFireTeamPlayerForPosition(int pos, int max) {
	int i, cnt = 0;
	fireteamData_t* f = CG_IsOnFireteam(cg.clientNum);

	if(!f || pos < 0 || pos >= max) {
		return NULL;
	}

	for(i = 0; i < MAX_CLIENTS && cnt < max; i++) {
		if(!(f == CG_IsOnFireteam(sortedFireTeamClients[i]))) {
			return NULL;
		}

		if(cnt == pos) {
			return &cgs.clientinfo[sortedFireTeamClients[i]];
		}
		cnt++;
	}

	return NULL;
}

/******************************************************************************
***** Main Functions
****/

#define FT_BAR_YSPACING 2.f
#define FT_BAR_HEIGHT 10.f
/* Original CG_DrawFireTeamOverlay: compact class icons, fourteen-character
 * names, health and a measured location column. No rank/weapon columns. */
static void CG_DrawOriginalFireTeamOverlay(const rectDef_t *rect) {
    clientInfo_t *members[6];
    char locations[6][128], text[64];
    fireteamData_t *team = CG_IsOnFireteam(cg.clientNum);
    vec4_t background, border, header = {0, 0, 0, .8f}, rowColor = {0, 0, 0, .2f};
    nitmodHudAnchor_t previous;
    int i, count = 0, limit = cg_locationMaxChars.integer;
    float x, y, width = 0, candidate, healthX;
    vec3_t location;
    vec_t *healthColor;
    if(!rect || !team || team->ident < 0 || team->ident >= MAX_FIRETEAMS / 2) return;
    if(limit < 0) limit = 0;
    if(limit > 127) limit = 127;
    for(i = 0; i < 6; ++i) {
        members[i] = CG_SortedFireTeamPlayerForPosition(i, 6);
        if(!members[i]) break;
        VectorCopy(members[i]->location, location);
        CG_NitmodLocationText(locations[i], sizeof(locations[i]), location, 1);
        candidate = 82 + (members[i]->health == 0 ? 7 : 0) +
            CG_Text_Width_Ext(locations[i], .2f, limit, &cgs.media.limboFont2);
        if(candidate > width) width = candidate;
        ++count;
    }
    if(!count) return;
    width += 40;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_LEFT);
    x = (int)rect->x; y = (int)(rect->y + 1);
    CG_NitmodHudColors(background, border);
    CG_DrawRect(x, y, width, 16 + 12 * count, 1, border);
    CG_FillRect(x + 1, y + 1, width - 2, 14 + 12 * count, background);
    CG_FillRect(x + 2, y + 2, width - 4, 12, header);
    Com_sprintf(text, sizeof(text), "Fireteam: %s", bg_fireteamNames[team->ident]);
    Q_strupr(text);
    CG_Text_Paint_Ext(x + 5, y + 12, .18f, .18f, colorWhite, text, 0, 0, 0, &cgs.media.limboFont1);
    for(i = 0; i < count; ++i) {
        clientInfo_t *ci = members[i];
        int skill = ci->cls >= PC_SOLDIER && ci->cls <= PC_COVERTOPS ? BG_ClassSkillForClass(ci->cls) : -1;
        float rowY = y + 14 + 12 * i;
        CG_FillRect(x + 2, rowY + 2, width - 4, 10, rowColor);
        if(skill >= 0 && skill < SK_NUM_SKILLS)
            CG_DrawPic(x + 4, rowY + 2, 10, 10, cgs.media.skillPics[skill]);
        CG_Text_Paint_Ext(x + 14, rowY + 10, .17f, .17f, colorWhite, ci->name, 0, 14, 3, &cgs.media.limboFont2);
        healthX = x + 94;
        healthColor = ci->health > 80 ? colorWhite : ci->health > 0 ? colorYellow : colorRed;
        if(ci->health == 0) {
            CG_Text_Paint_Ext(healthX, rowY + 10, .17f, .17f,
                cg.time % 500 < 251 ? colorRed : colorWhite, "*", 0, 0, 3, &cgs.media.limboFont2);
            healthX += 7;
            healthColor = cg.time % 500 < 251 ? colorWhite : colorRed;
        }
        Com_sprintf(text, sizeof(text), "%i", ci->health > 0 ? ci->health : 0);
        CG_Text_Paint_Ext(healthX, rowY + 10, .17f, .17f, healthColor, text, 0, 0, 3, &cgs.media.limboFont2);
        CG_Text_Paint_Ext(healthX + 24, rowY + 10, .17f, .17f, colorWhite, locations[i], 0, limit, 3, &cgs.media.limboFont2);
    }
    trap_R_SetColor(NULL);
    CG_NitmodHudAnchor(previous);
}

void CG_DrawFireTeamOverlay( rectDef_t* rect ) {
	int x = rect->x;
	int y = rect->y + 1;	// +1, jitter it into place in 1024 :)
	float h;
	clientInfo_t* ci = NULL;
	char buffer[64];
	fireteamData_t* f = NULL;
	int i;
	vec4_t clr1 =	{ .16f,		.2f,	.17f,	.8f };
	vec4_t clr2 =	{ 0.f,		0.f,		0.f,		.2f };
	vec4_t clr3 =	{ 0.25f,		0.f,		0.f,		153/255.f };
	vec4_t tclr =	{ 0.6f,		0.6f,		0.6f,		1.0f };
	vec4_t bgColor		= { 0.0f, 0.0f, 0.0f, 0.6f };		// window
	vec4_t borderColor	= { 0.5f, 0.5f, 0.5f, 0.5f };	// window

	if(NITMOD_UsesOriginalProtocol()) { CG_DrawOriginalFireTeamOverlay(rect); return; }

	if(!(f = CG_IsOnFireteam( cg.clientNum ))) {
		return;
	}

	h = 12 + 2 + 2;
	for(i = 0; i < 6; i++) {
		ci = CG_SortedFireTeamPlayerForPosition( i, 6 );
		if(!ci) {
			break;;
		}

		h += FT_BAR_HEIGHT + FT_BAR_YSPACING;
	}

	CG_NitmodHudColors(bgColor, borderColor);
	CG_DrawRect( x, y, 204, h, 1, borderColor);
	CG_FillRect( x + 1, y + 1, 204 - 2, h - 2, bgColor);

	x += 2;
	y += 2;

	CG_FillRect( x, y, 204 - 4, 12, clr1 );

	sprintf( buffer, "Fireteam: %s", bg_fireteamNames[f->ident] );
	Q_strupr( buffer );
	CG_Text_Paint_Ext( x + 3, y + FT_BAR_HEIGHT, .19f, .19f, tclr, buffer, 0, 0, 0, &cgs.media.limboFont1 );

	x += 2;
	//y += 2;

	for(i = 0; i < 6; i++) {
		y += FT_BAR_HEIGHT + FT_BAR_YSPACING;
		x = rect->x + 2;

		ci = CG_SortedFireTeamPlayerForPosition( i, 6 );
		if(!ci) {
			break;;
		}
		
		if( ci->selected ) {
			CG_FillRect( x, y + FT_BAR_YSPACING, 204 - 4, FT_BAR_HEIGHT, clr3 );
		} else {
			CG_FillRect( x, y + FT_BAR_YSPACING, 204 - 4, FT_BAR_HEIGHT, clr2 );
		}

		x += 4;
				
		CG_Text_Paint_Ext( x, y + FT_BAR_HEIGHT, .2f, .2f, tclr, BG_ClassLetterForNumber( ci->cls ), 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2 );	
		x += 10;
		
		CG_Text_Paint_Ext( x, y + FT_BAR_HEIGHT, .2f, .2f, tclr, ci->team == TEAM_AXIS ? miniRankNames_Axis[ci->rank] : miniRankNames_Allies[ci->rank], 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2 );	
		x += 22;
		
		CG_Text_Paint_Ext(x, y + FT_BAR_HEIGHT, .2f, .2f, tclr, ci->name, 0, 17, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2 );
		x += 90;

/*		CG_DrawPic(x + 2, y + 2, FT_BAR_HEIGHT - 4, FT_BAR_HEIGHT - 4, cgs.media.movementAutonomyIcons[0]);
		x += FT_BAR_HEIGHT;

		CG_DrawPic(x + 2, y + 2, FT_BAR_HEIGHT - 4, FT_BAR_HEIGHT - 4, cgs.media.weaponAutonomyIcons[0]);
		x += FT_BAR_HEIGHT;
		x += 4;*/

/*		if( isLeader ) {
			CG_Text_Paint_Ext(x, y + FT_BAR_HEIGHT, .2f, .2f, tclr, va("%i", i+4), 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2 );
		}*/
		x += 20;
		
		if( ci->health > 80 ) {
			CG_Text_Paint_Ext(x, y + FT_BAR_HEIGHT,  .2f, .2f, tclr, va("%i", ci->health < 0 ? 0 : ci->health ), 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2 );
		} else if( ci->health > 0 ) {
			CG_Text_Paint_Ext(x, y + FT_BAR_HEIGHT,  .2f, .2f, colorYellow, va("%i", ci->health < 0 ? 0 : ci->health ), 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2 );
		} else {
			CG_Text_Paint_Ext(x, y + FT_BAR_HEIGHT,  .2f, .2f, colorRed, va("%i", ci->health < 0 ? 0 : ci->health ), 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2 );
		}
		//x += 20;

		{
			vec3_t loc;
			char location[128];
			char *s;

			loc[0] = ci->location[0];
			loc[1] = ci->location[1];
			loc[2] = ci->location[2];

			CG_NitmodLocationText(location, sizeof(location), loc, 1);
			s = va( "^3(%s)", location );

			x = rect->x + ( 204 - 4 - CG_Text_Width_Ext( s, .2f, 0, &cgs.media.limboFont2 ) );

			CG_Text_Paint_Ext( x, y + FT_BAR_HEIGHT,  .2f, .2f, tclr, s, 0, cg_locationMaxChars.integer, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2 );
		}
	}
}

qboolean CG_FireteamGetBoxNeedsButtons() {
	if ( cgs.applicationEndTime > cg.time ) {
		if( cgs.applicationClient < 0 || cgs.applicationClient >= MAX_CLIENTS ) {
			return qfalse;
		}
		return qtrue;
	}

	if ( cgs.invitationEndTime > cg.time ) {
		if( cgs.invitationClient < 0 || cgs.invitationClient >= MAX_CLIENTS ) {
			return qfalse;
		}
		return qtrue;
	}

	if ( cgs.propositionEndTime > cg.time ) {
		if( cgs.propositionClient < 0 || cgs.propositionClient >= MAX_CLIENTS ||
		    cgs.propositionClient2 < 0 || cgs.propositionClient2 >= MAX_CLIENTS ) {
			return qfalse;
		}
		return qtrue;
	}

	return qfalse;
}

const char* CG_FireteamGetBoxText() {
	if ( cgs.applicationEndTime > cg.time ) {
		if ( cgs.applicationClient == -1 ) {
			return "Sent";
		}

		if ( cgs.applicationClient == -2 ) {
			return "Failed";
		}

		if ( cgs.applicationClient == -3 ) {
			return "Accepted";
		}

		if ( cgs.applicationClient == -4 ) {
			return "Sent";
		}

		if( cgs.applicationClient < 0 || cgs.applicationClient >= MAX_CLIENTS ) {
			return NULL;
		}

		return va("Accept application from %s?", cgs.clientinfo[cgs.applicationClient].name);
	}

	if ( cgs.invitationEndTime > cg.time ) {
		if ( cgs.invitationClient == -1 ) {
			return "Sent";
		}

		if ( cgs.invitationClient == -2 ) {
			return "Failed";
		}

		if ( cgs.invitationClient == -3 ) {
			return "Accepted";
		}

		if ( cgs.invitationClient == -4 ) {
			return "Sent";
		}

		if( cgs.invitationClient < 0 || cgs.invitationClient >= MAX_CLIENTS ) {
			return NULL;
		}

		return va("Accept invitiation from %s?", cgs.clientinfo[cgs.invitationClient].name);
	}

	if ( cgs.propositionEndTime > cg.time ) {
		if ( cgs.propositionClient == -1 ) {
			return "Sent";
		}

		if ( cgs.propositionClient == -2 ) {
			return "Failed";
		}

		if ( cgs.propositionClient == -3 ) {
			return "Accepted";
		}

		if ( cgs.propositionClient == -4 ) {
			return "Sent";
		}

		if( cgs.propositionClient < 0 || cgs.propositionClient >= MAX_CLIENTS ||
		    cgs.propositionClient2 < 0 || cgs.propositionClient2 >= MAX_CLIENTS ) {
			return NULL;
		}

		return va( "Accept %s's proposition to invite %s to join your fireteam?", cgs.clientinfo[cgs.propositionClient2].name, cgs.clientinfo[cgs.propositionClient].name);
	}

	return NULL;
}

qboolean CG_FireteamHasClass( int classnum, qboolean selectedonly ) {
	fireteamData_t* ft;
	int i;

	if( !(ft = CG_IsOnFireteam( cg.clientNum )) ) {
		return qfalse;
	}

	for( i = 0; i < MAX_CLIENTS; i++ ) {
/*		if( i == cgs.clientinfo ) {
			continue;
		}*/

		if( !cgs.clientinfo[ i ].infoValid ) {
			continue;
		}

		if( ft != CG_IsOnFireteam( i ) ) {
			continue;
		}

		if( cgs.clientinfo[ i ].cls != classnum ) {
			continue;
		}

		if( selectedonly && !cgs.clientinfo[ i ].selected ) {
			continue;
		}

		return qtrue;
	}

	return qfalse;
}

const char* CG_BuildSelectedFirteamString( void ) {
	char buffer[256];
	clientInfo_t* ci;
	int cnt = 0;
	int i;

	*buffer = '\0';
	for( i = 0; i < 6; i++ ) {
		ci = CG_SortedFireTeamPlayerForPosition( i, 6 );
		if( !ci ) {
			break;
		}

		if( !ci->selected ) {
			continue;
		}

		cnt++;

		Q_strcat( buffer, sizeof( buffer ), va( "%i ", ci->clientNum ) );
	}

	if( cnt == 0 ) {
		return "0";
	}

	if( !cgs.clientinfo[cg.clientNum].selected ) {
		Q_strcat( buffer, sizeof( buffer ), va( "%i ", cg.clientNum ) );
		cnt++;
	}
	
	return va( "%i %s", cnt, buffer );
}
