#include "nitmod_bot_handle.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
static nitmodBotHandleEntry_t entries[NITMOD_BOT_ENTITY_COUNT];
static int CheckLifecycle(void) {
    unsigned int serial, flags;
    int index, errors = 0;
    nitmodBotHandleEntry_t before[NITMOD_BOT_ENTITY_COUNT];
    if(sizeof(entries[0]) != 4 || offsetof(nitmodBotHandleEntry_t, flags) != 2 ||
       offsetof(nitmodBotHandleEntry_t, reserved) != 3) ++errors;
    for(index = 0; index < NITMOD_BOT_ENTITY_COUNT; ++index) {
        entries[index].serial = (uint16_t)index;
        entries[index].flags = (uint8_t)index;
        entries[index].reserved = (uint8_t)(index ^ 0xa5);
    }
    NITMOD_BotInitHandles(entries);
    for(index = 0; index < NITMOD_BOT_ENTITY_COUNT; ++index)
        if(entries[index].serial != 1 || entries[index].flags != (uint8_t)(index & 0xfc) ||
           entries[index].reserved != (uint8_t)(index ^ 0xa5)) ++errors;
    for(serial = 0; serial < 65536; ++serial) {
        entries[7].serial = (uint16_t)serial; entries[7].flags = 255;
        if(!NITMOD_BotAdvanceHandle(entries, 7) ||
           entries[7].serial != (serial == 65535 ? 1 : serial + 1) ||
           entries[7].flags != 252 || entries[7].reserved != (7 ^ 0xa5)) ++errors;
    }
    for(flags = 0; flags < 256; ++flags) {
        entries[7].serial = 9; entries[7].flags = (uint8_t)flags;
        NITMOD_BotAdvanceHandle(entries, 7);
        if(entries[7].serial != 10 || entries[7].flags != (flags & 252)) ++errors;
    }
    memcpy(before, entries, sizeof(entries));
    if(NITMOD_BotAdvanceHandle(entries, -1) || NITMOD_BotAdvanceHandle(entries, 1024) ||
       NITMOD_BotAdvanceHandle(NULL, 0) || memcmp(before, entries, sizeof(entries))) ++errors;
    NITMOD_BotInitHandles(NULL);
    /* A valid slot update must not touch any adjacent record. */
    NITMOD_BotAdvanceHandle(entries, 1023);
    if(memcmp(before, entries, sizeof(entries) - sizeof(entries[0]))) ++errors;
    printf("Bot handle lifecycle: all serials/flag bytes and 1024 reset slots, %d errors\n", errors);
    return errors;
}
static uint16_t serials[NITMOD_BOT_ENTITY_COUNT];
static unsigned char inuse[NITMOD_BOT_ENTITY_COUNT];
int main(void) {
    unsigned int value;
    int index, errors = 0;
    errors += CheckLifecycle();
    if(sizeof(nitmodBotHandle_t) != 4) ++errors;
    for(value = 0; value < 65536; ++value) {
        nitmodBotHandle_t handle = NITMOD_BotPackHandle(7, (uint16_t)value);
        serials[7] = (uint16_t)value; inuse[7] = 1;
        if(handle != ((uint32_t)value << 16 | 7) || NITMOD_BotHandleIndex(handle) != 7 ||
           NITMOD_BotHandleSerial(handle) != value || NITMOD_BotResolveHandle(handle, serials, inuse) != 7) ++errors;
        serials[7] = (uint16_t)(value + 1);
        if(NITMOD_BotResolveHandle(handle, serials, inuse) != -1) ++errors;
    }
    for(index = 0; index < NITMOD_BOT_ENTITY_COUNT; ++index) {
        nitmodBotHandle_t handle = NITMOD_BotPackHandle(index, 0xffff);
        serials[index] = 0xffff; inuse[index] = 1;
        if(NITMOD_BotResolveHandle(handle, serials, inuse) != index) ++errors;
        inuse[index] = 0; serials[index] = 1;
        if(NITMOD_BotResolveHandle(handle, serials, inuse) !=
           (index == NITMOD_BOT_WORLD_INDEX ? index : -1)) ++errors;
    }
    for(value = 1024; value < 65536; ++value)
        if(NITMOD_BotResolveHandle(UINT32_C(0xabcd0000) | value, serials, inuse) != -1) ++errors;
    if(NITMOD_BotPackHandle(-1, 99) != NITMOD_BOT_INVALID_HANDLE ||
       NITMOD_BotPackHandle(1024, 99) != NITMOD_BOT_INVALID_HANDLE ||
       NITMOD_BotResolveHandle(7, 0, inuse) != -1 ||
       NITMOD_BotResolveHandle(7, serials, 0) != -1) ++errors;
    printf("Bot handles: all 65536 serials and index bit patterns checked, %d errors\n", errors);
    return errors != 0;
}
