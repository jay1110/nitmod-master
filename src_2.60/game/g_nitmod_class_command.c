#include "g_local.h"
#include "g_nitmod_teamcount.h"
#include "nitmod_protocol.h"

/* Original Cmd_ResetSetup_f (tail at ELF 0x66383): any of the three
 * changed latches publishes userinfo, including a class-only cancellation. */
void Cmd_ResetSetup_f(gentity_t *ent) {
    clientSession_t *session;
    int slot, changed;
    if(!ent || !ent->client || !level.clients) return;
    for(slot = 0; slot < MAX_CLIENTS; ++slot) if(ent == &g_entities[slot]) break;
    if(slot == MAX_CLIENTS || ent->client != &level.clients[slot]) return;
    session = &ent->client->sess;
    changed = session->latchPlayerType != session->playerType ||
        session->latchPlayerWeapon != session->playerWeapon ||
        session->latchPlayerWeapon2 != session->playerWeapon2;
    session->latchPlayerType = session->playerType;
    session->latchPlayerWeapon = session->playerWeapon;
    session->latchPlayerWeapon2 = session->playerWeapon2;
    if(changed) ClientUserinfoChanged(slot);
}

/* Native enum arguments, matching this tree's team/loadout protocol.
 * Original binary weapon IDs are not an alternative numbering scheme. */
void Cmd_SetClass_f( gentity_t *ent, unsigned int dwCommand, qboolean fValue ) {
    static const char *classes[] = { "Soldier", "Medic", "Engineer", "Field Ops", "Covert Ops" };
    char classText[MAX_TOKEN_CHARS], weaponText[MAX_TOKEN_CHARS], secondaryText[MAX_TOKEN_CHARS];
    char message[128], team[8];
    int slot, cls, weapon = WP_NONE, secondary = WP_NONE;
    (void)dwCommand; (void)fValue;
    if( !ent || !ent->client || !level.clients ) return;
    for( slot = 0; slot < MAX_CLIENTS; slot++ ) if( ent == &g_entities[slot] ) break;
    if( slot == MAX_CLIENTS || ent->client != &level.clients[slot] ) return;
    if( trap_Argc() < 2 ) {
        cls = ent->client->sess.latchPlayerType;
        Com_sprintf(message, sizeof(message), "print \"%s class\n\"",
            cls >= PC_SOLDIER && cls <= PC_COVERTOPS ? classes[cls] : "^1Unknown!");
        trap_SendServerCommand(slot, message);
        return;
    }
    if( ent->client->sess.sessionTeam == TEAM_AXIS ) strcpy(team, "Axis");
    else if( ent->client->sess.sessionTeam == TEAM_ALLIES ) strcpy(team, "Allies");
    else {
        trap_SendServerCommand(slot, "print \"^3Cannot pick a class unless you're on a team!\n\"");
        return;
    }
    trap_Argv(1, classText, sizeof(classText));
    trap_Argv(2, weaponText, sizeof(weaponText));
    trap_Argv(3, secondaryText, sizeof(secondaryText));
    /* Validate the weapon tuple before changing any state. Missing weapon
     * arguments retain the original zero default; malformed values reject. */
    if( (*weaponText && !NITMOD_ParseProtocolInteger(weaponText, &weapon)) ||
        (*secondaryText && !NITMOD_ParseProtocolInteger(secondaryText, &secondary)) ||
        weapon >= WP_NUM_WEAPONS || secondary >= WP_NUM_WEAPONS ) return;
    if( NITMOD_ParseProtocolInteger(classText, &cls) && cls <= PC_COVERTOPS )
        ent->client->sess.latchPlayerType = cls;
    if( !SetTeam(ent, team, qfalse, (weapon_t)weapon, (weapon_t)secondary, qtrue) ) {
        G_NITMOD_RefreshTeamPopulation();
        G_NITMOD_SetClientWeapons(ent, weapon, secondary, qtrue);
    }
}
