#include "cg_local.h"
#include "cg_nitmod_debug.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_events.h"

extern void CG_StartShakeCamera(float strength);
vmCvar_t cg_obituary, cg_tkSounds, cg_goatSound;
static sfxHandle_t obituaryGoat, obituaryGib, obituaryTK;
static qboolean obituarySoundsLoaded;

/* Original qagame modNames at ELF 0x2a7bc0. Not weapon_t or ET's MOD enum. */
int CG_NitmodDeathCause(int wireCause) {
    static const int causes[] = {
        MOD_UNKNOWN, MOD_MACHINEGUN, MOD_BROWNING, MOD_MG42, MOD_GRENADE,
        MOD_KNIFE, MOD_LUGER, MOD_COLT, MOD_MP40, MOD_THOMPSON, MOD_STEN,
        MOD_GARAND, MOD_SILENCER, MOD_FG42, MOD_FG42SCOPE, MOD_PANZERFAUST,
        MOD_GRENADE_LAUNCHER, MOD_FLAMETHROWER, MOD_GRENADE_PINEAPPLE,
        MOD_MAPMORTAR, MOD_MAPMORTAR_SPLASH, MOD_DYNAMITE, MOD_AIRSTRIKE,
        MOD_SYRINGE, MOD_AMMO, MOD_ARTY, MOD_WATER, MOD_SLIME, MOD_LAVA,
        MOD_CRUSH, MOD_TELEFRAG, MOD_FALLING, MOD_SUICIDE, MOD_TARGET_LASER,
        MOD_TRIGGER_HURT, MOD_EXPLOSIVE, MOD_CARBINE, MOD_KAR98, MOD_GPG40,
        MOD_M7, MOD_LANDMINE, MOD_SATCHEL, MOD_SMOKEBOMB, MOD_MOBILE_MG42,
        MOD_SILENCED_COLT, MOD_GARAND_SCOPE, MOD_CRUSH_CONSTRUCTION,
        MOD_CRUSH_CONSTRUCTIONDEATH, MOD_CRUSH_CONSTRUCTIONDEATH_NOATTACKER,
        MOD_K43, MOD_K43_SCOPE, MOD_MORTAR, MOD_AKIMBO_COLT, MOD_AKIMBO_LUGER,
        MOD_AKIMBO_SILENCEDCOLT, MOD_AKIMBO_SILENCEDLUGER, MOD_SMOKEGRENADE,
        MOD_SWITCHTEAM, MOD_UNKNOWN, MOD_UNKNOWN, MOD_UNKNOWN, MOD_UNKNOWN,
        MOD_UNKNOWN, MOD_UNKNOWN, MOD_UNKNOWN, MOD_UNKNOWN, MOD_TRIPMINE,
        MOD_UNKNOWN, MOD_UNKNOWN
    };
    return wireCause >= 0 && wireCause < sizeof(causes)/sizeof(causes[0]) ? causes[wireCause] : MOD_UNKNOWN;
}

void CG_NitmodObituaryReset(void) {
    obituarySoundsLoaded = qfalse;
    obituaryGoat = obituaryGib = obituaryTK = 0;
}

void CG_NitmodSpecialObituary(int cause, char **message, char **suffix) {
    /* Original Obituaries_killedby, ELF 0x134940; only defined private pairs. */
    switch(cause) {
    case 58: *message = "was stomped by"; *suffix = ""; break;
    case 59: *message = "was poisoned by"; *suffix = ""; break;
    case 60: *message = "was scared to death by"; *suffix = ""; break;
    case 62: *message = "was pushed too far by"; *suffix = ""; break;
    case 63: *message = "was killed by"; *suffix = "'s Throwing Knife"; break;
    case 65: *message = "was detonated by"; *suffix = "'s Bomb"; break;
    case 67: *message = "choked on"; *suffix = "'s Poison Gas"; break;
    case 68: *message = "choked on"; *suffix = "'s own poison gas landmine"; break;
    }
}

void CG_NitmodObituaryPrint(const char *text, qhandle_t shader, const entityState_t *event) {
    nitmodObituaryPlan_t plan;
    if(!event || !text || !*text) return;
    if(!NITMOD_UsesOriginalProtocol()) { CG_AddPMItem(PM_DEATH, text, shader); return; }
    if(CG_NitmodPlanGraphicObituary(event, cg_obituary.integer, shader, &plan) &&
       CG_NitmodAddGraphicObituary(plan.first, plan.second, plan.shader, plan.scale, plan.color)) {
        CG_Printf("%s\n", text);
        return;
    }
    if(cg_obituary.integer == 2) {
        CG_AddToTeamChat(text, event->clientNum);
        CG_Printf("%s\n", text);
    } else if(cg_obituary.integer >= 1 && cg_obituary.integer <= 4) {
        /* Invalid media or an exhausted popup pool retain readable text. */
        CG_AddPMItem(PM_DEATH, text, shader);
    } else CG_Printf("%s\n", text);
}

void CG_NitmodObituarySounds(const entityState_t *es) {
    int target, attacker, listener, cause;
    qboolean goat, gib, tk;
    if(!es || !cg.snap || !NITMOD_UsesOriginalProtocol()) return;
    target = es->otherEntityNum; attacker = es->otherEntityNum2;
    listener = cg.snap->ps.clientNum; cause = es->eventParm;
    if(target < 0 || target >= MAX_CLIENTS || attacker < 0 || attacker >= MAX_CLIENTS ||
       listener < 0 || listener >= MAX_CLIENTS || target == attacker) return;
    goat = (listener == target || listener == attacker) &&
        ((cause == 5 && (cg_goatSound.integer & 1)) || (cause == 63 && (cg_goatSound.integer & 2)));
    gib = cause == 58 && (listener == target || listener == attacker);
    tk = cg_tkSounds.integer && cgs.gametype != 8 && cause >= 0 && cause < 69 &&
        cause != 23 && cause != 24 && cause != 42 && cause != 57 && cause != 61 && cause != 64 &&
        cgs.clientinfo[target].team == cgs.clientinfo[attacker].team &&
        (cgs.clientinfo[target].team == TEAM_AXIS || cgs.clientinfo[target].team == TEAM_ALLIES);
    if(!goat && !gib && !tk) return;
    if(!obituarySoundsLoaded) {
        obituaryGoat = trap_S_RegisterSound("sound/nit/goat.wav", qfalse);
        obituaryGib = trap_S_RegisterSound("sound/player/gib.wav", qfalse);
        obituaryTK = trap_S_RegisterSound("sound/nit/tk.wav", qfalse);
        obituarySoundsLoaded = qtrue;
    }
    if(gib && obituaryGib > 0) trap_S_StartSound(cg.snap->ps.origin, listener, CHAN_AUTO, obituaryGib);
    if(goat && obituaryGoat > 0) {
        trap_S_StartSound(cg.snap->ps.origin, target, CHAN_WEAPON, obituaryGoat);
        trap_S_StartSound(cg.snap->ps.origin, attacker, CHAN_WEAPON, obituaryGoat);
    }
    if(tk && obituaryTK > 0) trap_S_StartSound(NULL, listener, CHAN_AUTO, obituaryTK);
}

/* Original CG_EntityEvent cases 94, 95, 97, 100, 102, 103. The sound table
 * at cgs+0x2038f84 is the same table used by original GENERAL_SOUND. */
qboolean CG_NitmodExtendedEvent(centity_t *cent, int wireEvent) {
	const entityState_t *es = &cent->currentState;
	int client, weapon;
	float distance, strength;
	vec3_t delta;
	switch(wireEvent) {
	case 104: case 105: case 106:
		CG_NitmodDebugEvent(es, wireEvent);
		return qtrue;
	case 94:
		/* EV_BODY_DP: reset only the cached player rendering state belonging
		 * to the referenced corpse. The original clears 0x514 bytes starting
		 * at centity_t.pe; use the typed member size on every target ABI. */
		if(es->otherEntityNum >= 0 && es->otherEntityNum < MAX_GENTITIES)
			memset(&cg_entities[es->otherEntityNum].pe, 0,
				sizeof(cg_entities[es->otherEntityNum].pe));
		return qtrue;
	case 95:
		CG_FireWeapon(cent, NITMOD_FIRE_THROWKNIFE);
		return qtrue;
	case 97:
		if(!cg.snap || es->number != cg.snap->ps.clientNum) return qtrue;
		weapon = NITMOD_WeaponFromWire(es->eventParm);
		if(weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ||
		   cg.weaponSelect <= WP_NONE || cg.weaponSelect >= WP_NUM_WEAPONS) return qtrue;
		CG_FinishWeaponChange(cg.weaponSelect, weapon);
		return qtrue;
	case 100:
	case 103:
		if(es->eventParm < 0 || es->eventParm >= MAX_SOUNDS) return qtrue;
		if(wireEvent == 103 && !cg.snap) return qtrue;
		client = wireEvent == 103 ? cg.snap->ps.clientNum : es->number;
		if(client < 0 || client >= MAX_GENTITIES) return qtrue;
		if(cgs.gameSounds[es->eventParm] > 0)
			trap_S_StartSoundVControl(NULL, client, CHAN_AUTO, cgs.gameSounds[es->eventParm], 255);
		return qtrue;
	case 102:
		if(!cg.snap) return qtrue;
		client = cg.snap->ps.clientNum;
		if(client < 0 || client >= MAX_CLIENTS) return qtrue;
		if(cgs.media.nitmodSlapSound > 0)
			trap_S_StartSound(cg.snap->ps.origin, client, CHAN_ANNOUNCER, cgs.media.nitmodSlapSound);
		if(es->onFireStart <= 0) return qtrue;
		VectorSubtract(cg.snap->ps.origin, cent->lerpOrigin, delta);
		distance = VectorLength(delta);
		if(distance >= es->onFireStart) return qtrue;
		strength = 1.0f - distance / es->onFireStart;
		if(strength > 0 && strength <= 1) CG_StartShakeCamera(strength);
		return qtrue;
	default:
		return qfalse;
	}
}

/* Original cases 91/92 add these lines in addition to the existing radio
 * script. Do not emit them for native ET servers or local prediction. */
void CG_NitmodFireSupportChat(const entityState_t *es, qboolean airstrike) {
	static const char *const artillery[] = {
		"^7Fire Mission: ^3Insufficient fire support.",
		"^7Fire Mission: ^3Aborting, can't see target.",
		"^7Fire Mission: ^3Firing for effect!"
	};
	static const char *const air[] = {
		"^7HQ: ^3All available planes are already en-route.",
		"^7Pilot: ^3Aborting, can't see target.",
		NULL
	};
	const char *text;
	if(!cg.snap || cg.snap->ps.clientNum < 0 || cg.snap->ps.clientNum >= MAX_CLIENTS ||
	   es->density < 0 || es->density > 2) return;
	text = airstrike ? air[es->density] : artillery[es->density];
	if(text) CG_AddToTeamChat(text, cg.snap->ps.clientNum);
}
