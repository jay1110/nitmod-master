#include "g_local.h"
#include "g_nitmod_abilities.h"
#include "g_nitmod_weapons.h"
#include "g_nitmod_war.h"
#include "g_nitmod_restrictions.h"
#include "g_nitmod_config.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_weapon_ids.h"

void G_NITMOD_ResetWarState( nitmodWarState_t *state ) {
    if( state ) state->stripped = 0;
}

int G_NITMOD_CheckWarEntry( gentity_t *entity, int warMode ) {
    if( !entity || !entity->client ||
        entity->client->pers.connected != CON_CONNECTED ||
        (entity->client->sess.sessionTeam != TEAM_AXIS &&
         entity->client->sess.sessionTeam != TEAM_ALLIES) ) return 0;
    /* ET 2.60 has no server demo-client facility. Do not reinterpret a
     * private original-client offset as part of the native client ABI. */
    return G_NITMOD_ApplyWarEntry(entity, &entity->client->nitmodWarState,
        warMode, 0);
}

int G_NITMOD_ApplyWarEntry( gentity_t *entity, nitmodWarState_t *state,
    int warMode, int isDemoClient ) {
    if( !state || !G_NITMOD_CanCheckWeapons(entity, isDemoClient) ||
        warMode != 4 || state->stripped ) return 0;
    G_NITMOD_RemoveWeapons(entity->client);
    entity->client->ps.weapon = WP_KNIFE;
    /* Original event 0x19 maps to native EV_NOAMMO, not raw ID 25.
     * Preserve the original ordering: mark completion after the event. */
    G_AddEvent(entity, EV_NOAMMO, 0);
    state->stripped = 1;
    return 1;
}

/* Original ammoTableMP+0x44, stride0x48: exactly these original IDs.
 * These include deployed MG/mortar, not their carried counterparts. */
static qboolean G_NITMOD_OriginalWeaponReconcileEntry(int original) {
    return original==5 || original==6 || original==10 || original==36 ||
        original==37 || original==42 || original==46;
}

/* Complete per-frame original ClientThink_checkWeapons inventory consumer. */
static qboolean G_NITMOD_ReconcileWeaponDenied(gentity_t *ent,int weapon,int pickup) {
    nitmodWeaponPolicyResult_t result=G_NITMOD_EvaluateServerWeaponPolicy(ent,weapon,pickup,1);
    return result.limit!=NITMOD_LIMIT_INVALID && result.decision==NITMOD_WEAPON_DENY;
}

void G_NITMOD_CheckClientWeapons(gentity_t *ent,int warMode) {
    gclient_t *cl;
    int original,weapon,changed;
    if(!ent || !ent->client || !G_NITMOD_CanCheckWeapons(ent,ent->client->pers.nitmodDemoClient))return;
    cl=ent->client;
    G_NITMOD_ApplyWarEntry(ent,&cl->nitmodWarState,warMode,cl->pers.nitmodDemoClient);
    for(original=0;original<52;++original) {
        weapon=NITMOD_NativeWeaponId(original);
        if(weapon<0 || !G_NITMOD_OriginalWeaponReconcileEntry(original))continue;
        if(COM_BitCheck(cl->ps.weapons,weapon) && G_NITMOD_ReconcileWeaponDenied(ent,weapon,1)) {
            if(weapon==WP_GPG40 || weapon==WP_M7) {
                COM_BitClear(cl->ps.weapons,weapon);
                if(cl->sess.rifleGrenadeStatus){cl->sess.rifleGrenadeStatus=0;ClientUserinfoChanged(ent-g_entities);}
            } else {
                G_DropWeapon(ent,weapon);
                changed=0;
                if(G_NITMOD_ReconcileWeaponDenied(ent,cl->sess.latchPlayerWeapon,0)) {
                    cl->sess.latchPlayerWeapon=BG_PlayerClassForPlayerState(&cl->ps)->classWeapons[0];changed=1;
                }
                if(cl->sess.playerWeapon!=cl->sess.latchPlayerWeapon) {
                    cl->sess.playerWeapon=cl->sess.latchPlayerWeapon;changed=1;
                }
                if(G_NITMOD_ReconcileWeaponDenied(ent,cl->sess.playerWeapon,0)) {
                    cl->sess.playerWeapon=BG_PlayerClassForPlayerState(&cl->ps)->classWeapons[0];changed=1;
                }
                if(changed)ClientUserinfoChanged(ent-g_entities);
            }
            G_NITMOD_CheckAdrenaline(ent,cl->pers.nitmodDemoClient,G_NITMOD_FirstAidUnlocks(cl),
                (unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenClasses",2));
            if(G_NITMOD_ClientSupports(ent-g_entities,NITMOD_FEATURE_WEAPON_MESSAGES))
                trap_SendServerCommand(ent-g_entities,"ncp 8");
        } else {
            G_NITMOD_CheckAdrenaline(ent,cl->pers.nitmodDemoClient,G_NITMOD_FirstAidUnlocks(cl),
                (unsigned int)G_NITMOD_LegacyCvarInteger("g_adrenClasses",2));
        }
    }
}
