#include "ui_local.h"
#include "ui_shared.h"
#include <limits.h>
#include <float.h>

qboolean	bg_loadscreeninited = qfalse;
fontInfo_t	bg_loadscreenfont1;
fontInfo_t	bg_loadscreenfont2;

void UI_LoadPanel_RenderHeaderText( panel_button_t* button );
void UI_LoadPanel_RenderLoadingText( panel_button_t* button );
void UI_LoadPanel_RenderPercentageMeter( panel_button_t* button );

/* Original Nitmod UI 0x21f90/0x22000.  These coordinates deliberately stay
 * in the 640-wide virtual space: the normal panel is 4:3 while status text
 * may use the additional width exposed by a widescreen renderer. */
static qboolean UI_NitmodDownloading( void ) {
	uiClientState_t cstate;
	char downloadName[MAX_INFO_VALUE];

	trap_GetClientState( &cstate );
	trap_Cvar_VariableStringBuffer( "cl_downloadName", downloadName,
		sizeof(downloadName) );
	return ( cstate.connState == CA_DISCONNECTED ||
		cstate.connState == CA_CONNECTED ) && downloadName[0];
}

/* Original UI_LoadPanel_RenderDownloadingBar 0x22690. */
static void UI_NitmodDrawDownloadBar( void ) {
	float downloadSize = trap_Cvar_VariableValue( "cl_downloadSize" );
	float downloadCount = trap_Cvar_VariableValue( "cl_downloadCount" );
	float fraction;
	float x, y, w, h;
	vec4_t background = { 1.f, 1.f, 1.f, .25f };

	if( !(downloadSize > 0.f) || downloadSize > FLT_MAX ) {
		return;
	}
	if(!(downloadCount >= 0.f)) downloadCount = 0.f;
	if(downloadCount > downloadSize) downloadCount = downloadSize;
	fraction = downloadCount / downloadSize;
	if( fraction < 0.f ) fraction = 0.f;
	if( fraction > 1.f ) fraction = 1.f;

	/* Draw in raw screen coordinates, matching the original full-width bar. */
	x = 0.f;
	y = 468.f * uiInfo.uiDC.yscale;
	w = 640.f * uiInfo.uiDC.xscale;
	h = 12.f * uiInfo.uiDC.yscale;
	trap_R_SetColor( background );
	trap_R_DrawStretchPic( x, y, w, h, 0, 0, 1, 1,
		uiInfo.uiDC.whiteShader );

	x = 2.f * uiInfo.uiDC.xscale;
	y = 469.f * uiInfo.uiDC.yscale;
	w = 638.f * fraction * uiInfo.uiDC.xscale;
	h = 10.f * uiInfo.uiDC.yscale;
	trap_R_SetColor( colorGreen );
	trap_R_DrawStretchPic( x, y, w, h, 0, 0, 1, 1,
		uiInfo.uiDC.whiteShader );
	trap_R_SetColor( NULL );
}

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
	0.35f, 0.35f,
	{ 1.0f, 1.0f, 1.0f, 0.6f },
	0, 0,
	&bg_loadscreenfont2,
};

panel_button_t loadScreenMap = {
	"gfx/loading/camp_map",
	NULL,
	{ 0, 0, 440, 480 },	// shouldn't this be square??
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

/*panel_button_t loadingPanelHeaderText = {
	NULL,
	"***TOP SECRET***",
	{ 440, 72, 200, 32 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&missiondescriptionHeaderTxt,
	NULL,
	NULL,
	BG_PanelButtonsRender_Text,
	NULL,
};*/

panel_button_t loadingPanelText = {
	NULL,
	NULL,
	{ 460, 72, 160, 244 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&missiondescriptionTxt,	/* font		*/
	NULL,					/* keyDown	*/
	NULL,					/* keyUp	*/
	UI_LoadPanel_RenderLoadingText,
	NULL,
};

/*panel_button_t campaignheaderPanelText = {
	NULL,
	"Connecting to:",
	{ 456, 24, 152, 232 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&campaignpheaderTxt,
	NULL,
	NULL,
	BG_PanelButtonsRender_Text,
	NULL,
};
*/
panel_button_t campaignPanelText = {
	NULL,
	NULL, //"CONNECTING...",
	{ 470, 33, 152, 232 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	&campaignpTxt,			/* font		*/
	NULL,					/* keyDown	*/
	NULL,					/* keyUp	*/
	UI_LoadPanel_RenderHeaderText,
	NULL,
};

panel_button_t* loadpanelButtons[] = {
	&loadScreenMap, &loadScreenBack,


	&loadingPanelText, /*&loadingPanelHeaderText,*/

	/*&campaignheaderPanelText,*/ &campaignPanelText,

	NULL,
};

/*
================
CG_DrawConnectScreen
================
*/
static qboolean connect_ownerdraw;
void UI_DrawLoadPanel( qboolean forcerefresh, qboolean ownerdraw, qboolean uihack ) {
	static qboolean inside = qfalse;
	float screenWidth;
	float screenHeight;
	float panelX[sizeof(loadpanelButtons) / sizeof(loadpanelButtons[0])];
	int i;

	if( inside ) {
		if( !uihack && trap_Cvar_VariableValue( "ui_connecting" ) ) {
			trap_Cvar_Set( "ui_connecting", "0" );
		}
		return;
	}

	connect_ownerdraw = ownerdraw;

	inside = qtrue;

	if( !bg_loadscreeninited ) {
		trap_R_RegisterFont( "ariblk", 27, &bg_loadscreenfont1 );
		trap_R_RegisterFont( "courbd", 30, &bg_loadscreenfont2 );

		BG_PanelButtonsSetup( loadpanelButtons );

		bg_loadscreeninited = qtrue;
	}

	/* Original UI_DrawLoadPanel 0x22bf0 clears the entire physical viewport.
	 * This prevents stale menu pixels around its 4:3 panel on widescreen. */
	screenWidth = (float)uiInfo.uiDC.glconfig.vidWidth;
	screenHeight = (float)uiInfo.uiDC.glconfig.vidHeight;
	trap_R_SetColor( colorBlack );
	trap_R_DrawStretchPic( 0, 0, screenWidth, screenHeight, 0, 0, 1, 1,
		uiInfo.uiDC.whiteShader );
	trap_R_SetColor( NULL );

	/* Original C_PanelButtonsSetup centers the 4:3 panel. Use temporary
	 * positions so reinitializing or changing resolution cannot add twice. */
	for(i = 0; loadpanelButtons[i]; ++i) {
		panelX[i] = loadpanelButtons[i]->rect.x;
		loadpanelButtons[i]->rect.x += UI_NitmodWideXOffset(&uiInfo.uiDC);
	}
	BG_PanelButtonsRender( loadpanelButtons );
	for(i = 0; loadpanelButtons[i]; ++i) loadpanelButtons[i]->rect.x = panelX[i];

	if( forcerefresh ) {
		//trap_UpdateScreen();
	}

	if( !uihack && trap_Cvar_VariableValue( "ui_connecting" ) ) {
		trap_Cvar_Set( "ui_connecting", "0" );
	}

	inside = qfalse;
}

#define STARTANGLE 40
void UI_LoadPanel_RenderPercentageMeter( panel_button_t* button ) {
	float hunkfrac;
	float w, h;
	vec2_t org;
	polyVert_t verts[4];

	org[0] =	button->rect.x;
	org[1] =	button->rect.y;
	w =			button->rect.w;
	h =			button->rect.h;

	hunkfrac = 0.f;
	AdjustFrom640( &org[0], &org[1], &w, &h );
	SetupRotatedThing( verts, org, w, h, DEG2RAD((180-STARTANGLE) - ((180-(2*STARTANGLE)) * hunkfrac)) );

	trap_R_Add2dPolys( verts, 4, button->hShaderNormal );
}
/*
void UI_LoadPanel_RenderCampaignNameText( panel_button_t* button ) {
	uiClientState_t	cstate;
	char *s;

	trap_GetClientState( &cstate );

	s = Q_strupr( cstate.servername );

	Text_Paint_Ext( button->rect.x, button->rect.y, button->font->scalex, button->font->scaley, button->font->colour, s, 0, 14, 0, button->font->font );
}*/

void MiniAngleToAxis( vec_t angle, vec2_t axes[2] ) {
	axes[0][0] = (vec_t)sin( -angle );
	axes[0][1] = -(vec_t)cos( -angle );

	axes[1][0] = -axes[0][1];
	axes[1][1] = axes[0][0];
}

void SetupRotatedThing( polyVert_t* verts, vec2_t org, float w, float h, vec_t angle ) {
	vec2_t axes[2];

	MiniAngleToAxis( angle, axes );

	verts[0].xyz[0] = org[0] - (w * 0.5f) * axes[0][0];
	verts[0].xyz[1] = org[1] - (w * 0.5f) * axes[0][1];
	verts[0].xyz[2] = 0;
	verts[0].st[0] = 0;
	verts[0].st[1] = 1;
	verts[0].modulate[0] = 255;
	verts[0].modulate[1] = 255;
	verts[0].modulate[2] = 255;
	verts[0].modulate[3] = 255;

	verts[1].xyz[0] = verts[0].xyz[0] + w * axes[0][0];
	verts[1].xyz[1] = verts[0].xyz[1] + w * axes[0][1];
	verts[1].xyz[2] = 0;
	verts[1].st[0] = 1;
	verts[1].st[1] = 1;
	verts[1].modulate[0] = 255;
	verts[1].modulate[1] = 255;
	verts[1].modulate[2] = 255;
	verts[1].modulate[3] = 255;

	verts[2].xyz[0] = verts[1].xyz[0] + h * axes[1][0];
	verts[2].xyz[1] = verts[1].xyz[1] + h * axes[1][1];
	verts[2].xyz[2] = 0;
	verts[2].st[0] = 1;
	verts[2].st[1] = 0;
	verts[2].modulate[0] = 255;
	verts[2].modulate[1] = 255;
	verts[2].modulate[2] = 255;
	verts[2].modulate[3] = 255;

	verts[3].xyz[0] = verts[2].xyz[0] - w * axes[0][0];
	verts[3].xyz[1] = verts[2].xyz[1] - w * axes[0][1];
	verts[3].xyz[2] = 0;
	verts[3].st[0] = 0;
	verts[3].st[1] = 0;
	verts[3].modulate[0] = 255;
	verts[3].modulate[1] = 255;
	verts[3].modulate[2] = 255;
	verts[3].modulate[3] = 255;
}

void UI_LoadPanel_RenderHeaderText( panel_button_t* button ) {
	uiClientState_t	cstate;
	char			downloadName[MAX_INFO_VALUE];

	trap_GetClientState( &cstate );

	trap_Cvar_VariableStringBuffer( "cl_downloadName", downloadName, sizeof(downloadName) );

	if( ( cstate.connState == CA_DISCONNECTED || cstate.connState == CA_CONNECTED ) && *downloadName ) {
		button->text = "DOWNLOADING...";
	} else {
		button->text = "CONNECTING...";
	}

	BG_PanelButtonsRender_Text( button );
}

#define ESTIMATES 80
int UI_DownloadCounter(const char *name) {
	double value = trap_Cvar_VariableValue(name);
	if(!(value >= 0)) return 0;
	if(value >= INT_MAX) return INT_MAX;
	return (int)value;
}
int UI_DownloadPercent(int count, int size) {
	if(size <= 0 || count <= 0) return 0;
	return count >= size ? 100 : (int)((double)count * 100.0 / size);
}
int UI_DownloadRate(int count, int started, int now) {
	double elapsed = ((double)now - started) / 1000.0;
	if(count <= 0 || started <= 0 || elapsed < 1) return 0;
	return count / (int)elapsed;
}
const char *UI_DownloadInfo( const char *downloadName )
{
	static int	tleEstimates[ESTIMATES] = { 60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,
											60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,
											60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,
											60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60 };
	static int	tleIndex = 0;
	char xferRateBuf[64], dlTimeBuf[64];
	int downloadSize, downloadCount, downloadTime;
	int xferRate;
	const char *progress;

	if(!downloadName) downloadName = "";
	downloadSize = UI_DownloadCounter( "cl_downloadSize" );
	downloadCount = UI_DownloadCounter( "cl_downloadCount" );
	downloadTime = UI_DownloadCounter( "cl_downloadTime" );

	if( downloadSize > 0 ) {
		int percent = UI_DownloadPercent(downloadCount, downloadSize);
		progress = va( "%s (%d%%)", downloadName, percent );
	} else {
		progress = downloadName;
	}

	if( downloadCount < 4096 || !downloadTime ) {
		return va( "Estimating download time for '%s'...", downloadName );
	}

	xferRate = UI_DownloadRate(downloadCount, downloadTime, uiInfo.uiDC.realTime);
	UI_ReadableSize( xferRateBuf, sizeof(xferRateBuf), xferRate );
	dlTimeBuf[0] = '\0';
	if( downloadSize > 0 && xferRate > 0 ) {
		int totalSeconds = downloadSize / xferRate;
		int remaining = totalSeconds - downloadCount / xferRate;
		double average = 0;
		int i;
		if( remaining < 0 ) remaining = 0;
		tleEstimates[tleIndex++] = remaining;
		if( tleIndex >= ESTIMATES ) tleIndex = 0;
		for( i = 0; i < ESTIMATES; ++i ) average += tleEstimates[i];
		UI_PrintTime( dlTimeBuf, sizeof(dlTimeBuf), (int)(average / ESTIMATES) );
	}
	if( xferRate > 0 ) {
		return va( "File: '%s'\nSpeed: %s/s\n\n^0%s -- %s remaining^7",
			downloadName, xferRateBuf, progress, dlTimeBuf );
	}
	return va( "\n\nEstimating download time for '%s'...", downloadName );
}

void UI_LoadPanel_RenderLoadingText( panel_button_t* button )
{
	uiClientState_t	cstate;
	char			downloadName[MAX_INFO_VALUE];
	char			buff[2560];
	char			*p, *s = "";
	float			y;
	float			textX;

	trap_GetClientState( &cstate );

	Com_sprintf( buff, sizeof(buff), "Connecting to:\n %s^*\n\n%s", cstate.servername, Info_ValueForKey( cstate.updateInfoString, "motd" ) );

	//Com_sprintf( buff, sizeof(buff), "%s^*", cstate.servername, Info_ValueForKey( cstate.updateInfoString, "motd" ) );

	trap_Cvar_VariableStringBuffer( "cl_downloadName", downloadName, sizeof(downloadName) );

	if( !connect_ownerdraw ) {
		if( !trap_Cvar_VariableValue( "ui_connecting" ) ) {
			switch( cstate.connState ) {
			case CA_CONNECTING:
				s = va( trap_TranslateString( "Awaiting connection...%i" ), cstate.connectPacketCount );
				break; 
			case CA_CHALLENGING:
				s = va( trap_TranslateString( "Awaiting challenge...%i" ), cstate.connectPacketCount );
				break;
			case CA_DISCONNECTED:
			case CA_CONNECTED:
				if( *downloadName || cstate.connState == CA_DISCONNECTED ) {
					s = (char *)UI_DownloadInfo( downloadName );
				} else {
					s = trap_TranslateString( "Awaiting gamestate..." );
				}
				break;
			case CA_LOADING:
			case CA_PRIMED:
			default:
				break;
			}
		} else if ( trap_Cvar_VariableValue( "ui_dl_running" ) ) {
			// only toggle during a disconnected download
			s = (char *)UI_DownloadInfo( downloadName );
		}

		Q_strcat( buff, sizeof(buff), va( "\n\n%s^*", s ) );

		if( cstate.connState < CA_CONNECTED && *cstate.messageString ) {
			Q_strcat( buff, sizeof(buff), va( "\n\n%s^*", cstate.messageString ) );
		}
	}

	BG_FitTextToWidth_Ext( buff, button->font->scalex, button->rect.w, sizeof(buff), button->font->font );

	//UI_DrawRect( button->rect.x, button->rect.y, button->rect.w, button->rect.h, colorRed );

	y = button->rect.y + 12;
	textX = UI_NitmodWideXOffset(&uiInfo.uiDC);

	s = p = buff;

	while( *p ) {
		if( *p == '\n' ) {
			*p++ = '\0';
			Text_Paint_Ext( textX, y, button->font->scalex, button->font->scaley,
				button->font->colour, s, 0, 0, 0, button->font->font );
			y += 8;
			s = p;
		} else {
			p++; 
		}
	}

	/* Nitmod moves download details out of the narrow side panel and keeps
	 * them directly above the full-width progress bar. */
	if( UI_NitmodDownloading() ) {
		char downloadText[2560];
		const char *line;

		Q_strncpyz( downloadText, UI_DownloadInfo( downloadName ),
			sizeof(downloadText) );
		BG_FitTextToWidth_Ext( downloadText, .2f, 640.f,
			sizeof(downloadText), &bg_loadscreenfont2 );
		y = 454.f;
		line = downloadText;
		p = downloadText;
		while( *p ) {
			if( *p == '\n' ) {
				*p++ = '\0';
				Text_Paint_Ext( textX, y, .2f, .2f, colorWhite, line,
					0, 0, 0, &bg_loadscreenfont2 );
				y += 8.f;
				line = p;
			} else {
				p++;
			}
		}
		if( line[0] ) {
			Text_Paint_Ext( textX, y, .2f, .2f, colorWhite, line,
				0, 0, 0, &bg_loadscreenfont2 );
		}
		UI_NitmodDrawDownloadBar();
	}
}
