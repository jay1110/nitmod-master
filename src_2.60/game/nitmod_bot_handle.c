#include "nitmod_bot_handle.h"

void NITMOD_BotInitHandles(nitmodBotHandleEntry_t entries[NITMOD_BOT_ENTITY_COUNT]) {
    int index;
    if(!entries) return;
    for(index = 0; index < NITMOD_BOT_ENTITY_COUNT; ++index) {
        entries[index].serial = 1;
        entries[index].flags &= 0xfc;
    }
}
int NITMOD_BotAdvanceHandle(nitmodBotHandleEntry_t entries[NITMOD_BOT_ENTITY_COUNT], int index) {
    uint16_t serial;
    if(!entries || index < 0 || index >= NITMOD_BOT_ENTITY_COUNT) return 0;
    serial = (uint16_t)(entries[index].serial + 1u);
    entries[index].serial = serial ? serial : 1;
    entries[index].flags &= 0xfc;
    return 1;
}

nitmodBotHandle_t NITMOD_BotPackHandle(int index, uint16_t serial) {
    if(index < 0 || index >= NITMOD_BOT_ENTITY_COUNT) return NITMOD_BOT_INVALID_HANDLE;
    return ((uint32_t)serial << 16) | (uint32_t)index;
}
int NITMOD_BotHandleIndex(nitmodBotHandle_t handle) {
    uint32_t index = handle & UINT32_C(0xffff);
    return index < NITMOD_BOT_ENTITY_COUNT ? (int)index : -1;
}
uint16_t NITMOD_BotHandleSerial(nitmodBotHandle_t handle) {
    return (uint16_t)(handle >> 16);
}
int NITMOD_BotResolveHandle(nitmodBotHandle_t handle,
    const uint16_t serials[NITMOD_BOT_ENTITY_COUNT],
    const unsigned char inuse[NITMOD_BOT_ENTITY_COUNT]) {
    int index = NITMOD_BotHandleIndex(handle);
    /* Original trusts the index before reading its table. Reject malformed
     * values first rather than reproducing that out-of-bounds access. */
    if(index < 0 || !serials || !inuse) return -1;
    if(index == NITMOD_BOT_WORLD_INDEX) return index;
    if(inuse[index] && serials[index] == NITMOD_BotHandleSerial(handle)) return index;
    return -1;
}
