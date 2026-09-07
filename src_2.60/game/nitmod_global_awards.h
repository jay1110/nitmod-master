#ifndef NITMOD_GLOBAL_AWARDS_H
#define NITMOD_GLOBAL_AWARDS_H
/* Original qagame 0x2a5700 and cgame 0x12ea60: all twelve wire rows,
 * including the deliberately unnamed team-kill award at index 2. */
typedef struct { int stat, threshold, mask; const char *title, *description; } nitmodGlobalAward_t;
static const nitmodGlobalAward_t globalAwards[] = {
    {0,1,1,"THE BEGINNING","Made his first kill!"},
    {0,100,2,"100 KILLS!","and it's not over! Hopefully..."},
    {2,1,4,"",""},
    {4,1,8,"NEED A MEDIC?","Made his first revive!"},
    {5,1,16,"WATCH YOUR STEP!","First Tripmine Kill"},
    {6,1,32,"FAT ASS!","First Goomba Kill"},
    {7,1,64,"BOOM HEADSHOT!","First scoped headshot"},
    {8,1,128,"ROASTER!","First Flamethrower kill"},
    {9,1,256,"I'M AN ENGINEER!","Constructed his first objective"},
    {10,1,512,"DESTROYER","Destroyed his first objective"},
    {12,1,1024,"REMOTE KILLER","First satchel kill"},
    {13,100,2048,"BUTCHER","100 Backstabs"}
};
#endif
