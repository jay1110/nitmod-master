extern qboolean CG_ParseWeaponConfig(const char *, weaponInfo_t *);
static char configText[20000];
static int configLength, configReads, configCloses;
static int QDECL ConfigEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_FS_FOPENFILE) {
        const char *name = va_arg(args, const char *);
        fileHandle_t *file = va_arg(args, fileHandle_t *);
        if(strcmp(name, "test.cfg") || va_arg(args, int) != FS_READ) exit(2);
        *file = configLength < 0 ? 0 : 41;
        va_end(args); return configLength;
    }
    if(command == CG_FS_READ) {
        void *data = va_arg(args, void *);
        int size = va_arg(args, int);
        if(size != configLength || va_arg(args, int) != 41) exit(2);
        memcpy(data, configText, size); ++configReads;
    } else if(command == CG_FS_FCLOSEFILE) {
        if(va_arg(args, int) != 41) exit(2);
        ++configCloses;
    } else if(command != CG_PRINT) exit(2);
    va_end(args); return 0;
}
static int CheckWeaponConfig(void) {
    static weaponInfo_t weapon, saved;
    int format, tokens, i, errors = 0;
    const char *fields[] = {"100 ", "6 ", "20 ", "9 ", "32768 ", "1 ", "2 "};
    dllEntry(ConfigEngine);
    memset(&saved, 0, sizeof(saved));
    saved.weapAnimations[0].firstFrame = 4711;
    for(format = 0; format < 2; ++format) {
        int count = format ? 7 : 4;
        for(tokens = 0; tokens <= MAX_WP_ANIMATIONS * count; ++tokens) {
            strcpy(configText, format ? "newfmt\n" : "// animation table\n");
            for(i = 0; i < tokens; ++i) strcat(configText, fields[i % count]);
            configLength = (int)strlen(configText); configReads = configCloses = 0;
            weapon = saved;
            if(CG_ParseWeaponConfig("test.cfg", &weapon) !=
               (tokens >= WEAP_ALTSWITCHFROM * count && tokens % count == 0)) ++errors;
            if(configReads != 1 || configCloses != 1) ++errors;
            if(tokens < WEAP_ALTSWITCHFROM * count || tokens % count != 0) {
                if(memcmp(&weapon, &saved, sizeof(weapon))) ++errors;
            } else for(i = 0; i < MAX_WP_ANIMATIONS; ++i) {
                animation_t *anim = &weapon.weapAnimations[i];
                if(anim->firstFrame != 100 || anim->numFrames != 6 || anim->loopFrames != 6 ||
                   anim->frameLerp != 50 || anim->initialLerp != 50 ||
                   anim->moveSpeed != (format ? (32768 | 65536 | 512) : 0)) ++errors;
            }
        }
    }
    for(i = 0; i < 4; ++i) {
        const int lengths[] = {-1, 0, 19999, 20000};
        configLength = lengths[i]; configReads = configCloses = 0; weapon = saved;
        if(CG_ParseWeaponConfig("test.cfg", &weapon) || configReads ||
           configCloses != (configLength >= 0) || memcmp(&weapon, &saved, sizeof(weapon))) ++errors;
    }
    {
        const char *bad[] = {"100 6 nan 0", "100 6 inf 0", "100 6 1e-20 0", "100 -1 20 0",
            "100 6 -1 0", "100 6 20 junk", "100 2147483648 20 0", "100 1.5 20 0"};
        for(i = 0; i < sizeof(bad)/sizeof(bad[0]); ++i) {
            int row;
            strcpy(configText, bad[i]); strcat(configText, " ");
            for(row = 1; row < MAX_WP_ANIMATIONS; ++row) strcat(configText, "100 6 20 0 ");
            configLength = (int)strlen(configText); weapon = saved;
            if(CG_ParseWeaponConfig("test.cfg", &weapon) || memcmp(&weapon, &saved, sizeof(weapon))) ++errors;
        }
    }
    configText[0] = 0;
    for(i = 0; i < MAX_WP_ANIMATIONS; ++i) strcat(configText, "100 6 0 -1 ");
    configLength = (int)strlen(configText); weapon = saved;
    if(!CG_ParseWeaponConfig("test.cfg", &weapon)) ++errors;
    for(i = 0; i < MAX_WP_ANIMATIONS; ++i)
        if(weapon.weapAnimations[i].frameLerp != 1000 || weapon.weapAnimations[i].loopFrames != 0) ++errors;
    dllEntry(Engine);
    return errors;
}
