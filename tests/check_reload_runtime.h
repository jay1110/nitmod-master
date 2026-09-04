#include "nitmod_weapon_reload.h"
extern void PM_ReloadClip(int weapon);
extern void PM_FinishWeaponReload(void);
extern void PM_WeaponUseAmmo(int weapon,int amount);

static int CheckActiveAmmoConsumption(void) {
    pmove_t move,*saved=pm;
    playerState_t state,expected;
    nitmodWeaponInventorySlots_t slots;
    int weapon,clip,side,war,bits,amount,mode,selected,mainClip,sideClip,errors=0;
    memset(&move,0,sizeof(move)); move.ps=&state; pm=&move;
    for(weapon=1;weapon<WP_NUM_WEAPONS;++weapon) {
        if(!NITMOD_WeaponInventorySlots(weapon,&slots)) continue;
        for(clip=0;clip<3;++clip) for(side=0;side<3;++side)
        for(war=0;war<4;++war) for(bits=0;bits<4;++bits)
        for(amount=0;amount<2;++amount) for(mode=0;mode<2;++mode) {
            memset(&state,0,sizeof(state)); state.weapon=weapon;
            state.ammo[BG_FindAmmoForWeapon(weapon)]=73;
            mainClip=BG_FindClipForWeapon(weapon);
            state.ammoclip[mainClip]=clip; selected=mainClip;
            if(BG_IsAkimboWeapon(weapon)) {
                sideClip=BG_FindClipForWeapon(BG_AkimboSidearm(weapon));
                state.ammoclip[sideClip]=side;
                if(!clip || (side && ((clip^side)&1))) selected=BG_AkimboSidearm(weapon);
            }
            expected=state;
            if(!mode || amount<=state.ammoclip[selected]) {
                expected.ammoclip[selected]-=amount;
                if(mode && !expected.ammoclip[selected] && ((bits&1) || (war==1 && weapon==WP_PANZERFAUST)))
                    expected.ammoclip[selected]=ammoTableMP[selected].defaultStartingClip;
            }
            move.nitmodReloadEnabled=mode; move.nitmodWarMode=war; move.nitmodNoReload=bits;
            PM_WeaponUseAmmo(weapon,amount);
            if(memcmp(&state,&expected,sizeof(state))) ++errors;
        }
    }
    /* The no-clips path remains reserve-based, even with refill enabled. */
    memset(&state,0,sizeof(state)); state.ammo[WP_MP40]=5;
    move.noWeapClips=qtrue; move.nitmodReloadEnabled=qtrue; move.nitmodNoReload=1;
    expected=state; expected.ammo[WP_MP40]=4;
    PM_WeaponUseAmmo(WP_MP40,1);
    if(memcmp(&state,&expected,sizeof(state))) ++errors;
    pm=saved;
    if(errors) fprintf(stderr,"%d active ammo consumption failures\n",errors);
    return errors;
}

/* Exercise the production Pmove operations in both complete module links. */
static int CheckReloadRuntime(void) {
    pmove_t move, *savedPm = pm;
    pmoveExt_t ext;
    playerState_t state, expected;
    nitmodWeaponInventorySlots_t slots;
    int weapon, mode, reserve, clip, hand, id, ammo, magazine, transfer;
    int type, timer, command, toggle, animation, errors=0;
    memset(&move,0,sizeof(move)); memset(&ext,0,sizeof(ext));
    move.ps=&state; move.pmext=&ext; pm=&move;
    for(mode=0;mode<2;++mode) {
        move.nitmodReloadEnabled=mode;
        for(weapon=1;weapon<WP_NUM_WEAPONS;++weapon) {
            if(!NITMOD_WeaponInventorySlots(weapon,&slots)) continue;
            for(reserve=0;reserve<41;reserve+=5) for(clip=0;clip<41;clip+=5) {
                memset(&state,0,sizeof(state)); state.weapon=weapon; state.stats[STAT_HEALTH]=99;
                for(id=0;id<MAX_WEAPONS;++id) { state.ammo[id]=reserve; state.ammoclip[id]=clip; }
                expected=state;
                for(hand=0;hand<(BG_IsAkimboWeapon(weapon)?2:1);++hand) {
                    id=hand ? BG_AkimboSidearm(weapon) : weapon;
                    if(mode) { NITMOD_WeaponInventorySlots(id,&slots); ammo=slots.ammo; magazine=slots.clip; }
                    else { ammo=BG_FindAmmoForWeapon(id); magazine=BG_FindClipForWeapon(id); }
                    transfer=ammoTableMP[id].maxclip-expected.ammoclip[magazine];
                    if(transfer>expected.ammo[ammo]) transfer=expected.ammo[ammo];
                    expected.ammo[ammo]-=transfer; expected.ammoclip[magazine]+=transfer;
                }
                PM_ReloadClip(weapon);
                if(memcmp(&state,&expected,sizeof(state))) ++errors;
            }
            for(type=PM_NORMAL;type<=PM_INTERMISSION;++type) for(timer=-1;timer<=1;++timer)
            for(command=0;command<2;++command) for(toggle=0;toggle<2;++toggle) {
                memset(&state,0,sizeof(state)); state.weapon=weapon; state.weaponstate=WEAPON_RELOADING;
                state.pm_type=type; state.weapAnim=123 | (toggle ? ANIM_TOGGLEBIT : 0);
                expected=state; expected.weaponstate=WEAPON_READY;
                ext.weapAnimTimer=timer; move.cmd.weapon=command ? WP_COLT : WP_NONE;
                if(type<PM_DEAD && timer<=0 && command) {
                    animation=weapon==WP_GPG40 || weapon==WP_M7 || weapon==WP_SATCHEL_DET ||
                        weapon==WP_MORTAR_SET || weapon==WP_MEDIC_ADRENALINE || weapon==WP_MOBILE_MG42_SET ? WEAP_IDLE2 : WEAP_IDLE1;
                    expected.weapAnim=(toggle ? 0 : ANIM_TOGGLEBIT)|animation;
                }
                PM_FinishWeaponReload();
                if(memcmp(&state,&expected,sizeof(state))) ++errors;
            }
        }
    }
    move.nitmodReloadEnabled=qtrue;
    memset(&state,0,sizeof(state)); state.weapon=WP_AKIMBO_LUGER;
    state.weaponstate=WEAPON_RELOADING; state.ammo[WP_LUGER]=20;
    state.ammoclip[WP_LUGER]=-1; expected=state;
    PM_ReloadClip(state.weapon);
    if(memcmp(&state,&expected,sizeof(state))) ++errors;
    PM_FinishWeaponReload();
    if(memcmp(&state,&expected,sizeof(state))) ++errors;
    state.ammoclip[WP_LUGER]=0; state.weaponTime=1; expected=state;
    PM_FinishWeaponReload(); if(memcmp(&state,&expected,sizeof(state))) ++errors;
    state.weaponTime=0; state.weaponDelay=1; expected=state;
    PM_FinishWeaponReload(); if(memcmp(&state,&expected,sizeof(state))) ++errors;
    pm=savedPm;
    errors+=CheckActiveAmmoConsumption();
    if(errors) fprintf(stderr,"%d active reload failures\n",errors);
    return errors;
}
