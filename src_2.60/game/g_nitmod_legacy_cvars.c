#include "g_local.h"
#include "g_nitmod_legacy_cvars.h"
typedef struct {
	vmCvar_t value;
	const char *name, *defaultValue;
	int flags;
	int modificationCount;
} nitmodLegacyCvar_t;
/* Original qagame gameCvarTable 0x2a7e20: gameplay/progression batch. */
static nitmodLegacyCvar_t legacyGameplayCvars[] = {
	{{0},"g_playDead","1",0}, {{0},"g_classChange","0",0},
	{{0},"g_privateMessages","1",0}, {{0},"g_fieldOps","0",0},
	{{0},"g_teamChangeKills","1",0}, {{0},"g_defaultMute","3600",0},
	{{0},"g_voting","1",0}, {{0},"g_maxWarp","4",0}, {{0},"g_antiwarp","1",0},
	{{0},"g_fear","2000",0}, {{0},"g_shortcuts","1",0},
	{{0},"g_XPDecay","0",0}, {{0},"g_XPDecayRate","0.0",0},
	{{0},"g_XPDecayFloor","0",0}, {{0},"g_maxXP","-1",0}, {{0},"g_slashKill","0",0},
	{{0},"skill_soldier","20 50 90 140 200",0}, {{0},"skill_medic","20 50 90 140 200",0},
	{{0},"skill_engineer","20 50 90 140 200",0}, {{0},"skill_fieldops","20 50 90 140 200",0},
	{{0},"skill_covertops","20 50 90 140 200",0}, {{0},"skill_battlesense","20 50 90 140 200",0},
	{{0},"skill_lightweapons","20 50 90 140 200",0},
	{{0},"g_truePing","0",0}, {{0},"g_skipCorrection","1",0},
	{{0},"g_teamDamageRestriction","0",0}, {{0},"g_minHits","6",0},
	{{0},"g_autoTempBan","0",0}, {{0},"g_autoTempBanTime","1800",0},
	{{0},"g_drawAttackerHP","1",0}, {{0},"g_msgs","0",0}, {{0},"g_msgpos","0",0},
	{{0},"team_airstrikeTime","10",0}, {{0},"team_artyTime","10",0},
	{{0},"g_constructiblexpsharing","0",0}, {{0},"g_asblock","0",0},
	{{0},"gametime","16:23:19",64}, {{0},"g_reset","0",64},
	{{0},"g_countryflags","0",33}, {{0},"g_logCrash","crash.log",1},
	{{0},"campaign_maps","",64},
	{{0},"g_logAdmin","",0}, {{0},"g_customConfig","",0},
	{{0},"g_debugHitboxes","0",0}, {{0},"g_debugPlayerHitboxes","0",0},
	{{0},"g_mapScriptDirectory","",0}, {{0},"g_campaignFile","",0},
	{{0},"g_censor","",0}, {{0},"g_censorNames","",0},
	{{0},"g_censorPenalty","1",0}, {{0},"g_censorMuteTime","0",0},
	{{0},"mod_version","2.3.5",68},
#ifdef __EMSCRIPTEN__
	{{0},"mod_build","wasm32",68},
#else
	{{0},"mod_build","linux-i386",68},
#endif
	{{0},"g_maxLevelLightWeapons","6",0}, {{0},"g_maxLevelBattleSense","6",0},
	{{0},"g_maxLevelSoldier","6",0}, {{0},"g_maxLevelMedic","6",0},
	{{0},"g_maxLevelEngineer","6",0}, {{0},"g_maxLevelFieldOp","6",0},
	{{0},"g_maxLevelCovertOp","6",0}, {{0},"g_weaponItems","1",0},
	{{0},"g_rockets","0",0}, {{0},"g_skills","0",0}, {{0},"g_missileCams","0",0},
	{{0},"g_throwDistance","75",0}, {{0},"g_realHead","1",0},
	{{0},"g_missileSpeed","0",0}, {{0},"g_missileHealth","5",0},
	{{0},"g_mortarBBox","0",0},
	{{0},"g_TDMScore","500",0}, {{0},"g_flushItems","1",0},
	{{0},"g_multikillTime","2000",0}, {{0},"g_headshot","0",0},
	{{0},"g_weaponScriptsDir","",0}, {{0},"g_missileGravity","0",0},
	{{0},"g_fixedphysics","0",5}, {{0},"g_fixedphysicsfps","125",5},
	{{0},"g_adrenaline","0",0}, {{0},"jp_keepAwards","0",0},
	{{0},"g_adrenClasses","2",0},
	{{0},"omnibot_path","",1025}, {{0},"omnibot_enable","0",9217},
	{{0},"omnibot_playing","0",8256}, {{0},"ip_max_clients","3",0},
	{{0},"g_floodprotect","1",0}, {{0},"g_floodthreshold","6",0},
	{{0},"g_floodWait","1000",0}, {{0},"lua_modules","",0},
	{{0},"lua_allowedModules","",0}, {{0},"g_noCharge","0",0},
	{{0},"g_instantSpawn","0",0}, {{0},"g_revenge","0",0},
	{{0},"g_autoQuitDelay","0",0}, {{0},"g_realBody","0",0},
	{{0},"g_dropObj","0",0}, {{0},"g_secureShrubPassword","",0},
	{{0},"g_GUIDChecks","1",0}, {{0},"g_IPChecks","1",0},
	{{0},"shoutcastPassword","",0}, {{0},"g_ettv_flags","3",0},
	{{0},"g_DMFragLimit","25",0}, {{0},"g_TDMOptions","0",0},
	{{0},"g_TDMObjBonus","100",0}, {{0},"g_misc","0",0},
	{{0},"team_maxTripmines","5",0}, {{0},"g_teamChangeDelay","0",0},
	{{0},"n_SQLiteDBPath","",0}, {{0},"n_userMail","1",0},
	{{0},"n_proneDelay","0",0}, {{0},"n_mapRecords","1",0},
	{{0},"n_allowDropWeapon","0",0}, {{0},"n_UserDBSync","0",0},
	{{0},"n_sniperWarOptions","7",0}, {{0},"n_dynamiteTimer","30000",0},
	{{0},"g_hitboxes","0",0}, {{0},"n_tripmineTimeout","1",1},
	{{0},"sv_NxAC","0",1100}, {{0},"n_NxAC","2",33},
	{{0},"n_NxAC_CvarScan","0",1}, {{0},"n_NxAC_CvarScanWait","10000",1},
	{{0},"n_NxAC_CvarScanDelay","750",1}, {{0},"n_NxAC_CvarScanInterval","300000",1},
	{{0},"n_NxAC_CheckClientBinary","0",1}, {{0},"n_NxAC_CvarScanMaxWarnings","1",1},
	{{0},"n_crazyGravity","0",1}, {{0},"n_crazyGravityMin","50",1},
	{{0},"n_crazyGravityMax","1000",1}, {{0},"n_crazyGravityInterval","30000",1},
	{{0},"n_minNameLength","0",1}, {{0},"n_reviveSpreeOptions","1",1},
	{{0},"n_multiReviveTime","2000",1}, {{0},"n_LogCurrentTime","0",1},
	{{0},"n_crouchStandDelay","0",1}, {{0},"n_standCrouchDelay","0",1},
	{{0},"n_tankMountDelay","0",1}, {{0},"n_noSkillUpgrades","0",1},
	{{0},"n_killAssistances","1",1}, {{0},"n_greetingPos","0",1},
	{{0},"n_voteMaxTimelimit","0",1}, {{0},"g_artilleryHints","1",1},
	{{0},"humans","0",9280}
};

static qboolean G_NITMOD_LegacyCvarPublishesSnapshot(const char *name) {
	static const char *published[] = {
		"g_missileCams", "g_misc", "n_proneDelay", "n_dynamiteTimer",
		"n_crouchStandDelay", "n_standCrouchDelay", "g_adrenaline",
		"jp_keepAwards", "g_TDMOptions"
	};
	unsigned int i;
	for(i = 0; i < sizeof(published) / sizeof(published[0]); ++i)
		if(!Q_stricmp(name, published[i])) return qtrue;
	return qfalse;
}

void G_NITMOD_RegisterLegacyGameplayCvars(void) {
	unsigned int i; for(i=0;i<sizeof(legacyGameplayCvars)/sizeof(*legacyGameplayCvars);++i) {
		trap_Cvar_Register(&legacyGameplayCvars[i].value,legacyGameplayCvars[i].name,legacyGameplayCvars[i].defaultValue,legacyGameplayCvars[i].flags);
		legacyGameplayCvars[i].modificationCount = legacyGameplayCvars[i].value.modificationCount;
	}
}
qboolean G_NITMOD_UpdateLegacyGameplayCvars(void) {
	unsigned int i;
	qboolean changed = qfalse;
	for(i=0;i<sizeof(legacyGameplayCvars)/sizeof(*legacyGameplayCvars);++i) {
		trap_Cvar_Update(&legacyGameplayCvars[i].value);
		if(legacyGameplayCvars[i].modificationCount != legacyGameplayCvars[i].value.modificationCount) {
			legacyGameplayCvars[i].modificationCount = legacyGameplayCvars[i].value.modificationCount;
			if(G_NITMOD_LegacyCvarPublishesSnapshot(legacyGameplayCvars[i].name))
				changed = qtrue;
		}
	}
	return changed;
}
int G_NITMOD_LegacyCvarInteger(const char *name,int fallback) {
	unsigned int i; if(!name||!*name)return fallback;
	for(i=0;i<sizeof(legacyGameplayCvars)/sizeof(*legacyGameplayCvars);++i) if(!Q_stricmp(name,legacyGameplayCvars[i].name))return legacyGameplayCvars[i].value.integer;
	return fallback;
}
float G_NITMOD_LegacyCvarValue(const char *name,float fallback) {
	unsigned int i; if(!name||!*name)return fallback;
	for(i=0;i<sizeof(legacyGameplayCvars)/sizeof(*legacyGameplayCvars);++i) if(!Q_stricmp(name,legacyGameplayCvars[i].name))return legacyGameplayCvars[i].value.value;
	return fallback;
}
void G_NITMOD_LegacyCvarString(const char *name,char *buffer,int bufferSize,const char *fallback) {
	unsigned int i;
	if(!buffer || bufferSize <= 0) return;
	for(i=0;i<sizeof(legacyGameplayCvars)/sizeof(*legacyGameplayCvars);++i) {
		if(name && !Q_stricmp(name,legacyGameplayCvars[i].name)) {
			Q_strncpyz(buffer,legacyGameplayCvars[i].value.string,bufferSize);
			return;
		}
	}
	Q_strncpyz(buffer,fallback ? fallback : "",bufferSize);
}

qboolean G_NITMOD_CensorText(const char *cvarName,char *text,int textSize) {
	char list[MAX_CVAR_VALUE_STRING];
	char word[MAX_TOKEN_CHARS];
	char *cursor, *start, *scan;
	int length;
	qboolean matched = qfalse;

	if(!text || textSize <= 0) return qfalse;
	G_NITMOD_LegacyCvarString(cvarName,list,sizeof(list),"");
	cursor = list;
	while(*cursor) {
		while(*cursor == ',' || *cursor == ' ' || *cursor == '\t') cursor++;
		start = cursor;
		while(*cursor && *cursor != ',') cursor++;
		length = cursor - start;
		while(length > 0 && (start[length - 1] == ' ' || start[length - 1] == '\t')) length--;
		if(length > 0) {
			if(length >= (int)sizeof(word)) length = sizeof(word) - 1;
			memcpy(word,start,length);
			word[length] = '\0';
			for(scan = text; *scan; scan++) {
				if(!Q_stricmpn(scan,word,length)) {
					memset(scan,'*',length);
					matched = qtrue;
					scan += length - 1;
				}
			}
		}
		if(*cursor == ',') cursor++;
	}
	text[textSize - 1] = '\0';
	return matched;
}
