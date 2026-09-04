/* Read-only regression coverage using shipped, unmodified Nitmod assets. */
static char assetDefinition[12000], *assetCursor;
static const char *privateAssetRoot;
static int ReadWeaponAsset(const char *, const char *, char *, int);
static int assetErrors, assetFrees;
static int QDECL WeaponAssetEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_PC_LOAD_SOURCE) {
        if(privateAssetRoot) {
            const char *name = va_arg(args, const char *);
            if(!ReadWeaponAsset(privateAssetRoot, name, assetDefinition, sizeof(assetDefinition))) { va_end(args); return 0; }
            assetCursor = assetDefinition;
        }
        va_end(args); return 17;
    }
    if(command == CG_PC_READ_TOKEN) {
        pc_token_t *token;
        char *text;
        (void)va_arg(args, int); token = va_arg(args, pc_token_t *);
        text = COM_Parse(&assetCursor);
        memset(token, 0, sizeof(*token));
        Q_strncpyz(token->string, text, sizeof(token->string));
        if(text[0] >= '0' && text[0] <= '9') {
            token->type = TT_NUMBER; token->intvalue = atoi(text); token->floatvalue = (float)atof(text);
        }
        va_end(args); return *text != 0;
    }
    if(command == CG_MILLISECONDS) { va_end(args); return 1000; }
    if(command == CG_PC_FREE_SOURCE) ++assetFrees;
    else if(command == CG_FS_FOPENFILE) {
        (void)va_arg(args, const char *); *va_arg(args, fileHandle_t *) = 0;
        va_end(args); return -1; /* Animation files tested separately below. */
    } else if(command == CG_R_REGISTERMODEL || command == CG_R_REGISTERSKIN ||
              command == CG_R_REGISTERSHADER || command == CG_R_REGISTERSHADERNOMIP ||
              command == CG_S_REGISTERSOUND) { va_end(args); return 777; }
    else if(command == CG_PRINT) ++assetErrors;
    else if(command == CG_PC_SOURCE_FILE_AND_LINE) {
        (void)va_arg(args, int); strcpy(va_arg(args, char *), "weapon asset"); *va_arg(args, int *) = 0;
    } else { fprintf(stderr, "Unexpected weapon asset syscall %d\n", command); exit(2); }
    va_end(args); return 0;
}
static int ReadWeaponAsset(const char *root, const char *name, char *buffer, int size) {
    char path[2048];
    FILE *file;
    size_t length;
    snprintf(path, sizeof(path), "%s/%s", root, name);
    file = fopen(path, "rb");
    if(!file) return 0;
    length = fread(buffer, 1, size - 1, file);
    if(ferror(file) || !feof(file)) { fclose(file); return 0; }
    fclose(file); buffer[length] = 0; return 1;
}
static int CheckWeaponAssets(const char *root) {
    const char *configs[] = {"models/weapons2/sten/weapon.cfg",
        "models/multiplayer/knife/weapon.cfg", "models/multiplayer/tripmine/weapon.cfg"};
    const char *definitions[] = {"weapons/knife.weap", "weapons/tripmine.weap"};
    const int weapons[] = {WP_KNIFE, WP_TRIPMINE};
    static weaponInfo_t parsed, saved;
    int i, errors = 0;
    for(i = 0; i < 3; ++i) {
        if(!ReadWeaponAsset(root, configs[i], configText, sizeof(configText))) { ++errors; continue; }
        configLength = (int)strlen(configText);
        memset(&parsed, 0, sizeof(parsed)); dllEntry(ConfigEngine);
        if(!CG_ParseWeaponConfig("test.cfg", &parsed) || parsed.weapAnimations[WEAP_RAISE].numFrames <= 0)
            ++errors;
        if(i == 0 && memcmp(&parsed.weapAnimations[WEAP_DROP2], &parsed.weapAnimations[WEAP_DROP], sizeof(animation_t))) ++errors;
    }
    for(i = 0; i < 2; ++i) {
        if(!ReadWeaponAsset(root, definitions[i], assetDefinition, sizeof(assetDefinition))) { ++errors; continue; }
        saved = cg_weapons[weapons[i]]; memset(&cg_weapons[weapons[i]], 0, sizeof(saved));
        assetCursor = assetDefinition; assetErrors = assetFrees = 0; dllEntry(WeaponAssetEngine);
        CG_RegisterWeapon(weapons[i], qtrue);
        parsed = cg_weapons[weapons[i]];
        if(assetErrors || assetFrees != 1 || !parsed.handsModel ||
           !parsed.weaponModel[W_FP_MODEL].model || (i == 1 && !parsed.missileModel)) ++errors;
        cg_weapons[weapons[i]] = saved;
    }
    {
        const int ids[] = {47,48,50,51};
        static gameState_t savedGame;
        savedGame = cgs.gameState;
        SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
        privateAssetRoot = root; assetErrors = assetFrees = 0;
        dllEntry(WeaponAssetEngine);
        CG_NitmodRegisterPrivateWeaponMedia();
        for(i = 0; i < 4; ++i) {
            const weaponInfo_t *media = CG_NitmodPrivateWeaponMedia(ids[i]);
            if(!media || !media->handsModel || !media->weaponModel[W_FP_MODEL].model ||
               (i > 0 && !media->missileModel)) ++errors;
        }
        if(assetErrors || assetFrees != 4 || CG_NitmodPrivateWeaponMedia(49)) ++errors;
        privateAssetRoot = NULL;
        cgs.gameState = savedGame;
    }
    if(errors) fprintf(stderr, "weapon assets: %d failures\n", errors);
    dllEntry(Engine); return errors;
}
