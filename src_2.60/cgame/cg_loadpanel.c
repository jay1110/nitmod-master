#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "../ui/ui_shared.h"

extern displayContextDef_t *DC;

qboolean	bg_loadscreeninited =	qfalse;
qboolean	bg_loadscreeninteractive;
fontInfo_t	bg_loadscreenfont1;
fontInfo_t	bg_loadscreenfont2;
qhandle_t	bg_axispin;
qhandle_t	bg_alliedpin;
qhandle_t	bg_neutralpin;
qhandle_t	bg_pin;

qhandle_t	bg_filter_pb;
qhandle_t	bg_filter_ff;
qhandle_t	bg_filter_hw;
qhandle_t	bg_filter_lv;
qhandle_t	bg_filter_al;
qhandle_t	bg_filter_bt;

qhandle_t	bg_mappic;

// panel_button_text_t FONTNAME = { SCALEX, SCALEY, COLOUR, STYLE, FONT };

panel_button_text_t missiondescriptionTxt = {
	0.2f, 0.2f,
	{ 0.0f, 0.0f, 0.0f, 1.f },
	0, 0,
	&bg_loadscreenfont2,
};

panel_button_text_t missiondescriptionHeaderTxt = {
	0.2f, 0.2f,
	{ 0.0f, 0.0f, 0.0f, 0.8f },
	 0,ITEM_ALIGN_CENTER,
	&bg_loadscreenfont2,
};

panel_button_text_t campaignpheaderTxt = {
	0.2f, 0.2f,
	{ 1.0f, 1.0f, 1.0f, 0.6f },
	0, 0,
	&bg_loadscreenfont2,
};

panel_button_text_t campaignpTxt = {
	0.30f, 0.30f,
	{ 1.0f, 1.0f, 1.0f, 0.6f },
	0, 0,
	&bg_loadscreenfont2,
};

panel_button_text_t loadScreenMeterBackTxt = {
	0.22f, 0.22f,
	{ 0.1f, 0.1f, 0.1f, 0.8f },
	 0, ITEM_ALIGN_CENTER,
	&bg_loadscreenfont2,
};

panel_button_t loadScreenMap = {
	"gfx/loading/camp_map",
	NULL,
	{ 0, 0, 440, 480 },	// shouldn't this be square?? // Gordon: no, the map is actually WIDER that tall, which makes it even worse...
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	NULL,	/* font		*/
	NULL,	/* keyDown	*/
	NULL,	/* keyUp	*/	
	BG_PanelButtonsRender_Img,
	NULL,
};

panel_button_t loadScreenBack = {
	"gfx/loading/camp_side",
	NULL,
	{ 440, 0, 200, 480 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	NULL,	/* font		*/
	NULL,	/* keyDown	*/
	NULL,	/* keyUp	*/	
	BG_PanelButtonsRender_Img,
	NULL,
};

panel_button_t loadScreenPins = {
	NULL,
	NULL,
	{ 0, 0, 640, 480 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	NULL,	/* font		*/
	NULL,	/* keyDown	*/
	NULL,	/* keyUp	*/	
	CG_LoadPanel_RenderCampaignPins,
	NULL,
};

panel_button_t missiondescriptionPanelHeaderText = {
	NULL,
	"***TOP SECRET***",
	{ 440, 72, 200, 32 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&missiondescriptionHeaderTxt,	/* font		*/
	NULL,					/* keyDown	*/
	NULL,					/* keyUp	*/
	BG_PanelButtonsRender_Text,
	NULL,
};

panel_button_t missiondescriptionPanelText = {
	NULL,
	NULL,
	{ 460, 84, 160, 232 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&missiondescriptionTxt,	/* font		*/
	NULL,					/* keyDown	*/
	NULL,					/* keyUp	*/
	CG_LoadPanel_RenderMissionDescriptionText,
	NULL,
};

panel_button_t campaignheaderPanelText = {
	NULL,
	NULL,
	{ 456, 24, 152, 232 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&campaignpheaderTxt,	/* font		*/
	NULL,					/* keyDown	*/
	NULL,					/* keyUp	*/
	CG_LoadPanel_RenderCampaignTypeText,
	NULL,
};

panel_button_t campaignPanelText = {
	NULL,
	NULL,
	{ 464, 40, 152, 232 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&campaignpTxt,			/* font		*/
	NULL,					/* keyDown	*/
	NULL,					/* keyUp	*/
	CG_LoadPanel_RenderCampaignNameText,
	NULL,
};

panel_button_t loadScreenMeterBack = {
	"gfx/loading/progressbar_back",
	NULL,
	{ 440+26, 480-30+1, 200-56, 20 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	NULL,	/* font		*/
	NULL,	/* keyDown	*/
	NULL,	/* keyUp	*/	
	BG_PanelButtonsRender_Img,
	NULL,
};

panel_button_t loadScreenMeterBack2 = {
	"gfx/loading/progressbar",
	NULL,
	{ 440+26, 480-30+1, 200-56, 20 },
	{ 1, 255, 0, 0, 255, 0, 0, 0 },
	NULL,	/* font		*/
	NULL,	/* keyDown	*/
	NULL,	/* keyUp	*/	
	CG_LoadPanel_RenderLoadingBar,
	NULL,
};

panel_button_t loadScreenMeterBackText = {
	NULL,
	"LOADING",
	{ 440+28, 480-28+12+1, 200-56-2, 16 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&loadScreenMeterBackTxt,	/* font		*/
	NULL,						/* keyDown	*/
	NULL,						/* keyUp	*/	
	BG_PanelButtonsRender_Text,
	NULL,
};

panel_button_t* loadpanelButtons[] = {
	&loadScreenMap, &loadScreenBack,


	&missiondescriptionPanelText, &missiondescriptionPanelHeaderText,

	&campaignheaderPanelText, &campaignPanelText,

	&loadScreenMeterBack, &loadScreenMeterBack2, &loadScreenMeterBackText,

	&loadScreenPins,

	NULL,
};

/*
================
CG_DrawConnectScreen
================
*/

const char* CG_LoadPanel_GameTypeName( gametype_t gt ) {
	/* Original server IDs 7/8 extend ET's gametype enum; display only. */
	switch( (int)gt ) {
		case GT_SINGLE_PLAYER:
			return "Single Player";
		case GT_COOP:
			return "Co-op";
		case GT_WOLF:
			return "Objective";
		case GT_WOLF_STOPWATCH:
			return "Stopwatch";
		case GT_WOLF_CAMPAIGN:
			return "Campaign";
		case GT_WOLF_LMS:
			return "Last Man Standing";
		case 6: return "Map Voting";
		case 7: return "Team Death Match";
		case 8: return "Death Match";
		default:
			break;
	}

	return "Invalid";
}

/* Original CG_DrawConnectScreen 0x7bc00 and loadpanelButtons 0x137800.
 * All assets remain in the original PK3; this is a code-only layout port. */
void CG_DrawConnectScreen( qboolean interactive, qboolean forcerefresh ) {
	static qboolean inside;
	static qhandle_t nxac;
	char info[MAX_INFO_STRING];
	const char *text;
	int used, expected, i;
	float fraction, width = 0;
	vec4_t shade = { .15f, .15f, .15f, .35f };
	vec4_t tint = { 1, 1, 1, 1 };
	panel_button_t description = missiondescriptionPanelText;
	panel_button_t heading = campaignheaderPanelText;
	panel_button_text_t descriptionFont = missiondescriptionTxt;
	panel_button_text_t headingFont = campaignpheaderTxt;
	qhandle_t icons[6];
	int enabled[6];
	if(!DC || inside) return;
	inside = qtrue;
	bg_loadscreeninteractive = interactive;
	if(!bg_loadscreeninited) {
		trap_Cvar_Set("ui_connecting", "0");
		DC->registerFont("ariblk", 27, &bg_loadscreenfont1);
		DC->registerFont("courbd", 30, &bg_loadscreenfont2);
		nxac = DC->registerShaderNoMip("ui/assets/filter_nxac_loading.tga");
		bg_filter_ff = DC->registerShaderNoMip("ui/assets/filter_ff");
		bg_filter_hw = DC->registerShaderNoMip("ui/assets/filter_weap");
		bg_filter_lv = DC->registerShaderNoMip("ui/assets/filter_lives");
		bg_filter_al = DC->registerShaderNoMip("ui/assets/filter_antilag");
		bg_filter_bt = DC->registerShaderNoMip("ui/assets/filter_balance");
		bg_mappic = 0;
		bg_loadscreeninited = qtrue;
	}
	CG_FillRect(0, 0, 640, 480, colorBlack);
	description.rect.x = 10; description.rect.y = 34;
	description.rect.w = 180; description.rect.h = 250;
	Vector4Set(descriptionFont.colour, 1, 1, 1, .75f);
	description.font = &descriptionFont;
	CG_LoadPanel_RenderMissionDescriptionText(&description);
	heading.rect.x = 10; heading.rect.y = 24;
	headingFont.scalex = headingFont.scaley = .35f;
	Vector4Set(headingFont.colour, 1, 1, 1, 1);
	heading.font = &headingFont;
	CG_LoadPanel_RenderCampaignTypeText(&heading);
	if(cgs.rawmapname[0]) {
		if(!bg_mappic) {
			bg_mappic = DC->registerShaderNoMip(va("levelshots/%s", cgs.rawmapname));
			if(!bg_mappic) bg_mappic = DC->registerShaderNoMip("levelshots/unknownmap");
		}
		trap_R_SetColor(NULL);
		CG_DrawPic(224, 2, 192, 144, bg_mappic);
	}
	if(cgs.gametype == GT_WOLF_CAMPAIGN) {
		text = DC->nameForCampaign();
		if(text) {
			CG_Text_Paint_Centred_Ext(320, 160, .3f, .3f, campaignpTxt.colour, text, 0, 0, 0, &bg_loadscreenfont2);
			CG_Text_Paint_Centred_Ext(320, 175, .3f, .3f, campaignpTxt.colour,
				va("%iof%i", cgs.currentCampaignMap + 1, cgs.campaignData.mapCount), 0, 0, 0, &bg_loadscreenfont2);
		}
	} else if(cgs.arenaInfoLoaded) {
		CG_Text_Paint_Centred_Ext(320, 160, .3f, .3f, campaignpTxt.colour, cgs.arenaData.longname, 0, 0, 0, &bg_loadscreenfont2);
	}
	trap_GetHunkData(&used, &expected);
	if(expected > 0) {
		fraction = (float)used / expected;
		if(fraction < 0) fraction = 0;
		if(fraction > 1) fraction = 1;
		CG_FilledBar(260, 458, 120, 10, colorMdRed, NULL, NULL, fraction, 0x50);
		CG_DrawRect_FixedBorder(260, 458, 120, 10, 1, colorDkGrey);
	}
	CG_Text_Paint_Centred_Ext(320, 466, .2f, .2f, colorWhite, cg.infoScreenText, 0, 0, 7, &bg_loadscreenfont2);
	DC->getConfigString(CS_SERVERINFO, info, sizeof(info));
	if(info[0]) {
		int last = -1;
		int motdBase = NITMOD_UsesOriginalProtocol() ? 841 : CS_CUSTMOTD;
		text = Info_ValueForKey(info, "sv_hostname");
		if(!text[0]) text = "ETHost";
		width = CG_Text_Width_Ext(text, .25f, 32, &bg_loadscreenfont1);
		for(i = 0; i < 7; ++i) {
			float lineWidth;
			const char *line = CG_ConfigString(motdBase + i);
			if(!line[0]) continue;
			last = i;
			lineWidth = CG_Text_Width_Ext(line, .25f, 50, &bg_loadscreenfont1);
			if(lineWidth > width) width = lineWidth;
		}
		if(last >= 0) CG_FillRect(320 - width * .5f - 4, 268, width + 8, last * 11 + 35, shade);
		CG_Text_Paint_Centred_Ext(320, 280, .25f, .25f, colorWhite, text, 0, 32, 0, &bg_loadscreenfont1);
		for(i = 0; i < 7; ++i) {
			const char *line = CG_ConfigString(motdBase + i);
			if(line[0]) CG_Text_Paint_Centred_Ext(320, 300 + i * 11, .2f, .2f, colorWhite, line, 0, 50, 0, &bg_loadscreenfont2);
		}
		icons[0] = bg_filter_ff; icons[1] = bg_filter_bt; icons[2] = bg_filter_al;
		icons[3] = bg_filter_hw; icons[4] = bg_filter_lv; icons[5] = nxac;
		enabled[0] = atoi(Info_ValueForKey(info, "g_friendlyfire")) & 1;
		enabled[1] = atoi(Info_ValueForKey(info, "g_balancedteams"));
		enabled[2] = atoi(Info_ValueForKey(info, "g_antilag"));
		enabled[3] = atoi(Info_ValueForKey(info, "g_heavyWeaponRestriction")) != 100;
		enabled[4] = atoi(Info_ValueForKey(info, "g_maxlives")) ||
			atoi(Info_ValueForKey(info, "g_axismaxlives")) || atoi(Info_ValueForKey(info, "g_alliedmaxlives"));
		enabled[5] = atoi(Info_ValueForKey(info, "sv_NxAC"));
		for(i = 0; i < 6; ++i) {
			tint[3] = enabled[i] ? 1 : .2f;
			trap_R_SetColor(tint);
			CG_DrawPic(236 + i * 28, 408, 16, 16, icons[i]);
		}
		trap_R_SetColor(NULL);
	}
	CG_Text_Paint_Centred_Ext(320, 450, .2f, .2f, colorWhite,
		"^7N^1!^7tmod", 0, 0, 0, &bg_loadscreenfont2);
	if(interactive) DC->drawHandlePic(DC->cursorx, DC->cursory, 32, 32, DC->Assets.cursor);
	if(forcerefresh) DC->updateScreen();
	inside = qfalse;
}

void CG_LoadPanel_RenderLoadingBar( panel_button_t* button ) {
	int hunkused, hunkexpected;
	float frac;

	trap_GetHunkData( &hunkused, &hunkexpected );

	if( hunkexpected <= 0 ) {
		return;
	}

	frac = hunkused/(float)hunkexpected;
	if( frac < 0.f ) {
		frac = 0.f;
	}
	if( frac > 1.f ) {
		frac = 1.f;
	}

	CG_DrawPicST( button->rect.x, button->rect.y, button->rect.w * frac, button->rect.h, 0, 0, frac, 1, button->hShaderNormal );
}

void CG_LoadPanel_RenderCampaignTypeText( panel_button_t* button ) {
/*	char buffer[1024];
	const char* str;
	DC->getConfigString( CS_SERVERINFO, buffer, sizeof( buffer ) );
	if( !*buffer ) {
		return;
	}

	str = Info_ValueForKey( buffer, "g_gametype" );
*/
	CG_Text_Paint_Ext( button->rect.x, button->rect.y, button->font->scalex, button->font->scaley, button->font->colour, va( "%s:", CG_LoadPanel_GameTypeName( cgs.gametype ) ), 0, 0, button->font->style, button->font->font );
}


void CG_LoadPanel_RenderCampaignNameText( panel_button_t* button ) {
	const char* cs;
	float w;
	//char buffer[1024];
	//int gametype;

	//DC->getConfigString( CS_SERVERINFO, buffer, sizeof( buffer ) );
	//cs = Info_ValueForKey( buffer, "g_gametype" );
	//gametype = atoi(cs);

	if( cgs.gametype == GT_WOLF_CAMPAIGN ) {

		cs = DC->nameForCampaign();
		if( !cs ) {
			return;
		}

		cs = va( "%s %iof%i", cs, cgs.currentCampaignMap+1, cgs.campaignData.mapCount );

		w = CG_Text_Width_Ext( cs, button->font->scalex, 0, button->font->font );
		CG_Text_Paint_Ext( button->rect.x + (button->rect.w - w)*0.5f, button->rect.y, button->font->scalex, button->font->scaley, button->font->colour, cs, 0, 0, 0, button->font->font );

	} else {

		if( !cgs.arenaInfoLoaded ) {
			return;
		}

		w = CG_Text_Width_Ext( cgs.arenaData.longname, button->font->scalex, 0, button->font->font );
		CG_Text_Paint_Ext( button->rect.x + (button->rect.w - w)*0.5f, button->rect.y, button->font->scalex, button->font->scaley, button->font->colour, cgs.arenaData.longname, 0, 0, 0, button->font->font );		
	}
}

void CG_LoadPanel_RenderMissionDescriptionText( panel_button_t* button ) {
	const char* cs;
	char *s, *p;
	char buffer[1024];
	float y;
	//int gametype;

	//DC->getConfigString( CS_SERVERINFO, buffer, sizeof( buffer ) );
	//cs = Info_ValueForKey( buffer, "g_gametype" );
	//gametype = atoi(cs);

//	DC->fillRect( button->rect.x, button->rect.y, button->rect.w, button->rect.h, colorRed );

	if( cgs.gametype == GT_WOLF_CAMPAIGN ) {

		cs = DC->descriptionForCampaign();
		if( !cs ) {
			return;
		}

	} else if( cgs.gametype == GT_WOLF_LMS ) {

		//cs = CG_ConfigString( CS_MULTI_MAPDESC3 );

		if( !cgs.arenaInfoLoaded ) {
			return;
		}

		cs = cgs.arenaData.lmsdescription;

	} else {

		if( !cgs.arenaInfoLoaded ) {
			return;
		}

		cs = cgs.arenaData.description;
	}

	Q_strncpyz( buffer, cs, sizeof(buffer) );
	while ((s = strchr(buffer, '*'))) {
		*s = '\n';
	}

	BG_FitTextToWidth_Ext( buffer, button->font->scalex, button->rect.w - 16, sizeof(buffer), button->font->font );

	y = button->rect.y + 12;

	s = p = buffer;
	while(*p) {
		if(*p == '\n') {
			*p++ = '\0';
			DC->drawTextExt( button->rect.x + 4, y, button->font->scalex, button->font->scaley, button->font->colour, s, 0, 0, 0, button->font->font );
			y += 8;
			s = p;
		} else {
			p++; 
		}
	}
}

void CG_LoadPanel_KeyHandling( int key, qboolean down ) {
	if( BG_PanelButtonsKeyEvent( key, down, loadpanelButtons ) ) {
		return;
	}
}

qboolean CG_LoadPanel_ContinueButtonKeyDown( panel_button_t* button, int key ) {
	if( key == K_MOUSE1 ) {
		CG_EventHandling( CGAME_EVENT_GAMEVIEW, qfalse );
		return qtrue;
	}

	return qfalse;
}


void CG_LoadPanel_DrawPin( const char* text, float px, float py, float sx, float sy, qhandle_t shader, float pinsize, float backheight ) {
	float x, y, w, h;
	vec4_t colourFadedBlack = { 0.f, 0.f, 0.f, 0.4f };

	w = DC->textWidthExt( text, sx, 0, &bg_loadscreenfont2 );
	if( px + 30 + w > 440 ) {
		DC->fillRect( px - w - 28 + 2, py - (backheight/2.f) + 2, 28 + w, backheight, colourFadedBlack );
		DC->fillRect( px - w - 28, py - (backheight/2.f), 28 + w, backheight, colorBlack );
	} else {
		DC->fillRect( px + 2, py - (backheight/2.f) + 2, 28 + w, backheight, colourFadedBlack );
		DC->fillRect( px, py - (backheight/2.f), 28 + w, backheight, colorBlack );
	}

	x = px - pinsize;
	y = py - pinsize;
	w = pinsize * 2.f;
	h = pinsize * 2.f;

	DC->drawHandlePic( x, y, w, h, shader );

	if( px + 30 + w > 440 ) {
		DC->drawTextExt( px - 12 - w - 28, py + 4, sx, sy, colorWhite, text, 0, 0, 0, &bg_loadscreenfont2 );
	} else {
		DC->drawTextExt( px + 16, py + 4, sx, sy, colorWhite, text, 0, 0, 0, &bg_loadscreenfont2 );
	}
}

void CG_LoadPanel_RenderCampaignPins( panel_button_t* button ) {
	int i;
	qhandle_t shader;
	/*char buffer[1024];
	char *s;
	int gametype;

	DC->getConfigString( CS_SERVERINFO, buffer, sizeof( buffer ) );
	s = Info_ValueForKey( buffer, "g_gametype" );
	gametype = atoi(s);*/

	if( cgs.gametype == GT_WOLF_STOPWATCH || cgs.gametype == GT_WOLF_LMS || cgs.gametype == GT_WOLF ) {
		float px, py;

		if( !cgs.arenaInfoLoaded ) {
			return;
		}

		px = ( cgs.arenaData.mappos[0] / 1024.f ) * 440.f;
		py = ( cgs.arenaData.mappos[1] / 1024.f ) * 480.f;

		CG_LoadPanel_DrawPin( cgs.arenaData.longname, px, py, 0.22f, 0.25f, bg_neutralpin, 16.f, 16.f );
	} else {
		if( !cgs.campaignInfoLoaded ) {
			return;
		}

		for( i = 0; i < cgs.campaignData.mapCount; i++ ) {
			float px, py;

			cg.teamWonRounds[1] = atoi( CG_ConfigString( CS_ROUNDSCORES1 ) );
			cg.teamWonRounds[0] = atoi( CG_ConfigString( CS_ROUNDSCORES2 ) );

			if( cg.teamWonRounds[1] & (1 << i) ) {
				shader = bg_axispin;
			} else if( cg.teamWonRounds[0] & (1 << i) ) {
				shader = bg_alliedpin;
			} else {
				shader = bg_neutralpin;
			}

			px = ( cgs.campaignData.arenas[i].mappos[0] / 1024.f ) * 440.f;
			py = ( cgs.campaignData.arenas[i].mappos[1] / 1024.f ) * 480.f;

			CG_LoadPanel_DrawPin( cgs.campaignData.arenas[i].longname, px, py, 0.22f, 0.25f, shader, 16.f, 16.f );
		}
	}
}
