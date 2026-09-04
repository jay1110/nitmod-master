#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_events.h"
#include "cg_nitmod_hud.h"

/* Immutable cgame ELF: Obituaries_killedby 0x134940, ammoTableMP 0x12fd00.
 * Weapon selection is the first matching MOD, with throwknife -> knife.
 * These are wire weapon IDs; never index cg_weapons with them directly. */
typedef struct { const char *message, *suffix; int wireWeapon; } nitmodObituary_t;
static const nitmodObituary_t originalObituaries[] = {
    { "died", "", 0 }, /* 0 */
    { "was perforated by", "'s Crew-served MG", 0 }, /* 1 */
    { "was perforated by", "'s Tank-mounted Browning .30 Cal", 0 }, /* 2 */
    { "was perforated by", "'s Tank-mounted MG42", 0 }, /* 3 */
    { "died", "", 0 }, /* 4 */
    { "was stabbed by", "'s Knife", 1 }, /* 5 */
    { "was killed by", "'s Luger 9mm", 2 }, /* 6 */
    { "was killed by", "'s .45ACP 1911", 7 }, /* 7 */
    { "was killed by", "'s MP40", 3 }, /* 8 */
    { "was killed by", "'s Thompson", 8 }, /* 9 */
    { "was killed by", "'s Sten", 10 }, /* 10 */
    { "was killed by", "'s M1 Garand", 24 }, /* 11 */
    { "was killed by", "'s Luger 9mm", 14 }, /* 12 */
    { "was killed by", "'s FG42", 31 }, /* 13 */
    { "was sniped by", "'s FG42", 41 }, /* 14 */
    { "was blasted by", "'s Panzerfaust", 5 }, /* 15 */
    { "was exploded by", "'s Grenade", 4 }, /* 16 */
    { "was cooked by", "'s Flamethrower", 6 }, /* 17 */
    { "was exploded by", "'s Grenade", 9 }, /* 18 */
    { "was killed by mortar support", "", 0 }, /* 19 */
    { "was killed by mortar support", "", 0 }, /* 20 */
    { "was detonated by", "'s Dynamite", 15 }, /* 21 */
    { "was blasted by", "'s Support Fire", 21 }, /* 22 */
    { "was revived by", "", 11 }, /* 23 */
    { NULL, NULL, 12 }, /* 24 */
    { "was shelled by", "'s Artillery Support", 13 }, /* 25 */
    { "drowned", "", 0 }, /* 26 */
    { "died by toxic materials", "", 0 }, /* 27 */
    { "was burned by lava", "", 0 }, /* 28 */
    { "was crushed", "", 0 }, /* 29 */
    { "was telefragged", "", 0 }, /* 30 */
    { "fell to his death", "", 0 }, /* 31 */
    { "killed himself", "", 0 }, /* 32 */
    { "was target of too strong beam", "", 0 }, /* 33 */
    { "was mortally wounded", "", 0 }, /* 34 */
    { "died in his own explosion", "", 0 }, /* 35 */
    { "was killed by", "'s M1 Garand", 23 }, /* 36 */
    { "was killed by", "'s K43", 22 }, /* 37 */
    { "was killed by", "'s Rifle Grenade", 36 }, /* 38 */
    { "was killed by", "'s Rifle Grenade", 37 }, /* 39 */
    { "failed to spot", "'s Landmine", 25 }, /* 40 */
    { "was blasted by", "'s Satchel Charge", 26 }, /* 41 */
    { NULL, NULL, 28 }, /* 42 */
    { "was mown down by", "'s Mobile MG42", 29 }, /* 43 */
    { "was killed by", "'s .45ACP 1911", 38 }, /* 44 */
    { "was sniped by", "'s M1 Garand", 39 }, /* 45 */
    { "got caught in", "'s construction madness", 0 }, /* 46 */
    { "got buried under", "'s rubble", 0 }, /* 47 */
    { "got buried under a pile of rubble", "", 0 }, /* 48 */
    { "was killed by", "'s K43", 30 }, /* 49 */
    { "was sniped by", "'s K43", 40 }, /* 50 */
    { "never saw", "'s Mortar Round coming", 33 }, /* 51 */
    { "was killed by", "'s Akimbo .45ACP 1911s", 34 }, /* 52 */
    { "was killed by", "'s Akimbo Luger 9mms", 35 }, /* 53 */
    { "was killed by", "'s Akimbo .45ACP 1911s", 44 }, /* 54 */
    { "was killed by", "'s Akimbo Luger 9mms", 45 }, /* 55 */
    { "stood on", "'s Airstrike Marker", 0 }, /* 56 */
    { NULL, NULL, 0 }, /* 57 */
    { "was stomped by", "", 0 }, /* 58 */
    { "was poisoned by", "", 47 }, /* 59 */
    { "was scared to death by", "", 0 }, /* 60 */
    { NULL, NULL, 0 }, /* 61 */
    { "was pushed too far by", "", 0 }, /* 62 */
    { "was killed by", "'s Throwing Knife", 1 }, /* 63 */
    { NULL, NULL, 0 }, /* 64 */
    { "was detonated by", "'s Bomb", 48 }, /* 65 */
    { "was detonated by", "'s Tripmine", 49 }, /* 66 */
    { "choked on", "'s Poison Gas", 50 }, /* 67 */
    { "choked on", "'s own poison gas landmine", 51 }, /* 68 */
};

int CG_NitmodObituaryWeapon(int cause) {
    if(cause < 0 || cause >= sizeof(originalObituaries) / sizeof(originalObituaries[0])) return WP_NONE;
    return NITMOD_WeaponFromWire(originalObituaries[cause].wireWeapon);
}

static const char *CG_NitmodSelfObituary(int cause) {
    switch(cause) {
    case 15: return "vaporized himself";
    case 16: case 18: return "dove on his own grenade";
    case 17: return "played with fire";
    case 21: return "dynamited himself to pieces";
    case 22: return "obliterated himself";
    case 25: return "fired-for-effect on himself";
    case 31: case 62: return "fell to his death";
    case 32: return "killed himself";
    case 38: case 39: return "ate his own rifle grenade";
    case 40: return "failed to spot his own landmine";
    case 41: return "embraced his own satchel explosion";
    case 46: return "engineered himself into oblivion";
    case 47: return "buried himself alive";
    case 51: return "never saw his own mortar round coming";
    case 56: return "danced on his airstrike marker";
    case 59: return "poisonned himself";
    case 61: return "was killed (Censor)";
    case 63: return "played with knives!";
    case 64: return "gibbed himself";
    case 65: return "was detonated by his own bomb";
    case 66: return "forgot where his tripmine was";
    case 67: return "choked on his own poison gas";
    case 68: return "choked on his own poison gas landmine";
    default: return NULL;
    }
}

/* Pure text planning, shared by dispatch and deterministic replay tests. */
qboolean CG_NitmodFormatObituary(int cause, const char *target, const char *attacker,
    qboolean self, qboolean teamkill, char *out, int size) {
    const nitmodObituary_t *entry;
    const char *single;
    if(!out || size <= 0) return qfalse;
    out[0] = 0;
    if(!target || cause == 57) return qfalse;
    entry = &originalObituaries[cause >= 0 && cause < sizeof(originalObituaries) / sizeof(originalObituaries[0]) ? cause : 0];
    single = self ? CG_NitmodSelfObituary(cause) : NULL;
    if(single) Com_sprintf(out, size, "%s %s", target, single);
    else if(!attacker) Com_sprintf(out, size, "%s %s", target,
        entry->message && entry->suffix && !*entry->suffix ? entry->message : "^7died");
    else if(!entry->message || !entry->suffix)
        Com_sprintf(out, size, "%s ^7died", target);
    else Com_sprintf(out, size, "%s%s %s %s%s",
        teamkill && !self && cause != 23 ? "^1TEAM KILL^7:" : "",
        target, entry->message, attacker, entry->suffix);
    return qtrue;
}

qboolean CG_NitmodPlanGraphicObituary(const entityState_t *es, int mode,
    qhandle_t fallback, nitmodObituaryPlan_t *plan) {
    int target, attacker, weapon, cause, scale;
    qboolean pair, single;
    if(!plan) return qfalse;
    memset(plan, 0, sizeof(*plan));
    if(!es || (mode != 3 && mode != 4)) return qfalse;
    target = es->otherEntityNum; attacker = es->otherEntityNum2; cause = es->eventParm;
    if(target < 0 || target >= MAX_CLIENTS || cause == 57) return qfalse;
    pair = cause >= 0 && cause < sizeof(originalObituaries)/sizeof(originalObituaries[0]) &&
        originalObituaries[cause].message && originalObituaries[cause].suffix;
    single = attacker < 0 || attacker >= MAX_CLIENTS ||
        (target == attacker && CG_NitmodSelfObituary(cause));
    plan->first = cgs.clientinfo[target].name;
    plan->second = single ? "" : cgs.clientinfo[attacker].name;
    plan->shader = fallback; plan->scale = 1;
    VectorSet(plan->color, 1, 1, 0);
    if(!single && pair) {
        if(mode == 3 || cause == 23) {
            plan->first = cgs.clientinfo[attacker].name;
            plan->second = cgs.clientinfo[target].name;
        }
        if(cause == 23) VectorSet(plan->color, 0, 1, 0);
        else if(target != attacker && cgs.gametype != 8 &&
            cgs.clientinfo[target].team == cgs.clientinfo[attacker].team)
            VectorSet(plan->color, 1, 0, 0);
        else VectorSet(plan->color, 1, 1, 1);
    }
    weapon = CG_NitmodObituaryWeapon(cause);
    scale = CG_NitmodWeaponIconScale(weapon);
    if(weapon > WP_NONE && weapon < WP_NUM_WEAPONS && cg_weapons[weapon].weaponIcon[0] > 0 &&
        scale >= 1 && scale <= 4) {
        plan->shader = cg_weapons[weapon].weaponIcon[0];
        plan->scale = scale;
    }
    return plan->shader > 0 && plan->first[0];
}

void CG_NitmodObituary(const entityState_t *es) {
    char targetName[MAX_NAME_LENGTH + 3], attackerName[MAX_NAME_LENGTH + 3], text[512];
    clientInfo_t *target, *attacker = NULL;
    qboolean self, teamkill;
    int listener;
    if(!es || es->otherEntityNum < 0 || es->otherEntityNum >= MAX_CLIENTS) return;
    target = &cgs.clientinfo[es->otherEntityNum];
    if(es->otherEntityNum2 >= 0 && es->otherEntityNum2 < MAX_CLIENTS)
        attacker = &cgs.clientinfo[es->otherEntityNum2];
    self = attacker && es->otherEntityNum == es->otherEntityNum2;
    teamkill = attacker && !self && target->team == attacker->team && cgs.gametype != 8;
    Q_strncpyz(targetName, target->name, sizeof(targetName) - 2);
    strcat(targetName, S_COLOR_WHITE);
    attackerName[0] = 0;
    if(attacker) {
        Q_strncpyz(attackerName, attacker->name, sizeof(attackerName) - 2);
        strcat(attackerName, S_COLOR_WHITE);
    }
    if(!CG_NitmodFormatObituary(es->eventParm, targetName, attacker ? attackerName : NULL,
        self, teamkill, text, sizeof(text))) return;
    listener = cg.snap ? cg.snap->ps.clientNum : -1;
    if(attacker && !self) {
        if(es->otherEntityNum2 == listener && es->eventParm != 23) {
            char killed[128];
            Com_sprintf(killed, sizeof(killed), teamkill ? "You killed ^1TEAMMATE ^7%s" : "You killed %s", targetName);
            if(!CG_NitmodKillPrint(killed, teamkill, cg.time))
                CG_CenterPrint(killed, 360, 9);
        }
        if(es->otherEntityNum == listener)
            Q_strncpyz(cg.killerName, attackerName, sizeof(cg.killerName));
        CG_NitmodObituarySounds(es);
    }
    CG_NitmodObituaryPrint(text, cgs.media.pmImages[PM_DEATH], es);
}
