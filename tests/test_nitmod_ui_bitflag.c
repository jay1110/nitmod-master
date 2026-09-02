#include "ui_local.h"
#include <stdio.h>
#include <stdlib.h>
extern void dllEntry(int (QDECL *)(int, ...));
extern qboolean Item_Parse(int, itemDef_t *);
extern void Script_ToggleCvarBit(itemDef_t *, qboolean *, char **);
extern qboolean Item_CheckBox_HandleKey(itemDef_t *, int);
extern void Item_CheckBox_Paint(itemDef_t *);
static int value, writes, drawn;
static int parsePosition, parseMask;
static int QDECL ParserSyscall(int command, ...) {
    va_list args;
    pc_token_t *token;
    static const char *tokens[] = {"{", "bitflag", "0", "}"};
    if(command != UI_PC_READ_TOKEN) exit(2);
    va_start(args, command);
    if(va_arg(args, int) != 1) exit(2);
    token = va_arg(args, pc_token_t *);
    va_end(args);
    if(parsePosition >= 4) return 0;
    memset(token, 0, sizeof(*token));
    Q_strncpyz(token->string, tokens[parsePosition], sizeof(token->string));
    if(parsePosition == 2) {
        token->type = TT_NUMBER; token->intvalue = parseMask;
        token->floatvalue = (float)parseMask;
        Com_sprintf(token->string, sizeof(token->string), "%d", parseMask);
    }
    ++parsePosition;
    return 1;
}
static void GetString(const char *name, char *out, int size) {
    if(strcmp(name, "flags")) exit(2);
    Com_sprintf(out, size, "%d", value);
}
static float GetValue(const char *name) {
    if(strcmp(name, "flags")) exit(2);
    return (float)value;
}
static void SetValue(const char *name, const char *text) {
    if(strcmp(name, "flags")) exit(2);
    value = atoi(text); ++writes;
}
static void Draw(float x, float y, float w, float h, qhandle_t shader) {
    (void)x; (void)y; (void)w; (void)h; drawn = shader;
}
int main(void) {
    displayContextDef_t dc;
    itemDef_t item;
    menuDef_t menu;
    int initial, mask, errors = 0;
    memset(&dc, 0, sizeof(dc)); memset(&item, 0, sizeof(item));
    memset(&menu, 0, sizeof(menu));
    dc.getCVarString = GetString; dc.getCVarValue = GetValue;
    dc.setCVar = SetValue; dc.drawHandlePic = Draw;
    dc.Assets.checkboxCheck = 1; dc.Assets.checkboxCheckNot = 2;
    dc.cursorx = dc.cursory = 5;
    Init_Display(&dc); String_Init();
    dllEntry(ParserSyscall);
    for(mask = 1; mask <= 16; mask <<= 1) {
        parsePosition = 0; parseMask = mask;
        if(!Item_Parse(1, &item) || parsePosition != 4 || item.bitflag != mask) ++errors;
    }
    item.parent = &menu; item.cvar = "flags";
    item.type = ITEM_TYPE_CHECKBOX; item.window.flags = WINDOW_HASFOCUS;
    item.window.rect.w = item.window.rect.h = 10;
    for(initial = 0; initial < 32; ++initial) for(mask = 1; mask <= 16; mask <<= 1) {
        char command[64], *args = command;
        qboolean abort = qfalse;
        value = initial; writes = 0; item.bitflag = mask;
        Item_CheckBox_Paint(&item);
        if(drawn != ((initial & mask) ? 1 : 2)) ++errors;
        if(!Item_CheckBox_HandleKey(&item, K_MOUSE1) || writes || value != initial) ++errors;
        Com_sprintf(command, sizeof(command), "flags %d", mask);
        Script_ToggleCvarBit(&item, &abort, &args);
        if(value != (initial ^ mask) || writes != 1 || abort) ++errors;
        Item_CheckBox_Paint(&item);
        if(drawn != ((value & mask) ? 1 : 2)) ++errors;
    }
    item.bitflag = 0; value = 3; writes = 0;
    if(!Item_CheckBox_HandleKey(&item, K_MOUSE1) || value || writes != 1) ++errors;
    if(errors) fprintf(stderr, "%d UI bitflag failures\n", errors);
    return errors != 0;
}
