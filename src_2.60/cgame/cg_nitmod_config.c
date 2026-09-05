/* Client half of Nitmod's extended configstring protocol. */

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "cg_local.h"
#include "../game/nitmod_skills.h"
#include "cg_nitmod_hud.h"
#include "cg_nitmod_events.h"
#include "cg_nitmod_stats.h"
#include "cg_nitmod_config.h"
#include "../game/nitmod_announcements.h"

static char nitmodConfigStrings[NITMOD_MAX_CONFIGSTRINGS][NITMOD_CONFIGSTRING_CHARS];
static unsigned int nitmodServerCapabilities;
static nitmodSimpleConfig_t nitmodSimpleConfig;
static nitmodGameState_t nitmodGameState;
static qboolean nitmodClassLimitsReceived;
static int nitmodClassMaxHealth[NUM_PLAYER_CLASSES];
static qboolean nitmodClassHealthReceived;
vmCvar_t n_forceSinglePistol, cg_FTAutoSelect;
vmCvar_t cg_markDistance, cg_projectileNudge, nitmod_sv_fps;
vmCvar_t cg_countryflags, cg_optimizePrediction, cg_locations;
vmCvar_t cg_logFile, cg_clientLog, cg_drawCam, cg_locationMaxChars;
vmCvar_t cg_TDMScorePos, cg_earlyTransition;

qboolean CG_NitmodBulletImpactVisible(int weapon, const vec3_t origin) {
    int distance = NITMOD_UsesOriginalProtocol() ? cg_markDistance.integer : 384;
    return weapon == WP_FG42SCOPE || weapon == WP_GARAND_SCOPE || weapon == WP_K43_SCOPE ||
        Distance(cg.refdef_current->vieworg, origin) < distance;
}

/* Original CG_CalcEntityLerpPositions, ELF 0x5b2e0..0x5b537.
 * Only visual trajectories are shifted, never the network state or prediction. */
int CG_NitmodProjectileTime(const entityState_t *state) {
    int frame, extra;
    if(!state || !cg.snap || !NITMOD_UsesOriginalProtocol() ||
       state->eType != ET_MISSILE || cg_projectileNudge.integer <= 0) return cg.time;
    /* Invalid server values must not divide by zero or overflow timestamps. */
    if(nitmod_sv_fps.integer <= 0) return cg.time;
    frame = 1000 / nitmod_sv_fps.integer;
    extra = state->clientNum == cg.clientNum ? 0 :
        (cg_projectileNudge.integer == 1 ? cg.snap->ping : cg_projectileNudge.integer);
    if(extra < 0 || extra > INT_MAX - frame) return cg.time;
    frame += extra;
    if(cg.time > INT_MAX - frame) return cg.time;
    return cg.time + frame;
}

qboolean CG_NitmodProjectileLerp(centity_t *cent) {
    int time;
    vec3_t start, delta;
    trace_t trace;
    if(!cent || !cg.snap || !NITMOD_UsesOriginalProtocol() ||
       cent->currentState.eType != ET_MISSILE || cg_projectileNudge.integer <= 0) return qfalse;
    time = CG_NitmodProjectileTime(&cent->currentState);
    BG_EvaluateTrajectory(&cent->currentState.pos, time, cent->lerpOrigin, qfalse, cent->currentState.effect2Time);
    BG_EvaluateTrajectory(&cent->currentState.apos, time, cent->lerpAngles, qtrue, cent->currentState.effect2Time);
    if(time != cg.time) {
        /* The original evaluates BOTH endpoints at the shifted time (0x5b3a8).
         * Preserve that behavior; do not invent a different collision sweep. */
        BG_EvaluateTrajectory(&cent->currentState.pos, time, start, qfalse, cent->currentState.effect2Time);
        CG_Trace(&trace, start, vec3_origin, vec3_origin, cent->lerpOrigin, cent->currentState.number, MASK_SHOT);
        if(trace.fraction < 1.0f) {
            VectorSubtract(cent->lerpOrigin, start, delta);
            VectorMA(start, trace.fraction, delta, cent->lerpOrigin);
        }
    }
    return qtrue;
}

unsigned int NITMOD_ClientPreferenceFlags(unsigned int flags, int fixedMove, int singlePistol) {
    if(!NITMOD_UsesOriginalProtocol()) return flags;
    flags &= ~0x60u;
    if(fixedMove > 0) flags |= 0x20u;
    if(singlePistol > 0) flags |= 0x40u;
    return flags;
}

/* Wire-only counters cannot share native PERS_TEAM/PERS_SPAWN_COUNT slots.
 * Keep one owned copy for each engine snapshot buffer, never a global latest
 * snapshot (which would expose future counters while interpolating). */
static struct {
    qboolean valid;
    int serverTime;
    int values[MAX_PERSISTANT];
} wirePersistant[2];

void NITMOD_ResetSnapshotPersistant(void) {
    memset(wirePersistant, 0, sizeof(wirePersistant));
}

const int *NITMOD_WirePersistant(const playerState_t *state) {
    int i;
    if(!state) return NULL;
    for(i = 0; i < 2; ++i) {
        if(state == &cg.activeSnapshots[i].ps && wirePersistant[i].valid &&
           wirePersistant[i].serverTime == cg.activeSnapshots[i].serverTime)
            return wirePersistant[i].values;
    }
    return state->persistant;
}

void NITMOD_TranslateSnapshotPersistant(snapshot_t *snapshot) {
    int wire[MAX_PERSISTANT], i;
    if(!snapshot) return;
    for(i = 0; i < 2; ++i) {
        if(snapshot == &cg.activeSnapshots[i]) {
            wirePersistant[i].valid = NITMOD_UsesOriginalProtocol();
            wirePersistant[i].serverTime = snapshot->serverTime;
            memcpy(wirePersistant[i].values, snapshot->ps.persistant, sizeof(wire));
        }
    }
    if(!NITMOD_UsesOriginalProtocol()) return;
    memcpy(wire, snapshot->ps.persistant, sizeof(wire));
    memset(snapshot->ps.persistant, 0, sizeof(snapshot->ps.persistant));
    snapshot->ps.persistant[PERS_SCORE] = wire[NITMOD_WIRE_PERS_SCORE];
    snapshot->ps.persistant[PERS_HITS] = wire[NITMOD_WIRE_PERS_HITS];
    snapshot->ps.persistant[PERS_TEAM] = wire[NITMOD_WIRE_PERS_TEAM];
    snapshot->ps.persistant[PERS_SPAWN_COUNT] = wire[NITMOD_WIRE_PERS_SPAWN_COUNT];
    snapshot->ps.persistant[PERS_KILLED] = wire[NITMOD_WIRE_PERS_DEATHS];
    snapshot->ps.persistant[PERS_RESPAWNS_LEFT] = wire[NITMOD_WIRE_PERS_RESPAWNS_LEFT];
    snapshot->ps.persistant[PERS_RESPAWNS_PENALTY] = wire[NITMOD_WIRE_PERS_RESPAWNS_PENALTY];
    snapshot->ps.persistant[PERS_REVIVE_COUNT] = wire[NITMOD_WIRE_PERS_REVIVE_COUNT];
    snapshot->ps.persistant[PERS_HWEAPON_USE] = wire[NITMOD_WIRE_PERS_HWEAPON_USE];
    /* No attacker index exists in this original array: slot 2 counts
     * body hits. Do not expose headshot counts as client numbers. */
    snapshot->ps.persistant[PERS_ATTACKER] = -1;
}

/* Original Nitmod weapon_t, distinct from ET's enum. Extensions have independent
 * typed inventories; original-server bomb/poison firing stays authoritative. */
static const int nitmodWireWeapons[52] = {
	WP_NONE, WP_KNIFE, WP_LUGER, WP_MP40, WP_GRENADE_LAUNCHER,
	WP_PANZERFAUST, WP_FLAMETHROWER, WP_COLT, WP_THOMPSON, WP_GRENADE_PINEAPPLE,
	WP_STEN, WP_MEDIC_SYRINGE, WP_AMMO, WP_ARTY, WP_SILENCER, WP_DYNAMITE,
	WP_SMOKETRAIL, VERYBIGEXPLOSION, WP_MEDKIT, WP_BINOCULARS, WP_PLIERS,
	WP_SMOKE_MARKER, WP_KAR98, WP_CARBINE, WP_GARAND, WP_LANDMINE,
	WP_SATCHEL, WP_SATCHEL_DET, WP_SMOKE_BOMB, WP_MOBILE_MG42, WP_K43,
	WP_FG42, WP_DUMMY_MG42, WP_MORTAR, WP_AKIMBO_COLT, WP_AKIMBO_LUGER,
	WP_GPG40, WP_M7, WP_SILENCED_COLT, WP_GARAND_SCOPE, WP_K43_SCOPE,
	WP_FG42SCOPE, WP_MORTAR_SET, WP_MEDIC_ADRENALINE, WP_AKIMBO_SILENCEDCOLT,
	WP_AKIMBO_SILENCEDLUGER, WP_MOBILE_MG42_SET, WP_POISON_SYRINGE, WP_BOMB, WP_TRIPMINE, WP_POISON_BOMB, WP_POISON_MINE
};

int NITMOD_WeaponFromWire(int weapon) {
	return weapon >= 0 && weapon < 52 && nitmodWireWeapons[weapon] >= 0
		? nitmodWireWeapons[weapon] : WP_NONE;
}

/* Original CG_DrawCursorhint switch; not the ET 2.60 hintType_t layout. */
int NITMOD_HintFromWire(int hint) {
	static const int hints[] = {
		HINT_NONE, HINT_FORCENONE, HINT_PLAYER, HINT_ACTIVATE,
		HINT_DOOR, HINT_DOOR_ROTATING, HINT_DOOR_LOCKED, HINT_DOOR_ROTATING_LOCKED,
		HINT_MG42, HINT_BREAKABLE, HINT_BREAKABLE_DYNAMITE, HINT_CHAIR,
		HINT_ALARM, HINT_HEALTH, HINT_KNIFE, HINT_LADDER, HINT_BUTTON, HINT_WATER,
		HINT_WEAPON, HINT_AMMO, HINT_POWERUP, HINT_INVENTORY,
		HINT_ACTIVATE, HINT_ACTIVATE, HINT_ACTIVATE, HINT_FORCENONE, HINT_FORCENONE,
		HINT_ACTIVATE, HINT_FORCENONE, HINT_BUILD, HINT_DISARM, HINT_REVIVE,
		HINT_DYNAMITE, HINT_CONSTRUCTIBLE, HINT_UNIFORM, HINT_LANDMINE,
		HINT_TANK, HINT_SATCHELCHARGE, HINT_PLYR_FRIEND
	};
	return hint >= 0 && hint < (int)(sizeof(hints) / sizeof(hints[0])) ? hints[hint] : HINT_ACTIVATE;
}
int NITMOD_WeaponToWire(int weapon) {
	int i;
	if(weapon < 0) return 0;
	for(i = 0; i < 52; ++i) if(nitmodWireWeapons[i] == weapon) return i;
	return 0;
}

/* Original aWeapID (ELF VA 0x1004a0), indexed here by wire weapon.
 * 26 means no statistics. In particular smoke bomb has no original row. */
int NITMOD_WeaponStatForWeapon(int weapon) {
	static const unsigned char originalStats[52] = {
		26,0,1,3,9,7,8,2,4,9,5,14,26,13,1,11,13,26,26,26,26,12,
		20,19,19,17,26,15,26,18,20,6,18,10,2,1,16,16,2,19,20,6,
		10,26,2,1,18,21,22,23,24,25
	};
	int stat;
	if(weapon < 0 || weapon >= WP_NUM_WEAPONS) return -1;
	if(NITMOD_UsesOriginalProtocol()) {
		stat = originalStats[NITMOD_WeaponToWire(weapon)];
		return stat == 26 ? -1 : stat;
	}
	stat = BG_WeapStatForWeapon(weapon);
	return stat == WS_MAX ? -1 : stat;
}

int NITMOD_WeaponStatCount(void) {
	return NITMOD_UsesOriginalProtocol() ? 26 : WS_MAX;
}

const char *NITMOD_WeaponStatName(int stat) {
	static const char *names[26] = {
		"Knife", "Luger", "Colt", "MP-40", "Thompson", "Sten", "FG-42", "Panzer",
		"F.Thrower", "Grenade", "Mortar", "Dynamite", "Airstrike", "Artillery", "Syringe",
		"Satchel", "G.Launchr", "Landmine", "MG-42 Gun", "Garand", "K43 Rifle",
		"Poison", "Bomb", "Tripmine", "Poison Gas", "Poison Gas Mine"
	};
	if(stat < 0 || stat >= NITMOD_WeaponStatCount()) return "UNKNOWN";
	return NITMOD_UsesOriginalProtocol() ? names[stat] : aWeaponInfo[stat].pszName;
}

const char *NITMOD_WeaponStatCode(int stat) {
	static const char *codes[26] = {
		"KNIF", "LUGR", "COLT", "MP40", "TMPS", "STEN", "FG42", "PNZR",
		"FLAM", "GRND", "MRTR", "DYNA", "ARST", "ARTY", "SRNG", "STCH",
		"GRLN", "LNMN", "MG42", "GARN", "K-43", "POIS", "BOMB", "TPMN", "PGAS", "PGASMINE"
	};
	if(stat < 0 || stat >= NITMOD_WeaponStatCount()) return "UNKNOWN";
	return NITMOD_UsesOriginalProtocol() ? codes[stat] : aWeaponInfo[stat].pszCode;
}

qboolean NITMOD_WeaponStatHasHeadshots(int stat) {
	if(stat < 0 || stat >= NITMOD_WeaponStatCount()) return qfalse;
	if(!NITMOD_UsesOriginalProtocol()) return aWeaponInfo[stat].fHasHeadShots;
	/* Original aWeaponInfo first word, including knife/panzer/flamethrower. */
	return stat <= 8 || (stat >= 18 && stat <= 20);
}

const char *NITMOD_ClientRankName(int team, int rank) {
	if(rank < 0 || rank >= NUM_EXPERIENCE_LEVELS) return "UNKNOWN";
	return (team == TEAM_AXIS ? rankNames_Axis : rankNames_Allies)[rank];
}

const char *NITMOD_PlayerConfigString(int clientNum) {
	if(clientNum < 0 || clientNum >= MAX_CLIENTS) return "";
	/* Original CG_RegisterGraphics starts at 0x2b1 and CG_ServerCommand
	 * subtracts 0x2b1 for player updates: 689, the same as this ET tree.
	 * 64 is NOT CS_PLAYERS in the supplied original binary. */
	return CG_ConfigString(CS_PLAYERS + clientNum);
}

/* Only normalize the predictable ring. External events remain wire IDs. */
int NITMOD_PredictedEventId(int event) {
	int id = event & ~EV_EVENT_BITS;
	int mapped = CG_NitmodEventDispatch(id);
	return mapped >= 0 ? mapped | (event & EV_EVENT_BITS) : event;
}
void NITMOD_NormalizePredictedEvents(playerState_t *state) {
	int i;
	if(!NITMOD_UsesOriginalProtocol()) return;
	for(i = 0; i < MAX_EVENTS; ++i) state->events[i] = NITMOD_PredictedEventId(state->events[i]);
}

/* Original CG_AddEntity/CG_CheckEvents: no spotlight, waypoint, bot-goal
 * or AA-gun slot. Wire 59 is the event base, not ET 2.60's 61. */
/* Original bg_itemlist ELF 0x12ed00, 73 records of 56 bytes. Resolve
 * class names against typed items rather than treating wire IDs as indices. */
int NITMOD_ItemFromWire(int item) {
	static const char *names[] = {
		NULL, "item_health_small", "item_health", "item_health_large", "item_health_cabinet",
		"item_health_turkey", "item_health_breadandmeat", "item_health_wall",
		"weapon_knife", "weapon_luger", "weapon_akimboluger", "weapon_akimbosilencedluger",
		"weapon_thompson", "weapon_dummy", "weapon_sten", "weapon_colt", "weapon_akimbocolt",
		"weapon_akimbosilencedcolt", "weapon_mp40", "weapon_panzerfaust", "weapon_grenadelauncher",
		"weapon_grenadepineapple", "weapon_grenadesmoke", "weapon_smoketrail", "weapon_medic_heal",
		"weapon_dynamite", "weapon_flamethrower", "weapon_class_special", "weapon_arty",
		"weapon_medic_syringe", "weapon_poison_syringe", "weapon_medic_adrenaline", "weapon_magicammo",
		"weapon_magicammo2", "weapon_magicammo2", "weapon_binoculars", "weapon_kar43",
		"weapon_kar43_scope", "weapon_kar98Rifle", "weapon_gpg40", "weapon_gpg40_allied",
		"weapon_M1CarbineRifle", "weapon_garandRifle", "weapon_garandRifleScope", "weapon_fg42",
		"weapon_fg42scope", "weapon_mortar", "weapon_mortar_set", "weapon_landmine", "weapon_poison_landmine",
		"weapon_satchel", "weapon_satchelDetonator", "weapon_smokebomb", "weapon_poisonbomb", "weapon_bomb",
		"weapon_tripmine", "weapon_mobile_mg42", "weapon_mobile_mg42_set", "weapon_silencer",
		"weapon_silencedcolt", "weapon_medic_heal", "ammo_syringe", "ammo_smoke_grenade",
		"ammo_smoke_grenade", "ammo_dynamite", "ammo_disguise", "ammo_airstrike",
		"ammo_landmine", NULL, "ammo_satchel_charge", "team_CTF_redflag", "team_CTF_blueflag", NULL
	};
	int i;
	if(item < 1 || item >= sizeof(names)/sizeof(names[0]) || !names[item]) return 0;
	for(i = 1; i < bg_numItems; ++i)
		if(bg_itemlist[i].classname && !strcmp(names[item], bg_itemlist[i].classname)) return i;
	return 0;
}

int NITMOD_EntityTypeFromWire(int type) {
	static const int types[] = {
		ET_GENERAL, ET_PLAYER, ET_ITEM, ET_MISSILE, ET_MOVER, ET_BEAM,
		ET_PORTAL, ET_SPEAKER, ET_PUSH_TRIGGER, ET_TELEPORT_TRIGGER,
		ET_INVISIBLE, ET_CONCUSSIVE_TRIGGER, ET_OID_TRIGGER, ET_EXPLOSIVE_INDICATOR,
		ET_EXPLOSIVE, ET_ALARMBOX, ET_CORONA, ET_TRAP, ET_GAMEMODEL, ET_FOOTLOCKER,
		ET_FLAMEBARREL, ET_FP_PARTS, ET_FIRE_COLUMN, ET_FIRE_COLUMN_SMOKE,
		ET_RAMJET, ET_FLAMETHROWER_CHUNK, ET_EXPLO_PART, ET_PROP, ET_AI_EFFECT,
		ET_CAMERA, ET_MOVERSCALED, ET_CONSTRUCTIBLE_INDICATOR, ET_CONSTRUCTIBLE,
		ET_CONSTRUCTIBLE_MARKER, ET_BOMB, ET_BEAM_2, ET_TANK_INDICATOR,
		ET_TANK_INDICATOR_DEAD, ET_CORPSE, ET_SMOKER, ET_TEMPHEAD, ET_MG42_BARREL,
		ET_TEMPLEGS, ET_TRIGGER_MULTIPLE, ET_TRIGGER_FLAGONLY, ET_TRIGGER_FLAGONLY_MULTIPLE,
		ET_GAMEMANAGER, ET_CABINET_H, ET_CABINET_A, ET_HEALER, ET_SUPPLIER,
		ET_LANDMINE_HINT, ET_ATTRACTOR_HINT, ET_SNIPER_HINT, ET_LANDMINESPOT_HINT,
		ET_COMMANDMAP_MARKER
	};
	if(type >= 59 && type <= 59 + 255) return ET_EVENTS + type - 59;
	return type >= 0 && type < sizeof(types)/sizeof(types[0]) ? types[type] : ET_INVISIBLE;
}

void NITMOD_TranslateSnapshotWeapons(snapshot_t *snapshot) {
	playerState_t *ps = &snapshot->ps;
	int ammo[MAX_WEAPONS], clip[MAX_WEAPONS], heat[MAX_WEAPONS];
	int owned[MAX_WEAPONS / 32], i, target;
	memcpy(ammo, ps->ammo, sizeof(ammo));
	memcpy(clip, ps->ammoclip, sizeof(clip));
	memcpy(heat, ps->weapHeat, sizeof(heat));
	memcpy(owned, ps->weapons, sizeof(owned));
	memset(ps->ammo, 0, sizeof(ps->ammo));
	memset(ps->ammoclip, 0, sizeof(ps->ammoclip));
	memset(ps->weapHeat, 0, sizeof(ps->weapHeat));
	memset(ps->weapons, 0, sizeof(ps->weapons));
	for(i = 0; i < 52; ++i) {
		target = nitmodWireWeapons[i];
		if(target < 0) continue;
		ps->ammo[target] = ammo[i]; ps->ammoclip[target] = clip[i]; ps->weapHeat[target] = heat[i];
		if((unsigned int)owned[i / 32] & (1u << (i % 32)))
			ps->weapons[target / 32] |= (int)(1u << (target % 32));
	}
	ps->weapon = NITMOD_WeaponFromWire(ps->weapon);
	ps->nextWeapon = NITMOD_WeaponFromWire(ps->nextWeapon);
	/* Original PM_Weapon uses 5/6 for fire/alternate fire; PM_BeginWeaponReload
	 * writes 7. ET 2.60 inserts READYING/RELAXING before these three states. */
	switch(ps->weaponstate) {
	case 5: ps->weaponstate = WEAPON_FIRING; break;
	case 6: ps->weaponstate = WEAPON_FIRINGALT; break;
	case 7: ps->weaponstate = WEAPON_RELOADING; break;
	}
	/* Pickup hints carry a weapon ID instead of a progress value. Convert
	 * it exactly once alongside the snapshot's other weapon fields. */
	if(ps->serverCursorHint == 18 || ps->serverCursorHint == 19)
		ps->serverCursorHintVal = NITMOD_WeaponFromWire(ps->serverCursorHintVal);
	ps->serverCursorHint = NITMOD_HintFromWire(ps->serverCursorHint);
	for(i = 0; i < snapshot->numEntities && i < MAX_ENTITIES_IN_SNAPSHOT; ++i) {
		entityState_t *es = &snapshot->entities[i];
		int event;
		es->eType = NITMOD_EntityTypeFromWire(es->eType);
		if(es->eType == ET_ITEM) es->modelindex = NITMOD_ItemFromWire(es->modelindex);
		event = es->eType >= ET_EVENTS ? es->eType - ET_EVENTS : es->event & ~EV_EVENT_BITS;
		/* Effects such as rubble overload weapon with gravity flags. */
		if(es->eType == ET_PLAYER || es->eType == ET_CORPSE || es->eType == ET_MISSILE ||
			(event >= 25 && event <= 39) || event == 48 || event == 49 || (event >= 52 && event <= 55) ||
			event == 67 || event == 70 || event == 71 || event == 95) {
			es->weapon = NITMOD_WeaponFromWire(es->weapon);
			es->nextWeapon = NITMOD_WeaponFromWire(es->nextWeapon);
		}
	}
}

/* nitrox_ReadNKey 0xf8e30: base64, 32 decoded characters, checksum % 100.
 * Unlike the original unbounded read, reject malformed input atomically. */
qboolean NITMOD_DecodeNKey(const char *encoded, int length, char guid[33]) {
	static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char decoded[33];
	unsigned int accumulator = 0;
	int i, bits = 0, count = 0, checksum = 0;
	if(!encoded || !guid || length != 44 || encoded[43] != '=') return qfalse;
	for(i = 0; i < 43; ++i) {
		const char *digit;
		if(!encoded[i] || !(digit = strchr(alphabet, encoded[i]))) return qfalse;
		accumulator = (accumulator << 6) | (unsigned int)(digit - alphabet);
		bits += 6;
		if(bits >= 8) {
			int value;
			bits -= 8;
			value = (accumulator >> bits) & 255;
			/* Generated original keys are alphanumeric; also exclude every
			 * character unsafe in userinfo before exposing the key. */
			if(!((value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z') ||
				(value >= '0' && value <= '9')) || count >= 32) return qfalse;
			decoded[count++] = (char)value;
			checksum += value;
		}
	}
	if(count != 32 || (accumulator & 3) || checksum % 100) return qfalse;
	decoded[32] = 0;
	memcpy(guid, decoded, sizeof(decoded));
	return qtrue;
}

void NITMOD_ReadNKey(void) {
	static qboolean warned;
	fileHandle_t file = 0;
	char encoded[44], guid[33];
	int length;
	trap_Cvar_Set("n_guid", "");
	length = trap_FS_FOpenFile("nkey.dat", &file, FS_READ);
	if(file && length == sizeof(encoded)) {
		trap_FS_Read(encoded, sizeof(encoded), file);
		trap_FS_FCloseFile(file);
		if(NITMOD_DecodeNKey(encoded, sizeof(encoded), guid)) {
			trap_Cvar_Set("n_guid", guid);
			return;
		}
	} else if(file) {
		trap_FS_FCloseFile(file);
	} else if(length < 0 && NITMOD_GenerateMissingNKey(guid)) {
		trap_Cvar_Set("n_guid", guid);
		return;
	}
	if(!warned) {
		CG_Printf("^3Nitmod: nkey.dat could not be loaded or created; no GUID supplied. Existing files are preserved.\n");
		warned = qtrue;
	}
}

int NITMOD_ParseLatchedClass(const char *info, int currentClass) {
	int value;
	const char *text = Info_ValueForKey(info, "lc");
	if(!NITMOD_ParseProtocolSigned(text, &value) || value < PC_SOLDIER || value > PC_COVERTOPS)
		return currentClass;
	return value;
}

/* Original player tokens sc=0x59, tv=0x5a, xp=0x70. Despite its name,
 * xp carries unlock masks, not XP counters. Reject malformed vectors atomically. */
qboolean NITMOD_DecodeClientSkills(const char *text, int *nativeLevels, int *displayLevels) {
    int levels[SK_NUM_SKILLS], i, maximum;
    /* text can point into Info_ValueForKey's rotating scratch buffers.
     * Consume it before protocol detection performs additional Info lookups. */
    if(!nativeLevels || !displayLevels || !NITMOD_ParseSkillDigits(text, 9, levels)) return qfalse;
    maximum = NITMOD_UsesOriginalProtocol() ? NITMOD_SKILL_LEVEL_COUNT - 1 : NUM_SKILL_LEVELS - 1;
    for(i = 0; i < SK_NUM_SKILLS; ++i) if(levels[i] > maximum) return qfalse;
    for(i = 0; i < SK_NUM_SKILLS; ++i) {
        displayLevels[i] = levels[i];
        nativeLevels[i] = levels[i] < NUM_SKILL_LEVELS ? levels[i] : NUM_SKILL_LEVELS - 1;
    }
    return qtrue;
}

void NITMOD_ParseClientExtras(const char *info, clientInfo_t *client) {
    const char *cursor;
    int value, values[SK_NUM_SKILLS] = {0}, count = 0;
    if(!client) return;
    client->nitmodTV = client->nitmodShoutcaster = qfalse;
    if(!info || !NITMOD_UsesOriginalProtocol()) return;
    if(NITMOD_ParseProtocolSigned(Info_ValueForKey(info, "sc"), &value))
        client->nitmodShoutcaster = value != 0;
    if(NITMOD_ParseProtocolSigned(Info_ValueForKey(info, "tv"), &value))
        client->nitmodTV = value != 0;
    memset(client->nitmodSkillMasks, 0, sizeof(client->nitmodSkillMasks));
    cursor = Info_ValueForKey(info, "xp");
    while(*cursor) {
        char number[16];
        int length = 0;
        while(*cursor == ' ') ++cursor;
        if(!*cursor) break;
        if(count == SK_NUM_SKILLS) return;
        while(*cursor && *cursor != ' ') {
            if(length >= sizeof(number) - 1) return;
            number[length++] = *cursor++;
        }
        number[length] = 0;
        if(!NITMOD_ParseProtocolSigned(number, &values[count])) return;
        ++count;
    }
    memcpy(client->nitmodSkillMasks, values, sizeof(values));
}

static nitmodSkillThresholds_t clientSkillThresholds;
static qboolean clientSkillThresholdsReady;
static const char *NITMOD_ClientSkillValue(void *context, const char *key) {
	return Info_ValueForKey((const char *)context, key);
}
qboolean NITMOD_UpdateClientSkillThresholds(const char *info) {
	if(!info || !NITMOD_ParseSkillThresholds(NITMOD_ClientSkillValue, (void *)info, &clientSkillThresholds)) return qfalse;
	clientSkillThresholdsReady = qtrue;
	return qtrue;
}
int NITMOD_ClientSkillNextThreshold(int skill, int level) {
	if(skill < 0 || skill >= SK_NUM_SKILLS || level < 0) return -1;
	if(!NITMOD_UsesOriginalProtocol()) return level < NUM_SKILL_LEVELS - 1 ? skillLevels[level + 1] : -1;
	if(level >= 5) return -1;
	if(!clientSkillThresholdsReady) {
		NITMOD_DefaultSkillThresholds(&clientSkillThresholds);
		clientSkillThresholdsReady = qtrue;
	}
	return clientSkillThresholds.threshold[skill][level + 1];
}

unsigned int NITMOD_NewSkillUnlocks(int oldMask, int newMask) {
    return (unsigned int)newMask & ~(unsigned int)oldMask & 0x3eu;
}

qboolean NITMOD_ClientSkillUnlocked(int client, int skill, int level) {
    if(client < 0 || client >= MAX_CLIENTS || skill < 0 || skill >= SK_NUM_SKILLS ||
       level < 0 || level >= NITMOD_SKILL_LEVEL_COUNT) return qfalse;
    if(NITMOD_UsesOriginalProtocol())
        return ((unsigned int)cgs.clientinfo[client].nitmodSkillMasks[skill] & (1u << level)) != 0;
    return cgs.clientinfo[client].skill[skill] >= level;
}

const char *CG_NitmodSpectatorLabel(const clientInfo_t *client, int ping) {
    if(ping == -1) return "^3CONNECTING";
    if(!client || !NITMOD_UsesOriginalProtocol()) return "^3SPECTATOR";
    if(client->nitmodTV) return client->nitmodShoutcaster ? "^5TV^7|^3SHOUTCASTER" : "^5TV^7|^3SPECTATOR";
    return client->nitmodShoutcaster ? "^3SHOUTCASTER" : "^3SPECTATOR";
}

int NITMOD_ParseCountryCode(const char *value) {
    int country;
    if(!NITMOD_ParseProtocolInteger(value, &country) || country < 0 || country >= 255) return 255;
    return country;
}

qboolean NITMOD_ClassIsDisabled(int team, int playerClass) {
	int limits[5], i, count = 0, maximum;
	if(!nitmodClassLimitsReceived || team == TEAM_SPECTATOR ||
		playerClass < PC_SOLDIER || playerClass > PC_COVERTOPS) return qfalse;
	limits[0] = nitmodGameState.maxSoldiers; limits[1] = nitmodGameState.maxMedics;
	limits[2] = nitmodGameState.maxEngineers; limits[3] = nitmodGameState.maxFieldops;
	limits[4] = nitmodGameState.maxCovertops;
	maximum = limits[playerClass];
	if(maximum == -1) return qfalse;
	for(i = 0; i < cgs.maxclients && i < MAX_CLIENTS; ++i) {
		const clientInfo_t *client = &cgs.clientinfo[i];
		if(i == cg.clientNum || !client->infoValid || client->team != team) continue;
		if(client->cls == playerClass || client->latchedClass == playerClass) ++count;
	}
	return count >= maximum;
}
qboolean NITMOD_WeaponQuotaDisabled(int weapon, int playerClass, int teamCount, int weaponCount) {
	int maximum;
	/* The reconstructed server sends the same # settings with native weapon
	 * IDs. Applying quotas must not depend on legacy ID translation. */
	if(!NITMOD_UsesNitmodHud() || !nitmodClassLimitsReceived) return qfalse;
	switch(weapon) {
		case WP_MP40: case WP_THOMPSON: return qfalse;
		case WP_STEN: return playerClass != PC_COVERTOPS && !(nitmodGameState.weapons & 512);
		case WP_PANZERFAUST:
			if(cgs.maxclients > 0 && (float)teamCount / ((float)cgs.maxclients * .5f) <=
				(float)nitmodGameState.panzerRestriction * .01f) return qtrue;
			maximum = nitmodGameState.maxPanzers; break;
		case WP_MOBILE_MG42: maximum = nitmodGameState.maxMG42s; break;
		case WP_FLAMETHROWER: maximum = nitmodGameState.maxFlamers; break;
		case WP_MORTAR: maximum = nitmodGameState.maxMortars; break;
		case WP_GPG40: case WP_M7: maximum = nitmodGameState.maxRifleGrenades; break;
		default: return qfalse;
	}
	return maximum != -1 && weaponCount >= maximum;
}

static nitmodMapEndStats_t nitmodMapEndStats;
static nitmodObjectiveEvent_t nitmodLastObjectiveEvent;
vmCvar_t nitmodHitSounds;
vmCvar_t cg_pmSounds;
vmCvar_t cg_shoveSounds;
vmCvar_t cg_noGreetingSounds;
vmCvar_t cg_drawBanners;
static char nitmodBanner[MAX_STRING_CHARS];
static int nitmodBannerTime;

/* Original CG_BannerPrint: escaped newlines, soft wrap at 55 visible
 * characters and a hard word break at 65. Color escapes have zero width. */
void NITMOD_FormatBanner(const char *text, char *out, int size) {
	int used = 0, visible = 0;
	if(!out || size <= 0) return;
	if(!text) text = "";
	while(*text && used < size - 1) {
		if(*text == '\n' || (text[0] == '\\' && text[1] == 'n')) {
			text += *text == '\n' ? 1 : 2;
			out[used++] = '\n'; visible = 0;
			continue;
		}
		if(Q_IsColorString(text)) {
			if(size - used < 3) break;
			out[used++] = *text++; out[used++] = *text++;
			continue;
		}
		if(visible >= 55 && *text == ' ') {
			out[used++] = '\n'; ++text; visible = 0;
			continue;
		}
		if(visible >= 65) {
			/* Keep room for the character as well as the inserted break. */
			if(size - used < 3) break;
			out[used++] = '\n'; visible = 0;
		}
		out[used++] = *text++; ++visible;
	}
	out[used] = 0;
}
static int nitmodKDCursor;
typedef struct {
	char name[256];
	char value[256];
	char original[256];
	qboolean hasOriginal;
} nitmodForcedCvar_t;
static nitmodForcedCvar_t nitmodForcedCvars[64];
static int nitmodForcedCvarCount;

static void NITMOD_ForceCvarCommand(void) {
	static const char *protectedNames[] = { "cl_profile", "x", "name", "sensitivity", "n_guid" };
	char name[256], value[256];
	int i;
	if(cg.demoPlayback || trap_Argc() != 3 || nitmodForcedCvarCount >= 64) return;
	if(!*CG_Argv(1) || strlen(CG_Argv(1)) >= sizeof(name) || strlen(CG_Argv(2)) >= sizeof(value)) return;
	Q_strncpyz(name, CG_Argv(1), sizeof(name));
	Q_strncpyz(value, CG_Argv(2), sizeof(value));
	for(i = 0; name[i]; ++i) {
		unsigned char c = name[i];
		if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || c == '_')) return;
	}
	for(i = 0; i < sizeof(protectedNames) / sizeof(protectedNames[0]); ++i)
		if(!Q_stricmp(name, protectedNames[i])) return;
	for(i = 0; i < nitmodForcedCvarCount; ++i)
		if(!Q_stricmp(name, nitmodForcedCvars[i].name)) break;
	if(i == nitmodForcedCvarCount) {
		Q_strncpyz(nitmodForcedCvars[i].name, name, sizeof(nitmodForcedCvars[i].name));
		trap_Cvar_VariableStringBuffer(name, nitmodForcedCvars[i].original,
			sizeof(nitmodForcedCvars[i].original));
		nitmodForcedCvars[i].hasOriginal = qtrue;
		++nitmodForcedCvarCount;
	}
	Q_strncpyz(nitmodForcedCvars[i].value, value, sizeof(nitmodForcedCvars[i].value));
}

void NITMOD_RestoreForcedCvars(void) {
	int i;

	/* A map restart tears down and recreates cgame in the same engine process.
	 * Put every cvar back before the new VM accepts another force list.  Keep
	 * the first observed value when a server changes one cvar repeatedly. */
	for(i = 0; i < nitmodForcedCvarCount; ++i) {
		const nitmodForcedCvar_t *entry = &nitmodForcedCvars[i];
		if(!entry->hasOriginal || !entry->name[0]) continue;
		trap_Cvar_Set(entry->name, entry->original);
	}
	nitmodForcedCvarCount = 0;
	memset(nitmodForcedCvars, 0, sizeof(nitmodForcedCvars));
}

void NITMOD_ApplyForcedCvars(void) {
	int i;
	char current[256];
	if(cg.demoPlayback) return;
	for(i = 0; i < nitmodForcedCvarCount; ++i) {
		const nitmodForcedCvar_t *entry = &nitmodForcedCvars[i];
		trap_Cvar_VariableStringBuffer(entry->name, current, sizeof(current));
		if(!Q_stricmp(entry->value, current)) continue;
		CG_Printf("server forcing cvar %s to %s\n", entry->name, entry->value);
		trap_Cvar_Register(NULL, entry->name, entry->value, 0);
		trap_Cvar_Set(entry->name, entry->value);
	}
}

qboolean NITMOD_DisplayCommand(const char *command) {
	if(NITMOD_UsesOriginalProtocol() && !strcmp(command, "sl")) {
		char info[256];
		trap_Args(info, sizeof(info));
		NITMOD_UpdateClientSkillThresholds(info);
		return qtrue;
	}
	int kind, count, start, i, kills[MAX_CLIENTS], deaths[MAX_CLIENTS];
	if(!strcmp(command, "cvs")) {
		char name[MAX_CVAR_VALUE_STRING], value[MAX_CVAR_VALUE_STRING];
		int request;
		if(cg.demoPlayback || trap_Argc() != 3 || !NITMOD_ParseProtocolInteger(CG_Argv(1), &request) ||
		   !*CG_Argv(2) || strlen(CG_Argv(2)) >= sizeof(name)) return qtrue;
		Q_strncpyz(name, CG_Argv(2), sizeof(name));
		for(i = 0; name[i]; ++i) {
			unsigned char c = name[i];
			if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
				(c >= '0' && c <= '9') || c == '_')) return qtrue;
		}
		trap_Cvar_VariableStringBuffer(name, value, sizeof(value));
		/* Do not turn an unrepresentable value into a false empty-cvar report.
		 * The original wire protocol has no escaping for quoted fields. */
		if(strpbrk(value, "\"\\\r\n")) return qtrue;
		trap_SendClientCommand(va("cvs %i %s \"%s\"\n", request, name, value));
		return qtrue;
	}
	if(!strcmp(command, "fc")) {
		NITMOD_ForceCvarCommand();
		return qtrue;
	}
	if(!strcmp(command, "gsnd")) {
		char path[MAX_QPATH];
		sfxHandle_t sound;
		if(trap_Argc() != 2 || !cg.snap || cg.snap->ps.clientNum < 0 ||
			cg.snap->ps.clientNum >= MAX_CLIENTS) return qtrue;
		trap_Cvar_Update(&cg_noGreetingSounds);
		if(cg_noGreetingSounds.integer) return qtrue;
		/* Do not truncate server paths into a different asset name. */
		if(!*CG_Argv(1) || strlen(CG_Argv(1)) >= sizeof(path)) return qtrue;
		Q_strncpyz(path, CG_Argv(1), sizeof(path));
		sound = trap_S_RegisterSound(path, qfalse);
		if(sound > 0) trap_S_StartSound(NULL, cg.snap->ps.clientNum, CHAN_VOICE, sound);
		return qtrue;
	}
	if(!strcmp(command, "pop")) {
		if(trap_Argc() == 2) {
			char text[MAX_STRING_CHARS];
			Q_strncpyz(text, CG_LocalizeServerCommand(CG_Argv(1)), sizeof(text));
			if(!CG_NitmodGlobalAwardActive()) CG_NitmodNotificationStart(text, cg.time);
			CG_Printf("%s^7\n", text);
		}
		return qtrue;
	}
	if(!strcmp(command, "bp")) {
		if(trap_Argc() != 3 || !NITMOD_ParseProtocolInteger(CG_Argv(1), &kind) || kind < 0 || kind > 2) return qtrue;
		trap_Cvar_Update(&cg_drawBanners);
		if(!cg_drawBanners.integer) return qtrue;
		if(kind == 2) {
			NITMOD_FormatBanner(CG_LocalizeServerCommand(CG_Argv(2)), nitmodBanner, sizeof(nitmodBanner));
			nitmodBannerTime = cg.time;
		} else if(kind == 0) {
			CG_AddToTeamChat(CG_LocalizeServerCommand(CG_Argv(2)), -1);
		} else {
			CG_Printf("%s\n", CG_LocalizeServerCommand(CG_Argv(2)));
		}
		return qtrue;
	}
	if(strcmp(command, "kd0") && strcmp(command, "kd1")) return qfalse;
	start = !strcmp(command, "kd0") ? 0 : nitmodKDCursor;
	if(!NITMOD_ParseProtocolInteger(CG_Argv(1), &count) || count < 0 || count > MAX_CLIENTS ||
		start < 0 || start > cg.numScores || count > cg.numScores - start ||
		start + count > MAX_CLIENTS || trap_Argc() != 2 + count * 3) return qtrue;
	for(i = 0; i < count; ++i) {
		int client = cg.scores[start + i].client;
		/* Original consumes only kills/deaths at 3+3*i, 4+3*i and uses score order. */
		if(client < 0 || client >= MAX_CLIENTS ||
			!NITMOD_ParseProtocolSigned(CG_Argv(3 + i * 3), &kills[i]) ||
			!NITMOD_ParseProtocolSigned(CG_Argv(4 + i * 3), &deaths[i])) return qtrue;
	}
	for(i = 0; i < count; ++i) {
		clientInfo_t *client = &cgs.clientinfo[cg.scores[start + i].client];
		cg.scores[start + i].kills = kills[i];
		cg.scores[start + i].deaths = deaths[i];
		client->kills = kills[i]; client->deaths = deaths[i];
	}
	nitmodKDCursor = start + count;
	return qtrue;
}

void NITMOD_DrawBanner(void) {
	char line[MAX_STRING_CHARS + 2];
	const char *cursor = nitmodBanner;
	char lastColor = '7';
	float *color;
	nitmodHudAnchor_t previous;
	int y = 0;
	int rowHeight = (int)(CG_Text_Height_Ext("A", .2f, 1, &cgs.media.limboFont1) * 1.5f);
	if(rowHeight < 1) rowHeight = 1;
	if(!cg_drawBanners.integer || !*cursor) return;
	color = CG_FadeColor(nitmodBannerTime, 10000);
	if(!color) { nitmodBanner[0] = 0; return; }
	/* Original Nitmod lays top-centre banners out in the 640x480 HUD area.
	 * Keep that area centred on wide displays instead of stretching its X axis. */
	previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
	while(*cursor && y < SCREEN_HEIGHT) {
		int n = 2;
		line[0] = '^'; line[1] = lastColor;
		while(*cursor && *cursor != '\n' && n < sizeof(line) - 1) {
			if(Q_IsColorString(cursor)) lastColor = cursor[1];
			line[n++] = *cursor++;
		}
		line[n] = 0;
		if(*cursor == '\n') ++cursor;
		y += rowHeight;
		CG_Text_Paint_Ext((int)((SCREEN_WIDTH - CG_Text_Width_Ext(line, 0.2f, 0, &cgs.media.limboFont1)) * 0.5f),
			y, 0.2f, 0.2f, color, line, 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont1);
	}
	CG_NitmodHudAnchor(previous);
}
static sfxHandle_t nitmodPrivateMessageSound;

void NITMOD_ShoveSound(int entityNum) {
	if(entityNum < 0 || entityNum >= MAX_GENTITIES) return;
	trap_Cvar_Update(&cg_shoveSounds);
	if(!cg_shoveSounds.integer || cgs.media.sfx_bullet_fleshhit[0] <= 0) return;
	trap_S_StartSoundVControl(NULL, entityNum, CHAN_AUTO, cgs.media.sfx_bullet_fleshhit[0], 255);
}

void NITMOD_ShoveSoundCommand(void) {
	int entityNum;
	if(trap_Argc() == 2 && NITMOD_ParseProtocolInteger(CG_Argv(1), &entityNum))
		NITMOD_ShoveSound(entityNum);
}

void NITMOD_PrivateMessageSound(int clientNum) {
	if(clientNum != cg.clientNum || clientNum < 0 || clientNum >= MAX_CLIENTS) return;
	trap_Cvar_Update(&cg_pmSounds);
	if(!cg_pmSounds.integer) return;
	if(!nitmodPrivateMessageSound)
		nitmodPrivateMessageSound = trap_S_RegisterSound("sound/nit/pm.wav", qfalse);
	trap_S_StartSoundVControl(NULL, clientNum, CHAN_VOICE, nitmodPrivateMessageSound, 255);
}
static qboolean nitmodHitSoundsRegistered;
qboolean NITMOD_UsesOriginalProtocol(void) {
	const char *info = CG_ConfigString(CS_SERVERINFO);
	return !Q_stricmp(Info_ValueForKey(info, "gamename"), "nitmod") &&
		Q_stricmp(Info_ValueForKey(info, "nitmod_csLayout"), "et260");
}
qboolean NITMOD_UsesNitmodHud(void) {
	return !Q_stricmp(Info_ValueForKey(CG_ConfigString(CS_SERVERINFO), "gamename"), "nitmod");
}
int NITMOD_CoreConfigToWire(int index) {
	switch(index) {
	case CS_MUSIC_QUEUE: return 25;
	case CS_SCRIPT_MOVER_NAMES: return 26;
	case CS_CONSTRUCTION_NAMES: return 27;
	case CS_VERSIONINFO: return -1;
	case CS_REINFSEEDS: return 28;
	case CS_SERVERTOGGLES: return 29;
	case CS_GLOBALFOGVARS: return 30;
	case CS_AXIS_MAPS_XP: return 31;
	case CS_ALLIED_MAPS_XP: return 32;
	case CS_INTERMISSION_START_TIME: return 33;
	case CS_ENDGAME_STATS: return 34;
	default: return index;
	}
}
int NITMOD_CoreConfigFromWire(int index) {
	switch(index) {
	case 25: return CS_MUSIC_QUEUE;
	case 26: return CS_SCRIPT_MOVER_NAMES;
	case 27: return CS_CONSTRUCTION_NAMES;
	case 28: return CS_REINFSEEDS;
	case 29: return CS_SERVERTOGGLES;
	case 30: return CS_GLOBALFOGVARS;
	case 31: return CS_AXIS_MAPS_XP;
	case 32: return CS_ALLIED_MAPS_XP;
	case 33: return CS_INTERMISSION_START_TIME;
	case 34: return CS_ENDGAME_STATS;
	/* These original slots must not trigger unrelated ET callbacks. */
	case 35: case 36: case 37: case 38: case 39: return -1;
	default: return index;
	}
}
int NITMOD_TagConnectBase(void) {
	return NITMOD_UsesOriginalProtocol() ? 0x309 : CS_TAGCONNECTS;
}
static sfxHandle_t nitmodHeadHitSound;
static sfxHandle_t nitmodTeamHitSound;
static sfxHandle_t nitmodSnapshotHeadSound, nitmodSnapshotBodySound;
static qboolean nitmodSnapshotSoundsRegistered;

/* Original CG_CheckLocalSounds: body first, then head, once per snapshot
 * counter increase (not once per bullet/count delta). Keep separate from
 * explicit nhs/event sounds and their separate sample selection. */
void NITMOD_SnapshotHitSounds(const playerState_t *oldState, const playerState_t *newState) {
    const int *oldValues, *newValues;
    qboolean body, head;
    if(!oldState || !newState || !NITMOD_UsesOriginalProtocol() || !nitmodHitSounds.integer ||
       newState->clientNum < 0 || newState->clientNum >= MAX_CLIENTS ||
       oldState->clientNum != newState->clientNum || newState->persistant[PERS_TEAM] == TEAM_SPECTATOR)
        return;
    oldValues = NITMOD_WirePersistant(oldState);
    newValues = NITMOD_WirePersistant(newState);
    body = newValues[NITMOD_WIRE_PERS_BODYHITS] > oldValues[NITMOD_WIRE_PERS_BODYHITS];
    head = newValues[NITMOD_WIRE_PERS_HITS] > oldValues[NITMOD_WIRE_PERS_HITS];
    if(!body && !head) return;
    if(!nitmodSnapshotSoundsRegistered) {
        nitmodSnapshotBodySound = trap_S_RegisterSound("sound/hitsounds/body.wav", qfalse);
        nitmodSnapshotHeadSound = trap_S_RegisterSound("sound/hitsounds/head.wav", qfalse);
        nitmodSnapshotSoundsRegistered = qtrue;
    }
    if(body && nitmodSnapshotBodySound > 0)
        trap_S_StartSound(NULL, newState->clientNum, CHAN_VOICE, nitmodSnapshotBodySound);
    if(head && nitmodSnapshotHeadSound > 0)
        trap_S_StartSound(NULL, newState->clientNum, CHAN_VOICE, nitmodSnapshotHeadSound);
}

static qboolean NITMOD_HasArgumentCount( const char *command, int expected ) {
	if( trap_Argc() == expected ) {
		return qtrue;
	}
	CG_Printf( "Nitmod: ignoring malformed %s command\n", command );
	return qfalse;
}

void NITMOD_ClearConfigStrings( void ) {
	clientSkillThresholdsReady = qfalse;
	CG_NitmodObituaryReset();
	CG_NitmodHudReset();
	CG_NitmodGlobalStatsReset();
	nitmodClassLimitsReceived = qfalse;
	nitmodClassHealthReceived = qfalse;
	memset( nitmodClassMaxHealth, 0, sizeof( nitmodClassMaxHealth ) );
	nitmodForcedCvarCount = 0;
	memset(nitmodForcedCvars, 0, sizeof(nitmodForcedCvars));
	nitmodHitSoundsRegistered = qfalse;
	nitmodHeadHitSound = nitmodTeamHitSound = 0;
	nitmodSnapshotHeadSound = nitmodSnapshotBodySound = 0;
	nitmodSnapshotSoundsRegistered = qfalse;
	nitmodBanner[0] = 0;
	nitmodBannerTime = nitmodKDCursor = 0;
	nitmodPrivateMessageSound = 0;
	memset( nitmodConfigStrings, 0, sizeof( nitmodConfigStrings ) );
	nitmodServerCapabilities = 0;
	memset( &nitmodSimpleConfig, 0, sizeof( nitmodSimpleConfig ) );
	memset( &nitmodGameState, 0, sizeof( nitmodGameState ) );
	nitmodGameState.dmWinnerClient = -1;
	memset( &nitmodMapEndStats, 0, sizeof( nitmodMapEndStats ) );
	memset( &nitmodLastObjectiveEvent, 0, sizeof( nitmodLastObjectiveEvent ) );
}

void NITMOD_AdvertiseCapabilities( void ) {
	/* Original servers do not implement our reconstruction handshake. */
	if ( !cg.demoPlayback &&
		!Q_stricmp( Info_ValueForKey( CG_ConfigString( CS_SERVERINFO ),
			"nitmod_csLayout" ), "et260" ) ) {
		trap_SendClientCommand( va( NITMOD_CAPABILITIES_COMMAND " %i %u",
			NITMOD_PROTOCOL_VERSION, NITMOD_FEATURES_CLIENT ) );
	}
}

/* Original nitmod_ClientCheck / CG_ServerCommand. This requests mod state;
 * it is not an integrity attestation and grants no reconstructed features. */
void NITMOD_BeginOriginalSession(void) {
	char game[MAX_QPATH];
	if(cg.demoPlayback || !NITMOD_UsesOriginalProtocol()) return;
	trap_Cvar_VariableStringBuffer("fs_game", game, sizeof(game));
	if(Q_stricmp(game, "nitmod")) {
		/* The original disconnects here. Keep the session intact and explain
		 * the mismatch instead of silently accepting a different mod folder. */
		CG_Printf("^3Nitmod: original session synchronization requires fs_game nitmod.\n");
		return;
	}
	NITMOD_ReadNKey();
	trap_SendClientCommand("imhere");
}

qboolean NITMOD_OriginalSessionCommand(const char *command) {
	if(!command || strcmp(command, "handshake") || !NITMOD_UsesOriginalProtocol()) return qfalse;
	if(cg.demoPlayback || trap_Argc() != 1) return qtrue;
	/* The first literal is pinned from original cgame ELF VA 0x10dad8
	 * (Ghidra 0x11dad8). rhs clears the server's per-client handshake latch. */
	trap_SendClientCommand("rhs");
	trap_SendClientCommand("handshake");
	trap_SendClientCommand("getdata");
	return qtrue;
}

qboolean NITMOD_ServerSupports( unsigned int feature ) {
	return ( nitmodServerCapabilities & feature ) == feature;
}

qboolean NITMOD_ProtocolCommand( const char *command ) {
	int protocolVersion;
	unsigned int capabilities;

	if ( Q_stricmp( command, NITMOD_CAPABILITIES_ACK_COMMAND ) ) {
		return qfalse;
	}
	if( !NITMOD_HasArgumentCount( NITMOD_CAPABILITIES_ACK_COMMAND, 3 ) ) {
		return qtrue;
	}
	if( !NITMOD_ParseProtocolInteger( CG_Argv( 1 ), &protocolVersion ) ||
		!NITMOD_ParseProtocolUnsigned( CG_Argv( 2 ), &capabilities ) ) {
		return qtrue;
	}
	if ( protocolVersion != NITMOD_PROTOCOL_VERSION ) {
		CG_Printf( "Nitmod: server protocol %i is unsupported\n", protocolVersion );
		nitmodServerCapabilities = 0;
		CG_setClientFlags();
		return qtrue;
	}
	nitmodServerCapabilities = capabilities & NITMOD_FEATURES_CLIENT;
	CG_setClientFlags();
	return qtrue;
}

const nitmodSimpleConfig_t *NITMOD_SimpleConfig( void ) {
	return &nitmodSimpleConfig;
}

const nitmodGameState_t *NITMOD_GameState( void ) {
	return &nitmodGameState;
}

const nitmodMapEndStats_t *NITMOD_MapEndStats( void ) {
	return &nitmodMapEndStats;
}

const nitmodObjectiveEvent_t *NITMOD_LastObjectiveEvent( void ) {
	return &nitmodLastObjectiveEvent;
}

void NITMOD_SimpleConfigCommand( void ) {
	if( !NITMOD_HasArgumentCount( "scs", 12 ) ) {
		return;
	}
	if( !NITMOD_ParseSimpleConfigSnapshot( trap_Argc(), CG_Argv, &nitmodSimpleConfig ) ) {
		return;
	}

	/* Native ET has this state in CS_FILTERCAMS; honour the Nitmod update
	 * immediately so custom servers and native clients cannot drift. */
	cg.filtercams = nitmodSimpleConfig.filterCams ? qtrue : qfalse;
}

void NITMOD_GameStateCommand( void ) {
	if( !NITMOD_HasArgumentCount( "#", 21 ) ) {
		return;
	}
	if( !NITMOD_ParseGameStateSnapshot( trap_Argc(), CG_Argv, &nitmodGameState ) ) {
		return;
	}
	nitmodClassLimitsReceived = qtrue;
}

void NITMOD_ClassHealthCommand( void ) {
	int values[NUM_PLAYER_CLASSES] = { 0 };
	int playerClass;

	if( !NITMOD_HasArgumentCount( "nch", NUM_PLAYER_CLASSES + 1 ) ) {
		return;
	}
	for( playerClass = PC_SOLDIER; playerClass <= PC_COVERTOPS; ++playerClass ) {
		if( !NITMOD_ParseProtocolInteger( CG_Argv( playerClass + 1 ), &values[playerClass] ) ||
			values[playerClass] < 0 || values[playerClass] > 32767 ) {
			return;
		}
	}
	memcpy( nitmodClassMaxHealth, values, sizeof( nitmodClassMaxHealth ) );
	nitmodClassHealthReceived = qtrue;
}

int NITMOD_ClassMaxHealth( int playerClass ) {
	if( !nitmodClassHealthReceived || playerClass < PC_SOLDIER || playerClass > PC_COVERTOPS ) {
		return 0;
	}
	return nitmodClassMaxHealth[playerClass];
}

void NITMOD_MapEndStatsCommand( void ) {
	if( !NITMOD_HasArgumentCount( "mes", 6 ) ) {
		return;
	}
	if( !NITMOD_ParseMapStatsSnapshot( trap_Argc(), CG_Argv, &nitmodMapEndStats ) ) {
		return;
	}

	CG_Printf( "^7Nitmod map statistics\n"
		"Bodyshots: ^2%u\n^7Headshots: ^2%u\n^7Kills: ^2%i\n^7Deaths: ^2%i\n^7Revives: ^2%u\n",
		nitmodMapEndStats.bodyshots, nitmodMapEndStats.headshots,
		nitmodMapEndStats.kills, nitmodMapEndStats.deaths, nitmodMapEndStats.revives );
}

void NITMOD_TeamScoresCommand( void ) {
	nitmodTeamScores_t next;
	if( !NITMOD_HasArgumentCount( "tsc", 3 ) ) {
		return;
	}
	/* cgs has no dedicated TDM score fields in the 2.60 baseline. */
	if( !NITMOD_ParseTeamScoreSnapshot( trap_Argc(), CG_Argv, &next ) ) {
		return;
	}
	CG_NitmodTDMScoreChanged( next.axis, next.allies, cg.time );
	nitmodGameState.teamScoreAxis = next.axis;
	nitmodGameState.teamScoreAllies = next.allies;
}

void NITMOD_TDMScoreLimitCommand( void ) {
	int limit;

	if( !NITMOD_HasArgumentCount( "z1", 2 ) ||
		!NITMOD_ParseProtocolSigned( CG_Argv( 1 ), &limit ) ) {
		return;
	}
	/* A non-positive value disables the widget, matching Nit_TDMInfo. */
	nitmodGameState.tdmScoreLimit = limit;
}

void NITMOD_TDMInfo_f( void ) {
	if( cgs.gametype != 7 || nitmodGameState.tdmScoreLimit <= 0 ) {
		return;
	}
	CG_Printf( "^7N^1!^7tmod: ^3Team Death Match Informations.\n"
		"^5> ^3Score to reach:\n"
		"- To win the match, your team has to reach %d points.\n"
		"^5> ^3Timelimit rules:\n", nitmodGameState.tdmScoreLimit );
	if( !(nitmodGameState.tdmOptions & 16) ) {
		CG_Printf( "- The map will ^1NOT ^7end as long as the score is not reached.\n" );
	} else {
		CG_Printf( "- If the timelimit is over, the map will end and the team with most points will win the round.\n"
			"- Reaching the score limit before timelimit hits will end the map.\n" );
	}
	CG_Printf( "^5> ^3Server TDM Options:\n" );
	if( nitmodGameState.tdmOptions & 1 ) {
		CG_Printf( "- Using 'Kill Based Scoring'. The only way to get points is by killing an enemy (1 point for your team per enemy killed).\n" );
	} else {
		CG_Printf( "- Every earned XP counts in the team score.\n" );
	}
	if( nitmodGameState.tdmOptions & 4 ) CG_Printf( "- Artillery support is disabled.\n" );
	if( nitmodGameState.tdmOptions & 8 ) CG_Printf( "- Intermission map voting is enabled.\n" );
	CG_Printf( "- Objective: Completing the final objective will ^1NOT ^7end the match. Depending on server settings, the winning team will earn ^2Bonus Points!^7.\n" );
}

void NITMOD_DMWinnerCommand( void ) {
	int client;
	if( trap_Argc() != 2 || !NITMOD_ParseProtocolInteger( CG_Argv( 1 ), &client ) ||
		client < 0 || client >= MAX_CLIENTS ) return;
	nitmodGameState.dmWinnerClient = client;
}

static const char *NITMOD_ObjectiveName( int objective ) {
	const char *name;

	if( objective < 0 || objective >= NITMOD_NCS_OBJECTIVE_COUNT ) {
		return NULL;
	}

	name = Info_ValueForKey( NITMOD_ConfigString( NITMOD_NCS_OBJECTIVES + objective ), "n" );
	return name[0] ? name : NULL;
}

void NITMOD_ObjectiveEventCommand( void ) {
	const char *verb;
	const char *actorName;
	const char *objectiveName;
	char message[MAX_STRING_CHARS];

	if( !NITMOD_HasArgumentCount( "ob", 6 ) ) {
		return;
	}

	if( !NITMOD_ParseObjectiveSnapshot( trap_Argc(), CG_Argv, MAX_CLIENTS, &nitmodLastObjectiveEvent ) ) {
		return;
	}
	actorName = cgs.clientinfo[nitmodLastObjectiveEvent.actor].name;
	if ( !actorName[0] ) {
		return;
	}
	objectiveName = NITMOD_ObjectiveName( nitmodLastObjectiveEvent.objective );

	if ( nitmodLastObjectiveEvent.type == 0 ) {
		switch ( nitmodLastObjectiveEvent.detail ) {
		case 0: verb = "Dynamite Planted"; break;
		case 1: verb = "Dynamite Defused"; break;
		default: return;
		}
		Com_sprintf( message, sizeof( message ), "%s %s ^gby ^7%s", verb,
			objectiveName ? objectiveName : "Objective", actorName );
	} else if ( nitmodLastObjectiveEvent.type == 4 ) {
		switch ( nitmodLastObjectiveEvent.detail ) {
		case 2: verb = "Objective Constructed"; break;
		case 3: verb = "Objective Destroyed"; break;
		case 4: verb = "Objective Damaged"; break;
		default: return;
		}
		Com_sprintf( message, sizeof( message ), "^g%s %s ^7%s",
			objectiveName ? objectiveName : "Objective", verb, actorName );
	} else if ( nitmodLastObjectiveEvent.type == 9 || nitmodLastObjectiveEvent.type == 10 ) {
		Com_sprintf( message, sizeof( message ), "^7%s ^gcaptured the Flag!", actorName );
	} else {
		return;
	}

	CG_AddPMItem( PM_MESSAGE, message, cgs.media.voiceChatShader );
	CG_Printf( "%s\n", message );
}

/* Negotiated transport uses the same typed receiver as original event 101. */
void NITMOD_SpreeEventCommand( void ) {
	int actor;
	int detail;
	int type;

	if( !NITMOD_HasArgumentCount( "nsp", 4 ) ) {
		return;
	}
	if( !NITMOD_ParseAnnouncementInteger( CG_Argv( 1 ), &actor ) ||
		!NITMOD_ParseAnnouncementInteger( CG_Argv( 2 ), &detail ) ||
		!NITMOD_ParseAnnouncementInteger( CG_Argv( 3 ), &type ) || actor >= MAX_CLIENTS ) {
		return;
	}
	CG_NitmodSpreeStart(actor, detail, type);
}

static void NITMOD_PlayHitSound(int hitType, int channel) {
	if(hitType != NITMOD_HIT_SOUND_TEAM && hitType != NITMOD_HIT_SOUND_HEAD) return;
	if( !nitmodHitSoundsRegistered ) {
		trap_Cvar_Register( &nitmodHitSounds, "cg_hitSounds", "1", CVAR_ARCHIVE );
		nitmodHeadHitSound = trap_S_RegisterSound( "sound/nit/hs.wav", qfalse );
		nitmodTeamHitSound = trap_S_RegisterSound( "sound/hitsounds/team.wav", qfalse );
		nitmodHitSoundsRegistered = qtrue;
	}
	trap_Cvar_Update( &nitmodHitSounds );
	if( !nitmodHitSounds.integer ) {
		return;
	}
	if( hitType == NITMOD_HIT_SOUND_TEAM ) {
		trap_S_StartSound( NULL, cg.snap ? cg.snap->ps.clientNum : -1, channel, nitmodTeamHitSound );
	} else if( hitType == NITMOD_HIT_SOUND_HEAD ) {
		trap_S_StartSound( NULL, cg.snap ? cg.snap->ps.clientNum : -1, channel, nitmodHeadHitSound );
	}
}

void NITMOD_HitSoundCommand(void) {
	int hitType;
	if(!NITMOD_HasArgumentCount("nhs", 2) || !NITMOD_ParseProtocolInteger(CG_Argv(1), &hitType)) return;
	NITMOD_PlayHitSound(hitType, CHAN_AUTO);
}

void NITMOD_HitSoundEvent(int hitType) {
	if(!cg.snap || cg.snap->ps.clientNum < 0 || cg.snap->ps.clientNum >= MAX_CLIENTS) return;
	NITMOD_PlayHitSound(hitType, CHAN_VOICE);
}

const char *NITMOD_ConfigString( int index ) {
	if ( index < 0 || index >= NITMOD_MAX_CONFIGSTRINGS ) {
		CG_Error( "NITMOD_ConfigString: bad index: %i", index );
		return "";
	}
	return nitmodConfigStrings[index];
}

void nitrox_ProcessNewCS( int index ) {
	const char *value;
	int assetIndex;

	value = NITMOD_ConfigString( index );

	/* Empty NCS values are updates too: the original dispatcher registers an
	 * empty asset (clearing its handle where applicable) and reparses emptied
	 * OID/spawn/fireteam slots.  Do not leave stale client-side state behind. */
	if ( index >= NITMOD_NCS_MODELS && index < NITMOD_NCS_SOUNDS ) {
		cgs.gameModels[index - NITMOD_NCS_MODELS] = trap_R_RegisterModel( value );
		return;
	}

	if ( index >= NITMOD_NCS_SOUNDS && index < NITMOD_NCS_SHADERS ) {
		assetIndex = index - NITMOD_NCS_SOUNDS;
		cgs.gameSounds[assetIndex] = 0;
		if ( value[0] && value[0] != '*' ) {
			if ( strstr( value, ".wav" ) ) {
				cgs.gameSounds[assetIndex] = trap_S_RegisterSound( value, qfalse );
			} else {
				CG_SoundScriptPrecache( value );
			}
		}
		return;
	}

	if ( index >= NITMOD_NCS_SHADERS && index < NITMOD_NCS_SHADERSTATE ) {
		assetIndex = index - NITMOD_NCS_SHADERS;
		cgs.gameShaders[assetIndex] = value[0] == '*'
			? trap_R_RegisterShader( value + 1 )
			: trap_R_RegisterShaderNoMip( value );
		Q_strncpyz( cgs.gameShaderNames[assetIndex], value + ( value[0] == '*' ), MAX_QPATH );
		return;
	}

	if ( index == NITMOD_NCS_SHADERSTATE ) {
		CG_ShaderStateChanged();
		return;
	}

	if ( index >= NITMOD_NCS_SKINS && index < NITMOD_NCS_SKINS + NITMOD_NCS_SKIN_COUNT ) {
		cgs.gameModelSkins[index - NITMOD_NCS_SKINS] = trap_R_RegisterSkin( value );
		return;
	}

	if ( index >= NITMOD_NCS_OBJECTIVES &&
		index < NITMOD_NCS_OBJECTIVES + NITMOD_NCS_OBJECTIVE_COUNT ) {
		CG_ParseOIDInfos();
		return;
	}

	if ( index >= NITMOD_NCS_SPAWNS && index < NITMOD_NCS_SPAWNS + NITMOD_NCS_SPAWN_COUNT ) {
		CG_ParseSpawns();
		return;
	}

	if ( index >= NITMOD_NCS_FIRETEAMS &&
		index < NITMOD_NCS_FIRETEAMS + NITMOD_NCS_FIRETEAM_COUNT ) {
		CG_ParseFireteams();
	}
}

void NITMOD_ConfigStringModified( int index, const char *value ) {
	if ( index < 0 || index >= NITMOD_MAX_CONFIGSTRINGS ) {
		CG_Error( "NITMOD_ConfigStringModified: bad index: %i", index );
		return;
	}

	if ( !value ) {
		value = "";
	}
	if ( strlen( value ) >= NITMOD_CONFIGSTRING_CHARS ) {
		CG_Printf( "Nitmod: ignoring oversized NCS value at index %i\n", index );
		return;
	}
	if ( !strcmp( nitmodConfigStrings[index], value ) ) {
		return;
	}

	Q_strncpyz( nitmodConfigStrings[index], value, sizeof( nitmodConfigStrings[index] ) );
	nitrox_ProcessNewCS( index );
}

const char *nitrox_ConfigString( int index ) {
	return NITMOD_ConfigString( index );
}

/* Translate only explicitly mapped asset/state consumers, not engine ABI indices. */
const char *NITMOD_AssetConfigString(int index) {
	if(NITMOD_UsesOriginalProtocol()) {
		if(index >= CS_MODELS && index < CS_MODELS + NITMOD_NCS_MODEL_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_MODELS + index - CS_MODELS);
		if(index >= CS_SOUNDS && index < CS_SOUNDS + NITMOD_NCS_SOUND_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_SOUNDS + index - CS_SOUNDS);
		if(index >= CS_SHADERS && index < CS_SHADERS + NITMOD_NCS_SHADER_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_SHADERS + index - CS_SHADERS);
		if(index == CS_SHADERSTATE) return NITMOD_ConfigString(NITMOD_NCS_SHADERSTATE);
		if(index >= CS_SKINS && index < CS_SKINS + NITMOD_NCS_SKIN_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_SKINS + index - CS_SKINS);
		if(index >= CS_OID_DATA && index < CS_OID_DATA + NITMOD_NCS_OBJECTIVE_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_OBJECTIVES + index - CS_OID_DATA);
		if(index >= CS_MULTI_SPAWNTARGETS && index < CS_MULTI_SPAWNTARGETS + NITMOD_NCS_SPAWN_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_SPAWNS + index - CS_MULTI_SPAWNTARGETS);
		if(index >= CS_FIRETEAMS && index < CS_FIRETEAMS + NITMOD_NCS_FIRETEAM_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_FIRETEAMS + index - CS_FIRETEAMS);
	}
	return CG_ConfigString(index);
}

void nitrox_ConfigStringModified( void ) {
	int index;
	if( !NITMOD_HasArgumentCount( NITMOD_CONFIGSTRING_COMMAND, 3 ) ) {
		return;
	}
	if( !NITMOD_ParseProtocolInteger( CG_Argv( 1 ), &index ) ||
		index >= NITMOD_MAX_CONFIGSTRINGS ) {
		return;
	}
	NITMOD_ConfigStringModified( index, CG_Argv( 2 ) );
}
