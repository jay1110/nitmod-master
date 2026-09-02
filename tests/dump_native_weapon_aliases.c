#include "g_local.h"
#include "nitmod_weapon_clip.h"
#include "nitmod_weapon_inventory.h"
#include "nitmod_weapon_consumption.h"
#include "nitmod_weapon_reload.h"
#include "nitmod_weapon_defaults.h"
int TestRecoveredWeaponReload( void );
int TestRecoveredReloadBegin( void );
int TestRecoveredReloadDispatch( void );
/* Unrelated bg_misc entrypoints must never invoke engine services here. */
vmCvar_t g_developer, g_gametype;
void Com_Error( int level, const char *format, ... ) { abort(); }
void Com_Printf( const char *format, ... ) { abort(); }
int trap_PC_ReadToken( int handle, pc_token_t *token ) { abort(); return 0; }
int trap_PC_SourceFileAndLine( int handle, char *filename, int *line ) { abort(); return 0; }
void trap_Cvar_VariableStringBuffer( const char *name, char *buffer, int size ) {
    /* Real predictable-event helper's debug-only logging query. */
    if( strcmp(name, "showevents") || size < 2 ) abort();
    buffer[0] = '0'; buffer[1] = 0;
}
void trap_Cvar_Set( const char *name, const char *value ) { abort(); }
/* Runs real native table lookup functions; no alias fixtures. */
#ifndef NITMOD_SWITCH_HARNESS
int main( int argc, char **argv ) {
    int weapon, i, a, b, selected, want, flag, flagSupported;
    int akimbo[] = { WP_AKIMBO_COLT, WP_AKIMBO_LUGER, WP_AKIMBO_SILENCEDCOLT, WP_AKIMBO_SILENCEDLUGER };
    int sidearm[] = { WP_COLT, WP_LUGER, WP_COLT, WP_LUGER };
    int akimboClips[] = { WP_AKIMBO_COLT, WP_AKIMBO_LUGER, WP_AKIMBO_COLT, WP_AKIMBO_LUGER };
    playerState_t state, before;
    nitmodWeaponInventorySlots_t slots;
    if( argc == 2 && !strcmp(argv[1], "--switch-times") ) {
        for( a = 0; a < WP_NUM_WEAPONS; ++a ) for( b = 0; b < WP_NUM_WEAPONS; ++b ) {
            want = -19;
            i = NITMOD_ScopeSwitchDuration(a, b, &want);
            printf("%d %d %d %d\n", a, b, i, want);
        }
        return 0;
    }
    if( TestRecoveredWeaponReload() ) return 10;
    if( TestRecoveredReloadBegin() ) return 11;
    if( TestRecoveredReloadDispatch() ) return 13;
    /* Exercise the actual table, native helpers and the new selector, not
     * the controlled alias fixture used by the separate boundary test. */
    for( i = 0; i < 4; ++i ) for( a = 0; a <= 16; ++a ) for( b = 0; b <= 16; ++b ) {
        memset(&state, 0, sizeof(state));
        state.ammoclip[akimboClips[i]] = a;
        state.ammoclip[sidearm[i]] = b;
        before = state;
        want = a && (!b || (a + b) % 2 == 0) ? akimboClips[i] : sidearm[i];
        if( !NITMOD_SelectWeaponClip(&state, akimbo[i], &selected) || selected != want ||
            memcmp(&state, &before, sizeof(state)) ) return 1;
        if( !NITMOD_SelectRecoveredWeaponClip(&state, akimbo[i], &selected) || selected != want ||
            memcmp(&state, &before, sizeof(state)) ) return 6;
        if( a || b ) {
            --before.ammoclip[want];
            if( !NITMOD_ConsumeSelectedWeaponClip(&state, akimbo[i], 1, 0, 0, ammoTableMP, WP_NUM_WEAPONS) ||
                memcmp(&state, &before, sizeof(state)) ) return 2;
        }
    }
    /* Independent adrenaline selection/consumption must not touch syringes. */
    for( a = 0; a <= 16; ++a ) for( b = 0; b <= 16; ++b ) {
        memset(&state, 0, sizeof(state));
        state.ammoclip[WP_MEDIC_ADRENALINE] = a;
        state.ammoclip[WP_MEDIC_SYRINGE] = b;
        before = state;
        if( !NITMOD_SelectRecoveredWeaponClip(&state, WP_MEDIC_ADRENALINE, &selected) ||
            selected != WP_MEDIC_ADRENALINE || memcmp(&state, &before, sizeof(state)) ) return 7;
        if( a ) {
            --before.ammoclip[WP_MEDIC_ADRENALINE];
            if( !NITMOD_ConsumeWeaponClip(&state, WP_MEDIC_ADRENALINE, selected, 1, 0, 0,
                &ammoTableMP[selected]) || memcmp(&state, &before, sizeof(state)) ) return 8;
        }
    }
    memset(&state, 0, sizeof(state));
    state.ammoclip[WP_MEDIC_ADRENALINE] = -1;
    before = state;
    selected = -17;
    if( NITMOD_SelectRecoveredWeaponClip(&state, WP_MEDIC_ADRENALINE, &selected) ||
        NITMOD_SelectRecoveredWeaponClip(NULL, WP_MEDIC_ADRENALINE, &selected) ||
        NITMOD_SelectRecoveredWeaponClip(&state, WP_MEDIC_ADRENALINE, NULL) ||
        NITMOD_SelectRecoveredWeaponClip(&state, WP_NONE, &selected) ||
        selected != -17 || memcmp(&state, &before, sizeof(state)) ) return 9;
    for( weapon = -1; weapon <= WP_NUM_WEAPONS; ++weapon ) {
        slots.ammo = -7;
        slots.clip = -9;
        if( NITMOD_WeaponInventorySlots(weapon, NULL) ) return 3;
        i = NITMOD_WeaponInventorySlots(weapon, &slots);
        flag = -19;
        flagSupported = NITMOD_WeaponAutoReloadDefault(weapon, &flag);
        if( flagSupported != i || (!flagSupported && flag != -19) ||
            NITMOD_WeaponAutoReloadDefault(weapon, NULL) ) return 12;
        if( !i && (slots.ammo != -7 || slots.clip != -9) ) return 4;
        if( weapon < 0 || weapon == WP_NUM_WEAPONS ) {
            if( i ) return 5;
            continue;
        }
        printf("%d %d %d %d %d %d %d %d %d\n", weapon, (int)BG_FindAmmoForWeapon((weapon_t)weapon),
               (int)BG_FindClipForWeapon((weapon_t)weapon), i, slots.ammo, slots.clip,
               NITMOD_ReloadWeaponEligible(weapon), flag, weapAlts[weapon]);
    }
    return 0;
}
#endif
