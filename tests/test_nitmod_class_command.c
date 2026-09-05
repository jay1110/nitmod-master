#include "g_local.h"
#undef vsnprintf
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
static gclient_t clients[MAX_CLIENTS], before;
static const char *args[4] = { "setclass", "2", "23", "2" };
static int argcValue = 4, calls, refreshes, weapons, prints, orderError, teamResult;
static int primary, secondary, printedSlot;
static char selectedTeam[8], printed[128];
static int publications;
void ClientUserinfoChanged(int slot) {
    ++publications;
    if(slot != 0 || clients[0].sess.latchPlayerType != clients[0].sess.playerType ||
       clients[0].sess.latchPlayerWeapon != clients[0].sess.playerWeapon ||
       clients[0].sess.latchPlayerWeapon2 != clients[0].sess.playerWeapon2) orderError = 1;
}
int trap_Argc( void ) { return argcValue; }
void trap_Argv( int n, char *buffer, int size ) {
    strncpy(buffer, n < argcValue ? args[n] : "", size - 1); buffer[size - 1] = 0;
}
void trap_SendServerCommand( int n, const char *text ) {
    prints++; printedSlot = n; strcpy(printed, text);
}
void QDECL Com_sprintf( char *buffer, int size, const char *fmt, ... ) {
    va_list ap; va_start(ap, fmt); vsnprintf(buffer, size, fmt, ap); va_end(ap);
}
qboolean SetTeam( gentity_t *ent, char *team, qboolean force, weapon_t w1, weapon_t w2, qboolean set ) {
    calls++; strcpy(selectedTeam, team); primary = w1; secondary = w2;
    if( force || !set || ent != &g_entities[0] ) orderError = 1;
    return (qboolean)teamResult;
}
int G_NITMOD_RefreshTeamPopulation( void ) {
    refreshes++; if( !calls || weapons ) orderError = 1; return 1;
}
int G_NITMOD_SetClientWeapons( gentity_t *ent, int w1, int w2, int update ) {
    weapons++; if( !refreshes || !update || w1 != primary || w2 != secondary ) orderError = 1;
    return 1;
}
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    level.clients = clients; g_entities[0].client = &clients[0];
    clients[0].sess.sessionTeam = TEAM_AXIS;
    Cmd_SetClass_f(&g_entities[0], 0, qfalse);
    CHECK( calls == 1 && refreshes == 1 && weapons == 1 && !orderError );
    CHECK( clients[0].sess.latchPlayerType == PC_ENGINEER && primary == WP_KAR98 && secondary == WP_LUGER );
    CHECK( !strcmp(selectedTeam, "Axis") );
    calls = refreshes = weapons = 0; teamResult = 1;
    clients[0].sess.sessionTeam = TEAM_ALLIES;
    args[1] = "4"; argcValue = 2;
    Cmd_SetClass_f(&g_entities[0], 0, qfalse);
    CHECK( calls == 1 && !refreshes && !weapons && !strcmp(selectedTeam, "Allies") );
    CHECK( primary == WP_NONE && secondary == WP_NONE && clients[0].sess.latchPlayerType == PC_COVERTOPS );
    calls = 0; argcValue = 4; args[2] = "999"; before = clients[0];
    Cmd_SetClass_f(&g_entities[0], 0, qfalse);
    CHECK( !calls && !memcmp(&before, &clients[0], sizeof(before)) );
    args[2] = "1x";
    Cmd_SetClass_f(&g_entities[0], 0, qfalse);
    CHECK( !calls && !memcmp(&before, &clients[0], sizeof(before)) );
    args[2] = "0"; args[1] = "99";
    Cmd_SetClass_f(&g_entities[0], 0, qfalse);
    CHECK( calls == 1 && clients[0].sess.latchPlayerType == PC_COVERTOPS );
    calls = 0; clients[0].sess.sessionTeam = TEAM_SPECTATOR; before = clients[0];
    Cmd_SetClass_f(&g_entities[0], 0, qfalse);
    CHECK( !calls && prints == 1 && !memcmp(&before, &clients[0], sizeof(before)) );
    argcValue = 1;
    Cmd_SetClass_f(&g_entities[0], 0, qfalse);
    CHECK( prints == 2 && printedSlot == 0 && !strcmp(printed, "print \"Covert Ops class\n\"") );
    Cmd_SetClass_f(NULL, 0, qfalse);
    CHECK( prints == 2 && !orderError );
    {
        int changes;
        for(changes = 0; changes < 8; ++changes) {
            clients[0].sess.playerType = PC_MEDIC;
            clients[0].sess.playerWeapon = WP_MP40;
            clients[0].sess.playerWeapon2 = WP_LUGER;
            clients[0].sess.latchPlayerType = changes & 1 ? PC_ENGINEER : PC_MEDIC;
            clients[0].sess.latchPlayerWeapon = changes & 2 ? WP_PANZERFAUST : WP_MP40;
            clients[0].sess.latchPlayerWeapon2 = changes & 4 ? WP_COLT : WP_LUGER;
            before = clients[0]; publications = 0;
            Cmd_ResetSetup_f(&g_entities[0]);
            CHECK(publications == !!changes && !orderError);
            before.sess.latchPlayerType = before.sess.playerType;
            before.sess.latchPlayerWeapon = before.sess.playerWeapon;
            before.sess.latchPlayerWeapon2 = before.sess.playerWeapon2;
            CHECK(!memcmp(&before, &clients[0], sizeof(before)));
            Cmd_ResetSetup_f(&g_entities[0]);
            CHECK(publications == !!changes);
        }
        publications = 0;
        Cmd_ResetSetup_f(NULL);
        Cmd_ResetSetup_f(&g_entities[MAX_CLIENTS]);
        CHECK(!publications);
    }
    return 0;
}
