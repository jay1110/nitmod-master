/* Full UI binding lifecycle, with engine-owned key state. */
extern qboolean Item_Bind_HandleKey(itemDef_t *, int, qboolean);
extern int BindingIDFromName(const char *);
extern void Item_Bind_Paint(itemDef_t *);
static char bindingPaint[128];
static void BindingKeyName(int key, char *out, int size) {
    Com_sprintf(out, size, "key%d", key);
}
static const char *BindingTranslate(const char *text) { return text; }
static void BindingPaint(float x, float y, float scale, vec4_t color,
    const char *text, float adjust, int limit, int style) {
    Q_strncpyz(bindingPaint, text, sizeof(bindingPaint));
}
static char bindingKeys[256][64];
static int bindingErrors, bindingRestarts;
static void BindingSet(int key, const char *command) {
    if(key < 0 || key >= 256) { fprintf(stderr, "invalid binding key %d\n", key); ++bindingErrors; return; }
    Q_strncpyz(bindingKeys[key], command, sizeof(bindingKeys[key]));
}
static void BindingGet(const char *command, int *first, int *second) {
    int i;
    *first = *second = -1;
    for(i = 0; i < 256; ++i) if(!Q_stricmp(command, bindingKeys[i])) {
        if(*first == -1) *first = i; else { *second = i; break; }
    }
}
static void BindingExecute(int when, const char *command) {
    if(when != EXEC_APPEND || strcmp(command, "in_restart\n")) ++bindingErrors;
    ++bindingRestarts;
}
static void BindingCapture(itemDef_t *item, int key) {
    if(!Item_Bind_HandleKey(item, K_ENTER, qtrue) || !Display_KeyBindPending()) ++bindingErrors;
    if(!Item_Bind_HandleKey(item, key, qtrue) || Display_KeyBindPending()) ++bindingErrors;
}
static int CheckBindings(displayContextDef_t *dc) {
    displayContextDef_t saved = *dc;
    itemDef_t item;
    int side, errors = 0;
    bindingErrors = bindingRestarts = 0;
    dc->getKeysForBinding = BindingGet; dc->setBinding = BindingSet;
    dc->executeText = BindingExecute; dc->cursorx = dc->cursory = 5;
    memset(&item, 0, sizeof(item)); item.window.rect.w = item.window.rect.h = 10;
    for(side = 0; side < 2; ++side) {
        memset(bindingKeys, 0, sizeof(bindingKeys));
        Controls_SetDefaults(side); Controls_SetConfig(qfalse);
        if(strcmp(bindingKeys[K_MOUSE2], "+attack2") || strcmp(bindingKeys['h'], "dropobj") ||
           strcmp(bindingKeys['n'], "globalstats")) ++errors;
    }
    memset(bindingKeys, 0, sizeof(bindingKeys));
    BindingSet('a', "globalstats"); BindingSet('b', "globalstats"); Controls_GetConfig();
    item.cvar = "globalstats"; BindingCapture(&item, K_BACKSPACE);
    if(*bindingKeys['a'] || *bindingKeys['b']) ++errors;
    BindingCapture(&item, 'a'); BindingCapture(&item, 'b');
    if(strcmp(bindingKeys['a'], "globalstats") || strcmp(bindingKeys['b'], "globalstats")) ++errors;
    BindingCapture(&item, 'c');
    if(*bindingKeys['a'] || *bindingKeys['b'] || strcmp(bindingKeys['c'], "globalstats")) ++errors;
    BindingCapture(&item, 'c');
    if(strcmp(bindingKeys['c'], "globalstats")) ++errors;
    /* Reassign another known command's key, keeping its other binding. */
    BindingSet('d', "dropobj"); BindingSet('e', "dropobj"); Controls_GetConfig();
    BindingCapture(&item, 'd');
    if(strcmp(bindingKeys['d'], "globalstats") || strcmp(bindingKeys['e'], "dropobj")) ++errors;
    /* Arbitrary original-menu command, absent from the default table. */
    item.cvar = "custom_menu_action";
    BindingCapture(&item, 'x'); BindingCapture(&item, 'y');
    if(strcmp(bindingKeys['x'], item.cvar) || strcmp(bindingKeys['y'], item.cvar)) ++errors;
    BindingCapture(&item, 'x');
    if(*bindingKeys['x'] || strcmp(bindingKeys['y'], item.cvar)) ++errors;
    BindingCapture(&item, K_BACKSPACE);
    if(*bindingKeys['y']) ++errors;
    {
        int before = bindingRestarts;
        BindingCapture(&item, K_ESCAPE);
        if(bindingRestarts != before) ++errors;
    }
    {
        itemDef_t other = item;
        other.cvar = "wrong_focus";
        if(!Item_Bind_HandleKey(&item, K_ENTER, qtrue)) ++errors;
        if(!Item_Bind_HandleKey(&other, 'z' | K_CHAR_FLAG, qtrue) || !Display_KeyBindPending()) ++errors;
        if(!Item_Bind_HandleKey(&other, '`', qtrue) || !Display_KeyBindPending()) ++errors;
        if(!Item_Bind_HandleKey(&other, 'z', qtrue) || Display_KeyBindPending() ||
           strcmp(bindingKeys['z'], item.cvar)) ++errors;
    }
    if(BindingIDFromName(NULL) != -1 || BindingIDFromName("") != -1) ++errors;
    dc->keynumToStringBuf = BindingKeyName;
    dc->translateString = BindingTranslate;
    dc->drawText = BindingPaint;
    item.window.flags = WINDOW_HASFOCUS | WINDOW_FOCUSPULSE;
    memset(bindingKeys, 0, sizeof(bindingKeys));
    BindingSet('a', item.cvar); BindingSet('b', item.cvar);
    Item_Bind_Paint(&item);
    if(strcmp(bindingPaint, "KEY97 or KEY98")) ++errors;
    item.cvar = NULL;
    Item_Bind_Paint(&item);
    if(strcmp(bindingPaint, "(???" ")")) ++errors;
    Item_Bind_Paint(NULL);
    memset(bindingKeys, 0, sizeof(bindingKeys)); Controls_GetConfig();
    *dc = saved;
    if(errors || bindingErrors) fprintf(stderr, "binding checks: %d state, %d callbacks\n", errors, bindingErrors);
    return errors + bindingErrors;
}
