#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_view.h"

void CG_Zoom(void);
void CG_DrawMiscGamemodels(void);

static centity_t *nitmodMissileCamera;

void CG_NitmodMissileCameraBeginFrame(void) {
	nitmodMissileCamera = NULL;
}

/* Original CG_Missile, ELF 0x65bde..0x65c99: remember the local player's
 * currently rendered panzer, mortar or rifle-grenade projectile according to
 * the server's g_missileCams mask.  This is deliberately based only on typed
 * entityState fields so it also consumes snapshots from an original server. */
void CG_NitmodMissileCameraTrack(centity_t *cent) {
	const entityState_t *state;
	int option;

	if(!cent || !cg.snap || !NITMOD_UsesOriginalProtocol()) return;
	state = &cent->currentState;
	if(state->eType != ET_MISSILE || state->clientNum != cg.snap->ps.clientNum) return;

	switch(state->weapon) {
	case WP_PANZERFAUST: option = 1; break;
	case WP_MORTAR:
	case WP_MORTAR_SET: option = 2; break;
	case WP_GPG40:
	case WP_M7: option = 4; break;
	default: return;
	}
	if(NITMOD_SimpleConfig()->missileCams & option) nitmodMissileCamera = cent;
}

/* Original CG_DrawMissileCamera, ELF 0x7ee70.  Render a compact 4:3 view from
 * 32 units ahead of the projectile and then restore the main refdef. */
void CG_NitmodDrawMissileCamera(void) {
	refdef_t camera;
	refdef_t *mainView;
	vec3_t forward;
	float x = 16, y = 160, width = 160, height = 120;

	if(!nitmodMissileCamera || !cg_drawCam.integer || cg.demoPlayback ||
	   !cg.snap || !cg.refdef_current || (cg.snap->ps.eFlags & EF_MOUNTEDTANK)) return;

	mainView = cg.refdef_current;
	camera = *mainView;
	CG_AdjustFrom640(&x, &y, &width, &height);
	camera.x = (int)x; camera.y = (int)y;
	camera.width = (int)width; camera.height = (int)height;
	VectorCopy(nitmodMissileCamera->lerpOrigin, camera.vieworg);
	AnglesToAxis(nitmodMissileCamera->lerpAngles, camera.viewaxis);
	VectorCopy(camera.viewaxis[0], forward);
	VectorMA(camera.vieworg, 32, forward, camera.vieworg);
	camera.time = cg.time;

	trap_R_SaveViewParms();
	cg.refdef_current = &camera;
	trap_R_ClearScene();
	CG_SetupFrustum();
	CG_DrawSkyBoxPortal(qfalse);
	if(!cg.hyperspace) {
		CG_AddPacketEntities();
		CG_AddMarks();
		CG_AddParticles();
		CG_AddLocalEntities();
		CG_AddSmokeSprites();
		CG_AddAtmosphericEffects();
		CG_AddFlameChunks();
		CG_AddTrails();
		CG_PB_RenderPolyBuffers();
		CG_DrawMiscGamemodels();
	}
	trap_SetClientLerpOrigin(camera.vieworg[0], camera.vieworg[1], camera.vieworg[2]);
	trap_R_RenderScene(&camera);
	cg.refdef_current = mainView;
	trap_R_RestoreViewParms();
}

/* Inlined in original CG_CalcViewValues (ELF 0xbc2b0). */
void CG_NitmodZoomSway(int time, float zoom, const playerState_t *state, vec3_t angles) {
    float spread, phase, pitchMinimum, yawMinimum;
    if(!zoom || !state || (state->eFlags & EF_MG42_ACTIVE)) return;
    spread = state->aimSpreadScale / 255.0f;
    pitchMinimum = state->weapon == WP_FG42SCOPE ? .4f : .1f;
    yawMinimum = state->weapon == WP_FG42SCOPE ? .8f : .2f;
    phase = (float)(time / 1000.0 * .24 * M_PI);
    angles[PITCH] += (spread+pitchMinimum) * (float)sin(phase+phase) * .13f;
    phase = (float)(time / 1000.0 * .12 * M_PI);
    angles[YAW] += (spread+yawMinimum) * (float)sin(phase+phase) * .7f;
}

/* Original CG_Letterbox does not apply the native cg_letterbox multiplier. */
void CG_NitmodLetterbox(refdef_t *view, int width, int height, float xpercent, float ypercent, qboolean center) {
    double w = (double)width*xpercent/100, h = (double)height*ypercent/100;
    /* Reject nonfinite/out-of-range inputs before any float-to-int cast. */
    if(!view || width < 0 || height < 0 || !(w >= 0 && w <= 2147483647.0) ||
       !(h >= 0 && h <= 2147483647.0)) return;
    view->width = (int)w & ~1; view->height = (int)h & ~1;
    if(center) { view->x = (width-view->width)/2; view->y = (height-view->height)/2; }
}

/* Original CG_CalcViewValues: poison first, then lean using the new angles. */
void CG_NitmodViewOffsets(int time, int flags, int weapons, float lean,
                         vec3_t angles, vec3_t origin) {
    vec3_t right;
    if(flags & NITMOD_EF_POISONED) {
        float phase = (float)(time / 1000.0 * .3 * M_PI);
        float wave = (float)sin(phase);
        angles[ROLL] += wave * 36;
        angles[YAW] += wave * 24;
        angles[PITCH] += (float)sin(phase * 2.5) * 12;
    }
    if(lean != 0) {
        angles[ROLL] += lean / ((weapons & 256) ? 3.2f : 2.f);
        AngleVectors(angles, NULL, right, NULL);
        VectorMA(origin, lean, right, origin);
    }
}

#define	WAVE_AMPLITUDE	1
#define	WAVE_FREQUENCY	0.4

int CG_CalcFov( void ) {
	static float lastfov = 90;		// for transitions back from zoomed in modes
	float	x;
	float	phase;
	float	v;
	int		contents;
	float	fov_x, fov_y;
	float	zoomFov;
	float	f;
	int		inwater;

	CG_Zoom();

	if ( cg.predictedPlayerState.stats[STAT_HEALTH] <= 0 && !(cg.snap->ps.pm_flags & PMF_FOLLOW) ) 
	{
		cg.zoomedBinoc = qfalse;
		cg.zoomTime = 0;
		cg.zoomval = 0;
	}

	if ( cg.predictedPlayerState.pm_type == PM_INTERMISSION ) {
		// if in intermission, use a fixed value
		fov_x = 90;
	} else {
		fov_x = cg_fov.value;
		if( !developer.integer ) {
			if ( fov_x < 90 ) {
				fov_x = 90;
			} else if ( fov_x > 160 ) {
				fov_x = 160;
			}
		}

		if( !cg.renderingThirdPerson || developer.integer ) {
			// account for zooms
			if(cg.zoomval) {
				zoomFov = cg.zoomval;	// (SA) use user scrolled amount

				if ( zoomFov < 1 ) {
					zoomFov = 1;
				} else if ( zoomFov > 160 ) {
					zoomFov = 160;
				}
			} else {
					zoomFov = lastfov;
			}
			
			// do smooth transitions for the binocs
			if(cg.zoomedBinoc) {		// binoc zooming in
				f = ( cg.time - cg.zoomTime ) / (float)ZOOM_TIME;
				if ( f > 1.0 ) {
					fov_x = zoomFov;
				} else {
					fov_x = fov_x + f * ( zoomFov - fov_x );
				}
				lastfov = fov_x;
			} else if (cg.zoomval) {	// zoomed by sniper/snooper
				fov_x = cg.zoomval;
				lastfov = fov_x;
			} else {					// binoc zooming out
				f = ( cg.time - cg.zoomTime ) / (float)ZOOM_TIME;
				if ( f > 1.0 ) {
					fov_x = fov_x;
				} else {
					fov_x = zoomFov + f * ( fov_x - zoomFov);
				}
			}
		}
	}

	cg.refdef_current->rdflags &= ~RDF_SNOOPERVIEW;

	// Arnout: mg42 zoom
	if (cg.snap->ps.persistant[PERS_HWEAPON_USE]) {
		fov_x = 55;
	} else if( cg.snap->ps.weapon == WP_MOBILE_MG42_SET ) {
		fov_x = 55;
	} else if( cg.snap->ps.eFlags & EF_MOUNTEDTANK ) {
		fov_x = 75;
	}

	if( cg.showGameView ) {
		fov_x = fov_y = 60.f;
	}

	// Arnout: this is weird... (but ensures square pixel ratio!)
	x = cg.refdef_current->width / tan( fov_x / 360 * M_PI );
	fov_y = atan2( cg.refdef_current->height, x );
	fov_y = fov_y * 360 / M_PI;
	// And this seems better - but isn't really
	//fov_y = fov_x / cgs.glconfig.windowAspect;

	// warp if underwater
	//if ( cg_pmove.waterlevel == 3 ) {
	contents = CG_PointContents( cg.refdef.vieworg, -1 );
	if ( contents & ( CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA ) ){
		phase = cg.time / 1000.0 * WAVE_FREQUENCY * M_PI * 2;
		v = WAVE_AMPLITUDE * sin( phase );
		fov_x += v;
		fov_y -= v;
		inwater = qtrue;
		cg.refdef_current->rdflags |= RDF_UNDERWATER;
	} else {
		cg.refdef_current->rdflags &= ~RDF_UNDERWATER;
		inwater = qfalse;
	}

	/* Original Nitmod overloads the ET camera bit with poison state. */
	if(NITMOD_UsesOriginalProtocol() && (cg.predictedPlayerState.eFlags & NITMOD_EF_POISONED)) {
		phase = cg.time / 1000.0 * .3 * M_PI * 2;
		v = 12 * sin(phase);
		fov_x += v; fov_y -= v;
		cg.refdef_current->rdflags |= RDF_UNDERWATER;
		inwater = qtrue;
	}

	// set it
	cg.refdef_current->fov_x = fov_x;
	cg.refdef_current->fov_y = fov_y;

/*
	if( cg.predictedPlayerState.eFlags & EF_PRONE ) {
		cg.zoomSensitivity = cg.refdef.fov_y / 500.0;
	} else
*/
	// rain - allow freelook when dead until we tap out into limbo
	if( cg.snap->ps.pm_type == PM_FREEZE || (cg.snap->ps.pm_type == PM_DEAD && (cg.snap->ps.pm_flags & PMF_LIMBO)) || cg.snap->ps.pm_flags & PMF_TIME_LOCKPLAYER ) {
		// No movement for pauses
		cg.zoomSensitivity = 0;
	} else if ( !cg.zoomedBinoc ) {
		// NERVE - SMF - fix for zoomed in/out movement bug
		if ( cg.zoomval ) {
			cg.zoomSensitivity = 0.6 * ( cg.zoomval / 90.f );	// NERVE - SMF - changed to get less sensitive as you zoom in
//				cg.zoomSensitivity = 0.1;
		} else {
			cg.zoomSensitivity = 1;
		}
		// -NERVE - SMF
	} else {
		cg.zoomSensitivity = cg.refdef_current->fov_y / 75.0;
	}

	return inwater;
}
